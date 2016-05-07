#ifndef _COMMANDPRINTPARAM_H_
#define _COMMANDPRINTPARAM_H_

#include "Command.h"

class CommandPrintParam : public Command {
private:
	bool           mBoolParam;
	float          mFloatParam;
	double         mDoubleParam;
	int            mIntParam;
	unsigned int   mUIntParam;
	std::string    mStringParam;

public:
	CommandPrintParam();
	virtual ~CommandPrintParam();

	virtual void parse(CommandParser & cmdParser) ;
	virtual void _execute();
};

#endif