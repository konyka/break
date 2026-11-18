#include "test_framework.h"

#include "../apps/core_app/core_app_net_transport.h"

#include <network/break_net_adapter.h>
#include <network/break_online_voice.h>

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#ifndef CORE_APP_TEST_SSL_FIXTURE_DIR
#error "CORE_APP_TEST_SSL_FIXTURE_DIR must be defined by the build system"
#endif
#define CORE_APP_TEST_STR2(x) #x
#define CORE_APP_TEST_STR(x) CORE_APP_TEST_STR2(x)

static const char k_psk_env[] = "CORE_APP_NET_TRANSPORT_TEST_PSK";
static const char k_psk_hex[] =
    "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";

typedef struct StepThreadArgs {
    BreakNetReactor *reactor;
    bool result;
} StepThreadArgs;

static void *step_thread_main(void *arg) {
    StepThreadArgs *args = (StepThreadArgs *)arg;
    args->result = break_net_reactor_step(args->reactor, 0);
    return NULL;
}

static bool file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0;
}

static bool trace_contains(FILE *trace, const char *needle) {
    char text[4096];
    usize length;
    fflush(trace);
    rewind(trace);
    length = fread(text, 1u, sizeof(text) - 1u, trace);
    text[length] = '\0';
    return strstr(text, needle) != NULL;
}

/* The reactor stop gives up after 1000 ms while another thread is still
 * inside a step. destroy must report TIMEOUT, keep the reactor and the
 * acceptor alive for that step, still clear the auth hook and the port file,
 * and answer every later call with TIMEOUT without touching them again. */
TEST(destroy_reports_stop_timeout_and_keeps_the_reactor) {
    const char *fixtures = CORE_APP_TEST_STR(CORE_APP_TEST_SSL_FIXTURE_DIR);
    char cert[512], key[512], port_file[256];
    CoreAppNetTransportConfig config;
    CoreAppNetworkHooks hooks;
    StepThreadArgs args;
    pthread_t thread;
    FILE *trace = tmpfile();
    snprintf(cert, sizeof(cert), "%s/snow_test_cert.pem", fixtures);
    snprintf(key, sizeof(key), "%s/snow_test_key.pem", fixtures);
    test_tmp(port_file, sizeof(port_file), "core_app_net_transport.port");
    (void)remove(port_file);
    ASSERT_NOT_NULL(trace);
    ASSERT_EQ(TEST_SETENV(k_psk_env, k_psk_hex), 0);

    memset(&config, 0, sizeof(config));
    config.bind = "127.0.0.1:0";
    config.tls_cert = cert;
    config.tls_key = key;
    config.psk_env = k_psk_env;
    config.port_file = port_file;
    CoreAppNetTransport *transport = core_app_net_transport_create(&config);
    ASSERT_NOT_NULL(transport);
    core_app_net_transport_hooks(transport, &hooks);
    ASSERT_EQ(hooks.start(hooks.user, trace), BREAK_RUNTIME_OK);
    ASSERT_TRUE(file_exists(port_file));

    BreakNetReactor *reactor = core_app_net_transport_reactor_for_test(transport);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_step_delay_for_test(reactor, 1500u));
    memset(&args, 0, sizeof(args));
    args.reactor = reactor;
    ASSERT_EQ(pthread_create(&thread, NULL, step_thread_main, &args), 0);
    struct timespec pause = {0, 50000000L};
    nanosleep(&pause, NULL);

    ASSERT_EQ(hooks.destroy(hooks.user), BREAK_RUNTIME_TIMEOUT);
    ASSERT_TRUE(trace_contains(trace, "event=network result=stop_timeout"));
    ASSERT_FALSE(file_exists(port_file));
    ASSERT_TRUE(core_app_net_transport_reactor_for_test(transport) == reactor);
    ASSERT_TRUE(break_net_reactor_stop_pending_for_test(reactor));
    ASSERT_EQ(hooks.destroy(hooks.user), BREAK_RUNTIME_TIMEOUT);
    core_app_net_transport_free(transport);
    ASSERT_TRUE(core_app_net_transport_reactor_for_test(transport) == reactor);

    ASSERT_EQ(pthread_join(thread, NULL), 0);
    ASSERT_TRUE(core_app_net_transport_reclaim_for_test(transport));
    fclose(trace);
}

/* A NULL frame and a frame the encoder rejects are counted as invalid
 * while producing; a valid frame with no peer sends nothing; after
 * stop_producers a frame is skipped before it is encoded. */
TEST(voice_frame_counts_invalid_and_skipped_frames) {
    const char *fixtures = CORE_APP_TEST_STR(CORE_APP_TEST_SSL_FIXTURE_DIR);
    char cert[512], key[512], port_file[256];
    CoreAppNetTransportConfig config;
    CoreAppNetworkHooks hooks;
    BreakVoiceFrame frame;
    FILE *trace = tmpfile();
    snprintf(cert, sizeof(cert), "%s/snow_test_cert.pem", fixtures);
    snprintf(key, sizeof(key), "%s/snow_test_key.pem", fixtures);
    test_tmp(port_file, sizeof(port_file), "core_app_net_transport_voice.port");
    (void)remove(port_file);
    ASSERT_NOT_NULL(trace);
    ASSERT_EQ(TEST_SETENV(k_psk_env, k_psk_hex), 0);
    memset(&config, 0, sizeof(config));
    config.bind = "127.0.0.1:0";
    config.tls_cert = cert;
    config.tls_key = key;
    config.psk_env = k_psk_env;
    config.port_file = port_file;
    CoreAppNetTransport *transport = core_app_net_transport_create(&config);
    ASSERT_NOT_NULL(transport);
    core_app_net_transport_hooks(transport, &hooks);
    ASSERT_NOT_NULL(hooks.voice_frame);
    ASSERT_EQ(hooks.start(hooks.user, trace), BREAK_RUNTIME_OK);

    memset(&frame, 0, sizeof(frame));
    frame.sample_rate = 48000u;
    frame.channels = 1u;
    frame.sample_count = BREAK_VOICE_MAX_SAMPLES;
    hooks.voice_frame(hooks.user, NULL);
    BreakVoiceFrame bad = frame;
    bad.sample_count = 0u;
    hooks.voice_frame(hooks.user, &bad);
    hooks.voice_frame(hooks.user, &frame);
    ASSERT_EQ(hooks.stop_admission(hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(hooks.stop_producers(hooks.user), BREAK_RUNTIME_OK);
    hooks.voice_frame(hooks.user, &bad);
    hooks.voice_frame(hooks.user, &frame);
    ASSERT_EQ(hooks.drain(hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(hooks.destroy(hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(trace_contains(trace,
        "voice_frames_sent=0 voice_frames_skipped=2 voice_frames_invalid=2\n"));
    core_app_net_transport_free(transport);
    fclose(trace);
}

TEST_MAIN_BEGIN()
    RUN_TEST(destroy_reports_stop_timeout_and_keeps_the_reactor);
    RUN_TEST(voice_frame_counts_invalid_and_skipped_frames);
TEST_MAIN_END()
