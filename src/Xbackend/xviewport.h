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

#ifndef _XVIEWPORT_H_
#define _XVIEWPORT_H_
#include "viewport.h"
class viewport;
#include "xbackend.h"
class xmaster;
#include "xslatearea.h"
class xslatearea;
#include "slateareascreen.h"
class slateareascreen;


using namespace std;


class xviewport : public viewport
{
public:
	xviewport(master *masteridd, int ownidd,xcb_screen_t *s);
	~xviewport();
	slate *create_slate_intern(viewport *parent, long int id,int position_xtemp,int position_ytemp);
	slatearea *create_area(slate *parent_slate);
	
	xcb_screen_t *screen;
	int32_t get_focused_slate();
	 uint16_t slate_width_p;
     uint16_t slate_height_p;
protected:
	void update_slice_info();

	
private:
	uint32_t evmask[2];
};

#endif // _XVIEWPORT_H_

