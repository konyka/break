/* Authoritative merge: a connection may write only the entities it owns and
 * only writable components, each value passes its validator, and a rejected
 * value leaves the authoritative World untouched. */
#include "test_framework.h"

#include <ecs/world_merge.h>

#include <string.h>

enum { kPos = 3u, kHealth = 4u, kTag = 5u };
enum { kAuth = 1u, kInbound = 2u };
enum { kA = 11u, kB = 22u };

typedef struct {
    i32 x;
    i32 y;
} Pos;

typedef struct {
    u32 calls;
    i32 max_step; /* a move longer than this per axis is clamped */
    bool reject_negative_x;
    BreakWorldMergeConnection last_connection;
    BreakNetEntityId last_id;
} Rules;

static BreakWorldMergeVerdict validate_pos(void *user, BreakWorldMergeConnection connection,
                                           BreakNetEntityId id, ComponentType component,
                                           const void *current, const void *proposed,
                                           void *accepted, u32 size) {
    Rules *rules = (Rules *)user;
    const Pos *cur = (const Pos *)current;
    const Pos *pro = (const Pos *)proposed;
    Pos *acc = (Pos *)accepted;
    rules->calls++;
    rules->last_connection = connection;
    rules->last_id = id;
    if (component != kPos || size != sizeof(Pos)) return BREAK_WORLD_MERGE_REJECT;
    if (memcmp(acc, pro, sizeof(Pos)) != 0) return BREAK_WORLD_MERGE_REJECT;
    if (rules->reject_negative_x && pro->x < 0) return BREAK_WORLD_MERGE_REJECT;
    if (pro->x - cur->x > rules->max_step) acc->x = cur->x + rules->max_step;
    if (cur->x - pro->x > rules->max_step) acc->x = cur->x - rules->max_step;
    if (pro->y - cur->y > rules->max_step) acc->y = cur->y + rules->max_step;
    if (cur->y - pro->y > rules->max_step) acc->y = cur->y - rules->max_step;
    return BREAK_WORLD_MERGE_ACCEPT;
}

/* Lowering health is a peer's business; raising it is kept as it was. */
static BreakWorldMergeVerdict validate_health(void *user, BreakWorldMergeConnection connection,
                                              BreakNetEntityId id, ComponentType component,
                                              const void *current, const void *proposed,
                                              void *accepted, u32 size) {
    (void)user;
    (void)connection;
    (void)id;
    (void)accepted;
    if (component != kHealth || size != sizeof(u32)) return BREAK_WORLD_MERGE_REJECT;
    return *(const u32 *)proposed <= *(const u32 *)current ? BREAK_WORLD_MERGE_ACCEPT
                                                           : BREAK_WORLD_MERGE_KEEP;
}

/* One authoritative World and two peers' inbound Worlds, each with its own
 * id map. Entity i has id ids[i] in all three. */
typedef struct {
    World *auth;
    World *in[2];
    BreakNetEntityMap *auth_ids;
    BreakNetEntityMap *in_ids[2];
    BreakNetEntityId id[3];
    Entity auth_e[3];
    Entity in_e[2][3];
    Rules rules;
    BreakWorldMerge *merge;
} Fx;

static World *make_world(void) {
    World *w = world_create();
    world_register_component(w, kPos, (u32)sizeof(Pos));
    world_register_component(w, kHealth, (u32)sizeof(u32));
    world_register_component(w, kTag, (u32)sizeof(u32));
    return w;
}

static Entity spawn(World *w, i32 x, u32 health) {
    Entity e = world_create_entity(w);
    Pos *p = (Pos *)world_add_component(w, e, kPos);
    p->x = x;
    p->y = 0;
    *(u32 *)world_add_component(w, e, kHealth) = health;
    *(u32 *)world_add_component(w, e, kTag) = 7u;
    return e;
}

static Pos pos_of(World *w, Entity e) {
    Pos p;
    memcpy(&p, world_get_component(w, e, kPos), sizeof p);
    return p;
}

static Pos *pos_at(World *w, Entity e) { return (Pos *)world_get_component(w, e, kPos); }
static u32 *health_at(World *w, Entity e) { return (u32 *)world_get_component(w, e, kHealth); }
static u32 *tag_at(World *w, Entity e) { return (u32 *)world_get_component(w, e, kTag); }

