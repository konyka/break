if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()
if(NOT DEFINED REPO_ROOT)
    message(FATAL_ERROR "REPO_ROOT is required")
endif()

set(workflow_path "${REPO_ROOT}/.github/workflows/core-app-native-validation.yml")
if(NOT EXISTS "${workflow_path}")
    message(FATAL_ERROR "missing native validation workflow: ${workflow_path}")
endif()
file(READ "${workflow_path}" workflow)
file(READ "${REPO_ROOT}/.github/workflows/windows-d3d12.yml" d3d12)
file(READ "${REPO_ROOT}/.github/workflows/ci.yml" ci)
file(SHA256 "${REPO_ROOT}/.github/workflows/ci.yml" ci_hash)

set_property(GLOBAL PROPERTY CORE_APP_NATIVE_VALIDATION_FAILURES "")
function(fail text)
    set_property(GLOBAL APPEND PROPERTY CORE_APP_NATIVE_VALIDATION_FAILURES "${text}")
endfunction()
function(require_text text needle label)
    string(FIND "${text}" "${needle}" offset)
    if(offset EQUAL -1)
        fail("${label}: missing: ${needle}")
    endif()
endfunction()
function(require_order text first second label)
    string(FIND "${text}" "${first}" first_offset)
    string(FIND "${text}" "${second}" second_offset)
    if(first_offset EQUAL -1 OR second_offset EQUAL -1 OR first_offset GREATER second_offset)
        fail("${label}: order required: ${first} -> ${second}")
    endif()
endfunction()
function(extract_job job out_var)
    set(marker "\n  ${job}:\n")
    string(FIND "${workflow}" "${marker}" start)
    if(start EQUAL -1)
        fail("missing job ${job}")
        set(${out_var} "" PARENT_SCOPE)
        return()
    endif()
    string(LENGTH "${marker}" marker_length)
    math(EXPR body_start "${start} + ${marker_length}")
    string(SUBSTRING "${workflow}" ${body_start} -1 remainder)
    string(REGEX MATCH "\n  [A-Za-z0-9_-]+:\n" next "${remainder}")
    if(next)
        string(FIND "${remainder}" "${next}" length)
    else()
        set(length -1)
    endif()
    string(SUBSTRING "${remainder}" 0 ${length} body)
    set(${out_var} "${body}" PARENT_SCOPE)
endfunction()

set(expected_preamble [=[name: Core App native validation

on:
  push:
    branches: [core-app-ci-validation]

permissions:
  contents: read

jobs:
]=])
string(FIND "${workflow}" "${expected_preamble}" preamble_offset)
if(NOT preamble_offset EQUAL 0)
    fail("native workflow must trigger only on pushes to core-app-ci-validation with read-only contents")
endif()

extract_job(core-app-macos-metal macos)
foreach(required IN ITEMS
        "name: macOS Metal CPU and contracts (no GPU evidence)"
        "runs-on: macos-15"
        "sudo xcode-select -s /Applications/Xcode_16.4.app/Contents/Developer && xcodebuild -version"
        "brew install shaderc spirv-cross"
        "cmake -S engine -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND=metal -DMYUI_PAL=cocoa"
        "cmake --build build --target core_app test_core_app_assets -j3"
        "./build/test_core_app_assets"
        "ctest --test-dir build -j3 --output-on-failure -R '^(test_core_app_target_contract|test_core_app_nm_missing|test_core_app_nm_unsupported|test_core_app_nested_contract|test_core_app_nm_symbol_missing|test_core_app_nm_symbol_missing_unsupported|test_core_app_contract_compat|test_core_app_formal_asset_tracking|test_core_app_naming_contract)$'")
    require_text("${macos}" "${required}" "macOS Metal job")
endforeach()
require_order("${macos}" "./build/test_core_app_assets"
    "ctest --test-dir build -j3" "macOS Metal job")

set(process_launch_helper_path
    "${REPO_ROOT}/engine/tests/test_core_app_process_launch.c")
set(process_launch_probe_path
    "${REPO_ROOT}/engine/tests/test_core_app_process_launch.cmake")
foreach(path IN ITEMS "${process_launch_helper_path}" "${process_launch_probe_path}")
    if(NOT EXISTS "${path}")
        fail("missing temporary process launch probe file: ${path}")
    endif()
