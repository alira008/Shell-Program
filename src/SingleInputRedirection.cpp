#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <string>
#include <iostream>

#include "SingleInputRedirection.h"

using namespace std;
/*
SingleInputRedirection::SingleInputRedirection(RShell* l){
	left = l;
}

SingleInputRedirection::SingleInputRedirection(RShell* l, RShell* r){
        left = l;
	right = r;
}
*/

int SingleInputRedirection::execute(int* fd, int connectorType, const char* name, int flag){
	int ret;
	string fileName = rhs->get_name();
	if(name){
		ret = lhs->execute(fd, 0, fileName.c_str(), 0);
		ret = lhs->execute(fd, connectorType, name, flag);
	}
	else{
		ret = lhs->execute(fd, 0, fileName.c_str(), 0);
	}
	return ret;

}

void SingleInputRedirection::print(){
	lhs->print();
	cout << " < ";
	rhs->print();
}

