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
		while( SDL_PollEvent( &event ) )
		{
			switch( event.type )
			{
				case SDL_QUIT: handleinput=false;
					break; //SDL_SCANCODE_LALT&
			
			}
		
			//SDL_BlitSurface(image, NULL, screen, NULL);
			// den veraenderten Bereich des display-surface auffrischen
			
		}
		SDL_Delay(10);
	}
}

long int sdl_master::id_slate_mouse(int x, int y)
{
	

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
	inputthread.join();
}

sdl_master::~sdl_master()
{
	cerr << "Destroy sdlmaster\n";
	cleanup();
	SDL_Quit();
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
		cerr << "Caught error:" << errorstring << " happened\n";
		return 1;
	}
	catch (...)
	{
		cerr << "An Error: happened\n";
		return 1;
	}
	return 0;
}
