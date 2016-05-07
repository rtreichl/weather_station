#ifndef _COMMANDPARSER_H_
#define _COMMANDPARSER_H_

#include <vector>

#include "Paremeter.h"
#include "Command.h"

typedef std::map<std::string, Command*> CommandMap;
typedef std::pair<std::string, Command*> CommandPair;

class CommandParser {
protected:
	std::vector<std::string> mTokens;
	CommandMap mCommands;

public:
	// null set constructor
	CommandParser();
	~CommandParser();

	// register command to commandmap
	void registerCmd(Command * cmd);

	// execute command with name of token[0]
	void executeCmd();

	// set command params
	void setCommandLine(const std::string & cmdLine);

	/** Return the argument count. */
	int argc() { return mTokens.size(); }

	/** Return the argument array. */
	std::vector<std::string> & argv() { return mTokens; }
	const std::vector<std::string> & argv() const { return mTokens; }

	/** Return the char* argument at the specified position. */
	std::string & operator [] (int pos) { return mTokens[pos]; }

	/** Return the const char* argument at the specified position. */
	const std::string & operator [] (int pos) const { return mTokens[pos]; }

	/** Return the position of an occurrence of a string in the argument list.
	* Return -1 if no string is found. */
	int find(const std::string& str) const;

	/** Return true if the specified parameter is an option in the form of
	* -option or --option. */
	bool isOption(int pos) const;

	/** Return true if the specified parameter is a string not in
	* the form of an option. */
	bool isString(int pos) const;

	/** Return true if the specified parameter is a number. */
	bool isNumber(int pos) const;
	bool containsOptions() const;

	/** Remove one or more arguments from the argv argument list,
	* and decrement the argc respectively. */
	void remove(int pos, int num = 1);

	/** Return true if the specified argument matches the given string. */
	bool match(int pos, const std::string& str) const;

	/** Search for an occurrence of a string in the argument list. If found,
	* remove that occurrence and return true. Otherwise, return false. */
	bool read(const std::string& str);
	bool read(const std::string& str, Parameter value1);
	bool read(const std::string& str, Parameter value1, Parameter value2);
	bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3);
	bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4);
	bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5);
	bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6);
	bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7);
	bool read(const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7, Parameter value8);


	/** If the argument value at the specified position matches the given string,
	* and subsequent parameters are also matched, then set the parameter values,
	* remove the arguments from the list, and return true. Otherwise, return false. */
	bool read(int pos, const std::string& str);
	bool read(int pos, const std::string& str, Parameter value1);
	bool read(int pos, const std::string& str, Parameter value1, Parameter value2);
	bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3);
	bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4);
	bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5);
	bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6);
	bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7);
	bool read(int pos, const std::string& str, Parameter value1, Parameter value2, Parameter value3, Parameter value4, Parameter value5, Parameter value6, Parameter value7, Parameter value8);
};

#endif