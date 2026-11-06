#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakOnlineHandle {
    u32 index;
    u32 generation;
} BreakOnlineHandle;

typedef struct BreakOnlineMemberHandle {
    BreakOnlineHandle room;
    BreakOnlineHandle member;
} BreakOnlineMemberHandle;

typedef struct BreakOnlineIdentity {
    u64 session_id;
    u64 player_id;
} BreakOnlineIdentity;

typedef bool (*BreakOnlineAuthenticateFn)(void *user, u64 session,
                                          BreakOnlineIdentity *out_identity);
typedef bool (*BreakOnlineSessionKeyFn)(void *user, u64 session,
                                        u8 out_key[32]);

typedef struct BreakOnlineAuthSource {
    void *user;
    BreakOnlineAuthenticateFn authenticate;
    BreakOnlineSessionKeyFn session_key;
} BreakOnlineAuthSource;

static inline bool break_online_handle_valid(BreakOnlineHandle handle)
{
    return handle.generation != 0u;
}

#ifdef __cplusplus
}
#endif
