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

viewport::viewport(master *masteridd, int ownidd) : slateid_prot()
{
	mroot=masteridd;
	ownid=ownidd;
	amount_filled_slates=0;
}

viewport::~viewport()
{
	
}
void viewport::cleanup()
{
	async_destroy_slates(max_avail_slates);
	destroy_mscreen_ob();
}


int viewport::get_viewport_width()
{
	if (horizontal_tiles<=0)
		return slices;
	else
		return horizontal_tiles;
}

int viewport::get_viewport_height()
{
	if (vertical_tiles<=0)
		return slices;
	else
		return vertical_tiles;
}

void viewport::set_viewport(int width, int height)
{
	if (width>=slices)
		horizontal_tiles=-1;
	else if (width<=0)
		horizontal_tiles=1;
	else
		horizontal_tiles=width;

	if (height>=slices)
		vertical_tiles=-1;
	else if (height<=0)
		vertical_tiles=1;
	else
		vertical_tiles=height;
	async_update_slates();
}


slate *viewport::getslate(int x, int y)
{
	if (x<0 || y<0)
	{
		cerr << "Error: x or y lower than 0, x:" << x << " y:" << y << endl;
		return 0;
	}
	int validate=calcidslate(x, y);
	if (validate>=max_avail_slates)
	{
		cerr << "Error: x or y greater than available slates, x:" << x << " y:" << y << endl;
		return 0;
	}
	return slate_pool[validate];

}

slate *viewport::getslate_by_id(long int id)
{
	if (id<0 || id>=max_avail_slates)
	{
		cerr << "Error: id out of range " << id  << endl;
		return 0;
	}
	return slate_pool[id];

}


//validate before calling
//update slices, caches, id_nto_last_beg, id_last_beg,
void viewport::createslate()
{
	slateid_prot.lock();
	int temp_x, temp_y;
	slate *verify;
	if (slate_idcount<slices*slices-slices)
	{
		temp_y=slices-1;
		temp_x=slate_idcount-id_last_beg;
	}
	else
	{
		temp_y=(cache_last_diag_point_id+(slices-1))-slate_idcount; //sure???
		temp_x=slices-1;
	}
	verify=create_slate_intern(this,slate_idcount, temp_x, temp_y);
	assert(verify);
		
	slate_pool.push_back(verify);
	slate_pool[slate_idcount]->init_slate();
	slate_idcount++;
	slateid_prot.unlock();
}

//validate before calling
void viewport::destroyslate()
{
	slateid_prot.lock();
	slate_pool.back()->cleanup();
	delete slate_pool.back();
	slate_pool.pop_back();
	slate_idcount--;;
	slateid_prot.unlock();
}

void async_update_slates_intern(slate *targob)
{
	targob->update();
}

void viewport::async_update_slates()
{	
	update_slice_info();
	vector<thread> temppool;
	for (long int count=0;count<max_avail_slates;count++)
	{
		temppool.push_back(thread(async_update_slates_intern,slate_pool[count]));
	}
	while (temppool.empty()==false)
	{
		temppool.back().join();
		temppool.pop_back();
	}
}

void async_destroy_slates_intern(slate *targob)
{
	targob->cleanup();
	delete targob;
}

void viewport::async_destroy_slates(long int amount)
{
	slateid_prot.lock();
	slate_idcount-=amount;
	vector<thread> temppool;
	for (long int count=0;count<amount;count++)
	{
		temppool.push_back(thread(async_destroy_slates_intern,slate_pool.back()));
		slate_pool.pop_back();
	}
	while (temppool.empty()==false)
	{
		temppool.back().join();
		temppool.pop_back();
	}
	slateid_prot.unlock();
}

void async_cleanup_slates_intern(slate *targob)
{
	targob->cleanup();
}

void viewport::async_cleanup_slates(long int id_beg, long int id_end)
{
	vector<thread> temppool;
	for (long int count=id_beg;count<id_end;count++)
		temppool.push_back(thread(async_cleanup_slates_intern,slate_pool[count]));
	while (temppool.empty()==false)
	{
		temppool.back().join();
		temppool.pop_back();
	}
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
	cache_nto_last_diag_point_id=cache_last_diag_point_id;
	cache_last_diag_point_id=slices*slices-slices;
	id_nto_last_beg=id_last_beg;
	id_last_beg=cache_last_diag_point_id-(slices-1);
	nto_last_slice_filled=last_slice_filled;
	last_slice_filled=0;
	
	update_slice_info();
	for (long int count=0;count<slices+slices-1;count++) //=(slices+1)+(slices+1)-1
		createslate();
	async_update_slates();
}

int viewport::removeslice()
{
	if (last_slice_filled>0 || nto_last_slice_filled >= (slices-1)+(slices-1)) //just one free slot
		return SL_destroy_failed;
	
	async_destroy_slates(slices+slices-1); //=(slices+1)+(slices+1)-1
	slices--;
	max_avail_slates=slices*slices;
	cache_last_diag_point_id=cache_nto_last_diag_point_id;
	cache_nto_last_diag_point_id=(slices-1)*(slices-1)-(slices-1);
	id_last_beg=id_nto_last_beg;
	id_nto_last_beg=cache_nto_last_diag_point_id-(slices-2);
	last_slice_filled=nto_last_slice_filled;
	nto_last_slice_filled=count_filled_slots(slices-1);
	
	async_update_slates();
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


void viewport::fillslate_intern(long int id)
{
	amount_filled_slates++;
	
	if (id>=id_last_beg)
		last_slice_filled++;
	else if (id>=id_nto_last_beg)
			nto_last_slice_filled++;
	
	if (amount_filled_slates>=max_avail_slates)
	{
		if (amount_filled_slates>max_avail_slates)
			cerr << "Debug: amount_filled_slates " << amount_filled_slates-max_avail_slates << "bigger than max_avail_slates" << endl; 
		addslice();
	}
}

void viewport::emptyslate_intern(long int id)
{
	amount_filled_slates--;
	if (id>=id_last_beg)
	{
		last_slice_filled--;
		removeslice();  //has protective routine
						//here because should be triggered just if the last slice changes
	}
	else if (id>=id_nto_last_beg)
			nto_last_slice_filled--;
	
}

void *viewport::get_viewport_screen()
{
	return viewport_screen;
}

int viewport::get_id()
{
	return ownid;
}

int viewport::get_slices()
{
	return slices;
}



void viewport::handle_event(void *event)
{
	for (long int count=0;count<max_avail_slates;count++)
		slate_pool[count]->handle_event(event);
}