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
	while (handleinput)
	{
		SDL_WaitEvent(&event);
		do
		{
			switch( event.type )
			{
				case SDL_QUIT: handleinput=false;
					break; //SDL_SCANCODE_LALT&
				case SDL_KEYDOWN:
					if (event.key.keysym.sym==SDLK_a )
						viewport_pool[0]->addslice();
					if(event.key.keysym.sym==SDLK_b )
						viewport_pool[0]->removeslice();
					break;
				case SDL_KEYUP:
						//SDL_WarpMouseInWindow(to_sdmac (viewport_pool[0]->get_viewport_screen ())->window,10,10);
					break;
			}
		} while (SDL_PollEvent (&event));
		SDL_Delay(100);
	}
	render=false;
}



viewport *sdl_master::create_viewport_intern(master *masteridd, int ownidd)
{
	return new sdl_viewport(masteridd,ownidd);
}

sdl_master::sdl_master(int argc, char* argv[])
{
	for (int count=0; count<SDL_GetNumVideoDisplays(); count++) //SDL_GetNumVideoDisplays
		createviewport();
	start_handling_input();
	render=true;
	renderthread=thread(kickstarter_renderthread,this);
	inputthread.join();
}

sdl_master::~sdl_master()
{
	cout << "Destroy sdlmaster\n";
	render=false;
	cleanup();
	renderthread.join();
	SDL_Quit();
}
void kickstarter_renderthread(sdl_master *parent_object)
{
	parent_object->renderthread_function();

}

void sdl_master::renderthread_function()
{
	while (render==true)
	{
		
		SDL_Delay(10);
	}
}

int sdlmain(int argc, char *argv[])
{
	try
	{
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
		    throw ("Error: could not initialize SDL");
		}
		
		sdl_master(argc,argv);
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
