## Process this file with automake to produce Makefile.in

## Created by Anjuta



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
	controller.cc \
	controller.h \
	sdlbackend.cc \
	sdlbackend.h

slates_CXXFLAGS = -std=c++11 

slates_LDFLAGS = 

slates_LDADD = $(SLATES_LIBS)


