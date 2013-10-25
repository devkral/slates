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
	main.cpp \
	master.cpp \
	master.h \
	viewport.cpp \
	viewport.h \
	slate.cpp \
	slate.h \
	slatearea.cpp \
	slatearea.h  \
	slateareascreen.cpp \
	slateareascreen.h \
	configbackend.cpp \
	configbackend.h


slates_SOURCES += \
	lockslate.cpp \
	lockslate.h \
	groupslate.cpp \
	groupslate.h \
	configslate.cpp \
	configslate.h \
	emptyslate.cpp \
	emptyslate.h \
	windowslate.cpp \
	windowslate.h \
	sysslate.cpp \
	sysslate.h



if IS_COMPILED_WITH_TESTBACKEND
slates_SOURCES += testbackend/testbackend.cpp \
	testbackend/testbackend.h \
	testbackend/tviewport.cpp \
	testbackend/tviewport.h \
	testbackend/tlockslate.cpp \
	testbackend/tlockslate.h \
	testbackend/temptyslate.cpp \
	testbackend/temptyslate.h \
	testbackend/tsysslate.cpp \
	testbackend/tsysslate.h \
	testbackend/tslatearea.cpp \
	testbackend/tslatearea.h
endif


if IS_COMPILED_WITH_SDL
slates_SOURCES += sdlbackend/sdlbackend.cpp \
	sdlbackend/sdlbackend.h \
	sdlbackend/sdlroutines.cpp \
	sdlbackend/sdlroutines.h \
	sdlbackend/sdlviewport.cpp \
	sdlbackend/sdlviewport.h \
	sdlbackend/sdlemptyslate.cpp \
	sdlbackend/sdlemptyslate.h \
	sdlbackend/sdllockslate.cpp \
	sdlbackend/sdllockslate.h \
	sdlbackend/sdlslatearea.cpp \
	sdlbackend/sdlslatearea.h
endif

if IS_COMPILED_WITH_X
slates_SOURCES += Xbackend/xbackend.cpp \
	Xbackend/xbackend.h \
	Xbackend/xroutines.cpp \
	Xbackend/xroutines.h \
	Xbackend/xviewport.cpp \
	Xbackend/xviewport.h \
	Xbackend/xlockslate.cpp \
	Xbackend/xlockslate.h \
	Xbackend/xemptyslate.cpp \
	Xbackend/xemptyslate.h \
	Xbackend/xsysslate.cpp \
	Xbackend/xsysslate.h \
	Xbackend/xslatearea.cpp \
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

