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
	testmaster();
	~testmaster();
	
	void init (int argc, char* argv[]);
	void inputhandler_function();
	uint16_t handle_masterevent(void *event);
	int32_t get_focused_viewport_id();
	bool is_system_mode();

private:
	viewport *create_viewport_intern(master *masteridd, int32_t ownidd, void *t);
};

int testmain(int argc ,char *argv[]);

#endif // _TESTBACKEND_H_
