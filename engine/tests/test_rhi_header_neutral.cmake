if(NOT DEFINED RHI_PUBLIC_HEADER)
    message(FATAL_ERROR "RHI_PUBLIC_HEADER is required")
endif()
if(NOT DEFINED RHI_VULKAN_NATIVE_HEADER)
    message(FATAL_ERROR "RHI_VULKAN_NATIVE_HEADER is required")
endif()
if(NOT EXISTS "${RHI_PUBLIC_HEADER}")
    message(FATAL_ERROR "missing public header: ${RHI_PUBLIC_HEADER}")
endif()
if(NOT EXISTS "${RHI_VULKAN_NATIVE_HEADER}")
    message(FATAL_ERROR "missing vulkan native header: ${RHI_VULKAN_NATIVE_HEADER}")
endif()
file(READ "${RHI_PUBLIC_HEADER}" rhi_public_text)
foreach(forbidden_token
        "VkDevice"
        "vkCmd"
        "VkAccelerationStructureInstanceKHR"
        "rhi_vk_validation_"
        "_get_vk_handle")
    string(FIND "${rhi_public_text}" "${forbidden_token}" forbidden_offset)
    if(NOT forbidden_offset EQUAL -1)
        message(FATAL_ERROR
            "rhi.h must stay backend-neutral; found token: ${forbidden_token}")
    endif()
endforeach()
foreach(required_token
        "RHI_BACKEND_METAL"
        "RHI_BACKEND_D3D12"
        "RHI_NATIVE_HANDLE_METAL"
        "RHI_NATIVE_HANDLE_D3D12")
    string(FIND "${rhi_public_text}" "${required_token}" required_offset)
    if(required_offset EQUAL -1)
        message(FATAL_ERROR "rhi.h missing neutral extension token: ${required_token}")
    endif()
endforeach()
file(READ "${RHI_VULKAN_NATIVE_HEADER}" vulkan_native_text)
foreach(required_native_token
        "RHINativeDevice"
        "RHITextureNativeInfo"
        "RHICmdBufferNativeInfo"
        "rhi_texture_get_native_info"
        "rhi_device_get_native_device"
        "rhi_backend_get_native_device"
        "rhi_backend_acceleration_structure_get_vk_handle"
        "rhi_acceleration_structure_get_vk_handle"
        "rhi_vk_validation_message_count"
        "rhi_vk_validation_message_count_reset"
        "rhi_vk_validation_gate_active"
        "rhi_vk_validation_set_enabled")
    string(FIND "${vulkan_native_text}" "${required_native_token}" native_offset)
    if(native_offset EQUAL -1)
        message(FATAL_ERROR
            "rhi_native_vulkan.h missing declaration: ${required_native_token}")
    endif()
endforeach()
