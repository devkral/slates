
//contains code from https://gitorious.org/qt-window-manager/qt-window-manager/blobs/master/main.cpp



#include "xbackend.h"

#include <iostream>
#include <unistd.h>
#include <system_error>
#include <cstring>
#include <csignal>
#include <getopt.h>
using namespace std;



viewport *xmaster::create_viewport_intern(master *masteridd, int32_t ownidd, void *monitor)
{
	return new xviewport(masteridd,ownidd, (xcb_screen_t *) monitor);
	//xcb_setup_roots_iterator( xcb_get_setup(c) ).data );
}


void signalcleanup(int )
{
	throw (new cleanup_exception);
}

xmaster::xmaster(){};


void xmaster::init(int argc, char* argv[])
{
	char *display=(char *)":0"; //display adress
	signal (SIGINT,signalcleanup);
    /* Verbindung zum X-Server öffnen */
	//http://xcb.freedesktop.org/manual/group__XCB__RandR__API.html
	//http://xcb.freedesktop.org/PublicApi/#index2h2
	int ch=0;
	// options descriptor
	struct option optionsx[] = {
        { "display", required_argument, &ch, 1 },
		{ "backend", required_argument, 0, 0 }, //cleans up backend
		{0, 0, 0, 0}};
	int index=1;
	while (getopt_long(argc, argv, "", optionsx, &index) != -1)
	{
		switch(ch)
		{
			case 1: display=optarg;
			break;
		}
	}
	if((con = xcb_connect(display, &numbermonitors)) == 0) {
		printf("Cannot get a connection\n");
		exit(1);
	}
	//delete window code
	closecookie = xcb_intern_atom(con, 0, 16, "WM_DELETE_WINDOW");
	closereply = xcb_intern_atom_reply(con, closecookie, 0);

	
	xcb_screen_iterator_t iter = xcb_setup_roots_iterator( xcb_get_setup(con) );
	if (numbermonitors==0) //if running a wm
		numbermonitors=1;   //for test purposes

	for (int16_t i = 0; i < numbermonitors; ++i) {
		createviewport(iter.data);
		xcb_screen_next (&iter);
    }
	inputhandler_function ();
	//inputthread.join();
	
}

xmaster::~xmaster()
{
	cerr << "cleaned up\n";
	cleanup();
	free(closereply);
	xcb_disconnect(con);
}

int32_t xmaster::get_focused_viewport()
{
	return 0;
}


void xmaster::inputhandler_function()
{
	
	xcb_generic_event_t *event=0;
	int16_t status=0;
	while (inputhandling)
	{
		event = xcb_wait_for_event(con);
		if (event!=0)
		{
			status=handle_event( (void *)event);
			free(event);
		}
		else
		{
			inputhandling=false;
		}
	}
}

uint16_t xmaster::handle_masterevent(void *event)
{
	xcb_button_press_event_t *bp;
	
	switch (((xcb_generic_event_t *)event)->response_type & ~0x80)
	{
		case XCB_KEY_PRESS:  /* beenden, wenn eine Taste gedrückt wird */
			/**where are the keysequences declared*/
			//inputhandling = false;
			return QUIT_DE;
			break;
		case XCB_EXPOSE:
			xcb_flush (con);
			return EVENT_HANDLED_INTERN;
			break;
		case XCB_BUTTON_PRESS:  /* beenden, wenn eine Taste gedrückt wird */
				bp= (xcb_button_press_event_t *)event;

				
                if (bp->detail==4 && 1) /**where are the keysequences declared for detail*/
				{
					int16_t width=(viewport_pool[0]->get_viewport_width())+1;
					int16_t height=(viewport_pool[0]->get_viewport_height())+1;
					viewport_pool[0]->set_viewport_size(width, height);
					return EVENT_HANDLED_INTERN;
				}
                else if (bp->detail==5) /**where are the keysequences declared for detail*/
				{
					int width=(viewport_pool[0]->get_viewport_width())-1;
					int height=(viewport_pool[0]->get_viewport_height())-1;
					viewport_pool[0]->set_viewport_size(width, height);
					return EVENT_HANDLED_INTERN;
				}
				break;
			case XCB_CLIENT_MESSAGE:
				if((*(xcb_client_message_event_t*)event).data.data32[0] == (*closereply).atom)
				{
					inputhandling = false;
					return QUIT_DE;
				}
				break;
		 }
	return EXP_ALL_VIEW;
}


int xmain(int argc ,char *argv[])
{
	xmaster t;
	try
	{
		t.init(argc,argv);
	}
	catch (cleanup_exception *exc)
	{
		return 0;
	}
	catch (restart_exception *exc)
	{
		return xmain(argc,argv);
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