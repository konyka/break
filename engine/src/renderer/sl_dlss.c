#include <renderer/sl_dlss.h>
#include <rhi/rhi_native_vulkan.h>
#include <core/types.h>

#ifdef ENGINE_STREAMLINE_CPP_ADAPTER
#include <renderer/sl_dlss_streamline_adapter.h>
#endif

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>

/* Streamline 关闭入口类型与全局 loader 状态：下方 VK 逃生舱与后端无关的
 * shutdown/api_status 路径共用；非 VK 编译单元里恒为 NULL/false。 */
typedef int (WINAPI *PFN_sl_shutdown)(void);

static HMODULE g_sl_module;
static PFN_sl_shutdown g_sl_shutdown_fn;
static bool g_initialized;
static bool g_api_ready;
static SLDlssCppAdapter g_cpp_adapter;
static bool g_cpp_adapter_set;

static void sl_dlss_clear_cpp_adapter(void) {
    memset(&g_cpp_adapter, 0, sizeof(g_cpp_adapter));
    g_cpp_adapter_set = false;
}

/* RHI-ESCAPE: Streamline interposer 只接受 Vulkan 原生句柄（slSetVulkanInfo）；ABI 镜像、loader 与 abort 路径仅 VK 后端编译，其他后端裁剪。 */
#if defined(ENGINE_RHI_BACKEND_VULKAN)
/* ---- ABI mirrors of the official Streamline 2.14.1 C++ headers ----
 *
 * The public sl.h headers are C++; this engine is C11, so the structures
 * passed across the sl.interposer.dll boundary are mirrored here exactly.
 * The layout contract is sl_struct.h's BaseStructure:
 *   { BaseStructure *next; StructType guid(16B); size_t version; }
 * followed by the declared members in declaration order with natural
 * alignment. static_asserts below pin the sizes this code was verified
 * against (x64, sl 2.14.1). */

typedef struct {
    u32 data1;
    u16 data2;
    u16 data3;
    u8  data4[8];
} SLStructType;

typedef struct {
    void        *next;
    SLStructType struct_type;
    usize        struct_version;
} SLBaseStructure;

/* sl::Feature: kFeatureDLSS = 0 */
static const u32 SL_FEATURE_DLSS = 0u;

/* sl::LogLevel { eOff, eDefault, eVerbose } */
static const u32 SL_LOG_LEVEL_DEFAULT = 1u;

/* sl::EngineType { eCustom=0 } / sl::RenderAPI { eD3D11, eD3D12, eVulkan } */
static const u32 SL_ENGINE_CUSTOM = 0u;
static const u32 SL_RENDER_API_VULKAN = 2u;

/* sl::PreferenceFlags::eDisableCLStateTracking | eAllowOTA */
static const u64 SL_PREF_FLAGS_DEFAULT = (1u << 0) | (1u << 3);
/* PreferenceFlags::eUseManualHooking. */
static const u64 SL_PREF_FLAG_MANUAL_HOOKING = (1u << 2);

/* kSDKVersion = (2<<48)|(14<<32)|(1<<16)|0xfedc */
#define SL_SDK_VERSION_2_14_1 (((u64)2 << 48) | ((u64)14 << 32) | ((u64)1 << 16) | (u64)0xfedc)

/* {1CA10965-BF8E-432B-8DA1-6716D879FB14}, kStructVersion1 */
typedef struct {
    SLBaseStructure base;
    u8   show_console;               /* +32 */
    u8   _pad0[3];
    u32  log_level;                  /* +36 */
    const wchar_t **paths_to_plugins; /* +40 */
    u32  num_paths_to_plugins;       /* +48 */
    u8   _pad1[4];
    const wchar_t *path_to_logs_and_data; /* +56 */
    void *allocate_callback;         /* +64 */
    void *release_callback;          /* +72 */
    void *log_message_callback;      /* +80 */
    u64  flags;                      /* +88 */
    const u32 *features_to_load;     /* +96 */
    u32  num_features_to_load;       /* +104 */
    u8   _pad2[4];
    u32  application_id;             /* +112 */
    u8   _pad3[4];
    u32  engine;                     /* +120 */
    u8   _pad4[4];
    const char *engine_version;      /* +128 */
    const char *project_id;          /* +136 */
    u32  render_api;                 /* +144 */
    u8   _pad5[4];
} SLPreferences;

