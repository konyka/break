#pragma once

#include <core/types.h>

typedef struct PlatformDynamicLibrary PlatformDynamicLibrary;

PlatformDynamicLibrary *platform_dynamic_open(const char *path);
void *platform_dynamic_symbol(PlatformDynamicLibrary *library, const char *name);
void platform_dynamic_close(PlatformDynamicLibrary *library);
