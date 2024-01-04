#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

void    banClientFromChannel(Channel &channel, Client &operat, std::string client_nickname)
{
    const Client *client = channel.getClientByNick(client_nickname);
    
    if (channel.isBanned(*client))
    {
		std::cout << MSG_HEADER_CHANNEL << "Client " << *client << " is already banned." << std::endl;
        return ;
    }
    channel.banClient(*client);
	channel.broadcastToChannel(RPL_BAN(user_id(operat.getNickname(), operat.getUsername()), channel.getName(), client_nickname));
}

void    unbanClientFromChannel(Channel &channel, Client &operat, std::string client_nickname)
{
    const Client *client = channel.getClientByNick(client_nickname);
    
    if (!channel.isBanned(const_cast<Client&>(*client)))
    {
		std::cout << MSG_HEADER_CHANNEL << "Client " << *client << " is already not banned." << std::endl;
        return ;
    }
    channel.restoreBannedClient(const_cast<Client&>(*client));
	channel.broadcastToChannel(RPL_UNBAN(user_id(operat.getNickname(), operat.getUsername()), channel.getName(), client_nickname));
}

void    banChannelMode(Client &operat, const std::string &client_nick, Channel &channel, const std::string &mode)
{
    //I need to check if the client is an operator.
    if (!channel.isOperator(operat))
    {
        operat.appendSendBuffer(ERR_NOTANOPERATOROFCHANNEL(operat.getNickname(), channel.getName()));
        return ;
    }
	//I need to check if the param is a member of the channel.
    if (!channel.doesClientExist(client_nick))
    {
        operat.appendSendBuffer(ERR_USERNOTINCHANNEL(client_nick, "", channel.getName()));
        return ;
    }
    //I need to check if the ban mode is active for the channel
    if (!channel.getMode().b)
    {
        channel.toggleMode('b', true);
    } 
	//then I need to direct the parameters to the relevant ban or the unban function
    if (mode[0] == '+')
        banClientFromChannel(channel, operat, client_nick);
    else if (mode[0] == '-')
        unbanClientFromChannel(channel, operat, client_nick);    
}

