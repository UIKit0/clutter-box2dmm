SUBDIRS		= src clutter-cairomm

EXTRA_DIST	= README					\
		  clutter-cairomm-config.h.in clutter-cairomm.h	\
		  clutter-cairomm.pc.in

cluttermm_includedir		= $(includedir)/clutter-cairomm-$(API_VER)
cluttermm_include_HEADERS	= clutter-cairomm.h

cluttermm_configdir		= $(libdir)/clutter-cairomm-$(API_VER)/include
cluttermm_config_DATA	= clutter-cairomm-config.h

pkgconfigdir		= $(libdir)/pkgconfig
pkgconfig_DATA		= clutter-cairomm-$(API_VER).pc
DISTCLEANFILES = $(pkgconfig_DATA)
