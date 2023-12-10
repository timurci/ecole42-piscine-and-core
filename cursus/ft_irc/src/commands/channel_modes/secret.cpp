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

void	secretChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode)
{
	(void) client;
	(void) params;

	if (mode[0] == '+')
	{
		if (channel.getMode().s)
			return;
		channel.toggleMode('s', true);
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSG(channel.getName(), "+s"));
	}
	else if (mode[0] == '-')
	{
		if (!channel.getMode().s)
			return;
		channel.toggleMode('s', false);
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSG(channel.getName(), "-s"));
	}
}
