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

AM_CONDITIONAL(IS_COMPILED_WITH_TESTBACKEND, [true])

AS_CASE(IS_COMPILED_WITH_TESTBACKEND,
true, AC_DEFINE([COMPILED_WITH_TESTBACKEND], [1], [ testbackend support: YES ]),
false, AC_MSG_RESULT( [ testbackend support: NO ]) )

PKG_CHECK_MODULES(GTKMM, [gtkmm-3.0],  AM_CONDITIONAL(IS_COMPILED_WITH_GTKMM, [true]),  AM_CONDITIONAL(IS_COMPILED_WITH_GTKMM, [false]) )
AS_CASE(IS_COMPILED_WITH_GTKMM,
true, AC_DEFINE([COMPILED_WITH_GTKMM], [1], [gtkmm support: YES]),
false, AC_MSG_RESULT( [ gtkmm support: NO ] ) )


PKG_CHECK_MODULES(SDL, [sdl SDL_image], AM_CONDITIONAL(IS_COMPILED_WITH_SDL, [true]), AM_CONDITIONAL(IS_COMPILED_WITH_SDL, [false]) )
AS_CASE(IS_COMPILED_WITH_SDL,
true, AC_DEFINE([COMPILED_WITH_SDL], [1], [sdl support: YES]),
false, AC_MSG_RESULT([sdl support: NO]))


AC_CONFIG_FILES([
Makefile
src/Makefile
po/Makefile.in
])

AC_OUTPUT
