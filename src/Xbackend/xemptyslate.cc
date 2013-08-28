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
#include <cstdlib>


using namespace std;


xemptyslate::xemptyslate(slatearea *parentt, master *parent_mastert) : emptyslate(parentt, parent_mastert)
{
	std::cout << "Enter xemptyslate\n"; 
   /* schwarzen Grafikkontext erzeugen */
	context = xcb_generate_id(((xmaster*) get_master () )->con);
	black = xcb_generate_id(((xmaster*) get_master () )->con);
	initvalues[0] = ((xviewport*) get_viewport ()) ->screen->white_pixel;
	initvalues[1] = XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
                                    XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
                                    XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
                                    XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE;
	
	//xcb_create_gc(((xmaster *) get_master())->con,context, ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->root, initmask, initvalues);

	window = xcb_generate_id(((xmaster *) get_master())->con);

	//	                  ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->root_depth,
	//init with stub values
	xcb_create_window(((xmaster *) get_master())->con,
	                  XCB_COPY_FROM_PARENT,
	                  window,
	                  ((xviewport*) get_viewport ()) ->screen->root,
                   0, 0, 100, 100, 1,
                   XCB_WINDOW_CLASS_INPUT_OUTPUT,
	                  ((xviewport*)get_viewport ()) ->screen->root_visual,
	                  initmask,initvalues);
                  // mask, values);
	
	
	xcb_map_window(((xmaster*)get_master ())->con,window);
	//xcb_create_gc (((xmaster *) get_master())->con, black, window, initmask, values);
	xcb_flush (((xmaster*)get_master ())-> con);
	//renderthread=thread(xviewport::kickstarter_renderthread,(viewport *)this);
}

xemptyslate::~xemptyslate()
{

	free(position_values);
	free(size_values);
	cerr << "Destroy xemptyslateo\n";
}
void xemptyslate::update()
{
	cout << "testtt\n";

	uint32_t *position_values_new=(uint32_t *) calloc(2,sizeof(uint32_t));
	position_values_new[0]=get_slatearea ()->get_x()*((xviewport*) get_viewport ())->slate_width_p;
	position_values_new[1]=get_slatearea ()->get_y()*((xviewport*) get_viewport ())->slate_height_p;
	xcb_configure_window (((xmaster*)get_master ())->con, window, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, position_values_new);
	free(position_values);
	position_values=position_values_new;
		
	uint32_t *size_values_new=(uint32_t *) calloc(2,sizeof(uint32_t));
	size_values_new[0]=((xviewport*) get_viewport ())->slate_width_p;
	size_values_new[1]=((xviewport*) get_viewport ())->slate_height_p;
	xcb_configure_window (((xmaster*)get_master ())->con, window, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, size_values_new);
	free(size_values);
	size_values=size_values_new;

	cout << position_values[0] << " " << position_values[1] << " size: " << size_values_new[0] << " " << size_values_new[1] << endl;
	
	//enter real values
    /**xcb_change_property (((xmaster *) get_master())->con,
                             XCB_PROP_MODE_REPLACE,
                             window,
                             XCB_ATOM_WM_NAME,
                             XCB_ATOM_STRING,
                             8,
                             strlen (title),
                             title );*/
	//xcb_map_window(((xmaster*)get_master ())->con,window);
	xcb_flush (((xmaster*)get_master ())-> con);

	
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