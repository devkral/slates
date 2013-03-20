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

#include "sdl_viewport.h"

#include <iostream>

using namespace std;


sdl_viewport::sdl_viewport(master *masteridd, int ownidd) : viewport(masteridd,ownidd)
{
	cerr << "Create sdl_viewport\n";
	viewport_screen=new sdlmastercanvas;
	to_sdmac(viewport_screen)->canvas=(char *)"kjaaio";
}

sdl_viewport::~sdl_viewport()
{
	cerr << "Destroy sdl_viewport\n";
}


slate *sdl_viewport::create_slate_intern(viewport *parent, long int id,int position_xtemp,int position_ytemp)
{
	return new sdl_slate(parent,id,position_xtemp,position_ytemp);
}

void sdl_viewport::destroy_mscreen_ob()
{
	delete to_sdmac(viewport_screen);
}