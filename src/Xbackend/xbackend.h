

#ifndef _XBACKEND_H_
#define _XBACKEND_H_

#include <xcb/xcb.h>

#include "master.h"
class master;
#include "xviewport.h"
class xviewport;


class xmaster : public master
{
public:
	xmaster(int argc, char* argv[]);
	~xmaster();
	void inputhandler_function();
	int handle_masterevent(void *event);

	xcb_connection_t *con;
	xcb_connection_t *display;
	int handle_event(void *event);
	
private:
	viewport *create_viewport_intern(master *masteridd, int ownidd, void *monitor);
	
	int numbermonitors=0;
	bool inputhandling = true;
	
};

 int xmain(int argc ,char *argv[]);


#endif // _XBACKEND_H_
