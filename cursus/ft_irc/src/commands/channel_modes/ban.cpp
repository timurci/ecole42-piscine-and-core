#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

static void	broadcastToAllChannelMembers2(Channel &channel, std::string announcement)
{
	std::map<const int, Client*>::iterator member = channel.getClients().begin();
	
	while (member != channel.getClients().end())
	{
		member->second->appendSendBuffer(announcement);
		member++;
	}	
}

void    banClientFromChannel(Channel &channel, Client &client, std::string operator_nickname)
{
    if (channel.doesClientExist(client))
    {
        if (!channel.getMode().b)
        {
            std::cout << "Ban mode is not activated in #" << channel.getName() << std::endl;
            return ;
        }
        if (channel.getAbleClients().find(client.getClientFd()) != channel.getAbleClients().end())
        {
            channel.banClient(client);
            std::string announcement = "The channel: " + channel.getName() + ", client : "
                + client.getNickname()  + ", has been banned by the operator: " + operator_nickname + "."; 
            broadcastToAllChannelMembers2(channel, announcement);
        }
        else
			std::cout << "The client: " << client.getNickname() << ", is already banned." << std::endl; 
    }
    else
		std::cout << "The client: " << client.getNickname() << ", is not a member of the channel: " << channel.getName() << "." << std::endl;
}

void    unbanClientFromChannel(Channel &channel, Client &client, std::string operator_nickname)
{
    if (!channel.getMode().b)
    {
        channel.restoreBannedClient(client);
        std::string announcement = "The channel: " + channel.getName() + ", client : "
            + client.getNickname() + ", has been unbanned by the operator: " + operator_nickname + "."; 
        broadcastToAllChannelMembers2(channel, announcement);
    }
    else
        std::cout << "The client: " << client.getNickname() << ", was not banned." << std::endl; 
}

//banChannelMode(client, mode_info, it_target->second, *it);
void    banChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode)
{
    //we now check if the client is a member of the channel.
    if (!channel.doesClientExist(client))
    {
        client.appendSendBuffer(ERR_USERNOTINCHANNEL(client.getNickname(), params, channel.getName()));
        return ;
    }
    if (mode[0] == '+')
        banClientFromChannel(channel, client, channel.getOperators().begin()->second->getNickname());
    else if (mode[0] == '-')
        unbanClientFromChannel(channel, client, channel.getOperators().begin()->second->getNickname());
}

/*
 * This function uses the above functions to ban or unban
 * 		datas[1] is the channel name,
 * 		datas[2] is the mode command ie "+b" or "-b" 
 *		datas[3] is the client nickname
 *		datas[0] is the operator nickname. 
 */	/*
void    banChannelMode(Server *server, std::string datas[4], int const client_fd)
{
    // hence we begin by checking if the second of the string array a channel name exists.
    std::map<std::string, Channel>::iterator    ch_it = server->getChannels().find(datas[1]);
    if (ch_it == server->getChannels().end())
    {
        //	Client &client = retrieveClient(server, client_fd);
        //	client.appendSendBuffer(reply);
		//if it doesn't exist then we send a message to client to indicate error.
        Client &client = retrieveClient(server, client_fd);
        client.appendSendBuffer(ERR_NOSUCHCHANNEL(datas[0], datas[1]));
        return ;
    }
	// if the client nickname is empty.  
    if (datas[3].empty())
    { 
		// we then check if the ban mode for the channel has been set.
        if (!ch_it->second.getMode().b && datas[2][0] == '+')
		// if the function parameter datas[2][0] is '+' then
			// Set the ban mode if it's not already set
            ch_it->second.toggleMode('b', true);
    		// Broadcastif the mode change to all channel members
            std::string announcement = "Mode: b is set true";  
            broadcastToAllChannelMembers(ch_it->second, announcement);
		// if the function parameter datas[2][0] is negative or anything else
        else if (!ch_it->second.getMode().b && datas[2][0] == '-')
        { 
			//unset the ban mode.
            ch_it->second.toggleMode('b', false);
			//broadcast the update to all channel members.
            std::string announcement = "Mode: b is set false";  
            broadcastToAllChannelMembers(ch_it->second, announcement);
        }
        //return
        return ;
    }
	//depending on the sign of the mode letter we ban or unban a client from a channel 
	//by calling the above functions.
		//I have cancelled the second parameter in the above function definitions
		//datas[1] is the channel name, 
		//datas[3] is the client nickname
		//datas[0] is the operator nickname.
    //if    
    if (datas[2][0] == '+')
    {
        //ban client from the channel
        banClientFromChannel(server, datas[1], datas[3], datas[0]);
    }
    //otherwise
    else
    {
        //unban client from the channel
        unbanClientFromChannel(server, datas[1], datas[3], datas[0]);
    }
}
*/
