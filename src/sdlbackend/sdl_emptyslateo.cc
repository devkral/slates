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


sdl_emptyslateo::sdl_emptyslateo(slate *parent_slate) : emptyslateo(parent_slate)
{
	cerr << "Create sdl_emptyslateo\n";
	screen_object=new sdlslatecanvas;
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
	SDL_Event event;
	while(isdrawn==true)
	{
		SDL_Delay(10000);
	}
}
