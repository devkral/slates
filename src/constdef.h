/*
 * constdef.h
 *
 * Copyright (C) 2013 - alex
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef constdefh
#define constdefh

#define OP_success 0
#define SL_destroy_failed -2
#define SL_not_empty -3 //used in slate

#define TYPE_sysslate 1
#define TYPE_emptyslate 2
#define TYPE_lockslate 3
#define TYPE_windowslate 4


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