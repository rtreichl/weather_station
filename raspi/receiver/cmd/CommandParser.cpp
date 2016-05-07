#include "CommandParser.h"
#include <algorithm>
#include <sstream>

std::vector<std::string> explode(const std::string & str, const char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream tokenStream(str);
	std::string tempStr;

	while (std::getline(tokenStream, tempStr, delimiter))
		tokens.push_back(tempStr);

	return tokens;
}

CommandParser::CommandParser() {

}

CommandParser::~CommandParser() {
	// clear command list
	for (auto cmdPair : this->mCommands)
		delete cmdPair.second;
}

// register command to commandmap
void CommandParser::registerCmd(Command * cmd) {
	CommandPair pair;
	pair.first = cmd->getName();
	pair.second = cmd;
	this->mCommands.insert(pair);
}

// execute command with name of token[0]
void CommandParser::executeCmd() {
	if (this->mTokens.size() > 0) {
		CommandMap::iterator itr = this->mCommands.find(this->mTokens[0]);
		if (itr != this->mCommands.end()) {
			itr->second->parse(*this);
			itr->second->execute();
		} else
			std::cout << this->mTokens[0] << " command doesnt exist!" << std::endl;
	} else
		std::cout << "no valid input" << std::endl;
}

void CommandParser::setCommandLine(const std::string & cmdLine) {
	this->mTokens = explode(cmdLine, ' ');
}

bool CommandParser::isOption(int pos) const
{
	return static_cast<size_t>(pos) < this->mTokens.size() && Parameter::isOption(this->mTokens[pos].c_str());
}

bool CommandParser::isString(int pos) const
{
	return static_cast<size_t>(pos) < this->mTokens.size() && Parameter::isString(this->mTokens[pos].c_str());
}

bool CommandParser::isNumber(int pos) const
{
	return static_cast<size_t>(pos) < this->mTokens.size() && Parameter::isNumber(this->mTokens[pos].c_str());
}


int CommandParser::find(const std::string& str) const
{
	for (int pos = 1; static_cast<size_t>(pos) < this->mTokens.size() ;++pos)
	{
		if (str == this->mTokens[pos])
		{
			return pos;
		}
	}
	return -1;
}

bool CommandParser::match(int pos, const std::string& str) const
{
	return static_cast<size_t>(pos) < this->mTokens.size() && str == this->mTokens[pos];
}


bool CommandParser::containsOptions() const
{
	for (int pos = 1; static_cast<size_t>(pos) < this->mTokens.size() ;++pos)
	{
		if (isOption(pos)) return true;
	}
	return false;
}


void CommandParser::remove(int pos, int num)
{
	if (num == 0) return;

	for (size_t i = 0; i < static_cast<size_t>(num); ++i)
		this->mTokens.erase(this->mTokens.begin() + pos);
}

bool CommandParser::read(const std::string& str)
{
	int pos = find(str);
	if (pos <= 0) return false;
	remove(pos);
	return true;
}

bool CommandParser::read(const std::string& str, Parameter value1)
{
	int pos = find(str);
	if (pos <= 0) return false;
	return read(pos, str, value1);
}

bool CommandParser::read(const std::string& str, Parameter value1, Parameter value2)
{
	int pos = find(str);
	if (pos <= 0) return false;
	return read(pos, str, value1, value2);
}

bool CommandParser::read(const std::string& str, Parameter value1, Parameter value2, Parameter value3)
{
	int pos = find(str);
	if (pos <= 0) return false;
	return read(pos, str, value1, value2, value3);
}

bool CommandParser::read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4)
{
	int pos = find(str);
	if (pos <= 0) return false;
	return read(pos, str, value1, value2, value3, value4);
}

bool CommandParser::read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5)
{
	int pos = find(str);
	if (pos <= 0) return false;
	return read(pos, str, value1, value2, value3, value4, value5);
}

bool CommandParser::read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6)
{
	int pos = find(str);
	if (pos <= 0) return false;
	return read(pos, str, value1, value2, value3, value4, value5, value6);
}

bool CommandParser::read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7)
{
	int pos = find(str);
	if (pos <= 0) return false;
	return read(pos, str, value1, value2, value3, value4, value5, value6, value7);
}

bool CommandParser::read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7, Parameter value8)
{
	int pos = find(str);
	if (pos <= 0) return false;
	return read(pos, str, value1, value2, value3, value4, value5, value6, value7, value8);
}

/** if the argument value at the position pos matches specified string, and subsequent
* Parameters are also matched then set the Parameter values and remove the from the list of arguments.*/
bool CommandParser::read(int pos, const std::string& str)
{
	if (match(pos, str))
	{
		remove(pos, 1);
		return true;
	}
	return false;
}

