#include "Server.hpp"
#include "Colors.hpp"
#include "Commands.hpp"

// Discards sockaddr_in info
static int acceptSocket(int listenSocket)
{
	sockaddr_in	client;
	socklen_t	addr_size = sizeof(sockaddr_in);
	return (accept(listenSocket, (sockaddr *)&client, &addr_size));
}

static void	tooManyClients(int client_socket)
{
	std::cout << RED << ERR_FULL_SERV << RESET << std::endl;
	send(client_socket, ERR_FULL_SERV, strlen(ERR_FULL_SERV) + 1, 0);
	close(client_socket);
}

int	Server::createClientConnection(std::vector<pollfd> &new_pollfds)
{
	int	client_sock = acceptSocket(server_socket_fd);

	if (client_sock == -1)
	{
		std::cerr << RED << "[Server] Accept() failed" << RESET << std::endl;
		return (CONTINUE);
	}
	if (pollfds.size() + new_pollfds.size() - 1 < MAX_CLIENT_NB)
		addClient(client_sock, new_pollfds);
	else
		tooManyClients(client_sock);
	return (SUCCESS);
}

static void print(const Client &client, const char *message)
{
	std::string	msg(message);
	size_t	pos;

	pos = msg.rfind("\r\n");
	if (pos != std::string::npos)
		msg.erase(pos);
	std::cout << MSG_HEADER_CLIENT
		<< "Message received from client\t";
	if (client.getNickname().empty())
		std::cout << YELLOW << "#" << client.getClientFd() << " [unregistered]" << RESET;
	else
		std::cout << YELLOW << "#" << client.getClientFd() << " (" << client.getNickname() << ")" << RESET;
	std::cout << "\t<< " << BLUE << msg << RESET << std::endl;
}

int	Server::handleExistingConnection(std::vector<pollfd>::iterator &it)
{
	std::map<const int, Client>::iterator	it_client = clients.find(it->fd);
	Client&									client = it_client->second;
	char									message[BUF_SIZE_MSG];
	int										read_count;
	
	memset(message, 0, sizeof(message));
	read_count = recv(it->fd, message, BUF_SIZE_MSG, 0);

	if (read_count <= FAILURE)
	{
		std::cerr << RED << "[Server] Recv() failed" << RESET << std::endl;
		delClient(it, client);
		return (BREAK);
	}
	else if (read_count == 0)
	{
		std::cout << "[" << YELLOW << "Server" << RESET << "] A client has just disconnected" << std::endl;
		delClient(it, client);
		return (BREAK);
	}
	else
	{
		print(client, message);
		client.appendRecvBuffer(message);

		if (client.getRecvBuffer().find("\r\n") != std::string::npos)
		{
			try 
			{
				parseMessage(client);
				//client.resetRecvBuffer();
			}
			catch(const std::exception& e) 
			{ 
				std::cout << "[SERVER] Caught exception : ";
				std::cerr << e.what() << std::endl;
				if (client.isRegistrationDone() == true)
					client.setDeconnectionStatus(true);
				return (BREAK);
			}
		}
	}
	return (SUCCESS);
}

int	Server::handlePolloutEvent( std::vector<pollfd>::iterator &it)
{
	std::map<const int, Client>::iterator	it_client = clients.find(it->fd);
	Client&									client = it_client->second;

	//maybe move it where you set deconnectionstatus
	if (client.getDeconnectionStatus() == true)
	{
		delClient(it, client);
		return (BREAK);
	}
	sendServerRpl(client);
	client.resetSendBuffer();
	return (SUCCESS);
}

int	Server::handlePollerEvent(std::vector<pollfd>::iterator &it)
{
	if (it->fd == server_socket_fd)
	{
		std::cerr << RED << "[Server] Listen socket error" << RESET << std::endl;
		return (FAILURE);
	}
	else
	{
		std::map<const int, Client>::iterator	it_client = clients.find(it->fd);
		Client&									client = it_client->second;

		delClient(it, client);
		return (BREAK);
	}
}

