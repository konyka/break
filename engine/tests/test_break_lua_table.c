#include "test_framework.h"
#include <script/break_lua_table.h>
#include <script/break_lua_test_hooks.h>

#include <lua/lua.h>

#include <string.h>

static const char kEcho[] =
    "function echo(value)\n"
    "    return value\n"
    "end\n";

static const char kBadReturns[] =
    "function deep()\n"
    "    local root = {}\n"
    "    local cursor = root\n"
    "    for i = 1, 20 do cursor.child = {}; cursor = cursor.child end\n"
    "    return root\n"
    "end\n"
    "function wide()\n"
    "    local value = {}\n"
    "    for i = 1, 20 do value[i] = i end\n"
    "    return value\n"
    "end\n"
    "function long_string()\n"
    "    return {v = '12345678'}\n"
    "end\n"
    "function cycle()\n"
    "    local value = {}\n"
    "    value.self = value\n"
    "    return value\n"
    "end\n"
    "function unsupported()\n"
    "    return {callback = function() end}\n"
    "end\n";

static BreakLuaTableValue table_value(void)
{
    BreakLuaTableValue value;
    memset(&value, 0, sizeof(value));
    value.type = BREAK_LUA_TABLE_TABLE;
    return value;
}

static BreakLuaTableValue number_value(double number)
{
    BreakLuaTableValue value;
    memset(&value, 0, sizeof(value));
    value.type = BREAK_LUA_TABLE_NUMBER;
    value.as.n = number;
    return value;
}

static BreakLuaTableValue bool_value(bool boolean)
{
    BreakLuaTableValue value;
    memset(&value, 0, sizeof(value));
    value.type = BREAK_LUA_TABLE_BOOL;
    value.as.b = boolean;
    return value;
}

static BreakLuaTableValue string_value(const char *string, u32 len)
{
    BreakLuaTableValue value;
    memset(&value, 0, sizeof(value));
    value.type = BREAK_LUA_TABLE_STRING;
    value.as.s.data = string;
    value.as.s.len = len;
    return value;
}

static BreakLuaTableValue handle_value(BreakLuaHostHandle handle)
{
    BreakLuaTableValue value;
    memset(&value, 0, sizeof(value));
    value.type = BREAK_LUA_TABLE_HOST_HANDLE;
    value.as.handle = handle;
    return value;
}

static u32 named_child(const BreakLuaTable *table, u32 parent, const char *name)
{
    BreakLuaTableNodeInfo info;
    u32 id;
    if (break_lua_table_node(table, parent, &info) != BREAK_LUA_OK) {
        return UINT32_MAX;
    }
    id = info.first_child;
    while (id != UINT32_MAX) {
        if (break_lua_table_node(table, id, &info) != BREAK_LUA_OK) {
            return UINT32_MAX;
        }
        if (!info.key_is_integer && info.key_len == strlen(name) &&
            memcmp(info.key, name, info.key_len) == 0) {
            return id;
        }
        id = info.next_sibling;
    }
    return UINT32_MAX;
}

TEST(table_create_validates_hard_limits)
{
    ASSERT_TRUE(break_lua_table_create(0u, 1u, 1u) == NULL);
    ASSERT_TRUE(break_lua_table_create(BREAK_LUA_TABLE_MAX_NODES + 1u, 1u, 1u) == NULL);
    ASSERT_TRUE(break_lua_table_create(4u, 0u, 1u) == NULL);
    ASSERT_TRUE(break_lua_table_create(4u, BREAK_LUA_TABLE_MAX_DEPTH + 1u, 1u) == NULL);
    ASSERT_TRUE(break_lua_table_create(4u, 1u, 0u) == NULL);
    ASSERT_TRUE(break_lua_table_create(4u, 1u, BREAK_LUA_TABLE_MAX_STRING + 1u) == NULL);
    break_lua_table_destroy(NULL);
}

