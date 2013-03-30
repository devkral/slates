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

#include "gtkmm_viewport.h"

#include <iostream>

using namespace std;


gtkmm_viewport::gtkmm_viewport(master *masteridd, int ownidd, gtkviewport *setviewport) : viewport(masteridd,ownidd)
{
	cout << "Create gtkmm_viewport\n";
	viewport_screen=setviewport;
}

gtkmm_viewport::~gtkmm_viewport()
{
	delete viewport_screen;
}


void gtkmm_viewport::update_slice_info()
{
	
}


slatearea *gtkmm_viewport::create_area(slate *parent_slate)
{
	gtkslatearea *temp=new gtkslatearea();
	gtkmm_slatearea *temp2=new gtkmm_slatearea(parent_slate,temp);
	temp2->init();
	return (slatearea*)temp2;

}
void *gtkmm_viewport::get_viewportscreen()
{
	return (void*)viewport_screen;
}

