/*
 * Copyright (C) 2018 Red Hat
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
 * Author: Carlos Garnacho <carlosg@gnome.org>
 */

#pragma once

#ifndef META_INPUT_THREAD_H_INSIDE
#error "This header cannot be included directly. Use "backends/native/meta-input-thread.h""
#endif /* META_INPUT_THREAD_H_INSIDE */

#include "backends/native/meta-xkb-utils.h"
#include "clutter/clutter.h"

#define META_TYPE_KEYMAP_NATIVE (meta_keymap_native_get_type ())
G_DECLARE_FINAL_TYPE (MetaKeymapNative, meta_keymap_native,
                      META, KEYMAP_NATIVE,
                      ClutterKeymap)

void meta_keymap_native_set_keyboard_map_in_impl (MetaKeymapNative  *keymap,
                                                  struct xkb_keymap *xkb_keymap);
struct xkb_keymap * meta_keymap_native_get_keyboard_map_in_impl (MetaKeymapNative *keymap);
void meta_keymap_native_update_in_impl (MetaKeymapNative *keymap,
                                        MetaSeatImpl     *seat_impl,
                                        struct xkb_state *xkb_state);

