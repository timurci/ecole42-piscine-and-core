#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

/**
 * @brief The MODE command is used to set or remove options (or modes) from a given target.
 * 
 * Parameters: <target> [<modestring> [<mode arguments>...]]
 * 
 * <modestring> starts with a plus ('+', 0x2B) or minus ('-', 0x2D) character, and is made up of the following characters:
 * '+': Adds the following mode(s).
 * '-': Removes the following mode(s).
 * 'a-zA-Z': Mode letters, indicating which modes are to be added/removed.
 * 
 * User case :
 * If <modestring> is given, the supplied modes will be applied : a MODE message will be sent to the user containing the changed modes. 
 * If one or more modes sent are not implemented on the server, 
 * the server MUST apply the modes that are implemented, and then send the ERR_UMODEUNKNOWNFLAG (501) in reply along with the MODE message.
 * 
 * Channel case :
 * syntax command : /mode <channel> <+ ou -> <mode> [parametres]
 * If the user has permission to change modes on the target, the supplied modes will be applied based on the type of the mode (see below). 
 * For type A, B, and C modes, arguments will be sequentially obtained from <mode arguments>. 
 * - If a type B or C mode does not have a parameter when being set, the server MUST ignore that mode. 
 * - If a type A mode has been sent without an argument : 
 * the contents of the list MUST be sent to the user, 
 * unless it contains sensitive information the user is not allowed to access. 
 * When the server is done processing the modes, a MODE command is sent to all members of the channel containing the mode changes. 
 * Servers MAY choose to hide sensitive information when sending the mode changes.
 * 
 * Exemples :
 * - +o : /mode #cool +o MEAT (MEAT devient opérateur sur #cool)
 * Message à send aux users du channel : ':irc.example.com MODE #cool +o MEAT'; 
 * The irc.example.com server gave channel operator privileges to MEAT on #cool.
 * - +k : /mode #cool +k COOLKEY (protège le channel par le mot de passe COOLKEY)
 * - +s : /mode #cool +s (le channel devient secret)
 * - plusieur modes : /mode #cool +ts (le channel est en mode +t +s)
 * 
 * @param server
 * @param client_fd User sending a msg
 * @param cmd_infos Structure w/ prefix, command name and message
 * 
 * Useful link : https://modern.ircdocs.horse/#mode-message
 * https://www.techbull.com/techbull/guide/internet/irccommande.html
 * 
 */

//void	broadcastToAllChannelMembers(Channel &channel, const std::string &reply)
//{
//	std::map<int, Client>::iterator member = channel.getClients().begin();
//	
//	while (member != channel.getClients().end())
//	{
//		member->second.appendSendBuffer(reply);
//		member++;
//	}
//}

static void	fillModeInfos(t_mode_info *mode_info, const std::string &command)
{
	size_t	pos, pivot_pos;

	// TARGET
	pivot_pos = 0;
	pos = command.find(" ");
	if (pos == std::string::npos)
	{
		mode_info->target = command.substr(pivot_pos);
		return ;
	}
	else
	{
		mode_info->target = command.substr(pivot_pos, pos - pivot_pos);
		pivot_pos = pos + 1;
	}

	// MODE
	pos = command.find(" ", pivot_pos);
	if (pos == std::string::npos)
	{
		mode_info->mode = command.substr(pivot_pos);
		return ;
	}
	else
	{
		mode_info->mode = command.substr(pivot_pos, pos - pivot_pos);
		pivot_pos = pos + 1;
	}

	// PARAM
	mode_info->params = command.substr(pivot_pos);
}

static void	changeChannelMode(Client &client, const t_mode_info &mode_info,
						   std::map<std::string, Channel> &channel_list)
{
	std::map<std::string, Channel>::iterator it_target = channel_list.find(mode_info.target);

	if (it_target == channel_list.end())
	{
        client.appendSendBuffer(ERR_NOSUCHCHANNEL(client.getNickname(), mode_info.target));
		return ;
	}

	std::vector<std::string> mode_vector;
	int	i_pivot = 0;

	for (int i = 1; mode_info.mode[i] != 0; i++)
	{
		if (mode_info.mode[i] == '+' || mode_info.mode[i] == '-')
		{
			mode_vector.push_back(mode_info.mode.substr(i_pivot, i - i_pivot));
			i_pivot = i;
		}
	}

	mode_vector.push_back(mode_info.mode.substr(i_pivot));
	
	for (std::vector<std::string>::iterator it = mode_vector.begin();
		it != mode_vector.end(); it++)
	{
		if (it->find("b") != std::string::npos)
			banChannelMode(client, mode_info.params, it_target->second, *it);
		if (it->find("k") != std::string::npos)
			keyChannelMode(client, mode_info.params, it_target->second, *it);
		if (it->find("l") != std::string::npos)
			limitChannelMode(client, mode_info.params, it_target->second, *it);
		if (it->find("m") != std::string::npos)
			moderateChannelMode(client, mode_info.params, it_target->second, *it);
		if (it->find("o") != std::string::npos)
			operatorChannelMode(client, mode_info.params, it_target->second, *it);
	}
}

