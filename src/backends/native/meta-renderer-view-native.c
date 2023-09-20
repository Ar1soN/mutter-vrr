/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */

/*
 * Copyright (C) 2020-2022 Dor Askayo
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
 * Written by:
 *     Dor Askayo <dor.askayo@gmail.com>
 */

#include "backends/native/meta-renderer-view-native.h"

#include "backends/meta-output.h"
#include "backends/native/meta-crtc-kms.h"
#include "backends/native/meta-frame-native.h"
#include "backends/native/meta-kms.h"
#include "backends/native/meta-kms-device.h"
#include "backends/native/meta-output-kms.h"

#include "clutter/clutter.h"

typedef enum _MetaFrameSyncMode
{
  META_FRAME_SYNC_MODE_INIT,
  META_FRAME_SYNC_MODE_ENABLED,
  META_FRAME_SYNC_MODE_DISABLED,
} MetaFrameSyncMode;

struct _MetaRendererViewNative
{
  MetaRendererView parent;

  MetaFrameSyncMode requested_frame_sync_mode;
  MetaFrameSyncMode frame_sync_mode;
};

G_DEFINE_TYPE (MetaRendererViewNative, meta_renderer_view_native,
               META_TYPE_RENDERER_VIEW)

static ClutterFrame *
meta_renderer_view_native_new_frame (ClutterStageView *stage_view)
{
  return (ClutterFrame *) meta_frame_native_new ();
}

static void
update_frame_sync_mode (MetaRendererViewNative *view_native,
                        ClutterFrame           *frame,
                        MetaOutput             *output,
                        MetaFrameSyncMode       sync_mode)
{
  MetaFrameNative *frame_native;
  MetaCrtc *crtc;
  MetaKmsCrtc *kms_crtc;
  MetaKmsDevice *kms_device;
  MetaKmsUpdate *kms_update;
  ClutterFrameClock *frame_clock;

  frame_native = meta_frame_native_from_frame (frame);

  frame_clock =
    clutter_stage_view_get_frame_clock (CLUTTER_STAGE_VIEW (view_native));

  crtc = meta_output_get_assigned_crtc (output);
  kms_crtc = meta_crtc_kms_get_kms_crtc (META_CRTC_KMS (crtc));
  kms_device = meta_kms_crtc_get_device (kms_crtc);

  kms_update = meta_frame_native_ensure_kms_update (frame_native, kms_device);

  switch (sync_mode)
    {
    case META_FRAME_SYNC_MODE_ENABLED:
      clutter_frame_clock_set_mode (frame_clock,
                                    CLUTTER_FRAME_CLOCK_MODE_VARIABLE);
      meta_output_kms_set_vrr_mode (META_OUTPUT_KMS (output),
                                    kms_update,
                                    TRUE);
      break;
    case META_FRAME_SYNC_MODE_DISABLED:
      clutter_frame_clock_set_mode (frame_clock,
                                    CLUTTER_FRAME_CLOCK_MODE_FIXED);
      meta_output_kms_set_vrr_mode (META_OUTPUT_KMS (output),
                                    kms_update,
                                    FALSE);
      break;
    case META_FRAME_SYNC_MODE_INIT:
      g_assert_not_reached ();
    }

  view_native->frame_sync_mode = sync_mode;
}

static MetaFrameSyncMode
get_applicable_sync_mode (MetaRendererViewNative *view_native,
                          MetaOutput             *output)
{
  if (meta_output_is_vrr_disallowed (output))
    return META_FRAME_SYNC_MODE_DISABLED;

  return view_native->requested_frame_sync_mode;
}

void
meta_renderer_view_native_maybe_update_frame_sync_mode (MetaRendererViewNative *view_native,
                                                        ClutterFrame           *frame)
{
  MetaRendererView *view = META_RENDERER_VIEW (view_native);
  MetaOutput *output;
  MetaFrameSyncMode applicable_sync_mode;

  output = meta_renderer_view_get_output (view);

  if (!meta_output_is_vrr_capable (output))
    return;

  applicable_sync_mode =
    get_applicable_sync_mode (view_native, output);

  if (G_LIKELY (applicable_sync_mode == view_native->frame_sync_mode))
    return;

  update_frame_sync_mode (view_native,
                          frame,
                          output,
                          applicable_sync_mode);
}

void
meta_renderer_view_native_request_frame_sync (MetaRendererViewNative *view_native,
                                              gboolean                enabled)
{
  view_native->requested_frame_sync_mode =
    enabled
    ? META_FRAME_SYNC_MODE_ENABLED
    : META_FRAME_SYNC_MODE_DISABLED;
}

gboolean
meta_renderer_view_native_is_frame_sync_enabled (MetaRendererViewNative *view_native)
{
  return view_native->frame_sync_mode == META_FRAME_SYNC_MODE_ENABLED;
}

static void
meta_renderer_view_native_class_init (MetaRendererViewNativeClass *klass)
{
  ClutterStageViewClass *stage_view_class = CLUTTER_STAGE_VIEW_CLASS (klass);

  stage_view_class->new_frame = meta_renderer_view_native_new_frame;
}

static void
meta_renderer_view_native_init (MetaRendererViewNative *view_native)
{
  view_native->requested_frame_sync_mode = META_FRAME_SYNC_MODE_DISABLED;
  view_native->frame_sync_mode = META_FRAME_SYNC_MODE_INIT;
}
