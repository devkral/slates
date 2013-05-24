// Licence see COPYING


#ifndef _SLATEAREASCREEN_H_
#define _SLATEAREASCREEN_H_

#include "master.h"
class master;
class slate;
class slatearea;

#include "constdef.h"

#include <thread>
using namespace std;


class slateareascreen
{
public:

	slateareascreen(master *parent_mastert);
	virtual ~slatetype();

	virtual void handle_event(void *event); //needn't to be implemented if there is an other solution
	//be carefull: if not called by input don't send something to an alleventhandler
	//virtual void handle_input(void *initializer); //needn't to be implemented if there is an other solution
	virtual void update()=0;
	void init();
	void cleanup();
	//virtual void draw_function(); //for kickstarter
	/** implementation idea:
	 * init with creation
	 * stop with destruction
	 * hide/draw via update and slateareas isvisible state
	 */
	master *get_master();
	virtual void set_slatearea(slatearea *in)=0;
	slatearea *get_slatearea();
	//virtual void set_visibility(bool t)=0;
	virtual bool isstatic();
	long int get_renderid();
	void set_renderid(long int id);
	virtual char TYPE()=0;
protected:
	slatearea *parent=0;
	atomic<bool> dirty;
private:
	master *parent_master=0;
	long int renderid=-1;

};
extern void kickstarter_drawthread(slatetype *parent);

#endif // _SLATEAREASCREEN_H_

