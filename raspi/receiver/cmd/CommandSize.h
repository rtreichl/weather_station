#ifndef _COMMANDPRINTSIZE_H_
#define _COMMANDPRINTSIZE_H_

#include "Command.h"

class CommandSize : public Command {
private:
	int mWidth;
	int mHeight;

public:
	CommandSize();
	virtual ~CommandSize();

	virtual void parse(CommandParser & cmdParser);
	virtual void _execute();
};

#endif
