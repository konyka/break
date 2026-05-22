#pragma once
#include <core/types.h>
#include <math.h>

typedef struct { f32 e[2]; } Vec2;
typedef struct { f32 e[3]; } Vec3;
typedef struct { f32 e[4]; } Vec4;
typedef struct { f32 e[4][4]; } Mat4;
typedef struct { f32 e[4]; } Quat;

_Static_assert(sizeof(Vec4) == 16, "Vec4 must be 16 bytes");
_Static_assert(sizeof(Mat4) == 64, "Mat4 must be 64 bytes");

static inline Vec3 vec3(f32 x, f32 y, f32 z) { return (Vec3){{x, y, z}}; }
static inline Vec4 vec4(f32 x, f32 y, f32 z, f32 w) { return (Vec4){{x, y, z, w}}; }

static inline Vec3 vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){{a.e[0]+b.e[0], a.e[1]+b.e[1], a.e[2]+b.e[2]}};
}
static inline Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){{a.e[0]-b.e[0], a.e[1]-b.e[1], a.e[2]-b.e[2]}};
}
static inline Vec3 vec3_scale(Vec3 v, f32 s) {
    return (Vec3){{v.e[0]*s, v.e[1]*s, v.e[2]*s}};
}
static inline f32 vec3_dot(Vec3 a, Vec3 b) {
    return a.e[0]*b.e[0] + a.e[1]*b.e[1] + a.e[2]*b.e[2];
}
static inline Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return (Vec3){{
        a.e[1]*b.e[2] - a.e[2]*b.e[1],
        a.e[2]*b.e[0] - a.e[0]*b.e[2],
        a.e[0]*b.e[1] - a.e[1]*b.e[0],
    }};
}
static inline f32 vec3_len(Vec3 v) {
    return sqrtf(vec3_dot(v, v));
}
static inline Vec3 vec3_normalize(Vec3 v) {
    f32 l = vec3_len(v);
    return l > 0.000001f ? vec3_scale(v, 1.0f/l) : vec3(0,0,0);
}

Mat4 mat4_identity(void);
Mat4 mat4_ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
Mat4 mat4_perspective(f32 fov_rad, f32 aspect, f32 near, f32 far);
Mat4 mat4_lookat(Vec3 eye, Vec3 target, Vec3 up);
Mat4 mat4_mul(Mat4 a, Mat4 b);
Mat4 mat4_inverse(Mat4 m);
Mat4 mat4_translation(f32 x, f32 y, f32 z);
Mat4 mat4_scaling(f32 x, f32 y, f32 z);
Mat4 mat4_from_quat(Quat q);
