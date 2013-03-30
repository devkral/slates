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

#ifndef _GTKMMSLATEAREA_H_
#define _GTKMMSLATEAREA_H_

#include "slate.h"
class slate;
//#include <slatetype.h>
class slatetype;
//class lockslateo;
#include "viewport.h"
class viewport;

#include "gtkmm_emptyslateo.h"
class gtkmm_emptyslateo;
#include "gtkmm_lockslateo.h"
class gtkmm_lockslateo;

#include "gtkmm_screenobject.h"
class gtkmm_screenobject;

using namespace std;

class gtkmm_slatearea : public slatearea
{
public:
	gtkmm_slatearea(slate *parent_slate, gtkslatearea *newarea);
	virtual ~gtkmm_slatearea();
	void *get_screen();
	void update_screen();
	void create_lockslatetype();
	void create_emptyslatetype();
protected:

private:
	gtkslatearea *slatearea_screen;
};

#endif // _SLATEAREA_H_

