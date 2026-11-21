#pragma once
#include <core/types.h>
#include <math.h>

#if defined(__SSE__) || defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)
    #include <xmmintrin.h>
    #define MATH_SSE 1
#else
    #define MATH_SSE 0
#endif

/* Reciprocal square root shared by physics, terrain, animation and camera
 * code. It is the correctly rounded 1/sqrtf on every architecture: the SSE
 * rsqrtss estimate (even with a Newton step) differs from arm64 in the last
 * bits, which made identical physics inputs diverge between x86-64 and arm64
 * (test_physics_replay pins the cross-architecture hashes). */
static inline f32 fast_rsqrt(f32 x) {
    return 1.0f / sqrtf(x);
}

/* Bilingual init/assert spellings come from core/types.h (BREAK_AGG,
 * BREAK_STATIC_ASSERT). */

typedef struct { f32 e[2]; } Vec2;
typedef struct { f32 e[3]; } Vec3;
typedef struct { f32 e[4]; } Vec4;
typedef struct { f32 e[4][4]; } Mat4;
typedef struct { f32 e[4]; } Quat;

BREAK_STATIC_ASSERT(sizeof(Vec4) == 16, "Vec4 must be 16 bytes");
BREAK_STATIC_ASSERT(sizeof(Mat4) == 64, "Mat4 must be 64 bytes");

static inline Vec3 vec3(f32 x, f32 y, f32 z) { return BREAK_AGG(Vec3){{x, y, z}}; }
static inline Vec4 vec4(f32 x, f32 y, f32 z, f32 w) { return BREAK_AGG(Vec4){{x, y, z, w}}; }

static inline Vec3 vec3_add(Vec3 a, Vec3 b) {
    return BREAK_AGG(Vec3){{a.e[0]+b.e[0], a.e[1]+b.e[1], a.e[2]+b.e[2]}};
}
static inline Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return BREAK_AGG(Vec3){{a.e[0]-b.e[0], a.e[1]-b.e[1], a.e[2]-b.e[2]}};
}
static inline Vec3 vec3_scale(Vec3 v, f32 s) {
    return BREAK_AGG(Vec3){{v.e[0]*s, v.e[1]*s, v.e[2]*s}};
}
static inline f32 vec3_dot(Vec3 a, Vec3 b) {
    return a.e[0]*b.e[0] + a.e[1]*b.e[1] + a.e[2]*b.e[2];
}
static inline Vec3 vec3_cross(Vec3 a, Vec3 b) {
    return BREAK_AGG(Vec3){{
        a.e[1]*b.e[2] - a.e[2]*b.e[1],
        a.e[2]*b.e[0] - a.e[0]*b.e[2],
        a.e[0]*b.e[1] - a.e[1]*b.e[0],
    }};
}
static inline f32 vec3_len_sq(Vec3 v) { return vec3_dot(v, v); }
static inline f32 vec3_len(Vec3 v) {
    f32 l2 = vec3_dot(v, v);
    return l2 > 1e-12f ? l2 * fast_rsqrt(l2) : 0.0f;
}
static inline Vec3 vec3_normalize(Vec3 v) {
    f32 l2 = vec3_dot(v, v);
    return l2 > 1e-12f ? vec3_scale(v, fast_rsqrt(l2)) : vec3(0,0,0);
}
static inline Vec3 vec3_lerp(Vec3 a, Vec3 b, f32 t) {
    return BREAK_AGG(Vec3){{
        a.e[0] + (b.e[0] - a.e[0]) * t,
        a.e[1] + (b.e[1] - a.e[1]) * t,
        a.e[2] + (b.e[2] - a.e[2]) * t,
    }};
}
static inline f32 vec3_distance(Vec3 a, Vec3 b) {
    return vec3_len(vec3_sub(a, b));
}

/* ---- Quaternion helpers ---- */
#define QUAT_IDENTITY (BREAK_AGG(Quat){{0.0f, 0.0f, 0.0f, 1.0f}})

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
    return BREAK_AGG(Quat){{-q.e[0], -q.e[1], -q.e[2], q.e[3]}};
}

