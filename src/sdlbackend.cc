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
#include <thread>
using namespace std;



//sdlborder
sdlborder::sdlborder(slateobject *parentt) : border(parentt)
{
	sdl_border_surf=SDL_GetVideoSurface ();

	uint32_t bcolor=SDL_MapRGBA (((SDL_Surface*)viewo->drawing_area)->format,
	255,0,0,100);
	SDL_FillRect (sdl_border_surf,NULL,bcolor);
}
sdlborder::~sdlborder()
{
	SDL_FreeSurface (sdl_border_surf);
	//SDL_Free
}

int sdlborder::construct(int x, int y, int weight, int height)
{
	sdl_border_rect.x=x;
	sdl_border_rect.y=y;
	sdl_border_rect.w=weight;
	sdl_border_rect.h=height;
	SDL_BlitSurface(sdl_border_surf,&sdl_border_rect,(SDL_Surface*)viewo->drawing_area,&sdl_border_rect);
	return 0;
}





//sdl-border end
//slateobject


sdlslateobject::sdlslateobject(slate *leftuppercornert) : slateobject(leftuppercornert)
{
	border_right=new sdlborder(this);
	border_bottom=new sdlborder(this);
	use_default_child();
}

void sdlslateobject::use_default_child()
{
	

}


void sdlslateobject::draw_borders()
{
	border_right->construct(0,0,10,10);
	
}


void sdlslateobject::draw_child()
{


}

void sdlslateobject::destroy_child()
{


}




//slateobject end

//masterslates

sdlmslate::sdlmslate(view_attributes *viewot) : masterslate(viewot)
{
	sobject=new sdlslateobject (this);
	//DEBUG
	sobject->draw_borders();
}

sdlmslate::sdlmslate(int pos_x_y_next, masterslate *controlpointpret) : masterslate(pos_x_y_next,controlpointpret)
{
	sobject=new sdlslateobject (this);
	//DEBUG
	//sobject->draw();
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

sdlsslate::~sdlsslate ()
{

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
sdlcontroller::sdlcontroller()// : controller()
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
	firstslate=new sdlmslate (viewo);
	drawthread();
	//gthread(std::thread(drawthread));

}
sdlcontroller::~sdlcontroller()
{
	run_graphic_thread=false;
	gthread.join();
	delete firstslate;
	firstslate=0;
}

bool sdlcontroller::comparescreen(void * screen)
{
}
void sdlcontroller::execevent(void * event)

{
}


void sdlcontroller::drawthread()
{
	while (run_graphic_thread)
	{
		SDL_Flip((SDL_Surface*)viewo->drawing_area);
		SDL_Delay(40);
		run_graphic_thread=false;
	}
}

//sdlcontroller end

//sdlmcontroller
sdlmcontroller::sdlmcontroller() : mastercontroller()
{
	addscreen(0);
	iodevicethread();
}
sdlmcontroller::~sdlmcontroller()
{

}



void sdlmcontroller::iodevicethread()
{
	while (run_io_thread)
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
					run_io_thread = false;
					break;


				case SDL_QUIT:
					run_io_thread = false;
					break;
			}
		}
	//SDL_Flip(screens.back());
//drawthread();
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