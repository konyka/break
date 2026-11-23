#include "core_app.h"

#if CORE_APP_CRASH_CONTEXT
#include "core_app_diagnostics.h"
#endif

#include <core/trace_core_app.h>
#include <platform/time.h>

#if CORE_APP_NET_TRANSPORT
#include "core_app_net_transport.h"

#include <signal.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#include <windows.h>
#include <shellapi.h>
#endif

static void print_help(void) {
    puts("Usage: core_app [OPTIONS]\n"
         "  --render record|auto|vulkan|opengl\n"
         "  --audio record|null|device\n"
         "  --audio-device NAME\n"
         "  --voice off|fake|device\n"
         "  --voice-capture-device NAME\n"
         "  --voice-null-capture\n"
         "  --voice-aligner-sinc\n"
         "  --voice-aligner-crossfade FRAMES (1..48000)\n"
         "  --assets DIR\n"
         "  --scenario PATH\n"
         "  --checkpoint DIR\n"
         "  --crash-context DIR\n"
         "  --trace PATH\n"
         "  --trace-json PATH\n"
         "  --trace-timestamps\n"
         "  --screenshot PATH\n"
         "  --fixed-step\n"
         "  --frames N\n"
         "  --require-device\n"
         "  --network\n"
#if CORE_APP_NET_TRANSPORT
         "  --bind HOST:PORT\n"
         "  --tls-cert PATH\n"
         "  --tls-key PATH\n"
         "  --psk-env NAME\n"
         "  --port-file PATH\n"
         "  --net-poll-ms 0..100\n"
         "  --voice-relay\n"
#endif
         "  --help");
}

