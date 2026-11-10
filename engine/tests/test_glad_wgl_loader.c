#include <glad.h>
#include <windows.h>

#include <stdio.h>
#include <string.h>

#ifdef TEST_WGL_LOADER_SIMULATED
static int wgl_modern_calls;
static int dll_modern_calls;
static int wgl_legacy_calls;
static int dll_legacy_calls;

static const GLubyte* APIENTRY mock_get_string(GLenum name) {
  static const GLubyte version[] = "4.5.0 Test";
  static const GLubyte empty[] = "";
  return name == GL_VERSION ? version : empty;
}

static void APIENTRY mock_get_integerv(GLenum name, GLint* data) {
  *data = name == GL_NUM_EXTENSIONS ? 1 : 0;
}

static const GLubyte* APIENTRY mock_get_stringi(GLenum name, GLuint index) {
  static const GLubyte empty[] = "";
  (void)name;
  (void)index;
  return empty;
}

static GLuint APIENTRY mock_create_shader(GLenum type) {
  (void)type;
  return 17u;
}

static void APIENTRY mock_neutral(void) {}

static void* APIENTRY mock_wgl_get_proc_address(const char* name) {
  if (strcmp(name, "glCreateShader") == 0) {
    wgl_modern_calls++;
    return (void*)mock_create_shader;
  }
  if (strcmp(name, "glGetString") == 0 ||
      strcmp(name, "glGetIntegerv") == 0 ||
      strcmp(name, "glGetStringi") == 0) {
    wgl_legacy_calls++;
    return NULL;
  }
  return (void*)mock_neutral;
}

HMODULE LoadLibraryW(LPCWSTR name) {
  static int module;
  (void)name;
  return (HMODULE)&module;
}

void* GetProcAddress(HMODULE module, const char* name) {
  (void)module;
  if (strcmp(name, "wglGetProcAddress") == 0)
    return (void*)mock_wgl_get_proc_address;
  if (strcmp(name, "glCreateShader") == 0) {
    dll_modern_calls++;
    return NULL;
  }
  if (strcmp(name, "glGetString") == 0) {
    dll_legacy_calls++;
    return (void*)mock_get_string;
  }
  if (strcmp(name, "glGetIntegerv") == 0)
    return (void*)mock_get_integerv;
  if (strcmp(name, "glGetStringi") == 0)
    return (void*)mock_get_stringi;
  return NULL;
}

BOOL FreeLibrary(HMODULE module) {
  (void)module;
  return 1;
}
#endif

#ifndef TEST_WGL_LOADER_SIMULATED
static int check_native(int condition, const char* message) {
  if (!condition) {
    printf("FAIL: %s\n", message);
    return 1;
  }
  return 0;
}

