#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

static std::string	findAnyChannel(const std::string &msg_to_parse);
static std::string	getRplList(const Client &client, std::map<std::string, Channel>::iterator &channel);

/**
 * @brief If the exact name of a channel is given, the only information about 
 * 		this channel is requested; otherwise, a list of all channels will be 
 * 		displayed.
 * 
 * 	Syntax : 
 * 	[IRSSI] LIST [-yes] [<channel>]
 * 	
 * 	Numeric Replies:
 * 		RPL_LISTSTART (321) : marks the start of a channel list. 
 * 		RPL_LIST (322) : sends information about a channel to the client.
 * 		RPL_LISTEND (323) : indicates the end of a LIST response.
 * 
 * 	Examples:
 * 		/LIST
 * 		/LIST -yes => "LIST" when received by server
 * 		/LIST #ubuntu
 */
void	list(Client &client, const t_cmd_info &cmd_info,
		  std::map<std::string, Channel> &channel_list)
{
	std::string channel_to_display	= findAnyChannel(cmd_info.params);
	std::string client_nick 		= client.getNickname();
	std::string	RPL_LISTSTART		= ":localhost 321 " + client_nick + " Channel :Users Name\r\n";
	std::string	RPL_LIST;
	std::string	RPL_LISTEND 		= ":localhost 323 " + client_nick + " :End of /LIST\r\n";

	if (channel_to_display.empty()) // "/LIST" => list all channels
	{
		if (channel_list.empty()) {
			client.appendSendBuffer(RPL_LISTEND);
		} 
		else 
		{
			client.appendSendBuffer(RPL_LISTSTART);
			std::map<std::string, Channel>::iterator it = channel_list.begin();
			while (it != channel_list.end())
			{
				RPL_LIST.clear();
				if (it->second.getMode().s == false
					|| (it->second.getMode().s && it->second.doesClientExist(client.getNickname()) == true))
				{
					RPL_LIST = getRplList(client, it);
					client.appendSendBuffer(RPL_LIST);
				}
				it++;
			}
			client.appendSendBuffer(RPL_LISTEND);
		}
	}
	else
	{
		std::map<std::string, Channel>::iterator channel = channel_list.find(channel_to_display);
		if (channel == channel_list.end()
			|| (channel->second.getMode().s
				&& channel->second.doesClientExist(client) == false))
		{	
			client.appendSendBuffer(RPL_LISTEND);
		} else {
			RPL_LIST = getRplList(client, channel);
			client.appendSendBuffer(RPL_LIST);
		}
	}
	return ;
}

static std::string	findAnyChannel(const std::string &msg_to_parse)
{
	std::string	channel;
	channel.clear();

	if (msg_to_parse.empty() || msg_to_parse.find("#") == msg_to_parse.npos) // Si pas d'arg ou pas de chan (#)
		return (channel);
	else
	{
		size_t i = 0;
		while (msg_to_parse[i] && (!isalpha(msg_to_parse[i]) && !isdigit(msg_to_parse[i]) && msg_to_parse[i] != '-' && msg_to_parse[i] != '_'))
			i++;
		while (msg_to_parse[i] && (isalpha(msg_to_parse[i]) || msg_to_parse[i] == '-' || msg_to_parse[i] == '_' || isdigit(msg_to_parse[i])))
			channel += msg_to_parse[i++];
		return (channel);
	}
}

static std::string	getRplList(const Client &client, std::map<std::string, Channel>::iterator &channel)
{
	std::stringstream concat;
	
	if (channel->second.getMode().p
		&& channel->second.doesClientExist(client) == false) // do not display topic if private chan and user not in it
	{
		concat << ":localhost 322 " << client.getNickname() << " #" << channel->second.getName() << " " \
		<< channel->second.getClients().size() << " " \
		<< ":The topic of this channel is private." \
		<< "\r\n";
	} 
	else
	{
		concat << ":localhost 322 " << client.getNickname() << " #" << channel->second.getName() << " "  \
		<< channel->second.getClients().size() << " "\
		<< (channel->second.getTopic().empty() ? ":No topic set for this channel yet."  : channel->second.getTopic()) \
		<< "\r\n";
	}
	return (concat.str());			
}
