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

void	topicChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode)
{
	(void) client;
	(void) params;

	if (mode[0] == '+')
	{
		if (channel.getMode().t)
			return;
		channel.toggleMode('t', true);
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSG(channel.getName(), "+t"));
	}
	else if (mode[0] == '-')
	{
		if (!channel.getMode().t)
			return;
		channel.toggleMode('t', false);
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSG(channel.getName(), "-t"));
	}
}