/* {0677315F-A746-4492-9F42-CB6142C9C3D4}, kStructVersion1 */
typedef struct {
    SLBaseStructure base;
    u8   *device_luid;               /* +32 */
    u32   device_luid_size;          /* +40 */
    u8    _pad[4];
    void *vk_physical_device;        /* +48 */
} SLAdapterInfo;

/* Streamline 2.14.1 sl::VulkanInfo, kStructVersion3. */
typedef struct {
    SLBaseStructure base;
    void *device;
    void *instance;
    void *physical_device;
    u32 compute_queue_index;
    u32 compute_queue_family;
    u32 graphics_queue_index;
    u32 graphics_queue_family;
    u32 optical_flow_queue_index;
    u32 optical_flow_queue_family;
    u8 use_native_optical_flow_mode;
    u8 _pad0[3];
    u32 compute_queue_create_flags;
    u32 graphics_queue_create_flags;
    u32 optical_flow_queue_create_flags;
} SLVulkanInfo;

_Static_assert(sizeof(SLVulkanInfo) == 96, "sl VulkanInfo layout 2.14.1");

_Static_assert(sizeof(SLBaseStructure) == 32, "sl base layout");
_Static_assert(sizeof(SLPreferences) == 152, "sl preferences layout 2.14.1");
_Static_assert(sizeof(SLAdapterInfo) == 56, "sl adapter info layout 2.14.1");

/* sl::Result codes this module classifies. */
#define SL_RESULT_OK 0
#define SL_RESULT_DRIVER_OUT_OF_DATE 2
#define SL_RESULT_OS_OUT_OF_DATE 3
#define SL_RESULT_NO_SUPPORTED_ADAPTER 6
#define SL_RESULT_ADAPTER_NOT_SUPPORTED 7
#define SL_RESULT_NGX_FAILED 16

typedef int (WINAPI *PFN_sl_init)(const SLPreferences *, u64);
typedef int (WINAPI *PFN_sl_is_feature_supported)(u32, const SLAdapterInfo *);
typedef int (WINAPI *PFN_sl_set_vulkan_info)(const SLVulkanInfo *);

static void sl_dlss_abort_init(void) {
    sl_dlss_clear_cpp_adapter();
    if (g_initialized && g_sl_shutdown_fn != NULL) g_sl_shutdown_fn();
    g_initialized = false;
    g_api_ready = false;
    g_sl_shutdown_fn = NULL;
    if (g_sl_module != NULL) {
        FreeLibrary(g_sl_module);
        g_sl_module = NULL;
    }
}

static const SLStructType kPrefGuid = {
    0x1ca10965u, 0xbf8eu, 0x432bu,
    { 0x8d, 0xa1, 0x67, 0x16, 0xd8, 0x79, 0xfb, 0x14 }
};
static const SLStructType kAdapterGuid = {
    0x0677315fu, 0xa746u, 0x4492u,
    { 0x9f, 0x42, 0xcb, 0x61, 0x42, 0xc9, 0xc3, 0xd4 }
};
static const SLStructType kVulkanInfoGuid = {
    0x0eed6fd5u, 0x82cdu, 0x43a9u,
    { 0xbd, 0xb5, 0x47, 0xa5, 0xba, 0x2f, 0x45, 0xd6 }
};