TEST(table_builder_enforces_depth_node_and_string_bounds_atomically)
{
    BreakLuaTable *table = break_lua_table_create(4u, 1u, 3u);
    BreakLuaTableValue table_kind = table_value();
    BreakLuaTableValue number = number_value(7.0);
    BreakLuaTableValue string = string_value("xyz", 3u);
    BreakLuaTableValue too_long = string_value("abcd", 4u);
    u32 root;
    u32 child = 0u;
    u32 node = 0u;
    u32 before;
    ASSERT_NOT_NULL(table);
    root = break_lua_table_root(table);
    ASSERT_EQ(root, 0u);
    ASSERT_EQ(break_lua_table_count(table), 1u);
    ASSERT_EQ(break_lua_table_add(table, root, "c", 1u, &table_kind, &child),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_table_add(table, child, "d", 1u, &table_kind, &node),
              BREAK_LUA_OVERLOAD);
    ASSERT_EQ(break_lua_table_count(table), 2u);

    ASSERT_EQ(break_lua_table_add(table, child, "abc", 3u, &string, &node),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_table_add_index(table, root, 9, &number, &node),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_table_count(table), 4u);
    before = break_lua_table_count(table);
    ASSERT_EQ(break_lua_table_add_index(table, root, 10, &number, &node),
              BREAK_LUA_OVERLOAD);
    ASSERT_EQ(break_lua_table_count(table), before);
    ASSERT_EQ(break_lua_table_add(table, root, "abcd", 4u, &number, &node),
              BREAK_LUA_OVERLOAD);
    ASSERT_EQ(break_lua_table_add(table, root, "ok", 2u, &too_long, &node),
              BREAK_LUA_OVERLOAD);
    ASSERT_EQ(break_lua_table_count(table), before);
    break_lua_table_destroy(table);
}

TEST(table_call_round_trips_nested_values_keys_and_host_handle)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaTable *input = break_lua_table_create(16u, 2u, 16u);
    BreakLuaTable *output = break_lua_table_create(16u, 2u, 16u);
    BreakLuaHostHandle handle = {0u, 0u};
    BreakLuaTableValue value;
    BreakLuaTableNodeInfo info;
    u32 root;
    u32 child = 0u;
    u32 node = 0u;
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(input);
    ASSERT_NOT_NULL(output);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "tables", kEcho, strlen(kEcho)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_host_handle_acquire(rt, 0xabcdefu, &handle),
              BREAK_LUA_OK);
    root = break_lua_table_root(input);
    value = number_value(12.5);
    ASSERT_EQ(break_lua_table_add(input, root, "number", 6u, &value, &node),
              BREAK_LUA_OK);
    value = string_value("hello", 5u);
    ASSERT_EQ(break_lua_table_add(input, root, "text", 4u, &value, &node),
              BREAK_LUA_OK);
    value = bool_value(true);
    ASSERT_EQ(break_lua_table_add(input, root, "flag", 4u, &value, &node),
              BREAK_LUA_OK);
    value = handle_value(handle);
    ASSERT_EQ(break_lua_table_add(input, root, "actor", 5u, &value, &node),
              BREAK_LUA_OK);
    value = table_value();
    ASSERT_EQ(break_lua_table_add(input, root, "nested", 6u, &value, &child),
              BREAK_LUA_OK);
    value = number_value(99.0);
    ASSERT_EQ(break_lua_table_add_index(input, child, -4, &value, &node),
              BREAK_LUA_OK);

    ASSERT_EQ(break_lua_runtime_call_table(rt, "tables", "echo", input, output),
              BREAK_LUA_OK);
    root = break_lua_table_root(output);
    node = named_child(output, root, "number");
    ASSERT_TRUE(node != UINT32_MAX);
    ASSERT_EQ(break_lua_table_node(output, node, &info), BREAK_LUA_OK);
    ASSERT_EQ(info.value.type, BREAK_LUA_TABLE_NUMBER);
    ASSERT_FLOAT_EQ(info.value.as.n, 12.5, 1e-12);
    node = named_child(output, root, "text");
    ASSERT_EQ(break_lua_table_node(output, node, &info), BREAK_LUA_OK);
    ASSERT_EQ(info.value.type, BREAK_LUA_TABLE_STRING);
    ASSERT_EQ(info.value.as.s.len, 5u);
    ASSERT_TRUE(memcmp(info.value.as.s.data, "hello", 5u) == 0);
    node = named_child(output, root, "flag");
    ASSERT_EQ(break_lua_table_node(output, node, &info), BREAK_LUA_OK);
    ASSERT_TRUE(info.value.as.b);
    node = named_child(output, root, "actor");
    ASSERT_EQ(break_lua_table_node(output, node, &info), BREAK_LUA_OK);
    ASSERT_EQ(info.value.type, BREAK_LUA_TABLE_HOST_HANDLE);
    ASSERT_EQ(info.value.as.handle.slot, handle.slot);
    ASSERT_EQ(info.value.as.handle.generation, handle.generation);
    child = named_child(output, root, "nested");
    ASSERT_TRUE(child != UINT32_MAX);
    ASSERT_EQ(break_lua_table_node(output, child, &info), BREAK_LUA_OK);
    node = info.first_child;
    ASSERT_EQ(break_lua_table_node(output, node, &info), BREAK_LUA_OK);
    ASSERT_TRUE(info.key_is_integer);
    ASSERT_EQ(info.integer_key, -4);
    ASSERT_FLOAT_EQ(info.value.as.n, 99.0, 1e-12);
    ASSERT_EQ(lua_gettop((lua_State *)break_lua_test_lua_state(rt)), 0);

    ASSERT_EQ(break_lua_host_handle_release(rt, handle), BREAK_LUA_OK);
    break_lua_table_destroy(output);
    break_lua_table_destroy(input);
    break_lua_runtime_destroy(rt);
}

