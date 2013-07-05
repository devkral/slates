// Licence see COPYING




#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "config.h"
#endif //_CONFIG_H_


#ifdef COMPILED_WITH_SDL
#include "sdlbackend/sdlbackend.h"
#endif
//#endif //test

#ifdef COMPILED_WITH_TESTBACKEND
#include "testbackend/testbackend.h"
#endif


#ifdef COMPILED_WITH_WAYLAND
#include "waylandbackend/waylandbackend.h"
#endif

#ifdef COMPILED_WITH_X
#include "Xbackend/xbackend.h"
#endif


#define DEFAULT_BACKEND 3

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

#include <iostream>
#include <string>
using namespace std;
   
int main (int argc, char *argv[])
{
	
	string testoptions="";
	if (argc>1)
		testoptions=argv[1];
	int sel=DEFAULT_BACKEND;
	if (testoptions=="sdl" || testoptions=="1")
	{
		sel=1;
	}
	if (testoptions=="test" || testoptions=="3")
	{
		sel=2;
	}
	
	int returnvalue;
	switch (sel)
	{
#ifdef COMPILED_WITH_SDL
		case 1: returnvalue=sdlmain(argc, argv);
			break;
#endif
#ifdef COMPILED_WITH_TESTBACKEND
		case 2: returnvalue=testmain(argc, argv);
			break;
#endif
#ifdef COMPILED_WITH_X
		case 3: returnvalue=xmain(argc, argv);
			break;
#endif	
#ifdef COMPILED_WITH_WAYLANDBACKEND
		case 4: returnvalue=waylandmain(argc, argv);
			break;
#endif
		default: std::cerr << "Error: backend doesn't exist\n"; returnvalue=1;
	}

	return returnvalue;
}

