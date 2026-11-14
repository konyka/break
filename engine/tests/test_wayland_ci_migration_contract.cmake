if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()
if(NOT DEFINED REPO_ROOT)
    message(FATAL_ERROR "REPO_ROOT is required")
endif()

function(contract_failure message_text)
    set_property(GLOBAL APPEND PROPERTY WAYLAND_CI_CONTRACT_FAILURES "${message_text}")
endfunction()

function(read_repo_file relative_path out_var)
    set(path "${REPO_ROOT}/${relative_path}")
    if(NOT EXISTS "${path}")
        contract_failure("missing file: ${relative_path}")
        set(${out_var} "" PARENT_SCOPE)
        return()
    endif()
    file(READ "${path}" contents)
    set(${out_var} "${contents}" PARENT_SCOPE)
endfunction()

function(require_contents relative_path text description)
    read_repo_file("${relative_path}" contents)
    string(FIND "${contents}" "${text}" offset)
    if(offset EQUAL -1)
        contract_failure("${relative_path}: missing ${description}: ${text}")
    endif()
endfunction()

function(forbid_contents relative_path text description)
    read_repo_file("${relative_path}" contents)
    string(FIND "${contents}" "${text}" offset)
    if(NOT offset EQUAL -1)
        contract_failure("${relative_path}: ${description}: ${text}")
    endif()
endfunction()

set(ci_path ".github/workflows/ci.yml")
read_repo_file("${ci_path}" ci)
foreach(forbidden IN ITEMS X11 x11 Xvfb xvfb "DISPLAY=:99" xdpyinfo)
    string(FIND "${ci}" "${forbidden}" offset)
    if(NOT offset EQUAL -1)
        contract_failure("${ci_path}: current workflow retains ${forbidden}")
    endif()
endforeach()

function(extract_ci_job job out_var)
    set(marker "\n  ${job}:\n")
    string(FIND "${ci}" "${marker}" start)
    if(start EQUAL -1)
        contract_failure("${ci_path}: missing current job ${job}")
        set(${out_var} "" PARENT_SCOPE)
        return()
    endif()
    string(LENGTH "${marker}" marker_length)
    math(EXPR body_start "${start} + ${marker_length}")
    string(SUBSTRING "${ci}" ${body_start} -1 remainder)
    string(REGEX MATCH "\n  [A-Za-z0-9_-]+:\n" next_marker "${remainder}")
    if(next_marker)
        string(FIND "${remainder}" "${next_marker}" body_length)
    else()
        set(body_length -1)
    endif()
    string(SUBSTRING "${remainder}" 0 ${body_length} body)
    set(${out_var} "${body}" PARENT_SCOPE)
endfunction()

function(require_lane job execution_token)
    extract_ci_job("${job}" block)
    if(block STREQUAL "")
        return()
    endif()
    foreach(required IN ITEMS
            "Linux Wayland"
            "weston --backend=headless-backend.so"
            "export XDG_RUNTIME_DIR="
            "export WAYLAND_DISPLAY="
            "test -S \"\$XDG_RUNTIME_DIR/\$WAYLAND_DISPLAY\""
            "id: graphics"
            "continue-on-error: true"
            "${execution_token}"
            "grep -c '\\*\\*\\*Skipped'"
            "grep -c '   Passed'"
            "echo \"rc=\$rc\" >> \"\$GITHUB_OUTPUT\""
            "echo \"skipped=\$skipped\" >> \"\$GITHUB_OUTPUT\""
            "echo \"passed=\$passed\" >> \"\$GITHUB_OUTPUT\""
            "steps.graphics.outputs.rc"
            "steps.graphics.outputs.skipped"
            "steps.graphics.outputs.passed"
            "[ \"\$skipped\" = \"0\" ] && [ \"\$passed\" -gt 0 ]"
            "-DPLATFORM=linux-wayland"
            "test \"\${{ steps.graphics.outputs.rc }}\" = \"0\""
            "test \"\${{ steps.graphics.outputs.passed }}\" -gt 0"
            "test \"\${{ steps.graphics.outputs.skipped }}\" = \"0\"")
        string(FIND "${block}" "${required}" offset)
        if(offset EQUAL -1)
            contract_failure("${job}: missing ${required}")
        endif()
    endforeach()
endfunction()

