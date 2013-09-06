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
	windowbounds.x=(Sint16)(get_slatearea ()->get_x ()*((sdlviewport *) get_viewport ())->slate_width + ((sdlslatearea* )get_slatearea ())->border);
	windowbounds.y=(Sint16)(get_slatearea ()->get_y ()*((sdlviewport *) get_viewport ())->slate_height + ((sdlslatearea* )get_slatearea ())->border);
	windowbounds.w=(Uint16)(get_slatearea ()->get_w ()*((sdlviewport *) get_viewport ())->slate_width - ((sdlslatearea* )get_slatearea ())->border);
	windowbounds.h=(Uint16)(get_slatearea ()->get_h ()*((sdlviewport *) get_viewport ())->slate_height - ((sdlslatearea* )get_slatearea ())->border);

	//SDL_CreateWindowAndRendererSync(&ewindow,&erender,&windowbounds);
	SDL_CreateRendererSync(((sdlviewport*)get_viewport())->viewportwindow,&erender);

	if (emptyusecount==0)
		epicture=IMG_Load("themes/exampleemptyslate2.png");
	emptyusecount++;
}

sdlemptyslate::~sdlemptyslate()
{
	emptyusecount--;
	SDL_DestroyWindowAndRenderer(0,erender);
	SDL_DestroyTexture (emptytex);
	if (emptyusecount<=0)
	{
		SDL_FreeSurface (epicture);
	}
}

void sdlemptyslate::update()
{
	if (get_slatearea ()->get_isdestroying()==true)
		return;
	//renderprot.lock();
	//cerr << windowbounds.x << " " << windowbounds.y << " " << windowbounds.w << " " << windowbounds.h << endl;
	SDL_Rect oldwindowbounds=windowbounds;

	windowbounds.x=(Sint16)(get_slatearea ()->get_x ()*((sdlviewport *) get_viewport ())->slate_width + ((sdlslatearea* )get_slatearea ())->border);
	windowbounds.y=(Sint16)(get_slatearea ()->get_y ()*((sdlviewport *) get_viewport ())->slate_height + ((sdlslatearea* )get_slatearea ())->border);
	windowbounds.w=(Uint16)(get_slatearea ()->get_w ()*((sdlviewport *) get_viewport ())->slate_width - ((sdlslatearea* )get_slatearea ())->border);
	windowbounds.h=(Uint16)(get_slatearea ()->get_h ()*((sdlviewport *) get_viewport ())->slate_height - ((sdlslatearea* )get_slatearea ())->border);


	SDL_SetWindowPosition(ewindow,windowbounds.x,windowbounds.y);
	SDL_SetWindowSize(ewindow,windowbounds.w,windowbounds.h);

	SDL_RaiseWindow (ewindow);

	if (!epicture)
	{
		cerr << "epicture couldn't be loaded\n";
		return;
	}
	/**
	if (!emptytex ||  oldwindowbounds.w!=windowbounds.w || oldwindowbounds.h!=windowbounds.h)
	{
		if (emptytex)
			SDL_DestroyTexture (emptytex);
		emptytex=SDL_CreateTexture (erender,
	                                                          ((sdlviewport*)get_viewport ())->viewdisplaymode.format,
	                                                           SDL_TEXTUREACCESS_STREAMING,
	                                                            windowbounds.w,
																windowbounds.h);
	}*/
	//SDL_Surface *emptysur=SDL_CreateRGBSurface (0,windowbounds.w,windowbounds.h,32,0,0,0,255);
	/**SDL_LockTexture(emptytex, 0, &emptysur->pixels, &emptysur->pitch);
	SDL_BlitSurface(epicture,&windowbounds,emptysur,&emptysur->clip_rect);
	// paint into surface pixels
	SDL_UnlockTexture(emptytex);
	
	SDL_RenderCopy(erender,emptytex, 0, 0);
	SDL_RenderPresent(erender);*/
	SDL_Surface *emptysur=SDL_CreateRGBSurface (0,((sdlviewport*)get_viewport())->dispbounds.w,((sdlviewport*)get_viewport())->dispbounds.h,32,0,0,0,255);
	SDL_LockTexture(((sdlviewport*)get_viewport())->background_IMG_tex, 0, &emptysur->pixels, &emptysur->pitch);
	//((SDL_Surface *emptysur=SDL_CreateRGBSurface (0,windowbounds.w,windowbounds.h,32,0,0,0,255);
	//SDL_LockTexture(((sdlviewport*)get_viewport())->background_IMG_tex, &windowbounds, &emptysur->pixels, &emptysur->pitch);
	SDL_BlitSurface(epicture,&windowbounds,emptysur,&windowbounds);
	// paint into surface pixels
	SDL_UnlockTexture(((sdlviewport*)get_viewport())->background_IMG_tex);
	((sdlviewport*)get_viewport())->draw_viewwindow ();
	
	
	
	wasinit=true;
	//renderprot.unlock();
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
						else
						{
							SDL_RenderCopy(erender,emptytex, 0, 0);
							SDL_RenderPresent(erender);
						}
						break;
				}

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

