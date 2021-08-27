#include <iostream>
using namespace std;

#include "OrConnector.h"


OrConnector::OrConnector()
{
}

OrConnector::~OrConnector()
{
}

int OrConnector::execute(int* fd, int connectorType, const char* name, int flag)
{
	int ret = lhs->execute(fd, connectorType, name, flag);
	if (ret == EXIT)
		return EXIT;
	else if (ret == SUCCESS)
		return SUCCESS;
	else
		return rhs->execute(fd, connectorType, name, flag);
}

void OrConnector::print()
{
	lhs->print();
	cout << " || ";
	rhs->print();
}

