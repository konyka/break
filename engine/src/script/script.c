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
            strncpy(se->funcs[se->func_count].name, func_name, 63);
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
                strncpy(se->globals[se->global_count].name, var_name, 63);
                se->globals[se->global_count].value = val;
                se->global_count++;
            }
        }
        return;
    }

    ScriptFunc *fn = &se->funcs[se->func_count - 1];
    u32 new_count = fn->op_count + 1;
    ScriptOp *new_ops = realloc(fn->ops, new_count * sizeof(ScriptOp));
    if (!new_ops) return;
    fn->ops = new_ops;
    fn->op_count = new_count;

    ScriptOp *op = &fn->ops[new_count - 1];
    memset(op, 0, sizeof(*op));

    char target[64] = {0};
    f32 val = 0;
    if (sscanf(line, "set %63s %f", target, &val) == 2) {
        op->type = SCRIPT_OP_SET;
        strncpy(op->target, target, 63);
        op->value = val;
    } else if (sscanf(line, "add %63s %f", target, &val) == 2) {
        op->type = SCRIPT_OP_ADD;
        strncpy(op->target, target, 63);
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
    }
    se->func_count = 0;
    se->global_count = 0;
    se->loaded = false;

    FILE *f = fopen(path, "rb");
    if (!f) return false;

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);

    free(se->source);
    se->source = malloc((usize)sz + 1);
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
        strncpy(se->globals[se->global_count].name, name, 63);
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

void script_call(ScriptEngine *se, const char *func_name) {
    ScriptFunc *fn = script_find_func(se, func_name);
    if (!fn) return;

    for (u32 i = 0; i < fn->op_count; i++) {
        ScriptOp *op = &fn->ops[i];
        switch (op->type) {
        case SCRIPT_OP_SET:
            script_set_global(se, op->target, op->value);
            break;
        case SCRIPT_OP_ADD: {
            f32 cur = script_get_global(se, op->target);
            script_set_global(se, op->target, cur + op->value);
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
    static u32 last_mtime = 0;
    u32 mt = file_mtime(path);
    if (mt != 0 && mt != last_mtime) {
        last_mtime = mt;
        script_load(se, path);
    }
}
