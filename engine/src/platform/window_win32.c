#ifdef ENGINE_PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <windowsx.h>  /* R423: GET_X_LPARAM / GET_Y_LPARAM */
#include <imm.h>

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
#include <platform/platform_text.h>
#include <core/types.h>
#include <core/log.h>
#include "gamepad_linux.h"  /* shared gamepad API; Windows impl in gamepad_win.c */

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <limits.h>  /* R564: INT_MAX clamp for bounded clipboard length */

struct Platform {
    HINSTANCE   hinstance;
    HWND        hwnd;
    HDC         hdc;
    InputState  input;
    u32         width, height;
    bool        should_close;
    bool        is_fullscreen;
    bool        mouse_relative;
    bool        mouse_visible;  /* R427: desired cursor visibility (ShowCursor is counter-based) */
    PlatformCursor cursor;
    PlatformTextQueue text_queue;
    PlatformImeSurrounding ime_surrounding;
    bool        ime_enabled;
    bool        ime_context_detached;
    uint16_t    pending_high_surrogate;
    u32         suppress_char_units;
    HIMC        ime_context;
    i32         ime_spot_x;
    i32         ime_spot_y;
    WINDOWPLACEMENT windowed_placement;  /* R566: keeps maximized state */
    DWORD       windowed_style;
};

static void win_apply_cursor(Platform *p) {
    LPCSTR resource;
    if (p == NULL) return;
    switch (p->cursor) {
    case PLATFORM_CURSOR_TEXT:
        resource = IDC_IBEAM;
        break;
    case PLATFORM_CURSOR_HAND:
        resource = IDC_HAND;
        break;
    case PLATFORM_CURSOR_ARROW:
    default:
        resource = IDC_ARROW;
        break;
    }
    SetCursor(LoadCursorA(NULL, resource));
}

/* ---- Key mapping ---- */

/* R369: lParam bit24 distinguishes main-board nav (extended) from keypad
 * when NumLock is off (non-extended VK_INSERT/END/… → KP 305–315). */
static i32 win_vk_to_index(i32 vk_code, LPARAM lParam) {
    if (vk_code >= 'A' && vk_code <= 'Z') return vk_code - 'A' + 'a';
    if (vk_code >= '0' && vk_code <= '9') return vk_code;

    bool extended = (lParam & (1 << 24)) != 0;

    switch (vk_code) {
    case VK_ESCAPE:   return 256;
    case VK_SPACE:    return 32;
    case VK_RETURN:   return 257;
    case VK_TAB:      return 259;
    case VK_BACK:     return 260;
    case VK_LEFT:     return extended ? 261 : 309; /* KP_4 */
    case VK_RIGHT:    return extended ? 262 : 311; /* KP_6 */
    case VK_UP:       return extended ? 263 : 313; /* KP_8 */
    case VK_DOWN:     return extended ? 264 : 307; /* KP_2 */
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
    case VK_PRIOR:    return extended ? 283 : 314; /* KP_9 */
    case VK_NEXT:     return extended ? 284 : 308; /* KP_3 */
    case VK_HOME:     return extended ? 285 : 312; /* KP_7 */
    case VK_END:      return extended ? 286 : 306; /* KP_1 */
    case VK_INSERT:   return extended ? 287 : 305; /* KP_0 */
    case VK_DELETE:   return extended ? 288 : 315; /* KP_Decimal */
    case VK_CLEAR:    return 310; /* KP_5 when NumLock off */
    /* R369: WM_KEY* delivers VK_SHIFT/VK_CONTROL, not L/R variants. */
    case VK_SHIFT:    return 289;
    case VK_CONTROL:  return 290;
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
    /* R363: boom was 300 (=INPUT_MOUSE_LEFT); KP_* live at 305+ */
    case VK_NUMPAD0:  return 305; /* particle boom */
    case VK_NUMPAD1:  return 306; /* tornado */
    case VK_NUMPAD2:  return 307; /* particle trail */
    case VK_NUMPAD3:  return 308; /* layout */
    case VK_NUMPAD4:  return 309; /* AA cycle */
    /* R364: CG/lens off digit row (1–8 stay gameplay) */
    case VK_NUMPAD5:  return 310; /* temp- */
    case VK_NUMPAD6:  return 311; /* temp+ */
    case VK_NUMPAD7:  return 312; /* tint- */
    case VK_NUMPAD8:  return 313; /* tint+ */
    case VK_NUMPAD9:  return 314; /* color grade */
    case VK_DECIMAL:  return 315; /* lensfx / CA / vig cycle */
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
    case VK_OEM_5:      return (i32)'\\'; /* R367: FogFar */
    default:            return -1;
    }
}

