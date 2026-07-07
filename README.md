# RouxBot.cpp

## Description
**RouxBot.cpp** is a C++98 chatbot designed to be compatible with *ft_irc* (a 42 project). Its goal is to learn from your behavior in order to provide better responses over time. This repository includes two versions of the bot: one tailored for *ft_irc* and another standalone version without any project-specific constraints. 

## Usage
> This project is still a work in progress, but there are already some features you can try.

To start the bot you have to compile it with `make`, then execute : 
```bash
./RouxBot <userName>
```

The program will not start unless you provide a _username_. This allows **RouxBot** to identify the person it is talking to. To interact with the bot, simply mention its name in your message, You can mention it anywhere in your message. Its name is case-insensitive.

```
> Hello RouxBot ! 

> rouxbot Hello ! 
```

For now, you can use a few commands to manage _users.json_ (this file is created automatically the first time RouxBot is run):

|Command|Description                                            |
|:--------|:------------------------------------------------------|
|!add     |Add a new user to the _users.json_ if he doesn't exist |
|!delete  |Delete a user from _users.json_                        |
|!set     |Set the users that talk to RouxBot, or create it       |
|!behavior|Set Manually the behavior of a user that already exist |

To use the you have to precise wich user after the command : 
```
> rouxbot !add nico
```

## Resources 
- Stackoverflow
- GeekforGeek
- W3school
- cplusplus

### AI usage
Some AI tools (Claude and ChatGPT) were used to translate this page and help me solve some issues.

