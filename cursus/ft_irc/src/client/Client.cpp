#include "Client.hpp"

/*
*				################################
*				###	CONSTRUCTOR & DESTRUCTOR ###
*				################################
*/
Client::Client(int client_fd)
: fd(client_fd), to_deconnect(false), connection_password(false),
 registration_done(false), welcome_sent(false), has_all_info(false), nb_info(0)
{
	// std::cout << YELLOW << "Client constructor for Client #" << client_fd << RESET << std::endl;
}

Client::~Client() {}

/*
*					#################
*					###	ACCESSORS ###
*					#################
*/
int				Client::getClientFd() const { return (fd); }
std::string		Client::getSendBuffer() const { return (sendbuf); }
std::string		Client::getRecvBuffer() const { return (recvbuf); }
std::string		Client::getNickname() const { return (nickname); }
std::string		Client::getOldNickname() const { return (old_nickname); }
std::string 	Client::getUsername() const { return (username); }
std::string		Client::getRealname() const { return (realname); }
std::string		Client::getMode() const { return (mode); }

bool			Client::getConnectionPassword() const { return (connection_password); }
bool			Client::isRegistrationDone() const { return (registration_done); }
bool			Client::isWelcomeSent()	const { return (welcome_sent); }
bool			Client::hasAllInfo() const { return (has_all_info); }
bool			Client::getDeconnectionStatus() const { return (to_deconnect); }
int				Client::getNbInfo() const { return (nb_info); }

void	Client::appendRecvBuffer(std::string const &buf)
{
	recvbuf += buf;
}

void	Client::resetRecvBuffer()
{
	recvbuf.clear();
}

void	Client::appendSendBuffer(std::string const &buf)
{
	sendbuf += buf;
}

void	Client::resetSendBuffer()
{
	sendbuf.clear();
}

void	Client::setDeconnectionStatus(bool status)
{
	to_deconnect = status;
}

void	Client::setNickname(std::string const &other_nickname)
{
	// If the nickname has more than 9 characters, it must be truncated
	nickname = (nickname.size() > 9) ? other_nickname.substr(0, 9) : other_nickname;
}

void	Client::setOldNickname(const std::string &other_nickname)
{
	old_nickname = other_nickname;
}

void	Client::setUsername(const std::string &other_username)
{
	username = other_username;
}

void	Client::setRealname(const std::string &other_realname)
{
	realname = other_realname;
}

void	Client::addMode(const std::string &other_mode)
{
	if (mode.empty() == true)
		mode = "+" + other_mode;
	else 
		mode += other_mode;
}

void	Client::removeMode(const std::string &other_mode)
{
	size_t pos = mode.find(other_mode);
	mode.erase(pos, 1);
}

void	Client::setConnectionPassword(bool boolean)
{
	connection_password = boolean;
}

void	Client::setRegistrationDone(bool boolean)
{
	registration_done = boolean;
}

void	Client::setWelcomeSent(bool boolean)
{
	welcome_sent = boolean;
}

void	Client::sethasAllInfo(bool boolean)
{
	has_all_info = boolean;
}

void	Client::addNbInfo(int n)
{
	nb_info += n;
	if (nb_info <= 0)
		nb_info = 0;
}

/*
*					##############################
*					### OTHER MEMBER FUNCTIONS ###
*					##############################
*/

int	Client::is_valid() const
{
	if (username.empty())
		return (FAILURE);
	if (nickname.empty())
		return (FAILURE);
	if (realname.empty())
		return (FAILURE);
	if (connection_password == false)
		return (FAILURE);
	if (this->getNbInfo() < 3)
		return (FAILURE);
	return (SUCCESS);
}

std::ostream&	operator<<(std::ostream &stream, const Client &client)
{
	stream << "#" << client.getClientFd();
	if (client.isRegistrationDone())
		stream << " (" << client.getNickname() << ")";
	else
		stream << " [unregistered]";
	return (stream);
}
