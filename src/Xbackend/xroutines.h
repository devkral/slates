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


#ifndef _XROUTINES_H_
#define _XROUTINES_H_


#include <xcb/xcb.h>
#include <string>

#include "configbackend.h"
using namespace std;

class xhelperclass
{
public:
	xcb_window_t window;
};





int testCookie (xcb_void_cookie_t cookie,
                xcb_connection_t *connection,
                std::string errMessage );

    void    drawText (xcb_connection_t *connection,
              xcb_screen_t     *screen,
              xcb_window_t      window,
              int16_t           x1,
              int16_t           y1,
              const char       *label );

xcb_gc_t getFontGC (xcb_connection_t *connection,
               xcb_screen_t     *screen,
               xcb_window_t      window,
               const char       *fontName );

void drawButton (xcb_connection_t *c,
             xcb_screen_t     *screen,
             xcb_window_t      window,
             int16_t           x1,
             int16_t           y1,
             const char       *label);


void init_key_actions(configbackend *);
void set_default_key_actions(configbackend *);


#endif //_XROUTINES_H_
