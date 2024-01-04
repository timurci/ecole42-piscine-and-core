#include "Server.hpp"
#include "Commands.hpp"
#include "Macro.hpp"
#include <sys/poll.h>

// Server::Server()
//
Server::Server(std::string port, std::string password, struct tm *timeinfo)
: servinfo(NULL), server_socket_fd(0) , port(port), password(password)
{
	std::cout << YELLOW << "Server running..." << RESET << std::endl;
	std::cout << YELLOW << "Server listening" << RESET << std::endl;
	setHints();
	setDatetime(timeinfo);
}

Server::~Server()
{
	std::cout << YELLOW << "Server shutting down..." << RESET << std::endl;
}

const char * 	Server::InvalidClientException::what (void) const throw() 
{
	return "The information given by the client are invalid.";
}

/**
 * @brief Attributes the correct parameters to the structure Hints.
 *
 */
void Server::setHints()
{
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;		  // We choose Ipv4
	hints.ai_socktype = SOCK_STREAM; // We choose to work with TCP stream sockets
	hints.ai_flags = AI_PASSIVE;	  // We'll be on localhost by default
}

std::string 					Server::getPort()	  const { return (port); }

std::string 					Server::getPassword() const { return (password); }

std::string 					Server::getDatetime() const { return (datetime); }

std::map<std::string, Channel>&	Server::getChannels()		{ return (channels); }

std::map<const int, Client>&	Server::getClients()		{ return (clients); }

std::vector<t_server_op>&		Server::getIrcOperators()	{ return (irc_operators); }

std::string 					Server::getMotd() const 	{ return (motd); }

void							Server::setPassword(std::string new_pwd)
{
	password = new_pwd;
}

void							Server::setDatetime(struct tm *timeinfo)
{
	char buffer[80];

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
  	std::string str(buffer);

	datetime = str;
}

void							Server::setMotd(std::string buffer)
{
	motd =  buffer;
}

/**
 * @brief Get the name, host and password of all the irc operators from a file
 * 
 * @param file Str of the config file with all of infos
 * @return int Returns SUCCESS (0) or FAILURE (-1)
 */

void	Server::addPollfd(const int fd, const short events, std::vector<pollfd> &dst)
{
	pollfd	pfd;

	pfd.fd = fd;
	pfd.events = events;
	pfd.revents = 0;
	dst.push_back(pfd);
}

int 		Server::readFromConfigFile(char *filename)
{
	std::ifstream				data;
	std::string					buffer;
	std::vector<std::string>	operators;

	data.open(filename);
	if (!data)
		return (FAILURE);
	while (getline(data, buffer)) {
		operators.push_back(buffer);
	}
	data.close();

	std::vector<std::string>::iterator it;
	for (it = operators.begin(); it != operators.end(); it++)
	{
		std::string	line = *it;
		t_server_op	op;
		
		int len = line.size() - (line.size() - line.find_first_of(' '));

		op.name.insert(0, line, 0, len);
		op.host.insert(0, line, len + 1, line.find_last_of(' ') - len - 1);
		op.password.insert(0, line, line.find_last_of(' ') + 1, line.size() - 1);
	
		// DEBUG
		//std::cout << "============= OPERATORS =============" << std::endl;
		//std::cout << "Op name : $" << op.name << "$" << std::endl;  
		//std::cout << "Op host : $" << op.host<< "$" << std::endl;  
		//std::cout << "Op pass : $" << op.password<< "$" << std::endl;  
		irc_operators.push_back(op);
	}
   return (SUCCESS);
}

/**
 * @brief Helps set up the structs 'hints' and 'servinfo' of our Server class
 *
 * @param port Value given by the user (e.g. "6667")
 * @return int Returns SUCCESS or FAILURE whether getaddrinfo works or not
 */
int Server::fillServinfo(char *port)
{
	if (getaddrinfo(NULL, port, &hints, &servinfo) < 0)
	{
		std::cerr << MSG_HEADER_SERVER << RED << "Failed at getaddrinfo" << RESET << std::endl;
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief This function follows step by step the required function calls to launch the server:
 *
 * 		1) socket() => get the server socket file descriptor
 * 		2) setsocktop() => enable the configuration of said socket (here, we wanted
 * 							to allow the re-use of a port if the IP address is different)
 * 		3) bind() => Associate the socket with a specific port (here, the one given by the user)
 * 		4) listen() => Wait for any incoming connections to our server socket
 *
 * @return int 0 for SUCCESS and -1 for FAILURE
 */
