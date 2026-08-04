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
     * right    s = (cy, 0, sy)             — analytically unit length
     * up       u = s × f = (-sy*sp, cp, cy*sp) — analytically unit length
     *
     * view = | s.x   s.y   s.z   -dot(s,eye) |
     *        | u.x   u.y   u.z   -dot(u,eye) |
     *        |-f.x  -f.y  -f.z    dot(f,eye) |
     *        |  0     0     0          1      |
     *
     * R439: right-handed basis — s = cross(f, world_up) gives det = +1 (the
     * pre-R439 s = (-cy,0,-sy) was left-handed: mirrored image, flipped
     * winding). Stored row 1 is unchanged by the flip: the old basis kept
     * u = f × s_L, which equals s × f for the new s = -s_L.
     * R438: stored canonical column-major (e[col][row]) — each row of the
     * math matrix above is written across e[0..3][row], translation lands in
     * e[3][0..2] (same layout as mat4_translation; uploaded untransposed). */
    f32 cy = cam->_cy, sy = cam->_sy, cp = cam->_cp, sp = cam->_sp;
    f32 ex = cam->position.e[0], ey = cam->position.e[1], ez = cam->position.e[2];

    Mat4 m;
    /* Row 0: right s = (cy, 0, sy) */
    m.e[0][0] = cy;       m.e[1][0] = 0.0f; m.e[2][0] = sy;
    m.e[3][0] = -(cy * ex + sy * ez);
    /* Row 1: up u = (-sy*sp, cp, cy*sp) */
    m.e[0][1] = -sy * sp; m.e[1][1] = cp;   m.e[2][1] = cy * sp;
    m.e[3][1] = sy * sp * ex - cp * ey - cy * sp * ez;
    /* Row 2: -forward = (-cp*sy, -sp, cp*cy) */
    m.e[0][2] = -cp * sy; m.e[1][2] = -sp;  m.e[2][2] = cp * cy;
    m.e[3][2] = cp * sy * ex + sp * ey - cp * cy * ez;
    /* Column 3 padding / bottom row */
    m.e[0][3] = 0.0f;     m.e[1][3] = 0.0f; m.e[2][3] = 0.0f; m.e[3][3] = 1.0f;
    return m;
}

Mat4 camera_inv_view(const Camera *cam) {
    /* R52-fix: Analytical inverse view using cached trig — zero extra trig calls.
     * V = [R|t] with R orthonormal → V_inv = [R^T | eye; 0 0 0 1].
     * R438: canonical column-major storage — column-major R^T is the
     * transpose of column-major R, so storage col j of the rotation block is
     * basis row j of the view matrix: col0 = s, col1 = u, col2 = -f. */
    f32 cy = cam->_cy, sy = cam->_sy, cp = cam->_cp, sp = cam->_sp;
    f32 ex = cam->position.e[0], ey = cam->position.e[1], ez = cam->position.e[2];
    Mat4 m;
    /* col0 = s = (cy, 0, sy) — R439 right-handed right vector */
    m.e[0][0] = cy;       m.e[0][1] = 0.0f;      m.e[0][2] = sy;       m.e[0][3] = 0.0f;
    /* col1 = u = (-sy*sp, cp, cy*sp) */
    m.e[1][0] = -sy * sp; m.e[1][1] = cp;        m.e[1][2] = cy * sp;  m.e[1][3] = 0.0f;
    /* col2 = -f = (-cp*sy, -sp, cp*cy) */
    m.e[2][0] = -cp * sy; m.e[2][1] = -sp;       m.e[2][2] = cp * cy;  m.e[2][3] = 0.0f;
    /* Translation column = eye */
    m.e[3][0] = ex;       m.e[3][1] = ey;        m.e[3][2] = ez;       m.e[3][3] = 1.0f;
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
    /* Save pre-update cached trig for WASD movement (move where you were looking). */
    f32 cy = cam->_cy, sy = cam->_sy, cp = cam->_cp, sp = cam->_sp;
    Vec3 fwd = {{cp * sy, sp, -cp * cy}};
    /* R439: right vector follows the right-handed view basis — (cy,0,sy),
     * the negation of the pre-flip left-handed right. Keeps D = screen-right. */
    Vec3 right = {{cy, 0.0f, sy}};

    /* R367: Shift+WASD is brush/ambient/teleport/mass — skip move while Shift held. */
    if (!input_key_down(input, 289)) {
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
    }

    /* Update orientation from mouse input. */
    cam->yaw   += input->mouse_dx * cam->mouse_sensitivity;
    cam->pitch += input->mouse_dy * cam->mouse_sensitivity;

    if (cam->yaw < 0.0f)          cam->yaw += 2.0f * 3.14159265f;
    if (cam->yaw > 2.0f * 3.14159265f) cam->yaw -= 2.0f * 3.14159265f;

    f32 pitch_limit = 1.5533f;
    if (cam->pitch >  pitch_limit) cam->pitch =  pitch_limit;
    if (cam->pitch < -pitch_limit) cam->pitch = -pitch_limit;

    /* Cache trig AFTER yaw/pitch update so downstream gets fresh values.
     * Eliminates one-frame delay: camera_view/camera_inv_view and main.c
     * cam_cy/cam_sy/cam_cp/cam_sp now reflect current frame's orientation. */
    cam->_cy = cosf(cam->yaw); cam->_sy = sinf(cam->yaw);
    cam->_cp = cosf(cam->pitch); cam->_sp = sinf(cam->pitch);
}
