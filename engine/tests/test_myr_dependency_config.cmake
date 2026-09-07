if(NOT DEFINED MYR_CMAKE)
    message(FATAL_ERROR "MYR_CMAKE is required")
endif()
if(NOT DEFINED MYUI_CMAKE)
    message(FATAL_ERROR "MYUI_CMAKE is required")
endif()
if(NOT DEFINED MYC_CMAKE)
    message(FATAL_ERROR "MYC_CMAKE is required")
endif()
if(NOT DEFINED MYMVVM_CMAKE)
    message(FATAL_ERROR "MYMVVM_CMAKE is required")
endif()
if(NOT DEFINED MYMVVM_UI_CMAKE)
    message(FATAL_ERROR "MYMVVM_UI_CMAKE is required")
endif()
if(NOT DEFINED MYPAL_CMAKE)
    message(FATAL_ERROR "MYPAL_CMAKE is required")
endif()
if(NOT DEFINED MYR_VULKAN_C)
    message(FATAL_ERROR "MYR_VULKAN_C is required")
endif()

file(READ "${MYR_CMAKE}" myr_cmake)
file(READ "${MYUI_CMAKE}" myui_cmake)
file(READ "${MYC_CMAKE}" myc_cmake)
file(READ "${MYMVVM_CMAKE}" mymvvm_cmake)
file(READ "${MYMVVM_UI_CMAKE}" mymvvm_ui_cmake)
file(READ "${MYPAL_CMAKE}" mypal_cmake)
file(READ "${MYR_VULKAN_C}" myr_vulkan_c)

foreach(required_text
        "MYUI_THIRD_PARTY_DIR"
        "CMAKE_CURRENT_LIST_DIR}/../../../external"
        "option(MYUI_GLES2"
        "option(MYUI_GL_DESKTOP"
        "option(MYUI_VULKAN"
        "find_package(OpenGL QUIET)"
        "OpenGL::GL"
        "find_path(MYUI_GLES2_INCLUDE_DIR"
        "find_library(MYUI_GLES2_LIBRARY"
        "find_package(Freetype QUIET)"
        "if(Freetype_FOUND)"
        "Freetype::Freetype"
        "MYUI_HARFBUZZ"
        "find_package(harfbuzz CONFIG QUIET)"
        "PkgConfig::HARFBUZZ")
    string(FIND "${myr_cmake}" "${required_text}" text_offset)
    if(text_offset EQUAL -1)
        message(FATAL_ERROR "myr dependency contract missing: ${required_text}")
    endif()
endforeach()

foreach(required_text
        "vulkan_shaders_regen"
        "generate_includes.cmake"
        "vulkan_shaders")
    string(FIND "${myr_cmake}" "${required_text}" text_offset)
    if(text_offset EQUAL -1)
        message(FATAL_ERROR "myr backend configuration contract missing: ${required_text}")
    endif()
endforeach()

if(myr_cmake MATCHES "pkg_check_modules\\(GLESV2")
    string(FIND "${myr_cmake}" "if(MYUI_GLES2" gles_guard_offset)
    if(gles_guard_offset EQUAL -1)
        message(FATAL_ERROR "GLES2 discovery must be guarded by MYUI_GLES2")
    endif()
endif()
if(myr_cmake MATCHES "pkg_check_modules\\(OPENGL")
    string(FIND "${myr_cmake}" "if(MYUI_GL_DESKTOP" gl_guard_offset)
    if(gl_guard_offset EQUAL -1)
        message(FATAL_ERROR "desktop OpenGL discovery must be guarded by MYUI_GL_DESKTOP")
    endif()
endif()
if(NOT myr_cmake MATCHES "find_package\\(OpenGL QUIET\\)")
    message(FATAL_ERROR "desktop OpenGL must have a cross-platform CMake discovery fallback")
endif()
if(NOT myr_cmake MATCHES "OpenGL::GL")
    message(FATAL_ERROR "desktop OpenGL must link through the portable OpenGL target")
endif()
if(NOT myr_cmake MATCHES "find_path\\(MYUI_GLES2_INCLUDE_DIR")
    message(FATAL_ERROR "GLES2 must support SDK/header discovery without pkg-config")
endif()
if(NOT myr_cmake MATCHES "find_library\\(MYUI_GLES2_LIBRARY")
    message(FATAL_ERROR "GLES2 must support native library discovery without pkg-config")
