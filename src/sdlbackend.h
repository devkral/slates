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

#ifdef COMPILED_WITH_SDL
#ifndef _SDLBACKEND_H_
#define _SDLBACKEND_H_
#include <SDL/SDL.h>
#include <vector>


#include "controller.h"

int sdlmain(int argc, char *argv[]);



class sdlslateobject : public slateobject
{
	public:
		sdlslateobject(slate *t);


};





class sdlsslate : public slaveslate
{
public:
	sdlsslate(int x, int y,masterslate *controlpointt);
	//defaultobject
	slateobject* give_default_slateobject (slate *t);
	//defaultobject end
	
private:
	sdlslateobject *sdlslateob;

};



class sdlmslate : public masterslate
{
public:
	sdlmslate(view_attributes *viewot);
	sdlmslate(int _x_y, masterslate *controlpointt);
	//defaultobject
	slateobject* give_default_slateobject (slate *t);
	//defaultobject end
	slaveslate* give_slave_slate(int x,int y,masterslate *controlpointt);
	masterslate* give_master_slate(int pos_x_y_next, masterslate *controlpointt);
	
private:
	SDL_Surface *master;

};


class sdlcontroller : public controller
{
public:
	sdlcontroller(int argc, char *argv[]);
	~sdlcontroller();
protected:

private:
	bool done = false;
	vector<SDL_Surface*> screens;
    SDL_Event event;
	const SDL_VideoInfo *sysdisplay;
};



#endif // _SDLBACKEND_H_
#endif //COMPILED_WITH_SDL
