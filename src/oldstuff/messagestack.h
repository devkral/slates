/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
 * Copyright (C) 2013 alex <alex@archal>
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

#ifndef _MESSAGESTACK_H_
#define _MESSAGESTACK_H_
#include <mutex>


//needs to be defined in backend
extern struct graphic_backend;


struct view_attributes
{
	int view_begin_x=0;
	int view_begin_y=0;
	//int size_view_area=-1; , else diagonal down with size slates
	int view_x_axis=0; //if 0: adjust automatically (amount_masterslates)
	int view_y_axis=0; //if 0: adjust automatically (amount_masterslates)
	int amount_masterslates=1; //if 0 clean exit
	int reso_x=-1;
	int reso_y=-1;
	graphic_backend graphicobject;
	/**
	inline void update_reso_slates()
	{
		if(amount_masterslates>0) //division through zero should not occur (but amount can reach zero and in case of errors less)
		{
			if (view_x_axis==0)
			{
				psize_slate_x=reso_x/amount_masterslates;
			}
			else
			{
				psize_slate_x=reso_x/view_x_axis;
			}

			if (view_y_axis==0)
			{
				psize_slate_y=reso_y/amount_masterslates;
			}
			else
			{
				psize_slate_y=reso_y/view_y_axis;
			}
		}
	}


	int psize_slate_x=-1;
	int psize_slate_y=-1;
	void *drawing_area=0;

	//borderarea WARNING: intern units
	int space_border=1; // 1 = sane default
	int thickness_border=1;**/
};



//FIXME: unit hack, no float units possible






class globstate
{
public:
	globstate();
	void setstate(unsigned char);
	unsigned char getstate(unsigned char);
		
protected:

private:
	std::mutex rw_mut();
	int lock();
	int unlock();
	bool is_locked=false;
	unsigned char state;
} glob_state_ob;

#endif // _MESSAGESTACK_H_

