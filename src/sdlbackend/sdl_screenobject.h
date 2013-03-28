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

#ifndef _SDL_SCREENOBJECT_H_
#define _SDL_SCREENOBJECT_H_

#include <SDL2/SDL.h>
//#include <SDL2/SDL_opengl.h>
#include <thread>
#include <atomic>

using namespace std;


typedef struct sdlmastercanvas_{
	sdlmastercanvas_(int borderthicknesst)
	{
		is_rendering=false;
		borderthickness=borderthicknesst;
	}
		
	~sdlmastercanvas_()
	{
		SDL_DestroyRenderer (globalrender);
		SDL_DestroyWindow (window);
		SDL_DestroyTexture(viewport_tex);
		SDL_FreeSurface(viewport);
	}
	SDL_Window* window=0;
	SDL_Renderer* globalrender=0;
	atomic<bool> is_rendering;
	SDL_Texture *viewport_tex=0;
	SDL_Surface *viewport=0;
	int displayindex=0;
	SDL_Rect dispbounds;
	SDL_DisplayMode curdisplaymode;
	int widget_w=0;
	int widget_h=0;
	int max_w=0;
	int max_h=0;
	int beg_x=0;
	int beg_y=0;
	int borderthickness=0;
	Uint32 white=0;
	Uint32 black=0;
	
	
}sdlmastercanvas;





typedef struct sdlslatecanvas_{
	sdlslatecanvas_(sdlmastercanvas *mastercanvast)
	{
		mastercanvas=mastercanvast;
		slateface=SDL_CreateRGBSurface(0,1,1,32,0,0,0,0);
	}
	~sdlslatecanvas_()
	{
		SDL_FreeSurface (slateface);
		SDL_DestroyRenderer (slaterender);
	}
	SDL_Rect slatebox;
	SDL_Renderer *slaterender;	
	SDL_Surface *slateface;	
	
	//must not be freed done by master
	sdlmastercanvas *mastercanvas=0;
	void updaterect(int x, int y, int w, int h)
	{
		slatebox.x=x+mastercanvas->borderthickness;
		slatebox.y=y+mastercanvas->borderthickness;
		slatebox.w=w-mastercanvas->borderthickness;
		slatebox.h=h-mastercanvas->borderthickness;

	};
	
}sdlslatecanvas;



extern sdlmastercanvas *to_sdmac(void* in);
extern sdlslatecanvas *to_sdslc(void* in);


#endif // _TSCREENOBJECT_H_

