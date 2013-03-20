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

#include "gtkmm_slate.h"

#include <iostream>

using namespace std;


gtkmm_slate::gtkmm_slate (viewport *parent, long int id,int position_xtemp,int position_ytemp) : slate(parent, id,position_xtemp,position_ytemp)
{
	cerr << "Create gtkmm_slate\n";
}

gtkmm_slate::~gtkmm_slate()
{
	cerr << "Destroy gtkmm_slate\n";
}


slateobject *gtkmm_slate::create_lockobject()
{
	return new gtkmm_lockslateo((slate*)this);
}


slateobject *gtkmm_slate::create_emptyobject()
{
	return new gtkmm_emptyslateo ((slate*)this);
}

slateobject *gtkmm_slate::create_sysobject()
{
	return new gtkmm_sysslateo ((slate*)this);
}


slateobject *gtkmm_slate::create_windowobject(string progname)
{
	return new gtkmm_windowslateo ((slate*)this);
}