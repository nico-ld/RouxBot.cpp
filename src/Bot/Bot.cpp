#include "Bot.hpp"

// === Constructor & Destructor ===
Bot::Bot() {
	_usersFileName = "users.json";
	_initVocabulary();
	
	std::cout << ROUXBOT DIM " is ready." RESET << std::endl;
}

Bot::~Bot() {
	std::cout << ROUXBOT DIM " is down." RESET << std::endl;
}

// === Exceptions ===
const char* Bot::CannotOpenFileException::what() const throw() {
	return ("Error: Cannot open 'users.json'");
}

const char* Bot::InvalidJsonFormatException::what() const throw() {
	return ("Error: `users.json` invalid format.");
}
