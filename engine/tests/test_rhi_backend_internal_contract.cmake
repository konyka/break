cmake_policy(SET CMP0054 NEW)

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
if(NOT DEFINED RHI_HEADLESS_SOURCE)
    message(FATAL_ERROR "RHI_HEADLESS_SOURCE is required")
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
if(NOT DEFINED RHI_PRESENT_HISTORY_SOURCE)
    message(FATAL_ERROR "RHI_PRESENT_HISTORY_SOURCE is required")
endif()
if(NOT DEFINED RHI_RT_TRACE_SOURCE)
    message(FATAL_ERROR "RHI_RT_TRACE_SOURCE is required")
endif()
if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()

function(extract_cmake_command text command_start output_var)
    string(REGEX REPLACE "#[^\r\n]*" "" uncommented_text "${text}")
    string(FIND "${uncommented_text}" "${command_start}" command_start_offset)
    if(command_start_offset EQUAL -1)
        set(${output_var} "" PARENT_SCOPE)
        return()
    endif()

    string(LENGTH "${uncommented_text}" text_length)
    set(scan_offset ${command_start_offset})
    set(parenthesis_depth 0)
    while(scan_offset LESS text_length)
        string(SUBSTRING "${uncommented_text}" ${scan_offset} 1 current_char)
        if(current_char STREQUAL "(")
            math(EXPR parenthesis_depth "${parenthesis_depth} + 1")
        elseif(current_char STREQUAL ")")
            math(EXPR parenthesis_depth "${parenthesis_depth} - 1")
            if(parenthesis_depth EQUAL 0)
                math(EXPR command_length "${scan_offset} - ${command_start_offset} + 1")
                string(SUBSTRING "${uncommented_text}" ${command_start_offset} ${command_length}
                    extracted_command)
                set(${output_var} "${extracted_command}" PARENT_SCOPE)
                return()
            endif()
        endif()
        math(EXPR scan_offset "${scan_offset} + 1")
    endwhile()
    set(${output_var} "" PARENT_SCOPE)
endfunction()

file(READ "${RHI_INTERNAL_HEADER}" internal_text)
file(READ "${RHI_SOURCE}" rhi_text)
file(READ "${RHI_GL_SOURCE}" gl_text)
file(READ "${RHI_VK_SOURCE}" vk_text)
file(READ "${ENGINE_CMAKE}" engine_cmake_text)
if(DEFINED RHI_OMIT_TARGET)
    if(RHI_OMIT_TARGET STREQUAL "engine")
        set(omit_command_start "add_library(engine STATIC")
    else()
        set(omit_command_start "add_executable(${RHI_OMIT_TARGET}")
    endif()
    extract_cmake_command("${engine_cmake_text}" "${omit_command_start}" omit_command)
    if(omit_command)
        if(RHI_OMIT_TARGET STREQUAL "engine")
            set(omit_replacement "add_library(engine STATIC)")
        else()
            set(omit_replacement "add_executable(${RHI_OMIT_TARGET})")
        endif()
        string(REPLACE "${omit_command}" "${omit_replacement}" engine_cmake_text
            "${engine_cmake_text}")
    endif()
endif()
foreach(required_source_path
        "${RHI_INTERNAL_HEADER}"
        "${RHI_SOURCE}"
        "${RHI_GL_SOURCE}"
        "${RHI_VK_SOURCE}"
        "${RHI_HEADLESS_SOURCE}"
        "${RHI_OWNERSHIP_SOURCE}"
        "${RHI_VALIDATION_SOURCE}"
        "${RHI_RESOURCES_SOURCE}"
        "${RHI_PRESENT_HISTORY_SOURCE}"
        "${RHI_RT_TRACE_SOURCE}")
    if(NOT EXISTS "${required_source_path}")
        message(FATAL_ERROR "RHI source contract input is missing: ${required_source_path}")
    endif()
endforeach()

# RHI core ownership: the five core sources stay in RHI_CORE_SOURCES.
extract_cmake_command("${engine_cmake_text}" "set(RHI_CORE_SOURCES" rhi_core_sources_block)
if(NOT rhi_core_sources_block)
    message(FATAL_ERROR "RHI core source ownership block is missing")
endif()
if(DEFINED RHI_OMIT_SOURCE)
    string(REPLACE "${RHI_OMIT_SOURCE}" "" engine_cmake_text "${engine_cmake_text}")
    extract_cmake_command("${engine_cmake_text}" "set(RHI_CORE_SOURCES" rhi_core_sources_block)
