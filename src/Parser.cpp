#include <cassert>
#include <iostream>
using namespace std;

#include "Base.h"
#include "Parser.h"
#include "SemicolonConnector.h"
#include "OrConnector.h"
#include "AndConnector.h"
#include "SingleInputRedirection.h"
#include "SingleOutputRedirection.h"
#include "DoubleOutputRedirection.h"
#include "Pipe.h"

Parser::~Parser()
{
}


/*********************** Removes comments from string line ***************************/
void Parser::remove_comment()
{
	size_t L = line.size();
	size_t pos = 0;
	while (pos < L) {
		char c = line[pos];
		if (c == '\"')
		{
			pos = line.find(c, pos + 1);
			assert(pos != string::npos);
			++pos;
		}
		else if (c == '#') {
			line = line.substr(0, pos);
			break;
		}
		else
		{
			++pos;
		}
	}
}

/******************** Sets Vector<string> String_List to tokens that are separated by [] and () ***************************/
void Parser::paren(){
	size_t L = line.size();
	size_t pos = 0;
	size_t pos2 = 0;
	size_t next_pos = string::npos;
	int lp_count = 0, rp_count = 0, lb_count = 0, rb_count = 0;
	while(pos < L){
		char c = line[pos];
		if(c == '('){
			add_new();	//	Pushes cur_str to String_List
			add_new("(");	//	Pushes "(" to string_list
			++pos;
			++lp_count;
		}
		else if(c == ')'){
			add_new();
			add_new(")");
			++pos;
			++rp_count;
		}
		else if(c == '['){
			add_new();
			add_new("test");
			++pos;
			++lb_count;
		}
		else if(c == ']'){
			add_new();
			++pos;
			++rb_count;
		}
		else{
			cur_str += c;
			++pos;
		}
	}
	assert(lp_count == rp_count);	//	Checks if there is an uneven number of parentheses
	assert(lb_count == rb_count);	//	Checks if there is an uneven number of brackets
	add_new();
}

/******************* Set vector<string> parsedCmds to tokens separated by ";", "||", "&&", " ", "\""" *****************************/
void Parser::parseConnectors(){

	vector<string>::iterator it = string_list.begin();
	for(it; it < string_list.end(); ++it){
		string token  = *it;
		size_t L = token.size();
		size_t pos = 0;
		size_t next_pos = string::npos;
		char c;
		while(pos < L){
			c = token[pos];
			if(c == ';'){
				if(!cur_str.empty())
					parsedCmds.push_back(cur_str);
				cur_str.clear();
				parsedCmds.push_back(";");
				++pos;
			}
			else if(c == ' '){
				if(!cur_str.empty())
					parsedCmds.push_back(cur_str);
				cur_str.clear();
				++pos;
			}
			else if(c == '\"'){
				if(!cur_str.empty())
					parsedCmds.push_back(cur_str);
				cur_str.clear();
				next_pos = token.find('\"', pos + 1);
				assert(next_pos != string::npos);
                        	parsedCmds.push_back(token.substr(pos + 1, next_pos - pos - 1));
                        	pos = next_pos + 1;
			}
			else if(c == '|'){
				if(!cur_str.empty())
                                	parsedCmds.push_back(cur_str);
                                cur_str.clear();
                                if(token[pos + 1] == '|'){
					parsedCmds.push_back("||");
                                	pos += 2;
				}
				else{
					parsedCmds.push_back("|");
					++pos;
				}
			}
			else if(c == '&'){
				if(!cur_str.empty())
                               		 parsedCmds.push_back(cur_str);
                                cur_str.clear();
                                assert(pos + 1 < L && token[pos + 1] == '&');
                                parsedCmds.push_back("&&");
                                pos += 2;
			}
			else if(c == '<'){
				if(!cur_str.empty())
					parsedCmds.push_back(cur_str);
				cur_str.clear();
				parsedCmds.push_back("<");
				++pos;
			}
			else if(c == '>'){
				if(!cur_str.empty())
					parsedCmds.push_back(cur_str);
				cur_str.clear();
				if(token[pos + 1] == '>'){
					parsedCmds.push_back(">>");
					pos += 2;
				}
				else{
					parsedCmds.push_back(">");
					++pos;
				}
			}
			else{
				cur_str += c;
				++pos;
			}
		}
		if(!cur_str.empty())
			parsedCmds.push_back(cur_str);
		cur_str.clear();
	}
}

