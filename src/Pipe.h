#ifndef __PIPE_H__
#define __PIPE_H__

#include "Connector.h"

class Pipe : public Connector{

	public:
		Pipe(){}
		virtual ~Pipe(){}
		
		virtual int execute(){}
		virtual void print();
	        virtual int execute(int*, int, const char*, int);//{}
};

#endif
