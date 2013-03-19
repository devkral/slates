dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT([slates],[0.1])


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

AC_DEFINE([COMPILED_WITH_TESTBACKEND], [1],[testbackend: YES])
ifdef(COMPILED_WITH_TESTBACKEND, AM_CONDITIONAL(IS_COMPILED_WITH_TESTBACKEND, true), AM_CONDITIONAL(IS_COMPILED_WITH_TESTBACKEND, false))





PKG_CHECK_MODULES(GTKMM, [gtkmm-3.0], AC_DEFINE([COMPILED_WITH_GTKMM], [1], [gtkmm support: YES]), [ AC_MSG_RESULT( [ gtkmm support: NO ] ) ] )

ifdef(GTKMM, AM_CONDITIONAL(IS_COMPILED_WITH_GTKMM,true),AM_CONDITIONAL(IS_COMPILED_WITH_GTKMM,false))

PKG_CHECK_MODULES(SDL, [sdl SDL_image], [AC_DEFINE([COMPILED_WITH_SDL], [1], [sdl support: YES])], [ AC_MSG_RESULT([sdl support: NO]) ] )

ifdef(SDL, AM_CONDITIONAL(IS_COMPILED_WITH_SDL,true), AM_CONDITIONAL(IS_COMPILED_WITH_SDL,false))




AC_CONFIG_FILES([
Makefile
src/Makefile
po/Makefile.in
])

AC_OUTPUT
