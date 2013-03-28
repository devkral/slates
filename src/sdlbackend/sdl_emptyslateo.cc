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
#include "sdl_slateotypes.h"

#include "sdlbackend.h"
class sdl_master;
#include <iostream>
#include <cassert>

using namespace std;


sdl_emptyslateo::sdl_emptyslateo(master *parent_mastert) : emptyslateo(parent_mastert)
{
	cout << "Create emptyslate\n";
	update_interval=100;
	//SDL_RendererPresent
	//
}

sdl_emptyslateo::~sdl_emptyslateo()
{
	
}

void sdl_emptyslateo::update()
{
	/**interact_with_draw.lock();
	//{

		SDL_Surface *initsur=SDL_CreateRGBSurface (0,to_sdslc(screen_object)->slatebox.w,to_sdslc(screen_object)->slatebox.h,32,0,0,0,0);
		if (!initsur)
			cerr << "Could not initialize surface\n";
		sdlemptyoo.init_colors(initsur);
		SDL_FillRect (initsur, &to_sdslc(screen_object)->slatebox, sdlemptyoo.white);
		sdlemptyoo.set_emptysur(initsur,to_sdslc(screen_object)->mastercanvas->globalrender);
		                     ;
	
	
		
		//SDL_FillRect (widget.emptysur, &widget.inner_object, black);
		//SDL_SetRenderTarget(to_sdslc(screen_object)->slaterender,to_sdslc (screen_object)->mastercanvas->viewport_tex);
		//SDL_RenderPresent(to_sdslc (screen_object)->slaterender);
		//cout << "new innerobject x: " << widget.inner_object.x << " y: " << widget.inner_object.y << " w: " << widget.inner_object.w << "h: " << widget.inner_object.h << endl;

		
		interact_with_draw.unlock();
	//}*/
}


void sdl_emptyslateo::handle_event (void *event, bool called_by_input)
{

	if (called_by_input==true && SDL_GetModState()&(KMOD_GUI|KMOD_CTRL))
	{
		int status=getmaster()->handle_event(event);
		if (status==MASTER_QUIT)
		{
			hasinputhandle=false;
		}
	}
	else if (called_by_input==true && ((SDL_Event*)event)->key.keysym.sym==SDLK_ESCAPE)
	{
		hasinputhandle=false;
		getmaster()->handle_masterevent(event);
	}
	else
	{
		switch( ((SDL_Event*)event)->type )
		{
			case SDL_QUIT: hasinputhandle=false;
				getmaster()->handle_masterevent(event); //message master
			break;
			case SDL_MOUSEBUTTONDOWN:
				if (((SDL_Event*)event)->button.button==SDL_BUTTON_LEFT)
				{
					cout << "Replace by lockobject\n";
				//	getfparent ()->lock_slate();
				}
			break;
			case SDL_KEYDOWN:
			break;
			case SDL_MOUSEMOTION: 
				/**
			if (called_by_input==true && specialcondition==false)
			{
				if (((SDL_Event*)event)->motion.x<to_sdslc (screen_object)->slatebox.x ||
					((SDL_Event*)event)->motion.y<to_sdslc (screen_object)->slatebox.y)
				{	
					hasinputhandle=false;
				}
				if (((SDL_Event*)event)->motion.x>to_sdslc (screen_object)->slatebox.x+to_sdslc (screen_object)->slatebox.w ||
					((SDL_Event*)event)->motion.y>to_sdslc (screen_object)->slatebox.y+to_sdslc (screen_object)->slatebox.h)
				{
					hasinputhandle=false;
				}
			}*/
			break;
		}
			
	}

}

void sdl_emptyslateo::handle_input (void *initializer)
{
	hasinputhandle=true;
	event=*((SDL_Event*)initializer);
	do
	{
		SDL_WaitEvent(&event);
		do
		{
			handle_event(&event,true);
		} while (SDL_PollEvent (&event));
		SDL_Delay(update_interval/2);
	}while (hasinputhandle);	
}


void sdl_emptyslateo::draw_function ()
{
	/**while(isdrawn==true)
	{

//		interact_with_draw.lock();
		
		if (interact_with_draw.try_lock_for(defaulttimeout))
		{

			//SDL_RenderCopy(to_sdslc (screen_object)->slaterender, widget.emptytex, 0, &to_sdslc(screen_object)->slatebox);
			SDL_RenderCopy(to_sdslc (screen_object)->mastercanvas->globalrender, sdlemptyoo.get_emptytex(), 0, &to_sdslc(screen_object)->slatebox);
			//SDL_RenderCopy(to_sdslc (screen_object)->slaterender, widget.emptytex, 0, &widget.inner_object);
			//SDL_RenderPresent(to_sdslc (screen_object)->slaterender);
			//if (to_sdslc (screen_object)->mastercanvas->is_rendering==false)
			//{
			//	to_sdslc (screen_object)->mastercanvas->is_rendering=true;
				//SDL_RenderCopy(to_sdslc (screen_object)->mastercanvas->globalrender,
				//               to_sdslc (screen_object)->mastercanvas->viewport_tex,0,0);
				//SDL_RenderPresent(to_sdslc (screen_object)->slaterender);
				SDL_RenderPresent(to_sdslc (screen_object)->mastercanvas->globalrender);
			//	to_sdslc (screen_object)->mastercanvas->is_rendering=false;
			//}
		
			interact_with_draw.unlock();
		}
		SDL_Delay(update_interval);
	}*/
}

