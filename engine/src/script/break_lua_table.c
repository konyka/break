#include <script/break_lua_table.h>

#include <script/break_lua_internal.h>

#include <lua/lauxlib.h>

#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct BreakLuaTableNode {
    bool key_is_integer;
    i64 integer_key;
    char key[BREAK_LUA_TABLE_MAX_STRING + 1u];
    u32 key_len;
    char string[BREAK_LUA_TABLE_MAX_STRING + 1u];
    u32 string_len;
    u32 first_child;
    u32 next_sibling;
    u32 depth;
    BreakLuaTableValueType type;
    union {
        bool b;
        f64 n;
        BreakLuaHostHandle handle;
    } as;
} BreakLuaTableNode;

struct BreakLuaTable {
    BreakLuaTableNode *nodes;
    BreakLuaTableNode *scratch;
    u32 node_capacity;
    u32 max_depth;
    u32 max_string_bytes;
    u32 count;
};

static void break_lua_table_init_root(BreakLuaTableNode *nodes)
{
    memset(nodes, 0, sizeof(*nodes));
    nodes[0].type = BREAK_LUA_TABLE_TABLE;
    nodes[0].first_child = BREAK_LUA_TABLE_NONE;
    nodes[0].next_sibling = BREAK_LUA_TABLE_NONE;
}

BreakLuaTable *break_lua_table_create(u32 node_capacity, u32 max_depth,
                                      u32 max_string_bytes)
{
    BreakLuaTable *table;
    if (node_capacity == 0u || node_capacity > BREAK_LUA_TABLE_MAX_NODES ||
        max_depth == 0u || max_depth > BREAK_LUA_TABLE_MAX_DEPTH ||
        max_string_bytes == 0u || max_string_bytes > BREAK_LUA_TABLE_MAX_STRING) {
        return NULL;
    }
    table = (BreakLuaTable *)calloc(1u, sizeof(*table));
    if (!table) {
        return NULL;
    }
    table->nodes = (BreakLuaTableNode *)calloc(
        node_capacity, sizeof(*table->nodes));
    table->scratch = (BreakLuaTableNode *)calloc(
        node_capacity, sizeof(*table->scratch));
    if (!table->nodes || !table->scratch) {
        free(table->scratch);
        free(table->nodes);
        free(table);
        return NULL;
    }
    table->node_capacity = node_capacity;
    table->max_depth = max_depth;
    table->max_string_bytes = max_string_bytes;
    table->count = 1u;
    break_lua_table_init_root(table->nodes);
    break_lua_table_init_root(table->scratch);
    return table;
}

void break_lua_table_destroy(BreakLuaTable *table)
{
    if (table) {
        free(table->scratch);
        free(table->nodes);
        free(table);
    }
}

void break_lua_table_clear(BreakLuaTable *table)
{
    if (table) {
        break_lua_table_init_root(table->nodes);
        table->count = 1u;
    }
}

u32 break_lua_table_root(const BreakLuaTable *table)
{
    (void)table;
    return 0u;
}

u32 break_lua_table_count(const BreakLuaTable *table)
{
    return table ? table->count : 0u;
}

