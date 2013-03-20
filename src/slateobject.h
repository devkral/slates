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

#ifndef _SLATEOBJECT_H_
#define _SLATEOBJECT_H_

//#include "master.h"
//class master;
//#include "viewport.h"
//class viewport;
#include "slate.h"
class slate;

#include "constdef.h"

#include <deque>
#include <memory>
using namespace std;



class slateobject
{
public:

	slateobject(slate *parent_slate);
	virtual ~slateobject();
	void set_screen_ob(void *screenob);
	void swap_screen_ob(shared_ptr<slateobject> swapso);
	void *get_screen_ob();
	virtual void destroy_screen_ob ()=0;
	void set_connectedslates(shared_ptr<deque<deque<slate*> > > conslateob);
	void swap_connectedslates(shared_ptr<slateobject> swapso);
	shared_ptr<deque< deque<slate*> > > get_connectedslates();

	//should be ignored in emptyobject
	void move(int x, int y); //swaps object
	void resizeleftuppercorner(int x_delta, int y_delta);
	void resizerightlowercorner(int x_delta, int y_delta);
	//if resize x or y <=0 close slate and replace by emptyslate
	
	virtual char TYPE()=0;
	void close();
	virtual void draw()=0;
	virtual void hide()=0;
	/** implementation idea:
	 * draw() start draw (and input?)thread (especially window) if isdrawn=false 
			elsewise update static elements

	 * hide() stop threads if isdrawn=true elsewise do nothing
	 */
	
protected:
	bool isdrawn=false;
	void *screen_object=0; //reason why here: must grow over slates
	//not thread safe
	shared_ptr<deque< deque<slate*> > > connectedslates; //outer vector y inner x
	friend slate;
private:
};

#endif // _SLATEOBJECT_H_

