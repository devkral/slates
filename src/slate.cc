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

#include "slate.h"
using namespace std;
#include <iostream>




void slate::show()
{
	sobject->set_slate_state_value(2,true);
	//draw_slate ();
	//sobject->draw();
};

void slate::hide()
{
	sobject->set_slate_state_value(2,false);
	//draw_slate ();
	//sobject->draw();
};







const view_attributes slate::get_viewo()
{
	return *viewo;

}
void slate::receive_slate_signal(int number) 
{
	switch (number)
	{
		case 1: 
			break;

	}


}
