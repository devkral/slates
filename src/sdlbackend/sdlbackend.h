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
#include "SDL.h"
#include <vector>
#include "master.h"
/**


#include <thread>

int sdlmain(int argc, char *argv[]);
class sdlmslate;
class slateobject;


class sdlborder : public border
{
	public:
		sdlborder(slateobject *parent);
		~sdlborder();
		int construct(int x, int y, int weight, int height);
		
	private:

		SDL_Surface *sdl_border_surf;
		SDL_Rect sdl_border_rect;

};

class sdlslateobject : public slateobject
{
	public:
		sdlslateobject(slate *parent);
		void use_default_child();
	private:
		void draw_borders();
		void draw_child();
		void destroy_child();

		
		/**int	x_points, y_points;
		int h_points, w_points;
		int thickness=1, space=1;
};





class sdlsslate : public slaveslate
{
public:
	sdlsslate(int x, int y,masterslate *controlpointt);
	~sdlsslate();
	//defaultobject
	slateobject* give_default_slateobject (slate *parent);
	//defaultobject end
	
private:

};



class sdlmslate : public masterslate
{
public:
	sdlmslate(view_attributes *viewot);
	sdlmslate(int _x_y, masterslate *controlpointt);
	~sdlmslate ();
	//defaultobject
	slateobject* give_default_slateobject (slate *parent);
	//defaultobject end
	slaveslate* give_slave_slate(int x,int y,masterslate *controlpointt);
	masterslate* give_master_slate(int pos_x_y_next, masterslate *controlpointt);
	
private:
	//friend sdlmslate;

};


class sdlcontroller : public controller
{
public:
	sdlcontroller();
	~sdlcontroller();
	
	void drawthread();
	void execevent(void *);
	
	bool comparescreen(void *screen);
protected:

private:
	//vector<SDL_Surface*> surfacestoscreens;
	const SDL_VideoInfo *sysdisplay;
	thread gthread;
};


class sdlmcontroller : public mastercontroller
{
public:
	sdlmcontroller();
	~sdlmcontroller();
	void iodevicethread();
	controller* givecontroller(void *);
private:
    SDL_Event event;
};

*/
/**
class sdlmain : public master
{
	sdlmain(int argc, char *argv[]);
	
}*/

void sdlmain(int argc, char *argv[]);
 


#endif // _SDLBACKEND_H_
