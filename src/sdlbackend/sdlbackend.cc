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
#include "configbackend.h"

#include <iostream>
#include <cstdlib>
#include <thread>
#include <system_error>

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


viewport *sdlmaster::create_viewport_intern(master *masteridd, int ownidd)
{
	return new sdlviewport(masteridd,ownidd);
}

sdlmaster::sdlmaster(){};

sdlmaster::init (int argc, char* argv[])
{
	SDL_init();
	for (int count=0; count<SDL_GetNumVideoDisplays(); count++) //SDL_GetNumVideoDisplays
		createviewport();
	inputhandler_function();
}

sdlmaster::~sdlmaster()
{
	cout << "Destroy sdlmaster\n";
	hasinputhandle=false;
	
	cleanup();
	SDL_Quit();
}

uint16_t handle_masterevent(void *event);
{
	int ishandled=0;
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
				if (((SDL_Event*)event)->key.keysym.sym==SDLK_c )
				{
					/**slatearea *temp=(slatearea *)viewport_pool[0]->get_slate_by_id(0)->get_selfreference_pointer ();
					assert(temp);
					slatearea *temp1=(slatearea *)viewport_pool[1]->get_slate_by_id(0)->get_selfreference_pointer ();
					slatearea *temp2=temp;
					temp=temp1;
					temp1=temp2;
					to_sdlslatearea(temp->get_screen())->slatebox.h-=4;
					ishandled=MASTER_HANDLED;*/
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
	sdlmaster t;
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
		return sdlmain(argc,argv);
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
	return 0;
}
