#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

/**
 * @brief The NOTICE command is used to send notices between users, as well as to send notices to channels. 
 * <target> is interpreted the same way as it is for the PRIVMSG command.
 * 
 * The NOTICE message is used similarly to PRIVMSG. 
 * The difference between NOTICE and PRIVMSG is that automatic replies must never be sent in response to a NOTICE message. 
 * This rule also applies to servers – they must not send any error back to the client on receipt of a NOTICE command. 

   @param server
   @param client_fd User sending a msg
   @param cmd_infos Structure w/ prefix, command name and message

   Useful link : https://modern.ircdocs.horse/#notice-message
 * 
 */

//static void  broadcastToChannel(Server *server, int const client_fd,
//								std::map<const int, Client>::iterator it_client,
//								std::map<std::string, Channel>::iterator it_channel,
//								std::string target, std::string msg_to_send)
//{
//   
//   // Envoi le message aux users du channel 
//   std::map<std::string, Client>::iterator member = it_channel->second.getClientList().begin(); // debut de la liste des clients du channel
//   while (member != it_channel->second.getClientList().end())
//   {
//      if (member->second.getClientFd() != client_fd)   // prevent to send the message to the sender
//         addToClientBuffer(server, member->second.getClientFd(), RPL_NOTICE(it_client->second.getNickname(), it_client->second.getUsername(), target, msg_to_send));
//      member++;
//   }
//}

//static bool isUserinChannel(std::map<const int, Client>::iterator it_client,
//							std::map<std::string, Channel>::iterator it_channel)
//{
//   if (it_channel->second.getClients().find(it_client->second.getClientFd()) != it_channel->second.getClients().end())
//      return (true);
//   return (false);
//}

void	notice(Client &client, const t_cmd_info &cmd_info,
			std::map<const int, Client> &client_list,
			std::map<std::string, Channel> &channel_list)
{ 
   std::map<const int, Client>::iterator it_client = client_list.find(client.getClientFd());

   std::string target;
   std::string msg_to_send;
  
   // Parsing message 
   size_t      delimiter = cmd_info.params.rfind(":");
   if (delimiter == std::string::npos)
      return ;
   target = cmd_info.params.substr(1, delimiter - 1);
   if (target.empty())
      return ;
   msg_to_send = cmd_info.params.substr(delimiter);

   delimiter = target.find(" ");
   if (delimiter != std::string::npos) // permet de gérer le double :: et les espaces de la fin
      target.erase(delimiter);  
  
   // Channel case
   if (target[0] == '#')
   {
      std::map<std::string, Channel>::iterator it_channel = channel_list.find(target.substr(1));

		if (it_channel == channel_list.end())
			return ;
		else if (it_channel->second.doesClientExist(client) == false)
			return ;
		else
			it_channel->second.broadcastToChannel(
				RPL_NOTICE(it_client->second.getNickname(), it_client->second.getUsername(),
			   		target, msg_to_send));
   }
   // user case
   else
   {
      std::map<std::string, Channel>::iterator it_channel = channel_list.find(target); // find channel name
     
      std::map<const int, Client>::iterator it_target = client_list.begin();
      while (it_target!=client_list.end())
      {
         if (it_target->second.getNickname() == target)
             break;
         it_target++;
      }
      if (it_target == client_list.end() && it_channel == channel_list.end()) // user and channel doesn't exist
         return ;  
      else
      {
         if (it_target == client_list.end()) // si le user n'existe pas mais le channel oui (gestion channel actif)
         {
            if (it_channel->second.doesClientExist(it_client->second) == true)
			{
				target.insert(1, "#");  // ajouter le # before target
				it_channel->second.broadcastToChannel(
				RPL_NOTICE(it_client->second.getNickname(), it_client->second.getUsername(),
			   		target, msg_to_send));
            }
            else
               return ;
         }
         else
            it_target->second.appendSendBuffer(RPL_NOTICE(it_client->second.getNickname(), it_client->second.getUsername(), target, msg_to_send));    
      }
   }
}
