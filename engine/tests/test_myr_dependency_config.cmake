if(NOT DEFINED MYR_CMAKE)
    message(FATAL_ERROR "MYR_CMAKE is required")
endif()

file(READ "${MYR_CMAKE}" myr_cmake)

foreach(required_text
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
