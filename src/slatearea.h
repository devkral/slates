// Licence see COPYING


#ifndef _SLATEAREA_H_
#define _SLATEAREA_H_

#include <atomic>

#include "slate.h"
class slate;
class slateareascreen;
class lockslate;
class emptyslate;

#include "viewport.h"
class viewport;


#include <deque>

using namespace std;


class slatearea
{
public:
	slatearea(slate *parent_slate);
	virtual ~slatearea();
	void cleanup();
	void init();
	slate *get_origin();
	master *get_master();
	viewport *get_viewport();



	void reposition(int16_t x, int16_t y,int16_t w, int16_t h); 
	int8_t reposition_check(int16_t x, int16_t y,int16_t w, int16_t h); 
	
	void update();
	slateareascreen *get_screen();
	void set_screen(slateareascreen *replace);
	
	virtual slateareascreen *create_emptyslate()=0;
	virtual slateareascreen *create_lockslate()=0;

	//virtual void handle_input(void *initializer)=0;
	
	virtual void handle_event(void  *event);
		
	void setlock(uint8_t lockstate); //0 unlocked, 1 locked, (2 do not lock not implemented) (3 lock on unfocus not implemented)
	
	int16_t get_x();
	int16_t get_y();
	int16_t get_w();
	int16_t get_h();
	bool isfilled();
	bool get_isdestroying ();
	void update_isfilled();

	int32_t get_renderid(); //usable as check if rendered (-1=not rendered)
	void set_renderid(int32_t id);
	
protected:
	slateareascreen *child=0;
private:
	deque< deque<slate*> > connectedslates; //outer vector y inner x
	bool filledold=false;
	atomic<bool> isdestroying;
	//give this over to windowlist
	int16_t width=1; //in slates
	int16_t height=1; //in slates

	int32_t renderid=-1;
};

#endif // _SLATEAREA_H_

