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
		member ++;
	}	
}

void	voiceChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode)
{
	if (params.empty() == true)
		return ;
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

	std::map<const int, Client*>::iterator it;
	for (it = channel.getVoicedClients().begin(); it != channel.getVoicedClients().end(); it ++)
	{
		if (it->second->getNickname() == params)
			break;
	}

	if (mode[0] == '+')
	{
		if (it != channel.getVoicedClients().end())
			return ;
		
		for (it = channel.getClients().begin(); it != channel.getClients().end(); it ++)
		{
			if (it->second->getNickname() == params) 
				channel.addToVoiced(*it->second);
		}
		broadcastToAllChannelMembers2(channel, RPL_ADDVOICE(client.getNickname(), client.getUsername(), channel.getName(), "+v", params));
	}

	else if (mode[0] == '-')
	{
		if (it == channel.getVoicedClients().end())
			return ;
		channel.getVoicedClients().erase(it);
		broadcastToAllChannelMembers2(channel, RPL_ADDVOICE(client.getNickname(), client.getUsername(), channel.getName(), "-v", params));
	}
}
