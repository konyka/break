#pragma once
/*
 * simd.h — SIMD intrinsics for performance-critical operations.
 *
 * Provides SSE/AVX accelerated versions of AABB overlap tests,
 * ray-AABB intersection, and vector operations.
 *
 * Falls back to scalar code when SIMD is not available.
 */

#include <core/types.h>
#include <math/math.h>

/* Check for SIMD support */
#if defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
    #define SIMD_SSE2 1
    #include <immintrin.h>
#else
    #define SIMD_SSE2 0
#endif

#if defined(__AVX2__)
    #define SIMD_AVX2 1
    #include <immintrin.h>
#else
    #define SIMD_AVX2 0
#endif

/* ============================================================
 * SSE2 Accelerated AABB Tests
 * ============================================================ */

#if SIMD_SSE2

/*
 * SSE2 AABB overlap test.
 * Tests if two AABBs overlap using SIMD comparison.
 * Returns 1 if overlapping, 0 otherwise.
 */
static inline int simd_aabb_overlap_sse2(
    const f32 *a_min, const f32 *a_max,
    const f32 *b_min, const f32 *b_max)
{
    /* Load directly from source pointers — no stack array intermediary */
    __m128 a_min_v = _mm_set_ps(0.0f, a_min[2], a_min[1], a_min[0]);
    __m128 a_max_v = _mm_set_ps(0.0f, a_max[2], a_max[1], a_max[0]);
    __m128 b_min_v = _mm_set_ps(0.0f, b_min[2], b_min[1], b_min[0]);
    __m128 b_max_v = _mm_set_ps(0.0f, b_max[2], b_max[1], b_max[0]);
    
    /* Test: a_max < b_min || b_max < a_min for each axis */
    __m128 test1 = _mm_cmplt_ps(a_max_v, b_min_v);  /* a_max < b_min */
    __m128 test2 = _mm_cmplt_ps(b_max_v, a_min_v);  /* b_max < a_min */
    
    /* Combine tests with OR */
    __m128 combined = _mm_or_ps(test1, test2);
    
    /* Check if any axis failed the overlap test */
    int mask = _mm_movemask_ps(combined);
    
    /* If any of the first 3 bits are set, there's no overlap */
    return (mask & 0x7) == 0;
}

/*
 * SSE2 ray-AABB intersection test.
 * Tests ray-box intersection using SIMD.
 * Returns 1 if hit, 0 otherwise. *out_t contains intersection distance.
 */
static inline int simd_ray_aabb_intersect_sse2(
    const f32 *origin, const f32 *inv_dir,
    const f32 *box_min, const f32 *box_max,
    f32 max_t, f32 *out_t)
{
    /* Load directly — no stack array intermediary */
    __m128 origin_v  = _mm_set_ps(0.0f, origin[2], origin[1], origin[0]);
    __m128 inv_dir_v = _mm_set_ps(0.0f, inv_dir[2], inv_dir[1], inv_dir[0]);
    __m128 box_min_v = _mm_set_ps(0.0f, box_min[2], box_min[1], box_min[0]);
    __m128 box_max_v = _mm_set_ps(0.0f, box_max[2], box_max[1], box_max[0]);
    
    /* t1 = (box_min - origin) * inv_dir */
    __m128 t1 = _mm_mul_ps(_mm_sub_ps(box_min_v, origin_v), inv_dir_v);
    /* t2 = (box_max - origin) * inv_dir */
    __m128 t2 = _mm_mul_ps(_mm_sub_ps(box_max_v, origin_v), inv_dir_v);
    
    /* Swap t1 and t2 where t1 > t2 */
    __m128 t_min = _mm_min_ps(t1, t2);
    __m128 t_max = _mm_max_ps(t1, t2);
    
    /* Extract values for scalar reduction via shuffle — no stack store */
    f32 tmin = 0.0f;
    f32 tmax = max_t;
    
    f32 v;
    v = _mm_cvtss_f32(t_min); if (v > tmin) tmin = v;
    v = _mm_cvtss_f32(t_max); if (v < tmax) tmax = v;
    if (tmin > tmax) return 0;
    t_min = _mm_shuffle_ps(t_min, t_min, _MM_SHUFFLE(1,1,1,1));
    t_max = _mm_shuffle_ps(t_max, t_max, _MM_SHUFFLE(1,1,1,1));
    v = _mm_cvtss_f32(t_min); if (v > tmin) tmin = v;
    v = _mm_cvtss_f32(t_max); if (v < tmax) tmax = v;
    if (tmin > tmax) return 0;
    t_min = _mm_shuffle_ps(t_min, t_min, _MM_SHUFFLE(2,2,2,2));
    t_max = _mm_shuffle_ps(t_max, t_max, _MM_SHUFFLE(2,2,2,2));
    v = _mm_cvtss_f32(t_min); if (v > tmin) tmin = v;
    v = _mm_cvtss_f32(t_max); if (v < tmax) tmax = v;
    if (tmin > tmax) return 0;
    
    *out_t = tmin;
    return 1;
}

