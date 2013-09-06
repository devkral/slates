// Licence see COPYING


#ifndef _SLATEAREASCREEN_H_
#define _SLATEAREASCREEN_H_


class master;
class slate;
class slatearea;
class viewport;

#include "configbackend.h"

using namespace std;


class slateareascreen
{
public:

	slateareascreen(slatearea *parentt, master *parent_mastert);
	virtual ~slateareascreen();

	virtual void handle_event(void *event); //needn't to be implemented if there is an other solution
	//be carefull: if not called by input don't send something to an alleventhandler
	virtual void update()=0;
	master *get_master();
	viewport *get_viewport();
	virtual bool isdirty()=0; //shall be rendered
	virtual bool islocked();
	void setlock(uint8_t lockstate);
	virtual uint8_t TYPE()=0;

	void swap_slatearea (slatearea *newparent); //just works if same viewport?, updated but not tested
	slatearea *get_slatearea ();

protected:

private:
	master *parent_master=0;
	uint8_t curlockstate=0; //0 normal 1 lock, 2 always_unlock,  (3 private_normal, 4 private_locked: not implemented)
	slatearea *parent=0;
	//TODO: Overlay for move/swap/etc

};

#endif // _SLATEAREASCREEN_H_