/***************** Pushes cur_str into vector<string> string_list *********************/
void Parser::add_new()
{
	if (test_mode)
	{
		//cout << "cur_str=" << cur_str << endl;
	}
	if (!cur_str.empty())
		string_list.push_back(cur_str);

	cur_str.clear();
}

/***************** Pushes str into vector<string> string_list *************************/
void Parser::add_new(const string& str)
{
	string_list.push_back(str);
	cur_str.clear();
}

/***************** Separates tokens in the vector<string> parsedCmds into tokens in postfix notation ****************/
/***************** While separating the tokens, we push vectors that include an executable with argument lists or vectors that include only connectors  ****************/ 
void Parser::postFixList(){
	string token;
	vector<string> executables;
	vector<string> ops;
	vector<string> operators;
	vector<vector<string>> commandList;
	vector<string>::iterator parsed_cmds_it = parsedCmds.begin();
	for(parsed_cmds_it; parsed_cmds_it < parsedCmds.end(); ++parsed_cmds_it){
		token = *parsed_cmds_it;
		if(token == "("){
			if(!executables.empty()){
				commandList.push_back(executables);
				executables.clear();
			}
			ops.push_back(token);
		}
		else if(token == ")"){
			if(!executables.empty()){
				commandList.push_back(executables);
				executables.clear();
			}
			while(!ops.empty() && ops.back() != "("){
				string op = ops.back();
				operators.push_back(op);
				commandList.push_back(operators);
				operators.clear();
				ops.pop_back();
			} 
			if(!ops.empty())
				ops.pop_back();
		}
		else if(token == ";" || token == "||" || token == "&&" || token == "<" || token == ">" || token == ">>" || token == "|"){
			if(!executables.empty()){
				commandList.push_back(executables);
				executables.clear();
			}
			while(!ops.empty() && ops.back() != "("){
				string op = ops.back();
				operators.push_back(op);
				commandList.push_back(operators);
				operators.clear();
				ops.pop_back();	
			}
			ops.push_back(token);
		}
		else{
			executables.push_back(token);
		}
	}
	if(!executables.empty()){
		commandList.push_back(executables);
		executables.clear();
	}
	while(!ops.empty()){
		string op = ops.back();
		operators.push_back(op);
		commandList.push_back(operators);
		operators.clear();
		ops.pop_back();
	}
	token_list = commandList;
}

