#include <iostream>
using namespace std;

#include "AndConnector.h"

AndConnector::AndConnector()
{

}

AndConnector::~AndConnector()
{

}

int AndConnector::execute(int* fd, int connectorType, const char* name, int flag)
{
	int ret = lhs->execute(fd, connectorType, name, flag);
	if (ret == EXIT)
		return EXIT;
	else if (ret == FAIL)
		return FAIL;
	else
		return rhs->execute(fd, connectorType, name, flag);
}

void AndConnector::print()
{
	lhs->print();
	cout << " && ";
	rhs->print();
}

