#pragma once
#include <core/types.h>
#include <math/math.h>

typedef struct {
    Vec4 planes[6];
} Frustum;

Frustum frustum_from_vp(Mat4 vp);
bool    frustum_test_aabb(const Frustum *f, Vec3 aabb_min, Vec3 aabb_max);
bool    frustum_test_point(const Frustum *f, Vec3 p);
bool    frustum_test_sphere(const Frustum *f, Vec3 center, f32 radius);
