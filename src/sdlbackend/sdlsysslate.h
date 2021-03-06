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

#ifndef _SDL_SYSSLATEO_H_
#define _SDL_SYSSLATEO_H_

#include "sysslateo.h"
class sysslateo;
#include "sdl_screenobject.h"
class sdl_screenobject;



#include "constdef.h"

using namespace std;

typedef struct sdlsysprivat_{
	~sdlsysprivat_()
	{
		SDL_FreeSurface(syssur);
		SDL_DestroyTexture (systex);
	}
	SDL_Surface *syssur=0;
	SDL_Texture *systex=0;
	SDL_Rect inner_object;
	
}sdlsys;

class sdl_sysslateo: public sysslateo 
{
public:
	sdl_sysslateo(slate *parent_slate, void *screenobject);
	~sdl_sysslateo();
	void draw();
	void cleanup_handler ();
	void draw_function ();
protected:

private:
	sdlsys widget;
	atomic<int> update_interval;
	SDL_Event event;
};

#endif // _SYSSLATEO_H_

