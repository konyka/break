#include "test_framework.h"

#include "../apps/core_app/core_app_net_transport.h"

#include <ecs/world_session.h>
#include <network/break_net_adapter.h>
#include <network/break_net_message.h>
#include <network/break_net_message_registry.h>
#include <network/break_online_aspect_replication.h>
#include <network/break_online_aspect_session.h>
#include <network/break_online_voice.h>
#include <network/break_replication_wire.h>
#include <runtime/runtime_bus.h>
#include <runtime/runtime_coordinator.h>
#include <runtime/runtime_queue.h>
#include <runtime/runtime_world_session.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
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
    BreakRuntimeBus *world_bus;
    BreakRuntimeCoordinator *world_coordinator;
    FILE *trace;
    char cert[512];
    char key[512];
    char port_file[256];
    u32 tick;
} AspectTransportFixture;

static bool transport_fixture_destroy(AspectTransportFixture *fixture);

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
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
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
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
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
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
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
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
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
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
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
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    ASSERT_TRUE(trace_contains(fixture.trace, "event=network_stats opened=0 closed=0 refused=1"));
    ASSERT_TRUE(trace_contains(fixture.trace, "event=network_aspect_stats opened=0 closed=0"));
    aspect_fixture_dispose(&fixture);
}

TEST(aspect_transport_destroy_releases_enabled_state) {
    AspectTransportFixture fixture;
    CoreAppNetAspectTestView view;
    ASSERT_TRUE(aspect_fixture_start(&fixture, "core_app_aspect_destroy.port", true));
    ASSERT_TRUE(aspect_fixture_open(&fixture, 0x6409u));
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
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

typedef struct WorldAttempt {
    u64 delta_id;
    BreakWorldDeltaWireKind kind;
    u64 base_snapshot_id;
    u64 target_snapshot_id;
    u64 target_tick;
} WorldAttempt;

static bool world_fixture_start_with(AspectTransportFixture *fixture, const char *name,
                                     bool world_enabled, bool aspect_enabled) {
    const char *fixtures = CORE_APP_TEST_STR(CORE_APP_TEST_SSL_FIXTURE_DIR);
    const bool legacy = fixture->config.world_use_legacy_publish;
    memset(fixture, 0, sizeof(*fixture));
    fixture->config.world_use_legacy_publish = legacy;
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
    fixture->config.world_replication = world_enabled;
    fixture->config.aspect_replication = aspect_enabled;
    fixture->transport = core_app_net_transport_create(&fixture->config);
    if (!fixture->transport) return false;
    if (break_runtime_bus_create(&fixture->world_bus) != BREAK_RUNTIME_OK ||
        core_app_net_transport_attach_bus(fixture->transport, fixture->world_bus) != BREAK_RUNTIME_OK) {
        return false;
    }
    {
        const BreakRuntimeCoordinatorConfig coordinator_config = {2u};
        if (break_runtime_coordinator_create(&coordinator_config, &fixture->world_coordinator) !=
            BREAK_RUNTIME_OK) {
            return false;
        }
    }
    core_app_net_transport_hooks(fixture->transport, &fixture->hooks);
    if (fixture->hooks.start(fixture->hooks.user, fixture->trace) != BREAK_RUNTIME_OK) return false;
    if (!fixture->hooks.world_adapter_register || !fixture->hooks.world_adapter ||
        fixture->hooks.world_adapter_register(fixture->hooks.user, fixture->world_bus,
                                              fixture->world_coordinator) != BREAK_RUNTIME_OK) {
        return false;
    }
    fixture->reactor = core_app_net_transport_reactor_for_test(fixture->transport);
    return fixture->reactor != NULL;
}

static bool world_fixture_start(AspectTransportFixture *fixture, const char *name,
                                bool world_enabled, bool aspect_enabled) {
    memset(fixture, 0, sizeof(*fixture));
    return world_fixture_start_with(fixture, name, world_enabled, aspect_enabled);
}

static bool transport_fixture_destroy(AspectTransportFixture *fixture) {
    BreakRuntimeState state;
    if (!fixture->world_coordinator) {
        return fixture->hooks.destroy(fixture->hooks.user) == BREAK_RUNTIME_OK;
    }
    state = break_runtime_coordinator_state(fixture->world_coordinator);
    if (state == BREAK_RUNTIME_CREATED &&
        break_runtime_coordinator_start(fixture->world_coordinator) != BREAK_RUNTIME_OK) {
        return false;
    }
    if (state != BREAK_RUNTIME_STOPPED &&
        break_runtime_coordinator_stop(fixture->world_coordinator) != BREAK_RUNTIME_OK) {
        return false;
    }
    if (core_app_net_transport_world_adapter(fixture->transport) != NULL) return false;
    if (fixture->reactor && fixture->hooks.destroy(fixture->hooks.user) != BREAK_RUNTIME_OK) return false;
    break_runtime_coordinator_destroy(fixture->world_coordinator);
    fixture->world_coordinator = NULL;
    break_runtime_bus_destroy(fixture->world_bus);
    fixture->world_bus = NULL;
    return true;
}

static void world_fixture_tick(AspectTransportFixture *fixture) {
    fixture->tick++;
    const CoreAppSnapshotEntity entities[2] = {
        {7u + fixture->tick - 1u, 3u, 1.5f, -2.0f, 3.25f, 11u},
        {8u + fixture->tick - 1u, 4u, -4.0f, 5.5f, 6.0f, 22u},
    };
    fixture->hooks.tick(fixture->hooks.user, fixture->tick, 9u, entities, 2u, 0u);
}

static bool world_fixture_open(AspectTransportFixture *fixture, BreakConnectionKey key) {
    CoreAppNetWorldTestView view;
    if (!break_net_reactor_enqueue_opened_for_test(fixture->reactor, key)) return false;
    world_fixture_tick(fixture);
    return core_app_net_transport_world_for_test(fixture->transport, &view) &&
           view.open_count == 1u;
}

static bool world_encode_full(const BreakWorldSnapshot *snapshot, u64 level_generation,
                              u8 **out_wire, usize *out_size) {
    BreakWorldDeltaWire message;
    usize count = 0u;
    usize slot = 0u;
    u8 *wire;
    usize size = 0u;
    memset(&message, 0, sizeof(message));
    for (usize i = 0u; i < break_world_snapshot_entity_count(snapshot); ++i) {
        Entity entity = break_world_snapshot_entity_at(snapshot, i);
        count++;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            usize bytes_size = 0u;
            if (break_world_snapshot_component_bytes(snapshot, entity, component,
                                                      &bytes, &bytes_size)) {
                count++;
            }
        }
    }
    if (count > UINT32_MAX) return false;
    message.kind = BREAK_WORLD_DELTA_WIRE_FULL;
    message.schema_hash = break_world_snapshot_schema_hash(snapshot);
    message.level_generation = level_generation;
    message.target_snapshot_id = break_world_snapshot_id(snapshot);
    message.target_tick = break_world_snapshot_tick(snapshot);
    message.record_count = (u32)count;
    message.records = (BreakWorldDeltaRecord *)calloc(count, sizeof(*message.records));
    if (count != 0u && !message.records) return false;
    for (usize i = 0u; i < break_world_snapshot_entity_count(snapshot); ++i) {
        Entity entity = break_world_snapshot_entity_at(snapshot, i);
        message.records[slot].kind = BREAK_DELTA_ENTITY_CREATE;
        message.records[slot].entity = entity;
        slot++;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            usize bytes_size = 0u;
            if (break_world_snapshot_component_bytes(snapshot, entity, component,
                                                      &bytes, &bytes_size)) {
                message.records[slot].kind = BREAK_DELTA_COMPONENT_ADD;
                message.records[slot].entity = entity;
                message.records[slot].component = component;
                message.records[slot].bytes = bytes;
                message.records[slot].size = bytes_size;
                slot++;
            }
        }
    }
    if (break_world_delta_wire_encoded_size(&message, &size) != BREAK_WORLD_DELTA_WIRE_OK) {
        free(message.records);
        return false;
    }
    wire = (u8 *)malloc(size);
    if (!wire) {
        free(message.records);
        return false;
    }
    bool ok = break_world_delta_wire_encode(&message, wire, size, &size) ==
              BREAK_WORLD_DELTA_WIRE_OK;
    free(message.records);
    if (!ok) {
        free(wire);
        return false;
    }
    *out_wire = wire;
    *out_size = size;
    return true;
}

static bool world_queue_full(AspectTransportFixture *fixture, BreakConnectionKey key,
                             const BreakWorldSnapshot *snapshot, u64 delta_id) {
    CoreAppNetWorldTestView view;
    BreakReplicationFragment *fragments = NULL;
    usize fragment_count = 0u;
    u8 *payload = NULL;
    usize payload_size = 0u;
    bool handled = true;
    if (!core_app_net_transport_world_for_test(fixture->transport, &view) || !view.created ||
        !world_encode_full(snapshot, view.level_generation, &payload, &payload_size)) {
        return false;
    }
    u64 epoch = break_world_session_stream_epoch(1u, break_schema_hash(view.schemas),
                                                 view.level_generation);
    if (break_replication_fragment_payload(delta_id, epoch, payload, payload_size, 64u,
                                           &fragments, &fragment_count) !=
        BREAK_REPLICATION_FRAGMENT_OK) {
        free(payload);
        return false;
    }
    for (usize i = 0u; i < fragment_count; ++i) {
        u8 wire[BREAK_REPLICATION_WIRE_HEADER_SIZE + 64u];
        usize wire_size = 0u;
        BreakNetOwnedMessage message;
        memset(&message, 0, sizeof(message));
        if (break_replication_wire_encode(&fragments[i], wire, sizeof(wire), &wire_size) !=
            BREAK_REPLICATION_FRAGMENT_OK) {
            handled = false;
            break;
        }
        message.message_id = BREAK_NET_MESSAGE_ID_WORLD_DELTA;
        message.protocol_version = BREAK_REPLICATION_WIRE_VERSION;
        message.sequence = (u32)i + 1u;
        message.data = wire;
        message.size = wire_size;
        if (!break_replication_session_handle_message(
                key, &message, break_world_session_bridge(view.session))) {
            handled = false;
            break;
        }
    }
    break_replication_fragments_free(fragments, fragment_count);
    free(payload);
    return handled;
}

