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

#include "sdl_slateotypes.h"



sdlemptyprivat::~sdlemptyprivat()
{
	if (iseverset==true)
	{
		SDL_FreeSurface(emptysur);
		SDL_DestroyTexture (emptytex);
	}
}

void sdlemptyprivat::init_colors(SDL_Surface *in)
{
	if (iseverset==false)
	{
		lockonwriteread.lock();
		white=SDL_MapRGBA (in->format, 255,255,255,255);
		black=SDL_MapRGBA (in->format, 0,0,0,255);
		lockonwriteread.unlock();
	}
}


void sdlemptyprivat::set_emptysur(SDL_Surface *in, SDL_Renderer *renderer)
{
	if (iseverset==false)
		lockonwriteread.lock();
	else
		if (lockonwriteread.try_lock()==false)
			return ;
	emptysur=in;
	
	if(emptytex!=0)
		SDL_DestroyTexture (emptytex);
	emptytex=SDL_CreateTextureFromSurface (renderer,emptysur);
	
	iseverset=true;
	lockonwriteread.unlock();
}
SDL_Texture *sdlemptyprivat::get_emptytex()
{
	if (iseverset==false)
		lockonwriteread.lock();
	else
		lockonwriteread.try_lock();
	return emptytex;
	lockonwriteread.unlock();
}

sdlemptyprivat sdlemptyoo;
