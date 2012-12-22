## Process this file with automake to produce Makefile.in

## Created by Anjuta



AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(SLATES_CFLAGS)\
	$(GTKMM_CFLAGS) \
	$(SDL_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = slates

slates_SOURCES = \
	main.cc \
	slate.cc \
	slate.h \
	gtkmmbackend.cc \
	gtkmmbackend.h \
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
	sdlbackend.cc \
	sdlbackend.h \
	controller.cc \
	controller.h \
	messages.cc \
	messages.h

slates_CXXFLAGS = -std=c++11 

slates_LDFLAGS = 

slates_LDADD = $(SLATES_LIBS) \
	$(GTKMM_LIBS) \
	$(SDL_LIBS)


