if(NOT WIN32)
    message(STATUS "D3D12 shader compile gate: UNAVAILABLE (non-Windows host)")
    return()
endif()

find_program(DXC_EXECUTABLE NAMES dxc dxc.exe)
if(NOT DXC_EXECUTABLE)
    message(STATUS "D3D12 shader compile gate: UNAVAILABLE (DXC not found)")
    return(77)
endif()

set(shader_source "${CMAKE_CURRENT_BINARY_DIR}/d3d12_shader_gate.hlsl")
set(shader_output "${CMAKE_CURRENT_BINARY_DIR}/d3d12_shader_gate.dxil")
file(WRITE "${shader_source}"
    "struct VSOut { float4 pos : SV_Position; };\n"
    "VSOut main(float3 pos : POSITION) {\n"
    "  VSOut o; o.pos = float4(pos, 1.0); return o;\n"
    "}\n")

execute_process(
    COMMAND "${DXC_EXECUTABLE}" -T vs_6_0 -E main -Fo "${shader_output}"
            "${shader_source}"
    RESULT_VARIABLE dxc_result
    OUTPUT_VARIABLE dxc_stdout
    ERROR_VARIABLE dxc_stderr)
if(NOT dxc_result EQUAL 0)
    message(FATAL_ERROR
        "D3D12 shader compile gate failed (DXC=${DXC_EXECUTABLE})\n"
        "stdout=${dxc_stdout}\nstderr=${dxc_stderr}")
endif()
if(NOT EXISTS "${shader_output}")
    message(FATAL_ERROR "D3D12 shader compile gate produced no DXIL output")
endif()
message(STATUS "D3D12 shader compile gate: COMPILE_PASS (DXC=${DXC_EXECUTABLE})")
