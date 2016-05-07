/*
 * CommandPrintCC110L.cpp
 *
 *  Created on: 22.03.2016
 *      Author: Richard Treichl
 */

#include "CommandPrintCC110L.h"
#include "../CommandParser.h"

CommandCC110LPrint::CommandCC110LPrint(CC110L * ptrCC110L) : Command("CC110L") {
	this->mCC110L = ptrCC110L;
	this->mWhat = "";
}

void CommandCC110LPrint::parse(CommandParser & cmdParser) {
	//bool           boolParam;
	//float          floatParam;
	//double         doubleParam;
	//int            intParam;
	//unsigned int   uintParam;
	//std::string    stringParam;

	// default value true
	this->mExecutable = true;

	// test reversed
	cmdParser.read("-", this->mWhat);
}

void CommandCC110LPrint::_execute() {
	if(this->mWhat == "last") {
		this->mCC110L->PrintRxAvailableBytes();
	}
	else if(this->mWhat == "register") {
		this->mCC110L->ReadStatus();
		this->mCC110L->PrintStatusRegisters();
	}
	else if(this->mWhat == "fifo") {
		this->mCC110L->PrintFifoStatus();
	}
	else if(this->mWhat == "gpio") {
		this->mCC110L->PrintGpioState();
	}
	else if(this->mWhat == "status") {
		this->mCC110L->PrintStatusByte();
	}
	else {
		std::cout << "Commands are 'last', 'register', 'fifo' and 'status'!" << std::endl;
	}
}


