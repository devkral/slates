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

#ifndef _GTKMM_LOCKSLATEO_H_
#define _GTKMM_LOCKSLATEO_H_

#include "lockslateo.h"
class lockslateo;
#include "gtkmm_screenobject.h"
class gtkmm_screenobject;

#include "constdef.h"

class gtkmm_lockslateo: public lockslateo
{
public:
	gtkmm_lockslateo(master *parent_master);
	~gtkmm_lockslateo();
	void update ();
	void lock (slatetype *);
	//void set_visibility(bool t);
	slatetype *unlock ();
	void draw_function ();
	void set_slatearea(slatearea *);

protected:

private:
	Gtk::Button lockbut;
	Gtk::Entry entry;
};

#endif // _LOCKSLATEO_H_

