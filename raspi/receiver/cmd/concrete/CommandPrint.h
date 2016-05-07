/*
 * CommandPrint.h
 *
 *  Created on: 03.03.2016
 *      Author: Richard Treichl
 */

#ifndef _CMD_CONCRETE_COMMANDPRINT_H_
#define _CMD_CONCRETE_COMMANDPRINT_H_

#include "../Command.h"
#include "../../driver/extern/hdc1000/hdc1000.h"

class CommandPrint : public Command {
private:
	HDC1000 * mHDC1000;
	std::string mWhat;

public:
	CommandPrint(HDC1000 * ptrHDC1000);
	~CommandPrint() {}

	virtual void parse(CommandParser & cmdParser) ;
	virtual void _execute();
};



#endif /* CONCRETE_COMMANDPRINT_H_ */
