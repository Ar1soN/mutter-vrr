/*
 * Copyright (C) 2021 Red Hat Inc.
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 */

#pragma once

#include "backends/native/meta-render-device-private.h"

#define META_TYPE_RENDER_DEVICE_SURFACELESS (meta_render_device_surfaceless_get_type ())
G_DECLARE_FINAL_TYPE (MetaRenderDeviceSurfaceless, meta_render_device_surfaceless,
                      META, RENDER_DEVICE_SURFACELESS,
                      MetaRenderDevice)

MetaRenderDeviceSurfaceless * meta_render_device_surfaceless_new (MetaBackend  *backend,
                                                                  GError      **error);

