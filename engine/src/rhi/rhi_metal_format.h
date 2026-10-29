#pragma once
#include <rhi/rhi.h>

/* Metal pixel-format ordinals. Deliberately NOT MTLPixelFormat constants so
 * this header stays C11 and platform-free; rhi_metal.m static-asserts each
 * ordinal against the real MTLPixelFormat value at compile time. */
typedef enum {
    RHI_METAL_FORMAT_INVALID = 0,
    RHI_METAL_FORMAT_RGBA8_UNORM,       /* MTLPixelFormatRGBA8Unorm */
    RHI_METAL_FORMAT_BGRA8_UNORM,       /* MTLPixelFormatBGRA8Unorm */
    RHI_METAL_FORMAT_RGBA16_FLOAT,      /* MTLPixelFormatRGBA16Float */
    RHI_METAL_FORMAT_RG16_FLOAT,        /* MTLPixelFormatRG16Float */
    RHI_METAL_FORMAT_R32_FLOAT,         /* MTLPixelFormatR32Float */
    RHI_METAL_FORMAT_DEPTH32_FLOAT,     /* MTLPixelFormatDepth32Float */
    RHI_METAL_FORMAT_RGBA8_UNORM_SRGB,  /* MTLPixelFormatRGBA8Unorm_sRGB */
} RHIMetalFormat;

static inline RHIMetalFormat rhi_metal_format_from_rhi(RHIFormat f) {
    switch (f) {
        case RHI_FORMAT_R8G8B8A8_UNORM:      return RHI_METAL_FORMAT_RGBA8_UNORM;
        case RHI_FORMAT_R8G8B8A8_SRGB:       return RHI_METAL_FORMAT_RGBA8_UNORM_SRGB;
        case RHI_FORMAT_B8G8R8A8_UNORM:      return RHI_METAL_FORMAT_BGRA8_UNORM;
        case RHI_FORMAT_R16G16B16A16_SFLOAT: return RHI_METAL_FORMAT_RGBA16_FLOAT;
        case RHI_FORMAT_R16G16_SFLOAT:       return RHI_METAL_FORMAT_RG16_FLOAT;
        case RHI_FORMAT_R32_FLOAT:           return RHI_METAL_FORMAT_R32_FLOAT;
        case RHI_FORMAT_D32_FLOAT:           return RHI_METAL_FORMAT_DEPTH32_FLOAT;
        default:                           return RHI_METAL_FORMAT_INVALID;
    }
}
/* bytes-per-pixel for readback/upload; depth formats report f32 bytes (R602
 * contract: D32 readback is 4B f32 per texel). 0 for INVALID. */
static inline u32 rhi_metal_format_bytes_per_pixel(RHIMetalFormat f) {
    switch (f) {
        case RHI_METAL_FORMAT_RGBA8_UNORM:   return 4u;
        case RHI_METAL_FORMAT_RGBA8_UNORM_SRGB: return 4u;
        case RHI_METAL_FORMAT_BGRA8_UNORM:   return 4u;
        case RHI_METAL_FORMAT_RGBA16_FLOAT:  return 8u;
        case RHI_METAL_FORMAT_RG16_FLOAT:    return 4u;
        case RHI_METAL_FORMAT_R32_FLOAT:     return 4u;
        case RHI_METAL_FORMAT_DEPTH32_FLOAT: return 4u;
        default:                             return 0u;
    }
}
/* Two-slot frame pacing helpers (aligned with rhi_frame_index semantics,
 * rhi.h:470-471): the slot to acquire into and the event value to wait on. */
static inline u32 rhi_metal_frame_slot(u64 frame_counter) {
    return (u32)(frame_counter % 2u);
}
static inline u64 rhi_metal_slot_wait_value(u64 frame_counter) {
    return frame_counter >= 2u ? frame_counter - 2u : 0u;
}

/* ---- Task 10: offline shader manifest ----
 * The Metal backend's rhi_shader_create receives the renderer's GLSL source
 * text; the build-time pipeline (tools/compile_metal_shaders.sh +
 * tools/gen_metal_shader_manifest.c) converts every engine/shaders *_vk
 * (and shared *.comp) file to MSL/metallib and emits a manifest keyed by
 * the FNV-1a 64 hash of the ORIGINAL GLSL bytes. This inline is the single
 * definition shared by the generator and the runtime so the hash contract
 * cannot drift. */
static inline u64 rhi_metal_fnv1a64(const void *data, usize len) {
    const u8 *p = (const u8 *)data;
    u64 h = 0xcbf29ce484222325ull;   /* FNV-1a 64 offset basis */
    while (len-- > 0u) {
        h ^= (u64)*p++;
        h *= 0x100000001b3ull;       /* FNV-1a 64 prime */
    }
    return h;
}

typedef struct {
    u64 source_hash;          /* rhi_metal_fnv1a64 of the GLSL source bytes */
    const char *msl_function; /* entry point inside engine.metallib */
} RHIMetalShaderManifestEntry;

/* Generated (build tree): rhi_metal_shader_manifest.c */
extern const RHIMetalShaderManifestEntry rhi_metal_shader_manifest[];
extern const usize rhi_metal_shader_manifest_count;
/* Embedded MSL fallback texts (parallel array, same order); compiled out
 * when RHI_METAL_SHADER_NO_EMBEDDED_MSL is defined. */
#ifndef RHI_METAL_SHADER_NO_EMBEDDED_MSL
extern const char *const rhi_metal_shader_msl[];
#endif
