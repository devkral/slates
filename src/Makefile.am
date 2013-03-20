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
	master.cc \
	master.h \
	constdef.h \
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
	emptyslateo.cc \
	emptyslateo.h 



if IS_COMPILED_WITH_TESTBACKEND
slates_SOURCES += testbackend/testbackend.cc \
	testbackend/testbackend.h \
	testbackend/tviewport.cc \
	testbackend/tviewport.h \
	testbackend/tslate.cc \
	testbackend/tslate.h \
	testbackend/twindowslateo.cc \
	testbackend/twindowslateo.h \
	testbackend/tlockslateo.cc \
	testbackend/tlockslateo.h \
	testbackend/tsysslateo.cc \
	testbackend/tsysslateo.h \
	testbackend/temptyslateo.cc \
	testbackend/temptyslateo.h \
	testbackend/tscreenobject.cc \
	testbackend/tscreenobject.h
endif

if IS_COMPILED_WITH_GTKMM
slates_SOURCES +=  gtkmmbackend/gtkmmbackend.cc \
	gtkmmbackend/gtkmmbackend.h \
	gtkmmbackend/gtkmm_viewport.cc \
	gtkmmbackend/gtkmm_viewport.h \
	gtkmmbackend/gtkmm_slate.cc \
	gtkmmbackend/gtkmm_slate.h \
	gtkmmbackend/gtkmm_windowslateo.cc \
	gtkmmbackend/gtkmm_windowslateo.h \
	gtkmmbackend/gtkmm_lockslateo.cc \
	gtkmmbackend/gtkmm_lockslateo.h \
	gtkmmbackend/gtkmm_sysslateo.cc \
	gtkmmbackend/gtkmm_sysslateo.h \
	gtkmmbackend/gtkmm_emptyslateo.cc \
	gtkmmbackend/gtkmm_emptyslateo.h \
	gtkmmbackend/gtkmm_screenobject.cc \
	gtkmmbackend/gtkmm_screenobject.h
endif

if IS_COMPILED_WITH_SDL
slates_SOURCES += sdlbackend/sdlbackend.cc \
	sdlbackend/sdlbackend.h \
	sdlbackend/sdl_viewport.cc \
	sdlbackend/sdl_viewport.h \
	sdlbackend/sdl_slate.cc \
	sdlbackend/sdl_slate.h \
	sdlbackend/sdl_windowslateo.cc \
	sdlbackend/sdl_windowslateo.h \
	sdlbackend/sdl_lockslateo.cc \
	sdlbackend/sdl_lockslateo.h \
	sdlbackend/sdl_sysslateo.cc \
	sdlbackend/sdl_sysslateo.h \
	sdlbackend/sdl_emptyslateo.cc \
	sdlbackend/sdl_emptyslateo.h \
	sdlbackend/sdl_screenobject.cc \
	sdlbackend/sdl_screenobject.h
endif

slates_CXXFLAGS = -std=c++11 

slates_LDADD = \
    $(GTKMM_LIBS) \
    $(SDL_LIBS) \
    $(SLATES_LIBS) 

