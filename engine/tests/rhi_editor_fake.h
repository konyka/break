#pragma once

#include <core/types.h>
#include <rhi/rhi.h>

typedef struct {
    u32 pipeline_creates, pipeline_destroys;
    u32 binding_destroys, buffer_creates;
    u32 live_shaders, live_pipelines, live_bindings, live_buffers;
} EditorRhiFakeStats;

void editor_rhi_fake_reset(void);
void editor_rhi_fake_set_enabled(bool enabled);
void editor_rhi_fake_stats(EditorRhiFakeStats *out);
u32 editor_rhi_fake_pipeline_revision(RHIPipeline pipeline);
/* REV=<n> of the vertex (fragment=false) or fragment (true) shader the
 * pipeline was linked from; 0 when the handle is not a live fake pipeline. */
u32 editor_rhi_fake_pipeline_stage_revision(RHIPipeline pipeline, bool fragment);
