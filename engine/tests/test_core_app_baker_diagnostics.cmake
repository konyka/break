foreach(var ENGINE_SOURCE_DIR CORE_APP_ASSET_BAKE CORE_APP_ASSET_TEST
        CORE_APP_ASSET_LAUNCH_TEST CORE_APP_MISSING_BAKER WORK)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

set_property(GLOBAL PROPERTY CORE_APP_DIAGNOSTIC_ERRORS "")

function(record_error text)
    string(LENGTH "${text}" length)
    if(length GREATER 1000)
        string(SUBSTRING "${text}" 0 1000 text)
        string(APPEND text " ... [truncated]")
    endif()
    get_property(errors GLOBAL PROPERTY CORE_APP_DIAGNOSTIC_ERRORS)
    string(APPEND errors "${text}\n")
    set_property(GLOBAL PROPERTY CORE_APP_DIAGNOSTIC_ERRORS "${errors}")
endfunction()

function(expect_contains text needle label)
    string(FIND "${text}" "${needle}" position)
    if(position LESS 0)
        record_error("${label}: missing '${needle}'; output=${text}")
    endif()
endfunction()

function(expect_not_contains text needle label)
    string(FIND "${text}" "${needle}" position)
    if(NOT position LESS 0)
        record_error("${label}: unexpected '${needle}'; output=${text}")
    endif()
endfunction()

function(expect_match text pattern label)
    if(NOT "${text}" MATCHES "${pattern}")
        record_error("${label}: missing /${pattern}/; output=${text}")
    endif()
endfunction()

function(run_process name expected_rc)
    execute_process(
        COMMAND ${ARGN}
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err
        TIMEOUT 30)
    set(output "${out}${err}")
    if(NOT "${rc}" STREQUAL "${expected_rc}")
        record_error("${name}: exit=${rc}, want=${expected_rc}; output=${output}")
    endif()
    set(CORE_APP_DIAGNOSTIC_OUTPUT "${output}" PARENT_SCOPE)
endfunction()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")

run_process(normal_baker 0 "${CORE_APP_ASSET_BAKE}" --output "${WORK}/normal")
expect_not_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}" "FAIL: CORE_APP_BAKE"
    "normal baker remains quiet")
foreach(asset level.bscn level.fg actors.sidecar director.lua player.lua broken.lua
        level.banm tone.wav deterministic.scenario load_unload.scenario rollback.scenario)
    if(NOT EXISTS "${WORK}/normal/${asset}")
        record_error("normal baker: missing ${asset}")
    endif()
endforeach()

file(WRITE "${WORK}/blocked-parent" "not a directory\n")
run_process(impossible_parent 1 "${CORE_APP_ASSET_BAKE}" --output
    "${WORK}/blocked-parent/child")
expect_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}"
    "FAIL: CORE_APP_BAKE stage=prepare step=prepare.platform_mkdir path=${WORK}/blocked-parent/child raw=0 "
    "output preparation diagnostic")
if(WIN32)
    expect_match("${CORE_APP_DIAGNOSTIC_OUTPUT}"
        "step=prepare.platform_mkdir[^\n]*os_error=[1-9][0-9]* errno=[0-9]+"
        "output preparation Win32 error")
else()
    expect_match("${CORE_APP_DIAGNOSTIC_OUTPUT}"
        "step=prepare.platform_mkdir[^\n]*os_error=0 errno=[1-9][0-9]*"
        "output preparation POSIX errno")
endif()

file(MAKE_DIRECTORY "${WORK}/scene-save/.level.bscn.bake-tmp")
run_process(scene_save_failure 1 "${CORE_APP_ASSET_BAKE}" --output
    "${WORK}/scene-save")
expect_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}"
    "FAIL: CORE_APP_BAKE stage=scene step=scene.save temporary=${WORK}/scene-save/.level.bscn.bake-tmp final=${WORK}/scene-save/level.bscn raw=0 "
    "scene.save diagnostic")
expect_match("${CORE_APP_DIAGNOSTIC_OUTPUT}"
    "step=scene.save[^\n]*errno=[1-9][0-9]*" "scene.save CRT error")
expect_not_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}" "stage=scene.commit"
    "scene.save short circuits before scene.commit")

file(MAKE_DIRECTORY "${WORK}/atomic-rename/level.bscn")
run_process(atomic_rename_failure 1 "${CORE_APP_ASSET_BAKE}" --output
    "${WORK}/atomic-rename")
if(WIN32)
    set(atomic_step MoveFileExA)
else()
    set(atomic_step rename)
endif()
expect_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}"
    "FAIL: CORE_APP_BAKE stage=scene.commit step=scene.commit.atomic.${atomic_step} temporary=${WORK}/atomic-rename/.level.bscn.bake-tmp final=${WORK}/atomic-rename/level.bscn "
    "scene.commit atomic rename diagnostic")
expect_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}"
    "atomic_temporary=${WORK}/atomic-rename/level.bscn.tmp"
    "atomic temporary path")
if(WIN32)
    expect_match("${CORE_APP_DIAGNOSTIC_OUTPUT}"
        "step=scene.commit.atomic.MoveFileExA[^\n]*raw=0 os_error=[1-9][0-9]* errno=[0-9]+"
        "atomic MoveFileExA result and error")
else()
    expect_match("${CORE_APP_DIAGNOSTIC_OUTPUT}"
        "step=scene.commit.atomic.rename[^\n]*raw=-1 os_error=0 errno=[1-9][0-9]*"
        "atomic rename result and errno")
endif()

