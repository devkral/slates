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
	values[0] = ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->black_pixel;
	values[1] = 0;

	
	xcb_create_gc(((xmaster *) get_master())->con,context, ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->root, mask, values);

	window = xcb_generate_id(((xmaster *) get_master())->con);
	
	//init with stub values
	xcb_create_window(((xmaster *) get_master())->con,
	                  ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->root_depth,
	                  window, ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->root,
                   1, 1, 100, 100, 1,
                   XCB_WINDOW_CLASS_INPUT_OUTPUT, ((xviewport*) get_slatearea ()->get_viewport ()) ->screen->root_visual,
                   mask, values);
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

bool xemptyslate::isstatic()
{
	return true;
}
bool xemptyslate::isdirty()
{
	return true;
}