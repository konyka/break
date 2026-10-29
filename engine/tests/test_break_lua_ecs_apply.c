#define _POSIX_C_SOURCE 200809L /* strdup */
/* Applying break_lua ECS batch records to a runtime ECS World: an end-to-end
 * case through a real Lua module, plus the rejection rules. */
#include "test_framework.h"

#include <ecs/ecs.h>
#include <script/break_lua.h>
#include <script/break_lua_ecs_apply.h>

#include <locale.h>
#include <math.h>
#include <string.h>

typedef struct TestPos { f32 x, y, z; } TestPos;
typedef struct TestTiny { u8 flag; } TestTiny;

enum { COMP_POS = 1, COMP_TINY = 2 };

static const BreakLuaEcsField k_schema[] = {
    { "transform", "x", COMP_POS, 0u },
    { "transform", "y", COMP_POS, 4u },
    { "transform", "z", COMP_POS, 8u },
    { "tiny", "v", COMP_TINY, 0u }, /* f32 does not fit in a 1-byte component */
    { "ghost", "x", 9u, 0u },       /* never registered in the World */
};
#define SCHEMA_N (sizeof(k_schema) / sizeof(k_schema[0]))

static BreakLuaEcsRecord spawn_rec(void)
{
    BreakLuaEcsRecord r;
    memset(&r, 0, sizeof(r));
    r.kind = BREAK_LUA_ECS_RECORD_SPAWN;
    return r;
}

static BreakLuaEcsRecord set_num(const char *c, const char *f, f64 v)
{
    BreakLuaEcsRecord r;
    memset(&r, 0, sizeof(r));
    r.kind = BREAK_LUA_ECS_RECORD_SET;
    r.value_type = BREAK_LUA_ECS_VALUE_NUMBER;
    strcpy(r.component, c);
    strcpy(r.field, f);
    r.value.n = v;
    return r;
}

static World *make_world(void)
{
    World *w = world_create();
    if (w != NULL) {
        world_register_component(w, COMP_POS, sizeof(TestPos));
        world_register_component(w, COMP_TINY, sizeof(TestTiny));
    }
    return w;
}

TEST(lua_script_spawns_and_sets_into_world)
{
    static const char chunk[] =
        "function build()\n"
        "  brk.ecs.spawn()\n"
        "  brk.ecs.set('transform', 'x', 1.5)\n"
        "  brk.ecs.set('transform', 'y', true)\n"
        "  brk.ecs.set('transform', 'z', '-2.25')\n"
        "  brk.ecs.spawn()\n"
        "  brk.ecs.set('transform', 'x', 7)\n"
        "end\n";
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaEcsBatch *batch = break_lua_ecs_batch_create(0u);
    World *w = make_world();
    BreakLuaEcsRecord recs[16];
    BreakLuaEcsApplyReport rep;
    usize n;
    TestPos *p;
    Entity first;
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(batch);
    ASSERT_NOT_NULL(w);
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, batch), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "m", chunk, sizeof(chunk) - 1u),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "m", "build", NULL, 0u, NULL, 0u),
              BREAK_LUA_OK);
    n = break_lua_ecs_batch_drain(batch, recs, 16u);
    ASSERT_EQ(n, 6u);

    ASSERT_TRUE(break_lua_ecs_apply(w, k_schema, SCHEMA_N, recs, 4u, &rep));
    ASSERT_EQ(rep.spawned, 1u);
    ASSERT_EQ(rep.set, 3u);
    ASSERT_EQ(rep.rejected, 0u);
    first = rep.last_spawned;
    ASSERT_TRUE(entity_valid(first));
    p = (TestPos *)world_get_component(w, first, COMP_POS);
    ASSERT_NOT_NULL(p);
    ASSERT_FLOAT_EQ(p->x, 1.5f, 0.0f);
    ASSERT_FLOAT_EQ(p->y, 1.0f, 0.0f);
    ASSERT_FLOAT_EQ(p->z, -2.25f, 0.0f);

    ASSERT_TRUE(break_lua_ecs_apply(w, k_schema, SCHEMA_N, recs + 4, 2u, &rep));
    ASSERT_EQ(rep.spawned, 1u);
    ASSERT_EQ(rep.set, 1u);
    ASSERT_TRUE(rep.last_spawned.index != first.index);
    p = (TestPos *)world_get_component(w, rep.last_spawned, COMP_POS);
    ASSERT_NOT_NULL(p);
    ASSERT_FLOAT_EQ(p->x, 7.0f, 0.0f);
    ASSERT_FLOAT_EQ(p->y, 0.0f, 0.0f); /* added zero-initialized */
    /* the first entity is untouched by the second call */
    p = (TestPos *)world_get_component(w, first, COMP_POS);
    ASSERT_FLOAT_EQ(p->x, 1.5f, 0.0f);
    break_lua_runtime_destroy(rt);
    break_lua_ecs_batch_destroy(batch);
    world_destroy(w);
}

