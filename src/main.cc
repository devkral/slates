/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2012 alex <devkral@web.de>
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

#include <gtkmm.h>
#include <iostream>

#include "config.h"
#include "gtkmmbackend.h"

/**
#ifdef ENABLE_NLS
#  include <libintl.h>
#endif
*/


   
int
main (int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,
      "org.slates.mainslate");
	Gtk::Window window;
	window.set_title ("slates");
	gtk_slate tt;
	Gtk::Button tz;
	tz.set_label("zz");
	//Gtk::Grid *t=(tt.return_widget());
	window.add(*(tt.return_widget()));
	tt.show();

	return app->run(window);
}

