#include "Bot.hpp"

// === Constructor & Destructor ===
Bot::Bot() {
	_usersFileName = "users.json";
	
	std::cout << ROUXBOT DIM " is ready." RESET << std::endl;
}

Bot::~Bot() {
	std::cout << ROUXBOT DIM " is down." RESET << std::endl;
}

// === Methods ===
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

// ~~ Users methods ~~
void Bot::setUser(std::string userName) {
	if (userName.empty())
		throw UserNameEmptyException();

	if (getUserInfo(userName).empty())
		addUser(userName);
}

void Bot::addUser(std::string userName) {
	if (userName.empty())
		throw UserNameEmptyException();

	std::ofstream usersFile(_usersFileName.c_str(), std::ios::app);
	if (!usersFile.is_open())
		throw CannotOpenFileException();
	
	usersFile << "{\"name\":\"" << userName << "\", \"behavior\":0}" << std::endl;
	usersFile.close();
	std::cout << DIM "User : " ITALIC << userName << RESET DIM " added." RESET << std::endl;
}

void Bot::deleteUser(std::string userName) {
	if (userName.empty())
		throw UserNameEmptyException();

	std::fstream usersFile(_usersFileName.c_str());
	if (!usersFile.is_open())
		throw CannotOpenFileException();

	std::cout << DIM "Deleting user : " ITALIC << userName << RESET DIM "..." RESET << std::endl;
	std::string line;
	std::vector<std::string> updatedFile;
	while (getline(usersFile, line)) {
		if (line.find(userName, 0) == std::string::npos) {
			std::cout << DIM "Save " ITALIC << line << RESET << std::endl;
			updatedFile.push_back(line.append("\n"));
		}
	}
	usersFile.close();
	usersFile.open(_usersFileName.c_str(), std::ios::out | std::ios::trunc);

	std::vector<std::string>::iterator it;
	for (it = updatedFile.begin(); it != updatedFile.end(); ++it) {
		usersFile << *it;
	}
	usersFile.close();
	std::cout << DIM "User : " ITALIC << userName << RESET DIM " have been deleted" << std::endl;
}

std::string Bot::getUserInfo(std::string userName) const {
	if (userName.empty())
		return ("");

	std::fstream _usersFile(_usersFileName.c_str());
	if (!_usersFile.is_open())
		throw CannotOpenFileException();
	
	std::string line;
	while (std::getline(_usersFile, line)) {
		if (line.find(userName, 0)) {
			_usersFile.close();
			return (line);
		}
	}
	_usersFile.close();
	return ("");
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
