## Process this file with automake to produce Makefile.in

## Created by Anjuta

SUBDIRS = sdlbackend gtkmmbackend

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
	slate.cc \
	slate.h \
	masterslate.cc \
	masterslate.h \
	slaveslate.cc \
	slaveslate.h \
	slateobject.cc \
	slateobject.h \
	border.cc \
	border.h \
	widgets.cc \
	widgets.h \
	controller.cc \
	controller.h \
	messages.cc \
	messages.h \
	sdlbackend/sdlbackend.h \
	sdlbackend/sdlbackend.cc \
	gtkmmbackend/gtkmmbackend.h \
	gtkmmbackend/gtkmmbackend.cc 
	
####
##	sdlbackend \
##	gtkmmbackend \


slates_CXXFLAGS = -std=c++11 

slates_LDADD = $(SLATES_LIBS) \
    $(GTKMM_LIBS) \
    $(SDL_LIBS)

