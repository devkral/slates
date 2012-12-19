/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
 * Copyright (C) 2012 alex <devkral@web.de>
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
#include "slate.h"
class slate;

/**
 * if slateobject overlapps some other widgets,hide them
 * 
 */
class view_attributes;


const int fpos_locked=0;
const int fpos_isolated=1;
const int fpos_shown=2;
const int fpos_readonly=3;
const int fpos_shown_lock=4;
//const int fpos_overlapped=6;
//const int fpos_??=7; not defined yet



class slateobject
{
public:
	slateobject(slate *leftuppercornert);
	~slateobject();

	void set_object(void *in_object);
	void *get_object();
	void draw();
	void destroy();
	void lock();
	void unlock();
	
	const view_attributes get_viewo();
		
	int resize(int width, int height);
	int move(slate *leftuppercornert); //begins with a left upper corner not necessary pos 0

	bool get_slate_state_value(unsigned short flag_pos);
		
protected:
	void *contained_object;
	slate *leftuppercorner;
	int size_x=1;
	int size_y=1;
	int lock_action; //0 hide 1 readonly 2 disappear on lock
	//virtual void destroy_child()=0;
	//vector parents;
	unsigned char slateo_state=16;
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
	 * 6: 
	 * 7: contains sensitive information (hides after a certain amount of inactivity in the slate) (reactivation by click)
	 * 
	 * */
	void set_slate_state_value(unsigned short flag_pos,bool flag_value);
	friend class slate;
};


#endif // _SLATEOBJECT_H_

