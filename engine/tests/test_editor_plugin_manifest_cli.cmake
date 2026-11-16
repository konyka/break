# editor --plugin-manifest: a broken manifest exits 2 before any window
# opens; a valid one is reported on stderr.
# -DEDITOR=<path> -DWORK_DIR=<dir> [-DPLUGINS=ON when built with BREAK_EDITOR_PLUGINS]
if(NOT DEFINED EDITOR OR NOT DEFINED WORK_DIR)
    message(FATAL_ERROR "EDITOR and WORK_DIR are required")
endif()
file(MAKE_DIRECTORY "${WORK_DIR}")
set(hash "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff")
file(WRITE "${WORK_DIR}/good.txt" "# plugins\nplugin tools-a ${hash} libs/a.so\n")
file(WRITE "${WORK_DIR}/bad.txt" "# plugins\nplugin tools-a nothex libs/a.so\n")
file(REMOVE "${WORK_DIR}/missing.txt")
set(errors "")
if(PLUGINS)
    set(good_note "loads after the window opens")
else()
    set(good_note "not loaded")
endif()

function(run_editor out_rc out_err)
    execute_process(COMMAND "${CMAKE_COMMAND}" -E env --unset=DISPLAY
                            --unset=WAYLAND_DISPLAY "${EDITOR}" ${ARGN}
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err TIMEOUT 20)
    set(${out_rc} "${rc}" PARENT_SCOPE)
    set(${out_err} "${err}" PARENT_SCOPE)
endfunction()

function(expect_fail_closed label want)
    run_editor(rc err ${ARGN})
    if(NOT rc EQUAL 2)
        string(APPEND errors "${label}: exit ${rc}, want 2\n")
    endif()
    string(FIND "${err}" "${want}" found)
    if(found EQUAL -1)
        string(APPEND errors "${label}: stderr lacks '${want}': ${err}\n")
    endif()
    set(errors "${errors}" PARENT_SCOPE)
endfunction()

expect_fail_closed("bad hash" "bad.txt line 2: bad sha256"
    --plugin-manifest "${WORK_DIR}/bad.txt")
expect_fail_closed("missing file" "missing.txt line 0: cannot read file"
    "--plugin-manifest=${WORK_DIR}/missing.txt")
expect_fail_closed("no value" "--plugin-manifest needs a path" --plugin-manifest)
expect_fail_closed("last option wins" "bad.txt line 2: bad sha256"
    --plugin-manifest "${WORK_DIR}/good.txt" --plugin-manifest "${WORK_DIR}/bad.txt")

# A valid manifest is reported, then a bare --remote (parsed after the
# manifest, always fail closed) stops the editor before any window opens.
run_editor(rc err --plugin-manifest "${WORK_DIR}/good.txt" --remote)
foreach(want IN ITEMS
        "good.txt: 1 entries"
        "editor: plugin tools-a ${WORK_DIR}/libs/a.so (${good_note}"
        "--remote")
    string(FIND "${err}" "${want}" found)
    if(found EQUAL -1)
        string(APPEND errors "good manifest: stderr lacks '${want}': ${err}\n")
    endif()
endforeach()
if(NOT rc EQUAL 2)
    string(APPEND errors "good manifest + --remote: exit ${rc}, want 2\n")
endif()

if(NOT errors STREQUAL "")
    message(FATAL_ERROR "editor --plugin-manifest:\n${errors}")
endif()
message(STATUS "editor --plugin-manifest OK")
