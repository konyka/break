if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()
if(NOT DEFINED REPO_ROOT)
    message(FATAL_ERROR "REPO_ROOT is required")
endif()
if(NOT DEFINED CI_YML)
    set(CI_YML "${REPO_ROOT}/.github/workflows/ci.yml")
endif()
if(NOT DEFINED ROLLBACK_YML)
    set(ROLLBACK_YML "${REPO_ROOT}/.github/workflows/rollback-drill.yml")
endif()
file(READ "${CI_YML}" ci)
file(READ "${ROLLBACK_YML}" rollback)

function(fail text)
    set_property(GLOBAL APPEND PROPERTY CI_EXECUTION_CONTRACT_FAILURES "${text}")
endfunction()

function(extract_job job out_var)
    set(marker "\n  ${job}:\n")
    string(FIND "${ci}" "${marker}" start)
    if(start EQUAL -1)
        fail("missing job ${job}")
        set(${out_var} "" PARENT_SCOPE)
        return()
    endif()
    string(LENGTH "${marker}" marker_length)
    math(EXPR body_start "${start} + ${marker_length}")
    string(SUBSTRING "${ci}" ${body_start} -1 remainder)
    string(REGEX MATCH "\n  [A-Za-z0-9_-]+:\n" next "${remainder}")
    if(next)
        string(FIND "${remainder}" "${next}" length)
    else()
        set(length -1)
    endif()
    string(SUBSTRING "${remainder}" 0 ${length} body)
    set(${out_var} "${body}" PARENT_SCOPE)
endfunction()

function(extract_step block marker out_var)
    string(FIND "${block}" "\n      ${marker}" start)
    if(start EQUAL -1)
        fail("missing step ${marker}")
        set(${out_var} "" PARENT_SCOPE)
        return()
    endif()
    string(LENGTH "\n      ${marker}" marker_length)
    math(EXPR body_start "${start} + ${marker_length}")
    string(SUBSTRING "${block}" ${body_start} -1 remainder)
    string(REGEX MATCH "\n      - (name|uses):" next "${remainder}")
    if(next)
        string(FIND "${remainder}" "${next}" length)
    else()
        set(length -1)
    endif()
    string(SUBSTRING "${remainder}" 0 ${length} body)
    set(${out_var} "${body}" PARENT_SCOPE)
endfunction()

function(require_order block first second)
    string(FIND "${block}" "${first}" a)
    string(FIND "${block}" "${second}" b)
    if(a EQUAL -1 OR b EQUAL -1 OR a GREATER b)
        fail("step order required: ${first} -> ${second}")
    endif()
endfunction()

function(require_always block marker)
    extract_step("${block}" "${marker}" step)
    string(FIND "${step}" "if: always()" found)
    if(found EQUAL -1)
        fail("${marker} must use if: always()")
    endif()
endfunction()

function(require_lane_semantics job execution_marker emit_marker require_marker)
    extract_job("${job}" block)
    set(upload_marker "- uses: actions/upload-artifact@")
    if(job STREQUAL "lane-benchmark-steam-deck-vk")
        set(upload_marker "- name: Upload receipt")
    endif()
    require_order("${block}" "${execution_marker}" "${emit_marker}")
    require_order("${block}" "${emit_marker}" "${upload_marker}")
    require_order("${block}" "${upload_marker}" "${require_marker}")
    require_always("${block}" "${emit_marker}")
    require_always("${block}" "${upload_marker}")
    require_always("${block}" "${require_marker}")
    extract_step("${block}" "${execution_marker}" execution)
    foreach(required IN ITEMS
            "id: graphics"
            "continue-on-error: true"
            "echo \"rc=\$rc\" >> \"\$GITHUB_OUTPUT\""
            "echo \"skipped=\$skipped\" >> \"\$GITHUB_OUTPUT\""
            "echo \"passed=\$passed\" >> \"\$GITHUB_OUTPUT\"")
        string(FIND "${execution}" "${required}" found)
        if(found EQUAL -1)
            fail("${job}: execution step missing ${required}")
        endif()
    endforeach()
endfunction()

require_lane_semantics(lane-gpu-runtime-linux-gl
    "- name: Test Wayland/OpenGL runtime"
    "- name: Emit evidence receipt"
    "- name: Require executed graphics tests")
require_lane_semantics(lane-gpu-runtime-linux-vk
    "- name: Test Wayland/Vulkan graphics"
    "- name: Emit evidence receipt"
    "- name: Require executed graphics tests")
require_lane_semantics(lane-validation-linux-vk
    "- name: Run Wayland graphics under validation layers"
    "- name: Emit evidence receipt"
    "- name: Require executed graphics tests")
require_lane_semantics(lane-benchmark-linux-vk
    "- name: Run Wayland benchmark"
    "- name: Emit benchmark receipt"
    "- name: Require executed benchmark")
require_lane_semantics(lane-benchmark-steam-deck-vk
    "- name: Run Wayland GPU suite and benchmark"
    "- name: Emit benchmark receipt"
    "- name: Require executed real-GPU benchmark")

