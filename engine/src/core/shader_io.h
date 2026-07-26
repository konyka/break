#pragma once

#include <core/types.h>

/* R399: single cap for all shader source reads (hotreload, main, renderers). */
#define SHADER_MAX_FILE_BYTES (4u << 20)  /* 4 MiB */

char *shader_read_file(const char *path, usize *out_len);