static int cli_error(const char *message) {
    fprintf(stderr, "core_app: %s\n", message);
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

static bool parse_render(const char *value, CoreAppRenderMode *out) {
    if (strcmp(value, "record") == 0) *out = CORE_APP_RENDER_RECORD;
    else if (strcmp(value, "auto") == 0) *out = CORE_APP_RENDER_AUTO;
    else if (strcmp(value, "vulkan") == 0) *out = CORE_APP_RENDER_VULKAN;
    else if (strcmp(value, "opengl") == 0) *out = CORE_APP_RENDER_OPENGL;
    else return false;
    return true;
}

#if CORE_APP_CRASH_CONTEXT
static const char *requested_render_backend(CoreAppRenderMode mode) {
    switch (mode) {
        case CORE_APP_RENDER_RECORD: return "record";
        case CORE_APP_RENDER_VULKAN: return "vulkan";
        case CORE_APP_RENDER_OPENGL: return "opengl";
        case CORE_APP_RENDER_AUTO:
        default: return "auto";
    }
}
#endif

static bool parse_audio(const char *value, CoreAppAudioMode *out) {
    if (strcmp(value, "record") == 0) *out = CORE_APP_AUDIO_RECORD;
    else if (strcmp(value, "null") == 0) *out = CORE_APP_AUDIO_NULL;
    else if (strcmp(value, "device") == 0) *out = CORE_APP_AUDIO_DEVICE;
    else return false;
    return true;
}

static bool parse_voice(const char *value, CoreAppVoiceMode *out) {
    if (strcmp(value, "off") == 0) *out = CORE_APP_VOICE_OFF;
    else if (strcmp(value, "fake") == 0) *out = CORE_APP_VOICE_FAKE;
    else if (strcmp(value, "device") == 0) *out = CORE_APP_VOICE_DEVICE;
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

/* Rewrites the finished text trace as a break.trace Chrome JSON document. */
static bool write_trace_json(const char *trace_path, const char *json_path) {
    bool ok = false;
    char *text = NULL;
    char *json = NULL;
    long size = -1;
    FILE *in = fopen(trace_path, "rb");
    if (!in) return false;
    if (fseek(in, 0, SEEK_END) == 0) size = ftell(in);
    if (size >= 0 && fseek(in, 0, SEEK_SET) == 0) text = malloc((usize)size + 1u);
    if (text && fread(text, 1u, (usize)size, in) == (usize)size) {
        BreakTraceCoreAppReport report;
        if (break_trace_core_app_to_chrome(text, (usize)size, NULL, 0u, &report) ==
                BREAK_TRACE_CONVERT_TOO_SMALL &&
            (json = malloc((usize)report.bytes + 1u)) != NULL &&
            break_trace_core_app_to_chrome(text, (usize)size, json, (usize)report.bytes + 1u,
                                           &report) == BREAK_TRACE_CONVERT_OK) {
            FILE *out = fopen(json_path, "wb");
            if (out) {
                ok = fwrite(json, 1u, (usize)report.bytes, out) == (usize)report.bytes;
                ok = fclose(out) == 0 && ok;
            }
        }
    }
    fclose(in);
    free(json);
    free(text);
    return ok;
}

#if CORE_APP_NET_TRANSPORT
/* One to three decimal digits, at most 100. Unlike --frames, zero (also
 * written "00" or "000") is valid: it means no pacing. */
static bool parse_poll_ms(const char *value, u32 *out) {
    u32 parsed = 0u;
    usize length = 0u;
    for (const char *p = value; *p != '\0'; ++p, ++length) {
        if (*p < '0' || *p > '9' || length >= 3u) return false;
        parsed = parsed * 10u + (u32)(*p - '0');
    }
    if (length == 0u || parsed > 100u) return false;
    *out = parsed;
    return true;
}
#endif

static int core_app_main(int argc, char **argv) {
    CoreAppConfig config = {
        .asset_root = "assets/core_app",
        .render_mode = CORE_APP_RENDER_AUTO,
        .audio_mode = CORE_APP_AUDIO_DEVICE,
    };
    int exit_code = 2;
    const char *trace_json_path = NULL;
    bool trace_timestamps = false;
    BreakRuntimeError result;
#if CORE_APP_CRASH_CONTEXT
    const char *crash_context = NULL;
    CoreAppDiagnosticsHooks diagnostics_hooks = {0};
    bool diagnostics_started = false;
#endif
#if CORE_APP_NET_TRANSPORT
    CoreAppNetTransportConfig net_config = {0};
    CoreAppNetTransport *transport = NULL;
    CoreAppNetworkHooks net_hooks;
    bool net_option_seen = false;
#endif

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
        } else if ((matched = take_value(argc, argv, &i, "--audio-device", &value)) != 0) {
            if (matched < 0) return cli_error("--audio-device requires a nonempty name");
            config.audio_device_name = value;
        } else if ((matched = take_value(argc, argv, &i, "--voice-capture-device", &value)) !=
                   0) {
            if (matched < 0) return cli_error("--voice-capture-device requires a nonempty name");
            config.voice_capture_device_name = value;
        } else if (strcmp(argv[i], "--voice-null-capture") == 0) {
            config.voice_null_capture = true;
        } else if (strcmp(argv[i], "--voice-aligner-sinc") == 0) {
            config.voice_aligner_sinc = true;
        } else if ((matched = take_value(argc, argv, &i, "--voice-aligner-crossfade", &value)) !=
                   0) {
            if (matched < 0 || !parse_frames(value, &config.voice_aligner_crossfade_frames) ||
                config.voice_aligner_crossfade_frames > 48000u)
                return cli_error("invalid --voice-aligner-crossfade value");
        } else if ((matched = take_value(argc, argv, &i, "--voice", &value)) != 0) {
            if (matched < 0 || !parse_voice(value, &config.voice_mode))
                return cli_error("invalid --voice value");
        } else if ((matched = take_value(argc, argv, &i, "--assets", &value)) != 0) {
            if (matched < 0) return cli_error("--assets requires a nonempty directory");
            config.asset_root = value;
        } else if ((matched = take_value(argc, argv, &i, "--scenario", &value)) != 0) {
            if (matched < 0) return cli_error("--scenario requires a nonempty path");
            config.scenario_path = value;
        } else if ((matched = take_value(argc, argv, &i, "--checkpoint", &value)) != 0) {
            if (matched < 0) return cli_error("--checkpoint requires a nonempty directory");
            config.checkpoint_dir = value;
        } else if ((matched = take_value(argc, argv, &i, "--crash-context", &value)) != 0) {
            if (matched < 0) return cli_error("--crash-context requires a nonempty directory");
#if CORE_APP_CRASH_CONTEXT
            crash_context = value;
#else
            return cli_error("--crash-context is unavailable in this build");
#endif
        } else if ((matched = take_value(argc, argv, &i, "--trace", &value)) != 0) {
            if (matched < 0) return cli_error("--trace requires a nonempty path");
            config.trace_path = value;
        } else if ((matched = take_value(argc, argv, &i, "--trace-json", &value)) != 0) {
            if (matched < 0) return cli_error("--trace-json requires a nonempty path");
            trace_json_path = value;
        } else if ((matched = take_value(argc, argv, &i, "--screenshot", &value)) != 0) {
            if (matched < 0) return cli_error("--screenshot requires a nonempty path");
            config.screenshot_path = value;
        } else if ((matched = take_value(argc, argv, &i, "--frames", &value)) != 0) {
            if (matched < 0 || !parse_frames(value, &config.max_frames))
                return cli_error("--frames requires a positive 32-bit integer");
#if CORE_APP_NET_TRANSPORT
        } else if ((matched = take_value(argc, argv, &i, "--bind", &value)) != 0) {
            if (matched < 0) return cli_error("--bind requires HOST:PORT");
            net_config.bind = value;
            net_option_seen = true;
        } else if ((matched = take_value(argc, argv, &i, "--tls-cert", &value)) != 0) {
            if (matched < 0) return cli_error("--tls-cert requires a nonempty path");
            net_config.tls_cert = value;
            net_option_seen = true;
        } else if ((matched = take_value(argc, argv, &i, "--tls-key", &value)) != 0) {
            if (matched < 0) return cli_error("--tls-key requires a nonempty path");
            net_config.tls_key = value;
            net_option_seen = true;
        } else if ((matched = take_value(argc, argv, &i, "--psk-env", &value)) != 0) {
            if (matched < 0) return cli_error("--psk-env requires a variable name");
            net_config.psk_env = value;
            net_option_seen = true;
        } else if ((matched = take_value(argc, argv, &i, "--port-file", &value)) != 0) {
            if (matched < 0) return cli_error("--port-file requires a nonempty path");
            net_config.port_file = value;
            net_option_seen = true;
        } else if ((matched = take_value(argc, argv, &i, "--net-poll-ms", &value)) != 0) {
            u32 poll_ms = 0u;
            if (matched < 0 || !parse_poll_ms(value, &poll_ms))
                return cli_error("--net-poll-ms requires 0..100");
            net_config.poll_ms = poll_ms;
            net_option_seen = true;
        } else if (strcmp(argv[i], "--voice-relay") == 0) {
            net_config.voice_relay = true;
            net_option_seen = true;
#endif
        } else if (strcmp(argv[i], "--trace-timestamps") == 0) {
            trace_timestamps = true;
        } else if (strcmp(argv[i], "--fixed-step") == 0) {
            config.fixed_step = true;
        } else if (strcmp(argv[i], "--require-device") == 0) {
            config.require_device = true;
        } else if (strcmp(argv[i], "--network") == 0) {
#if CORE_APP_ENABLE_NETWORK
            config.network = true;
#else
            return cli_error("--network is unavailable in this build");
#endif
        } else {
            return cli_error("unknown or malformed argument");
        }
    }
    if (config.voice_mode == CORE_APP_VOICE_DEVICE && config.audio_mode != CORE_APP_AUDIO_DEVICE)
        return cli_error("--voice=device requires --audio=device");
    if ((config.voice_aligner_sinc || config.voice_aligner_crossfade_frames > 0u) &&
        config.voice_mode == CORE_APP_VOICE_OFF)
        return cli_error("--voice-aligner-sinc/--voice-aligner-crossfade require --voice=fake|device");
    if (config.voice_null_capture && config.voice_mode != CORE_APP_VOICE_DEVICE)
        return cli_error("--voice-null-capture requires --voice=device");
    if (config.audio_device_name && config.audio_mode != CORE_APP_AUDIO_DEVICE)
        return cli_error("--audio-device requires --audio=device");
    if (config.voice_capture_device_name && config.voice_mode != CORE_APP_VOICE_DEVICE)
        return cli_error("--voice-capture-device requires --voice=device");
    if (config.voice_capture_device_name && config.voice_null_capture)
        return cli_error("--voice-capture-device conflicts with --voice-null-capture");
    if (trace_json_path && !config.trace_path)
        return cli_error("--trace-json requires --trace");
    if (trace_timestamps && !config.trace_path)
        return cli_error("--trace-timestamps requires --trace");
    if (trace_timestamps) {
        time_init();
        break_trace_core_app_set_clock(time_microseconds);
    }

#if CORE_APP_NET_TRANSPORT
    if (net_option_seen && !config.network)
        return cli_error("network options require --network");
    if (config.network) {
        char host[64];
        u16 port = 0u;
        if (!net_config.bind || !net_config.tls_cert || !net_config.tls_key ||
            !net_config.psk_env || !net_config.port_file) {
            return cli_error(
                "--network requires --bind, --tls-cert, --tls-key, --psk-env and --port-file");
        }
        if (!core_app_net_parse_bind(net_config.bind, host, sizeof(host), &port))
            return cli_error("invalid --bind value");
        /* A write to a peer that already closed must fail with EPIPE and be
         * counted by the session layer instead of killing the process. */
#ifdef SIGPIPE
        signal(SIGPIPE, SIG_IGN);
#endif
        transport = core_app_net_transport_create(&net_config);
        if (!transport) return cli_error("invalid network configuration");
        core_app_net_transport_hooks(transport, &net_hooks);
        config.network_hooks = &net_hooks;
    }
#endif
#if CORE_APP_CRASH_CONTEXT
    if (crash_context) {
        CoreAppDiagnosticsSnapshot initial_snapshot;
        memset(&initial_snapshot, 0, sizeof(initial_snapshot));
        initial_snapshot.rhi_backend = requested_render_backend(config.render_mode);
        initial_snapshot.gpu_name = "pending";
        diagnostics_hooks.publish = core_app_diagnostics_publish;
        config.diagnostics = &diagnostics_hooks;
        if (!core_app_diagnostics_start(crash_context)) {
#if CORE_APP_NET_TRANSPORT
            core_app_net_transport_free(transport);
#endif
            return cli_error("could not start --crash-context");
        }
        diagnostics_started = true;
        core_app_diagnostics_publish(diagnostics_hooks.user, &initial_snapshot);
    }
#endif
    result = core_app_run(&config, &exit_code);
#if CORE_APP_CRASH_CONTEXT
    if (diagnostics_started) core_app_diagnostics_stop();
#endif
#if CORE_APP_NET_TRANSPORT
    core_app_net_transport_free(transport);
#endif
    if (result != BREAK_RUNTIME_OK)
        fprintf(stderr, "core_app: runtime returned %s\n", break_runtime_error_name(result));
    if (trace_json_path && !write_trace_json(config.trace_path, trace_json_path)) {
        fprintf(stderr, "core_app: could not write --trace-json %s\n", trace_json_path);
        if (exit_code == 0) exit_code = 2;
    }
    return exit_code;
}

