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

/* 计划 E Task 7 断言（不改构建逻辑）：本翻译单元由 engine/CMakeLists.txt 的
 * `if(WIN32 AND STREAMLINE_ROOT)` 门控编入 engine 目标；其可执行路径消费
 * VkCommandBuffer 原生句柄，只在 Vulkan 后端宏（见 sl_dlss.c 的 RHI-ESCAPE
 * 配对）编译的 engine 里可达。GL/D3D12 lane 下该库链接但保持惰性
 * （loader 编译期 fail-closed，不会装配回调）。 */

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
        out->capture_command_state = nullptr;
        out->restore_command_state = nullptr;
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
