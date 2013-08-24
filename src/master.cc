// Licence see COPYING


#include "master.h"


using namespace std;


bool checkpassword(char *password)
{
#ifdef UNIX

	cerr << "password not implemented yet\n";
	return true;
#elif WINDOWS

	cerr << "password not implemented yet\n";
	return true;
#endif
}


master::master()
{
}


master::~master()
{

}

int master::amount_viewports()
{
	return viewport_pool.size();
}


void master::cleanup()
{
	while (viewport_pool.empty()!=true)
		destroyviewport();
}


viewport *master::get_viewport_by_id(int viewportid)
{
	return viewport_pool[viewportid];

}


slate *master::get_slate_by_id(int viewportid, long int slateid)
{
	return get_viewport_by_id(viewportid)->get_slate_by_id(slateid);
}

void master::swapcontent(int viewportid1, long int slateid1,int viewportid2, long int slateid2)
{
	slateareascreen *temp=get_slate_by_id(viewportid1,slateid1)->get_slatearea()->get_screen();
	get_slate_by_id(viewportid1,slateid1)->get_slatearea()->set_screen(get_slate_by_id(viewportid2,slateid2)->get_slatearea()->get_screen());
	get_slate_by_id(viewportid2,slateid2)->get_slatearea()->set_screen(temp);
}


//validate before calling
void master::createviewport(void *monitor)
{
	viewport_pool.push_back(create_viewport_intern(this,viewport_idcount,monitor));
	viewport_pool[viewport_idcount]->addslice();
	viewport_idcount++;
}

//validate before calling
void master::destroyviewport()
{
	viewport_pool.back()->cleanup();
	delete viewport_pool.back();
	viewport_pool.pop_back();
	viewport_idcount--;
}

void lock_intern(viewport *viewp)
{
	viewp->lock();
}

void master::lock()
{
	vector<thread> threadpool_lock;
	for (long int count=0; count<viewport_idcount; count++)
		threadpool_lock.push_back( thread(lock_intern,viewport_pool[count]));
	while (threadpool_lock.empty()==false)
	{
		if (threadpool_lock.back().joinable())
			threadpool_lock.back().join();
		threadpool_lock.pop_back();
	}
}
void unlock_intern(viewport *viewp)
{
	viewp->unlock();
}

void master::unlock()
{
	vector<thread> threadpool_unlock;
	for (long int count=0; count<amount_viewports(); count++)
		threadpool_unlock.push_back( thread(unlock_intern,viewport_pool[count]));
	while (threadpool_unlock.empty()==false)
	{
		if (threadpool_unlock.back().joinable())
			threadpool_unlock.back().join();
		threadpool_unlock.pop_back();
	}
}

bool master::unlock_slates (char *password)
{
	if (checkpassword(password))
	{
		unlock();
		return true;
	}
	else
		return false;
}

void handle_event_intern(viewport *viewportobject, void *event)
{
	viewportobject->handle_event(event);

}

int master::handle_event(void *event)
{
	int status=handle_masterevent(event);
	if (status==MASTER_UNHANDLED)
	{
		vector<thread> threadpool_events;
		for (long int count=0; count<amount_viewports(); count++)
		{
			threadpool_events.push_back( thread(handle_event_intern,viewport_pool[count],event));
		}
		while (threadpool_events.empty()==false)
		{
			if (threadpool_events.back().joinable())
				threadpool_events.back().join();
			threadpool_events.pop_back();
		}
	}
	return status;
}