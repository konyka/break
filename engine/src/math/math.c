#include <math/math.h>
#include <string.h>

#if defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
    #include <immintrin.h>
    #define MATH_SSE2 1
#else
    #define MATH_SSE2 0
#endif

Mat4 mat4_identity(void) {
    Mat4 m = {0};
    m.e[0][0] = 1.0f; m.e[1][1] = 1.0f;
    m.e[2][2] = 1.0f; m.e[3][3] = 1.0f;
    return m;
}

Mat4 mat4_ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near_val, f32 far_val) {
    Mat4 m = {0};
    m.e[0][0] =  2.0f / (right - left);
    m.e[1][1] =  2.0f / (top - bottom);
    m.e[2][2] = -2.0f / (far_val - near_val);
    m.e[3][0] = -(right + left) / (right - left);
    m.e[3][1] = -(top + bottom) / (top - bottom);
    m.e[3][2] = -(far_val + near_val) / (far_val - near_val);
    m.e[3][3] =  1.0f;
    return m;
}

Mat4 mat4_perspective(f32 fov_rad, f32 aspect, f32 near_val, f32 far_val) {
    f32 f = 1.0f / tanf(fov_rad * 0.5f);
    Mat4 m = {0};
    m.e[0][0] = f / aspect;
    m.e[1][1] = f;
    m.e[2][2] = -(far_val + near_val) / (far_val - near_val);
    m.e[2][3] = -1.0f;
    m.e[3][2] = -(2.0f * far_val * near_val) / (far_val - near_val);
    return m;
}

Mat4 mat4_lookat(Vec3 eye, Vec3 target, Vec3 up) {
    Vec3 f = vec3_normalize(vec3_sub(target, eye));
    Vec3 s = vec3_normalize(vec3_cross(f, up));
    Vec3 u = vec3_cross(s, f);

    Mat4 m = mat4_identity();
    /* Left-handed view matrix matching camera_view convention:
     * right s_L = -normalize(cross(f,up)) so that s_L x u = f (not -f).
     * camera_view uses this same left-handed basis: s x u = f, not -f. */
    m.e[0][0] = -s.e[0]; m.e[0][1] = -s.e[1]; m.e[0][2] = -s.e[2];
    m.e[0][3] =  vec3_dot(s, eye);
    m.e[1][0] =  u.e[0]; m.e[1][1] =  u.e[1]; m.e[1][2] =  u.e[2];
    m.e[1][3] = -vec3_dot(u, eye);
    m.e[2][0] = -f.e[0]; m.e[2][1] = -f.e[1]; m.e[2][2] = -f.e[2];
    m.e[2][3] =  vec3_dot(f, eye);
    return m;
}

