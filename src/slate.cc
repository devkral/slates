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

#include "slate.h"

slate::slate (viewport *parent,long int id,int position_xtemp,int position_ytemp)
{
	slateid=id;
	parent_viewport=parent;
	position_x=position_xtemp;
	position_y=position_ytemp;
	create_area();
}

slate::~slate()
{
	if (child!=0)
		delete child;
	child=0;
}




bool slate::isfilled()
{
	return child->isfilled();
}

master *slate::getmaster()
{
	return parent_viewport->getmaster();
}

viewport *slate::getviewport()
{
	return parent_viewport;
}

void slate::create_area()
{
	if (child!=0)
		delete child;
	child=getviewport()->create_area(this);
}

void slate::replace_area(slatearea *newarea)
{
	if (child!=0)
		delete child;
	child=newarea;
}

/**
void slate::emptyslate_nonunique()
{
	shared_ptr<deque< deque<slate*> > > tempconectedslates=child_slateo->connectedslates;
	while (tempconectedslates->empty()==false)
	{
		while (tempconectedslates->back().empty()==false)
		{
			tempconectedslates->back().back()->replace_childobject(create_emptyobject());
			tempconectedslates->back().back()->draw();
			tempconectedslates->back().pop_back();
		}
		tempconectedslates->pop_back();
	}
}*/

void slate::update()
{
	child->update();
}

void slate::lock()
{
	//child->lock();
}

void slate::unlock()
{
	//child->unlock();
}


int slate::get_x()
{
	return position_x;
}

int slate::get_y()
{
	return position_y;
}

bool slate::isorigin()
{
	if (child->get_origin()->get_id()==get_id())
		return true;
	else
		return false;

}
int slate::get_id()
{
	return slateid;
}

void slate::handle_input(void *initializer)
{
	child->handle_input(initializer);
}

void slate::handle_event(void *event)
{
	child->handle_event(event);
}