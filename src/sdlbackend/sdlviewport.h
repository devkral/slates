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
	sdlviewport(master *masteridd, int16_t ownidd);
	~sdlviewport();
	/**int32_t id_slate_mouse(int16_t x, int16_t y);
	slate *get_slate_mouse(int16_t x, int16_t y);*/
	int32_t get_focused_slate_id(); 
	void update_slice_info();
	slatearea *create_area(slate *parent_slate);

	void set_focused_slate(int32_t slateid);
	
	uint32_t slate_width=-1, slate_height=-1;
	
	void draw_viewwindow();
	
	SDL_Surface *background_IMG;
	SDL_Texture *background_IMG_tex;
	
	SDL_Renderer *viewportrender;
	SDL_DisplayMode viewdisplaymode;
	SDL_Rect dispbounds;
	SDL_Window *viewportwindow=0;
protected:
	
private:
	int32_t focused_slate=0;
	
};



#endif // _SDL_VIEWPORT_H_