require_lane(lane-gpu-runtime-linux-gl "test_rhi_wayland_runtime")
require_lane(lane-gpu-runtime-linux-vk "ctest --test-dir build -L graphics")
require_lane(lane-validation-linux-vk "VK_LAYER_KHRONOS_validation")
require_lane(lane-benchmark-linux-vk "ctest --test-dir build -L benchmark")

extract_ci_job(lane-gpu-runtime-linux-gl gl_block)
foreach(required_test test_mesh_gpu_gl test_world_presentation_gl test_mycompose_gpu_opengl)
    string(FIND "${gl_block}" "${required_test}" offset)
    if(offset EQUAL -1)
        contract_failure("lane-gpu-runtime-linux-gl: missing real GL coverage ${required_test}")
    endif()
endforeach()

# The Vulkan lane runs `-L graphics`; the Compose GPU test must carry it.
read_repo_file("engine/CMakeLists.txt" engine_cmake)
string(FIND "${engine_cmake}" "set(compose_gpu_target test_mycompose_gpu_\${compose_gpu_variant})" offset)
string(FIND "${engine_cmake}" "LABELS \"graphics;compose;platform_runtime\"" compose_labels)
if(offset EQUAL -1 OR compose_labels EQUAL -1)
    contract_failure("engine/CMakeLists.txt: test_mycompose_gpu_<backend> must be registered with the graphics label")
endif()

# Compose fuzz smokes are EXCLUDE_FROM_ALL: every lane that builds the fuzz
# targets explicitly must name these too, or `-L fuzz` ends in Not Run.
foreach(required_fuzz fuzz_mycompose_tree fuzz_mycompose_intent
        fuzz_core_app_checkpoint fuzz_core_app_scenario fuzz_core_app_network)
    string(REGEX MATCHALL "${required_fuzz}" fuzz_hits "${ci}")
    list(LENGTH fuzz_hits fuzz_hit_count)
    if(fuzz_hit_count LESS 3)
        contract_failure("${ci_path}: ${required_fuzz} appears ${fuzz_hit_count} times; expected the asan list and both build steps")
    endif()
endforeach()

extract_ci_job(lane-benchmark-steam-deck-vk deck_block)
foreach(required IN ITEMS
        "libwayland-dev" "wayland-protocols" "libxkbcommon-dev" "weston"
        "weston --backend=headless-backend.so" "-DPLATFORM=linux-wayland")
    string(FIND "${deck_block}" "${required}" offset)
    if(offset EQUAL -1)
        contract_failure("lane-benchmark-steam-deck-vk: missing ${required}")
    endif()
endforeach()

extract_ci_job(lane-proton proton_block)
foreach(required IN ITEMS "wayland-scanner" "pkg-config" "UNAVAILABLE")
    string(FIND "${proton_block}" "${required}" offset)
    if(offset EQUAL -1)
        contract_failure("lane-proton: missing explicit Wayland availability gate ${required}")
    endif()
endforeach()

foreach(config_file IN ITEMS
        ".github/workflows/ci-image.yml"
        ".github/workflows/rollback-drill.yml"
        ".github/docker/ci-linux.Dockerfile")
    read_repo_file("${config_file}" contents)
    foreach(forbidden IN ITEMS
            X11 x11 Xvfb xvfb libx11-dev libxrandr-dev libxi-dev libxtst-dev)
        string(FIND "${contents}" "${forbidden}" offset)
        if(NOT offset EQUAL -1)
            contract_failure("${config_file}: retains direct legacy dependency ${forbidden}")
        endif()
    endforeach()
endforeach()

foreach(required IN ITEMS libwayland-dev wayland-protocols libxkbcommon-dev weston
        libgl1-mesa-dev libegl1-mesa-dev libvulkan-dev mesa-vulkan-drivers)
    require_contents(".github/docker/ci-linux.Dockerfile" "${required}" "Wayland/Mesa/Vulkan dependency")
endforeach()
foreach(required IN ITEMS "command -v weston" "command -v wayland-scanner")
    require_contents(".github/workflows/ci-image.yml" "${required}" "image smoke check")
endforeach()