bool CommandParser::read(int pos, const std::string& str, Parameter value1)
{
	if (match(pos, str))
	{
		if (static_cast<size_t>(pos + 1)< this->mTokens.size() )
		{
			if (value1.valid(this->mTokens[pos + 1].c_str()))
			{
				value1.assign(this->mTokens[pos + 1].c_str());
				remove(pos, 2);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool CommandParser::read(int pos, const std::string& str, Parameter value1, Parameter value2)
{
	if (match(pos, str))
	{
		if (static_cast<size_t>(pos + 2)< this->mTokens.size() )
		{
			if (value1.valid(this->mTokens[pos + 1].c_str()) &&
				value2.valid(this->mTokens[pos + 2].c_str()))
			{
				value1.assign(this->mTokens[pos + 1].c_str());
				value2.assign(this->mTokens[pos + 2].c_str());
				remove(pos, 3);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool CommandParser::read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3)
{
	if (match(pos, str))
	{
		if (static_cast<size_t>(pos + 3)< this->mTokens.size() )
		{
			if (value1.valid(this->mTokens[pos + 1].c_str()) &&
				value2.valid(this->mTokens[pos + 2].c_str()) &&
				value3.valid(this->mTokens[pos + 3].c_str()))
			{
				value1.assign(this->mTokens[pos + 1].c_str());
				value2.assign(this->mTokens[pos + 2].c_str());
				value3.assign(this->mTokens[pos + 3].c_str());
				remove(pos, 4);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool CommandParser::read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4)
{
	if (match(pos, str))
	{
		if (static_cast<size_t>(pos + 4)< this->mTokens.size() )
		{
			if (value1.valid(this->mTokens[pos + 1].c_str()) &&
				value2.valid(this->mTokens[pos + 2].c_str()) &&
				value3.valid(this->mTokens[pos + 3].c_str()) &&
				value4.valid(this->mTokens[pos + 4].c_str()))
			{
				value1.assign(this->mTokens[pos + 1].c_str());
				value2.assign(this->mTokens[pos + 2].c_str());
				value3.assign(this->mTokens[pos + 3].c_str());
				value4.assign(this->mTokens[pos + 4].c_str());
				remove(pos, 5);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool CommandParser::read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5)
{
	if (match(pos, str))
	{
		if (static_cast<size_t>(pos + 5)< this->mTokens.size() )
		{
			if (value1.valid(this->mTokens[pos + 1].c_str()) &&
				value2.valid(this->mTokens[pos + 2].c_str()) &&
				value3.valid(this->mTokens[pos + 3].c_str()) &&
				value4.valid(this->mTokens[pos + 4].c_str()) &&
				value5.valid(this->mTokens[pos + 5].c_str()))
			{
				value1.assign(this->mTokens[pos + 1].c_str());
				value2.assign(this->mTokens[pos + 2].c_str());
				value3.assign(this->mTokens[pos + 3].c_str());
				value4.assign(this->mTokens[pos + 4].c_str());
				value5.assign(this->mTokens[pos + 5].c_str());
				remove(pos, 6);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool CommandParser::read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6)
{
	if (match(pos, str))
	{
		if (static_cast<size_t>(pos + 6)< this->mTokens.size() )
		{
			if (value1.valid(this->mTokens[pos + 1].c_str()) &&
				value2.valid(this->mTokens[pos + 2].c_str()) &&
				value3.valid(this->mTokens[pos + 3].c_str()) &&
				value4.valid(this->mTokens[pos + 4].c_str()) &&
				value5.valid(this->mTokens[pos + 5].c_str()) &&
				value6.valid(this->mTokens[pos + 6].c_str()))
			{
				value1.assign(this->mTokens[pos + 1].c_str());
				value2.assign(this->mTokens[pos + 2].c_str());
				value3.assign(this->mTokens[pos + 3].c_str());
				value4.assign(this->mTokens[pos + 4].c_str());
				value5.assign(this->mTokens[pos + 5].c_str());
				value6.assign(this->mTokens[pos + 6].c_str());
				remove(pos, 7);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool CommandParser::read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7)
{
	if (match(pos, str))
	{
		if (static_cast<size_t>(pos + 7)< this->mTokens.size() )
		{
			if (value1.valid(this->mTokens[pos + 1].c_str()) &&
				value2.valid(this->mTokens[pos + 2].c_str()) &&
				value3.valid(this->mTokens[pos + 3].c_str()) &&
				value4.valid(this->mTokens[pos + 4].c_str()) &&
				value5.valid(this->mTokens[pos + 5].c_str()) &&
				value6.valid(this->mTokens[pos + 6].c_str()) &&
				value7.valid(this->mTokens[pos + 7].c_str()))
			{
				value1.assign(this->mTokens[pos + 1].c_str());
				value2.assign(this->mTokens[pos + 2].c_str());
				value3.assign(this->mTokens[pos + 3].c_str());
				value4.assign(this->mTokens[pos + 4].c_str());
				value5.assign(this->mTokens[pos + 5].c_str());
				value6.assign(this->mTokens[pos + 6].c_str());
				value7.assign(this->mTokens[pos + 7].c_str());
				remove(pos, 8);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool CommandParser::read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7, Parameter value8)
{
	if (match(pos, str))
	{
		if (static_cast<size_t>(pos + 8)< this->mTokens.size() )
		{
			if (value1.valid(this->mTokens[pos + 1].c_str()) &&
				value2.valid(this->mTokens[pos + 2].c_str()) &&
				value3.valid(this->mTokens[pos + 3].c_str()) &&
				value4.valid(this->mTokens[pos + 4].c_str()) &&
				value5.valid(this->mTokens[pos + 5].c_str()) &&
				value6.valid(this->mTokens[pos + 6].c_str()) &&
				value7.valid(this->mTokens[pos + 7].c_str()) &&
				value8.valid(this->mTokens[pos + 8].c_str()))
			{
				value1.assign(this->mTokens[pos + 1].c_str());
				value2.assign(this->mTokens[pos + 2].c_str());
				value3.assign(this->mTokens[pos + 3].c_str());
				value4.assign(this->mTokens[pos + 4].c_str());
				value5.assign(this->mTokens[pos + 5].c_str());
				value6.assign(this->mTokens[pos + 6].c_str());
				value7.assign(this->mTokens[pos + 7].c_str());
				value8.assign(this->mTokens[pos + 8].c_str());
				remove(pos, 9);
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}