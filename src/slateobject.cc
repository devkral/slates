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
	connectedslates=make_shared<deque< deque<slate*> > >();
	(*connectedslates).push_back( deque<slate*>() );
	(*connectedslates)[0].push_back(parent_slate);
}

slateobject::~slateobject()
{
	
}



void slateobject::set_screen_ob(void *screenob)
{
	screen_object=screenob;
}
void slateobject::swap_screen_ob(shared_ptr<slateobject> swapso)
{
	void *temp=screen_object;
	set_screen_ob(swapso->get_screen_ob());
	swapso->set_screen_ob(temp);
}

void *slateobject::get_screen_ob()
{
	return screen_object;
}


void slateobject::set_connectedslates(shared_ptr<deque< deque<slate*> > > conslateob)
{
	connectedslates=conslateob;

}
void slateobject::swap_connectedslates(shared_ptr<slateobject> swapso)
{
	shared_ptr<deque< deque<slate*> > > tempob=swapso->get_connectedslates();
	set_connectedslates(swapso->get_connectedslates());
	swapso->set_connectedslates(tempob);
}

shared_ptr<deque< deque<slate*> > > slateobject::get_connectedslates()
{
	return connectedslates;
}

void slateobject::move(int x, int y)
{
	(*connectedslates)[0][0]->swap_childobject((*connectedslates)[0][0]->getviewport()->getslate (x,y));
}
void slateobject::resizeleftuppercorner(int x_delta, int y_delta)
{
	//implement in slate

}

void slateobject::resizerightlowercorner(int x_delta, int y_delta)
{
	//implement in slate

}

void slateobject::close()
{
	getfparent()->emptyslate();
}
void slateobject::hide()
{
	if (isdrawn==true)
	{
		isdrawn=false;
		drawthread.join();
	}
}
void slateobject::cleanup()
{
	hide();
	cleanup_handler();
}

slate *slateobject::getfparent()
{
	return (*connectedslates)[0][0];
}

viewport *slateobject::getviewport()
{
	return getfparent()->getviewport();
}


void kickstarter_drawthread(slateobject *parent)
{
	parent->draw_function ();
}