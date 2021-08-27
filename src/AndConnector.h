#ifndef __AND_CONNECTOR_H__
#define __AND_CONNECTOR_H__
#include "Connector.h"
class AndConnector :
	public Connector
{
public:
	AndConnector();
	virtual ~AndConnector();

	virtual int execute( ){}
	virtual void print();
	virtual int execute(int*, int, const char*, int);//perror("error called execute in and connector");}
};

#endif

