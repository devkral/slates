// Licence see COPYING

#ifndef _MASTER_H_
#define _MASTER_H_
#include "viewport.h"
class viewport;
class slateobject;
#include "slate.h"
//class slate;

#include "configbackend.h"

#include <vector>


using namespace std;

class cleanup_exception
{


};

class restart_exception
{


};

class master
{
public:
	master();
	virtual ~master();
	void createviewport(void *monitor=0);
	void destroyviewport(int16_t viewid);
	virtual void init(int argc, char *argv[])=0;
	void cleanup();
	viewport *get_viewport_by_id (int16_t  id);
	slate *get_slate_by_id(int16_t idview, int32_t  idslate);
	void swapcontent(int16_t viewportid1, int32_t slateid1,int16_t viewportid2, int32_t slateid2);
	int16_t amount_viewports(); //in short: get all screens

	virtual int16_t get_focused_viewport_id()=0; 
	viewport * get_focused_viewport();
	
	virtual bool is_system_mode()=0; //e.g. is border active
	void lock();
	bool unlock_slates(char *password);
	virtual uint16_t handle_event(void *event); //sometimes a better handler is needed
	virtual uint16_t handle_masterevent(void *event)=0; //returns true if handled by master return false if handled by slates


protected:
	vector<viewport*> viewport_pool;
	virtual viewport *create_viewport_intern(master *master_parent, int16_t ownidd, void *monitor)=0;
	
private:
	void unlock();
	int16_t viewport_idcount=0;
};

#endif // _MASTER_H_

