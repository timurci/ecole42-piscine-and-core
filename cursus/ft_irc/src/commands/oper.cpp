#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

static std::string	getName(std::string msg_to_parse);
static std::string	getPassword(std::string msg_to_parse);
static std::vector<t_server_op>::const_iterator	findOper(const std::string &name, const std::vector<t_server_op> &irc_op_list);


/**
 * @brief The OPER command is used by a normal user to obtain IRC operator privileges.
 * 	Both parameters are required for the command to be successful.
 *
 *  Command: OPER
 *  Parameters: <name> <password>
 *
 * Numeric Replies:
 *
 * ERR_NEEDMOREPARAMS (461)
 * ERR_PASSWDMISMATCH (464)
 * ERR_NOOPERHOST (491)
 * RPL_YOUREOPER (381)
 *
 * Example:
 *  [CLIENT] OPER foo bar
 *  [SERVER] ; Attempt to register as an operator using a name of "foo" and the password "bar".
 */
void oper(Client &client, const t_cmd_info &cmd_info,
		  const std::vector<t_server_op> &irc_op_list)
{
	std::string name		= getName(cmd_info.params);
	std::string password	= getPassword(cmd_info.params);

	if (name.empty() || password.empty())
		client.appendSendBuffer(ERR_NEEDMOREPARAMS(client.getNickname(), cmd_info.command));
	
	std::vector<t_server_op>::const_iterator it_op = findOper(name, irc_op_list);

	if (it_op == irc_op_list.end())
		client.appendSendBuffer(ERR_NOOPERHOST(client.getNickname(), name));
	else if (it_op->password != password)
		client.appendSendBuffer(ERR_PASSWDMISMATCH(client.getNickname()));
	else
	{
		client.appendSendBuffer(RPL_YOUREOPER(client.getNickname()));
		client.addMode("o");
		client.appendSendBuffer(MODE_USERMSG(client.getNickname(), "+o"));
	}
}

static std::vector<t_server_op>::const_iterator	findOper(const std::string &name, const std::vector<t_server_op> &irc_op_list)
{
	std::vector<t_server_op>::const_iterator	op;

	for (op = irc_op_list.begin(); op != irc_op_list.end(); op++)
	{
		if (op->name == name)
			break ;
	}
	return (op);
}

static std::string	getName(std::string msg_to_parse)
{
	std::string name;

	name.clear();
	if (msg_to_parse.empty() == false || msg_to_parse.find(" ") != msg_to_parse.npos)
	{
		name.insert(0, msg_to_parse, 0,
					msg_to_parse.find_last_of(" "));
	}
	return (name);
}

static std::string	getPassword(std::string msg_to_parse)
{
	std::string password;

	password.clear();
	if (msg_to_parse.empty() == false || msg_to_parse.find(" ") != msg_to_parse.npos)
	{
		password.insert(0, msg_to_parse,
					msg_to_parse.find_last_of(" ") + 1,
					msg_to_parse.size() - 1);
	}
	return (password);
}
