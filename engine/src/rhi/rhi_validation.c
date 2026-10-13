#include <rhi/rhi.h>

#include <string.h>

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
