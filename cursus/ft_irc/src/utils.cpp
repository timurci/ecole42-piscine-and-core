#include "Irc.hpp"
#include "Server.hpp"
#include "Commands.hpp"
#include "Client.hpp"

void	Server::sendServerRpl(const Client &client)
{
	const std::string&	buf = client.getSendBuffer();
	std::istringstream	buf_stream(buf);
	std::string			reply;
	size_t				pos;
	
	send(client.getClientFd(), buf.c_str(), buf.size(), 0);
	while (getline(buf_stream, reply))
	{
		pos = reply.rfind("\r\n");
		if (pos != std::string::npos)
			reply.erase(pos);
		std::cout << MSG_HEADER_SERVER << "Message sent to client\t\t";
		if (client.getNickname().empty())
			std::cout << "#" << client.getClientFd() << " [unregistered]";
		else
			std::cout << "#" << client.getClientFd() << " (" << client.getNickname() << ")";
		std::cout << "\t>> " << CYAN << reply << RESET << std::endl;
	}
}

Client*	Server::findClient(const int client_fd)
{
	std::map<const int, Client>::iterator it_client = clients.find(client_fd);
	
	if (it_client == clients.end())
		return (NULL);
	return (&it_client->second);
}
// ########################################################################

// Channel function
std::string	getListOfMembers(Channel &channel, const bool client_in_channel)
{
	std::map<const int, Client*>&			client_list	= channel.getClients();
	std::map<const int, Client*>::iterator	it;
	std::string								nick;
	std::string								members_list;

	for (it = client_list.begin(); it != client_list.end(); it++)
	{
		nick.clear();
		nick = it->second->getNickname();
		// if a member of a channel is invisible and
		// the client is not on the channel, skip
		if (it->second->getMode().find('i') != std::string::npos
			&& client_in_channel == false)
				continue;
			
		if (channel.isOperator(*it->second) == true)
			members_list += "@";
		members_list += nick;
		members_list += " ";
	}
	if (members_list.size() >= 1 && members_list[members_list.size() - 1] == ' ')
		members_list.erase(members_list.end()-1);
	return (members_list);
}

//Channel function
std::string	getChannelName(std::string msg_to_parse)
{
	std::string channel_name;
	size_t i = 0;
	while (msg_to_parse[i] && (!isalpha(msg_to_parse[i]) && !isdigit(msg_to_parse[i]) && msg_to_parse[i] != '-' && msg_to_parse[i] != '_'))
		i++;
	while (msg_to_parse[i] && (isalpha(msg_to_parse[i]) || msg_to_parse[i] == '-' || msg_to_parse[i] == '_' || isdigit(msg_to_parse[i])))
		channel_name += msg_to_parse[i++];
	return (channel_name);
}

// ?
std::string	getSymbol(Channel &channel)
{
	std::string symbol;

	if (channel.getMode().s)
		symbol += "@";
	else if (channel.getMode().p)
		symbol += "*";
	else
		symbol += "=";
	return (symbol); 
}

// Server datetime
void	Server::sendClientRegistration(Client &client, const std::string &datetime)
{
	client.appendSendBuffer(RPL_WELCOME(user_id(client.getNickname(), client.getUsername()), client.getNickname()));
	client.appendSendBuffer(RPL_YOURHOST(client.getNickname(), "42_Ftirc", "1.1"));
	client.appendSendBuffer(RPL_CREATED(client.getNickname(), datetime));
	client.appendSendBuffer(RPL_MYINFO(client.getNickname(), "localhost", "1.1", "io", "kost", "k"));
	client.appendSendBuffer(RPL_ISUPPORT(client.getNickname(), "CHANNELLEN=32 NICKLEN=9 TOPICLEN=307"));
	
	std::ifstream		data;
	char				filepath[24] = "src/config/motd.config";

	data.open(filepath);
	if (!data)
	{
		client.appendSendBuffer(ERR_NOMOTD(client.getNickname()));
		return ;
	}
	else
	{
		std::string		motd_lines;
		std::string		buf;
		
		buf = RPL_MOTDSTART(client.getNickname(), "42_Ftirc (localhost)");
		while (getline(data, motd_lines))
		{
			buf += RPL_MOTD(client.getNickname(), motd_lines);
		}
		buf += RPL_ENDOFMOTD(client.getNickname());
		client.appendSendBuffer(buf);
	}
	data.close();
}