static BreakLuaError break_lua_table_add_node(BreakLuaTable *table, u32 parent,
    bool key_is_integer, i64 integer_key, const char *key, usize key_len,
    const BreakLuaTableValue *value, u32 *out_node)
{
    BreakLuaTableNode *parent_node;
    BreakLuaTableNode *node;
    u32 index;
    u32 depth;
    if (!table || !value || (!key_is_integer && !key && key_len != 0u)) {
        return BREAK_LUA_INVALID;
    }
    if (parent >= table->count) {
        return BREAK_LUA_STALE;
    }
    parent_node = &table->nodes[parent];
    if (parent_node->type != BREAK_LUA_TABLE_TABLE) {
        return BREAK_LUA_INVALID;
    }
    if ((!key_is_integer && key_len > table->max_string_bytes) ||
        (value->type == BREAK_LUA_TABLE_STRING &&
         value->as.s.len > table->max_string_bytes)) {
        return BREAK_LUA_OVERLOAD;
    }
    if (value->type == BREAK_LUA_TABLE_STRING && value->as.s.len != 0u &&
        !value->as.s.data) {
        return BREAK_LUA_INVALID;
    }
    if (value->type < BREAK_LUA_TABLE_NIL ||
        value->type > BREAK_LUA_TABLE_HOST_HANDLE) {
        return BREAK_LUA_INVALID;
    }
    if (table->count >= table->node_capacity) {
        return BREAK_LUA_OVERLOAD;
    }
    depth = parent_node->depth +
            (value->type == BREAK_LUA_TABLE_TABLE ? 1u : 0u);
    if (depth > table->max_depth) {
        return BREAK_LUA_OVERLOAD;
    }

    index = table->count;
    node = &table->nodes[index];
    memset(node, 0, sizeof(*node));
    node->key_is_integer = key_is_integer;
    node->integer_key = integer_key;
    node->first_child = BREAK_LUA_TABLE_NONE;
    node->next_sibling = BREAK_LUA_TABLE_NONE;
    node->depth = depth;
    node->type = value->type;
    if (!key_is_integer) {
        if (key_len != 0u) {
            memcpy(node->key, key, key_len);
        }
        node->key[key_len] = '\0';
        node->key_len = (u32)key_len;
    }
    switch (value->type) {
    case BREAK_LUA_TABLE_BOOL:
        node->as.b = value->as.b;
        break;
    case BREAK_LUA_TABLE_NUMBER:
        node->as.n = value->as.n;
        break;
    case BREAK_LUA_TABLE_STRING:
        if (value->as.s.len != 0u) {
            memcpy(node->string, value->as.s.data, value->as.s.len);
        }
        node->string[value->as.s.len] = '\0';
        node->string_len = value->as.s.len;
        break;
    case BREAK_LUA_TABLE_HOST_HANDLE:
        node->as.handle = value->as.handle;
        break;
    default:
        break;
    }
    if (parent_node->first_child == BREAK_LUA_TABLE_NONE) {
        parent_node->first_child = index;
    } else {
        u32 sibling = parent_node->first_child;
        while (table->nodes[sibling].next_sibling != BREAK_LUA_TABLE_NONE) {
            sibling = table->nodes[sibling].next_sibling;
        }
        table->nodes[sibling].next_sibling = index;
    }
    table->count++;
    if (out_node) {
        *out_node = index;
    }
    return BREAK_LUA_OK;
}

BreakLuaError break_lua_table_add(BreakLuaTable *table, u32 parent,
                                  const char *key, usize key_len,
                                  const BreakLuaTableValue *value,
                                  u32 *out_node)
{
    return break_lua_table_add_node(table, parent, false, 0, key, key_len,
                                    value, out_node);
}

BreakLuaError break_lua_table_add_index(BreakLuaTable *table, u32 parent,
                                        i64 key,
                                        const BreakLuaTableValue *value,
                                        u32 *out_node)
{
    return break_lua_table_add_node(table, parent, true, key, NULL, 0u,
                                    value, out_node);
}

BreakLuaError break_lua_table_node(const BreakLuaTable *table, u32 node,
                                   BreakLuaTableNodeInfo *out)
{
    const BreakLuaTableNode *source;
    if (!table || !out) {
        return BREAK_LUA_INVALID;
    }
    if (node >= table->count) {
        return BREAK_LUA_STALE;
    }
    source = &table->nodes[node];
    memset(out, 0, sizeof(*out));
    out->key_is_integer = source->key_is_integer;
    out->integer_key = source->integer_key;
    out->key = source->key;
    out->key_len = source->key_len;
    out->first_child = source->first_child;
    out->next_sibling = source->next_sibling;
    out->depth = source->depth;
    out->value.type = source->type;
    switch (source->type) {
    case BREAK_LUA_TABLE_BOOL:
        out->value.as.b = source->as.b;
        break;
    case BREAK_LUA_TABLE_NUMBER:
        out->value.as.n = source->as.n;
        break;
    case BREAK_LUA_TABLE_STRING:
        out->value.as.s.data = source->string;
        out->value.as.s.len = source->string_len;
        break;
    case BREAK_LUA_TABLE_HOST_HANDLE:
        out->value.as.handle = source->as.handle;
        break;
    default:
        break;
    }
    return BREAK_LUA_OK;
}

