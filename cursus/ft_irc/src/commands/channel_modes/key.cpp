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

bool    isAlpha(const std::string &str)
{
    for (size_t i=0; i < str.length(); i ++)
    {
        if (!isalpha(str[i]))
            return (false);
    }
    return (true);
}

/*
 * The keyChannelMode function in the provided C++98 IRC code handles the 
 * setting and unsetting of the channel key mode (+k and -k). This mode 
 * allows the channel to be password protected, requiring users to 
 * provide the correct password in order to join the channel.
 * also below is the mode_structure explanation
 *
    struct mode_struct
    {
	    std::string	target;	//channel name
	    std::string	mode;	//mode
	    std::string	params;	//password
    };
 * 1. The way the code is written is that we access the client and the channel that will be used throughout the function
 * 2. We also find the position of k in the mode string of the channel which we will need in the remainder of the func. 
 * 3. If no parameter has been fed to this function then we stop there as we cant set a pass word and return.
 * 4. Then we finally look to see what is required settin or unsetting security. For that we examine the first charcter
 *    of the fourth parameter ofthis function.
 * 5. Then we just add / remove "k" and set / unset password.     
 */
 /*
void	keyChannelMode(Server *server, mode_struct mode_infos, int const client_fd, std::string mode_str)
{
	//In ban.cpp we called channels because it is related to channels. Where as key is 
	//supposed to be related to clients. We start by finding the client using the file descriptor (this is supposed to be the operator client right?). 
	//Clients are keyed by fd (else where its nick).
    std::map<std::string, Client>::iterator cl_it = server->getClients().find(client_fd);
 	//find the channel using the target name. Is the target name the name of the channel as it is supposed 
	//to be the key of the map container for channels. 
    std::map<std::string, Channel>::iterator ch_it = server->getChannels().find(mode_infos.target);
	// Find the position of 'k' in the channel mode string (if i had to deal with a map container i would have had enter a key valur to find and the return can be an iterator had i initailized an iterator) in this case i just enter the string that i am searching for in the string and it returns the size_t pos of the found
	//This must be adjusted to conform with my class definition
    size_t  pos = ch_it->second.getMode().find("k");
	// If the params (password) are empty, return ()
	//In the IRC protocol, when a channel mode is set or unset (like the +k or -k mode in this case), 
	//additional parameters can be provided to modify the mode. For example, when setting a channel 
	//key (+k), a password is often specified as a parameter. Hence if there is no password stated
	//there is no point in activating the password mode fo the channel. Right?
	//Additionally deactivation may not have been requested since it would not have been activated in
	//the first place because there was never a password stated. Without a password, the channel key 
	//mode change wouldn't make sense. For example, setting the +k mode without providing a password 
	//could result in an inconsistent or insecure state for the channel, defeating the purpose of 
	//password protection.
    if (mode_infos.params.empty())
        //return
        return ;
 	//if the first character of the fourth parameter to this functionis '+' meaning activate this mode
	//rather than deactivate
    if (mode_str[0] == '+')
	{
		// if the k mode is already present in the channel mode string attribute (size_t pos from above must not be equal to std::string:npos)
        if (pos != std::string::npos)
			//then just return as it is already set. 
            return ;
		//If the password is nor alpha-numeric 
        if (!isAlpha(mode_infos.params))
		{
			//send a message to the client - it is supposed to be the operator client.
            addToClientBuffer(server, client_fd, ERR_INVALIDMODEPARAM(cl_it->second.getNickname(), mode_infos.target, "+k", mode_infos.params));
			// return
            return ;
		}
		//add "k" to the string mode attribute of channel (addMode basically does a "str" + "str") 
		ch_it->second.addMode("k"); 
		//we set the password for the channel using the second parameter of this function which is a struct_mode  
        ch_it->second.setChannelPassword(mode_infos.params);
		//we broadcast the change to all clients "a password has been set for this channel" and we inform them of the new password.
		//This time I will use the set message in the header file.
        broadcastToAllMembers(ch_it->second, MODE_CHANNELMSGWITHPARAM(mode_infos.target, "+k", mode_infos_param));
 	}
	// otherwise if the intention is to deactivate the key mode for the channel
	else
	{
		// if the k is not present in the string mode (that means there is nothing to deactivate) type size_t pos from above must be equal to std::string::npos
        if (pos == std::string::npos)       
			//just return;keyChannelMode
            return ;
		//remove mode "k" from the mode attribute of the channel using the member function 
        ch_it->target.removeMode("k");
		//remove the set parameter int the password attribute of the channel using the relevant class channel member function  
        ch_it->target.removeChannelPassword();
		//inform the clients of the channel about the updates.
        broadcastToAllMembers(ch_it->second, MODE_CHANNELMSGWITHPARAM(mode_infos.target, "-k", mode_infos_param));   //INCOMPLETE
	}
}
*/
//keyChannelMode(client, mode_info, it_target->second, *it);
void    keyChannelMode(Client &client, const std::string &params, Channel &channel, const std::string &mode)
{
    //If no password has been passed then nothing left to do.
    if (params.empty())
        return ;
    if (!isAlpha(params))
        std::cout << ERR_INVALIDMODEPARAM(client.getNickname(), channel.getName(), "+k", params) << std::endl;
    if (!channel.doesClientExist(client))
    {
        client.appendSendBuffer(ERR_USERNOTINCHANNEL(client.getNickname(), params, channel.getName()));
        return ;
    }
    if (mode[0] == '+')
    {
        channel.toggleMode('k', true);
        channel.setPassword(params);
        broadcastToAllChannelMembers2(channel, MODE_CHANNELMSGWITHPARAM(channel.getName(), "+k", params));
    }
    else if (mode[0] == '-')
    {
        channel.toggleMode('k', false);
        channel.removePassword();
        broadcastToAllChannelMembers2(channel, MODE_CHANNELMSGWITHPARAM(channel.getName(), "-k", params));
    }
}   
