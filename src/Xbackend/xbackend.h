

#ifndef _XBACKEND_H_
#define _XBACKEND_H_

#include "xroutines.h"

#include "master.h"
class master;
#include "xviewport.h"
class xviewport;


class xmaster : public master
{
public:
	xmaster();
	~xmaster();
	void init(int argc, char* argv[]);
	void inputhandler_function();
	int32_t get_focused_viewport_id();
	uint16_t handle_masterevent(void *event);
	bool is_system_mode();
	xcb_connection_t *con;
	xcb_connection_t *display;
	//uint16_t handle_event(void *event);
	
private:
	viewport *create_viewport_intern(master *masteridd, int32_t ownidd, void *monitor);
	xcb_intern_atom_cookie_t closecookie;
	xcb_intern_atom_reply_t* closereply;
	int32_t numbermonitors=0;
	bool inputhandling = true;
	
	int32_t focused_viewport=0;
	
};

 int xmain(int argc ,char *argv[]);


#endif // _XBACKEND_H_
