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

#include "xviewport.h"

#include "xslatearea.h"
class xslatearea;
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;


xviewport::xviewport(master *masteridd, int ownidd,xcb_screen_t *s) : viewport(masteridd,ownidd)
{
	const uint32_t evmask = XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT |XCB_EVENT_MASK_ENTER_WINDOW;
	xcb_void_cookie_t void_cook;
	screen=s;
	void_cook = xcb_change_window_attributes_checked(((xmaster *)get_master())->con, screen->root,
		    XCB_CW_EVENT_MASK, &evmask);

	xcb_map_window(((xmaster*)get_master ())->con,screen->root);
	renderthread=thread(xviewport::kickstarter_renderthread,(viewport *)this);
	

		
  //    uint32_t             mask;
  // uint32_t             values[2];
   
 
   /* Fenster erzeugen */
 
   //mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
   //values[0] = view->white_pixel;
   //values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;

 
                        /* event loop, Ereignisschleife */
}

xviewport::~xviewport()
{
	free(screen);
}


void xviewport::update_slice_info()
{
	cout << "slice info update\n";
	
}

void xviewport::render(slateareascreen *renderob)
{
	/* show window */
	//xcb_window_t find out how to manipulate
	xcb_map_window(((xmaster*)get_master ())->con, ((xhelperclass *)renderob)->window);

	/* force */
	xcb_flush(((xmaster*)get_master ())->con);
	sleep(4);
}

slatearea *xviewport::create_area(slate *parent_slate)
{
	return (slatearea*) new xslatearea(parent_slate);
}