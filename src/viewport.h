// Licence see COPYING

/**
 * viewport should be a monitor or something where windows can be shown fullscreen
 * 
 * */


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
#include <atomic>


using namespace std;



extern int32_t calcidslate(int16_t x, int16_t y);

class viewport
{
public:
	viewport(master *master_parent, int32_t viewportidtemp);
	virtual ~viewport();
	slate *get_slate(int16_t x, int16_t y);
	slate *get_slate_by_id(int32_t id);
	void addslice();
	int16_t removeslice();
	int32_t count_filled_slots(int16_t sliceid);
	void fill_slate_intern(int32_t id); //counter 
	void empty_slate_intern(int32_t id); //counter don't confuse with emptyslate
	virtual void handle_event(void *event, uint8_t receiver); //0=all, 1 focused, 2 active rendered
	void cleanup();
	void lock();
	void unlock();
	
	void update_slates();
	void async_destroy_slates(int32_t amount);
	void async_create_slates();
	
	master *get_master();

	int32_t get_viewport_id();
	int16_t get_slices();

	void set_viewport_size(int16_t width, int16_t height); //unit slates
	void set_viewport_begin(int16_t x, int16_t y); //unit slates
	int16_t get_viewport_width();
	int16_t get_viewport_height();
	int16_t get_viewport_beg_x();
	int16_t get_viewport_beg_y();
	bool get_isdestroying(); //superseeded by exceptions?

	void add_renderob(slatearea *renderob);
	void remove_renderob(int32_t renderid);
	slatearea *get_renderob(int32_t renderid);

	//don't forget negative BORDERSLATE
	virtual int32_t get_focused_slate_id()=0;
	slate * get_focused_slate();

	virtual void update_slice_info()=0;
	virtual slatearea *create_area(slate *parent_slate)=0;

protected:
	int32_t safe_slice=slices; //is max slice where it is safe to handle events
	mutex protrender; //is locked while slates update
	deque<slatearea*> render_pool; //pool with windows which must be rendered
	vector<slate*> slate_pool; //leftwing first, then diag then top wing
private:
	int16_t horizontal_tiles=-1;
	int16_t vertical_tiles=-1;
	int16_t view_beg_slate_x=0;
	int16_t view_beg_slate_y=0;
	int32_t viewportid;
	int16_t slices=0;
	int32_t slate_idcount=0; 
	mutex slateid_prot; //protects slateid
	int32_t amount_filled_slates;
	atomic<bool> isdestroying;
	//long int max_avail_slates=0; //=slice*slice-1=size-1 of slate_pool

	


	//deque<slatetype*> slatetype_pool;
	master *mroot;
	
	
	void lock_all_intern();
	void unlock_all_intern();
	
	//cache
	int32_t cache_last_diag_point_id=0;
	int32_t cache_nto_last_diag_point_id=0;
	
	//autoremove last slice
		//last slice
		int32_t last_slice_filled=0;
		int32_t id_last_beg=0;

		//next to last slice
		int32_t nto_last_slice_filled=0;
		int32_t id_nto_last_beg=0;


	
	friend master;
};



#endif // _VIEWPORT_H_