static HMODULE sl_load_interposer(void) {
    static const wchar_t *candidates[] = {
        L"../third_party/streamline-bin/v2.14.1/bin/x64/sl.interposer.dll",
        L"third_party/streamline-bin/v2.14.1/bin/x64/sl.interposer.dll",
        L"sl.interposer.dll",
    };
    wchar_t env_path[512];
    usize i;

    /* Explicit override wins and is exclusive: a bad BREAK_SL_DIR path must
       fail closed instead of silently falling back to the bundled candidates. */
    if (GetEnvironmentVariableW(L"BREAK_SL_DIR", env_path,
                                (DWORD)(sizeof(env_path) / sizeof(wchar_t))) > 0 &&
        env_path[0] != L'\0') {
        wchar_t full[1024];
        int written = _snwprintf_s(full, (rsize_t)(sizeof(full) / sizeof(wchar_t)),
                                   _TRUNCATE, L"%s\\sl.interposer.dll", env_path);
        if (written > 0) {
            HMODULE m = LoadLibraryExW(full, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
            if (m != NULL) return m;
        }
        return NULL;
    }
    for (i = 0; i < sizeof(candidates) / sizeof(candidates[0]); i++) {
        HMODULE m = LoadLibraryExW(candidates[i], NULL,
                                   LOAD_WITH_ALTERED_SEARCH_PATH);
        if (m != NULL) return m;
    }
    return NULL;
}
#endif

const char *sl_dlss_probe_result_text(SLDlssProbeResult result) {
    switch (result) {
    case SL_DLSS_SUPPORTED: return "supported";
    case SL_DLSS_MISSING_RUNTIME: return "sl.interposer.dll not found";
    case SL_DLSS_INIT_FAILED: return "slInit failed";
    case SL_DLSS_FEATURE_UNSUPPORTED:
        return "dlss unsupported on this adapter/driver/os";
    case SL_DLSS_INTERNAL_ERROR: return "internal loader error";
    case SL_DLSS_UNAVAILABLE:
    default: return "unavailable";
    }
}

SLDlssApiStatus sl_dlss_api_status(void) {
    return g_api_ready ? SL_DLSS_API_READY : SL_DLSS_API_UNAVAILABLE;
}

bool sl_dlss_resource_tag_desc_validate(const SLDlssResourceTagDesc *desc) {
    if (desc == NULL || desc->texture == NULL ||
        desc->texture->type != RHI_NATIVE_HANDLE_VULKAN ||
        desc->texture->image == NULL || desc->texture->memory == NULL ||
        desc->texture->view == NULL ||
        desc->texture->width == 0u || desc->texture->height == 0u ||
        desc->texture->native_format == 0u ||
        desc->texture->mip_levels == 0u ||
        desc->texture->array_layers == 0u ||
        desc->texture->image_layout == 0xffffffffu)
        return false;
    return desc->type == SL_TAG_DEPTH ||
           desc->type == SL_TAG_MOTION_VECTORS ||
           desc->type == SL_TAG_SCALING_INPUT_COLOR ||
           desc->type == SL_TAG_SCALING_OUTPUT_COLOR;
}

bool sl_dlss_set_cpp_adapter(const SLDlssCppAdapter *adapter) {
    if (adapter == NULL || adapter->capture_command_state == NULL ||
        adapter->set_tags_and_evaluate == NULL ||
        adapter->restore_command_state == NULL) {
        memset(&g_cpp_adapter, 0, sizeof(g_cpp_adapter));
        g_cpp_adapter_set = false;
        return false;
    }
    g_cpp_adapter = *adapter;
    g_cpp_adapter_set = true;
    return true;
}

bool sl_dlss_evaluate_tags(const SLDlssResourceTagDesc *tags,
                           u32 tag_count, u32 output_width,
                           u32 output_height) {
    (void)tags;
    (void)tag_count;
    (void)output_width;
    (void)output_height;
    /* Streamline manual hooking cannot safely evaluate without the recording
     * command buffer. Callers must use the explicit RHI-aware entry point. */
    return false;
}

bool sl_dlss_evaluate_tags_with_command_buffer(
    const RHIDevice *dev, const RHICmdBuffer *cmd,
    const SLDlssResourceTagDesc *tags, u32 tag_count,
    u32 output_width, u32 output_height) {
    /* RHI-ESCAPE: Streamline 回调消费 native（Vk）command buffer（rhi_cmd_buffer_get_native_info），仅 VK 后端可达；其他后端 fail-closed。 */
#if defined(ENGINE_RHI_BACKEND_VULKAN)
    RHICmdBufferNativeInfo command_info;
    void *native_command_buffer = NULL;
    if (!g_cpp_adapter_set || tags == NULL || tag_count == 0u ||
        output_width == 0u || output_height == 0u) return false;
    if (dev == NULL || cmd == NULL ||
        !rhi_cmd_buffer_get_native_info(dev, cmd, &command_info) ||
        !command_info.recording || command_info.command_buffer == NULL)
        return false;
    native_command_buffer = command_info.command_buffer;
    for (u32 i = 0u; i < tag_count; ++i) {
        if (!sl_dlss_resource_tag_desc_validate(&tags[i])) return false;
    }
    if (!g_cpp_adapter.capture_command_state(
            g_cpp_adapter.context, native_command_buffer))
        return false;
    bool evaluated = g_cpp_adapter.set_tags_and_evaluate(
        g_cpp_adapter.context, tags, tag_count, output_width, output_height,
        native_command_buffer);
    bool restored = g_cpp_adapter.restore_command_state(
        g_cpp_adapter.context, native_command_buffer);
    return evaluated && restored;
#else
    (void)dev;
    (void)cmd;
    (void)tags;
    (void)tag_count;
    (void)output_width;
    (void)output_height;
    return false;
#endif
}

bool sl_dlss_probe(const RHINativeDevice *native, SLDlssProbeResult *out_result) {
    /* RHI-ESCAPE: probe 走 sl.interposer 的 Vulkan 句柄路径（slSetVulkanInfo），仅 VK 后端编译；其他后端 fail-closed（g_cpp_adapter 不经 loader 初始化）。 */
#if defined(ENGINE_RHI_BACKEND_VULKAN)
    PFN_sl_init init_fn;
    PFN_sl_is_feature_supported supported_fn;
    PFN_sl_set_vulkan_info set_vk_fn;
    SLPreferences prefs;
    SLAdapterInfo adapter;
    u32 feature = SL_FEATURE_DLSS;
    int rc;

    if (out_result != NULL) *out_result = SL_DLSS_UNAVAILABLE;
    if (g_initialized) {
        if (out_result != NULL) *out_result = SL_DLSS_SUPPORTED;
        return true;
    }
    if (g_sl_module == NULL) g_sl_module = sl_load_interposer();
    if (g_sl_module == NULL) {
        if (out_result != NULL) *out_result = SL_DLSS_MISSING_RUNTIME;
        return false;
    }
    init_fn = (PFN_sl_init)(void *)GetProcAddress(g_sl_module, "slInit");
    g_sl_shutdown_fn = (PFN_sl_shutdown)(void *)GetProcAddress(g_sl_module, "slShutdown");
    supported_fn = (PFN_sl_is_feature_supported)(void *)GetProcAddress(
        g_sl_module, "slIsFeatureSupported");
    set_vk_fn = (PFN_sl_set_vulkan_info)(void *)GetProcAddress(
        g_sl_module, "slSetVulkanInfo");
    if (init_fn == NULL || g_sl_shutdown_fn == NULL ||
        supported_fn == NULL || set_vk_fn == NULL) {
        if (out_result != NULL) *out_result = SL_DLSS_MISSING_RUNTIME;
        return false;
    }

    memset(&prefs, 0, sizeof(prefs));
    prefs.base.next = NULL;
    prefs.base.struct_type = kPrefGuid;
    prefs.base.struct_version = 1u;
    prefs.show_console = false;
    prefs.log_level = SL_LOG_LEVEL_DEFAULT;
    prefs.path_to_logs_and_data = NULL;
    /* Manual hooking is mandatory here: this engine owns vkCreateInstance /
     * vkCreateDevice and passes the native handles explicitly below. */
    prefs.flags = SL_PREF_FLAGS_DEFAULT | SL_PREF_FLAG_MANUAL_HOOKING;
    prefs.features_to_load = &feature;
    prefs.num_features_to_load = 1u;
    prefs.engine = SL_ENGINE_CUSTOM;
    prefs.engine_version = "break";
    prefs.render_api = SL_RENDER_API_VULKAN;

    rc = init_fn(&prefs, SL_SDK_VERSION_2_14_1);
    if (rc != SL_RESULT_OK) {
        g_sl_shutdown_fn = NULL;
        if (out_result != NULL) *out_result = SL_DLSS_INIT_FAILED;
        return false;
    }
    g_initialized = true;

    if (native == NULL || native->type != RHI_NATIVE_HANDLE_VULKAN) {
        sl_dlss_abort_init();
        if (out_result != NULL) *out_result = SL_DLSS_INIT_FAILED;
        return false;
    }
    {
        SLVulkanInfo vk_info;
        int set_result;
        memset(&vk_info, 0, sizeof(vk_info));
        vk_info.base.struct_type = kVulkanInfoGuid;
        vk_info.base.struct_version = 3u;
        vk_info.device = native->device;
        vk_info.instance = native->instance;
        vk_info.physical_device = native->physical_device;
        vk_info.graphics_queue_family = native->graphics_queue_family;
        vk_info.graphics_queue_index = 0u;
        set_result = set_vk_fn(&vk_info);
        if (set_result != SL_RESULT_OK) {
            sl_dlss_abort_init();
            if (out_result != NULL) *out_result = SL_DLSS_INIT_FAILED;
            return false;
        }
    }

    memset(&adapter, 0, sizeof(adapter));
    adapter.base.next = NULL;
    adapter.base.struct_type = kAdapterGuid;
    adapter.base.struct_version = 1u;
    if (native != NULL && native->type == RHI_NATIVE_HANDLE_VULKAN)
        adapter.vk_physical_device = native->physical_device;

    rc = supported_fn(SL_FEATURE_DLSS, &adapter);
    if (rc == SL_RESULT_OK) {
#ifdef ENGINE_STREAMLINE_CPP_ADAPTER
        {
            SLDlssCppAdapter cpp_adapter;
            memset(&cpp_adapter, 0, sizeof(cpp_adapter));
            if (sl_dlss_streamline_adapter_create((void *)g_sl_module,
                                                   &cpp_adapter))
                sl_dlss_set_cpp_adapter(&cpp_adapter);
        }
#endif
        g_api_ready = true;
        if (out_result != NULL) *out_result = SL_DLSS_SUPPORTED;
        return true;
    }
    if (rc == SL_RESULT_DRIVER_OUT_OF_DATE || rc == SL_RESULT_OS_OUT_OF_DATE ||
        rc == SL_RESULT_NO_SUPPORTED_ADAPTER || rc == SL_RESULT_ADAPTER_NOT_SUPPORTED) {
        sl_dlss_abort_init();
        if (out_result != NULL) *out_result = SL_DLSS_FEATURE_UNSUPPORTED;
        return false;
    }
    sl_dlss_abort_init();
    if (out_result != NULL) *out_result = SL_DLSS_INTERNAL_ERROR;
    return false;
#else
    (void)native;
    if (out_result != NULL) *out_result = SL_DLSS_UNAVAILABLE;
    return false;
#endif
}

void sl_dlss_shutdown(void) {
    sl_dlss_clear_cpp_adapter();
    if (g_initialized && g_sl_shutdown_fn != NULL) g_sl_shutdown_fn();
    g_initialized = false;
    g_api_ready = false;
    g_sl_shutdown_fn = NULL;
    if (g_sl_module != NULL) {
        FreeLibrary(g_sl_module);
        g_sl_module = NULL;
    }
}

#else /* !_WIN32 */

const char *sl_dlss_probe_result_text(SLDlssProbeResult result) {
    (void)result;
    return "unavailable (non-windows build)";
}

bool sl_dlss_probe(const RHINativeDevice *native, SLDlssProbeResult *out_result) {
    (void)native;
    if (out_result != NULL) *out_result = SL_DLSS_UNAVAILABLE;
    return false;
}

void sl_dlss_shutdown(void) {
}

SLDlssApiStatus sl_dlss_api_status(void) {
    return SL_DLSS_API_UNAVAILABLE;
}

bool sl_dlss_set_cpp_adapter(const SLDlssCppAdapter *adapter) {
    (void)adapter;
    return false;
}

bool sl_dlss_evaluate_tags(const SLDlssResourceTagDesc *tags,
                           u32 tag_count, u32 output_width,
                           u32 output_height) {
    (void)tags;
    (void)tag_count;
    (void)output_width;
    (void)output_height;
    return false;
}

bool sl_dlss_evaluate_tags_with_command_buffer(
    const RHIDevice *dev, const RHICmdBuffer *cmd,
    const SLDlssResourceTagDesc *tags, u32 tag_count,
    u32 output_width, u32 output_height) {
    (void)dev; (void)cmd; (void)tags; (void)tag_count;
    (void)output_width; (void)output_height;
    return false;
}

#endif
