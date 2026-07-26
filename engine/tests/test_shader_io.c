#include "test_framework.h"
#include <core/shader_io.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define TMP_SHADER "/tmp/test_shader_io.glsl"

TEST(shader_read_rejects_oversized_file)
{
    FILE *f = fopen(TMP_SHADER, "wb");
    ASSERT_NOT_NULL(f);
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
    ASSERT_TRUE(ftruncate(fileno(f), (off_t)SHADER_MAX_FILE_BYTES + 1) == 0);
#else
    if (fseek(f, (long)SHADER_MAX_FILE_BYTES, SEEK_SET) == 0) fputc('x', f);
#endif
    fclose(f);

    usize len = 99;
    char *data = shader_read_file(TMP_SHADER, &len);
    ASSERT_TRUE(data == NULL);
    ASSERT_EQ(len, (usize)99);

    remove(TMP_SHADER);
}

TEST_MAIN_BEGIN()
    RUN_TEST(shader_read_rejects_oversized_file);
TEST_MAIN_END()