static void	modeForChannel(Client &client, const t_mode_info &mode_info,
						   std::map<std::string, Channel> &channel_list)
{
	// syntax command : /mode <channel> <+ ou -> <mode> [parametres]
	//std::map<const int, Client>::iterator it_client = server->getClients().find(client_fd);

	t_mode_info n_mode_info = mode_info;

	n_mode_info.target.erase(0,1);

	std::map<std::string, Channel>::iterator it_channel_target = channel_list.find(n_mode_info.target);

	if (it_channel_target == channel_list.end())
	{
		client.appendSendBuffer(ERR_NOSUCHCHANNEL(client.getNickname(), n_mode_info.target));
		return ;
	}

	// If <mode> is not given
	if (n_mode_info.mode.empty() == true)
	{
		if (it_channel_target->second.getClients().find(client.getClientFd()) != it_channel_target->second.getClients().end()
		&& it_channel_target->second.getPassword().empty() == false)
			client.appendSendBuffer(RPL_CHANNELMODEISWITHKEY(client.getNickname(), n_mode_info.target, it_channel_target->second.getStringMode(), it_channel_target->second.getPassword()));
		else
			client.appendSendBuffer(RPL_CHANNELMODEIS(client.getNickname(), n_mode_info.target, it_channel_target->second.getStringMode()));
		return ;
	}

	// Check si le client est operator du channel
	std::set<std::string>::iterator it = it_channel_target->second.getOperators().begin();
	for (; it != it_channel_target->second.getOperators().end(); it++)
	{
		if (*it == client.getNickname())
			break;
	}
	if (it == it_channel_target->second.getOperators().end())
	{
		client.appendSendBuffer(ERR_CHANOPRIVSNEEDED(client.getNickname(), n_mode_info.target));
		return ;
	}
	if (n_mode_info.mode[0] == '+' || n_mode_info.mode[0] == '-')
		changeChannelMode(client, n_mode_info, channel_list);
}

static void	modeForUser(Client &client, const t_mode_info &mode_info, std::map<const int, Client> &client_list)
{
	std::map<const int, Client>::iterator it_user_target = client_list.begin();

    while (it_user_target != client_list.end())
    {
    	if (it_user_target->second.getNickname() == mode_info.target)
        	break;
    	it_user_target++;
    }
	if (it_user_target == client_list.end())
	{
		client.appendSendBuffer(ERR_NOSUCHNICK(client.getNickname(), mode_info.target));
		return ;
	}
	//  If <target> is a different nick than the user who sent the command
	if (it_user_target->second.getNickname() != client.getNickname())
	{
		client.appendSendBuffer(ERR_USERSDONTMATCH(client.getNickname()));
		return ;
	}

	// If <mode> is not given
	if (mode_info.mode.empty() == true)
		client.appendSendBuffer(RPL_UMODEIS(client.getNickname(), client.getMode()));
	
	// Attribue un mode à l'user (modes autorisés 'i' & 'o' ?)
	if (mode_info.mode[0] == '+' || mode_info.mode[0] == '-')
	{
		std::string::const_iterator pos = mode_info.mode.begin();
		while (pos != mode_info.mode.end())
		{
			if (*pos == '+')
			{
				pos++;
				while (*pos != '+' && *pos != '-' && pos != mode_info.mode.end())
				{
					if (*pos == 'i')
					{
						if (it_user_target->second.getMode().find("i") == std::string::npos)
						{
							it_user_target->second.addMode("i");
							client.appendSendBuffer(MODE_USERMSG(client.getNickname(), "+i"));
						}
					}
					pos++;
				}
			}
			if (*pos == '-')
			{
				pos++;
				while (*pos != '+' && *pos != '-' && pos != mode_info.mode.end())
				{
					if (*pos == 'i')
					{
						if (it_user_target->second.getMode().find("i") != std::string::npos)
						{
							it_user_target->second.removeMode("i");
							client.appendSendBuffer(MODE_USERMSG(client.getNickname(), "-i"));
						}
					}
					if (*pos == 'o')
					{
						if (it_user_target->second.getMode().find("o") != std::string::npos)
						{
							it_user_target->second.removeMode("o");
							client.appendSendBuffer(MODE_USERMSG(client.getNickname(), "-o"));
						}
					}
					pos++;
				}
			}
		}
		if (mode_info.mode.find("O") != std::string::npos || mode_info.mode.find("r") != std::string::npos || mode_info.mode.find("w") != std::string::npos)
			client.appendSendBuffer(ERR_UMODEUNKNOWNFLAG(client.getNickname()));
	}
}

void	modeFunction(Client &client, const t_cmd_info &cmd_info,
				  std::map<const int, Client> &client_list, std::map<std::string, Channel> &channel_list)
{
	t_mode_info	mode_info;
	
	fillModeInfos(&mode_info, cmd_info.params);

	if (mode_info.target[0] == '#')
		modeForChannel(client, mode_info, channel_list);
	else
		modeForUser(client, mode_info, client_list);
}
