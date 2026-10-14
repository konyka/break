foreach(required_var SIZE_HEADER WIN32_SOURCE X11_SOURCE WAYLAND_SOURCE COCOA_SOURCE)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()
if(NOT EXISTS "${SIZE_HEADER}")
    message(FATAL_ERROR "missing: ${SIZE_HEADER}")
endif()
file(READ "${SIZE_HEADER}" size_text)
foreach(required_fn
        "platform_size_win32" "platform_size_x11"
        "platform_size_wayland" "platform_size_cocoa")
    string(FIND "${size_text}" "${required_fn}" fn_offset)
    if(fn_offset EQUAL -1)
        message(FATAL_ERROR "platform_size.h missing: ${required_fn}")
    endif()
endforeach()
foreach(consumer_spec
        "${WIN32_SOURCE}|platform_size_win32"
        "${X11_SOURCE}|platform_size_x11"
        "${WAYLAND_SOURCE}|platform_size_wayland"
        "${COCOA_SOURCE}|platform_size_cocoa")
    string(REPLACE "|" ";" consumer_parts "${consumer_spec}")
    list(GET consumer_parts 0 consumer_path)
    list(GET consumer_parts 1 consumer_token)
    file(READ "${consumer_path}" consumer_text)
    string(FIND "${consumer_text}" "${consumer_token}" consumer_offset)
    if(consumer_offset EQUAL -1)
        message(FATAL_ERROR
            "window backend must consume the shared size helper: ${consumer_path} <- ${consumer_token}")
    endif()
endforeach()
