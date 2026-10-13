if(NOT DEFINED RHI_INTERNAL_HEADER)
    message(FATAL_ERROR "RHI_INTERNAL_HEADER is required")
endif()
if(NOT DEFINED RHI_SOURCE)
    message(FATAL_ERROR "RHI_SOURCE is required")
endif()
if(NOT DEFINED RHI_GL_SOURCE)
    message(FATAL_ERROR "RHI_GL_SOURCE is required")
endif()
if(NOT DEFINED RHI_VK_SOURCE)
    message(FATAL_ERROR "RHI_VK_SOURCE is required")
endif()
if(NOT DEFINED RHI_OWNERSHIP_SOURCE)
    message(FATAL_ERROR "RHI_OWNERSHIP_SOURCE is required")
endif()
if(NOT DEFINED RHI_VALIDATION_SOURCE)
    message(FATAL_ERROR "RHI_VALIDATION_SOURCE is required")
endif()
if(NOT DEFINED RHI_RESOURCES_SOURCE)
    message(FATAL_ERROR "RHI_RESOURCES_SOURCE is required")
endif()
if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()

file(READ "${RHI_INTERNAL_HEADER}" internal_text)
file(READ "${RHI_SOURCE}" rhi_text)
file(READ "${RHI_GL_SOURCE}" gl_text)
file(READ "${RHI_VK_SOURCE}" vk_text)
file(READ "${ENGINE_CMAKE}" engine_cmake_text)
if(NOT EXISTS "${RHI_OWNERSHIP_SOURCE}")
    message(FATAL_ERROR "RHI ownership source is missing: ${RHI_OWNERSHIP_SOURCE}")
endif()
if(NOT EXISTS "${RHI_VALIDATION_SOURCE}")
    message(FATAL_ERROR "RHI validation source is missing: ${RHI_VALIDATION_SOURCE}")
endif()
if(NOT EXISTS "${RHI_RESOURCES_SOURCE}")
    message(FATAL_ERROR "RHI resources source is missing: ${RHI_RESOURCES_SOURCE}")
endif()

foreach(required_text
        "src/rhi/rhi_ownership.c"
        "src/rhi/rhi_validation.c"
        "src/rhi/rhi_resources.c")
    string(FIND "${engine_cmake_text}" "${required_text}" target_offset)
    if(target_offset EQUAL -1)
        message(FATAL_ERROR "engine CMake source ownership missing: ${required_text}")
    endif()
endforeach()

foreach(required_text
        "RHIResourceType"
        "RHIResourceSlot"
        "struct RHIDevice"
        "g_current_device"
        "rhi_alloc_slot"
        "rhi_get_resource_typed"
        "rhi_free_slot"
        "rhi_frame_owner_begin_backend"
        "rhi_frame_owner_begin_destroy"
        "rhi_frame_owner_is_current"
        "rhi_frame_owner_release"
        "rhi_device_control_try_acquire"
        "rhi_device_control_release")
    string(FIND "${internal_text}" "${required_text}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "backend internal contract missing: ${required_text}")
    endif()
endforeach()

string(FIND "${gl_text}" "rhi_backend_internal.h" gl_include_offset)
if(gl_include_offset EQUAL -1)
    message(FATAL_ERROR "OpenGL backend must include the private internal contract")
endif()
string(FIND "${vk_text}" "rhi_backend_internal.h" vk_include_offset)
if(vk_include_offset EQUAL -1)
    message(FATAL_ERROR "Vulkan backend must include the private internal contract")
endif()

string(FIND "${rhi_text}" "rhi_backend_internal.h" rhi_include_offset)
if(rhi_include_offset EQUAL -1)
    message(FATAL_ERROR "rhi.c must include the private internal contract explicitly")
endif()
