# break_http target contract: a formal optional static library that no shipped
# binary links, with exactly the documented public surface and no test hooks.
# -DENGINE_CMAKE -DHTTP_ARCHIVE

foreach(var ENGINE_CMAKE HTTP_ARCHIVE)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()
file(READ "${ENGINE_CMAKE}" cmake_text)

if(NOT cmake_text MATCHES "add_library\\(break_http STATIC src/net_http/break_http.c\\)")
    message(FATAL_ERROR "break_http must be a STATIC library owning exactly src/net_http/break_http.c")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(break_http PUBLIC OpenSSL::SSL OpenSSL::Crypto\\)")
    message(FATAL_ERROR "break_http must link OpenSSL::SSL and OpenSSL::Crypto PUBLIC")
endif()
string(REGEX MATCHALL "src/net_http/break_http\\.c" mentions "${cmake_text}")
list(LENGTH mentions n)
if(NOT n EQUAL 1)
    message(FATAL_ERROR "src/net_http/break_http.c must appear exactly once, got ${n}")
endif()

# no shipped binary links the transport; the dev tools that do are named here
string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break|editor)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_http")
        message(FATAL_ERROR "break_http leaked into a shipped binary's link line: ${line}")
    endif()
endforeach()
string(REGEX MATCH "add_library\\(engine STATIC[^)]*\\)" engine_block "${cmake_text}")
if(engine_block MATCHES "net_http")
    message(FATAL_ERROR "engine must not compile src/net_http sources")
endif()

find_program(NM NAMES nm llvm-nm)
if(NOT NM)
    message(FATAL_ERROR "nm not found")
endif()
execute_process(COMMAND ${NM} -g --defined-only --format=posix "${HTTP_ARCHIVE}"
    RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
if(NOT rc EQUAL 0)
    message(FATAL_ERROR "nm failed: ${err}")
endif()
set(expected
    break_http_error_name break_http_get break_http_get_range break_http_post
    break_http_update_fetch break_http_rollout_percent_bp)
string(REPLACE "\n" ";" lines "${out}")
set(actual "")
foreach(line IN LISTS lines)
    if(line MATCHES "^([A-Za-z_][A-Za-z0-9_]*) [TDBR] ")
        set(sym "${CMAKE_MATCH_1}")
        if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
            string(REGEX REPLACE "^_" "" sym "${sym}")
        endif()
        # UCRT <stdio.h> inline helpers are emitted as external definitions by clang
        # on Windows; they are header artifacts, not library API.
        if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows" AND sym MATCHES
           "^(__local_stdio_printf_options|__local_stdio_scanf_options|_?v?s?n?printf|_?v?snprintf(_l)?|_vsprintf_l|_?sprintf|_vsscanf_l|_?sscanf)$")
            continue()
        endif()
        list(APPEND actual "${sym}")
    endif()
endforeach()
list(SORT actual)
list(SORT expected)
if(NOT actual STREQUAL expected)
    message(FATAL_ERROR "break_http exports differ.\n  actual:   ${actual}\n  expected: ${expected}")
endif()
foreach(sym IN LISTS actual)
    if(sym MATCHES "for_test|_test_|testing|insecure|noverify|no_verify")
        message(FATAL_ERROR "break_http exports a test hook or an insecure switch: ${sym}")
    endif()
endforeach()

# the TLS policy is in the source, not in a flag: pin the three lines that matter
get_filename_component(ENGINE_DIR "${ENGINE_CMAKE}" DIRECTORY)
file(READ "${ENGINE_DIR}/src/net_http/break_http.c" src)
foreach(needle "SSL_VERIFY_PEER" "TLS1_2_VERSION" "SSL_set1_host" "X509_V_OK")
    if(NOT src MATCHES "${needle}")
        message(FATAL_ERROR "break_http.c lost its TLS rule: ${needle}")
    endif()
endforeach()
if(src MATCHES "SSL_VERIFY_NONE" OR src MATCHES "SSL_CTX_set_default_verify_paths")
    message(FATAL_ERROR "break_http.c weakens verification or uses the system trust store")
endif()

message(STATUS "break_http contract OK")
