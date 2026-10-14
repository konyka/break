foreach(required_var TEST_VULKAN_SOURCE ENGINE_CMAKE CI_WORKFLOW)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()

file(READ "${TEST_VULKAN_SOURCE}" tv_text)
# 两个隔离门必须都在（R588 point-shadow 门 / R580 deferred G-Buffer 门）。
foreach(required_token
        "getenv(\"TV_ONLY_PSHADOW\")" "getenv(\"TV_ONLY_GBUFFER\")"
        "R588" "R580")
    string(FIND "${tv_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR
            "test_vulkan.c isolation gate missing: ${required_token}")
    endif()
endforeach()
# 隔离门必须保持「环境变量驱动、仅诊断用途」：CMake 与 CI 一律不得引用
#（一旦被 CI 引用，子集会伪装成全量证据）。
foreach(build_file "${ENGINE_CMAKE}" "${CI_WORKFLOW}")
    file(READ "${build_file}" build_text)
    string(FIND "${build_text}" "TV_ONLY" tv_offset)
    if(NOT tv_offset EQUAL -1)
        message(FATAL_ERROR
            "TV_ONLY_* isolation gates must not be referenced by build/CI files: ${build_file}")
    endif()
endforeach()