if(WIN32)
    file(WRITE "${WORK}/blocked-temp" "not a directory\n")
    run_process(prepare_a_failure 1 "${CMAKE_COMMAND}" -E env
        "TEMP=${WORK}/blocked-temp" "${CORE_APP_ASSET_TEST}")
    expect_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}"
        "FAIL: CORE_APP_TEST stage=prepare slot=A " "A preparation slot")
    expect_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}" "${WORK}/blocked-temp/break_core_app_assets_a_"
        "A preparation path")
    expect_match("${CORE_APP_DIAGNOSTIC_OUTPUT}"
        "stage=prepare slot=A[^\n]*os_error=[1-9][0-9]*"
        "A preparation Win32 error")
else()
    find_program(SH_EXECUTABLE sh REQUIRED)
    foreach(slot A B)
        string(TOLOWER "${slot}" lower_slot)
        set(pid_file "${WORK}/prepare-${lower_slot}.pid")
        set(launch_script [=[printf '%s\n' "$$" > "$1"
: > "/tmp/break_core_app_assets_LOWER_$$"
exec "$2"
]=])
        string(REPLACE "LOWER" "${lower_slot}" launch_script "${launch_script}")
        execute_process(
            COMMAND "${SH_EXECUTABLE}" -c "${launch_script}" sh "${pid_file}"
                "${CORE_APP_ASSET_TEST}"
            RESULT_VARIABLE rc
            OUTPUT_VARIABLE out
            ERROR_VARIABLE err
            TIMEOUT 30)
        set(output "${out}${err}")
        if(NOT "${rc}" STREQUAL "1")
            record_error("prepare ${slot}: exit=${rc}, want=1; output=${output}")
        endif()
        if(EXISTS "${pid_file}")
            file(READ "${pid_file}" pid)
            string(STRIP "${pid}" pid)
        else()
            set(pid "")
        endif()
        if(NOT pid MATCHES "^[0-9]+$")
            record_error("prepare ${slot}: invalid launcher pid '${pid}'; output=${output}")
        else()
            set(expected_path "/tmp/break_core_app_assets_${lower_slot}_${pid}")
            expect_contains("${output}"
                "FAIL: CORE_APP_TEST stage=prepare slot=${slot} step=prepare.file_size path=${expected_path} raw=1 "
                "${slot} preparation diagnostic")
            string(REGEX MATCHALL "FAIL: CORE_APP_TEST stage=prepare slot=${slot} "
                prepare_lines "${output}")
            list(LENGTH prepare_lines prepare_count)
            if(NOT prepare_count EQUAL 1)
                record_error("prepare ${slot}: diagnostic count=${prepare_count}, want=1; output=${output}")
            endif()
            file(REMOVE "/tmp/break_core_app_assets_a_${pid}")
            file(REMOVE "/tmp/break_core_app_assets_b_${pid}")
            file(REMOVE_RECURSE "/tmp/break_core_app_assets_a_${pid}")
            file(REMOVE_RECURSE "/tmp/break_core_app_assets_b_${pid}")
        endif()
    endforeach()
endif()

run_process(launch_a_failure 1 "${CORE_APP_ASSET_LAUNCH_TEST}")
expect_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}"
    "FAIL: CORE_APP_TEST stage=launch slot=A step=launch.system command=\"${CORE_APP_MISSING_BAKER}\" --output \""
    "A launch command")
expect_match("${CORE_APP_DIAGNOSTIC_OUTPUT}"
    "step=launch.system[^\n]*raw=-?[1-9][0-9]* os_error=[0-9]+ errno=[0-9]+"
    "raw system result")
expect_not_contains("${CORE_APP_DIAGNOSTIC_OUTPUT}" "stage=launch slot=B"
    "A launch failure short circuits B")

file(READ "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_asset_bake.c" baker_source)
foreach(step scene.save scene.commit.probe scene.commit.file_size scene.commit.size
        scene.commit.malloc scene.commit.fopen scene.commit.read scene.commit.close
        scene.commit.remove prepare.platform_mkdir)
    expect_contains("${baker_source}" "\"${step}\"" "baker step ${step}")
endforeach()
expect_contains("${baker_source}" "step=%s.atomic.%s"
    "atomic API step formatting")
expect_contains("${baker_source}" "got=%llu expected=%llu extra=%d ferror=%d"
    "scene read fields")
expect_contains("${baker_source}" "platform_atomic_writer_open_diagnostic"
    "atomic diagnostic channel")

file(READ "${ENGINE_SOURCE_DIR}/tests/test_core_app_assets.c" asset_test_source)
foreach(step prepare.file_size prepare.platform_mkdir prepare.clear_directory
        prepare.remove launch.command launch.system)
    expect_contains("${asset_test_source}" "\"${step}\"" "asset test step ${step}")
endforeach()
foreach(call
        "prepare_asset_directory(g_assets_a, \"A\")"
        "prepare_asset_directory(g_assets_b, \"B\")"
        "run_baker(g_assets_a, \"A\")"
        "run_baker(g_assets_b, \"B\")"
        "g_bake_result = run_baker(g_assets_a, \"A\")")
    expect_contains("${asset_test_source}" "${call}" "asset test call ${call}")
endforeach()

file(READ "${ENGINE_SOURCE_DIR}/src/platform/platform_fs.c" platform_source)
foreach(api CreateFileA WriteFile FlushFileBuffers CloseHandle MoveFileExA
        mkstemp write fsync close rename "open(dir)" "fsync(dir)" unlink)
    expect_contains("${platform_source}" "\"${api}\"" "PAL saved ${api} diagnostic")
endforeach()

get_property(errors GLOBAL PROPERTY CORE_APP_DIAGNOSTIC_ERRORS)
if(NOT errors STREQUAL "")
    message(FATAL_ERROR "Core App diagnostics contract failed:\n${errors}")
endif()
message(STATUS "Core App diagnostics contract passed")
