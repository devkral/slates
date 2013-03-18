## Process this file with automake to produce Makefile.in

## Created by Anjuta

SUBDIRS = sdlbackend gtkmmbackend testbackend

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
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

if GTKMM
	slates_SOURCES += gtkmmbackend/gtkmmown.la
endif

if SDL
	slates_SOURCES += sdlbackend/sdlown.la
endif

dnl if TEST_BACKEND
	slates_SOURCES += testbackend/testown.la
dnl endif

####
##	sdlbackend \
##	gtkmmbackend \


slates_CXXFLAGS = -std=c++11 

slates_LDADD = $(SLATES_LIBS) \
    $(GTKMM_LIBS) \
    $(SDL_LIBS)

