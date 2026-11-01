#include <physics/vehicle.h>
#include <physics/character.h>
#include <math.h>

static Quat chassis_quat(const RigidBody *b) {
    f32 l2 = b->orientation.e[0] * b->orientation.e[0] + b->orientation.e[1] * b->orientation.e[1] +
             b->orientation.e[2] * b->orientation.e[2] + b->orientation.e[3] * b->orientation.e[3];
    if (l2 <= 1e-12f) return QUAT_IDENTITY;
    return quat_normalize(b->orientation);
}

bool vehicle_create(Vehicle *v, PhysicsWorld *pw, Vec3 position) {
    if (!v || !pw) return false;
    u32 id = physics_body_create(pw, position, vec3(0.9f, 0.35f, 1.8f), 800.0f, false, 0);
    if (id == UINT32_MAX) return false;
    v->chassis = id;
    v->wheel_radius = 0.35f;
    v->suspension_rest = 0.35f;
    v->stiffness = 80000.0f;
    v->occupied = false;
    v->wheel_local[0] = vec3(-0.8f, -0.15f, 1.2f);
    v->wheel_local[1] = vec3(0.8f, -0.15f, 1.2f);
    v->wheel_local[2] = vec3(-0.8f, -0.15f, -1.2f);
    v->wheel_local[3] = vec3(0.8f, -0.15f, -1.2f);
    PhysicsPose pose;
    pose.orientation = QUAT_IDENTITY;
    pose.angular_velocity = vec3(0, 0, 0);
    pose.inertia_diag = vec3(1, 1, 1);
    physics_body_set_pose(pw, id, &pose);
    return true;
}

void vehicle_step(Vehicle *v, PhysicsWorld *pw, const VehicleInput *in, f32 dt) {
    if (!v || !pw || !in || v->chassis >= pw->count) return;
    (void)dt;
    RigidBody *b = &pw->bodies[v->chassis];
    Quat q = chassis_quat(b);
    Vec3 down = quat_rotate_vec3(q, vec3(0, -1, 0));
    Vec3 forward = quat_rotate_vec3(q, vec3(0, 0, 1));
    f32 spring = 0.0f;
    f32 reach = v->suspension_rest + v->wheel_radius;
    for (u32 i = 0; i < 4; i++) {
        Vec3 origin = vec3_add(b->position, quat_rotate_vec3(q, v->wheel_local[i]));
        Vec3 delta = vec3_scale(down, reach);
        f32 t = 1.0f;
        Vec3 hit;
        if (!physics_sweep_test(pw, origin, delta, v->chassis, &hit, &t)) continue;
        f32 compression = reach * (1.0f - t);
        if (compression > 0.0f) spring += compression * v->stiffness;
    }
    f32 throttle = in->throttle;
    if (throttle > 1.0f) throttle = 1.0f;
    if (throttle < -1.0f) throttle = -1.0f;
    f32 brake = in->brake;
    if (brake < 0.0f) brake = 0.0f;
    if (brake > 1.0f) brake = 1.0f;
    f32 drive = throttle * 12000.0f;
    b->acceleration = vec3(forward.e[0] * drive * b->inv_mass,
                           -9.81f + spring * b->inv_mass,
                           forward.e[2] * drive * b->inv_mass);
    if (brake > 0.0f) {
        f32 keep = 1.0f - brake;
        b->velocity.e[0] *= keep;
        b->velocity.e[2] *= keep;
    }
    f32 steer = in->steer;
    if (steer > 1.0f) steer = 1.0f;
    if (steer < -1.0f) steer = -1.0f;
    b->angular_velocity.e[1] = steer * 1.2f;
    b->inertia_diag = vec3(1, 1, 1);
}

bool vehicle_enter(Vehicle *v) {
    if (!v || v->occupied) return false;
    v->occupied = true;
    return true;
}

bool vehicle_exit(Vehicle *v, PhysicsWorld *pw, Vec3 *out_feet) {
    if (!v || !pw || !out_feet || !v->occupied || v->chassis >= pw->count) return false;
    RigidBody *b = &pw->bodies[v->chassis];
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
