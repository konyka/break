foreach(required_var ENGINE_SOURCE_DIR WORK CLANG_CL ZIG_EXECUTABLE)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")
set(failures "")
set(common_args
    -DCMAKE_SYSTEM_NAME=Windows
    -DENGINE_ENABLE_WAYLAND=OFF
    -DENGINE_RHI_BACKEND=opengl
    -DENGINE_ENABLE_IPO=OFF
    -DENGINE_BUILD_TESTS=ON
    -DBREAK_ENABLE_SNOWFLAKE=OFF
    -DBREAK_ENABLE_CRYPTO=OFF
    -DBREAK_ENABLE_CRASH=OFF
    -DMYUI_PAL=dummy)

execute_process(
    COMMAND "${CMAKE_COMMAND}" -S "${ENGINE_SOURCE_DIR}" -B "${WORK}/msvc" -G Ninja
        ${common_args}
        "-DCMAKE_C_COMPILER=${CLANG_CL}" "-DCMAKE_CXX_COMPILER=${CLANG_CL}"
        -DCMAKE_C_COMPILER_WORKS=TRUE -DCMAKE_CXX_COMPILER_WORKS=TRUE
        -DCMAKE_C_ABI_COMPILED=TRUE -DCMAKE_CXX_ABI_COMPILED=TRUE
    RESULT_VARIABLE msvc_rc OUTPUT_VARIABLE msvc_out ERROR_VARIABLE msvc_err)
if(NOT msvc_rc EQUAL 0)
    string(APPEND failures "clang-cl configure failed\n${msvc_out}${msvc_err}\n")
else()
    file(READ "${WORK}/msvc/compile_commands.json" commands)
    string(REGEX MATCH "\"command\"[^\n]*test_public_api_cpp20.cpp[^\n]*" public_command "${commands}")
    if(NOT public_command)
        string(APPEND failures "public C++20 compile command is missing\n")
    else()
        string(FIND "${public_command}" "/Zc:__cplusplus" flag_offset)
        if(flag_offset EQUAL -1)
            string(APPEND failures "MSVC C++20 command lacks /Zc:__cplusplus\n${public_command}\n")
        endif()
    endif()
endif()

set(zig_cc "${WORK}/zig-cc.sh")
set(zig_cxx "${WORK}/zig-cxx.sh")
set(zig_ar "${WORK}/zig-ar.sh")
set(zig_ranlib "${WORK}/zig-ranlib.sh")
file(WRITE "${zig_cc}" "#!/usr/bin/env bash\nexec \"${ZIG_EXECUTABLE}\" cc -target x86_64-windows-gnu \"$@\"\n")
file(WRITE "${zig_cxx}" "#!/usr/bin/env bash\nexec \"${ZIG_EXECUTABLE}\" c++ -target x86_64-windows-gnu \"$@\"\n")
file(WRITE "${zig_ar}" "#!/usr/bin/env bash\nexec \"${ZIG_EXECUTABLE}\" ar \"$@\"\n")
file(WRITE "${zig_ranlib}" "#!/usr/bin/env bash\nexec \"${ZIG_EXECUTABLE}\" ranlib \"$@\"\n")
file(CHMOD "${zig_cc}" "${zig_cxx}" "${zig_ar}" "${zig_ranlib}" PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

execute_process(
    COMMAND "${CMAKE_COMMAND}" -S "${ENGINE_SOURCE_DIR}" -B "${WORK}/mingw" -G Ninja
        ${common_args}
        "-DCMAKE_C_COMPILER=${zig_cc}" "-DCMAKE_CXX_COMPILER=${zig_cxx}"
        "-DCMAKE_AR=${zig_ar}" "-DCMAKE_RANLIB=${zig_ranlib}"
        -DCMAKE_BUILD_TYPE=Debug
    RESULT_VARIABLE mingw_rc OUTPUT_VARIABLE mingw_out ERROR_VARIABLE mingw_err)
if(NOT mingw_rc EQUAL 0)
    string(APPEND failures "Windows GNU configure failed\n${mingw_out}${mingw_err}\n")
else()
    execute_process(
        COMMAND "${CMAKE_COMMAND}" --build "${WORK}/mingw"
            --target test_glad_wgl_loader -j3
        RESULT_VARIABLE build_rc OUTPUT_VARIABLE build_out ERROR_VARIABLE build_err)
    if(NOT build_rc EQUAL 0)
        string(APPEND failures "Windows GNU WGL loader build failed\n${build_out}${build_err}\n")
    else()
        find_program(NM_EXECUTABLE NAMES llvm-nm nm PATHS /usr/bin /usr/local/bin)
        if(NOT NM_EXECUTABLE)
            string(APPEND failures "nm is required to verify the Windows mock symbols\n")
        else()
            execute_process(
                COMMAND "${NM_EXECUTABLE}"
                    "${WORK}/mingw/CMakeFiles/test_glad_wgl_loader.dir/tests/test_glad_wgl_loader.c.obj"
                RESULT_VARIABLE nm_rc OUTPUT_VARIABLE nm_out ERROR_VARIABLE nm_err)
            if(NOT nm_rc EQUAL 0)
                string(APPEND failures "could not inspect Windows WGL loader symbols\n${nm_out}${nm_err}\n")
            endif()
            foreach(mock_symbol LoadLibraryW GetProcAddress FreeLibrary)
                string(REGEX MATCH "[0-9A-Fa-f]+ T ${mock_symbol}" defined_symbol "${nm_out}")
                if(defined_symbol)
                    string(APPEND failures
                        "Windows system API is redefined by the test: ${defined_symbol}\n")
                endif()
            endforeach()
        endif()
    endif()
endif()

if(failures)
    message(FATAL_ERROR "remote Windows toolchain contract failed:\n${failures}")
endif()
message(STATUS "remote Windows toolchain contract OK")