extract_job(lane-headless-windows-asan windows_asan)
foreach(required IN ITEMS
        "CMAKE_C_FLAGS=\"-fsanitize=address -fno-omit-frame-pointer\""
        "CMAKE_CXX_FLAGS=\"-fsanitize=address -fno-omit-frame-pointer\""
        "Copy the ASan runtime DLLs next to the tests")
    string(FIND "${windows_asan}" "${required}" found)
    if(found EQUAL -1)
        fail("Windows ASan lane missing ${required}")
    endif()
endforeach()

foreach(macos_job IN ITEMS lane-native-surface-cocoa lane-gpu-runtime-macos-metal ios-metal-build)
    extract_job("${macos_job}" macos_block)
    string(FIND "${macos_block}" "runs-on: macos-15" found)
    if(found EQUAL -1)
        fail("${macos_job} must use the supported arm64 macos-15 runner")
    endif()
    if(macos_block MATCHES "macos-14|macos-15-intel")
        fail("${macos_job} changed its retired label or arm64 architecture")
    endif()
endforeach()
string(FIND "${ci}" "runs-on: macos-14" retired_label)
if(NOT retired_label EQUAL -1)
    fail("workflow retains unsupported macos-14 runner")
endif()
foreach(xcode_job IN ITEMS lane-gpu-runtime-macos-metal ios-metal-build)
    extract_job("${xcode_job}" xcode_block)
    string(FIND "${xcode_block}" "sudo xcode-select -s /Applications/Xcode_16.4.app/Contents/Developer && xcodebuild -version" found)
    if(found EQUAL -1)
        fail("${xcode_job} must select official macos-15 Xcode 16.4 and print its version")
    endif()
    if(xcode_block MATCHES "Xcode_15\\.4\\.app")
        fail("${xcode_job} retains Xcode 15.4, which is absent from macos-15")
    endif()
endforeach()
file(READ "${REPO_ROOT}/engine/external/locked_dependencies.json" locked_dependencies)
foreach(required_pin IN ITEMS "CI pin 16.4" "/Applications/Xcode_16.4.app")
    string(FIND "${locked_dependencies}" "${required_pin}" found)
    if(found EQUAL -1)
        fail("locked_dependencies.json is not synchronized with the CI Xcode pin: ${required_pin}")
    endif()
endforeach()

extract_job(lane-benchmark-steam-deck-vk deck)
foreach(marker IN ITEMS "- name: Emit benchmark receipt" "- name: Require executed real-GPU benchmark")
    extract_step("${deck}" "${marker}" step)
    foreach(required IN ITEMS
            "source hardware.env"
            "check_steam_deck_hardware.cmake"
            "DECK_EXPECTED_VENDOR_ID"
            "DECK_EXPECTED_DEVICE_ID")
        string(FIND "${step}" "${required}" found)
        if(found EQUAL -1)
            fail("Steam Deck ${marker} missing ${required}")
        endif()
    endforeach()
    if(marker STREQUAL "- name: Require executed real-GPU benchmark")
        set(hardware_test "test \"\$hardware_ok\" = \"true\"")
    else()
        set(hardware_test "[ \"\$hardware_ok\" = \"true\" ]")
    endif()
    string(FIND "${step}" "${hardware_test}" hardware_found)
    if(hardware_found EQUAL -1)
        fail("Steam Deck ${marker} does not enforce hardware_ok")
    endif()
endforeach()

extract_job(lane-proton proton)
foreach(required IN ITEMS
        "exit 77"
        "id: steamrt"
        "continue-on-error: true"
        "if [ \"\${{ steps.steamrt.outcome }}\" = \"success\" ]; then lvl=HEADLESS; else lvl=UNAVAILABLE; fi")
    string(FIND "${proton}" "${required}" found)
    if(found EQUAL -1)
        fail("Proton missing ${required}")
    endif()
endforeach()

foreach(required IN ITEMS
        "TAG: \${{ inputs.tag }}"
        "ref: \${{ env.TAG }}"
        "git tag -v \"\$TAG\""
        "supported tag \$TAG")
    string(FIND "${rollback}" "${required}" found)
    if(found EQUAL -1)
        fail("rollback missing safe env usage ${required}")
    endif()
endforeach()
foreach(forbidden IN ITEMS
        "tag=\"\${{ inputs.tag }}\""
        "git tag -v \"\${{ inputs.tag }}\""
        "supported tag \${{ inputs.tag }}")
    string(FIND "${rollback}" "${forbidden}" found)
    if(NOT found EQUAL -1)
        fail("rollback retains direct expression in shell: ${forbidden}")
    endif()
endforeach()
string(FIND "${rollback}" "- name: Validate supported rollback tag" validate)
string(FIND "${rollback}" "- uses: actions/checkout" checkout)
if(validate EQUAL -1 OR checkout EQUAL -1 OR validate GREATER checkout)
    fail("rollback validation must precede checkout")
endif()

get_property(failure_lines GLOBAL PROPERTY CI_EXECUTION_CONTRACT_FAILURES)
if(failure_lines)
    string(REPLACE ";" "\n" failures "${failure_lines}")
    message(FATAL_ERROR "CI execution semantics contract failed:\n${failures}\n")
endif()
message(STATUS "CI execution semantics contract OK")
