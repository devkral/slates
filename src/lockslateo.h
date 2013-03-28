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

#ifndef _LOCKSLATEO_H_
#define _LOCKSLATEO_H_

#include "slatetype.h"
class slatetype;
//#include "slatearea.h"
class slatearea;

#include "constdef.h"

class lockslateo : public slatetype
{
public:
	lockslateo(master *parent_mastert);
	~lockslateo();
	char TYPE();
	void lock(slatearea *slateareaout,slatetype *lockedobject);
	virtual slatetype *unlock(slatearea *slateareaout)=0;
	virtual bool isempty()=0;
protected:

private:
	void sendunlock();
};

#endif // _LOCKSLATEO_H_