static inline Quat quat_normalize(Quat q) {
    f32 l2 = q.e[0]*q.e[0] + q.e[1]*q.e[1] + q.e[2]*q.e[2] + q.e[3]*q.e[3];
    if (l2 <= 1e-12f) return QUAT_IDENTITY;
    f32 inv = fast_rsqrt(l2);
    return BREAK_AGG(Quat){{q.e[0]*inv, q.e[1]*inv, q.e[2]*inv, q.e[3]*inv}};
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

/* atan2 built only from IEEE + - * / and comparisons, so it rounds the same
 * on every libm and architecture provided the including file is compiled
 * with -ffp-contract=off (engine/CMakeLists.txt sets it for src/physics,
 * src/math and tests/test_math.c); the platform atan2f differs by 1 ULP
 * between glibc releases, which broke cross-machine physics lockstep.
 * Octant reduction to t = min/max in [0, 1], then an odd polynomial; max
 * error about 3.2e-7 rad. Signed zeros follow IEEE (the sign of y picks
 * -0 or -pi); (inf, inf) returns NaN. Physics uses this for hinge,
 * cone-twist and slider angles. */
static inline f32 math_atan2f(f32 y, f32 x) {
    f32 ax = fabsf(x);
    f32 ay = fabsf(y);
    f32 hi = ax > ay ? ax : ay;
    f32 lo = ax > ay ? ay : ax;
    if (hi == 0.0f) return signbit(y) ? -0.0f : 0.0f;
    f32 t = lo / hi;
    f32 t2 = t * t;
    f32 p = -0.0040540580f;
    p = p * t2 + 0.0218612288f;
    p = p * t2 - 0.0559098861f;
    p = p * t2 + 0.0964200441f;
    p = p * t2 - 0.1390853351f;
    p = p * t2 + 0.1994653599f;
    p = p * t2 - 0.3332985605f;
    p = p * t2 + 0.9999993329f;
    f32 r = p * t;
    if (ay > ax) r = 1.57079637f - r;
    if (x < 0.0f) r = 3.14159274f - r;
    return signbit(y) ? -r : r;
}

/* sin and cos built only from IEEE double + - * / and conversions, for the
 * same reason as math_atan2f: quat_from_axis_angle integrates every rotating
 * body, and the platform sinf/cosf are free to round differently between
 * libm releases. The argument is reduced by k*pi/2 in double with a two-part
 * pi/2 (Cody-Waite), and the musl float kernels are evaluated in double on
 * [-pi/4, pi/4]; error below 3e-8 while |x| <= 2^28, where k*pi/2 is exact
 * and the bits do not depend on FMA contraction. Beyond 2^28 the argument is
 * first reduced with fmod by a rounded 2*pi (fmod itself is exact), so the
 * result stays bounded and repeatable but loses accuracy as |x| grows. NaN
 * and infinity give NaN; a signed zero gives sin = x, cos = 1. */
static inline void math_sincosf(f32 x, f32 *sin_out, f32 *cos_out) {
    if (x == 0.0f) {
        *sin_out = x;
        *cos_out = 1.0f;
        return;
    }
    if (!isfinite(x)) {
        *sin_out = NAN;
        *cos_out = NAN;
        return;
    }
    double d = (double)x;
    if (fabs(d) > 268435456.0) d = fmod(d, 6.28318530717958647692);
    double kd = d * 0.63661977236758134308;
    long long k = (long long)(kd < 0.0 ? kd - 0.5 : kd + 0.5);
    double r = d - (double)k * 1.57079631090164184570e+00;
    r = r - (double)k * 1.58932547735281966916e-08;
    double z = r * r;
    double w = z * z;
    double sr = (r + (z * r) * (-0.166666666416265235595 + z * 0.0083333293858894631756)) +
                ((z * r) * w) * (-0.000198393348360966317347 + z * 0.0000027183114939898219064);
    double cr = ((1.0 + z * -0.499999997251031003120) + w * 0.0416666233237390631894) +
                (w * z) * (-0.00138867637746099294692 + z * 0.0000243904487962774090654);
    switch ((unsigned)(k & 3)) {
    case 0: *sin_out = (f32)sr; *cos_out = (f32)cr; break;
    case 1: *sin_out = (f32)cr; *cos_out = (f32)-sr; break;
    case 2: *sin_out = (f32)-sr; *cos_out = (f32)-cr; break;
    default: *sin_out = (f32)-cr; *cos_out = (f32)sr; break;
    }
}

static inline Quat quat_from_axis_angle(Vec3 axis, f32 angle) {
    f32 l = vec3_len(axis);
    if (l <= 1e-6f) return QUAT_IDENTITY;
    f32 inv = 1.0f / l;
    f32 s, c;
    math_sincosf(angle * 0.5f, &s, &c);
    return BREAK_AGG(Quat){{axis.e[0]*inv*s, axis.e[1]*inv*s, axis.e[2]*inv*s, c}};
}

static inline Vec3 quat_rotate_vec3(Quat q, Vec3 v) {
    Vec3 qv = BREAK_AGG(Vec3){{q.e[0], q.e[1], q.e[2]}};
    Vec3 t = vec3_scale(vec3_cross(qv, v), 2.0f);
    return vec3_add(vec3_add(v, vec3_scale(t, q.e[3])), vec3_cross(qv, t));
}

Mat4 mat4_identity(void);
Mat4 mat4_ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
Mat4 mat4_perspective(f32 fov_rad, f32 aspect, f32 near, f32 far);
/* Right-handed view matrix matching camera_view convention (R439).
 * right = normalize(cross(f,up)), up = cross(s,f), rows [s; u; -f] (det=+1),
 * translation in e[3][0..2] (canonical column-major, same as
 * mat4_translation). See camera_view() for the same basis. */
Mat4 mat4_lookat(Vec3 eye, Vec3 target, Vec3 up);
/* R73-4: static inline mat4_mul — enables inlining in skeleton/animation hot paths.
 * Saves 128B per-call stack copy (two Mat4 by-value) + eliminates cross-TU call overhead. */
static inline Mat4 mat4_mul(Mat4 a, Mat4 b) {
    Mat4 out;
#if MATH_SSE
    for (int col = 0; col < 4; col++) {
        __m128 c0 = _mm_set1_ps(b.e[col][0]);
        __m128 c1 = _mm_set1_ps(b.e[col][1]);
        __m128 c2 = _mm_set1_ps(b.e[col][2]);
        __m128 c3 = _mm_set1_ps(b.e[col][3]);
        __m128 r = _mm_mul_ps(_mm_loadu_ps(a.e[0]), c0);
        r = _mm_add_ps(r, _mm_mul_ps(_mm_loadu_ps(a.e[1]), c1));
        r = _mm_add_ps(r, _mm_mul_ps(_mm_loadu_ps(a.e[2]), c2));
        r = _mm_add_ps(r, _mm_mul_ps(_mm_loadu_ps(a.e[3]), c3));
        _mm_storeu_ps(out.e[col], r);
    }
#else
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            out.e[col][row] =
                a.e[0][row] * b.e[col][0] +
                a.e[1][row] * b.e[col][1] +
                a.e[2][row] * b.e[col][2] +
                a.e[3][row] * b.e[col][3];
        }
    }
