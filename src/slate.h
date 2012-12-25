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

#ifndef _SLATE_H_
#define _SLATE_H_


//overlap to close

#include "messages.h"
#include "slateobject.h"
#include "border.h"

class slateobject;


using namespace std;




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
};






class slate
{
public:
	virtual bool is_masterslate()=0; //important =0
	virtual void emit_slate_signal(slate_messenger message)=0;
	virtual void inc_used_slates()=0;
	virtual void dec_used_slates()=0;
	virtual slateobject* give_default_slateobject(slate *leftuppercornert)=0;
	
	void show();
	void hide();
	void destroy();
	void lock();
	void unlock();
	void move(int x, int y);
	void resize(int x_size, int y_size);
	
	int attach_child(slateobject *tt);
	int detach_child();


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

