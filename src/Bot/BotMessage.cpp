#include "Bot.hpp"

std::string userTarget(std::string message, size_t pos, size_t size) {
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

	tokenizeMessage(message);

	std::vector<std::pair<std::string, e_intent> >::iterator it;
	size_t oldSize = _tokens.size();
	for (it = _tokens.begin(); it != _tokens.end(); it++) {
		if ((*it).first == "rouxbot") {
			_tokens.erase(it);
			break ;
		}
	}
	if (oldSize == _tokens.size())
		return (1);
	
	std::cout << ROUXBOT DIM " received : " << _tokens << RESET << std::endl;

	return (0);
}

void Bot::tokenizeMessage(std::string message) {
	_tokens.clear();

	std::string word;
	std::stringstream ss(message);
	std::map<std::string, e_intent>::iterator itVoc;
	std::map<std::string, void (Bot::*)(std::string)>::iterator itAction;

	while (ss >> word) {
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);

		for (size_t i = 0; i < word.size(); i++) {
			if (std::ispunct(word[i])) {
				if (word[i] == '!' && i == 0) {
					for (itAction = _actionUser.begin(); itAction != _actionUser.end(); itAction++){
						if (word.find(itAction->first, 0) == std::string::npos)
							break ;
					}
					word.erase(i, 1);
				}
				else
					word.erase(i, 1);
			}
		}

		itVoc = _vocabulary.find(word);
		if (itVoc != _vocabulary.end())
			_tokens.push_back(std::make_pair(word, itVoc->second));
		else
			_tokens.push_back(std::make_pair(word, INTENT_UNKNOW));
	}
}
