#ifdef ENGINE_PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

/* ---- High-DPI compatibility shims (for older Windows SDKs) ---- */
#ifndef DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
typedef HANDLE DPI_AWARENESS_CONTEXT;
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#endif

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0
#endif

#include <platform/platform.h>
#include <platform/input.h>
#include <core/types.h>
#include <core/log.h>
#include "gamepad_linux.h"  /* shared gamepad API; Windows impl in gamepad_win.c */

#include <stdlib.h>
#include <string.h>

struct Platform {
    HINSTANCE   hinstance;
    HWND        hwnd;
    HDC         hdc;
    InputState  input;
    u32         width, height;
    bool        should_close;
    bool        is_fullscreen;
    bool        mouse_relative;
    RECT        windowed_rect;
    DWORD       windowed_style;
};

/* ---- Key mapping ---- */

static i32 win_vk_to_index(i32 vk_code) {
    if (vk_code >= 'A' && vk_code <= 'Z') return vk_code - 'A' + 'a';
    if (vk_code >= '0' && vk_code <= '9') return vk_code;

    switch (vk_code) {
    case VK_ESCAPE:   return 256;
    case VK_SPACE:    return 32;
    case VK_RETURN:   return 257;
    case VK_TAB:      return 259;
    case VK_BACK:     return 260;
    case VK_LEFT:     return 261;
    case VK_RIGHT:    return 262;
    case VK_UP:       return 263;
    case VK_DOWN:     return 264;
    case VK_F1:       return 271;
    case VK_F2:       return 272;
    case VK_F3:       return 273;
    case VK_F4:       return 274;
    case VK_F5:       return 275;
    case VK_F6:       return 276;
    case VK_F7:       return 277;
    case VK_F8:       return 278;
    case VK_F9:       return 279;
    case VK_F10:      return 280;
    case VK_F11:      return 281;
    case VK_F12:      return 282;
    case VK_PRIOR:    return 283;
    case VK_NEXT:     return 284;
    case VK_HOME:     return 285;
    case VK_END:      return 286;
    case VK_INSERT:   return 287;
    case VK_DELETE:   return 288;
    case VK_LSHIFT:   return 289;
    case VK_RSHIFT:   return 289;
    case VK_LCONTROL: return 290;
    case VK_RCONTROL: return 290;
    /* R360: disambiguate End/Insert dual-binds in main (reset/DOF/water). */
    case VK_PAUSE:    return 291;
    case VK_SCROLL:   return 292;
    case VK_NUMLOCK:  return 293;
    case VK_CAPITAL:  return 294;
    case VK_APPS:     return 295; /* R361: SSGI (was '[') */
    case VK_MULTIPLY: return 296; /* R361: SSS */
    case VK_DIVIDE:   return 297; /* R361: lens flare */
    case VK_SUBTRACT: return 298; /* R361: sharpen */
    case VK_ADD:      return 299; /* R361: contact shadow */
    case VK_OEM_MINUS:  return 45;
    case VK_OEM_PLUS:   return 61;
    case VK_OEM_4:      return 91;
    case VK_OEM_6:      return 93;
    case VK_OEM_1:      return 59;
    case VK_OEM_7:      return 39;
    case VK_OEM_COMMA:  return 44;
    case VK_OEM_PERIOD: return 46;
    case VK_OEM_2:      return 47;
    case VK_OEM_3:      return 96;
    default:            return -1;
    }
}

