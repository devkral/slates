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

#include "tsysslateo.h"

#include <iostream>

using namespace std;

tsysslateo::tsysslateo(slate *parent_slate, void *screenob) : sysslate(parent_slate,screenob)
{
	cerr << "Create tsysslateo\n";
	screen_object=new tpscreen;
}

tsysslateo::~tsysslateo()
{
	cerr << "Destroy tsysslateo\n";
}

void tsysslateo::draw()
{
	if (isdrawn==false)
	{
		isdrawn=true;
		cerr << "Draw tsysslateo\n";
		drawthread=thread(kickstarter_drawthread, (slateobject *)this);
	}
	else
	{
		cerr << "Update tsysslateo\n";
	}
}

void tsysslateo::cleanup_handler ()
{
	delete to_tps(screen_object);
}

void tsysslateo::draw_function ()
{
}
