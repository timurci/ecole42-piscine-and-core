#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

//static void	broadcastToChannel(Channel &channel, const Client &client, std::string reason);
static void	removeFromServer(std::map<std::string, Channel> &channel_list, const Client &killed_user);
/**
 * @brief The QUIT command is used to terminate a client’s connection to the server. 
 *  The server acknowledges this by replying with an ERROR message and closing 
 *  the connection to the client.
 * 
 * 	When connections are terminated by a client-sent QUIT command, 
 *  servers SHOULD prepend <reason> with the ASCII string "Quit: " when sending 
 *  QUIT messages to other clients, to represent that this user terminated the 
 *  connection themselves. This applies even if <reason> is empty, in which case 
 *  the reason sent to other clients SHOULD be just this "Quit: " string. 
 * 	
 *  Parameters: [<reason>]
 * 
 *  Example : [CLIENT] QUIT :Gone to have lunch   
 * 			  [SERV] ;Client exiting from the network
 * 
 * 	Source: https://modern.ircdocs.horse/#quit-message
 */
void	quit(Client &client, const t_cmd_info &cmd_info, std::map<std::string, Channel> &channel_list)
{
	std::map<std::string, Channel>::iterator  channel_itr = channel_list.begin();

	// inform the concerned user
	client.appendSendBuffer(RPL_QUIT(user_id(client.getNickname(), client.getUsername()), cmd_info.params));
	// inform all the users that share a channel w/ the user quitting
	for (; channel_itr != channel_list.end(); channel_itr++)
	{
		//std::map<const int, Client*>& 			chan_members = channel_itr->second.getClients();
		//std::map<const int, Client*>::iterator	member		 = chan_members.begin();

		if (channel_itr->second.removeClientFromChannel(client))
			channel_itr->second.broadcastToChannel(
				RPL_QUIT(user_id(client.getNickname(), client.getUsername()), cmd_info.params)
		);
		//for (; member != chan_members.end(); member++) // check all chan_members
		//{
		//	if (member->second->getClientFd() == client.getClientFd()) // erase user from the chan + inform the others 
		//	{
		//		chan_members.erase(client.getClientFd());
		//		broadcastToChannel(channel_itr->second, client, cmd_info.params);
		//		break ;
		//	}
		//}
	}
	// close the connection (no need for irssi, but nc needs it)
	client.setDeconnectionStatus(true);
	removeFromServer(channel_list, client);
}

//static void	broadcastToChannel(Channel &channel, const Client &client, std::string reason)
//{
//	std::map<const int, Client*>::iterator member = channel.getClients().begin();
//	
//	while (member != channel.getClients().end())
//	{
//		if (member->second->getClientFd() != client.getClientFd())
//			member->second->appendSendBuffer(RPL_QUIT(user_id(client.getNickname(), client.getUsername()), reason));
//		member++;
//	}
//}

static void	removeFromServer(std::map<std::string, Channel> &channel_list, const Client &killed_user)
{
	std::map<std::string, Channel>::iterator	chan;
	for (chan = channel_list.begin(); chan != channel_list.end(); chan++)
	{
		if (chan->second.doesClientExist(killed_user))
			chan->second.getClients().erase(killed_user.getClientFd());
	}
}