static BreakWorldMergeConfig base_config(Fx *fx, BreakWorldMergeComponent comps[2]) {
    BreakWorldMergeConfig cfg;
    memset(comps, 0, 2u * sizeof(*comps));
    comps[0].component = kPos;
    comps[0].validate = validate_pos;
    comps[0].user = &fx->rules;
    comps[1].component = kHealth;
    comps[1].validate = validate_health;
    memset(&cfg, 0, sizeof cfg);
    cfg.authoritative = fx->auth;
    cfg.ids = fx->auth_ids;
    cfg.authoritative_key = kAuth;
    cfg.components = comps;
    cfg.component_count = 2u;
    cfg.max_owned = 4u;
    return cfg;
}

static bool fx_init(Fx *fx) {
    BreakNetEntityMapConfig mc = {64u, 100u};
    BreakWorldMergeComponent comps[2];
    BreakWorldMergeConfig cfg;
    memset(fx, 0, sizeof(*fx));
    fx->rules.max_step = 5;
    fx->auth = make_world();
    if (!break_net_entity_map_create(&mc, &fx->auth_ids)) return false;
    for (u32 c = 0u; c < 2u; ++c) {
        fx->in[c] = make_world();
        if (!break_net_entity_map_create(&mc, &fx->in_ids[c])) return false;
    }
    for (u32 i = 0u; i < 3u; ++i) {
        fx->auth_e[i] = spawn(fx->auth, (i32)(10u * i), 100u);
        if (break_net_entity_map_bind_new(fx->auth_ids, kAuth, fx->auth_e[i], &fx->id[i]) !=
            BREAK_NET_ENTITY_OK) {
            return false;
        }
        for (u32 c = 0u; c < 2u; ++c) {
            fx->in_e[c][i] = spawn(fx->in[c], (i32)(10u * i), 100u);
            if (break_net_entity_map_adopt(fx->in_ids[c], fx->id[i], kInbound, fx->in_e[c][i]) !=
                BREAK_NET_ENTITY_OK) {
                return false;
            }
        }
    }
    cfg = base_config(fx, comps);
    return break_world_merge_create(&cfg, &fx->merge) == BREAK_WORLD_MERGE_OK;
}

static void fx_dispose(Fx *fx) {
    break_world_merge_destroy(fx->merge);
    for (u32 c = 0u; c < 2u; ++c) {
        break_net_entity_map_destroy(fx->in_ids[c]);
        world_destroy(fx->in[c]);
    }
    break_net_entity_map_destroy(fx->auth_ids);
    world_destroy(fx->auth);
}

static BreakWorldMergeResult merge_peer(Fx *fx, u32 peer, BreakWorldMergeReport *rep) {
    return break_world_merge_connection(fx->merge, peer == 0u ? kA : kB, fx->in[peer],
                                        fx->in_ids[peer], kInbound, rep);
}

TEST(an_owned_entity_takes_the_validated_value) {
    Fx fx;
    BreakWorldMergeReport rep;
    BreakWorldMergeStats st;
    ASSERT_TRUE(fx_init(&fx));
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[0]), BREAK_WORLD_MERGE_OK);
    pos_at(fx.in[0], fx.in_e[0][0])->x = 3;
    pos_at(fx.in[0], fx.in_e[0][0])->y = 20; /* too far in one step: clamped to +5 */
    ASSERT_EQ(merge_peer(&fx, 0u, &rep), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).x, 3);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).y, 5);
    ASSERT_EQ(rep.entities, 1u);
    ASSERT_EQ(rep.written, 1u);
    ASSERT_EQ(rep.unchanged, 1u); /* health is equal on both sides */
    ASSERT_EQ(rep.kept, 0u);
    ASSERT_EQ(rep.skipped, 0u);
    ASSERT_EQ(fx.rules.calls, 1u);
    ASSERT_EQ(fx.rules.last_connection, (u64)kA);
    ASSERT_EQ(fx.rules.last_id, fx.id[0]);
    break_world_merge_stats(fx.merge, &st);
    ASSERT_EQ(st.merges, 1u);
    ASSERT_EQ(st.written, 1u);
    ASSERT_EQ(st.owned, 1u);
    fx_dispose(&fx);
}

