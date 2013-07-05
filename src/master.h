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

using namespace std;



class master
{
public:
	master();
	virtual ~master();
	void createviewport();
	virtual viewport *create_viewport_intern(master *master_parent, int ownidd)=0;
	void destroyviewport();
	void cleanup();
	void swapcontent(int viewportid1, long int slateid1,int viewportid2, long int slateid2);
	void lock();
	bool unlock_slates(char *password);
	void start_handling_input();
	virtual void inputhandler_function()=0;
	void stop_handling_input();
	virtual int handle_event(void *event); //sometimes a better handler is needed
	virtual int handle_masterevent(void *event)=0; //returns true if handled by master return false if handled by slates


protected:
	vector<viewport*> viewport_pool;
	thread inputthread;
	bool hasinputhandle=false;
	timed_mutex protectmaster_eventhandle;
	
private:
	void unlock();
	int viewport_idcount=0;
};

extern void kickstarter_inputthread(master *parent_object);

#endif // _MASTER_H_

