#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

static void    banClientFromChannel(Server *server, int const client_fd, std::string &channelName, std::string client_nickname, std::string operator_nickname)
{
	std::map<std::string, Channel>::iterator it = server->getChannels().find(channelName);
    if (it->second.doesClientExist(client_nickname) == true) // si client dans la client_list
    {
        // condition is banned ? 
        if (it->second.isBanned(client_nickname) == false)
        {
            it->second.addToBanned(client_nickname);
			// send RPL to every member of the channel 
			std::map<const int, Client>::iterator it_client = server->getClients().find(client_fd);
			std::string	RPL_BAN = ":" + operator_nickname + "!" + it_client->second.getUsername() \
			+ "@localhost MODE #" + channelName + " +b " + client_nickname + "\r\n";
			broadcastToAllChannelMembers(server, it->second, RPL_BAN);
			// add flag +b to channel mode if not already
			if (it->second.getMode().find("b") == std::string::npos)
				it->second.addMode("b");
        }
        else
            std::cout << YELLOW << client_nickname << " is already banned\n" << RESET;
    }
    else // si client n'est pas dans la client list
        addToClientBuffer(server, client_fd, ERR_NOSUCHNICK(client_nickname, channelName));
}

static void    unbanClientFromChannel(Server *server, int const client_fd, std::string &channelName, std::string client_nickname, std::string operator_nickname)
{
	std::map<const int, Client>::iterator it = server->getClients().begin();
	for (it = server->getClients().begin(); it != server->getClients().end(); it++)
	{
		if (it->second.getNickname() == client_nickname)
			break ;
	}
	if (it != server->getClients().end()) // si client dans la client_list du server
    {
		std::map<std::string, Channel>::iterator it_channel = server->getChannels().find(channelName);
		if (it_channel->second.isBanned(client_nickname) == true)
		{
			it_channel->second.removeFromBanned(client_nickname);
			// send RPL to every member of the channel
			std::map<const int, Client>::iterator it_client = server->getClients().find(client_fd);
			std::string	RPL_BAN = ":" + operator_nickname + "!" + it_client->second.getUsername() \
			+ "@localhost MODE #" + channelName + " -b " + client_nickname + "\r\n";
			
			broadcastToAllChannelMembers(server, it_channel->second, RPL_BAN); 
		}
	}
	else // si client n'est pas dans la client list
        addToClientBuffer(server, client_fd, ERR_NOSUCHNICK(client_nickname, channelName));
}

void    banChannelMode(Client &client, const t_mode_info &mode_info,
					   Channel &channel, const std::string &mode_str)
{
	// datas[0] : client.getNickname()
	// datas[1] : mode_info.target
	// datas[2] : mode_str
	// datas[3] : mode_info.params
	// use channel instead of it_channel_target
	
	if (datas[3].empty() == true)
	{
		std::map<std::string, Channel>::iterator it_channel_target = server->getChannels().find(datas[1]);
		size_t pos = it_channel_target->second.getMode().find("b");
		// Add or remove mode
		if (datas[2][0] == '+')
		{
			if (pos != std::string::npos) // le mode est deja présent
				return;
			it_channel_target->second.addMode("b");
			broadcastToAllChannelMembers(server, it_channel_target->second, MODE_CHANNELMSG(datas[1], "+b"));
		}
		else // si c'est '-'
		{
			if (pos == std::string::npos) // le mode n'est pas présent
				return;
			it_channel_target->second.removeMode("b");
			broadcastToAllChannelMembers(server, it_channel_target->second, MODE_CHANNELMSG(datas[1], "-b"));
		}
		return ;
	}
    if (datas[2][0] == '+')
        banClientFromChannel(server, client_fd, datas[1], datas[3], datas[0]);
    else if (datas[2][0] == '-')
        unbanClientFromChannel(server, client_fd, datas[1], datas[3], datas[0]);
}
