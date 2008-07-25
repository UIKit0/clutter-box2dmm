# Build the generate_extra_defs utility executable.
# This is not used directly to build the rest of the project.

LIBS = -lglibmm_generate_extra_defs-2.4

noinst_PROGRAMS = generate_extra_defs_clutter_cairo
generate_extra_defs_clutter_cairo_SOURCES = generate_defs_clutter_cairo.cc

generate_extra_defs_clutter_cairo_CXXFLAGS = $(CLUTTER_CAIROMM_CFLAGS)
generate_extra_defs_clutter_cairo_LDADD = $(CLUTTER_CAIROMM_LIBS)
