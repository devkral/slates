// Licence see COPYING


#ifndef _SLATEAREA_H_
#define _SLATEAREA_H_

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

	
	//void move(int16_t x, int16_t y);  //swaps origin
	//void resize(int16_t w, int16_t h);
	//void resizeleftuppercorner(int x_delta, int y_delta);
	//void resizerightlowercorner(int x_delta, int y_delta);
	void update();
	slateareascreen *get_screen();
	void set_screen(slateareascreen *replace);
	
	virtual slateareascreen *create_emptyslate()=0;

	//virtual void handle_input(void *initializer)=0;
	
	void handle_event(void  *event);
		
	void setlock(uint8_t lockstate);
	
	int32_t get_x();
	int32_t get_y();
	int32_t get_w();
	int32_t get_h();
	bool isfilled();
	bool get_isdestroying ();
	void update_isfilled();
	
protected:
	slateareascreen *child=0;
	bool hasinputhandle=false;
private:
	deque< deque<slate*> > connectedslates; //outer vector y inner x
	bool filledold=false;
	bool isdestroying=false;
	//give this over to windowlist
	int32_t width=1; //in slates
	int32_t height=1; //in slates
};

#endif // _SLATEAREA_H_