/*
 * SSE2 vectorized velocity/position update for physics step.
 * Updates 4 floats at once for better throughput.
 */
static inline void simd_vec3_add_scaled_sse2(
    f32 *out, const f32 *a, const f32 *b, f32 scale)
{
    __m128 a_v = _mm_set_ps(0.0f, a[2], a[1], a[0]);
    __m128 b_v = _mm_set_ps(0.0f, b[2], b[1], b[0]);
    __m128 scale_v = _mm_set1_ps(scale);
    
    __m128 result = _mm_add_ps(a_v, _mm_mul_ps(b_v, scale_v));
    
    /* Store back only 3 components */
    out[0] = _mm_cvtss_f32(result);
    out[1] = _mm_cvtss_f32(_mm_shuffle_ps(result, result, _MM_SHUFFLE(1,1,1,1)));
    out[2] = _mm_cvtss_f32(_mm_shuffle_ps(result, result, _MM_SHUFFLE(2,2,2,2)));
}

/*
 * SSE2 vectorized damping: v *= damping for 3 components
 */
static inline void simd_vec3_scale_sse2(f32 *out, const f32 *v, f32 scale)
{
    __m128 v_v = _mm_set_ps(0.0f, v[2], v[1], v[0]);
    __m128 scale_v = _mm_set1_ps(scale);
    __m128 result = _mm_mul_ps(v_v, scale_v);
    
    out[0] = _mm_cvtss_f32(result);
    out[1] = _mm_cvtss_f32(_mm_shuffle_ps(result, result, _MM_SHUFFLE(1,1,1,1)));
    out[2] = _mm_cvtss_f32(_mm_shuffle_ps(result, result, _MM_SHUFFLE(2,2,2,2)));
}

/*
 * SSE2 dot product of two Vec3
 */
static inline f32 simd_vec3_dot_sse2(const f32 *a, const f32 *b)
{
    __m128 a_v = _mm_set_ps(0.0f, a[2], a[1], a[0]);
    __m128 b_v = _mm_set_ps(0.0f, b[2], b[1], b[0]);
    __m128 prod = _mm_mul_ps(a_v, b_v);
    
    /* Horizontal add: sum all 4 components */
    __m128 shuf = _mm_shuffle_ps(prod, prod, _MM_SHUFFLE(2, 3, 0, 1));
    __m128 sums = _mm_add_ps(prod, shuf);
    shuf = _mm_movehl_ps(shuf, sums);
    sums = _mm_add_ss(sums, shuf);
    
    return _mm_cvtss_f32(sums);
}

#else /* Fallback scalar implementations */

static inline int simd_aabb_overlap_sse2(
    const f32 *a_min, const f32 *a_max,
    const f32 *b_min, const f32 *b_max)
{
    for (int i = 0; i < 3; i++) {
        if (a_max[i] < b_min[i] || b_max[i] < a_min[i])
            return 0;
    }
    return 1;
}

