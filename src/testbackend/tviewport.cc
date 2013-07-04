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

#include "tviewport.h"

#include "tslatearea.h"
class tslatearea;
#include <iostream>

using namespace std;


tviewport::tviewport(master *masteridd, int ownidd) : viewport(masteridd,ownidd)
{
	cerr << "Create tviewport\n";
}

tviewport::~tviewport()
{
	cerr << "Destroy tviewport\n";
}


void tviewport::update_slice_info()
{
	cout << "slice updated\n";
}

void tviewport::render(slateareascreen *renderob)
{
	cout << "renderob updated\n";
}

slatearea *tviewport::create_area(slate *parent_slate)
{
	return (slatearea*) new tslatearea(parent_slate);
}