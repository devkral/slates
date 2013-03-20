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

#ifndef _TLOCKSLATEO_H_
#define _TLOCKSLATEO_H_

#include "lockslateo.h"
class lockslateo;
#include "tscreenobject.h"
class tscreenobject;

#include "constdef.h"

class tlockslateo: public lockslateo 
{
public:
	tlockslateo(slate *parent_slate);
	~tlockslateo();
	void draw();
	void hide();
	void destroy_screen_ob ();
protected:

private:
	void unlock();
};

#endif // _LOCKSLATEO_H_