static bool world_collect_attempt(AspectTransportFixture *fixture, BreakConnectionKey key,
                                  const u8 *first_wire, usize first_size, WorldAttempt *out) {
    CoreAppNetWorldTestView view;
    BreakReplicationReassembler *reassembler = NULL;
    u8 *payload = NULL;
    usize payload_size = 0u;
    bool complete = false;
    bool ok = core_app_net_transport_world_for_test(fixture->transport, &view) && view.created;
    memset(out, 0, sizeof(*out));
    if (ok) {
        u64 epoch = break_world_session_stream_epoch(1u, break_schema_hash(view.schemas),
                                                     view.level_generation);
        reassembler = break_replication_reassembler_create(epoch);
        ok = reassembler != NULL;
    }
    if (ok && first_size != 0u) {
        BreakReplicationFragment fragment;
        BreakReplicationReassemblyResult result;
        ok = break_replication_wire_decode(first_wire, first_size, &fragment) ==
             BREAK_REPLICATION_FRAGMENT_OK;
        if (ok) {
            out->delta_id = fragment.delta_id;
            result = break_replication_reassembler_push(reassembler, &fragment,
                                                        &payload, &payload_size);
            complete = result == BREAK_REPLICATION_REASSEMBLY_COMPLETE;
            ok = complete || result == BREAK_REPLICATION_REASSEMBLY_INCOMPLETE;
        }
    }
    while (ok) {
        BreakConnectionKey outbound_key = 0u;
        BreakNetOwnedMessage outbound;
        if (break_net_reactor_poll_outbound_for_test(fixture->reactor, &outbound_key,
                                                     &outbound) != BREAK_NET_EVENT_OK) {
            break;
        }
        if (outbound_key == key && outbound.message_id == BREAK_NET_MESSAGE_ID_WORLD_DELTA) {
            BreakReplicationFragment fragment;
            BreakReplicationReassemblyResult result;
            ok = break_replication_wire_decode(outbound.data, outbound.size, &fragment) ==
                 BREAK_REPLICATION_FRAGMENT_OK;
            if (ok) {
                out->delta_id = fragment.delta_id;
                result = break_replication_reassembler_push(reassembler, &fragment,
                                                            &payload, &payload_size);
                complete = result == BREAK_REPLICATION_REASSEMBLY_COMPLETE;
                ok = complete || result == BREAK_REPLICATION_REASSEMBLY_INCOMPLETE;
            }
        }
        break_net_message_release(&outbound);
    }
    if (ok && complete) {
        BreakWorldDeltaWire decoded;
        ok = break_world_delta_wire_decode(payload, payload_size, &decoded) ==
             BREAK_WORLD_DELTA_WIRE_OK;
        if (ok) {
            out->kind = decoded.kind;
            out->base_snapshot_id = decoded.base_snapshot_id;
            out->target_snapshot_id = decoded.target_snapshot_id;
            out->target_tick = decoded.target_tick;
            break_world_delta_wire_clear(&decoded);
        }
    } else {
        ok = false;
    }
    break_replication_reassembly_free(payload);
    break_replication_reassembler_destroy(reassembler);
    return ok;
}

static void world_put16(u8 *out, u16 value) {
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
}

static void world_put64(u8 *out, u64 value) {
    for (u32 i = 0u; i < 8u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static u64 world_get64(const u8 *bytes) {
    u64 value = 0u;
    for (u32 i = 0u; i < 8u; ++i) value |= (u64)bytes[i] << (i * 8u);
    return value;
}

static bool world_next_control(AspectTransportFixture *fixture, BreakConnectionKey *out_key,
                               BreakNetOwnedMessage *out_message) {
    for (;;) {
        if (break_net_reactor_poll_outbound_for_test(fixture->reactor, out_key, out_message) !=
            BREAK_NET_EVENT_OK) {
            return false;
        }
        if (out_message->message_id == BREAK_NET_MESSAGE_ID_WORLD_CONTROL) return true;
        break_net_message_release(out_message);
    }
}

static void world_clear_outbound(AspectTransportFixture *fixture) {
    BreakConnectionKey key = 0u;
    BreakNetOwnedMessage message;
    while (break_net_reactor_poll_outbound_for_test(fixture->reactor, &key, &message) ==
           BREAK_NET_EVENT_OK) {
        break_net_message_release(&message);
    }
}

static bool world_control_payload_matches(const BreakNetOwnedMessage *message,
                                          BreakWorldSessionControlKind kind, u64 delta_id,
                                          u64 target_id, u64 target_tick, u64 level) {
    const u8 *bytes = (const u8 *)message->data;
    usize expected_size = message->protocol_version == 2u
                              ? BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2
                              : BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE;
    if (message->size != expected_size || message->size < 32u ||
        memcmp(bytes, "BRWC", 4u) != 0 ||
        ((usize)bytes[4] | ((usize)bytes[5] << 8u)) != message->protocol_version) {
        return false;
    }
    return (u16)((u16)bytes[6] | ((u16)bytes[7] << 8u)) == (u16)kind &&
           world_get64(bytes + 8u) == delta_id && world_get64(bytes + 16u) == target_id &&
           world_get64(bytes + 24u) == target_tick &&
           (message->protocol_version == 1u ||
            (message->protocol_version == 2u && world_get64(bytes + 32u) == level));
}

static bool world_send_control(AspectTransportFixture *fixture, BreakConnectionKey key,
                               BreakWorldSessionControlKind kind, const WorldAttempt *attempt) {
    u8 payload[BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2];
    BreakNetOwnedMessage message;
    CoreAppNetWorldTestView view;
    if (!core_app_net_transport_world_for_test(fixture->transport, &view)) return false;
    memset(payload, 0, sizeof(payload));
    memcpy(payload, "BRWC", 4u);
    world_put16(payload + 4u, 2u);
    world_put16(payload + 6u, (u16)kind);
    if (attempt) {
        if (kind == BREAK_WORLD_SESSION_CONTROL_ACK) {
            world_put64(payload + 8u, attempt->delta_id);
        }
        world_put64(payload + 16u, attempt->target_snapshot_id);
        world_put64(payload + 24u, attempt->target_tick);
    }
    world_put64(payload + 32u, view.level_generation);
    memset(&message, 0, sizeof(message));
    message.message_id = BREAK_NET_MESSAGE_ID_WORLD_CONTROL;
    message.protocol_version = 2u;
    message.sequence = 1u;
    message.data = payload;
    message.size = sizeof(payload);
    return core_app_net_transport_world_control_for_test(fixture->transport, key, &message);
}

TEST(world_transport_default_off_creates_no_state_or_trace) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView world;
    CoreAppNetAspectTestView aspect;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_default.port", false, false));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &world));
    ASSERT_FALSE(world.enabled);
    ASSERT_FALSE(world.created);
    ASSERT_TRUE(world.schemas == NULL);
    ASSERT_TRUE(world.authoritative == NULL);
    ASSERT_TRUE(world.diagnostic == NULL);
    ASSERT_TRUE(world.session == NULL);
    ASSERT_EQ(world.open_count, 0u);
    ASSERT_TRUE(core_app_net_transport_world_adapter(fixture.transport) == NULL);
    ASSERT_FALSE(break_runtime_bus_kind_accepts(
        fixture.world_bus, BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND, 1u,
        sizeof(BreakRuntimeWorldCommand)));
    world_fixture_tick(&fixture);
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &aspect));
    ASSERT_FALSE(aspect.enabled);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    ASSERT_TRUE(trace_contains(fixture.trace, "event=network_stats"));
    ASSERT_FALSE(trace_contains(fixture.trace, "event=network_world_stats"));
    ASSERT_FALSE(trace_contains(fixture.trace, "event=network_aspect_stats"));
    aspect_fixture_dispose(&fixture);
}

