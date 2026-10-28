/* Scripted input replay — see editor_input_script.h. */

#include "editor_input_script.h"

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCRIPT_MAX_COORD 16384.0f
#define SCRIPT_MAX_WAIT 100000L
#define SCRIPT_MAX_CHORD_KEYS 4u
#define SCRIPT_KEY_SHIFT 289
#define SCRIPT_KEY_CTRL 290

typedef enum {
    CMD_WAIT,
    CMD_MOVE,
    CMD_MOVE_TO,
    CMD_DOWN,
    CMD_UP,
    CMD_CLICK,
    CMD_KEY,
    CMD_KEYDOWN,
    CMD_KEYUP,
    CMD_CHORD,
    CMD_SCROLL,
    CMD_SCREENSHOT,
    CMD_EXPECT,
    CMD_QUIT
} ScriptOp;

typedef struct {
    ScriptOp op;
    u32 line;
    long frames;            /* wait */
    f32 x, y;               /* move; move_to fractions */
    i32 keys[SCRIPT_MAX_CHORD_KEYS]; /* key/button codes; chord: mods then key */
    u32 key_count;
    char arg[BREAK_EDITOR_INPUT_SCRIPT_MAX_ARG]; /* widget/file/expectation */
} ScriptCmd;

struct BreakEditorInputScript {
    ScriptCmd *cmds;
    usize count;
    usize pc;     /* current command */
    u32 phase;    /* sub-frame of a multi-frame command */
    long waited;  /* frames already waited */
    u32 failures;
    u32 first_failure_line;
    bool quit;
    bool done;
};

static void script_err(char *err, usize cap, u32 line, const char *what) {
    if (err != NULL && cap > 0u) {
        (void)snprintf(err, cap, "line %u: %s", (unsigned)line, what);
    }
}

static bool parse_long(const char *tok, long lo, long hi, long *out) {
    char *end = NULL;
    long v;
    if (tok == NULL || *tok == '\0') return false;
    errno = 0;
    v = strtol(tok, &end, 10);
    if (errno != 0 || end == tok || *end != '\0' || v < lo || v > hi) {
        return false;
    }
    *out = v;
    return true;
}

static bool parse_float(const char *tok, f32 lo, f32 hi, f32 *out) {
    char *end = NULL;
    double v;
    if (tok == NULL || *tok == '\0') return false;
    errno = 0;
    v = strtod(tok, &end);
    if (errno != 0 || end == tok || *end != '\0' || !isfinite(v) ||
        v < (double)lo || v > (double)hi) {
        return false;
    }
    *out = (f32)v;
    return true;
}

static i32 key_code(const char *name) {
    static const struct {
        const char *name;
        i32 code;
    } k_named[] = {
        {"space", 32},       {"escape", 256}, {"enter", 257},
        {"tab", 259},        {"backspace", 260}, {"left", 261},
        {"right", 262},      {"up", 263},     {"down", 264},
        {"delete", 288},     {"shift", SCRIPT_KEY_SHIFT},
        {"ctrl", SCRIPT_KEY_CTRL},
    };
    usize i;
    if (name == NULL || name[0] == '\0') return -1;
    if (name[1] == '\0' && ((name[0] >= 'a' && name[0] <= 'z') ||
                            (name[0] >= '0' && name[0] <= '9'))) {
        return (i32)name[0];
    }
    if (name[0] == 'f' && name[1] >= '1' && name[1] <= '9') {
        long n;
        if (parse_long(name + 1, 1, 12, &n)) {
            return (i32)(271 + n - 1);
        }
        return -1;
    }
    for (i = 0; i < sizeof(k_named) / sizeof(k_named[0]); i++) {
        if (strcmp(name, k_named[i].name) == 0) return k_named[i].code;
    }
    return -1;
}

static i32 button_code(const char *name) {
    if (name == NULL) return -1;
    if (strcmp(name, "left") == 0) return INPUT_MOUSE_LEFT;
    if (strcmp(name, "right") == 0) return INPUT_MOUSE_RIGHT;
    if (strcmp(name, "middle") == 0) return INPUT_MOUSE_MIDDLE;
    return -1;
}

