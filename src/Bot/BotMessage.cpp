#include "Bot.hpp"

int Bot::processMessage(std::string &message) {
	if (message.empty())
		return (1);

	_message = message;
	_messageCopy = _message;
	std::transform(_messageCopy.begin(), _messageCopy.end(), _messageCopy.begin(), ::tolower);

	if (_messageCopy.find("rouxbot") == std::string::npos)
		return (1);
	
	std::cout << "RouxBot received : " << _message << std::endl;
	return (0);
}