int Server::launchServer()
{
	server_socket_fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if (server_socket_fd == FAILURE)
	{
		std::cerr << MSG_HEADER_SERVER << RED "Cannot initialize a socket" << RESET << std::endl;
		return (FAILURE);
	}
	int optvalue = 1; // enables the re-use of a port if the IP address is different
	if (setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue)) == FAILURE)
	{
		std::cerr << MSG_HEADER_SERVER << RED << "setsockopt() has failed" << RESET << std::endl;
		return (FAILURE);
	}
	if (bind(server_socket_fd, servinfo->ai_addr, servinfo->ai_addrlen) == FAILURE)
	{
		std::cerr << MSG_HEADER_SERVER << RED << "Bind has failed" << RESET << std::endl;
		return (FAILURE);
	}
	if (listen(server_socket_fd, BACKLOG) == FAILURE)
	{
		std::cerr << MSG_HEADER_SERVER << RED << "Listen has failed" << RESET << std::endl;
		return (FAILURE);
	}
	freeaddrinfo(servinfo);
	servinfo = NULL;
	return (SUCCESS);
}

// Is poll_fd argument really necessary, what if you use it on an object variable?
void Server::addClient(const int client_socket, std::vector<pollfd> &dst)
{
	Client new_client(client_socket);

	addPollfd(client_socket, POLLIN | POLLOUT, dst);
	clients.insert(std::pair<int, Client>(client_socket, new_client));
	//clients.insert(std::pair<int, Client>(client_socket, client_socket));
	std::cout << MSG_HEADER_SERVER
		GREEN << "Successfully added client #" << client_socket << RESET << std::endl;
}

// A better approach to remove clients from channels is knowing
// which channels has the client joined.
void Server::delClient(std::vector<pollfd>::iterator &it_poll, Client &client)
{
	std::cout << MSG_HEADER_SERVER << "Client disconnecting "
		RED << client << RESET << std::endl;

	std::map<std::string, Channel>::iterator it = channels.begin();
	while (it != channels.end())
		it++->second.removeClientFromChannel(client);
	close(it_poll->fd);
	clients.erase(it_poll->fd);
	pollfds.erase(it_poll);

	std::cout << MSG_HEADER_SERVER
		<< "Client has been removed. Total number of Client is now: "
		YELLOW << (unsigned int)(pollfds.size() - 1) << RESET << std::endl;
}

//void Server::addChannel(const std::string &channelName)
//{
//	(void) channelName;
//	std::map<std::string, Channel>::iterator it = channels.find(channelName);
//	if (it != channels.end())
//	{
//		std::cout << "Channel already exists, choose an other name\n";
//		return ;
//	}
//	Channel	channel(channelName);
//	channels.insert(std::pair<std::string, Channel>(channel.getName(), channel));
//	std::cout << MSG_HEADER_SERVER
//	<< GREEN << "Channel added #" << channelName << RESET << std::endl;
//}
//
//void Server::addClientToChannel(const std::string &channelName, Client &client)
//{
//	std::map<std::string, Channel>::iterator it;
//	it = channels.find(channelName);
//	std::string client_nickname = client.getNickname();
//	if (it->second.doesClientExist(client) == false)
//	{
//		it->second.addClient(client);
//		// Utilise return value of addClient to prevent success message in case of error.
//		std::cout << "Client successfully joined channel" << channelName << "!" << std::endl;
//	}
//	else 
//		std::cout << YELLOW << client.getNickname() << " is already here\n" << RESET;
//}
//
//bool    Server::isChannel(const std::string &channelName) const
//{
//    std::map<std::string, Channel>::const_iterator it;
//    it = channels.find(channelName);
//    if (it == channels.end())
//    {
//        std::cout << MSG_HEADER_SERVER << RED << "The channel "
//			<< channelName << "does not exist\n" << RESET;
//        return (false);
//    }
//    return (true);
//}
