#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

#include "Command.h"

Command::Command()
{

}


Command::~Command()
{
}

int Command::execute_build_in()
{
	if (name == "exit") {
		return EXIT;
	}
	return FAIL;
}

int Command::execute_test(){
	string f = "-f";
	string d = "-d";
	char *f_flag = c_str(f);
	char *d_flag = c_str(d);
	struct stat sb;
	char **arg_list = get_test_arg_list();
	if(-1 == stat(arg_list[1], &sb)){
		cout<< "(False)" << endl;
		return FAIL;
	}
	if(args[0] == f){
		if(S_ISREG(sb.st_mode)){
			cout << "(True)" << endl;
			return SUCCESS;
		}
		else{
			cout << "(False)" << endl;
			return FAIL;
		}
	}
	else if(args[0] == d){
		if(S_ISDIR(sb.st_mode)){
			cout << "(True)" << endl;
			return SUCCESS;
		}
		else{
			cout << "(False)" << endl;
			return FAIL;
		}
	}
	else{
		cout << "(True)" << endl;
		return SUCCESS;
	}
}

bool Command::is_execute_test(){
	return name == "test";
}

int Command::execute()
{
	if (test_mode)
	{
		cout << "will execute command: ";
		print();
		cout << endl;
	}

	if (is_build_in()){
		return execute_build_in();
	}
	
	if(is_execute_test()){
		return execute_test();
	}


	char **arg_list = get_arg_list();
	if (test_mode) {
		print_args(arg_list);
	}


	int pid;
	pid = fork();

	if (pid < 0)
	{
		perror("an error occurs in fork");
		exit(-1);
	}
	else if (pid == 0) {
		int ret = ::execvp(arg_list[0], arg_list);
		cout << "result_code:" << ret << endl;
		perror("an error occurs in execvp with result code:");
		exit(-1);
	}
	else {
		int status = 0;
		while (true)
		{
			int child_id = wait(&status);
			if (child_id < 0)
			{
				perror("an error occurs in wait");
				exit(-1);
			}
			else if (child_id == pid) {
				break;
			}
		}

		free_args(arg_list);

		if (WIFEXITED(status)) {
			if (test_mode)
			{
				cout << "the child process exit normally" << endl;
			}

			int exit_value = WEXITSTATUS(status);
			if (exit_value == 0)
				return SUCCESS;
			else 
				return FAIL;
		}
		else {
			if (test_mode)
			{
				cout << "the child process exit from some error" << endl;
			}
			return FAIL;
		}
	}

	return SUCCESS;
}

int Command::execute(int *fd, int connectorType, const char* fileName, int flag){
	int inputOutput = (connectorType >= 1) ? 1 : 0;

	if (test_mode)
	{
		cout << "will execute command: ";
		print();
		cout << endl;
	}

	if (is_build_in()){
		return execute_build_in();
	}
	
	if(is_execute_test()){
		return execute_test();
	}


	char **arg_list = get_arg_list();
	if (test_mode) {
		print_args(arg_list);
	}

	int saveStdInOut = dup(inputOutput);
	if(!flag){
		switch(connectorType){
			case 0:
				fd[inputOutput] = open(fileName, O_RDONLY);
       				if(fd[inputOutput] < 0){
        	        		perror("error opening file");
        	        		exit(-1);
        			}		
				break;
			case 1:
				fd[inputOutput] = open(fileName, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IWOTH);
			        if(fd[inputOutput] < 0){
        	 		       	perror("error opening file");
       		 			exit(-1);
        			}
				break;
			case 2: 
				fd[inputOutput] = open(fileName, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IWOTH);
			        if(fd[inputOutput] < 0){
        	        		perror("error opening file");
        	        		exit(-1);
       		 		}
				break;
			default:
				break;
		}
	}

	int pid;
	pid = fork();

	if (pid < 0)
	{
		perror("an error occurs in fork");
		exit(-1);
	}
	else if (pid == 0) 
	{
		if(connectorType != 3 && !flag){
			close(inputOutput);
			if(dup2(fd[inputOutput], inputOutput) < 0){
				perror("an error in dup2");
				exit(-1);
			}
		}
		else if(connectorType != 3 && flag){
			close(inputOutput);
			if(dup2(fd[inputOutput], inputOutput) < 0){
				perror("an error in dup2");
				exit(-1);
			}
		}	
		if(execvp(arg_list[0], arg_list) < 0){
			perror("an error occurs in execvp with result code:");
			exit(-1);
		}
	}
	else {
		int status = 0;
		while (true)
		{
			int child_id = wait(&status);
			if (child_id < 0)
			{
				perror("an error occurs in wait");
				exit(-1);
			}
			else if (child_id == pid) {
				break;
			}
		}

		free_args(arg_list);
		
		if (WIFEXITED(status)) {
			if (test_mode)
			{
				cout << "the child process exit normally" << endl;
			}

			int exit_value = WEXITSTATUS(status);
			if (exit_value == 0)
				return SUCCESS;
			else 
				return FAIL;
		}
		else {
			if (test_mode)
			{
				cout << "the child process exit from some error" << endl;
			}
			return FAIL;
		}
		if(connectorType != 3){
			if(dup2(saveStdInOut, inputOutput) < 0){
				perror("error in stdinout");
				exit(-1);
			}	
		}
	}
	return SUCCESS;
}



bool Command::is_build_in(){
	return name == "exit";
}

char** Command::get_arg_list()
{
	
	int L = args.size();

	char **arg_list = new char*[L + 2];
	int i = 0;
	arg_list[0] = c_str(name);
	++i;
	int j = 0;
	for (i = 1; j < L; ++i, ++j)
		arg_list[i] = c_str(args[j]);

	arg_list[i] = NULL;

	return arg_list;
}

void Command::free_args(char** arg_list)
{
	for (int i = 0;arg_list[i] != NULL;++i) {
		delete[] arg_list[i];
	}
	delete[] arg_list;
}

char** Command::get_test_arg_list()
{
	string e_flag = "-e";
	string f_flag = "-f";
	string d_flag = "-d";
        int L = args.size();

        char **arg_list = new char*[L  + 2 - 1];
       	int i = 0;
	int j = 0;
	if(args[0] == "-e"){
		arg_list[0] = c_str(e_flag);
		++j;
	}
	else if(args[0] == "-f"){
		arg_list[0] = c_str(f_flag);
		++j;
	}
	else if(args[0] == "-d"){
		arg_list[0] = c_str(d_flag);
		++j;
	}
	else{
		arg_list[0] = c_str(e_flag);
	}
        for ( i = 1; j < L; ++i, ++j)
                arg_list[i] = c_str(args[j]);

        arg_list[i] = NULL;

        return arg_list;
}

void Command::print_args(char** arg_list)
{
	for (int i = 0; arg_list[i] != NULL; ++i) {
		cout << arg_list[i] << endl;
	}
}

char* Command::c_str(string& arg)
{
	int L = arg.size();
	char* p = new char[L + 1];
	memset(p, 0, L + 1);
	strncpy(p, arg.c_str(), L);
	return p;
}

void Command::print_full_info()
{
	cout << "comand name:" << name << endl;;
	cout << "has " <<args.size() << " arguments: " << endl;
	for (auto const &e : args)
		cout << e << endl;
	cout << endl;
}

void Command::print()
{
	cout << name;
	for (auto const &e : args) {
		cout << " ";
		bool quote_flag = (e.find(' ') != string::npos);
		if (quote_flag)
			cout << "\"";
		cout << e;
		if (quote_flag)
			cout << "\"";
	}
}

