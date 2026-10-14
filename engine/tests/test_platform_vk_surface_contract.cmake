foreach(required_var RHI_VK_SOURCE VK_SURFACE_SOURCE VK_SURFACE_HEADER ENGINE_CMAKE)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()

file(READ "${RHI_VK_SOURCE}" vk_text)
file(READ "${ENGINE_CMAKE}" engine_cmake_text)

# rhi_vk.c 不得再直接创建 WSI surface（token 级证据：创建调用已迁入 PAL）。
foreach(forbidden_token
        "vkCreateWin32SurfaceKHR" "vkCreateXlibSurfaceKHR"
        "vkCreateWaylandSurfaceKHR" "vkCreateAndroidSurfaceKHR"
        "VkMetalSurfaceCreateInfoEXT" "VkWin32SurfaceCreateInfoKHR"
        "VkXlibSurfaceCreateInfoKHR" "VkWaylandSurfaceCreateInfoKHR"
        "VkAndroidSurfaceCreateInfoKHR")
    string(FIND "${vk_text}" "${forbidden_token}" forbidden_offset)
    if(NOT forbidden_offset EQUAL -1)
        message(FATAL_ERROR
            "rhi_vk.c still creates WSI surfaces directly: ${forbidden_token}")
    endif()
endforeach()
# rhi_vk.c 必须改经 PAL 入口。
string(FIND "${vk_text}" "platform_vk_create_surface_handles(" pal_call_offset)
if(pal_call_offset EQUAL -1)
    message(FATAL_ERROR "rhi_vk.c must create the surface via platform_vk_create_surface_handles")
endif()
string(FIND "${vk_text}" "platform_vk_required_instance_extensions(" pal_ext_offset)
if(pal_ext_offset EQUAL -1)
    message(FATAL_ERROR "rhi_vk.c must source instance extensions via platform_vk_required_instance_extensions")
endif()

# PAL 模块存在且五个平台分支齐备。
if(NOT EXISTS "${VK_SURFACE_HEADER}")
    message(FATAL_ERROR "missing: ${VK_SURFACE_HEADER}")
endif()
if(NOT EXISTS "${VK_SURFACE_SOURCE}")
    message(FATAL_ERROR "missing: ${VK_SURFACE_SOURCE}")
endif()
file(READ "${VK_SURFACE_SOURCE}" surface_text)
foreach(required_token
        "ENGINE_PLATFORM_WINDOWS" "ENGINE_PLATFORM_WAYLAND"
        "ENGINE_PLATFORM_ANDROID" "ENGINE_PLATFORM_LINUX"
        "vkCreateWin32SurfaceKHR" "vkCreateXlibSurfaceKHR"
        "vkCreateWaylandSurfaceKHR" "vkCreateAndroidSurfaceKHR"
        "vkCreateMetalSurfaceEXT")
    string(FIND "${surface_text}" "${required_token}" surface_offset)
    if(surface_offset EQUAL -1)
        message(FATAL_ERROR
            "platform_vk_surface.c missing platform branch token: ${required_token}")
    endif()
endforeach()
foreach(dual_token "ENGINE_PLATFORM_MACOS" "ENGINE_PLATFORM_IOS")
    string(FIND "${surface_text}" "${dual_token}" dual_offset)
    if(dual_offset EQUAL -1)
        message(FATAL_ERROR
            "platform_vk_surface.c missing platform branch token: ${dual_token}")
    endif()
endforeach()
# PAL 源必须编入 engine target。
string(FIND "${engine_cmake_text}" "src/platform/platform_vk_surface.c" cmake_offset)
if(cmake_offset EQUAL -1)
    message(FATAL_ERROR "engine target does not compile src/platform/platform_vk_surface.c")
endif()
