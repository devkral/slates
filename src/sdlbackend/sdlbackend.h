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

#ifdef COMPILED_WITH_X
#include <xcb/xcb.h>
#endif

using namespace std;



class sdlmaster : public master
{
public:
	sdlmaster();
	~sdlmaster();
	void init(int argc, char* argv[]);
	void simple_init(int argc, char* argv[]);
#ifdef  COMPILED_WITH_X
	void x_init(int argc, char *argv[]);
#endif
#ifdef  COMPILED_WITH_WAYLAND
	void wayland_init(int argc, char *argv[]);
#endif
	void inputhandler_function();
	bool is_system_mode();
	int16_t get_focused_viewport_id ();
	int16_t get_backend ();
	uint16_t handle_masterevent(void *event);

protected:
	
private:
	viewport *create_viewport_intern(master *masteridd, int16_t ownidd, void *monitor);
	int16_t focused_viewport=0;
	
};

int sdlmain(int argc, char *argv[]);
 


#endif // _SDLBACKEND_H_
