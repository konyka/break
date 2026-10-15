if(NOT WIN32)
    message(STATUS "D3D12 shader compile gate: UNAVAILABLE (non-Windows host)")
    return()
endif()

get_filename_component(GATE_SOURCE_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
set(SDK_DXC "${GATE_SOURCE_DIR}/../external/VulkanSDK/Bin/dxc.exe")
if(EXISTS "${SDK_DXC}")
    set(DXC_EXECUTABLE "${SDK_DXC}")
else()
    find_program(DXC_EXECUTABLE NAMES dxc dxc.exe)
endif()
if(NOT DXC_EXECUTABLE)
    message(STATUS "D3D12 shader compile gate: UNAVAILABLE (DXC not found)")
    # cmake -P 顶层 return(77) 在 CMP0140 OLD 下只告警不中止（参数被忽略），
    # 执行会穿透到下面的 FATAL_ERROR；cmake_language(EXIT) 才真正以 77 退出，
    # 让 ctest 的 SKIP_RETURN_CODE 生效。
    cmake_language(EXIT 77)
endif()

if(NOT DEFINED CMAKE_CURRENT_BINARY_DIR)
    message(FATAL_ERROR "D3D12 shader compile gate requires CMAKE_CURRENT_BINARY_DIR")
endif()

set(gate_dir "${CMAKE_CURRENT_BINARY_DIR}/d3d12-shader-compile-gate")
set(include_dir "${gate_dir}/includes")
file(REMOVE_RECURSE "${gate_dir}")
file(MAKE_DIRECTORY "${include_dir}")

execute_process(
    COMMAND "${DXC_EXECUTABLE}" --version
    RESULT_VARIABLE version_result
    OUTPUT_VARIABLE compiler_identity
    ERROR_VARIABLE version_stderr
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE)
if(NOT version_result EQUAL 0 OR compiler_identity STREQUAL "")
    file(REMOVE_RECURSE "${gate_dir}")
    message(FATAL_ERROR
        "D3D12 shader compile gate could not identify DXC\n"
        "DXC=${DXC_EXECUTABLE}\nresult=${version_result}\n"
        "stderr=${version_stderr}")
endif()

file(WRITE "${include_dir}/shader_gate.inc.hlsl"
    "float4 gate_color() { return float4(1.0, 0.0, 0.0, 1.0); }\n")
file(WRITE "${gate_dir}/valid.hlsl"
    "#include \"shader_gate.inc.hlsl\"\n"
    "struct VSOut { float4 pos : SV_Position; float4 color : COLOR0; };\n"
    "VSOut main(float3 pos : POSITION) {\n"
    "  VSOut o; o.pos = float4(pos, 1.0); o.color = gate_color(); return o;\n"
    "}\n")
file(WRITE "${gate_dir}/invalid.hlsl"
    "float4 main( : SV_Position { return 0; }\n")
file(WRITE "${gate_dir}/missing-include.hlsl"
    "#include \"not-present.hlsl\"\n"
    "float4 main(float4 pos : POSITION) : SV_Position { return pos; }\n")

function(run_shader_case case_name source_file output_file expected_success)
    if(expected_success)
        file(REMOVE "${output_file}")
    else()
        file(WRITE "${output_file}" "stale output must never be accepted")
    endif()
    execute_process(
        COMMAND "${DXC_EXECUTABLE}" -T vs_6_0 -E main -I "${include_dir}"
                -Fo "${output_file}" "${source_file}"
        RESULT_VARIABLE case_result
        OUTPUT_VARIABLE case_stdout
        ERROR_VARIABLE case_stderr
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_STRIP_TRAILING_WHITESPACE)
    set(case_diagnostics "${case_stdout}\n${case_stderr}")
    if(EXISTS "${output_file}")
        file(SIZE "${output_file}" case_size)
        set(case_output_exists TRUE)
    else()
        set(case_size 0)
        set(case_output_exists FALSE)
    endif()
    if(NOT expected_success AND case_output_exists)
        file(REMOVE "${output_file}")
        set(case_output_exists FALSE)
    endif()

    if(expected_success)
        if(NOT case_result EQUAL 0 OR NOT EXISTS "${output_file}" OR case_size LESS 1)
            set(case_failure
                "${case_name}: expected successful status and non-empty output; result=${case_result}; size=${case_size}; diagnostics=${case_diagnostics}")
        endif()
    elseif(case_result EQUAL 0 OR case_output_exists OR case_diagnostics STREQUAL "")
        set(case_failure
            "${case_name}: expected failure status, no output, and diagnostics; result=${case_result}; output_exists=${case_output_exists}; diagnostics=${case_diagnostics}")
    endif()
    set(${case_name}_result "${case_result}" PARENT_SCOPE)
    set(${case_name}_diagnostics "${case_diagnostics}" PARENT_SCOPE)
    set(${case_name}_output_exists "${case_output_exists}" PARENT_SCOPE)
    set(${case_name}_failure "${case_failure}" PARENT_SCOPE)
endfunction()

run_shader_case(valid "${gate_dir}/valid.hlsl" "${gate_dir}/valid.dxil" TRUE)
run_shader_case(invalid "${gate_dir}/invalid.hlsl" "${gate_dir}/invalid.dxil" FALSE)
run_shader_case(missing_include "${gate_dir}/missing-include.hlsl" "${gate_dir}/missing-include.dxil" FALSE)

set(gate_failures "")
foreach(case_name valid invalid missing_include)
    if(${case_name}_failure)
        string(APPEND gate_failures "\n${${case_name}_failure}")
    endif()
endforeach()
file(REMOVE_RECURSE "${gate_dir}")

if(gate_failures)
    message(FATAL_ERROR
        "D3D12 shader compile gate failed:${gate_failures}\n"
        "DXC=${DXC_EXECUTABLE}\nprofile=vs_6_0\nidentity=${compiler_identity}")
endif()

message(STATUS "D3D12 shader compile gate: COMPILE_PASS")
message(STATUS "  DXC=${DXC_EXECUTABLE}")
message(STATUS "  profile=vs_6_0")
message(STATUS "  identity=${compiler_identity}")
message(STATUS "  include_dir=${include_dir}")
message(STATUS "  valid=status=0 output=non-empty include=resolved")
message(STATUS "  invalid=status=non-zero output=absent diagnostics=present")
message(STATUS "  missing_include=status=non-zero output=absent diagnostics=present")