static bool win_queue_utf16(Platform *platform, PlatformTextType type,
                            const uint16_t *text, usize units, i32 cursor) {
    char *utf8 = platform_utf16_to_utf8_alloc(text, units);
    bool queued;
    if (utf8 == NULL) return false;
    queued = platform_text_queue_push(&platform->text_queue, type, utf8, cursor);
    free(utf8);
    return queued;
}

static void win_queue_char(Platform *platform, uint16_t unit) {
    uint16_t text[2];
    if (platform->pending_high_surrogate != 0) {
        if (unit >= 0xDC00u && unit <= 0xDFFFu) {
            text[0] = platform->pending_high_surrogate;
            text[1] = unit;
            win_queue_utf16(platform, PLATFORM_TEXT_COMMIT, text, 2, 0);
            platform->pending_high_surrogate = 0;
            return;
        }
        text[0] = platform->pending_high_surrogate;
        win_queue_utf16(platform, PLATFORM_TEXT_COMMIT, text, 1, 0);
        platform->pending_high_surrogate = 0;
    }
    if (unit >= 0xD800u && unit <= 0xDBFFu) {
        platform->pending_high_surrogate = unit;
    } else {
        text[0] = unit;
        win_queue_utf16(platform, PLATFORM_TEXT_COMMIT, text, 1, 0);
    }
}

static void win_queue_ime_composition(Platform *platform, HIMC context,
                                      DWORD flags) {
    LONG bytes;
    usize units;
    i32 cursor = 0;
    WCHAR *utf16;
    if ((flags & GCS_RESULTSTR) != 0) {
        bytes = ImmGetCompositionStringW(context, GCS_RESULTSTR, NULL, 0);
        if (bytes > 0 &&
            (usize)bytes <= PLATFORM_TEXT_MAX_BYTES * sizeof(*utf16) &&
            (bytes % (LONG)sizeof(*utf16)) == 0) {
            units = (usize)bytes / sizeof(utf16[0]);
            utf16 = malloc((usize)bytes + sizeof(*utf16));
            if (utf16 != NULL &&
                ImmGetCompositionStringW(context, GCS_RESULTSTR, utf16,
                                         (DWORD)bytes) == bytes) {
                if (win_queue_utf16(platform, PLATFORM_TEXT_COMMIT,
                                    (const uint16_t *)utf16, units, 0)) {
                    if (units <= UINT32_MAX - platform->suppress_char_units)
                        platform->suppress_char_units += (u32)units;
                    else
                        platform->suppress_char_units = UINT32_MAX;
                }
            }
            free(utf16);
        }
    }
    if ((flags & GCS_COMPSTR) != 0) {
        bytes = ImmGetCompositionStringW(context, GCS_COMPSTR, NULL, 0);
        if (bytes < 0) return;
        if (bytes == 0) {
            (void)platform_text_queue_push(&platform->text_queue,
                                           PLATFORM_TEXT_PREEDIT, "", 0);
            return;
        }
        if ((usize)bytes > PLATFORM_TEXT_MAX_BYTES * sizeof(*utf16) ||
            (bytes % (LONG)sizeof(*utf16)) != 0) return;
        units = (usize)bytes / sizeof(utf16[0]);
        utf16 = malloc((usize)bytes + sizeof(*utf16));
        if (utf16 == NULL || ImmGetCompositionStringW(context, GCS_COMPSTR, utf16,
                                                       (DWORD)bytes) != bytes) {
            free(utf16);
            return;
        }
        if ((flags & GCS_CURSORPOS) != 0) {
            LONG position = ImmGetCompositionStringW(context, GCS_CURSORPOS,
                                                      NULL, 0);
            if (position > 0) {
                cursor = platform_utf16_units_to_codepoints(
                    (const uint16_t *)utf16,
                    position < (LONG)units ? (i32)position : (i32)units);
            }
        }
        win_queue_utf16(platform, PLATFORM_TEXT_PREEDIT,
                        (const uint16_t *)utf16, units, cursor);
        free(utf16);
    }
}

