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
if(NOT EXISTS "${RHI_OWNERSHIP_SOURCE}")
    message(FATAL_ERROR "RHI ownership source is missing: ${RHI_OWNERSHIP_SOURCE}")
endif()
if(NOT EXISTS "${RHI_VALIDATION_SOURCE}")
    message(FATAL_ERROR "RHI validation source is missing: ${RHI_VALIDATION_SOURCE}")
endif()
if(NOT EXISTS "${RHI_RESOURCES_SOURCE}")
    message(FATAL_ERROR "RHI resources source is missing: ${RHI_RESOURCES_SOURCE}")
endif()

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

foreach(required_source_path
        "${RHI_INTERNAL_HEADER}"
        "${RHI_SOURCE}"
        "${RHI_GL_SOURCE}"
        "${RHI_VK_SOURCE}"
        "${RHI_OWNERSHIP_SOURCE}"
        "${RHI_VALIDATION_SOURCE}"
        "${RHI_RESOURCES_SOURCE}"
        "${RHI_PRESENT_HISTORY_SOURCE}"
        "${RHI_RT_TRACE_SOURCE}")
    if(NOT EXISTS "${required_source_path}")
        message(FATAL_ERROR "RHI source contract input is missing: ${required_source_path}")
    endif()
endforeach()

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

foreach(direct_rhi_target
        "test_rhi_capabilities"
        "test_rhi_native"
        "test_rt_trace")
    extract_cmake_command("${engine_cmake_text}"
        "target_link_libraries(${direct_rhi_target}" direct_link_block)
    if(NOT direct_link_block)
        message(FATAL_ERROR
            "direct RHI test link ownership is missing: ${direct_rhi_target}")
    endif()
    string(FIND "${direct_link_block}" "engine" direct_engine_link_offset)
    if(NOT direct_engine_link_offset EQUAL -1)
        message(FATAL_ERROR
            "direct RHI test must link its owned sources, not engine: ${direct_rhi_target}")
    endif()
endforeach()

extract_cmake_command("${engine_cmake_text}" "add_library(engine STATIC" engine_block)
if(NOT engine_block)
    message(FATAL_ERROR "engine source ownership target is missing")
endif()
foreach(required_engine_text
        "src/renderer/rt_trace.c"
        "src/rhi/rhi_gl.c"
        "src/rhi/rhi_vk.c")
    string(FIND "${engine_block}" "${required_engine_text}" engine_source_offset)
    if(required_engine_text STREQUAL "src/rhi/rhi_gl.c" OR
       required_engine_text STREQUAL "src/rhi/rhi_vk.c")
        if(NOT engine_source_offset EQUAL -1)
            message(FATAL_ERROR
                "backend source must remain owned by rhi.c unity inclusion: ${required_engine_text}")
        endif()
    elseif(engine_source_offset EQUAL -1)
        message(FATAL_ERROR "engine source ownership missing: ${required_engine_text}")
    endif()
endforeach()
string(FIND "${engine_block}" "RHI_CORE_SOURCES" engine_core_sources_offset)
if(engine_core_sources_offset EQUAL -1)
    message(FATAL_ERROR "engine must consume the complete RHI_CORE_SOURCES aggregate")
endif()

foreach(future_backend_token
        "rhi_metal.c" "ENGINE_RHI_BACKEND_METAL"
        "ENGINE_RHI_BACKEND_D3D12")
    string(FIND "${engine_cmake_text}" "${future_backend_token}" future_backend_offset)
    if(NOT future_backend_offset EQUAL -1)
        message(FATAL_ERROR
            "future backend is represented in current source ownership graph: ${future_backend_token}")
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
