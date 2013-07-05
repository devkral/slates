dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT([slates],[0.1])

 AC_PROG_CXX([clang++ g++])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.13])
AM_SILENT_RULES([yes])



AC_PROG_CXX



dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=slates
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])




LT_INIT

# here: bash except some additions


buildtestbackend="yes"

if test "x$buildtestbackend" = "xyes" ; then
	AM_CONDITIONAL(IS_COMPILED_WITH_TESTBACKEND, [true])
	AC_DEFINE([COMPILED_WITH_TESTBACKEND], [1], [ testbackend support: YES ])
else
	AM_CONDITIONAL(IS_COMPILED_WITH_TESTBACKEND, [false])
	AC_MSG_RESULT( [ testbackend support: NO ])
fi


PKG_CHECK_MODULES(SDL2, [sdl2 SDL2_image], [buildsdlbackend="yes"] , [buildsdlbackend="no"] )

buildsdlbackend="no"

if test "x$buildsdlbackend" = "xyes" ; then
	AM_CONDITIONAL(IS_COMPILED_WITH_SDL, [true])
	AC_DEFINE([COMPILED_WITH_SDL], [1], [sdl support: YES])
else
	AM_CONDITIONAL(IS_COMPILED_WITH_SDL, [false])
fi

#-lXdamage -lXcomposite -lX11 -lXrender
PKG_CHECK_MODULES(X, [xdamage xcomposite x11 xrender], [buildxbackend="yes"] , [buildxbackend="no"] )

#buildxbackend="no"

if test "x$buildxbackend" = "xyes" ; then
	AM_CONDITIONAL(IS_COMPILED_WITH_X, [true])
	AC_DEFINE([COMPILED_WITH_X], [1], [X support: YES])
else
	AM_CONDITIONAL(IS_COMPILED_WITH_X, [false])
fi

#PKG_CHECK_MODULES(X, [X], [buildxbackend="yes"] , [buildxbackend="no"] )

buildwaylandbackend="no"

if test "x$buildwaylandbackend" = "xyes" ; then
	AM_CONDITIONAL(IS_COMPILED_WITH_WAYLAND, [true])
	AC_DEFINE([COMPILED_WITH_WAYLAND], [1], [wayland support: YES])
else
	AM_CONDITIONAL(IS_COMPILED_WITH_WAYLAND, [false])
fi

AC_CONFIG_FILES([
Makefile
src/Makefile
po/Makefile.in
])

AC_OUTPUT
