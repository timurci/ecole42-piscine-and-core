#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

static std::string	getKickedName(std::string msg_to_parse);
static void			broadcastToChannel(Channel &channel, Client &client, std::string kicked, std::string reason);
static std::string	getReason(std::string msg_to_parse);

/**
 * @brief The KICK command can be used to request the forced removal of a user 
 *  from a channel. It causes the <user> to be removed from the <channel> by force. 
 *  If no comment is given, the server SHOULD use a default message instead.
 * 
 *  Parameters: <channel> <user> *( "," <user> ) [<comment>]
 * 
 * Numeric Replies:
 * 
 * ERR_NEEDMOREPARAMS (461)
 * ERR_NOSUCHCHANNEL (403)
 * ERR_CHANOPRIVSNEEDED (482)
 * ERR_USERNOTINCHANNEL (441)
 * ERR_NOTONCHANNEL (442)
 * 
 * Example:
 * Client's request : KICK #Finnish John :Speaking English
 * 
 * Server's Response: " Command to kick John from #Finnish using "Speaking English" 
 * 						as the reason (comment)."
 *
 * @param server
 * @param cmd_infos Structure w/ prefix, command name and message
 */
void	kick(Client &client, const t_cmd_info &cmd_info, std::map<std::string, Channel> &channel_list)
{
	Client& 		requester		= client;
	std::string		requester_name	= requester.getNickname();
	std::string		channel_name	= getChannelName(cmd_info.params);
	std::string		kicked_name		= getKickedName(cmd_info.params);
	std::string		reason			= getReason(cmd_info.params);

	std::map<std::string, Channel>&			 channels 	= channel_list;
	std::map<std::string, Channel>::iterator it_chan	= channels.find(channel_name);

	if (it_chan == channels.end())
	{
		client.appendSendBuffer(ERR_NOSUCHCHANNEL(requester_name, channel_name));
		// sendServerRpl(client_fd, ERR_NOSUCHCHANNEL(requester_name, channel_name));
		return ;
	}

	const Client	*kicked_client	= it_chan->second.getClientByNick(kicked_name);

	reason = (reason.empty()) ? ":Kicked by the channel's operator" : reason;

	// DEBUG
	// std::cout << "Requester : |" << requester_name << "|" << std::endl;
	// std::cout << "Reason : |" << reason << "|" << std::endl;
	// std::cout << "Kicked : |" << kicked_name << "|" << std::endl;

	if (channel_name.empty() || kicked_name.empty())
	{
		client.appendSendBuffer(ERR_NEEDMOREPARAMS(client.getNickname(), cmd_info.command));
		// sendServerRpl(client_fd, ERR_NEEDMOREPARAMS(requester_name, cmd_infos.name));
		return ;
	}
	else if (it_chan->second.doesClientExist(client) == false)
	{
		client.appendSendBuffer(ERR_NOTONCHANNEL(client.getNickname(), channel_name));
		// sendServerRpl(client_fd, ERR_NOTONCHANNEL(requester_name, channel_name));
		return ;
	}
	else if (kicked_client == NULL)
	{
		client.appendSendBuffer(ERR_USERNOTINCHANNEL(client.getNickname(), kicked_name, channel_name));
		return ;
	}
	else if (it_chan->second.isOperator(client) == false)
	{
		client.appendSendBuffer(ERR_CHANOPRIVSNEEDED(requester_name, channel_name));
		return ;
	}
	else
	{
		broadcastToChannel(it_chan->second, requester, kicked_name, reason);
		it_chan->second.removeClientFromChannel(*kicked_client);
		//it_chan->second.getClients().erase(kicked_client->getClientFd());
		it_chan->second.addToKickedClients(kicked_name);
	}
}

static std::string	getKickedName(std::string msg_to_parse)
{
	std::string kicked;

	if (msg_to_parse[0] == ' ')
		msg_to_parse.erase(0, 1);
	kicked = msg_to_parse.substr(msg_to_parse.find(' ') + 1, (msg_to_parse.find(':') - 1 - (msg_to_parse.find(' ') + 1)));
	return (kicked);

}

static void			broadcastToChannel(Channel &channel, Client &client, std::string kicked, std::string reason)
{
	std::map<const int, Client*>::iterator member = channel.getClients().begin();
	
	while (member != channel.getClients().end())
	{
		member->second->appendSendBuffer(RPL_KICK(user_id(client.getNickname(),
											client.getUsername()), channel.getName(),
											kicked, reason));
		member++;
	}
}

static std::string	getReason(std::string msg_to_parse)
{
	std::string reason;
	
	reason.clear();
	// If a colon is present, the reason.append(...) line extracts the 
	// substring starting from the character after the colon to the end 
	// of the string (std::string::npos). 
	if (msg_to_parse.find(":") != msg_to_parse.npos) 
		reason.append(msg_to_parse, msg_to_parse.find(":") + 1, std::string::npos);
	return (reason);
}
