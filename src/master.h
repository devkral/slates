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

#ifndef _MASTER_H_
#define _MASTER_H_
#include "viewport.h"
class viewport;
//#include "slate.h"
//class slate;
//#include "slateobject.h"
//class slateobject;

#include "constdef.h"

#include <vector>

using namespace std;

class master
{
public:
	virtual ~master();
	void createviewport();
	virtual viewport *create_viewport_intern(master *masteridd, int ownidd)=0;
	void destroyviewport();
	void swapcontent(int viewportid1, long int slateid1,int viewportid2, long int slateid2);
	void lock();
	int unlock();
protected:
	vector<viewport*> viewport_pool;
private:
	void unlock_slates_intern();
	int viewport_idcount=0;
};

#endif // _MASTER_H_

