## Copyright (c) 2009  Openismus GmbH  <http://www.openismus.com/>
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
## along with this library.  If not, see <http://www.gnu.org/licenses/>.

AUTOMAKE_OPTIONS = subdir-objects

EXTRA_DIST = pyramid/gnome_logo.png slides/gnome_logo.png table/gnome_logo.png


check_PROGRAMS = bridge/example chain/example pyramid/example slides/example table/example distance_joint/example

clutter_box2dmm_includes = -I$(top_builddir)/clutter-box2d $(if $(srcdir:.=),-I$(top_srcdir)/clutter-box2d)

AM_CPPFLAGS = -I$(top_builddir) $(clutter_box2dmm_includes) $(CLUTTER_BOX2DMM_CFLAGS)
AM_CXXFLAGS = $(CLUTTER_BOX2DMM_WXXFLAGS)

LDADD = $(CLUTTER_BOX2DMM_LIBS) $(top_builddir)/clutter-box2d/clutter-box2dmm/libclutter-box2dmm-$(CLUTTER_BOX2DMM_API_VERSION).la

bridge_example_SOURCES = bridge/main.cc
chain_example_SOURCES = chain/main.cc
pyramid_example_SOURCES = pyramid/main.cc
slides_example_SOURCES = slides/main.cc
table_example_SOURCES = table/main.cc
distance_joint_example_SOURCES = distance_joint/main.cc






