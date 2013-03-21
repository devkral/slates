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

#include "sdl_slate.h"

#include <iostream>

using namespace std;


sdl_slate::sdl_slate (viewport *parent, long int id,int position_xtemp,int position_ytemp) : slate(parent, id,position_xtemp,position_ytemp)
{
	cerr << "Create sdl_slate\n";
}

sdl_slate::~sdl_slate()
{
	cerr << "Destroy sdl_slate\n";
}


slateobject *sdl_slate::create_lockobject()
{
	sdlslatecanvas *temp=new sdlslatecanvas(position_x*(to_sdmac (getviewport()->get_viewport_screen())->widget_w),
	position_y*(to_sdmac (getviewport()->get_viewport_screen())->widget_h),
	(to_sdmac (getviewport()->get_viewport_screen())->widget_w),
	 (to_sdmac (getviewport()->get_viewport_screen())->widget_h));
	temp->mastercanvas=to_sdmac (getviewport()->get_viewport_screen());
	return new sdl_lockslateo((slate*)this, temp);
}


slateobject *sdl_slate::create_emptyobject()
{
	sdlslatecanvas *temp=new sdlslatecanvas(position_x*(to_sdmac (getviewport()->get_viewport_screen())->widget_w),
	position_y*(to_sdmac (getviewport()->get_viewport_screen())->widget_h),
	(to_sdmac (getviewport()->get_viewport_screen())->widget_w),
	 (to_sdmac (getviewport()->get_viewport_screen())->widget_h));
	temp->mastercanvas=to_sdmac (getviewport()->get_viewport_screen());
	return new sdl_emptyslateo ((slate*)this,temp);
}

slateobject *sdl_slate::create_sysobject()
{
	sdlslatecanvas *temp=new sdlslatecanvas(position_x*(to_sdmac (getviewport()->get_viewport_screen())->widget_w),
	position_y*(to_sdmac (getviewport()->get_viewport_screen())->widget_h),
	(to_sdmac (getviewport()->get_viewport_screen())->widget_w),
	 (to_sdmac (getviewport()->get_viewport_screen())->widget_h));
	temp->mastercanvas=to_sdmac (getviewport()->get_viewport_screen());
	return new sdl_sysslateo ((slate*)this,temp);
}


slateobject *sdl_slate::create_windowobject(string progname)
{
	sdlslatecanvas *temp=new sdlslatecanvas(position_x*(to_sdmac (getviewport()->get_viewport_screen())->widget_w),
	position_y*(to_sdmac (getviewport()->get_viewport_screen())->widget_h),
	(to_sdmac (getviewport()->get_viewport_screen())->widget_w),
	 (to_sdmac (getviewport()->get_viewport_screen())->widget_h));
	temp->mastercanvas=to_sdmac (getviewport()->get_viewport_screen());
	return new sdl_windowslateo ((slate*)this,temp);
}