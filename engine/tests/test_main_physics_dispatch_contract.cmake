# Source contract: the engine main loop hands its TaskSystem to the physics
# world, so contact solving and integration can run on the workers once a
# scene is large enough (the parallel paths are bit-identical to the serial
# step, see test_physics_parallel), and detaches it before the TaskSystem is
# destroyed.
#   1. main.c includes physics/physics_task.h,
#   2. physics_world_set_parallel_for(physics, physics_task_parallel_for,
#      tasks, ...) comes after task_system_create and before the first
#      physics_step,
#   3. physics_world_set_parallel_for(physics, NULL, NULL, 0u) comes before
#      task_system_destroy(tasks).
if(NOT DEFINED ENGINE_SOURCE_DIR)
    message(FATAL_ERROR "ENGINE_SOURCE_DIR is required")
endif()

file(READ "${ENGINE_SOURCE_DIR}/src/main.c" text)
set(errors "")

string(FIND "${text}" "#include <physics/physics_task.h>" include_at)
if(include_at EQUAL -1)
    string(APPEND errors "main.c: missing #include <physics/physics_task.h>\n")
endif()

string(FIND "${text}" "task_system_create(" create_at)
string(FIND "${text}" "physics_world_set_parallel_for(physics, physics_task_parallel_for, tasks," attach_at)
string(FIND "${text}" "physics_step(physics," step_at)
string(FIND "${text}" "physics_world_set_parallel_for(physics, NULL, NULL, 0u);" detach_at)
string(FIND "${text}" "task_system_destroy(tasks);" destroy_at)

if(attach_at EQUAL -1)
    string(APPEND errors "main.c: the physics world is never given the TaskSystem dispatcher\n")
else()
    if(create_at EQUAL -1 OR attach_at LESS create_at)
        string(APPEND errors "main.c: the dispatcher is attached before the TaskSystem exists\n")
    endif()
    if(step_at EQUAL -1 OR step_at LESS attach_at)
        string(APPEND errors "main.c: physics_step runs before the dispatcher is attached\n")
    endif()
endif()
if(detach_at EQUAL -1)
    string(APPEND errors "main.c: the dispatcher is never detached\n")
elseif(destroy_at EQUAL -1 OR destroy_at LESS detach_at)
    string(APPEND errors "main.c: the TaskSystem is destroyed before the dispatcher is detached\n")
endif()

if(NOT errors STREQUAL "")
    message(FATAL_ERROR "main physics dispatch contract failed:\n${errors}")
endif()
message(STATUS "main physics dispatch contract passed")
