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

#ifndef _SDLSLATEOTYPES_H_
#define _SDLSLATEOTYPES_H_


#include "constdef.h"

#include <SDL2/SDL.h>
#include <mutex>

using namespace std;

class sdlemptyprivat
{
public:
	//sdlemptyprivat();
	~sdlemptyprivat();


	SDL_Surface *emptysur=0;
	
	Uint32 white=0;
	Uint32 black=0;
	void init_colors(SDL_Surface *in);
	mutex lockonwriteread;
	void set_emptysur(SDL_Surface *in, SDL_Renderer *renderer);
	//void set_emptytex(SDL_Surface *in);
	//SDL_Surface *get_emptysur();
	SDL_Texture *get_emptytex();
private:
	bool iseverset=false;
};
//extern sdlemptyprivat sdlemptyoo;
#endif // _SDLSLATEOTYPES_H_

