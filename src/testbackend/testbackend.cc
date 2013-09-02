// license: none

#include "testbackend.h"

#include <iostream>
#include <system_error>

using namespace std;



viewport *testmaster::create_viewport_intern(master *masteridd, int32_t ownidd,void *monitor=0)
{
	return new tviewport(masteridd,ownidd);
}
testmaster::testmaster(){};

void testmaster::init(int argc, char* argv[])
{
	cerr << "Create testmaster\n";
	createviewport(0);
}

testmaster::~testmaster()
{
	cerr << "Destroy testmaster\n";
	cleanup();
}

bool testmaster::is_system_mode()
{
	
	return true;
}

void testmaster::inputhandler_function()
{


}
uint16_t testmaster::handle_masterevent(void *event)
{
	return EXP_ALL_VIEW;
}

int32_t testmaster::get_focused_viewport_id()
{
	return 0;
}

int testmain(int argc ,char *argv[])
{

	testmaster *t=new testmaster();
	int return_var=0;
	try
	{
		t->init(argc,argv);
	}
	catch (cleanup_exception *exc)
	{
		return_var=0;
	}
	catch (restart_exception *exc)
	{
		delete t;
		return_var=testmain(argc,argv);
	}	
	catch (const std::system_error& error)
	{
		cerr << "Caught error: " << error.what() << endl;
		return_var=1;
	}	
	catch (char  *errorstring)
	{
		cerr << "Caught error string:" << errorstring << " happened\n";
		return_var=1;
	}
	catch (...)
	{
		cerr << "An Error: happened\n";
		return_var=1;
	}
	
	return return_var;
}