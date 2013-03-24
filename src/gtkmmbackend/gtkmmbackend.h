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


#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "config.h"
#endif //_CONFIG_H_


#ifndef _GTKMMBACKEND_H_
#define _GTKMMBACKEND_H_

#include "master.h"
#include "gtkmm_viewport.h"

class gtkmmmaster : public master
{
public:
	gtkmmmaster(int argc, char* argv[]);
	~gtkmmmaster();
	void inputhandler_function();
	Glib::RefPtr<Gtk::Application> masterapp;
	int handle_masterevent(void *event);
protected:
	

private:
	viewport *create_viewport_intern(master *masteridd, int ownidd);
};

int gtkmmmain(int argc ,char *argv[]);


#endif // _GTKMMBACKEND_H_
