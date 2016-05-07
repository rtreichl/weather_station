#include "CommandParser.h"
#include "CommandPrintParams.h"
#include "CommandSize.h"

//int main(int argc, char **argv) {
//	// example usage:
//	CommandParser cmdParser;
//	std::string line;
//
//	// register cmds
//	cmdParser.registerCmd(new CommandPrintParam());
//	cmdParser.registerCmd(new CommandSize());
//
//	// read command line
//	// till exit
//
//	std::cout << "cmd << ";
//	while (std::getline(std::cin, line)) {
//		if (line != "exit" && line.size() != 0) {
//			cmdParser.setCommandLine(line);
//			cmdParser.executeCmd();
//			std::cout << "cmd << ";
//		}
//		else if(line == "exit")
//			break;
//	}
//
//	return 0;
//}

// example of CommandPrintParams
/*
int main(int argc, char **argv) {
	// example usage:
	CommandParser cmdParser;
	CommandPrintParam cmd;
	std::string line;

	std::cout << "cmd << ";
	while (std::getline(std::cin, line)) {
		if (line != "exit") {
			cmdParser.setCommandLine(line);
			cmd.parse(cmdParser);
			cmd.execute();
			std::cout << "cmd << ";
		}
		else
		break;
	}

	return 0;
}
*/

// example of CommandParser only
/*
int main(int argc, char **argv) {
	// example usage:
	CommandParser cmdParser;
	std::string line;

	while (std::getline(std::cin, line)) {
		if (line != "exit") {
			int width = 0;
			int height = 0;

			cmdParser.setCommandLine(line);
			cmdParser.read("-width -height", width, height);

			std::cout << "Tipped: " << line << std::endl;
			std::cout << "Params -width: " << width << " -height: " << height << std::endl;
			std::cout << std::endl;

		}
		else
			break;
	}

	return 0;
}
*/
