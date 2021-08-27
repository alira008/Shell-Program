#include <iostream>
using namespace std;

#include "SemicolonConnector.h"

SemicolonConnector::SemicolonConnector()
{
}


SemicolonConnector::~SemicolonConnector()
{
}

int SemicolonConnector::execute(int* fd, int connectorType, const char* name, int flag)
{
	int ret = lhs->execute(fd, connectorType, name, flag);
	if (ret == EXIT)
		return EXIT;
	else 
		return rhs->execute(fd, connectorType, name, flag);
}

void SemicolonConnector::print()
{
	lhs->print();
	cout << " ; ";
	rhs->print();
}

