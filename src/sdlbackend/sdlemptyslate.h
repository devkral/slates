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

#ifndef _SDL_EMPTYSLATEO_H_
#define _SDL_EMPTYSLATEO_H_
#include "emptyslate.h"
class emptyslate;
#include "sdlroutines.h"


//#include <mutex>


static SDL_Texture *emptytex=0;
static SDL_Surface *epicture=0;
static int32_t emptyusecount=0;

class sdlemptyslate : public emptyslate
{
public:
	sdlemptyslate(slatearea *parentt, master *parent_mastert);
	~sdlemptyslate();
	void update();
	void set_slatearea(slatearea *in);
	void create_emptyslate ();
	void handle_event(void *event);
	bool isdirty();
protected:

//	sdlempty widget;
	int update_interval;

	
	//mutex renderprot;	

	SDL_Window *ewindow=0;
	SDL_Renderer *erender=0;
	SDL_Rect windowbounds;

private:
	bool wasinit=false;
	
	//SDL_Surface *epicture;
};

#endif // _EMPTYSLATEO_H_

