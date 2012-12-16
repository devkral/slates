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

#include "slateobject.h"


//slate_object
slateobject::slateobject(slate *leftuppercornert)
{
	leftuppercorner=leftuppercornert;
}
slateobject::~slateobject()
{
	//delete contained_object;
	contained_object=0;

}


void slateobject::set_object(void *in_object)
{
	contained_object=in_object;
}
void *slateobject::get_object()
{
	return contained_object;
}

const view_attributes slateobject::get_viewo()
{
	return leftuppercorner->get_viewo();

}

;

//slate_object END