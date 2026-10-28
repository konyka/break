/* Editor side of the scripted input replay — see editor_input_driver.h. */

#include "editor_input_driver.h"

#include "editor_image_preview.h"
#include "editor_input_script.h"

#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_doc.h>
#include <platform/input.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myui/my_widget.h"
#include "myui/widgets/my_button.h"

#define DRIVER_MAX_SCRIPT_BYTES (64u * 1024u)

struct BreakEditorInputDriver {
    BreakEditorInputScript *script;
    BreakEditorShell *shell; /* borrowed for the current frame */
    char shot[BREAK_EDITOR_INPUT_SCRIPT_MAX_ARG]; /* queued screenshot */
    bool shot_pending;
    u32 shot_failures;
};

bool break_editor_input_driver_take_cli(int *argc, char **argv,
                                        const char **out_path, char *err,
                                        usize err_cap) {
    int i, kept = 1;
    *out_path = NULL;
    for (i = 1; i < *argc; i++) {
        if (strcmp(argv[i], "--input-script") == 0) {
            if (i + 1 >= *argc) {
                (void)snprintf(err, err_cap, "--input-script needs a file");
                return false;
            }
            *out_path = argv[++i];
            continue;
        }
        argv[kept++] = argv[i];
    }
    argv[kept] = NULL;
    *argc = kept;
    return true;
}

BreakEditorInputDriver *break_editor_input_driver_create(const char *path,
                                                         char *err,
                                                         usize err_cap) {
    BreakEditorInputDriver *d;
    FILE *f;
    char *text;
    usize n;
    f = fopen(path, "rb");
    if (f == NULL) {
        (void)snprintf(err, err_cap, "cannot open input script %s", path);
        return NULL;
    }
    text = (char *)malloc(DRIVER_MAX_SCRIPT_BYTES + 1u);
    if (text == NULL) {
        fclose(f);
        return NULL;
    }
    n = fread(text, 1u, DRIVER_MAX_SCRIPT_BYTES + 1u, f);
    fclose(f);
    if (n > DRIVER_MAX_SCRIPT_BYTES) {
        free(text);
        (void)snprintf(err, err_cap, "input script larger than 64 KiB");
        return NULL;
    }
    d = (BreakEditorInputDriver *)calloc(1u, sizeof(*d));
    if (d == NULL) {
        free(text);
        return NULL;
    }
    d->script = break_editor_input_script_parse(text, n, err, err_cap);
    free(text);
    if (d->script == NULL) {
        free(d);
        return NULL;
    }
    return d;
}

void break_editor_input_driver_destroy(BreakEditorInputDriver *d) {
    if (d == NULL) return;
    break_editor_input_script_destroy(d->script);
    free(d);
}

/* ---- hooks ---- */

/* "list@text": the realized row of a list view whose button text is
 * `text` (rows are the list's direct children). */
static my_widget_t *drv_find_row(my_widget_t *list, const char *text) {
    usize i, n;
    if (list == NULL) return NULL;
    n = my_widget_child_count(list);
    for (i = 0; i < n; i++) {
        my_widget_t *row = my_widget_get_child(list, i);
        if (row != NULL && my_button_is_instance(row)) {
            const my_button_t *b = (const my_button_t *)row;
            if (b->text != NULL && strcmp(b->text, text) == 0) return row;
        }
    }
    return NULL;
}

