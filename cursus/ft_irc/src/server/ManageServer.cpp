#include "Server.hpp"
#include "Colors.hpp"
#include "Commands.hpp"

int Server::manageServerLoop(void)
{
	addPollfd(server_socket_fd, POLLIN, pollfds);

	while (server_shutdown == false)
	{
		std::vector<pollfd>	new_pollfds;

		if (poll(&pollfds[0],
		   static_cast<unsigned int>(pollfds.size()), -1) <= SUCCESS)
		{
			if (errno == EINTR)
				break ;
			std::cerr << RED << "[Server] Poll error" << RESET << std::endl;
			throw ;
		}
		std::vector<pollfd>::iterator it = pollfds.begin();
		while (it != pollfds.end())
		{
			if (it->revents & POLLIN)
			{
				if (it->fd == server_socket_fd)
				{
					if (createClientConnection(new_pollfds) == CONTINUE)
						continue ;
				}
				else if (handleExistingConnection(it) == BREAK)
					break ;
			}
			else if (it->revents & POLLOUT)
			{
				if (handlePolloutEvent(it) == BREAK)
					break ;
			}
			else if (it->revents & POLLERR)
			{
				if (handlePollerEvent(it) == BREAK)
					break ;
				else
					return (FAILURE);
			}
			it++;
		}
		pollfds.insert(pollfds.end(), new_pollfds.begin(), new_pollfds.end());
	}
	return (SUCCESS);
}

// Check what happens when continue and break is used in a nested loop.
// Check how it++ iteration is handled; maybe it is more meaningful to switch to "for"
