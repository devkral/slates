// Licence see COPYING


#ifndef constdefh
#define constdefh
#include <cassert>

#include <chrono>

static std::chrono::seconds defaulttimeout(4);

#define OP_success 0
#define SL_destroy_failed -2
#define SL_not_empty -3 //used in slate
#define xy_negative -4
#define xy_out_of_range -4

#define MASTER_HANDLED 1
#define MASTER_UNHANDLED 2
#define MASTER_QUIT 3
#define MASTER_TIMEDOUT 4

#define TYPE_empty 1
#define TYPE_locked 2
#define TYPE_filled 3


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







#endif