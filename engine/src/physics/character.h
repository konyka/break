#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/physics.h>

typedef struct {
    Vec3  position;
    Vec3  velocity;
    f32   radius;
    f32   height;
    f32   slope_limit;
    f32   step_height;
    bool  grounded;
    bool  jump_requested;
} CharacterController;

CharacterController character_create(Vec3 pos, f32 radius, f32 height);
void    character_update(CharacterController *cc, PhysicsWorld *pw, f32 dt,
                          Vec3 move_input, bool jump);
Vec3    character_get_position(const CharacterController *cc);
bool    character_is_grounded(const CharacterController *cc);

bool    physics_sweep_test(const PhysicsWorld *pw, Vec3 origin, Vec3 delta,
                            u32 ignore_body, Vec3 *out_hit_pos, f32 *out_t);