TEST(entities_the_connection_does_not_own_are_ignored) {
    Fx fx;
    BreakWorldMergeReport rep;
    ASSERT_TRUE(fx_init(&fx));
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[0]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kB, fx.id[1]), BREAK_WORLD_MERGE_OK);
    /* A writes its own entity, B's entity and an unowned one */
    pos_at(fx.in[0], fx.in_e[0][0])->x = 2;
    pos_at(fx.in[0], fx.in_e[0][1])->x = 99;
    pos_at(fx.in[0], fx.in_e[0][2])->x = 99;
    ASSERT_EQ(merge_peer(&fx, 0u, &rep), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).x, 2);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[1]).x, 10);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[2]).x, 20);
    ASSERT_EQ(rep.entities, 1u);
    /* B's own write goes through */
    pos_at(fx.in[1], fx.in_e[1][1])->x = 12;
    ASSERT_EQ(merge_peer(&fx, 1u, &rep), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[1]).x, 12);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).x, 2);
    fx_dispose(&fx);
}

/* Several accepted values of different entities and components in one batch
 * each land in their own place. */
TEST(every_accepted_value_of_a_batch_lands_where_it_belongs) {
    Fx fx;
    BreakWorldMergeReport rep;
    ASSERT_TRUE(fx_init(&fx));
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[0]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[2]), BREAK_WORLD_MERGE_OK);
    pos_at(fx.in[0], fx.in_e[0][0])->x = 4;
    *health_at(fx.in[0], fx.in_e[0][0]) = 60u;
    pos_at(fx.in[0], fx.in_e[0][2])->x = 18;
    pos_at(fx.in[0], fx.in_e[0][2])->y = -3;
    *health_at(fx.in[0], fx.in_e[0][2]) = 30u;
    ASSERT_EQ(merge_peer(&fx, 0u, &rep), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(rep.written, 4u);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).x, 4);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).y, 0);
    ASSERT_EQ(*health_at(fx.auth, fx.auth_e[0]), 60u);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[2]).x, 18);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[2]).y, -3);
    ASSERT_EQ(*health_at(fx.auth, fx.auth_e[2]), 30u);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[1]).x, 10);
    fx_dispose(&fx);
}

TEST(only_writable_components_are_merged) {
    Fx fx;
    BreakWorldMergeReport rep;
    ASSERT_TRUE(fx_init(&fx));
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[0]), BREAK_WORLD_MERGE_OK);
    *tag_at(fx.in[0], fx.in_e[0][0]) = 999u; /* not registered as writable */
    *health_at(fx.in[0], fx.in_e[0][0]) = 40u;
    ASSERT_EQ(merge_peer(&fx, 0u, &rep), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(*tag_at(fx.auth, fx.auth_e[0]), 7u);
    ASSERT_EQ(*health_at(fx.auth, fx.auth_e[0]), 40u);
    /* raising health is KEEP: unchanged, and the rest of the batch still applies */
    *health_at(fx.in[0], fx.in_e[0][0]) = 90u;
    pos_at(fx.in[0], fx.in_e[0][0])->x = 1;
    ASSERT_EQ(merge_peer(&fx, 0u, &rep), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(*health_at(fx.auth, fx.auth_e[0]), 40u);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).x, 1);
    ASSERT_EQ(rep.kept, 1u);
    ASSERT_EQ(rep.written, 1u);
    fx_dispose(&fx);
}

TEST(a_rejected_value_applies_nothing_of_the_batch) {
    Fx fx;
    BreakWorldMergeReport rep;
    BreakWorldMergeStats st;
    ASSERT_TRUE(fx_init(&fx));
    fx.rules.reject_negative_x = true;
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[0]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[1]), BREAK_WORLD_MERGE_OK);
    pos_at(fx.in[0], fx.in_e[0][0])->x = 4;        /* fine */
    *health_at(fx.in[0], fx.in_e[0][0]) = 50u;     /* fine */
    pos_at(fx.in[0], fx.in_e[0][1])->x = -1;       /* refused */
    memset(&rep, 0xab, sizeof rep);
    ASSERT_EQ(merge_peer(&fx, 0u, &rep), BREAK_WORLD_MERGE_REJECTED);
    ASSERT_EQ(rep.written, 0u);
    ASSERT_EQ(rep.entities, 0u);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).x, 0);
    ASSERT_EQ(*health_at(fx.auth, fx.auth_e[0]), 100u);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[1]).x, 10);
    break_world_merge_stats(fx.merge, &st);
    ASSERT_EQ(st.rejected, 1u);
    ASSERT_EQ(st.written, 0u);
    ASSERT_EQ(st.merges, 0u);
    fx_dispose(&fx);
}

