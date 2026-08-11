/* Particle indirect-buffer contract tests. */
#include "test_framework.h"
#include <renderer/particles.h>
#include <stdlib.h>

TEST(cull_fallback_builds_complete_indirect_command)
{
    usize words = 4u + PARTICLES_MAX;
    u32 *buf = (u32 *)calloc(words, sizeof(u32));
    ASSERT_NOT_NULL(buf);

    particles_build_cull_fallback(buf, words);

    ASSERT_EQ(buf[0], 1u);
    ASSERT_EQ(buf[1], PARTICLES_MAX);
    ASSERT_EQ(buf[2], 0u);
    ASSERT_EQ(buf[3], 0u);
    ASSERT_EQ(buf[4], 0u);
    ASSERT_EQ(buf[PARTICLES_MAX + 3u], PARTICLES_MAX - 1u);
    free(buf);
}

TEST(cull_fallback_rejects_short_buffer)
{
    u32 buf[4] = {9u, 9u, 9u, 9u};
    particles_build_cull_fallback(buf, 4u);
    ASSERT_EQ(buf[0], 9u);
    ASSERT_EQ(buf[1], 9u);
    ASSERT_EQ(buf[2], 9u);
    ASSERT_EQ(buf[3], 9u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(cull_fallback_builds_complete_indirect_command);
    RUN_TEST(cull_fallback_rejects_short_buffer);
TEST_MAIN_END()
