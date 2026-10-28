# Release configuration contract: what the shipped binaries may contain.
# Roadmap acceptance "No default remote debug or unsigned update path in
# release configuration" (docs/design/security_threat_model.md §3/§10).
#
# -DNM=<nm> -DENGINE_DEMO=<path> -DDXX_BREAK=<path> [-DEDITOR=<path>]
# -DBUILD_TYPE=<CMAKE_BUILD_TYPE>
#
# 1. engine_demo / dxx_break carry no transport, session, update, crypto,
#    crash-upload or editor-remote code at all (no remote surface, no update
#    path of any kind, signed or not).
# 2. No test hooks (`*_for_test`, `*test_hook*`) in shipped binaries: the
#    allowlist below is empty and must stay so. The scripted input replay
#    (BREAK_EDITOR_INPUT_SCRIPT) must not ship either.
# 3. editor: --remote fails closed (exit 2, before any window or listener)
#    without TLS material, and any --remote-* option without --remote is
#    rejected. Runs headless (no DISPLAY needed: the parser exits first).
if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()
foreach(var NM ENGINE_DEMO DXX_BREAK)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

# Empty since 2026-10-28: every *_for_test seam lives behind a *_TESTING
# define compiled only into a test variant (break_net_test,
# engine_rhi_vulkan_alloc_fault, test_editor_shell, ...). Keep it empty.
set(hook_allowlist "")

function(release_defined_symbols binary out_var)
    execute_process(COMMAND "${NM}" --defined-only "${binary}"
        OUTPUT_VARIABLE nm_out RESULT_VARIABLE nm_rc ERROR_VARIABLE nm_err)
    if(NOT nm_rc EQUAL 0)
        message(FATAL_ERROR "nm failed on ${binary}: ${nm_err}")
    endif()
    string(REPLACE "\n" ";" lines "${nm_out}")
    set(syms "")
    foreach(line IN LISTS lines)
        if(line MATCHES "^[0-9a-fA-F]+ [A-Za-z] ([A-Za-z0-9_.$]+)$")
            set(sym "${CMAKE_MATCH_1}")
            if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
                string(REGEX REPLACE "^_" "" sym "${sym}")
            endif()
            list(APPEND syms "${sym}")
        endif()
    endforeach()
    set(${out_var} "${syms}" PARENT_SCOPE)
endfunction()

set(errors "")

# --- 1. runtime binaries: no remote / update / transport surface ---------
foreach(binary IN ITEMS "${ENGINE_DEMO}" "${DXX_BREAK}")
    if(NOT EXISTS "${binary}")
        message(FATAL_ERROR "missing shipped binary ${binary}")
    endif()
    release_defined_symbols("${binary}" syms)
    foreach(sym IN LISTS syms)
        if(sym MATCHES "^(break_net_|break_session_|break_update_|break_crypto_|break_crash_upload|break_editor_|snow_)")
            string(APPEND errors "${binary}: runtime binary carries ${sym}\n")
        endif()
    endforeach()
endforeach()

# --- 2. test-hook ratchet over every shipped binary ----------------------
set(shipped "${ENGINE_DEMO}" "${DXX_BREAK}")
if(DEFINED EDITOR AND NOT "${EDITOR}" STREQUAL "" AND EXISTS "${EDITOR}")
    list(APPEND shipped "${EDITOR}")
endif()
foreach(binary IN LISTS shipped)
    release_defined_symbols("${binary}" syms)
    foreach(sym IN LISTS syms)
        if(sym MATCHES "_for_test$|test_hook")
            list(FIND hook_allowlist "${sym}" idx)
            if(idx EQUAL -1)
                string(APPEND errors
                    "${binary}: new test hook ${sym} ships in a release binary "
                    "(compile it only into a *_TESTING test variant)\n")
            endif()
        endif()
    endforeach()
endforeach()

# --- 2b. no scripted input replay in the shipped editor ------------------
if(DEFINED EDITOR AND NOT "${EDITOR}" STREQUAL "" AND EXISTS "${EDITOR}")
    release_defined_symbols("${EDITOR}" syms)
    foreach(sym IN LISTS syms)
        if(sym MATCHES "^break_editor_input_(script|driver)_")
            string(APPEND errors "${EDITOR}: ships the input replay (${sym}); "
                "it belongs to BREAK_EDITOR_INPUT_SCRIPT=ON validation builds\n")
        endif()
    endforeach()
endif()

# --- 3. editor --remote fails closed --------------------------------------
if(DEFINED EDITOR AND NOT "${EDITOR}" STREQUAL "" AND EXISTS "${EDITOR}")
    set(cases
        "--remote|--remote requires TLS"
        "--remote-cert,/nonexistent|options need --remote"
        "--remote,--remote-cert,/nonexistent|requires TLS")
    foreach(case IN LISTS cases)
        string(REPLACE "|" ";" parts "${case}")
        list(GET parts 0 argstr)
        list(GET parts 1 want)
        string(REPLACE "," ";" args "${argstr}")
        execute_process(COMMAND "${CMAKE_COMMAND}" -E env --unset=DISPLAY
                                --unset=WAYLAND_DISPLAY "${EDITOR}" ${args}
            RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err
            TIMEOUT 20)
        if(NOT rc EQUAL 2)
            string(APPEND errors "editor ${argstr}: exit ${rc}, want 2 (fail closed)\n")
        endif()
        string(FIND "${err}" "${want}" found)
        if(found EQUAL -1)
            string(APPEND errors "editor ${argstr}: stderr lacks '${want}': ${err}\n")
        endif()
    endforeach()
endif()

if(NOT errors STREQUAL "")
    message(FATAL_ERROR "release configuration contract (${BUILD_TYPE}):\n${errors}")
endif()
message(STATUS "release configuration contract OK (${BUILD_TYPE})")
