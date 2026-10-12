#include "sl_dlss_streamline_adapter.h"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <sl.h>
#include <sl_core_api.h>
#include <sl_core_types.h>
#include <sl_dlss.h>

namespace {

bool evaluate(void *context, const SLDlssResourceTagDesc *descs,
              u32 count, u32 width, u32 height,
              void *native_command_buffer) {
    (void)context;
    (void)descs;
    (void)count;
    (void)width;
    (void)height;
    (void)native_command_buffer;
    /* The adapter becomes executable only after the RHI exposes the recording
     * VkCommandBuffer and a state-restore hook. */
    return false;
}

} // namespace

extern "C" bool sl_dlss_streamline_adapter_create(void *module,
                                                    SLDlssCppAdapter *out) {
    (void)module;
    if (out != nullptr) {
        out->set_tags_and_evaluate = nullptr;
        out->context = nullptr;
    }
    /* Do not register an inert callback. The native command-buffer contract is
     * not available yet, so the C loader must report no executable adapter. */
    return false;
}

#else

extern "C" bool sl_dlss_streamline_adapter_create(void *, SLDlssCppAdapter *) {
    return false;
}

#endif