read_repo_file(".github/workflows/rollback-drill.yml" rollback)
foreach(required IN ITEMS
        "Validate supported rollback tag"
        "BASH_REMATCH[1]"
        "2.0.0"
        "UNAVAILABLE"
        "libwayland-dev"
        "wayland-protocols"
        "libxkbcommon-dev")
    string(FIND "${rollback}" "${required}" offset)
    if(offset EQUAL -1)
        contract_failure("rollback-drill.yml: missing ${required}")
    endif()
endforeach()
string(FIND "${rollback}" "Validate supported rollback tag" validate_offset)
string(FIND "${rollback}" "actions/checkout" checkout_offset)
if(validate_offset EQUAL -1 OR checkout_offset EQUAL -1 OR validate_offset GREATER checkout_offset)
    contract_failure("rollback-drill.yml: version floor must run before checkout")
endif()

foreach(spec IN ITEMS
        "README.md|an X11 OpenGL build"
        "README.md|on X11 and Wayland"
        "README.md|Linux X11 CI"
        "docs/Build_Guide.md|GCC X11/OpenGL"
        "docs/Build_Guide.md|关闭时使用 X11"
        "docs/Build_Guide.md|默认为 OFF（使用 X11）"
        "docs/Build_Guide.md|X11 + Vulkan"
        "docs/Build_Guide.md|X11 + OpenGL"
        "docs/Build_Guide.md|Linux (X11)"
        "docs/Build_Guide.md|显式启动 Xvfb"
        "docs/Architecture_Overview.md|window_x11"
        "docs/Architecture_Overview.md|X11 / Wayland"
        "docs/Architecture_Overview.md|X11 + OpenGL"
        "docs/Architecture_Overview.md|X11 + Vulkan"
        "docs/Architecture_Overview.md|Linux 的 X11、Wayland"
        "docs/Engine_Modules.md|window_x11.c"
        "docs/Engine_Modules.md|X11 返回"
        "docs/Engine_Modules.md|调用 X11/Wayland"
        "docs/index.md|X11/Wayland/Win32/Cocoa"
        "docs/myui_echart_usage.md|--platform x11"
        "docs/myui_echart_usage.md|XImage blit on X11"
        "docs/myui_echart_usage.md|x11 + software"
        "docs/vulkan_support_matrix.md|原生（Xcb surface）"
        "docs/vulkan_support_matrix.md|X11=`VK_KHR_xlib_surface`"
        "docs/rhi_benchmark_receipt_schema.md|\"platform\": \"linux-x11\""
        "docs/design/input_extended.md|XInput2/X11"
        "docs/design/input_extended.md|### X11"
        "docs/design/rhi_runtime_backend.md|X11 gives both"
        "docs/cross_engine/missing_capabilities.md|列出 X11、Wayland"
        "docs/qnx_compat.md|与 X11 约定一致"
        "docs/qnx_compat.md|与 X11 相同的引擎键码")
    string(REPLACE "|" ";" parts "${spec}")
    list(GET parts 0 path)
    list(GET parts 1 old_claim)
    forbid_contents("${path}" "${old_claim}" "current support claim remains")
endforeach()

foreach(spec IN ITEMS
        "README.md|native Wayland only"
        "docs/Build_Guide.md|Linux 仅支持原生 Wayland"
        "docs/Architecture_Overview.md|Wayland（Linux 唯一窗口系统）"
        "docs/Engine_Modules.md|Linux 唯一窗口后端"
        "docs/design/input_extended.md|Historical X11/XI2 backend (pre-2.0.0)"
        "docs/design/input_extended.md|Historical verification evidence (pre-2.0.0)"
        "docs/myui_integration.md|X11 support was removed"
        "docs/myui_remaining_work.md|历史条目中的 X11"
        "docs/rhi_backend_evidence.md|历史 CI 证据（保留原文，非当前支持）")
    string(REPLACE "|" ";" parts "${spec}")
    list(GET parts 0 path)
    list(GET parts 1 current_claim)
    require_contents("${path}" "${current_claim}" "current Wayland-only statement")
endforeach()

get_property(failure_lines GLOBAL PROPERTY WAYLAND_CI_CONTRACT_FAILURES)
if(failure_lines)
    string(REPLACE ";" "\n" failures "${failure_lines}")
    message(FATAL_ERROR "Wayland CI/version/document migration contract failed:\n${failures}\n")
endif()
message(STATUS "Wayland CI and current-document contract OK")
