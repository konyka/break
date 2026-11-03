#include <physics/vehicle.h>
#include <physics/character.h>
#include <math.h>
#include <string.h>

static Quat chassis_quat(const RigidBody *b) {
    f32 l2 = b->orientation.e[0] * b->orientation.e[0] + b->orientation.e[1] * b->orientation.e[1] +
             b->orientation.e[2] * b->orientation.e[2] + b->orientation.e[3] * b->orientation.e[3];
    if (l2 <= 1e-12f) return QUAT_IDENTITY;
    return quat_normalize(b->orientation);
}

bool vehicle_create(Vehicle *v, PhysicsWorld *pw, Vec3 position) {
    if (!v || !pw) return false;
    Vehicle next;
    memset(&next, 0, sizeof(next));
    PhysicsBodyHandle id = physics_body_create(pw, position, vec3(0.9f, 0.35f, 1.8f), 800.0f, false, 0);
    if (!physics_body_handle_is_valid(id)) return false;
    next.chassis = id;
    next.wheel_radius = 0.35f;
    next.suspension_rest = 0.35f;
    next.stiffness = 80000.0f;
    next.wheel_local[0] = vec3(-0.8f, -0.15f, 1.2f);
    next.wheel_local[1] = vec3(0.8f, -0.15f, 1.2f);
    next.wheel_local[2] = vec3(-0.8f, -0.15f, -1.2f);
    next.wheel_local[3] = vec3(0.8f, -0.15f, -1.2f);
    PhysicsPose pose;
    pose.orientation = QUAT_IDENTITY;
    pose.angular_velocity = vec3(0, 0, 0);
    pose.inertia_diag = vec3(1, 1, 1);
    physics_body_set_pose(pw, id, &pose);
    for (u32 i = 0; i < 4; i++) {
        next.wheels[i].local_position = next.wheel_local[i];
        next.wheels[i].ground_body = PHYSICS_BODY_HANDLE_INVALID;
    }
    *v = next;
    return true;
}

void vehicle_destroy(Vehicle *v, PhysicsWorld *pw) {
    if (!v) return;
    if (pw && physics_body_resolve(pw, v->chassis)) physics_body_park(pw, v->chassis);
    v->chassis = PHYSICS_BODY_HANDLE_INVALID;
    v->occupied = false;
    memset(&v->control, 0, sizeof(v->control));
    memset(v->wheels, 0, sizeof(v->wheels));
    for (u32 i = 0; i < 4; i++) v->wheels[i].ground_body = PHYSICS_BODY_HANDLE_INVALID;
}

