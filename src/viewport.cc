// Licence see COPYING


#include "viewport.h"


#include "slateareascreen.h"
#include "slate.h"
#include "master.h"

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
	isdestroying=true;
}
void viewport::cleanup()
{
	isdestroying=true;
	slateid_prot.lock();
	async_destroy_slates(slate_pool.size()-1);
}

int viewport::get_viewport_width()
{
	if (horizontal_tiles<=0)
		return slices;
	else
		return horizontal_tiles;
}
bool viewport::get_isdestroying()
{
	return isdestroying;
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
	update_slates();
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
	update_slates();
}


slate *viewport::get_slate(int x, int y)
{
	if (x<0 || y<0)
	{
		cerr << "Error: x or y lower than 0, x:" << x << " y:" << y << endl;
		return 0;
	}
	int validate=calcidslate(x, y);
	if (validate>=slate_pool.size())
	{
		cerr << "Error: x or y greater than available slates, x:" << x << " y:" << y << endl;
		return 0;
	}
	return slate_pool[validate];

}

slate *viewport::get_slate_by_id(long int id)
{
	if (id<0 || id>=slate_pool.size())
	{
		cerr << "Error: id out of range " << id  << endl;
		return 0;
	}
	return slate_pool[id];

}

void viewport::update_slates()
{	
	if (get_isdestroying())
		return;
	protrender.lock();
	for (long int count=0;count<slate_pool.size();count++)
	{
		slate_pool[count]->update();
	}
	protrender.unlock();
}

void async_create_slates_intern(slate *placeholderpointer)
{
	assert(placeholderpointer);
	placeholderpointer->init();
}

void viewport::async_create_slates()
{
	if (get_isdestroying())
		return;
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
	while (slate_idcount<slices*slices) //don't use slate_pool.size() endless loop
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
		
}


void async_destroy_slates_intern(slate *targob)
{
	if(targob)
	{
		targob->cleanup();
		delete targob;
		targob=0;
	}
}

void viewport::async_destroy_slates(long int amount)
{
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
	if (get_isdestroying())
		return;
	if(slateid_prot.try_lock())
	{
		slices++;
		//max_avail_slates=slices*slices;
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
		update_slates();
		slateid_prot.unlock();
	}
}

int viewport::removeslice()
{
	if (get_isdestroying() || last_slice_filled>0 || nto_last_slice_filled >= (slices-1)+(slices-1)) //just one free slot
	{
		return SL_destroy_failed;
	}
	if(slateid_prot.try_lock())
	{
		async_destroy_slates(slices+slices-1); //=(slices+1)+(slices+1)-1
		slices--;
		//max_avail_slates=slices*slices;
		cache_last_diag_point_id=cache_nto_last_diag_point_id;
		cache_nto_last_diag_point_id=(slices-1)*(slices-1)-(slices-1);
		id_last_beg=id_nto_last_beg;
		id_nto_last_beg=cache_nto_last_diag_point_id-(slices-2);
		last_slice_filled=nto_last_slice_filled;
		nto_last_slice_filled=count_filled_slots(slices-1);

		update_slice_info();
		update_slates();
		slateid_prot.unlock();
		return OP_success;
	}
	return SL_destroy_failed;
}
master *viewport::get_master()
{
	return mroot;
}


void viewport::lock()
{
	if (get_isdestroying())
		return;
	for (long int count=0;count<slate_pool.size();count++)
	{
		if (slate_pool[count]->isorigin())
			slate_pool[count]->setlock(1);
	}
}

void viewport::unlock()
{
	if (get_isdestroying())
		return;
	for (long int count=0;count<slate_pool.size();count++)
	{
		if (slate_pool[count]->isorigin())
			slate_pool[count]->setlock(0);
	}
}

void viewport::fill_slate_intern(long int id)
{
	amount_filled_slates++;
	
	if (id>=id_last_beg)
		last_slice_filled++;
	else if (id>=id_nto_last_beg)
			nto_last_slice_filled++;
	
	if (amount_filled_slates>=slate_pool.size()-1)
	{
		if (amount_filled_slates>=slate_pool.size())
			cerr << "Debug: amount_filled_slates " << amount_filled_slates << "bigger than slate_pool" << endl; 
		addslice();
	}
}

void viewport::empty_slate_intern(long int id)
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
	for (long int count=0;count<slate_pool.size();count++)
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


void viewport::add_renderob(slateareascreen *renderob)
{
	protrender.lock();
	renderob->set_renderid (render_pool.size()); //nice hack: size must be one less before adding
	render_pool.push_back(renderob);
	protrender.unlock();
}
void viewport::remove_renderob(long int renderid)
{
	protrender.lock();
	render_pool[renderid]->set_renderid (-1);
	render_pool.erase(render_pool.begin()+renderid);
	protrender.unlock();
}


slateareascreen *viewport::get_renderob(long int renderid)
{
	return render_pool[renderid];
}