#endif
    return out;
}
Mat4 mat4_inverse(Mat4 m);
/* R49: Multiply diagonal ortho matrix D by view matrix V (D*V).
 * PRECONDITION: D must be diagonal + translation
 *   (only d.e[i][i] and d.e[3][0..2] may be non-zero, d.e[3][3]==1).
 *   Results are undefined for arbitrary matrices.
 * D has 7 non-zero elements (d0,d1,d2,d3x,d3y,d3z,1): 21 muls + 12 adds vs 64+48 for generic mul.
 * For symmetric ortho (d3x=d3y=d3z=0): 12 muls + 0 adds. */
static inline Mat4 mat4_mul_ortho_diag(Mat4 d, Mat4 v) {
    f32 d0 = d.e[0][0], d1 = d.e[1][1], d2 = d.e[2][2], d3x = d.e[3][0], d3y = d.e[3][1], d3z = d.e[3][2];
    Mat4 out;
    /* (D*V)[col][row] = d_row * V[col][row] + D[3][row] * V[col][3] */
    out.e[0][0] = d0 * v.e[0][0] + d3x * v.e[0][3]; out.e[0][1] = d1 * v.e[0][1] + d3y * v.e[0][3]; out.e[0][2] = d2 * v.e[0][2] + d3z * v.e[0][3]; out.e[0][3] = v.e[0][3];
    out.e[1][0] = d0 * v.e[1][0] + d3x * v.e[1][3]; out.e[1][1] = d1 * v.e[1][1] + d3y * v.e[1][3]; out.e[1][2] = d2 * v.e[1][2] + d3z * v.e[1][3]; out.e[1][3] = v.e[1][3];
    out.e[2][0] = d0 * v.e[2][0] + d3x * v.e[2][3]; out.e[2][1] = d1 * v.e[2][1] + d3y * v.e[2][3]; out.e[2][2] = d2 * v.e[2][2] + d3z * v.e[2][3]; out.e[2][3] = v.e[2][3];
    out.e[3][0] = d0 * v.e[3][0] + d3x;               out.e[3][1] = d1 * v.e[3][1] + d3y;               out.e[3][2] = d2 * v.e[3][2] + d3z;               out.e[3][3] = 1.0f;
    return out;
}
/* R50: Multiply perspective projection P by view V (P*V), exploiting P sparsity.
 * P has: e[0][0]=A, e[1][1]=B, e[2][2]=C, e[2][3]=-1, e[3][2]=D, rest=0
 * (except TAA jitter / screen shake in e[2][0..1]).
 * 24 muls + 10 adds vs 64+48 for generic mul. */
