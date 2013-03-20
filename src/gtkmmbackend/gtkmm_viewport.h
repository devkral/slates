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

#ifndef _GTKMM_VIEWPORT_H_
#define _GTKMM_VIEWPORT_H_
#include "viewport.h"
class viewport;
#include "gtkmm_slate.h"
class gtkmm_slate;
#include "gtkmm_screenobject.h"
class gtkmm_screenobject;

#include "constdef.h"



using namespace std;


class gtkmm_viewport : public viewport
{
public:
	gtkmm_viewport(master *masteridd, int ownidd);
	~gtkmm_viewport();
	slate *create_slate_intern(viewport *parent, long int id,int position_xtemp,int position_ytemp);
protected:

private:
	void destroy_mscreen_ob();
	void create_mscreen_ob();
};

#endif // _VIEWPORT_H_
