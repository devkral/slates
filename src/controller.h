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

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <masterslate.h>
class masterslate;

class controller
{
public:
	controller();
	~controller();
	virtual void drawthread();
	
protected:
	masterslate *screen;
	//vector<masterslate*> list_roots; 
private:
	
};

class mastercontroller
{
public:
	mastercontroller();
	~mastercontroller();
	virtual void iodevicethread()=0;
	virtual controller* givecontroller()=0;
	virtual void notify_controller()=0;
protected:
	vector<controller*> list_roots;// screens
	int cur_iodevice=0;
	

}

#endif // _CONTROLLER_H_

