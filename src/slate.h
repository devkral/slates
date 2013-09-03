// Licence see COPYING


#ifndef _SLATE_H_
#define _SLATE_H_
//#include "master.h"
//class master;
#include "viewport.h"
class viewport;
#include "slatearea.h"
class slatearea;

#include "configbackend.h"

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
	void update();
	int16_t get_x();
	int16_t get_y();
	int32_t get_id();
	void handle_event(void *event);
	
	bool isorigin();
	
	void free_slate();
	void annect_slate(slatearea *newarea);
	slatearea *get_slatearea();
	
protected:
	mutex change_slate; //
private:
	int16_t position_x;
	int16_t position_y;
	int32_t slateid;
	viewport *parent_viewport=0;
	slatearea *child=0;
	bool isready=false;

};
#endif // _SLATE_H_

