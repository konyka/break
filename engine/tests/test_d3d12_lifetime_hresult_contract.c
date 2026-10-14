#include "test_framework.h"

#include <stdbool.h>
#include <stdint.h>

typedef int32_t D3D12ContractResult;
enum {
    CONTRACT_OK = 0,
    CONTRACT_E_FAIL = (D3D12ContractResult)0x80004005,
    CONTRACT_E_OUTOFMEMORY = (D3D12ContractResult)0x8007000E,
    CONTRACT_DEVICE_REMOVED = (D3D12ContractResult)0x887A0005,
    CONTRACT_DEVICE_RESET = (D3D12ContractResult)0x887A0007,
    CONTRACT_E_BUSY = (D3D12ContractResult)0x8000000A,
};

typedef enum {
    CONTRACT_FAIL_NONE,
    CONTRACT_FAIL_ADAPTER,
    CONTRACT_FAIL_QUEUE,
    CONTRACT_FAIL_DESCRIPTOR,
    CONTRACT_FAIL_FENCE,
} ContractFailure;

typedef enum {
    RESOURCE_COMMON,
    RESOURCE_COPY_DEST,
    RESOURCE_SHADER_READ,
} ResourceState;

typedef struct {
    void *adapter;
    void *queue;
    void *descriptor_heap;
    void *fence;
    ContractFailure failure;
    uint64_t next_fence;
    uint64_t completed_fence;
    bool descriptor_live;
    uint64_t descriptor_retire_fence;
    ResourceState resource_state;
    D3D12ContractResult operation_result;
    D3D12ContractResult device_lost_result;
    bool device_lost;
} ContractDevice;

static void contract_cleanup(ContractDevice *device) {
    device->fence = NULL;
    device->descriptor_heap = NULL;
    device->queue = NULL;
    device->adapter = NULL;
    device->descriptor_live = false;
    device->descriptor_retire_fence = 0u;
}

static D3D12ContractResult contract_probe_adapter(ContractDevice *device) {
    if (device->failure == CONTRACT_FAIL_ADAPTER) return CONTRACT_E_FAIL;
    device->adapter = (void *)(uintptr_t)1u;
    return CONTRACT_OK;
}

static D3D12ContractResult contract_create_device(ContractDevice *device) {
    D3D12ContractResult result = contract_probe_adapter(device);
    if (result != CONTRACT_OK) {
        contract_cleanup(device);
        return result;
    }
    if (device->failure == CONTRACT_FAIL_QUEUE) {
        contract_cleanup(device);
        return CONTRACT_E_FAIL;
    }
    device->queue = (void *)(uintptr_t)2u;
    if (device->failure == CONTRACT_FAIL_DESCRIPTOR) {
        contract_cleanup(device);
        return CONTRACT_E_OUTOFMEMORY;
    }
    device->descriptor_heap = (void *)(uintptr_t)3u;
    if (device->failure == CONTRACT_FAIL_FENCE) {
        contract_cleanup(device);
        return CONTRACT_E_OUTOFMEMORY;
    }
    device->fence = (void *)(uintptr_t)4u;
    device->resource_state = RESOURCE_COMMON;
    return CONTRACT_OK;
}

static D3D12ContractResult contract_signal(ContractDevice *device,
                                           uint64_t *out_value) {
    if (device->fence == NULL || out_value == NULL) return CONTRACT_E_FAIL;
    *out_value = ++device->next_fence;
    return CONTRACT_OK;
}

static D3D12ContractResult contract_retire(ContractDevice *device,
                                           uint64_t value) {
    if (device->fence == NULL || value < device->completed_fence ||
        value > device->next_fence) return CONTRACT_E_FAIL;
    device->completed_fence = value;
    return CONTRACT_OK;
}

