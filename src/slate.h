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

//rename to singular

//overlap to close


#include "slateobject.h"
#include "border.h"

class slateobject;
class border;
using namespace std;




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

struct slate_messenger
{
	slate *caller;
	int message=-1;
	int x_beg=-1;
	int x_end=-1;
	int y_beg=-1;
	int y_end=-1;

	//don't set (will be set by emit_slate_signal ())
	int xy_beg=-1;
	int xy_end=-1;
};

enum sigslate{
destroy,assoz,deassoz,lock,unlock
};


class slate
{
public:
	virtual bool is_masterslate()=0; //important =0
	virtual int attach_child(slateobject *tt)=0;
	virtual int detach_child ()=0;
	virtual void assoz(bool assoz_flag)=0;
	
	//virtual void draw_slate ()=0;
	
	void show();
	void hide();

	void lock();
	void unlock();


	unsigned char get_slate_state();
	
	const view_attributes get_viewo();
	virtual void emit_slate_signal(slate_messenger message);
	void receive_slate_signal(int number); 
	//slate();
	
protected:
	slateobject *sobject;
	//bool is_placeholder=true;
	border *border_right, *border_bottom;
	view_attributes *viewo; //copy for nonfriends


	
	bool is_assoz;
	bool is_drawn;
private:
	
};



#endif // _SLATES_H_

