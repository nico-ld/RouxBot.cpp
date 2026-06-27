#include "Bot.hpp"

void Bot::setUser(std::string userName) {
	if (userName.empty())
		return ;

	if (getUserInfo(userName).empty())
		addUser(userName);
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
