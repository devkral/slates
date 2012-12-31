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

#ifndef _BORDER_H_
#define _BORDER_H_


#include "slateobject.h"
class slateobject;
#include "slate.h"
class view_attributes;

class border
{
public:
	border(slateobject *parentt);
	virtual ~border();
	virtual int construct(int x, int y, int weight, int height)=0;
protected:
		slateobject *parent;
		view_attributes *viewo;
private:
};

#endif // _BORDER_H_
