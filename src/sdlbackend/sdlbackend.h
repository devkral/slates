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
#include "sdl_viewport.h"
class sdl_viewport;


#include "SDL.h"
#include <vector>
#include <thread>
#include <atomic>


using namespace std;



class sdl_master : public master
{
public:
	sdl_master(int argc, char* argv[]);
	~sdl_master();
	void inputhandler_function(); 
	void renderthread_function(); 
protected:
	
private:
	thread renderthread;
	atomic<bool> render;
	viewport *create_viewport_intern(master *masteridd, int ownidd);
};
void kickstarter_renderthread(sdl_master *parent_object);

int sdlmain(int argc, char *argv[]);
 


#endif // _SDLBACKEND_H_
