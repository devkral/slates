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

#include "sdlemptyslate.h"

#include "sdlbackend.h"
#include <iostream>

using namespace std;


sdlemptyslate::sdlemptyslate(slatearea *parentt, master *parent_mastert) : emptyslate(parentt, parent_mastert)
{
	cerr << "Create sdlemptyslate\n";
	windowbounds.x=(Sint16)(get_slatearea ()->get_x ()*((sdlviewport *) get_viewport ())->slate_width + ((sdlslatearea* )get_slatearea ())->border);
	windowbounds.y=(Sint16)(get_slatearea ()->get_y ()*((sdlviewport *) get_viewport ())->slate_height + ((sdlslatearea* )get_slatearea ())->border);
	windowbounds.w=(Uint16)(get_slatearea ()->get_w ()*((sdlviewport *) get_viewport ())->slate_width - ((sdlslatearea* )get_slatearea ())->border-3);
	windowbounds.h=(Uint16)(get_slatearea ()->get_h ()*((sdlviewport *) get_viewport ())->slate_height - ((sdlslatearea* )get_slatearea ())->border-3);

	cerr << windowbounds.x << " " << windowbounds.y << " " << windowbounds.w << " " << windowbounds.h << endl;
	ewindow=SDL_CreateWindow("Slates", windowbounds.x, windowbounds.y,
			           windowbounds.w, windowbounds.h,SDL_WINDOW_BORDERLESS);//SDL_WINDOW_BORDERLESS
	
	if (((sdlviewport*)get_viewport ())->hw_accel())
		erender=SDL_CreateRenderer (ewindow,-1,SDL_RENDERER_ACCELERATED);
	else
		erender=SDL_CreateRenderer (ewindow,-1,SDL_RENDERER_SOFTWARE);

	if (!epicture)
		epicture=IMG_Load("themes/exampleemptyslate2.png");
}	   

sdlemptyslate::~sdlemptyslate()
{
	SDL_DestroyRenderer (erender);
	SDL_DestroyWindow (ewindow);
	SDL_DestroyTexture (emptytex);
	SDL_FreeSurface (epicture);
}

void sdlemptyslate::update()
{
	if (get_slatearea ()->get_isdestroying()==true)
		return;
	//cerr << windowbounds.x << " " << windowbounds.y << " " << windowbounds.w << " " << windowbounds.h << endl;
	SDL_Rect oldwindowbounds=windowbounds;

	windowbounds.x=(Sint16)(get_slatearea ()->get_x ()*((sdlviewport *) get_viewport ())->slate_width + ((sdlslatearea* )get_slatearea ())->border);
	windowbounds.y=(Sint16)(get_slatearea ()->get_y ()*((sdlviewport *) get_viewport ())->slate_height + ((sdlslatearea* )get_slatearea ())->border);
	windowbounds.w=(Uint16)(get_slatearea ()->get_w ()*((sdlviewport *) get_viewport ())->slate_width - ((sdlslatearea* )get_slatearea ())->border-3);
	windowbounds.h=(Uint16)(get_slatearea ()->get_h ()*((sdlviewport *) get_viewport ())->slate_height - ((sdlslatearea* )get_slatearea ())->border-3);


	SDL_SetWindowPosition(ewindow,windowbounds.x,windowbounds.y);
	SDL_SetWindowSize(ewindow,windowbounds.w,windowbounds.h);

	SDL_RaiseWindow (ewindow);

	if (!epicture)
	{
		cerr << "epicture couldn't be loaded\n";
		return;
	}
	if (!emptytex || oldwindowbounds.x!=windowbounds.x || oldwindowbounds.y!=windowbounds.y ||
	    oldwindowbounds.w!=windowbounds.w || oldwindowbounds.h!=windowbounds.h)
	{
		if (emptytex)
			SDL_DestroyTexture (emptytex);
		emptytex=SDL_CreateTexture (erender,
	                                                          ((sdlviewport*)get_viewport ())->viewdisplaymode.format,
	                                                           SDL_TEXTUREACCESS_STREAMING,
	                                                            windowbounds.w,
																windowbounds.h);
	}
	SDL_Surface *emptysur=SDL_CreateRGBSurface (0,windowbounds.w,windowbounds.h,32,0,0,0,255);
	SDL_LockTexture(emptytex, 0, &emptysur->pixels, &emptysur->pitch);
	SDL_BlitSurface(epicture,0,emptysur,0);
	// paint into surface pixels
	SDL_UnlockTexture(emptytex);
	
	SDL_RenderCopy(erender,emptytex, 0, 0);
	SDL_RenderPresent(erender);
	
	wasinit=true;
}


void sdlemptyslate::handle_event (void *event)
{

	switch( ((SDL_Event*)event)->type )
	{
		case SDL_WINDOWEVENT:
			if ( ((SDL_Event*)event)->window.windowID==SDL_GetWindowID(ewindow))
			{
				switch(  ((SDL_Event*)event)->window.event)
				{
					case SDL_WINDOWEVENT_ENTER:
					{
						((sdlslatearea*)get_slatearea ())->isfocused=true;
						((sdlviewport *)get_viewport ())->set_focused_slate (get_slatearea ()->get_origin ()->get_id());
					}
					break;
					case SDL_WINDOWEVENT_LEAVE:
					{
						((sdlslatearea*)get_slatearea ())->isfocused=false;
					}
					break;
					case SDL_WINDOWEVENT_RESIZED:
						update();
						break;
					case SDL_WINDOWEVENT_MOVED:
						update();
						break;
					default:
						if (!wasinit)
							update();

						break;
				}
				SDL_RenderCopy(erender,emptytex, 0, 0);
				SDL_RenderPresent(erender);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			/**if (((SDL_Event*)event)->button.button==SDL_BUTTON_LEFT)
			{
				get_slatearea ()->setlock(0);
			}*/
			break;
		case SDL_KEYDOWN:
			break;
	}

}

bool sdlemptyslate::isdirty()
{
	return true;
}

