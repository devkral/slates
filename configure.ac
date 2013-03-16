dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT([slates],[0.1])

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=slates
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
# AM_GLIB_GNU_GETTEXT obsolete?



LT_INIT



PKG_CHECK_MODULES(GTKMM,[gtkmm-3.0],[AC_DEFINE([COMPILED_WITH_GTKMM], [1], [gtkmm support: YES])],
 [AC_MSG_RESULT([gtkmm support: NO])])
 
 
PKG_CHECK_MODULES(SDL,[sdl SDL_image],[AC_DEFINE([COMPILED_WITH_SDL], [1], [sdl support: YES])],
 [AC_MSG_RESULT([sdl support: NO])])




AC_CONFIG_FILES([
Makefile
src/Makefile
po/Makefile.in
src/sdlbackend/Makefile
src/gtkmmbackend/Makefile
])

AC_OUTPUT
