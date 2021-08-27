#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

int main() {
	pid_t pid;
	pid = fork();
	char *cmdList[2]; 
	cmdList[0] = "ls";
	cmdList[1] = NULL;
	if (pid == 0) {
		cout << "This is child process, pid number is: " << getpid() << endl; 
		execvp(cmdList[0], cmdList);
		cout << "execvp failed" << endl;
		exit(1);
	}
	else if(pid == -1) {
		cout << "fork failed" << endl;
		exit(1);
	}
	else if(pid > 0) {
		cout << "This is parent process, pid number is: " << getpid() << endl;
		waitpid(pid, NULL,0);
	}
	return 0;
}