/* ---- Window procedure ---- */

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    Platform *p = (Platform *)GetWindowLongPtrA(hwnd, GWLP_USERDATA);

    if (!p) return DefWindowProcA(hwnd, msg, wParam, lParam);

    switch (msg) {
    case WM_CLOSE:
        p->should_close = true;
        return 0;

    case WM_SIZE:
        p->width  = (u32)LOWORD(lParam);
        p->height = (u32)HIWORD(lParam);
        return 0;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN: {
        i32 idx = win_vk_to_index((i32)wParam);
        if (idx >= 0) input_set_key(&p->input, idx, true);
        return 0;
    }
    case WM_KEYUP:
    case WM_SYSKEYUP: {
        i32 idx = win_vk_to_index((i32)wParam);
        if (idx >= 0) input_set_key(&p->input, idx, false);
        return 0;
    }

    case WM_DPICHANGED: {
        /* Use the suggested rect from lParam to keep window visually consistent */
        RECT *suggested = (RECT *)lParam;
        SetWindowPos(hwnd, NULL,
                     suggested->left, suggested->top,
                     suggested->right - suggested->left,
                     suggested->bottom - suggested->top,
                     SWP_NOZORDER | SWP_NOACTIVATE);

        /* Refresh cached client size */
        RECT client;
        GetClientRect(hwnd, &client);
        p->width  = (u32)(client.right - client.left);
        p->height = (u32)(client.bottom - client.top);
        return 0;
    }

    case WM_MOUSEMOVE:
        input_set_mouse(&p->input, (f32)LOWORD(lParam), (f32)HIWORD(lParam));
        return 0;

    case WM_MOUSEWHEEL: {
        f32 delta = (f32)GET_WHEEL_DELTA_WPARAM(wParam) / (f32)WHEEL_DELTA;
        input_set_scroll(&p->input, 0.0f, delta);
        return 0;
    }

    case WM_LBUTTONDOWN:
        input_set_key(&p->input, INPUT_MOUSE_LEFT, true);
        return 0;
    case WM_LBUTTONUP:
        input_set_key(&p->input, INPUT_MOUSE_LEFT, false);
        return 0;
    case WM_RBUTTONDOWN:
        input_set_key(&p->input, INPUT_MOUSE_RIGHT, true);
        return 0;
    case WM_RBUTTONUP:
        input_set_key(&p->input, INPUT_MOUSE_RIGHT, false);
        return 0;
    case WM_MBUTTONDOWN:
        input_set_key(&p->input, INPUT_MOUSE_MIDDLE, true);
        return 0;
    case WM_MBUTTONUP:
        input_set_key(&p->input, INPUT_MOUSE_MIDDLE, false);
        return 0;
    case WM_XBUTTONDOWN: {
        WORD x_btn = GET_XBUTTON_WPARAM(wParam);
        if (x_btn == XBUTTON1)      input_set_key(&p->input, INPUT_MOUSE_4, true);
        else if (x_btn == XBUTTON2) input_set_key(&p->input, INPUT_MOUSE_5, true);
        return 0;
    }
    case WM_XBUTTONUP: {
        WORD x_btn = GET_XBUTTON_WPARAM(wParam);
        if (x_btn == XBUTTON1)      input_set_key(&p->input, INPUT_MOUSE_4, false);
        else if (x_btn == XBUTTON2) input_set_key(&p->input, INPUT_MOUSE_5, false);
        return 0;
    }

    case WM_INPUT: {
        if (!p->mouse_relative) break;

        UINT size = 0;
        GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));

        BYTE buffer[64];
        if (size > 0 && size <= sizeof(buffer)) {
            if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer, &size,
                                sizeof(RAWINPUTHEADER)) == size) {
                RAWINPUT *raw = (RAWINPUT *)buffer;
                if (raw->header.dwType == RIM_TYPEMOUSE) {
                    p->input.mouse_dx += (f32)raw->data.mouse.lLastX;
                    p->input.mouse_dy += (f32)raw->data.mouse.lLastY;
                }
            }
        }
        return 0;
    }

    default:
        break;
    }

    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

/* ---- Platform API ---- */

Platform *platform_create(const PlatformConfig *cfg) {
    Platform *p = calloc(1, sizeof(Platform));
    if (!p) { LOG_FATAL("Failed to allocate Platform"); return NULL; }

    p->hinstance = GetModuleHandleA(NULL);
    p->width  = cfg->width;
    p->height = cfg->height;

    /* ---- Enable Per-Monitor DPI Awareness V2 (Windows 10 1703+) ----
     * Use dynamic loading so we degrade gracefully on older systems
     * (Windows 7/8, pre-1703 Windows 10) where the function is absent.
     */
    typedef BOOL (WINAPI *PFN_SetProcessDpiAwarenessContext)(DPI_AWARENESS_CONTEXT);
    HMODULE user32 = GetModuleHandleA("user32.dll");
    if (user32) {
        PFN_SetProcessDpiAwarenessContext set_dpi_ctx =
            (PFN_SetProcessDpiAwarenessContext)GetProcAddress(user32, "SetProcessDpiAwarenessContext");
        if (set_dpi_ctx) {
            set_dpi_ctx(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
        }
    }

    WNDCLASSEXA wc;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEXA);
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = p->hinstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "BreakEngine";

    if (!RegisterClassExA(&wc)) {
        LOG_FATAL("Failed to register window class");
        free(p);
        return NULL;
    }

    DWORD style = WS_OVERLAPPEDWINDOW;
    RECT rect = { 0, 0, (LONG)cfg->width, (LONG)cfg->height };
    AdjustWindowRect(&rect, style, FALSE);

    i32 win_w = rect.right - rect.left;
    i32 win_h = rect.bottom - rect.top;

    p->hwnd = CreateWindowExA(
        0, "BreakEngine", cfg->title, style,
        CW_USEDEFAULT, CW_USEDEFAULT, win_w, win_h,
        NULL, NULL, p->hinstance, NULL);

    if (!p->hwnd) {
        LOG_FATAL("Failed to create window");
        UnregisterClassA("BreakEngine", p->hinstance);
        free(p);
        return NULL;
    }

    SetWindowLongPtrA(p->hwnd, GWLP_USERDATA, (LONG_PTR)p);

    p->hdc = GetDC(p->hwnd);

    ShowWindow(p->hwnd, SW_SHOW);
    UpdateWindow(p->hwnd);

    input_init(&p->input);
    gamepad_init();

    LOG_INFO("Platform initialized: %ux%u \"%s\"", cfg->width, cfg->height, cfg->title);
    return p;
}

