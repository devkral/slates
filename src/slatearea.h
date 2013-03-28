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

#ifndef _SLATEAREA_H_
#define _SLATEAREA_H_

class slatearea
{
public:
	slatearea(slate *parent_slate);
	~slatearea();
	
	void move(int x, int y);  //swaps origin
	slate *get_origin();
	
	void resize(int w, int h);
	//void resizeleftuppercorner(int x_delta, int y_delta);
	//void resizerightlowercorner(int x_delta, int y_delta);
	void update();
	virtual void update_screen();

	void handle_event(void  *event);
	void handle_input(void *initializer);
	
	void lock();
	void unlock();
	
	int get_x();
	int get_y();
	bool isfilled();
	bool get_isvisible();
	
protected:

private:
	deque< deque<slate*> > connectedslates; //outer vector y inner x
	void *screen=0;
	char lockstate=0; //0 normal 1 lock, 2 always_unlock,  (3 private_normal, 4 private_locked: not implemented)
	bool isvisible=false;
	slatetype *child;
	//overgive this in windowlist
	int width=1; //in slates
	int height=1; //in slates
//	friend slateobject;
};

#endif // _SLATEAREA_H_

