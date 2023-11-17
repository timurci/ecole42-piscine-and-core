#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include "Irc.hpp"
#include "Client.hpp"

class Channel
{
	private:
		std::map<std::string, Client>	_clientList;
		std::vector<std::string>		_kicked_users;
		std::vector<std::string>		_banned_users;
		std::vector<std::string>		_operators;
		std::vector<std::string>		_voiced_users;
		std::string 					_name;
		std::string						_operatorPassword;
		std::string						_topic;
		std::string						_mode;
		std::string						_channel_password;
		int								_capacity_limit;
	public:
		Channel(std::string const &name);
		~Channel();

		/* Accessors */
		std::string						getName() const;
		std::string						getTopic() const;
		std::string						getMode() const;
		std::string						getChannelPassword() const;
		int								getCapacityLimit() const;
		std::vector<std::string>&		getOperators() ;
		std::vector<std::string>&		getKickedUsers() ;
		std::vector<std::string>&		getBannedUsers() ;
		std::vector<std::string>&		getVoicedUsers() ;
		std::map <std::string, Client>&	getClientList();
		void							setTopic(std::string& newTopic);
		void							setChannelPassword(std::string password);
		void							setCapacityLimit(int limit);
		bool							doesClientExist(const std::string &clientName);
		/* Manage client in Channel */
		void							addClientToChannel(Client &client);
		void							removeClientFromChannel(const std::string &clientName);
		/* Operators */
		void							addFirstOperator(std::string operatorName);
		void							removeOperator(std::string operatoName);
		// void							addOperator(std::string operatorName);
		bool							isOperator(const std::string &operatorName);
		/* Modes */
		void							addMode(std::string const mode);
		void							removeMode(std::string const mode);
		void							removeChannelPassword();
		/* Client status */
		void							addToKicked(std::string &banned_name);
		void							addToBanned(std::string &banned_name);
		void							removeFromBanned(std::string &banned_name);
		bool							isBanned(const std::string &banned_name);
		void							addToVoiced(std::string &voiced_name);
		void							removeFromVoiced(std::string &voiced_name);
		bool							isVoiced(const std::string &voiced_name);

};

#endif
