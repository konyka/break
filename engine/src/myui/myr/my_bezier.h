/**
 * @file my_bezier.h
 * @brief Cubic bezier subdivision (M19a): adaptive de Casteljau into
 * polylines, shared by the soft and gles2 backends (their path models
 * are identical point/contour arrays).
 */
#ifndef MY_BEZIER_H
#define MY_BEZIER_H

#include <stdint.h>

#include "myc/my_error.h"

/** @brief Emitted for each new polyline endpoint (the curve's start
 * point is NOT emitted — the caller owns it via move_to). */
typedef my_ret_t (*my_bezier_emit_fn_t)(void* ctx, float x, float y);

/**
 * @brief Subdivide the cubic bezier (x0,y0)-(x1,y1) with controls
 * (cx1,cy1),(cx2,cy2) into a polyline, emitting each endpoint.
 * Flatness tolerance in pixels (0.25 recommended); recursion depth is
 * capped at max_depth (16 recommended) so degenerate input cannot
 * explode. out_segments (may be NULL) receives the emitted count.
 */
my_ret_t my_bezier_cubic_to_lines(float x0, float y0, float cx1, float cy1,
                                  float cx2, float cy2, float x1, float y1,
                                  float tolerance, int32_t max_depth,
                                  my_bezier_emit_fn_t emit, void* ctx,
                                  int32_t* out_segments);

#endif /* MY_BEZIER_H */
