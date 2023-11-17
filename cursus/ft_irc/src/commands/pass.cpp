#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

//std::string	retrievePassword(std::string msg_to_parse)
//{
//	std::string	password;
//	size_t i = 0;
//	
//	password.clear();
//	
//	while (msg_to_parse[i] && msg_to_parse[i] == ' ')
//		i++;
//	while (msg_to_parse[i] && msg_to_parse[i] != ' ')
//		password += msg_to_parse[i++];
//	return (password);
//}

/**
 * @brief The PASS command is used to set a ‘connection password’.
 * The password supplied must match the one defined in the server configuration.
 * 	
 * Syntax: PASS <password>
 * 
 * Numeric replies:
 * 	ERR_NEEDMOREPARAMS (461)
 * 	ERR_ALREADYREGISTERED (462)
 * 	ERR_PASSWDMISMATCH (464)
 * 
 * Example :
 *  [CLIENT] /PASS secretpassword
 */

int		pass(Client &client, const t_cmd_info &cmd_info,
		  const std::string &server_password)
{
	//std::string	password	= retrievePassword(cmd_info.message);
	std::string	password = cmd_info.params;

	if (!server_password.empty() && password.empty() == true)
	{
		client.appendSendBuffer(ERR_NEEDMOREPARAMS(client.getNickname(), cmd_info.command));
		return (FAILURE);
	}
	else if (server_password != password)
	{
		client.appendSendBuffer(ERR_PASSWDMISMATCH(client.getNickname()));
		//if (client.isRegistrationDone() == false)
		//	client.addNbInfo(-1);
		return (FAILURE);
	}
	else
	{
		client.addNbInfo(+1);
		return (SUCCESS);
	}
}
