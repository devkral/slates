

#include "xbackend.h"

#include <iostream>
#include <unistd.h>
#include <system_error>
#include <cstring>
#include <csignal>
#include <getopt.h>
using namespace std;



viewport *xmaster::create_viewport_intern(master *masteridd, int16_t ownidd, void *monitor)
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
	signal (SIGINT,signalcleanup);
    /* Verbindung zum X-Server öffnen */
	//http://xcb.freedesktop.org/manual/group__XCB__RandR__API.html
	//http://xcb.freedesktop.org/PublicApi/#index2h2
	int ch=0;
	// options descriptor

	con = xcb_connect(getenv("DISPLAY"), &numbermonitors);
	if(con == 0) {
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
	
}

xmaster::~xmaster()
{
	cerr << "cleaned up\n";
	cleanup();
	free(closereply);
	xcb_disconnect(con);
}

bool xmaster::is_system_mode()
{
	return true;
}

int16_t xmaster::get_focused_viewport_id()
{
	return 0;
}

void xmaster::inputhandler_function()
{
	
	xcb_generic_event_t *event=0;
	int16_t status=0;
	bool inputhandling=true;
	while (inputhandling)
	{
		event = xcb_wait_for_event(con);
		if (event!=0)
		{
			handle_event (event);
		}
		else
		{
			inputhandling=false;
		}
		free(event);
	}
}


uint16_t xmaster::handle_masterevent(void *event)
{
	xcb_button_press_event_t *bp;
	
	switch (((xcb_generic_event_t *)event)->response_type & ~0x80)
	{
		case XCB_KEY_PRESS:
			//inputhandling = false;
			break;
		case XCB_KEY_RELEASE: {
                        xcb_key_release_event_t *kr = (xcb_key_release_event_t *)event;

                        switch (kr->detail) {
                            case 9: //ESC
                                return QUIT_DE;
								break;
							case 38: 

								break;
							case 41: 
				{
					int width=(viewport_pool[get_focused_viewport_id()]->get_viewport_width())-1;
					int height=(viewport_pool[get_focused_viewport_id()]->get_viewport_height())-1;
					viewport_pool[get_focused_viewport_id()]->set_viewport_size(width, height);
					return EVENT_HANDLED_INTERN;
				}
								break;
							case 25:
				{
					viewport_pool[get_focused_viewport_id()]->addslice();
					return EVENT_HANDLED_INTERN;
				}
								break;
							case 39:
				{
					viewport_pool[get_focused_viewport_id()]->removeslice();
					return EVENT_HANDLED_INTERN;
				}
								break;
                        }
                    }
		break;
		case XCB_EXPOSE:
			return EXP_ACTIVE_SLATES;
			break;
		case XCB_BUTTON_PRESS: 
			bp= (xcb_button_press_event_t *)event;
				//cout << bp->detail;
			
			if (is_system_mode())
		{
				switch (bp->detail)
				{
						case 4: 
				{
					int16_t width=(viewport_pool[get_focused_viewport_id()]->get_viewport_width())+1;
					int16_t height=(viewport_pool[get_focused_viewport_id()]->get_viewport_height())+1;
					viewport_pool[get_focused_viewport_id()]->set_viewport_size(width, height);
					return EVENT_HANDLED_INTERN;
				}
						break;
						case 5:
				{
					int16_t width=(viewport_pool[get_focused_viewport_id()]->get_viewport_width())-1;
					int16_t height=(viewport_pool[get_focused_viewport_id()]->get_viewport_height())-1;
					viewport_pool[get_focused_viewport_id()]->set_viewport_size(width, height);
					return EVENT_HANDLED_INTERN;
				}
						break;

				}
		}

				break;
			case XCB_CLIENT_MESSAGE:
				if((*(xcb_client_message_event_t*)event).data.data32[0] == (*closereply).atom)
				{
					return QUIT_DE;
				}
				break;
		 }
	return EXP_ALL_VIEW;
}

int xmain(int argc ,char *argv[])
{

	xmaster *t=new xmaster();
	int return_var=0;
	try
	{
		t->init(argc,argv);
	}
	catch (cleanup_exception *exc)
	{
		return_var=0;
	}
	catch (restart_exception *exc)
	{
		delete t;
		return_var=xmain(argc,argv);
	}	
	catch (const std::system_error& error)
	{
		cerr << "Caught error: " << error.what() << endl;
		return_var=1;
	}	
	catch (char  *errorstring)
	{
		cerr << "Caught error string:" << errorstring << " happened\n";
		return_var=1;
	}
	catch (...)
	{
		cerr << "An Error: happened\n";
		return_var=1;
	}
	
	return return_var;
}