TEST(table_output_limits_and_cycles_preserve_previous_output)
{
    static const char *const functions[] = {
        "deep", "wide", "long_string", "cycle"
    };
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaTable *input = break_lua_table_create(2u, 2u, 3u);
    BreakLuaTable *output = break_lua_table_create(4u, 2u, 3u);
    BreakLuaTableValue marker = number_value(99.0);
    BreakLuaTableNodeInfo info;
    u32 node = 0u;
    u32 marker_id;
    usize i;
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(input);
    ASSERT_NOT_NULL(output);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "bad", kBadReturns,
                                            strlen(kBadReturns)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_table_add(output, break_lua_table_root(output),
                                  "m", 1u, &marker, &node),
              BREAK_LUA_OK);
    marker_id = node;
    for (i = 0u; i < sizeof(functions) / sizeof(functions[0]); i++) {
        ASSERT_EQ(break_lua_runtime_call_table(rt, "bad", functions[i],
                                               input, output),
                  BREAK_LUA_OVERLOAD);
        ASSERT_EQ(break_lua_table_count(output), 2u);
        ASSERT_EQ(break_lua_table_node(output, marker_id, &info), BREAK_LUA_OK);
        ASSERT_FLOAT_EQ(info.value.as.n, 99.0, 1e-12);
        ASSERT_EQ(lua_gettop((lua_State *)break_lua_test_lua_state(rt)), 0);
    }
    ASSERT_EQ(break_lua_runtime_call_table(rt, "bad", "unsupported",
                                           input, output),
              BREAK_LUA_FAILED);
    ASSERT_EQ(break_lua_table_count(output), 2u);
    ASSERT_EQ(lua_gettop((lua_State *)break_lua_test_lua_state(rt)), 0);
    break_lua_table_destroy(output);
    break_lua_table_destroy(input);
    break_lua_runtime_destroy(rt);
}

TEST_MAIN_BEGIN()
    RUN_TEST(table_create_validates_hard_limits);
    RUN_TEST(table_builder_enforces_depth_node_and_string_bounds_atomically);
    RUN_TEST(table_call_round_trips_nested_values_keys_and_host_handle);
    RUN_TEST(table_output_limits_and_cycles_preserve_previous_output);
TEST_MAIN_END()
