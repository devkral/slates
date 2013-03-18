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

#include "master.h"

void master::swapcontent(int viewportid1, long int slateid1,int viewportid2, long int slateid2)
{
	viewport_pool[viewportid1]->slate_pool[slateid1]->swap_childobject(viewport_pool[viewportid2]->slate_pool[slateid2]->get_childobject());
}


master::~master()
{
	while (viewport_pool.empty()!=true)
		destroyviewport();
}


//validate before calling
void master::createviewport()
{
	viewport_pool.push_back(create_viewport_intern(this,viewport_idcount));
	viewport_pool[viewport_idcount]->addslice();
	viewport_idcount++;
}

//validate before calling
void master::destroyviewport()
{
	delete viewport_pool.back();
	viewport_pool.pop_back();
	viewport_idcount--;
}

void master::lock ()
{
	for (int count=0;count<viewport_idcount;count) //viewport_idcount is one higher than used id
		viewport_pool[count]->lock_all_intern();
}
int master::unlock ()
{
	if (1)
	{
		unlock_slates_intern();
	}
	else
		return PASSW_wrong;
}

void master::unlock_slates_intern()
{
	for (int count=0;count<viewport_idcount;count) //viewport_idcount is one higher than used id
		viewport_pool[count]->unlock_all_intern();
}