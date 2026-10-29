#include "test_framework.h"

#include "editor_input_script.h"

#include <string.h>

static BreakEditorInputScript *parse(const char *text, char *err) {
    err[0] = '\0';
    return break_editor_input_script_parse(text, strlen(text), err, 128u);
}

typedef struct {
    u32 expects, screenshots, locates;
    bool expect_result;
    char last[128];
} Hooks;

static bool h_locate(void *user, const char *name, f32 fx, f32 fy, f32 *x,
                     f32 *y) {
    Hooks *h = (Hooks *)user;
    h->locates++;
    if (strcmp(name, "editor-add-button") != 0) return false;
    *x = 100.0f + 40.0f * fx;
    *y = 200.0f + 20.0f * fy;
    return true;
}
static bool h_expect(void *user, const char *what) {
    Hooks *h = (Hooks *)user;
    h->expects++;
    snprintf(h->last, sizeof(h->last), "%s", what);
    return h->expect_result;
}
static void h_shot(void *user, const char *file) {
    Hooks *h = (Hooks *)user;
    h->screenshots++;
    snprintf(h->last, sizeof(h->last), "%s", file);
}

static BreakEditorInputScriptHooks hooks_for(Hooks *h) {
    BreakEditorInputScriptHooks k;
    k.locate = h_locate;
    k.expect = h_expect;
    k.screenshot = h_shot;
    k.user = h;
    return k;
}

/* Frame loop the way the editor runs it: new_frame (3->2, 1->0), then the
 * script step writes the frame's input. */
static bool frame(BreakEditorInputScript *s, InputState *in,
                  const BreakEditorInputScriptHooks *k) {
    input_new_frame(in);
    return break_editor_input_script_step(s, in, 1.0f, k);
}

TEST(parse_accepts_every_command) {
    char err[128];
    BreakEditorInputScript *s = parse(
        "# comment\n"
        "\n"
        "wait 3\n"
        "move 10 20\n"
        "move_to editor-add-button\n"
        "move_to editor-add-button 0.25 0.75\n"
        "down left\nup left\nclick right\n"
        "key w\nkeydown shift\nkeyup shift\n"
        "chord ctrl+shift+r\n"
        "scroll -2\n"
        "screenshot out.ppm\n"
        "expect entities 1\n"
        "quit\n",
        err);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_editor_input_script_command_count(s), 15u);
    break_editor_input_script_destroy(s);
}

TEST(parse_errors_name_the_line) {
    char err[128];
    char big[600];
    ASSERT_TRUE(parse("wait 1\nfly 3\n", err) == NULL);
    ASSERT_TRUE(strstr(err, "line 2") != NULL);
    ASSERT_TRUE(parse("move 1\n", err) == NULL);
    ASSERT_TRUE(strstr(err, "line 1") != NULL);
    /* quoted tokens keep spaces (English palette row labels) */
    {
        BreakEditorInputScript *qs =
            parse("move_to \"editor-palette-list@Language: \xE4\xB8\xAD\xE6\x96\x87 (Chinese)\"\nquit\n", err);
        ASSERT_NOT_NULL(qs);
        ASSERT_EQ(break_editor_input_script_command_count(qs), 2u);
        break_editor_input_script_destroy(qs);
    }
    ASSERT_TRUE(parse("move 1 x\n", err) == NULL);
    ASSERT_TRUE(parse("move 99999 0\n", err) == NULL);
    ASSERT_TRUE(parse("wait 200000\n", err) == NULL);
    ASSERT_TRUE(parse("wait -1\n", err) == NULL);
    ASSERT_TRUE(parse("key hyper\n", err) == NULL);
    ASSERT_TRUE(parse("click thumb\n", err) == NULL);
    ASSERT_TRUE(parse("chord ctrl+\n", err) == NULL);
    ASSERT_TRUE(parse("chord ctrl+shift+alt+meta+q\n", err) == NULL);
    ASSERT_TRUE(parse("move_to\n", err) == NULL);
    ASSERT_TRUE(parse("move_to a 2 0.5\n", err) == NULL);
    ASSERT_TRUE(parse("move_to \"editor-palette-list@Language: \n", err) == NULL);
    ASSERT_TRUE(parse("move_to \"row\"junk\n", err) == NULL);
    ASSERT_TRUE(parse("screenshot\n", err) == NULL);
    memset(big, 'a', sizeof(big) - 2u);
    big[0] = '#';
    big[sizeof(big) - 2u] = '\n';
    big[sizeof(big) - 1u] = '\0';
    ASSERT_TRUE(parse(big, err) == NULL);
    ASSERT_TRUE(strstr(err, "long") != NULL);
    ASSERT_TRUE(break_editor_input_script_parse(NULL, 0u, err, 128u) == NULL);
}

