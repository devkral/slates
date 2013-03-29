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


#include "gtkmmbackend.h"
#include <iostream>
#include <system_error>
using namespace std;

viewport *gtkmmmaster::create_viewport_intern(master *masteridd, int ownidd)
{
	gtkmm_viewport *temp=new gtkmm_viewport(masteridd,ownidd);
	return temp;
}

gtkmmmaster::gtkmmmaster(int argc, char* argv[]) : master()
{
	masterapp=Gtk::Application::create(argc, argv, "org.slates.test");
	createviewport();
	start_handling_input();
}

gtkmmmaster::~gtkmmmaster()
{
	cerr << "Destroy gtkmmmaster\n";
}
void gtkmmmaster::inputhandler_function()
{
	masterapp->run();
}

int gtkmmmaster::handle_masterevent(void *event)
{
	return MASTER_UNHANDLED;
}


int gtkmmmain(int argc, char *argv[])
{
	try
	{
		gtkmmmaster(argc,argv);
	}
	catch (const std::system_error& error)
	{
		cerr << "Caught error: " << error.what() << endl;
		return 1;
	}	
	catch (char  *errorstring)
	{
		cerr << "Caught error string:" << errorstring << " happened\n";
		return 1;
	}
	catch (...)
	{
		cerr << "An Error: happened\n";
		return 1;
	}
	return 0;
}

