#pragma once

#include <script/break_lua.h>

#define BREAK_LUA_TABLE_MAX_NODES 256u
#define BREAK_LUA_TABLE_MAX_DEPTH 16u
#define BREAK_LUA_TABLE_MAX_STRING 127u
#define BREAK_LUA_TABLE_NONE UINT32_MAX

typedef struct BreakLuaTable BreakLuaTable;

typedef enum BreakLuaTableValueType {
    BREAK_LUA_TABLE_NIL = 0,
    BREAK_LUA_TABLE_BOOL,
    BREAK_LUA_TABLE_NUMBER,
    BREAK_LUA_TABLE_STRING,
    BREAK_LUA_TABLE_TABLE,
    BREAK_LUA_TABLE_HOST_HANDLE
} BreakLuaTableValueType;

typedef struct BreakLuaTableValue {
    BreakLuaTableValueType type;
    union {
        bool b;
        f64 n;
        struct {
            const char *data;
            u32 len;
        } s;
        BreakLuaHostHandle handle;
    } as;
} BreakLuaTableValue;

typedef struct BreakLuaTableNodeInfo {
    bool key_is_integer;
    i64 integer_key;
    const char *key;
    u32 key_len;
    u32 first_child;
    u32 next_sibling;
    u32 depth;
    BreakLuaTableValue value;
} BreakLuaTableNodeInfo;

BreakLuaTable *break_lua_table_create(u32 node_capacity, u32 max_depth,
                                      u32 max_string_bytes);
void break_lua_table_destroy(BreakLuaTable *table);
void break_lua_table_clear(BreakLuaTable *table);
u32 break_lua_table_root(const BreakLuaTable *table);
u32 break_lua_table_count(const BreakLuaTable *table);

BreakLuaError break_lua_table_add(BreakLuaTable *table, u32 parent,
                                  const char *key, usize key_len,
                                  const BreakLuaTableValue *value,
                                  u32 *out_node);
BreakLuaError break_lua_table_add_index(BreakLuaTable *table, u32 parent,
                                        i64 key,
                                        const BreakLuaTableValue *value,
                                        u32 *out_node);
BreakLuaError break_lua_table_node(const BreakLuaTable *table, u32 node,
                                   BreakLuaTableNodeInfo *out);

BreakLuaError break_lua_runtime_call_table(BreakLuaRuntime *runtime,
                                            const char *module_name,
                                            const char *function_name,
                                            const BreakLuaTable *argument,
                                            BreakLuaTable *result);
