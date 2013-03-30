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
	viewport_screen=new sdl_viewportcanvas(2);
	//SDL_CreateWindowAndRenderer(
	SDL_GetDisplayBounds(get_viewport_id(), &viewport_screen->dispbounds);
	bool justmaximize=true;
	if (justmaximize)
		viewport_screen->window=SDL_CreateWindow("Slates", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			           viewport_screen->dispbounds.w, viewport_screen->dispbounds.h,SDL_WINDOW_MAXIMIZED);
	else
		viewport_screen->window=SDL_CreateWindow("Slates", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			           viewport_screen->dispbounds.w, viewport_screen->dispbounds.h,SDL_WINDOW_FULLSCREEN);
	SDL_GetCurrentDisplayMode(get_viewport_id (),&viewport_screen->curdisplaymode);

	viewport_screen->globalrender=SDL_CreateRenderer(viewport_screen->window,-1,SDL_RENDERER_SOFTWARE);//|SDL_RENDERER_PRESENTVSYNC);//SDL_RENDERER_ACCELERATED);

	viewport_screen->viewport_tex=SDL_CreateTexture (viewport_screen->globalrender,
	                                                           viewport_screen->curdisplaymode.format,
	                                                           SDL_TEXTUREACCESS_STREAMING,
	                                                            viewport_screen->dispbounds.w,
																viewport_screen->dispbounds.h);
	viewport_screen->viewport=IMG_Load("themes/samplebackground.png");
	if (to_sdlviewport(viewport_screen)->viewport!=0)
	{
		to_sdlviewport(viewport_screen)->viewport_tex=SDL_CreateTextureFromSurface (to_sdlviewport(viewport_screen)->globalrender,to_sdlviewport(viewport_screen)->viewport);
		SDL_RenderCopy(to_sdlviewport(viewport_screen)->globalrender,to_sdlviewport(viewport_screen)->viewport_tex, 0, 0);
		SDL_RenderPresent(to_sdlviewport(viewport_screen)->globalrender);
		//SDL_UpdateTexture(to_sdmac(viewport_screen)->viewport_tex,0,to_sdmac(viewport_screen)->viewport->pixels,to_sdmac(viewport_screen)->viewport->pitch);
	}
	else
		cerr << "Couldn't load theme.\n";
	
}




sdl_viewport::~sdl_viewport()
{
	delete viewport_screen;
	viewport_screen=0;
}


long int sdl_viewport::id_slate_mouse(int x, int y)
{
	if (x<0 || y<0)
		return xy_negative;
	return calcidslate(x/viewport_screen->widget_w, y/viewport_screen->widget_h);
}
slate *sdl_viewport::get_slate_mouse(int x, int y)
{
	long int id= id_slate_mouse(x, y);
	if (id<0)
		return 0;
	return get_slate_by_id(id);

}


void sdl_viewport::update_slice_info()
{
	viewport_screen->widget_w=viewport_screen->dispbounds.w/get_viewport_width();
	viewport_screen->widget_h=viewport_screen->dispbounds.h/get_viewport_height();

	viewport_screen->beg_x=viewport_screen->widget_w*get_viewport_beg_x();
	viewport_screen->beg_y=viewport_screen->widget_h*get_viewport_beg_y();
	
	viewport_screen->max_w=viewport_screen->widget_w*get_viewport_width ();
	viewport_screen->max_h=viewport_screen->widget_h*get_viewport_height ();
	SDL_RenderClear(to_sdlviewport(viewport_screen)->globalrender);
	SDL_RenderCopy(viewport_screen->globalrender,viewport_screen->viewport_tex, 0, 0);
	SDL_RenderPresent(viewport_screen->globalrender);
}


void *sdl_viewport::get_viewportscreen()
{
	return (void*)viewport_screen;
}
slatearea *sdl_viewport::create_area(slate *parent_slate)
{
	sdl_slateareacanvas *temp=new sdl_slateareacanvas(viewport_screen);
	sdl_slatearea *temp2=new sdl_slatearea(parent_slate,temp);
	temp2->init();
	
	return (slatearea *)temp2 ;
}
