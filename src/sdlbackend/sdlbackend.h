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


#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "config.h"
#endif //_CONFIG_H_

#ifndef _SDLBACKEND_H_
#define _SDLBACKEND_H_

#include "master.h"
class master;
#include "sdlviewport.h"
class sdlviewport;


#include "SDL.h"
#include <vector>


using namespace std;



class sdlmaster : public master
{
public:
	sdlmaster();
	void init(int argc, char* argv[]);
	~sdlmaster();
	void inputhandler_function();
	int32_t get_focused_viewport ();
	uint16_t handle_masterevent(void *event);
protected:
	
private:
	viewport *create_viewport_intern(master *masteridd, int ownidd, void *monitor);
};

int sdlmain(int argc, char *argv[]);
 


#endif // _SDLBACKEND_H_
