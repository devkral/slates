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

slatetype::slatetype(viewport *parent_viewportt);
{
	parent_viewport=parent_viewportt;
	isdrawn=true;
	drawthread=thread(kickstarter_drawthread,this);
}

slatetype::~slatetype()
{
	isdrawn=false;
	hasinputhandle=false;
	if (drawthread.joinable())
		drawthread.join();
}

void slatetype::update()
{

}

void slatetype::draw_function()
{
	//code
}

viewport *slatetype::getviewport()
{
	return parent_viewport;
}


void slatetype::handle_event(void *event, bool called_by_input)
{

}

void slatetype::handle_input(void *initializer)
{
	
}

void kickstarter_drawthread(slatetype *parent)
{
	parent->draw_function ();
}