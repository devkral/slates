
//contains code from https://gitorious.org/qt-window-manager/qt-window-manager/blobs/master/main.cpp



#include "xbackend.h"

#include <iostream>
#include <unistd.h>
#include <system_error>
#include <cstring>
#include <csignal>
using namespace std;



viewport *xmaster::create_viewport_intern(master *masteridd, int ownidd, void *monitor)
{
	return new xviewport(masteridd,ownidd, (xcb_screen_t *) monitor);
	//xcb_setup_roots_iterator( xcb_get_setup(c) ).data );
}


void signalcleanup(int )
{
	exit(1);
}

xmaster::xmaster(int argc, char* argv[])
{
	
	signal (SIGINT,signalcleanup);
    /* Verbindung zum X-Server öffnen */
	//http://xcb.freedesktop.org/manual/group__XCB__RandR__API.html
	//http://xcb.freedesktop.org/PublicApi/#index2h2

	/**if ((display = XOpenDisplay(0)) == NULL)
	{
		std::cerr << "Cannot open display\n"; 
		exit(1);
	}*/
	if((con = xcb_connect(0, &numbermonitors)) == 0) {
		printf("Cannot get a connection\n");
		exit(1);
	}
	
	xcb_screen_iterator_t iter = xcb_setup_roots_iterator( xcb_get_setup(con) );
	if (numbermonitors==0) //if running a wm
		numbermonitors=1;   //for test purposes

	for (int i = 0; i < numbermonitors; ++i) {
		createviewport(iter.data);
		xcb_screen_next (&iter);
    }
	inputhandler_function ();
	//inputthread.join();
	
}

xmaster::~xmaster()
{
	cleanup();
	xcb_disconnect(con);
}
void xmaster::inputhandler_function()
{
	
	xcb_generic_event_t *event=0;
	while (inputhandling)
	{
		event = xcb_wait_for_event(con);
		handle_event( (void *)event);
		free(event);
	}
}

int xmaster::handle_masterevent(void *event)
{
		switch (((xcb_generic_event_t *)event)->response_type & ~0x80)
		{
			case XCB_EXPOSE:    /* draw or redraw the window */
				return MASTER_UNHANDLED;
				//xcb_poly_fill_rectangle(con, window, g,  1, &r);
				//xcb_flush(con);	/* show window */
	//xcb_window_t find out how to manipulate
	//xcb_map_window(((xmaster*)get_master ())->con, ((xhelperclass *)renderob)->window);

	/* force */
	//xcb_flush(((xmaster*)get_master ())->con);
	//sleep(4);
				break;
			case XCB_KEY_PRESS:  /* beenden, wenn eine Taste gedrückt wird */
				inputhandling = false;
				return MASTER_QUIT;
				break;
		 }

	return MASTER_UNHANDLED;
}

int xmaster::handle_event(void *event)
{
	int status=handle_masterevent(event);
	if (status==MASTER_UNHANDLED)
	{
		for (long int count=0; count<amount_viewports(); count++)
		{
			viewport_pool[count]->handle_event(event);
		}
	}
	return status;
}

int xmain(int argc ,char *argv[])
{
	try
	{
		xmaster(argc,argv);
	}
	catch (const std::system_error& error)
	{
		cerr << "Caught error: " << error.what() << endl;
		return 1;
	}	
	catch (char  *errorstring)
	{
		cerr << "Caught error string:" << errorstring << " happened\n";
		return 1;
	}
	catch (...)
	{
		cerr << "An Error: happened\n";
		return 1;
	}

	return 0;
}