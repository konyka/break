#include <rhi/rhi.h>

#include <string.h>

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