endif()
if(myr_cmake MATCHES "pkg_check_modules\\(VULKAN")
    string(FIND "${myr_cmake}" "if(MYUI_VULKAN" vk_guard_offset)
    if(vk_guard_offset EQUAL -1)
        message(FATAL_ERROR "Vulkan discovery must be guarded by MYUI_VULKAN")
    endif()
endif()
if(myr_cmake MATCHES "CMAKE_SOURCE_DIR}/tools/gen_vulkan_shaders.py")
    message(FATAL_ERROR "myr shader regeneration must not use the host source root")
endif()
if(myr_vulkan_c MATCHES "VK_USE_PLATFORM_XLIB_KHR" OR
   myr_vulkan_c MATCHES "VK_USE_PLATFORM_WAYLAND_KHR")
    message(FATAL_ERROR
        "myr must not force Linux Vulkan WSI headers; PAL owns surface creation")
endif()
foreach(required_text
        "surface_enabled"
        "swapchain_enabled"
        "vk_device_ext_present"
        "vk_global_init_reset"
        "instance_ext_count"
        "vk_instance_ext_enabled"
        "my_vgcanvas_vulkan_instance"
        "my_vgcanvas_vulkan_instance_acquire"
        "my_vgcanvas_vulkan_instance_acquire_with_extensions"
        "my_vgcanvas_vulkan_instance_release")
    string(FIND "${myr_vulkan_c}" "${required_text}" text_offset)
    if(text_offset EQUAL -1)
        message(FATAL_ERROR "Vulkan WSI capability contract missing: ${required_text}")
    endif()
endforeach()

if(myr_cmake MATCHES "pkg_check_modules\\(FREETYPE[ \t]+freetype2\\)")
    message(FATAL_ERROR "myr must not require pkg-config for FreeType")
endif()

function(check_module_contract module_name module_var)
    set(module_text "${${module_var}}")
    string(FIND "${module_text}" "MYUI_SOURCE_DIR" source_root_offset)
    if(source_root_offset EQUAL -1)
        message(FATAL_ERROR "${module_name} dependency contract missing: MYUI_SOURCE_DIR")
    endif()
    string(FIND "${module_text}" "MYUI_ENGINE_SOURCE_DIR" engine_root_offset)
    if(engine_root_offset EQUAL -1)
        message(FATAL_ERROR "${module_name} dependency contract missing: MYUI_ENGINE_SOURCE_DIR")
    endif()
    if(NOT module_text MATCHES "MYUI_SOURCE_DIR[ \t]+\"\\$\\{CMAKE_CURRENT_LIST_DIR\\}/\\.\\.\"")
        message(FATAL_ERROR "${module_name} must derive MYUI_SOURCE_DIR from its parent directory")
    endif()
    if(NOT module_text MATCHES "MYUI_ENGINE_SOURCE_DIR[ \t]+\"\\$\\{CMAKE_CURRENT_LIST_DIR\\}/\\.\\.\\/\\.\\.\"")
        message(FATAL_ERROR "${module_name} must derive MYUI_ENGINE_SOURCE_DIR from the module location")
    endif()
    if(module_text MATCHES "CMAKE_SOURCE_DIR}/src")
        message(FATAL_ERROR "${module_name} must not hard-code source paths from CMAKE_SOURCE_DIR")
    endif()
endfunction()

check_module_contract(myr myr_cmake)
check_module_contract(myui myui_cmake)
check_module_contract(myc myc_cmake)
check_module_contract(mymvvm mymvvm_cmake)
check_module_contract(mymvvm_myui mymvvm_ui_cmake)
check_module_contract(mypal mypal_cmake)

foreach(required_text
        "add_library(mypal STATIC"
        "my_event.c"
        "my_pal_media.c"
        "my_pal_vulkan.c"
        "dummy/my_pal_dummy.c"
        "Threads::Threads")
    string(FIND "${mypal_cmake}" "${required_text}" text_offset)
    if(text_offset EQUAL -1)
        message(FATAL_ERROR "mypal dependency contract missing: ${required_text}")
    endif()
endforeach()

foreach(required_text
        "MYUI_THIRD_PARTY_DIR"
        "CMAKE_CURRENT_LIST_DIR}/../../../external")
    string(FIND "${myui_cmake}" "${required_text}" text_offset)
    if(text_offset EQUAL -1)
        message(FATAL_ERROR "myui dependency contract missing: ${required_text}")
    endif()
endforeach()
