/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
 * Copyright (C) 2013 alex <devkral@web.de>
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

#ifndef _GTKMM_SLATE_H_
#define _GTKMM_SLATE_H_

#include "slate.h"
class slate;

#include "gtkmm_emptyslateo.h"
class gtkmm_emptyslateo;
#include "gtkmm_lockslateo.h"
class gtkmm_lockslateo;
#include "gtkmm_sysslateo.h"
class gtkmm_sysslateo;
#include "gtkmm_windowslateo.h"
class gtkmm_windowslateo;

#include "constdef.h"


using namespace std;


class gtkmm_slate : public slate
{
public:
	gtkmm_slate (viewport *parent, long int id,int position_xtemp,int position_ytemp);
	~gtkmm_slate();
protected:

private:

	slateobject *create_lockobject();
	slateobject *create_emptyobject();
	slateobject *create_sysobject();
	slateobject *create_windowobject(string progname);
	
};
#endif // _SLATE_H_

