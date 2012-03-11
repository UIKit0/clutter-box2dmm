/* Copyright (C) 1998-2006 The gtkmm Development Team
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

#include "glibmm_generate_extra_defs/generate_extra_defs.h"
#include <clutter/clutter.h>
#include <clutter-box2d/clutter-box2d.h>
#include <iostream>


int main (int argc, char *argv[])
{
  clutter_init(&argc, &argv) ;

  std::cout 
    << get_defs(CLUTTER_TYPE_BOX2D)
    << get_defs(CLUTTER_TYPE_BOX2D_COLLISION)
    << get_defs(CLUTTER_TYPE_BOX2D_CHILD)
    ;

  return 0;
}
