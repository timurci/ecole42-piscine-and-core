#include "Channel.hpp"


//Capacity is initialized to 100 at construction.
Channel::Channel(const std::string& theChannelName) : _name(theChannelName)
{}

Channel::~Channel()
{}

std::string&    Channel::getName()
{
    return _name;
}

void    Channel::setName(std::string theName)
{
    _name = theName;
}

std::map<const int, Client*>&	Channel::getClients()
{
    return _clients; 
}

std::map<const int, Client*>&	Channel::getAbleClients()
{
  return _ableClients; 
}

std::set<std::string>&	Channel::getBannedClients()
{
    return _bannedClients;
}

std::set<std::string>&	Channel::getKickedClients()
{
    return _kickedClients;
}

Client*	Channel::getClientByNick(const std::string &client_nick) const
{
	std::map<const int, Client *>::const_iterator	itr;

	for (itr = _clients.begin(); itr != _clients.end(); itr++)
		if (itr->second->getNickname() == client_nick)
			return (itr->second);
	return (NULL);
}

//This function can only be used when we are sure that the client nick name is 
//present in the Channel. Hence doesClientExit function must have been previously executed.
Client &Channel::getClientRefByNick(const std::string &client_nick) const
{
    
    std::map<const int, Client *>::const_iterator	it;

    for (it = _clients.begin(); it != _clients.end(); it ++)
		if (it->second->getNickname() == client_nick)
			return *(it->second);
    throw std::out_of_range("Client with nickname " + client_nick + " not found in the channel.");
}

std::string&    Channel::getTopic()
{
    return _topic;
}

void    Channel::setTopic(const std::string& theTopic)
{
    _topic = theTopic;
}

std::string& Channel::getPassword()
{
    return (_password);
}

void    Channel::setPassword(const std::string& thePassword)
{
    toggleMode('k', true);
    _password = thePassword;
}

std::set<std::string>&   Channel::getOperators()
{
    return _operators;
}

int Channel::getCapacity() const
{
    return _capacity;
}

void    Channel::setCapacity(int theCapacity)
{
    toggleMode('l', true);
    _capacity = theCapacity;
}

void    Channel::unsetCapacity()
{
    toggleMode('l', false);
}

Mode&   Channel::getMode()
{
    return _mode;
}

std::string	Channel::getStringMode(void) const
{
	char mode_str[11] = "+";

	if (_mode.t)
		strcat(mode_str, "t");
	if (_mode.m)
		strcat(mode_str, "m");
	if (_mode.l)
		strcat(mode_str, "l");
	if (_mode.k)
		strcat(mode_str, "k");
	if (_mode.s)
		strcat(mode_str, "s");
	if (_mode.p)
		strcat(mode_str, "p");
	if (_mode.v)
		strcat(mode_str, "v");
	if (_mode.o)
		strcat(mode_str, "o");
	if (_mode.b)
		strcat(mode_str, "b");

	if (strlen(mode_str) == 1)
		mode_str[0] = 0;

    return (mode_str);
}

void	Channel::broadcastToChannel(const std::string &message)
{
	std::map<const int, Client*>::iterator it = Channel::getClients().begin();
	
	while (it != Channel::getClients().end())
		it++->second->appendSendBuffer(message);
}

/**
 * @brief Adds a client to the channel.
 *
 * This function adds the specified client to the channel's list of clients, provided that
 * the channel's mode allows for it. It checks if the channel is at its user limit (if the "l" mode is set)
 * and returns 0 with a warning if the limit is reached. It also checks if the client is not already in
 * the channel's list of clients and not in the list of kicked clients. If both conditions are met, it
 * inserts the client into the list of clients and also adds the client to the list of able clients.
 *
 * @param client The client to be added to the channel.
 *
 * @return Returns 1 if the client was successfully added to the channel, or 0 if the client was
 * not added due to channel capacity or if the client is already in the channel or has been kicked.
 */
