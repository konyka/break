cmake_policy(SET CMP0054 NEW)

if(NOT DEFINED RHI_DISPATCH_DIR OR NOT DEFINED RHI_API_LIST)
    message(FATAL_ERROR "RHI_DISPATCH_DIR and RHI_API_LIST are required")
endif()

set(required_files
    "${RHI_DISPATCH_DIR}/rhi_api.h"
    "${RHI_DISPATCH_DIR}/rhi_dispatch.c"
    "${RHI_DISPATCH_DIR}/rhi_api_bind_gl.c"
    "${RHI_DISPATCH_DIR}/rhi_api_bind_vk.c"
    "${RHI_DISPATCH_DIR}/rhi_backend_rename_gl.h"
    "${RHI_DISPATCH_DIR}/rhi_backend_rename_vk.h")
foreach(required_file IN LISTS required_files RHI_API_LIST)
    if(NOT EXISTS "${required_file}")
        message(FATAL_ERROR "missing RHI dispatch contract input: ${required_file}")
    endif()
endforeach()

file(STRINGS "${RHI_API_LIST}" api_names)
list(LENGTH api_names api_count)
if(NOT api_count EQUAL 135)
    message(FATAL_ERROR "RHI backend API must contain 135 names, got ${api_count}")
endif()
set(unique_names ${api_names})
list(REMOVE_DUPLICATES unique_names)
list(LENGTH unique_names unique_count)
if(NOT unique_count EQUAL api_count)
    message(FATAL_ERROR "RHI backend API contains duplicate names")
endif()
list(FIND api_names "rhi_device_create" create_index)
list(FIND api_names "rhi_device_create_compiled" compiled_index)
if(create_index EQUAL -1 OR compiled_index EQUAL -1)
    message(FATAL_ERROR "RHI backend API must inventory both creation entry points")
endif()

file(READ "${RHI_DISPATCH_DIR}/rhi_api.h" api_h)
file(READ "${RHI_DISPATCH_DIR}/rhi_dispatch.c" dispatch_c)
file(READ "${RHI_DISPATCH_DIR}/rhi_api_bind_gl.c" bind_gl)
file(READ "${RHI_DISPATCH_DIR}/rhi_api_bind_vk.c" bind_vk)
file(READ "${RHI_DISPATCH_DIR}/rhi_backend_rename_gl.h" rename_gl)
file(READ "${RHI_DISPATCH_DIR}/rhi_backend_rename_vk.h" rename_vk)

function(assert_match_count text pattern expected description)
    string(REGEX MATCHALL "${pattern}" matches "${text}")
    list(LENGTH matches actual)
    if(NOT actual EQUAL expected)
        message(FATAL_ERROR
            "${description}: expected ${expected}, got ${actual}")
    endif()
endfunction()

set(begin_marker "/* RHI_FORWARDERS_BEGIN */")
set(end_marker "/* RHI_FORWARDERS_END */")
string(FIND "${dispatch_c}" "${begin_marker}" begin)
string(FIND "${dispatch_c}" "${end_marker}" end)
if(begin EQUAL -1 OR end EQUAL -1 OR NOT end GREATER begin)
    message(FATAL_ERROR "generated forwarder markers are missing or malformed")
endif()
string(LENGTH "${begin_marker}" begin_marker_length)
math(EXPR forwarders_begin "${begin} + ${begin_marker_length}")
math(EXPR forwarders_length "${end} - ${forwarders_begin}")
string(SUBSTRING "${dispatch_c}" ${forwarders_begin} ${forwarders_length} forwarders)

set(forwarder_count 0)
foreach(name IN LISTS api_names)
    assert_match_count("${api_h}" "\\(\\*${name}\\)" 1
        "RHIApi entry for ${name}")
    assert_match_count("${rename_gl}" "#define[ \t]+${name}[ \t]+rhi_gl_${name}" 1
        "OpenGL rename for ${name}")
    assert_match_count("${rename_vk}" "#define[ \t]+${name}[ \t]+rhi_vk_${name}" 1
        "Vulkan rename for ${name}")
    assert_match_count("${bind_gl}" "\\.${name}[ \t]*=" 1
        "OpenGL binding for ${name}")
    assert_match_count("${bind_vk}" "\\.${name}[ \t]*=" 1
        "Vulkan binding for ${name}")
    if(name STREQUAL "rhi_device_create" OR name STREQUAL "rhi_device_create_compiled")
        assert_match_count("${forwarders}" "[ \t\r\n*]${name}[ \t\r\n]*\\(" 0
            "runtime-owned forwarder exclusion for ${name}")
    else()
        assert_match_count("${forwarders}" "[ \t\r\n*]${name}[ \t\r\n]*\\(" 1
            "public forwarder for ${name}")
        math(EXPR forwarder_count "${forwarder_count} + 1")
    endif()
endforeach()

assert_match_count("${api_h}" "\\(\\*rhi_[A-Za-z0-9_]+\\)" 135
    "total RHIApi entries (no extras)")
assert_match_count("${forwarders}"
    "(^|\n)[A-Za-z_][A-Za-z0-9_ \t*]*rhi_[A-Za-z0-9_]+[ \t]*\\("
    ${forwarder_count} "total public forwarders (no extras)")
assert_match_count("${rename_gl}" "#define[ \t]+rhi_[A-Za-z0-9_]+[ \t]+rhi_gl_" 135
    "total OpenGL renames (no extras)")
assert_match_count("${rename_vk}" "#define[ \t]+rhi_[A-Za-z0-9_]+[ \t]+rhi_vk_" 135
    "total Vulkan renames (no extras)")
assert_match_count("${bind_gl}" "\\.rhi_[A-Za-z0-9_]+[ \t]*=" 135
    "total OpenGL bindings (no extras)")
assert_match_count("${bind_vk}" "\\.rhi_[A-Za-z0-9_]+[ \t]*=" 135
    "total Vulkan bindings (no extras)")

foreach(binding IN ITEMS bind_gl bind_vk)
    assert_match_count("${${binding}}"
        "\\.rhi_device_create[ \t]*=[ \t]*rhi_device_create," 1
        "${binding} explicit-create backend binding")
    assert_match_count("${${binding}}"
        "\\.rhi_device_create_compiled[ \t]*=[ \t]*NULL," 1
        "${binding} runtime-owned compiled-create slot")
endforeach()

message(STATUS "RHI dispatch contract OK: 132 API entries, ${forwarder_count} forwarders")
