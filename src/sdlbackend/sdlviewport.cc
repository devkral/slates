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

#include "sdlviewport.h"



#include <iostream>
#include <SDL2/SDL_image.h>



using namespace std;
sdlviewport::sdlviewport(master *masteridd, int ownidd) : viewport(masteridd,ownidd)
{
	cerr << "Create sdl_viewport\n";
	//SDL_CreateWindowAndRenderer(
	SDL_GetDisplayBounds(get_viewport_id(), &dispbounds);
	bool justmaximize=true;
	if (justmaximize)
		viewportwindow=SDL_CreateWindow("Slates", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			           dispbounds.w, dispbounds.h,SDL_WINDOW_MAXIMIZED);
	else
		viewportwindow=SDL_CreateWindow("Slates", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			           dispbounds.w, dispbounds.h,SDL_WINDOW_FULLSCREEN);
	SDL_GetCurrentDisplayMode(get_viewport_id (),&curdisplaymode);

	globalrender=SDL_CreateRenderer(viewportwindow,-1,SDL_RENDERER_SOFTWARE);//|SDL_RENDERER_PRESENTVSYNC);//SDL_RENDERER_ACCELERATED);

	/**viewport_screen->viewport_tex=SDL_CreateTexture (viewport_screen->globalrender,
	                                                           viewport_screen->curdisplaymode.format,
	                                                           SDL_TEXTUREACCESS_STREAMING,
	                                                            viewport_screen->dispbounds.w,
																viewport_screen->dispbounds.h);*/
	background_IMG=*IMG_Load("themes/samplebackground.png");
/**	if (background_IMG_tex!=0)
	{
		to_sdlviewport(viewport_screen)->viewport_tex=SDL_CreateTextureFromSurface (to_sdlviewport(viewport_screen)->globalrender,to_sdlviewport(viewport_screen)->viewport);
		SDL_RenderCopy(to_sdlviewport(viewport_screen)->globalrender,to_sdlviewport(viewport_screen)->viewport_tex, 0, 0);
		SDL_RenderPresent(to_sdlviewport(viewport_screen)->globalrender);
		//SDL_UpdateTexture(to_sdmac(viewport_screen)->viewport_tex,0,to_sdmac(viewport_screen)->viewport->pixels,to_sdmac(viewport_screen)->viewport->pitch);
	}
	else
		cerr << "Couldn't load theme.\n";*/
	
}




sdlviewport::~sdlviewport()
{
	free(globalrender);
	free( viewportwindow);
}


int32_t sdlviewport::id_slate_mouse(int16_t x, int16_t y)
{
	if (x<0 || y<0)
		return POS_NEG;
	return calcidslate(x/slate_width, y/slate_height);
}
slate *sdlviewport::get_slate_mouse(int16_t x, int16_t y)
{
	long int id= id_slate_mouse(x, y);
	if (id<0)
		return 0;
	return get_slate_by_id(id);

}


void sdlviewport::update_slice_info()
{
	slate_width=dispbounds.w/get_viewport_width();
	slate_height=dispbounds.h/get_viewport_height();
}

int32_t sdlviewport::get_focused_slate()
{
	return 0; 

}

slatearea *sdlviewport::create_area(slate *parent_slate)
{
	return (slatearea*) new sdlslatearea(parent_slate);
}

