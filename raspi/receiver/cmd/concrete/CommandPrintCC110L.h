/*
 * CommandPrintCC110L.h
 *
 *  Created on: 22.03.2016
 *      Author: Richard Treichl
 */

#ifndef CONCRETE_COMMANDPRINTCC110L_H_
#define CONCRETE_COMMANDPRINTCC110L_H_

#include "../Command.h"
#include "../../driver/extern/cc110l/cc110l.h"

class CommandCC110LPrint : public Command {
private:
	CC110L * mCC110L;
	std::string mWhat;

public:
	CommandCC110LPrint(CC110L * ptrCC110L);
	~CommandCC110LPrint() {}

	virtual void parse(CommandParser & cmdParser) ;
	virtual void _execute();
};

#endif /* CONCRETE_COMMANDPRINTCC110L_H_ */
