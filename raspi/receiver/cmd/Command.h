#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <iostream>
#include <string>
#include "Paremeter.h"

// forward declaration
class CommandParser;

// executer pattern
class Command {
protected:
	bool mExecutable;

private:
	std::string mCommandName;
	
public:
	Command(const std::string & commandName);
	virtual ~Command();

	virtual void parse(CommandParser & cmdParser) = 0;
	virtual void _execute() = 0;

	virtual void execute();

	const std::string & getName();
};

#endif