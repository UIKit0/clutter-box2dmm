## Copyright (c) 2001
## The cluttermm development team.

SUBDIRS = private

sublib_name = clutter-cairomm
sublib_libname = clutter-cairomm-$(API_VER)
sublib_libversion = $(CLUTTER_CAIROMM_SO_VERSION)
sublib_namespace = Clutter
sublib_cflags = $(CLUTTER_CAIROMM_CFLAGS) -I$(top_srcdir)/clutter
sublib_topdir = clutter-cairo


files_extra_h	= wrap_init.h init.h
files_extra_cc	= init.cc

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES = libclutter-cairomm-@API_VER@.la
libclutter_cairomm_@API_VER@_la_SOURCES = $(files_all_cc)
libclutter_cairomm_@API_VER@_la_LDFLAGS = $(common_ldflags)
libclutter_cairomm_@API_VER@_la_LIBADD = $(CLUTTER_CAIROMM_LIBS)

