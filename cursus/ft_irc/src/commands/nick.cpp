#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Commands.hpp"

//static std::string	retrieveNickname(std::string msg_to_parse)
//{
//	std::string nickname;
//
//	nickname.clear(); //unnecessary?
//	if (msg_to_parse.empty())
//		return (nickname);
//	if (msg_to_parse.empty() == false && msg_to_parse[0] == ' ')
//		msg_to_parse.erase(0, 1);
//	if (msg_to_parse.empty() == false && msg_to_parse.find(' '))
//	{
//		char *str = const_cast<char *>(msg_to_parse.data());
//		nickname = strtok(str, " ");
//	}
//	if (nickname.empty())
//		nickname.clear();
//	return (nickname);
//}

//static bool	isForbidden(char c)
//{
//	if (c == ' ' || c == ',' || c == '*' || c == '?' || c == '!'
//		|| c == '@' || c == '.')
//		return (true);
//	else
//		return (false);
//}

static bool	containsInvalidCharacters(std::string nickname)
{
	if (nickname[0] == '$' || nickname[0] == ':' || nickname[0] == '#')
		return (true);
	
	if (nickname.find_first_of(" ,*?!@.") != std::string::npos)
		return (true);
	//for (size_t i = 0; i < nickname.size(); i++) {
	//		if (isForbidden(nickname[i]) == true)
	//			return (true);
	//}
	return (false);			
}

static bool	isAlreadyUsed(const std::map<const int, Client> &client_list,
						  const std::string &new_nickname)
{
	std::map<const int, Client>::const_iterator	client_itr = client_list.begin();

	while (client_itr != client_list.end())
	{
		if (client_itr->second.getNickname() == new_nickname)
			return (true);
		client_itr++;
	}
	return (false);
}

/**
 * @brief The NICK command is used to give the client a nickname or 
 * 		change the previous one.
 * 
 * 	Syntax: NICK <nickname>
 * 
 * 	Nicknames are non-empty strings with the following restrictions:
 * 	
 * 	They MUST NOT contain any of the following characters: 
 * 	- space (' '), 
 * 	- comma (','), 
 * 	- asterisk ('*'), 
 * 	- question mark ('?'), 
 * 	- exclamation mark ('!'), 
 * 	- at sign ('@'),
 * 	- dot ('.').
 * 	
 * 	They MUST NOT start with any of the following characters: 
 * 	dollar ('$'), colon (':'), diese (#).
 * 	
 * 	Numeric Replies:
 * 
 * 	ERR_NONICKNAMEGIVEN (431)
 * 	ERR_ERRONEUSNICKNAME (432)
 * 	ERR_NICKNAMEINUSE (433)
 * 	ERR_NICKCOLLISION (436)
 * 
 * 	Example:
 * 	[CLIENT] /Nick mike
 * 
 */

void	nick(Client &client, const t_cmd_info &cmd_info,
		  const std::map<const int, Client> &client_list)
{
	//std::string	nickname = retrieveNickname(cmd_info.params);
	std::string	nickname = cmd_info.params;

	if (nickname.empty())
		client.appendSendBuffer(ERR_NONICKNAMEGIVEN(client.getNickname()));
	else if (containsInvalidCharacters(nickname))
		client.appendSendBuffer( ERR_ERRONEUSNICKNAME(client.getNickname(), nickname));
	else if (isAlreadyUsed(client_list, nickname) == true)
		client.appendSendBuffer(ERR_NICKNAMEINUSE(client.getNickname(), nickname));
	else
	{
		if (client.isRegistrationDone() == true)
		{
			client.setOldNickname(client.getNickname());
			std::cout << "[Server] Nickname change registered. Old nickname is now : " << client.getOldNickname() << std::endl;
			client.setNickname(nickname);
		}
		else
		{
			client.setNickname(nickname);
			client.setOldNickname(nickname);
			client.addNbInfo(+1);
		}
	}
	client.appendSendBuffer(RPL_NICK(client.getOldNickname(), client.getUsername(), client.getNickname()));
}
