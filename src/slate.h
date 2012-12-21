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

#ifndef _SLATE_H_
#define _SLATE_H_


//overlap to close


#include "slateobject.h"
#include "border.h"

class slateobject;

slateobject default_sobject(slate *j);
using namespace std;

const int sig_destroy=1;
const int sig_show=2;
const int sig_hide=3;
const int sig_lock=4;
const int sig_unlock=5;
const int sig_sensitive=6;
const int sig_resize=7;
const int sig_move=8;


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
	slate *caller; //not used yet
	virtual int type(){return -1;};
	int x_beg=-1;
	int x_end=-1;
	int y_beg=-1;
	int y_end=-1;

	//don't set (will be set by emit_slate_signal ())
	int xy_beg=-1;
	int xy_end=-1;
};

struct message_destroy : public slate_messenger
{
	int type()
	{
		return sig_destroy;
	}
	slateobject *new_child;

};


struct message_resize : public slate_messenger
{
	int type()
	{
		return sig_resize;
	}
	slateobject *new_child;

};


struct message_move : public slate_messenger
{
	int type()
	{
		return sig_move;
	}
	slateobject *new_child;

};




class slate
{
public:
	virtual bool is_masterslate()=0; //important =0
	virtual void emit_slate_signal(slate_messenger message)=0;
	virtual void inc_used_slates()=0;
	virtual void dec_used_slates()=0;
		
	void show();
	void hide();
	void destroy();
	void lock();
	void unlock();
	void move(int x, int y);
	void resize(int x_size, int y_size);
	int attach_child(slateobject *tt);
	int detach_child ();


	const view_attributes get_viewo();
	void receive_slate_signal(slate_messenger *slate_message); //lifetime great enough. At least as long as I don't use threads
	
protected:
	slateobject *sobject;
	view_attributes *viewo; //copy for nonfriends


	
	bool is_assoz;
	bool is_drawn;
private:
	
};



#endif // _SLATE_H_