static inline int simd_ray_aabb_intersect_sse2(
    const f32 *origin, const f32 *inv_dir,
    const f32 *box_min, const f32 *box_max,
    f32 max_t, f32 *out_t)
{
    f32 tmin = 0.0f;
    f32 tmax = max_t;
    
    for (int i = 0; i < 3; i++) {
        f32 t1 = (box_min[i] - origin[i]) * inv_dir[i];
        f32 t2 = (box_max[i] - origin[i]) * inv_dir[i];
        if (t1 > t2) { f32 tmp = t1; t1 = t2; t2 = tmp; }
        if (t1 > tmin) tmin = t1;
        if (t2 < tmax) tmax = t2;
        if (tmin > tmax) return 0;
    }
    *out_t = tmin;
    return 1;
}

static inline void simd_vec3_add_scaled_sse2(
    f32 *out, const f32 *a, const f32 *b, f32 scale)
{
    out[0] = a[0] + b[0] * scale;
    out[1] = a[1] + b[1] * scale;
    out[2] = a[2] + b[2] * scale;
}

static inline void simd_vec3_scale_sse2(f32 *out, const f32 *v, f32 scale)
{
    out[0] = v[0] * scale;
    out[1] = v[1] * scale;
    out[2] = v[2] * scale;
}

static inline f32 simd_vec3_dot_sse2(const f32 *a, const f32 *b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

#endif /* SIMD_SSE2 */

/* ============================================================
 * Batch AABB Operations (Process 4 AABBs at once with SSE)
 * ============================================================ */

#if SIMD_SSE2

/*
 * Test 4 AABBs against a single query AABB in parallel.
 * Returns a 4-bit mask indicating which AABBs overlap.
 */
static inline u32 simd_aabb_overlap_batch_sse2(
    const f32 *query_min, const f32 *query_max,
    const f32 *aabb_mins, const f32 *aabb_maxs)  /* 4 AABBs, interleaved */
{
    __m128 qmin_x = _mm_set1_ps(query_min[0]);
    __m128 qmin_y = _mm_set1_ps(query_min[1]);
    __m128 qmin_z = _mm_set1_ps(query_min[2]);
    __m128 qmax_x = _mm_set1_ps(query_max[0]);
    __m128 qmax_y = _mm_set1_ps(query_max[1]);
    __m128 qmax_z = _mm_set1_ps(query_max[2]);
    
    /* Load 4 AABB mins */
    __m128 amin_x = _mm_loadu_ps(&aabb_mins[0]);
    __m128 amin_y = _mm_loadu_ps(&aabb_mins[4]);
    __m128 amin_z = _mm_loadu_ps(&aabb_mins[8]);
    
    /* Load 4 AABB maxs */
    __m128 amax_x = _mm_loadu_ps(&aabb_maxs[0]);
    __m128 amax_y = _mm_loadu_ps(&aabb_maxs[4]);
    __m128 amax_z = _mm_loadu_ps(&aabb_maxs[8]);
    
    /* Test: qmax < amin || amax < qmin for each axis */
    __m128 fail_x = _mm_or_ps(_mm_cmplt_ps(qmax_x, amin_x), _mm_cmplt_ps(amax_x, qmin_x));
    __m128 fail_y = _mm_or_ps(_mm_cmplt_ps(qmax_y, amin_y), _mm_cmplt_ps(amax_y, qmin_y));
    __m128 fail_z = _mm_or_ps(_mm_cmplt_ps(qmax_z, amin_z), _mm_cmplt_ps(amax_z, qmin_z));
    
    /* Combine all failures */
    __m128 fail = _mm_or_ps(_mm_or_ps(fail_x, fail_y), fail_z);
    
    /* Return mask of passing AABBs (inverted fail mask) */
    int fail_mask = _mm_movemask_ps(fail);
    return (~fail_mask) & 0xF;
}

#else

static inline u32 simd_aabb_overlap_batch_sse2(
    const f32 *query_min, const f32 *query_max,
    const f32 *aabb_mins, const f32 *aabb_maxs)
{
    u32 result = 0;
    for (int i = 0; i < 4; i++) {
        int overlap = 1;
        for (int j = 0; j < 3; j++) {
            if (query_max[j] < aabb_mins[i * 4 + j] || 
                aabb_maxs[i * 4 + j] < query_min[j]) {
                overlap = 0;
                break;
            }
        }
        if (overlap) result |= (1u << i);
    }
    return result;
}

#endif /* SIMD_SSE2 */
