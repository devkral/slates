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
#include "slatearea.h"
class slatearea;

#include "constdef.h"

#include <memory>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

class slate
{
public:
	slate (viewport *parent,long int id, int position_xtemp,int position_ytemp);
	virtual ~slate();
	void init();
	bool isfilled();
	master *get_master();
	viewport *get_viewport();
	void lock();
	void unlock();
	void create_area();
	void replace_area(slatearea *newarea);
	void update();
	int get_x();
	int get_y();
	int get_id();
	void handle_input(void *initializer);
	void handle_event(void *event);
	
	bool isorigin();
	void *get_selfreference_pointer();
	
protected:
	mutex change_slate; //
private:
	int position_x;
	int position_y;
	long int slateid;
	viewport *parent_viewport=0;
	slatearea *child=0;

};
#endif // _SLATE_H_