int Channel::addClient(Client& client)
{
    if (_mode.l && _clients.size() >= _capacity)
    {
        if (COMMENT)
            std::cout << MSG_HEADER_CHANNEL << client << "\t: warning! capacity breach for channel " << getName() << std::endl;
        return (0);
    }
    if (_clients.find(client.getClientFd()) == _clients.end()
        //_kickedClients.find(client.getNickname()) == _kickedClients.end()
		) 
    {
        int i = 1;
        std::pair<std::map<const int, Client*>::iterator, bool> result =_clients.insert(std::pair<const int, Client*>(client.getClientFd(), &client));
        i &= result.second;
        i &= addAbleClient(client);
        if (COMMENT && i)
            std::cout << MSG_HEADER_CHANNEL << client << " is added to clients of channel " << getName() << std::endl;
        return (i);
    }
    return (0);
}

/**
 * Add a client to the map of able clients.
 *
 * @param client The client to be added.
 * @return 1 if the client was successfully added, 0 otherwise.
 */
int Channel::addAbleClient(Client& client)
{
std::pair<std::map<const int, Client*>::iterator, bool> result = _ableClients.insert(std::pair<const int, Client*>(client.getClientFd(), &client));
if (COMMENT && result.second)
	std::cout << MSG_HEADER_CHANNEL << client << " is added to able clients of channel " << getName() << std::endl;
return result.second;
}

/**
 * @brief Kicks a client from the channel.
 *
 * This function checks if the given client exists in the channel's client list.
 * If the client is found, it performs several actions to remove the client, including
 * kicking, banning, removing operator status, and removing voice privileges if applicable.
 *
 * @param client The client to be kicked from the channel.
 * @return 1 if the client is successfully kicked and removed, 0 if the client is not found.
 */
int Channel::kickClient(Client& client)
{
    size_t  s = _clients.size();
    std::map<const int, Client*>::iterator it = _clients.find(client.getClientFd());
    if (it != _clients.end())
    {
        int i = 1;
        if (!isBanned(client))
            i &= kickAbleClient(client);
        else
            i &= dismissBannedClient(client);
        if (isOperator(client))
            i &= dismissOperator(client);
        _clients.erase(it);
        i &= (s - _clients.size());
        i &= addToKickedClients(client);
        if (COMMENT && i)
            std::cout << MSG_HEADER_CHANNEL
				<< CYAN << client << RESET
				<< " is kicked from the channel " << RED << getName() << RESET << std::endl; 
        return (i);
    }
    return (0);
}

/**
 * @brief Removes a client from the channel.
 *
 * This function checks if the given client exists in the channel's client list.
 * If the client is found, it performs several actions to remove the client, including
 * kicking, banning, removing operator status, and removing voice privileges if applicable.
 *
 * @param client The client to be removed from the channel.
 * @return 1 if the client is successfully removed, 0 if the client is not found.
 */
int Channel::removeClientFromChannel(const Client &client)
{
    size_t  s = _clients.size();
    std::map<const int, Client*>::iterator it = _clients.find(client.getClientFd());

    if (it != _clients.end())
    {
        int i = 1;
        if (!isBanned(client))
            i &= kickAbleClient(client);
        if (isOperator(client))
            i &= dismissOperator(client);
        _clients.erase(it);
        i &= (s - _clients.size());
        if (COMMENT && i)
            std::cout << MSG_HEADER_CHANNEL
				<< PURPLE << client << RESET
				<< " is removed from channel " RED << getName() << RESET << std::endl;
        return (i);
    }
    return (0);    
}

/**
 * @brief Kicks an able client from the channel.
 *
 * This function removes the specified able client from the channel. It first checks if
 * the client is in the _ableClients map and, if found, removes the client from the map.
 * It returns 1 if the client was successfully kicked, or 0 if the client was not found
 * in the _ableClients map.
 *
 * @param client The able client to be kicked from the channel.
 *
 * @return Returns 1 if the able client was successfully kicked, or 0 if the client was not found
 * in the _ableClients map.
 */