TEST(structure_is_never_changed_by_a_peer) {
    Fx fx;
    BreakWorldMergeReport rep;
    Entity extra;
    ASSERT_TRUE(fx_init(&fx));
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[0]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[1]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[2]), BREAK_WORLD_MERGE_OK);
    /* the peer removed a component, destroyed an entity, created one */
    world_remove_component(fx.in[0], fx.in_e[0][0], kHealth);
    pos_at(fx.in[0], fx.in_e[0][0])->x = 3;
    world_destroy_entity(fx.in[0], fx.in_e[0][1]);
    extra = spawn(fx.in[0], 500, 1u);
    (void)extra;
    /* and the authority removed a writable component from entity 2 */
    world_remove_component(fx.auth, fx.auth_e[2], kPos);
    pos_at(fx.in[0], fx.in_e[0][2])->x = 21;
    ASSERT_EQ(merge_peer(&fx, 0u, &rep), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).x, 3);
    ASSERT_NOT_NULL(health_at(fx.auth, fx.auth_e[0]));
    ASSERT_EQ(*health_at(fx.auth, fx.auth_e[0]), 100u);
    ASSERT_TRUE(world_entity_exists(fx.auth, fx.auth_e[1]));
    ASSERT_TRUE(world_get_component(fx.auth, fx.auth_e[2], kPos) == NULL);
    ASSERT_EQ(rep.entities, 2u);  /* entity 1 is gone from the inbound World */
    ASSERT_EQ(rep.skipped, 3u);   /* entity 1, entity 0's health, entity 2's position */
    ASSERT_EQ(rep.written, 1u);
    fx_dispose(&fx);
}

TEST(ownership_grant_conflict_revoke_and_capacity) {
    Fx fx;
    BreakNetEntityId extra = 9999u;
    BreakWorldMergeReport rep;
    ASSERT_TRUE(fx_init(&fx));
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[0]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[0]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kB, fx.id[0]), BREAK_WORLD_MERGE_CONFLICT);
    ASSERT_EQ(break_world_merge_owner(fx.merge, fx.id[0]), (u64)kA);
    ASSERT_EQ(break_world_merge_owner(fx.merge, fx.id[1]), 0u);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[1]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kB, fx.id[2]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kB, extra), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kB, extra + 1u), BREAK_WORLD_MERGE_OVERLOAD);
    ASSERT_EQ(break_world_merge_revoke(fx.merge, fx.id[0]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_revoke(fx.merge, fx.id[0]), BREAK_WORLD_MERGE_NOT_FOUND);
    ASSERT_EQ(break_world_merge_owner(fx.merge, fx.id[0]), 0u);
    /* a revoked id is no longer writable */
    pos_at(fx.in[0], fx.in_e[0][0])->x = 1;
    ASSERT_EQ(merge_peer(&fx, 0u, &rep), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).x, 0);
    ASSERT_EQ(break_world_merge_revoke_connection(fx.merge, kB), 2u);
    ASSERT_EQ(break_world_merge_owner(fx.merge, fx.id[2]), 0u);
    ASSERT_EQ(break_world_merge_owner(fx.merge, fx.id[1]), (u64)kA);
    ASSERT_EQ(break_world_merge_revoke_connection(fx.merge, kB), 0u);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kB, fx.id[0]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, 0u, fx.id[2]), BREAK_WORLD_MERGE_INVALID);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, 0u), BREAK_WORLD_MERGE_INVALID);
    ASSERT_EQ(break_world_merge_grant(NULL, kA, fx.id[2]), BREAK_WORLD_MERGE_INVALID);
    ASSERT_EQ(break_world_merge_revoke(NULL, fx.id[2]), BREAK_WORLD_MERGE_INVALID);
    ASSERT_EQ(break_world_merge_revoke_connection(NULL, kA), 0u);
    ASSERT_EQ(break_world_merge_owner(NULL, fx.id[1]), 0u);
    fx_dispose(&fx);
}

