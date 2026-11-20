#include "test_quic_udp_proxy.h"

#include <snow/quic_ngtcp2.h>
#include <snow/udp_engine.h>

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PROXY_QUEUE_CAPACITY 32u
#define PROXY_UP 0u
#define PROXY_DOWN 1u

typedef struct {
    bool used;
    u64 ordinal;
    u64 due_ns;
    SnowTransportDatagramAddress destination;
    u32 length;
    u8 bytes[SNOW_QUIC_NGTCP2_MAX_PACKET];
} ProxyPacket;

typedef struct {
    TestQuicUdpProxySet *set;
    SnowSocketFd fd;
    u16 port;
    SnowTransportDatagramAddress server;
    SnowTransportDatagramAddress client;
    bool client_known;
    u64 next_ordinal;
    u64 received[TEST_QUIC_UDP_PROXY_STATS_DIRS];
    u64 dropped_by_direction[TEST_QUIC_UDP_PROXY_STATS_DIRS];
    u64 jittered_by_direction[TEST_QUIC_UDP_PROXY_STATS_DIRS];
    u64 forwarded;
    u64 dropped;
    u64 delayed;
    u64 reordered;
    u64 jittered;
    u32 random_state[TEST_QUIC_UDP_PROXY_STATS_DIRS];
    ProxyPacket queue[PROXY_QUEUE_CAPACITY];
} ProxyChannel;

struct TestQuicUdpProxySet {
    SnowUdpEngine *engine;
    ProxyChannel *channels;
    u32 channel_count;
    bool enabled;
    bool reorder_first;
    bool failed;
    bool random_enabled;
    u32 random_drop_percent[TEST_QUIC_UDP_PROXY_STATS_DIRS];
    u32 random_jitter_max_ms;
    u32 drop_every;
    u32 delay_ms;
    u64 now_ns; /* current owner-thread monotonic clock */
};

static u32 proxy_random(ProxyChannel *channel, u32 direction) {
    u32 state = channel->random_state[direction];
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    channel->random_state[direction] = state;
    return state;
}

static bool proxy_address_equal(const SnowTransportDatagramAddress *a,
                                const SnowTransportDatagramAddress *b) {
    return a->family == b->family && a->port == b->port &&
           memcmp(a->address, b->address, 4u) == 0;
}

static bool proxy_send(ProxyChannel *channel,
                       const SnowTransportDatagramAddress *destination,
                       const u8 *bytes, u32 length) {
    SnowTransportDatagram datagram;
    size_t sent = 0u;
    memset(&datagram, 0, sizeof(datagram));
    datagram.abi_version = SNOW_TRANSPORT_DATAGRAM_ABI_VERSION;
    datagram.data = bytes;
    datagram.length = length;
    datagram.metadata.abi_version = SNOW_TRANSPORT_DATAGRAM_ABI_VERSION;
    datagram.metadata.destination = *destination;
    SnowStatus status = SnowUdpEngineSend(channel->set->engine, channel->fd,
                                          &datagram, &sent);
    if (status == SNOW_OK && sent == length) {
        channel->forwarded++;
        return true;
    }
    if (status != SNOW_ERR_AGAIN) {
        channel->set->failed = true;
    }
    return false;
}

