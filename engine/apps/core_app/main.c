#include "core_app.h"

#include <core/trace_core_app.h>
#include <platform/time.h>

#if CORE_APP_NET_TRANSPORT
#include "core_app_net_transport.h"

#include <signal.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_help(void) {
    puts("Usage: core_app [OPTIONS]\n"
         "  --render record|auto|vulkan|opengl\n"
         "  --audio record|null|device\n"
         "  --audio-device NAME\n"
         "  --voice off|fake|device\n"
         "  --voice-capture-device NAME\n"
         "  --voice-null-capture\n"
         "  --assets DIR\n"
         "  --scenario PATH\n"
         "  --checkpoint DIR\n"
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

int main(int argc, char **argv) {
    CoreAppConfig config = {
        .asset_root = "assets/core_app",
        .render_mode = CORE_APP_RENDER_AUTO,
        .audio_mode = CORE_APP_AUDIO_DEVICE,
    };
    int exit_code = 2;
    const char *trace_json_path = NULL;
    bool trace_timestamps = false;
    BreakRuntimeError result;
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
    result = core_app_run(&config, &exit_code);
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