static BreakLuaError break_lua_table_push_node(lua_State *L,
                                                const BreakLuaTable *table,
                                                u32 index)
{
    const BreakLuaTableNode *node = &table->nodes[index];
    u32 child;
    lua_newtable(L);
    child = node->first_child;
    while (child != BREAK_LUA_TABLE_NONE) {
        const BreakLuaTableNode *source = &table->nodes[child];
        BreakLuaError err = BREAK_LUA_OK;
        if (source->key_is_integer) {
            lua_pushinteger(L, (lua_Integer)source->integer_key);
        } else {
            lua_pushlstring(L, source->key, source->key_len);
        }
        switch (source->type) {
        case BREAK_LUA_TABLE_NIL:
            lua_pushnil(L);
            break;
        case BREAK_LUA_TABLE_BOOL:
            lua_pushboolean(L, source->as.b ? 1 : 0);
            break;
        case BREAK_LUA_TABLE_NUMBER:
            lua_pushnumber(L, (lua_Number)source->as.n);
            break;
        case BREAK_LUA_TABLE_STRING:
            lua_pushlstring(L, source->string, source->string_len);
            break;
        case BREAK_LUA_TABLE_TABLE:
            err = break_lua_table_push_node(L, table, child);
            break;
        case BREAK_LUA_TABLE_HOST_HANDLE: {
            BreakLuaValue value;
            memset(&value, 0, sizeof(value));
            value.type = BREAK_LUA_VALUE_HOST_HANDLE;
            value.as.handle = source->as.handle;
            err = break_lua_push_value(L, &value);
            break;
        }
        default:
            err = BREAK_LUA_INVALID;
            break;
        }
        if (err != BREAK_LUA_OK) {
            return err;
        }
        lua_rawset(L, -3);
        child = source->next_sibling;
    }
    return BREAK_LUA_OK;
}

static BreakLuaError break_lua_table_take_children(lua_State *L, int index,
                                                    BreakLuaTable *result,
                                                    u32 parent)
{
    BreakLuaError err = BREAK_LUA_OK;
    index = lua_absindex(L, index);
    lua_pushnil(L);
    while (lua_next(L, index) != 0) {
        const char *key = NULL;
        usize key_len = 0u;
        i64 integer_key = 0;
        bool key_is_integer = false;
        BreakLuaTableValue value;
        u32 child = 0u;
        memset(&value, 0, sizeof(value));
        if (lua_type(L, -2) == LUA_TSTRING) {
            size_t len = 0u;
            key = lua_tolstring(L, -2, &len);
            key_len = (usize)len;
        } else if (lua_type(L, -2) == LUA_TNUMBER && lua_isinteger(L, -2)) {
            key_is_integer = true;
            integer_key = (i64)lua_tointeger(L, -2);
        } else {
            lua_pop(L, 1);
            return BREAK_LUA_FAILED;
        }
        switch (lua_type(L, -1)) {
        case LUA_TNIL:
            value.type = BREAK_LUA_TABLE_NIL;
            break;
        case LUA_TBOOLEAN:
            value.type = BREAK_LUA_TABLE_BOOL;
            value.as.b = lua_toboolean(L, -1) != 0;
            break;
        case LUA_TNUMBER:
            value.type = BREAK_LUA_TABLE_NUMBER;
            value.as.n = (f64)lua_tonumber(L, -1);
            break;
        case LUA_TSTRING: {
            size_t len = 0u;
            const char *string = lua_tolstring(L, -1, &len);
            if (len > result->max_string_bytes) {
                lua_pop(L, 1);
                return BREAK_LUA_OVERLOAD;
            }
            value.type = BREAK_LUA_TABLE_STRING;
            value.as.s.data = string;
            value.as.s.len = (u32)len;
            break;
        }
        case LUA_TTABLE:
            value.type = BREAK_LUA_TABLE_TABLE;
            break;
        case LUA_TUSERDATA: {
            BreakLuaValue scalar;
            err = break_lua_take_value(L, -1, &scalar);
            if (err != BREAK_LUA_OK) {
                lua_pop(L, 1);
                return err;
            }
            if (scalar.type != BREAK_LUA_VALUE_HOST_HANDLE) {
                lua_pop(L, 1);
                return BREAK_LUA_FAILED;
            }
            value.type = BREAK_LUA_TABLE_HOST_HANDLE;
            value.as.handle = scalar.as.handle;
            break;
        }
        default:
            lua_pop(L, 1);
            return BREAK_LUA_FAILED;
        }
        if (key_is_integer) {
            err = break_lua_table_add_index(result, parent, integer_key,
                                            &value, &child);
        } else {
            err = break_lua_table_add(result, parent, key, key_len,
                                      &value, &child);
        }
        if (err == BREAK_LUA_OK && value.type == BREAK_LUA_TABLE_TABLE) {
            err = break_lua_table_take_children(L, -1, result, child);
        }
        lua_pop(L, 1);
        if (err != BREAK_LUA_OK) {
            return err;
        }
    }
    return BREAK_LUA_OK;
}

