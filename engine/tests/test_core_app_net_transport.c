#include "test_framework.h"

#include "../apps/core_app/core_app_net_transport.h"

#include <network/break_net_adapter.h>
#include <network/break_online_voice.h>
#include <runtime/runtime_bus.h>
#include <runtime/runtime_queue.h>

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
        "voice_frames_sent=0 voice_frames_skipped=2 voice_frames_invalid=2"
        " voice_frames_received=0 voice_frames_played=0 voice_frames_concealed=0"
        " voice_frames_dropped=0 voice_peak=0 voice_frames_relayed=0 voice_relay_dropped=0"
        " voice_mute_requests=0 voice_mute_rejected=0 voice_frames_muted=0"
        " voice_frames_rate_limited=0\n"));
    core_app_net_transport_free(transport);
    fclose(trace);
}

/* Every reactor event becomes one notice on an attached bus, whether the
 * reactor queued it or had to drop it; the notice carries the event's
 * identity and correlation id, never the payload. */
static bool net_next_notice(BreakRuntimeQueue *queue, CoreAppNetEventNotice *out) {
    BreakRuntimeOwnedMessage *m = NULL;
    BreakRuntimeMessageView view;
    bool ok;
    if (break_runtime_queue_poll(queue, &m) != BREAK_RUNTIME_OK || !m) return false;
    ok = break_runtime_message_view(m, &view) == BREAK_RUNTIME_OK &&
         view.kind == CORE_APP_NET_EVENT_KIND &&
         core_app_net_event_notice_decode(view.data, view.size, out) &&
         view.correlation_id == out->correlation_id;
    break_runtime_message_release(m);
    return ok;
}

TEST(reactor_events_are_published_on_the_bus) {
    const char *fixtures = CORE_APP_TEST_STR(CORE_APP_TEST_SSL_FIXTURE_DIR);
    char cert[512], key[512], port_file[256];
    CoreAppNetTransportConfig config;
    CoreAppNetworkHooks hooks;
    CoreAppNetEventNotice notice;
    CoreAppNetEventStats stats;
    BreakRuntimeBus *bus = NULL;
    BreakRuntimeQueue *queue = NULL;
    u32 sub = 0u;
    const BreakRuntimeQueueConfig queue_config = {2u, 0u};
    const u16 kind = CORE_APP_NET_EVENT_KIND;
    const unsigned char payload[3] = {1u, 2u, 3u};
    FILE *trace = tmpfile();
    snprintf(cert, sizeof(cert), "%s/snow_test_cert.pem", fixtures);
    snprintf(key, sizeof(key), "%s/snow_test_key.pem", fixtures);
    test_tmp(port_file, sizeof(port_file), "core_app_net_transport_bus.port");
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
    ASSERT_EQ(break_runtime_bus_create(&bus), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_queue_create(&queue_config, &queue), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_net_transport_attach_bus(NULL, bus), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_net_transport_attach_bus(transport, bus), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_subscribe(bus, "core_app.net", queue, &kind, 1u, &sub),
              BREAK_RUNTIME_OK);
    core_app_net_transport_hooks(transport, &hooks);
    ASSERT_EQ(hooks.start(hooks.user, trace), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_net_transport_attach_bus(transport, NULL), BREAK_RUNTIME_REJECTED);

    BreakNetReactor *reactor = core_app_net_transport_reactor_for_test(transport);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(reactor, 41u));
    ASSERT_TRUE(break_net_reactor_enqueue_correlated_message_for_test(
        reactor, 41u, 77u, 1u, 0x5150u, payload, sizeof(payload)));
    ASSERT_TRUE(net_next_notice(queue, &notice));
    ASSERT_EQ(notice.type, (u32)BREAK_NET_EVENT_CONNECTION_OPENED);
    ASSERT_EQ(notice.connection_key, 41u);
    ASSERT_TRUE(notice.queued);
    ASSERT_EQ(notice.correlation_id, 0u);
    ASSERT_TRUE(net_next_notice(queue, &notice));
    ASSERT_EQ(notice.type, (u32)BREAK_NET_EVENT_MESSAGE_RECEIVED);
    ASSERT_EQ(notice.connection_key, 41u);
    ASSERT_EQ(notice.message_id, 77u);
    ASSERT_EQ(notice.correlation_id, 0x5150u);
    ASSERT_EQ(notice.payload_size, 3u);
    ASSERT_FALSE(net_next_notice(queue, &notice));

    /* a full subscriber queue drops notices without waiting */
    for (u32 i = 0; i < 4u; i++)
        ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(reactor, 100u + i));
    ASSERT_EQ(core_app_net_transport_event_stats(transport, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.published, 4u);
    ASSERT_EQ(stats.undelivered, 2u);
    while (net_next_notice(queue, &notice)) {}

    ASSERT_EQ(hooks.stop_admission(hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(hooks.stop_producers(hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(hooks.drain(hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(hooks.destroy(hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(trace_contains(trace, "net_events_published=4 net_events_undelivered=2"));
    core_app_net_transport_free(transport);
    (void)break_runtime_bus_unsubscribe(bus, sub);
    break_runtime_queue_destroy(queue);
    break_runtime_bus_destroy(bus);
    fclose(trace);
}

/* A kind registered with other parameters is refused. */
TEST(attach_bus_rejects_a_conflicting_kind) {
    CoreAppNetTransportConfig config;
    BreakRuntimeBus *bus = NULL;
    const BreakRuntimeBusKind other = {CORE_APP_NET_EVENT_KIND, 9u, 8u, "other", false, 0u};
    memset(&config, 0, sizeof(config));
    config.bind = "127.0.0.1:0";
    config.tls_cert = "c";
    config.tls_key = "k";
    config.psk_env = k_psk_env;
    config.port_file = "p";
    CoreAppNetTransport *transport = core_app_net_transport_create(&config);
    ASSERT_NOT_NULL(transport);
    ASSERT_EQ(break_runtime_bus_create(&bus), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_register_kind(bus, &other), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_net_transport_attach_bus(transport, bus), BREAK_RUNTIME_REJECTED);
    core_app_net_transport_free(transport);
    break_runtime_bus_destroy(bus);
}

TEST_MAIN_BEGIN()
    RUN_TEST(destroy_reports_stop_timeout_and_keeps_the_reactor);
    RUN_TEST(voice_frame_counts_invalid_and_skipped_frames);
    RUN_TEST(reactor_events_are_published_on_the_bus);
    RUN_TEST(attach_bus_rejects_a_conflicting_kind);
TEST_MAIN_END()