TEST(world_adapter_registration_rebaseline_and_reopen_epochs) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView before;
    CoreAppNetWorldTestView after;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    BreakRuntimeWorldCommand stale;
    BreakReplicationSessionBridgeStats bridge;
    const BreakConnectionKey key = UINT64_C(0x100000001);
    u64 old_epoch = 0u;
    u64 new_epoch = 0u;
    usize drained = 0u;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_adapter_epoch.port", true, false));
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    ASSERT_NOT_NULL(adapter);
    ASSERT_TRUE(fixture.hooks.world_adapter(fixture.hooks.user) == adapter);
    ASSERT_TRUE(break_runtime_bus_kind_accepts(
        fixture.world_bus, BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND, 1u,
        sizeof(BreakRuntimeWorldCommand)));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &before));
    ASSERT_NOT_NULL(before.session);
    ASSERT_EQ(before.level_generation, 0u);

    world_fixture_tick(&fixture);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &after));
    ASSERT_TRUE(after.session == before.session);
    ASSERT_EQ(after.level_generation, 9u);
    ASSERT_TRUE(core_app_net_transport_world_adapter(fixture.transport) == adapter);
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, key, &old_epoch));
    ASSERT_NEQ(old_epoch, 0u);
    break_replication_session_bridge_stats(break_world_session_bridge(after.session), &bridge);
    ASSERT_EQ(bridge.connections, 1u);

    ASSERT_NOT_NULL(core_app_net_transport_world_reopen_for_test(fixture.transport, key));
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, key, &new_epoch));
    ASSERT_NEQ(new_epoch, 0u);
    ASSERT_NEQ(new_epoch, old_epoch);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &after));
    ASSERT_TRUE(after.session == before.session);
    memset(&stale, 0, sizeof(stale));
    stale.kind = BREAK_RUNTIME_WORLD_COMMAND_ACK;
    stale.connection_key = key;
    stale.connection_epoch = old_epoch;
    stale.level_generation = 9u;
    stale.delta_id = UINT64_C(0x10000000A);
    stale.target_snapshot_id = UINT64_C(0x20000000B);
    stale.target_tick = 77u;
    ASSERT_EQ(core_app_net_transport_world_submit(fixture.transport, &stale,
                                                  UINT64_C(0xF123456789ABCDEF)),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    ASSERT_EQ(drained, 1u);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.stale_rejected, 1u);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, key, &new_epoch));
    ASSERT_NEQ(new_epoch, old_epoch);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_adapter_submit_defers_open_close_and_fifo_controls) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    BreakRuntimeWorldCommand item;
    BreakNetOwnedMessage outbound;
    const BreakConnectionKey key = UINT64_C(0x200000002);
    const u64 high_cid = UINT64_C(0xF123456789ABCDEF);
    BreakConnectionKey outbound_key = 0u;
    u64 epoch = 0u;
    usize drained = 0u;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_adapter_fifo.port", true, false));
    world_fixture_tick(&fixture);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    ASSERT_NOT_NULL(adapter);
    memset(&item, 0, sizeof(item));
    item.kind = BREAK_RUNTIME_WORLD_COMMAND_OPEN;
    item.connection_key = key;
    item.level_generation = 9u;
    ASSERT_EQ(core_app_net_transport_world_submit(fixture.transport, &item, high_cid),
              BREAK_RUNTIME_OK);
    ASSERT_FALSE(break_world_session_baseline(view.session, key, NULL, NULL));
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.submitted, 1u);
    ASSERT_EQ(stats.drained, 0u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_EQ(break_runtime_world_session_drain(adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(break_world_session_baseline(view.session, key, NULL, NULL));
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, key, &epoch));
    ASSERT_NEQ(epoch, 0u);

    memset(&item, 0, sizeof(item));
    item.kind = BREAK_RUNTIME_WORLD_COMMAND_ACK;
    item.connection_key = key;
    item.connection_epoch = epoch;
    item.level_generation = 9u;
    item.delta_id = UINT64_C(0x10000000A);
    item.target_snapshot_id = UINT64_C(0x20000000B);
    item.target_tick = UINT64_C(0x30000000C);
    ASSERT_EQ(core_app_net_transport_world_submit(fixture.transport, &item, high_cid),
              BREAK_RUNTIME_OK);
    item.kind = BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL;
    item.delta_id = 0u;
    item.target_snapshot_id = UINT64_C(0x40000000D);
    item.target_tick = UINT64_C(0x50000000E);
    ASSERT_EQ(core_app_net_transport_world_submit(fixture.transport, &item, high_cid - 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.queued, 2u);
    ASSERT_EQ(break_runtime_world_session_drain(adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(world_next_control(&fixture, &outbound_key, &outbound));
    ASSERT_EQ(outbound_key, key);
    ASSERT_EQ(outbound.correlation_id, high_cid);
    ASSERT_TRUE(world_control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                              UINT64_C(0x10000000A), UINT64_C(0x20000000B),
                                              UINT64_C(0x30000000C), 9u));
    break_net_message_release(&outbound);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_EQ(break_runtime_world_session_drain(adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(world_next_control(&fixture, &outbound_key, &outbound));
    ASSERT_EQ(outbound_key, key);
    ASSERT_EQ(outbound.correlation_id, high_cid - 1u);
    ASSERT_TRUE(world_control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_NEED_FULL,
                                              0u, UINT64_C(0x40000000D),
                                              UINT64_C(0x50000000E), 9u));
    break_net_message_release(&outbound);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);

    memset(&item, 0, sizeof(item));
    item.kind = BREAK_RUNTIME_WORLD_COMMAND_CLOSE;
    item.connection_key = key;
    item.connection_epoch = epoch;
    item.level_generation = 9u;
    ASSERT_EQ(core_app_net_transport_world_submit(fixture.transport, &item, high_cid - 2u),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(break_world_session_baseline(view.session, key, NULL, NULL));
    ASSERT_EQ(break_runtime_world_session_drain(adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_FALSE(break_world_session_baseline(view.session, key, NULL, NULL));
    ASSERT_FALSE(break_runtime_world_session_connection_epoch(adapter, key, &epoch));
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

static bool world_make_control_pending(AspectTransportFixture *fixture,
                                       BreakConnectionKey key, u64 delta_id) {
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSessionStats stats;
    BreakWorldSnapshot *snapshot;
    bool ok = core_app_net_transport_world_for_test(fixture->transport, &view);
    snapshot = ok ? break_world_snapshot_build(view.authoritative, view.schemas, 20u) : NULL;
    if (!snapshot) return false;
    ok = world_queue_full(fixture, key, snapshot, delta_id);
    for (usize i = 0u; ok && i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ok = break_net_reactor_send(fixture->reactor, key, BREAK_NET_MESSAGE_ID_PING,
                                    1u, "x", 1u) == BREAK_NET_SEND_OK;
    }
    core_app_net_transport_world_drain_for_test(fixture->transport, 20u);
    break_runtime_world_session_stats(
        core_app_net_transport_world_adapter(fixture->transport), &stats);
    break_world_snapshot_release(snapshot);
    return ok && stats.control_pending && stats.queued == 0u;
}

TEST(world_adapter_open_pending_control_reconciles_epoch_slot_and_diagnostic) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    const BreakConnectionKey open_key = 0x140au;
    const BreakConnectionKey pending_key = UINT64_C(0x300000003);
    u64 epoch = 0u;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_open_pending.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, open_key));
    ASSERT_TRUE(world_make_control_pending(&fixture, open_key, 81u));
    adapter = core_app_net_transport_world_adapter(fixture.transport);

    (void)core_app_net_transport_world_open_for_test(fixture.transport, pending_key);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_TRUE(stats.control_pending);
    ASSERT_FALSE(break_runtime_world_session_connection_epoch(adapter, pending_key, &epoch));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.open_count, 1u);
    ASSERT_EQ(view.opened, 1u);
    ASSERT_NOT_NULL(view.diagnostic);

    world_clear_outbound(&fixture);
    core_app_net_transport_world_drain_for_test(fixture.transport, 21u);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, pending_key, &epoch));
    ASSERT_NEQ(epoch, 0u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.open_count, 2u);
    ASSERT_EQ(view.opened, 2u);
    ASSERT_NOT_NULL(view.diagnostic);
    ASSERT_TRUE(break_world_session_baseline(view.session, pending_key, NULL, NULL));
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_adapter_reopen_pending_control_completes_second_open) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    const BreakConnectionKey key = 0x240bu;
    u64 old_epoch = 0u;
    u64 new_epoch = 0u;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_reopen_pending.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(world_make_control_pending(&fixture, key, 83u));
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, key, &old_epoch));
    ASSERT_NEQ(old_epoch, 0u);

    ASSERT_TRUE(core_app_net_transport_world_reopen_for_test(fixture.transport, key) == NULL);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.open_count, 1u);
    ASSERT_EQ(view.opened, 1u);
    ASSERT_EQ(view.closed, 0u);
    ASSERT_NOT_NULL(view.diagnostic);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, key, &new_epoch));
    ASSERT_EQ(new_epoch, old_epoch);

    world_clear_outbound(&fixture);
    core_app_net_transport_world_drain_for_test(fixture.transport, 21u);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, key, &new_epoch));
    ASSERT_NEQ(new_epoch, 0u);
    ASSERT_NEQ(new_epoch, old_epoch);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.open_count, 1u);
    ASSERT_EQ(view.opened, 2u);
    ASSERT_EQ(view.closed, 1u);
    ASSERT_NOT_NULL(view.diagnostic);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_adapter_close_pending_control_reconciles_epoch_slot_and_diagnostic) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    const BreakConnectionKey key = 0x240au;
    u64 epoch = 0u;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_close_pending.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(world_make_control_pending(&fixture, key, 82u));
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, key, &epoch));
    ASSERT_NEQ(epoch, 0u);

    core_app_net_transport_world_close_for_test(fixture.transport, key);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_TRUE(stats.control_pending);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, key, &epoch));
    ASSERT_NEQ(epoch, 0u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.open_count, 1u);
    ASSERT_EQ(view.closed, 0u);
    ASSERT_NOT_NULL(view.diagnostic);

    world_clear_outbound(&fixture);
    core_app_net_transport_world_drain_for_test(fixture.transport, 21u);
    ASSERT_FALSE(break_runtime_world_session_connection_epoch(adapter, key, &epoch));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.open_count, 0u);
    ASSERT_EQ(view.closed, 1u);
    ASSERT_TRUE(view.diagnostic == NULL);
    ASSERT_FALSE(break_world_session_baseline(view.session, key, NULL, NULL));
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_adapter_cancel_pending_open_after_disconnect_closes_original_key) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    const BreakConnectionKey open_key = 0x140bu;
    const BreakConnectionKey canceled_key = UINT64_C(0x300000004);
    u64 epoch = 0u;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_cancel_disconnect.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, open_key));
    ASSERT_TRUE(world_make_control_pending(&fixture, open_key, 84u));
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    (void)core_app_net_transport_world_open_for_test(fixture.transport, canceled_key);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_TRUE(stats.control_pending);

    core_app_net_transport_world_disconnect_for_test(fixture.transport, canceled_key);
    world_clear_outbound(&fixture);
    core_app_net_transport_world_drain_for_test(fixture.transport, 21u);
    ASSERT_FALSE(break_runtime_world_session_connection_epoch(adapter, canceled_key, &epoch));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_FALSE(break_world_session_baseline(view.session, canceled_key, NULL, NULL));
    ASSERT_EQ(view.open_count, 1u);
    ASSERT_EQ(view.opened, 2u);
    ASSERT_EQ(view.closed, 1u);
    ASSERT_NOT_NULL(view.diagnostic);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_adapter_disconnect_does_not_commit_old_open_to_reused_slot) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    const BreakConnectionKey open_key = 0x140cu;
    const BreakConnectionKey canceled_key = UINT64_C(0x300000005);
    const BreakConnectionKey new_key = UINT64_C(0x400000006);
    u64 epoch = 0u;
    int old_slot;
    int new_slot;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_slot_reuse.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, open_key));
    ASSERT_TRUE(world_make_control_pending(&fixture, open_key, 86u));
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    (void)core_app_net_transport_world_open_for_test(fixture.transport, canceled_key);
    old_slot = core_app_net_transport_world_slot_for_test(fixture.transport, canceled_key);
    ASSERT_TRUE(old_slot >= 0);
    core_app_net_transport_world_disconnect_for_test(fixture.transport, canceled_key);

    (void)core_app_net_transport_world_open_for_test(fixture.transport, new_key);
    new_slot = core_app_net_transport_world_slot_for_test(fixture.transport, new_key);
    ASSERT_TRUE(new_slot >= 0);
    world_clear_outbound(&fixture);
    core_app_net_transport_world_drain_for_test(fixture.transport, 21u);
    ASSERT_FALSE(break_runtime_world_session_connection_epoch(adapter, canceled_key, &epoch));
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, new_key, &epoch));
    ASSERT_NEQ(epoch, 0u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_FALSE(break_world_session_baseline(view.session, canceled_key, NULL, NULL));
    ASSERT_TRUE(break_world_session_baseline(view.session, new_key, NULL, NULL));
    ASSERT_NEQ(new_slot, old_slot);
    ASSERT_EQ(view.open_count, 2u);
    ASSERT_EQ(view.opened, 3u);
    ASSERT_EQ(view.closed, 1u);
    ASSERT_NOT_NULL(view.diagnostic);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_adapter_close_failure_after_disconnect_is_not_misread_as_success) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    const BreakConnectionKey key = 0x240cu;
    u64 epoch = 0u;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_close_failure_disconnect.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(world_make_control_pending(&fixture, key, 85u));
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, key, &epoch));
    ASSERT_NEQ(epoch, 0u);
    core_app_net_transport_world_close_for_test(fixture.transport, key);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_TRUE(break_world_session_close(view.session, key));

    core_app_net_transport_world_disconnect_for_test(fixture.transport, key);
    world_clear_outbound(&fixture);
    core_app_net_transport_world_drain_for_test(fixture.transport, 21u);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, key, &epoch));
    ASSERT_NEQ(epoch, 0u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_FALSE(break_world_session_baseline(view.session, key, NULL, NULL));
    ASSERT_EQ(view.open_count, 1u);
    ASSERT_EQ(view.opened, 1u);
    ASSERT_EQ(view.closed, 0u);
    ASSERT_NOT_NULL(view.diagnostic);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_adapter_same_key_pending_close_defers_cross_slot_open) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    CoreAppNetConnectionTestView old_slot_view;
    CoreAppNetConnectionTestView new_slot_view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    const BreakConnectionKey control_key = UINT64_C(0x500000007);
    const BreakConnectionKey reused_key = UINT64_C(0x600000008);
    u64 old_epoch = 0u;
    u64 new_epoch = 0u;
    int old_slot;
    int new_slot;
    bool epoch_open;
    bool old_released;
    bool new_committed;
    bool counts_match;
    bool drained;
    bool destroyed;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_same_key_close.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, control_key));
    ASSERT_TRUE(core_app_net_transport_world_open_for_test(fixture.transport, reused_key));
    old_slot = core_app_net_transport_world_slot_for_test(fixture.transport, reused_key);
    ASSERT_TRUE(old_slot >= 0);
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, reused_key, &old_epoch));
    ASSERT_NEQ(old_epoch, 0u);
    ASSERT_TRUE(world_make_control_pending(&fixture, control_key, 87u));

    core_app_net_transport_world_disconnect_for_test(fixture.transport, reused_key);
    (void)core_app_net_transport_world_open_for_test(fixture.transport, reused_key);
    new_slot = core_app_net_transport_world_slot_for_test(fixture.transport, reused_key);
    ASSERT_TRUE(new_slot >= 0);
    ASSERT_NEQ(new_slot, old_slot);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_TRUE(stats.control_pending);

    world_clear_outbound(&fixture);
    core_app_net_transport_world_drain_for_test(fixture.transport, 21u);
    core_app_net_transport_world_drain_for_test(fixture.transport, 22u);
    epoch_open = break_runtime_world_session_connection_epoch(adapter, reused_key, &new_epoch);
    old_released = core_app_net_transport_connection_for_test(
                       fixture.transport, (u32)old_slot, &old_slot_view) &&
                   old_slot_view.key == 0u && !old_slot_view.world_open &&
                   old_slot_view.world_epoch == 0u && old_slot_view.world_transition_kind == 0u &&
                   old_slot_view.world_transition_key == 0u &&
                   old_slot_view.world_diagnostic == NULL &&
                   old_slot_view.world_pending_diagnostic == NULL;
    new_committed = core_app_net_transport_connection_for_test(
                        fixture.transport, (u32)new_slot, &new_slot_view) &&
                    new_slot_view.key == reused_key && new_slot_view.world_open &&
                    new_slot_view.world_epoch == new_epoch &&
                    new_slot_view.world_diagnostic != NULL &&
                    !new_slot_view.world_admission_pending;
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    counts_match = view.open_count == 2u && view.opened == 3u && view.closed == 1u;
    break_runtime_world_session_stats(adapter, &stats);
    drained = stats.queued == 0u && !stats.control_pending;
    destroyed = transport_fixture_destroy(&fixture);
    aspect_fixture_dispose(&fixture);
    ASSERT_TRUE(destroyed);
    ASSERT_TRUE(epoch_open);
    ASSERT_NEQ(new_epoch, 0u);
    ASSERT_NEQ(new_epoch, old_epoch);
    ASSERT_TRUE(old_released);
    ASSERT_TRUE(new_committed);
    ASSERT_TRUE(counts_match);
    ASSERT_TRUE(drained);
}

