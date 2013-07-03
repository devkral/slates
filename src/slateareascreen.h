// Licence see COPYING


#ifndef _SLATEAREASCREEN_H_
#define _SLATEAREASCREEN_H_


class master;
class slate;
class slatearea;

#include "constdef.h"

using namespace std;


class slateareascreen
{
public:

	slateareascreen(master *parent_mastert);
	virtual ~slateareascreen();

	virtual void handle_event(void *event); //needn't to be implemented if there is an other solution
	//be carefull: if not called by input don't send something to an alleventhandler
	//virtual void handle_input(void *initializer); //needn't to be implemented if there is an other solution
	virtual void update()=0;
	//void init();
	//void cleanup();
	//virtual void draw_function(); //for kickstarter
	/** implementation idea:
	 * init with creation
	 * stop with destruction
	 * hide/draw via update and slateareas isvisible state
	 */
	master *get_master();
	virtual bool isstatic();
	virtual bool isdirty();
	virtual bool islocked();
	void setlock(int lockstate);
	long int get_renderid();
	void set_renderid(long int id);
	virtual char TYPE()=0;

	void swap_slatearea (slatearea *newparent); //just works if same viewport
	slatearea *get_slatearea ();

protected:

private:
	master *parent_master=0;
	long int renderid=-1;
	char curlockstate=0; //0 normal 1 lock, 2 always_unlock,  (3 private_normal, 4 private_locked: not implemented)
	slatearea *parent=0;
	//TODO: Overlay for move/swap/etc

};

#endif // _SLATEAREASCREEN_H_

