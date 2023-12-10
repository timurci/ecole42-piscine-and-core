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
	const Client *client = channel.getClientByNick(client_nick);
	if (mode[0] == '+')
	{
		if (channel.isOperator(const_cast<Client&>(*client)))
		{
			operat.appendSendBuffer(ERR_ALTREADYANOPERATOR(client_nick));
			return ;
		}
		channel.addOperator(const_cast<Client&>(*client));
		(const_cast<Client&>(*client)).appendSendBuffer(RPL_YOUREOPER(client_nick));
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSGWITHPARAM(channel.getName(), "+o", client_nick));
	}
	else if (mode[0] == '-')
	{
		if (!channel.isOperator(const_cast<Client&>(*client)))
		{
			operat.appendSendBuffer(ERR_NOTANOPERATOROFCHANNEL(client_nick, channel.getName()));
			return ;
		}
		channel.dismissOperator(const_cast<Client&>(*client));
		(const_cast<Client&>(*client)).appendSendBuffer(RPL_YOURENOTOPER(client_nick, channel.getName()));	
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSGWITHPARAM(channel.getName(), "-o", client_nick));
	}

}
	


/*
void	operatorChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode)
{
	if (params.empty() == true)
		return ;
	// we check to see if the client does belong to the channel
	if (client.getNickname() != params)
	{
		client.appendSendBuffer(ERR_NOSUCHNICK(client.getNickname(), params));
		return ;
	}
	if (!channel.doesClientExist(client))
	{
		client.appendSendBuffer(ERR_USERNOTINCHANNEL(client.getNickname(), params, channel.getName()));
		return ;
	}
	//we search for the parameter operator in the operators vector.
	std::map<const int, Client*>::iterator it;
	for (it = channel.getOperators().begin(); it != channel.getOperators().end(); it ++)
	{
		if (it->second->getNickname() == params)
			break;
	}
	if (mode[0] == '+')
	{
		//if the operator that we want to asssign to the channel is already an operator 
		if (it != channel.getOperators().end())
			return ;
		
		for (it = channel.getClients().begin(); it != channel.getClients().end(); it ++)
		{
			if (it->second->getNickname() == params) 
				channel.addOperator(*it->second);
		}
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSGWITHPARAM(channel.getName(), "+o", params));
	}
	else if (mode[0] == '-')
	{
		//if the operator that we want to delete from the channel operator continer is not present then just return 
		if (it == channel.getOperators().end()) 
			return ;
		channel.getOperators().erase(it);
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSGWITHPARAM(channel.getName(), "-o", params));
	}
}
*/