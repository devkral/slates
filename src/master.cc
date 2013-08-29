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

int32_t master::amount_viewports()
{
	return viewport_pool.size();
}


void master::cleanup()
{
	while (viewport_pool.empty()!=true)
		destroyviewport();
}


viewport *master::get_viewport_by_id(int32_t viewportid)
{
	return viewport_pool[viewportid];

}


slate *master::get_slate_by_id(int32_t viewportid, int32_t slateid)
{
	return get_viewport_by_id(viewportid)->get_slate_by_id(slateid);
}

void master::swapcontent(int32_t viewportid1, int32_t slateid1,int32_t viewportid2, int32_t slateid2)
{
	slateareascreen *temp=get_slate_by_id(viewportid1,slateid1)->get_slatearea()->get_screen();
	get_slate_by_id(viewportid1,slateid1)->get_slatearea()->set_screen(get_slate_by_id(viewportid2,slateid2)->get_slatearea()->get_screen());
	get_slate_by_id(viewportid2,slateid2)->get_slatearea()->set_screen(temp);
}


//validate before calling
void master::createviewport(void *monitor)
{
	if (viewport_idcount==INT32_MAX)
	{
		cerr << "Reached maximal amount of viewports.\n";
		return;
	}
	viewport_pool.push_back(create_viewport_intern(this,viewport_idcount,monitor));
	viewport_pool[viewport_idcount]->addslice();
	viewport_idcount++;
}

//validate before calling
void master::destroyviewport()
{
	if (viewport_pool.size()==0)
	{
		cerr << "Tried to destroy viewport but viewport_pool empty\n";
		return;
	}
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
	for (int32_t count=0; count<viewport_idcount; count++)
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
	for (int32_t count=0; count<amount_viewports(); count++)
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


void handle_event_intern(viewport *viewportobject, void *event, uint8_t receiver)
{
	viewportobject->handle_event(event,receiver);

}

uint16_t master::handle_event(void *event)
{
	uint16_t status=handle_masterevent(event);
	if (status==EXP_ALL_VIEW)
	{
		vector<thread> threadpool_events;
		for (int32_t count=0; count<amount_viewports(); count++)
		{
			threadpool_events.push_back( thread(handle_event_intern,viewport_pool[count],event,0));
		}
		while (threadpool_events.empty()==false)
		{
			if (threadpool_events.back().joinable())
				threadpool_events.back().join();
			threadpool_events.pop_back();
		}
	}
	if (status==EXP_ACTIVE_SLATES)
	{
		vector<thread> threadpool_events;
		for (int32_t count=0; count<amount_viewports(); count++)
		{
			threadpool_events.push_back( thread(handle_event_intern,viewport_pool[count],event,2));
		}
		while (threadpool_events.empty()==false)
		{
			if (threadpool_events.back().joinable())
				threadpool_events.back().join();
			threadpool_events.pop_back();
		}
	}
	if (status==EXP_FOCUS_VIEW)
	{
		viewport_pool[get_focused_viewport ()]->handle_event(event,0);	
	}

	if (status==EXP_FOCUS_SLATE)
	{
		viewport_pool[get_focused_viewport ()]->handle_event(event,1);
	}

	
	if (status==ADD_SLICE)
	{
		viewport_pool[get_focused_viewport ()]->addslice();
	}
	if (status==REMOVE_SLICE)
	{
		viewport_pool[get_focused_viewport ()]->removeslice();
	}
	if (status==ACTIVATE_LOCK)
	{
		lock();
	}
	if (status==QUIT_DE)
	{
		throw (new cleanup_exception);
	}
	if (status==RELOAD_DE)
	{
		throw (new restart_exception);
	}
	return status;
}