if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()
if(NOT DEFINED ENGINE_SOURCE_DIR)
    message(FATAL_ERROR "ENGINE_SOURCE_DIR is required")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)
foreach(required_text
        "set(ENGINE_RHI_BACKEND \"auto\" CACHE STRING"
        "set(ENGINE_RHI_BACKEND_EFFECTIVE"
        "RHI backend: requested="
        "ENGINE_RHI_BACKEND must be auto, opengl, or vulkan"
        "ENGINE_RHI_BACKEND STREQUAL \"vulkan\""
        "ENGINE_RHI_BACKEND STREQUAL \"opengl\"")
    string(FIND "${cmake_text}" "${required_text}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "RHI backend selection contract missing: ${required_text}")
    endif()
endforeach()

foreach(forbidden_backend "metal" "d3d12")
    if(cmake_text MATCHES "ENGINE_RHI_BACKEND[ \t]*STREQUAL[ \t]*\"${forbidden_backend}\"")
        message(FATAL_ERROR "unimplemented backend selector admitted: ${forbidden_backend}")
    endif()
endforeach()

if(cmake_text MATCHES "ENGINE_RHI_BACKEND.*metal" OR
   cmake_text MATCHES "ENGINE_RHI_BACKEND.*d3d12")
    message(FATAL_ERROR "RHI selector must not claim unimplemented native backends")
endif()
