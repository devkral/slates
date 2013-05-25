// Licence see COPYING


#ifndef _SLATE_H_
#define _SLATE_H_
//#include "master.h"
//class master;
#include "viewport.h"
class viewport;
#include "slatearea.h"
class slatearea;

#include "constdef.h"

#include <memory>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

class slate
{
public:
	slate (viewport *parent,long int id, int position_xtemp,int position_ytemp);
	virtual ~slate();
	void cleanup();
	void init();
	bool isfilled();
	void update_isfilled(bool state);
	master *get_master();
	viewport *get_viewport();
	void setlock(int lockstate);
	void create_area();
	void replace_area(slatearea *newarea);
	void update();
	int get_x();
	int get_y();
	int get_id();
	void handle_input(void *initializer);
	void handle_event(void *event);
	
	bool isorigin();
	slatearea *get_slatearea();
	void set_slatearea(slatearea *parent);
	
protected:
	mutex change_slate; //
private:
	int position_x;
	int position_y;
	long int slateid;
	viewport *parent_viewport=0;
	slatearea *child=0;

};
#endif // _SLATE_H_

