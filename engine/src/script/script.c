#include <script/script.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void script_engine_init(ScriptEngine *se) {
    memset(se, 0, sizeof(*se));
}

void script_engine_shutdown(ScriptEngine *se) {
    for (u32 i = 0; i < se->func_count; i++) {
        free(se->funcs[i].ops);
    }
    free(se->source);
    memset(se, 0, sizeof(*se));
}

static void script_parse_line(ScriptEngine *se, const char *line) {
    char func_name[64] = {0};
    if (sscanf(line, "func %63s", func_name) == 1) {
        if (se->func_count < SCRIPT_MAX_CALLBACKS) {
            snprintf(se->funcs[se->func_count].name, sizeof(se->funcs[se->func_count].name), "%s", func_name);
            se->funcs[se->func_count].ops = NULL;
            se->funcs[se->func_count].op_count = 0;
            se->func_count++;
        }
        return;
    }

    if (se->func_count == 0) {
        char var_name[64];
        f32 val;
        if (sscanf(line, "var %63s = %f", var_name, &val) == 2) {
            if (se->global_count < SCRIPT_MAX_GLOBALS) {
                snprintf(se->globals[se->global_count].name, sizeof(se->globals[se->global_count].name), "%s", var_name);
                se->globals[se->global_count].value = val;
                se->global_count++;
            }
        }
        return;
    }

    ScriptFunc *fn = &se->funcs[se->func_count - 1];
    /* Capacity-based growth: initial 16, double when full (avoids per-op realloc) */
    if (fn->op_count >= fn->op_capacity) {
        u32 new_cap = fn->op_capacity == 0 ? 16 : fn->op_capacity * 2;
        ScriptOp *new_ops = realloc(fn->ops, new_cap * sizeof(ScriptOp));
        if (!new_ops) return;
        fn->ops = new_ops;
        fn->op_capacity = new_cap;
    }
    fn->op_count++;

    ScriptOp *op = &fn->ops[fn->op_count - 1];
    memset(op, 0, sizeof(*op));
    op->resolved_index = -1;  /* Task 5: mark as unresolved */

    char target[64] = {0};
    f32 val = 0;
    if (sscanf(line, "set %63s %f", target, &val) == 2) {
        op->type = SCRIPT_OP_SET;
        snprintf(op->target, sizeof(op->target), "%s", target);
        op->value = val;
    } else if (sscanf(line, "add %63s %f", target, &val) == 2) {
        op->type = SCRIPT_OP_ADD;
        snprintf(op->target, sizeof(op->target), "%s", target);
        op->value = val;
    } else if (sscanf(line, "spawn %f %f %f", &op->args[0], &op->args[1], &op->args[2]) == 3) {
        op->type = SCRIPT_OP_SPAWN;
    } else if (strncmp(line, "print", 5) == 0) {
        op->type = SCRIPT_OP_PRINT;
    } else {
        fn->op_count--;
    }
}

bool script_load(ScriptEngine *se, const char *path) {
    for (u32 i = 0; i < se->func_count; i++) {
        free(se->funcs[i].ops);
        se->funcs[i].ops = NULL;
        se->funcs[i].op_count = 0;
        se->funcs[i].op_capacity = 0;
    }
    se->func_count = 0;
    se->global_count = 0;
    se->loaded = false;

    FILE *f = fopen(path, "rb");
    if (!f) return false;

    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return false; }
    long sz = ftell(f);
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return false; }
    if (sz < 0) { fclose(f); return false; }

    free(se->source);
    se->source = malloc((usize)sz + 1);
    if (!se->source) { fclose(f); return false; }
    usize rd = fread(se->source, 1, (usize)sz, f);
    se->source[rd] = '\0';
    fclose(f);

    char *line = se->source;
    while (*line) {
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';

        while (*line == ' ' || *line == '\t') line++;
        if (*line != '#' && *line != '\0') {
            script_parse_line(se, line);
        }

        if (nl) line = nl + 1;
        else break;
    }

    se->loaded = true;
    LOG_INFO("Script loaded: %s (%u funcs, %u vars)", path, se->func_count, se->global_count);
    return true;
}

