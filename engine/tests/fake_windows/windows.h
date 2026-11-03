#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define WINAPI
#define CALLBACK
#define TRUE 1
#define FALSE 0

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int16_t SHORT;
typedef int32_t LONG;
typedef uintptr_t ULONG_PTR;
typedef unsigned int UINT;
typedef int BOOL;
typedef void *HANDLE;
typedef HANDLE HMODULE;
typedef HANDLE HTOUCHINPUT;
typedef void (WINAPI *FARPROC)(void);

typedef struct {
    LONG x;
    LONG y;
} POINT;

typedef struct {
    LONG x;
    LONG y;
    HANDLE hSource;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dwMask;
    DWORD dwTime;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT;

#define TOUCHEVENTF_MOVE 0x0001
#define TOUCHEVENTF_DOWN 0x0002
#define TOUCHEVENTF_UP 0x0004

#define ERROR_SUCCESS 0u
#define ERROR_DEVICE_NOT_CONNECTED 1167u

static inline HMODULE LoadLibraryA(const char *name)
{
    (void)name;
    return NULL;
}

static inline FARPROC GetProcAddress(HMODULE module, const char *name)
{
    (void)module;
    (void)name;
    return NULL;
}

static inline BOOL FreeLibrary(HMODULE module)
{
    (void)module;
    return TRUE;
}
