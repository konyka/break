#include <windows.h>
#include <glad.h>

#include <stdio.h>
#include <string.h>

#define FUNCTION_POINTERS_EQUAL(actual, expected)                              \
  (sizeof(actual) == sizeof(expected) &&                                       \
   memcmp(&(actual), &(expected), sizeof(actual)) == 0)

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
typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

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
  int modern_context_supported = 0;
  int max_texture_size = 0;
  int major = 0;
  int minor = 0;
  int profile = 0;
  int extension_count = 0;
  HINSTANCE instance = GetModuleHandleW(NULL);
  const wchar_t class_name[] = L"break_wgl_loader_test";
  WNDCLASSEXW wc;
  PIXELFORMATDESCRIPTOR pfd;
  HWND hwnd = NULL;
  HDC dc = NULL;
  HGLRC context = NULL;
  HGLRC modern_context = NULL;
  HMODULE real_module = NULL;
  BOOL class_registered = FALSE;
  PROC create_context_attribs_proc = NULL;
  PROC wgl_create_shader = NULL;
  PROC wgl_get_stringi = NULL;
  FARPROC dll_get_string = NULL;
  FARPROC dll_get_integerv = NULL;
  PFNWGLCREATECONTEXTATTRIBSARBPROC create_context_attribs = NULL;
  const GLubyte* version_string = NULL;
  const GLubyte* renderer_string = NULL;
  const GLubyte* extension_string = NULL;
  char version[256] = "unavailable";
  char renderer[256] = "unavailable";
  int context_attribs[] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
      WGL_CONTEXT_MINOR_VERSION_ARB, 5,
      WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      0};

  if (instance == NULL) {
    failures += check_native(0, "GetModuleHandleW failed");
    goto cleanup;
  }
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
  dll_get_string = GetProcAddress(real_module, "glGetString");
  dll_get_integerv = GetProcAddress(real_module, "glGetIntegerv");
  failures += check_native(dll_get_string != NULL, "GetProcAddress(glGetString) failed");
  failures += check_native(dll_get_integerv != NULL,
                           "GetProcAddress(glGetIntegerv) failed");
  loaded = gladLoadGL();
  failures += check_native(loaded == 1, "bootstrap gladLoadGL did not initialize");
  failures += check_native(glad_glGetString != NULL, "no legacy glGetString entry");
  failures += check_native(glad_glGetIntegerv != NULL, "no legacy glGetIntegerv entry");
  failures += check_native(FUNCTION_POINTERS_EQUAL(glad_glGetString, dll_get_string),
                           "legacy glGetString differs from the real opengl32 export");
  failures += check_native(
      FUNCTION_POINTERS_EQUAL(glad_glGetIntegerv, dll_get_integerv),
      "glGetIntegerv differs from the real opengl32 export");
  if (glad_glGetString != NULL) {
    version_string = glad_glGetString(GL_VERSION);
    renderer_string = glad_glGetString(GL_RENDERER);
    failures += check_native(version_string != NULL && version_string[0] != '\0',
                             "the real opengl32 version query returned no version string");
    failures += check_native(renderer_string != NULL && renderer_string[0] != '\0',
                             "the real opengl32 renderer query returned no renderer string");
    if (version_string != NULL) {
      snprintf(version, sizeof(version), "%s", (const char*)version_string);
    }
    if (renderer_string != NULL) {
      snprintf(renderer, sizeof(renderer), "%s", (const char*)renderer_string);
    }
  }
  if (glad_glGetIntegerv != NULL) {
    glad_glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);
    failures += check_native(max_texture_size > 0,
                             "legacy glGetIntegerv returned no texture size");
  }

  create_context_attribs_proc = wglGetProcAddress("wglCreateContextAttribsARB");
  modern_context_supported = create_context_attribs_proc != NULL;
  if (!modern_context_supported) goto cleanup;
  failures += check_native(sizeof(create_context_attribs) ==
                               sizeof(create_context_attribs_proc),
                           "wglCreateContextAttribsARB pointer size mismatch");
  if (sizeof(create_context_attribs) != sizeof(create_context_attribs_proc)) {
    goto cleanup;
  }
  memcpy(&create_context_attribs, &create_context_attribs_proc,
         sizeof(create_context_attribs));
  modern_context = create_context_attribs(dc, NULL, context_attribs);
  if (modern_context == NULL) {
    failures += check_native(0, "advertised wglCreateContextAttribsARB failed for GL 4.5 core");
    goto cleanup;
  }
  if (!wglMakeCurrent(dc, modern_context)) {
    failures += check_native(0, "wglMakeCurrent failed for the modern context");
    goto cleanup;
  }
  if (!wglDeleteContext(context)) {
    failures += check_native(0, "wglDeleteContext failed for the bootstrap context");
    goto cleanup;
  }
  context = NULL;

  loaded = gladLoadGL();
  failures += check_native(loaded == 1, "modern gladLoadGL did not initialize");
  wgl_create_shader = wglGetProcAddress("glCreateShader");
  wgl_get_stringi = wglGetProcAddress("glGetStringi");
  failures += check_native(glad_glCreateShader != NULL,
                           "no glCreateShader entry on the modern WGL context");
  failures += check_native(glad_glGetStringi != NULL,
                           "no glGetStringi entry on the modern WGL context");
  failures += check_native(glad_glGetString != NULL,
                           "no legacy glGetString entry on the modern WGL context");
  failures += check_native(glad_glGetIntegerv != NULL,
                           "no legacy glGetIntegerv entry on the modern WGL context");
  failures += check_native(FUNCTION_POINTERS_EQUAL(glad_glCreateShader, wgl_create_shader),
                           "glCreateShader differs from the real wglGetProcAddress result");
  failures += check_native(FUNCTION_POINTERS_EQUAL(glad_glGetStringi, wgl_get_stringi),
                           "glGetStringi differs from the real wglGetProcAddress result");
  failures += check_native(FUNCTION_POINTERS_EQUAL(glad_glGetString, dll_get_string),
                           "modern glGetString differs from the real opengl32 export");
  failures += check_native(
      FUNCTION_POINTERS_EQUAL(glad_glGetIntegerv, dll_get_integerv),
      "modern glGetIntegerv differs from the real opengl32 export");
  if (glad_glGetString != NULL) {
    version_string = glad_glGetString(GL_VERSION);
    renderer_string = glad_glGetString(GL_RENDERER);
    failures += check_native(version_string != NULL && version_string[0] != '\0',
                             "modern glGetString returned no version string");
    failures += check_native(renderer_string != NULL && renderer_string[0] != '\0',
                             "modern glGetString returned no renderer string");
    if (version_string != NULL) {
      snprintf(version, sizeof(version), "%s", (const char*)version_string);
    }
    if (renderer_string != NULL) {
      snprintf(renderer, sizeof(renderer), "%s", (const char*)renderer_string);
    }
  }
  if (glad_glGetIntegerv != NULL) {
    glad_glGetIntegerv(GL_MAJOR_VERSION, &major);
    glad_glGetIntegerv(GL_MINOR_VERSION, &minor);
    glad_glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
    glad_glGetIntegerv(GL_NUM_EXTENSIONS, &extension_count);
    failures += check_native(major > 4 || (major == 4 && minor >= 5),
                             "the current context is not OpenGL 4.5 or newer");
    failures += check_native((profile & GL_CONTEXT_CORE_PROFILE_BIT) != 0,
                             "the current context is not a core profile");
    failures += check_native(extension_count > 0,
                             "modern glGetIntegerv returned no extensions");
  }
  if (glad_glGetStringi != NULL && extension_count > 0) {
    extension_string = glad_glGetStringi(GL_EXTENSIONS, 0);
    failures += check_native(extension_string != NULL && extension_string[0] != '\0',
                             "modern glGetStringi returned no extension");
  }

