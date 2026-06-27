NAME		:= RouxBot
CXXFLAGS	:= -Wall -Wextra -Werror -g -std=c++98
CXX			:= c++
INC			:= -Iincludes

SRC_DIR		:= src/
BOT_DIR		:= src/Bot/
SRC			:= \
				$(SRC_DIR)main.cpp \
				$(BOT_DIR)Bot.cpp \
				$(BOT_DIR)BotUser.cpp \
				$(BOT_DIR)BotMessage.cpp \
				$(BOT_DIR)BotVocabulary.cpp

OBJ_DIR		:= obj/
OBJ			:= $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) $(OBJ) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $(INC) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f users.json

re: fclean all

.PHONY: all clean fclean re
