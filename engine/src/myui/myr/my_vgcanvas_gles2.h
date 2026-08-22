/**
 * @file my_vgcanvas_gles2.h
 * @brief GLES2 vgcanvas backend (implements the frozen vtable from M1).
 *
 * The caller owns the GL context (PAL window / EGL): create this backend
 * after a context is current, with the framebuffer size. Geometry is
 * triangulated on the CPU (rects -> 2 triangles, rounded corners -> fans,
 * path fill -> even-odd scanline spans batched as triangles, strokes ->
 * segment quads) and submitted as small batches with a single pos+color
 * program. No anti-aliasing, draw_text NOT_SUPPORTED (same as soft).
 */
#ifndef MY_VGCANVAS_GLES2_H
#define MY_VGCANVAS_GLES2_H

#include "myc/my_mem.h"
#include "myr/my_gl.h"
#include "myr/my_vgcanvas.h"

/**
 * @brief Create the backend with an explicit GL table (mock or
 * my_gl_real_default()). NULL allocator = default.
 */
my_vgcanvas_t* my_vgcanvas_gles2_create_with_gl(const my_allocator_t* allocator,
                                                int32_t width, int32_t height,
                                                const my_gl_t* gl);

/**
 * @brief Create the backend on the current real GLES2 context.
 * Returns NULL when built without GLES2 support or shader setup fails.
 */
my_vgcanvas_t* my_vgcanvas_gles2_create(const my_allocator_t* allocator,
                                        int32_t width, int32_t height);

/** @brief Notify a physical framebuffer resize (updates viewport + scissor
 * math). The caller converts logical window dimensions before calling. */
my_ret_t my_vgcanvas_gles2_resize(my_vgcanvas_t* vg, int32_t width,
                                  int32_t height);

/**
 * @brief Toggle multisample anti-aliasing (M11c): glEnable/Disable(
 * GL_MULTISAMPLE) is recorded and applied. Effective ONLY when the
 * underlying surface was created with samples (EGL_SAMPLES > 0; the PAL
 * GL mounts prefer 4x and fall back to no AA, see my_pal_gl_has_
 * multisample) -- on a plain surface this is a documented no-op.
 */
my_ret_t my_vgcanvas_gles2_set_antialias(my_vgcanvas_t* vg, bool enabled);

/** @brief Update the surface multisample capability after PAL negotiation. */
my_ret_t my_vgcanvas_gles2_set_multisample_available(my_vgcanvas_t* vg,
                                                      bool available);

/**
 * @brief HiDPI display scale (M12c): vertices/device coords = (user +
 * translate) * scale, font sizes multiply; viewport stays physical.
 * Default 1.0 (pass-through). Lives in the state stack.
 */
my_ret_t my_vgcanvas_gles2_set_scale(my_vgcanvas_t* vg, float scale);

#endif /* MY_VGCANVAS_GLES2_H */
