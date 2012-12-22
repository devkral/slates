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

#ifndef _MESSAGES_H_
#define _MESSAGES_H_

class slate;
class slateobject;

const int sig_destroy=1;
const int sig_show=2;
const int sig_hide=3;
const int sig_lock=4;
const int sig_unlock=5;
const int sig_sensitive=6;
const int sig_resize=7;
const int sig_move=8;


struct slate_messenger
{
	slate *caller; //not used yet
	virtual int type(){return -1;};
	int x_beg=-1;
	int x_end=-1;
	int y_beg=-1;
	int y_end=-1;

	//don't set (will be set by emit_slate_signal ())
	int xy_beg=-1;
	int xy_end=-1;
};

struct message_destroy : public slate_messenger
{
	int type()
	{
		return sig_destroy;
	}
	slateobject *new_child;

};


struct message_resize : public slate_messenger
{
	int type()
	{
		return sig_resize;
	}
	slateobject *new_child;

};


struct message_move : public slate_messenger
{
	int type()
	{
		return sig_move;
	}
	slateobject *new_child;

};


#endif // _MESSAGES_H_

