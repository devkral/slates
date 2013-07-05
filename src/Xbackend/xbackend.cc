/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
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

#include "xbackend.h"

#include <iostream>
#include <system_error>

using namespace std;



viewport *xbackend::create_viewport_intern(master *masteridd, int ownidd)
{
	return new xviewport(masteridd,ownidd);
}

xbackend::xbackend(int argc, char* argv[])
{
	createviewport();
}

xbackend::~xbackend()
{
	cleanup();
}
void xbackend::inputhandler_function()
{


}
int testmaster::handle_masterevent(void *event)
{
	return MASTER_UNHANDLED;
}



int xmain(int argc ,char *argv[])
{
	try
	{
		xbackend(argc,argv);
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