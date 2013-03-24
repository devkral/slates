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

#include "sdl_emptyslateo.h"

#include "sdlbackend.h"
class sdl_master;
#include <iostream>
#include <cassert>

using namespace std;


sdl_emptyslateo::sdl_emptyslateo(slate *parent_slate, void *screenob) : emptyslateo(parent_slate,screenob)
{
	update_interval=100;
	//SDL_RendererPresent
	//
}

sdl_emptyslateo::~sdl_emptyslateo()
{
}

void sdl_emptyslateo::draw()
{

	to_sdslc(screen_object)->updaterect(
	            (getfparent()->get_position_x())*(to_sdmac (getviewport()->get_viewport_screen())->widget_w),
	           (getfparent()->get_position_y())*(to_sdmac (getviewport()->get_viewport_screen())->widget_h),
	(to_sdmac (getviewport()->get_viewport_screen())->widget_w),
	 (to_sdmac (getviewport()->get_viewport_screen())->widget_h));

	
	widget.inner_object.x=to_sdslc(screen_object)->slatebox.x+2;
	widget.inner_object.y=to_sdslc(screen_object)->slatebox.y+2;
	widget.inner_object.w=to_sdslc(screen_object)->slatebox.w-2;
	widget.inner_object.h=to_sdslc(screen_object)->slatebox.h-2;

	widget.emptysur=SDL_CreateRGBSurface (0,widget.inner_object.w,widget.inner_object.h,32,0,0,0,0);
	assert(widget.emptysur!=0);
	
	Uint32 white=SDL_MapRGBA (widget.emptysur->format, 255,255,255,255);

	SDL_FillRect (widget.emptysur, &widget.inner_object, white);
	widget.emptytex=SDL_CreateTextureFromSurface (to_sdslc(screen_object)->mastercanvas->screenrender,widget.emptysur);
	//SDL_RenderPresent(to_sdslc (screen_object)->mastercanvas->screenrender);
	
	 
	if (isdrawn==false)
	{
		isdrawn=true;
		drawthread=thread(kickstarter_drawthread, (slateobject *)this);
	}
	else
	{
		isdrawn=false;
		drawthread.join();
		isdrawn=true;
		drawthread=thread(kickstarter_drawthread, (slateobject *)this);
	}
}




void sdl_emptyslateo::cleanup_handler ()
{
	delete to_sdslc (screen_object);
}

void sdl_emptyslateo::draw_function ()
{
	while(isdrawn==true)
	{
		//SDL_RenderCopy(to_sdslc (screen_object)->mastercanvas->screenrender, widget.emptytex, &widget.inner_object, &widget.inner_object);

		SDL_RenderCopy(to_sdslc (screen_object)->mastercanvas->screenrender, widget.emptytex, NULL, &widget.inner_object);
		if (to_sdslc (screen_object)->mastercanvas->is_rendering==false)
		{
			to_sdslc (screen_object)->mastercanvas->is_rendering=true;
			SDL_RenderPresent(to_sdslc (screen_object)->mastercanvas->screenrender);
			to_sdslc (screen_object)->mastercanvas->is_rendering=false;
		}
		SDL_Delay(update_interval);
	}
}

void sdl_emptyslateo::handle_event (void *event)
{
	switch( ((SDL_Event*)event)->type )
	{
		case SDL_QUIT: hasinputhandle=false;
			getfparent()->getmaster()->send_event_to_all(event); //message master
			break;
		case SDL_KEYUP:
		case SDL_KEYDOWN:
			//the only modifier keys with which shortcuts can be made
			if (((SDL_Event*)event)->key.keysym.sym==SDLK_ESCAPE ||
			    ((SDL_Event*)event)->key.keysym.mod&KMOD_CTRL!=0 ||
			    ((SDL_Event*)event)->key.keysym.mod&KMOD_GUI!=0)
			{	if (getfparent()->getmaster()->send_event_to_all(event)==MASTER_QUIT)
				{
					hasinputhandle=false;
				}
			}
			break;
		case SDL_MOUSEMOTION: 
			if (specialcondition==false)
			{
				if (((SDL_Event*)event)->motion.x<to_sdslc (screen_object)->slatebox.x ||
					((SDL_Event*)event)->motion.y<to_sdslc (screen_object)->slatebox.y)
						hasinputhandle=false;
				if (((SDL_Event*)event)->motion.x>to_sdslc (screen_object)->slatebox.x+to_sdslc (screen_object)->slatebox.w ||
					((SDL_Event*)event)->motion.y<to_sdslc (screen_object)->slatebox.y+to_sdslc (screen_object)->slatebox.h)
						hasinputhandle=false;
			}
			break;
			
	}

}

void sdl_emptyslateo::handle_input (void *initializer)
{
	event=*((SDL_Event*)initializer);
	do
	{
		SDL_WaitEvent(&event);
		do
		{
			handle_event(&event);
		} while (SDL_PollEvent (&event));
		SDL_Delay(update_interval/2);
	}while (hasinputhandle);
		

	
}
