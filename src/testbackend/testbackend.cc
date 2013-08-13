// license: none

#include "testbackend.h"

#include <iostream>
#include <system_error>

using namespace std;



viewport *testmaster::create_viewport_intern(master *masteridd, int ownidd,void *monitor=0)
{
	return new tviewport(masteridd,ownidd);
}

testmaster::testmaster(int argc, char* argv[])
{
	cerr << "Create testmaster\n";
	createviewport(0);
}

testmaster::~testmaster()
{
	cerr << "Destroy testmaster\n";
	cleanup();
}
void testmaster::inputhandler_function()
{


}
int testmaster::handle_masterevent(void *event)
{
	return MASTER_UNHANDLED;
}



int testmain(int argc ,char *argv[])
{
	try
	{
		testmaster(argc,argv);
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
	cout << "100: " << calcidslate(100,100) << " 5: " << calcidslate(5,5) << endl;

	return 0;
}