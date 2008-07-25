// -*- c++ -*-
/*
 * Copyright 2008 cluttermm development team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <clutter-box2dmm-config.h> //For LIBCLUTTERMM_VERSION
#include <clutter-box2dmm/wrap_init.h>
#include <cluttermm/init.h>

namespace Clutter
{

namespace Box2D
{

void init(int* nargs, gchar **args[])
{
  Clutter::init(nargs, args);
  wrap_init(); //Tells the Glib::wrap() table about the libclutter-box2dmm classes.
}

} //namespace Box2D

} //namespace Clutter
