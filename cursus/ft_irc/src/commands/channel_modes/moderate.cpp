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

//Bu fonksiyon sadece ve sadece m modunu aktifleştiriyor yada pasifleştiriyor.
//Ancak ikinci bir fonksiyon tarafından kullanılırsa anlamı var. Sadece bu kanalın
//modere edilip edilemeyeceğini bildiriyor.
void	moderateChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode)
{
	(void) client;
	(void) params;
	 
	if (mode[0] == '+')
	{
		if (channel.getMode().m)
			return;
		channel.toggleMode('m', true);
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSG(channel.getName(), "+m"));
	}
	else if (mode[0] == '-')
	{
		if (!channel.getMode().m)
			return;
		channel.toggleMode('m', false);
		broadcastToAllChannelMembers2(channel, MODE_CHANNELMSG(channel.getName(), "-m"));
	}
}