static SnowStatus proxy_flush(ProxyChannel *channel, u64 now_ns,
                              u64 *nearest_ns) {
    /* Select by due time, not slot index: under load both the delayed first
     * packet and its successor may be overdue, and the successor must still
     * be transmitted first to make the reorder injection deterministic. */
    for (;;) {
        i32 selected = -1;
        for (u32 i = 0u; i < PROXY_QUEUE_CAPACITY; ++i) {
            ProxyPacket *candidate = &channel->queue[i];
            if (!candidate->used) {
                continue;
            }
            if (candidate->due_ns > now_ns) {
                if (*nearest_ns > candidate->due_ns) {
                    *nearest_ns = candidate->due_ns;
                }
                continue;
            }
            if (selected < 0 ||
                candidate->due_ns < channel->queue[selected].due_ns ||
                (candidate->due_ns == channel->queue[selected].due_ns &&
                 candidate->ordinal < channel->queue[selected].ordinal)) {
                selected = (i32)i;
            }
        }
        if (selected < 0) {
            return SNOW_OK;
        }
        ProxyPacket *packet = &channel->queue[selected];
        bool earlier_queued = false;
        for (u32 j = 0u; j < PROXY_QUEUE_CAPACITY; ++j) {
            if (channel->queue[j].used && j != (u32)selected &&
                channel->queue[j].ordinal < packet->ordinal) {
                earlier_queued = true;
                break;
            }
        }
        SnowTransportDatagram datagram;
        size_t sent = 0u;
        memset(&datagram, 0, sizeof(datagram));
        datagram.abi_version = SNOW_TRANSPORT_DATAGRAM_ABI_VERSION;
        datagram.data = packet->bytes;
        datagram.length = packet->length;
        datagram.metadata.abi_version = SNOW_TRANSPORT_DATAGRAM_ABI_VERSION;
        datagram.metadata.destination = packet->destination;
        SnowStatus status = SnowUdpEngineSend(channel->set->engine, channel->fd,
                                              &datagram, &sent);
        if (status == SNOW_ERR_AGAIN) {
            packet->due_ns = now_ns + UINT64_C(1000000);
            if (*nearest_ns > packet->due_ns) {
                *nearest_ns = packet->due_ns;
            }
            continue;
        }
        if (status != SNOW_OK || sent != packet->length) {
            channel->set->failed = true;
            return status != SNOW_OK ? status : SNOW_ERR_IO;
        }
        if (earlier_queued) {
            channel->reordered++;
        }
        channel->forwarded++;
        packet->used = false;
    }
}

static SnowStatus proxy_service(void *userdata, u64 now_ns,
                                u64 *out_deadline_ns) {
    TestQuicUdpProxySet *set = (TestQuicUdpProxySet *)userdata;
    set->now_ns = now_ns;
    u64 nearest_ns = UINT64_MAX;
    for (u32 i = 0u; i < set->channel_count; ++i) {
        SnowStatus status = proxy_flush(&set->channels[i], now_ns, &nearest_ns);
        if (status != SNOW_OK) {
            return status;
        }
    }
    *out_deadline_ns = nearest_ns;
    return SNOW_OK;
}

static bool proxy_queue(ProxyChannel *channel, u32 direction,
                        const SnowTransportDatagramAddress *destination,
                        const SnowTransportDatagram *datagram, u64 now_ns) {
    ProxyPacket *free_packet = NULL;
    for (u32 i = 0u; i < PROXY_QUEUE_CAPACITY; ++i) {
        if (!channel->queue[i].used) {
            free_packet = &channel->queue[i];
            break;
        }
    }
    if (free_packet == NULL ||
        datagram->length > SNOW_QUIC_NGTCP2_MAX_PACKET) {
        channel->dropped++;
        channel->dropped_by_direction[direction]++;
        return true;
    }
    u64 delay_ns = (u64)channel->set->delay_ms * UINT64_C(1000000);
    if (channel->set->random_enabled) {
        u32 delay_ms = proxy_random(channel, direction) %
                       (channel->set->random_jitter_max_ms + 1u);
        delay_ns = (u64)delay_ms * UINT64_C(1000000);
        if (delay_ms != 0u) {
            channel->jittered++;
            channel->jittered_by_direction[direction]++;
        }
    } else if (channel->set->reorder_first &&
               channel->received[direction] == 1u) {
        delay_ns *= 2u;
    }
    free_packet->used = true;
    free_packet->ordinal = channel->next_ordinal++;
    free_packet->due_ns = now_ns + delay_ns;
    free_packet->destination = *destination;
    free_packet->length = (u32)datagram->length;
    memcpy(free_packet->bytes, datagram->data, datagram->length);
    channel->delayed++;
    return true;
}

