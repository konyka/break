#if !defined(_WIN32)
int main(void) { return 77; }
#else

#include <rhi/rhi_d3d12.h>

static int context_is_empty(const RHI_D3D12Context *context) {
    return context->adapter == NULL && context->device == NULL &&
           context->queue == NULL && context->allocators[0] == NULL &&
           context->allocators[1] == NULL && context->command_lists[0] == NULL &&
           context->command_lists[1] == NULL && context->rtv_heap == NULL &&
           context->dsv_heap == NULL && context->cbv_srv_uav_heap == NULL &&
           context->fence == NULL && context->fence_event == NULL &&
           context->descriptor_live == 0u;
}

int main(void) {
    RHI_D3D12Context context;
    RHI_D3D12CreateFailure failure;
    for (failure = RHI_D3D12_FAIL_ADAPTER;
         failure <= RHI_D3D12_FAIL_EVENT; ++failure) {
        if (rhi_d3d12_context_create(&context, failure) >= 0 ||
            !context_is_empty(&context)) return 1;
        rhi_d3d12_context_destroy(&context);
    }
    return 0;
}

#endif
