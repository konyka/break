#pragma once

#include <network/break_online_types.h>
#include <network/break_session.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline bool break_online_session_authenticate(void *user, u64 session,
                                                      BreakOnlineIdentity *out)
{
    BreakSessionManager *manager = (BreakSessionManager *)user;
    BreakSessionId id;
    if (!manager || !session || !out ||
        break_session_manager_state(manager, session) != BREAK_SESSION_AUTHENTICATED) {
        return false;
    }
    id = break_session_manager_session_id(manager, session);
    if (!id) return false;
    out->session_id = id;
    out->player_id = id;
    return true;
}

static inline BreakOnlineAuthSource break_online_session_auth(
    BreakSessionManager *manager)
{
    BreakOnlineAuthSource source;
    source.user = manager;
    source.authenticate = break_online_session_authenticate;
    return source;
}

#ifdef __cplusplus
}
#endif
