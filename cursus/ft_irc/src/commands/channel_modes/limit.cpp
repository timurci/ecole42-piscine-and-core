#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"
#include <cstdlib>

static void	broadcastToAllChannelMembers2(Channel &channel, std::string announcement)
{
	std::map<const int, Client*>::iterator member = channel.getClients().begin();
	
	while (member != channel.getClients().end())
	{
		member->second->appendSendBuffer(announcement);
		member++;
	}	
}


static bool	valid(Channel &channel, int limit)
{
    if (limit < 1 || limit < (int) channel.getClients().size())
    {
        return (0);
    }
    return (1);
}


void limitChannelMode(Client &operat, const std::string &limit, Channel &channel, const std::string &mode)
{
    if (!channel.isOperator(operat))
    {
        operat.appendSendBuffer(ERR_NOTANOPERATOROFCHANNEL(operat.getNickname(), channel.getName()));
        return ;
    }
    int limit_int = atoi(limit.c_str()); 
    if (mode[0] == '+')
    {   
        if (!valid(channel, limit_int))
        {
            std::ostringstream oss;
            oss << limit_int;
            std::string num_str = oss.str();
            operat.appendSendBuffer(ERR_INVALIDLIMIT(num_str));
            return ;
        }    
        channel.setCapacity(limit_int);
        broadcastToAllChannelMembers2(channel, MODE_CHANNELMSGWITHPARAM(channel.getName(), "+l", limit));
    }
    else if (mode[0] == '-')
    {   if (!channel.getMode().l)
            return ;
        channel.unsetCapacity();
        broadcastToAllChannelMembers2(channel, MODE_CHANNELMSGWITHPARAM(channel.getName(), "-l", limit));
    }
}   
