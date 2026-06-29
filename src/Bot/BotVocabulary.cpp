#include "Bot.hpp"

void Bot::_initVocabulary(void) {
	_initActionUser();
	_initPoliteness();
	_initQuestion();
}

void Bot::_initActionUser(void) {
	_actionUser["delete"] = &Bot::deleteUser;
	_actionUser["add"] = &Bot::addUser;
	_actionUser["set"] = &Bot::setUser;
	
	_vocabulary["delete"] = ACTION;
	_vocabulary["add"] = ACTION;
	_vocabulary["set"] = ACTION;
}

void Bot::_initPoliteness(void) {
	_vocabulary["hello"] = GREETING;
	_vocabulary["hi"] = GREETING;
	_vocabulary["hey"] = GREETING;
	_vocabulary["yo"] = GREETING;
	_vocabulary["bye"] = FAREWELL;
	_vocabulary["goodbye"] = FAREWELL;
	_vocabulary["thanks"] = THANKS;
	_vocabulary["thank"] = THANKS;
}

void Bot::_initQuestion(void) {
	_vocabulary["what"] = QUESTION;
	_vocabulary["why"] = QUESTION;
	_vocabulary["where"] = QUESTION;
	_vocabulary["which"] = QUESTION;
	_vocabulary["how"] = QUESTION;
}

void Bot::_initInsult(void) {
	_vocabulary["idiot"] = INSULT;
	_vocabulary["moron"] = INSULT;
	_vocabulary["stupid"] = INSULT;
	_vocabulary["dumb"] = INSULT;
	_vocabulary["fool"] = INSULT;
	_vocabulary["jerk"] = INSULT;
	_vocabulary["weirdo"] = INSULT;
	_vocabulary["jackass"] = INSULT;
}
