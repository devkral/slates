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
#include <iostream>




void slate::show()
{
	set_slate_state_value(2,true);
	//draw_slate ();
	//sobject->draw();
};

void slate::hide()
{
	set_slate_state_value(2,false);
	//draw_slate ();
	//sobject->draw();
};



unsigned char slate::get_slate_state()
{
	return slate_state;

}

bool slate::get_slate_state_value (unsigned short flag_pos)
{
	if (flag_pos>7)
		std::cerr << "Error: accesses value out of range.\n";
	return 1&slate_state>>flag_pos;
}

void slate::set_slate_state_value(unsigned short flag_pos,bool flag_value)
{
	if (flag_pos>7)
		std::cerr << "Error: tried to set flag out of range.\n";
	else
		if (flag_value)
			slate_state|1<<flag_pos;
		else
			slate_state=slate_state&~(1<<flag_pos);

}

const view_attributes slate::get_viewo()
{
	return *viewo;

}

