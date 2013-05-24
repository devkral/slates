// Licence see COPYING


#include "master.h"


using namespace std;

#ifdef UNIX
bool checkpassword(char *password)
{
	cerr << "password not implemented yet\n";
	return true;
}
#elif WINDOWS

bool checkpassword(char *password)
{
	cerr << "password not implemented yet\n";
	return true;
}
#endif



master::master()
{
}


master::~master()
{

}

void master::cleanup()
{
	stop_handling_input();
	while (viewport_pool.empty()!=true)
		destroyviewport();
}

void master::swapcontent(int viewportid1, long int slateid1,int viewportid2, long int slateid2)
{
	//viewport_pool[viewportid1]->slate_pool[slateid1]->swap_childobject(viewport_pool[viewportid2]->slate_pool[slateid2]);
}


//validate before calling
void master::createviewport()
{
	viewport_pool.push_back(create_viewport_intern(this,viewport_idcount));
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
	for (long int count=0; count<viewport_idcount; count++)
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



void master::start_handling_input()
{
	hasinputhandle=true;
	inputthread=thread(kickstarter_inputthread,(master *)this);
}

void master::stop_handling_input()
{
	if (hasinputhandle)
	{
		hasinputhandle=false;
		inputthread.join();
	}
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
		for (long int count=0; count<viewport_idcount; count++)
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


void kickstarter_inputthread(master *parent_object)
{
	parent_object->inputhandler_function();

}