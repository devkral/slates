/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
 * Copyright (C) 2012 alex <devkral@web.de>
 * 
 * slates is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * slates is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "config.h"
#endif //_CONFIG_H_


#include "sdlbackend.h"
//#include "configbackend.h"

#include <iostream>
#include <cstdlib>
#include <csignal>
#include <thread>
#include <system_error>


#ifdef COMPILED_WITH_X
//xcb_randr_id works somehow just in C
//Workaround
#include <xcb/xcbext.h>
xcb_extension_t  xcb_randr_id_ = { (char *)"RANDR", 0 };;

#endif

using namespace std;

void sdlmaster::inputhandler_function()
{
	SDL_Event event;
	while (1)
	{
		SDL_WaitEvent(&event);
		do
		{
			handle_event ((void *)&event);
		} while (SDL_PollEvent (&event));
		//SDL_Delay(100);
	}
}

viewport *sdlmaster::create_viewport_intern(master *masteridd, int16_t ownidd, void *monitor)
{
	return new sdlviewport(masteridd,ownidd,monitor);
}

sdlmaster::sdlmaster(){};

void signalcleanup2(int )
{
	throw (new cleanup_exception);
}

void sdlmaster::init (int argc, char* argv[])
{
	signal (SIGINT,signalcleanup2);
	int cindex=1;
	string testoptions;
	while (cindex<argc-1) //-1 because cindex must be followed by argument
	{
		if (strcmp(argv[cindex],"--backend")==0)
		{
			if (argv[cindex+1]!=NULL)
			{
				testoptions=argv[cindex+1];
				break;
			}
		}
		cindex++;
	}
	testoptions="X";
#ifdef  COMPILED_WITH_X
	cout << "X\n";
	if (testoptions=="X") 
		x_init(argc,argv);
	else
#endif
#if COMPILED_WITH_WAYLAND
		if (testoptions=="wayland")
		wayland_init(argc,argv);
	else
#endif
		simple_init(argc,argv);
	
}

void sdlmaster::simple_init(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	for (int count=0; count<SDL_GetNumVideoDisplays(); count++) //SDL_GetNumVideoDisplays
	{
		createviewport();
	}
	inputhandler_function();
}

#ifdef COMPILED_WITH_X



void sdlmaster::x_init(int argc, char *argv[])
{
	int numbermonitors=0;
	const xcb_query_extension_reply_t *qer;
	/** connect */
	X_con = xcb_connect(getenv("DISPLAY"), &numbermonitors);
	if(X_con == 0)
	{
		cerr << "Cannot get a connection\n";
		exit(1);
	}

	
	xcb_prefetch_extension_data(X_con, &xcb_randr_id_);
	//int xfd = xcb_get_file_descriptor(X_con);
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	xcb_screen_iterator_t iter = xcb_setup_roots_iterator( xcb_get_setup(X_con) );
	if (numbermonitors==0) //if running a wm
		numbermonitors=1;   //for test purposes

	for (int16_t i = 0; i < numbermonitors; ++i) {
		createviewport(iter.data);
		xcb_screen_next (&iter);
    }
	inputhandler_function();
}
#endif

#ifdef  COMPILED_WITH_WAYLAND
void sdlmaster::wayland_init(int argc, char *argv[])
{

}
#endif


sdlmaster::~sdlmaster()
{
	cout << "Destroy sdlmaster\n";	
#ifdef COMPILED_WITH_X
	if (X_con)
		xcb_disconnect(X_con);
	
#endif

	
	cleanup();
	SDL_Quit();
}
bool sdlmaster::is_system_mode()
{
	if (get_focused_viewport ()->get_focused_slate_id()<=get_focused_viewport ()->get_last_slate_id() &&((sdlslatearea*)get_focused_viewport ()->get_focused_slate()->get_slatearea())->isfocused)
		return false;
	else
		return true;
}

int16_t sdlmaster::get_focused_viewport_id ()
{
	return 0;
}

uint16_t sdlmaster::handle_masterevent(void *event)
{
	uint16_t return_val;
	if (SDL_GetModState ()&KMOD_CTRL && SDL_GetModState ()&(KMOD_ALT|KMOD_SHIFT))
	{
		return_val=EXP_ALL_VIEW;
	}else
	{
		return_val=EXP_FOCUS_SLATE;
	}
	
	switch (((SDL_Event*)event)->type)
	{
		case SDL_QUIT: 
			return_val=QUIT_DE;
			break;
		case SDL_WINDOWEVENT: 
			((sdlviewport*)get_focused_viewport ())->draw_viewwindow();
			return_val=EXP_ACTIVE_SLATES;
			break;
		case SDL_MOUSEBUTTONDOWN:
			//return_val=EXP_FOCUS_SLATE;
			break;
		case SDL_MOUSEBUTTONUP:
			//return_val=EXP_FOCUS_SLATE;
			break;
		case SDL_MOUSEMOTION:
			//return_val=EXP_FOCUS_SLATE;
			break;
		case SDL_KEYDOWN:
			{
				if (((SDL_Event*)event)->key.keysym.sym==SDLK_a && is_system_mode())
				{
						return_val=ADD_SLICE;
				}
				if (((SDL_Event*)event)->key.keysym.sym==SDLK_b && is_system_mode())
				{
					return_val=REMOVE_SLICE;
				}
				if (((SDL_Event*)event)->key.keysym.sym==SDLK_r && SDL_GetModState ()&KMOD_CTRL &&
				    SDL_GetModState ()&KMOD_SHIFT    && is_system_mode())
				{
					return_val=RELOAD_DE;
				}else if (((SDL_Event*)event)->key.keysym.sym==SDLK_r &&
				    SDL_GetModState ()&KMOD_CTRL  && is_system_mode())
				{
					get_focused_viewport()->update_slice_info();
				}

				if (((SDL_Event*)event)->key.keysym.sym==SDLK_q && SDL_GetModState ()&KMOD_CTRL && SDL_GetModState ()&KMOD_SHIFT)
				{
					return_val=QUIT_DE;
				}
			}
			break;
		case SDL_MOUSEWHEEL:
			{
				
				if ((SDL_GetModState()&KMOD_CTRL) && (SDL_GetModState()&KMOD_SHIFT))
				{
					int width=(viewport_pool[0]->get_viewport_width())-((SDL_Event*)event)->wheel.y;
					int height=(viewport_pool[0]->get_viewport_height())-((SDL_Event*)event)->wheel.x;
					get_focused_viewport()->set_viewport_size(width, height);
					return_val=EVENT_HANDLED_INTERN;
				}else if ((SDL_GetModState()&KMOD_CTRL)) // && (SDL_GetModState()&KMOD_ALT))
				{
					int width=(viewport_pool[0]->get_viewport_width())-((SDL_Event*)event)->wheel.x;
					int height=(viewport_pool[0]->get_viewport_height())-((SDL_Event*)event)->wheel.y;
					get_focused_viewport()->set_viewport_size(width, height);
					return_val=EVENT_HANDLED_INTERN;
				}
			}
			break;
	
		}
	
	return return_val;
}

//#define NONCATCHSDL 1

int sdlmain(int argc, char *argv[])
{
	sdlmaster *t=new sdlmaster();
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
		return_var=sdlmain(argc,argv);
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
