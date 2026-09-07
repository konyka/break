if(NOT DEFINED MYUI_ROOT_CMAKE)
    message(FATAL_ERROR "MYUI_ROOT_CMAKE is required")
endif()

file(READ "${MYUI_ROOT_CMAKE}" myui_root_cmake)

foreach(required_text
        "project(myui LANGUAGES C)"
        "CMAKE_C_STANDARD 11"
        "CMAKE_C_STANDARD_REQUIRED ON"
        "CMAKE_C_EXTENSIONS OFF"
        "MYUI_FONT_STB"
        "MYUI_FONT_FREETYPE"
        "MYUI_IMAGE_STB"
        "MYUI_UI_YAML"
        "MYUI_BIDI"
        "MYUI_HARFBUZZ"
        "MYUI_GLES2"
        "MYUI_GL_DESKTOP"
        "MYUI_VULKAN"
        "add_subdirectory(myc)"
        "add_subdirectory(myr)"
        "add_subdirectory(mypal)"
        "add_subdirectory(myui)"
        "add_subdirectory(mymvvm)"
        "add_subdirectory(mymvvm_myui)"
        "MYUI_THIRD_PARTY_DIR")
    string(FIND "${myui_root_cmake}" "${required_text}" text_offset)
    if(text_offset EQUAL -1)
        message(FATAL_ERROR "myui subproject contract missing: ${required_text}")
    endif()
endforeach()

if(myui_root_cmake MATCHES "CMAKE_SOURCE_DIR")
    message(FATAL_ERROR "myui subproject must not depend on CMAKE_SOURCE_DIR")
endif()

string(FIND "${myui_root_cmake}" "add_subdirectory(myc)" myc_offset)
string(FIND "${myui_root_cmake}" "add_subdirectory(myr)" myr_offset)
string(FIND "${myui_root_cmake}" "add_subdirectory(mypal)" mypal_offset)
string(FIND "${myui_root_cmake}" "add_subdirectory(myui)" myui_offset)
string(FIND "${myui_root_cmake}" "add_subdirectory(mymvvm)" mymvvm_offset)
string(FIND "${myui_root_cmake}" "add_subdirectory(mymvvm_myui)" mymvvm_ui_offset)
if(NOT myc_offset LESS myr_offset OR
   NOT myr_offset LESS mypal_offset OR
   NOT mypal_offset LESS myui_offset OR
   NOT myui_offset LESS mymvvm_offset OR
   NOT mymvvm_offset LESS mymvvm_ui_offset)
    message(FATAL_ERROR "myui subproject dependency order is invalid")
endif()
