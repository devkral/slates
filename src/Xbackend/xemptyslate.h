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

#ifndef _XEMPTYSLATE_H_
#define _XEMPTYSLATE_H_
#include "emptyslate.h"
class emptyslate;
#include "xbackend.h"
class xmaster;
#include "xviewport.h"
class xhelperclass;
#include <xcb/xcb.h>

class xemptyslate : public emptyslate, xhelperclass
{
public:
	xemptyslate(slatearea *parentt, master *parent_mastert);
	~xemptyslate();
	void update();
	bool isstatic();
	bool isdirty();


	uint32_t mask= XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
	uint32_t values[2];
	xcb_rectangle_t      r = { 20, 20, 60, 60 };
	xcb_gcontext_t context;
	
protected:

private:
	const char *title="test";
};

#endif // _TEMPTYSLATEO_H_

