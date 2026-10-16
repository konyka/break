#pragma once

#include <core/types.h>
#include <rhi/rhi.h>

/* R399: single cap for all shader source reads (hotreload, main, renderers). */
#define SHADER_MAX_FILE_BYTES (4u << 20)  /* 4 MiB */

typedef enum {
    SHADER_IO_RESOURCE_SAMPLER,
    SHADER_IO_RESOURCE_UNIFORM,
    SHADER_IO_RESOURCE_STORAGE,
    SHADER_IO_RESOURCE_PUSH_CONSTANT,
    SHADER_IO_RESOURCE_IMAGE,
} ShaderIOResourceKind;

typedef enum {
    SHADER_IO_LAYOUT_DEFAULT,
    SHADER_IO_LAYOUT_STD140,
    SHADER_IO_LAYOUT_STD430,
    SHADER_IO_LAYOUT_PUSH_CONSTANT,
} ShaderIOLayout;

#define SHADER_IO_NAME_MAX 64u
#define SHADER_IO_FORMAT_MAX 32u

typedef struct {
    char name[SHADER_IO_NAME_MAX];
    char format[SHADER_IO_FORMAT_MAX];
    ShaderIOResourceKind kind;
    ShaderIOLayout layout;
    u32 set;
    u32 binding;
    u32 location;
} ShaderIOBinding;

u64 shader_reflect_bindings_hash(const ShaderIOBinding *bindings, usize count);
usize shader_reflect_bindings(const char *src, usize len,
                              ShaderIOBinding *out, usize capacity);

char *shader_read_file(const char *path, usize *out_len);

/* Inserts `#define <name> 1` immediately after the #version line. */
char *shader_inject_define(const char *src, usize len, const char *name, usize *out_len);

/* 计划 E Task 2：后端 shader 变体路径（caps.shader_variant 驱动）。 */
const char *shader_variant_suffix(RHIShaderVariant v); /* "" 或 "_vk" */
/* "shaders/foo.vert" + GLSL_VK -> 写出 "shaders/foo_vk.vert"；越界返回 NULL。 */
char *shader_variant_path(const char *base_path, RHIShaderVariant v,
                          char *out, usize cap);