static bool drv_locate(void *user, const char *name, f32 fx, f32 fy, f32 *x,
                       f32 *y) {
    BreakEditorInputDriver *d = (BreakEditorInputDriver *)user;
    my_widget_t *root = break_editor_shell_root(d->shell);
    my_widget_t *w;
    const char *at = strchr(name, '@');
    int32_t gx = 0, gy = 0;
    if (at != NULL) {
        char list_name[64];
        usize ln = (usize)(at - name);
        if (ln == 0u || ln >= sizeof(list_name)) return false;
        memcpy(list_name, name, ln);
        list_name[ln] = '\0';
        w = drv_find_row(my_widget_find_descendant(root, list_name), at + 1);
    } else {
        w = my_widget_find_descendant(root, name);
    }
    if (w == NULL || w->rect.w <= 0 || w->rect.h <= 0) return false;
    my_widget_local_to_global(w, &gx, &gy);
    *x = (f32)gx + fx * (f32)w->rect.w;
    *y = (f32)gy + fy * (f32)w->rect.h;
    if (getenv("BREAK_INPUT_SCRIPT_TRACE") != NULL) {
        printf("input-script: move_to %s -> (%.1f, %.1f) rect %d,%d %dx%d\n",
               name, (double)*x, (double)*y, (int)gx, (int)gy, (int)w->rect.w,
               (int)w->rect.h);
    }
    return true;
}

static const char *selected_name(BreakEditorShell *shell) {
    BreakEditorDoc *doc = break_editor_shell_doc(shell);
    BreakEditorEntityId sel = break_editor_shell_selected(shell);
    usize i, n = break_editor_doc_entity_count(doc);
    for (i = 0; i < n; i++) {
        BreakEditorEntityId id;
        const char *name = NULL;
        if (break_editor_doc_entity_at(doc, i, &id, &name) &&
            id.index == sel.index && id.generation == sel.generation) {
            return name != NULL ? name : "";
        }
    }
    return NULL;
}

/* Checks: entities <n> | selected <name|none> | tool <none|w|e|r> |
 * undo <n> | palette <open|closed> | preview_reloads <n> |
 * pos_x_above <v> | pos_x_below <v> (selected entity's Transform) |
 * log_contains <text> | print (diagnostic line, always passes) */
static bool drv_expect(void *user, const char *what) {
    BreakEditorInputDriver *d = (BreakEditorInputDriver *)user;
    BreakEditorShell *shell = d->shell;
    BreakEditorDoc *doc = break_editor_shell_doc(shell);
    char key[32];
    const char *arg;
    usize klen;
    long n = 0;
    arg = strchr(what, ' ');
    klen = arg != NULL ? (usize)(arg - what) : strlen(what);
    if (klen >= sizeof(key)) return false;
    memcpy(key, what, klen);
    key[klen] = '\0';
    arg = arg != NULL ? arg + 1 : "";
    if (strcmp(key, "entities") == 0) {
        return sscanf(arg, "%ld", &n) == 1 &&
               (long)break_editor_doc_entity_count(doc) == n;
    }
    if (strcmp(key, "selected") == 0) {
        const char *name = selected_name(shell);
        return strcmp(arg, "none") == 0 ? name == NULL
                                        : name != NULL && strcmp(name, arg) == 0;
    }
    if (strcmp(key, "tool") == 0) {
        BreakEditorGizmoMode m = break_editor_shell_gizmo_mode(shell);
        return (strcmp(arg, "none") == 0 && m == BREAK_EDITOR_GIZMO_NONE) ||
               (strcmp(arg, "w") == 0 && m == BREAK_EDITOR_GIZMO_TRANSLATE) ||
               (strcmp(arg, "e") == 0 && m == BREAK_EDITOR_GIZMO_ROTATE) ||
               (strcmp(arg, "r") == 0 && m == BREAK_EDITOR_GIZMO_SCALE);
    }
    if (strcmp(key, "undo") == 0) {
        return sscanf(arg, "%ld", &n) == 1 &&
               (long)break_editor_cmd_stack_undo_count(
                   break_editor_doc_stack(doc)) == n;
    }
    if (strcmp(key, "palette") == 0) {
        bool open = break_editor_shell_palette_is_open(shell);
        return strcmp(arg, "open") == 0 ? open : !open;
    }
    if (strcmp(key, "preview_reloads") == 0) {
        BreakEditorImagePreviewStats st;
        return sscanf(arg, "%ld", &n) == 1 &&
               break_editor_shell_image_preview_stats(shell, &st) &&
               (long)st.reloads == n;
    }
    if (strcmp(key, "pos_x_above") == 0 || strcmp(key, "pos_x_below") == 0) {
        f32 x = 0.0f;
        double limit = 0.0;
        if (sscanf(arg, "%lf", &limit) != 1 ||
            !break_editor_doc_get_field_f32(doc, break_editor_shell_selected(shell),
                                            BREAK_EDITOR_COMPONENT_TRANSFORM,
                                            0u, &x)) {
            return false;
        }
        return key[6] == 'a' ? (double)x > limit : (double)x < limit;
    }
    if (strcmp(key, "log_contains") == 0) {
        return arg[0] != '\0' &&
               strstr(break_editor_shell_console_text(shell), arg) != NULL;
    }
    if (strcmp(key, "print") == 0) {
        /* diagnostics only: always passes */
        BreakEditorEntityId sel = break_editor_shell_selected(shell);
        f32 x = 0.0f;
        (void)break_editor_doc_get_field_f32(doc, sel,
                                             BREAK_EDITOR_COMPONENT_TRANSFORM,
                                             0u, &x);
        printf("input-script: entities=%u selected=%s tool=%d undo=%u pos.x=%.3f status=%s\n",
               (unsigned)break_editor_doc_entity_count(doc),
               selected_name(shell) != NULL ? selected_name(shell) : "none",
               (int)break_editor_shell_gizmo_mode(shell),
               (unsigned)break_editor_cmd_stack_undo_count(
                   break_editor_doc_stack(doc)),
               (double)x, break_editor_shell_status_text(shell));
        return true;
    }
    return false;
}

