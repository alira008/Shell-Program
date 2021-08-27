#include "Parser.h"
#include "RShell.h"

int main() {
	//string line = "echo ; echo || \" && a b c\" || \" ;d e f\" && \"# test\" # coo  ";
	//string line = "echo a b c ; ls -b && echo test";
	//Parser parser(line);
	RShell rshell;
	rshell.run();

	return 0;
}
