#include "Command.h"

Command::Command(const std::string & commandName) {
	// default not executable
	this->mExecutable = true;
	this->mCommandName = commandName;
}

Command::~Command() {
	// empty
}

void Command::execute() {
	if (!this->mExecutable)
		std::cout << this->mCommandName << ": is not executable error param missing?" << std::endl;
	else
		this->_execute();
}

const std::string & Command::getName() {
	return this->mCommandName;
}