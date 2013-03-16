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

#include "slateobject.h"

#include <iostream>

using namespace std;

slateobject::slateobject(slate *parent_slate)
{
	connectedslates=new vector< vector<slate*> >;
	(*connectedslates).push_back( vector<slate*>() );
	(*connectedslates)[0].push_back(parent_slate);
}

slateobject::~slateobject()
{
	delete connectedslates;
}
void slateobject::set_screen_ob(void *screenob)
{
	screen_object=screenob;
}

void *slateobject::get_screen_ob()
{
	return screen_object;
}

