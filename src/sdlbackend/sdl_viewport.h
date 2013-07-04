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

#ifndef _SDL_VIEWPORT_H_
#define _SDL_VIEWPORT_H_
#include "viewport.h"
class viewport;

#include "sdl_slatearea.h"
class sdl_slatearea;

#include "sdl_screenobject.h"
class sdl_screenobject;


#include "constdef.h"





using namespace std;


class sdl_viewport : public viewport
{
public:
	sdl_viewport(master *masteridd, int ownidd);
	~sdl_viewport();
	long int id_slate_mouse(int x, int y);
	slate *get_slate_mouse(int x, int y);
	void *get_viewportscreen();
	void update_slice_info();
	void render();
	slatearea *create_area(slate *parent_slate);
	
protected:
	
	sdl_viewportcanvas *viewport_screen;
	
private:
	
	
};


void kickstarter_renderthread(sdl_viewport *parent_object);
#endif // _VIEWPORT_H_

