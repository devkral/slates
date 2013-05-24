/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * slates
 * Copyright (C) 2013 alex <devkral@web.de>
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software
 * and associated documentation files (the "Software"),
 * to deal in the Software without restriction,
 * including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _CONFREADER_H_
#define _CONFREADER_H_

#include <string>
//#include <regex>
//regex would be nice if there would 1. work 2. there were sane tutorials including ^ and $ signs

#define buffersize 256

using namespace std;

typedef struct _parsedob
{
	string varpart="";
	string valuepart="";
	string whole="";
	
}parsedob;


class confreader
{
	public:
		confreader(string file);
		~confreader();
		void set_single_variable(string varname, string varvalue);
		void add_variable(string varname, string varvalue);
		void del_variable(string varname, string varvalue="");
		string get_variable(string varname);
	
	private:
		string filename;
		//regex split_bc;
		//regex split_varval;
		
		
};

#endif //CONFREADER
