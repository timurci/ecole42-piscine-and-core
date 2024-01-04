#include "Irc.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Commands.hpp"

static void	botHour(Client &client, const std::string &bot_name)
{
	std::stringstream ss;
    std::time_t t = std::time(NULL);
    std::tm* tm_local = std::localtime(&t);

    ss << "Current local time: " << tm_local->tm_hour << ":" 
       << tm_local->tm_min << ":" << tm_local->tm_sec;
    
    std::string time = ss.str();
	client.appendSendBuffer(RPL_PRIVMSG(bot_name, bot_name, client.getNickname(), time));
}

static void	botRandom(Client &client, const std::string &bot_name)
{
	srand(time(NULL)); // initializes the random number generator with a seed value based on the current time
    int index = rand() % 10 + 1; // number between 1 and 10
	
	std::string str;
	switch (index)
	{
		case 1: str = "Wearing headphones for just an hour could increase the bacteria in your ear by 700 times."; break;
		case 2: str = "Google images was literally created after Jennifer Lopez wore that infamous dress at the 2000 Grammys"; break;
		case 3: str = "Los Angeles' full name is 'El Pueblo de Nuestra Senora la Reina de los Angeles de Porciuncula'"; break;
		case 4: str = "Tigers have striped skin, not just striped fur."; break;
		case 5: str = "Like fingerprints, everyone's tongue print is different."; break;
		case 6: str = "Cat urine glows under a black-light."; break;
		case 7: str = "A shrimp's heart is in its head."; break;
		case 8: str = "The Spice Girls were originally a band called Touch."; break;
		case 9: str = "The unicorn is the national animal of Scotland"; break;
		case 10: str = "In 2014, there was a Tinder match in Antarctica"; break;
		default: str = "Are you hacking?"; break;
	}
	client.appendSendBuffer(RPL_PRIVMSG(bot_name, bot_name, client.getNickname(), str));
}

void	bot(Client &client, const std::string &msg)
{
	std::string bot_name = "bot42";
	std::string	bot_cmd(msg);
	std::string	validCmds[4] = {
		":HELP",
		":HOUR",
		":RANDOM",
		};

	// change bot_cmd into caps letter
	for (size_t i = 0; i < bot_cmd.size(); i++)
		bot_cmd[i] = std::toupper(bot_cmd[i]);
	
	int index = 0;
	while (index < 4)
	{
		if (bot_cmd == validCmds[index])
			break;
		index++;
	}
	switch (index + 1)
	{
		case 1: client.appendSendBuffer(RPL_PRIVMSG(bot_name, bot_name, client.getNickname(), "Ask me 'HOUR' or 'RANDOM'")); break;
		case 2: botHour(client, bot_name); break;
		case 3: botRandom(client, bot_name); break;
		default:
			client.appendSendBuffer(RPL_PRIVMSG(bot_name, bot_name, client.getNickname(), "Invalid request, ask 'HELP' for more information"));
	}
}
