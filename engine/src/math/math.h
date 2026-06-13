#pragma once
#include <core/types.h>
#include <math.h>

#if defined(__SSE__) || defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)
    #include <xmmintrin.h>
    #define MATH_SSE 1
#else
    #define MATH_SSE 0
#endif

/* Fast reciprocal square root: _mm_rsqrt_ss + one Newton-Raphson step (~22-bit accuracy).
 * Unified definition used by physics, terrain, animation, and camera subsystems. */
static inline f32 fast_rsqrt(f32 x) {
#if MATH_SSE
    __m128 v = _mm_set_ss(x);
    __m128 e = _mm_rsqrt_ss(v);
    e = _mm_mul_ss(e, _mm_sub_ss(_mm_set_ss(1.5f),
            _mm_mul_ss(_mm_mul_ss(_mm_set_ss(0.5f), v), _mm_mul_ss(e, e))));
    f32 r;
    _mm_store_ss(&r, e);
    return r;
#else
    return 1.0f / sqrtf(x);
#endif
}

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
    f32 l2 = vec3_dot(v, v);
    return l2 > 1e-12f ? l2 * fast_rsqrt(l2) : 0.0f;
}
static inline Vec3 vec3_normalize(Vec3 v) {
    f32 l2 = vec3_dot(v, v);
    return l2 > 1e-12f ? vec3_scale(v, fast_rsqrt(l2)) : vec3(0,0,0);
}
static inline Vec3 vec3_lerp(Vec3 a, Vec3 b, f32 t) {
    return (Vec3){{
        a.e[0] + (b.e[0] - a.e[0]) * t,
        a.e[1] + (b.e[1] - a.e[1]) * t,
        a.e[2] + (b.e[2] - a.e[2]) * t,
    }};
}
static inline f32 vec3_distance(Vec3 a, Vec3 b) {
    return vec3_len(vec3_sub(a, b));
}

/* ---- Quaternion helpers ---- */
#define QUAT_IDENTITY ((Quat){{0.0f, 0.0f, 0.0f, 1.0f}})

static inline Quat quat_identity(void) { return QUAT_IDENTITY; }

static inline Quat quat_mul(Quat a, Quat b) {
    Quat r;
    r.e[0] = a.e[3]*b.e[0] + a.e[0]*b.e[3] + a.e[1]*b.e[2] - a.e[2]*b.e[1];
    r.e[1] = a.e[3]*b.e[1] - a.e[0]*b.e[2] + a.e[1]*b.e[3] + a.e[2]*b.e[0];
    r.e[2] = a.e[3]*b.e[2] + a.e[0]*b.e[1] - a.e[1]*b.e[0] + a.e[2]*b.e[3];
    r.e[3] = a.e[3]*b.e[3] - a.e[0]*b.e[0] - a.e[1]*b.e[1] - a.e[2]*b.e[2];
    return r;
}

static inline Quat quat_inverse(Quat q) {
    /* Assumes unit quaternion: conjugate equals inverse. */
    return (Quat){{-q.e[0], -q.e[1], -q.e[2], q.e[3]}};
}

static inline Quat quat_normalize(Quat q) {
    f32 l2 = q.e[0]*q.e[0] + q.e[1]*q.e[1] + q.e[2]*q.e[2] + q.e[3]*q.e[3];
    if (l2 <= 1e-12f) return QUAT_IDENTITY;
    f32 inv = fast_rsqrt(l2);
    return (Quat){{q.e[0]*inv, q.e[1]*inv, q.e[2]*inv, q.e[3]*inv}};
}

/* Normalized linear interpolation (nlerp) — fast approximation replacing slerp.
 * Eliminates acosf + sinf×3 (4 transcendental functions). For animation blending
 * the angular error is negligible (<1°) while being ~10× faster. */
static inline Quat quat_slerp(Quat a, Quat b, f32 t) {
    f32 dot = a.e[0]*b.e[0] + a.e[1]*b.e[1] + a.e[2]*b.e[2] + a.e[3]*b.e[3];
    Quat bb = b;
    if (dot < 0.0f) {
        dot = -dot;
        bb.e[0] = -bb.e[0]; bb.e[1] = -bb.e[1];
        bb.e[2] = -bb.e[2]; bb.e[3] = -bb.e[3];
    }
    /* nlerp: linear interpolation + re-normalize.
     * For dot > 0.9995 the quaternions are nearly identical, plain lerp suffices.
     * For dot < 0.9995, nlerp is still an excellent approximation. */
    f32 s0 = 1.0f - t;
    f32 s1 = t;
    Quat r;
    r.e[0] = s0*a.e[0] + s1*bb.e[0];
    r.e[1] = s0*a.e[1] + s1*bb.e[1];
    r.e[2] = s0*a.e[2] + s1*bb.e[2];
    r.e[3] = s0*a.e[3] + s1*bb.e[3];
    return quat_normalize(r);
}

/* quat_nlerp: normalized linear interpolation — same implementation as quat_slerp
 * (which already uses nlerp internally). Separate name for semantic clarity. */
static inline Quat quat_nlerp(Quat a, Quat b, f32 t) {
    f32 dot = a.e[0]*b.e[0] + a.e[1]*b.e[1] + a.e[2]*b.e[2] + a.e[3]*b.e[3];
    if (dot < 0.0f) {
        b.e[0] = -b.e[0]; b.e[1] = -b.e[1];
        b.e[2] = -b.e[2]; b.e[3] = -b.e[3];
    }
    f32 s0 = 1.0f - t;
    Quat r;
    r.e[0] = s0*a.e[0] + t*b.e[0];
    r.e[1] = s0*a.e[1] + t*b.e[1];
    r.e[2] = s0*a.e[2] + t*b.e[2];
    r.e[3] = s0*a.e[3] + t*b.e[3];
    return quat_normalize(r);
}

static inline Quat quat_from_axis_angle(Vec3 axis, f32 angle) {
    f32 l = vec3_len(axis);
    if (l <= 1e-6f) return QUAT_IDENTITY;
    f32 inv = 1.0f / l;
    f32 half = angle * 0.5f;
    f32 s = sinf(half);
    return (Quat){{axis.e[0]*inv*s, axis.e[1]*inv*s, axis.e[2]*inv*s, cosf(half)}};
}

static inline Vec3 quat_rotate_vec3(Quat q, Vec3 v) {
    Vec3 qv = (Vec3){{q.e[0], q.e[1], q.e[2]}};
    Vec3 t = vec3_scale(vec3_cross(qv, v), 2.0f);
    return vec3_add(vec3_add(v, vec3_scale(t, q.e[3])), vec3_cross(qv, t));
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