endif()
foreach(required_source
        "src/rhi/rhi.c"
        "src/rhi/rhi_ownership.c"
        "src/rhi/rhi_validation.c"
        "src/rhi/rhi_resources.c"
        "src/rhi/rhi_present_history.c")
    string(FIND "${rhi_core_sources_block}" "${required_source}" source_offset)
    if(source_offset EQUAL -1)
        message(FATAL_ERROR "RHI core source ownership missing: ${required_source}")
    endif()
endforeach()

# rhi.c must no longer unity-include a backend.
foreach(unity_token "#include <rhi/rhi_vk.c>" "#include <rhi/rhi_gl.c>")
    string(FIND "${rhi_text}" "${unity_token}" unity_offset)
    if(NOT unity_offset EQUAL -1)
        message(FATAL_ERROR "rhi.c must not unity-include a backend: ${unity_token}")
    endif()
endforeach()

# engine owns the core aggregate and no backend source.
extract_cmake_command("${engine_cmake_text}" "add_library(engine STATIC" engine_block)
if(NOT engine_block)
    message(FATAL_ERROR "engine source ownership target is missing")
endif()
string(FIND "${engine_block}" "RHI_CORE_SOURCES" engine_core_sources_offset)
if(engine_core_sources_offset EQUAL -1)
    message(FATAL_ERROR "engine must consume the complete RHI_CORE_SOURCES aggregate")
endif()
string(FIND "${engine_block}" "src/renderer/rt_trace.c" engine_rt_trace_offset)
if(engine_rt_trace_offset EQUAL -1)
    message(FATAL_ERROR "engine source ownership missing: src/renderer/rt_trace.c")
endif()
foreach(backend_source "src/rhi/rhi_gl.c" "src/rhi/rhi_vk.c" "src/rhi/rhi_headless.c"
        "src/rhi/rhi_metal.m" "src/rhi/rhi_d3d12.c")
    string(FIND "${engine_block}" "${backend_source}" engine_backend_offset)
    if(NOT engine_backend_offset EQUAL -1)
        message(FATAL_ERROR "engine must not own a backend source: ${backend_source}")
    endif()
endforeach()

# Each backend library owns exactly its own backend source.
foreach(backend_spec
        "engine_rhi_opengl|src/rhi/rhi_gl.c"
        "engine_rhi_vulkan|src/rhi/rhi_vk.c"
        "engine_rhi_headless|src/rhi/rhi_headless.c"
        "engine_rhi_metal|src/rhi/rhi_metal.m"
        "engine_rhi_d3d12|src/rhi/rhi_d3d12.c")
    string(REPLACE "|" ";" backend_parts "${backend_spec}")
    list(GET backend_parts 0 backend_target)
    list(GET backend_parts 1 backend_source)
    extract_cmake_command("${engine_cmake_text}"
        "add_library(${backend_target} STATIC" backend_block)
    if(NOT backend_block)
        message(FATAL_ERROR "RHI backend library is missing: ${backend_target}")
    endif()
    string(FIND "${backend_block}" "${backend_source}" own_offset)
    if(own_offset EQUAL -1)
        message(FATAL_ERROR
            "RHI backend library does not own its source: ${backend_target} ${backend_source}")
    endif()
    foreach(other_source "src/rhi/rhi_gl.c" "src/rhi/rhi_vk.c" "src/rhi/rhi_headless.c"
            "src/rhi/rhi_metal.m" "src/rhi/rhi_d3d12.c")
        if(NOT other_source STREQUAL backend_source)
            string(FIND "${backend_block}" "${other_source}" other_offset)
            if(NOT other_offset EQUAL -1)
                message(FATAL_ERROR
                    "RHI backend library owns a foreign backend source: ${backend_target} ${other_source}")
            endif()
        endif()
    endforeach()
endforeach()

# The selection helper must exist.
string(FIND "${engine_cmake_text}" "function(engine_link_rhi_backend" helper_offset)
if(helper_offset EQUAL -1)
    message(FATAL_ERROR "engine_link_rhi_backend helper is missing")
endif()

