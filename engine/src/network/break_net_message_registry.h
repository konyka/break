#ifndef BREAK_NET_MESSAGE_REGISTRY_H
#define BREAK_NET_MESSAGE_REGISTRY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_NET_PROTOCOL_VERSION 1u
#define BREAK_NET_MESSAGE_ID_AUTH 1u
#define BREAK_NET_MESSAGE_ID_PING 2u
#define BREAK_NET_MESSAGE_ID_CHALLENGE 3u
#define BREAK_NET_MESSAGE_ID_MAX 65535u
#define BREAK_NET_REGISTRY_MAX_MESSAGES 64u
#define BREAK_NET_MAX_PAYLOAD_SIZE (64u * 1024u)

typedef enum BreakNetMessagePhase {
    BREAK_NET_MESSAGE_PHASE_ANY = 0,
    BREAK_NET_MESSAGE_PHASE_AUTHENTICATING,
    BREAK_NET_MESSAGE_PHASE_AUTHENTICATED
} BreakNetMessagePhase;

typedef enum BreakNetDuplicatePolicy {
    BREAK_NET_DUPLICATE_REJECT = 0,
    BREAK_NET_DUPLICATE_IDEMPOTENT = 1
} BreakNetDuplicatePolicy;

typedef struct BreakNetMessageDefinition {
    uint16_t message_id;
    uint16_t minimum_version;
    uint16_t maximum_version;
    size_t payload_limit;
    BreakNetMessagePhase phase;
    BreakNetDuplicatePolicy duplicate_policy;
} BreakNetMessageDefinition;

typedef struct BreakNetMessageRegistry {
    BreakNetMessageDefinition definitions[BREAK_NET_REGISTRY_MAX_MESSAGES];
    size_t count;
} BreakNetMessageRegistry;

void break_net_message_registry_init(BreakNetMessageRegistry *registry);
bool break_net_message_registry_register(BreakNetMessageRegistry *registry,
                                          const BreakNetMessageDefinition *definition);
const BreakNetMessageDefinition *break_net_message_registry_lookup(
    const BreakNetMessageRegistry *registry, uint16_t message_id);
bool break_net_message_definition_supports_version(
    const BreakNetMessageDefinition *definition, uint16_t version);

const BreakNetMessageRegistry *break_net_message_registry_default(void);

#ifdef __cplusplus
}
#endif

#endif
