if(POLICY CMP0140)
    cmake_policy(SET CMP0140 NEW)
endif()

if(NOT WIN32)
    message(STATUS "D3D12 dependency gate: UNAVAILABLE (non-Windows host)")
    cmake_language(EXIT 77)
endif()

set(_sdk_root "$ENV{WindowsSdkDir}")
set(_sdk_version "$ENV{WindowsSDKVersion}")
if(NOT _sdk_root OR NOT _sdk_version)
    set(_sdk_root "C:/Program Files (x86)/Windows Kits/10")
    file(GLOB _sdk_include_candidates LIST_DIRECTORIES true
        "${_sdk_root}/Include/*")
    set(_sdk_versions)
    foreach(_candidate IN LISTS _sdk_include_candidates)
        get_filename_component(_candidate_version "${_candidate}" NAME)
        if(_candidate_version MATCHES "^[0-9]+(\\.[0-9]+)+$")
            if(IS_DIRECTORY "${_sdk_root}/Lib/${_candidate_version}")
                list(APPEND _sdk_versions "${_candidate_version}")
            endif()
        endif()
    endforeach()
    list(SORT _sdk_versions COMPARE NATURAL ORDER DESCENDING)
    list(LENGTH _sdk_versions _sdk_version_count)
    if(_sdk_version_count GREATER 0)
        list(GET _sdk_versions 0 _sdk_version)
    endif()
    # Plan D: prefer the pinned SDK when it is installed alongside newer ones.
    list(FIND _sdk_versions "10.0.26100.0" _pinned_idx)
    if(NOT _pinned_idx EQUAL -1)
        set(_sdk_version "10.0.26100.0")
    endif()
endif()
# Plan D: SDK version pin. A machine with a different Windows SDK is
# UNAVAILABLE for the d3d12 lane, never silently re-pinned.
if(NOT _sdk_version STREQUAL "10.0.26100.0")
    message(STATUS "D3D12 dependency gate: UNAVAILABLE (Windows SDK '${_sdk_version}' != pinned 10.0.26100.0)")
    cmake_language(EXIT 77)
endif()
set(_sdk_include "${_sdk_root}/Include/${_sdk_version}")
set(_sdk_lib "${_sdk_root}/Lib/${_sdk_version}")
set(_sdk_um_lib "${_sdk_lib}/um/x64")
set(_sdk_ucrt_lib "${_sdk_lib}/ucrt/x64")
find_path(D3D12_INCLUDE_DIR d3d12.h
    PATHS "${_sdk_include}/um"
    NO_DEFAULT_PATH)
find_path(DXGI_INCLUDE_DIR NAMES dxgi.h dxgi1_4.h dxgi1_6.h
    PATHS "${_sdk_include}/shared" "${_sdk_include}/um"
    NO_DEFAULT_PATH)
find_library(D3D12_LIBRARY NAMES d3d12
    PATHS "${_sdk_lib}" "$ENV{WindowsSdkDir}/Lib"
    PATH_SUFFIXES um/x64 um
    NO_DEFAULT_PATH)
find_library(DXGI_LIBRARY NAMES dxgi
    PATHS "${_sdk_lib}" "$ENV{WindowsSdkDir}/Lib"
    PATH_SUFFIXES um/x64 um
    NO_DEFAULT_PATH)
find_program(DXC_EXECUTABLE NAMES dxc dxc.exe)
find_program(D3D12_PROBE_COMPILER NAMES cl clang-cl)
find_program(D3D12_PROBE_NINJA NAMES ninja ninja.exe)
find_program(D3D12_PROBE_LINKER NAMES lld-link lld-link.exe)

if(NOT D3D12_INCLUDE_DIR OR NOT DXGI_INCLUDE_DIR)
    message(STATUS "D3D12 dependency gate: UNAVAILABLE (headers incomplete)")
elseif(NOT D3D12_LIBRARY OR NOT DXGI_LIBRARY)
    message(STATUS "D3D12 dependency gate: UNAVAILABLE (libraries incomplete)")
elseif(NOT DXC_EXECUTABLE)
    message(STATUS "D3D12 dependency gate: UNAVAILABLE (DXC not found)")
elseif(NOT D3D12_PROBE_COMPILER)
    message(STATUS "D3D12 dependency gate: UNAVAILABLE (C/C++ compiler not found)")
