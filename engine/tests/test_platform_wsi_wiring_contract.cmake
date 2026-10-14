foreach(required_var PLATFORM_H WSI_H WIN32_SOURCE X11_SOURCE WAYLAND_SOURCE
                     COCOA_SOURCE MOBILE_SOURCE RHI_SOURCE RHI_INTERNAL_HEADER MAIN_SOURCE)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "${required_var} is required")
    endif()
endforeach()

# platform.h：只增不改——既有签名 token 必须还在。
file(READ "${PLATFORM_H}" platform_text)
foreach(required_token
        "platform_wsi_surface_query" "platform_wsi_surface("
        "platform_mobile_notify_suspend" "platform_mobile_notify_resume"
        "platform_mobile_notify_surface_lost" "platform_mobile_notify_surface_recreated"
        "platform_window_native" "platform_display_native" "platform_surface_native")
    string(FIND "${platform_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "platform.h missing token: ${required_token}")
    endif()
endforeach()

# platform_wsi.h：两个新判定函数；OHOS 不得进入后端枚举。
file(READ "${WSI_H}" wsi_text)
foreach(required_token "platform_wsi_frame_allowed" "platform_wsi_rhi_teardown_allowed")
    string(FIND "${wsi_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "platform_wsi.h missing: ${required_token}")
    endif()
endforeach()
string(FIND "${wsi_text}" "PLATFORM_WSI_BACKEND_OHOS" ohos_offset)
if(NOT ohos_offset EQUAL -1)
    message(FATAL_ERROR "OHOS must stay out of PlatformWsiBackend (fail-closed)")
endif()

# 五个窗口后端的接线 token。
foreach(backend_spec
        "${WIN32_SOURCE}|platform_wsi_surface_suspend"
        "${WIN32_SOURCE}|platform_wsi_surface_resize"
        "${X11_SOURCE}|platform_wsi_surface_resize"
        "${WAYLAND_SOURCE}|platform_wsi_surface_resize"
        "${COCOA_SOURCE}|platform_wsi_surface_resize"
        "${MOBILE_SOURCE}|platform_mobile_notify_suspend"
        "${MOBILE_SOURCE}|platform_mobile_notify_resume"
        "${MOBILE_SOURCE}|platform_mobile_notify_surface_lost"
        "${MOBILE_SOURCE}|platform_mobile_notify_surface_recreated")
    string(REPLACE "|" ";" backend_parts "${backend_spec}")
    list(GET backend_parts 0 backend_path)
    list(GET backend_parts 1 backend_token)
    file(READ "${backend_path}" backend_text)
    string(FIND "${backend_text}" "${backend_token}" backend_offset)
    if(backend_offset EQUAL -1)
        message(FATAL_ERROR
            "WSI wiring missing: ${backend_path} <- ${backend_token}")
    endif()
endforeach()
foreach(backend_path
        "${WIN32_SOURCE}" "${X11_SOURCE}" "${WAYLAND_SOURCE}"
        "${COCOA_SOURCE}" "${MOBILE_SOURCE}")
    file(READ "${backend_path}" backend_text)
    foreach(lifecycle_token
            "platform_wsi_surface_init" "platform_wsi_surface_destroy"
            "platform_wsi_surface_query")
        string(FIND "${backend_text}" "${lifecycle_token}" offset)
        if(offset EQUAL -1)
            message(FATAL_ERROR
                "WSI wiring missing: ${backend_path} <- ${lifecycle_token}")
        endif()
    endforeach()
endforeach()

# RHI 侧：挂载点 + DESTROYING 门。
file(READ "${RHI_INTERNAL_HEADER}" internal_text)
string(FIND "${internal_text}" "PlatformWsiSurface *wsi" internal_offset)
if(internal_offset EQUAL -1)
    message(FATAL_ERROR "RHIDevice must carry a PlatformWsiSurface attachment")
endif()
file(READ "${RHI_SOURCE}" rhi_text)
foreach(required_token "rhi_device_attach_wsi" "platform_wsi_rhi_teardown_allowed")
    string(FIND "${rhi_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "rhi.c missing: ${required_token}")
    endif()
endforeach()
file(READ "${MAIN_SOURCE}" main_text)
foreach(required_token "rhi_device_attach_wsi" "rhi_device_destroy_ex")
    string(FIND "${main_text}" "${required_token}" offset)
    if(offset EQUAL -1)
        message(FATAL_ERROR "main.c missing: ${required_token}")
    endif()
endforeach()
