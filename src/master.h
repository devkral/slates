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
	viewport *get_viewport_by_id (int id);
	slate *get_slate_by_id(int idview, long int idslate);
	void swapcontent(int viewportid1, long int slateid1,int viewportid2, long int slateid2);
	int countviewports(); //in short: get all screens
	
	void lock();
	bool unlock_slates(char *password);
	virtual int handle_event(void *event); //sometimes a better handler is needed
	virtual int handle_masterevent(void *event)=0; //returns true if handled by master return false if handled by slates


protected:
	vector<viewport*> viewport_pool;
	virtual viewport *create_viewport_intern(master *master_parent, int ownidd, void *monitor)=0;
	
private:
	void unlock();
	int viewport_idcount=0;
};

extern void kickstarter_inputthread(master *parent_object);

#endif // _MASTER_H_

