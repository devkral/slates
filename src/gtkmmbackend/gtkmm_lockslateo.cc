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

#include "gtkmm_lockslateo.h"

#include <iostream>

using namespace std;

gtkmm_lockslateo::gtkmm_lockslateo(slate *parent_slate, void *screenob) : lockslateo(parent_slate,screenob)
{
	cerr << "Create gtkmm_lockslateo\n";
	screen_object=new gtwidget;
}

gtkmm_lockslateo::~gtkmm_lockslateo()
{
	cerr << "Destroy gtkmm_lockslateo\n";
}

void gtkmm_lockslateo::draw()
{
	if (isdrawn==false)
	{
		isdrawn=true;
		draw_function ();
	}
	else
	{
		to_gtw(screen_object)->widgetspace.show();
	}
}
void gtkmm_lockslateo::hide()
{
	to_gtw(screen_object)->widgetspace.hide();
}

void gtkmm_lockslateo::unlock()
{
	cerr << "check password\n";
	getfparent()->getmaster()->unlock((char*)"test");

}

void gtkmm_lockslateo::cleanup_handler ()
{
	delete to_gtw(screen_object);
}
void gtkmm_lockslateo::draw_function ()
{
	to_gtw(screen_object)->widgetspace.show();
}