endforeach()
if(EXISTS "${process_launch_helper_path}")
    file(READ "${process_launch_helper_path}" process_launch_helper)
    foreach(required IN ITEMS
            [=[int raw = system(argv[1]);]=]
            [=[int saved_errno = errno;]=]
            [=[unsigned long os_error = (unsigned long)GetLastError();]=]
            [=[CORE_APP_PROCESS_LAUNCH command=%s raw=%d os_error=%lu errno=%d\n]=]
            [=[return raw == 0 ? 0 : 1;]=])
        require_text("${process_launch_helper}" "${required}"
            "process launch C system() boundary")
    endforeach()
endif()
if(EXISTS "${process_launch_probe_path}")
    file(READ "${process_launch_probe_path}" process_launch_probe)
    foreach(required IN ITEMS
            [=[set(original "\"${CORE_APP_ASSET_BAKE}\" --output \"${WORK}/original\"")]=]
            [=[set(outer_quoted "\"${original}\"")]=]
            [=[string(REPLACE "${WORK}/original" "${WORK}/outer_quoted" outer_quoted "${outer_quoted}")]=]
            [=[set(backslashes "\"${exe_backslashes}\" --output \"${out_backslashes}\"")]=]
            [=[set(unquoted "${CORE_APP_ASSET_BAKE} --output ${WORK}/unquoted")]=]
            [=[foreach(variant IN ITEMS original outer_quoted backslashes unquoted)]=]
            [=[execute_process(COMMAND "${CORE_APP_PROCESS_LAUNCH}" "${command}"]=]
            [=[${WORK}/${variant}/level.bscn]=]
            [=[set(${variant}_stdout "${stdout}")]=]
            [=[if(NOT "${original_result}" STREQUAL "1")]=]
            [=[string(REGEX MATCH "CORE_APP_PROCESS_LAUNCH command=.* raw=(-?[0-9]+) os_error=[0-9]+ errno=-?[0-9]+" original_record "${original_stdout}")]=]
            [=[if("${original_record}" STREQUAL "")]=]
            [=[set(original_raw "${CMAKE_MATCH_1}")]=]
            [=[if(original_raw EQUAL 0)]=])
        require_text("${process_launch_probe}" "${required}"
            "four-variant real baker probe")
    endforeach()
endif()
file(READ "${REPO_ROOT}/engine/CMakeLists.txt" engine_cmake)
foreach(required IN ITEMS
        [=[add_executable(test_core_app_process_launch tests/test_core_app_process_launch.c)]=]
        [=[add_test(NAME test_core_app_process_launch_probe]=]
        [=[-DCORE_APP_PROCESS_LAUNCH=$<TARGET_FILE:test_core_app_process_launch>]=]
        [=[-DCORE_APP_ASSET_BAKE=$<TARGET_FILE:core_app_asset_bake>]=]
        [=[-P ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_core_app_process_launch.cmake)]=])
    require_text("${engine_cmake}" "${required}" "process launch target registration")
endforeach()

extract_job(core-app-windows-msvc windows)
set(expected_process_launch_step [=[      - name: Probe Core App Windows process launch
        id: process_launch_probe
        continue-on-error: true
        env:
          ENGINE_LOCKED_DEPS_ALLOW_ABSENT: 1
        run: ctest --test-dir build -j3 -R '^test_core_app_process_launch_probe$' -V
]=])
require_text("${windows}" "${expected_process_launch_step}"
    "Windows real C system() process launch step")
require_order("${windows}" "${expected_process_launch_step}"
    "      - name: Run real baker and assets test" "Windows process launch probe placement")
require_order("${windows}" "${expected_process_launch_step}"
    "./build/test_core_app_assets.exe" "Windows original assets preservation")
foreach(required IN ITEMS
        "name: Windows MSVC CPU assets (no GPU evidence)"
        "runs-on: windows-latest"
        "cmake -P engine/tools/fetch_d3d12_agility_sdk.cmake"
        "- name: Add Windows SDK dxc to PATH"
        "uses: ilammy/msvc-dev-cmd@v1"
        "arch: x64"
        "cmake -S engine -B build -G Ninja -DCMAKE_C_COMPILER=cl -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=OFF -DENGINE_ENABLE_IPO=OFF -DENGINE_BUILD_FUZZ_SMOKE=ON"
        "cmake --build build --target core_app_asset_bake test_core_app_process_launch test_core_app_assets test_core_app_assets_launch_diagnostic -j3"
        "      - name: Run real baker and assets test\n        id: original_assets"
        "ENGINE_LOCKED_DEPS_ALLOW_ABSENT: 1"
        "rm -rf \"\$RUNNER_TEMP/core-app-native-validation-assets\""
        "diagnostics_log=\"\$RUNNER_TEMP/core-app-native-diagnostics.log\""
        "./build/core_app_asset_bake.exe --output \"\$RUNNER_TEMP/core-app-native-validation-assets\" >\"\$bake_log\" 2>&1"
        "bake_rc=\$?"
        "./build/test_core_app_assets.exe >\"\$test_log\" 2>&1"
        "test_rc=\$?"
        "ctest --test-dir build -j3 -R '^test_core_app_baker_diagnostics$' -V >\"\$diagnostics_log\" 2>&1"
        "diagnostics_rc=\$?"
        "cat \"\$bake_log\""
        "cat \"\$test_log\""
        "printf '\\n=== test_core_app_baker_diagnostics (exit %s) ===\\n' \"\$diagnostics_rc\""
        "cat \"\$diagnostics_log\""
        "first_failure=\$(grep -m1 'FAIL:' \"\$bake_log\" || grep -m1 'FAIL:' \"\$test_log\" || grep -m1 'FAIL:' \"\$diagnostics_log\" || true)"
        "if [ \"\$bake_rc\" -ne 0 ] || [ \"\$test_rc\" -ne 0 ] || [ \"\$diagnostics_rc\" -ne 0 ]; then"
        "echo \"::error::Core App native validation failed (baker exit=\$bake_rc, assets exit=\$test_rc, diagnostics exit=\$diagnostics_rc); full logs above\"")
    require_text("${windows}" "${required}" "Windows MSVC job")
endforeach()
require_order("${windows}" "./build/core_app_asset_bake.exe"
    "./build/test_core_app_assets.exe" "Windows MSVC job")
require_order("${windows}" "./build/test_core_app_assets.exe"
    "ctest --test-dir build -j3 -R '^test_core_app_baker_diagnostics$' -V"
    "Windows native diagnostics invocation")
require_order("${windows}" "ctest --test-dir build -j3 -R '^test_core_app_baker_diagnostics$' -V"
    "diagnostics_rc=\$?" "Windows native diagnostics return capture")
require_order("${windows}" "diagnostics_rc=\$?"
    "set -e" "Windows native diagnostics capture before errexit")
require_order("${windows}" "./build/test_core_app_assets.exe"
    "cat \"\$bake_log\"" "Windows MSVC job")
require_order("${windows}" "cat \"\$bake_log\""
    "cat \"\$test_log\"" "Windows MSVC job")
require_order("${windows}" "cat \"\$test_log\""
    "cat \"\$diagnostics_log\"" "Windows native diagnostics full log")
require_order("${windows}" "cat \"\$diagnostics_log\""
    "first_failure=\$(grep -m1 'FAIL:'" "Windows native diagnostics failure annotation")
foreach(forbidden IN ITEMS "| head" "| tail" "head -" "tail -")
    string(FIND "${windows}" "${forbidden}" truncation_offset)
    if(NOT truncation_offset EQUAL -1)
        fail("Windows MSVC job truncates native diagnostics: ${forbidden}")
    endif()
endforeach()

set(expected_native_diagnostic [=[      - name: Diagnose Core App asset directories (failure only)
        if: ${{ always() && (steps.original_assets.outcome == 'failure' || steps.process_launch_probe.outcome != 'success') }}
        shell: pwsh
        run: |
          $ErrorActionPreference = 'Continue'
          try {
            $formal = Join-Path $env:GITHUB_WORKSPACE 'engine/assets/core_app'
            Write-Output "=== Core App formal assets: $formal ==="
            if (Test-Path -LiteralPath $formal -PathType Container) {
              Get-ChildItem -LiteralPath $formal -File -Force | ForEach-Object {
                $hash = Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256
                Write-Output "FORMAL FILE $($_.Name) PATH $($_.FullName) LENGTH $($_.Length) bytes SHA256 $($hash.Hash)"
              }
            } else {
              Write-Output "MISSING $formal"
            }
            $output = Join-Path $env:RUNNER_TEMP 'core-app-native-validation-assets'
            Write-Output "=== Core App asset output: $output ==="
            if (Test-Path -LiteralPath $output -PathType Container) {
              Get-ChildItem -LiteralPath $output -Force | ForEach-Object {
                if ($_.PSIsContainer) {
                  Write-Output "DIR $($_.Name)"
                } else {
                  $hash = Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256
                  Write-Output "FILE $($_.Name) PATH $($_.FullName) LENGTH $($_.Length) bytes SHA256 $($hash.Hash)"
                }
              }
            } else {
              Write-Output "MISSING $output"
            }
            foreach ($pattern in @('break_core_app_assets_a_*', 'break_core_app_assets_b_*')) {
              $root = Join-Path $env:TEMP $pattern
              Write-Output "=== Native temp directories: $root ==="
              try {
                $directories = @(Get-ChildItem -Path $root -Directory -Force -ErrorAction Stop)
              } catch [System.Management.Automation.ItemNotFoundException] {
                $directories = @()
              }
              if ($directories.Count -eq 0) {
                Write-Output "MISSING $root"
              } else {
                foreach ($directory in $directories) {
                  Write-Output "DIR $($directory.FullName)"
                  Get-ChildItem -LiteralPath $directory.FullName -File -Force | ForEach-Object {
                    $hash = Get-FileHash -LiteralPath $_.FullName -Algorithm SHA256
                    Write-Output "FILE $($_.Name) PATH $($_.FullName) LENGTH $($_.Length) bytes SHA256 $($hash.Hash)"
                  }
                }
              }
            }
          } catch {
            Write-Output "Core App asset directory diagnostic error: $($_.Exception.Message)"
          }
          exit 0
]=])
require_text("${windows}" "${expected_native_diagnostic}"
    "Windows native asset directory diagnostic")
require_text("${windows}" "            exit 1
          fi

${expected_native_diagnostic}" "Windows native asset directory diagnostic placement")
set(expected_process_launch_failure_gate [=[      - name: Preserve Core App process launch probe failure
        if: always()
        shell: pwsh
        run: |
          $probeOutcome = '${{ steps.process_launch_probe.outcome }}'
          Write-Output "Core App process launch probe outcome: $probeOutcome"
          if ($probeOutcome -ne 'success') {
            Write-Error "Core App process launch probe did not succeed; preserving failure"
            exit 1
          }
]=])
require_text("${windows}" "${expected_process_launch_failure_gate}"
    "Windows process launch failure gate")
require_text("${windows}" "${expected_native_diagnostic}\n${expected_process_launch_failure_gate}"
    "Windows process launch failure gate placement after directory collection")
string(LENGTH "${windows}" windows_length)
string(LENGTH "${expected_process_launch_failure_gate}" process_launch_gate_length)
math(EXPR process_launch_gate_expected_start
    "${windows_length} - ${process_launch_gate_length}")
string(FIND "${windows}" "${expected_process_launch_failure_gate}"
    process_launch_gate_start)
if(NOT process_launch_gate_start EQUAL process_launch_gate_expected_start)
    fail("Windows process launch failure gate must be the final step with no later continue-on-error")
endif()
require_text("${windows}" "Get-ChildItem -Path \$root -Directory -Force -ErrorAction Stop"
    "Windows native enumeration must surface non-absence errors")
require_text("${windows}" "catch [System.Management.Automation.ItemNotFoundException]"
    "Windows native enumeration may suppress only expected absence")
string(FIND "${windows}" "-ErrorAction SilentlyContinue" native_suppression_offset)
if(NOT native_suppression_offset EQUAL -1)
    fail("Windows native asset directory diagnostic must not suppress enumeration errors indiscriminately")
endif()

foreach(forbidden IN ITEMS
        "workflow_dispatch:" "pull_request:" "schedule:" "packages: write"
        "actions/upload-artifact" "make_evidence_receipt" "GPU_RUNTIME" "NATIVE_SURFACE")
    string(FIND "${workflow}" "${forbidden}" forbidden_offset)
    if(NOT forbidden_offset EQUAL -1)
        fail("native workflow has an out-of-scope trigger, publish, or evidence claim: ${forbidden}")
    endif()
endforeach()

set(expected_d3d12_trigger [=[on:
  push:
    branches: [master, core-app-ci-validation]
  pull_request:
    branches: [master]

jobs:]=])
require_text("${d3d12}" "${expected_d3d12_trigger}" "D3D12 trigger")
set(expected_d3d12_diagnostic [=[      - name: Diagnose Core App compatibility (failure only)
        if: failure()
        timeout-minutes: 8
        env:
          ENGINE_LOCKED_DEPS_ALLOW_ABSENT: 1
        shell: bash
        run: |
          compat_log="$RUNNER_TEMP/core-app-contract-compat-v.log"
          set +e
          ctest --test-dir build-d3d12 -R '^test_core_app_contract_compat$' -V > "$compat_log" 2>&1
          compat_rc=$?
          cat "$compat_log"
          for fixture in \
            build-d3d12/core_app_contract_compat/corrupt-build/CTestTestfile.cmake \
            build-d3d12/core_app_contract_compat/nm-build/CTestTestfile.cmake
          do
            printf '\n=== %s ===\n' "$fixture"
            if [ -f "$fixture" ]; then
              cat "$fixture"
            else
              echo "MISSING: $fixture"
            fi
          done
          exit "$compat_rc"

]=])
require_text("${d3d12}" "${expected_d3d12_diagnostic}"
    "D3D12 compatibility diagnostic")
require_text("${d3d12}" "            exit 1
          fi

${expected_d3d12_diagnostic}" "D3D12 compatibility diagnostic placement after headless tests")
require_text("${d3d12}" "${expected_d3d12_diagnostic}      - name: WARP GPU-runtime floor"
    "D3D12 compatibility diagnostic placement before WARP tests")
string(REPLACE "${expected_d3d12_diagnostic}" ""
    d3d12_without_diagnostic "${d3d12}")
string(REPLACE "branches: [master, core-app-ci-validation]"
    "branches: [master]" d3d12_without_validation "${d3d12_without_diagnostic}")
string(SHA256 d3d12_base_hash "${d3d12_without_validation}")
if(NOT d3d12_base_hash STREQUAL "11344c7bda647136befef9d1d97906b103b2774874813a360d6fbaeae747d412")
    fail("D3D12 jobs or evidence semantics changed beyond the validation trigger and compatibility diagnostic")
endif()

find_program(core_app_bash bash)
set(compat_step_marker "      - name: Diagnose Core App compatibility (failure only)\n")
set(compat_next_step_marker "\n      - name: WARP GPU-runtime floor")
string(FIND "${d3d12}" "${compat_step_marker}" compat_step_start)
string(FIND "${d3d12}" "${compat_next_step_marker}" compat_step_end)
if(compat_step_start EQUAL -1 OR compat_step_end EQUAL -1 OR compat_step_end LESS compat_step_start)
    fail("D3D12 compatibility diagnostic Bash check could not extract the delivered step")
else()
    math(EXPR compat_step_length "${compat_step_end} - ${compat_step_start}")
    string(SUBSTRING "${d3d12}" ${compat_step_start} ${compat_step_length} compat_step)
    set(compat_run_marker "        run: |\n")
    string(FIND "${compat_step}" "${compat_run_marker}" compat_run_start)
    if(compat_run_start EQUAL -1)
        fail("D3D12 compatibility diagnostic Bash check could not extract the delivered run block")
    elseif(NOT core_app_bash)
        fail("D3D12 compatibility diagnostic Bash check requires bash")
    else()
        string(LENGTH "${compat_run_marker}" compat_run_marker_length)
        math(EXPR compat_body_start "${compat_run_start} + ${compat_run_marker_length}")
        string(SUBSTRING "${compat_step}" ${compat_body_start} -1 compat_run_indented)
        string(REGEX REPLACE "(^|\n)          " "\\1" compat_run "${compat_run_indented}")

        if(DEFINED ENV{TMPDIR} AND NOT "$ENV{TMPDIR}" STREQUAL "")
            file(TO_CMAKE_PATH "$ENV{TMPDIR}" core_app_test_temp)
        elseif(DEFINED ENV{TEMP} AND NOT "$ENV{TEMP}" STREQUAL "")
            file(TO_CMAKE_PATH "$ENV{TEMP}" core_app_test_temp)
        else()
            set(core_app_test_temp "/tmp")
        endif()
        string(RANDOM LENGTH 16 ALPHABET 0123456789abcdef core_app_test_suffix)
        set(core_app_bash_root "${core_app_test_temp}/core-app-compat-contract-${core_app_test_suffix}")
        set(core_app_runner_temp "${core_app_bash_root}/runner")
        set(core_app_bash_work "${core_app_bash_root}/work")
        file(MAKE_DIRECTORY
            "${core_app_runner_temp}"
            "${core_app_bash_work}/build-d3d12/core_app_contract_compat/corrupt-build"
            "${core_app_bash_work}/build-d3d12/core_app_contract_compat/nm-build")
        file(WRITE "${core_app_bash_work}/build-d3d12/core_app_contract_compat/corrupt-build/CTestTestfile.cmake"
            "corrupt fixture\n")
        file(WRITE "${core_app_bash_work}/build-d3d12/core_app_contract_compat/nm-build/CTestTestfile.cmake"
            "nm fixture\n")
        set(core_app_cat_calls "${core_app_bash_root}/cat-calls")
        set(core_app_bash_prelude [=[#!/usr/bin/env bash
set -o pipefail
ctest() {
  return 23
}
cat() {
  printf '%s\n' "$*" >> "$COMPAT_CAT_CALLS"
  if [ "$1" = "$RUNNER_TEMP/core-app-contract-compat-v.log" ]; then
    return 91
  fi
  return 0
}
]=])
        file(WRITE "${core_app_bash_root}/compat-run.sh"
            "${core_app_bash_prelude}${compat_run}")
        execute_process(
            COMMAND "${CMAKE_COMMAND}" -E env
                "RUNNER_TEMP=${core_app_runner_temp}"
                "COMPAT_CAT_CALLS=${core_app_cat_calls}"
                "${core_app_bash}" "${core_app_bash_root}/compat-run.sh"
            WORKING_DIRECTORY "${core_app_bash_work}"
            RESULT_VARIABLE core_app_compat_result
            OUTPUT_VARIABLE core_app_compat_output
            ERROR_VARIABLE core_app_compat_error)
        if(NOT "${core_app_compat_result}" STREQUAL "23")
            fail("D3D12 compatibility diagnostic Bash check returned ${core_app_compat_result} instead of compat status 23 after a cat failure")
        endif()
        set(core_app_expected_cat_calls "${core_app_runner_temp}/core-app-contract-compat-v.log
build-d3d12/core_app_contract_compat/corrupt-build/CTestTestfile.cmake
build-d3d12/core_app_contract_compat/nm-build/CTestTestfile.cmake
")
        if(EXISTS "${core_app_cat_calls}")
            file(READ "${core_app_cat_calls}" core_app_actual_cat_calls)
        else()
            set(core_app_actual_cat_calls "")
        endif()
        if(NOT "${core_app_actual_cat_calls}" STREQUAL "${core_app_expected_cat_calls}")
            fail("D3D12 compatibility diagnostic Bash check did not attempt both fixture reads after the failed log read; expected ${core_app_expected_cat_calls} but got ${core_app_actual_cat_calls}")
        endif()
        file(REMOVE_RECURSE "${core_app_bash_root}")
    endif()
endif()

string(FIND "${ci}" "core-app-ci-validation" ci_validation_offset)
if(NOT ci_validation_offset EQUAL -1)
    fail("main ci.yml must not gain the temporary validation trigger")
endif()
if(NOT ci_hash STREQUAL "ddc7166c0bbd7cbbd76121daae2dd8b373bc945ad0ae03fb0fc007baf5336ab4")
    fail("main ci.yml changed; master-specific image publishing must remain untouched")
endif()

get_property(failure_lines GLOBAL PROPERTY CORE_APP_NATIVE_VALIDATION_FAILURES)
if(failure_lines)
    string(REPLACE ";" "\n" failures "${failure_lines}")
    message(FATAL_ERROR "Core App native validation workflow contract failed:\n${failures}\n")
endif()
message(STATUS "Core App native validation workflow contract OK")
