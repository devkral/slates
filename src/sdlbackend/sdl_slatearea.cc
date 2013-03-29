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

#include "sdl_slatearea.h"

sdl_slatearea::sdl_slatearea(slate *parent_slate, sdl_slateareacanvas *canvastemp) : slatearea(parent_slate)
{
	screen=canvastemp;
}

sdl_slatearea::~sdl_slatearea()
{
	
	delete screen;
	screen=0;
}

void *sdl_slatearea::get_screen()
{
	return (void*)screen;
}

void sdl_slatearea::update_screen()
{
	screen->updaterect(
			        (get_origin ()->get_x())*(screen->viewportcanvas->widget_w-screen->viewportcanvas->beg_x),
			       (get_origin()->get_y())*(screen->viewportcanvas->widget_h-screen->viewportcanvas->beg_y),
		(screen->viewportcanvas->widget_w - screen->viewportcanvas->beg_x),
		 (screen->viewportcanvas->widget_h - screen->viewportcanvas->beg_y));
}

void sdl_slatearea::create_lockslatetype()
{
	sdl_lockslateo *temp=new sdl_lockslateo(get_master());
	temp->init();
	temp->lock(this,child);
	child=temp;
}

void sdl_slatearea::create_emptyslatetype()
{
	emptyslateo *temp=new sdl_emptyslateo(get_master());
	selfreference_pointer=temp->set_slatearea(this);
	temp->init();
	child=temp;
}