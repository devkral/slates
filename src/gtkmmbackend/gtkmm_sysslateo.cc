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

#include "gtkmm_sysslateo.h"

#include <iostream>

using namespace std;

gtkmm_sysslateo::gtkmm_sysslateo(slate *parent_slate) : sysslateo(parent_slate)
{
	cerr << "Create gtkmm_sysslateo\n";
	screen_object=new gtwidget;
}

gtkmm_sysslateo::~gtkmm_sysslateo()
{
	cerr << "Destroy gtkmm_sysslateo\n";
}

void gtkmm_sysslateo::draw()
{
	if (isdrawn==false)
	{
		isdrawn=true;
		cerr << "Draw gtkmm_sysslateo\n";
	}
	else
	{
		cerr << "Update gtkmm_sysslateo\n";
	}
}

void gtkmm_sysslateo::cleanup_handler ()
{
	delete to_gtw(screen_object);
}

void gtkmm_sysslateo::draw_function ()
{
}