void platform_destroy(Platform *p) {
    if (!p) return;
    gamepad_shutdown();
    if (p->hdc) ReleaseDC(p->hwnd, p->hdc);
    if (p->hwnd) DestroyWindow(p->hwnd);
    UnregisterClassA("BreakEngine", p->hinstance);
    free(p);
    LOG_INFO("Platform destroyed");
}

PlatformEventResult platform_poll(Platform *p) {
    input_new_frame(&p->input);

    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    /* Pump gamepads (XInput) into the shared input state. */
    gamepad_poll(p->input.gamepads);

    if (p->should_close) return PLATFORM_EVENT_QUIT;
    return PLATFORM_EVENT_NONE;
}

InputState *platform_input(Platform *p) {
    return &p->input;
}

void *platform_window_native(Platform *p) {
    return (void *)p->hwnd;
}

void *platform_display_native(Platform *p) {
    return (void *)p->hinstance;
}

void *platform_surface_native(Platform *p) {
    return (void *)p->hwnd;
}

void platform_get_size(Platform *p, u32 *w, u32 *h) {
    if (w) *w = p->width;
    if (h) *h = p->height;
}

f32 platform_get_dpi(Platform *p) {
    /* Use GetDpiForWindow (Win10 1607+) via dynamic loading */
    typedef UINT (WINAPI *PFN_GetDpiForWindow)(HWND);
    static PFN_GetDpiForWindow fn_get_dpi = NULL;
    static bool resolved = false;
    if (!resolved) {
        HMODULE user32 = GetModuleHandleA("user32.dll");
        if (user32)
            fn_get_dpi = (PFN_GetDpiForWindow)GetProcAddress(user32, "GetDpiForWindow");
        resolved = true;
    }
    if (fn_get_dpi) {
        UINT dpi = fn_get_dpi(p->hwnd);
        return dpi > 0 ? (f32)dpi : 96.0f;
    }
    return 96.0f;
}

i32 platform_get_scale_factor(Platform *p) {
    f32 dpi = platform_get_dpi(p);
    return (i32)((dpi + 48.0f) / 96.0f);
}

u32 platform_get_monitor_count(Platform *p) {
    (void)p;
    return (u32)GetSystemMetrics(SM_CMONITORS);
}

/* ---- Multi-monitor enumeration ---- */

typedef struct {
    MonitorInfo *infos;
    u32 count;
    u32 max_count;
} MonitorEnumData;

static BOOL CALLBACK monitor_enum_proc(HMONITOR hmon, HDC hdc, LPRECT rect, LPARAM data) {
    (void)hdc; (void)rect;
    MonitorEnumData *med = (MonitorEnumData *)data;
    if (med->count >= med->max_count) return FALSE;

    MONITORINFOEXW mi;
    memset(&mi, 0, sizeof(mi));
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoW(hmon, (MONITORINFO *)&mi)) return TRUE;

    MonitorInfo *info = &med->infos[med->count];
    memset(info, 0, sizeof(MonitorInfo));

    /* Device name (wchar -> UTF-8) */
    WideCharToMultiByte(CP_UTF8, 0, mi.szDevice, -1,
                        info->name, (int)sizeof(info->name) - 1, NULL, NULL);
    info->name[sizeof(info->name) - 1] = '\0';

    /* Position and size */
    info->x = mi.rcMonitor.left;
    info->y = mi.rcMonitor.top;
    info->width  = (u32)(mi.rcMonitor.right - mi.rcMonitor.left);
    info->height = (u32)(mi.rcMonitor.bottom - mi.rcMonitor.top);

    /* Primary flag */
    info->primary = (mi.dwFlags & MONITORINFOF_PRIMARY) != 0;

    /* Refresh rate via DEVMODE */
    DEVMODEW dm;
    memset(&dm, 0, sizeof(dm));
    dm.dmSize = sizeof(dm);
    if (EnumDisplaySettingsW(mi.szDevice, ENUM_CURRENT_SETTINGS, &dm)) {
        info->refresh_rate = (u32)dm.dmDisplayFrequency;
    }

    /* DPI: GetDpiForMonitor (Win 8.1+) via dynamic load */
    UINT dpi_x = 96, dpi_y = 96;
    typedef HRESULT (WINAPI *PFN_GetDpiForMonitor)(HMONITOR, int, UINT *, UINT *);
    HMODULE shcore = LoadLibraryA("shcore.dll");
    if (shcore) {
        PFN_GetDpiForMonitor fn =
            (PFN_GetDpiForMonitor)GetProcAddress(shcore, "GetDpiForMonitor");
        if (fn) fn(hmon, 0 /* MDT_EFFECTIVE_DPI */, &dpi_x, &dpi_y);
        FreeLibrary(shcore);
    }
    info->dpi   = (f32)dpi_x;
    info->scale = (i32)((dpi_x + 48) / 96);

    med->count++;
    return TRUE;
}

