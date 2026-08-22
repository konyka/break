/**
 * @file my_vgcanvas_break_rhi.h
 * @brief Break RHI backend for myui's vector canvas interface.
 *
 * The canvas records triangles in myui's font-vertex layout
 * (xy + uv + RGBA) and submits them through the Break RHI. Solid geometry
 * and glyphs share a single atlas-backed pipeline; images use a second
 * RGBA-texture pipeline. Path tessellation is delegated to my_vggeometry.
 * The public capability query exposes level 0 only. The canvas deliberately
 * keeps a single-sample target until the Break RHI exposes transactional
 * sample-count negotiation; requests for higher levels return
 * MY_RET_NOT_SUPPORTED without changing state.
 */
#ifndef MY_VGCANVAS_BREAK_RHI_H
#define MY_VGCANVAS_BREAK_RHI_H

#include "myr/my_vgcanvas.h"
#include "rhi/rhi.h"

my_vgcanvas_t *my_vgcanvas_break_rhi_create(const my_allocator_t *allocator,
                                            RHIDevice *device, u32 width,
                                            u32 height);

void my_vgcanvas_break_rhi_set_cmd(my_vgcanvas_t *vg, RHICmdBuffer *cmd);

my_ret_t my_vgcanvas_break_rhi_resize(my_vgcanvas_t *vg, u32 width,
                                      u32 height);

#endif /* MY_VGCANVAS_BREAK_RHI_H */
