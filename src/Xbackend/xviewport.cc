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
	evmask[0]= XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT |XCB_EVENT_MASK_ENTER_WINDOW;
	evmask[1]=0 ;/**XCB_EVENT_MASK_EXPOSURE  | XCB_EVENT_MASK_BUTTON_PRESS   |
                                    XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
                                    XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE;*/
	xcb_void_cookie_t void_cook;
	screen=s;
	void_cook = xcb_change_window_attributes_checked(((xmaster *)get_master())->con, screen->root,
		    XCB_CW_EVENT_MASK, evmask);

	//xcb_change_property(con, XCB_PROP_MODE_REPLACE, screen->root, EWMH._NET_WM_STATE, XCB_ATOM_ATOM, 32, 1, &(EWMH._NET_WM_STATE_FULLSCREEN));

//printf ("Informations of screen %ld:\n", screen->root);
  printf ("  width.........: %d\n", screen->width_in_pixels);
  printf ("  height........: %d\n", screen->height_in_pixels);
//printf ("  white pixel...: %ld\n", screen->white_pixel);
//printf ("  black pixel...: %ld\n", screen->black_pixel);
  printf ("\n");

		
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
	//free(screen); //causes error, double free, freed in master?
}


void xviewport::update_slice_info()
{
	slate_width_p=screen->width_in_pixels/get_viewport_width();
	slate_height_p=screen->height_in_pixels/get_viewport_height();
	cout << slate_width_p << " " << slate_height_p << endl;
	update_slates ();
	cout << "survived" << endl;
	
}

int32_t xviewport::get_focused_slate()
{
	return 0;
}


slatearea *xviewport::create_area(slate *parent_slate)
{
	return (slatearea*) new xslatearea(parent_slate);
}