#if defined(_WIN32)
static bool windows_device_name_arg(char **argv, int index) {
    const char *arg = argv[index];
    if (index > 0 &&
        (strcmp(argv[index - 1], "--audio-device") == 0 ||
         strcmp(argv[index - 1], "--voice-capture-device") == 0)) {
        return true;
    }
    return strncmp(arg, "--audio-device=", sizeof("--audio-device=") - 1u) == 0 ||
           strncmp(arg, "--voice-capture-device=",
                   sizeof("--voice-capture-device=") - 1u) == 0;
}

static char *windows_utf8_arg(const wchar_t *arg) {
    int size = WideCharToMultiByte(CP_UTF8, 0, arg, -1, NULL, 0, NULL, NULL);
    char *result;
    if (size <= 0) return NULL;
    result = malloc((usize)size);
    if (!result) return NULL;
    if (WideCharToMultiByte(CP_UTF8, 0, arg, -1, result, size, NULL, NULL) != size) {
        free(result);
        return NULL;
    }
    return result;
}

int main(int argc, char **argv) {
    int wide_argc = 0;
    int i;
    int exit_code = 2;
    bool needed = false;
    LPWSTR *wide_argv;
    char **args;
    for (i = 0; i < argc; ++i) {
        if (windows_device_name_arg(argv, i)) {
            needed = true;
            break;
        }
    }
    if (!needed) return core_app_main(argc, argv);
    wide_argv = CommandLineToArgvW(GetCommandLineW(), &wide_argc);
    if (!wide_argv) return cli_error("could not read the Windows command line");
    if (wide_argc != argc) {
        LocalFree(wide_argv);
        return cli_error("could not match the Windows command line");
    }
    args = malloc(((usize)argc + 1u) * sizeof(*args));
    if (!args) {
        LocalFree(wide_argv);
        return cli_error("could not allocate the Windows command line");
    }
    memcpy(args, argv, ((usize)argc + 1u) * sizeof(*args));
    for (i = 0; i < argc; ++i) {
        if (!windows_device_name_arg(argv, i)) continue;
        args[i] = windows_utf8_arg(wide_argv[i]);
        if (!args[i]) break;
    }
    if (i == argc) {
        exit_code = core_app_main(argc, args);
    } else {
        cli_error("could not convert the Windows audio device name to UTF-8");
    }
    for (i = 0; i < argc; ++i) {
        if (args[i] != argv[i]) free(args[i]);
    }
    free(args);
    LocalFree(wide_argv);
    return exit_code;
}
#else
int main(int argc, char **argv) {
    return core_app_main(argc, argv);
}
#endif
