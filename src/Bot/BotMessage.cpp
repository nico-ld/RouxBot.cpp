#include "Bot.hpp"

int Bot::processMessage(std::string &message) {
	if (message.empty())
		return (1);

	_message = message;
	_messageCopy = _message;
	std::transform(_messageCopy.begin(), _messageCopy.end(), _messageCopy.begin(), ::tolower);

	if (_messageCopy.find("rouxbot") == std::string::npos)
		return (1);

	std::map<std::string, void (Bot::*)(std::string)>::iterator it;
	for (it = _actionUser.begin(); it != _actionUser.end(); ++it) {
		if (_messageCopy.find(it->first) != std::string::npos) {
			(this->*(it->second))("jean");
			break ;
		}
	}

	return (0);
}
