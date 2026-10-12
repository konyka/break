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

#include <vector>

namespace {

template <typename T>
T *resolve(HMODULE module, const char *name) {
    return reinterpret_cast<T *>(GetProcAddress(module, name));
}

bool evaluate(void *context, const SLDlssResourceTagDesc *descs,
              u32 count, u32 width, u32 height) {
    HMODULE module = static_cast<HMODULE>(context);
    if (module == nullptr || descs == nullptr || count == 0u ||
        width == 0u || height == 0u)
        return false;

    auto get_token = resolve<PFun_slGetNewFrameToken>(module,
                                                           "slGetNewFrameToken");
    auto set_tags = resolve<PFun_slSetTagForFrame>(module,
                                                       "slSetTagForFrame");
    auto set_options = resolve<PFun_slDLSSSetOptions>(module,
                                                          "slDLSSSetOptions");
    auto evaluate_feature = resolve<PFun_slEvaluateFeature>(
        module, "slEvaluateFeature");
    if (get_token == nullptr || set_tags == nullptr || set_options == nullptr ||
        evaluate_feature == nullptr)
        return false;

    std::vector<sl::Resource> resources;
    std::vector<sl::ResourceTag> tags;
    resources.reserve(count);
    tags.reserve(count);
    for (u32 i = 0u; i < count; ++i) {
        const RHITextureNativeInfo *texture = descs[i].texture;
        if (!sl_dlss_resource_tag_desc_validate(&descs[i]) ||
            descs[i].lifecycle == SL_TAG_VALID_UNTIL_EVALUATE)
            return false;
        resources.emplace_back(sl::ResourceType::eTex2d, texture->image,
                               texture->memory, texture->view,
                               texture->image_layout);
        resources.back().width = texture->width;
        resources.back().height = texture->height;
        resources.back().nativeFormat = texture->native_format;
        resources.back().mipLevels = texture->mip_levels;
        resources.back().arrayLayers = texture->array_layers;
        resources.back().flags = 0u;
        resources.back().usage = 0u;
        resources.back().internalFlags = sl::Resource::eNone;
        resources.back().reserved = 0u;
        tags.emplace_back(&resources.back(),
                          static_cast<sl::BufferType>(descs[i].type),
                          static_cast<sl::ResourceLifecycle>(descs[i].lifecycle));
    }

    sl::FrameToken *token = nullptr;
    if (get_token(token, nullptr) != sl::Result::eOk || token == nullptr)
        return false;
    sl::ViewportHandle viewport(0u);
    sl::DLSSOptions options;
    options.mode = sl::DLSSMode::eBalanced;
    options.outputWidth = width;
    options.outputHeight = height;
    if (set_options(viewport, options) != sl::Result::eOk)
        return false;
    if (set_tags(*token, viewport, tags.data(), count, nullptr) != sl::Result::eOk)
        return false;
    return evaluate_feature(sl::kFeatureDLSS, *token, nullptr, 0u, nullptr) ==
           sl::Result::eOk;
}

} // namespace

extern "C" bool sl_dlss_streamline_adapter_create(void *module,
                                                    SLDlssCppAdapter *out) {
    if (module == nullptr || out == nullptr) return false;
    out->set_tags_and_evaluate = evaluate;
    out->context = module;
    return true;
}

#else

extern "C" bool sl_dlss_streamline_adapter_create(void *, SLDlssCppAdapter *) {
    return false;
}

#endif
