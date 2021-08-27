#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include "DoubleOutputRedirection.h"
/*
DoubleOutRedirection::DoubleOutRedirection(RShell* l){
	left = l;
}

<<<<<<< HEAD
DoubleOutRedirection::DoubleOutRedirection(RShell*l, RShell* r){
	left = l;
	right = r;
}
*/

using namespace std;

int DoubleOutRedirection::execute(int* fd, int connectorType, const char* name, int flag){

	string fileName = rhs->get_name();

	return lhs->execute(NULL, 2, fileName.c_str(), 0);

}

void DoubleOutRedirection::print(){
	lhs->print();
	cout << " >> ";
	rhs->print();
}
