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

#include "emptyslateo.h"

emptyslateo::emptyslateo(master *parent_mastert) : slatetype(parent_mastert)
{

}

emptyslateo::~emptyslateo()
{

}

char emptyslateo::TYPE()
{
	return TYPE_empty;
}
/**

int slate::fillslate(string progname)
{
	if (child_slateo.use_count()==0 || child_slateo->TYPE()==TYPE_emptyslate)
	{
		replace_childobject(create_windowobject(progname));
		draw();
		parent_viewport->fillslate_intern(slateid);
		
		return OP_success;
	}
	else
		return SL_not_empty;
}
int slate::fillsysslate()
{
	if (child_slateo.use_count()==0 || child_slateo->TYPE()==TYPE_emptyslate)
	{
		slateobject *verify=create_sysobject();
		assert(verify);
		replace_childobject(verify);
		draw();
		parent_viewport->fillslate_intern(slateid);
		
		return OP_success;
	}
	else
		return SL_not_empty;
}

void slate::emptyslate()
{
	if (child_slateo!=0 && child_slateo->TYPE()!=TYPE_emptyslate)
			parent_viewport->emptyslate_intern(slateid);
	if (child_slateo.use_count()==0)
	{
		replace_childobject(create_emptyobject());
		draw();
	}
	else
		emptyslate_nonunique();
}
*/