TEST(invalid_records_are_rejected_without_writes)
{
    World *w = make_world();
    BreakLuaEcsRecord recs[10];
    BreakLuaEcsApplyReport rep;
    TestPos *p;
    ASSERT_NOT_NULL(w);
    recs[0] = set_num("transform", "x", 1.0);      /* no target yet */
    recs[1] = spawn_rec();
    recs[2] = set_num("transform", "w", 1.0);      /* unknown field */
    recs[3] = set_num("light", "x", 1.0);          /* unknown component */
    recs[4] = set_num("tiny", "v", 1.0);           /* does not fit */
    recs[5] = set_num("ghost", "x", 1.0);          /* not registered */
    recs[6] = set_num("transform", "x", NAN);      /* non-finite */
    recs[7] = set_num("transform", "x", 1e300);    /* overflows f32 */
    recs[8] = set_num("transform", "y", 0.0);
    recs[8].value_type = BREAK_LUA_ECS_VALUE_STRING;
    strcpy(recs[8].value.s.data, "12abc");         /* not a full number */
    recs[8].value.s.len = 5u;
    recs[9] = set_num("transform", "x", 3.0);      /* the one valid write */
    recs[9].kind = 99u;                             /* ...but unknown kind */

    ASSERT_TRUE(break_lua_ecs_apply(w, k_schema, SCHEMA_N, recs, 10u, &rep));
    ASSERT_EQ(rep.spawned, 1u);
    ASSERT_EQ(rep.set, 0u);
    ASSERT_EQ(rep.rejected, 9u);
    /* nothing was added to the spawned entity */
    p = (TestPos *)world_get_component(w, rep.last_spawned, COMP_POS);
    ASSERT_TRUE(p == NULL);
    ASSERT_TRUE(world_get_component(w, rep.last_spawned, COMP_TINY) == NULL);

    ASSERT_FALSE(break_lua_ecs_apply(NULL, k_schema, SCHEMA_N, recs, 1u, &rep));
    ASSERT_FALSE(break_lua_ecs_apply(w, k_schema, SCHEMA_N, NULL, 1u, &rep));
    ASSERT_FALSE(break_lua_ecs_apply(w, k_schema, SCHEMA_N, recs, 1u, NULL));
    ASSERT_TRUE(break_lua_ecs_apply(w, NULL, 0u, NULL, 0u, &rep));
    ASSERT_EQ(rep.spawned + rep.set + rep.rejected, 0u);
    world_destroy(w);
}

TEST(added_component_is_zeroed_even_on_reused_chunk_memory)
{
    World *w = make_world();
    BreakLuaEcsRecord recs[2];
    BreakLuaEcsApplyReport rep;
    TestPos *p;
    Entity junk;
    ASSERT_NOT_NULL(w);
    /* leave non-zero bytes in the TestPos column, then free the slot */
    junk = world_create_entity(w);
    p = (TestPos *)world_add_component(w, junk, COMP_POS);
    ASSERT_NOT_NULL(p);
    p->x = 11.0f; p->y = 22.0f; p->z = 33.0f;
    world_destroy_entity(w, junk);

    recs[0] = spawn_rec();
    recs[1] = set_num("transform", "x", 5.0);
    ASSERT_TRUE(break_lua_ecs_apply(w, k_schema, SCHEMA_N, recs, 2u, &rep));
    ASSERT_EQ(rep.set, 1u);
    p = (TestPos *)world_get_component(w, rep.last_spawned, COMP_POS);
    ASSERT_NOT_NULL(p);
    ASSERT_FLOAT_EQ(p->x, 5.0f, 0.0f);
    ASSERT_FLOAT_EQ(p->y, 0.0f, 0.0f);
    ASSERT_FLOAT_EQ(p->z, 0.0f, 0.0f);
    world_destroy(w);
}

static BreakLuaEcsRecord set_str(const char *c, const char *f, const char *v)
{
    BreakLuaEcsRecord r;
    memset(&r, 0, sizeof(r));
    r.kind = BREAK_LUA_ECS_RECORD_SET;
    r.value_type = BREAK_LUA_ECS_VALUE_STRING;
    strcpy(r.component, c);
    strcpy(r.field, f);
    r.value.s.len = (u32)strlen(v);
    memcpy(r.value.s.data, v, r.value.s.len + 1u);
    return r;
}

/* String values parse with '.' as the only decimal separator whatever the
 * process locale is; a comma is never a separator. */
TEST(string_values_parse_independently_of_the_locale)
{
    World *w = make_world();
    BreakLuaEcsRecord recs[4];
    BreakLuaEcsApplyReport rep;
    char *saved = NULL;
    const char *prev = setlocale(LC_NUMERIC, NULL);
    TestPos *p;
    bool have_comma_locale;
    ASSERT_NOT_NULL(w);
    if (prev != NULL) {
        saved = strdup(prev);
    }
    have_comma_locale = setlocale(LC_NUMERIC, "de_DE.UTF-8") != NULL ||
                        setlocale(LC_NUMERIC, "de_DE.utf8") != NULL ||
                        setlocale(LC_NUMERIC, "fr_FR.UTF-8") != NULL;
    if (!have_comma_locale) {
        printf("    (no comma-decimal locale installed; C locale only)\n");
    }
    recs[0] = spawn_rec();
    recs[1] = set_str("transform", "x", "-2.25");
    recs[2] = set_str("transform", "y", "1,5");
    recs[3] = set_str("transform", "z", "3e2");
    ASSERT_TRUE(break_lua_ecs_apply(w, k_schema, SCHEMA_N, recs, 4u, &rep));
    if (saved != NULL) {
        (void)setlocale(LC_NUMERIC, saved);
        free(saved);
    }
    ASSERT_EQ(rep.set, (usize)2);
    ASSERT_EQ(rep.rejected, (usize)1);
    p = (TestPos *)world_get_component(w, rep.last_spawned, COMP_POS);
    ASSERT_NOT_NULL(p);
    ASSERT_TRUE(p->x == -2.25f);
    ASSERT_TRUE(p->y == 0.0f);
    ASSERT_TRUE(p->z == 300.0f);
    world_destroy(w);
}

TEST_MAIN_BEGIN()
    RUN_TEST(lua_script_spawns_and_sets_into_world);
    RUN_TEST(invalid_records_are_rejected_without_writes);
    RUN_TEST(added_component_is_zeroed_even_on_reused_chunk_memory);
    RUN_TEST(string_values_parse_independently_of_the_locale);
TEST_MAIN_END()
