/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
 * Copyright (C) 2012 alex <>
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

#ifndef _GTKBACKEND_H_
#define _GTKBACKEND_H_
#include <gtkmm.h>

class gtk_sys_slate : public Gtk::Button
{


public:
	gtk_sys_slate();
	
private:

};

class gtk_slate {
public:
	gtk_slate ();
	void split_slate(int hight, int width);
	Gtk::Grid *return_widget();
	void show();
protected:
	
private:
	Gtk::Grid slategrid;
	gtk_sys_slate ttz;
		gtk_sys_slate ttd;
	void fill_slate(int hight, int width);
	virtual void leftclick();
};



#endif // _GTKBACKEND_H_

