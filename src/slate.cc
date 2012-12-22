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
#include <iostream>



using namespace std;

void slate::show()
{
	sobject->draw();
	sobject->set_slate_state_value(2,true);
};

void slate::hide()
{
	sobject->draw();
	sobject->set_slate_state_value(2,false);
};

void slate::destroy()
{
	detach_child ();
	sobject->set_slate_state_value(2,false);
};





const view_attributes slate::get_viewo()
{
	return *viewo;

}
void slate::receive_slate_signal(slate_messenger *message) 
{
	switch (message->type())
	{
		case sig_destroy: cout << "Waaargh";
			break;
		case sig_show: show();
			break;
		case sig_hide: hide();
			break;
		case -1: cerr << "Error: Don't use slate_messenger directly\n";
			break;
		default: cerr << "Error: Unknown signal\n";
		break;
	}


}

int slate::detach_child ()
{
	sobject=give_default_slateobject(this);
	is_assoz=false;
	dec_used_slates();
	return 0;
}

int slate::attach_child(slateobject *tt)
{
	if (is_assoz==true)
	{
		sobject->destroy();
		delete sobject;		
	}
	sobject=tt;
	if (is_assoz==false)
	{
		is_assoz=true;
		inc_used_slates();
	}
	return 0;
}

