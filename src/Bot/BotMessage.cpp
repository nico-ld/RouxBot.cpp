#include "Bot.hpp"

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

	executeCommand();

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
					itAction = _actionUser.find(word);
					if (itAction == _actionUser.end())
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

static bool isNameValid(std::string name, e_intent type) {
	if (type == INTENT_ACTION) {
		std::cerr << DIM "Target error : " << name << " is a command." RESET << std::endl;
		return (false);
	}
	else
		return (true);
}

void Bot::executeCommand(void) {
	if (_tokens.empty())
		return ;

	std::vector<std::pair<std::string, e_intent> >::iterator it;
	std::map<std::string, void (Bot::*)(std::string)>::iterator itAction;
	for (it = _tokens.begin(); it != _tokens.end(); it++) {
		if ((it + 1) == _tokens.end()) {
			std::cerr << DIM "Target error : no target given." RESET << std::endl;
			break ;
		}
		if (it->second == INTENT_ACTION && isNameValid((it + 1)->first, (it + 1)->second)) {
			itAction = _actionUser.find(it->first);
			if (itAction != _actionUser.end()) {
				(this->*(itAction->second))((it + 1)->first);
			}
		}
	}
}
