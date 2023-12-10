#ifndef CLIENT_HPP
# define CLIENT_HPP

# ifndef CLIENT_DIAGNOSTICS
#  define CLIENT_DIAGNOSTICS 1
# endif

# include "Irc.hpp"

typedef struct s_server_op
{
	std::string name;
	std::string	host;
	std::string	password;
}	t_server_op;

class Client
{
	private:
		int				fd;
		std::string		recvbuf;
		std::string		sendbuf;
		bool			to_deconnect;
		std::string		nickname;
		std::string		old_nickname;
		std::string		username;
		std::string		realname;
		std::string		mode;
		bool			connection_password;
		bool			registration_done;
		bool			welcome_sent;
		bool			has_all_info;
		int				nb_info;
	
	public:
		Client(int fd);
		//Client(const Client &);
		~Client(void);
	
		Client&			operator=(const Client &);

		// Server infos
		int				getClientFd(void) const;
		std::string		getRecvBuffer(void) const; //returned ref
		std::string		getSendBuffer(void) const; //returned ref
		bool			getDeconnectionStatus(void) const; //returned ref
		void			appendRecvBuffer(const std::string &msg);
		void			resetRecvBuffer();
		void			appendSendBuffer(const std::string &msg);
		void			resetSendBuffer();
		void			setDeconnectionStatus(bool status);
		// Client Registration infos
		std::string		getNickname(void) const; //returned ref
		std::string		getOldNickname(void) const; //returned ref
		std::string		getUsername(void) const;
		std::string		getRealname(void) const;
		bool			getConnectionPassword(void) const; //returned ref
		void			setNickname(const std::string &nickname);
		void			setOldNickname(const std::string &nickname);
		void			setUsername(const std::string &username);
		void			setRealname(const std::string &realname);
		void			setConnectionPassword(bool boolean);
		// User modes
		std::string		getMode(void) const; //returned ref
		void			addMode(const std::string &mode);
		void			removeMode(const std::string &mode);
		// Client registration system
		bool			isRegistrationDone(void) const; //returned ref
		bool			isWelcomeSent(void) const; //returned ref
		bool			hasAllInfo(void) const; //returned ref
		int				getNbInfo(void) const;
		int				is_valid(void) const;
		void			setRegistrationDone(bool boolean);
		void			setWelcomeSent(bool boolean);
		void			sethasAllInfo(bool boolean);
		void			addNbInfo(int n);
};

std::ostream&	operator<<(std::ostream &, const Client &);

#endif