static void break_lua_table_swap_storage(BreakLuaTable *table)
{
    BreakLuaTableNode *nodes = table->nodes;
    table->nodes = table->scratch;
    table->scratch = nodes;
}

void break_lua_table_call_impl(lua_State *L, BreakLuaTableOpCtx *ctx)
{
    BreakLuaRuntime *runtime = *(BreakLuaRuntime **)lua_getextraspace(L);
    int base = lua_gettop(L);
    int status;
    bool armed;
    BreakLuaError err;
    u32 old_count;
    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->env_ref);
    lua_pushstring(L, ctx->function_name);
    lua_rawget(L, -2);
    if (!lua_isfunction(L, -1)) {
        ctx->hdr.status = BREAK_LUA_INVALID;
        lua_settop(L, base);
        return;
    }
    luaL_checkstack(L, 64, "break_lua table call");
    err = break_lua_table_push_node(L, ctx->argument,
                                    break_lua_table_root(ctx->argument));
    if (err != BREAK_LUA_OK) {
        ctx->hdr.status = err;
        lua_settop(L, base);
        return;
    }
    armed = runtime->instruction_budget != 0u;
    if (armed) {
        const int count = runtime->instruction_budget > (u64)INT_MAX
                              ? INT_MAX
                              : (int)runtime->instruction_budget;
        runtime->budget_tripped = false;
        break_lua_execution_hook_arm(runtime, count);
    }
    status = lua_pcall(L, 1, 1, 0);
    if (armed) {
        break_lua_execution_hook_disarm(runtime);
    }
    if (status != LUA_OK) {
        ctx->hdr.status = status == LUA_ERRMEM ? BREAK_LUA_OOM
                                               : BREAK_LUA_FAILED;
        lua_settop(L, base);
        return;
    }
    if (!lua_istable(L, -1)) {
        ctx->hdr.status = BREAK_LUA_FAILED;
        lua_settop(L, base);
        return;
    }

    old_count = ctx->result->count;
    break_lua_table_swap_storage(ctx->result);
    break_lua_table_init_root(ctx->result->nodes);
    ctx->result->count = 1u;
    err = break_lua_table_take_children(L, -1, ctx->result,
                                        break_lua_table_root(ctx->result));
    if (err != BREAK_LUA_OK) {
        break_lua_table_swap_storage(ctx->result);
        ctx->result->count = old_count;
        ctx->hdr.status = err;
        lua_settop(L, base);
        return;
    }
    ctx->hdr.status = BREAK_LUA_OK;
    lua_settop(L, base);
}

BreakLuaError break_lua_runtime_call_table(BreakLuaRuntime *runtime,
                                            const char *module_name,
                                            const char *function_name,
                                            const BreakLuaTable *argument,
                                            BreakLuaTable *result)
{
    BreakLuaTableOpCtx ctx;
    BreakLuaModule *module;
    BreakLuaError owner = break_lua_runtime_check_owner(runtime);
    usize name_len;
    usize fn_len;
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    if (!module_name || !function_name || !argument || !result) {
        return BREAK_LUA_INVALID;
    }
    name_len = break_lua_name_len(module_name, BREAK_LUA_MAX_MODULE_NAME_BYTES);
    fn_len = break_lua_name_len(function_name, BREAK_LUA_MAX_MODULE_NAME_BYTES);
    if (name_len == 0u || name_len >= BREAK_LUA_MAX_MODULE_NAME_BYTES ||
        fn_len == 0u || fn_len >= BREAK_LUA_MAX_MODULE_NAME_BYTES) {
        return BREAK_LUA_INVALID;
    }
    module = break_lua_module_find(runtime, module_name);
    if (!module) {
        return BREAK_LUA_STALE;
    }
    memset(&ctx, 0, sizeof(ctx));
    ctx.hdr.op = BREAK_LUA_OP_CALL_TABLE;
    ctx.env_ref = module->env_ref;
    ctx.function_name = function_name;
    ctx.argument = argument;
    ctx.result = result;
    return break_lua_op_run(runtime, &ctx.hdr);
}
