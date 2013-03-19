## Process this file with automake to produce Makefile.in

## Created by Anjuta


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
	constdef.h \
	emptyslateo.cc \
	emptyslateo.h 


#why the hell it doesn't work? And who makes such easy tasks so hard? Are GNUs aliens from outer space?

ifdef(`COMPILED_WITH_TESTBACKEND',
	slates_SOURCES += testbackend/testbackend.cc \
		testbackend/testbackend.h 
')
	

ifdef(`COMPILED_WITH_GTKMM',
	slates_SOURCES += gtkmmbackend/gtkmmbackend.cc \
		gtkmmbackend/gtkmmbackend.h 
')

ifdef(`COMPILED_WITH_SDL',
	slates_SOURCES += sdlbackend/sdlbackend.cc \
		sdlbackend/sdlbackend.h 
')


slates_CXXFLAGS = -std=c++11 

slates_LDADD = \
    $(GTKMM_LIBS) \
    $(SDL_LIBS) \
    $(SLATES_LIBS) 

