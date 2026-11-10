#include <glad.h>
#include <windows.h>

#include <stdio.h>
#include <string.h>

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

int main(void) {
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
}
