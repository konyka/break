#pragma once

#include <core/types.h>
#include <rhi/rhi.h>

typedef struct {
    u32 pipeline_creates, pipeline_destroys;
    u32 binding_destroys, buffer_creates;
    u32 live_shaders, live_pipelines, live_bindings, live_buffers;
    /* textures (image preview): every create/destroy, the live count and
     * the size of the last successful create */
    u32 texture_creates, texture_destroys, live_textures;
    u32 last_texture_w, last_texture_h;
    /* mip chain: levels of the last create, rhi_texture_upload_mip calls
     * accepted for a live texture (level < levels, exact level extent),
     * and those rejected */
    u32 last_texture_mips, mip_uploads, mip_upload_rejects;
} EditorRhiFakeStats;

void editor_rhi_fake_reset(void);
void editor_rhi_fake_set_enabled(bool enabled);
void editor_rhi_fake_stats(EditorRhiFakeStats *out);
u32 editor_rhi_fake_pipeline_revision(RHIPipeline pipeline);
/* true while `texture` is a live fake texture */
bool editor_rhi_fake_texture_live(RHITexture texture);
/* the next n rhi_texture_create calls fail (return the null handle) */
void editor_rhi_fake_fail_texture_creates(u32 n);
/* REV=<n> of the vertex (fragment=false) or fragment (true) shader the
 * pipeline was linked from; 0 when the handle is not a live fake pipeline. */
u32 editor_rhi_fake_pipeline_stage_revision(RHIPipeline pipeline, bool fragment);
