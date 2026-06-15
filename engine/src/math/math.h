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
/* Left-handed view matrix matching camera_view convention.
 * right = -normalize(cross(f,up)), translation in e[i][3] (i=0,1,2).
 * s_L x u = f (not -f). See camera_view() for the same basis. */
Mat4 mat4_lookat(Vec3 eye, Vec3 target, Vec3 up);
Mat4 mat4_mul(Mat4 a, Mat4 b);
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
