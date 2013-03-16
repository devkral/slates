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


#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "config.h"
#endif //_CONFIG_H_

#ifndef _TESTBACKEND_H_
#define _TESTBACKEND_H_

#include "master.h"
class master;
#include "viewport.h"
class viewport;
#include "slate.h"
class slate;
class slateobject;
#include "windowslateo.h"
class windowslateo;
#include "lockslateo.h"
class lockslateo;
#include "sysslateo.h"
class sysslateo;

class testso;
class testsl;
class testvp;
class testmain;


class testlockso : public lockslateo
{
public:
	testlockso();
	~testlockso();

};


class testsl : public slate
{
public:
	testsl(viewport *parent, long int id,int position_xtemp,int position_ytemp);
	~testsl();
protected:
	
private:
	slateobject *create_lockobject();
	slateobject *create_emptyobject();
	slateobject *create_sysobject();
	slateobject *create_windowobject(string progname);
};

class testvp : public viewport
{
public:
	testvp(master *masteridd, int ownidd);
	~testvp();
	
protected:

private:
	slate *create_slate_intern(viewport *parent, long int id,int position_xtemp,int position_ytemp);

};



class testmain : public master
{
public:
	testmain(int argc, char* argv[]);
	~testmain();

private:
	viewport *create_viewport_intern(master *masteridd, int ownidd);
};


#endif // _TESTBACKEND_H_
