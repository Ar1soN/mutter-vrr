/*
 * Copyright (C) 2013 Red Hat Inc.
 * Copyright (C) 2018 Robert Mader
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <glib-object.h>

#include "backends/meta-backend-types.h"
#include "backends/meta-orientation-manager.h"
#include "core/util-private.h"

enum _MetaMonitorTransform
{
  META_MONITOR_TRANSFORM_NORMAL,
  META_MONITOR_TRANSFORM_90,
  META_MONITOR_TRANSFORM_180,
  META_MONITOR_TRANSFORM_270,
  META_MONITOR_TRANSFORM_FLIPPED,
  META_MONITOR_TRANSFORM_FLIPPED_90,
  META_MONITOR_TRANSFORM_FLIPPED_180,
  META_MONITOR_TRANSFORM_FLIPPED_270,
};
#define META_MONITOR_N_TRANSFORMS (META_MONITOR_TRANSFORM_FLIPPED_270 + 1)
#define META_MONITOR_ALL_TRANSFORMS ((1 << META_MONITOR_N_TRANSFORMS) - 1)

/* Returns true if transform causes width and height to be inverted
   This is true for the odd transforms in the enum */
static inline gboolean
meta_monitor_transform_is_rotated (MetaMonitorTransform transform)
{
  return (transform % 2);
}

/* Returns true if transform involves flipping */
static inline gboolean
meta_monitor_transform_is_flipped (MetaMonitorTransform transform)
{
  return (transform >= META_MONITOR_TRANSFORM_FLIPPED);
}

META_EXPORT_TEST
MetaMonitorTransform meta_monitor_transform_from_orientation (MetaOrientation orientation);

META_EXPORT_TEST
MetaMonitorTransform meta_monitor_transform_invert (MetaMonitorTransform transform);

META_EXPORT_TEST
MetaMonitorTransform meta_monitor_transform_transform (MetaMonitorTransform transform,
                                                       MetaMonitorTransform other);

void meta_monitor_transform_transform_point (MetaMonitorTransform  transform,
                                             int                  *area_width,
                                             int                  *area_height,
                                             int                  *point_x,
                                             int                  *point_y);

void meta_monitor_transform_transform_matrix (MetaMonitorTransform  transform,
                                              graphene_matrix_t    *matrix);