TEST(world_adapter_canceled_open_defers_same_key_cross_slot_open) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    CoreAppNetConnectionTestView old_slot_view;
    CoreAppNetConnectionTestView new_slot_view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    const BreakConnectionKey control_key = UINT64_C(0x500000009);
    const BreakConnectionKey reused_key = UINT64_C(0x60000000a);
    u64 control_epoch = 0u;
    u64 new_epoch = 0u;
    int old_slot;
    int new_slot;
    bool epoch_open;
    bool old_released;
    bool new_committed;
    bool counts_match;
    bool drained;
    bool destroyed;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_same_key_cancel.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, control_key));
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(adapter, control_key, &control_epoch));
    ASSERT_TRUE(world_make_control_pending(&fixture, control_key, 88u));
    (void)core_app_net_transport_world_open_for_test(fixture.transport, reused_key);
    old_slot = core_app_net_transport_world_slot_for_test(fixture.transport, reused_key);
    ASSERT_TRUE(old_slot >= 0);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_TRUE(stats.control_pending);

    core_app_net_transport_world_disconnect_for_test(fixture.transport, reused_key);
    (void)core_app_net_transport_world_open_for_test(fixture.transport, reused_key);
    new_slot = core_app_net_transport_world_slot_for_test(fixture.transport, reused_key);
    ASSERT_TRUE(new_slot >= 0);
    ASSERT_NEQ(new_slot, old_slot);
    world_clear_outbound(&fixture);
    core_app_net_transport_world_drain_for_test(fixture.transport, 21u);
    core_app_net_transport_world_drain_for_test(fixture.transport, 22u);

    epoch_open = break_runtime_world_session_connection_epoch(adapter, reused_key, &new_epoch);
    old_released = core_app_net_transport_connection_for_test(
                       fixture.transport, (u32)old_slot, &old_slot_view) &&
                   old_slot_view.key == 0u && !old_slot_view.world_open &&
                   old_slot_view.world_epoch == 0u && old_slot_view.world_transition_kind == 0u &&
                   old_slot_view.world_transition_key == 0u &&
                   old_slot_view.world_diagnostic == NULL &&
                   old_slot_view.world_pending_diagnostic == NULL;
    new_committed = core_app_net_transport_connection_for_test(
                        fixture.transport, (u32)new_slot, &new_slot_view) &&
                    new_slot_view.key == reused_key && new_slot_view.world_open &&
                    new_slot_view.world_epoch == new_epoch &&
                    new_slot_view.world_diagnostic != NULL &&
                    !new_slot_view.world_admission_pending;
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    counts_match = view.open_count == 2u && view.opened == 3u && view.closed == 1u;
    break_runtime_world_session_stats(adapter, &stats);
    drained = stats.queued == 0u && !stats.control_pending;
    destroyed = transport_fixture_destroy(&fixture);
    aspect_fixture_dispose(&fixture);
    ASSERT_TRUE(destroyed);
    ASSERT_TRUE(epoch_open);
    ASSERT_NEQ(new_epoch, 0u);
    ASSERT_TRUE(new_epoch > control_epoch);
    ASSERT_TRUE(old_released);
    ASSERT_TRUE(new_committed);
    ASSERT_TRUE(counts_match);
    ASSERT_TRUE(drained);
}

