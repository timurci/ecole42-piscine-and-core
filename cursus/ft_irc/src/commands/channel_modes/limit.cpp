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

/*
    struct mode_struct
    {
	    std::string	target;	//channel name
	    std::string	mode;	//mode
	    std::string	params;	//password
    };
*/

/*
 * This function uses the above functions to ban or unban
 * 		datas[1] is the channel name,
 * 		datas[2] is the mode command ie "+b" or "-b" 
 *		datas[3] is the client nickname
 *		datas[0] is the operator nickname. 
 */

/*  limitChannelMode(client, mode_info, it_target->second, *it); */
void   limitChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode)
{
    //we convert the string limit value into an int.
    size_t limit = atoi(params.c_str());
    //if the first character of mode is + then
    if (mode[0] == '+')
    {
		// we check the validity of limit as it can be no less than the existing number of channel clients. 
        if (limit < channel.getClients().size())
            return ;
        //we set the new limit.
        channel.setCapacity(limit);
        //if l is already set true, then there is obviously nothing left to do hence 
        if (channel.getMode().l)
            //return
            return ;
		// we add the l mode to the mode string (its a basic append)
        channel.toggleMode('k', true);
        //broadcast update to the channel members using the definition MODE_CHANNELMSGWITHPARAM
        broadcastToAllChannelMembers2(channel, MODE_CHANNELMSGWITHPARAM(channel.getName(), "+l", client.getNickname()));
    }
    //else if the first character of the datas[2](mode "+l" or "-l")
    else if (mode[0] == '-')
    {
        //we indicate the limit value as -1 as to state that limit is not applicable.
        limit = -1;
        //we update the new limit value to our channel
        channel.setCapacity(limit);
        //if "l" is false in the mode struct of the channel, then we dont really need to cancel the limit as its not necessary, we 
        if (!channel.getMode().l)
            //return
            return ;
        //we remove the mode l from the mode string
        channel.toggleMode('k', false);
        //we broadcast the result to all channel members
        broadcastToAllChannelMembers2(channel, MODE_CHANNELMSG(channel.getName(), "-l"));
    }
}

