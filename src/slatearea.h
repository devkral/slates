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

#ifndef _SLATEAREA_H_
#define _SLATEAREA_H_

#include "slate.h"
class slate;
//#include <slatetype.h>
class slatetype;
class lockslateo;
class emptyslateo;

#include "viewport.h"
class viewport;


#include <deque>

using namespace std;

class slatearea
{
public:
	slatearea(slate *parent_slate);
	virtual ~slatearea();
	void cleanup();
	void init();
	void move(int x, int y);  //swaps origin
	slate *get_origin();
	master *get_master();
	viewport *get_viewport();
	
	void resize(int w, int h);
	//void resizeleftuppercorner(int x_delta, int y_delta);
	//void resizerightlowercorner(int x_delta, int y_delta);
	void update();
	virtual void *get_screen()=0;
	virtual void update_screen()=0;
	
	virtual void create_lockslatetype()=0;
	virtual void create_emptyslatetype()=0;

	virtual void handle_input(void *initializer)=0;
	
	void handle_event(void  *event);
		
	void lock();
	void unlock();
	
	int get_x();
	int get_y();
	bool isfilled();
	bool get_isvisible();
	bool get_isondestruction ();
	void set_childslatearea(slatearea *replace);
	
protected:
	slatetype *child=0;
	bool hasinputhandle=false;
private:
	deque< deque<slate*> > connectedslates; //outer vector y inner x
	char lockstate=0; //0 normal 1 lock, 2 always_unlock,  (3 private_normal, 4 private_locked: not implemented)
	
	bool isvisible=false;
	bool isondestruction=false;
	//give this over to windowlist
	int width=1; //in slates
	int height=1; //in slates
//	friend slateobject;
};


void kickstarter_drawthread(slatetype *parent)
{
	parent->draw_function ();
}

#endif // _SLATEAREA_H_

