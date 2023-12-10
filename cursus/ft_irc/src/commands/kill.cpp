#include "Irc.hpp"
#include "Channel.hpp"
#include "Commands.hpp"

static std::string	retrieveNickname(std::string msg);
static std::string	retrieveComment(std::string msg);
static bool			isIrcOperator(const Client &client,
							const std::vector<t_server_op> &irc_op_list);
static void			broadcastQuit(std::map<const int, Client> &client_list,
							const std::string &reply);
static std::map<const int, Client>::iterator	getClientFromNick(const std::string &nick,
												std::map<const int, Client> &client_list);
//static Client*		clientExists(Server *server, std::string nickname);
//static void			removeFromServer(Server *server, std::string killed_user);

/**
 * @brief The KILL command is used to close the connection between a given client
 * 		and the server they are connected to. KILL is a privileged command and 
 * 		is available only to IRC Operators. Clients can rejoin instantly after 
 * 		this command is performed on them.
 * 	
 * 	Syntax :
 * 	KILL <nickname> <comment>
 * 
 * 		<nickname> represents the user to be ‘killed’, and 
 * 		<comment> is shown to all users and to the user themselves upon being killed.
 * 
 * 		The <source> of the message should be the operator who performed the command.
 */
void	kill(Client &client, const t_cmd_info &cmd_info,
			std::map<const int, Client> &client_list,
			const std::vector<t_server_op> &irc_op_list)
{
	std::string killer = client.getNickname();
	std::string killed = retrieveNickname(cmd_info.params);
	std::string	comment = retrieveComment(cmd_info.params);
	std::map<const int, Client>::iterator killed_user = getClientFromNick(killed, client_list);
	
	if (killed.empty())
		client.appendSendBuffer(ERR_NEEDMOREPARAMS(killer, cmd_info.command));
	else if (killed_user == client_list.end())
		client.appendSendBuffer(ERR_NOSUCHNICK(killer, killed));
	else if (comment.empty()) // deal with this in retrieveComment()
		comment = "default";
	else if (client.getMode().find('o') == std::string::npos && isIrcOperator(client, irc_op_list) == false)
		client.appendSendBuffer(ERR_NOPRIVILEGES(killer));
	else
	{
		/* the client being killed receives the KILL message, 
		   and the <source> of the message SHOULD be the operator who performed the command. */
		killed_user->second.appendSendBuffer(RPL_KILL(user_id(killer, client.getUsername()),
												killed, comment));

		/* The user being killed and every user sharing a channel with them receives 
			a QUIT message representing that they are leaving the network. */
		std::string quit_reason = ":Killed (" + killer + " (" + comment + "))";
		broadcastQuit(client_list,
				RPL_QUIT(user_id(killed, killed_user->second.getUsername()), quit_reason));
		
		/* The user being killed then receives the ERROR message */
		std::string error_reason = ":Closing Link: localhost. Killed (" + killer + " (" + comment + "))";
		killed_user->second.appendSendBuffer(RPL_ERROR(user_id(killed, killed_user->second.getUsername()),
												 error_reason));

		/* After this, their connection is closed. */ 
		killed_user->second.setDeconnectionStatus(true);
		//removeFromServer(server, killed);
	}
}

//static void	removeFromServer(Server *server, std::string killed_user)
//{
//	std::map<std::string, Channel>&				channels = server->getChannels();
//	std::map<std::string, Channel>::iterator	chan;
//
//	for (chan = channels.begin(); chan != channels.end(); chan++)
//	{
//		if (chan->second.doesClientExist(killed_user))
//		{
//			chan->second.getClientList().erase(killed_user);
//		}
//	}
//	
//}

static std::map<const int, Client>::iterator	getClientFromNick(const std::string &nick,
												std::map<const int, Client> &client_list)
{
	std::map<const int, Client>::iterator it = client_list.begin();

	while (it != client_list.end())
	{
		if (it->second.getNickname() == nick)
			break ;
		++it;
	}
	return (it);
}

static void	broadcastQuit(std::map<const int, Client> &client_list, const std::string &reply)
{
	std::map<const int, Client>::iterator it;
	
	for (it = client_list.begin(); it != client_list.end(); it++)
		it->second.appendSendBuffer(reply);
}

static bool	isIrcOperator(const Client &client, const std::vector<t_server_op> &irc_op_list)
{
	std::vector<t_server_op>::const_iterator it;

	for (it = irc_op_list.begin(); it != irc_op_list.end(); it++)
		if (it->name == client.getNickname())
			return (true);
	return (false);
}

static std::string	retrieveNickname(std::string msg)
{
	std::string nickname;

	if (msg[0] == ' ')
		msg.erase(0,1);
	if (msg.empty())
	{
		nickname.clear();
		return (nickname);
	}
	else
	{
		if (msg.find(' ') != std::string::npos)
			nickname.insert(0, msg, 0, msg.find_first_of(' '));
		else
			nickname.insert(0, msg, 0, msg.npos);
	}
	return (nickname);
}

static std::string retrieveComment(std::string msg)
{
	std::string comment;

	if (msg[0] == ' ')
		msg.erase(0,1);
	if (msg.empty() || msg.find(' ') == std::string::npos)
	{
		comment.clear();
		return (comment);
	}
	else
	{
		if (msg.find(' ') != std::string::npos)
			comment.insert(0, msg,  msg.find_first_of(' ') + 1, msg.npos);
	}
	return (comment);
}
