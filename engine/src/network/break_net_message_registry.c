#include "network/break_net_message_registry.h"

#include <string.h>

void break_net_message_registry_init(BreakNetMessageRegistry *registry)
{
    if (registry != NULL) {
        memset(registry, 0, sizeof(*registry));
    }
}

bool break_net_message_registry_register(BreakNetMessageRegistry *registry,
                                          const BreakNetMessageDefinition *definition)
{
    if (registry == NULL || definition == NULL || definition->message_id == 0u ||
        definition->minimum_version > definition->maximum_version ||
        definition->payload_limit > BREAK_NET_MAX_PAYLOAD_SIZE ||
        registry->count >= BREAK_NET_REGISTRY_MAX_MESSAGES) {
        return false;
    }
    if (break_net_message_registry_lookup(registry, definition->message_id) != NULL) {
        return false;
    }
    registry->definitions[registry->count++] = *definition;
    return true;
}

const BreakNetMessageDefinition *break_net_message_registry_lookup(
    const BreakNetMessageRegistry *registry, uint16_t message_id)
{
    size_t i;
    if (registry == NULL || message_id == 0u) {
        return NULL;
    }
    for (i = 0u; i < registry->count; ++i) {
        if (registry->definitions[i].message_id == message_id) {
            return &registry->definitions[i];
        }
    }
    return NULL;
}

bool break_net_message_definition_supports_version(
    const BreakNetMessageDefinition *definition, uint16_t version)
{
    return definition != NULL && version >= definition->minimum_version &&
           version <= definition->maximum_version;
}

const BreakNetMessageRegistry *break_net_message_registry_default(void)
{
    static const BreakNetMessageRegistry registry = {
        {
            {BREAK_NET_MESSAGE_ID_AUTH, 1u,
#ifdef BREAK_ENABLE_CRYPTO
             2u,
#else
             1u,
#endif
             BREAK_NET_MAX_PAYLOAD_SIZE,
             BREAK_NET_MESSAGE_PHASE_ANY, BREAK_NET_DUPLICATE_REJECT},
            {BREAK_NET_MESSAGE_ID_PING, 1u, 1u, BREAK_NET_MAX_PAYLOAD_SIZE,
             BREAK_NET_MESSAGE_PHASE_ANY, BREAK_NET_DUPLICATE_IDEMPOTENT},
#ifdef BREAK_ENABLE_CRYPTO
            {BREAK_NET_MESSAGE_ID_CHALLENGE, 1u, 1u, 16u,
             BREAK_NET_MESSAGE_PHASE_ANY, BREAK_NET_DUPLICATE_REJECT}
#endif
        },
#ifdef BREAK_ENABLE_CRYPTO
        3u
#else
        2u
#endif
    };
    return &registry;
}
