#ifndef __SINGLEINPUTREDIRECTION_H__
#define __SINGLEINPUTREDIRECTION_H__

#include "Connector.h"
#include "RShell.h"
class SingleInputRedirection : public Connector{
	private:
		RShell* left;
		RShell* right;
	public:
		SingleInputRedirection(){}
		SingleInputRedirection(RShell* l):left(l){}
		SingleInputRedirection(RShell* l, RShell* r):left(l), right(r){}
		virtual ~SingleInputRedirection(){}
		
		virtual int execute(){}
		virtual void print();
       		virtual int execute(int* fd, int connectorType, const char* fileName, int flag);//{return lhs->execute(fds, connectorType, fileName, flag);}
};

#endif
