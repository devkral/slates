/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
 * Copyright (C) 2013 alex <devkral@web.de>
 * 
 * slates is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * slates is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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






master::~master()
{
	stop_handling_input();
}

void master::swapcontent(int viewportid1, long int slateid1,int viewportid2, long int slateid2)
{
	viewport_pool[viewportid1]->slate_pool[slateid1]->swap_childobject(viewport_pool[viewportid2]->slate_pool[slateid2]);
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
void master::cleanup()
{
	while (viewport_pool.empty()!=true)
		destroyviewport();
}

void master::lock ()
{
	for (int count=0;count<viewport_idcount;count) //viewport_idcount is one higher than used id
		viewport_pool[count]->lock_all_intern();
}
bool master::unlock (char *password)
{
	if (checkpassword(password))
	{
		unlock_slates_intern();
		return true;
	}
	else
		return false;
}

void master::unlock_slates_intern()
{
	for (int count=0;count<viewport_idcount;count) //viewport_idcount is one higher than used id
		viewport_pool[count]->unlock_all_intern();
}

void master::start_handling_input()
{
	handleinput=true;
	inputthread=thread(kickstarter_inputthread,(master *)this);
}

void master::stop_handling_input()
{
	if (handleinput)
	{
		handleinput=false;
		inputthread.join();
	}
}
int master::send_event_to_all(void *event)
{
	int status=handle_masterevent(event);
	if (status==MASTER_UNHANDLED)
	{
		for (long int count=0; count<viewport_idcount; count++)
			viewport_pool[count]->handle_event(event);
	}
	return status;
}


void kickstarter_inputthread(master *parent_object)
{
	parent_object->inputhandler_function();

}