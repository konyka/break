#pragma once

#include <rhi/rhi.h>

/*
 * One-bounce ray-tracing probe — the first real ray-traced pixel.
 *
 * Builds a minimal ray-tracing pipeline (raygen + miss + closest-hit shaders),
 * a shader binding table, and an acceleration-structure descriptor set for
 * `tlas`, traces exactly one ray from (0,0,1) along (0,0,-1) through a 1x1
 * storage image, and copies the pixel back to the host.
 *
 * Expected values with the engine's one-triangle geometry (vertices
 * (0,1,0),(-1,-1,0),(1,-1,0), identity instance transform):
 *   - HIT  -> green {0, 255, 0, 255}
 *   - MISS -> blue  {0, 0, 255, 255}
 *
 * Requires RHI_FEATURE_RAY_TRACING_PIPELINE | RHI_FEATURE_ACCELERATION_STRUCTURE
 * on the device; every other condition fails closed with a classified reason
 * retrievable via rt_trace_last_error().
 */
bool rt_trace_probe(RHIDevice *dev, RHIAccelerationStructure tlas,
                    u8 out_pixel[4]);
const char *rt_trace_last_error(void);