void vehicle_step(Vehicle *v, PhysicsWorld *pw, const VehicleInput *in, f32 dt) {
    if (!v || !pw || !in) return;
    if (!isfinite(dt) || !(dt > 0.0f) || !isfinite(in->throttle) ||
        !isfinite(in->steer) || !isfinite(in->brake)) return;
    RigidBody *b = physics_body_resolve(pw, v->chassis);
    if (!b || b->inv_mass <= 0.0f) return;

    VehicleControlState control;
    control.throttle = in->throttle;
    control.steer = in->steer;
    control.brake = in->brake;
    if (control.throttle > 1.0f) control.throttle = 1.0f;
    if (control.throttle < -1.0f) control.throttle = -1.0f;
    if (control.steer > 1.0f) control.steer = 1.0f;
    if (control.steer < -1.0f) control.steer = -1.0f;
    if (control.brake > 1.0f) control.brake = 1.0f;
    if (control.brake < 0.0f) control.brake = 0.0f;
    v->control = control;
    if (control.throttle != 0.0f || control.steer != 0.0f || control.brake != 0.0f)
        physics_body_wake(pw, v->chassis);

    Quat q = chassis_quat(b);
    Vec3 up = quat_rotate_vec3(q, vec3(0, 1, 0));
    Vec3 down = vec3_scale(up, -1.0f);
    Vec3 forward = quat_rotate_vec3(q, vec3(0, 0, 1));
    Vec3 suspension = vec3(0, 0, 0);
    Vec3 drive = vec3(0, 0, 0);
    Vec3 grip_delta = vec3(0, 0, 0);
    u32 grounded = 0;
    f32 reach = v->suspension_rest + v->wheel_radius;
    for (u32 i = 0; i < 4; i++) {
        VehicleWheel *wheel = &v->wheels[i];
        wheel->local_position = v->wheel_local[i];
        wheel->world_position = vec3_add(b->position, quat_rotate_vec3(q, wheel->local_position));
        wheel->contact_point = vec3(0, 0, 0);
        wheel->contact_normal = vec3(0, 0, 0);
        wheel->ground_body = PHYSICS_BODY_HANDLE_INVALID;
        wheel->compression = 0.0f;
        wheel->suspension_force = 0.0f;
        wheel->grounded = false;

        Vec3 delta = vec3_scale(down, reach);
        f32 t = 1.0f;
        Vec3 hit;
        Vec3 normal;
        PhysicsBodyHandle ground_body;
        if (!physics_sweep_test_ex(pw, wheel->world_position, delta, v->chassis,
                                   &hit, &t, &ground_body, &normal)) continue;
        f32 compression = reach * (1.0f - t);
        if (!(compression > 0.0f)) continue;
        Vec3 lever = vec3_sub(wheel->world_position, b->position);
        Vec3 point_velocity = vec3_add(b->velocity, vec3_cross(b->angular_velocity, lever));
        f32 force = compression * v->stiffness + 6000.0f * vec3_dot(point_velocity, down);
        if (force < 0.0f) force = 0.0f;
        wheel->grounded = true;
        wheel->ground_body = ground_body;
        wheel->contact_point = hit;
        wheel->contact_normal = normal;
        wheel->compression = compression;
        wheel->suspension_force = force;
        suspension = vec3_add(suspension, vec3_scale(normal, force));
        grounded++;

        Vec3 wheel_forward = forward;
        if (i < 2u) {
            Quat steering = quat_from_axis_angle(up, control.steer * 0.55f);
            wheel_forward = quat_rotate_vec3(steering, forward);
        }
        drive = vec3_add(drive, vec3_scale(wheel_forward, control.throttle * 3000.0f));
        Vec3 wheel_right = vec3_normalize(vec3_cross(up, wheel_forward));
        f32 lateral = vec3_dot(point_velocity, wheel_right);
        grip_delta = vec3_sub(grip_delta, vec3_scale(wheel_right, lateral));
    }

    Vec3 force = vec3_add(suspension, drive);
    b->acceleration = vec3_add(vec3(0, -9.81f, 0), vec3_scale(force, b->inv_mass));
    if (grounded > 0u) {
        f32 grip = 10.0f * dt;
        if (grip > 1.0f) grip = 1.0f;
        grip_delta = vec3_scale(grip_delta, grip / (f32)grounded);
        b->velocity = vec3_add(b->velocity, grip_delta);
        f32 keep = 1.0f - control.brake * 8.0f * dt;
        if (keep < 0.0f) keep = 0.0f;
        b->velocity.e[0] *= keep;
        b->velocity.e[2] *= keep;
        if (b->inertia_diag.e[1] > 0.0f) {
            f32 speed = vec3_dot(b->velocity, forward);
            f32 target_yaw = control.steer * speed * tanf(0.55f) / 2.4f;
            f32 blend = 8.0f * dt;
            if (blend > 1.0f) blend = 1.0f;
            b->angular_velocity.e[1] += (target_yaw - b->angular_velocity.e[1]) * blend;
        }
    }
}

bool vehicle_enter(Vehicle *v) {
    if (!v || v->occupied) return false;
    v->occupied = true;
    return true;
}

bool vehicle_exit(Vehicle *v, PhysicsWorld *pw, Vec3 *out_feet) {
    if (!v || !pw || !out_feet || !v->occupied) return false;
    RigidBody *b = physics_body_resolve(pw, v->chassis);
    if (!b) return false;
    Quat q = chassis_quat(b);
    Vec3 right = quat_rotate_vec3(q, vec3(1, 0, 0));
    Vec3 origin = vec3_add(b->position, vec3_scale(right, 0.2f));
    Vec3 delta = vec3_scale(right, 1.5f);
    f32 t = 1.0f;
    Vec3 hit;
    if (physics_sweep_test(pw, origin, delta, v->chassis, &hit, &t)) return false;
    *out_feet = vec3_add(origin, delta);
    out_feet->e[1] = b->position.e[1];
    v->occupied = false;
    return true;
}
