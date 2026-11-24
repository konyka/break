#include "test_framework.h"

#include "../apps/core_app/core_app_net_transport.h"

#include <network/break_net_adapter.h>
#include <network/break_net_message.h>
#include <network/break_net_message_registry.h>
#include <network/break_online_aspect_replication.h>
#include <network/break_online_aspect_session.h>
#include <network/break_online_voice.h>
#include <network/break_replication_wire.h>
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

typedef struct AspectTransportFixture {
    CoreAppNetTransportConfig config;
    CoreAppNetTransport *transport;
    CoreAppNetworkHooks hooks;
    BreakNetReactor *reactor;
    FILE *trace;
    char cert[512];
    char key[512];
    char port_file[256];
    u32 tick;
} AspectTransportFixture;

static bool aspect_fixture_start(AspectTransportFixture *fixture, const char *name,
                                 bool enabled) {
    const char *fixtures = CORE_APP_TEST_STR(CORE_APP_TEST_SSL_FIXTURE_DIR);
    memset(fixture, 0, sizeof(*fixture));
    snprintf(fixture->cert, sizeof(fixture->cert), "%s/snow_test_cert.pem", fixtures);
    snprintf(fixture->key, sizeof(fixture->key), "%s/snow_test_key.pem", fixtures);
    test_tmp(fixture->port_file, sizeof(fixture->port_file), name);
    (void)remove(fixture->port_file);
    fixture->trace = tmpfile();
    if (!fixture->trace || TEST_SETENV(k_psk_env, k_psk_hex) != 0) return false;
    fixture->config.bind = "127.0.0.1:0";
    fixture->config.tls_cert = fixture->cert;
    fixture->config.tls_key = fixture->key;
    fixture->config.psk_env = k_psk_env;
    fixture->config.port_file = fixture->port_file;
    fixture->config.aspect_replication = enabled;
    fixture->transport = core_app_net_transport_create(&fixture->config);
    if (!fixture->transport) return false;
    core_app_net_transport_hooks(fixture->transport, &fixture->hooks);
    if (fixture->hooks.start(fixture->hooks.user, fixture->trace) != BREAK_RUNTIME_OK) return false;
    fixture->reactor = core_app_net_transport_reactor_for_test(fixture->transport);
    return fixture->reactor != NULL;
}

static void aspect_fixture_dispose(AspectTransportFixture *fixture) {
    core_app_net_transport_free(fixture->transport);
    fixture->transport = NULL;
    if (fixture->trace) fclose(fixture->trace);
    fixture->trace = NULL;
    (void)remove(fixture->port_file);
}

static void aspect_fixture_tick(AspectTransportFixture *fixture) {
    const CoreAppSnapshotEntity entities[2] = {
        {7u, 3u, 1.5f, -2.0f, 3.25f, 11u},
        {8u, 4u, -4.0f, 5.5f, 6.0f, 22u},
    };
    fixture->tick++;
    fixture->hooks.tick(fixture->hooks.user, fixture->tick, 9u, entities, 2u, 0u);
}

static bool aspect_fixture_open(AspectTransportFixture *fixture, BreakConnectionKey key) {
    if (!break_net_reactor_enqueue_opened_for_test(fixture->reactor, key)) return false;
    aspect_fixture_tick(fixture);
    CoreAppNetAspectTestView view;
    return core_app_net_transport_aspect_for_test(fixture->transport, &view) &&
           view.open_count == 1u;
}

static bool aspect_queue_packet(AspectTransportFixture *fixture, BreakConnectionKey key,
                                u64 delta_id, usize fragment_size, bool first_only) {
    CoreAppNetAspectTestView view;
    BreakReplicationFragment *fragments = NULL;
    usize fragment_count = 0u;
    u8 packet[2048];
    usize packet_size = 0u;
    bool handled = true;
    if (!core_app_net_transport_aspect_for_test(fixture->transport, &view) || !view.created)
        return false;
    if (break_aspect_encode_with_epoch(
            view.authoritative, view.objects[0],
            break_aspect_active_mask(view.authoritative, view.objects[0]),
            BREAK_ASPECT_BASELINE, 1u, packet, sizeof(packet), &packet_size) != BREAK_RUNTIME_OK ||
        break_replication_fragment_payload(
            delta_id, break_aspect_schema_hash(view.authoritative), packet, packet_size,
            fragment_size, &fragments, &fragment_count) != BREAK_REPLICATION_FRAGMENT_OK) {
        return false;
    }
    for (usize i = 0u; i < fragment_count; ++i) {
        u8 wire[BREAK_REPLICATION_WIRE_HEADER_SIZE + 2048u];
        usize wire_size = 0u;
        BreakNetOwnedMessage message;
        memset(&message, 0, sizeof(message));
        if (break_replication_wire_encode(&fragments[i], wire, sizeof(wire), &wire_size) !=
            BREAK_REPLICATION_FRAGMENT_OK) {
            handled = false;
            break;
        }
        message.message_id = BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT;
        message.protocol_version = BREAK_REPLICATION_WIRE_VERSION;
        message.sequence = (u32)delta_id;
        message.data = wire;
        message.size = wire_size;
        if (!break_replication_session_handle_message(
                key, &message, break_aspect_session_bridge(view.session))) {
            handled = false;
            break;
        }
        if (first_only) break;
    }
    break_replication_fragments_free(fragments, fragment_count);
    return handled;
}

