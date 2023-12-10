#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

static bool			containsAtLeastOneAlphaChar(std::string str);
//static void			broadcastToAllChannelMembers(Server *server, Channel &channel, std::string user, std::string nick, std::string reason);
static std::string	getReason(std::string msg_to_parse);

/**
 * @brief The PART command removes the client from the given channel(s).
 * 
 * 	Syntax: PART <channel>{,<channel>} [<reason>]
 * 
 *  On sending a successful PART command, the user will receive a PART message 
 *  from the server for each channel they have been removed from. 
 *  <reason> is the reason that the client has left the channel(s).
 * 
 *  Numeric Replies:
 *   ERR_NEEDMOREPARAMS (461)
 *   ERR_NOSUCHCHANNEL (403)
 *   ERR_NOTONCHANNEL (442)
 * 	
 * 	Example:
 * 	[IRSSI] /PART #test,#hey :Dining
 * 	[SERVER] leaves both channels #test and #hey with the reason "Dining"
 * 	[SERVER to CLIENT]"@user_id PART #channel Dining" (for EACH channel they leave)
 */

void	part(Client &client, const t_cmd_info &cmd_info,
		  std::map<std::string, Channel> &channel_list)
{
	std::string nick		= client.getNickname();
	std::string	channel;
	t_cmd_info	n_cmd_info = cmd_info;

	if (n_cmd_info.params.empty() == true)
	{
		client.appendSendBuffer(ERR_NEEDMOREPARAMS(nick, n_cmd_info.command));
		return ;
	}
	
	std::string reason = getReason(cmd_info.params);

	n_cmd_info.params.erase(n_cmd_info.params.find(reason), reason.length()); // #chan reason" becomes "#chan "

	while (containsAtLeastOneAlphaChar(n_cmd_info.params) == true)
	{
		channel = getChannelName(n_cmd_info.params);
		n_cmd_info.params.erase(n_cmd_info.params.find(channel), channel.length()); 

		std::map<std::string, Channel>::iterator it = channel_list.find(channel);

		if (it == channel_list.end()) // a) if chan does not exist
		{
			client.appendSendBuffer(ERR_NOSUCHCHANNEL(nick, channel));
			continue ;
		}
		else if (it != channel_list.end()
				&& it->second.doesClientExist(nick) == false) // b) if chan exists and client is not a member
		{
			client.appendSendBuffer(ERR_NOTONCHANNEL(nick, channel));
			continue ;
		}
		else // c) if command is successful 
		{
			it->second.removeClientFromChannel(client);
			client.appendSendBuffer(RPL_PART(user_id(nick, client.getUsername()), channel, reason));
			//broadcastToAllChannelMembers(server, it->second, client.getUsername(), nick, reason);
		}
	}
}

static std::string	getReason(std::string msg_to_parse)
{
	std::string reason;
	
	reason.clear(); // by default let's say there is no reason = "#hey"
	
	if (msg_to_parse.find(":") != msg_to_parse.npos) // If there is a ":", there is a reason => "#hey :bonjour"
		reason.append(msg_to_parse, msg_to_parse.find(":") + 1, std::string::npos);
	return (reason); // expected outcome : "bonjour"
}

static bool			containsAtLeastOneAlphaChar(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isalpha(str[i]))
			return (true);
	}
	return (false);
}

//static void			broadcastToAllChannelMembers(Server *server, Channel &channel, std::string user, std::string nick, std::string reason)
//{
//	std::map<std::string, Client>::iterator member = channel.getClientList().begin();
//	
//	while (member != channel.getClientList().end())
//	{
//		addToClientBuffer(server, member->second.getClientFd(), RPL_PART(user_id(nick, user), channel.getName(), reason));
//		member++;
//	}
//}
