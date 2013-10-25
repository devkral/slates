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

#include "xslatearea.h"
#include "xemptyslate.h"

xslatearea::xslatearea(slate *parent_slate) : slatearea(parent_slate)
{
		
}
xslatearea::~xslatearea()
{
		
}
slateareascreen *xslatearea::create_lockslate()
{
	return new xlockslate(child,this,get_master());
}

slateareascreen *xslatearea::create_emptyslate()
{
	return new xemptyslate(this,get_master());
}

void xslatearea::handle_input(void *initializer)
{
child->handle_event (initializer);
	/**
	switch (((xcb_generic_event_t *)initializer)->response_type & ~0x80)
	{
		case XCB_EXPOSE:
			((xhelperclass*)child)->window;
			break;
		default:
			
	}*/
	
}