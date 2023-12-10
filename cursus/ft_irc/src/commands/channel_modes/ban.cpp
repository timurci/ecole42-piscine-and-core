#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

//static void	broadcastToAllChannelMembers2(Channel &channel, std::string announcement)
//{
//	std::map<const int, Client*>::iterator member = channel.getClients().begin();
//	
//	while (member != channel.getClients().end())
//	{
//		member->second->appendSendBuffer(announcement);
//		member++;
//	}	
//}


void    banClientFromChannel(Channel &channel, Client &operat, std::string client_nickname)
{
    const Client *client = channel.getClientByNick(client_nickname);
    
    if (channel.isBanned(*client))
    {
		std::cout << MSG_HEADER_CHANNEL << "Client " << *client << " is already banned." << std::endl;
        return ;
    }
    channel.banClient(*client);
    //std::string announcement =  "Client : " + client->getNickname()  + ", has been banned by the operator: " 
    //            + operat.getNickname() + " from the channel: " + channel.getName();
	channel.broadcastToChannel(RPL_BAN(user_id(operat.getNickname(), operat.getUsername()), channel.getName(), client_nickname));
    //broadcastToAllChannelMembers2(channel, announcement);
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
    //std::string announcement =  "Client : " + client->getNickname()  + ", has been unbanned by the operator: " 
    //            + operat.getNickname() + " and restored to the channel: " + channel.getName();
    //broadcastToAllChannelMembers2(channel, announcement);
	channel.broadcastToChannel(RPL_UNBAN(user_id(operat.getNickname(), operat.getUsername()), channel.getName(), client_nickname));
}

//banChannelMode(client, mode_info.params, it_target->second, mode_info.mode);
    //öncelikle buraya gönderilen client, kanal operatörü.
    //mode_info.mode[0] den + yada - yi okuyorum.
    //channeldan channel name okuyabiliyorum
    //param hakkında ban yada unban hükmü verilen kişi   
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

