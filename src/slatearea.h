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
	void move(int x, int y);  //swaps origin
	slate *get_origin();
	master *get_master();
	viewport *get_viewport();
	
	void resize(int w, int h);
	//void resizeleftuppercorner(int x_delta, int y_delta);
	//void resizerightlowercorner(int x_delta, int y_delta);
	void update();
	slateareascreen *get_screen();
	void set_screen(slateareascreen *replace);
	
	virtual slateareascreen *create_emptyslate()=0;

	virtual void handle_input(void *initializer)=0;
	
	void handle_event(void  *event);
		
	void setlock(int lockstate);
	
	int get_x();
	int get_y();
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
	int width=1; //in slates
	int height=1; //in slates
};

#endif // _SLATEAREA_H_

