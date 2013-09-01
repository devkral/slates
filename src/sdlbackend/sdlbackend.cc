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

viewport *sdlmaster::create_viewport_intern(master *masteridd, int ownidd, void *monitor)
{
	return new sdlviewport(masteridd,ownidd);
}

sdlmaster::sdlmaster(){};

void sdlmaster::init (int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	for (int count=0; count<SDL_GetNumVideoDisplays(); count++) //SDL_GetNumVideoDisplays
		createviewport();
	inputhandler_function();
}

sdlmaster::~sdlmaster()
{
	cout << "Destroy sdlmaster\n";	
	cleanup();
	SDL_Quit();
}


int32_t sdlmaster::get_focused_viewport ()
{
	return 0;
}

uint16_t sdlmaster::handle_masterevent(void *event)
{
	uint16_t return_val=EXP_FOCUS_SLATE;
	switch (((SDL_Event*)event)->type)
	{
		case SDL_QUIT: 
			return_val=QUIT_DE;
				break;

		case SDL_KEYDOWN:
				if (((SDL_Event*)event)->key.keysym.sym==SDLK_a )
				{
					viewport_pool[get_focused_viewport()]->addslice();
					return_val=EVENT_HANDLED_INTERN;
				}
				if (((SDL_Event*)event)->key.keysym.sym==SDLK_b )
				{
					if (viewport_pool[get_focused_viewport()]->removeslice()==SL_DESTROY_FAILED)
						cerr << "Destroy failed\n";
					return_val=EVENT_HANDLED_INTERN;
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
					//viewport_pool[get_focused_viewport()]->update_slice_info();
					//flush
					return_val=EXP_ACTIVE_SLATES;
				}
				if ((SDL_GetModState()&KMOD_CTRL) && (SDL_GetModState()&KMOD_ALT) && (SDL_GetModState()&KMOD_SHIFT))
				{
					viewport_pool[0]->set_viewport_size(viewport_pool[0]->get_viewport_height(), viewport_pool[0]->get_viewport_width());
				}		

				
				if (((SDL_Event*)event)->key.keysym.sym==SDLK_ESCAPE )
				{
					return_val=QUIT_DE;
				}

				break;
			case SDL_MOUSEWHEEL:
				{
					if ((SDL_GetModState()&KMOD_CTRL) && (SDL_GetModState()&KMOD_ALT))
					{
						int width=(viewport_pool[0]->get_viewport_width())-((SDL_Event*)event)->wheel.x;
						int height=(viewport_pool[0]->get_viewport_height())-((SDL_Event*)event)->wheel.y;
						viewport_pool[0]->set_viewport_size(width, height);
						return_val=EVENT_HANDLED_INTERN;
					}
				
					break;
				}
	
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
