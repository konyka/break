#include "test_framework.h"

#include <network/break_online_aspect_session.h>

#include <string.h>

static uint64_t test_aspect_session_link_clock(void *user)
{
    return *(const uint64_t *)user;
}

/* Links only break_net_test: the aspect symbols must arrive through the
 * library's public link interface, not through an explicit break_online. */
TEST(aspect_session_api_links_without_explicit_break_online)
{
    BreakAspectStoreConfig store_config = {2u, 16u, 128u};
    BreakAspectSchema schema = {2u, 1u, BREAK_ASPECT_U32, 4u};
    BreakAspectStore *store = NULL;
    BreakAspectSessionConfig config;
    BreakAspectSession *session;
    uint64_t now = 0u;

    ASSERT_EQ(break_aspect_store_create(&store_config, &store), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_schema_register(store, &schema), BREAK_RUNTIME_OK);
    memset(&config, 0, sizeof(config));
    config.store = store;
    config.bridge.max_connections = 1u;
    config.bridge.stream_capacity = 2u;
    config.bridge.max_pending_bytes_per_connection = 128u;
    config.bridge.max_total_pending_bytes = 128u;
    config.bridge.max_metadata_bytes_per_connection = 4096u;
    config.bridge.max_total_metadata_bytes = 4096u;
    config.bridge.max_fragment_bytes = 64u;
    config.bridge.max_fragment_count = 4u;
    config.bridge.completion_capacity = 2u;
    config.bridge.max_completion_packet_bytes = 128u;
    config.bridge.max_completion_queue_bytes = 256u;
    config.bridge.clock = test_aspect_session_link_clock;
    config.bridge.clock_user = &now;
    session = break_aspect_session_create(&config);
    ASSERT_NOT_NULL(session);
    ASSERT_TRUE(break_aspect_session_open(session, 1u));
    ASSERT_TRUE(break_aspect_session_close(session, 1u));
    break_aspect_session_destroy(session);
    break_aspect_store_destroy(store);
}
TEST_MAIN_BEGIN()
    RUN_TEST(aspect_session_api_links_without_explicit_break_online);
TEST_MAIN_END()
