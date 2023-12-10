#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

static std::string	findChannel(std::string msg_to_parse);
/**
 * @brief The INVITE command is used to invite a user to a channel. 
 * 	The parameter <nickname> is the nickname of the person to be invited to the 
 * 	target channel <channel>.
 * 
 * 	Syntax : INVITE <nickname> <channel>
 * 
 */
void	invite(Client &client, const t_cmd_info &cmd_info, std::map<const int, Client> &client_list,
			std::map<std::string, Channel> &channel_list)
{
	std::string channel_name	= findChannel(cmd_info.params);
	std::string invited_client	= findNickname(cmd_info.params);
	
	if (invited_client.empty() || channel_name.empty())
	{
		client.appendSendBuffer(ERR_NEEDMOREPARAMS(client.getNickname(), cmd_info.command));
		return ;
	}

	// Check if the channel exists
	std::map<std::string, Channel>::iterator channel = channel_list.find(channel_name);
	if (channel == channel_list.end())
	{
		client.appendSendBuffer(ERR_NOSUCHCHANNEL(client.getNickname(), channel_name));
		return ;
	}
	
	// Check that the person inviting is a member of said channel
	if (channel->second.doesClientExist(client) == false)
	{
		client.appendSendBuffer(ERR_NOTONCHANNEL(client.getNickname(), channel_name));
		return ;
	}
	
	// Check that the invited user is not already on the channel
	if (channel->second.doesClientExist(invited_client) == true)
	{
		std::cout << RED << "DEBUG: CLIENT " << invited_client << " ALREADY EXISTS!" << RESET << std::endl;
		client.appendSendBuffer(ERR_USERONCHANNEL(client.getNickname(), invited_client, channel_name));
		return ;
	}
	
	// If all checks are successful => send a RPL_INVITING + invite to the inviting user 
	client.appendSendBuffer(RPL_INVITING(user_id(client.getNickname(), client.getUsername()), client.getNickname(), invited_client, channel_name));

	std::map<const int, Client>::iterator	it;
	for (it = client_list.begin(); it != client_list.end(); it++)
	{
		if (it->second.getNickname() == invited_client)
		{
			it->second.appendSendBuffer(RPL_INVITE(user_id(client.getNickname(), client.getUsername()), it->second.getNickname(), channel_name));
			break;
		}
	}
}

// Exemple of user input : "INVITE Wiz #foo_bar"
// 							=> msg_to_parse is " Wiz #foo_bar"
std::string	findNickname(std::string msg_to_parse)
{
	std::string nickname;
	nickname.clear();
	
	if (msg_to_parse.empty() == true)
		return (nickname);
	char *str = const_cast<char *>(msg_to_parse.data());
	nickname = strtok(str, " ");
	
	if (nickname.empty() 							// Si pas de token après INVITE
		|| nickname.find("#") != nickname.npos)		// Si le seul token est le channel
		nickname.clear();
	return (nickname);
}

std::string	findChannel(std::string msg_to_parse)
{
	std::string channel;

	if (msg_to_parse.empty() || msg_to_parse.find("#") == msg_to_parse.npos)
	{
		channel.clear();
	}
	else
	{
		channel.append(msg_to_parse, msg_to_parse.find("#") + 1, std::string::npos);
	}
	return (channel);
}