TEST(world_adapter_rejected_pending_open_releases_connection_before_slot_reuse) {
    AspectTransportFixture fixture;
    CoreAppNetConnectionTestView old_view;
    CoreAppNetConnectionTestView reused_view;
    BreakRuntimeWorldSession *adapter;
    BreakVoiceFrame frame;
    CoreAppClockProbe clock_request = {CORE_APP_CLOCK_PROBE_REQUEST, 123u, 0u, 0u};
    u8 voice_wire[BREAK_VOICE_MAX_DATAGRAM_SIZE];
    u8 mute_wire[CORE_APP_VOICE_MUTE_BYTES];
    u8 clock_wire[CORE_APP_CLOCK_PROBE_BYTES];
    u32 voice_size = 0u;
    usize mute_size = 0u;
    usize clock_size = 0u;
    const BreakConnectionKey control_key = UINT64_C(0x50000000b);
    const BreakConnectionKey rejected_key = UINT64_C(0x60000000c);
    const BreakConnectionKey new_key = UINT64_C(0x60000000d);
    u64 epoch = 0u;
    int rejected_slot;
    int reused_slot;
    bool rejected_epoch_absent;
    bool rejected_cleaned;
    bool reused_open;
    bool reused_clean;
    bool fresh_voice;
    bool destroyed;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_reject_voice.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, control_key));
    ASSERT_TRUE(world_make_control_pending(&fixture, control_key, 89u));
    (void)core_app_net_transport_world_open_for_test(fixture.transport, rejected_key);
    rejected_slot = core_app_net_transport_world_slot_for_test(fixture.transport, rejected_key);
    ASSERT_TRUE(rejected_slot >= 0);
    ASSERT_TRUE(core_app_net_transport_authenticate_for_test(fixture.transport, rejected_key));
    ASSERT_TRUE(core_app_net_transport_seed_physics_for_test(fixture.transport, rejected_key));

    memset(&frame, 0, sizeof(frame));
    frame.sequence = 9u;
    frame.sample_rate = 48000u;
    frame.channels = 1u;
    frame.sample_count = BREAK_VOICE_MAX_SAMPLES;
    for (u32 i = 0u; i < frame.sample_count; ++i) frame.samples[i] = (i16)(i * 17u);
    ASSERT_EQ(break_voice_encode(&frame, voice_wire, sizeof(voice_wire), &voice_size),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_voice_mute_encode(77u, true, mute_wire, sizeof(mute_wire), &mute_size),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_EQ(core_app_clock_probe_encode(&clock_request, clock_wire, sizeof(clock_wire),
                                          &clock_size),
              CORE_APP_SNAPSHOT_OK);
    ASSERT_TRUE(break_net_reactor_enqueue_message_for_test(
        fixture.reactor, rejected_key, BREAK_NET_MESSAGE_ID_CORE_VOICE, 1u,
        voice_wire, voice_size));
    ASSERT_TRUE(break_net_reactor_enqueue_message_for_test(
        fixture.reactor, rejected_key, CORE_APP_VOICE_MUTE_MESSAGE_ID, 1u,
        mute_wire, mute_size));
    ASSERT_TRUE(break_net_reactor_enqueue_message_for_test(
        fixture.reactor, rejected_key, CORE_APP_CLOCK_PROBE_MESSAGE_ID, 1u,
        clock_wire, clock_size));
    core_app_net_transport_pump_for_test(fixture.transport);
    ASSERT_TRUE(core_app_net_transport_connection_for_test(fixture.transport,
                                                           (u32)rejected_slot, &old_view));
    ASSERT_TRUE(old_view.authenticated);
    ASSERT_NEQ(old_view.session_id, 0u);
    ASSERT_NOT_NULL(old_view.voice_receiver);
    ASSERT_EQ(old_view.voice_accepted, 1u);
    ASSERT_EQ(old_view.voice_played, 0u);
    ASSERT_TRUE(old_view.voice_rate_ready);
    ASSERT_EQ(old_view.voice_mute_count, 1u);
    ASSERT_TRUE(old_view.clock_probe_pending);
    ASSERT_TRUE(old_view.physics_baseline_owned);
    ASSERT_TRUE(old_view.correction_pending);
    ASSERT_TRUE(old_view.world_admission_pending);

    adapter = core_app_net_transport_world_adapter(fixture.transport);
    break_runtime_world_session_set_next_connection_epoch_for_test(adapter, 0u);
    world_clear_outbound(&fixture);
    core_app_net_transport_world_drain_for_test(fixture.transport, 21u);
    rejected_epoch_absent =
        !break_runtime_world_session_connection_epoch(adapter, rejected_key, &epoch);
    rejected_cleaned = core_app_net_transport_connection_for_test(
                           fixture.transport, (u32)rejected_slot, &old_view) &&
                       old_view.key == 0u && !old_view.authenticated &&
                       old_view.session_id == 0u &&
                       old_view.session_state != (int)BREAK_SESSION_AUTHENTICATED &&
                       !old_view.world_open && !old_view.world_admission_pending &&
                       old_view.world_transition_kind == 0u &&
                       old_view.world_diagnostic == NULL &&
                       old_view.world_pending_diagnostic == NULL &&
                       old_view.voice_receiver == NULL && !old_view.voice_rate_ready &&
                       old_view.voice_mute_count == 0u && !old_view.clock_probe_pending &&
                       !old_view.physics_baseline_owned && old_view.physics_baseline_size == 0u &&
                       !old_view.correction_pending;

    break_runtime_world_session_set_next_connection_epoch_for_test(adapter, 1000u);
    reused_open = core_app_net_transport_world_open_for_test(fixture.transport, new_key);
    reused_slot = core_app_net_transport_world_slot_for_test(fixture.transport, new_key);
    reused_clean = reused_open && reused_slot == rejected_slot &&
                   core_app_net_transport_connection_for_test(
                       fixture.transport, (u32)reused_slot, &reused_view) &&
                   reused_view.world_open && reused_view.world_epoch != 0u &&
                   reused_view.world_diagnostic != NULL && reused_view.voice_receiver == NULL &&
                   !reused_view.voice_rate_ready && reused_view.voice_mute_count == 0u &&
                   !reused_view.clock_probe_pending && reused_view.clock_samples == 0u &&
                   !reused_view.physics_baseline_owned && !reused_view.correction_pending;

    ASSERT_TRUE(core_app_net_transport_authenticate_for_test(fixture.transport, new_key));
    frame.sequence = 10u;
    ASSERT_EQ(break_voice_encode(&frame, voice_wire, sizeof(voice_wire), &voice_size),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(break_net_reactor_enqueue_message_for_test(
        fixture.reactor, new_key, BREAK_NET_MESSAGE_ID_CORE_VOICE, 1u,
        voice_wire, voice_size));
    core_app_net_transport_pump_for_test(fixture.transport);
    fresh_voice = core_app_net_transport_connection_for_test(
                      fixture.transport, (u32)reused_slot, &reused_view) &&
                  reused_view.authenticated && reused_view.voice_receiver != NULL &&
                  reused_view.voice_accepted == 1u && reused_view.voice_played == 0u &&
                  reused_view.voice_rate_ready && reused_view.voice_mute_count == 0u &&
                  !reused_view.clock_probe_pending;
    destroyed = transport_fixture_destroy(&fixture);
    aspect_fixture_dispose(&fixture);
    ASSERT_TRUE(destroyed);
    ASSERT_TRUE(rejected_epoch_absent);
    ASSERT_TRUE(rejected_cleaned);
    ASSERT_TRUE(reused_open);
    ASSERT_TRUE(reused_clean);
    ASSERT_TRUE(fresh_voice);
}

TEST(world_transport_open_copies_fixed_pod_entities_independently) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    CoreAppNetAspectTestView aspect;
    BreakReplicationSessionBridgeStats bridge;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_open.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, 0x140au));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_TRUE(view.enabled);
    ASSERT_TRUE(view.created);
    ASSERT_NOT_NULL(view.schemas);
    ASSERT_NOT_NULL(view.authoritative);
    ASSERT_NOT_NULL(view.diagnostic);
    ASSERT_NOT_NULL(view.session);
    ASSERT_TRUE(view.authoritative != view.diagnostic);
    ASSERT_EQ(view.level_generation, 9u);
    ASSERT_EQ(view.objects[0].index, 1u);
    ASSERT_EQ(view.objects[0].generation, 1u);
    ASSERT_EQ(view.objects[1].index, 2u);
    ASSERT_EQ(view.objects[1].generation, 1u);
    ASSERT_NEQ(break_schema_hash(view.schemas), 0u);
    ASSERT_EQ(break_world_entity_count(view.authoritative), 2u);
    ASSERT_EQ(break_world_entity_count(view.diagnostic), 0u);
    ASSERT_EQ(*(const u32 *)world_get_component(view.authoritative, view.objects[0], 1u), 7u);
    ASSERT_EQ(*(const u32 *)world_get_component(view.authoritative, view.objects[0], 2u), 3u);
    ASSERT_EQ(*(const f32 *)world_get_component(view.authoritative, view.objects[0], 3u), 1.5f);
    ASSERT_EQ(*(const f32 *)world_get_component(view.authoritative, view.objects[1], 5u), 6.0f);
    ASSERT_EQ(*(const u32 *)world_get_component(view.authoritative, view.objects[1], 6u), 22u);
    break_replication_session_bridge_stats(break_world_session_bridge(view.session), &bridge);
    ASSERT_EQ(bridge.connections, 1u);
    ASSERT_EQ(view.opened, 1u);
    ASSERT_EQ(view.closed, 0u);
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &aspect));
    ASSERT_FALSE(aspect.enabled);
    ASSERT_FALSE(aspect.created);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_transport_bounded_tick_and_shutdown_drain_only_fill_diagnostic_world) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakWorldSessionStats stats;
    BreakWorldSnapshot *first;
    BreakWorldSnapshot *second;
    BreakWorldSnapshot *third;
    u32 *authoritative_index;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_drain.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, 0x240au));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    authoritative_index = (u32 *)world_get_component(view.authoritative, view.objects[0], 1u);
    ASSERT_NOT_NULL(authoritative_index);
    *authoritative_index = 70u;
    first = break_world_snapshot_build(view.authoritative, view.schemas, 20u);
    ASSERT_NOT_NULL(first);
    *authoritative_index = 71u;
    second = break_world_snapshot_build(view.authoritative, view.schemas, 30u);
    ASSERT_NOT_NULL(second);
    *authoritative_index = 7u;
    ASSERT_TRUE(world_queue_full(&fixture, 0x240au, first, 90u));
    ASSERT_TRUE(world_queue_full(&fixture, 0x240au, second, 91u));
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.bridge.completion_count, 2u);
    ASSERT_EQ(stats.applied_packets, 0u);
    ASSERT_EQ(break_world_entity_count(view.diagnostic), 0u);

    world_fixture_tick(&fixture);
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.applied_packets, 1u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.drained_packets, 1u);
    ASSERT_EQ(stats.bridge.completion_count, 1u);
    ASSERT_EQ(*(const u32 *)world_get_component(view.diagnostic, view.objects[0], 1u), 70u);
    ASSERT_EQ(*authoritative_index, 8u);

    world_fixture_tick(&fixture);
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.applied_packets, 2u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    ASSERT_EQ(*(const u32 *)world_get_component(view.diagnostic, view.objects[0], 1u), 71u);
    ASSERT_EQ(*authoritative_index, 9u);

    *authoritative_index = 72u;
    third = break_world_snapshot_build(view.authoritative, view.schemas, 40u);
    ASSERT_NOT_NULL(third);
    *authoritative_index = 9u;
    ASSERT_TRUE(world_queue_full(&fixture, 0x240au, third, 92u));
    ASSERT_EQ(fixture.hooks.stop_admission(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.stop_producers(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.hooks.drain(fixture.hooks.user), BREAK_RUNTIME_OK);
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.applied_packets, 3u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_TRUE(view.diagnostic == NULL);
    ASSERT_EQ(*authoritative_index, 9u);
    break_world_snapshot_release(third);
    break_world_snapshot_release(second);
    break_world_snapshot_release(first);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    ASSERT_TRUE(trace_contains(fixture.trace,
        "event=network_world_stats opened=1 closed=1 applied=3 need_full=0 rejected=0"
        " full_publishes=0 delta_publishes=0 sent_fragments=0 queue_depth=0 dropped=0"));
    aspect_fixture_dispose(&fixture);
}

TEST(world_transport_local_ack_uses_adapter_exactly_once) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    BreakWorldSnapshot *snapshot;
    BreakNetOwnedMessage outbound;
    BreakConnectionKey outbound_key = 0u;
    const BreakConnectionKey key = 0x340au;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_local_ack.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    snapshot = break_world_snapshot_build(view.authoritative, view.schemas, 20u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(world_queue_full(&fixture, key, snapshot, 70u));
    world_fixture_tick(&fixture);
    ASSERT_TRUE(world_next_control(&fixture, &outbound_key, &outbound));
    ASSERT_EQ(outbound_key, key);
    ASSERT_NEQ(outbound.correlation_id, 0u);
    ASSERT_TRUE(world_control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                              70u, break_world_snapshot_id(snapshot), 20u, 9u));
    break_net_message_release(&outbound);
    while (break_net_reactor_poll_outbound_for_test(fixture.reactor, &outbound_key, &outbound) ==
           BREAK_NET_EVENT_OK) {
        ASSERT_NEQ(outbound.message_id, BREAK_NET_MESSAGE_ID_WORLD_CONTROL);
        break_net_message_release(&outbound);
    }
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.submitted, 2u);
    ASSERT_EQ(stats.drained, 2u);
    ASSERT_EQ(stats.applied, 2u);
    ASSERT_EQ(stats.transport_overloads, 0u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    break_world_snapshot_release(snapshot);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_transport_local_control_retries_without_new_submit_or_duplicate) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    BreakWorldSnapshot *snapshot;
    BreakNetOwnedMessage outbound;
    BreakConnectionKey outbound_key = 0u;
    const BreakConnectionKey key = 0x340bu;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_local_retry.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    snapshot = break_world_snapshot_build(view.authoritative, view.schemas, 20u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(world_queue_full(&fixture, key, snapshot, 71u));
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, key, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    core_app_net_transport_world_drain_for_test(fixture.transport, 20u);
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.submitted, 2u);
    ASSERT_EQ(stats.transport_overloads, 1u);
    ASSERT_TRUE(stats.control_pending);
    world_clear_outbound(&fixture);

    core_app_net_transport_world_drain_for_test(fixture.transport, 21u);
    ASSERT_TRUE(world_next_control(&fixture, &outbound_key, &outbound));
    ASSERT_EQ(outbound_key, key);
    ASSERT_NEQ(outbound.correlation_id, 0u);
    ASSERT_TRUE(world_control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                              71u, break_world_snapshot_id(snapshot), 20u, 9u));
    break_net_message_release(&outbound);
    while (break_net_reactor_poll_outbound_for_test(fixture.reactor, &outbound_key, &outbound) ==
           BREAK_NET_EVENT_OK) {
        ASSERT_NEQ(outbound.message_id, BREAK_NET_MESSAGE_ID_WORLD_CONTROL);
        break_net_message_release(&outbound);
    }
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_EQ(stats.submitted, 2u);
    ASSERT_EQ(stats.transport_overloads, 1u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_EQ(stats.queued, 0u);
    break_world_snapshot_release(snapshot);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_transport_publishes_full_delta_and_need_full_from_confirmed_baseline) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakWorldSessionSenderState state;
    BreakWorldSessionStats stats;
    WorldAttempt initial;
    WorldAttempt delta;
    WorldAttempt recovered;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_publish.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, 0x440au));
    ASSERT_EQ(core_app_net_transport_world_publish_for_test(fixture.transport, 0x440au),
              BREAK_NET_SEND_OK);
    ASSERT_TRUE(world_collect_attempt(&fixture, 0x440au, NULL, 0u, &initial));
    ASSERT_EQ(initial.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(initial.delta_id, 1u);
    ASSERT_EQ(initial.base_snapshot_id, 0u);
    ASSERT_EQ(initial.target_tick, 1u);

    world_fixture_tick(&fixture);
    ASSERT_EQ(core_app_net_transport_world_publish_for_test(fixture.transport, 0x440au),
              BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_TRUE(world_send_control(&fixture, 0x440au, BREAK_WORLD_SESSION_CONTROL_ACK, &initial));
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_EQ(core_app_net_transport_world_publish_for_test(fixture.transport, 0x440au),
              BREAK_NET_SEND_OK);
    ASSERT_TRUE(world_collect_attempt(&fixture, 0x440au, NULL, 0u, &delta));
    ASSERT_EQ(delta.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(delta.delta_id, 2u);
    ASSERT_EQ(delta.base_snapshot_id, initial.target_snapshot_id);
    ASSERT_EQ(delta.target_tick, 2u);

    world_fixture_tick(&fixture);
    ASSERT_TRUE(world_send_control(&fixture, 0x440au, BREAK_WORLD_SESSION_CONTROL_NEED_FULL,
                                   &delta));
    ASSERT_EQ(core_app_net_transport_world_publish_for_test(fixture.transport, 0x440au),
              BREAK_NET_SEND_OK);
    ASSERT_TRUE(world_collect_attempt(&fixture, 0x440au, NULL, 0u, &recovered));
    ASSERT_EQ(recovered.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(recovered.delta_id, 3u);
    ASSERT_EQ(recovered.base_snapshot_id, 0u);
    ASSERT_EQ(recovered.target_tick, 3u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.published_full_packets, 2u);
    ASSERT_EQ(stats.published_delta_packets, 1u);
    ASSERT_TRUE(break_world_session_sender_state(view.session, 0x440au, &state));
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_EQ(state.next_delta_id, 4u);
    ASSERT_TRUE(view.sent_fragments >= 3u);
    ASSERT_EQ(view.terminal_errors, 0u);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    ASSERT_TRUE(trace_contains(fixture.trace,
        "full_publishes=2 delta_publishes=1"));
    aspect_fixture_dispose(&fixture);
}

TEST(world_transport_overload_resumes_the_same_immutable_attempt) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakWorldSnapshot *expected;
    BreakWorldSnapshot *changed;
    BreakWorldSessionSenderState state;
    BreakWorldSessionStats stats;
    WorldAttempt attempt;
    u8 first_wire[256];
    usize first_size = 0u;
    bool found_first = false;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_overload.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, 0x540au));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    expected = break_world_snapshot_build(view.authoritative, view.schemas, 1u);
    ASSERT_NOT_NULL(expected);
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY - 1u; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, 0x540au,
                                         BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(core_app_net_transport_world_publish_for_test(fixture.transport, 0x540au),
              BREAK_NET_SEND_OVERLOAD);
    ASSERT_TRUE(break_world_session_sender_state(view.session, 0x540au, &state));
    ASSERT_TRUE(state.attempt_pending);
    ASSERT_EQ(state.next_delta_id, 2u);
    ASSERT_EQ(state.history_count, 0u);
    while (true) {
        BreakConnectionKey outbound_key = 0u;
        BreakNetOwnedMessage outbound;
        if (break_net_reactor_poll_outbound_for_test(fixture.reactor, &outbound_key,
                                                     &outbound) != BREAK_NET_EVENT_OK) {
            break;
        }
        if (outbound.message_id == BREAK_NET_MESSAGE_ID_WORLD_DELTA) {
            ASSERT_FALSE(found_first);
            ASSERT_TRUE(outbound.size <= sizeof(first_wire));
            memcpy(first_wire, outbound.data, outbound.size);
            first_size = outbound.size;
            found_first = true;
        }
        break_net_message_release(&outbound);
    }
    ASSERT_TRUE(found_first);
    world_fixture_tick(&fixture);
    changed = break_world_snapshot_build(view.authoritative, view.schemas, 2u);
    ASSERT_NOT_NULL(changed);
    ASSERT_NEQ(break_world_snapshot_id(changed), break_world_snapshot_id(expected));
    ASSERT_EQ(core_app_net_transport_world_publish_for_test(fixture.transport, 0x540au),
              BREAK_NET_SEND_OK);
    ASSERT_TRUE(world_collect_attempt(&fixture, 0x540au, first_wire, first_size, &attempt));
    ASSERT_EQ(attempt.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(attempt.delta_id, 1u);
    ASSERT_EQ(attempt.target_snapshot_id, break_world_snapshot_id(expected));
    ASSERT_EQ(attempt.target_tick, 1u);
    ASSERT_NEQ(attempt.target_snapshot_id, break_world_snapshot_id(changed));
    ASSERT_TRUE(break_world_session_sender_state(view.session, 0x540au, &state));
    ASSERT_FALSE(state.attempt_pending);
    ASSERT_EQ(state.history_count, 1u);
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.published_full_packets, 1u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_TRUE(view.sent_fragments > 1u);
    ASSERT_EQ(view.terminal_errors, 0u);
    break_world_snapshot_release(changed);
    break_world_snapshot_release(expected);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_transport_terminal_error_releases_attempt_and_counts_drop) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakWorldSessionSenderState state;
    BreakWorldSessionStats stats;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_terminal.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, 0x640au));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY - 1u; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, 0x640au,
                                         BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(core_app_net_transport_world_publish_for_test(fixture.transport, 0x640au),
              BREAK_NET_SEND_OVERLOAD);
    ASSERT_TRUE(break_world_session_sender_state(view.session, 0x640au, &state));
    ASSERT_TRUE(state.attempt_pending);
    while (true) {
        BreakConnectionKey outbound_key = 0u;
        BreakNetOwnedMessage outbound;
        if (break_net_reactor_poll_outbound_for_test(fixture.reactor, &outbound_key,
                                                     &outbound) != BREAK_NET_EVENT_OK) {
            break;
        }
        break_net_message_release(&outbound);
    }
    ASSERT_TRUE(break_net_reactor_stop(fixture.reactor, 1000u));
    ASSERT_EQ(core_app_net_transport_world_publish_for_test(fixture.transport, 0x640au),
              BREAK_NET_SEND_CLOSED);
    ASSERT_TRUE(break_world_session_sender_state(view.session, 0x640au, &state));
    ASSERT_FALSE(state.attempt_pending);
    ASSERT_EQ(state.history_count, 0u);
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.published_full_packets, 0u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.sent_fragments, 1u);
    ASSERT_EQ(view.terminal_errors, 1u);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    ASSERT_TRUE(trace_contains(fixture.trace,
        "full_publishes=0 delta_publishes=0 sent_fragments=1 queue_depth=0 dropped=1"));
    aspect_fixture_dispose(&fixture);
}

