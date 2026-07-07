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
	
	size_t pos = _messageCopy.find("rouxbot");
	if (pos == std::string::npos)
		return (1);
	_messageCopy.erase(pos, 7);
	
	std::cout << ROUXBOT DIM " received " << _messageCopy << RESET << std::endl;
	tokenizeMessage();

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

void Bot::tokenizeMessage(void) {
	int scores[INTENT_UNKNOW] = {0};

	// Normalize message

	std::stringstream ss(_messageCopy);
	std::string word;
	while (ss >> word) {
		std::map<std::string, e_intent>::iterator it = _vocabulary.find(word);
		if (it != _vocabulary.end()) {
			_tokens[word] = it->second;
			scores[it->second] += 1;
		}
		else
			_tokens[word] = INTENT_UNKNOW;
	}

	_messageType = INTENT_UNKNOW;
	int bestScore = 0;
	for (int i = 0; i < INTENT_UNKNOW; i++) {
		if (scores[i] > bestScore) {
			bestScore = scores[i];
			_messageType = i;
		}
	}

	std::cout << DIM "Type of message : " 
				<< ((_messageType == INTENT_GREETING) ? "GREETING" :
				(_messageType == INTENT_FAREWELL) ? "FAREWELL" :
				(_messageType == INTENT_THANKS) ? "THANKS" :
				(_messageType == INTENT_QUESTION) ? "QUESTION" :
				(_messageType == INTENT_INSULT) ? "INSULT" :
				(_messageType == INTENT_ACTION) ? "ACTION" : 
				"UNKNOW") 
				<< RESET << std::endl;
}
