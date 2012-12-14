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


#include "gtkmmbackend.h"
#include <iostream>
using namespace std;

/**template< class T_CppObject > Glib::RefPtr<T_CppObject>
transform_to_rptr(const Glib::RefPtr< Glib::Object >& p)
{
	return Glib::RefPtr<T_CppObject>::cast_dynamic(p);
}*/





gtk_slate::gtk_slate(): slategrid()
{
	slates_horizontal=1;
	slates_vertical=1;
	slategrid.attach(ttz,0,0,1,1);
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

	
	
}*/


void gtk_slate::split_slate(int height,int width)
{
	//logic: [] begins with 0 we begin with 1/slates_vertical
	cout << "height" << height << " width " << width << endl;
	for (int _height=slates_vertical; _height<slates_vertical+height; _height++)
	{
		cout << "halleluljah _height " << _height << endl;
		//slategrid.insert_row(_height);
		for (int counterw=0; counterw<slates_horizontal; counterw++)
			{
				cout << "halleluljah counterw " << counterw << endl;
				slategrid.attach(ttz,counterw,_height,1,1);
			}
	}
	slates_vertical=height;
	for (int _width=slates_horizontal; _width<slates_horizontal+width; _width++)
	{
		//slategrid.insert_column(_width);
		for (int counterh=0; counterh<slates_vertical; counterh++)
			{
				slategrid.attach(ttz,_width,counterh,1,1);
			}
	}
	slates_horizontal=width;
	show();
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

}


