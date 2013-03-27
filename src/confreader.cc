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
#include "confreader.h"
#include <fstream>

confreader::confreader(string file)
{
	filename=file;
	fstream tempout(filename.c_str(),ios_base::out);
	tempout.close();
}

confreader::~confreader()
{
	
}

void confreader::set_variable(string varname, string varvalue)
{
	fstream confstr;
	string searchtemp="";
	string new_var_line=varname+"="+varvalue+"\n";
	char buffer[buffersize];
	string fullfilestring="";
	bool is_set=false;
	confstr.open(filename.c_str(),ios_base::in);
	while (is_set==false && confstr.eof()==false)
	{
		while (confstr.peek()==' ')
			confstr.get();		
		confstr.getline(buffer,buffersize,'\n');
		searchtemp=buffer;
		if (!searchtemp.find(varname)==0)
			fullfilestring+=searchtemp+"\n";
		else if (is_set==false)
		{
			fullfilestring+=new_var_line;
			is_set=true;
			break;
		}
		else  //removes duplicates
		{
			fullfilestring+="#"+searchtemp+"\n";
			
		}
			
	}
	confstr.close();
	if (is_set==true)
	{
		confstr.open(filename.c_str(),ios_base::out | ios_base::trunc);
		confstr.write(fullfilestring.c_str(),fullfilestring.length());
		confstr.close();
	}else
	{
		confstr.open(filename.c_str(),ios_base::out | ios_base::app);
		confstr.write(new_var_line.c_str(),new_var_line.length());
		confstr.close();
	}
}

void confreader::del_variable(string varname)
{
	string searchtemp="";
	string fullfilestring="";
	fstream confstr(filename.c_str(),ios_base::in);
	char buffer[buffersize];
	while (confstr.eof()==false)
	{
		confstr.getline(buffer,buffersize,'\n');
		searchtemp=buffer;
		if (!searchtemp.find(varname)==0)
			fullfilestring+=searchtemp+"\n";
	}
	confstr.close();
	confstr.open(filename.c_str(),ios_base::out | ios_base::trunc);
	confstr.write(fullfilestring.c_str(),fullfilestring.length());
	confstr.close();
}

string confreader::get_variable(string varname)
{
	char buffer[buffersize];
	string searchtemp="";
	int nextchar=' ';
	fstream confstr(filename.c_str(),ios_base::in);
	
	do{
		while (confstr.peek()==' ')
			confstr.get();
		confstr.get(buffer,buffersize,'\n');
		searchtemp=buffer;
		nextchar=confstr.get();
		if (nextchar=='\n' || nextchar==EOF )
		{
			if (searchtemp.find(varname)==0)
			{
				return searchtemp.erase(0,searchtemp.find("=")+1);
			}
		}
		else
			throw ((char *)"line too long");
	}while (nextchar!=EOF);
	confstr.close();
	return "";
}


