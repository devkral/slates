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


#include "xroutines.h"
#include "configbackend.h"
#include <cstring>
#include <iostream>

int testCookie (xcb_void_cookie_t cookie,
                xcb_connection_t *connection,
                string errMessage )
{
	xcb_generic_error_t *error = xcb_request_check (connection, cookie);
	if (error)
	{
		cerr << errMessage  << " Errorcode: " << to_string(error->error_code) << endl;
		return -1;
	}
	return 0;
}


xcb_gc_t gc_font_get (xcb_connection_t *c,
             xcb_screen_t     *screen,
             xcb_window_t      window,
             const char       *font_name)
{
	uint32_t             value_list[3];
	xcb_void_cookie_t    cookie_font;
	xcb_void_cookie_t    cookie_gc;
	xcb_generic_error_t *error;
	xcb_font_t           font;
	xcb_gcontext_t       gc;
	uint32_t             mask;

	font = xcb_generate_id (c);
	cookie_font = xcb_open_font_checked (c, font,
                                       strlen (font_name),
                                       font_name);

	if (testCookie( cookie_font,c,"ERROR: can't open font")==-1)
	    return (xcb_gc_t)-1;
	
	gc = xcb_generate_id (c);
	mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
	value_list[0] = screen->black_pixel;
	value_list[1] = screen->white_pixel;
	value_list[2] = font;
	cookie_gc = xcb_create_gc_checked (c, gc, window, mask, value_list);
	error = xcb_request_check (c, cookie_gc);
	if (error)
	{
		cerr << "ERROR: can't create gc\n";
		return (xcb_gc_t)-1;
	}

	cookie_font = xcb_close_font_checked (c, font);
	error = xcb_request_check (c, cookie_font);
	error = xcb_request_check (c, cookie_gc);
	if (error)
	{
		cerr << "ERROR: can't close font\n";
		return (xcb_gc_t)-1;
	}

	return (xcb_gc_t)gc;
}

xcb_gc_t getFontGC (xcb_connection_t *connection,
               xcb_screen_t     *screen,
               xcb_window_t      window,
               const char       *fontName )
{

	xcb_font_t font = xcb_generate_id (connection);
	xcb_void_cookie_t fontCookie = xcb_open_font_checked (connection,
                                                              font,
                                                              strlen (fontName),
                                                              fontName );
	testCookie (fontCookie, connection, "can't open font");

	xcb_gcontext_t gc = xcb_generate_id (connection);
	uint32_t  mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
	uint32_t value_list[3];
	value_list[0] = screen->black_pixel;
	value_list[1] = screen->white_pixel;
	value_list[2] = font;

	xcb_void_cookie_t gcCookie = xcb_create_gc_checked (connection,
                                                            gc,
                                                            window,
                                                            mask,
                                                            value_list );
	testCookie (gcCookie, connection, "can't create gc");

	fontCookie = xcb_close_font_checked (connection, font);
	testCookie (fontCookie, connection, "can't close font");

	return (xcb_gc_t)gc;
}

void drawButton (xcb_connection_t *connection,
                xcb_screen_t     *screen,
                xcb_window_t      window,
                int16_t           x1, 
                int16_t           y1, 
                const char       *label )
    {   
        uint8_t length = strlen (label);
        int16_t inset = 2;
        int16_t width = 7 * length + 2 * (inset + 1); 
        int16_t height = 13 + 2 * (inset + 1); 

        xcb_point_t points[5];
        points[0].x = x1; 
        points[0].y = y1; 
        points[1].x = x1 + width;
        points[1].y = y1; 
        points[2].x = x1 + width;
        points[2].y = y1 - height;
        points[3].x = x1; 
        points[3].y = y1 - height;
        points[4].x = x1; 
        points[4].y = y1; 

        xcb_gcontext_t gc = getFontGC (connection, screen, window, "7x13");
        xcb_void_cookie_t lineCookie = xcb_poly_line_checked (connection,
                                                              XCB_COORD_MODE_ORIGIN,
                                                              window,
                                                              gc,
                                                              5,
                                                              points );
        testCookie (lineCookie, connection, "can't draw lines");

        xcb_void_cookie_t textCookie = xcb_image_text_8_checked (connection,
                                                                 length,
                                                                 window,
                                                                 gc,
                                                                 x1 + inset + 1,
                                                                 y1 - inset - 1,
                                                                 label );
        testCookie (textCookie, connection, "can't paste text");

        xcb_void_cookie_t gcCookie = xcb_free_gc (connection, gc);
        testCookie (gcCookie, connection, "can't free gc");
	};


void button_test (xcb_connection_t *c,
             xcb_screen_t     *screen,
             xcb_window_t      window,
             int16_t           x1,
             int16_t           y1,
             const char       *label)
{
};

uint16_t set_key_actions()
{
	return 0;
}

void init_key_actions()
{


}

void set__default_key_actions()
{

}