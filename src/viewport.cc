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

#include "viewport.h"


long int calcidslate(long int x, long int y)
{
	long int diagrefpoint;
	long int fromrefpoint;
	long int result;
	if (x<y)
	{
		diagrefpoint=y*y+y;  //begin from zero so (y+1)*(y+1)-y-1
		fromrefpoint=y-x;
		result=diagrefpoint-fromrefpoint;
	}
	else
	{
		diagrefpoint=x*x+x; //begin from zero same calculation
		fromrefpoint=x-y;
		result=diagrefpoint+fromrefpoint;
	}
	return result;
}

viewport::viewport(master *masteridd, int ownidd)
{
	mroot=masteridd;
	ownid=ownidd;
}

viewport::~viewport()
{
	while (slate_pool.empty()!=true)
		destroyslate();
}


slate *viewport::getslate(int x, int y)
{
	if (x<0 || y<0)
	{
		cerr << "Error: x or y lower than 0, x:" << x << " y:" << y << endl;
		return 0;
	}
	int validate=calcidslate(x, y);
	if (validate>max_avail_slates-1)
	{
		cerr << "Error: x or y greater than available slates, x:" << x << " y:" << y << endl;
		return 0;
	}
	return slate_pool[validate];

}


//validate before calling
void viewport::createslate()
{
	int temp_x, temp_y;
	
	if (slate_idcount<slices*slices-slices)
	{
		temp_y=slices;
		temp_x=cache_last_diag_point_id;
	}
	else
	{
		temp_y=cache_last_diag_point_id;
		temp_x=slices;
	}

	slate_pool.push_back(create_slate_intern(this,slate_idcount, temp_x, temp_y));
	slate_pool[slate_idcount]->init_slate();
	slate_idcount++;
}

//validate before calling
void viewport::destroyslate()
{
	delete slate_pool.back();
	slate_pool.pop_back();
	slate_idcount--;
}

int viewport::count_filled_slots(int sliceid)
{
	int temp=0;
	long int count=0;
	for (count=0;count<sliceid+sliceid;count++) //slices+slices+1 but begins with 0 so not needed
		if (slate_pool[sliceid+sliceid-count]->isfilled()==true)
			temp++;
	return temp;
}

void viewport::addslice()
{
	slices++;
	max_avail_slates=slices*slices;
	cache_last_diag_point_id=slices*slices-slices;
	nto_last_slate_filled=last_slate_filled;
	last_slate_filled=0;
	long int count=0;
	for (count=0;count<slices+slices-1;count++) //=(slices+1)+(slices+1)-1
		createslate();
}

int viewport::removeslice()
{
	if (last_slate_filled>0)
		return SL_destroy_failed;

	long int count=0;
	for (count=0;count<slices+slices-1;count++) //=(slices+1)+(slices+1)-1
		destroyslate();
	slices--;
	max_avail_slates=slices*slices;
	cache_last_diag_point_id=slices*slices-slices;
	last_slate_filled=nto_last_slate_filled;
	nto_last_slate_filled=count_filled_slots(slices-1);
	return OP_success;
}
master *viewport::getmaster()
{
	return mroot;
}

void viewport::lock_all_intern()
{
	for (long int count=0;count<max_avail_slates;count++)
		(slate_pool[count])->lock_slate();
}

void viewport::unlock_all_intern()
{
	for (long int count=0;count<max_avail_slates;count++)
		(slate_pool[count])->unlock_slate();
}