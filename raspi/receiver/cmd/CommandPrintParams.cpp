#include "CommandPrintParams.h"
#include "CommandParser.h"

CommandPrintParam::CommandPrintParam() : Command("PrintParams") {
	// empty
}

CommandPrintParam::~CommandPrintParam() {
	// empty
}

void CommandPrintParam::parse(CommandParser & cmdParser) {
	//bool           boolParam;
	//float          floatParam;
	//double         doubleParam;
	//int            intParam;
	//unsigned int   uintParam;
	//std::string    stringParam;

	// default value true
	this->mExecutable = true;

	// test reversed
	this->mExecutable &= cmdParser.read("-s", this->mStringParam);
	this->mExecutable &= cmdParser.read("-u", this->mUIntParam);
	this->mExecutable &= cmdParser.read("-i", this->mIntParam);
	this->mExecutable &= cmdParser.read("-d", this->mDoubleParam);
	this->mExecutable &= cmdParser.read("-f", this->mFloatParam);
	this->mExecutable &= cmdParser.read("-b", this->mBoolParam);
}

void CommandPrintParam::_execute() {
	std::cout << "CMD >> " << this->getName()
		<< " -s: " << this->mStringParam
		<< " -u: " << this->mUIntParam
		<< " -i: " << this->mIntParam
		<< " -d: " << this->mDoubleParam
		<< " -f: " << this->mFloatParam
		<< " -b: " << this->mBoolParam
		<< std::endl;
}
