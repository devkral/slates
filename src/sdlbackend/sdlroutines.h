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


#ifndef _SDLROUTINES_H_
#define _SDLROUTINES_H_

#ifdef COMPILED_WITH_X
#include <xcb/xcb.h>
#endif


#include <SDL.h>
#include <SDL2/SDL_syswm.h> //not included in SDL.h
#include <SDL2/SDL_image.h>
#include <string>
#include <cstdlib>

//#include "configbackend.h"

using namespace std;


#ifdef COMPILED_WITH_X
	static xcb_connection_t *X_con=0;
	//static X_ext_data=0;
	
#endif

void MoveWindowToScreen (SDL_SysWMinfo *wininf, int32_t screen);




void SDL_CreateWindowAndRendererSync (SDL_Window** win, SDL_Renderer** rend, SDL_Rect *windowbounds);
void SDL_CreateRendererSync (SDL_Window* win, SDL_Renderer** rend);

void SDL_DestroyWindowAndRenderer (SDL_Window* win, SDL_Renderer* rend);
bool hw_accel();


#endif //_SDLROUTINES_H_
