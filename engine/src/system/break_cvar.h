#pragma once

#include <core/types.h>

#define BREAK_CVAR_HARD_MAX 256u
#define BREAK_CVAR_NAME_CAPACITY 64u
#define BREAK_CVAR_STRING_CAPACITY 128u
#define BREAK_CVAR_CONFIG_MAX_BYTES (64u * 1024u)

typedef enum BreakCVarStatus {
    BREAK_CVAR_OK = 0,
    BREAK_CVAR_INVALID,
    BREAK_CVAR_OVERLOAD,
    BREAK_CVAR_OOM,
    BREAK_CVAR_REJECTED,
    BREAK_CVAR_FAILED
} BreakCVarStatus;

typedef enum BreakCVarType {
    BREAK_CVAR_BOOL = 1,
    BREAK_CVAR_INT,
    BREAK_CVAR_FLOAT,
    BREAK_CVAR_STRING
} BreakCVarType;

enum {
    BREAK_CVAR_READONLY = 1u << 0,
    BREAK_CVAR_CHEAT = 1u << 1
};

typedef union BreakCVarValue {
    bool boolean;
    i64 integer;
    f64 number;
    const char *string;
} BreakCVarValue;

typedef struct BreakCVarRegistry BreakCVarRegistry;
typedef void (*BreakCVarChangedFn)(const char *name, void *user);

typedef struct BreakCVarDesc {
    const char *name;
    BreakCVarType type;
    u32 flags;
    BreakCVarValue default_value;
    i64 min_integer;
    i64 max_integer;
    f64 min_number;
    f64 max_number;
    BreakCVarChangedFn changed;
    void *changed_user;
} BreakCVarDesc;

BreakCVarRegistry *break_cvar_create(u32 capacity);
void break_cvar_destroy(BreakCVarRegistry *registry);
BreakCVarStatus break_cvar_register(BreakCVarRegistry *registry,
                                    const BreakCVarDesc *desc);
BreakCVarStatus break_cvar_get(const BreakCVarRegistry *registry,
                               const char *name, BreakCVarType type,
                               BreakCVarValue *out_value);
BreakCVarStatus break_cvar_set(BreakCVarRegistry *registry, const char *name,
                               BreakCVarValue value, bool allow_cheat);
BreakCVarStatus break_cvar_load(BreakCVarRegistry *registry, const char *path,
                                bool allow_cheat);
BreakCVarStatus break_cvar_save(const BreakCVarRegistry *registry,
                                const char *path);
