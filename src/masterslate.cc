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

#include <iostream>
#include "masterslate.h"
#include <assert.h>

using namespace std;


masterslate::masterslate(int _pos_x_y, masterslate *controlpret)
{
	controlpre=controlpret;
	pos_x_y=_pos_x_y;

	viewo=controlpre->viewo;

	create_slice();

}

masterslate::masterslate(view_attributes *viewot)
{
	controlpre=0;
	pos_x_y=0;
	viewo =viewo;
}


masterslate::~masterslate()
{
	if (!left_slates.empty())
	{
		left_slates.clear();
	}
	if (!top_slates.empty())
	{
		top_slates.clear();
	}
	if (controlnext!=0)
	{
		delete controlnext;
		controlnext=0;
	}

}

/**
bool masterslate::is_filled(int x=-1,int y=-1)
{
	//if ((x<0 && y<0) || (pos_x==x && pos_y==y))
		return is_placeholder;

	if (x<y && y==pos_y)
		return top->is_filled(x,y);
	if (y<x && x==pos_x)
		return left->is_filled(x,y);
		
	if (pos_x==pos_y)
	{
		if (controlnext!=0)
			controlnext->is_filled(int x,int y);
		else
		{
			cerr << "Debug: position not found\n";
			return false;
		}

	}else {
		
		cerr << "Debug: is_filled executed without being controlpoint and is not in the same column\n";
		return 	controlpoint->is_filled(x,y);
	}

}
*/

               
void masterslate::inc_used_slates()
{
	used_slades++;
	if (2*pos_x_y+1<=used_slades)
	{
		used_slades++;
		controlnext=new masterslate(pos_x_y+1,this);
	}
}


void masterslate::dec_used_slates()
{
	if (used_slades>0)
		used_slades--;
	else
	{
		used_slades=0;
		std::cerr << "Error: tried decrement even zero\n";
	}
		
	if (controlnext!=0 && controlnext->freeme())
		delete controlnext;
}
void masterslate::create_slice()
{
	for(int it=0;it<pos_x_y;it++)
	{
		left_slates.push_back(slaveslate(it,pos_x_y,this));
		top_slates.push_back(slaveslate(pos_x_y,it,this));
	}

}


bool masterslate::freeme()
{
	if (pos_x_y!=0 && used_slades==0)
		return true;
	else
		return false;
}

int masterslate::detach_child ()
{
	sobject=default_object;
	is_assoz=false;
	dec_used_slates();
	show();
}

int masterslate::attach_child(slateobject *tt)
{
	sobject=tt;
	is_assoz=true;
	inc_used_slates();
	show();
}


bool masterslate::is_masterslate ()
{
	return true;
}



void masterslate::notify_left_slates (slate_messenger *message)
{
	if (pos_x_y>=message->y_beg && pos_x_y<=message->y_end)
	{
		int max_countx=message->x_end;
		if (pos_x_y<=message->x_end)
			max_countx=pos_x_y-1;
		
		for (int countx=message->x_beg;countx<=max_countx;countx++)
			left_slates[countx].receive_slate_signal (message->message);
	}

}

void masterslate::notify_top_slates (slate_messenger *message)
{
	if (pos_x_y>=message->x_beg && pos_x_y<=message->x_end)
	{	
		int max_county=message->y_end;
		if (pos_x_y<=message->y_end)
			max_county=pos_x_y-1;

		for (int county=message->y_beg;county<=max_county;county++)
			left_slates[county].receive_slate_signal (message->message);
	}

}


void masterslate::emit_slate_signal(slate_messenger message)
{
	if (message.xy_beg==-1)
	{
		if (message.x_beg<message.y_beg)
			message.xy_beg=message.x_beg;
		else
			message.xy_beg=message.y_beg;

		if (message.x_end<message.y_end)
			message.xy_end=message.y_end;
		else
			message.xy_end=message.x_end;
		
	}
	assert(message.xy_beg>=0);
	assert(message.xy_end>=0);
	
	if (message.xy_beg<pos_x_y)
		controlpre->emit_slate_signal(message);

	//slates left
	notify_left_slates (&message);
	                    
	if (pos_x_y>=message.x_beg && pos_x_y<=message.x_end && pos_x_y>=message.x_beg && pos_x_y<=message.x_end)
		receive_slate_signal (message.message);
		
	//slates top
	notify_top_slates (&message);

	if (message.xy_end<pos_x_y)
		controlnext->emit_slate_signal (message);
	
}