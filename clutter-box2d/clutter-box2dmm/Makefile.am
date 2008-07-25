## Copyright (c) 2001
## The cluttermm development team.

SUBDIRS = private

sublib_name = clutter-box2dmm
sublib_libname = clutter-box2dmm-$(API_VER)
sublib_libversion = $(CLUTTER_BOX2DMM_SO_VERSION)
sublib_namespace = Clutter
sublib_cflags = $(CLUTTER_BOX2DMM_CFLAGS) -I$(top_srcdir)/clutter
sublib_topdir = clutter-box2d


files_extra_h	= wrap_init.h init.h
files_extra_cc	= init.cc

include $(top_srcdir)/build_shared/Makefile_build_gensrc.am_fragment

lib_LTLIBRARIES = libclutter-box2dmm-@API_VER@.la
libclutter_box2dmm_@API_VER@_la_SOURCES = $(files_all_cc)
libclutter_box2dmm_@API_VER@_la_LDFLAGS = $(common_ldflags)
libclutter_box2dmm_@API_VER@_la_LIBADD = $(CLUTTER_BOX2DMM_LIBS)

