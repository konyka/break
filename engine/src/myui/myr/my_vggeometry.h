/**
 * @file my_vggeometry.h
 * @brief Shared CPU geometry for the GPU vgcanvas backends (M25b).
 *
 * Extracted verbatim from the gles2 backend (my_vgcanvas_gles2.c) so the
 * Vulkan backend consumes the exact same triangulation: path point /
 * contour accumulation, even-odd scanline fill, stroke strip generation
 * (segment quads + round caps/joins), rounded-rect subdivision and
 * bezier subdivision point collection. Output is a flat array of
 * device-space xy float pairs, triangles, ready to upload.
 *
 * Transform: push() emits (coord + t) * scale; set it from the canvas
 * state before building each draw's vertices.
 */
#ifndef MY_VGGEOMETRY_H
#define MY_VGGEOMETRY_H

#include "myc/my_mem.h"
#include "myr/my_vgcanvas.h"

typedef struct my_vggeo_point_t {
  float x;
  float y;
} my_vggeo_point_t;

typedef struct my_vggeo_contour_t {
  size_t start;
  size_t count;
  bool closed;
} my_vggeo_contour_t;

typedef struct my_vggeometry_t {
  const my_allocator_t* allocator;
  /* path accumulation (raw, untransformed) */
  my_vggeo_point_t* points;
  size_t point_count, point_cap;
  my_vggeo_contour_t* contours;
  size_t contour_count, contour_cap;
  /* triangle output: device-space xy pairs; vert_count is in floats */
  float* verts;
  size_t vert_count, vert_cap;
  float tx, ty, scale; /**< applied at push() time */
} my_vggeometry_t;

void my_vggeometry_init(my_vggeometry_t* g, const my_allocator_t* allocator);
void my_vggeometry_destroy(my_vggeometry_t* g);
void my_vggeometry_set_transform(my_vggeometry_t* g, float tx, float ty,
                                 float scale);

/** @brief Clear the triangle output (not the path). */
void my_vggeometry_begin_verts(my_vggeometry_t* g);
/** @brief Append one vertex, transform applied (grow-fail drops it, same
 * semantics as the pre-extraction gles2 writer). */
void my_vggeometry_push(my_vggeometry_t* g, float x, float y);

/* primitives (append triangles to the output) */
void my_vggeometry_rect(my_vggeometry_t* g, float x0, float y0, float x1,
                        float y1);
void my_vggeometry_circle_fan(my_vggeometry_t* g, float cx, float cy, float r,
                              int segments);
void my_vggeometry_fill_rounded_rect(my_vggeometry_t* g, float x, float y,
                                     float w, float h, float radius);
void my_vggeometry_stroke_rect(my_vggeometry_t* g, float x, float y, float w,
                               float h, float line_width);

/* path accumulation */
my_ret_t my_vggeometry_begin_path(my_vggeometry_t* g);
my_ret_t my_vggeometry_move_to(my_vggeometry_t* g, float x, float y);
my_ret_t my_vggeometry_line_to(my_vggeometry_t* g, float x, float y);
my_ret_t my_vggeometry_close_path(my_vggeometry_t* g);
my_ret_t my_vggeometry_curve_to(my_vggeometry_t* g, float cx1, float cy1,
                                float cx2, float cy2, float x, float y);

/**
 * @brief Even-odd scanline fill of the current path over the (device
 * space) clip rect; every filled span becomes one rect (2 triangles).
 */
my_ret_t my_vggeometry_fill(my_vggeometry_t* g, const my_rect_t* clip);
/** @brief Stroke the current path: segment quads + round caps/joins. */
my_ret_t my_vggeometry_stroke(my_vggeometry_t* g, float line_width,
                              my_line_cap_t cap, my_line_join_t join);

#endif /* MY_VGGEOMETRY_H */
