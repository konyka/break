#pragma once
/* Test-only UDP impairment proxy backed by Snowflake's SnowUdpEngine.
 * Each channel owns one loopback port so the server can distinguish clients. */

#include <core/types.h>

#define TEST_QUIC_UDP_PROXY_STATS_DIRS 2u

typedef struct TestQuicUdpProxySet TestQuicUdpProxySet;

typedef struct TestQuicUdpProxyStats {
    u64 received[TEST_QUIC_UDP_PROXY_STATS_DIRS];
    u64 forwarded;
    u64 dropped;
    u64 delayed;
    u64 reordered;
    u32 queued;
} TestQuicUdpProxyStats;

bool test_quic_udp_proxy_set_create(u16 server_port, u32 channel_count,
                                    TestQuicUdpProxySet **out);
void test_quic_udp_proxy_set_destroy(TestQuicUdpProxySet **set);
u16 test_quic_udp_proxy_port(const TestQuicUdpProxySet *set, u32 channel);

/* Impairment is off during handshake/authentication. Once enabled, every
 * drop_every-th packet per direction is dropped and all others are delayed.
 * With reorder_first, the first packet per direction is delayed twice as long
 * so a later packet is actually transmitted first. Zero disables each rule. */
void test_quic_udp_proxy_set_impairment(TestQuicUdpProxySet *set, bool enabled,
                                        u32 drop_every, u32 delay_ms,
                                        bool reorder_first);
bool test_quic_udp_proxy_set_step(TestQuicUdpProxySet *set, u32 timeout_ms);
void test_quic_udp_proxy_set_stats(const TestQuicUdpProxySet *set, u32 channel,
                                   TestQuicUdpProxyStats *out);
