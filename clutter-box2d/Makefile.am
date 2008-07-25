SUBDIRS		= src clutter-box2dmm

EXTRA_DIST	= README					\
		  clutter-box2dmm-config.h.in clutter-box2dmm.h	\
		  clutter-box2dmm.pc.in

cluttermm_includedir		= $(includedir)/clutter-box2dmm-$(API_VER)
cluttermm_include_HEADERS	= clutter-box2dmm.h

cluttermm_configdir		= $(libdir)/clutter-box2dmm-$(API_VER)/include
cluttermm_config_DATA	= clutter-box2dmm-config.h

pkgconfigdir		= $(libdir)/pkgconfig
pkgconfig_DATA		= clutter-box2dmm-$(API_VER).pc
DISTCLEANFILES = $(pkgconfig_DATA)