static int run_native_wgl_test(void) {
  int failures = 0;
  int loaded = 0;
  int pixel_format;
  HINSTANCE instance = GetModuleHandleW(NULL);
  const wchar_t class_name[] = L"break_wgl_loader_test";
  WNDCLASSEXW wc;
  PIXELFORMATDESCRIPTOR pfd;
  HWND hwnd = NULL;
  HDC dc = NULL;
  HGLRC context = NULL;
  HMODULE real_module = NULL;
  BOOL class_registered = FALSE;

  memset(&wc, 0, sizeof(wc));
  wc.cbSize = sizeof(wc);
  wc.lpfnWndProc = DefWindowProcW;
  wc.hInstance = instance;
  wc.lpszClassName = class_name;
  class_registered = RegisterClassExW(&wc) != 0;
  failures += check_native(class_registered, "RegisterClassExW failed");
  if (!class_registered) goto cleanup;

  hwnd = CreateWindowExW(0, class_name, L"break wgl loader test",
                         WS_OVERLAPPEDWINDOW, 0, 0, 1, 1, HWND_MESSAGE,
                         NULL, instance, NULL);
  if (hwnd == NULL) {
    failures += check_native(0, "CreateWindowExW failed");
    goto cleanup;
  }
  dc = GetDC(hwnd);
  if (dc == NULL) {
    failures += check_native(0, "GetDC failed");
    goto cleanup;
  }

  memset(&pfd, 0, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 24;
  pixel_format = ChoosePixelFormat(dc, &pfd);
  if (pixel_format == 0) {
    failures += check_native(0, "ChoosePixelFormat failed");
    goto cleanup;
  }
  if (!SetPixelFormat(dc, pixel_format, &pfd)) {
    failures += check_native(0, "SetPixelFormat failed");
    goto cleanup;
  }

  context = wglCreateContext(dc);
  if (context == NULL) {
    failures += check_native(0, "wglCreateContext failed");
    goto cleanup;
  }
  if (!wglMakeCurrent(dc, context)) {
    failures += check_native(0, "wglMakeCurrent failed");
    goto cleanup;
  }

  real_module = LoadLibraryW(L"opengl32.dll");
  if (real_module == NULL) {
    failures += check_native(0, "could not load the real opengl32.dll");
    goto cleanup;
  }
  loaded = gladLoadGL();
  failures += check_native(loaded == 1, "gladLoadGL did not initialize with the test DLL");
  failures += check_native(glad_glCreateShader != NULL,
                           "no modern glCreateShader entry on the real WGL context");
  failures += check_native(
      glad_glCreateShader == (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"),
      "glCreateShader differs from the real wglGetProcAddress result");
  failures += check_native(
      glad_glGetString == (PFNGLGETSTRINGPROC)GetProcAddress(real_module, "glGetString"),
      "legacy glGetString differs from the real opengl32 export");
  failures += check_native(
      glad_glGetIntegerv == (PFNGLGETINTEGERVPROC)GetProcAddress(real_module, "glGetIntegerv"),
      "glGetIntegerv differs from the real opengl32 export");
  failures += check_native(
      glad_glGetStringi == (PFNGLGETSTRINGIPROC)wglGetProcAddress("glGetStringi"),
      "glGetStringi differs from the real wglGetProcAddress result");
  if (glad_glGetString != NULL) {
    failures += check_native(glad_glGetString(GL_VERSION) != NULL,
                             "the real opengl32 version query returned no version string");
  }

cleanup:
  if (context != NULL) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(context);
  }
  if (dc != NULL) ReleaseDC(hwnd, dc);
  if (hwnd != NULL) DestroyWindow(hwnd);
  if (class_registered) UnregisterClassW(class_name, instance);
  if (real_module != NULL) FreeLibrary(real_module);

  if (failures != 0) {
    printf("WGL native loader: loaded=%d glad_glCreateShader=%p wglCreateShader=%p\n",
           loaded, (void*)glad_glCreateShader,
           (void*)wglGetProcAddress("glCreateShader"));
  } else {
    printf("PASS: gladLoadGL resolved modern entry through WGL and legacy entry through DLL\n");
  }
  return failures;
}
#endif

int main(void) {
#ifdef TEST_WGL_LOADER_SIMULATED
  int failures = 0;
  int loaded = gladLoadGL();
#define CHECK(condition, message)                                                \
  do {                                                                           \
    if (!(condition)) {                                                          \
      printf("FAIL: %s\n", message);                                            \
      failures++;                                                                \
    }                                                                            \
  } while (0)

  CHECK(loaded == 1, "gladLoadGL did not initialize with the test DLL");
  CHECK(glad_glCreateShader == (PFNGLCREATESHADERPROC)mock_create_shader,
        "glCreateShader was not resolved through wglGetProcAddress");
  CHECK(wgl_modern_calls == 1, "wglGetProcAddress did not resolve glCreateShader");
  CHECK(dll_modern_calls == 0, "glCreateShader unexpectedly used the DLL fallback");
  CHECK(glad_glGetString == (PFNGLGETSTRINGPROC)mock_get_string,
        "legacy glGetString did not fall back to GetProcAddress");
  CHECK(wgl_legacy_calls > 0, "legacy entries did not try WGL before the DLL fallback");
  CHECK(dll_legacy_calls > 0, "legacy entries did not reach GetProcAddress");
#undef CHECK

  if (failures != 0) {
    printf("WGL loader: wgl_modern=%d dll_modern=%d wgl_legacy=%d dll_legacy=%d\n",
           wgl_modern_calls, dll_modern_calls, wgl_legacy_calls,
           dll_legacy_calls);
    return 1;
  }
  printf("PASS: gladLoadGL resolved modern entry through WGL and legacy entry through DLL\n");
  return 0;
#else
  return run_native_wgl_test();
#endif
}