TEST(an_owned_id_unknown_on_either_side_is_skipped) {
    Fx fx;
    BreakWorldMergeReport rep;
    ASSERT_TRUE(fx_init(&fx));
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, 5555u), BREAK_WORLD_MERGE_OK); /* nowhere */
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[0]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_net_entity_map_release(fx.in_ids[0], fx.id[0]), BREAK_NET_ENTITY_OK);
    pos_at(fx.in[0], fx.in_e[0][0])->x = 3;
    ASSERT_EQ(merge_peer(&fx, 0u, &rep), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).x, 0);
    ASSERT_EQ(rep.entities, 0u);
    ASSERT_EQ(rep.skipped, 2u);
    /* bound in the inbound map but not in the authoritative one */
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[1]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_net_entity_map_release(fx.auth_ids, fx.id[1]), BREAK_NET_ENTITY_OK);
    pos_at(fx.in[0], fx.in_e[0][1])->x = 13;
    ASSERT_EQ(merge_peer(&fx, 0u, &rep), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[1]).x, 10);
    ASSERT_EQ(rep.skipped, 3u);
    /* an id bound under another world_key in the inbound map is not this World */
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[2]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_net_entity_map_rebind(fx.in_ids[0], fx.id[2], 77u, fx.in_e[0][2]),
              BREAK_NET_ENTITY_OK);
    pos_at(fx.in[0], fx.in_e[0][2])->x = 23;
    ASSERT_EQ(merge_peer(&fx, 0u, &rep), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[2]).x, 20);
    ASSERT_EQ(rep.skipped, 4u);
    fx_dispose(&fx);
}

TEST(create_and_merge_validate_their_arguments) {
    Fx fx;
    BreakWorldMergeComponent comps[2];
    BreakWorldMergeConfig cfg;
    BreakWorldMerge *m = (BreakWorldMerge *)&fx;
    BreakWorldMergeReport rep;
    BreakWorldMergeStats st;
    ASSERT_TRUE(fx_init(&fx));
    ASSERT_EQ(break_world_merge_create(NULL, &m), BREAK_WORLD_MERGE_INVALID);
    cfg = base_config(&fx, comps);
    ASSERT_EQ(break_world_merge_create(&cfg, NULL), BREAK_WORLD_MERGE_INVALID);
    cfg.authoritative = NULL;
    ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_INVALID);
    ASSERT_TRUE(m == NULL);
    cfg = base_config(&fx, comps);
    cfg.ids = NULL;
    ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_INVALID);
    cfg = base_config(&fx, comps);
    cfg.components = NULL;
    ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_INVALID);
    cfg = base_config(&fx, comps);
    cfg.component_count = 0u;
    ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_INVALID);
    cfg.component_count = BREAK_WORLD_MERGE_MAX_COMPONENTS + 1u;
    ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_INVALID);
    {
        /* exactly the maximum component count and owned capacity are accepted */
        World *wide = world_create();
        BreakWorldMergeComponent many[BREAK_WORLD_MERGE_MAX_COMPONENTS];
        memset(many, 0, sizeof many);
        for (u32 i = 0u; i < BREAK_WORLD_MERGE_MAX_COMPONENTS; ++i) {
            world_register_component(wide, 20u + i, 4u);
            many[i].component = 20u + i;
            many[i].validate = validate_health;
        }
        cfg = base_config(&fx, comps);
        cfg.authoritative = wide;
        cfg.components = many;
        cfg.component_count = BREAK_WORLD_MERGE_MAX_COMPONENTS;
        cfg.max_owned = BREAK_WORLD_MERGE_MAX_OWNED;
        ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_OK);
        ASSERT_NOT_NULL(m);
        break_world_merge_destroy(m);
        m = NULL;
        world_destroy(wide);
    }
    cfg = base_config(&fx, comps);
    cfg.max_owned = 0u;
    ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_INVALID);
    cfg.max_owned = BREAK_WORLD_MERGE_MAX_OWNED + 1u;
    ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_INVALID);
    cfg = base_config(&fx, comps);
    comps[1].validate = NULL;
    ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_INVALID);
    cfg = base_config(&fx, comps);
    comps[1].component = kPos; /* listed twice */
    ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_INVALID);
    cfg = base_config(&fx, comps);
    comps[1].component = 60u; /* not registered in the authoritative World */
    ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_INVALID);
    cfg = base_config(&fx, comps);
    comps[1].component = ECS_MAX_COMPONENTS;
    ASSERT_EQ(break_world_merge_create(&cfg, &m), BREAK_WORLD_MERGE_INVALID);
    ASSERT_TRUE(m == NULL);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[0]), BREAK_WORLD_MERGE_OK);
    memset(&rep, 0xab, sizeof rep);
    ASSERT_EQ(break_world_merge_connection(NULL, kA, fx.in[0], fx.in_ids[0], kInbound, &rep),
              BREAK_WORLD_MERGE_INVALID);
    ASSERT_EQ(rep.written, 0u);
    ASSERT_EQ(break_world_merge_connection(fx.merge, kA, NULL, fx.in_ids[0], kInbound, &rep),
              BREAK_WORLD_MERGE_INVALID);
    ASSERT_EQ(break_world_merge_connection(fx.merge, kA, fx.in[0], NULL, kInbound, &rep),
              BREAK_WORLD_MERGE_INVALID);
    ASSERT_EQ(break_world_merge_connection(fx.merge, 0u, fx.in[0], fx.in_ids[0], kInbound, &rep),
              BREAK_WORLD_MERGE_INVALID);
    ASSERT_EQ(break_world_merge_connection(fx.merge, kA, fx.auth, fx.in_ids[0], kInbound, &rep),
              BREAK_WORLD_MERGE_INVALID); /* merging the authority into itself */
    ASSERT_EQ(break_world_merge_connection(fx.merge, kA, fx.in[0], fx.in_ids[0], kInbound, NULL),
              BREAK_WORLD_MERGE_OK);
    break_world_merge_stats(fx.merge, &st);
    ASSERT_EQ(st.merges, 1u);
    break_world_merge_stats(NULL, &st);
    break_world_merge_stats(fx.merge, NULL);
    break_world_merge_destroy(NULL);
    fx_dispose(&fx);
}

