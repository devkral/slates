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

#include "controller.h"

//controller::controller()



mastercontroller::mastercontroller()
{
}

mastercontroller::~mastercontroller()
{
}

void mastercontroller::notify_controller(void *t)
{
	list_roots[cur_iodevice]->execevent(t);
}

bool mastercontroller::addscreen (void *screen)
{
	list_roots.push_back (givecontroller(screen));
}

bool mastercontroller::removescreen (void *screen)
{
	bool found=false;
	for (int count=0; count < list_roots.size(); count++)
	{
		if (list_roots[count]->comparescreen(screen)==true)
		{
			delete list_roots[count];
			list_roots.erase(list_roots.begin()+count-1);
			found=true;
		}
	}
	return found;
}
