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

slate::slate (viewport *parent, long int id,int position_xtemp,int position_ytemp)
{
	parent_viewport=parent;
	slateid=id;
	position_x=position_xtemp;
	position_y=position_ytemp;
}

slate::~slate()
{
	//cleanup();
}

void slate::init_slate()
{
	emptyslate();
	preserve_after_lock.reset(create_lockobject());
}

void slate::cleanup()
{
	destroy_slate();
}



void slate::destroy_slate()
{
	replace_childobject(0);
}

bool slate::isfilled()
{
	return filled;
}

master *slate::getmaster()
{
	return parent_viewport->getmaster();
}

viewport *slate::getviewport()
{
	return parent_viewport;
}


void slate::set_screen_ob(void *screenob)
{
	child_slateo->set_screen_ob(screenob);
}

void *slate::get_screen_ob()
{
	return child_slateo->get_screen_ob();
}


void slate::swap_childobject(shared_ptr<slateobject> child, shared_ptr<slateobject> preserved_child)
{
	child_slateo->hide();
	preserved_child->hide();
	void *temp2=child_slateo->get_screen_ob();
	child_slateo->swap_connectedslates(child);
	preserve_after_lock->swap_connectedslates(preserved_child);
	preserve_after_lock.swap(preserved_child);
	child_slateo.swap(child);
	child->set_screen_ob(child_slateo->get_screen_ob());
	child_slateo->set_screen_ob(temp2);
}

void slate::swap_childobject(slate *swapslate)
{
	swap_childobject(swapslate->get_childobject(),swapslate->get_lockobject());
}

void slate::replace_childobject(slateobject *temp)
{
	if (child_slateo.use_count()!=0)
	{	
		child_slateo->cleanup();
	}
	if(temp!=0)
	{
		child_slateo.reset(temp);
	}
	else
	{
		child_slateo.reset();
	}
}

shared_ptr<slateobject> slate::get_childobject()
{
	return child_slateo;
}

shared_ptr<slateobject> slate::get_lockobject()
{
	return preserve_after_lock;
}

void slate::lock_slate()
{
	if (lockstate!=0)
	{
		preserve_after_lock.swap(child_slateo);
		lockstate=2;
		preserve_after_lock->hide();
		draw();
	}
}

void slate::unlock_slate()
{
	if (lockstate!=2)
	{
		child_slateo.swap(preserve_after_lock);
		lockstate=0;
		preserve_after_lock->hide();
		draw();
	}
}

int slate::fillslate(string progname)
{
	if (child_slateo.use_count()==0 || child_slateo->TYPE()==TYPE_emptyslate)
	{
		replace_childobject(create_windowobject(progname));
		draw();
		parent_viewport->fillslate_intern(slateid);
		
		return OP_success;
	}
	else
		return SL_not_empty;
}
int slate::fillsysslate()
{
	if (child_slateo.use_count()==0 || child_slateo->TYPE()==TYPE_emptyslate)
	{
		replace_childobject(create_sysobject());
		draw();
		parent_viewport->fillslate_intern(slateid);
		
		return OP_success;
	}
	else
		return SL_not_empty;
}

void slate::emptyslate()
{
	if (child_slateo!=0 && child_slateo->TYPE()!=TYPE_emptyslate)
			parent_viewport->emptyslate_intern(slateid);
	if (child_slateo.use_count()==0)
	{
		replace_childobject(create_emptyobject());
		draw();
	}
	else
		emptyslate_nonunique();
}

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
}

void slate::draw()
{
	child_slateo->draw();
}
void slate::hide()
{
	child_slateo->hide();
}

int slate::get_position_x()
{
	return position_x;
}

int slate::get_position_y()
{
	return position_y;
}
void slate::handle_input(void *initializer)
{
	child_slateo->handle_input(initializer);
}

void slate::handle_event(void *event)
{
	child_slateo->handle_event(event,false);
}