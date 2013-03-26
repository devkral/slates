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
//#include "slateobject.h"
//class slateobject;

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
	viewport(master *masteridd, int ownidd);
	~viewport();
	slate *getslate(int x, int y);
	slate *getslate_by_id(long int id);
	void addslice();
	int removeslice();
	int count_filled_slots(int sliceid);
	void fillslate_intern(long int id); //counter 
	void emptyslate_intern(long int id); //counter
	void handle_event(void *event);
	void async_update_slates();
	
	void async_cleanup_slates(long int id_beg, long int id_end);
	void async_destroy_slates(long int amount);
	
	master *getmaster();

	void *get_viewport_screen();
	int get_id();
	int get_slices();
	void cleanup();

	void set_viewport(int width, int height); //unit slates
	int get_viewport_width();
	int get_viewport_height();

protected:
	//every display a viewport_screen
	void *viewport_screen=0;
	virtual void update_slice_change()=0;
private:
	int horizontal_tiles=-1;
	int vertical_tiles=-1;
	int ownid=0;
	int slices=0;
	void destroyslate();
	void createslate();
	long int slate_idcount=0;
	mutex slateid_prot;
	atomic<long int> amount_filled_slates;
	long int max_avail_slates=0; //=slice*slice
	vector<slate*> slate_pool; //leftwing first, then diag then top wing
	master *mroot;


	


	virtual slate *create_slate_intern(viewport *parent, long int id,int position_xtemp,int position_ytemp)=0;

	
	void lock_all_intern();
	void unlock_all_intern();
	virtual void destroy_mscreen_ob()=0;
	virtual void create_mscreen_ob()=0;
	
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

