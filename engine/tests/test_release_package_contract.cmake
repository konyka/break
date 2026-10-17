# Contract test: release packaging script carries the full offline content list.
# -DPACKAGER=<abs engine/tools/package_release.sh> -DENGINE_CMAKE=<abs engine/CMakeLists.txt>
if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()
if(POLICY CMP0140)
    cmake_policy(SET CMP0140 NEW)
endif()
if(NOT DEFINED PACKAGER OR NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "PACKAGER and ENGINE_CMAKE are required")
endif()
if(NOT EXISTS "${PACKAGER}")
    message(FATAL_ERROR "release packager missing: ${PACKAGER}")
endif()
file(READ "${PACKAGER}" pk)
foreach(item "SHA256SUMS" "MANIFEST" "D3D12Core" "metallib" ".dxil" ".spv"
             "rhi_backend_rollout.json" "locked_dependencies.json" "receipt")
    string(FIND "${pk}" "${item}" off)
    if(off EQUAL -1)
        message(FATAL_ERROR "packager does not handle required content: ${item}")
    endif()
endforeach()
if(pk MATCHES "latest")
    message(FATAL_ERROR "packager must not reference 'latest'")
endif()
file(READ "${ENGINE_CMAKE}" cm)
if(NOT cm MATCHES "project\\(PureCEngine VERSION [0-9]+\\.[0-9]+\\.[0-9]+")
    message(FATAL_ERROR "engine/CMakeLists.txt project() must carry an explicit semver VERSION")
endif()

# tag 名 v<x.y.z> 必须与 project() VERSION 相等；HEAD 无 tag 时跳过（发布前由
# git tag -v 人工核验，见 runbook §5；tag 由 maintainer 在发布时创建——Task 9
# 本身不打 tag，本机无 maintainer GPG 私钥）。
get_filename_component(engine_dir "${ENGINE_CMAKE}" DIRECTORY)
execute_process(COMMAND git tag --points-at HEAD
    WORKING_DIRECTORY "${engine_dir}" OUTPUT_VARIABLE tags_out
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
if(tags_out)
    string(REGEX MATCH "project\\(PureCEngine VERSION ([0-9]+\\.[0-9]+\\.[0-9]+)" vm "${cm}")
    set(proj_ver "${CMAKE_MATCH_1}")
    string(REPLACE "\n" ";" tag_list "${tags_out}")
    if(NOT "v${proj_ver}" IN_LIST tag_list)
        message(FATAL_ERROR "HEAD tag list (${tags_out}) does not contain v${proj_ver}")
    endif()
endif()
message(STATUS "release package contract OK")
