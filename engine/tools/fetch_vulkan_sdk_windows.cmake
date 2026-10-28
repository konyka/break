# Fetches and silently installs the pinned LunarG Vulkan SDK on Windows CI
# runners (windows-latest ships no Vulkan SDK / shaderc). Pattern follows
# fetch_d3d12_agility_sdk.cmake: pinned version + pinned SHA256, TLS verify,
# fail-closed. Bump _version and _sha256 together; recompute the hash with
#   certutil -hashfile vulkan-sdk-<version>.exe SHA256
# after downloading https://sdk.lunarg.com/sdk/download/<version>/windows/vulkan-sdk.exe
set(_version "1.4.321.0")
set(_sha256 "14ebc56ef981e03a292adadd2559fbbfcd0289ec157bfd0f0d5f9fdcb40042a9")
set(_url "https://sdk.lunarg.com/sdk/download/${_version}/windows/vulkan-sdk.exe")
set(_installer "${CMAKE_BINARY_DIR}/vulkan-sdk-${_version}.exe")
set(_root "C:/VulkanSDK/${_version}")

# The installer registers vulkan-1.dll in System32; the engine needs the
# import libraries, headers and shaderc under the SDK root.
set(_required
    "${_root}/Lib/vulkan-1.lib"
    "${_root}/Lib/shaderc_shared.lib"
    "${_root}/Include/vulkan/vulkan.h"
    "${_root}/Include/shaderc/shaderc.h")

set(_already_installed TRUE)
foreach(_f IN LISTS _required)
    if(NOT EXISTS "${_f}")
        set(_already_installed FALSE)
    endif()
endforeach()

if(NOT _already_installed)
    if(NOT EXISTS "${_installer}")
        # sdk.lunarg.com drops connections now and then ("Failure when receiving
        # data from the peer", curl 56) and can stall. EXPECTED_HASH on
        # file(DOWNLOAD) turns any failed transfer into an immediate fatal error,
        # so it cannot be retried; download without it, retry the transfer, and
        # verify the pinned SHA256 myself after each completed attempt. A hash
        # mismatch is never retried: it is fail-closed, same as before.
        set(_code 1)
        foreach(_attempt RANGE 1 4)
            message(STATUS "Downloading Vulkan SDK ${_version} from ${_url} (attempt ${_attempt}/4)")
            file(DOWNLOAD "${_url}" "${_installer}" STATUS _st TLS_VERIFY ON
                INACTIVITY_TIMEOUT 60)
            list(GET _st 0 _code)
            if(_code EQUAL 0)
                break()
            endif()
            file(REMOVE "${_installer}")
            message(WARNING "Vulkan SDK download attempt ${_attempt} failed: ${_st}")
            if(_attempt LESS 4)
                execute_process(COMMAND "${CMAKE_COMMAND}" -E sleep 15)
            endif()
        endforeach()
        if(NOT _code EQUAL 0)
            message(FATAL_ERROR "Vulkan SDK download failed after 4 attempts: ${_st}")
        endif()
        file(SHA256 "${_installer}" _downloaded_sha)
        if(NOT _downloaded_sha STREQUAL _sha256)
            file(REMOVE "${_installer}")
            message(FATAL_ERROR
                "Vulkan SDK installer hash mismatch (expected ${_sha256}, got ${_downloaded_sha})")
        endif()
    else()
        file(SHA256 "${_installer}" _cached_sha)
        if(NOT _cached_sha STREQUAL _sha256)
            file(REMOVE "${_installer}")
            message(FATAL_ERROR
                "cached Vulkan SDK installer hash mismatch (expected ${_sha256}, got ${_cached_sha}); deleted, re-run to re-download")
        endif()
    endif()

    # Qt Installer Framework unattended install; installs the SDK plus the
    # Vulkan runtime (vulkan-1.dll into System32).
    execute_process(
        COMMAND "${_installer}" --accept-licenses --default-answer
                --confirm-command install
        RESULT_VARIABLE _rc
        OUTPUT_VARIABLE _out
        ERROR_VARIABLE _err
        TIMEOUT 900)
    if(NOT _rc EQUAL 0)
        message(FATAL_ERROR
            "Vulkan SDK installer exited ${_rc}:\n${_out}\n${_err}")
    endif()
endif()

foreach(_f IN LISTS _required)
    if(NOT EXISTS "${_f}")
        message(FATAL_ERROR "Vulkan SDK install incomplete — missing ${_f}")
    endif()
endforeach()
message(STATUS "Vulkan SDK ${_version} ready at ${_root}")

# Export the layout to subsequent workflow steps (no-op locally).
if(DEFINED ENV{GITHUB_ENV})
    file(APPEND "$ENV{GITHUB_ENV}" "VULKAN_SDK=${_root}\n")
endif()
if(DEFINED ENV{GITHUB_PATH})
    # Bin holds shaderc_shared.dll (import-lib consumers need it at runtime).
    file(APPEND "$ENV{GITHUB_PATH}" "${_root}/Bin\n")
endif()
