#pragma once
#include <rhi/rhi.h>
#include <platform/filewatch.h>

typedef struct {
    RHIDevice  *device;
    RHIPipeline pipeline;
    char        vert_path[256];
    char        frag_path[256];
    FileWatcher watcher;
    bool        ready;
} HotReloadPipeline;

typedef struct {
    RHIDevice  *device;
    RHITexture *target;
    char        path[256];
    FileWatcher watcher;
    bool        ready;
    /* Optional: called after a successful GPU re-upload (e.g. invalidate mips). */
    void      (*on_reloaded)(void *user);
    void       *on_reloaded_user;
} HotReloadTexture;

bool  hotreload_pipeline_init(HotReloadPipeline *hr, RHIDevice *dev,
                               const char *vert_path, const char *frag_path,
                               RHIPipelineDesc *out_desc);
void  hotreload_pipeline_shutdown(HotReloadPipeline *hr);
void  hotreload_pipeline_poll(HotReloadPipeline *hr);

bool  hotreload_texture_init(HotReloadTexture *hr, RHIDevice *dev,
                              const char *path, RHITexture *target);
void  hotreload_texture_set_callback(HotReloadTexture *hr,
                                      void (*on_reloaded)(void *user), void *user);
void  hotreload_texture_poll(HotReloadTexture *hr);
void  hotreload_texture_shutdown(HotReloadTexture *hr);
