#include <rhi/rhi_backend_internal.h>

static _Thread_local unsigned char g_rhi_thread_token;
_Thread_local RHIDevice *g_rhi_frame_device;
_Thread_local bool g_rhi_frame_owner_preclaimed;

#define RHI_FRAME_OWNER_DESTROYING ((uintptr_t)1u)
#define RHI_FRAME_OWNER_CONTROLLING ((uintptr_t)2u)

static uintptr_t rhi_thread_owner_token(void) {
    return (uintptr_t)&g_rhi_thread_token;
}

bool rhi_frame_owner_try_acquire(RHIDevice *dev) {
    uintptr_t expected = 0u;
    if (dev == NULL || g_rhi_frame_device != NULL) return false;
    if (!atomic_compare_exchange_strong_explicit(
        &dev->frame_owner, &expected, rhi_thread_owner_token(),
        memory_order_acquire, memory_order_relaxed)) return false;
    g_rhi_frame_device = dev;
    return true;
}

bool rhi_frame_owner_begin_destroy(RHIDevice *dev) {
    uintptr_t expected = 0u;
    if (dev == NULL || g_rhi_frame_device == dev) return false;
    return atomic_compare_exchange_strong_explicit(
        &dev->frame_owner, &expected, RHI_FRAME_OWNER_DESTROYING,
        memory_order_acquire, memory_order_relaxed);
}

bool rhi_device_control_try_acquire(RHIDevice *dev) {
    uintptr_t expected = 0u;
    if (dev == NULL) return false;
    return atomic_compare_exchange_strong_explicit(
        &dev->frame_owner, &expected, RHI_FRAME_OWNER_CONTROLLING,
        memory_order_acquire, memory_order_relaxed);
}

void rhi_device_control_release(RHIDevice *dev) {
    uintptr_t expected = RHI_FRAME_OWNER_CONTROLLING;
    if (dev == NULL) return;
    (void)atomic_compare_exchange_strong_explicit(
        &dev->frame_owner, &expected, 0u, memory_order_release,
        memory_order_relaxed);
}

bool rhi_frame_owner_is_current(const RHIDevice *dev) {
    return dev != NULL && g_rhi_frame_device == dev &&
           atomic_load_explicit(&dev->frame_owner, memory_order_acquire) ==
               rhi_thread_owner_token();
}

void rhi_frame_owner_release(RHIDevice *dev) {
    uintptr_t expected;
    if (dev == NULL) return;
    expected = rhi_thread_owner_token();
    if (atomic_compare_exchange_strong_explicit(
            &dev->frame_owner, &expected, 0u, memory_order_release,
            memory_order_relaxed) && g_rhi_frame_device == dev) {
        g_rhi_frame_device = NULL;
        g_rhi_frame_owner_preclaimed = false;
    }
}

bool rhi_frame_owner_begin_backend(RHIDevice *dev) {
    if (g_rhi_frame_owner_preclaimed) {
        g_rhi_frame_owner_preclaimed = false;
        return rhi_frame_owner_is_current(dev);
    }
    return rhi_frame_owner_try_acquire(dev);
}
