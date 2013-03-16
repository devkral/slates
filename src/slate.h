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

#ifndef _SLATE_H_
#define _SLATE_H_
//#include "master.h"
//class master;
#include "viewport.h"
class viewport;
#include "slateobject.h"
class slateobject;

#include "constdef.h"


#include <string>

using namespace std;


class slate
{
public:
	slate (viewport *parent, long int id,int position_xtemp,int position_ytemp);
	bool isfilled();
	master *getmaster();
	viewport *getviewport();
	void set_screen_ob(void *screenob);
	void *get_screen_ob();
	void swap_childobject(slateobject ** const child); //swaps inplace
	slateobject ** const get_childobject();
	void lock_slate();
	void unlock_slate();
	int fillslate(string progname); //own content
	void emptyslate(); //reset to default
	
protected:

private:
	bool filled=false;
	char lockstate=0; //0 normal, 1 always_unlock 2 lock (3 private: not implemented)
	long int slateid;
	int position_x;
	int position_y;
	viewport *parent_viewport;
	slateobject *child_slateo=0;
	slateobject *preserve_after_lock=0;

	virtual slateobject *create_lockobject()=0;
	virtual slateobject *create_emptyobject()=0;
	virtual slateobject *create_sysobject()=0;
	virtual slateobject *create_windowobject(string progname)=0;
};
#endif // _SLATE_H_

