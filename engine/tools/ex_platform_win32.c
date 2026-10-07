/**
 * @file ex_platform_win32.c
 * @brief Windows runner: Win32 window with StretchDIBits software blit
 *        or a WGL desktop-GL context driving the gles2 vgcanvas table.
 */
#include "explorer_internal.h"

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <GL/gl.h>

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif

static app_t* g_app;
static int g_gl;
static HWND g_hwnd;

static void present_soft(HDC dc) {
  BITMAPINFO bi;
  ZeroMemory(&bi, sizeof(bi));
  bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bi.bmiHeader.biWidth = EX_W;
  bi.bmiHeader.biHeight = -EX_H; /* top-down rows */
  bi.bmiHeader.biPlanes = 1;
  bi.bmiHeader.biBitCount = 32;
  bi.bmiHeader.biCompression = BI_RGB;
  StretchDIBits(dc, 0, 0, EX_W, EX_H, 0, 0, EX_W, EX_H,
                (const void*)ex_lcd_pixels(g_app), &bi, DIB_RGB_COLORS,
                SRCCOPY);
}

static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  switch (msg) {
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC dc = BeginPaint(hwnd, &ps);
      if (g_gl) {
        ex_frame_gl(g_app);
        SwapBuffers(dc);
      } else {
        present_soft(dc);
      }
      EndPaint(hwnd, &ps);
      return 0;
    }
    case WM_MOUSEMOVE:
      ex_pointer(g_app, GET_X_LPARAM(lp), GET_Y_LPARAM(lp), 0);
      InvalidateRect(hwnd, NULL, FALSE);
      return 0;
    case WM_LBUTTONDOWN:
      ex_pointer(g_app, GET_X_LPARAM(lp), GET_Y_LPARAM(lp), 1);
      InvalidateRect(hwnd, NULL, FALSE);
      return 0;
    case WM_MOUSEWHEEL:
      ex_wheel(g_app, ((short)HIWORD(wp)) > 0 ? 1 : -1);
      InvalidateRect(hwnd, NULL, FALSE);
      return 0;
    case WM_CHAR:
      ex_key(g_app, (int)wp);
      InvalidateRect(hwnd, NULL, FALSE);
      return 0;
    case WM_ERASEBKGND:
      return 1;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      return DefWindowProcW(hwnd, msg, wp, lp);
  }
}

static HWND make_window(HINSTANCE inst, const char* title) {
  WNDCLASSW wc;
  RECT r = {0, 0, EX_W, EX_H};
  wchar_t wtitle[64];
  MultiByteToWideChar(CP_UTF8, 0, title, -1, wtitle, 64);
  ZeroMemory(&wc, sizeof(wc));
  wc.style = CS_OWNDC;
  wc.lpfnWndProc = wnd_proc;
  wc.hInstance = inst;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.lpszClassName = L"MyUIExplorer";
  RegisterClassW(&wc);
  AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
  return CreateWindowW(L"MyUIExplorer", wtitle, WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT, CW_USEDEFAULT, r.right - r.left,
                       r.bottom - r.top, NULL, NULL, inst, NULL);
}

int ex_run_win32(app_t* app, int gl) {
  HINSTANCE inst = GetModuleHandle(NULL);
  MSG msg;
  PIXELFORMATDESCRIPTOR pfd;
  int pf;
  HDC dc;
  HGLRC rc = NULL;
  g_app = app;
  g_gl = gl;
  g_hwnd = make_window(inst, gl ? "MyUI explorer [win32/gl]"
                                : "MyUI explorer [win32/soft]");
  dc = GetDC(g_hwnd);
  if (gl) {
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                  PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pf = ChoosePixelFormat(dc, &pfd);
    if (pf == 0 || !SetPixelFormat(dc, pf, &pfd)) return 1;
    rc = wglCreateContext(dc);
    if (rc == NULL || !wglMakeCurrent(dc, rc)) return 1;
    ex_gl_vg_create(app);
  }
  ShowWindow(g_hwnd, SW_SHOW);
  for (;;) {
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) return 0;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    if (gl) {
      ex_frame_gl(app);
      SwapBuffers(dc);
    } else {
      ex_frame_soft(app);
      present_soft(dc);
    }
    Sleep(8);
  }
}

#endif /* _WIN32 */
