#include "Bot.hpp"

// === Constructor & Destructor ===
Bot::Bot() {
	_usersFileName = "users.json";
	_messageType = UNKNOW;
	
	std::cout << ROUXBOT DIM " is ready." RESET << std::endl;
}

Bot::~Bot() {
	std::cout << ROUXBOT DIM " is down." RESET << std::endl;
}

// === Exceptions ===
const char* Bot::CannotOpenFileException::what() const throw() {
	return ("Error: Cannot open 'users.json'");
}

const char* Bot::UserNameEmptyException::what() const throw() {
	return ("Error: The USER name is empty.");
}

const char* Bot::RemoveTmpFileException::what() const throw() {
	return ("Error: An error occurs while trying to remove 'tmpUsers.json'.");
}