TEST(parse_rejects_too_many_commands) {
    static char text[(BREAK_EDITOR_INPUT_SCRIPT_MAX_COMMANDS + 1u) * 7u + 1u];
    char err[128];
    usize i, n = 0;
    for (i = 0; i <= BREAK_EDITOR_INPUT_SCRIPT_MAX_COMMANDS; i++) {
        memcpy(text + n, "wait 1\n", 7u);
        n += 7u;
    }
    text[n] = '\0';
    ASSERT_TRUE(parse(text, err) == NULL);
    ASSERT_TRUE(strstr(err, "too many") != NULL);
    text[n - 7u] = '\0'; /* exactly the maximum */
    {
        BreakEditorInputScript *s = parse(text, err);
        ASSERT_NOT_NULL(s);
        break_editor_input_script_destroy(s);
    }
}

TEST(click_key_and_chord_produce_one_frame_edges) {
    char err[128];
    InputState in;
    Hooks h;
    BreakEditorInputScriptHooks k;
    BreakEditorInputScript *s =
        parse("move 30 40\nclick left\nkey w\nchord ctrl+z\n", err);
    ASSERT_NOT_NULL(s);
    memset(&h, 0, sizeof(h));
    k = hooks_for(&h);
    input_init(&in);
    ASSERT_TRUE(frame(s, &in, &k)); /* move */
    ASSERT_TRUE(in.has_mouse_pos);
    ASSERT_TRUE(in.mouse_x == 30.0f && in.mouse_y == 40.0f);
    ASSERT_TRUE(frame(s, &in, &k)); /* click: press */
    ASSERT_EQ(in.keys[INPUT_MOUSE_LEFT], 3u);
    ASSERT_TRUE(frame(s, &in, &k)); /* click: release */
    ASSERT_EQ(in.keys[INPUT_MOUSE_LEFT], 1u);
    ASSERT_TRUE(frame(s, &in, &k)); /* key w press */
    ASSERT_EQ(in.keys['w'], 3u);
    ASSERT_TRUE(frame(s, &in, &k)); /* key w release */
    ASSERT_EQ(in.keys['w'], 1u);
    ASSERT_TRUE(frame(s, &in, &k)); /* chord: modifiers down */
    ASSERT_EQ(in.keys[290], 3u);
    ASSERT_EQ(in.keys['z'], 0u);
    ASSERT_TRUE(frame(s, &in, &k)); /* chord: key down, ctrl held */
    ASSERT_EQ(in.keys[290], 2u);
    ASSERT_EQ(in.keys['z'], 3u);
    ASSERT_TRUE(frame(s, &in, &k)); /* chord: all up */
    ASSERT_EQ(in.keys['z'], 1u);
    ASSERT_EQ(in.keys[290], 1u);
    ASSERT_FALSE(frame(s, &in, &k)); /* finished */
    ASSERT_EQ(in.keys['z'], 0u);
    ASSERT_EQ(break_editor_input_script_failures(s), 0u);
    break_editor_input_script_destroy(s);
}