int Channel::kickAbleClient(const Client& client)
{
    size_t  s = _ableClients.size();
    std::map<const int, Client*>::iterator it = _ableClients.find(client.getClientFd());

    if (it != _ableClients.end())
    {
        _ableClients.erase(it);
        int i = s - _ableClients.size();
        if (COMMENT && i)
		std::cout << MSG_HEADER_CHANNEL << client << " was removed from able clients in channel " << getName() << std::endl;
        return (i);
    }
    else if (COMMENT)
        std::cout << MSG_HEADER_CHANNEL << client << " is not an able client of channel " << getName() << std::endl;
    return (1);
}

/**
 * @brief Dismisses a banned client from the channel.
 *
 * This function checks if the given client is in the list of banned clients in the channel.
 * If the client is found, it removes them from the list of banned clients. If the removal is successful,
 * the client is considered dismissed from the banned list. If the client is not banned, a message is displayed.
 *
 * @param client The banned client to be dismissed.
 * @return 1 if the client is successfully dismissed from the banned list, 0 if unsuccessful.
 */
int Channel::dismissBannedClient(const Client& client)
{
    size_t  s = _bannedClients.size();
    std::set<std::string>::iterator it = _bannedClients.find(client.getNickname());
    if (it != _bannedClients.end())
    {
        _bannedClients.erase(it);
        int i = s - _bannedClients.size(); 
        if (COMMENT && i)
            std::cout << MSG_HEADER_CHANNEL << client << " is dismissed from banned clients in channel " << getName() << std::endl;
        return (i);
    }
    else if (COMMENT)
        std::cout << MSG_HEADER_CHANNEL << client << " was not banned from channel " << getName() << std::endl;
    return (1);
}

/**
 * @brief Adds a client as an operator in the channel.
 *
 * This function checks if the given client is already an operator. If the client is not
 * already an operator, it adds them to the list of channel operators. If the addition is successful,
 * the client is assigned operator status. If the client is already an operator, a message is displayed.
 *
 * @param op The client to be added as an operator.
 * @return 1 if the client is successfully added as an operator, 0 if unsuccessful.
 */
int    Channel::addOperator(const Client& op)
{
    int i = 1;
    if (!isOperator(op))
    {
        std::pair<std::set<std::string>::iterator, bool> result = _operators.insert(op.getNickname());
        i = result.second;
        if (COMMENT && i)
            std::cout << MSG_HEADER_CHANNEL << op << " is assigned as an operator of channel " << getName() << std::endl;
        return (i);
    }
    if (COMMENT)
        std::cout << MSG_HEADER_CHANNEL << op << " is already an operator of channel " << getName() << std::endl;
    return (i);
}

/**
 * @brief Dismisses an operator from the channel.
 *
 * This function checks if the given client is an operator in the channel and, if so,
 * removes them from the list of operators. If the removal is successful, the client
 * is considered removed from the operator status. If the client is not an operator,
 * a message is displayed.
 *
 * @param op The operator to be dismissed from the channel.
 * @return 1 if the operator is successfully dismissed, 0 if unsuccessful.
 */
int Channel::dismissOperator(const Client& op)
{
    size_t  s = _operators.size();
    std::set<std::string>::iterator it = _operators.find(op.getNickname());
    if (it != _operators.end())
    {    
        _operators.erase(it);
        int i = s - _operators.size();
        if (COMMENT && i)
            std::cout << MSG_HEADER_CHANNEL << op << " is dismissed as an operator of channel " << getName() << std::endl;
        return (i);
    }
    else if (COMMENT)
        std::cout << MSG_HEADER_CHANNEL << op << " is not an operator of channel " << getName() << std::endl;
    return (1);
}

/**
 * @brief Checks if a client is an operator in the channel.
 *
 * This function determines whether a client has operator privileges in the channel by searching for
 * their client file descriptor in the list of channel operators.
 *
 * @param client The client to check for operator status.
 * @return True if the client is an operator, false otherwise.
 */
bool    Channel::isOperator(const Client& client)
{
    return (_operators.find(client.getNickname()) != _operators.end());
}