cleanup:
  if (context != NULL || modern_context != NULL) {
    failures += check_native(wglMakeCurrent(NULL, NULL),
                             "wglMakeCurrent(NULL, NULL) failed");
  }
  if (modern_context != NULL) {
    failures += check_native(wglDeleteContext(modern_context),
                             "wglDeleteContext failed for the modern context");
  }
  if (context != NULL) {
    failures += check_native(wglDeleteContext(context),
                             "wglDeleteContext failed during cleanup");
  }
  if (dc != NULL) {
    failures += check_native(ReleaseDC(hwnd, dc) != 0, "ReleaseDC failed");
  }
  if (hwnd != NULL) {
    failures += check_native(DestroyWindow(hwnd), "DestroyWindow failed");
  }
  if (class_registered) {
    failures += check_native(UnregisterClassW(class_name, instance),
                             "UnregisterClassW failed");
  }
  if (real_module != NULL) {
    failures += check_native(FreeLibrary(real_module), "FreeLibrary failed");
  }

  if (failures != 0) {
    printf("FAIL: WGL native loader: loaded=%d modern_context_supported=%d "
           "GL_VERSION=%s GL_RENDERER=%s\n",
           loaded, modern_context_supported, version, renderer);
    return failures;
  }
  if (failures == 0 && !modern_context_supported) {
    printf("SKIP: WGL_ARB_create_context unavailable; GL_VERSION=%s GL_RENDERER=%s\n",
           version, renderer);
    return 77;
  }
  printf("PASS: gladLoadGL resolved modern WGL and legacy DLL entries; "
         "GL_VERSION=%s GL_RENDERER=%s\n",
         version, renderer);
  return 0;
}
#endif

int main(void) {
#ifdef TEST_WGL_LOADER_SIMULATED
  int failures = 0;
  int loaded = gladLoadGL();
  PFNGLCREATESHADERPROC expected_create_shader = mock_create_shader;
  PFNGLGETSTRINGPROC expected_get_string = mock_get_string;
#define CHECK(condition, message)                                                \
  do {                                                                           \
    if (!(condition)) {                                                          \
      printf("FAIL: %s\n", message);                                            \
      failures++;                                                                \
    }                                                                            \
  } while (0)

  CHECK(loaded == 1, "gladLoadGL did not initialize with the test DLL");
  CHECK(FUNCTION_POINTERS_EQUAL(glad_glCreateShader, expected_create_shader),
        "glCreateShader was not resolved through wglGetProcAddress");
  CHECK(wgl_modern_calls == 1, "wglGetProcAddress did not resolve glCreateShader");
  CHECK(dll_modern_calls == 0, "glCreateShader unexpectedly used the DLL fallback");
  CHECK(FUNCTION_POINTERS_EQUAL(glad_glGetString, expected_get_string),
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
