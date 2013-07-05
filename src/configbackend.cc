// License see COPYING

#include "configbackend.h"

#include <fstream>
#include <iostream>
#include <cctype>
#include <cstring>


configbackend::configbackend(string file)
{
	filename=file;
	init();
}
configbackend::configbackend()
{
	configbackend((string)slateconfigfilename);
}

configbackend::~configbackend()
{
	
}

void configbackend::init()
{
	confrwlock.lock();
	fstream tempout(filename.c_str(),ios_base::out);
	tempout.close();
	

	
	confrwlock.unlock();
}


void reset(parsedob *ob)
{
	ob->varpart="";
	ob->valuepart="";
	ob->whole="";
}

bool is_end_of_parseable(char buf[buffersize], int pos, int paraphrases)
{
	for (unsigned int count=pos; count<strlen(buf); count++)
	{
		if (buf[count]=='#' && paraphrases%2==0)
			return true;
		if (!isblank(buf[count]) && buf[count]!='\n' )
			return false;
	}
	return true;
		
}


int parseline2(fstream *confstr, parsedob *ob, int state, int paraphrases);

int parseline(fstream *in, parsedob *ob)
{
	int state=0; //0 var part 1 value part 2 comment part
	int paraphrases=0;
	reset(ob);
	return parseline2(in, ob, state, paraphrases);
}

int parseline2(fstream *confstr, parsedob *ob, int state, int paraphrases)
{
	char buffer[buffersize];
	if (confstr->peek()==EOF)
		return 2;
	
	confstr->get(buffer,buffersize,'\n');
	int nextchar=confstr->get();
	if (nextchar!='\n' && nextchar!=EOF)
	{
		cerr << "Error: Line too long; max length: " << buffersize << "\n";
		return 1;
	}
	
	
	int len=strlen(buffer);
		
	if (len>buffersize)
		throw (char*)"Bufferoverflow configparser";
	
	
	for (int count=0;count<len;count++)
	{		
		if (state==2)
		{
			ob->whole+=buffer[count];
			continue;
		}
		
		
		if (state==0 && buffer[count]==' ')
		{
			ob->whole+=buffer[count];
			continue;
		}
		
		if (state==0 && buffer[count]=='=' && paraphrases%2==0)
		{
			state=1;
			ob->whole+=buffer[count];
			continue;
		}
		
		if (buffer[count]=='"') //state<2 && 
		{
			paraphrases++;
			ob->whole+=buffer[count];
			continue;
		}
		if (buffer[count]=='#' && paraphrases%2==0) //state<2 && 
		{
			if (paraphrases%2==0)
				state=2;
			ob->whole+=buffer[count];
			continue;
		}
		//state==1 because no freak programmer should insert horrible long variable names
		if (state==1 &&  buffer[count]=='\\' && is_end_of_parseable(buffer,count,paraphrases))
		{
			ob->whole+=&buffer[count];
			ob->whole+="\n";
			return parseline2(confstr,ob,state,paraphrases);
		}
		
		if (state==0)
		{
			ob->varpart+=buffer[count];
			ob->whole+=buffer[count];
			continue;
		}
		if (state==1)
		{
			ob->valuepart+=buffer[count];
			ob->whole+=buffer[count];
			continue;
		}
	}
	ob->whole+="\n";
	return 0;
	
}




void configbackend::set_single_variable(string varname, string varvalue)
{
	confrwlock.lock();
	string searchtemp="";
	string new_var_line=varname+"="+varvalue+"\n";
	string fullfilestring="";
	bool is_set=false;
	parsedob parsed;
	int status=0;
	fstream confstr(filename.c_str(),ios_base::in);
	while (1)
	{
		
		status=parseline(&confstr,&parsed);
		if (status==1)
			return;
		if (status==2)
			break;
		
		if (parsed.varpart!=varname)
			fullfilestring+=parsed.whole;
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
	confrwlock.unlock();
}


void configbackend::add_variable(string varname, string varvalue)
{
	confrwlock.lock();
	fstream confstr;
	string new_var_line=varname+"="+varvalue+"\n";
	confstr.open(filename.c_str(),ios_base::out | ios_base::app);
	confstr.write(new_var_line.c_str(),new_var_line.length());
	confstr.close();
	confrwlock.unlock();
}

void configbackend::del_variable(string varname, string varvalue)
{
	confrwlock.lock();
	string searchtemp="";
	string fullfilestring="";
	parsedob parsed;
	int status=0;
	fstream confstr(filename.c_str(),ios_base::in);
	while (confstr.eof()==false)
	{
		status=parseline(&confstr,&parsed);
		if (status==1)
			return;
		if (status==2)
			break;
			
		if (parsed.varpart!=varname && (varvalue=="" || parsed.valuepart!=varvalue))
			fullfilestring+=parsed.whole;
	}
	confstr.close();
	confstr.open(filename.c_str(),ios_base::out | ios_base::trunc);
	confstr.write(fullfilestring.c_str(),fullfilestring.length());
	confstr.close();
	confrwlock.unlock();
}

string configbackend::get_variable(string varname)
{
	confrwlock.lock();
	string collect="";
	parsedob parsed;
	int status=0;
	
	fstream confstr(filename.c_str(),ios_base::in);
	while (1){
		status=parseline(&confstr,&parsed);
		if (status==1)
			return "";
		if (status==2)
			break;
		if (parsed.varpart==varname)
			collect+=parsed.valuepart+"\n";
		
	};
	confstr.close();
	if (collect.find("\n")!=EOF)
		collect=collect.erase(collect.rfind("\n"));
	confrwlock.unlock();
	return collect;
}


