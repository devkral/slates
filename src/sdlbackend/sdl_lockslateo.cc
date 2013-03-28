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

#include "sdl_lockslateo.h"

#include <iostream>

using namespace std;

sdl_lockslateo::sdl_lockslateo(master *parent_mastert) : lockslateo(parent_mastert)
{
	cerr << "Create sdl_lockslateo\n";
	update_interval=3000;
}

sdl_lockslateo::~sdl_lockslateo()
{
	cerr << "Destroy sdl_lockslateo\n";
}


void sdl_lockslateo::update()
{
/**	interact_with_draw.lock();
	//{
		to_sdslc(screen_object)->updaterect(
			        (getfparent()->get_position_x())*(to_sdmac (getviewport()->get_viewport_screen())->widget_w-to_sdmac (getviewport()->get_viewport_screen())->beg_x),
			       (getfparent()->get_position_y())*(to_sdmac (getviewport()->get_viewport_screen())->widget_h-to_sdmac (getviewport()->get_viewport_screen())->beg_y),
		(to_sdmac (getviewport()->get_viewport_screen())->widget_w - to_sdmac (getviewport()->get_viewport_screen())->beg_x),
		 (to_sdmac (getviewport()->get_viewport_screen())->widget_h - to_sdmac (getviewport()->get_viewport_screen())->beg_y));

	
		if (isvisible==false || to_sdslc (screen_object)->mastercanvas->max_w<=to_sdslc (screen_object)->slatebox.x || 
		    to_sdslc (screen_object)->mastercanvas->max_h<=to_sdslc (screen_object)->slatebox.y ||
		    to_sdslc (screen_object)->slatebox.x+to_sdslc (screen_object)->slatebox.w<=0  ||
		    to_sdslc (screen_object)->slatebox.y+to_sdslc (screen_object)->slatebox.h<=0)
		{
			isdrawn=false;
			hasinputhandle=false;
		}
		else if (isdrawn==false)
		{
			if (drawthread.joinable())
				drawthread.join();
			isdrawn=true;
			drawthread=thread(kickstarter_drawthread, (slateobject *)this);
		}
		
		interact_with_draw.unlock();
	//}*/
}


void sdl_lockslateo::handle_event (void *event, bool called_by_input)
{

	if (called_by_input==true && ((SDL_Event*)event)->key.keysym.sym==SDLK_ESCAPE)
	{
		hasinputhandle=false;
		//getfparent()->getmaster()->handle_masterevent(event);
	}
	else
	{
		switch( ((SDL_Event*)event)->type )
		{
			case SDL_QUIT: hasinputhandle=false;
				//getfparent()->getmaster()->handle_masterevent(event); //message master
			break;
			case SDL_MOUSEBUTTONDOWN:
				if (((SDL_Event*)event)->button.button==SDL_BUTTON_LEFT)
				{
					cout << "Replaced by emptyobject\n";
					//getfparent ()->unlock_slate();
				}
			break;
			case SDL_MOUSEMOTION: 
			if (called_by_input==true)
			{
				/**if (((SDL_Event*)event)->motion.x<to_sdslc (screen_object)->slatebox.x ||
					((SDL_Event*)event)->motion.y<to_sdslc (screen_object)->slatebox.y)
				{	
					hasinputhandle=false;
				}
				if (((SDL_Event*)event)->motion.x>to_sdslc (screen_object)->slatebox.x+to_sdslc (screen_object)->slatebox.w ||
					((SDL_Event*)event)->motion.y>to_sdslc (screen_object)->slatebox.y+to_sdslc (screen_object)->slatebox.h)
				{
					hasinputhandle=false;
				}*/
			}
			break;
		}
			
	}

}

void sdl_lockslateo::handle_input (void *initializer)
{
	hasinputhandle=true;
	cout << "lockslate ready to serve\n"; 
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


void sdl_lockslateo::draw_function ()
{
	/**while(isdrawn==true)
	{

		if (interact_with_draw.try_lock_for(defaulttimeout))
		{

			//SDL_RenderCopy(to_sdslc (screen_object)->slaterender, widget.emptytex, 0, &to_sdslc(screen_object)->slatebox);
			//SDL_RenderCopy(to_sdslc (screen_object)->mastercanvas->globalrender, widget.emptytex, 0, &to_sdslc(screen_object)->slatebox);
			//SDL_RenderCopy(to_sdslc (screen_object)->slaterender, widget.emptytex, 0, &widget.inner_object);
			//SDL_RenderPresent(to_sdslc (screen_object)->slaterender);
			//if (to_sdslc (screen_object)->mastercanvas->is_rendering==false)
			//{
			//	to_sdslc (screen_object)->mastercanvas->is_rendering=true;
				//SDL_RenderCopy(to_sdslc (screen_object)->mastercanvas->globalrender,
				//               to_sdslc (screen_object)->mastercanvas->viewport_tex,0,0);
				//SDL_RenderPresent(to_sdslc (screen_object)->slaterender);
				//SDL_RenderPresent(to_sdslc (screen_object)->mastercanvas->globalrender);
			//	to_sdslc (screen_object)->mastercanvas->is_rendering=false;
			//}
		
			interact_with_draw.unlock();
		}
		SDL_Delay(update_interval);
	}*/
}


string sdl_lockslateo::enter_password ()
{
	bool done=false;
	SDL_Event textevent;
	SDL_StartTextInput();
	//while (!done)
	//{
		

	//}
	return (string)"test";

}

slatetype *sdl_lockslateo::unlock(slatearea *ttt)
{
	return 0;
}
bool sdl_lockslateo::isempty()
{
	return true;
}

void sdl_lockslateo::lock(slatearea *, slatetype*)
{

}
