#ifndef __OR__CONNECTOR_H__
#define __OR__CONNECTOR_H__

#include "Connector.h"
class OrConnector :
	public Connector
{
public:
	OrConnector();
	virtual ~OrConnector();

	virtual int execute(){}
	virtual void print();
	virtual int execute(int*, int, const char*, int);//{perror("error called execute in or connector");}
};

#endif

