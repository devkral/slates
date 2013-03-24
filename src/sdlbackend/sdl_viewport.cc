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

#include "sdl_viewport.h"

#include <iostream>
#include <SDL2/SDL_image.h>

using namespace std;


sdl_viewport::sdl_viewport(master *masteridd, int ownidd) : viewport(masteridd,ownidd)
{
	cerr << "Create sdl_viewport\n";
	create_mscreen_ob();
	//addslice(); 
}




sdl_viewport::~sdl_viewport()
{
	
}


slate *sdl_viewport::create_slate_intern(viewport *parent, long int id,int position_xtemp,int position_ytemp)
{
	return new sdl_slate(parent,id,position_xtemp,position_ytemp);
}

void sdl_viewport::destroy_mscreen_ob()
{
	delete to_sdmac(viewport_screen);
}

void sdl_viewport::create_mscreen_ob()
{
	viewport_screen=new sdlmastercanvas;
	//SDL_CreateWindowAndRenderer(
	SDL_GetDisplayBounds(get_id(), &to_sdmac(viewport_screen)->dispbounds);
	to_sdmac(viewport_screen)->window=SDL_CreateWindow("Slates", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                 to_sdmac(viewport_screen)->dispbounds.w, to_sdmac(viewport_screen)->dispbounds.h,SDL_WINDOW_MAXIMIZED);//SDL_WINDOW_FULLSCREEN);
	SDL_GetWindowDisplayMode(to_sdmac(viewport_screen)->window,&to_sdmac(viewport_screen)->curdisplaymode);

	to_sdmac(viewport_screen)->globalrender=SDL_CreateRenderer(to_sdmac(viewport_screen)->window,-1,SDL_RENDERER_SOFTWARE);//SDL_RENDERER_ACCELERATED);
	to_sdmac(viewport_screen)->viewport_tex=SDL_CreateTexture (to_sdmac(viewport_screen)->globalrender,
	                                                           to_sdmac(viewport_screen)->curdisplaymode.format,
	                                                           SDL_TEXTUREACCESS_STREAMING,
	                                                            to_sdmac(viewport_screen)->dispbounds.w,
																to_sdmac(viewport_screen)->dispbounds.h);
	to_sdmac(viewport_screen)->viewport=IMG_Load("themes/samplebackground.png");
	if (to_sdmac(viewport_screen)->viewport!=0)
		SDL_UpdateTexture(to_sdmac(viewport_screen)->viewport_tex,0,to_sdmac(viewport_screen)->viewport->pixels,to_sdmac(viewport_screen)->viewport->pitch);
	else
		cerr << "Couldn't load theme.\n";
}

long int sdl_viewport::id_slate_mouse(int x, int y)
{
	if (x<0 || y<0)
		return xy_negative;
	return calcidslate(x/to_sdmac(viewport_screen)->widget_w, y/to_sdmac(viewport_screen)->widget_h);
}
slate *sdl_viewport::get_slate_mouse(int x, int y)
{
	long int id= id_slate_mouse(x, y);
	if (id<0)
		return 0;
	return getslate_by_id(id);

}


void sdl_viewport::update_slice_change()
{
	to_sdmac(viewport_screen)->widget_w=to_sdmac(viewport_screen)->dispbounds.w/get_slices();
	to_sdmac(viewport_screen)->widget_h=to_sdmac(viewport_screen)->dispbounds.h/get_slices();
}



