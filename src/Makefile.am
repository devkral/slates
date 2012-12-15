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
	slates.cc \
	slates.h \
	gtkmmbackend.cc \
	gtkmmbackend.h

slates_CXXFLAGS = -std=c++11 

slates_LDFLAGS = 

slates_LDADD = $(SLATES_LIBS)


