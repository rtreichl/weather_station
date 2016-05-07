/*
 * CommandPrint.cpp
 *
 *  Created on: 03.03.2016
 *      Author: Richard Treichl
 */

#include "CommandPrint.h"
#include "../CommandParser.h"

CommandPrint::CommandPrint(HDC1000 * ptrHDC1000) : Command("print") {
	this->mHDC1000 = ptrHDC1000;
	this->mWhat = "";
}

void CommandPrint::parse(CommandParser & cmdParser) {
	//bool           boolParam;
	//float          floatParam;
	//double         doubleParam;
	//int            intParam;
	//unsigned int   uintParam;
	//std::string    stringParam;

	// default value true
	this->mExecutable = true;

	// test reversed
	cmdParser.read("-what", this->mWhat);
}

void CommandPrint::_execute() {
	if(this->mWhat == "humidity") {
		float humidity = this->mHDC1000->ReadHumidity();
		cout << "HDC Humidity: " << humidity << std::endl;
	}
	// 3. Fall what = ""
	else {
		float temp = this->mHDC1000->ReadTemperature();
		cout << "HDC Temperature: " << temp << std::endl;
	}
}