/* An inbound World whose component has a different registered size than the
 * authoritative one is refused before any validator runs. */
TEST(a_component_size_mismatch_rejects_the_batch) {
    Fx fx;
    World *odd = world_create();
    BreakNetEntityMap *odd_ids = NULL;
    BreakNetEntityMapConfig mc = {8u, 100u};
    BreakWorldMergeReport rep;
    Entity e;
    ASSERT_TRUE(fx_init(&fx));
    world_register_component(odd, kPos, 4u);
    world_register_component(odd, kHealth, (u32)sizeof(u32));
    e = world_create_entity(odd);
    ASSERT_NOT_NULL(world_add_component(odd, e, kPos));
    ASSERT_TRUE(break_net_entity_map_create(&mc, &odd_ids));
    ASSERT_EQ(break_net_entity_map_adopt(odd_ids, fx.id[0], kInbound, e), BREAK_NET_ENTITY_OK);
    ASSERT_EQ(break_world_merge_grant(fx.merge, kA, fx.id[0]), BREAK_WORLD_MERGE_OK);
    ASSERT_EQ(break_world_merge_connection(fx.merge, kA, odd, odd_ids, kInbound, &rep),
              BREAK_WORLD_MERGE_REJECTED);
    ASSERT_EQ(fx.rules.calls, 0u);
    ASSERT_EQ(pos_of(fx.auth, fx.auth_e[0]).x, 0);
    {
        BreakWorldMergeStats st;
        break_world_merge_stats(fx.merge, &st);
        ASSERT_EQ(st.rejected, 1u);
    }
    break_net_entity_map_destroy(odd_ids);
    world_destroy(odd);
    fx_dispose(&fx);
}

TEST_MAIN_BEGIN()
    RUN_TEST(an_owned_entity_takes_the_validated_value);
    RUN_TEST(entities_the_connection_does_not_own_are_ignored);
    RUN_TEST(every_accepted_value_of_a_batch_lands_where_it_belongs);
    RUN_TEST(only_writable_components_are_merged);
    RUN_TEST(a_rejected_value_applies_nothing_of_the_batch);
    RUN_TEST(structure_is_never_changed_by_a_peer);
    RUN_TEST(ownership_grant_conflict_revoke_and_capacity);
    RUN_TEST(an_owned_id_unknown_on_either_side_is_skipped);
    RUN_TEST(create_and_merge_validate_their_arguments);
    RUN_TEST(a_component_size_mismatch_rejects_the_batch);
TEST_MAIN_END()
