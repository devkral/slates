// Licence see COPYING

#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_
class master;
class slate;
class slateareascreen;

class slatearea;

#include "configbackend.h"

#include <vector>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>


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
	void fill_slate_intern(long int id); //counter 
	void empty_slate_intern(long int id); //counter don't confuse with emptyslate
	void handle_event(void *event);
	void cleanup();
	void lock();
	void unlock();
	
	void update_slates();
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
	bool get_isdestroying();

	void add_renderob(slateareascreen *renderob);
	void remove_renderob(long int renderid);
	slateareascreen *get_renderob(long int renderid);
	void rendering();
	virtual void render(slateareascreen *renderob)=0; 

	virtual void update_slice_info()=0;
	virtual slatearea *create_area(slate *parent_slate)=0;

protected:
	static void kickstarter_renderthread (viewport *renderingob);
private:
	int horizontal_tiles=-1;
	int vertical_tiles=-1;
	int view_beg_slate_x=0;
	int view_beg_slate_y=0;
	int viewportid;
	int slices=0;
	long int slate_idcount=0;
	mutex slateid_prot;
	long int amount_filled_slates;
	bool isdestroying=false;
	//long int max_avail_slates=0; //=slice*slice=size-1 of slate_pool
	vector<slate*> slate_pool; //leftwing first, then diag then top wing

	deque<slateareascreen*> render_pool;

	

	mutex protrender;
	thread renderthread;
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