static void proxy_receive(SnowUdpEngine *engine, SnowSocketFd fd,
                          const SnowTransportDatagram *datagram, void *userdata) {
    (void)engine;
    (void)fd;
    ProxyChannel *channel = (ProxyChannel *)userdata;
    TestQuicUdpProxySet *set = channel->set;
    bool from_server = proxy_address_equal(&datagram->metadata.source,
                                           &channel->server);
    u32 direction = from_server ? PROXY_DOWN : PROXY_UP;
    SnowTransportDatagramAddress destination;
    if (from_server) {
        if (!channel->client_known) {
            set->failed = true;
            return;
        }
        destination = channel->client;
    } else {
        channel->client = datagram->metadata.source;
        channel->client_known = true;
        destination = channel->server;
    }
    if (!set->enabled) {
        if (!proxy_send(channel, &destination, datagram->data,
                        (u32)datagram->length) && !set->failed) {
            /* Preserve handshake progress on transient backpressure too. */
            (void)proxy_queue(channel, direction, &destination, datagram,
                              set->now_ns);
        }
        return;
    }

    channel->received[direction]++;
    if (set->random_enabled &&
        proxy_random(channel, direction) % 100u <
            set->random_drop_percent[direction]) {
        channel->dropped++;
        channel->dropped_by_direction[direction]++;
        return;
    }
    if (set->drop_every != 0u &&
        channel->received[direction] % set->drop_every == 0u) {
        channel->dropped++;
        channel->dropped_by_direction[direction]++;
        return;
    }
    (void)proxy_queue(channel, direction, &destination, datagram, set->now_ns);
}

static SnowSocketFd proxy_bind(u16 *out_port) {
    SnowSocketFd fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        return SNOW_SOCKET_INVALID_FD;
    }
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) != 0) {
        close(fd);
        return SNOW_SOCKET_INVALID_FD;
    }
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = 0;
    if (bind(fd, (const struct sockaddr *)&address, sizeof(address)) != 0) {
        close(fd);
        return SNOW_SOCKET_INVALID_FD;
    }
    socklen_t length = sizeof(address);
    if (getsockname(fd, (struct sockaddr *)&address, &length) != 0) {
        close(fd);
        return SNOW_SOCKET_INVALID_FD;
    }
    *out_port = ntohs(address.sin_port);
    return fd;
}

bool test_quic_udp_proxy_set_create(u16 server_port, u32 channel_count,
                                    TestQuicUdpProxySet **out) {
    if (out == NULL || server_port == 0u || channel_count == 0u ||
        channel_count > 16u) {
        return false;
    }
    *out = NULL;
    TestQuicUdpProxySet *set = (TestQuicUdpProxySet *)calloc(1u, sizeof(*set));
    if (set == NULL) {
        return false;
    }
    set->channels = (ProxyChannel *)calloc(channel_count,
                                           sizeof(ProxyChannel));
    if (set->channels == NULL) {
        free(set);
        return false;
    }
    set->channel_count = channel_count;

    SnowUdpEngineConfig config;
    memset(&config, 0, sizeof(config));
    config.abi_version = SNOW_UDP_ENGINE_ABI_VERSION;
    config.max_sockets = channel_count;
    config.max_datagrams_per_step = 64u;
    config.max_datagram_bytes = SNOW_QUIC_NGTCP2_MAX_PACKET;
    config.poll_event_capacity = 16u;
    config.service = proxy_service;
    config.service_userdata = set;
    if (SnowUdpEngineCreate(&config, &set->engine) != SNOW_OK) {
        test_quic_udp_proxy_set_destroy(&set);
        return false;
    }

    for (u32 i = 0u; i < channel_count; ++i) {
        ProxyChannel *channel = &set->channels[i];
        channel->set = set;
        channel->fd = proxy_bind(&channel->port);
        if (channel->fd == SNOW_SOCKET_INVALID_FD) {
            test_quic_udp_proxy_set_destroy(&set);
            return false;
        }
        channel->server.family = kSnowTransportDatagramAddressIpv4;
        channel->server.port = server_port;
        channel->server.address[0] = 127u;
        channel->server.address[3] = 1u;
        SnowSocketFd owned = channel->fd;
        if (SnowUdpEngineAddOwned(set->engine, owned, proxy_receive, channel) !=
            SNOW_OK) {
            close(owned);
            channel->fd = SNOW_SOCKET_INVALID_FD;
            test_quic_udp_proxy_set_destroy(&set);
            return false;
        }
        /* Keep the descriptor value for engine send calls; ownership has moved
         * to the engine, so this helper never closes it after AddOwned. */
    }
    *out = set;
    return true;
}

