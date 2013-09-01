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

}

sdlemptyslate::~sdlemptyslate()
{
	if (emptysur)
	{
		SDL_FreeSurface (emptysur);
		emptysur=0;
	}
	if (emptytex)
	{
		SDL_DestroyTexture (emptytex);
		emptytex=0;
	}
}

void sdlemptyslate::update()
{
	//cout << "Update empty\n";
	if (get_slatearea ()->get_isdestroying()==true)
		return;
	//{

		if (emptysur)
		{
			SDL_FreeSurface (emptysur);
			emptysur=0;
		}
		//emptysur=SDL_CreateRGBSurface (0,((sdlslatearea *) get_slatearea ())->slatebox.w,to_sdlslatearea (parent->get_screen())->slatebox.h,32,0,0,0,0);
		if (!emptysur)
			return;
		
		white=SDL_MapRGBA (emptysur->format, 255,255,255,255);
		black=SDL_MapRGBA (emptysur->format, 0,0,0,255);
		//SDL_FillRect (emptysur, &to_sdlslatearea (parent->get_screen())->slatebox,white);
		if (emptytex)
		{
			SDL_DestroyTexture (emptytex);
			emptytex=0;
		}
		//emptytex=SDL_CreateTextureFromSurface (to_sdlslatearea (parent->get_screen())->viewportcanvas->globalrender,emptysur);

	//}
}


void sdlemptyslate::handle_event (void *event, bool called_by_input)
{
/**
	if (called_by_input==true && SDL_GetModState()&(KMOD_GUI|KMOD_CTRL))
	{
		int status=get_master()->handle_event(event);
		if (status==MASTER_QUIT)
		{
			hasinputhandle=false;
		}
	}
	else if (called_by_input==true && ((SDL_Event*)event)->key.keysym.sym==SDLK_ESCAPE)
	{
		hasinputhandle=false;
		get_master()->handle_masterevent(event);
	}
	else
	{
		switch( ((SDL_Event*)event)->type )
		{
			case SDL_QUIT: hasinputhandle=false;
				get_master()->handle_masterevent(event); //message master
			break;
			case SDL_MOUSEBUTTONDOWN:
				if (((SDL_Event*)event)->button.button==SDL_BUTTON_LEFT)
				{
					cout << "Replace by lockobject\n";
					parent->lock();
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
				}
				if (((SDL_Event*)event)->motion.x>to_sdlslatearea (parent->get_screen())->slatebox.x+to_sdlslatearea (parent->get_screen())->slatebox.w ||
					((SDL_Event*)event)->motion.y>to_sdlslatearea (parent->get_screen())->slatebox.y+to_sdlslatearea (parent->get_screen())->slatebox.h)
				{
				}
			}
			break;
		}
			
	}
*/
}

bool sdlemptyslate::isdirty()
{
	return true;
}

