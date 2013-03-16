## Process this file with automake to produce Makefile.in

## Created by Anjuta

SUBDIRS = sdlbackend gtkmmbackend oldstuff

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
    $(GTKMM_CFLAGS) \
    $(SDL_CFLAGS) \
	$(SLATES_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = slates

slates_SOURCES = \
	main.cc \
	sdlbackend/sdlbackend.h \
	sdlbackend/sdlbackend.cc \
	gtkmmbackend/gtkmmbackend.h \
	gtkmmbackend/gtkmmbackend.cc \
	testbackend/testbackend.h \
	testbackend/testbackend.cc \
	master.cc \
	master.h \
	viewport.cc \
	viewport.h \
	slate.cc \
	slate.h \
	slateobject.cc \
	slateobject.h \
	windowslateo.cc \
	windowslateo.h \
	lockslateo.cc \
	lockslateo.h \
	sysslateo.cc \
	sysslateo.h \
	constdef.h 
	
####
##	sdlbackend \
##	gtkmmbackend \


slates_CXXFLAGS = -std=c++11 

slates_LDADD = $(SLATES_LIBS) \
    $(GTKMM_LIBS) \
    $(SDL_LIBS)

