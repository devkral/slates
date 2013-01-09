/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
 * Copyright (C) 2012 alex <>
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



#ifdef COMPILED_WITH_GTKMM
#include "gtkmmbackend.h"
#include <iostream>
using namespace std;



/**
gtkmmcontroller::gtkmmcontroller()
{



}*/



/**

gtk_slate::gtk_slate(): slategrid()
{
	slates_horizontal=1;
	slates_vertical=1;
	slategrid.attach(ttz,1,1,1,1);
	ttz.signal_clicked ().connect(sigc::mem_fun(*this,&gtk_slate::leftclick));
}

gtk_sys_slate::gtk_sys_slate()
{
	set_label("Slate");
	//slategrid->attach();
}
/**
void gtk_slate::fill_slate(int height,int width)
{
	for (int counterh=slates_vertical; counterh<slates_vertical+height; counterh++)
			for (int counterw=slates_horizontal; counterw<slates_horizontal+width; counterw++)
				{
					slategrid.attach(ttz,counterw,counterh,1,1);
				}

	
	
}


void gtk_slate::split_slate(int hor_parts,int vert_parts)
{
	slategrid.set_size_request (slates_horizontal+hor_parts,slates_vertical+vert_parts);
	//logic: [] begins with 0 we begin with 1/slates_vertical
	cout << "height" << vert_parts << " width " << hor_parts << endl;
	for (int _height=slates_vertical+1; _height<=slates_vertical+vert_parts; _height++)
	{
		//slategrid.insert_row(_height);
		//slategrid.insert_row(0);
		for (int counterw=1; counterw<=slates_horizontal; counterw++)
			{
				cout << "attach to " << counterw << " " << _height << endl;
				slategrid.attach(ttd,counterw,_height,1,1);
			}
	}
	slates_vertical+=vert_parts;
	for (int _width=slates_horizontal+1; _width<=slates_horizontal+hor_parts; _width++)
	{
		//slategrid.insert_column(_width);
		//slategrid.insert_column(0);
		for (int counterh=1; counterh<=slates_vertical; counterh++)
			{
				cout << "2loopattach to " << _width << " " << counterh << endl;
				slategrid.attach(ttz,_width,counterh,1,1);
			}
	}
	slates_horizontal+=vert_parts;
	show();
	cout << slates_vertical << endl << slates_horizontal << endl;
	//fill_slate(height,width);
}

Gtk::Grid* gtk_slate::return_widget()
{
	return &slategrid;
}

void gtk_slate::leftclick()
{
	split_slate(1,1);
	show();
}

void gtk_slate::show()
{
	//slategrid.show();
	slategrid.show_all ();
	slategrid.show_all_children ();

}
*/

int gtkmmmain(int argc, char *argv[])
{
		Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,
      "org.slates.mainslate");
	Gtk::Window window;
	window.set_title ("slates");
	//slate tt;
	Gtk::Button tz;
	tz.set_label("zz");
	//Gtk::Grid *t=(tt.return_widget());
	//window.add(*(tt.return_widget()));
	//tt.show();

	return app->run(window);
}
#endif //COMPILED_WITH_GTKMM
