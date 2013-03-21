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


#include <iostream>

using namespace std;


sdl_emptyslateo::sdl_emptyslateo(slate *parent_slate, void *screenob) : emptyslateo(parent_slate,screenob)
{
	update_interval=100;
	widget.inner_object.x=to_sdslc(screen_object)->slatebox.x;
	widget.inner_object.y=to_sdslc(screen_object)->slatebox.y;
	widget.inner_object.w=to_sdslc(screen_object)->slatebox.w;
	widget.inner_object.h=to_sdslc(screen_object)->slatebox.h;
	widget.inn=SDL_CreateRGBSurface (0,widget.inner_object.w,widget.inner_object.h,32,255,1,1,0);
	
}

sdl_emptyslateo::~sdl_emptyslateo()
{
}
void sdl_emptyslateo::draw()
{
	if (isdrawn==false)
	{
		isdrawn=true;
		drawthread=thread(kickstarter_drawthread, (slateobject *)this);
	}
	else
	{
		cerr << "Update sdl_emptyslateo\n";
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

		SDL_RenderClear(to_sdslc(screen_object)->mastercanvas->screenrender);
        //SDL_RenderCopy(to_sdslc(screen_object)->mastercanvas->screenrender, &widget.inn, NULL, NULL);

		
		SDL_RenderCopy(to_sdslc(screen_object)->mastercanvas->screenrender,
		               SDL_CreateTextureFromSurface(to_sdslc(screen_object)->mastercanvas->screenrender,
		                                            widget.inn),NULL,&widget.inner_object);
		SDL_RenderPresent(to_sdslc(screen_object)->mastercanvas->screenrender);
		//SDL_BlitSurface(inn,0, to_sdslc(screen_object)->mastercanvas->viewport,&widget.inner_object);
		//SDL_RenderDrawRect(to_sdslc(screen_object)->mastercanvas->screenrender,&widget.inner_object);
		SDL_Delay(update_interval);
	}
}
