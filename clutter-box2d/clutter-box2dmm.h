/* clutter-box2dmm - a C++ wrapper for clutter-gtk
 *
 * Copyright 2008 The cluttermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef LIBCLUTTER_BOX2DMM_H
#define LIBCLUTTER_BOX2DMM_H

/** @mainpage clutter-box2dmm Reference Manual
 *
 * @section description Description
 *
 * clutter-box2dmm is a C++ wrapper for clutter-box2d.
 *
 * See also the <a href="http://www.clutter-project.org/">clutter website</a>.
 *
 * @section basics Basic Usage
 * Include the clutter-box2dmm header:
 * @code
 * #include <clutter-box2dmm.h>
 * @endcode
 * (You may include individual headers, such as @c clutter-box2dmm/box2d.h
 * instead.)
 *
 * If your source file is @c program.cc, you can compile it with:
 * @code
 * g++ program.cc -o program `pkg-config --cflags --libs clutter-box2dmm-0.10`
 * @endcode
 *
 * Alternatively, if using autoconf, use the following in @c configure.ac:
 * @code
 * PKG_CHECK_MODULES([CLUTTER_BOX2DMM], [clutter-box2dmm-0.10])
 * @endcode
 * Then use the generated @c CLUTTER_BOX2DMM_CFLAGS and @c CLUTTER_BOX2DMM_LIBS
 * variables in the project @c Makefile.am files. For example:
 * @code
 * program_CPPFLAGS = $(CLUTTER_BOX2DMM_CFLAGS)
 * program_LDADD = $(CLUTTER_BOX2DMM_LIBS}
 * @endcode
 */

/* cluttermm version.  */
extern const int clutter_box2dmm_major_version;
extern const int clutter_box2dmm_minor_version;
extern const int clutter_box2dmm_micro_version;

#include <cluttermm.h>
#include <clutter-box2dmm/init.h>
#include <clutter-box2dmm/box2d.h>

#endif /* #ifndef LIBCLUTTER_BOX2DMM_H */
