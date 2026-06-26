#include "Bot.hpp"

void Bot::_initActionUser(void) {
	_actionUser["delete"] = &Bot::deleteUser;
	_actionUser["add"] = &Bot::addUser;
	_actionUser["set"] = &Bot::setUser;
}