void test_quic_udp_proxy_set_destroy(TestQuicUdpProxySet **set) {
    if (set == NULL || *set == NULL) {
        return;
    }
    if ((*set)->engine != NULL) {
        SnowUdpEngineDestroy((*set)->engine);
    }
    free((*set)->channels);
    free(*set);
    *set = NULL;
}

u16 test_quic_udp_proxy_port(const TestQuicUdpProxySet *set, u32 channel) {
    return set != NULL && channel < set->channel_count
               ? set->channels[channel].port
               : 0u;
}

void test_quic_udp_proxy_set_impairment(TestQuicUdpProxySet *set, bool enabled,
                                        u32 drop_every, u32 delay_ms,
                                        bool reorder_first) {
    if (set == NULL) {
        return;
    }
    set->enabled = enabled;
    set->drop_every = drop_every;
    set->delay_ms = delay_ms;
    set->reorder_first = reorder_first;
}

void test_quic_udp_proxy_set_random(TestQuicUdpProxySet *set, bool enabled,
                                    u32 seed, u32 uplink_drop_percent,
                                    u32 downlink_drop_percent,
                                    u32 jitter_max_ms) {
    if (set == NULL) {
        return;
    }
    set->random_enabled = enabled;
    set->random_drop_percent[0] =
        uplink_drop_percent > 100u ? 100u : uplink_drop_percent;
    set->random_drop_percent[1] =
        downlink_drop_percent > 100u ? 100u : downlink_drop_percent;
    set->random_jitter_max_ms = jitter_max_ms;
    for (u32 i = 0u; i < set->channel_count; ++i) {
        for (u32 direction = 0u; direction < TEST_QUIC_UDP_PROXY_STATS_DIRS;
             ++direction) {
            u32 stream = i * TEST_QUIC_UDP_PROXY_STATS_DIRS + direction + 1u;
            u32 state = seed ^ (0x9E3779B9u * stream);
            set->channels[i].random_state[direction] =
                state != 0u ? state : 0xA341316Cu;
        }
    }
}

bool test_quic_udp_proxy_set_step(TestQuicUdpProxySet *set, u32 timeout_ms) {
    if (set == NULL || set->failed) {
        return false;
    }
    size_t delivered = 0u;
    return SnowUdpEngineStep(set->engine, (int)timeout_ms, &delivered) == SNOW_OK &&
           !set->failed;
}

void test_quic_udp_proxy_set_stats(const TestQuicUdpProxySet *set, u32 channel,
                                   TestQuicUdpProxyStats *out) {
    memset(out, 0, sizeof(*out));
    if (set == NULL || channel >= set->channel_count) {
        return;
    }
    const ProxyChannel *proxy = &set->channels[channel];
    for (u32 i = 0u; i < TEST_QUIC_UDP_PROXY_STATS_DIRS; ++i) {
        out->received[i] = proxy->received[i];
        out->dropped_by_direction[i] = proxy->dropped_by_direction[i];
        out->jittered_by_direction[i] = proxy->jittered_by_direction[i];
    }
    out->forwarded = proxy->forwarded;
    out->dropped = proxy->dropped;
    out->delayed = proxy->delayed;
    out->reordered = proxy->reordered;
    out->jittered = proxy->jittered;
    for (u32 i = 0u; i < PROXY_QUEUE_CAPACITY; ++i) {
        if (proxy->queue[i].used) {
            out->queued++;
        }
    }
}
