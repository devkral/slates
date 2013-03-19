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



#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "config.h"
#endif //_CONFIG_H_

#include <iostream>

//#ifdef test
#ifdef COMPILED_WITH_GTKMM
#include "gtkmmbackend/gtkmmbackend.h"
#endif


#ifdef COMPILED_WITH_SDL
#include "sdlbackend/sdlbackend.h"
#endif
//#endif //test

#ifdef COMPILED_WITH_TESTBACKEND
#include "testbackend/testbackend.h"
#endif



#define DEFAULT_BACKEND 1

/**
 * Backends
 * 1 sdl
 * 2 gtkmm
 * 3 test
 * /


/**
#ifdef ENABLE_NLS
#  include <libintl.h>
#endif
*/


   
int
main (int argc, char *argv[])
{
	int sel=3; //debug
	switch (sel)
	{
#ifdef COMPILED_WITH_SDL
		case 1: sdlmain(argc, argv);
			break;
#endif
#ifdef COMPILED_WITH_GTKMM
		case 2: //gtkmmmain(argc, argv);
			break;
#endif	
#ifdef COMPILED_WITH_TESTBACKEND

		case 3: testmain(argc, argv);
			break;
#endif	
		default: std::cerr << "Error: no backend\n";
	}
	

	
	
}

