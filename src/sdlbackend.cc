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

#ifdef COMPILED_WITH_SDL
#include "sdlbackend.h"
#include <iostream>
//#include <cstdlib>
#include <unistd.h>
#include <SDL/SDL.h>
using namespace std;

int sdlmain(int argc, char *argv[])
{
	SDL_Surface *screen;
    SDL_Event event;
	int done = 0;
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE | SDL_INIT_EVENTTHREAD) == -1) {
        printf("Can't init SDL:  %s\n", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);
    screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL) {
        printf("Can't set video mode: %s\n", SDL_GetError());
        return 1;
    }   

while (!done)
{
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				done = 1;
				break;
		}
	}
	usleep(100);
		 
}
    return 0;


}
#endif //COMPILED_WITH_SDL