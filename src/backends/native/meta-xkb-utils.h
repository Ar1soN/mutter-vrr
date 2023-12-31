/*
 * Copyright (C) 2010  Intel Corporation.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.

 * Authors:
 *  Damien Lespiau <damien.lespiau@intel.com>
 */

#pragma once

#include <xkbcommon/xkbcommon.h>

#include "clutter/clutter.h"

ClutterEvent *    meta_key_event_new_from_evdev (ClutterInputDevice *device,
                                                 ClutterInputDevice *core_keyboard,
                                                 ClutterEventFlags   flags,
                                                 struct xkb_state   *xkb_state,
                                                 uint32_t            button_state,
                                                 uint64_t            time_us,
                                                 uint32_t            key,
                                                 uint32_t            state);
ClutterModifierType meta_xkb_translate_modifiers (struct xkb_state    *state,
                                                  ClutterModifierType  button_state);
uint32_t meta_xkb_keycode_to_evdev (uint32_t hardware_keycode);
uint32_t meta_xkb_evdev_to_keycode (uint32_t evcode);
