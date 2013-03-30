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

#include "slatetype.h"

#include <iostream>

using namespace std;

slatetype::slatetype(master *parent_mastert)
{
	parent_master=parent_mastert;
}

slatetype::~slatetype()
{

}

master *slatetype::get_master()
{
	return parent_master;
}

void slatetype::init()
{
	drawthread=thread(kickstarter_drawthread,this);
}

void slatetype::cleanup()
{
	
	isdrawn=false;
	hasinputhandle=false;
	if (drawthread.joinable())
		drawthread.join();
}

void slatetype::draw_function()
{
	//code
}


void slatetype::handle_event(void *event)
{

}

void slatetype::handle_input(void *initializer)
{
	
}

void kickstarter_drawthread(slatetype *parent)
{
	parent->draw_function ();
}