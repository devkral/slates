// license: none

#include "testbackend.h"

#include <iostream>
#include <system_error>

using namespace std;



viewport *testmaster::create_viewport_intern(master *masteridd, int32_t ownidd,void *monitor=0)
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
uint16_t testmaster::handle_masterevent(void *event)
{
	return EXP_ALL_VIEW;
}

int32_t testmaster::get_focused_viewport()
{
	return 0;
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