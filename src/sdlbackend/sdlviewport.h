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

#include "sdlslatearea.h"
class sdlslatearea;







using namespace std;


class sdlviewport : public viewport
{
public:
	sdlviewport(master *masteridd, int ownidd);
	~sdlviewport();
	long int id_slate_mouse(int x, int y);
	slate *get_slate_mouse(int x, int y);
	int32_t get_focused_slate(); 
	void *get_viewportscreen();
	void update_slice_info();
	slatearea *create_area(slate *parent_slate);
	
protected:
	static void kickstarter_renderthread (viewport *renderingob);
	thread renderthread;
	
private:
	
	
};



#endif // _SDL_VIEWPORT_H_