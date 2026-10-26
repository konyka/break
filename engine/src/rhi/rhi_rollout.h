#ifndef RHI_ROLLOUT_H
#define RHI_ROLLOUT_H
#include <rhi/rhi.h>
#include <stddef.h>

/* Baked from engine/assets/rhi_backend_rollout.json at configure time;
 * 0 = build without the rollout config (e.g. tests compiling core sources
 * directly). */
#ifndef ENGINE_RHI_ROLLOUT_CONFIG_VERSION
#define ENGINE_RHI_ROLLOUT_CONFIG_VERSION 0
#endif

typedef struct RHIRolloutEvent {
    const char *event;   /* backend_selected|fallback|device_lost|present_failure|shader_failure */
    const char *backend; /* vulkan|metal|d3d12|opengl */
    const char *reason;  /* platform-default|explicit-env|compat-override|config-fallback|none */
    int config_version;  /* ENGINE_RHI_ROLLOUT_CONFIG_VERSION; 0 = 无配置 */
    const char *result;  /* RHIResult 名或 "OK" */
} RHIRolloutEvent;

int rhi_rollout_format(char *buf, size_t cap, const RHIRolloutEvent *ev);
void rhi_rollout_emit(const RHIRolloutEvent *ev);
const char *rhi_result_name(RHIResult result);

/* Name of the backend this build linked ("vulkan"|"metal"|"d3d12"|"opengl")
 * and the rollout reason it was selected with. Lives here (not in callers)
 * so renderer/main code stays backend-token-free. */
const char *rhi_rollout_compiled_backend(void);
const char *rhi_rollout_compiled_reason(void);

/* Multi-backend builds (docs/design/rhi_runtime_backend.md): the runtime
 * selection module records the backend it actually created, so every later
 * RHIEVT line (device_lost, present_failure, ...) names that backend instead
 * of the build's primary. NULL backend clears the record. Single-backend
 * builds never call it and keep the compile-time answer. */
void rhi_rollout_set_runtime_selection(const char *backend, const char *reason);

#endif
