/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
 * Copyright (C) 2013 alex <devkral@web.de>
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

#ifndef _SDL_SCREENOBJECT_H_
#define _SDL_SCREENOBJECT_H_

#include "SDL2/SDL.h"
#include <iostream>
using namespace std;



typedef struct sdlmastercanvas_{
	~sdlmastercanvas_()
	{
		SDL_FreeSurface(masterscreen);
		SDL_DestroyWindow(window);
		delete dispbounds;
	}
	SDL_Window *window;
	SDL_Surface *masterscreen=0;
	int displayindex=0;
	SDL_Rect *dispbounds=0;
	
	
}sdlmastercanvas;

typedef struct sdlslatecanvas_{
	~sdlslatecanvas_()
	{
		SDL_FreeSurface(slatescreen);
		//SDL_FreeRect(slatebox);
		delete slatebox;
	}
	int x;
	int y;
	int w;
	int h;
	SDL_Surface *slatescreen=0;
	SDL_Rect *slatebox=0;

	//must not be freed done by master
	sdlmastercanvas *mastercanvas=0;
	
}sdlslatecanvas;

extern sdlmastercanvas *to_sdmac(void* in);
extern sdlslatecanvas *to_sdslc(void* in);


#endif // _TSCREENOBJECT_H_
