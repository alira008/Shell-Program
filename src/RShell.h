#ifndef __RSHELL_H__
#define __RSHELL_H__
class RShell
{
public:
	RShell();
	virtual ~RShell();

	bool exit_flag = false;
	void run();

	void print_prompt();
};

#endif // RShell

