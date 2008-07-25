# Build the generate_extra_defs utility executable.
# This is not used directly to build the rest of the project.

LIBS = -lglibmm_generate_extra_defs-2.4

noinst_PROGRAMS = generate_extra_defs_clutter_box2d
generate_extra_defs_clutter_box2d_SOURCES = generate_defs_clutter_box2d.cc

generate_extra_defs_clutter_box2d_CXXFLAGS = $(CLUTTER_BOX2DMM_CFLAGS)
generate_extra_defs_clutter_box2d_LDADD = $(CLUTTER_BOX2DMM_LIBS)
