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

execute_process(
    COMMAND "${ZIG_EXECUTABLE}" env
    RESULT_VARIABLE zig_env_rc OUTPUT_VARIABLE zig_env ERROR_VARIABLE zig_env_err)
string(REGEX MATCH "\\.lib_dir = \"([^\"]+)\"" zig_lib_dir_match "${zig_env}")
set(zig_lib_dir "${CMAKE_MATCH_1}")
if(NOT zig_env_rc EQUAL 0 OR
        NOT EXISTS "${zig_lib_dir}/libc/include/any-windows-any/windows.h")
    string(APPEND failures "could not locate Zig Windows headers\n${zig_env}${zig_env_err}\n")
else()
    execute_process(
        COMMAND "${ZIG_EXECUTABLE}" clang --driver-mode=cl -target x86_64-windows-gnu
            /nologo /W4 /WX
            /clang:-Wno-pragma-pack /clang:-Wno-missing-declarations
            /clang:-Wno-unused-function
            -D_WIN32=1
            "-I${ENGINE_SOURCE_DIR}/external"
            "-I${zig_lib_dir}/include"
            "-I${zig_lib_dir}/libc/include/any-windows-any"
            /c "${ENGINE_SOURCE_DIR}/tests/test_glad_wgl_loader.c"
            "-Fo${WORK}/msvc/test_glad_wgl_loader.clang-cl.obj"
        RESULT_VARIABLE msvc_build_rc OUTPUT_VARIABLE msvc_build_out
        ERROR_VARIABLE msvc_build_err)
    if(NOT msvc_build_rc EQUAL 0)
        string(APPEND failures
            "MSVC-compatible WGL loader compile failed\n${msvc_build_out}${msvc_build_err}\n")
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
        execute_process(
            COMMAND "${zig_cc}"
                -D_CRT_SECURE_NO_WARNINGS -D_WIN32=1
                "-I${ENGINE_SOURCE_DIR}/external"
                -g -std=c11 -Wall -Wextra -Werror -pedantic -Wno-pedantic
                -Werror=cast-function-type
                -c "${ENGINE_SOURCE_DIR}/tests/test_glad_wgl_loader.c"
                -o "${WORK}/mingw/test_glad_wgl_loader.strict.obj"
            RESULT_VARIABLE strict_build_rc OUTPUT_VARIABLE strict_build_out
            ERROR_VARIABLE strict_build_err)
        if(NOT strict_build_rc EQUAL 0)
            string(APPEND failures
                "Windows GNU strict WGL test compile failed\n${strict_build_out}${strict_build_err}\n")
        endif()
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

if(EXISTS "${WORK}/mingw/CTestTestfile.cmake")
    file(READ "${WORK}/mingw/CTestTestfile.cmake" mingw_ctest)
    string(REGEX MATCH
        "set_tests_properties\\([^\n]*test_glad_wgl_loader[^\n]*SKIP_RETURN_CODE \"77\""
        wgl_skip_property "${mingw_ctest}")
    if(NOT wgl_skip_property)
        string(APPEND failures "Windows WGL loader lacks SKIP_RETURN_CODE 77\n")
    endif()
endif()

file(READ "${ENGINE_SOURCE_DIR}/tests/test_glad_wgl_loader.c" wgl_test_source)
foreach(required_lifecycle RegisterClassExW CreateWindowExW GetDC ChoosePixelFormat
        SetPixelFormat wglCreateContext wglDeleteContext ReleaseDC DestroyWindow UnregisterClassW)
    string(FIND "${wgl_test_source}" "${required_lifecycle}" lifecycle_offset)
    if(lifecycle_offset EQUAL -1)
        string(APPEND failures "native WGL lifecycle is missing ${required_lifecycle}\n")
    endif()
endforeach()
string(FIND "${wgl_test_source}" "wglMakeCurrent(dc, context)" make_current_offset)
string(FIND "${wgl_test_source}" "gladLoadGL()" load_gl_offset)
if(make_current_offset EQUAL -1 OR load_gl_offset EQUAL -1 OR
        make_current_offset GREATER load_gl_offset)
    string(APPEND failures "a real WGL context is not made current before gladLoadGL\n")
endif()
string(FIND "${wgl_test_source}" "wglMakeCurrent(NULL, NULL)" clear_current_offset)
if(clear_current_offset EQUAL -1 OR clear_current_offset LESS load_gl_offset)
    string(APPEND failures "WGL context is not released after gladLoadGL\n")
endif()

string(FIND "${wgl_test_source}" "#ifndef TEST_WGL_LOADER_SIMULATED" native_start)
string(FIND "${wgl_test_source}" "int main(void)" native_end)
if(native_start EQUAL -1 OR native_end EQUAL -1 OR native_start GREATER native_end)
    string(APPEND failures "native WGL test branch is missing\n")
else()
    math(EXPR native_length "${native_end} - ${native_start}")
    string(SUBSTRING "${wgl_test_source}" ${native_start} ${native_length} native_source)
    foreach(required_modern wglCreateContextAttribsARB WGL_CONTEXT_MAJOR_VERSION_ARB
            WGL_CONTEXT_MINOR_VERSION_ARB WGL_CONTEXT_CORE_PROFILE_BIT_ARB
            modern_context GL_NUM_EXTENSIONS GL_RENDERER)
        string(FIND "${native_source}" "${required_modern}" modern_offset)
        if(modern_offset EQUAL -1)
            string(APPEND failures "native modern WGL path is missing ${required_modern}\n")
        endif()
    endforeach()
    string(REGEX MATCHALL "gladLoadGL\\(\\)" native_loads "${native_source}")
    list(LENGTH native_loads native_load_count)
    if(NOT native_load_count EQUAL 2)
        string(APPEND failures
            "native WGL test must load both bootstrap and modern contexts\n")
    endif()
    string(REGEX MATCH "if \\(failures == 0 && !modern_context_supported\\)"
        capability_gate "${native_source}")
    if(NOT capability_gate)
        string(APPEND failures "native WGL capability skip is not gated on valid legacy checks\n")
    endif()
    string(FIND "${native_source}" "return 77;" native_skip_return)
    string(FIND "${native_source}" "SKIP:" native_skip_diagnostic)
    if(native_skip_return EQUAL -1 OR native_skip_diagnostic EQUAL -1)
        string(APPEND failures "native WGL capability skip lacks exit 77 or diagnostics\n")
    endif()
    foreach(required_modern_check "glad_glCreateShader != NULL" "glad_glGetStringi != NULL")
        string(FIND "${native_source}" "${required_modern_check}" modern_check_offset)
        if(modern_check_offset EQUAL -1)
            string(APPEND failures "native modern context check is missing ${required_modern_check}\n")
        endif()
    endforeach()
endif()

if(failures)
    message(FATAL_ERROR "remote Windows toolchain contract failed:\n${failures}")
endif()
message(STATUS "remote Windows toolchain contract OK")
