#pragma once

#include <network/break_online_types.h>
#include <network/network.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_NAT_HARD_MAX_PEERS 64u
#define BREAK_NAT_HARD_MAX_PAIRS 32u

typedef struct BreakNatCoordinator BreakNatCoordinator;
typedef struct BreakNatEndpoint BreakNatEndpoint;
typedef u64 (*BreakNatClockMsFn)(void *user);

typedef struct BreakNatCoordinatorConfig {
    u32 max_peers;
    u32 max_pairs;
    u32 queue_capacity;
    BreakOnlineAuthSource auth;
    BreakNatClockMsFn clock;
    void *clock_user;
} BreakNatCoordinatorConfig;

typedef struct BreakNatEndpointConfig {
    u64 session;
    u32 queue_capacity;
    BreakNatClockMsFn clock;
    void *clock_user;
} BreakNatEndpointConfig;

BreakRuntimeError break_nat_coordinator_create(
    NetSocket *socket, const BreakNatCoordinatorConfig *config,
    BreakNatCoordinator **out);
void break_nat_coordinator_destroy(BreakNatCoordinator *coordinator);
BreakRuntimeError break_nat_coordinator_receive_socket(
    BreakNatCoordinator *coordinator, u32 max_datagrams);
BreakRuntimeError break_nat_coordinator_poll(BreakNatCoordinator *coordinator,
                                             u32 max_messages);
u32 break_nat_coordinator_peer_count(const BreakNatCoordinator *coordinator);
u64 break_nat_coordinator_invalid_messages(const BreakNatCoordinator *coordinator);
BreakRuntimeError break_nat_coordinator_peer_for_session(
    const BreakNatCoordinator *coordinator, u64 session, BreakOnlineHandle *out);
BreakRuntimeError break_nat_coordinator_peer_observed(
    const BreakNatCoordinator *coordinator, BreakOnlineHandle peer, NetAddress *out);
BreakRuntimeError break_nat_coordinator_pair(
    BreakNatCoordinator *coordinator, BreakOnlineHandle a, BreakOnlineHandle b,
    u64 nonce, u32 ttl_ms, BreakOnlineHandle *out_pair);
BreakRuntimeError break_nat_coordinator_pair_close(
    BreakNatCoordinator *coordinator, BreakOnlineHandle pair);
BreakRuntimeError break_nat_coordinator_pair_ack_mask(
    const BreakNatCoordinator *coordinator, BreakOnlineHandle pair, u32 *out);

BreakRuntimeError break_nat_endpoint_create(
    NetSocket *socket, const NetAddress *coordinator,
    const BreakNatEndpointConfig *config, BreakNatEndpoint **out);
void break_nat_endpoint_destroy(BreakNatEndpoint *endpoint);
BreakRuntimeError break_nat_peer_hello(BreakNatEndpoint *endpoint);
BreakRuntimeError break_nat_endpoint_receive_socket(BreakNatEndpoint *endpoint,
                                                    u32 max_datagrams);
BreakRuntimeError break_nat_endpoint_poll(BreakNatEndpoint *endpoint,
                                          u32 max_messages);
bool break_nat_endpoint_registered(const BreakNatEndpoint *endpoint);
bool break_nat_endpoint_armed(const BreakNatEndpoint *endpoint,
                              BreakOnlineHandle pair);
bool break_nat_endpoint_connected(const BreakNatEndpoint *endpoint,
                                  BreakOnlineHandle pair);

#ifdef __cplusplus
}
#endif
