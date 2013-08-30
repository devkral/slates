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

sdllockslate::sdllockslate(master *parent_mastert) : lockslate(parent_mastert)
{
	cerr << "Create sdl_lockslateo\n";
	update_interval=3000;
}

sdllockslate::~sdllockslate()
{
	cerr << "Destroy sdllockslate\n";
}


void sdllockslate::update()
{
	if (parent->get_isondestruction()==true)
		return;
	interact_with_draw.lock();
	//{

		if (locksur)
		{
			SDL_FreeSurface (locksur);
			locksur=0;
		}
		locksur=SDL_CreateRGBSurface (0,to_sdlslatearea (parent->get_screen())->slatebox.w,to_sdlslatearea (parent->get_screen())->slatebox.h,32,0,0,0,0);
		if (!locksur)
			return;
		
		green=SDL_MapRGBA (locksur->format, 0,255,0,255);
		SDL_FillRect (locksur, &to_sdlslatearea (parent->get_screen())->slatebox,green);
		if (locktex)
		{
			SDL_DestroyTexture (locktex);
			locktex=0;
		}
		locktex=SDL_CreateTextureFromSurface (to_sdlslatearea (parent->get_screen())->viewportcanvas->globalrender,locksur);

		interact_with_draw.unlock();
	//}
}


void sdllockslate::handle_event (void *event, bool called_by_input)
{
		if (parent->get_isvisible()==true && interact_with_draw.try_lock_for(defaulttimeout))
		{
			to_sdlslatearea (parent->get_screen())->viewportcanvas->drawmutex.lock();
			SDL_RenderCopy(to_sdlslatearea (parent->get_screen())->viewportcanvas->globalrender, locktex, 0, &to_sdlslatearea (parent->get_screen())->slatebox);
			SDL_RenderPresent(to_sdlslatearea (parent->get_screen())->viewportcanvas->globalrender);
			to_sdlslatearea (parent->get_screen())->viewportcanvas->drawmutex.unlock();

			interact_with_draw.unlock();
		}
	switch( ((SDL_Event*)event)->type )
		{
			case SDL_QUIT:
				get_master()->handle_masterevent(event); //message master
			break;
			case SDL_MOUSEBUTTONDOWN:
				if (((SDL_Event*)event)->button.button==SDL_BUTTON_LEFT)
				{
					cout << "unlock\n";
					parent->unlock();
				}
			break;
			case SDL_KEYDOWN:
			break;
			case SDL_MOUSEMOTION: 
				
			if (called_by_input==true && specialcondition==false)
			{
				if (((SDL_Event*)event)->motion.x<to_sdlslatearea (parent->get_screen())->slatebox.x ||
					((SDL_Event*)event)->motion.y<to_sdlslatearea (parent->get_screen())->slatebox.y)
				{	
					hasinputhandle=false;
				}
				if (((SDL_Event*)event)->motion.x>to_sdlslatearea (parent->get_screen())->slatebox.x+to_sdlslatearea (parent->get_screen())->slatebox.w ||
					((SDL_Event*)event)->motion.y>to_sdlslatearea (parent->get_screen())->slatebox.y+to_sdlslatearea (parent->get_screen())->slatebox.h)
				{
					hasinputhandle=false;
				}
			}
			break;
		}
			
	}

}




string sdllockslateo::enter_password ()
{
	bool done=false;
	SDL_Event textevent;
	SDL_StartTextInput();
	//while (!done)
	//{
		

	//}
	return (string)"test";

}

slatetype *sdllockslate::unlock()
{
	return lockedob;
}
bool sdllockslate::isempty()
{
	return true;
}

void sdllockslate::lock(slatetype *locked)
{
	lockedob=locked;
}
void sdllockslate::set_slatearea(slatearea *set)
{
	parent=set;
}
