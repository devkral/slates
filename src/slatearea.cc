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

#include "slatearea.h"


#include "lockslateo.h"
class lockslateo;

slatearea::slatearea(slate *parent_slate)
{
	connectedslates.push_back( deque<slate*>() );
	connectedslates[0].push_back(parent_slate);
	
}

slatearea::~slatearea()
{
	isondestruction=true;
}

void slatearea::init()
{
	create_emptyslatetype();
}

void slatearea::cleanup()
{
	isondestruction=true;
	if (child)
	{
		child->cleanup();
		delete child;
		child=0;
	}
	while (connectedslates.empty()==false)
	{
		connectedslates.pop_back();
	}
}

bool slatearea::isfilled()
{
	if (child->TYPE()!=TYPE_empty)
		return true;
	else
		return false;
}

bool slatearea::get_isondestruction ()
{
	return isondestruction;
}

bool slatearea::get_isvisible ()
{
	if (isondestruction==true)
		return false;
	return isvisible;
}
slate *slatearea::get_origin()
{
	return connectedslates[0][0];
}

master *slatearea::get_master()
{
	return get_origin()->get_master();
}

void slatearea::handle_event(void  *event)
{
	child->handle_event(event);
}

void slatearea::handle_input(void *initializer)
{
	child->handle_input(initializer);
}

void slatearea::update()
{
	if (get_x()+width<=get_origin ()->get_viewport()->get_viewport_beg_x() ||
		get_y()+height<=get_origin ()->get_viewport()->get_viewport_beg_y() ||
		get_x()>=get_origin ()->get_viewport()->get_viewport_width()+get_origin ()->get_viewport()->get_viewport_beg_x() ||
		get_y()>=get_origin()->get_viewport()->get_viewport_height()+get_origin ()->get_viewport()->get_viewport_beg_y())
	{
		isvisible=false;
	}

	else
	{
		isvisible=true;
	}
	update_screen();
	child->update();
}
void *slatearea::get_selfreference_pointer()
{
	return selfreference_pointer;
}

void slatearea::lock()
{
	if (lockstate==0)
	{
		create_lockslatetype ();
		lockstate+=1;
	}
}

void slatearea::unlock()
{
	if (lockstate==1)
	{
		lockslateo *temp=(lockslateo*)child;
		child=temp->unlock(this);
		if (temp->isempty()==true)
			delete temp;
		lockstate-=1;
	}
}

int slatearea::get_x()
{
	get_origin()->get_x();
}
int slatearea::get_y()
{
	get_origin()->get_y();
}


void slatearea::move(int x, int y)
{
	//get_origin()->get_viewport()->ge;
}

void slatearea::resize(int w, int h)
{

}