TEST(aspect_transport_default_off_creates_no_state_or_trace) {
    AspectTransportFixture fixture;
    CoreAppNetAspectTestView view;
    ASSERT_TRUE(aspect_fixture_start(&fixture, "core_app_aspect_default.port", false));
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &view));
    ASSERT_FALSE(view.enabled);
    ASSERT_FALSE(view.created);
    ASSERT_TRUE(view.authoritative == NULL);
    ASSERT_TRUE(view.inbound == NULL);
    ASSERT_TRUE(view.replication == NULL);
    ASSERT_TRUE(view.session == NULL);
    ASSERT_TRUE(view.spatial_index == NULL);
    ASSERT_EQ(view.open_count, 0u);
    ASSERT_EQ(view.scope_count, 0u);
    ASSERT_EQ(fixture.hooks.stop_admission(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.stop_producers(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.drain(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(trace_contains(fixture.trace, "event=network_stats"));
    ASSERT_FALSE(trace_contains(fixture.trace, "event=network_aspect_stats"));
    aspect_fixture_dispose(&fixture);
}

TEST(aspect_transport_open_copies_fixed_pod_objects) {
    AspectTransportFixture fixture;
    CoreAppNetAspectTestView view;
    BreakAspectSessionStats stats;
    u32 unsigned_value = 0u;
    f32 float_value = 0.0f;
    ASSERT_TRUE(aspect_fixture_start(&fixture, "core_app_aspect_open.port", true));
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &view));
    ASSERT_TRUE(view.enabled);
    ASSERT_TRUE(view.created);
    ASSERT_NOT_NULL(view.authoritative);
    ASSERT_NOT_NULL(view.inbound);
    ASSERT_NOT_NULL(view.replication);
    ASSERT_NOT_NULL(view.session);
    ASSERT_NOT_NULL(view.spatial_index);
    ASSERT_EQ(view.objects[0].index, 1u);
    ASSERT_EQ(view.objects[0].generation, 1u);
    ASSERT_EQ(view.objects[1].index, 2u);
    ASSERT_EQ(view.objects[1].generation, 1u);
    ASSERT_NEQ(break_aspect_schema_hash(view.authoritative), 0u);
    ASSERT_EQ(break_aspect_schema_hash(view.authoritative),
              break_aspect_schema_hash(view.inbound));
    ASSERT_TRUE(aspect_fixture_open(&fixture, 0x1409u));
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &view));
    break_aspect_session_stats(view.session, &stats);
    ASSERT_EQ(stats.bridge.connections, 1u);
    ASSERT_EQ(break_aspect_replication_connection_count(view.replication), 1u);
    ASSERT_EQ(view.opened, 1u);
    ASSERT_EQ(view.closed, 0u);
    ASSERT_EQ(break_aspect_get_u32(view.authoritative, view.objects[0], 1u, &unsigned_value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(unsigned_value, 7u);
    ASSERT_EQ(break_aspect_get_u32(view.authoritative, view.objects[0], 2u, &unsigned_value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(unsigned_value, 3u);
    ASSERT_EQ(break_aspect_get_f32(view.authoritative, view.objects[0], 3u, &float_value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(float_value, 1.5f);
    ASSERT_EQ(break_aspect_get_f32(view.authoritative, view.objects[1], 5u, &float_value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(float_value, 6.0f);
    ASSERT_EQ(break_aspect_get_u32(view.authoritative, view.objects[1], 6u, &unsigned_value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(unsigned_value, 22u);
    ASSERT_EQ(fixture.hooks.stop_admission(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.stop_producers(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.drain(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_OK);
    aspect_fixture_dispose(&fixture);
}

TEST(aspect_transport_tick_and_shutdown_drain_only_fill_diagnostic_store) {
    AspectTransportFixture fixture;
    CoreAppNetAspectTestView view;
    BreakAspectSessionStats stats;
    u64 authoritative_revision;
    u32 index = 0u;
    ASSERT_TRUE(aspect_fixture_start(&fixture, "core_app_aspect_drain.port", true));
    ASSERT_TRUE(aspect_fixture_open(&fixture, 0x2409u));
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &view));
    authoritative_revision = break_aspect_object_revision(view.authoritative, view.objects[0]);
    ASSERT_TRUE(aspect_queue_packet(&fixture, 0x2409u, 1u, 512u, false));
    break_aspect_session_stats(view.session, &stats);
    ASSERT_EQ(stats.bridge.completion_count, 1u);
    ASSERT_EQ(stats.applied_packets, 0u);
    aspect_fixture_tick(&fixture);
    break_aspect_session_stats(view.session, &stats);
    ASSERT_EQ(stats.applied_packets, 1u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.drained_packets, 1u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    ASSERT_EQ(break_aspect_get_u32(view.inbound, view.objects[0], 1u, &index),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(index, 7u);
    ASSERT_EQ(break_aspect_object_revision(view.authoritative, view.objects[0]),
              authoritative_revision);

    ASSERT_EQ(fixture.hooks.stop_admission(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.stop_producers(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(aspect_queue_packet(&fixture, 0x2409u, 2u, 512u, false));
    ASSERT_EQ(fixture.hooks.drain(fixture.hooks.user), BREAK_RUNTIME_OK);
    break_aspect_session_stats(view.session, &stats);
    ASSERT_EQ(stats.applied_packets, 2u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.drained_packets, 2u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(trace_contains(fixture.trace,
        "event=network_aspect_stats opened=1 closed=1 applied=2 rejected=0 drained=2"
        " sent_fragments=0 queue_depth=0 dropped=0"));
    aspect_fixture_dispose(&fixture);
}

TEST(aspect_transport_tick_expires_partial_inbound) {
    AspectTransportFixture fixture;
    CoreAppNetAspectTestView view;
    BreakAspectSessionStats stats;
    const struct timespec pause = {0, 60000000L};
    ASSERT_TRUE(aspect_fixture_start(&fixture, "core_app_aspect_tick.port", true));
    ASSERT_TRUE(aspect_fixture_open(&fixture, 0x3409u));
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &view));
    ASSERT_TRUE(aspect_queue_packet(&fixture, 0x3409u, 1u, 17u, true));
    break_aspect_session_stats(view.session, &stats);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    ASSERT_TRUE(stats.bridge.pending_bytes > 0u);
    nanosleep(&pause, NULL);
    aspect_fixture_tick(&fixture);
    break_aspect_session_stats(view.session, &stats);
    ASSERT_EQ(stats.bridge.expired_streams, 1u);
    ASSERT_EQ(stats.bridge.pending_bytes, 0u);
    ASSERT_EQ(fixture.hooks.stop_admission(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.stop_producers(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.drain(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_OK);
    aspect_fixture_dispose(&fixture);
}

TEST(aspect_transport_sync_counts_sends_and_close_releases_connection) {
    AspectTransportFixture fixture;
    CoreAppNetAspectTestView view;
    BreakAspectSessionStats stats;
    ASSERT_TRUE(aspect_fixture_start(&fixture, "core_app_aspect_sync.port", true));
    ASSERT_TRUE(aspect_fixture_open(&fixture, 0x4409u));
    ASSERT_EQ(core_app_net_transport_aspect_sync_for_test(fixture.transport, 0x4409u),
              BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < 2u; ++i) {
        BreakConnectionKey outbound_key = 0u;
        BreakNetOwnedMessage outbound;
        BreakReplicationFragment decoded;
        ASSERT_EQ(break_net_reactor_poll_outbound_for_test(fixture.reactor, &outbound_key,
                                                           &outbound),
                  BREAK_NET_EVENT_OK);
        ASSERT_EQ(outbound_key, 0x4409u);
        ASSERT_EQ(outbound.message_id, BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT);
        ASSERT_EQ(outbound.protocol_version, BREAK_REPLICATION_WIRE_VERSION);
        ASSERT_EQ(break_replication_wire_decode(outbound.data, outbound.size, &decoded),
                  BREAK_REPLICATION_FRAGMENT_OK);
        ASSERT_EQ(decoded.fragment_count, 1u);
        ASSERT_TRUE(decoded.size > 4u);
        ASSERT_TRUE(memcmp(decoded.data, "BRA1", 4u) == 0);
        break_net_message_release(&outbound);
    }
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  fixture.reactor, &(BreakConnectionKey){0u}, &(BreakNetOwnedMessage){0}),
              BREAK_NET_EVENT_EMPTY);
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &view));
    ASSERT_EQ(view.sent_fragments, 2u);
    ASSERT_EQ(view.scope_count, 2u);
    ASSERT_EQ(core_app_net_transport_aspect_sync_for_test(fixture.transport, 0x4409u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  fixture.reactor, &(BreakConnectionKey){0u}, &(BreakNetOwnedMessage){0}),
              BREAK_NET_EVENT_EMPTY);
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &view));
    ASSERT_EQ(view.sent_fragments, 2u);

    ASSERT_EQ(fixture.hooks.stop_admission(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.stop_producers(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.drain(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &view));
    break_aspect_session_stats(view.session, &stats);
    ASSERT_EQ(stats.bridge.connections, 0u);
    ASSERT_EQ(break_aspect_replication_connection_count(view.replication), 0u);
    ASSERT_EQ(view.open_count, 0u);
    ASSERT_EQ(view.scope_count, 0u);
    ASSERT_EQ(view.closed, 1u);
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(trace_contains(fixture.trace,
        "event=network_aspect_stats opened=1 closed=1 applied=0 rejected=0 drained=0"
        " sent_fragments=2 queue_depth=0 dropped=0"));
    aspect_fixture_dispose(&fixture);
}

TEST(aspect_transport_open_failure_rolls_back_session) {
    AspectTransportFixture fixture;
    CoreAppNetAspectTestView view;
    BreakAspectSessionStats stats;
    ASSERT_TRUE(aspect_fixture_start(&fixture, "core_app_aspect_rollback.port", true));
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &view));
    ASSERT_EQ(break_aspect_connection_open(view.replication, 0x5409u, 4096u, 512u),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(fixture.reactor, 0x5409u));
    aspect_fixture_tick(&fixture);
    break_aspect_session_stats(view.session, &stats);
    ASSERT_EQ(stats.bridge.connections, 0u);
    ASSERT_EQ(break_aspect_replication_connection_count(view.replication), 1u);
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &view));
    ASSERT_EQ(view.open_count, 0u);
    ASSERT_EQ(view.opened, 0u);
    ASSERT_EQ(view.closed, 0u);
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(trace_contains(fixture.trace, "event=network_stats opened=0 closed=0 refused=1"));
    ASSERT_TRUE(trace_contains(fixture.trace, "event=network_aspect_stats opened=0 closed=0"));
    aspect_fixture_dispose(&fixture);
}

TEST(aspect_transport_destroy_releases_enabled_state) {
    AspectTransportFixture fixture;
    CoreAppNetAspectTestView view;
    ASSERT_TRUE(aspect_fixture_start(&fixture, "core_app_aspect_destroy.port", true));
    ASSERT_TRUE(aspect_fixture_open(&fixture, 0x6409u));
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &view));
    ASSERT_TRUE(view.enabled);
    ASSERT_FALSE(view.created);
    ASSERT_TRUE(view.authoritative == NULL);
    ASSERT_TRUE(view.inbound == NULL);
    ASSERT_TRUE(view.replication == NULL);
    ASSERT_TRUE(view.session == NULL);
    ASSERT_TRUE(view.spatial_index == NULL);
    ASSERT_EQ(view.open_count, 0u);
    ASSERT_EQ(view.scope_count, 0u);
    ASSERT_EQ(view.opened, 1u);
    ASSERT_EQ(view.closed, 1u);
    ASSERT_TRUE(core_app_net_transport_reactor_for_test(fixture.transport) == NULL);
    ASSERT_TRUE(trace_contains(fixture.trace, "event=network_aspect_stats opened=1 closed=1"));
    aspect_fixture_dispose(&fixture);
}

TEST_MAIN_BEGIN()
    RUN_TEST(destroy_reports_stop_timeout_and_keeps_the_reactor);
    RUN_TEST(voice_frame_counts_invalid_and_skipped_frames);
    RUN_TEST(reactor_events_are_published_on_the_bus);
    RUN_TEST(attach_bus_rejects_a_conflicting_kind);
    RUN_TEST(aspect_transport_default_off_creates_no_state_or_trace);
    RUN_TEST(aspect_transport_open_copies_fixed_pod_objects);
    RUN_TEST(aspect_transport_tick_and_shutdown_drain_only_fill_diagnostic_store);
    RUN_TEST(aspect_transport_tick_expires_partial_inbound);
    RUN_TEST(aspect_transport_sync_counts_sends_and_close_releases_connection);
    RUN_TEST(aspect_transport_open_failure_rolls_back_session);
    RUN_TEST(aspect_transport_destroy_releases_enabled_state);
TEST_MAIN_END()
