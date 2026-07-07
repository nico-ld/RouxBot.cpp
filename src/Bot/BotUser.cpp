#include "Bot.hpp"

void Bot::setUser(std::string userName) {
	if (userName.empty())
		return ;

	_userName = userName;
	
	std::string userInfo = getUserInfo(userName);
	if (userInfo.empty()) {
		addUser(userName);
		_userBehavior = 0;
	}
	else {
		size_t pos = userInfo.find("behavior");
		if (pos == std::string::npos)
			throw InvalidJsonFormatException();
		pos += 10;
		
		_userBehavior = atoi(userInfo.c_str() + pos);
	}

	std::cout << DIM "User setted on " << _userName << ", behavior : " << _userBehavior << RESET << std::endl;
}

void Bot::setUserBehavior(std::string userName) {
	if (userName.empty())
		return ;

	std::string input;
	std::cout << "Enter the new Behavior value [-10, 10] (STOP to quit)\n > ";
	std::getline(std::cin, input);
	if (input == "STOP")
		return ;
	char *end;
	int n = std::strtol(input.c_str(), &end, 10);
	while ((n == 0 && *end) || n < -10 || n > 10) {
		std::cerr << "Error:  please enter an integer between -10 and 10 (STOP to quit)\n > ";
		std::getline(std::cin, input);
		n = std::strtol(input.c_str(), &end, 10);
		if (input == "STOP")
			return ;
	}
}

void Bot::addUser(std::string userName) {
	if (userName.empty())
		return ;

	std::ofstream usersFile(_usersFileName.c_str(), std::ios::app);
	if (!usersFile.is_open())
		throw CannotOpenFileException();
	
	usersFile << "{\"name\":\"" << userName << "\", \"behavior\":0}" << std::endl;
	usersFile.close();
	std::cout << DIM "User : " ITALIC << userName << RESET DIM " added." RESET << std::endl;
}

void Bot::deleteUser(std::string userName) {
	if (userName.empty())
		return ;

	std::fstream usersFile(_usersFileName.c_str());
	if (!usersFile.is_open())
		throw CannotOpenFileException();

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
	std::cout << DIM "User : " ITALIC << userName << RESET DIM " have been deleted" RESET << std::endl;
}

std::string Bot::getUserInfo(std::string userName) const {
	if (userName.empty())
		return ("");

	std::fstream usersFile(_usersFileName.c_str());
	if (!usersFile.is_open()) {
		usersFile.open(_usersFileName.c_str(), std::ios::out);
		if (usersFile.is_open())
			return ("");
		throw CannotOpenFileException();
	}
	
	std::string line;
	while (std::getline(usersFile, line)) {
		if (line.find(userName, 0)) {
			usersFile.close();
			return (line);
		}
	}
	usersFile.close();
	return ("");
}
