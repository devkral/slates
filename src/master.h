// Licence see COPYING

#ifndef _MASTER_H_
#define _MASTER_H_
#include "viewport.h"
class viewport;
class slateobject;
//#include "slate.h"
//class slate;
//#include "slateobject.h"
//class slateobject;

#include "configbackend.h"

#include <vector>
#include <thread>
#include <mutex>


#include "slate.h"

using namespace std;



class master
{
public:
	master();
	virtual ~master();
	void createviewport(void *monitor=0);
	void destroyviewport();
	void cleanup();
	viewport *get_viewport_by_id (int32_t  id);
	slate *get_slate_by_id(int32_t idview, int32_t  idslate);
	void swapcontent(int32_t viewportid1, int32_t slateid1,int32_t viewportid2, int32_t slateid2);
	int32_t amount_viewports(); //in short: get all screens

	virtual int32_t get_focused_viewport()=0; 
	
	void lock();
	bool unlock_slates(char *password);
	virtual uint16_t handle_event(void *event); //sometimes a better handler is needed
	virtual uint16_t handle_masterevent(void *event)=0; //returns true if handled by master return false if handled by slates


protected:
	vector<viewport*> viewport_pool;
	virtual viewport *create_viewport_intern(master *master_parent, int32_t ownidd, void *monitor)=0;
	
private:
	void unlock();
	int32_t viewport_idcount=0;
};

extern void kickstarter_inputthread(master *parent_object);

#endif // _MASTER_H_