static D3D12ContractResult contract_allocate_descriptor(ContractDevice *device) {
    if (device->descriptor_heap == NULL) return CONTRACT_E_FAIL;
    if (device->descriptor_live &&
        device->completed_fence < device->descriptor_retire_fence)
        return CONTRACT_E_BUSY;
    device->descriptor_live = true;
    device->descriptor_retire_fence = 0u;
    return CONTRACT_OK;
}

static D3D12ContractResult contract_retire_descriptor(ContractDevice *device) {
    uint64_t fence_value;
    if (!device->descriptor_live) return CONTRACT_E_FAIL;
    if (contract_signal(device, &fence_value) != CONTRACT_OK) return CONTRACT_E_FAIL;
    device->descriptor_retire_fence = fence_value;
    return CONTRACT_OK;
}

static D3D12ContractResult contract_transition(ContractDevice *device,
                                                ResourceState next) {
    bool legal = (device->resource_state == RESOURCE_COMMON &&
                  next == RESOURCE_COPY_DEST) ||
                 (device->resource_state == RESOURCE_COPY_DEST &&
                  next == RESOURCE_SHADER_READ) ||
                 (device->resource_state == next);
    if (device->fence == NULL || !legal) return CONTRACT_E_FAIL;
    device->resource_state = next;
    return CONTRACT_OK;
}

static bool contract_is_device_lost(D3D12ContractResult result) {
    return result == CONTRACT_DEVICE_REMOVED || result == CONTRACT_DEVICE_RESET;
}

static D3D12ContractResult contract_execute_operation(ContractDevice *device) {
    D3D12ContractResult result;
    if (device->fence == NULL || device->device_lost) return CONTRACT_E_FAIL;
    result = device->operation_result;
    if (contract_is_device_lost(result)) {
        device->device_lost = true;
        device->device_lost_result = result;
        contract_cleanup(device);
    }
    return result;
}

TEST(adapter_probe_failure_has_no_handle)
{
    ContractDevice device = {0};
    device.failure = CONTRACT_FAIL_ADAPTER;
    ASSERT_EQ(contract_create_device(&device), CONTRACT_E_FAIL);
    ASSERT_EQ(device.adapter, NULL);
    ASSERT_EQ(device.queue, NULL);
    ASSERT_EQ(device.descriptor_heap, NULL);
    ASSERT_EQ(device.fence, NULL);
}

TEST(each_creation_failure_cleans_partial_handles)
{
    ContractFailure failures[] = {
        CONTRACT_FAIL_QUEUE, CONTRACT_FAIL_DESCRIPTOR, CONTRACT_FAIL_FENCE};
    size_t i;
    for (i = 0u; i < sizeof(failures) / sizeof(failures[0]); ++i) {
        ContractDevice device = {0};
        device.failure = failures[i];
        ASSERT_NEQ(contract_create_device(&device), CONTRACT_OK);
        ASSERT_EQ(device.adapter, NULL);
        ASSERT_EQ(device.queue, NULL);
        ASSERT_EQ(device.descriptor_heap, NULL);
        ASSERT_EQ(device.fence, NULL);
    }
}

TEST(fence_values_are_monotonic_and_retirement_is_bounded)
{
    ContractDevice device = {0};
    uint64_t first;
    uint64_t second;
    ASSERT_EQ(contract_create_device(&device), CONTRACT_OK);
    ASSERT_EQ(contract_signal(&device, &first), CONTRACT_OK);
    ASSERT_EQ(contract_signal(&device, &second), CONTRACT_OK);
    ASSERT_TRUE(second > first);
    ASSERT_EQ(contract_retire(&device, second), CONTRACT_OK);
    ASSERT_EQ(device.completed_fence, second);
    ASSERT_EQ(contract_retire(&device, first), CONTRACT_E_FAIL);
    ASSERT_EQ(device.completed_fence, second);
    ASSERT_EQ(contract_retire(&device, second + 1u), CONTRACT_E_FAIL);
    ASSERT_EQ(device.completed_fence, second);
    contract_cleanup(&device);
}

