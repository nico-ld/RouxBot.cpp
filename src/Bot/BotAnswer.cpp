#include "Bot.hpp"

void Bot::answerMessage(void) {
	if (_messageType == INTENT_GREETING)
		std::cout << BOLD "Rouxbot" RESET " : hello " << std::endl;
}