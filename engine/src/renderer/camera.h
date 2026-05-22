#pragma once
#include <core/types.h>
#include <platform/input.h>
#include <math/math.h>

typedef struct {
    Vec3 position;
    f32  yaw;
    f32  pitch;
    f32  fov;
    f32  aspect;
    f32  near_plane;
    f32  far_plane;
    f32  move_speed;
    f32  mouse_sensitivity;
} Camera;

void camera_init(Camera *cam, f32 fov, f32 aspect, f32 near_plane, f32 far_plane);
Mat4 camera_view(const Camera *cam);
Mat4 camera_projection(const Camera *cam);
void camera_update(Camera *cam, const InputState *input, f32 dt);
