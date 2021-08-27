#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string>
#include <vector>
using namespace std;

#include "Base.h"
class Command:public Base
{
public:

/******************** Command Variables **************************************************/

	vector<string> args;
	string name;
	//string fileName;


/******************** Command Functions and constructor/descructor *************************/

	Command();
	virtual ~Command();
	virtual int execute();
	virtual int execute(int *fd, int connectorType, const char* fileName, int flag);      //ConnectorType:  0 is single input redir,     1 is single output redir,       2 is double output redir

/******************** Command Helper Functions ********************************************/

	virtual string get_name(){return name;}
	int execute_build_in();
	bool is_build_in();

	int execute_test();
	bool is_execute_test();
		

	char** get_arg_list();
	char** get_test_arg_list();

	void free_args(char** arg_list);
	void print_args(char** arg_list);

	char* c_str(string& arg);

	void add(string& arg) {
		args.push_back(arg);
	}

	void print_full_info();
	virtual void print();
};

#endif


