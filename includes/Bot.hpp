#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>

// === Text decoration ===
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define DIM "\033[2m"
#define ITALIC "\033[3m"

// === RouxBot label ===
#define ROUXBOT DIM ITALIC "RouxBot" RESET

enum e_message_type {
	UNKNOW,
	HELLO,
	ACTION,
	QUESTION,
	INSULT
};

class Bot
{
	public:
		// === Constructor & Destructor === 
		Bot();
		~Bot();

		// === Methods ===
		// ~~ Messages methods ~~
		int processMessage(std::string &message);

		// ~~ Users methods ~~
		void setUser(std::string userName);
		void addUser(std::string userName);
		void deleteUser(std::string userName);
		std::string getUserInfo(std::string userName) const;

		// === Exceptions ===
		class CannotOpenFileException: public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class UserNameEmptyException: public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class RemoveTmpFileException: public std::exception {
			public:
				virtual const char* what() const throw();
		};

	private:
		std::string		_usersFileName;
		std::string		_message;
		std::string		_messageCopy;
		int				_messageType;

		// === Vocabulary ===
		std::map<std::string, void (Bot::*)(std::string)> _actionUser;
		void _initActionUser( void );
};