/**
 * @brief Toggles a channel mode.
 *
 * This function allows you to toggle various channel modes by specifying the mode character
 * and a boolean value to enable or disable the mode. 
 *    
 *   t (Topic):          Only channel operators can change the channel's topic.
 *   m (Moderated):      Only channel operators and voiced users can send messages.
 *   l (User Limit):     Limits the number of users who can join the channel.
 *   k (Key):            A password is required to join the channel.
 *   s (Secret):         The channel does not appear in the channel list, and users must know the name to join.
 *   p (Private):        Hides the channel from being listed in the server's public list.
 *   v (Voice):          Users with this mode can speak in a moderated channel, even if it's set to +m.
 *   o (Operator):       Channel operators have elevated privileges.
 *   b (Ban):            Users can be banned from the channel by their nickname or hostname. 
 *   
 * @param mode The mode character to toggle (e.g., 't' for topic, 'm' for moderated, 'k' for key).
 * @param true_false A boolean value to enable (true) or disable (false) the mode.
 */
void    Channel::toggleMode(const char mode, bool true_false)
{
    switch (mode)
    {
        case    't': _mode.t = true_false; break;
        case    'm': _mode.m = true_false; break;
        case    'l': _mode.l = true_false; break;
        case    'k': _mode.k = true_false; break;
        case    's': _mode.s = true_false; break;
        case    'p': _mode.p = true_false; break;
        case    'v': _mode.v = true_false; break;
        case    'o': _mode.o = true_false; break;
        case    'b': _mode.b = true_false; break;
    }
}
//OK
void    Channel::removePassword()
{
    _password.clear();
    toggleMode('k', false);
}

/**
 * @brief Adds a client to the list of kicked clients.
 *
 * This function adds the specified client to the channel's list of kicked clients by inserting
 * the client into the _kickedClients map. It checks if the insertion was successful and returns 1
 * if the client was successfully added to the list of kicked clients. It also prints a message if
 * the insertion is successful.
 *
 * @param client The client to be added to the list of kicked clients.
 *
 * @return Returns 1 if the client was successfully added to the list of kicked clients, or 0 if the
 * insertion was not successful.
 */
int Channel::addToKickedClients(Client& client)
{
    std::pair<std::set<std::string>::iterator, bool> result = _kickedClients.insert(client.getNickname());
    int i = 1;
    i &= result.second;
    if (COMMENT && i)
        std::cout << MSG_HEADER_CHANNEL << client << " is added to the kicked clients of channel " << getName() << std::endl;
    return (i);
}


int Channel::addToKickedClients(const std::string &client_nick)
{
    std::pair<std::set<std::string>::iterator, bool> result = _kickedClients.insert(client_nick);
    int i = 1;
    i &= result.second;
    if (COMMENT && i)
        std::cout << MSG_HEADER_CHANNEL << client_nick << " is added to the kicked clients of channel " << getName() << std::endl;
    return (i);
}

/**
 * @brief Bans a client from the channel.
 *
 * This function bans the specified client from the channel by inserting the client into
 * the _bannedClients map. It checks if the channel's mode allows banning (mode "b") and if
 * the client is not already in the list of banned clients. If both conditions are met, it inserts
 * the client into the list of banned clients and kicks the client from the _ableClients (if not already kicked).
 * If the insertion and kicking operations are successful, it returns 1 and prints a ban message.
 * If the client is already banned or if banning is not allowed by the channel's mode, it returns 0.
 *
 * @param client The client to be banned from the channel.
 *
 * @return Returns 1 if the client was successfully banned from the channel, or 0 if the client
 * was already banned, if banning is not allowed by the channel's mode, or if the kick operation fails.
 */
