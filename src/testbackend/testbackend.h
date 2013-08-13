// license: none


#ifndef _TESTBACKEND_H_
#define _TESTBACKEND_H_

#include "master.h"
class master;
#include "tviewport.h"
class tviewport;


class testmaster : public master
{
public:
	testmaster(int argc, char* argv[]);
	~testmaster();
	void inputhandler_function();
	int handle_masterevent(void *event);

private:
	viewport *create_viewport_intern(master *masteridd, int ownidd, void *t);
};

int testmain(int argc ,char *argv[]);

#endif // _TESTBACKEND_H_
