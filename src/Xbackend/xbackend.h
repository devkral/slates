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


#ifndef _XBACKEND_H_
#define _XBACKEND_H_

#include "master.h"
class master;


class xbackend : public master
{
public:
	xbackend(int argc, char* argv[]);
	~xbackend();
	void inputhandler_function();
	int handle_masterevent(void *event);

private:
	viewport *create_viewport_intern(master *masteridd, int ownidd);
};

 int xmain(int argc ,char *argv[])


#endif // _XBACKEND_H_
