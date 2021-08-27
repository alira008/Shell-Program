#ifndef __DOUBLEOUTPUTREDIRECTION_H__
#define __DOUBLEOUTPUTREDIRECTION_H__

#include "Connector.h"
#include "RShell.h"

class DoubleOutRedirection : public Connector{
	private:
		RShell* left;
		RShell* right;
	public:
		DoubleOutRedirection(){}
		DoubleOutRedirection(RShell* l):left(l){}
		DoubleOutRedirection(RShell* l, RShell* r):left(l), right(r){}
		virtual ~DoubleOutRedirection(){}
		
		virtual int execute(){}
		virtual void print();
       		virtual int execute(int*, int, const char*, int);//{perror("error called execute in double out connector");}
};

#endif
