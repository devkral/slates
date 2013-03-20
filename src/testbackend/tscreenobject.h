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

#ifndef _TSCREENOBJECT_H_
#define _TSCREENOBJECT_H_

#include <iostream>
using namespace std;


typedef struct tviewportscreen_{
	~tviewportscreen_()
	{
		cerr << "tvs I'm gone\n";
		delete canvas;
	}
	char *canvas;
	
	
}tviewportscreen;

typedef struct tpscreen_{
	~tpscreen_()
	{
		cerr << "tps I'm gone\n";
	}
	int x;
	int y;
	int w;
	int h;
	
}tpscreen;

extern tviewportscreen *to_tvs(void* in);
extern tpscreen *to_tps(void* in);


#endif // _TSCREENOBJECT_H_