/* ---- Window procedure ---- */

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    Platform *p = (Platform *)GetWindowLongPtrW(hwnd, GWLP_USERDATA);

    if (!p) return DefWindowProcW(hwnd, msg, wParam, lParam);

    switch (msg) {
    case WM_CLOSE:
        p->should_close = true;
        return 0;

    /* R368: match X11 FocusOut / Wayland keyboard_leave — release stuck keys. */
    case WM_KILLFOCUS:
        input_release_all(&p->input);
        p->pending_high_surrogate = 0;
        return 0;

    case WM_SETFOCUS:
        return 0;

    case WM_SIZE:
        p->width  = (u32)LOWORD(lParam);
        p->height = (u32)HIWORD(lParam);
        return 0;

    case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT) {
            win_apply_cursor(p);
            return TRUE;
        }
        break;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN: {
        p->suppress_char_units = 0;
        i32 idx = win_vk_to_index((i32)wParam, lParam);
        if (idx >= 0) input_set_key(&p->input, idx, true);
        if (msg == WM_KEYDOWN) return 0;
        /* R562: system keys must still reach DefWindowProcW - consuming
         * WM_SYSKEY* here killed Alt+F4 (DefWindowProcW turns it into
         * WM_CLOSE) and every other default system-key accelerator. */
        break;
    }
    case WM_KEYUP:
    case WM_SYSKEYUP: {
        i32 idx = win_vk_to_index((i32)wParam, lParam);
        if (idx >= 0) input_set_key(&p->input, idx, false);
        if (msg == WM_KEYUP) return 0;
        break;  /* R562: see WM_SYSKEYDOWN above */
    }

    case WM_IME_COMPOSITION: {
        HIMC context = ImmGetContext(hwnd);
        if (context != NULL) {
            win_queue_ime_composition(p, context, (DWORD)lParam);
            ImmReleaseContext(hwnd, context);
        }
        return 0;
    }

    case WM_CHAR:
        if (p->ime_enabled && wParam >= 0x20 && wParam != 0x7Fu) {
            if (p->suppress_char_units > 0) {
                p->suppress_char_units--;
                return 0;
            }
            win_queue_char(p, (uint16_t)wParam);
            return 0;
        }
        break;

#ifndef WM_UNICHAR
#define WM_UNICHAR 0x0109
#endif
    case WM_UNICHAR:
        if (wParam == UNICODE_NOCHAR) return TRUE;
        if (p->ime_enabled) {
            uint32_t codepoint = (uint32_t)wParam;
            if (codepoint <= 0xFFFFu) {
                win_queue_char(p, (uint16_t)codepoint);
            } else if (codepoint <= 0x10FFFFu) {
                uint16_t text[2];
                codepoint -= 0x10000u;
                text[0] = (uint16_t)(0xD800u + (codepoint >> 10));
                text[1] = (uint16_t)(0xDC00u + (codepoint & 0x3FFu));
                win_queue_utf16(p, PLATFORM_TEXT_COMMIT, text, 2, 0);
            }
            return 0;
        }
        break;

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
        /* R423: GET_*_LPARAM sign-extends — LOWORD/HIWORD are unsigned, so
         * negative coords (secondary monitor left of / above the primary)
         * wrapped to huge positive values. */
        if (p->mouse_relative) {
            /* R563: in relative mode WM_INPUT raw deltas own mouse_dx/dy;
             * accumulating absolute-position deltas here too double-counted
             * (~2x speed, mixed units). Track only the absolute position,
             * mirroring the X11 backend's exclusive relative branch. */
            p->input.has_mouse_pos = true;
            p->input.mouse_x = (f32)GET_X_LPARAM(lParam);
            p->input.mouse_y = (f32)GET_Y_LPARAM(lParam);
        } else {
            input_set_mouse(&p->input, (f32)GET_X_LPARAM(lParam),
                            (f32)GET_Y_LPARAM(lParam));
        }
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

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

