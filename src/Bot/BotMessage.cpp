#include "Bot.hpp"

static std::string userTarget(std::string message, size_t pos, size_t size) {
	size_t start = pos + size;
	while (start < message.length() && std::isspace(message[start]))
		start++;
	
	std::string target = "";
	size_t end = message.find(' ', start);
	while (start < message.length() && start < end)
		target.push_back(message[start++]);
	return (target);
}

int Bot::processMessage(std::string &message) {
	if (message.empty())
		return (1);

	_message = message;
	_messageCopy = _message;
	std::transform(_messageCopy.begin(), _messageCopy.end(), _messageCopy.begin(), ::tolower);
	std::string::iterator newEnd = std::remove_if(_messageCopy.begin(), _messageCopy.end(), ::ispunct);
	_messageCopy.erase(newEnd, _messageCopy.end());

	size_t pos = _messageCopy.find("rouxbot");
	if (pos == std::string::npos)
		return (1);
	_messageCopy.erase(pos, 7);

	std::cout << ROUXBOT DIM " received " << _messageCopy << RESET << std::endl;

	std::map<std::string, void (Bot::*)(std::string)>::iterator it;
	for (it = _actionUser.begin(); it != _actionUser.end(); ++it) {
		pos = _messageCopy.find(it->first, 0);
		if (pos != std::string::npos) {
			(this->*(it->second))(userTarget(_messageCopy, pos, it->first.length()));
			break ;
		}
	}

	return (0);
}
