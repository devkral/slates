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

#ifndef _SDL_SLATE_H_
#define _SDL_SLATE_H_

#include "slate.h"
class slate;

#include "sdl_emptyslateo.h"
class sdl_emptyslateo;
#include "sdl_lockslateo.h"
class sdl_lockslateo;
#include "sdl_sysslateo.h"
class sdl_sysslateo;
#include "sdl_windowslateo.h"
class sdl_windowslateo;

#include "constdef.h"


using namespace std;


class sdl_slate : public slate
{
public:
	sdl_slate (viewport *parent, long int id,int position_xtemp,int position_ytemp);
	~sdl_slate();
protected:

private:

	slateobject *create_lockobject();
	slateobject *create_emptyobject();
	slateobject *create_sysobject();
	slateobject *create_windowobject(string progname);
	
};
#endif // _SLATE_H_