static BreakWorldSnapshot *world_snapshot_with_index(CoreAppNetWorldTestView *view,
                                                     u32 value, u64 tick) {
    u32 *index = (u32 *)world_get_component(view->authoritative, view->objects[0], 1u);
    if (!index) return NULL;
    *index = value;
    return break_world_snapshot_build(view->authoritative, view->schemas, tick);
}

TEST(world_transport_two_connections_isolate_diagnostic_world_and_reopen) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakWorldSessionStats stats;
    BreakWorldSnapshot *snapshot;
    World *diagnostic_a;
    World *diagnostic_b;
    const BreakConnectionKey key_a = 0x250au;
    const BreakConnectionKey key_b = 0x350au;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_isolation.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, key_a));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    diagnostic_a = view.diagnostic;
    ASSERT_NOT_NULL(diagnostic_a);
    ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(fixture.reactor, key_b));
    world_fixture_tick(&fixture);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.open_count, 2u);
    diagnostic_b = view.diagnostic;
    ASSERT_NOT_NULL(diagnostic_b);

    snapshot = world_snapshot_with_index(&view, 70u, 20u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(world_queue_full(&fixture, key_a, snapshot, 70u));
    break_world_snapshot_release(snapshot);
    world_fixture_tick(&fixture);
    ASSERT_EQ(*(const u32 *)world_get_component(diagnostic_a, view.objects[0], 1u), 70u);

    snapshot = world_snapshot_with_index(&view, 71u, 21u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(world_queue_full(&fixture, key_b, snapshot, 71u));
    break_world_snapshot_release(snapshot);
    world_fixture_tick(&fixture);
    ASSERT_EQ(*(const u32 *)world_get_component(diagnostic_a, view.objects[0], 1u), 70u);
    ASSERT_EQ(*(const u32 *)world_get_component(diagnostic_b, view.objects[0], 1u), 71u);
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.applied_packets, 2u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.need_full_packets, 0u);

    snapshot = world_snapshot_with_index(&view, 72u, 22u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(world_queue_full(&fixture, key_a, snapshot, 72u));
    break_world_snapshot_release(snapshot);
    snapshot = world_snapshot_with_index(&view, 81u, 23u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(world_queue_full(&fixture, key_b, snapshot, 81u));
    break_world_snapshot_release(snapshot);
    world_fixture_tick(&fixture);
    ASSERT_EQ(*(const u32 *)world_get_component(diagnostic_a, view.objects[0], 1u), 72u);
    ASSERT_EQ(*(const u32 *)world_get_component(diagnostic_b, view.objects[0], 1u), 81u);
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.applied_packets, 4u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.need_full_packets, 0u);

    diagnostic_a = core_app_net_transport_world_reopen_for_test(fixture.transport, key_a);
    ASSERT_NOT_NULL(diagnostic_a);
    ASSERT_EQ(break_world_entity_count(diagnostic_a), 0u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.open_count, 2u);
    ASSERT_EQ(view.opened, 3u);
    ASSERT_EQ(view.closed, 1u);
    ASSERT_TRUE(view.diagnostic == diagnostic_b);
    ASSERT_EQ(break_world_entity_count(diagnostic_a), 0u);
    ASSERT_EQ(*(const u32 *)world_get_component(diagnostic_b, view.objects[0], 1u), 81u);

    snapshot = world_snapshot_with_index(&view, 80u, 30u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(world_queue_full(&fixture, key_a, snapshot, 80u));
    break_world_snapshot_release(snapshot);
    snapshot = world_snapshot_with_index(&view, 91u, 31u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(world_queue_full(&fixture, key_b, snapshot, 91u));
    break_world_snapshot_release(snapshot);
    world_fixture_tick(&fixture);
    ASSERT_EQ(*(const u32 *)world_get_component(diagnostic_a, view.objects[0], 1u), 80u);
    ASSERT_EQ(*(const u32 *)world_get_component(diagnostic_b, view.objects[0], 1u), 91u);
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.applied_packets, 6u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.need_full_packets, 0u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);

    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.open_count, 0u);
    ASSERT_EQ(view.closed, 3u);
    ASSERT_TRUE(view.diagnostic == NULL);
    ASSERT_TRUE(trace_contains(fixture.trace,
        "event=network_world_stats opened=3 closed=3 applied=6 need_full=0 rejected=0"));
    aspect_fixture_dispose(&fixture);
}

TEST(world_transport_open_failure_rolls_back_aspect_and_world) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView world;
    CoreAppNetAspectTestView aspect;
    BreakReplicationSessionBridgeStats bridge;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_rollback.port", true, true));
    world_fixture_tick(&fixture);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &world));
    ASSERT_TRUE(break_world_session_open(world.session, 0x740au));
    ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(fixture.reactor, 0x740au));
    world_fixture_tick(&fixture);
    break_replication_session_bridge_stats(break_world_session_bridge(world.session), &bridge);
    ASSERT_EQ(bridge.connections, 1u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &world));
    ASSERT_EQ(world.open_count, 0u);
    ASSERT_EQ(world.opened, 0u);
    ASSERT_EQ(world.closed, 0u);
    ASSERT_TRUE(world.diagnostic == NULL);
    ASSERT_TRUE(core_app_net_transport_aspect_for_test(fixture.transport, &aspect));
    ASSERT_EQ(aspect.open_count, 0u);
    ASSERT_EQ(aspect.opened, 1u);
    ASSERT_EQ(aspect.closed, 1u);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    ASSERT_TRUE(trace_contains(fixture.trace, "event=network_stats opened=0 closed=0 refused=1"));
    ASSERT_TRUE(trace_contains(fixture.trace, "event=network_world_stats opened=0 closed=0"));
    aspect_fixture_dispose(&fixture);
}

