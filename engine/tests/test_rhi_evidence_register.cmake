if(NOT DEFINED REPO_ROOT)
    message(FATAL_ERROR "REPO_ROOT is required")
endif()
if(NOT DEFINED EVIDENCE_DOC)
    message(FATAL_ERROR "EVIDENCE_DOC is required")
endif()
if(NOT EXISTS "${EVIDENCE_DOC}")
    message(FATAL_ERROR "evidence register missing: ${EVIDENCE_DOC}")
endif()
file(READ "${EVIDENCE_DOC}" evidence_text)
foreach(required_row
        "Linux X11 × OpenGL"
        "Linux X11 × Vulkan"
        "Linux Wayland × GL/VK"
        "Windows × Vulkan"
        "Windows × D3D12"
        "macOS × Vulkan(MoltenVK)"
        "macOS/iOS × 原生 Metal"
        "Android × Vulkan"
        "iOS × Vulkan(MoltenVK)"
        "OHOS")
    string(FIND "${evidence_text}" "${required_row}" row_offset)
    if(row_offset EQUAL -1)
        message(FATAL_ERROR "evidence register missing platform/backend row: ${required_row}")
    endif()
endforeach()
foreach(required_level
        "NONE" "COMPILED" "HEADLESS" "NATIVE_SURFACE" "GPU_RUNTIME" "BENCHMARK_COMPARABLE")
    string(FIND "${evidence_text}" "${required_level}" level_offset)
    if(level_offset EQUAL -1)
        message(FATAL_ERROR "evidence register missing evidence-level token: ${required_level}")
    endif()
endforeach()
if(NOT IS_DIRECTORY "${REPO_ROOT}/.scratch-vkprobe")
    message(FATAL_ERROR "frozen evidence directory missing: ${REPO_ROOT}/.scratch-vkprobe")
endif()
if(NOT EXISTS "${REPO_ROOT}/engine/profile_trace.json")
    message(FATAL_ERROR "frozen evidence file missing: ${REPO_ROOT}/engine/profile_trace.json")
endif()
