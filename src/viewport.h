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

#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_
#include "master.h"
class master;
#include "slate.h"
class slate;
#include "slatetype.h"
class slatetype;

class slatearea;

#include "constdef.h"

#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>



using namespace std;



extern long int calcidslate(long int x, long int y);

class viewport
{
public:
	viewport(master *master_parent, int viewportidtemp);
	virtual ~viewport();
	slate *get_slate(int x, int y);
	slate *get_slate_by_id(long int id);
	void addslice();
	int removeslice();
	int count_filled_slots(int sliceid);
	void fillslate_intern(long int id); //counter 
	void emptyslate_intern(long int id); //counter
	void handle_event(void *event);
	void cleanup();
	void lock();
	void unlock();
	
	void async_update_slates();
	void async_destroy_slates(long int amount);
	void async_create_slates();
	
	master *get_master();

	int get_viewport_id();
	int get_slices();

	void set_viewport_size(int width, int height); //unit slates
	void set_viewport_begin(int x, int y); //unit slates
	int get_viewport_width();
	int get_viewport_height();
	int get_viewport_beg_x();
	int get_viewport_beg_y();


	virtual void *get_viewportscreen()=0;
	virtual void update_slice_info()=0;
	virtual slatearea *create_area(slate *parent_slate)=0;
	

protected:
	
private:
	int horizontal_tiles=-1;
	int vertical_tiles=-1;
	int view_beg_slate_x=0;
	int view_beg_slate_y=0;
	int viewportid;
	int slices=0;
	long int slate_idcount=0;
	mutex slateid_prot;
	atomic<long int> amount_filled_slates;
	long int max_avail_slates=0; //=slice*slice
	vector<slate*> slate_pool; //leftwing first, then diag then top wing
	//deque<slatetype*> slatetype_pool;
	master *mroot;
	
	
	void lock_all_intern();
	void unlock_all_intern();
	
	//cache
	long int cache_last_diag_point_id=0;
	long int cache_nto_last_diag_point_id=0;
	
	//autoremove last slice
		//last slice
		int last_slice_filled=0;
		long int id_last_beg=0;

		//next to last slice
		int nto_last_slice_filled=0;
		long int id_nto_last_beg=0;
	friend master;
};

#endif // _VIEWPORT_H_

