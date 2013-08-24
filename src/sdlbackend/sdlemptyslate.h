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


#include <mutex>






class sdlemptyslate : public emptyslate
{
public:
	sdlemptyslate(master *parent_mastert);
	~sdlemptyslate();
	void update();
	void cleanup_handler ();
	void set_slatearea(slatearea *in);
	void handle_input(void *initializer);
	void handle_event(void *event, bool called_by_input);
protected:

//	sdlempty widget;
	int update_interval;
	SDL_Event event;
	bool specialcondition=false;
	//void set_visibility(bool t);

	//static???
	SDL_Surface *emptysur=0;
	SDL_Texture *emptytex=0;
	Uint32 white=0;
	Uint32 black=0;

private:
};

#endif // _EMPTYSLATEO_H_