/* Splits `line` in place on spaces/tabs; returns the token count (<= max). */
static u32 split(char *line, char **tok, u32 max) {
    u32 n = 0;
    char *p = line;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') *p++ = '\0';
        if (*p == '\0') break;
        if (n == max) return max + 1u; /* too many tokens */
        tok[n++] = p;
        while (*p != '\0' && *p != ' ' && *p != '\t') p++;
    }
    return n;
}

static bool parse_line(char *line, u32 lineno, ScriptCmd *cmd, char *err,
                       usize cap) {
    char *tok[6];
    char *rest = NULL; /* expect keeps the rest of the line verbatim */
    u32 n;
    const char *op;
    memset(cmd, 0, sizeof(*cmd));
    cmd->line = lineno;
    if (strncmp(line, "expect ", 7) == 0) {
        rest = line + 7;
        while (*rest == ' ' || *rest == '\t') rest++;
        if (*rest == '\0' || strlen(rest) >= sizeof(cmd->arg)) {
            script_err(err, cap, lineno, "expect needs a check");
            return false;
        }
        cmd->op = CMD_EXPECT;
        memcpy(cmd->arg, rest, strlen(rest) + 1u);
        return true;
    }
    n = split(line, tok, 5u);
    if (n == 0u || n > 5u) {
        script_err(err, cap, lineno, "bad number of arguments");
        return false;
    }
    op = tok[0];
    if (strcmp(op, "wait") == 0) {
        if (n != 2u || !parse_long(tok[1], 0, SCRIPT_MAX_WAIT, &cmd->frames)) {
            script_err(err, cap, lineno, "wait <frames 0..100000>");
            return false;
        }
        cmd->op = CMD_WAIT;
    } else if (strcmp(op, "move") == 0) {
        if (n != 3u ||
            !parse_float(tok[1], -SCRIPT_MAX_COORD, SCRIPT_MAX_COORD, &cmd->x) ||
            !parse_float(tok[2], -SCRIPT_MAX_COORD, SCRIPT_MAX_COORD, &cmd->y)) {
            script_err(err, cap, lineno, "move <x> <y>");
            return false;
        }
        cmd->op = CMD_MOVE;
    } else if (strcmp(op, "move_to") == 0) {
        cmd->x = 0.5f;
        cmd->y = 0.5f;
        if ((n != 2u && n != 4u) || strlen(tok[1]) >= sizeof(cmd->arg) ||
            (n == 4u && (!parse_float(tok[2], 0.0f, 1.0f, &cmd->x) ||
                         !parse_float(tok[3], 0.0f, 1.0f, &cmd->y)))) {
            script_err(err, cap, lineno, "move_to <widget> [<fx 0..1> <fy 0..1>]");
            return false;
        }
        memcpy(cmd->arg, tok[1], strlen(tok[1]) + 1u);
        cmd->op = CMD_MOVE_TO;
    } else if (strcmp(op, "down") == 0 || strcmp(op, "up") == 0 ||
               strcmp(op, "click") == 0) {
        i32 b = n == 2u ? button_code(tok[1]) : -1;
        if (b < 0) {
            script_err(err, cap, lineno, "button must be left, right or middle");
            return false;
        }
        cmd->keys[0] = b;
        cmd->key_count = 1u;
        cmd->op = op[0] == 'd' ? CMD_DOWN : op[0] == 'u' ? CMD_UP : CMD_CLICK;
    } else if (strcmp(op, "key") == 0 || strcmp(op, "keydown") == 0 ||
               strcmp(op, "keyup") == 0) {
        i32 k = n == 2u ? key_code(tok[1]) : -1;
        if (k < 0) {
            script_err(err, cap, lineno, "unknown key name");
            return false;
        }
        cmd->keys[0] = k;
        cmd->key_count = 1u;
        cmd->op = strcmp(op, "key") == 0       ? CMD_KEY
                  : strcmp(op, "keydown") == 0 ? CMD_KEYDOWN
                                               : CMD_KEYUP;
    } else if (strcmp(op, "chord") == 0) {
        char *p, *part;
        if (n != 2u) {
            script_err(err, cap, lineno, "chord <mod>+<key>");
            return false;
        }
        p = tok[1];
        for (;;) {
            i32 k;
            part = p;
            p = strchr(p, '+');
            if (p != NULL) *p++ = '\0';
            k = key_code(part);
            if (k < 0 || cmd->key_count == SCRIPT_MAX_CHORD_KEYS) {
                script_err(err, cap, lineno, "bad chord");
                return false;
            }
            cmd->keys[cmd->key_count++] = k;
            if (p == NULL) break;
        }
        if (cmd->key_count < 2u) {
            script_err(err, cap, lineno, "chord needs a modifier and a key");
            return false;
        }
        cmd->op = CMD_CHORD;
    } else if (strcmp(op, "scroll") == 0) {
        if (n != 2u || !parse_float(tok[1], -100.0f, 100.0f, &cmd->y)) {
            script_err(err, cap, lineno, "scroll <dy -100..100>");
            return false;
        }
        cmd->op = CMD_SCROLL;
    } else if (strcmp(op, "screenshot") == 0) {
        if (n != 2u || strlen(tok[1]) >= sizeof(cmd->arg)) {
            script_err(err, cap, lineno, "screenshot <file>");
            return false;
        }
        memcpy(cmd->arg, tok[1], strlen(tok[1]) + 1u);
        cmd->op = CMD_SCREENSHOT;
    } else if (strcmp(op, "quit") == 0) {
        if (n != 1u) {
            script_err(err, cap, lineno, "quit takes no arguments");
            return false;
        }
        cmd->op = CMD_QUIT;
    } else {
        script_err(err, cap, lineno, "unknown command");
        return false;
    }
    return true;
}