elseif(NOT D3D12_PROBE_NINJA)
    message(STATUS "D3D12 dependency gate: UNAVAILABLE (Ninja not found)")
elseif(NOT D3D12_PROBE_LINKER)
    message(STATUS "D3D12 dependency gate: UNAVAILABLE (Windows linker not found)")
else()
    if(D3D12_DEPENDENCY_PROBE_DIR)
        set(_probe_dir "${D3D12_DEPENDENCY_PROBE_DIR}")
    else()
        set(_probe_dir "${CMAKE_CURRENT_BINARY_DIR}/d3d12-dependency-probe")
    endif()
    file(REMOVE_RECURSE "${_probe_dir}")
    file(MAKE_DIRECTORY "${_probe_dir}")
    file(WRITE "${_probe_dir}/toolchain.cmake"
        "set(CMAKE_C_COMPILER [=[${D3D12_PROBE_COMPILER}]=])\n"
        "set(CMAKE_LINKER [=[${D3D12_PROBE_LINKER}]=])\n"
        "set(CMAKE_EXE_LINKER_FLAGS_INIT [=[/nodefaultlib /entry:main /subsystem:console]=])\n"
        "set(ENV{INCLUDE} [=[${_sdk_include}/um;${_sdk_include}/shared]=])\n"
        "set(ENV{LIB} [=[${_sdk_um_lib};${_sdk_ucrt_lib}]=])\n")
    file(WRITE "${_probe_dir}/CMakeLists.txt"
        "cmake_minimum_required(VERSION 3.20)\n"
        "project(d3d12_dependency_probe C)\n"
        "add_executable(d3d12_dependency_probe main.c)\n"
        "set_target_properties(d3d12_dependency_probe PROPERTIES LINKER_LANGUAGE C)\n"
        "target_include_directories(d3d12_dependency_probe PRIVATE [=[${_sdk_include}/shared]=] [=[${_sdk_include}/um]=] [=[${_sdk_include}/winrt]=])\n"
        "target_link_options(d3d12_dependency_probe PRIVATE /nodefaultlib /entry:main /subsystem:console)\n"
        "target_link_libraries(d3d12_dependency_probe PRIVATE [=[${D3D12_LIBRARY}]=] [=[${DXGI_LIBRARY}]=] kernel32.lib)\n")
    file(WRITE "${_probe_dir}/main.c"
        "#include <d3d12.h>\n"
        "#include <dxgi1_4.h>\n"
        "int main(void) { return 0; }\n")
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -S "${_probe_dir}" -B "${_probe_dir}/build"
            -G Ninja
            -DCMAKE_BUILD_TYPE=Release
            -DCMAKE_C_COMPILER_WORKS=TRUE
            -DCMAKE_C_ABI_COMPILED=TRUE
            -DCMAKE_MAKE_PROGRAM:FILEPATH=${D3D12_PROBE_NINJA}
            -DCMAKE_TOOLCHAIN_FILE:FILEPATH=${_probe_dir}/toolchain.cmake
        RESULT_VARIABLE _configure_result
        OUTPUT_VARIABLE _configure_output
        ERROR_VARIABLE _configure_error)
    if(_configure_result EQUAL 0)
        execute_process(
            COMMAND "${CMAKE_COMMAND}" --build "${_probe_dir}/build" --config Release
            RESULT_VARIABLE _build_result
            OUTPUT_VARIABLE _build_output
            ERROR_VARIABLE _build_error)
    else()
        set(_build_result 1)
    endif()
    file(REMOVE_RECURSE "${_probe_dir}")
    if(NOT _configure_result EQUAL 0 OR NOT _build_result EQUAL 0)
        message(STATUS "D3D12 dependency gate: UNAVAILABLE (compile/link probe failed)")
        cmake_language(EXIT 77)
    endif()
    message(STATUS "D3D12 dependency gate: COMPILE_DEPENDENCIES_AVAILABLE")
    return()
endif()

message(STATUS "  d3d12_include=${D3D12_INCLUDE_DIR}")
message(STATUS "  dxgi_include=${DXGI_INCLUDE_DIR}")
message(STATUS "  d3d12_library=${D3D12_LIBRARY}")
message(STATUS "  dxgi_library=${DXGI_LIBRARY}")
message(STATUS "  dxc=${DXC_EXECUTABLE}")
cmake_language(EXIT 77)
