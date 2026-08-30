if(NOT DEFINED MYR_CMAKE)
    message(FATAL_ERROR "MYR_CMAKE is required")
endif()
if(NOT DEFINED MYUI_CMAKE)
    message(FATAL_ERROR "MYUI_CMAKE is required")
endif()

file(READ "${MYR_CMAKE}" myr_cmake)
file(READ "${MYUI_CMAKE}" myui_cmake)

foreach(required_text
        "MYUI_THIRD_PARTY_DIR"
        "CMAKE_CURRENT_LIST_DIR}/../../../external"
        "find_package(Freetype QUIET)"
        "if(Freetype_FOUND)"
        "Freetype::Freetype"
        "MYUI_HARFBUZZ"
        "find_package(harfbuzz CONFIG QUIET)"
        "PkgConfig::HARFBUZZ")
    string(FIND "${myr_cmake}" "${required_text}" text_offset)
    if(text_offset EQUAL -1)
        message(FATAL_ERROR "myr dependency contract missing: ${required_text}")
    endif()
endforeach()

if(myr_cmake MATCHES "pkg_check_modules\\(FREETYPE[ \t]+freetype2\\)")
    message(FATAL_ERROR "myr must not require pkg-config for FreeType")
endif()

if(myr_cmake MATCHES "CMAKE_SOURCE_DIR}/3rd")
    message(FATAL_ERROR "myr must not hard-code third-party paths from CMAKE_SOURCE_DIR")
endif()

foreach(required_text
        "MYUI_THIRD_PARTY_DIR"
        "CMAKE_CURRENT_LIST_DIR}/../../../external")
    string(FIND "${myui_cmake}" "${required_text}" text_offset)
    if(text_offset EQUAL -1)
        message(FATAL_ERROR "myui dependency contract missing: ${required_text}")
    endif()
endforeach()

if(myui_cmake MATCHES "CMAKE_SOURCE_DIR}/3rd")
    message(FATAL_ERROR "myui must not hard-code third-party paths from CMAKE_SOURCE_DIR")
endif()
