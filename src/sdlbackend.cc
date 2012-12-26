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


#define widthf sysdisplay->current_w
#define heightf sysdisplay->current_h

#ifdef COMPILED_WITH_SDL
#include "sdlbackend.h"
#include <iostream>
//#include <cstdlib>
#include <unistd.h>
#include "SDL.h"
using namespace std;

//slateobject

sdlslateobject::sdlslateobject(slate *leftuppercornert) : slateobject(leftuppercornert)
{
	leftuppercorner=leftuppercornert;
	SDL_Rect u;
	u.x=0;
	u.y=0;
	u.h=100;
	u.w=100;
	//cout << (int)screens.back()->format->BitsPerPixel;
	//SDL_FillRect(screens.back(), &u, 2552552550);
}


//slateobject end

//masterslates

sdlmslate::sdlmslate(view_attributes *viewot) : masterslate(viewot)
{
	//viewo=viewot;
}

sdlmslate::sdlmslate(int pos_x_y_next, masterslate *controlpointpret) : masterslate(pos_x_y_next,controlpointpret)
{
	
}

sdlmslate::~sdlmslate ()
{
	//~masterslate();
	if (is_beginning_slate ())
	{
		SDL_FreeSurface((SDL_Surface*)viewo->drawing_area);
		viewo->drawing_area=0;
		
		delete viewo;
		viewo=0;
	}

}

masterslate* sdlmslate::give_master_slate(int pos_x_y_next, masterslate *controlpointt)
{
	return new sdlmslate(pos_x_y_next,controlpointt);
}


slaveslate* sdlmslate::give_slave_slate(int x,int y,masterslate *controlpointt)
{

	return new sdlsslate(x,y,controlpointt);
}
//masterslates end
//slaveslates
sdlsslate::sdlsslate(int x, int y,masterslate *controlpointt) : slaveslate (x,y,controlpointt)
{
	//screen=controlpointt->screen;

}

//slaveslates end


//defaultobject
slateobject *sdlsslate::give_default_slateobject(slate *parent)
{
	return new sdlslateobject(parent);
}

slateobject *sdlmslate::give_default_slateobject(slate *t)
{
	return new sdlslateobject(t);
}

//defaultobject end


//sdlcontroller
sdlcontroller::sdlcontroller() : controller()
{
	sysdisplay=SDL_GetVideoInfo();

	SDL_Surface *tempscreen=0;
	view_attributes *tempattri=0;
	
	tempscreen=SDL_SetVideoMode(widthf, heightf, 24, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT);// | SDL_FULLSCREEN);
	if (tempscreen == 0)
	{
	    cerr << "Can't set video mode: " << SDL_GetError() << std::endl;
		exit(1);
	}

	viewo=new view_attributes;
	
	viewo->reso_x=widthf;
	viewo->reso_y=heightf;
	viewo->drawing_area=(void*)tempscreen;
	screen=new sdlmslate (viewo);

}
sdlcontroller::~sdlcontroller()
{
	delete screen;
	screen=0;
}

bool sdlcontroller::comparescreen(void * screen)
{
}
void sdlcontroller::execevent(void * event)

{
}


//sdlcontroller end

//sdlmcontroller
sdlmcontroller::sdlmcontroller()
{
	addscreen(0);
	iodevicethread();
}
void sdlcontroller::drawthread()
{
	SDL_Flip((SDL_Surface*)viewo->drawing_area);

}

void sdlmcontroller::iodevicethread()
{
	while (!done)
	{

		//SDL_WaitEvent (&event);
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_BUTTON_WHEELUP:
					notify_controller (&event);
					break;

						
				case SDL_KEYDOWN:
					done = true;
					break;


				case SDL_QUIT:
					done = true;
					break;
			}
		}
	//SDL_Flip(screens.back());
	SDL_Delay(10);
		 
	}
}


controller* sdlmcontroller::givecontroller(void *display)
{
	return new sdlcontroller ();
}





//sdlmcontroller end



int sdlmain(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "Can't init SDL:  " << SDL_GetError() << "\n";
        return 1;
    }
	
	//SDL_EnableUNICODE(1);
    atexit(SDL_Quit);
	//try{
		sdlmcontroller();
	//}
    return 0;
}

#endif //COMPILED_WITH_SDL