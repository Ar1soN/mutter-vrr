/*
 * Copyright (C) 2019 Red Hat Inc.
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

#include "compositor/meta-compositor-server.h"

#define META_TYPE_COMPOSITOR_NATIVE (meta_compositor_native_get_type ())
G_DECLARE_FINAL_TYPE (MetaCompositorNative, meta_compositor_native,
                      META, COMPOSITOR_NATIVE, MetaCompositor)

MetaCompositorNative * meta_compositor_native_new (MetaDisplay *display,
                                                   MetaBackend *backend);
