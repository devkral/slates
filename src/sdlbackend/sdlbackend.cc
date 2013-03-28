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


#include <iostream>
#include <cstdlib>
#include <thread>
#include <system_error>

using namespace std;

void sdl_master::inputhandler_function()
{
	SDL_Event event;
	while (hasinputhandle)
	{
		SDL_WaitEvent(&event);
		do
		{
			switch( event.type )
			{
				case SDL_QUIT: hasinputhandle=false;
					break;
				case SDL_MOUSEMOTION:{
					slate* temp=((sdl_viewport*)viewport_pool[0])->get_slate_mouse(event.motion.x,event.motion.y);
					if (temp!=0)
						temp->handle_input(&event);
					break;}
				default:{
					handle_masterevent(&event);
					break;}
			}
		} while (SDL_PollEvent (&event));
		//SDL_Delay(100);
	}
}


viewport *sdl_master::create_viewport_intern(master *masteridd, int ownidd)
{
	return new sdl_viewport(masteridd,ownidd);
}

sdl_master::sdl_master(int argc, char* argv[]) : master()
{
	for (int count=0; count<SDL_GetNumVideoDisplays(); count++) //SDL_GetNumVideoDisplays
		createviewport();
	start_handling_input();
	inputthread.join();
}

sdl_master::~sdl_master()
{
	//~master();
	cout << "Destroy sdlmaster\n";
	SDL_Quit();
}

int sdl_master::handle_masterevent(void *event)
{
	int ishandled=MASTER_UNHANDLED;
	if(protectmaster_eventhandle.try_lock_for(defaulttimeout))
	{
		switch (((SDL_Event*)event)->type)
		{
			case SDL_QUIT: hasinputhandle=false;
				ishandled=MASTER_QUIT;
				break;

			case SDL_KEYDOWN:
				if (((SDL_Event*)event)->key.keysym.sym==SDLK_a )
				{
					viewport_pool[0]->addslice();
					ishandled=MASTER_HANDLED;
				}
				if (((SDL_Event*)event)->key.keysym.sym==SDLK_b )
				{
					if (viewport_pool[0]->removeslice()==SL_destroy_failed)
						cerr << "Destroy failed\n";
					ishandled=MASTER_HANDLED;
				}
				if (((SDL_Event*)event)->key.keysym.sym==SDLK_r )
				{
					viewport_pool[0]->update_slice_info();
					viewport_pool[0]->async_update_slates();
					ishandled=MASTER_HANDLED;
				}
				if ((SDL_GetModState()&KMOD_CTRL) && (SDL_GetModState()&KMOD_ALT) && (SDL_GetModState()&KMOD_SHIFT))
				{
					viewport_pool[0]->set_viewport_size(viewport_pool[0]->get_viewport_height(), viewport_pool[0]->get_viewport_width());
				}		

				
				if (((SDL_Event*)event)->key.keysym.sym==SDLK_ESCAPE )
				{
					hasinputhandle=false;
					ishandled=MASTER_QUIT;
				}

				break;
			case SDL_MOUSEWHEEL:
				{
					if ((SDL_GetModState()&KMOD_CTRL) && (SDL_GetModState()&KMOD_ALT))
					{
						int width=(viewport_pool[0]->get_viewport_width())-((SDL_Event*)event)->wheel.x;
						int height=(viewport_pool[0]->get_viewport_height())-((SDL_Event*)event)->wheel.y;
						viewport_pool[0]->set_viewport_size(width, height);
						ishandled=MASTER_HANDLED;
					}
				
					break;
				}
	
		}
		protectmaster_eventhandle.unlock();
	}
	else
		ishandled=MASTER_TIMEDOUT;
	return ishandled;
}

//#define NONCATCHSDL 1

int sdlmain(int argc, char *argv[])
{
#ifndef NONCATCHSDL
	try
	{
#endif
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
		    throw ("Error: could not initialize SDL");
		}
		
		sdl_master(argc,argv);
#ifndef NONCATCHSDL
	}
	catch (const std::system_error& error)
	{
		cerr << "Caught error: " << error.what() << endl;
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
#endif	
	return 0;
}