/* ---- Platform API ---- */

Platform *platform_create(const PlatformConfig *cfg) {
    Platform *p = calloc(1, sizeof(Platform));
    int title_units;
    wchar_t *title;
    if (!p) { LOG_FATAL("Failed to allocate Platform"); return NULL; }

    p->hinstance = GetModuleHandleW(NULL);
    p->width  = cfg->width;
    p->height = cfg->height;
    p->mouse_visible = true;  /* R427: cursor starts visible */
    p->cursor = PLATFORM_CURSOR_ARROW;

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

    WNDCLASSEXW wc;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEXW);
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = p->hinstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"BreakEngine";

    if (!RegisterClassExW(&wc)) {
        LOG_FATAL("Failed to register window class");
        free(p);
        return NULL;
    }

    DWORD style = WS_OVERLAPPEDWINDOW;
    RECT rect = { 0, 0, (LONG)cfg->width, (LONG)cfg->height };
    AdjustWindowRect(&rect, style, FALSE);

    i32 win_w = rect.right - rect.left;
    i32 win_h = rect.bottom - rect.top;

    title_units = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
                                      cfg->title, -1, NULL, 0);
    if (title_units <= 0) {
        LOG_FATAL("Invalid UTF-8 window title");
        UnregisterClassW(L"BreakEngine", p->hinstance);
        free(p);
        return NULL;
    }
    title = malloc((size_t)title_units * sizeof(*title));
    if (title == NULL || MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
                                             cfg->title, -1, title,
                                             title_units) != title_units) {
        free(title);
        LOG_FATAL("Failed to convert window title to UTF-16");
        UnregisterClassW(L"BreakEngine", p->hinstance);
        free(p);
        return NULL;
    }

    p->hwnd = CreateWindowExW(
        0, L"BreakEngine", title, style,
        CW_USEDEFAULT, CW_USEDEFAULT, win_w, win_h,
        NULL, NULL, p->hinstance, NULL);
    free(title);

    if (!p->hwnd) {
        LOG_FATAL("Failed to create window");
        UnregisterClassW(L"BreakEngine", p->hinstance);
        free(p);
        return NULL;
    }

    SetWindowLongPtrW(p->hwnd, GWLP_USERDATA, (LONG_PTR)p);

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
    platform_text_queue_destroy(&p->text_queue);
    if (p->hdc) ReleaseDC(p->hwnd, p->hdc);
    if (p->hwnd) DestroyWindow(p->hwnd);
    UnregisterClassW(L"BreakEngine", p->hinstance);
    free(p);
    LOG_INFO("Platform destroyed");
}

