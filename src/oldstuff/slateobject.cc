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

#include "slateobject.h"

#include <iostream>
#include <cassert>
using namespace std;


slateobject::slateobject(slate *leftuppercornert)
{
	leftuppercorner=leftuppercornert;
	viewo=leftuppercorner->viewo;
	intu.x=leftuppercorner->get_x()*(viewo->psize_slate_x);
	intu.y=leftuppercorner->get_y()*(viewo->psize_slate_y);
	intu.width_child=(viewo->psize_slate_x)-((viewo->space_border)+(viewo->thickness_border));
	intu.height_child=(viewo->psize_slate_y)-((viewo->space_border)+(viewo->thickness_border));

}
slateobject::~slateobject()
{
	//destroy_child();
	delete border_right;
	delete border_bottom;
}

void slateobject::set_object(void *in_object)
{
	//delete contained_object;

	contained_object=in_object;
}
void *slateobject::get_object()
{
	return contained_object;
}

const view_attributes slateobject::get_viewo()
{
	return leftuppercorner->get_viewo();

}

bool slateobject::get_slate_state_value (unsigned short flag_pos)
{
	if (flag_pos>7)
		std::cerr << "Error: accesses value out of range.\n";
	return 1&slateo_state>>flag_pos;
}

void slateobject::set_slate_state_value(unsigned short flag_pos,bool flag_value)
{
	if (flag_pos>7)
		std::cerr << "Error: tried to set flag out of range.\n";
	else
		if (flag_value)
			slateo_state|1<<flag_pos;
		else
			slateo_state=slateo_state&~(1<<flag_pos);

}

void slateobject::draw()
{
	draw_borders();
	//draw_child();
}



//very powerful tool, don't forget: you can use it for two resize tasks:
//adapt to new resolution w_diff, h_diff=0 (just enter two parameters)
//resize slate
void slateobject::resize_diff(int x_points_diff, int y_points_diff,int w_diff=0, int h_diff=0)
{
	size_x+=w_diff;
	size_y+=h_diff;
	assert (size_x>=0 && size_y>=0);
	//	cerr << "Error: x or y lower zero\n";
	intu.width_child+=x_points_diff;
	intu.height_child+=y_points_diff;
}

/**unsigned char slateobject::get_slate_state()
{
	return slate_state;

}*/