BreakEditorInputScript *break_editor_input_script_parse(const char *text,
                                                        usize len, char *err,
                                                        usize err_cap) {
    BreakEditorInputScript *s;
    usize pos = 0u;
    u32 lineno = 0u;
    if (err != NULL && err_cap > 0u) err[0] = '\0';
    if (text == NULL) {
        script_err(err, err_cap, 0u, "no script");
        return NULL;
    }
    s = (BreakEditorInputScript *)calloc(1u, sizeof(*s));
    if (s == NULL) return NULL;
    s->cmds = (ScriptCmd *)calloc(BREAK_EDITOR_INPUT_SCRIPT_MAX_COMMANDS,
                                  sizeof(ScriptCmd));
    if (s->cmds == NULL) {
        free(s);
        return NULL;
    }
    while (pos < len) {
        char line[BREAK_EDITOR_INPUT_SCRIPT_MAX_LINE];
        usize start = pos, l;
        char *p;
        while (pos < len && text[pos] != '\n') pos++;
        l = pos - start;
        if (pos < len) pos++; /* the '\n' */
        lineno++;
        if (l > 0u && text[start + l - 1u] == '\r') l--;
        if (l >= sizeof(line)) {
            script_err(err, err_cap, lineno, "line too long");
            break_editor_input_script_destroy(s);
            return NULL;
        }
        memcpy(line, text + start, l);
        line[l] = '\0';
        p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '\0' || *p == '#') continue;
        if (s->count == BREAK_EDITOR_INPUT_SCRIPT_MAX_COMMANDS) {
            script_err(err, err_cap, lineno, "too many commands");
            break_editor_input_script_destroy(s);
            return NULL;
        }
        if (!parse_line(p, lineno, &s->cmds[s->count], err, err_cap)) {
            break_editor_input_script_destroy(s);
            return NULL;
        }
        s->count++;
    }
    return s;
}

void break_editor_input_script_destroy(BreakEditorInputScript *s) {
    if (s == NULL) return;
    free(s->cmds);
    free(s);
}

usize break_editor_input_script_command_count(const BreakEditorInputScript *s) {
    return s != NULL ? s->count : 0u;
}

static void script_fail(BreakEditorInputScript *s, u32 line) {
    s->failures++;
    if (s->first_failure_line == 0u) s->first_failure_line = line;
}