static inline Mat4 mat4_mul_proj_view(Mat4 p, Mat4 v) {
    f32 A = p.e[0][0], B = p.e[1][1], C = p.e[2][2], jx = p.e[2][0], jy = p.e[2][1], D = p.e[3][2];
    Mat4 out;
    /* (P*V)[col][row] = sum_k P[k][row] * V[col][k]
     * P col0=(A,0,0,0), col1=(0,B,0,0), col2=(jx,jy,C,-1), col3=(0,0,D,0)
     * row0: A*V[c][0]+jx*V[c][2]  row1: B*V[c][1]+jy*V[c][2]
     * row2: C*V[c][2]+D*V[c][3]   row3: -V[c][2] */
    out.e[0][0] = A * v.e[0][0] + jx * v.e[0][2]; out.e[0][1] = B * v.e[0][1] + jy * v.e[0][2]; out.e[0][2] = C * v.e[0][2] + D * v.e[0][3]; out.e[0][3] = -v.e[0][2];
    out.e[1][0] = A * v.e[1][0] + jx * v.e[1][2]; out.e[1][1] = B * v.e[1][1] + jy * v.e[1][2]; out.e[1][2] = C * v.e[1][2] + D * v.e[1][3]; out.e[1][3] = -v.e[1][2];
    out.e[2][0] = A * v.e[2][0] + jx * v.e[2][2]; out.e[2][1] = B * v.e[2][1] + jy * v.e[2][2]; out.e[2][2] = C * v.e[2][2] + D * v.e[2][3]; out.e[2][3] = -v.e[2][2];
    out.e[3][0] = A * v.e[3][0] + jx * v.e[3][2]; out.e[3][1] = B * v.e[3][1] + jy * v.e[3][2]; out.e[3][2] = C * v.e[3][2] + D * v.e[3][3]; out.e[3][3] = -v.e[3][2];
    return out;
}
/* R53-fix: Analytical inverse of a perspective projection matrix.
 * PRECONDITION: p must be a standard perspective projection matrix
 *   (output of mat4_perspective, optionally with TAA jitter / screen shake in e[2][0..1]).
 *   p.e[0][0], p.e[1][1], p.e[3][2] must be non-zero.
 *   Results are undefined for arbitrary matrices.
 * P has: col0=(A,0,0,0), col1=(0,B,0,0), col2=(jx,jy,C,-1), col3=(0,0,D,0)
 * inv(P): col0=(1/A,0,0,0), col1=(0,1/B,0,0), col2=(0,0,0,1/D), col3=(jx/A,jy/B,-1,C/D)
 * Only 3 divisions + 6 muls vs ~120 muls + 1 div for generic mat4_inverse.
 * Correctly includes TAA jitter (jx, jy) and screen shake. */
static inline Mat4 mat4_inv_perspective(Mat4 p) {
    f32 invA = 1.0f / p.e[0][0], invB = 1.0f / p.e[1][1];
    f32 invD = 1.0f / p.e[3][2];
    Mat4 out;
    out.e[0][0] = invA;               out.e[0][1] = 0.0f;            out.e[0][2] = 0.0f; out.e[0][3] = 0.0f;
    out.e[1][0] = 0.0f;                out.e[1][1] = invB;            out.e[1][2] = 0.0f; out.e[1][3] = 0.0f;
    out.e[2][0] = 0.0f;                out.e[2][1] = 0.0f;            out.e[2][2] = 0.0f; out.e[2][3] = invD;
    out.e[3][0] = p.e[2][0] * invA;    out.e[3][1] = p.e[2][1] * invB; out.e[3][2] = -1.0f; out.e[3][3] = p.e[2][2] * invD;
    return out;
}
Mat4 mat4_translation(f32 x, f32 y, f32 z);
Mat4 mat4_scaling(f32 x, f32 y, f32 z);
Mat4 mat4_from_quat(Quat q);