PlatformEventResult platform_poll(Platform *p) {
    input_new_frame(&p->input);

    MSG msg;
    while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
        /* R423: WM_QUIT never reaches the window proc (it's a thread-queue
         * message) — handle it here like the WM_CLOSE path. */
        if (msg.message == WM_QUIT) {
            p->should_close = true;
            break;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    /* Pump gamepads (XInput) into the shared input state. */
    gamepad_poll(p->input.gamepads);

    if (p->should_close) return PLATFORM_EVENT_QUIT;
    return PLATFORM_EVENT_NONE;
}

u32 platform_poll_text(Platform *p, PlatformTextEvent *out, u32 max_events) {
    return p != NULL ? platform_text_queue_pop(&p->text_queue, out, max_events)
                     : 0;
}

void platform_ime_set_enabled(Platform *p, bool enabled) {
    if (p == NULL) return;
    if (p->ime_enabled == enabled) return;
    p->ime_enabled = enabled;
    if (enabled) {
        if (p->ime_context_detached) {
            (void)ImmAssociateContext(p->hwnd, p->ime_context);
            p->ime_context_detached = false;
        }
    } else {
        p->pending_high_surrogate = 0;
        p->suppress_char_units = 0;
        if (!p->ime_context_detached) {
            p->ime_context = ImmAssociateContext(p->hwnd, NULL);
            p->ime_context_detached = true;
        }
    }
}

bool platform_ime_is_enabled(Platform *p) {
    return p != NULL && p->ime_enabled;
}

void platform_ime_set_surrounding(Platform *p, const char *utf8, i32 cursor,
                                  i32 anchor) {
    if (p != NULL) {
        platform_ime_surrounding_set(&p->ime_surrounding, utf8,
                                     cursor > 0 ? (usize)cursor : 0,
                                     anchor > 0 ? (usize)anchor : 0);
    }
}

void platform_ime_set_spot(Platform *p, i32 x, i32 y) {
    HIMC context;
    COMPOSITIONFORM composition;
    CANDIDATEFORM candidate;
    if (p == NULL) return;
    p->ime_spot_x = x;
    p->ime_spot_y = y;
    context = ImmGetContext(p->hwnd);
    if (context == NULL) return;
    memset(&composition, 0, sizeof(composition));
    composition.dwStyle = CFS_POINT;
    composition.ptCurrentPos.x = x;
    composition.ptCurrentPos.y = y;
    ImmSetCompositionWindow(context, &composition);
    memset(&candidate, 0, sizeof(candidate));
    candidate.dwIndex = 0;
    candidate.dwStyle = CFS_CANDIDATEPOS;
    candidate.ptCurrentPos.x = x;
    candidate.ptCurrentPos.y = y;
    ImmSetCandidateWindow(context, &candidate);
    ImmReleaseContext(p->hwnd, context);
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

void platform_get_logical_size(Platform *p, u32 *w, u32 *h) {
    /* R565: guard NULL before platform_get_content_scale (it dereferences
     * p->hwnd); the ternaries after the call were dead code as ordered. */
    if (p == NULL) {
        if (w) *w = 0;
        if (h) *h = 0;
        return;
    }
    f32 scale = platform_get_content_scale(p);
    if (w) *w = (u32)((f32)p->width / scale + 0.5f);
    if (h) *h = (u32)((f32)p->height / scale + 0.5f);
}

void platform_get_drawable_size(Platform *p, u32 *w, u32 *h) {
    if (w) *w = p != NULL ? p->width : 0;
    if (h) *h = p != NULL ? p->height : 0;
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

f32 platform_get_content_scale(Platform *p) {
    f32 dpi = platform_get_dpi(p);
    return dpi > 0.0f ? dpi / 96.0f : 1.0f;
}

f32 platform_get_input_scale(Platform *p) {
    return platform_get_content_scale(p);
}

i32 platform_get_scale_factor(Platform *p) {
    return (i32)(platform_get_content_scale(p) + 0.5f);
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
        /* Save current windowed state. R566: GetWindowPlacement (unlike
         * GetWindowRect) also captures the maximized/minimized show state
         * and the restored (normal) rect, so a maximized window no longer
         * comes back un-maximized after a fullscreen round-trip. */
        p->windowed_style = (DWORD)GetWindowLongA(p->hwnd, GWL_STYLE);
        p->windowed_placement.length = sizeof(p->windowed_placement);
        GetWindowPlacement(p->hwnd, &p->windowed_placement);

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
        /* Restore windowed state (placement restores the show state too) */
        SetWindowLongA(p->hwnd, GWL_STYLE, (LONG)p->windowed_style);
        SetWindowPlacement(p->hwnd, &p->windowed_placement);
        /* Apply the restored style's frame without moving the window. */
        SetWindowPos(p->hwnd, NULL, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                     SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
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
    if (!p) return;
    /* R427: ShowCursor is counter-based, not idempotent — calling it for every
     * set_visible(true) drifts the counter until the cursor is stuck hidden.
     * Track the desired state and only call ShowCursor on transitions. */
    if (visible == p->mouse_visible) return;
    ShowCursor(visible ? TRUE : FALSE);
    p->mouse_visible = visible;
}

bool platform_cursor_set(Platform *p, PlatformCursor cursor) {
    if (p == NULL || cursor > PLATFORM_CURSOR_HAND) return false;
    p->cursor = cursor;
    win_apply_cursor(p);
    return true;
}

bool platform_window_begin_move(Platform *p) {
    if (p == NULL || p->hwnd == NULL) return false;
    ReleaseCapture();
    SendMessageW(p->hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
    return true;
}

bool platform_needs_client_decoration(Platform *p) {
    (void)p;
    return false;
}

bool platform_clipboard_set_text(Platform *p, const char *utf8) {
    int units;
    HGLOBAL memory;
    wchar_t *wide;
    if (p == NULL || utf8 == NULL || !OpenClipboard(p->hwnd)) return false;
    units = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    if (units <= 0) {
        CloseClipboard();
        return false;
    }
    memory = GlobalAlloc(GMEM_MOVEABLE, (SIZE_T)units * sizeof(wchar_t));
    if (memory == NULL) {
        CloseClipboard();
        return false;
    }
    wide = GlobalLock(memory);
    if (wide == NULL || MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wide,
                                             units) <= 0) {
        if (wide != NULL) GlobalUnlock(memory);
        GlobalFree(memory);
        CloseClipboard();
        return false;
    }
    GlobalUnlock(memory);
    if (!EmptyClipboard() || SetClipboardData(CF_UNICODETEXT, memory) == NULL) {
        GlobalFree(memory);
        CloseClipboard();
        return false;
    }
    CloseClipboard();
    return true;
}

bool platform_clipboard_get_text(Platform *p, char *out, usize out_size) {
    HANDLE handle;
    const wchar_t *wide;
    bool ok = false;
    if (p == NULL || out == NULL || out_size == 0 || !OpenClipboard(p->hwnd))
        return false;
    handle = GetClipboardData(CF_UNICODETEXT);
    wide = handle != NULL ? GlobalLock(handle) : NULL;
    if (wide != NULL) {
        /* R564: Windows does not guarantee CF_UNICODETEXT is NUL-terminated;
         * bound the scan by the GlobalAlloc region instead of trusting
         * wcslen not to run past it. */
        usize max_units = (usize)(GlobalSize(handle) / sizeof(wchar_t));
        usize units = wcsnlen(wide, max_units);
        (void)platform_utf16_to_utf8((const uint16_t *)wide, units, out,
                                     out_size);
        GlobalUnlock(handle);
        ok = true;
    }
    CloseClipboard();
    return ok;
}

PlatformClipboardResult platform_clipboard_get_text_alloc(Platform *p,
                                                           char **out) {
    HANDLE handle;
    const wchar_t *wide;
    int bytes;
    (void)p;
    if (out == NULL) return PLATFORM_CLIPBOARD_EMPTY;
    *out = NULL;
    if (!OpenClipboard(p != NULL ? p->hwnd : NULL)) return PLATFORM_CLIPBOARD_EMPTY;
    handle = GetClipboardData(CF_UNICODETEXT);
    wide = handle != NULL ? GlobalLock(handle) : NULL;
    if (wide == NULL) {
        CloseClipboard();
        return PLATFORM_CLIPBOARD_EMPTY;
    }
    /* R564: same unterminated-clipboard hazard as platform_clipboard_get_text;
     * pass the bounded length to WideCharToMultiByte instead of -1. */
    usize max_units = (usize)(GlobalSize(handle) / sizeof(wchar_t));
    usize units = wcsnlen(wide, max_units);
    if (units > (usize)INT_MAX) units = (usize)INT_MAX;
    bytes = WideCharToMultiByte(CP_UTF8, 0, wide, (int)units, NULL, 0, NULL, NULL);
    if (bytes > 0) *out = malloc((size_t)bytes + 1);
    if (*out != NULL) {
        (void)WideCharToMultiByte(CP_UTF8, 0, wide, (int)units, *out, bytes, NULL, NULL);
        (*out)[bytes] = '\0';
    } else if (units == 0) {
        /* Preserve the old "READY with empty string" result for empty text. */
        *out = malloc(1);
        if (*out != NULL) (*out)[0] = '\0';
    }
    GlobalUnlock(handle);
    CloseClipboard();
    return *out != NULL ? PLATFORM_CLIPBOARD_READY : PLATFORM_CLIPBOARD_EMPTY;
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

        /* Hide cursor and capture (R427: go through set_visible so the
         * ShowCursor counter stays consistent with mouse_visible) */
        platform_mouse_set_visible(p, false);
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

        platform_mouse_set_visible(p, true);  /* R427: see above */
        ReleaseCapture();
        ClipCursor(NULL);

        p->mouse_relative = false;
    }
}

#endif /* ENGINE_PLATFORM_WINDOWS */