TEST(world_adapter_created_rollback_drains_before_network_destroy) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    BreakWorldSnapshot *snapshot;
    const BreakConnectionKey key = 0x840du;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_created_rollback.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    snapshot = break_world_snapshot_build(view.authoritative, view.schemas, 20u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(world_queue_full(&fixture, key, snapshot, 73u));
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, key, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    core_app_net_transport_world_drain_for_test(fixture.transport, 20u);
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_TRUE(stats.control_pending);
    ASSERT_EQ(break_runtime_coordinator_state(fixture.world_coordinator), BREAK_RUNTIME_CREATED);

    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_TIMEOUT);
    ASSERT_TRUE(core_app_net_transport_world_adapter(fixture.transport) == adapter);
    ASSERT_TRUE(core_app_net_transport_reactor_for_test(fixture.transport) == fixture.reactor);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_TRUE(view.created);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_TRUE(stats.control_pending);
    ASSERT_TRUE(break_runtime_bus_kind_accepts(
        fixture.world_bus, BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND, 1u,
        sizeof(BreakRuntimeWorldCommand)));

    world_clear_outbound(&fixture);
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(core_app_net_transport_world_adapter(fixture.transport) == NULL);
    ASSERT_TRUE(core_app_net_transport_reactor_for_test(fixture.transport) == NULL);
    break_world_snapshot_release(snapshot);
    break_runtime_coordinator_destroy(fixture.world_coordinator);
    fixture.world_coordinator = NULL;
    break_runtime_bus_destroy(fixture.world_bus);
    fixture.world_bus = NULL;
    aspect_fixture_dispose(&fixture);
}

TEST(world_adapter_failed_rollback_drains_before_network_destroy) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakRuntimeWorldSessionStats stats;
    BreakWorldSnapshot *snapshot;
    const BreakConnectionKey key = 0x840cu;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_failed_rollback.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    snapshot = break_world_snapshot_build(view.authoritative, view.schemas, 20u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(world_queue_full(&fixture, key, snapshot, 72u));
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, key, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    core_app_net_transport_world_drain_for_test(fixture.transport, 20u);
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_TRUE(stats.control_pending);
    ASSERT_EQ(break_runtime_coordinator_start(fixture.world_coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_stop(fixture.world_coordinator), BREAK_RUNTIME_TIMEOUT);
    ASSERT_TRUE(core_app_net_transport_world_adapter(fixture.transport) == adapter);
    ASSERT_TRUE(core_app_net_transport_reactor_for_test(fixture.transport) == fixture.reactor);
    ASSERT_EQ(break_runtime_coordinator_fail(fixture.world_coordinator, BREAK_RUNTIME_FAILED),
              BREAK_RUNTIME_OK);

    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_TIMEOUT);
    ASSERT_TRUE(core_app_net_transport_world_adapter(fixture.transport) == adapter);
    ASSERT_TRUE(core_app_net_transport_reactor_for_test(fixture.transport) == fixture.reactor);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_TRUE(view.created);
    break_runtime_world_session_stats(adapter, &stats);
    ASSERT_TRUE(stats.control_pending);
    ASSERT_TRUE(break_runtime_bus_kind_accepts(
        fixture.world_bus, BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND, 1u,
        sizeof(BreakRuntimeWorldCommand)));
    world_clear_outbound(&fixture);
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(core_app_net_transport_world_adapter(fixture.transport) == NULL);
    ASSERT_TRUE(core_app_net_transport_reactor_for_test(fixture.transport) == NULL);
    break_world_snapshot_release(snapshot);
    break_runtime_coordinator_destroy(fixture.world_coordinator);
    fixture.world_coordinator = NULL;
    break_runtime_bus_destroy(fixture.world_bus);
    fixture.world_bus = NULL;
    aspect_fixture_dispose(&fixture);
}

TEST(world_adapter_destroy_clears_pointer_before_network_timeout) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter_before_stop;
    BreakRuntimeWorldSession *adapter_after_stop;
    StepThreadArgs args;
    pthread_t thread;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_network_timeout.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, 0x840bu));
    adapter_before_stop = core_app_net_transport_world_adapter(fixture.transport);
    ASSERT_NOT_NULL(adapter_before_stop);
    ASSERT_EQ(break_runtime_coordinator_start(fixture.world_coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_stop(fixture.world_coordinator), BREAK_RUNTIME_OK);
    adapter_after_stop = core_app_net_transport_world_adapter(fixture.transport);
    ASSERT_TRUE(adapter_after_stop == NULL);
    ASSERT_TRUE(break_runtime_bus_kind_accepts(
        fixture.world_bus, BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND, 1u,
        sizeof(BreakRuntimeWorldCommand)));
    ASSERT_TRUE(break_net_reactor_step_delay_for_test(fixture.reactor, 1500u));
    memset(&args, 0, sizeof(args));
    args.reactor = fixture.reactor;
    ASSERT_EQ(pthread_create(&thread, NULL, step_thread_main, &args), 0);
    {
        const struct timespec pause = {0, 50000000L};
        nanosleep(&pause, NULL);
    }
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_TIMEOUT);
    ASSERT_TRUE(core_app_net_transport_world_adapter(fixture.transport) == adapter_after_stop);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_FALSE(view.created);
    ASSERT_TRUE(view.session == NULL);
    ASSERT_TRUE(core_app_net_transport_reactor_for_test(fixture.transport) == fixture.reactor);
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_TIMEOUT);
    core_app_net_transport_free(fixture.transport);
    ASSERT_EQ(pthread_join(thread, NULL), 0);
    ASSERT_TRUE(core_app_net_transport_reclaim_for_test(fixture.transport));
    fixture.transport = NULL;
    break_runtime_coordinator_destroy(fixture.world_coordinator);
    fixture.world_coordinator = NULL;
    break_runtime_bus_destroy(fixture.world_bus);
    fixture.world_bus = NULL;
    ASSERT_TRUE(adapter_after_stop == NULL);
    aspect_fixture_dispose(&fixture);
}

TEST(world_transport_destroy_releases_enabled_state) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_destroy.port", true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, 0x840au));
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_TRUE(view.enabled);
    ASSERT_FALSE(view.created);
    ASSERT_TRUE(view.schemas == NULL);
    ASSERT_TRUE(view.authoritative == NULL);
    ASSERT_TRUE(view.diagnostic == NULL);
    ASSERT_TRUE(view.session == NULL);
    ASSERT_EQ(view.open_count, 0u);
    ASSERT_EQ(view.opened, 1u);
    ASSERT_EQ(view.closed, 1u);
    ASSERT_TRUE(core_app_net_transport_reactor_for_test(fixture.transport) == NULL);
    ASSERT_TRUE(trace_contains(fixture.trace, "event=network_world_stats opened=1 closed=1"));
    aspect_fixture_dispose(&fixture);
}

static void world_fixture_tick_with_index(AspectTransportFixture *fixture, u32 index) {
    const CoreAppSnapshotEntity entities[2] = {
        {index, 3u, 1.5f, -2.0f, 3.25f, 11u},
        {8u, 4u, -4.0f, 5.5f, 6.0f, 22u},
    };
    fixture->tick++;
    fixture->hooks.tick(fixture->hooks.user, fixture->tick, 9u, entities, 2u, 0u);
}

static bool world_fixture_welcome(AspectTransportFixture *fixture, BreakConnectionKey key) {
    CoreAppNetConnectionTestView connection;
    int slot = core_app_net_transport_world_slot_for_test(fixture->transport, key);
    if (slot < 0 || !core_app_net_transport_authenticate_for_test(fixture->transport, key)) {
        return false;
    }
    world_fixture_tick(fixture);
    return core_app_net_transport_connection_for_test(fixture->transport, (u32)slot,
                                                      &connection) &&
           connection.authenticated;
}

static usize world_outbound_deltas_for(AspectTransportFixture *fixture, BreakConnectionKey key) {
    BreakConnectionKey outbound_key = 0u;
    BreakNetOwnedMessage message;
    usize count = 0u;
    while (break_net_reactor_poll_outbound_for_test(fixture->reactor, &outbound_key, &message) ==
           BREAK_NET_EVENT_OK) {
        if (outbound_key == key && message.message_id == BREAK_NET_MESSAGE_ID_WORLD_DELTA) {
            count++;
        }
        break_net_message_release(&message);
    }
    return count;
}