# Source-owning consumers keep their ownership; test_rhi_tlas_instance_encode
# must not pull the whole aggregate.
foreach(consumer_spec
        "engine|add_library(engine STATIC|RHI_CORE_SOURCES|src/core/log.c"
        "test_rhi_capabilities|add_executable(test_rhi_capabilities|RHI_CORE_SOURCES|tests/test_rhi_capabilities.c"
        "test_rhi_native|add_executable(test_rhi_native|RHI_CORE_SOURCES|tests/test_rhi_native.c"
        "test_rhi_tlas_instance_encode|add_executable(test_rhi_tlas_instance_encode|src/rhi/rhi_validation.c|tests/test_rhi_tlas_instance_encode.c"
        "test_rt_trace|add_executable(test_rt_trace|RHI_CORE_SOURCES|tests/test_rt_trace.c|src/renderer/rt_trace.c")
    string(REPLACE "|" ";" consumer_parts "${consumer_spec}")
    list(GET consumer_parts 0 consumer_name)
    list(GET consumer_parts 1 consumer_command)
    list(REMOVE_AT consumer_parts 0 1)
    extract_cmake_command("${engine_cmake_text}" "${consumer_command}" consumer_block)
    if(NOT consumer_block)
        message(FATAL_ERROR "RHI source ownership target is missing: ${consumer_name}")
    endif()
    foreach(required_consumer_source IN LISTS consumer_parts)
        string(FIND "${consumer_block}" "${required_consumer_source}" consumer_source_offset)
        if(consumer_source_offset EQUAL -1)
            message(FATAL_ERROR
                "RHI source ownership missing from ${consumer_name}: ${required_consumer_source}")
        endif()
    endforeach()
    if(consumer_name STREQUAL "test_rhi_tlas_instance_encode")
        string(FIND "${consumer_block}" "RHI_CORE_SOURCES" forbidden_core_sources_offset)
        if(NOT forbidden_core_sources_offset EQUAL -1)
            message(FATAL_ERROR
                "RHI source ownership unexpectedly shared with test_rhi_tlas_instance_encode")
        endif()
    endif()
endforeach()

# Direct RHI contract tests link exactly the headless backend and never the
# engine library (the word "engine" alone must not appear as a link item).
foreach(direct_rhi_target
        "test_rhi_capabilities"
        "test_rhi_native"
        "test_rt_trace"
        "test_rhi_error_contract"
        "test_rhi_frame_lifecycle_contract")
    extract_cmake_command("${engine_cmake_text}"
        "target_link_libraries(${direct_rhi_target}" direct_link_block)
    if(NOT direct_link_block)
        message(FATAL_ERROR
            "direct RHI test link ownership is missing: ${direct_rhi_target}")
    endif()
    string(FIND "${direct_link_block}" "engine_rhi_headless" headless_offset)
    if(headless_offset EQUAL -1)
        message(FATAL_ERROR
            "direct RHI test must link engine_rhi_headless: ${direct_rhi_target}")
    endif()
    if(direct_link_block MATCHES "(^|[ \t\r\n(])engine([ \t\r\n)])")
        message(FATAL_ERROR
            "direct RHI test must link its owned sources, not engine: ${direct_rhi_target}")
    endif()
endforeach()

# Every executable that links engine must select exactly one backend through
# the helper; no target link block may name two backend libraries.
foreach(rhi_consumer_target
        "engine_demo"
        "dxx_break"
        "test_vulkan"
        "test_engine_lifecycle"
        "test_platform_null_safety"
        "test_imgui_compat"
        "test_myui_break_pal"
        "test_platform_x11_runtime"
        "test_rhi_x11_runtime"
        "test_platform_wayland_runtime"
        "test_platform_win32_runtime"
        "test_platform_cocoa_runtime")
    string(FIND "${engine_cmake_text}"
        "engine_link_rhi_backend(${rhi_consumer_target})" helper_call_offset)
    if(helper_call_offset EQUAL -1)
        message(FATAL_ERROR
            "engine consumer must select a backend via the helper: ${rhi_consumer_target}")
    endif()
endforeach()
foreach(linked_target
        "engine_demo" "dxx_break" "test_vulkan" "test_engine_lifecycle"
        "test_platform_null_safety" "test_imgui_compat" "test_myui_break_pal"
        "test_platform_x11_runtime" "test_rhi_x11_runtime"
        "test_platform_wayland_runtime" "test_platform_win32_runtime"
        "test_platform_cocoa_runtime" "test_rhi_capabilities" "test_rhi_native"
        "test_rt_trace" "test_rhi_error_contract" "test_rhi_frame_lifecycle_contract")
    extract_cmake_command("${engine_cmake_text}"
        "target_link_libraries(${linked_target}" link_block)
    if(link_block)
        set(backend_link_count 0)
        foreach(backend_lib engine_rhi_opengl engine_rhi_vulkan engine_rhi_headless
                engine_rhi_metal engine_rhi_d3d12)
            string(FIND "${link_block}" "${backend_lib}" backend_lib_offset)
            if(NOT backend_lib_offset EQUAL -1)
                math(EXPR backend_link_count "${backend_link_count} + 1")
            endif()
        endforeach()
        if(backend_link_count GREATER 1)
            message(FATAL_ERROR
                "target links more than one RHI backend library: ${linked_target}")
        endif()
    endif()
endforeach()

# Plan D admitted d3d12: engine_rhi_d3d12 is a real backend library (covered by
# the ownership loops above), so no backend remains banned from the graph.

# Backend internal contract surface (unchanged).
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
