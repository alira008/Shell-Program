#ifndef __PARSER_H__
#define __PARSER_H__
#include <vector>
#include <string>
#include <stack>
using namespace std;

#include "Base.h"
#include "Command.h"

class Parser
{
public:
	string line;

	vector<string>  string_list;
	vector<vector<string>>	token_list;
	vector<string>	parsedCmds;
	string cur_str;

public:
	Parser(const string& line):line(line){};
	virtual ~Parser();

public:
	Base* parse();
	void remove_comment();
	
	Base* build_tree();
	void paren();
	void parseConnectors();
	void postFixList();

	void add_new();
	void add_new(const string& str);
	
	void print_string_list();

	bool is_connector(string& str);
};

#endif

