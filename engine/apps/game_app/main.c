#include "game_app.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_help(void) {
    puts("Usage: game_app [OPTIONS]\n"
         "  --render record|auto|vulkan|opengl\n"
         "  --audio record|null|device\n"
         "  --assets DIR\n"
         "  --scenario PATH\n"
         "  --checkpoint DIR\n"
         "  --trace PATH\n"
         "  --screenshot PATH\n"
         "  --fixed-step\n"
         "  --frames N\n"
         "  --require-device\n"
         "  --network\n"
         "  --help");
}

static int cli_error(const char *message) {
    fprintf(stderr, "game_app: %s\n", message);
    return 2;
}

static int take_value(int argc, char **argv, int *index, const char *name,
                      const char **out) {
    const char *arg = argv[*index];
    usize length = strlen(name);
    if (strcmp(arg, name) == 0) {
        if (*index + 1 >= argc || argv[*index + 1][0] == '\0') return -1;
        *out = argv[++*index];
        return 1;
    }
    if (strncmp(arg, name, length) == 0 && arg[length] == '=') {
        if (arg[length + 1] == '\0') return -1;
        *out = arg + length + 1;
        return 1;
    }
    return 0;
}

static bool parse_render(const char *value, GameRenderMode *out) {
    if (strcmp(value, "record") == 0) *out = GAME_RENDER_RECORD;
    else if (strcmp(value, "auto") == 0) *out = GAME_RENDER_AUTO;
    else if (strcmp(value, "vulkan") == 0) *out = GAME_RENDER_VULKAN;
    else if (strcmp(value, "opengl") == 0) *out = GAME_RENDER_OPENGL;
    else return false;
    return true;
}

static bool parse_audio(const char *value, GameAudioMode *out) {
    if (strcmp(value, "record") == 0) *out = GAME_AUDIO_RECORD;
    else if (strcmp(value, "null") == 0) *out = GAME_AUDIO_NULL;
    else if (strcmp(value, "device") == 0) *out = GAME_AUDIO_DEVICE;
    else return false;
    return true;
}

static bool parse_frames(const char *value, u32 *out) {
    char *end = NULL;
    unsigned long long parsed;
    for (const char *p = value; *p != '\0'; ++p) {
        if (*p < '0' || *p > '9') return false;
    }
    parsed = strtoull(value, &end, 10);
    if (end == value || *end != '\0' || parsed == 0u || parsed > UINT32_MAX)
        return false;
    *out = (u32)parsed;
    return true;
}

int main(int argc, char **argv) {
    GameAppConfig config = {
        .asset_root = "assets/game_app",
        .render_mode = GAME_RENDER_AUTO,
        .audio_mode = GAME_AUDIO_DEVICE,
    };
    int exit_code = 2;
    BreakRuntimeError result;

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        const char *value = NULL;
        int matched;
        if ((matched = take_value(argc, argv, &i, "--render", &value)) != 0) {
            if (matched < 0 || !parse_render(value, &config.render_mode))
                return cli_error("invalid --render value");
        } else if ((matched = take_value(argc, argv, &i, "--audio", &value)) != 0) {
            if (matched < 0 || !parse_audio(value, &config.audio_mode))
                return cli_error("invalid --audio value");
        } else if ((matched = take_value(argc, argv, &i, "--assets", &value)) != 0) {
            if (matched < 0) return cli_error("--assets requires a nonempty directory");
            config.asset_root = value;
        } else if ((matched = take_value(argc, argv, &i, "--scenario", &value)) != 0) {
            if (matched < 0) return cli_error("--scenario requires a nonempty path");
            config.scenario_path = value;
        } else if ((matched = take_value(argc, argv, &i, "--checkpoint", &value)) != 0) {
            if (matched < 0) return cli_error("--checkpoint requires a nonempty directory");
            config.checkpoint_dir = value;
        } else if ((matched = take_value(argc, argv, &i, "--trace", &value)) != 0) {
            if (matched < 0) return cli_error("--trace requires a nonempty path");
            config.trace_path = value;
        } else if ((matched = take_value(argc, argv, &i, "--screenshot", &value)) != 0) {
            if (matched < 0) return cli_error("--screenshot requires a nonempty path");
            config.screenshot_path = value;
        } else if ((matched = take_value(argc, argv, &i, "--frames", &value)) != 0) {
            if (matched < 0 || !parse_frames(value, &config.max_frames))
                return cli_error("--frames requires a positive 32-bit integer");
        } else if (strcmp(argv[i], "--fixed-step") == 0) {
            config.fixed_step = true;
        } else if (strcmp(argv[i], "--require-device") == 0) {
            config.require_device = true;
        } else if (strcmp(argv[i], "--network") == 0) {
#if GAME_APP_ENABLE_NETWORK
            config.network = true;
#else
            return cli_error("--network is unavailable in this build");
#endif
        } else {
            return cli_error("unknown or malformed argument");
        }
    }

    result = game_app_run(&config, &exit_code);
    if (result != BREAK_RUNTIME_OK)
        fprintf(stderr, "game_app: runtime returned %s\n", break_runtime_error_name(result));
    return exit_code;
}
