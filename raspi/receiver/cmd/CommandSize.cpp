#include "CommandSize.h"
#include "CommandParser.h"

CommandSize::CommandSize() : Command("Size") {
	// empty
}

CommandSize::~CommandSize() {
	// empty
}

void CommandSize::parse(CommandParser & cmdParser) {
	//bool           boolParam;
	//float          floatParam;
	//double         doubleParam;
	//int            intParam;
	//unsigned int   uintParam;
	//std::string    stringParam;

	// default value true
	this->mExecutable = true;

	// test reversed
	this->mExecutable &= cmdParser.read("-width", this->mWidth);
	this->mExecutable &= cmdParser.read("-height", this->mHeight);
}

void CommandSize::_execute() {
	std::cout << "CMD >> " <<  this->getName()
		<< " -width: " << this->mWidth
		<< " -height: " << this->mHeight
		<< std::endl;
}
