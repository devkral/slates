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

#include "slates.h"
using namespace std;

slate::slate(int _pos_x, int _pos_y, slate *controlpointt=0,bool createslice=true)
{
	controlpoint=controlpointt;
	pos_x=_pos_x;
	pos_y=_pos_y;
	if (createslice==true)
	{
		if (pos_x>0)
			create_row();
		if (pos_y>0)
			create_column ();
	}

}
slate::slate()
{
	controlpoint=0;
	pos_x=0;
	pos_y=0;
}


slate::~slate()
{
	if (pos_x>0)
	{
		delete left_slate;
		left_slate=0;
	}
	if (pos_y>0)
	{
		delete top_slate;
		top_slate=0;
	}
	if (pos_y==pos_x)
		delete controlnext;

}

void slate::new_slate()
{
	if (pos_x==pos_y)
	{
		used_slades++;
	}
	if (pos_x!=0 && pos_y!=0)
		controlnext->new_slate();
	if (pos_x==pos_y && pos_x+pos_y+1<=used_slades)
	{
		used_slades++;
		controlnext=new slate(pos_x+1,pos_y+1,this);
	}
}


void slate::freed_slate()
{
	if (pos_x==pos_y)
	{
		if (used_slades>0)
			used_slades--;
		else
			used_slades=0;
				
		if (controlnext!=0 && controlnext->freeme())
			delete controlnext;
	}   
}
void slate::create_row()
{
	if (pos_x>0)
	{
		left_slate=new slate(pos_x-1,pos_y,controlpoint,false);
		left_slate->create_row();
	}

}

void slate::create_column()
{
	if (pos_y>0)
	{
		top_slate=new slate(pos_x,pos_y-1,controlpoint,false);
		top_slate->create_column();
	}

}

bool slate::freeme()
{
	if (pos_x!=0 && used_slades==0)
		return true;
	else
		return false;
}



//slate_object
slateobject::slateobject(void *slateobject=0, bool placeholdert=true)
{
	contained_object=slateobject;
	placeholder=placeholdert;
}
slateobject::~slateobject()
{
	//delete contained_object;
	contained_object=0;

}
bool slateobject::is_filled()
{
	if (placeholder==false && contained_object!=0)
		return true;
	return false;
}
void slateobject::set_object(void *in_object)
{
	contained_object=in_object;
}
void *slateobject::get_object()
{
	return contained_object;
}

//slate_object END