static void drv_screenshot(void *user, const char *file) {
    BreakEditorInputDriver *d = (BreakEditorInputDriver *)user;
    (void)snprintf(d->shot, sizeof(d->shot), "%s", file);
    d->shot_pending = true;
}

bool break_editor_input_driver_frame(BreakEditorInputDriver *d,
                                     Platform *platform,
                                     BreakEditorShell *shell) {
    BreakEditorInputScriptHooks hooks;
    u32 before;
    bool more;
    if (d == NULL) return true;
    d->shell = shell;
    hooks.locate = drv_locate;
    hooks.expect = drv_expect;
    hooks.screenshot = drv_screenshot;
    hooks.user = d;
    before = break_editor_input_script_failures(d->script);
    more = break_editor_input_script_step(d->script, platform_input(platform),
                                          platform_get_input_scale(platform),
                                          &hooks);
    if (break_editor_input_script_failures(d->script) != before) {
        fprintf(stderr, "input-script: step failed (first failure at line %u)\n",
                (unsigned)break_editor_input_script_first_failure_line(d->script));
    }
    return more;
}

void break_editor_input_driver_after_frame(BreakEditorInputDriver *d,
                                           RHIDevice *device, u32 w, u32 h) {
    usize bytes;
    u8 *px;
    FILE *f;
    if (d == NULL || !d->shot_pending) return;
    d->shot_pending = false;
    bytes = (usize)w * (usize)h * 4u;
    px = (u8 *)malloc(bytes);
    if (px == NULL || !rhi_screenshot(device, 0, 0, w, h, px, bytes) ||
        (f = fopen(d->shot, "wb")) == NULL) {
        free(px);
        d->shot_failures++;
        fprintf(stderr, "input-script: screenshot %s failed\n", d->shot);
        return;
    }
    /* binary PPM, top-down rows (rhi_screenshot contract) */
    fprintf(f, "P6\n%u %u\n255\n", (unsigned)w, (unsigned)h);
    {
        usize i;
        for (i = 0; i < (usize)w * (usize)h; i++) {
            (void)fwrite(px + i * 4u, 1u, 3u, f);
        }
    }
    fclose(f);
    free(px);
}

int break_editor_input_driver_exit_code(const BreakEditorInputDriver *d) {
    if (d == NULL) return 0;
    return break_editor_input_script_failures(d->script) == 0u &&
                   d->shot_failures == 0u
               ? 0
               : 3;
}
