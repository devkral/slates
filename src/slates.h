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


const int fpos_locked=0;
const int fpos_isolated=1;
const int fpos_shown=2;
const int fpos_readonly=3;
const int fpos_placeholder=4;
const int fpos_shown_lock=5;
const int fpos_overlapped=6;
//const int fpos_??=7; not defined yet

struct screenresolution
{
	int points_x=-1;
	int points_y=-1;
};

struct view_attributes
{
	int view_begin_x=0;
	int view_begin_y=0;
	int x_axis=1;
	int y_axis=1;
	int reso_x=-1;
	int reso_y=-1;
	int psize_slate_x=-1;
	int psize_slate_y=-1;
};


class slate
{
public:
	virtual bool is_masterslate()=0; //important =0
	virtual int attach_child(slateobject *tt)=0;
	virtual int detach_child ()=0;
	virtual void overlap(bool overlapped_flag)=0;
	
	//virtual void draw_slate ()=0;
	
	void show();
	void hide();

	void lock();
	void unlock();


	unsigned char get_slate_state();
	bool get_slate_state_value(unsigned short flag_pos);
	const view_attributes get_viewo();
	//slate();
	
protected:
	slateobject *sobject;
	//bool is_placeholder=true;
	border *border_right, *border_bottom;
	view_attributes *viewo; //copy for nonfriends
	unsigned char slate_state=16;
	//00000000
	/**
	 * (right to left)
	 * Position: action
	 * 0: is locked //int 0
	 * 1: is isolated //int 2 
	 * 2: is shown //int 4
	 * 3: is readonly //int 8
	 * 4: is placeholder // int:16
	 * 5: is shown on lock //readonly! int 32
	 * 6: is overlapped // int 64
	 * 7: ?? //int 128
	 * 
	 * */
	void set_slate_state_value(unsigned short flag_pos,bool flag_value);
	
	//bool lock_state;
	int lock_action; //0 hide 1 readonly 2 disappear on lock
	//int slate_state; //0 normal 1 isolated
private:
	
	
};



#endif // _SLATES_H_

