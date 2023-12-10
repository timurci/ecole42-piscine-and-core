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

void	privateChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode)
{
	(void) params;
	(void) client;

	if (mode[0] == '+')
	{
		if (channel.getMode().s)
			return;
		channel.toggleMode('p', true);
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSG(channel.getName(), "+p"));
	}
	else if (mode[1] == '-')
	{
		if (!channel.getMode().s)
			return;
		channel.toggleMode('p', false);
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSG(channel.getName(), "-p"));
	}
}
