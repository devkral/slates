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

#include "xemptyslate.h"

#include <cstring>
#include <iostream>



using namespace std;


xemptyslate::xemptyslate(slatearea *parentt, master *parent_mastert) : emptyslate(parentt, parent_mastert)
{
	std::cout << "Enter xemptyslate\n"; 
   /* schwarzen Grafikkontext erzeugen */
	context = xcb_generate_id(((xmaster*) get_master () )->con);
	black = xcb_generate_id(((xmaster*) get_master () )->con);
	initvalues[0] = ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->white_pixel;
	initvalues[1] = 0;
	
	xcb_create_gc(((xmaster *) get_master())->con,context, ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->root, initmask, initvalues);

	window = xcb_generate_id(((xmaster *) get_master())->con);

	//	                  ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->root_depth,
	//init with stub values
	xcb_create_window(((xmaster *) get_master())->con,
	                  XCB_COPY_FROM_PARENT,
	                  window,
	                  ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->root,
                   0, 0, 1000, 1000, 1,
                   XCB_WINDOW_CLASS_INPUT_OUTPUT,
	                  ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->root_visual,
	                  initmask,initvalues);
                  // mask, values);
	
	xcb_map_window(((xmaster*)get_master ())->con,window);
	//xcb_create_gc (((xmaster *) get_master())->con, black, window, initmask, values);
	xcb_flush (((xmaster*)get_master ())-> con);
	//renderthread=thread(xviewport::kickstarter_renderthread,(viewport *)this);
}

xemptyslate::~xemptyslate()
{
	cerr << "Destroy xemptyslateo\n";
}
void xemptyslate::update()
{
	//enter real values
    xcb_change_property (((xmaster *) get_master())->con,
                             XCB_PROP_MODE_REPLACE,
                             window,
                             XCB_ATOM_WM_NAME,
                             XCB_ATOM_STRING,
                             8,
                             strlen (title),
                             title );
	

	
}
void xemptyslate::handle_event(void *event)
{
	switch (((xcb_generic_event_t *)event)->response_type & ~0x80)
	{
		case XCB_EXPOSE:
			/* We draw the points */
      //xcb_poly_point (((xmaster *) get_master())->con, XCB_COORD_MODE_ORIGIN, window, black, 4, points);
			xcb_flush (((xmaster*)get_master ())-> con);
			break;
		default:
			break;
			
	}

}


bool xemptyslate::isstatic()
{
	return true;
}
bool xemptyslate::isdirty()
{
	return true;
}