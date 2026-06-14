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
    /* Cached trig from camera_update — reused by camera_view to avoid 4 redundant trig calls per frame. */
    f32  _cy, _sy, _cp, _sp;
    /* Cached projection matrix — invalidated when fov/aspect/near/far change. */
    Mat4 _proj;
    f32  _proj_fov;
    f32  _proj_aspect;
    f32  _proj_near;
    f32  _proj_far;
} Camera;

void camera_init(Camera *cam, f32 fov, f32 aspect, f32 near_plane, f32 far_plane);
Mat4 camera_view(const Camera *cam);
/* R52: Analytical inverse view — uses cached trig, zero extra trig calls, ~0 muls. */
Mat4 camera_inv_view(const Camera *cam);
Mat4 camera_projection(Camera *cam);
void camera_update(Camera *cam, const InputState *input, f32 dt);
