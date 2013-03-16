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

#ifndef _MASTERSLATE_H_
#define _MASTERSLATE_H_
#include <vector>
#include "slate.h"
#include "slaveslate.h"
class slaveslate;
class slate;

class masterslate: public slate 
{
public:
	//unsigned char get_slate_info();
	//virtual void split_slate(int hight, int width); //
	
	virtual slaveslate* give_slave_slate(int x, int y,masterslate *controlpointt)=0;
	virtual masterslate* give_master_slate(int pos_x_y_next ,masterslate *controlpointpret)=0;
	bool freeme();
	void inc_used_slates();
	void dec_used_slates();
	bool is_beginning_slate();
	//bool is_filled(int x=-1, int y=-1); //default return for cur slate
	masterslate(int _x_y, masterslate *controlpointpret);
	masterslate(view_attributes *viewot);
	virtual ~masterslate();
	//~slate();
	
	void draw_slate ();
	void lockall();
	void unlockall();
	int get_x();
	int get_y();
	

	bool is_masterslate ();
	//void assoz(bool assoz_flag);
	void emit_slate_signal(slate_messenger message);
	
protected:
	int role;
	unsigned int pos_x_y; //begin pos=0

	//virtual void fill_slate(int hight, int width)=0;
	
	
		
private:
	void create_slice();
	vector <slaveslate*> left_slates, top_slates;
	masterslate *controlpre=0,*controlnext=0;
	int used_slades; //controlpoints contain the number of used slates in their slice
	//unsigned char slate_info; //<private><readonlypublic><readonly><isolated><assoz><mainslate><locked/minimized><?>
	void notify_left_slates(slate_messenger *message); //should be just executed by emit_slate_signal
	void notify_top_slates(slate_messenger *message); //should be just executed by emit_slate_signal
	void message_calc_all(slate_messenger message); 
	void message_calc_x_y(slate_messenger message);
	
	friend class slaveslate;
	//friend class slateobject;
};


#endif // _MASTERSLATE_H_
