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
    /* Editor wire protocol (Stage 4 scene editor Phase 4): ids 4..20 occupy
     * the free id space after AUTH/PING/CHALLENGE. The envelope codec only
     * consults this default registry, so the editor messages MUST be
     * registered here (docs/design/session_protocol.md:117 — the documented
     * codec boundary). payload_limit 4096 matches the editor protocol's
     * inbound bound (editor/editor_protocol.h). Duplicate policy is
     * IDEMPOTENT: the session layer treats REJECT as "at most once per
     * session" (message_seen && REJECT => duplicate — the AUTH/CHALLENGE
     * semantics), which would make every editor command single-use per
     * connection. IDEMPOTENT dispatches every request with a new sequence
     * and only swallows an exact replay of the last sequence for that id
     * (documented in docs/design/editor_remote.md). */
#define BREAK_EDITOR_DEF(id)                                                  \
    {(id), 1u, 1u, 4096u, BREAK_NET_MESSAGE_PHASE_ANY,                        \
     BREAK_NET_DUPLICATE_IDEMPOTENT}
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
             BREAK_NET_MESSAGE_PHASE_ANY, BREAK_NET_DUPLICATE_REJECT},
#endif
            BREAK_EDITOR_DEF(4u),  /* DESCRIBE */
            BREAK_EDITOR_DEF(5u),  /* LIST */
            BREAK_EDITOR_DEF(6u),  /* SPAWN */
            BREAK_EDITOR_DEF(7u),  /* REMOVE */
            BREAK_EDITOR_DEF(8u),  /* RENAME */
            BREAK_EDITOR_DEF(9u),  /* SET_FIELD */
            BREAK_EDITOR_DEF(10u), /* UNDO */
            BREAK_EDITOR_DEF(11u), /* REDO */
            BREAK_EDITOR_DEF(12u), /* EVAL */
            BREAK_EDITOR_DEF(13u), /* RESULT */
            BREAK_EDITOR_DEF(14u), /* SAVE */
            BREAK_EDITOR_DEF(15u), /* LOAD */
            BREAK_EDITOR_DEF(16u), /* VIEW */
            BREAK_EDITOR_DEF(17u), /* CAMERA_SET */
            BREAK_EDITOR_DEF(18u), /* HISTORY */
            BREAK_EDITOR_DEF(19u), /* UNDO_OWN */
            BREAK_EDITOR_DEF(20u)  /* REDO_OWN */
        },
#ifdef BREAK_ENABLE_CRYPTO
        20u
#else
        19u
#endif
    };
#undef BREAK_EDITOR_DEF
    return &registry;
}
