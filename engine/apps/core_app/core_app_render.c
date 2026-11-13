#include "core_app_render.h"

#include <inttypes.h>
#include <string.h>

static BreakRuntimeError render_trace(CoreAppRender *render, const char *line,
                                      u64 first, u64 second) {
    if (!render || !render->trace || !line) return BREAK_RUNTIME_INVALID;
    if (fprintf(render->trace, line, first, second) < 0 ||
        fflush(render->trace) != 0) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_render_start(CoreAppRender *render, FILE *trace) {
    if (!render || !trace) return BREAK_RUNTIME_INVALID;
    memset(render, 0, sizeof(*render));
    render->trace = trace;
    render->admission_open = true;
    render->producing = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_render_stage_level(const CoreAppRenderResource *resources,
                                          u32 resource_count, u64 generation,
                                          CoreAppRenderLevel *out_level) {
    if (!out_level || generation == 0u ||
        resource_count > CORE_APP_RENDER_RESOURCE_CAPACITY ||
        (resource_count > 0u && !resources)) {
        return BREAK_RUNTIME_INVALID;
    }
    CoreAppRenderLevel candidate;
    memset(&candidate, 0, sizeof(candidate));
    candidate.generation = generation;
    candidate.resource_count = resource_count;
    for (u32 i = 0u; i < resource_count; ++i) {
        if (resources[i].id == 0u || resources[i].generation != generation) {
            return BREAK_RUNTIME_INVALID;
        }
        for (u32 prior = 0u; prior < i; ++prior) {
            if (resources[prior].id == resources[i].id) return BREAK_RUNTIME_REJECTED;
        }
        candidate.resources[i] = resources[i];
    }
    *out_level = candidate;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_render_level_committed(CoreAppRender *render,
                                              const CoreAppRenderLevel *level) {
    if (!render || !level || !render->admission_open || !render->producing ||
        level->generation == 0u || level->resource_count > CORE_APP_RENDER_RESOURCE_CAPACITY) {
        return BREAK_RUNTIME_REJECTED;
    }
    for (u32 i = 0u; i < level->resource_count; ++i) {
        const CoreAppRenderResource *resource = &level->resources[i];
        if (resource->generation != level->generation) return BREAK_RUNTIME_STALE;
        BreakRuntimeError result = render_trace(
            render,
            "COREAPPTRACE version=1 event=render kind=resource generation=%" PRIu64
            " id=%" PRIu64 "\n",
            resource->generation, resource->id);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_render_record_frame(CoreAppRender *render,
                                           const CoreAppRenderFrame *frame) {
    if (!render || !frame || !render->admission_open || !render->producing ||
        render->idle || frame->generation == 0u ||
        frame->resource_count > CORE_APP_RENDER_RESOURCE_CAPACITY ||
        frame->frame <= render->last_frame) {
        return BREAK_RUNTIME_REJECTED;
    }
    BreakRuntimeError result = render_trace(
        render, "COREAPPTRACE version=1 event=frame frame=%" PRIu64
        " generation=%" PRIu64 "\n", frame->frame, frame->generation);
    if (result != BREAK_RUNTIME_OK) return result;
    result = render_trace(
        render, "COREAPPTRACE version=1 event=render kind=frame frame=%" PRIu64
        " generation=%" PRIu64 "\n", frame->frame, frame->generation);
    if (result != BREAK_RUNTIME_OK) return result;
    render->last_frame = frame->frame;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_render_record_world(CoreAppRender *render, u64 generation,
                                             const WorldFrameSnapshot *snapshot) {
    if (!render || !snapshot || !render->trace || !render->admission_open ||
        !render->producing || render->idle || generation == 0u ||
        snapshot->frame_id != render->last_frame ||
        snapshot->draw_count > WORLD_PRESENT_MAX_OBJECTS) {
        return BREAK_RUNTIME_REJECTED;
    }
    u32 stream = 0u;
    for (u32 i = 0u; i < snapshot->draw_count; ++i) {
        if (snapshot->draws[i].gpu.vertex.generation != (u32)generation) {
            return BREAK_RUNTIME_STALE;
        }
        if (snapshot->draws[i].stream) stream++;
    }
    if (fprintf(render->trace,
                "COREAPPTRACE version=1 event=render kind=world frame=%" PRIu64
                " generation=%" PRIu64 " draws=%u stream=%u batches=%u instances=%u objects=",
                snapshot->frame_id, generation, snapshot->draw_count, stream,
                snapshot->batch_count, snapshot->instance_count) < 0) {
        return BREAK_RUNTIME_FAILED;
    }
    for (u32 i = 0u; i < snapshot->draw_count; ++i) {
        if (fprintf(render->trace, i == 0u ? "%u" : ",%u",
                    snapshot->draws[i].object_id) < 0) {
            return BREAK_RUNTIME_FAILED;
        }
    }
    if (fprintf(render->trace, " sun_y=%.9g\n",
                (double)snapshot->lighting.sun_dir.e[1]) < 0 ||
        fflush(render->trace) != 0) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_render_stop_admission(CoreAppRender *render) {
    if (!render) return BREAK_RUNTIME_INVALID;
    render->admission_open = false;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_render_stop_producers(CoreAppRender *render) {
    if (!render) return BREAK_RUNTIME_INVALID;
    render->producing = false;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_render_idle(CoreAppRender *render) {
    if (!render) return BREAK_RUNTIME_INVALID;
    if (render->producing) return BREAK_RUNTIME_REJECTED;
    render->idle = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_render_destroy(CoreAppRender *render) {
    if (!render) return BREAK_RUNTIME_INVALID;
    if (!render->idle) return BREAK_RUNTIME_REJECTED;
    render->trace = NULL;
    return BREAK_RUNTIME_OK;
}
