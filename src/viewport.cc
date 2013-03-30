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

viewport::viewport(master *master_parent,int viewportidtemp)
{
	viewportid=viewportidtemp;
	mroot=master_parent;
	amount_filled_slates=0;
}

viewport::~viewport()
{
	
}
void viewport::cleanup()
{
	async_destroy_slates(max_avail_slates);
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

void viewport::set_viewport_size(int width, int height)
{
	if (width>=slices)
		horizontal_tiles=-1;
	else if (width<1)
		horizontal_tiles=1;
	else
		horizontal_tiles=width;

	if (height>=slices)
		vertical_tiles=-1;
	else if (height<1)
		vertical_tiles=1;
	else
		vertical_tiles=height;
	update_slice_info();
	async_update_slates();
}

int viewport::get_viewport_beg_x()
{
	return view_beg_slate_x;
}

int viewport::get_viewport_beg_y()
{
	return view_beg_slate_y;
}

void viewport::set_viewport_begin(int x, int y)
{
	if (x<0)
		view_beg_slate_x=0;
	if (x<slices)
		view_beg_slate_x=x;

	if (y<0)
		view_beg_slate_y=0;
	if (y<slices)
		view_beg_slate_y=y;
	update_slice_info();
	async_update_slates();
}


slate *viewport::get_slate(int x, int y)
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

slate *viewport::get_slate_by_id(long int id)
{
	if (id<0 || id>=max_avail_slates)
	{
		cerr << "Error: id out of range " << id  << endl;
		return 0;
	}
	return slate_pool[id];

}

void async_update_slates_intern(slate *targob)
{
	assert(targob);
	targob->update();
}

void viewport::async_update_slates()
{	
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

void async_create_slates_intern(slate *placeholderpointer)
{
	assert(placeholderpointer);
	placeholderpointer->init();
}

void viewport::async_create_slates()
{
	if(slateid_prot.try_lock())
	{
		vector<thread> temppool;
		int temp_x, temp_y;
		while (slate_idcount<slices*slices-slices)
		{
			temp_y=slices-1;
			temp_x=slate_idcount-id_last_beg;

			//warning synchronize this in both while loops
			slate *placeholderpointer=new slate(this,slate_idcount,temp_x,temp_y); 
			slate_pool.push_back(placeholderpointer);
			temppool.push_back(thread(async_create_slates_intern,placeholderpointer));
		
			slate_idcount++;
		}
		while (slate_idcount<max_avail_slates)
		{
			temp_y=(cache_last_diag_point_id+(slices-1))-slate_idcount; //sure???
			temp_x=slices-1;

			slate *placeholderpointer=new slate(this,slate_idcount,temp_x,temp_y); 
			slate_pool.push_back(placeholderpointer);
			temppool.push_back(thread(async_create_slates_intern,placeholderpointer));

			slate_idcount++;

		}
	
		while (temppool.empty()==false)
		{
			temppool.back().join();
			temppool.pop_back();
		}
		slateid_prot.unlock();
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
	vector<thread> temppool;
	for (long int count=0;count<amount;count++)
	{
		temppool.push_back(thread(async_destroy_slates_intern,slate_pool.back()));
		slate_pool.pop_back();
		slate_idcount--;
	}
	while (temppool.empty()==false)
	{
		temppool.back().join();
		temppool.pop_back();
	}
	slateid_prot.unlock();
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
	async_create_slates();
//	for (long int count=0;count<slices+slices-1;count++) //=(slices+1)+(slices+1)-1
//		createslate();
	async_update_slates();
}

int viewport::removeslice()
{
	if (last_slice_filled>0 || nto_last_slice_filled >= (slices-1)+(slices-1)) //just one free slot
	{
		return SL_destroy_failed;
	}
	async_destroy_slates(slices+slices-1); //=(slices+1)+(slices+1)-1
	slices--;
	max_avail_slates=slices*slices;
	cache_last_diag_point_id=cache_nto_last_diag_point_id;
	cache_nto_last_diag_point_id=(slices-1)*(slices-1)-(slices-1);
	id_last_beg=id_nto_last_beg;
	id_nto_last_beg=cache_nto_last_diag_point_id-(slices-2);
	last_slice_filled=nto_last_slice_filled;
	nto_last_slice_filled=count_filled_slots(slices-1);

	update_slice_info();
	async_update_slates();
	return OP_success;
}
master *viewport::get_master()
{
	return mroot;
}

void lock_intern(slate *temp)
{
	temp->lock();
}

void viewport::lock()
{
	vector<thread> temppool;
	for (long int count=0;count<amount_filled_slates;count++)
	{
		if (slate_pool[count]->isorigin())
			temppool.push_back(thread(lock_intern,slate_pool[count]));
	}
	while (temppool.empty()==false)
	{
		temppool.back().join();
		temppool.pop_back();
	}
}

void unlock_intern(slate *temp)
{
	temp->unlock();
}

void viewport::unlock()
{
	vector<thread> temppool;
	for (long int count=0;count<amount_filled_slates;count++)
	{
		if (slate_pool[count]->isorigin())
			temppool.push_back(thread(unlock_intern,slate_pool[count]));
		
	}
	while (temppool.empty()==false)
	{
		temppool.back().join();
		temppool.pop_back();
	}
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

int viewport::get_viewport_id()
{
	return viewportid;
}

int viewport::get_slices()
{
	return slices;
}


void handle_event_intern(slate *slateob, void *event)
{
	slateob->handle_event(event);
}
void viewport::handle_event(void *event)
{
	vector<thread> threadpool_events;
	for (long int count=0;count<max_avail_slates;count++)
	{
		if (slate_pool[count]->isorigin())
		{
			threadpool_events.push_back( thread(handle_event_intern,slate_pool[count],event));
		}
	}
	while (threadpool_events.empty()==false)
	{
		if (threadpool_events.back().joinable())
			threadpool_events.back().join();
		threadpool_events.pop_back();
	}
}