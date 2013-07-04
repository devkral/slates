## Process this file with automake to produce Makefile.in

## Created by Anjuta

AUTOMAKE_OPTIONS = subdir-objects


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(GTKMM_CFLAGS) \
	$(SDL2_CFLAGS) \
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
	confreader.cc \
	confreader.h \
	slatearea.cc \
	slatearea.h  \
	slateareascreen.cc \
	slateareascreen.h


slates_SOURCES += \
	lockslate.cc \
	lockslate.h \
	groupslate.cc \
	groupslate.h \
	configslate.cc \
	configslate.h \
	emptyslate.cc \
	emptyslate.h
	windowslate.cc \
	windowslate.h \
	sysslate.cc \
	sysslate.h
	



if IS_COMPILED_WITH_TESTBACKEND
slates_SOURCES += testbackend/testbackend.cc \
	testbackend/testbackend.h \
	testbackend/tviewport.cc \
	testbackend/tviewport.h \
	testbackend/tlockslate.cc \
	testbackend/tlockslate.h \
	testbackend/temptyslate.cc \
	testbackend/temptyslate.h \
	testbackend/tslateareascreen.cc \
	testbackend/tslateareascreen.h \
	testbackend/tslatearea.cc \
	testbackend/tslatearea.h
endif

if IS_COMPILED_WITH_GTKMM
slates_SOURCES +=  gtkmmbackend/gtkmmbackend.cc \
	gtkmmbackend/gtkmmbackend.h \
	gtkmmbackend/gtkmm_viewport.cc \
	gtkmmbackend/gtkmm_viewport.h \
	gtkmmbackend/gtkmm_lockslateo.cc \
	gtkmmbackend/gtkmm_lockslateo.h \
	gtkmmbackend/gtkmm_emptyslateo.cc \
	gtkmmbackend/gtkmm_emptyslateo.h \
	gtkmmbackend/gtkmm_screenobject.cc \
	gtkmmbackend/gtkmm_screenobject.h \
	gtkmmbackend/gtkmm_slatearea.cc \
	gtkmmbackend/gtkmm_slatearea.h
endif

if IS_COMPILED_WITH_SDL
slates_SOURCES += sdlbackend/sdlbackend.cc \
	sdlbackend/sdlbackend.h \
	sdlbackend/sdl_viewport.cc \
	sdlbackend/sdl_viewport.h \
	sdlbackend/sdl_emptyslateo.cc \
	sdlbackend/sdl_emptyslateo.h \
	sdlbackend/sdl_screenobject.cc \
	sdlbackend/sdl_screenobject.h \
	sdlbackend/sdl_slatearea.cc \
	sdlbackend/sdl_slatearea.h 
endif

if IS_COMPILED_WITH_X
#slates_SOURCES += 

endif

if IS_COMPILED_WITH_WAYLAND
#slates_SOURCES +=

endif

slates_CXXFLAGS = -std=c++11

slates_LDADD = \
    $(GTKMM_LIBS) \
    $(SDL2_LIBS) \
    $(SLATES_LIBS)

