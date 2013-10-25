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
	save();
}

void configbackend::init()
{
	confrwlock.lock();
	fstream tempout(filename.c_str(),ios_base::out);
	tempout.close();
	confrwlock.unlock();
}


void configbackend::load()
{
	confrwlock.lock();
	config_runtime.clear();
	string checktemp="";
	string value_name;
	vector<string> value_list;
	
	size_t delimiter_varval=string::npos;
	//delimiter_valval=std::npos,
	//delimiter_comment=std::npos;
	ifstream loadtemp(filename);
	loadtemp >> checktemp;
	while (!loadtemp.eof())
	{
/**		delimiter_comment=checktemp.find("#");
		while (delimiter_comment!=std::npos && checktemp.find("\\#")+1 == delimiter_comment)
			delimiter_comment=checktemp.find("#",delimiter_comment);
		if (delimiter_comment!=std::npos)
			checktemp.erase(delimiter_comment);*/

		
		while (checktemp.find("\t")!=string::npos)
				checktemp.erase(checktemp.find("\t"),checktemp.find("\t"));
		while (checktemp.find(" ")!=string::npos)
			 if (checktemp.find("\\ ")+1 != checktemp.find(" "))
				checktemp.erase(checktemp.find(" "),checktemp.find(" "));
			
		delimiter_varval=checktemp.find("=");
		if (delimiter_varval!=string::npos && checktemp.find("\\=")+1 !=delimiter_varval )
		{
			while (checktemp.find("\\=") < delimiter_varval)
				checktemp.erase(checktemp.find("\\="),checktemp.find("\\="));
			

			value_name=checktemp.substr(0,delimiter_varval-1);
			if (value_name.empty())
			{
				cerr << "Invalid fileformat: \"=\" without valuename\n";
				goto end_configread;
			}
			
			checktemp.erase(0,delimiter_varval);
			while (checktemp.find("=")!=string::npos)
			{
				if (checktemp.find("=")==checktemp.find("\\=")+1 )
				{
					checktemp.erase(checktemp.find("\\="),checktemp.find("\\="));
				}
				else
				{
					cerr << "Invalid fileformat: an uncommented \"=\" too much\n";
					goto end_configread;
				}
			}
/**			delimiter_valval=checktemp.find(",");
			while (delimiter_valval!=std::npos)
			{
				if (checktemp.find("\\,")+1 !=delimiter_valval  )
				{
					while (checktemp.find("\\,") !=std::npos && checktemp.find("\\,")<delimiter_valval)
						checktemp.erase(checktemp.find("\\,"),checktemp.find("\\,"));

					config_runtime.insert(value_name,checktemp.substr(0,delimiter_valval));
			    }
				delimiter_valval=checktemp.find(",",delimiter_valval);
			}*/
			if (!checktemp.empty())
				config_runtime.insert(std::make_pair(value_name,checktemp));
		}
end_configread:
		checktemp.clear();
		loadtemp >> checktemp;
	}
	
	confrwlock.unlock();
}


void configbackend::save()
{
	confrwlock.lock();
	string tempstr="";
	std::unordered_multimap<std::string,std::string>::const_iterator runtime_it=config_runtime.begin();
	std::pair<std::unordered_multimap<std::string,std::string>::const_iterator,std::unordered_multimap<std::string,std::string>::const_iterator>
			default_result_it;
	bool compare_successful=true;
	ofstream writeconfig_stream(filename,ios_base::trunc);
	
	while ( runtime_it!=config_runtime.end())
	{
		compare_successful=true;
		tempstr=(*runtime_it).second;
		default_result_it=config_default.equal_range((*runtime_it).first);
		if (default_result_it.first!=config_default.end() && !tempstr.empty())
		{
			compare_successful=false;
			while (default_result_it.first!=default_result_it.second)
			{
				if (default_result_it.first->second==tempstr)
				{
					compare_successful=true;
					break;
				}
				default_result_it.first++;
			}
		}

			
		if (!compare_successful)
		{
			while (tempstr.find (" ")!=string::npos && tempstr.find ("\\ ")+1!=tempstr.find (" "))
				tempstr.insert(tempstr.find (" "),"\\");
			while (tempstr.find ("\t")!=string::npos)
				tempstr.erase(tempstr.find ("\t"),tempstr.find ("\t"));
			while (tempstr.find ("=")!=string::npos && tempstr.find ("\\=")+1!=tempstr.find ("="))
				tempstr.insert(tempstr.find ("="),"\\");
			writeconfig_stream << (*runtime_it).first+"="+tempstr+"\n";
		}
		
		runtime_it++;
	}
	writeconfig_stream.close();
	confrwlock.unlock();

}

vector<string> configbackend::get_variable(string varname)
{
		std::pair<std::unordered_multimap<std::string,std::string>::const_iterator,std::unordered_multimap<std::string,std::string>::const_iterator>
			key_result=config_runtime.equal_range(varname);
	vector<string> tempvector;
	string tempstring="";
	if (key_result.first!=config_runtime.end())
	{
		while  (key_result.first!=key_result.second)
		{
			tempstring=key_result.first->second;
			tempvector.push_back(tempstring);
			key_result.first++;
		}
	}
	key_result=config_default.equal_range(varname);
	if (key_result.first!=config_default.end())
	{
		tempstring=key_result.first->second;
		tempvector.push_back(tempstring);
		key_result.first++;
	}
	else
	{
		cerr << "Variable: " << varname << " couldn't be found in config\nPlease define it at least in default config";
	}
	return tempvector;
}

void configbackend::reset_variable(string varname)
{
	config_runtime.erase(varname);
}

/**
string configbackend::search_variable(string value)
{
	config_runtime.erase(varname);
}*/


void configbackend::set_variable(string varname,vector<string> inobvec, bool shall_append=true)
{
	if (!shall_append)
		config_runtime.erase(varname);

	for (string temp : inobvec)
		config_runtime.insert(std::make_pair(varname,temp));
}

void configbackend::set_keybinding(string varname,string keycombination)
{
	vector<string> combvect={keycombination};
	set_variable ("key:"+varname,combvect,false);
}

string configbackend::get_keybindaction(string input_event)
{
	vector<string> vect_results=get_variable ("key:"+input_event);
	if (vect_results.empty())
		return "";
	else
		return vect_results[0];
}


/**
uint16_t configbackend::compare_input(void *)
{

};*/


/**
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


void configbackend::append_variable(string varname, string varvalue)
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

*/
