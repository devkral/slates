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

#include "gtkmm_emptyslateo.h"


#include <iostream>

using namespace std;


gtkmm_emptyslateo::gtkmm_emptyslateo(slate *parent_slate, void *screenob) : emptyslateo(parent_slate,screenob)
{
	cerr << "Create gtkmm_emptyslateo\n";
	screen_object=new gtwidget;
}

gtkmm_emptyslateo::~gtkmm_emptyslateo()
{
	cerr << "Destroy gtkmm_emptyslateo\n";
}
void gtkmm_emptyslateo::draw()
{
	if (isdrawn==false)
	{
		isdrawn=true;
		draw_function();
	}
	else
	{
		to_gtw(screen_object)->widgetspace.show();
	}
}

void gtkmm_emptyslateo::hide()
{
	to_gtw(screen_object)->widgetspace.hide();
}

void gtkmm_emptyslateo::cleanup_handler ()
{
	delete to_gtw(screen_object);
}

void gtkmm_emptyslateo::draw_function ()
{
	to_gtw(screen_object)->widgetspace.show();
}
