/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
 * Copyright (C) 2013 alex <devkral@web.de>
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

#include "slatearea.h"

slatearea::slatearea(slate *parent_slate)
{
	connectedslates.push_back( deque<slate*>() );
	connectedslates[0].push_back(parent_slate);
	x=get_origin()->get_x();
	y=get_origin()->get_y();
	get_origin()->getviewport()->getempty();
}

slatearea::~slatearea()
{
	if (isfilled())
	{
		delete child;
	}
	
	while (connectedslates.empty()==false)
	{
		delete connectedslates.back();
		connectedslates.pop_back();
	}
}

bool slatearea::isfilled()
{
	if (child->TYPE()==TYPE_windowslate)
		return false;
	else
		return true;
}
slate *slatearea::get_origin()
{
	return connectedslates[0][0];
}

void slatearea::lock()
{
	if (lockstate==0)
	{
		child=get_origin()->create_lockslatetype (this,child);
		lockstate+=1;
	}
}

void slatearea::unlock()
{
	if (lockstate==1)
	{
		slatetype *temp=child;
		child=temp->unlock();
		delete temp;
		lockstate-=1;
	}
}

int slatearea::get_x()
{
	get_origin()->get_x();
}
int slatearea::get_y()
{
	get_origin()->get_y();
}

