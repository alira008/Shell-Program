#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <iostream>
#include "Pipe.h"

using namespace std;

int Pipe::execute(int* fd, int connectorType, const char* name, int flag){

	int fds[2];

	if(pipe(fds) < 0){
		perror("error in pipe");
		exit(-1);
	}
	close(fds[0]);	
	int ret = lhs->execute(fds, 1, NULL, 1);
	
	close(fds[1]);	
	if(ret == FAIL)
		return FAIL;
	else{
		ret = rhs->execute(fds, 0, NULL, 1);
		if(ret == FAIL)
			return FAIL;
		else{
			close(fds[0]);
			return SUCCESS;
		}
	}

}

void Pipe::print(){
	lhs->print();
	cout << " | ";
	rhs->print();
}
