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
using namespace std;
//slate_object
slateobject::slateobject(slate *leftuppercornert)
{
	leftuppercorner=leftuppercornert;
}
slateobject::~slateobject()
{
	//delete contained_object;
	contained_object=0;

}


void slateobject::set_object(void *in_object)
{
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

/**unsigned char slateobject::get_slate_state()
{
	return slate_state;

}*/