TEST(wait_move_to_scale_and_hooks) {
    char err[128];
    InputState in;
    Hooks h;
    BreakEditorInputScriptHooks k;
    u32 i;
    BreakEditorInputScript *s = parse(
        "wait 3\nmove_to editor-add-button 0.5 0.5\nmove_to missing\n"
        "scroll 2\nscreenshot a.ppm\nexpect entities 1\nexpect tool w\nquit\n"
        "move 1 1\n",
        err);
    ASSERT_NOT_NULL(s);
    memset(&h, 0, sizeof(h));
    h.expect_result = true;
    k = hooks_for(&h);
    input_init(&in);
    for (i = 0; i < 3u; i++) {
        input_new_frame(&in);
        ASSERT_TRUE(break_editor_input_script_step(s, &in, 2.0f, &k));
        ASSERT_FALSE(in.has_mouse_pos);
    }
    input_new_frame(&in);
    ASSERT_TRUE(break_editor_input_script_step(s, &in, 2.0f, &k));
    /* logical (120, 210) times the 2.0 input scale */
    ASSERT_TRUE(in.mouse_x == 240.0f && in.mouse_y == 420.0f);
    input_new_frame(&in);
    ASSERT_TRUE(break_editor_input_script_step(s, &in, 2.0f, &k)); /* missing */
    ASSERT_EQ(break_editor_input_script_failures(s), 1u);
    ASSERT_EQ(break_editor_input_script_first_failure_line(s), 3u);
    ASSERT_TRUE(in.mouse_x == 240.0f); /* unchanged */
    input_new_frame(&in);
    ASSERT_TRUE(break_editor_input_script_step(s, &in, 2.0f, &k));
    ASSERT_TRUE(in.scroll_dy == 2.0f);
    input_new_frame(&in);
    ASSERT_TRUE(break_editor_input_script_step(s, &in, 2.0f, &k));
    ASSERT_EQ(h.screenshots, 1u);
    ASSERT_TRUE(strcmp(h.last, "a.ppm") == 0);
    input_new_frame(&in);
    ASSERT_TRUE(break_editor_input_script_step(s, &in, 2.0f, &k));
    ASSERT_TRUE(strcmp(h.last, "entities 1") == 0);
    h.expect_result = false;
    input_new_frame(&in);
    ASSERT_TRUE(break_editor_input_script_step(s, &in, 2.0f, &k));
    ASSERT_EQ(h.expects, 2u);
    ASSERT_EQ(break_editor_input_script_failures(s), 2u);
    ASSERT_EQ(break_editor_input_script_first_failure_line(s), 3u);
    input_new_frame(&in);
    ASSERT_FALSE(break_editor_input_script_step(s, &in, 2.0f, &k)); /* quit */
    ASSERT_TRUE(break_editor_input_script_quit_requested(s));
    input_new_frame(&in);
    ASSERT_FALSE(break_editor_input_script_step(s, &in, 2.0f, &k));
    ASSERT_TRUE(in.mouse_x == 240.0f); /* nothing after quit runs */
    break_editor_input_script_destroy(s);
}

TEST(null_hooks_count_as_failures_not_crashes) {
    char err[128];
    InputState in;
    BreakEditorInputScript *s =
        parse("move_to x\nexpect y\nscreenshot z\n", err);
    ASSERT_NOT_NULL(s);
    input_init(&in);
    while (frame(s, &in, NULL)) {
    }
    ASSERT_EQ(break_editor_input_script_failures(s), 3u);
    break_editor_input_script_destroy(s);
    ASSERT_FALSE(break_editor_input_script_step(NULL, &in, 1.0f, NULL));
    break_editor_input_script_destroy(NULL);
}

int main(void) {
    printf("=== Running Tests ===\n");
    RUN_TEST(parse_accepts_every_command);
    RUN_TEST(parse_errors_name_the_line);
    RUN_TEST(parse_rejects_too_many_commands);
    RUN_TEST(click_key_and_chord_produce_one_frame_edges);
    RUN_TEST(wait_move_to_scale_and_hooks);
    RUN_TEST(null_hooks_count_as_failures_not_crashes);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n", g_test_pass,
           g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
