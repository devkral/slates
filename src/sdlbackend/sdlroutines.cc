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


#include "sdlroutines.h"
#include <iostream>
#include <mutex>

static mutex rendsync;
void SDL_CreateWindowAndRendererSync (SDL_Window** win, SDL_Renderer** rend, SDL_Rect *windowbounds)
{
	rendsync.lock();
	*win=SDL_CreateWindow("Slates", windowbounds->x, windowbounds->y,
	           windowbounds->w, windowbounds->h,SDL_WINDOW_BORDERLESS);//SDL_WINDOW_BORDERLESS
	if (hw_accel())
		*rend=SDL_CreateRenderer (*win,-1,SDL_RENDERER_ACCELERATED);
	else
		*rend=SDL_CreateRenderer (*win,-1,SDL_RENDERER_SOFTWARE);
	rendsync.unlock();
}

static mutex destroysync;
void SDL_DestroyWindowAndRendererSync (SDL_Window* win, SDL_Renderer* rend)
{
	destroysync.lock();
	SDL_DestroyRenderer (rend);
	SDL_DestroyWindow (win);
	destroysync.unlock();
}
bool hw_accel()
{
	return false;
}