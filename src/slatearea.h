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


	//direction is flag 1 for North, 2 for East, 4 for South, 8 for West !!! bitshift!!!  default east south others implemented later
	//use 0 by default until other mechanics are implemented
	void reposition(int16_t x, int16_t y,int16_t w, int16_t h); 
	int8_t reposition_check(int16_t x, int16_t y,int16_t w, int16_t h); 
	
	//void move(int16_t x, int16_t y);  //swaps origin
	//void resizeluppercorner(int16_t w, int16_t h);
	//void resizerlowercorner(int16_t w, int16_t h);
	void update();
	slateareascreen *get_screen();
	void set_screen(slateareascreen *replace);
	
	virtual slateareascreen *create_emptyslate()=0;

	//virtual void handle_input(void *initializer)=0;
	
	void handle_event(void  *event);
		
	void setlock(uint8_t lockstate);
	
	int16_t get_x();
	int16_t get_y();
	int16_t get_w();
	int16_t get_h();
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
	int16_t width=1; //in slates
	int16_t height=1; //in slates
};

#endif // _SLATEAREA_H_

