# Fails when sources or docs contain mojibake: UTF-8 text that was decoded as
# GBK/CP936 and saved again. The typical victims are punctuation such as
# U+2014 EM DASH (UTF-8 E2 80 94), which turns into "閳?" or "鈥?". The markers
# below are the GBK readings of the lead bytes of common UTF-8 punctuation;
# real Chinese text in this repository does not use them.
#
# Usage: cmake -DREPO_ROOT=<repo> -P test_source_encoding.cmake

if(NOT DEFINED REPO_ROOT)
    message(FATAL_ERROR "REPO_ROOT is required")
endif()

set(markers "閳" "鈥" "锛" "銆" "鍦" "绋嬪" "鏄剧")

file(GLOB_RECURSE files
    "${REPO_ROOT}/engine/src/*.c" "${REPO_ROOT}/engine/src/*.h"
    "${REPO_ROOT}/engine/apps/*.c" "${REPO_ROOT}/engine/apps/*.h"
    "${REPO_ROOT}/engine/tests/*.c" "${REPO_ROOT}/engine/tests/*.h"
    "${REPO_ROOT}/engine/shaders/*"
    "${REPO_ROOT}/docs/*.md")
list(FILTER files EXCLUDE REGEX "/external/|/third_party/")
# this file names the markers on purpose
list(FILTER files EXCLUDE REGEX "test_source_encoding\\.cmake$")

set(bad "")
foreach(f IN LISTS files)
    file(READ "${f}" text)
    foreach(m IN LISTS markers)
        string(FIND "${text}" "${m}" pos)
        if(NOT pos EQUAL -1)
            file(RELATIVE_PATH rel "${REPO_ROOT}" "${f}")
            list(APPEND bad "${rel} (contains '${m}')")
            break()
        endif()
    endforeach()
endforeach()

list(LENGTH files n)
if(bad)
    list(JOIN bad "\n  " bad_text)
    message(FATAL_ERROR "mojibake (UTF-8 read as GBK) found in:\n  ${bad_text}")
endif()
message(STATUS "source encoding scan passed (${n} files)")