bool platform_get_monitor_info(Platform *p, u32 index, MonitorInfo *out) {
    (void)p;
    if (!out) return false;

    MonitorInfo infos[PLATFORM_MAX_MONITORS];
    MonitorEnumData data = { infos, 0, PLATFORM_MAX_MONITORS };
    EnumDisplayMonitors(NULL, NULL, monitor_enum_proc, (LPARAM)&data);

    if (index >= data.count) return false;
    *out = infos[index];
    return true;
}

void platform_toggle_fullscreen(Platform *p) {
    if (!p->is_fullscreen) {
        /* Save current windowed state */
        p->windowed_style = (DWORD)GetWindowLongA(p->hwnd, GWL_STYLE);
        GetWindowRect(p->hwnd, &p->windowed_rect);

        /* Remove window decoration and maximize to monitor */
        MONITORINFO mi;
        mi.cbSize = sizeof(MONITORINFO);
        HMONITOR mon = MonitorFromWindow(p->hwnd, MONITOR_DEFAULTTONEAREST);
        GetMonitorInfoA(mon, &mi);

        SetWindowLongA(p->hwnd, GWL_STYLE, (LONG)(p->windowed_style & ~WS_OVERLAPPEDWINDOW));
        SetWindowPos(p->hwnd, HWND_TOP,
                     mi.rcMonitor.left, mi.rcMonitor.top,
                     mi.rcMonitor.right - mi.rcMonitor.left,
                     mi.rcMonitor.bottom - mi.rcMonitor.top,
                     SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    } else {
        /* Restore windowed state */
        SetWindowLongA(p->hwnd, GWL_STYLE, (LONG)p->windowed_style);
        SetWindowPos(p->hwnd, NULL,
                     p->windowed_rect.left, p->windowed_rect.top,
                     p->windowed_rect.right - p->windowed_rect.left,
                     p->windowed_rect.bottom - p->windowed_rect.top,
                     SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOZORDER);
        ShowWindow(p->hwnd, SW_NORMAL);
    }
    p->is_fullscreen = !p->is_fullscreen;
}

void platform_mouse_capture(Platform *p, bool capture) {
    if (capture) {
        SetCapture(p->hwnd);
    } else {
        ReleaseCapture();
    }
}

void platform_mouse_set_visible(Platform *p, bool visible) {
    (void)p;
    ShowCursor(visible ? TRUE : FALSE);
}

void platform_mouse_set_relative(Platform *p, bool relative) {
    if (!p) return;

    if (relative && !p->mouse_relative) {
        /* Register Raw Input mouse device */
        RAWINPUTDEVICE rid;
        memset(&rid, 0, sizeof(rid));
        rid.usUsagePage = 0x01;  /* HID_USAGE_PAGE_GENERIC */
        rid.usUsage     = 0x02;  /* HID_USAGE_GENERIC_MOUSE */
        rid.dwFlags     = RIDEV_INPUTSINK;
        rid.hwndTarget  = p->hwnd;
        RegisterRawInputDevices(&rid, 1, sizeof(rid));

        /* Hide cursor and capture */
        ShowCursor(FALSE);
        SetCapture(p->hwnd);

        /* Clip cursor to client area */
        RECT client;
        GetClientRect(p->hwnd, &client);
        POINT tl = { client.left,  client.top    };
        POINT br = { client.right, client.bottom };
        ClientToScreen(p->hwnd, &tl);
        ClientToScreen(p->hwnd, &br);
        RECT clip = { tl.x, tl.y, br.x, br.y };
        ClipCursor(&clip);

        p->mouse_relative = true;
    } else if (!relative && p->mouse_relative) {
        /* Unregister Raw Input device */
        RAWINPUTDEVICE rid;
        memset(&rid, 0, sizeof(rid));
        rid.usUsagePage = 0x01;
        rid.usUsage     = 0x02;
        rid.dwFlags     = RIDEV_REMOVE;
        rid.hwndTarget  = NULL;
        RegisterRawInputDevices(&rid, 1, sizeof(rid));

        ShowCursor(TRUE);
        ReleaseCapture();
        ClipCursor(NULL);

        p->mouse_relative = false;
    }
}

#endif /* ENGINE_PLATFORM_WINDOWS */