static void set_mouse(InputState *in, f32 x, f32 y) {
    in->mouse_dx = in->has_mouse_pos ? x - in->mouse_x : 0.0f;
    in->mouse_dy = in->has_mouse_pos ? y - in->mouse_y : 0.0f;
    in->mouse_x = x;
    in->mouse_y = y;
    in->has_mouse_pos = true;
}

/* Edge values match the platform: 3 = pressed this frame, 1 = released this
 * frame (input_new_frame turns them into 2 = held / 0 = up). */
static void press(InputState *in, i32 k) { in->keys[k] = 3u; }
static void release(InputState *in, i32 k) {
    if (in->keys[k] != 0u) in->keys[k] = 1u;
}

/* Returns true when the command is complete after this frame. */
static bool run(BreakEditorInputScript *s, const ScriptCmd *c, InputState *in,
                f32 scale, const BreakEditorInputScriptHooks *h) {
    u32 i;
    switch (c->op) {
    case CMD_WAIT:
        if (s->waited >= c->frames) return true;
        s->waited++;
        return s->waited >= c->frames;
    case CMD_MOVE:
        set_mouse(in, c->x * scale, c->y * scale);
        return true;
    case CMD_MOVE_TO: {
        f32 x = 0.0f, y = 0.0f;
        if (h == NULL || h->locate == NULL ||
            !h->locate(h->user, c->arg, c->x, c->y, &x, &y)) {
            script_fail(s, c->line);
        } else {
            set_mouse(in, x * scale, y * scale);
        }
        return true;
    }
    case CMD_DOWN:
    case CMD_KEYDOWN:
        press(in, c->keys[0]);
        return true;
    case CMD_UP:
    case CMD_KEYUP:
        release(in, c->keys[0]);
        return true;
    case CMD_CLICK:
    case CMD_KEY:
        if (s->phase == 0u) {
            press(in, c->keys[0]);
            return false;
        }
        release(in, c->keys[0]);
        return true;
    case CMD_CHORD:
        if (s->phase == 0u) {
            for (i = 0; i + 1u < c->key_count; i++) press(in, c->keys[i]);
            return false;
        }
        if (s->phase == 1u) {
            press(in, c->keys[c->key_count - 1u]);
            return false;
        }
        for (i = 0; i < c->key_count; i++) release(in, c->keys[i]);
        return true;
    case CMD_SCROLL:
        in->scroll_dy = c->y;
        return true;
    case CMD_SCREENSHOT:
        if (h == NULL || h->screenshot == NULL) {
            script_fail(s, c->line);
        } else {
            h->screenshot(h->user, c->arg);
        }
        return true;
    case CMD_EXPECT:
        if (h == NULL || h->expect == NULL || !h->expect(h->user, c->arg)) {
            script_fail(s, c->line);
        }
        return true;
    case CMD_QUIT:
        s->quit = true;
        return true;
    }
    return true;
}

bool break_editor_input_script_step(BreakEditorInputScript *s,
                                    InputState *input, f32 input_scale,
                                    const BreakEditorInputScriptHooks *hooks) {
    if (s == NULL || input == NULL || s->done) {
        return false;
    }
    if (s->pc >= s->count) {
        s->done = true;
        return false;
    }
    if (!(input_scale > 0.0f)) input_scale = 1.0f;
    if (run(s, &s->cmds[s->pc], input, input_scale, hooks)) {
        s->pc++;
        s->phase = 0u;
        s->waited = 0;
        if (s->quit) {
            s->done = true;
            return false;
        }
    } else {
        s->phase++;
    }
    return true;
}

u32 break_editor_input_script_failures(const BreakEditorInputScript *s) {
    return s != NULL ? s->failures : 0u;
}

u32 break_editor_input_script_first_failure_line(
    const BreakEditorInputScript *s) {
    return s != NULL ? s->first_failure_line : 0u;
}

bool break_editor_input_script_quit_requested(const BreakEditorInputScript *s) {
    return s != NULL && s->quit;
}