TEST(descriptor_reuse_requires_fence_retirement)
{
    ContractDevice device = {0};
    ASSERT_EQ(contract_create_device(&device), CONTRACT_OK);
    ASSERT_EQ(contract_allocate_descriptor(&device), CONTRACT_OK);
    ASSERT_EQ(contract_retire_descriptor(&device), CONTRACT_OK);
    ASSERT_EQ(contract_allocate_descriptor(&device), CONTRACT_E_BUSY);
    ASSERT_EQ(contract_retire(&device, device.descriptor_retire_fence), CONTRACT_OK);
    ASSERT_EQ(contract_allocate_descriptor(&device), CONTRACT_OK);
    contract_cleanup(&device);
}

TEST(resource_state_transitions_reject_stale_order)
{
    ContractDevice device = {0};
    ASSERT_EQ(contract_create_device(&device), CONTRACT_OK);
    ASSERT_EQ(contract_transition(&device, RESOURCE_SHADER_READ), CONTRACT_E_FAIL);
    ASSERT_EQ(device.resource_state, RESOURCE_COMMON);
    ASSERT_EQ(contract_transition(&device, RESOURCE_COPY_DEST), CONTRACT_OK);
    ASSERT_EQ(contract_transition(&device, RESOURCE_SHADER_READ), CONTRACT_OK);
    ASSERT_EQ(contract_transition(&device, RESOURCE_COPY_DEST), CONTRACT_E_FAIL);
    ASSERT_EQ(device.resource_state, RESOURCE_SHADER_READ);
    contract_cleanup(&device);
}

TEST(device_lost_is_distinct_from_transient_failure)
{
    ASSERT_TRUE(contract_is_device_lost(CONTRACT_DEVICE_REMOVED));
    ASSERT_TRUE(contract_is_device_lost(CONTRACT_DEVICE_RESET));
    ASSERT_FALSE(contract_is_device_lost(CONTRACT_E_FAIL));
    ASSERT_FALSE(contract_is_device_lost(CONTRACT_E_OUTOFMEMORY));
    ASSERT_FALSE(contract_is_device_lost(CONTRACT_E_BUSY));
}

TEST(device_lost_operation_propagates_and_cleans_up)
{
    D3D12ContractResult lost_results[] = {
        CONTRACT_DEVICE_REMOVED, CONTRACT_DEVICE_RESET};
    size_t i;
    for (i = 0u; i < sizeof(lost_results) / sizeof(lost_results[0]); ++i) {
        ContractDevice device = {0};
        device.operation_result = lost_results[i];
        ASSERT_EQ(contract_create_device(&device), CONTRACT_OK);
        ASSERT_EQ(contract_allocate_descriptor(&device), CONTRACT_OK);
        ASSERT_EQ(contract_execute_operation(&device), lost_results[i]);
        ASSERT_TRUE(device.device_lost);
        ASSERT_EQ(device.device_lost_result, lost_results[i]);
        ASSERT_EQ(device.adapter, NULL);
        ASSERT_EQ(device.queue, NULL);
        ASSERT_EQ(device.descriptor_heap, NULL);
        ASSERT_EQ(device.fence, NULL);
        ASSERT_FALSE(device.descriptor_live);
        ASSERT_EQ(device.resource_state, RESOURCE_COMMON);
        ASSERT_EQ(contract_execute_operation(&device), CONTRACT_E_FAIL);
    }
}

TEST_MAIN_BEGIN()
    RUN_TEST(adapter_probe_failure_has_no_handle);
    RUN_TEST(each_creation_failure_cleans_partial_handles);
    RUN_TEST(fence_values_are_monotonic_and_retirement_is_bounded);
    RUN_TEST(descriptor_reuse_requires_fence_retirement);
    RUN_TEST(resource_state_transitions_reject_stale_order);
    RUN_TEST(device_lost_is_distinct_from_transient_failure);
    RUN_TEST(device_lost_operation_propagates_and_cleans_up);
TEST_MAIN_END()
