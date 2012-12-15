/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
 * Copyright (C) 2012 alex <alex@archal>
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

#ifndef _SLATES_H_
#define _SLATES_H_
using namespace std;
//rename to singular

#ifdef use_gtkmm
#include "gtkmmbackend.h"
#endif //use_gtkmm

#ifdef sdl_gtkmm

#endif //sdl_gtkmm

#include "slateobject.h"
#include "border.h"

class slateobject;
class border;

struct screenresolution
{
	int points_x=-1;
	int points_y=-1;
};

struct view
{
	int view_begin_x=0;
	int view_begin_y=0;
	int x_axis=1;
	int y_axis=1;
	int reso_x=-1;
	int reso_y=-1;
};


class slate
{
public:
	virtual bool is_masterslate()=0; //important =0
	virtual int attach_child(slateobject *tt)=0;
	virtual int detach_child ()=0;
	//virtual void draw_slate ()=0;
	bool is_filled();
	void show();
	void hide();
	bool is_locked();
	void lock();
	void unlock();
	
protected:
	slateobject *sobject;
	bool is_placeholder=true;
	border *border_right, *border_bottom;
	bool lock;
	int lock_action; //0 hidden 1 readonly 2 disappear on lock
	int slate_state; //0 normal 1 
private:
	
	
};



#endif // _SLATES_H_

