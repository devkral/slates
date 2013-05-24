// Licence see COPYING


#ifndef _SLATEAREA_H_
#define _SLATEAREA_H_

#include "slate.h"
class slate;
//#include <slatetype.h>
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
	
	virtual slateareascreen *create_lockslate()=0;
	virtual slateareascreen *create_emptyslate()=0;

	virtual void handle_input(void *initializer)=0;
	
	void handle_event(void  *event);
		
	void lock();
	void unlock();
	
	int get_x();
	int get_y();
	bool isfilled();
	bool get_isondestruction ();
	void set_childslatearea(slatearea *replace);
	
protected:
	slatetype *child=0;
	bool hasinputhandle=false;
private:
	deque< deque<slate*> > connectedslates; //outer vector y inner x
	char lockstate=0; //0 normal 1 lock, 2 always_unlock,  (3 private_normal, 4 private_locked: not implemented)
	
	bool isondestruction=false;
	//give this over to windowlist
	int width=1; //in slates
	int height=1; //in slates
//	friend slateobject;
};


void kickstarter_drawthread(slatetype *parent)
{
	parent->draw_function ();
}

#endif // _SLATEAREA_H_

