#ifndef __SINGLEOUTPUTREDIRECTION_H__
#define __SINGLEOUTPUTREDIRECTION_H__

#include "Connector.h"
#include "RShell.h"

class SingleOutRedirection : public Connector{
	private:
		RShell* left;
		RShell* right;
	public:
		SingleOutRedirection(){}
		SingleOutRedirection(RShell* l):left(l){}
		SingleOutRedirection(RShell* l, RShell* r):left(l), right(r){}
		virtual ~SingleOutRedirection(){}
		
		virtual int execute(){}
		virtual void print();
	        virtual int execute(int*, int , const char*, int);//{perror("error called execute in single out connector");}
};

#endif