int    Channel::banClient(const Client& client)
{
    int i = 0;
    if (_mode.b)
    {
        std::set<std::string>::iterator it = _bannedClients.find(client.getNickname());

        if (it != _bannedClients.end())
        {
            if (COMMENT)
                std::cout << MSG_HEADER_CHANNEL << client << " was already banned from channel " << getName() << std::endl;
            return (0);
        }
        std::pair<std::set<std::string>::iterator, bool> result = _bannedClients.insert(client.getNickname());
        i = result.second;
        if (COMMENT && i)
            std::cout << MSG_HEADER_CHANNEL << client << " is banned from channel " << getName() << std::endl;
    }
    return (i);
}

/**
 * @brief Restores a banned client to the channel.
 *
 * This function checks if the given client is banned, and if so, it restores
 * the client by removing them from the banned list and adding them to the
 * able client list.
 *
 * @param client The client to be restored.
 * @return Returns 1 if the client is successfully restored, 0 if the client is not banned.
 */
int Channel::restoreBannedClient(Client& client)
{
    if (!isBanned(client))
    {
        if (COMMENT)
            std::cout << MSG_HEADER_CHANNEL << client << " does not exist amongst the banned in channel " << getName() << std::endl;
        return (0);
    }
    int i = dismissBannedClient(client) && addAbleClient(client);
    if (COMMENT && i)
        std::cout << MSG_HEADER_CHANNEL << client << " has been restored as an able client of channel " << getName() << std::endl;
    return (i);
}

/**
 * @brief Checks if a client is banned in the channel.
 *
 * This function determines whether a client is banned from the channel by
 * searching for their client file descriptor in the list of banned clients.
 *
 * @param client The client to check for banning status.
 * @return True if the client is banned, false otherwise.
 */
bool    Channel::isBanned(const Client& client) const
{
    return (_bannedClients.find(client.getNickname()) != _bannedClients.end());
}

bool    Channel::doesClientExist(const Client &client) const
{
    return  (_clients.find(client.getClientFd()) != _clients.end()); // || 
             //(_kickedClients.find(client.getNickname()) != _kickedClients.end()
}

bool	Channel::doesClientExist(const std::string &client_nick) const
{
	std::map<const int, Client*>::const_iterator	itr;

	for (itr = _clients.begin(); itr != _clients.end(); itr++)
		if (itr->second->getNickname() == client_nick)
			return (true);
	return (false);
}

void    Channel::PrintChannel()
{
    std::cout << "Channel Topic: " << getTopic() << std::endl;
    std::cout << "Channel\tName: " << getName() << std::endl;
    std::cout << "\t\t\tOperators: " << std::endl;
    std::cout << "\t\t\t\t\t";

    std::map<const int, Client*>::const_iterator	it_map;
	std::set<std::string>::const_iterator			it_set;

    for (it_set = this->getOperators().begin(); it_set != this->getOperators().end(); it_set ++)
    {
        std::cout << *it_set << ", ";
    }
    std::cout << std::endl;

    std::cout << "\t\t\tClients: " << std::endl;
    std::cout << "\t\t\t\t\t";

    for (it_map = this->getClients().begin(); it_map != this->getClients().end(); it_map++)
    {
        std::cout << it_map->second->getClientFd() << ", ";
    }
    std::cout << std::endl;

    std::cout << "\t\t\tAble Clients: " << std::endl;
    std::cout << "\t\t\t\t\t";

    for (it_map = this->getAbleClients().begin(); it_map != this->getAbleClients().end(); it_map++)
    {
        std::cout << it_map->second->getClientFd() << ", ";
    }
    std::cout << std::endl;

    std::cout << "\t\t\tBanned Clients: " << std::endl;
    std::cout << "\t\t\t\t\t";
    for (it_set = this->getBannedClients().begin(); it_set != this->getBannedClients().end(); it_set++)
    {
        std::cout << *it_set << ", ";
    }
    std::cout << std::endl;

    std::cout << "\t\t\tKicked Clients: " << std::endl;
    std::cout << "\t\t\t\t\t";

    for (it_set = this->getKickedClients().begin(); it_set != this->getKickedClients().end(); it_set++)
    {
        std::cout << *it_set << ", ";
    }
    std::cout << std::endl;
}
