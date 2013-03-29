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

#include "gtkmm_slatearea.h"


#include "lockslateo.h"
class lockslateo;

gtkmm_slatearea::gtkmm_slatearea(slate *parent_slate) : slatearea(parent_slate)
{
	slatearea_screen=new gtkslatearea();
}

gtkmm_slatearea::~gtkmm_slatearea()
{
	delete slatearea_screen;
}

void *gtkmm_slatearea::get_screen()
{
	return (void*)slatearea_screen;
}

void gtkmm_slatearea::update_screen()
{
}
void gtkmm_slatearea::create_lockslatetype()
{

}
void gtkmm_slatearea::create_emptyslatetype()
{

}
