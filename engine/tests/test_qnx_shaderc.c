#include "test_framework.h"
#include <core/types.h>
#include <shaderc/shaderc.h>

static bool compile_shader(shaderc_shader_kind kind, const char *source)
{
    shaderc_compiler_t compiler = shaderc_compiler_initialize();
    shaderc_compile_options_t options = NULL;
    shaderc_compilation_result_t result = NULL;
    usize size = 0u;
    u32 magic = 0u;
    bool ok = false;

    if (compiler == NULL) return false;
    options = shaderc_compile_options_initialize();
    if (options == NULL) goto cleanup;
    shaderc_compile_options_set_target_env(
        options, shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
    shaderc_compile_options_set_target_spirv(options, shaderc_spirv_version_1_5);
    result = shaderc_compile_into_spv(compiler, source, strlen(source), kind,
                                      "qnx_shaderc_test.glsl", "main", options);
    if (result == NULL) goto cleanup;
    if (shaderc_result_get_compilation_status(result) !=
        shaderc_compilation_status_success) {
        printf("shaderc error: %s\n", shaderc_result_get_error_message(result));
        goto cleanup;
    }
    size = shaderc_result_get_length(result);
    if (size < sizeof(magic) || size % sizeof(u32) != 0u) goto cleanup;
    memcpy(&magic, shaderc_result_get_bytes(result), sizeof(magic));
    if (magic != 0x07230203u) goto cleanup;
    ok = true;

cleanup:
    if (result != NULL) shaderc_result_release(result);
    if (options != NULL) shaderc_compile_options_release(options);
    shaderc_compiler_release(compiler);
    return ok;
}

TEST(qnx_shaderc_compiles_vertex_glsl)
{
    ASSERT_TRUE(compile_shader(
        shaderc_vertex_shader,
        "#version 450\n"
        "layout(location = 0) in vec2 position;\n"
        "void main() { gl_Position = vec4(position, 0.0, 1.0); }\n"));
}

TEST(qnx_shaderc_compiles_fragment_glsl)
{
    ASSERT_TRUE(compile_shader(
        shaderc_fragment_shader,
        "#version 450\n"
        "layout(location = 0) out vec4 color;\n"
        "void main() { color = vec4(1.0); }\n"));
}

TEST_MAIN_BEGIN()
    RUN_TEST(qnx_shaderc_compiles_vertex_glsl);
    RUN_TEST(qnx_shaderc_compiles_fragment_glsl);
TEST_MAIN_END()
