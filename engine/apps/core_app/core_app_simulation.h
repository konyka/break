#pragma once

#include "core_app_input.h"

#include <ecs/ecs.h>
#include <game/break_game.h>
#include <physics/character.h>
#include <physics/physics.h>
#include <runtime/runtime_types.h>

#define CORE_APP_FIXED_DT (1.0f / 60.0f)
#define CORE_APP_FIXED_DT_NS 16666667ull
#define CORE_APP_MAX_SUBSTEPS 8u
#define CORE_APP_TOUCH_STICK_RADIUS 0.1f

typedef enum CoreAppAction {
    CORE_APP_ACTION_FORWARD = 0,
    CORE_APP_ACTION_BACK,
    CORE_APP_ACTION_LEFT,
    CORE_APP_ACTION_RIGHT,
    CORE_APP_ACTION_JUMP,
    CORE_APP_ACTION_INTERACT,
    CORE_APP_ACTION_FIRE,
    CORE_APP_ACTION_SAVE,
    CORE_APP_ACTION_LOAD,
    CORE_APP_ACTION_COUNT
} CoreAppAction;

typedef struct CoreAppSimulationDesc {
    World *world;
    BreakGame *actor_runtime;
    PhysicsWorld *physics;
    Entity user;
    Vec3 spawn;
} CoreAppSimulationDesc;

typedef struct CoreAppMoveIntent {
    f32 forward;
    f32 strafe;
    bool jump;
    bool interact;
} CoreAppMoveIntent;

typedef struct CoreAppAccumulator {
    u64 remainder_ns;
    u64 dropped_ns;
} CoreAppAccumulator;

typedef struct CoreAppSimulation CoreAppSimulation;

CoreAppSimulation *core_app_simulation_create(const CoreAppSimulationDesc *desc);
void core_app_simulation_destroy(CoreAppSimulation *simulation);
BreakRuntimeError core_app_simulation_intent(CoreAppSimulation *simulation,
                                             const CoreAppInputFrame *frame,
                                             CoreAppMoveIntent *out);
BreakRuntimeError core_app_simulation_tick(CoreAppSimulation *simulation,
                                           const CoreAppInputFrame *frame);
BreakRuntimeError core_app_simulation_user_position(
    const CoreAppSimulation *simulation, Vec3 *out);
BreakRuntimeError core_app_simulation_place_user(CoreAppSimulation *simulation,
                                                Vec3 position);
u64 core_app_simulation_tick_count(const CoreAppSimulation *simulation);

u32 core_app_accumulator_advance(CoreAppAccumulator *accumulator, u64 elapsed_ns);
