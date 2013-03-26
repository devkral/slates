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

#include <memory>
#include <thread>
#include <string>
#include <mutex>

using namespace std;


class slate
{
public:
	slate (viewport *parent, long int id,int position_xtemp,int position_ytemp);
	virtual ~slate();
	void cleanup();
	bool isfilled();
	master *getmaster();
	viewport *getviewport();
	void set_screen_ob(void *screenob);
	void *get_screen_ob();
	void swap_childobject(shared_ptr<slateobject> child, shared_ptr<slateobject> preserved_child); //swaps inplace
	void swap_childobject(slate *swapslate); //swaps inplace
	void replace_childobject(slateobject *temp);
	shared_ptr<slateobject> get_childobject();
	shared_ptr<slateobject> get_lockobject();
	void lock_slate();
	void unlock_slate();
	int fillslate(string progname); //own content
	int fillsysslate();
	void emptyslate(); //reset to default
	void init_slate();
	void destroy_slate();
	void draw();
	void hide();
	void update();
	int get_position_x();
	int get_position_y();
	void handle_input(void *initializer);
	void handle_event(void *event);
	
protected:
	mutex change_slate; //
private:
	int position_x;
	int position_y;
	bool filled=false;
	char lockstate=0; //0 normal, 1 always_unlock 2 lock (3 private: not implemented)
	long int slateid;
	viewport *parent_viewport;
		
	shared_ptr<slateobject> child_slateo;
	shared_ptr<slateobject> preserve_after_lock;

	void emptyslate_nonunique();
	
	virtual slateobject *create_lockobject()=0;
	virtual slateobject *create_emptyobject()=0;
	virtual slateobject *create_sysobject()=0;
	virtual slateobject *create_windowobject(string progname)=0;
	
};
#endif // _SLATE_H_

