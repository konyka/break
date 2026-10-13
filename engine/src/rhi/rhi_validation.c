#include <rhi/rhi.h>

#include <string.h>

bool rhi_present_damage_validate(const RHIPresentRect *rects, u32 count,
                                 u32 width, u32 height) {
    u32 i;
    if (count > RHI_MAX_PRESENT_DAMAGE_RECTS || width == 0u || height == 0u ||
        (count != 0u && rects == NULL)) {
        return false;
    }
    for (i = 0; i < count; ++i) {
        const RHIPresentRect *rect = &rects[i];
        if (rect->x < 0 || rect->y < 0 || rect->w == 0u || rect->h == 0u ||
            (u64)rect->x + rect->w > width ||
            (u64)rect->y + rect->h > height) {
            return false;
        }
    }
    return true;
}

bool rhi_present_damage_to_bottom_left(const RHIPresentRect *rects, u32 count,
                                       u32 width, u32 height,
                                       RHIPresentRect *out, u32 capacity) {
    u32 i;

    if (count > capacity || (count != 0u && out == NULL) ||
        !rhi_present_damage_validate(rects, count, width, height)) {
        return false;
    }
    for (i = 0u; i < count; ++i) {
        RHIPresentRect rect = rects[i];
        rect.y = (i32)(height - ((u32)rect.y + rect.h));
        out[i] = rect;
    }
    return true;
}

bool rhi_screenshot_region_validate(u32 x, u32 y, u32 w, u32 h,
                                    u32 width, u32 height,
                                    usize dst_bytes) {
    usize required;
    usize max_size = (usize)-1;
    if (width == 0u || height == 0u || w == 0u || h == 0u ||
        x >= width || y >= height || w > width - x || h > height - y) {
        return false;
    }
    if ((usize)w > max_size / 4u) {
        return false;
    }
    required = (usize)w * 4u;
    if ((usize)h > max_size / required) {
        return false;
    }
    required *= (usize)h;
    return required <= (usize)RHI_MAX_SCREENSHOT_BYTES && dst_bytes >= required;
}

bool rhi_texture_desc_validate(const RHITextureDesc *desc) {
    u32 max_extent;
    u32 max_mips = 1u;

    if (desc == NULL || desc->width == 0u || desc->height == 0u ||
        desc->width > RHI_MAX_DRAWABLE_DIMENSION ||
        desc->height > RHI_MAX_DRAWABLE_DIMENSION ||
        desc->format < RHI_FORMAT_R8G8B8A8_UNORM ||
        desc->format > RHI_FORMAT_D32_FLOAT ||
        desc->format == RHI_FORMAT_UNDEFINED ||
        desc->mip_levels > RHI_MAX_MIP_LEVELS) {
        return false;
    }
    max_extent = desc->width > desc->height ? desc->width : desc->height;
    while (max_extent > 1u) {
        max_extent >>= 1u;
        max_mips++;
    }
    return desc->mip_levels == 0u || desc->mip_levels <= max_mips;
}

bool rhi_buffer_desc_validate(const RHIBufferDesc *desc) {
    const RHIBufferUsage known_usage = (RHIBufferUsage)(
        RHI_BUFFER_USAGE_VERTEX | RHI_BUFFER_USAGE_INDEX |
        RHI_BUFFER_USAGE_UNIFORM | RHI_BUFFER_USAGE_TEXEL |
        RHI_BUFFER_USAGE_STORAGE | RHI_BUFFER_USAGE_INDIRECT |
        RHI_BUFFER_USAGE_AS_BUILD_INPUT | RHI_BUFFER_USAGE_DEVICE_ADDRESS);
    return desc != NULL && desc->size != 0u &&
           (desc->usage & known_usage) != 0 &&
           (desc->usage & (RHIBufferUsage)~known_usage) == 0;
}

bool rhi_cubemap_desc_validate(const RHICubemapDesc *desc) {
    u32 max_mips = 1u;
    u32 extent;

    if (desc == NULL || desc->size == 0u ||
        desc->size > RHI_MAX_DRAWABLE_DIMENSION ||
        desc->format < RHI_FORMAT_R8G8B8A8_UNORM ||
        desc->format > RHI_FORMAT_R16G16B16A16_SFLOAT ||
        desc->mip_levels > RHI_MAX_MIP_LEVELS) {
        return false;
    }
    extent = desc->size;
    while (extent > 1u) {
        extent >>= 1u;
        max_mips++;
    }
    return desc->mip_levels == 0u || desc->mip_levels <= max_mips;
}

bool rhi_tlas_instance_encode(void *dst, usize dst_size,
                              u64 blas_device_address,
                              const RHITLASInstanceDesc *desc) {
    u32 packed0, packed1;
    if (dst == NULL || dst_size < RHI_TLAS_INSTANCE_SIZE || desc == NULL ||
        blas_device_address == 0u) return false;
    packed0 = (desc->instance_custom_index & 0x00FFFFFFu) |
              ((u32)desc->instance_mask << 24);
    packed1 = (desc->sbt_record_offset & 0x00FFFFFFu) |
              ((desc->instance_flags & 0xFFu) << 24);
    memset(dst, 0, RHI_TLAS_INSTANCE_SIZE);
    memcpy((u8 *)dst, desc->transform, sizeof(desc->transform));
    memcpy((u8 *)dst + 48, &packed0, sizeof(packed0));
    memcpy((u8 *)dst + 52, &packed1, sizeof(packed1));
    memcpy((u8 *)dst + 56, &blas_device_address, sizeof(blas_device_address));
    return true;
}

bool rhi_offscreen_fbo_desc_validate(const RHICapabilities *caps,
                                     const RHIOffscreenFBODesc *desc) {
    if (!caps || !desc || desc->width == 0u || desc->height == 0u ||
        desc->width > RHI_MAX_DRAWABLE_DIMENSION ||
        desc->height > RHI_MAX_DRAWABLE_DIMENSION) return false;
    if (desc->color_format < RHI_FORMAT_R8G8B8A8_UNORM ||
        desc->color_format > RHI_FORMAT_R32_FLOAT ||
        desc->color_format == RHI_FORMAT_UNDEFINED ||
        desc->color_format == RHI_FORMAT_D32_FLOAT) return false;

    u32 samples = desc->sample_count == 0u ? 1u : desc->sample_count;
    u32 sample_bit = rhi_sample_count_bit(samples);
    if (sample_bit == 0u || (caps->color_sample_counts & sample_bit) == 0u ||
        (caps->depth_sample_counts & sample_bit) == 0u)
        return false;
    if (samples > 1u && (!caps->color_resolve_supported ||
                         !caps->depth_resolve_supported))
        return false;
    return true;
}

bool rhi_mrt_desc_validate(u32 width, u32 height,
                           const RHIFormat *formats, u32 attachment_count) {
    if (width == 0u || height == 0u ||
        width > RHI_MAX_DRAWABLE_DIMENSION ||
        height > RHI_MAX_DRAWABLE_DIMENSION ||
        formats == NULL || attachment_count == 0u ||
        attachment_count > RHI_MRT_MAX_ATTACHMENTS) {
        return false;
    }
    for (u32 i = 0u; i < attachment_count; ++i) {
        if (formats[i] < RHI_FORMAT_R8G8B8A8_UNORM ||
            formats[i] > RHI_FORMAT_R32_FLOAT ||
            formats[i] == RHI_FORMAT_UNDEFINED ||
            formats[i] == RHI_FORMAT_D32_FLOAT) {
            return false;
        }
    }
    return true;
}
