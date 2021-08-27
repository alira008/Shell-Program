#include <string>
#include <iostream>
using namespace std;

#include "RShell.h"
#include "Parser.h"

RShell::RShell()
{
}


RShell::~RShell()
{
}

void RShell::run()
{
	int fd[2];
	while (true)
	{
		print_prompt();
		string line;
		getline(cin, line);
		string::size_type only_spaces = line.find_first_not_of(" ");
		if(only_spaces != string::npos){	//	If there are only spaces it does not execute the tree and parser
			Parser parser(line);
			Base* tree = parser.parse();
			int ret = tree->execute(fd, 3, NULL, 0);
			if (ret == EXIT)
				break;
		}
	}
}

void RShell::print_prompt()
{
	const string prompt = "$ ";
	cout << prompt;
}

