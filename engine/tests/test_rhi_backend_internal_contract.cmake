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

file(READ "${RHI_INTERNAL_HEADER}" internal_text)
file(READ "${RHI_SOURCE}" rhi_text)
file(READ "${RHI_GL_SOURCE}" gl_text)
file(READ "${RHI_VK_SOURCE}" vk_text)

foreach(required_text
        "RHIResourceType"
        "RHIResourceSlot"
        "struct RHIDevice"
        "g_current_device"
        "rhi_alloc_slot"
        "rhi_get_resource_typed"
        "rhi_free_slot")
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
