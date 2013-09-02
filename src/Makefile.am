## Process this file with automake to produce Makefile.in

## Created by Anjuta

AUTOMAKE_OPTIONS = subdir-objects


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(X_CFLAGS) \
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
	viewport.cc \
	viewport.h \
	slate.cc \
	slate.h \
	slatearea.cc \
	slatearea.h  \
	slateareascreen.cc \
	slateareascreen.h \
	configbackend.cc \
	configbackend.h


slates_SOURCES += \
	lockslate.cc \
	lockslate.h \
	groupslate.cc \
	groupslate.h \
	configslate.cc \
	configslate.h \
	emptyslate.cc \
	emptyslate.h \
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
	testbackend/tsysslate.cc \
	testbackend/tsysslate.h \
	testbackend/tslatearea.cc \
	testbackend/tslatearea.h
endif


if IS_COMPILED_WITH_SDL
slates_SOURCES += sdlbackend/sdlbackend.cc \
	sdlbackend/sdlbackend.h \
	sdlbackend/sdlroutines.cc \
	sdlbackend/sdlroutines.h \
	sdlbackend/sdlviewport.cc \
	sdlbackend/sdlviewport.h \
	sdlbackend/sdlemptyslate.cc \
	sdlbackend/sdlemptyslate.h \
	sdlbackend/sdllockslate.cc \
	sdlbackend/sdllockslate.h \
	sdlbackend/sdlslatearea.cc \
	sdlbackend/sdlslatearea.h
endif

if IS_COMPILED_WITH_X
slates_SOURCES += Xbackend/xbackend.cc \
	Xbackend/xbackend.h \
	Xbackend/xroutines.cc \
	Xbackend/xroutines.h \
	Xbackend/xviewport.cc \
	Xbackend/xviewport.h \
	Xbackend/xlockslate.cc \
	Xbackend/xlockslate.h \
	Xbackend/xemptyslate.cc \
	Xbackend/xemptyslate.h \
	Xbackend/xsysslate.cc \
	Xbackend/xsysslate.h \
	Xbackend/xslatearea.cc \
	Xbackend/xslatearea.h
endif

if IS_COMPILED_WITH_WAYLAND
#slates_SOURCES +=

endif

slates_CXXFLAGS = -std=c++11 -pthread

slates_LDADD = \
    $(X_LIBS) \
    $(SDL2_LIBS) \
    $(SLATES_LIBS)

