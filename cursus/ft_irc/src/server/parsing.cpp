#include "Irc.hpp"
#include "Server.hpp"
#include "Commands.hpp"

static std::string splitMessage(std::vector<std::string> *cmds, std::string msg)
{
	size_t		pos;
	std::string	delimiter = "\r\n";
	std::string	substr;

	while ((pos = msg.find(delimiter)) != std::string::npos)
	{
		substr = msg.substr(0, pos);
		cmds->push_back(substr);
		msg.erase(0, pos + delimiter.length());
	}
	return (msg);
}

// Refine this function
static int	parseCommand(std::string cmd_line, t_cmd_info *cmd_info)
{
	size_t	pos = 0;
	size_t	pivot_pos = 0;

	if (cmd_line.empty() == true)
		return (FAILURE);

	// :xyz' '
	// 0123[4]
	// pos = 4, pivot = 0
	// pos - pivot = 4
	// 1, pos - pivot - 1
	pos = cmd_line.find(' ');
	if (pos != std::string::npos && cmd_line[0] == ':')
	{
		cmd_info->prefix.assign(cmd_line, pivot_pos + 1, pos - pivot_pos - 1);
		pivot_pos = pos + 1;
	}

	// ' 'NICK' '
	//  4 5678[9]
	// pos = 9, pivot = 5
	// pos - pivot = 4
	if (pivot_pos > cmd_line.size())
		return (FAILURE);
	pos = cmd_line.find(' ', pivot_pos);
	if (pos != std::string::npos)
	{
		cmd_info->command.assign(cmd_line, pivot_pos, pos - pivot_pos);
		pivot_pos = pos + 1;
	}
	else
		cmd_info->command.assign(cmd_line, pivot_pos, std::string::npos);

	if (pivot_pos > cmd_line.size())
		return (SUCCESS);
	cmd_info->params.assign(cmd_line, pivot_pos, std::string::npos);

	for (size_t i = 0; i < cmd_info->command.size(); i++)
		cmd_info->command[i] = std::toupper(cmd_info->command[i]);
	
	// DEBUG
	// std::cout << "Command : |" << RED << cmd_infos.name << "|" << RESET << std::endl;
	// std::cout << "Prefix : " << BLUE << cmd_infos.prefix << RESET << std::endl;
	// std::cout << "Message : " << GREEN << cmd_infos.message << RESET << std::endl;
	return (SUCCESS);
}

// Only partly registers the client in each call. NICK, USER, PASS
static void registerClient(std::map<const int, Client> &client_list,
						   Client &client, const std::string &cmd,
						   const std::string &server_password)
{
	t_cmd_info	cmd_info;

	if (parseCommand(cmd, &cmd_info) == FAILURE)
		return ;

	// Convert string to t_cmd_info, you don't want to confuse message with the command
	if (cmd_info.command.find("NICK") != std::string::npos)
		nick(client, cmd_info, client_list);
	else if (cmd_info.command.find("USER") != std::string::npos)
		user(client, cmd_info);
	else if (cmd_info.command.find("PASS") != std::string::npos)
	{
		if (pass(client, cmd_info, server_password) == SUCCESS)
			client.setConnectionPassword(true);
		else
			client.setConnectionPassword(false);
	}
}

static void execCommand(std::map<const int, Client> &client_list,
						std::map<std::string, Channel> &channel_list,
						std::vector<t_server_op> &irc_op_list,
						Client &client,
						const std::string &cmd_line)
{
	std::string	validCmds[VALID_LEN] = {
		"INVITE",
		"JOIN",
		"KICK",
		"KILL",
		"LIST",
		"MODE",
		"MOTD",
		"NAMES",
		"NICK",
		"NOTICE",
		"OPER",
		"PART",
		"PING",
		"PRIVMSG",
		"QUIT",
		"TOPIC",
		"USER",
		"WHO" // Alias for NAMES
		};

	t_cmd_info cmd_info;
	int index = 0;

	if (parseCommand(cmd_line, &cmd_info) == FAILURE)
		return ;

	while (index < VALID_LEN)
	{
		if (cmd_info.command == validCmds[index])
			break;
		index++;
	}

	switch (index + 1)
	{
		case 1: invite(client, cmd_info, client_list, channel_list); break;
		case 2: join(client, cmd_info, channel_list); break;
		case 3: kick(client, cmd_info, channel_list); break;
		case 4: kill(client, cmd_info, client_list, irc_op_list); break;
		case 5: list(client, cmd_info, channel_list); break;
		case 6: modeFunction(client, cmd_info, client_list, channel_list); break;
		case 7: motd(client, cmd_info); break;
		case 8: names(client, cmd_info, channel_list); break;
		case 9: nick(client, cmd_info, client_list); break;
    	//case 10: notice(client, cmd_info, client_list, channel_list); break;
		case 11: oper(client, cmd_info, irc_op_list); break;
		case 12: part(client, cmd_info, channel_list); break;
		case 13: ping(client, cmd_info); break;
		case 14: privmsg(client, cmd_info, client_list, channel_list); break;
		case 15: quit(client, cmd_info, channel_list); break;
		case 16: topic(client, cmd_info, channel_list); break;
		case 17: user(client, cmd_info); break;
		case 18: names(client, cmd_info, channel_list); break;
		default:
			client.appendSendBuffer(ERR_UNKNOWNCOMMAND(client.getNickname(), cmd_info.command));
	}
}

void Server::parseMessage(Client &client)
{
	std::vector<std::string>	cmds;
	std::string					buf_tail;

	buf_tail = splitMessage(&cmds, client.getRecvBuffer());
	client.resetRecvBuffer();
	client.appendRecvBuffer(buf_tail);

	for (size_t i = 0; i != cmds.size(); i++)
	{
		if (client.isRegistrationDone() == false)
		{
			if (client.hasAllInfo() == false)
			{
				registerClient(clients, client, cmds[i], this->getPassword());
				if (client.getNbInfo() == 3)
					client.sethasAllInfo(true);
			}
			if (client.hasAllInfo() == true && client.isWelcomeSent() == false)
			{
				if (client.is_valid() == SUCCESS)
				{
					sendClientRegistration(client, getDatetime());
					client.setWelcomeSent(true);
					client.setRegistrationDone(true);
				}		
				else
					throw Server::InvalidClientException();
			}
		}
		else
			execCommand(clients, channels, irc_operators, client, cmds[i]);
	}
}