TEST(world_publication_default_off_creates_nothing) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView world;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_publication_off.port", false,
                                    false));
    ASSERT_TRUE(core_app_net_transport_world_publication(fixture.transport) == NULL);
    world_fixture_tick(&fixture);
    ASSERT_TRUE(core_app_net_transport_world_publication(fixture.transport) == NULL);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &world));
    ASSERT_EQ(world.snapshot_build_failures, 0u);
    ASSERT_EQ(world.publish_rejected, 0u);
    ASSERT_EQ(world.notice_overloads, 0u);
    ASSERT_TRUE(core_app_net_transport_world_publication(NULL) == NULL);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_publication_runtime_path_gates_on_auth_and_waits_for_ack) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldSession *adapter;
    BreakWorldSnapshotPublication *publication;
    BreakRuntimeWorldPublishProgress progress;
    BreakRuntimeWorldConnectionSnapshot snapshot;
    BreakWorldSessionStats stats;
    WorldAttempt initial;
    WorldAttempt delta;
    BreakWorldSnapshotLease lease;
    const BreakConnectionKey key = 0x940au;

    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_publication_on.port", true, false));
    publication = core_app_net_transport_world_publication(fixture.transport);
    ASSERT_NOT_NULL(publication);
    adapter = core_app_net_transport_world_adapter(fixture.transport);
    ASSERT_NOT_NULL(adapter);
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_EQ(break_runtime_world_session_connection_snapshots(adapter, &snapshot, 1u), 1u);
    ASSERT_FALSE(snapshot.publish_ready);

    world_fixture_tick(&fixture);
    ASSERT_EQ(world_outbound_deltas_for(&fixture, key), 0u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.published_full_packets, 0u);

    ASSERT_TRUE(world_fixture_welcome(&fixture, key));
    world_clear_outbound(&fixture);
    world_fixture_tick(&fixture);
    ASSERT_TRUE(world_collect_attempt(&fixture, key, NULL, 0u, &initial));
    ASSERT_EQ(initial.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(initial.delta_id, 1u);
    ASSERT_EQ(break_runtime_world_session_connection_snapshots(adapter, &snapshot, 1u), 1u);
    ASSERT_TRUE(snapshot.publish_ready);
    ASSERT_NEQ(snapshot.completed_publication_epoch, 0u);
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
    ASSERT_EQ(lease.publication_epoch, snapshot.completed_publication_epoch);
    ASSERT_EQ(lease.level_generation, 9u);
    ASSERT_EQ(break_world_snapshot_id(lease.snapshot), initial.target_snapshot_id);
    break_world_snapshot_lease_release(&lease);

    world_fixture_tick_with_index(&fixture, 99u);
    world_fixture_tick_with_index(&fixture, 100u);
    ASSERT_EQ(world_outbound_deltas_for(&fixture, key), 0u);
    ASSERT_TRUE(break_runtime_world_session_publish_progress(adapter, &progress));
    ASSERT_EQ(progress.dirty_connections, 0u);
    ASSERT_FALSE(progress.continuation_pending);

    ASSERT_TRUE(world_send_control(&fixture, key, BREAK_WORLD_SESSION_CONTROL_ACK, &initial));
    world_fixture_tick_with_index(&fixture, 101u);
    ASSERT_TRUE(world_collect_attempt(&fixture, key, NULL, 0u, &delta));
    ASSERT_EQ(delta.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(delta.delta_id, 2u);
    ASSERT_EQ(delta.base_snapshot_id, initial.target_snapshot_id);

    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    break_world_session_stats(view.session, &stats);
    ASSERT_EQ(stats.published_full_packets, 1u);
    ASSERT_EQ(stats.published_delta_packets, 1u);
    ASSERT_EQ(view.snapshot_build_failures, 0u);
    ASSERT_EQ(view.publish_rejected, 0u);
    ASSERT_EQ(view.notice_overloads, 0u);
    ASSERT_EQ(view.terminal_errors, 0u);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    ASSERT_TRUE(core_app_net_transport_world_publication(fixture.transport) == NULL);
    aspect_fixture_dispose(&fixture);
}

TEST(world_publication_snapshot_build_failure_counts_and_recovers) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    WorldAttempt initial;
    const BreakConnectionKey key = 0x940bu;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_publication_fail.port", true,
                                    false));
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(world_fixture_welcome(&fixture, key));
    world_clear_outbound(&fixture);
    core_app_net_transport_world_fail_next_build_for_test(fixture.transport);
    world_fixture_tick(&fixture);
    ASSERT_EQ(world_outbound_deltas_for(&fixture, key), 0u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.snapshot_build_failures, 1u);
    ASSERT_EQ(view.publish_rejected, 0u);
    world_fixture_tick(&fixture);
    ASSERT_TRUE(world_collect_attempt(&fixture, key, NULL, 0u, &initial));
    ASSERT_EQ(initial.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.snapshot_build_failures, 1u);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_publication_restarted_tick_keeps_publishing) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    WorldAttempt initial;
    WorldAttempt next;
    const BreakConnectionKey key = 0x940cu;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_publication_tick.port", true,
                                    false));
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(world_fixture_welcome(&fixture, key));
    world_clear_outbound(&fixture);
    fixture.tick = 40u;
    world_fixture_tick(&fixture);
    ASSERT_TRUE(world_collect_attempt(&fixture, key, NULL, 0u, &initial));
    ASSERT_EQ(initial.target_tick, 41u);
    ASSERT_TRUE(world_send_control(&fixture, key, BREAK_WORLD_SESSION_CONTROL_ACK, &initial));
    fixture.tick = 0u;
    world_fixture_tick_with_index(&fixture, 55u);
    ASSERT_TRUE(world_collect_attempt(&fixture, key, NULL, 0u, &next));
    ASSERT_EQ(next.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(next.target_tick, 42u);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.publish_rejected, 0u);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_publication_legacy_switch_skips_runtime_notice) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakRuntimeWorldPublishProgress progress;
    BreakRuntimeWorldSessionStats stats;
    WorldAttempt initial;
    const BreakConnectionKey key = 0x940du;
    memset(&fixture, 0, sizeof(fixture));
    fixture.config.world_use_legacy_publish = true;
    ASSERT_TRUE(world_fixture_start_with(&fixture, "core_app_world_publication_legacy.port",
                                         true, false));
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(world_fixture_welcome(&fixture, key));
    world_clear_outbound(&fixture);
    world_fixture_tick(&fixture);
    ASSERT_TRUE(world_collect_attempt(&fixture, key, NULL, 0u, &initial));
    ASSERT_EQ(initial.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_TRUE(break_runtime_world_session_publish_progress(
        core_app_net_transport_world_adapter(fixture.transport), &progress));
    ASSERT_EQ(progress.observed_publication_epoch, 0u);
    break_runtime_world_session_stats(core_app_net_transport_world_adapter(fixture.transport),
                                      &stats);
    ASSERT_FALSE(stats.publish_pending);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    ASSERT_EQ(view.terminal_errors, 0u);
    ASSERT_TRUE(transport_fixture_destroy(&fixture));
    aspect_fixture_dispose(&fixture);
}

TEST(world_publication_survives_adapter_destroy_timeout) {
    AspectTransportFixture fixture;
    CoreAppNetWorldTestView view;
    BreakWorldSnapshotPublication *publication;
    BreakWorldSnapshotLease lease;
    BreakWorldSnapshot *snapshot;
    const BreakConnectionKey key = 0x940eu;
    ASSERT_TRUE(world_fixture_start(&fixture, "core_app_world_publication_timeout.port", true,
                                    false));
    ASSERT_TRUE(world_fixture_open(&fixture, key));
    ASSERT_TRUE(world_fixture_welcome(&fixture, key));
    world_fixture_tick(&fixture);
    publication = core_app_net_transport_world_publication(fixture.transport);
    ASSERT_NOT_NULL(publication);
    ASSERT_TRUE(core_app_net_transport_world_for_test(fixture.transport, &view));
    snapshot = break_world_snapshot_build(view.authoritative, view.schemas, 20u);
    ASSERT_NOT_NULL(snapshot);
    ASSERT_TRUE(world_queue_full(&fixture, key, snapshot, 74u));
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        (void)break_net_reactor_send(fixture.reactor, key, BREAK_NET_MESSAGE_ID_PING, 1u, "x",
                                     1u);
    }
    core_app_net_transport_world_drain_for_test(fixture.transport, 20u);
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_TIMEOUT);
    ASSERT_TRUE(core_app_net_transport_world_publication(fixture.transport) == publication);
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
    break_world_snapshot_lease_release(&lease);
    world_clear_outbound(&fixture);
    ASSERT_EQ(fixture.hooks.destroy(fixture.hooks.user), BREAK_RUNTIME_OK);
    ASSERT_TRUE(core_app_net_transport_world_publication(fixture.transport) == NULL);
    break_world_snapshot_release(snapshot);
    break_runtime_coordinator_destroy(fixture.world_coordinator);
    fixture.world_coordinator = NULL;
    break_runtime_bus_destroy(fixture.world_bus);
    fixture.world_bus = NULL;
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
    RUN_TEST(world_transport_default_off_creates_no_state_or_trace);
    RUN_TEST(world_adapter_registration_rebaseline_and_reopen_epochs);
    RUN_TEST(world_adapter_submit_defers_open_close_and_fifo_controls);
    RUN_TEST(world_adapter_open_pending_control_reconciles_epoch_slot_and_diagnostic);
    RUN_TEST(world_adapter_reopen_pending_control_completes_second_open);
    RUN_TEST(world_adapter_close_pending_control_reconciles_epoch_slot_and_diagnostic);
    RUN_TEST(world_adapter_cancel_pending_open_after_disconnect_closes_original_key);
    RUN_TEST(world_adapter_disconnect_does_not_commit_old_open_to_reused_slot);
    RUN_TEST(world_adapter_close_failure_after_disconnect_is_not_misread_as_success);
    RUN_TEST(world_adapter_same_key_pending_close_defers_cross_slot_open);
    RUN_TEST(world_adapter_canceled_open_defers_same_key_cross_slot_open);
    RUN_TEST(world_adapter_rejected_pending_open_releases_connection_before_slot_reuse);
    RUN_TEST(world_transport_open_copies_fixed_pod_entities_independently);
    RUN_TEST(world_transport_bounded_tick_and_shutdown_drain_only_fill_diagnostic_world);
    RUN_TEST(world_transport_local_ack_uses_adapter_exactly_once);
    RUN_TEST(world_transport_local_control_retries_without_new_submit_or_duplicate);
    RUN_TEST(world_transport_publishes_full_delta_and_need_full_from_confirmed_baseline);
    RUN_TEST(world_transport_overload_resumes_the_same_immutable_attempt);
    RUN_TEST(world_transport_terminal_error_releases_attempt_and_counts_drop);
    RUN_TEST(world_transport_two_connections_isolate_diagnostic_world_and_reopen);
    RUN_TEST(world_transport_open_failure_rolls_back_aspect_and_world);
    RUN_TEST(world_adapter_created_rollback_drains_before_network_destroy);
    RUN_TEST(world_adapter_failed_rollback_drains_before_network_destroy);
    RUN_TEST(world_adapter_destroy_clears_pointer_before_network_timeout);
    RUN_TEST(world_transport_destroy_releases_enabled_state);
    RUN_TEST(world_publication_default_off_creates_nothing);
    RUN_TEST(world_publication_runtime_path_gates_on_auth_and_waits_for_ack);
    RUN_TEST(world_publication_snapshot_build_failure_counts_and_recovers);
    RUN_TEST(world_publication_restarted_tick_keeps_publishing);
    RUN_TEST(world_publication_legacy_switch_skips_runtime_notice);
    RUN_TEST(world_publication_survives_adapter_destroy_timeout);
TEST_MAIN_END()
