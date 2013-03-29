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

gtkmm_lockslateo::gtkmm_lockslateo(master *parent_master) : lockslateo(parent_master)
{
	cerr << "Create gtkmm_lockslateo\n";
}

gtkmm_lockslateo::~gtkmm_lockslateo()
{
	cerr << "Destroy gtkmm_lockslateo\n";
}

void gtkmm_lockslateo::draw_function ()
{
	
}

void gtkmm_lockslateo::update ()
{
	
}
