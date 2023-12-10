#ifndef	MACRO_HPP
#define MACRO_HPP

# define SUCCESS 0
# define FAILURE -1
# define BREAK 2
# define CONTINUE 3

# define BACKLOG 10          // Nb max of clients queuing
# define MAX_CLIENT_NB 9     // Nb max of clients overall
# define BUF_SIZE_MSG 4096

/*		MESSAGE		*/
# define ERR_FULL_SERV "[Server] You cannot join, the server is already full"

// Message convenience
# define MSG_HEADER_SERVER "[\033[0;33m  Server  \033[0m] " // YELLOW
# define MSG_HEADER_CLIENT "[\033[0;35m  Client  \033[0m] " // PURPLE
# define MSG_HEADER_CHANNEL "[\033[0;36m  Channel \033[0m] " // CYAN

#endif
