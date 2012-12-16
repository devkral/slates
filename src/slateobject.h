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

#ifndef _SLATEOBJECT_H_
#define _SLATEOBJECT_H_
#include "slates.h"
class slate;

/**
 * if slateobject overlapps some other widgets,hide them
 * 
 */
class view_attributes;

class slateobject
{
	public:
		slateobject(slate *leftuppercornert);
		~slateobject();

		void set_object(void *in_object);
		void *get_object();
		void draw();
		const view_attributes get_viewo();
		
		int resize(int width, int height);
		int move(slate *leftuppercornert); //begins with a left upper corner not necessary pos 0

		
	protected:
		void *contained_object;
		slate *leftuppercorner;
		int size_x=1;
		int size_y=1;
		

};


#endif // _SLATEOBJECT_H_

