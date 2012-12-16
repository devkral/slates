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

#include "slaveslate.h"

slaveslate::slaveslate(int x, int y, masterslate *controlpointt)
{
	pos_x=x;
	pos_y=y;
	controlpoint=controlpointt;
	viewo=controlpoint->viewo;
	

}



int slaveslate::detach_child ()
{
	sobject=controlpoint->default_object;
	set_slate_state_value (fpos_placeholder,true); //is placeholder
		controlpoint->dec_used_slates();
	show();
}

int slaveslate::attach_child(slateobject *tt)
{
	sobject=tt;
	set_slate_state_value (fpos_placeholder,false);
		controlpoint->inc_used_slates();
}

void slaveslate::overlap(bool overlapped_flag)
{
	if (overlapped_flag)
	{
		set_slate_state_value(fpos_overlapped,true);
		hide();
		controlpoint->inc_used_slates(); //an overlapped slate is an used slate
	}
	else
	{
		set_slate_state_value(fpos_overlapped,false);
		show();
		controlpoint->dec_used_slates(); //an overlapped slate is an used slate
	}
}

bool slaveslate::is_masterslate ()
{
	return false;
}