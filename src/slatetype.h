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

#include "master.h"
class master;
class slate;
class slatearea;

#include "constdef.h"

#include <thread>
using namespace std;


class slatetype
{
public:

	slatetype(master *parent_mastert);
	virtual ~slatetype();
	
	virtual void handle_event(void *event); //needn't to be implemented if there is an other solution
	//be carefull: if not called by input don't send something to an alleventhandler
	virtual void handle_input(void *initializer); //needn't to be implemented if there is an other solution
	virtual void update()=0;
	void init();
	void cleanup();
	virtual void draw_function(); //for kickstarter
	/** implementation idea:
	 * init with creation
	 * stop with destruction
	 * hide/draw via update and slateareas isvisible state
	 */
	master *get_master();
	virtual void set_slatearea(slatearea *in)=0;
	slatearea *get_slatearea();
	virtual void set_visibility(bool t)=0;
	bool get_isvisible();
	virtual char TYPE()=0;
protected:
	bool isdrawn=true;
	bool hasinputhandle=false;
	bool isvisible=true;
	thread drawthread;
	slatearea *parent=0;
private:
	master *parent_master=0;
	
};
extern void kickstarter_drawthread(slatetype *parent);

#endif // _SLATEOBJECT_H_

