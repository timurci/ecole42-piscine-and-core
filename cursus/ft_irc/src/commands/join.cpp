#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

static bool			containsAtLeastOneAlphaChar(std::string str);
static std::string	retrieveKey(std::string msg_to_parse);
static void			addChannel(std::map<std::string, Channel> &channel_list, std::string const &channelName);
static void			addClientToChannel(std::map<std::string, Channel>::iterator it, Client &client);
static void			sendChanInfos(Channel &channel, Client &client);

/**
 * @brief The JOIN command indicates that the client wants to join the given channel(s), 
 * 	each channel using the given key for it. The server receiving the command checks 
 * 	whether or not the client can join the given channel, and processes the request. 
 * 
 * 	While a client is joined to a channel, they receive all relevant information about 
 * 	that channel including the JOIN, PART, KICK, and MODE messages affecting the channel. 
 * 	They receive all PRIVMSG and NOTICE messages sent to the channel, and they also 
 * 	receive QUIT messages from other clients joined to the same channel (to let them 
 * 	know those users have left the channel and the network). 
 * 
 *  Numeric Replies:
 *  
 *  ERR_NEEDMOREPARAMS (461)
 *  ERR_NOSUCHCHANNEL (403)
 *  ERR_TOOMANYchannel_list (405)
 *  ERR_BADCHANNELKEY (475)
 *  ERR_BANNEDFROMCHAN (474)
 *  ERR_CHANNELISFULL (471)
 *  ERR_INVITEONLYCHAN (473)
 *  ERR_BADCHANMASK (476)
 *  RPL_TOPIC (332)
 *  RPL_TOPICWHOTIME (333)
 *  RPL_NAMREPLY (353)
 *  RPL_ENDOFNAMES (366)
 *  
 *  Examples:
 * 	[CLIENT]  JOIN #foobar
 *  [SERVER] ; join channel #foobar.
 * 
 * 	[CLIENT]  JOIN #foo,#bar fubar,foobar
 * 	[SERVER]; join channel #foo using key "fubar" and channel #bar using key "foobar".
 */

// cmd_info.params'ı silmek yerine döngü içerisinde birden fazla kanal veya key
// olabilecegini hesaba katan bir algoritma yaz.
void	join(Client &client, const t_cmd_info &cmd_info,
		  std::map<std::string, Channel> &channel_list)
{
	std::string client_nickname = client.getNickname();
	std::string	channel_name;
	std::string	params = cmd_info.params;

	if (containsAtLeastOneAlphaChar(params) == false)
		client.appendSendBuffer(ERR_NEEDMOREPARAMS(client.getNickname(), cmd_info.command));
	while (containsAtLeastOneAlphaChar(params) == true)
	{
		channel_name.clear(); //unnecessesary?
		channel_name = getChannelName(params);

		params.erase(params.find(channel_name), channel_name.length()); 
		
		std::map<std::string, Channel>::iterator	it = channel_list.find(channel_name);

		if (it == channel_list.end())
			addChannel(channel_list, channel_name);	
		else if (it->second.getMode().k)
		{
			std::string key = retrieveKey(params);
			params.erase(params.find(key), key.length());
			if (key != it->second.getPassword())
			{
				client.appendSendBuffer(ERR_BADCHANNELKEY(client.getNickname(), channel_name));
				continue;
			}
		}

		it = channel_list.find(channel_name);
	
		if (it->second.getMode().l && (int)it->second.getClients().size() == it->second.getCapacity())
		{
			client.appendSendBuffer(ERR_CHANNELISFULL(client.getNickname(), channel_name));
			continue ;
		}

		if (it->second.getMode().b && it->second.isBanned(client) == true)
			client.appendSendBuffer(ERR_BANNEDFROMCHAN(client.getNickname(), channel_name));
		else 
		{
			addClientToChannel(it, client);
			if (it->second.getOperators().empty())
				it->second.addOperator(client);
			sendChanInfos(it->second, client);
		}
	}
	
}

/**
 * @brief If a client’s JOIN command to the server is successful, the server MUST send, in this order:
 * 
 * 	1) A JOIN message
 * 	2) The channel's TOPIC if there is one (RPL_TOPIC)
 * 	3) The NAMES of the users in this channel
 *  
 * [:msanjuan_!msanjuan@localhost 353 msanjuan_ = #hello :@msanjuan_ ]
 */
static void		sendChanInfos(Channel &channel, Client &client)
{
	std::string	nick			= client.getNickname();
	std::string username		= client.getUsername();
	std::string	channel_name	= channel.getName();
 	
	//std::map<int, Client>::iterator member = channel.getClients().begin();

	//while (member != channel.getClients().end()) //why is there a loop? you don't use member
	//{
		client.appendSendBuffer(RPL_JOIN(user_id(nick, username), channel_name));
		if (channel.getTopic().empty() == false) // why do you send topic to every user?
			client.appendSendBuffer(RPL_TOPIC(nick, channel_name, channel.getTopic()));
		
		std::string	list_of_members = getListOfMembers(channel, true);
		std::string symbol			= getSymbol(channel);

		client.appendSendBuffer(RPL_NAMREPLY(username, symbol, channel_name, list_of_members));
		client.appendSendBuffer(RPL_ENDOFNAMES(username, channel_name));
	//	member++;
	//}
}

static bool		containsAtLeastOneAlphaChar(std::string str)
{
	// If +k mode activated, the input is " #foo,#bar fubar,foobar".
	// But we only want this part : "#foo,#bar"
	
	if (str[0] == ' ')
		str.erase(0, 1);
	if (str.find(" ") != str.npos)
		str = str.substr(0, str.find(" "));
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isalpha(str[i]))
			return (true);
	}
	return (false);
}

static std::string	retrieveKey(std::string msg_to_parse)
{
	std::string	key;
	key.clear(); //unnecessesary?
	
	int	begin_pos = (msg_to_parse.find(",") == 0) ? msg_to_parse.find(",") + 1 : 0;
	
	while (msg_to_parse[begin_pos] != ',' && msg_to_parse[begin_pos])
	{
		if (msg_to_parse[begin_pos] == '_' || msg_to_parse[begin_pos] == '-'|| isalpha(msg_to_parse[begin_pos]) || isdigit(msg_to_parse[begin_pos]))
			key += msg_to_parse[begin_pos];
		begin_pos++;
	}
	return (key);
}

static void	addChannel(std::map<std::string, Channel> &channel_list, std::string const &channelName)
{
	std::map<std::string, Channel>::iterator it = channel_list.find(channelName);
	if (it != channel_list.end())
	{
		std::cout << "Channel already exists, choose an other name\n";
		return ;
	}
	Channel	channel(channelName);
	channel_list.insert(std::pair<std::string, Channel>(channelName, channel));
	std::cout << MSG_HEADER_SERVER
	<< GREEN << "Channel added #" << channelName << RESET << std::endl;
}

static void	addClientToChannel(std::map<std::string, Channel>::iterator it, Client &client)
{
	if (it->second.doesClientExist(client) == false)
		it->second.addClient(client);
		//it->second.getClients().insert(std::pair<const int, Client*>(client.getClientFd(), &client));
	else 
		std::cout << YELLOW << client.getNickname() << " is already at #" << it->first
			<< RESET << std::endl;
}
