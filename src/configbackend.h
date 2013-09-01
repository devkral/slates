// License see COPYING

#ifndef _CONFIGBACKEND_H_
#define _CONFIGBACKEND_H_

#include <string>
#include <mutex>
#include <cassert>

using namespace std;

#ifdef _WIN64
#define WINDOWS

#elif _WIN32
#define WINDOWS

#elif __APPLE__
#define UNIX

#elif __linux
#define UNIX

#elif __unix
#define UNIX

#elif __posix
#define UNIX

#endif


#define OP_SUCCESS 0
#define SL_DESTROY_FAILED -2
#define SL_NOT_EMPTY -3 //used in slate
#define POS_NEG -4
#define POS_OUT_OF_RANGE -5

//will be replaced
/**#define MASTER_HANDLED 1
#define MASTER_UNHANDLED 2
#define MASTER_QUIT 3
#define MASTER_TIMEDOUT 4*/

#define TYPE_empty 1
#define TYPE_locked 2
#define TYPE_filled 3

typedef struct _parsedob
{
	string varpart="";
	string valuepart="";
	string whole="";
	
}parsedob;



//actions
#define ADD_SLICE 0
#define REMOVE_SLICE 1
#define EXP_ALL_VIEW 2
#define EXP_FOCUS_VIEW 3
#define EXP_FOCUS_SLATE 4
#define EXP_ACTIVE_SLATES 5
#define ACTIVATE_LOCK 6
#define RELOAD_DE 7
#define QUIT_DE 8
#define EVENT_HANDLED_INTERN 9 //handled internally
//implemented???
#define FULLSCREEN 10 //also archived by scrolling
#define UNFULLSCREEN 11
#define RESIZE_SLATEAREA 12
#define MOVE_SLATEAREA 13



#ifndef slateconfigfilename
#define slateconfigfilename "~/.slates"
#endif



// buffersize
#define buffersize 256


#define deftheme (theme="")
#define defborder (theme="")

class configbackend
{
	public:
		configbackend();
		configbackend(string filename);
		~configbackend();
		void set_single_variable(string varname, string varvalue);
		void add_variable(string varname, string varvalue);
		void del_variable(string varname, string varvalue="");
		string get_variable(string varname);

	protected:

	private:
		void init();
		string filename;
		mutex confrwlock;

	/**	unordered_map<string,string> defaultvars={
			{"theme","/usr/share/grub/themes/starfield/starfield.png"},
			{"border","3"},
			{"scollup",""},
			{"scolldown",""}
		};*/
};

#endif // _CONFIGBACKEND_H_

