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

#include <thread>
using namespace std;


class slatetype
{
public:

	slatetype(viewport *parent_viewportt);
	virtual ~slatetype();
	viewport *getviewport();
	
	virtual void handle_event(void *initializer, bool called_by_input); //needn't to be implemented if there is an other solution
	//be carefull: if not called by input don't send something to an alleventhandler
	virtual void handle_input(void *initializer); //needn't to be implemented if there is an other solution
	virtual void update()=0;

	virtual void draw_function(); //for kickstarter
	/** implementation idea:
	 * init with creation
	 * stop with destruction
	 * hide/draw via update and slateareas isvisible state
	 */
	
	
	virtual char TYPE()=0;
protected:
	bool isdrawn=false;
	bool hasinputhandle=false;
	thread drawthread;
	viewport *parent_viewport;
	//thread window_inputthread;
private:
	
};
extern void kickstarter_drawthread(slateobject *parent);

#endif // _SLATEOBJECT_H_