void script_set_global(ScriptEngine *se, const char *name, f32 value) {
    for (u32 i = 0; i < se->global_count; i++) {
        if (strcmp(se->globals[i].name, name) == 0) {
            se->globals[i].value = value;
            return;
        }
    }
    if (se->global_count < SCRIPT_MAX_GLOBALS) {
        snprintf(se->globals[se->global_count].name, sizeof(se->globals[se->global_count].name), "%s", name);
        se->globals[se->global_count].value = value;
        se->global_count++;
    }
}

f32 script_get_global(ScriptEngine *se, const char *name) {
    for (u32 i = 0; i < se->global_count; i++) {
        if (strcmp(se->globals[i].name, name) == 0) return se->globals[i].value;
    }
    return 0.0f;
}

static ScriptFunc *script_find_func(ScriptEngine *se, const char *name) {
    for (u32 i = 0; i < se->func_count; i++) {
        if (strcmp(se->funcs[i].name, name) == 0) return &se->funcs[i];
    }
    return NULL;
}

/* Resolve or create global variable index (shared by SET/ADD, Round 18). */
static inline i32 script_resolve_global(ScriptEngine *se, ScriptOp *op) {
    if (op->resolved_index >= 0) return op->resolved_index;
    for (u32 g = 0; g < se->global_count; g++) {
        if (strcmp(se->globals[g].name, op->target) == 0) {
            op->resolved_index = (i32)g;
            return op->resolved_index;
        }
    }
    if (se->global_count < SCRIPT_MAX_GLOBALS) {
        op->resolved_index = (i32)se->global_count;
        snprintf(se->globals[se->global_count].name,
                 sizeof(se->globals[se->global_count].name), "%s", op->target);
        se->globals[se->global_count].value = 0.0f;
        se->global_count++;
        return op->resolved_index;
    }
    return -1;
}

void script_call(ScriptEngine *se, const char *func_name) {
    ScriptFunc *fn = script_find_func(se, func_name);
    if (!fn) return;

    for (u32 i = 0; i < fn->op_count; i++) {
        ScriptOp *op = &fn->ops[i];
        switch (op->type) {
        case SCRIPT_OP_SET: {
            i32 idx = script_resolve_global(se, op);
            if (idx >= 0 && (u32)idx < se->global_count)
                se->globals[idx].value = op->value;
            break;
        }
        case SCRIPT_OP_ADD: {
            i32 idx = script_resolve_global(se, op);
            if (idx >= 0 && (u32)idx < se->global_count)
                se->globals[idx].value += op->value;
            break;
        }
        case SCRIPT_OP_SPAWN:
            LOG_INFO("Script spawn: %.1f %.1f %.1f", op->args[0], op->args[1], op->args[2]);
            break;
        case SCRIPT_OP_PRINT:
            LOG_INFO("Script: global count=%u", se->global_count);
            break;
        }
    }
}

static u32 file_mtime(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return (u32)st.st_mtime;
}

void script_reload_if_changed(ScriptEngine *se, const char *path) {
    if (!se) return;
    /* R309 (CORRECTNESS): track the observed mtime PER ENGINE, not in a
     * function-local static shared by every ScriptEngine and every path.
     * The old static broke reload in two ways:
     *   1. Re-init staleness — script_engine_init() memsets an engine back to
     *      empty (loaded=false, no funcs), but the shared static kept the old
     *      mtime, so this call saw mt==last_mtime and skipped script_load(),
     *      leaving the re-initialized engine permanently empty (every
     *      script_call a silent no-op) across a level/engine recreate.
     *   2. Multi-file confusion — alternating two paths (or two engines)
     *      through one static made each call look "changed" (thrashing reloads)
     *      or "unchanged" (never reloads) depending on mtime collisions.
     * se->last_mtime is zeroed by script_engine_init, so a fresh engine always
     * loads the current file on its first check. */
    u32 mt = file_mtime(path);
    if (mt != 0 && mt != se->last_mtime) {
        se->last_mtime = mt;
        script_load(se, path);
    }
}
