foreach(required_var RHI_VK_SOURCE VK_SURFACE_SOURCE VK_SURFACE_HEADER ENGINE_CMAKE)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()

file(READ "${RHI_VK_SOURCE}" vk_text)
file(READ "${ENGINE_CMAKE}" engine_cmake_text)
get_filename_component(engine_source_dir "${ENGINE_CMAKE}" DIRECTORY)
file(READ "${engine_source_dir}/src/platform/window_screen.c" qnx_screen_text)
string(FIND "${qnx_screen_text}" "usage |= SCREEN_USAGE_VULKAN;" qnx_usage_offset)
if(qnx_usage_offset EQUAL -1)
    message(FATAL_ERROR
        "QNX Vulkan windows must opt into SCREEN_USAGE_VULKAN")
endif()

# rhi_vk.c 不得再直接创建 WSI surface（token 级证据：创建调用已迁入 PAL）。
foreach(forbidden_token
        "vkCreateWin32SurfaceKHR" "vkCreateXlibSurfaceKHR"
        "vkCreateWaylandSurfaceKHR" "vkCreateAndroidSurfaceKHR"
        "vkCreateScreenSurfaceQNX"
        "VkMetalSurfaceCreateInfoEXT" "VkWin32SurfaceCreateInfoKHR"
        "VkXlibSurfaceCreateInfoKHR" "VkWaylandSurfaceCreateInfoKHR"
        "VkAndroidSurfaceCreateInfoKHR" "VkScreenSurfaceCreateInfoQNX")
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

# PAL 模块存在且六个平台分支齐备。
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
        "ENGINE_PLATFORM_QNX"
        "vkCreateWin32SurfaceKHR" "vkCreateXlibSurfaceKHR"
        "vkCreateWaylandSurfaceKHR" "vkCreateAndroidSurfaceKHR"
        "vkCreateMetalSurfaceEXT" "vkCreateScreenSurfaceQNX")
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

# Android 引用配对：vk->native_window 只能在 PAL 创建成功之后赋值。
# PAL 在成功路径 acquire（失败路径自行回滚），vk_shutdown 以字段非 NULL 为
# release 条件——若赋值早于 platform_vk_create_surface_handles 调用，任何
# 前置失败路径都会让 release 无配对地多执行一次（净下溢）。
set(android_assign_token "vk->native_window = (struct ANativeWindow *)window_native;")
string(FIND "${vk_text}" "${android_assign_token}" android_assign_offset)
if(android_assign_offset EQUAL -1)
    message(FATAL_ERROR
        "rhi_vk.c must retain the Android native_window assignment for the shutdown release")
endif()
string(FIND "${vk_text}" "${android_assign_token}" android_assign_second
    REVERSE)
if(NOT android_assign_second EQUAL android_assign_offset)
    message(FATAL_ERROR
        "rhi_vk.c must assign vk->native_window exactly once")
endif()
if(android_assign_offset LESS pal_call_offset)
    message(FATAL_ERROR
        "rhi_vk.c must assign vk->native_window only after platform_vk_create_surface_handles succeeds")
endif()
