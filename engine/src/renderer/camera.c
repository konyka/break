#include <renderer/camera.h>
#include <math.h>

void camera_init(Camera *cam, f32 fov, f32 aspect, f32 near_plane, f32 far_plane) {
    cam->position         = vec3(0.0f, 2.0f, 8.0f);
    cam->yaw              = 0.0f;
    cam->pitch            = 0.0f;
    cam->fov              = fov;
    cam->aspect           = aspect;
    cam->near_plane       = near_plane;
    cam->far_plane        = far_plane;
    cam->move_speed       = 3.0f;
    cam->mouse_sensitivity = 0.002f;
    /* Initialize cached trig so camera_view() works without camera_update(). */
    cam->_cy = 1.0f; cam->_sy = 0.0f;
    cam->_cp = 1.0f; cam->_sp = 0.0f;
    /* Initialize cached projection as invalid (forces first-call recompute). */
    cam->_proj_fov = -1.0f;
    cam->_proj_aspect = -1.0f;
    cam->_proj_near = -1.0f;
    cam->_proj_far = -1.0f;
}

Mat4 camera_view(const Camera *cam) {
    /* Direct view matrix from cached trig: eliminates mat4_lookat overhead
     * (2 vec3_normalize + 2 vec3_cross + mat4_identity) and 4 redundant trig calls.
     *
     * forward  f = (cp*sy, sp, -cp*cy)     — analytically unit length
     * right    s = (-cy, 0, -sy)            — analytically unit length
     * up       u = s × f = (-sy*sp, cp, cy*sp) — analytically unit length
     *
     * view = | s.x   s.y   s.z   -dot(s,eye) |
     *        | u.x   u.y   u.z   -dot(u,eye) |
     *        |-f.x  -f.y  -f.z    dot(f,eye) |
     *        |  0     0     0          1      |
     */
    f32 cy = cam->_cy, sy = cam->_sy, cp = cam->_cp, sp = cam->_sp;
    f32 ex = cam->position.e[0], ey = cam->position.e[1], ez = cam->position.e[2];

    Mat4 m;
    /* Row 0: right s = (-cy, 0, -sy) */
    m.e[0][0] = -cy;  m.e[0][1] = 0.0f; m.e[0][2] = -sy;
    m.e[0][3] = cy * ex + sy * ez;
    /* Row 1: up u = (-sy*sp, cp, cy*sp) */
    m.e[1][0] = -sy * sp;  m.e[1][1] = cp;  m.e[1][2] = cy * sp;
    m.e[1][3] = sy * sp * ex - cp * ey - cy * sp * ez;
    /* Row 2: -forward = (-cp*sy, -sp, cp*cy) */
    m.e[2][0] = -cp * sy;  m.e[2][1] = -sp;  m.e[2][2] = cp * cy;
    m.e[2][3] = cp * sy * ex + sp * ey - cp * cy * ez;
    /* Row 3 */
    m.e[3][0] = 0.0f;  m.e[3][1] = 0.0f;  m.e[3][2] = 0.0f;  m.e[3][3] = 1.0f;
    return m;
}

Mat4 camera_inv_view(const Camera *cam) {
    /* R52-fix: Analytical inverse view using cached trig — zero extra trig calls.
     * V = [R|t] with R orthonormal → V_inv = [R^T | eye; 0 0 0 1].
     * In e[col][row] column-major storage, R^T columns = rows of V's rotation block.
     * V row0 = R_row0 = (s.x, u.x, -f.x, 0) = (-cy, -sy*sp, -cp*sy, 0)
     * V row1 = R_row1 = (s.y, u.y, -f.y, 0) = (0, cp, -sp, 0)
     * V row2 = R_row2 = (s.z, u.z, -f.z, 0) = (-sy, cy*sp, cp*cy, 0) */
    f32 cy = cam->_cy, sy = cam->_sy, cp = cam->_cp, sp = cam->_sp;
    f32 ex = cam->position.e[0], ey = cam->position.e[1], ez = cam->position.e[2];
    Mat4 m;
    /* R^T col0 = R row0 */
    m.e[0][0] = -cy;      m.e[0][1] = -sy * sp;  m.e[0][2] = -cp * sy;  m.e[0][3] = ex;
    /* R^T col1 = R row1 */
    m.e[1][0] = 0.0f;     m.e[1][1] = cp;         m.e[1][2] = -sp;        m.e[1][3] = ey;
    /* R^T col2 = R row2 */
    m.e[2][0] = -sy;      m.e[2][1] = cy * sp;    m.e[2][2] = cp * cy;    m.e[2][3] = ez;
    /* Row 3 */
    m.e[3][0] = 0.0f;     m.e[3][1] = 0.0f;       m.e[3][2] = 0.0f;       m.e[3][3] = 1.0f;
    return m;
}

Mat4 camera_projection(Camera *cam) {
    /* Cache projection matrix — skip tanf + 3 divisions when fov/aspect/near/far unchanged. */
    if (cam->fov != cam->_proj_fov || cam->aspect != cam->_proj_aspect ||
        cam->near_plane != cam->_proj_near || cam->far_plane != cam->_proj_far) {
        cam->_proj = mat4_perspective(cam->fov, cam->aspect, cam->near_plane, cam->far_plane);
        cam->_proj_fov = cam->fov;
        cam->_proj_aspect = cam->aspect;
        cam->_proj_near = cam->near_plane;
        cam->_proj_far = cam->far_plane;
    }
    return cam->_proj;
}

void camera_update(Camera *cam, const InputState *input, f32 dt) {
    /* Precompute trig values once — avoids 8-12 transcendental calls per frame */
    f32 cy = cosf(cam->yaw);
    f32 sy = sinf(cam->yaw);
    f32 cp = cosf(cam->pitch);
    f32 sp = sinf(cam->pitch);

    /* Cache for camera_view() to reuse (avoids 4 redundant trig calls). */
    cam->_cy = cy; cam->_sy = sy; cam->_cp = cp; cam->_sp = sp;

    /* Forward = normalize(cp*sy, sp, -cp*cy) — already unit length since cp²+sp²=1 */
    Vec3 fwd = {{cp * sy, sp, -cp * cy}};
    /* Right = normalize(fwd × up) = normalize(-cy, 0, -sy) for up=(0,1,0) */
    Vec3 right = {{-cy, 0.0f, -sy}};

    if (input_key_down(input, 'w')) {
        cam->position = vec3_add(cam->position, vec3_scale(fwd, cam->move_speed * dt));
    }
    if (input_key_down(input, 's')) {
        cam->position = vec3_sub(cam->position, vec3_scale(fwd, cam->move_speed * dt));
    }
    if (input_key_down(input, 'd')) {
        cam->position = vec3_add(cam->position, vec3_scale(right, cam->move_speed * dt));
    }
    if (input_key_down(input, 'a')) {
        cam->position = vec3_sub(cam->position, vec3_scale(right, cam->move_speed * dt));
    }

    cam->yaw   += input->mouse_dx * cam->mouse_sensitivity;
    cam->pitch += input->mouse_dy * cam->mouse_sensitivity;

    if (cam->yaw < 0.0f)          cam->yaw += 2.0f * 3.14159265f;
    if (cam->yaw > 2.0f * 3.14159265f) cam->yaw -= 2.0f * 3.14159265f;

    f32 pitch_limit = 1.5533f;
    if (cam->pitch >  pitch_limit) cam->pitch =  pitch_limit;
    if (cam->pitch < -pitch_limit) cam->pitch = -pitch_limit;
}
