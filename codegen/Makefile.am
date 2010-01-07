## Copyright (c) 2009  Openismus GmbH <http://www.openismus.com/>
##
## This file is part of clutter-box2dmm.
##
## clutter-box2dmm is free software: you can redistribute it and/or modify it
## under the terms of the GNU Lesser General Public License as published
## by the Free Software Foundation, either version 2.1 of the License,
## or (at your option) any later version.
##
## clutter-box2dmm is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
## See the GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

AUTOMAKE_OPTIONS = subdir-objects

include $(srcdir)/m4/filelist.am

dist_noinst_DATA = $(addprefix m4/,$(files_codegen_m4_private))

codegen_m4dir = $(datadir)/$(CLUTTER_BOX2DMM_MODULE_NAME)/proc/m4
dist_codegen_m4_DATA = $(addprefix m4/,$(files_codegen_m4_public))

noinst_PROGRAMS = extradefs/generate_extra_defs

extradefs_generate_extra_defs_SOURCES = extradefs/generate_extra_defs_clutter_box2d.cc
extradefs_generate_extra_defs_LDADD   = $(CLUTTER_BOX2DMM_LIBS) -lglibmm_generate_extra_defs-2.4

AM_CPPFLAGS = -I$(top_builddir) $(CLUTTER_BOX2DMM_CFLAGS)
AM_CXXFLAGS = $(CLUTTER_BOX2DMM_WXXFLAGS)

# Instruct GNU make to delete the targets of a rule after it failed, in
# order to avoid the complication of handling that situation manually.
.DELETE_ON_ERROR:
