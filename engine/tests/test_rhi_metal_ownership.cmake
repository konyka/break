cmake_policy(SET CMP0054 NEW)

# engine_rhi_metal 所有权契约：metal 后端源恰被 engine_rhi_metal 拥有；
# engine 核心库不得直接包含 rhi_metal.m；helper 必须有 metal 分发分支。
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

file(READ "${ENGINE_CMAKE}" cmake_text)
string(REGEX REPLACE "#[^\r\n]*" "" cmake_text "${cmake_text}")
foreach(required_text
        "add_library(engine_rhi_metal STATIC"
        "src/rhi/rhi_metal.m"
        "ENGINE_RHI_BACKEND_METAL=1"
        "-framework Metal"
        "-framework QuartzCore"
        "-framework Foundation"
        "ENGINE_RHI_BACKEND_EFFECTIVE STREQUAL \"metal\""
        "target_link_libraries(\${target} PRIVATE engine_rhi_metal)")
    string(FIND "${cmake_text}" "${required_text}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "metal backend ownership contract missing: ${required_text}")
    endif()
endforeach()

# 反向断言：engine 库的 add_library 块内不得出现 rhi_metal.m（后端独立成库）。
extract_cmake_command("${cmake_text}" "add_library(engine STATIC" engine_block)
if(NOT engine_block)
    message(FATAL_ERROR "metal ownership contract: engine target block is missing")
endif()
string(FIND "${engine_block}" "src/rhi/rhi_metal.m" metal_in_engine_offset)
if(NOT metal_in_engine_offset EQUAL -1)
    message(FATAL_ERROR
        "engine must not own the metal backend source: src/rhi/rhi_metal.m")
endif()

# engine_rhi_metal 块不得夹带其他后端源。
extract_cmake_command("${cmake_text}" "add_library(engine_rhi_metal STATIC" metal_block)
if(NOT metal_block)
    message(FATAL_ERROR "metal ownership contract: engine_rhi_metal target block is missing")
endif()
foreach(foreign_source
        "src/rhi/rhi_gl.c" "src/rhi/rhi_vk.c" "src/rhi/rhi_headless.c")
    string(FIND "${metal_block}" "${foreign_source}" foreign_offset)
    if(NOT foreign_offset EQUAL -1)
        message(FATAL_ERROR
            "engine_rhi_metal owns a foreign backend source: ${foreign_source}")
    endif()
endforeach()
