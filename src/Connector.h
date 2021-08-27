#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "Base.h"
#include "Command.h"
using namespace std;
class Connector :
	public Base
{
public:
	Base * lhs;
	Base*  rhs;
	Connector() {

	}
	virtual ~Connector();

	virtual int execute() = 0;
	virtual void print() = 0;
	virtual int execute(int*, int, const char*, int) = 0;
	virtual string get_name(){};
};

#endif

