#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

void	operatorChannelMode(Client &operat, const std::string &client_nick, Channel &channel, const std::string &mode)
{
	if (!channel.isOperator(operat))
	{
		operat.appendSendBuffer(ERR_NOTANOPERATOROFCHANNEL(operat.getNickname(), channel.getName()));
		return ;
	}
	if (!channel.doesClientExist(client_nick))
	{
		operat.appendSendBuffer(ERR_USERNOTINCHANNEL(client_nick, "", channel.getName()));
		return;
	}
	Client *client = channel.getClientByNick(client_nick);
	if (mode[0] == '+')
	{
		if (channel.isOperator(*client))
		{
			operat.appendSendBuffer(ERR_ALTREADYANOPERATOR(client_nick));
			return ;
		}
		channel.addOperator(*client);
		(*client).appendSendBuffer(RPL_YOUREOPER(client_nick));
		channel.broadcastToChannel(MODE_CHANNELMSGWITHPARAM(channel.getName(), "+o", client_nick));
	}
	else if (mode[0] == '-')
	{
		if (!channel.isOperator(*client))
		{
			operat.appendSendBuffer(ERR_NOTANOPERATOROFCHANNEL(client_nick, channel.getName()));
			return ;
		}
		channel.dismissOperator(*client);
		(*client).appendSendBuffer(RPL_YOURENOTOPER(client_nick, channel.getName()));	
		channel.broadcastToChannel(MODE_CHANNELMSGWITHPARAM(channel.getName(), "-o", client_nick));
	}

}