Mat4 mat4_inverse(Mat4 m) {
    f32 *e = &m.e[0][0];
    f32 inv[16];    inv[0]  =  e[5]*e[10]*e[15] - e[5]*e[11]*e[14] - e[9]*e[6]*e[15] + e[9]*e[7]*e[14] + e[13]*e[6]*e[11] - e[13]*e[7]*e[10];
    inv[4]  = -e[4]*e[10]*e[15] + e[4]*e[11]*e[14] + e[8]*e[6]*e[15] - e[8]*e[7]*e[14] - e[12]*e[6]*e[11] + e[12]*e[7]*e[10];
    inv[8]  =  e[4]*e[9]*e[15]  - e[4]*e[11]*e[13] - e[8]*e[5]*e[15] + e[8]*e[7]*e[13] + e[12]*e[5]*e[11] - e[12]*e[7]*e[9];
    inv[12] = -e[4]*e[9]*e[14]  + e[4]*e[10]*e[13] + e[8]*e[5]*e[14] - e[8]*e[6]*e[13] - e[12]*e[5]*e[10] + e[12]*e[6]*e[9];

    inv[1]  = -e[1]*e[10]*e[15] + e[1]*e[11]*e[14] + e[9]*e[2]*e[15] - e[9]*e[3]*e[14] - e[13]*e[2]*e[11] + e[13]*e[3]*e[10];
    inv[5]  =  e[0]*e[10]*e[15] - e[0]*e[11]*e[14] - e[8]*e[2]*e[15] + e[8]*e[3]*e[14] + e[12]*e[2]*e[11] - e[12]*e[3]*e[10];
    inv[9]  = -e[0]*e[9]*e[15]  + e[0]*e[11]*e[13] + e[8]*e[1]*e[15] - e[8]*e[3]*e[13] - e[12]*e[1]*e[11] + e[12]*e[3]*e[9];
    inv[13] =  e[0]*e[9]*e[14]  - e[0]*e[10]*e[13] - e[8]*e[1]*e[14] + e[8]*e[2]*e[13] + e[12]*e[1]*e[10] - e[12]*e[2]*e[9];

    inv[2]  =  e[1]*e[6]*e[15]  - e[1]*e[7]*e[14]  - e[5]*e[2]*e[15] + e[5]*e[3]*e[14] + e[13]*e[2]*e[7]  - e[13]*e[3]*e[6];
    inv[6]  = -e[0]*e[6]*e[15]  + e[0]*e[7]*e[14]  + e[4]*e[2]*e[15] - e[4]*e[3]*e[14] - e[12]*e[2]*e[7]  + e[12]*e[3]*e[6];
    inv[10] =  e[0]*e[5]*e[15]  - e[0]*e[7]*e[13]  - e[4]*e[1]*e[15] + e[4]*e[3]*e[13] + e[12]*e[1]*e[7]  - e[12]*e[3]*e[5];
    inv[14] = -e[0]*e[5]*e[14]  + e[0]*e[6]*e[13]  + e[4]*e[1]*e[14] - e[4]*e[2]*e[13] - e[12]*e[1]*e[6]  + e[12]*e[2]*e[5];

    inv[3]  = -e[1]*e[6]*e[11]  + e[1]*e[7]*e[10]  + e[5]*e[2]*e[11] - e[5]*e[3]*e[10] - e[9]*e[2]*e[7]   + e[9]*e[3]*e[6];
    inv[7]  =  e[0]*e[6]*e[11]  - e[0]*e[7]*e[10]  - e[4]*e[2]*e[11] + e[4]*e[3]*e[10] + e[8]*e[2]*e[7]   - e[8]*e[3]*e[6];
    inv[11] = -e[0]*e[5]*e[11]  + e[0]*e[7]*e[9]   + e[4]*e[1]*e[11] - e[4]*e[3]*e[9]  - e[8]*e[1]*e[7]   + e[8]*e[3]*e[5];
    inv[15] =  e[0]*e[5]*e[10]  - e[0]*e[6]*e[9]   - e[4]*e[1]*e[10] + e[4]*e[2]*e[9]  + e[8]*e[1]*e[6]   - e[8]*e[2]*e[5];

    f32 det = e[0]*inv[0] + e[1]*inv[4] + e[2]*inv[8] + e[3]*inv[12];
    if (det == 0.0f) return mat4_identity();

    f32 idet = 1.0f / det;
    Mat4 out;
    f32 *o = &out.e[0][0];
    for (int i = 0; i < 16; i++) o[i] = inv[i] * idet;
    return out;
}

Mat4 mat4_translation(f32 x, f32 y, f32 z) {
    Mat4 m = mat4_identity();
    m.e[3][0] = x;
    m.e[3][1] = y;
    m.e[3][2] = z;
    return m;
}

Mat4 mat4_scaling(f32 x, f32 y, f32 z) {
    Mat4 m = {0};
    m.e[0][0] = x;
    m.e[1][1] = y;
    m.e[2][2] = z;
    m.e[3][3] = 1.0f;
    return m;
}

Mat4 mat4_from_quat(Quat q) {
    f32 x = q.e[0], y = q.e[1], z = q.e[2], w = q.e[3];
    Mat4 m = mat4_identity();
    m.e[0][0] = 1.0f - 2.0f*(y*y + z*z);
    m.e[0][1] = 2.0f*(x*y + w*z);
    m.e[0][2] = 2.0f*(x*z - w*y);
    m.e[1][0] = 2.0f*(x*y - w*z);
    m.e[1][1] = 1.0f - 2.0f*(x*x + z*z);
    m.e[1][2] = 2.0f*(y*z + w*x);
    m.e[2][0] = 2.0f*(x*z + w*y);
    m.e[2][1] = 2.0f*(y*z - w*x);
    m.e[2][2] = 1.0f - 2.0f*(x*x + y*y);
    return m;
}
