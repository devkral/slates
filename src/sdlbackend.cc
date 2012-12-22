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
#include <SDL/SDL.h>
using namespace std;


sdlmslate::sdlmslate(view_attributes *viewot) : masterslate(viewot)
{
//SDL_SetClipRect();

}
slaveslate* sdlmslate::give_slave_slate(int x,int y,masterslate *controlpointt)
{

	return new sdlsslate(x,y,controlpointt);
}


sdlslateobject::sdlslateobject(slate *t) : slateobject(t)
{


}

masterslate* sdlmslate::give_master_slate(int pos_x_y_next, masterslate *controlpointt)
{

	//return new sdlmslate(pos_x_y_next,controlpointt);
}

sdlsslate::sdlsslate(int x, int y,masterslate *controlpointt) : slaveslate (x,y,controlpointt)
{




}


//defaultobject
slateobject *sdlsslate::give_default_slateobject(slate *t)
{
	return new sdlslateobject(t);
}

slateobject *sdlmslate::give_default_slateobject(slate *t)
{
	return new sdlslateobject(t);
}

//defaultobject end

sdlcontroller::sdlcontroller(int argc, char *argv[]) : controller()
{
	sysdisplay=SDL_GetVideoInfo();


	for (int z=0; z==0; z++)
	{
		SDL_Surface *tempscreen=SDL_SetVideoMode(widthf, heightf, 24, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT);// | SDL_FULLSCREEN);
        if (tempscreen == NULL)
		{
		    printf("Can't set video mode: %s\n", SDL_GetError());
    		exit(1);
		}
		screens.push_back (tempscreen);
	}
	SDL_Rect u;
	u.x=0;
	u.y=0;
	u.h=100;
	u.w=100;
	cout << (int)screens.back()->format->BitsPerPixel;
	SDL_FillRect(screens.back(), &u, 2552552550);
	while (!done)
	{

		//SDL_WaitEvent (&event);
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					done = true;
					break;


				case SDL_QUIT:
					done = true;
					break;
			}
		}
	SDL_Flip(screens.back());
	SDL_Delay(10);
		 
	}

}
sdlcontroller::~sdlcontroller()
{

	//for (std::vector<SDL_Surface>::iterator it = screens.begin(); it != screens.end(); ++it)
	while (!screens.empty())
	{
		SDL_FreeSurface(screens.back());
		screens.pop_back();

	}
}

int sdlmain(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "Can't init SDL:  " << SDL_GetError() << "\n";
        return 1;
    }

	
	//SDL_EnableUNICODE(1);
    atexit(SDL_Quit);

	
	sdlcontroller(argc,argv);

	

    return 0;


}
#endif //COMPILED_WITH_SDL