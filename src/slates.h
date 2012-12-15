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


#ifdef use_gtkmm
#include "gtkmmbackend.h"
#endif //use_gtkmm

#ifdef sdl_gtkmm

#endif //sdl_gtkmm





class slateobject;

class slate
{
public:
	//unsigned char get_slate_info();
	//virtual void split_slate(int hight, int width); //
	bool freeme();
	slate(int x, int y, slate *controlpointt, bool createslice);
	slate();
	~slate();
	
protected:
	void freed();
	int role;
	//virtual void fill_slate(int hight, int width);

	
		
private:
	slateobject *sobject;
	void new_slate();
	void freed_slate();
	void create_row();
	void create_column ();
	unsigned int pos_x, pos_y; //begin pos=1
	slate *left_slate=0, *top_slate=0,*controlpoint=0,*controlnext=0; //if itself controlpoint (x=y) rl diagonal up, controlnext lr diagonal down
	//void D_tactic;
	int used_slades; //controlpoints contain the number of used slates in their slice
	//int slates_horizontal;
	//int slates_vertical;
	//unsigned char slate_info; //<private><readonlypublic><readonly><isolated><assoz><mainslate><locked/minimized><?>
	
};

class slateobject
{
	public:
		slateobject(void *in_object, bool placeholdert);
		~slateobject();
		bool is_filled();
		void set_object(void *in_object);
		void *get_object();
		
	private:
		void *contained_object;
		bool placeholder;
};



class sys_slate
{



};


#endif // _SLATES_H_

