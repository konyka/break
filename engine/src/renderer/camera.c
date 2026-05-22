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
}

static Vec3 camera_forward(const Camera *cam) {
    f32 cp = cosf(cam->pitch);
    return vec3_normalize(vec3(
        cp * sinf(cam->yaw),
        sinf(cam->pitch),
        -cp * cosf(cam->yaw)
    ));
}

static Vec3 camera_right(const Camera *cam) {
    Vec3 fwd = camera_forward(cam);
    Vec3 world_up = vec3(0.0f, 1.0f, 0.0f);
    return vec3_normalize(vec3_cross(fwd, world_up));
}

Mat4 camera_view(const Camera *cam) {
    Vec3 fwd = camera_forward(cam);
    Vec3 target = vec3_add(cam->position, fwd);
    return mat4_lookat(cam->position, target, vec3(0.0f, 1.0f, 0.0f));
}

Mat4 camera_projection(const Camera *cam) {
    return mat4_perspective(cam->fov, cam->aspect, cam->near_plane, cam->far_plane);
}

void camera_update(Camera *cam, const InputState *input, f32 dt) {
    if (input_key_down(input, 'w')) {
        Vec3 fwd = camera_forward(cam);
        cam->position = vec3_add(cam->position, vec3_scale(fwd, cam->move_speed * dt));
    }
    if (input_key_down(input, 's')) {
        Vec3 fwd = camera_forward(cam);
        cam->position = vec3_sub(cam->position, vec3_scale(fwd, cam->move_speed * dt));
    }
    if (input_key_down(input, 'd')) {
        Vec3 right = camera_right(cam);
        cam->position = vec3_add(cam->position, vec3_scale(right, cam->move_speed * dt));
    }
    if (input_key_down(input, 'a')) {
        Vec3 right = camera_right(cam);
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
