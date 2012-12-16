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

#ifndef _SLAVESLATE_H_
#define _SLAVESLATE_H_

#include "slates.h"
#include "masterslate.h"

class masterslate;

class slaveslate: public slate 
{
public:
	bool is_masterslate ();
	slaveslate(int x, int y,masterslate *controlpointt);
	int detach_child ();
	int attach_child (slateobject *tt);
	void draw_slate ();
	void overlap(bool overlapped_flag);

protected:

private:
	masterslate *controlpoint=0;
	unsigned int pos_x, pos_y; //begin pos=0
};

#endif // _SLAVESLATE_H_

