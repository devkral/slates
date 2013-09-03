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

#include "sdllockslate.h"

#include <iostream>

using namespace std;

sdllockslate::sdllockslate(slateareascreen *oldchild,slatearea *parentt,master *parent_mastert) : lockslate(oldchild,parentt,parent_mastert)
{
	cerr << "Create sdllockslate\n";
}

sdllockslate::~sdllockslate()
{
	cerr << "Destroy sdllockslate\n";
}


void sdllockslate::update()
{
	if (get_slatearea ()->get_isdestroying()==true)
		return;
	//interact_with_draw.lock();
	//{

		if (locksur)
		{
			SDL_FreeSurface (locksur);
			locksur=0;
		}
		//locksur=SDL_CreateRGBSurface (0,to_sdlslatearea (parent->get_screen())->slatebox.w,to_sdlslatearea (parent->get_screen())->slatebox.h,32,0,0,0,0);
		if (!locksur)
			return;
		
		green=SDL_MapRGBA (locksur->format, 0,255,0,255);
		//SDL_FillRect (locksur, &to_sdlslatearea (parent->get_screen())->slatebox,green);
		if (locktex)
		{
			SDL_DestroyTexture (locktex);
			locktex=0;
		}
		//locktex=SDL_CreateTextureFromSurface (to_sdlslatearea (parent->get_screen())->viewportcanvas->globalrender,locksur);

		//interact_with_draw.unlock();
	//}
}


void sdllockslate::handle_event (void *event)
{

}

bool sdllockslate::isdirty()
{
	return true;
}


string sdllockslate::enter_password ()
{
	bool done=false;
	SDL_Event textevent;
	SDL_StartTextInput();
	//while (!done)
	//{
		

	//}
	return (string)"test";

}

