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

#include "testbackend.h"

#include <iostream>

using namespace std;

testsl::testsl(viewport *parent, long int id,int position_xtemp,int position_ytemp) : slate(parent, id,position_xtemp,position_ytemp)
{

}

testsl::~testsl()
{

}


slateobject *testsl::create_lockobject()
{
	cerr << "Created lockobject\n";
	return 0;
}


slateobject *testsl::create_emptyobject()
{
	cerr << "Created emptyobject\n";
	return 0;

}

slateobject *testsl::create_sysobject()
{
	cerr << "Created sysobject\n";
	return 0;

}


slateobject *testsl::create_windowobject(string progname)
{
	cerr << "Created windowobject " << progname << endl ;
	return 0;
}



testvp::testvp(master *masteridd, int ownidd): viewport(masteridd,ownidd)
{


}

testvp::~testvp()
{


}

slate *testvp::create_slate_intern(viewport *parent, long int id,int position_xtemp,int position_ytemp)
{
	cerr << "created slate: " << id << endl;
	return new testsl(parent,id,position_xtemp,position_ytemp);
}


viewport *testmain::create_viewport_intern(master *masteridd, int ownidd)
{
	cerr << "created viewport: " << ownidd << endl;
	return new testvp(masteridd,ownidd);
}

testmain::~testmain()
{


}


testmain::testmain(int argc, char* argv[])
{
	createviewport();
	cerr << endl;
	viewport_pool[0]->addslice();
	cerr << endl;
	viewport_pool[0]->addslice();
	

}