/************** This function builds the tree and returns the root of the tree *****************/
Base* Parser::build_tree(){
	vector<vector<string>>::iterator token_it = token_list.begin();
	vector<string> token_vec;
	stack<Base*> base_ptr_stack;
	for(token_it; token_it < token_list.end(); ++token_it){
		token_vec = *token_it;
		vector<string>::iterator it = token_vec.begin();
		string op = *it;
       		if(token_vec[0] == ";"){
                       	Connector* con_ptr = new SemicolonConnector;
			if(!base_ptr_stack.empty()){
				con_ptr->rhs = base_ptr_stack.top();
				base_ptr_stack.pop();
			} 
			if(!base_ptr_stack.empty()){
				con_ptr->lhs = base_ptr_stack.top();
				base_ptr_stack.pop();
			}
			base_ptr_stack.push(con_ptr);
               	}
       		else if(token_vec[0] == "||"){
                        Connector* con_ptr = new OrConnector;
                        if(!base_ptr_stack.empty()){
                                con_ptr->rhs = base_ptr_stack.top();
                                base_ptr_stack.pop();
                        }
                        if(!base_ptr_stack.empty()){
                                con_ptr->lhs = base_ptr_stack.top();
                                base_ptr_stack.pop();
                        }
                        base_ptr_stack.push(con_ptr);
                }       	       
       	        else if(token_vec[0] == "&&"){
                        Connector* con_ptr = new AndConnector;
                        if(!base_ptr_stack.empty()){
                                con_ptr->rhs = base_ptr_stack.top();
                                base_ptr_stack.pop();
                        }
                        if(!base_ptr_stack.empty()){
                                con_ptr->lhs = base_ptr_stack.top();
                                base_ptr_stack.pop();
                        }
                        base_ptr_stack.push(con_ptr);
                }
		else if(token_vec[0] == "<"){
			Connector* con_ptr = new SingleInputRedirection;
			if(!base_ptr_stack.empty()){
				con_ptr->rhs = base_ptr_stack.top();
				base_ptr_stack.pop();
			}
			if(!base_ptr_stack.empty()){
				con_ptr->lhs = base_ptr_stack.top();
				base_ptr_stack.pop();
			}
			base_ptr_stack.push(con_ptr);
		}
                else if(token_vec[0] == ">"){
                        Connector* con_ptr = new SingleOutRedirection;
                        if(!base_ptr_stack.empty()){
                                con_ptr->rhs = base_ptr_stack.top();
                                base_ptr_stack.pop();
                        }
                        if(!base_ptr_stack.empty()){
                                con_ptr->lhs = base_ptr_stack.top();
                                base_ptr_stack.pop();
                        }
                        base_ptr_stack.push(con_ptr);
                }
                else if(token_vec[0] == ">>"){
                        Connector* con_ptr = new DoubleOutRedirection;
                        if(!base_ptr_stack.empty()){
                                con_ptr->rhs = base_ptr_stack.top();
                                base_ptr_stack.pop();
                        }
                        if(!base_ptr_stack.empty()){
                                con_ptr->lhs = base_ptr_stack.top();
                                base_ptr_stack.pop();
                        }
                        base_ptr_stack.push(con_ptr);
                }
                else if(token_vec[0] == "|"){
                        Connector* con_ptr = new Pipe;
                        if(!base_ptr_stack.empty()){
                                con_ptr->rhs = base_ptr_stack.top();
                                base_ptr_stack.pop();
                        }
                        if(!base_ptr_stack.empty()){
                                con_ptr->lhs = base_ptr_stack.top();
                                base_ptr_stack.pop();
                        }
                        base_ptr_stack.push(con_ptr);
                }
		else{
			Command* base_ptr = new Command;
			base_ptr->name = op;
			++it;
			while(it < token_vec.end()){
				op = *it;
				if(is_connector(op))
					break;
				else{
					base_ptr->add(op);
					++it;
				}
			}
			base_ptr_stack.push(base_ptr);
		}
        	
	}
	assert(base_ptr_stack.top() != NULL);		
	return base_ptr_stack.top();
}

void Parser::print_string_list() 
{
	for (auto & e : string_list)
		cout << e << endl;
}

bool Parser::is_connector(string& str)
{
	static const vector<string> connectors = {
		";","&&","||"
	};

	for (auto const & e : connectors)
	{
		if (str == e) {
			return true;
		}
	}

	return false;
}

Base * Parser::parse()
{
	remove_comment();
	if (test_mode) {
		cout << "act line is:" << line << endl;
	}
	paren();
	parseConnectors();
	postFixList();

/*	for(vector<vector<string>>::iterator it1 = token_list.begin(); it1 < token_list.end(); ++it1){
		vector<string> tokens = *it1;
		for(vector<string>::iterator it2 = tokens.begin(); it2 < tokens.end(); ++it2)
			cout << *it2 << endl;
	}
*/
	if (test_mode) {
		print_string_list();
	}

	Base* tree = build_tree();

	assert(tree != NULL);
	if (1) {
		tree->print();
		cout << endl;
	}
	
	return tree;
}


