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

#ifndef _SLATEOBJECT_H_
#define _SLATEOBJECT_H_

//#include "master.h"
//class master;
//#include "viewport.h"
//class viewport;
#include "slate.h"
class slate;

#include "constdef.h"

#include <vector>
using namespace std;



class slateobject
{
public:

	slateobject(slate *parent_slate);
	virtual ~slateobject();
	void set_screen_ob(void *screenob);
	void *get_screen_ob();
	void set_connectedslates(vector< vector<slate*> > *conslateob);
	vector< vector<slate*> > *get_connectedslates();
	virtual char TYPE()=0;
	virtual void draw()=0;
protected:

private:
	vector< vector<slate*> > *connectedslates; //outer vector y inner x
	void *screen_object=0;
};

#endif // _SLATEOBJECT_H_

