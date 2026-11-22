#pragma once

#include "core_app.h"

#ifdef __cplusplus
extern "C" {
#endif

bool core_app_diagnostics_start(const char *spool_root);
void core_app_diagnostics_stop(void);
void core_app_diagnostics_publish(
    void *user, const CoreAppDiagnosticsSnapshot *snapshot);

#ifdef __cplusplus
}
#endif
