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
slaveslate::~slaveslate()
{

}

/**
void slaveslate::assoz(bool assoz_flag)
{
	if (assoz_flag)
	{
		is_assoz=true;
		hide();
		controlpoint->inc_used_slates(); //an assoz slate is an used slate
	}
	else
	{
		is_assoz=false;
		show();
		controlpoint->dec_used_slates(); //an assoz slate is an used slate
	}
}*/

bool slaveslate::is_masterslate ()
{
	return false;
}

void slaveslate::emit_slate_signal(slate_messenger message)
{
	controlpoint->emit_slate_signal(message);
}

void slaveslate::inc_used_slates()
{
	controlpoint->inc_used_slates ();
}
void slaveslate::dec_used_slates()
{
	controlpoint->dec_used_slates ();
}

int slaveslate::get_x()
{
	return pos_x;
}
int slaveslate::get_y()
{
	return pos_y;
}