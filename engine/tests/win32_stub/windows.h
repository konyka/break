#ifndef TEST_WIN32_STUB_WINDOWS_H
#define TEST_WIN32_STUB_WINDOWS_H

#include <stddef.h>

#ifndef APIENTRY
#define APIENTRY
#endif

typedef void* HMODULE;
typedef int BOOL;
typedef const wchar_t* LPCWSTR;

HMODULE LoadLibraryW(LPCWSTR name);
void* GetProcAddress(HMODULE module, const char* name);
BOOL FreeLibrary(HMODULE module);

#endif
