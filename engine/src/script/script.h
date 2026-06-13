#pragma once
#include <core/types.h>

#define SCRIPT_MAX_CALLBACKS 64
#define SCRIPT_MAX_GLOBALS   128

typedef struct {
    char name[64];
    f32  value;
} ScriptGlobal;

typedef enum {
    SCRIPT_OP_SET,
    SCRIPT_OP_ADD,
    SCRIPT_OP_SPAWN,
    SCRIPT_OP_PRINT,
} ScriptOpType;

typedef struct {
    ScriptOpType type;
    char         target[64];
    f32          value;
    f32          args[3];
    i32          resolved_index;  /* cached global index (-1 = unresolved) */
} ScriptOp;

typedef struct {
    char       name[64];
    ScriptOp  *ops;
    u32        op_count;
    u32        op_capacity;
} ScriptFunc;

typedef struct {
    ScriptFunc    funcs[SCRIPT_MAX_CALLBACKS];
    u32           func_count;
    ScriptGlobal  globals[SCRIPT_MAX_GLOBALS];
    u32           global_count;
    char         *source;
    bool          loaded;
} ScriptEngine;

void  script_engine_init(ScriptEngine *se);
void  script_engine_shutdown(ScriptEngine *se);
bool  script_load(ScriptEngine *se, const char *path);
void  script_set_global(ScriptEngine *se, const char *name, f32 value);
f32   script_get_global(ScriptEngine *se, const char *name);
void  script_call(ScriptEngine *se, const char *func_name);
void  script_reload_if_changed(ScriptEngine *se, const char *path);
