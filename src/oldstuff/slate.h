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

#ifndef _SLATE_H_
#define _SLATE_H_


//overlap to close

#include "messages.h"
#include "slateobject.h"

class slateobject;


using namespace std;


class slate
{
public:
	virtual bool is_masterslate()=0; //important =0
	virtual void emit_slate_signal(slate_messenger message)=0;
	virtual void inc_used_slates()=0;
	virtual void dec_used_slates()=0;
	virtual slateobject* give_default_slateobject(slate *leftuppercornert)=0;

	virtual ~slate();
	void show();
	void hide();
	void destroy();
	void lock();
	void unlock();
	void move(int x, int y);
	void resize(int x_size, int y_size);
	
	int attach_child(slateobject *tt);
	int detach_child();


	const view_attributes get_viewo();
	void receive_slate_signal(slate_messenger *slate_message); //lifetime great enough. At least as long as I don't use threads
	
protected:
	slateobject *sobject;
	view_attributes *viewo; //copy for nonfriends


	
	bool is_assoz;
	bool is_drawn;
	virtual int get_x()=0;
	virtual int get_y()=0;
	friend class slateobject;
private:
	
};



#endif // _SLATE_H_

