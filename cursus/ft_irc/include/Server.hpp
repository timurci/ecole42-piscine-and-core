#ifndef SERVER_HPP
# define SERVER_HPP

# include "Irc.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Commands.hpp"
# include <iostream>
# include <fstream>
# include <csignal>

extern bool	server_shutdown;

class Server
{
	private:
		struct addrinfo					hints;
		struct addrinfo					*servinfo;
		int								server_socket_fd;
		std::map<const int, Client>		clients;
		std::map<std::string, Channel>	channels;
		std::vector<pollfd>				pollfds;
		std::string						port;
		std::string						password;
		std::string						datetime;
		std::vector<t_server_op>		irc_operators;
		std::string						motd;
	
	public:
		// Constructor & destructor
		Server();
		Server(const Server &);
		Server(std::string port, std::string password, struct tm *timeinfo);
		~Server();

		Server&		operator=(const Server &);

	public:
		// Accessors
		std::string								getPort() const;
		std::string								getPassword() const;
		std::string								getDatetime() const;
		std::map<std::string, Channel>& 		getChannels();
		std::map<const int, Client>&			getClients();
		std::vector<pollfd>&					getPollfds();
		Client*									findClient(const int client_fd);
		std::vector<t_server_op>&				getIrcOperators();
		std::string								getMotd() const;
		void									setHints();
		void									setPassword(std::string new_pwd);
		void									setDatetime(struct tm *timeinfo);
		void									setMotd(std::string buffer);

	public:
		int 		readFromConfigFile(char *filename);
		int			fillServinfo(char *port);
		int			launchServer();
		int			manageServerLoop();

	private:
		// Running Server functions
		void		addPollfd(const int fd, const short events, std::vector<pollfd> &dst);
		void		sendServerRpl(const Client &);
		int			createClientConnection(std::vector<pollfd> &new_pollfds);
		int			handleExistingConnection(std::vector<pollfd>::iterator &it);
		int			handlePolloutEvent(std::vector<pollfd>::iterator &it);
		int			handlePollerEvent(std::vector<pollfd>::iterator &it);

		// Manage Clients functions
		void		addClient(const int client_socket, std::vector<pollfd> &poll_fds);
		// void 		delClient(std::vector<pollfd> &poll_fds, int current_fd);
		void 		delClient(std::vector<pollfd>::iterator &it_poll, Client &client);
		void 		fillClients(std::map<const int, Client> &client_list, int client_fd, std::string cmd);
		void		sendClientRegistration(Client &client, const std::string &datetime);
		// Parsing & Commands functions
		void		parseMessage(Client &client);
		//void		execCommand(int const client_fd, std::string cmd_line);
		// Display functions
		void		printChannel(std::string &channelName) const;
		void		printOper(std::string &channelName) const;
		// Custom exceptions
		class InvalidClientException : public std::exception {
			public :
					const char *	what (void) const throw();
		};
	//private:
		// Channel functions // Unused functions.
		//void	addChannel(const std::string &channelName);
		//void	addClientToChannel(const std::string &channelName, Client &client);
		//bool	isChannel(const std::string &channelName) const;
};

#endif
