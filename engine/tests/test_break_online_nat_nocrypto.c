#include "test_framework.h"
#include <network/break_online_nat.h>

#include <string.h>

static bool test_authenticate(void *user, u64 session, BreakOnlineIdentity *out)
{
    (void)user; (void)session;
    out->session_id = 1u;
    out->player_id = 1u;
    return true;
}

static bool test_session_key(void *user, u64 session, u8 out_key[32])
{
    (void)user; (void)session;
    memset(out_key, 0, 32u);
    return true;
}

static u64 test_clock(void *user)
{
    (void)user;
    return 0u;
}

TEST(no_crypto_network_subsystem_initializes)
{
    ASSERT_TRUE(net_init());
}

TEST(no_crypto_nat_create_fails_closed_with_null_outputs)
{
    NetSocket *socket = net_udp_create(0);
    BreakNatCoordinatorConfig coordinator_config;
    BreakNatEndpointConfig endpoint_config;
    BreakNatCoordinator *coordinator = (BreakNatCoordinator *)1;
    BreakNatEndpoint *endpoint = (BreakNatEndpoint *)1;
    NetAddress coordinator_address;
    u32 i;
    ASSERT_NOT_NULL(socket);
    memset(&coordinator_config, 0, sizeof(coordinator_config));
    coordinator_config.max_peers = 1u;
    coordinator_config.max_pairs = 1u;
    coordinator_config.queue_capacity = 1u;
    coordinator_config.auth.authenticate = test_authenticate;
    coordinator_config.auth.session_key = test_session_key;
    coordinator_config.clock = NULL;
    coordinator_config.challenge_key[0] = 1u;
    ASSERT_EQ(break_nat_coordinator_create(socket, &coordinator_config, &coordinator),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(coordinator, NULL);
    coordinator_config.clock = test_clock;
    ASSERT_EQ(break_nat_coordinator_create(socket, &coordinator_config, &coordinator),
              BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(coordinator, NULL);
    memset(&coordinator_address, 0, sizeof(coordinator_address));
    strcpy(coordinator_address.host, "127.0.0.1");
    coordinator_address.port = 9u;
    memset(&endpoint_config, 0, sizeof(endpoint_config));
    endpoint_config.session = 1u;
    endpoint_config.queue_capacity = 1u;
    endpoint_config.session_key = test_session_key;
    endpoint_config.clock = test_clock;
    ASSERT_EQ(break_nat_endpoint_create(socket, &coordinator_address,
                                        &endpoint_config, &endpoint),
              BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(endpoint, NULL);
    for (i = 0u; i < 32u; ++i) {
        ASSERT_EQ(coordinator_config.challenge_key[i], i == 0u ? 1u : 0u);
    }
    net_close(socket);
    net_shutdown();
}

TEST_MAIN_BEGIN()
    RUN_TEST(no_crypto_network_subsystem_initializes);
    RUN_TEST(no_crypto_nat_create_fails_closed_with_null_outputs);
TEST_MAIN_END()
