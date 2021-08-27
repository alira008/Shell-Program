#ifndef __BASE_H__
#define __BASE_H__

#define EXIT 0
#define SUCCESS 1
#define FAIL 2
#define test_mode 0

#include <string>
using namespace std;

class Base
{
public:
	Base();
	virtual ~Base();
	virtual int execute() = 0;
	virtual int execute(int*, int, const char*, int) = 0;
	virtual void print() = 0;
	virtual string get_name() = 0;
};


#endif

