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

void slate::swap_childobject(slateobject ** const child)
{
	slateobject *temp=child_slateo;
	void *temp2=temp->get_screen_ob();
	
	child_slateo=*child;
	*child=temp;

	(*child)->set_screen_ob(child_slateo->get_screen_ob());
	child_slateo->set_screen_ob(temp2);
}

slateobject ** const slate::get_childobject()
{
	return &child_slateo;
}

void slate::lock_slate()
{
	if (lockstate!=0)
	{
		preserve_after_lock=child_slateo;
		child_slateo=create_lockobject();
		lockstate=2;
	}
}

void slate::unlock_slate()
{
	if (lockstate!=2)
	{
		delete child_slateo;
		child_slateo=preserve_after_lock;
		lockstate=0;
	}
}

int slate::fillslate(string progname)
{
	if (child_slateo==0 || child_slateo->TYPE()==TYPE_emptyslate)
	{
		create_windowobject(progname);
		return OP_success;
	}
	else
		return SL_not_empty;
}


void slate::emptyslate()
{
	delete child_slateo;
	child_slateo=create_emptyobject();
}