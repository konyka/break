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

extract_job(core-app-windows-msvc windows)
foreach(required IN ITEMS
        "name: Windows MSVC CPU assets (no GPU evidence)"
        "runs-on: windows-latest"
        "cmake -P engine/tools/fetch_d3d12_agility_sdk.cmake"
        "- name: Add Windows SDK dxc to PATH"
        "uses: ilammy/msvc-dev-cmd@v1"
        "arch: x64"
        "cmake -S engine -B build -G Ninja -DCMAKE_C_COMPILER=cl -DCMAKE_BUILD_TYPE=Debug -DENGINE_VULKAN=OFF -DENGINE_ENABLE_IPO=OFF -DENGINE_BUILD_FUZZ_SMOKE=ON"
        "cmake --build build --target core_app_asset_bake test_core_app_assets -j3"
        "ENGINE_LOCKED_DEPS_ALLOW_ABSENT: 1"
        "rm -rf \"\$RUNNER_TEMP/core-app-native-validation-assets\""
        "./build/core_app_asset_bake.exe --output \"\$RUNNER_TEMP/core-app-native-validation-assets\" >\"\$bake_log\" 2>&1"
        "bake_rc=\$?"
        "./build/test_core_app_assets.exe >\"\$test_log\" 2>&1"
        "test_rc=\$?"
        "cat \"\$bake_log\""
        "cat \"\$test_log\""
        "first_failure=\$(grep -m1 'FAIL:' \"\$bake_log\" || grep -m1 'FAIL:' \"\$test_log\" || true)"
        "if [ \"\$bake_rc\" -ne 0 ] || [ \"\$test_rc\" -ne 0 ]; then")
    require_text("${windows}" "${required}" "Windows MSVC job")
endforeach()
require_order("${windows}" "./build/core_app_asset_bake.exe"
    "./build/test_core_app_assets.exe" "Windows MSVC job")
require_order("${windows}" "./build/test_core_app_assets.exe"
    "cat \"\$bake_log\"" "Windows MSVC job")
require_order("${windows}" "cat \"\$bake_log\""
    "cat \"\$test_log\"" "Windows MSVC job")
require_order("${windows}" "cat \"\$test_log\""
    "first_failure=\$(grep -m1 'FAIL:'" "Windows MSVC job")
foreach(forbidden IN ITEMS "| head" "| tail" "head -" "tail -")
    string(FIND "${windows}" "${forbidden}" truncation_offset)
    if(NOT truncation_offset EQUAL -1)
        fail("Windows MSVC job truncates native diagnostics: ${forbidden}")
    endif()
endforeach()

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
string(REPLACE "branches: [master, core-app-ci-validation]"
    "branches: [master]" d3d12_without_validation "${d3d12}")
string(SHA256 d3d12_base_hash "${d3d12_without_validation}")
if(NOT d3d12_base_hash STREQUAL "11344c7bda647136befef9d1d97906b103b2774874813a360d6fbaeae747d412")
    fail("D3D12 jobs or evidence semantics changed beyond the validation trigger")
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
