#pragma once

#include <ecs/ecs.h>

/* Internal ECS transaction primitive.
 *
 * world_clone_deep requires exclusive ownership of source for the duration of
 * the call: callers must not concurrently mutate or query it. The returned
 * world owns every allocation and may be mutated independently.
 *
 * world_replace_contents requires the caller to exclusively own both
 * destination and replacement. It consumes replacement on success; do not
 * destroy or otherwise use replacement afterwards. Existing external Query,
 * QueryIter, and component pointers into destination are invalidated by the
 * replacement. */
World *world_clone_deep(const World *source);
bool   world_replace_contents(World *destination, World *replacement);

#ifdef ECS_TESTING
/* Fail the Nth clone allocation (zero-based); -1 disables injection. */
void world_clone_test_fail_after(i32 allocation_index);
#endif
