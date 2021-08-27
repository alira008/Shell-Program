#ifndef __SEMICOLON_CONNECTOR_H__
#define __SEMICOLON_CONNECTOR_H__

#include "Connector.h"
class SemicolonConnector :
	public Connector
{
public:
	SemicolonConnector();
	virtual ~SemicolonConnector();

	virtual int execute(){}
	virtual void print();
        virtual int execute(int*, int, const char*, int);//{perror("error called execute in semicolon connector");}
};

#endif

