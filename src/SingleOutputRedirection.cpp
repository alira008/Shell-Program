#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include "SingleOutputRedirection.h"
/*
SingleOutRedirection::SingleOutRedirection(RShell* l){
	left = l;
}

<<<<<<< HEAD
SingleOutRedirection::SingleOutRedirection(RShell* l, RShell* r){
        left = l;
	right = r;
}
*/

using namespace std;

int SingleOutRedirection::execute(int* fd, int connectorType, const char* name, int flag){

	string fileName = rhs->get_name();
	
	return lhs->execute(fd, 1, fileName.c_str(), 0);

}

void SingleOutRedirection::print(){
	lhs->print();
	cout << " > ";
	rhs->print();
}
