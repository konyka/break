#pragma once
#include <core/types.h>
#include <math/math.h>

typedef struct VegetationDesc {
    const u8 *density;
    u32 width;
    u32 depth;
    f32 cell;
    u32 prototype_count; /* 1..8 */
} VegetationDesc;

typedef struct VegetationInstance {
    Vec3 position;
    u32 prototype;
} VegetationInstance;

typedef struct VegetationBuild {
    VegetationInstance *instances;
    u32 capacity;
    u32 count;
    u32 dropped;
} VegetationBuild;

bool vegetation_build(const VegetationDesc *desc, const f32 *heights, f32 height_scale,
                      VegetationBuild *out);
