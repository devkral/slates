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
sdlviewport::sdlviewport(master *masteridd, int16_t ownidd) : viewport(masteridd,ownidd)
{
	cerr << "Create sdlviewport\n";
	SDL_GetDisplayBounds(get_viewport_id(), &dispbounds);
	viewportwindow=SDL_CreateWindow("Slates", 0, 0,
		           dispbounds.w, dispbounds.h,SDL_WINDOW_FULLSCREEN);

	/**
	SDL_SysWMinfo *wminfo;
	SDL_GetWindowWMInfo(viewportwindow, wminfo);
	if (wminfo->subsystem==SDL_SYSWM_X11)
	{
		MoveWindowToScreen (wminfo,(int32_t)get_id());

	}*/
	
	SDL_GetCurrentDisplayMode(get_viewport_id (),&viewdisplaymode);
	if (hw_accel())
		viewportrender=SDL_CreateRenderer(viewportwindow,-1,SDL_RENDERER_ACCELERATED);//SDL_RENDERER_SOFTWARE);//|SDL_RENDERER_PRESENTVSYNC);//);
	else
		viewportrender=SDL_CreateRenderer(viewportwindow,-1,SDL_RENDERER_SOFTWARE);//SDL_RENDERER_SOFTWARE);//|SDL_RENDERER_PRESENTVSYNC);//SDL_RENDERER_ACCELERATED);


	SDL_SetRenderDrawColor(viewportrender, 255, 0, 0, 255);
	SDL_RenderClear (viewportrender);
	SDL_RenderPresent (viewportrender);
	
	background_IMG_tex=SDL_CreateTexture (viewportrender,
	                                                          viewdisplaymode.format,
	                                                           SDL_TEXTUREACCESS_STREAMING,
	                                                            dispbounds.w,
																dispbounds.h);
	//http://stackoverflow.com/questions/12506979/what-is-the-point-of-an-sdl2-texture
	if (background_IMG_tex)
	{
		background_IMG=IMG_Load("themes/examplebackground.png");
		
		
		
		if (!background_IMG)
			cerr << "Couldn't load theme.\n";
		//SDL_UpdateTexture(to_sdmac(viewport_screen)->viewport_tex,0,to_sdmac(viewport_screen)->viewport->pixels,to_sdmac(viewport_screen)->viewport->pitch);
	}
	if (!background_IMG_tex)
		cerr << "Couldn't load texture.\n";
	draw_viewwindow();
}




sdlviewport::~sdlviewport()
{
	
	SDL_DestroyTexture (background_IMG_tex);
	SDL_FreeSurface (background_IMG);
	SDL_DestroyRenderer (viewportrender);
	SDL_DestroyWindow ( viewportwindow);
}

void sdlviewport::set_focused_slate(int32_t slateid)
{
	focused_slate=slateid;
}




void sdlviewport::draw_viewwindow()
{

	//SDL_ShowWindow (viewportwindow);
	//SDL_SetWindowFullscreen (viewportwindow,SDL_WINDOW_FULLSCREEN);
	SDL_RenderCopy(viewportrender,background_IMG_tex, 0, 0);
	SDL_RenderPresent(viewportrender);
}

/**
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

}*/


void sdlviewport::update_slice_info()
{
	slate_width=dispbounds.w/get_viewport_width();
	slate_height=dispbounds.h/get_viewport_height();
		if (background_IMG)
		{
			SDL_Surface *tempsur=SDL_CreateRGBSurface (0,dispbounds.w,dispbounds.h,32,0,0,0,0);
			SDL_LockTexture(background_IMG_tex, &dispbounds, &tempsur->pixels, &tempsur->pitch);
			SDL_BlitSurface(background_IMG,0,tempsur,0);
			// paint into surface pixels
			SDL_UnlockTexture(background_IMG_tex);
			
		}
}

int32_t sdlviewport::get_focused_slate_id()
{
	return focused_slate; 

}

slatearea *sdlviewport::create_area(slate *parent_slate)
{
	return (slatearea*) new sdlslatearea(parent_slate);
}

