#include <renderer/vegetation.h>
#include <math.h>

bool vegetation_build(const VegetationDesc *desc, const f32 *heights, f32 height_scale,
                      VegetationBuild *out) {
    if (!desc || !heights || !out || !desc->density) return false;
    if (desc->width == 0 || desc->depth == 0 || !(desc->cell > 0.0f) || !isfinite(desc->cell)) return false;
    if (desc->prototype_count == 0 || desc->prototype_count > 8u) return false;
    if (!isfinite(height_scale)) return false;
    if (desc->width > UINT32_MAX / desc->depth) return false;
    if (out->capacity > 0 && !out->instances) return false;
    out->count = 0;
    out->dropped = 0;
    for (u32 z = 0; z < desc->depth; z++) {
        for (u32 x = 0; x < desc->width; x++) {
            u32 i = z * desc->width + x;
            u8 density = desc->density[i];
            if (density == 0) continue;
            if (!isfinite(heights[i])) return false;
            if (out->count >= out->capacity) {
                out->dropped++;
                continue;
            }
            VegetationInstance *inst = &out->instances[out->count++];
            inst->position = vec3(((f32)x + 0.5f) * desc->cell,
                                  heights[i] * height_scale,
                                  ((f32)z + 0.5f) * desc->cell);
            inst->prototype = (u32)density % desc->prototype_count;
        }
    }
    return true;
}
