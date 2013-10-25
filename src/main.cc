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
 * 2 test
 * 3 x
 */


/**
#ifdef ENABLE_NLS
#  include <libintl.h>
#endif
*/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;
void help()
{
	cout << "Backends:\n" << "wayland,X,test,sdl\n";
}

int main (int argc, char *argv[])
{
	/**slates_config=new configbackend();
	slates_config->load();*/
	int sel=DEFAULT_BACKEND;
	string testoptions="";
	// options descriptor

	int cindex=1;
	while (cindex<argc-1) //-1 because cindex must be followed by argument
	{
		if (strcmp(argv[cindex],"--renderingsystem")==0)
		{
			if (argv[cindex+1]!=NULL)
			{
				testoptions=argv[cindex+1];
				break;
			}
		}
		
		cindex++;
	}
	
	
	if (testoptions=="sdl")
	{
//#ifdef COMPILED_WITH_SDL
		sel=1;
/**#else
		cerr << "Not compiled with sdl support\n";
#endif*/
	}
	if (testoptions=="test")
	{
#ifdef COMPILED_WITH_TESTBACKEND
		sel=2;
#else
		cerr << "Not compiled with testbackend\n";
#endif
	}
	if (testoptions=="X\n")
	{
#ifdef COMPILED_WITH_X
		sel=3;
#else
		cerr << "Not compiled with X backend\n";
#endif
	}
	if (testoptions=="wayland\n")
	{
#ifdef COMPILED_WITH_X
		sel=4;
#else
		cerr << "Not compiled with wayland backend\n";
#endif
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
	//delete slates_config;
	return returnvalue;
}

