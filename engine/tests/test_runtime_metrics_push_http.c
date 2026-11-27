#define _POSIX_C_SOURCE 200809L
#if defined(__APPLE__)
#define _DARWIN_C_SOURCE 1 /* INADDR_LOOPBACK */
#endif
#define _DEFAULT_SOURCE
/* runtime_metrics_push_http: POSTs the BRKM1 encoding of a registry to a
 * collector over break_http, against a one-connection loopback fake. */
#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#include "test_framework.h"

#include <runtime/runtime_metrics.h>
#include <runtime/runtime_metrics_push_http.h>
#include <core/platform_thread.h>

#if defined(_WIN32)
typedef SOCKET TestSock;
#define TEST_SOCK_BAD INVALID_SOCKET
#define test_sock_close closesocket
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>
typedef int TestSock;
#define TEST_SOCK_BAD (-1)
#define test_sock_close close
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if !defined(_WIN32)
#include <time.h>
#endif

static unsigned long long test_now_ms(void) {
#if defined(_WIN32)
    return (unsigned long long)GetTickCount64();
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (unsigned long long)ts.tv_sec * 1000ull + (unsigned long long)ts.tv_nsec / 1000000ull;
#endif
}

static void test_sleep_ms(unsigned ms) {
#if defined(_WIN32)
    Sleep(ms);
#else
    struct timespec ts = {(time_t)(ms / 1000u), (long)(ms % 1000u) * 1000000L};
    nanosleep(&ts, NULL);
#endif
}

/* A one-connection fake collector on the loopback: it records the request it
 * received and answers with a canned byte string (or nothing). */
typedef struct {
    TestSock listen_fd;
    const char *answer;      /* NULL: close without answering */
    size_t answer_len;
    unsigned hold_ms;        /* stay silent this long after the request before answering */
    char got[70000];
    size_t got_len;
    PlatformThread th;
} Fake;

static PLATFORM_THREAD_RET fake_main(PLATFORM_THREAD_ARG arg) {
    Fake *f = (Fake *)arg;
    TestSock fd = accept(f->listen_fd, NULL, NULL);
    size_t head_end = 0, want = 0;
    if (fd == TEST_SOCK_BAD) return PLATFORM_THREAD_RETURN;
    for (;;) {
        int r = (int)recv(fd, f->got + f->got_len, (int)(sizeof(f->got) - f->got_len), 0);
        char *he;
        if (r <= 0) break;
        f->got_len += (size_t)r;
        f->got[f->got_len < sizeof(f->got) ? f->got_len : sizeof(f->got) - 1u] = '\0';
        he = strstr(f->got, "\r\n\r\n");
        if (he != NULL && want == 0u) {
            const char *cl = strstr(f->got, "Content-Length: ");
            head_end = (size_t)(he - f->got) + 4u;
            want = head_end + (cl != NULL ? (size_t)strtoul(cl + 16, NULL, 10) : 0u);
        }
        if (want != 0u && f->got_len >= want) break;
    }
    if (f->hold_ms != 0u) test_sleep_ms(f->hold_ms);
    if (f->answer != NULL) (void)send(fd, f->answer, (int)f->answer_len, 0);
    test_sock_close(fd);
    return PLATFORM_THREAD_RETURN;
}

static bool fake_start_held(Fake *f, const char *answer, unsigned hold_ms, int *port);

static bool fake_start(Fake *f, const char *answer, int *port) {
    return fake_start_held(f, answer, 0u, port);
}

static bool fake_start_held(Fake *f, const char *answer, unsigned hold_ms, int *port) {
    struct sockaddr_in a;
    socklen_t al = sizeof(a);
    int one = 1;
    memset(f, 0, sizeof(*f));
    f->answer = answer;
    f->answer_len = answer != NULL ? strlen(answer) : 0u;
    f->hold_ms = hold_ms;
    f->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (f->listen_fd == TEST_SOCK_BAD) return false;
    setsockopt(f->listen_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&one, sizeof(one));
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (bind(f->listen_fd, (struct sockaddr *)&a, sizeof(a)) != 0 || listen(f->listen_fd, 1) != 0 ||
        getsockname(f->listen_fd, (struct sockaddr *)&a, &al) != 0) {
        return false;
    }
    *port = (int)ntohs(a.sin_port);
    return platform_thread_create(&f->th, fake_main, f);
}

static void fake_stop(Fake *f) {
    /* a connection the adapter never made would leave the thread blocked in accept(): make one,
     * so a refusal that happens before connecting ends the test with a failure, not a hang */
    struct sockaddr_in a;
    socklen_t al = sizeof(a);
    TestSock poke = socket(AF_INET, SOCK_STREAM, 0);
    if (poke != TEST_SOCK_BAD && getsockname(f->listen_fd, (struct sockaddr *)&a, &al) == 0) {
        (void)connect(poke, (struct sockaddr *)&a, sizeof(a));
    }
    if (poke != TEST_SOCK_BAD) test_sock_close(poke);
    platform_thread_join(f->th);
    test_sock_close(f->listen_fd);
}

#define OK200 "HTTP/1.1 200 OK\r\nContent-Length: 3\r\nConnection: close\r\n\r\nok\n"

static void ctx_for(BreakRuntimeMetricsPushHttp *c, int port) {
    memset(c, 0, sizeof(*c));
    c->cfg.io_timeout_ms = 3000u;
    snprintf(c->base_url, sizeof(c->base_url), "http://127.0.0.1:%d", port);
}

static BreakRuntimeMetrics *sample_registry(void) {
    BreakRuntimeMetrics *m = NULL;
    if (break_runtime_metrics_create(NULL, &m) != BREAK_RUNTIME_OK) return NULL;
    (void)break_runtime_metrics_add(m, "net.sent", BREAK_RUNTIME_METRIC_COUNTER, 7u);
    (void)break_runtime_metrics_set(m, "q.depth", BREAK_RUNTIME_METRIC_GAUGE, 3u);
    return m;
}

static BreakRuntimeError push_against(const char *answer, BreakRuntimeMetrics *m, Fake *f) {
    BreakRuntimeMetricsPushHttp c;
    int port = 0;
    BreakRuntimeError r;
    if (!fake_start(f, answer, &port)) return BREAK_RUNTIME_FAILED;
    ctx_for(&c, port);
    r = break_runtime_metrics_push_http(&c, m);
    fake_stop(f);
    return r;
}

TEST(a_200_answer_is_ok_and_the_body_decodes_to_the_snapshot) {
    static Fake f;
    BreakRuntimeMetrics *m = sample_registry();
    BreakRuntimeMetricSample got[4];
    u32 n = 0u;
    const char *body;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(push_against(OK200, m, &f), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(strstr(f.got, "POST /metrics HTTP/1.1\r\n"));
    ASSERT_NOT_NULL(strstr(f.got, "Content-Type: text/x-break-metrics\r\n"));
    body = strstr(f.got, "\r\n\r\n");
    ASSERT_NOT_NULL(body);
    body += 4;
    ASSERT_EQ(break_runtime_metrics_decode(body, strlen(body), got, 4u, &n), BREAK_RUNTIME_OK);
    ASSERT_EQ(n, 2u);
    ASSERT_STR_EQ(got[0].name, "net.sent");
    ASSERT_EQ(got[0].value, 7u);
    ASSERT_STR_EQ(got[1].name, "q.depth");
    ASSERT_EQ(got[1].value, 3u);
    break_runtime_metrics_destroy(m);
}

TEST(any_other_status_or_a_broken_answer_is_failed) {
    static Fake f;
    BreakRuntimeMetrics *m = sample_registry();
    const char *answers[] = {
        "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\nConnection: close\r\n\r\n",
        "HTTP/1.1 204 No Content\r\nConnection: close\r\n\r\n",
        "HTTP/1.1 302 Found\r\nLocation: http://127.0.0.1:1/\r\nContent-Length: 0\r\n\r\n",
        "HTTP/1.1 200 OK\r\nConnection: close\r\n\r\nok\n",
        NULL,
    };
    ASSERT_NOT_NULL(m);
    for (size_t i = 0; i < sizeof(answers) / sizeof(answers[0]); i++)
        ASSERT_EQ(push_against(answers[i], m, &f), BREAK_RUNTIME_FAILED);
    break_runtime_metrics_destroy(m);
}

TEST(an_empty_registry_is_pushed_as_an_empty_body) {
    static Fake f;
    BreakRuntimeMetrics *m = NULL;
    ASSERT_EQ(break_runtime_metrics_create(NULL, &m), BREAK_RUNTIME_OK);
    ASSERT_EQ(push_against(OK200, m, &f), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(strstr(f.got, "Content-Length: 0\r\n"));
    break_runtime_metrics_destroy(m);
}

/* A refusal made locally must not reach a live collector that would say 200. */
static bool refused_without_contact(const char *suffix, BreakRuntimeMetrics *m,
                                    BreakRuntimeError want) {
    static Fake f;
    BreakRuntimeMetricsPushHttp c;
    int port = 0;
    BreakRuntimeError r;
    if (!fake_start(&f, OK200, &port)) return false;
    ctx_for(&c, port);
    if (suffix) {
        size_t used = strlen(c.base_url);
        snprintf(c.base_url + used, sizeof(c.base_url) - used, "%s", suffix);
    }
    r = break_runtime_metrics_push_http(&c, m);
    fake_stop(&f);
    return r == want && f.got_len == 0u;
}

static PLATFORM_THREAD_RET push_from_other_thread(PLATFORM_THREAD_ARG arg) {
    BreakRuntimeMetricsPushHttp c;
    memset(&c, 0, sizeof(c));
    snprintf(c.base_url, sizeof(c.base_url), "http://127.0.0.1:9");
    *(BreakRuntimeError *)((void **)arg)[1] =
        break_runtime_metrics_push_http(&c, (BreakRuntimeMetrics *)((void **)arg)[0]);
    return PLATFORM_THREAD_RETURN;
}

TEST(bad_arguments_are_refused_before_any_connection) {
    BreakRuntimeMetrics *m = sample_registry();
    BreakRuntimeMetricsPushHttp c;
    BreakRuntimeError other = BREAK_RUNTIME_OK;
    void *args[2];
    PlatformThread th;
    ASSERT_NOT_NULL(m);
    ASSERT_TRUE(refused_without_contact("/", m, BREAK_RUNTIME_INVALID));
    ASSERT_TRUE(refused_without_contact(NULL, NULL, BREAK_RUNTIME_INVALID));
    memset(&c, 0, sizeof(c));
    ASSERT_EQ(break_runtime_metrics_push_http(NULL, m), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_push_http(&c, m), BREAK_RUNTIME_INVALID); /* empty base */
    memset(c.base_url, 'a', sizeof(c.base_url));
    ASSERT_EQ(break_runtime_metrics_push_http(&c, m), BREAK_RUNTIME_INVALID); /* no NUL */
    args[0] = m;
    args[1] = &other;
    ASSERT_TRUE(platform_thread_create(&th, push_from_other_thread, args));
    platform_thread_join(th);
    ASSERT_EQ(other, BREAK_RUNTIME_REJECTED); /* encode is owner-thread-only */
    break_runtime_metrics_destroy(m);
}

TEST(a_registry_too_large_to_send_is_overload_and_never_sent) {
    BreakRuntimeMetrics *m = NULL;
    BreakRuntimeMetricsConfig cfg = {BREAK_RUNTIME_METRICS_MAX_CAPACITY};
    char name[BREAK_RUNTIME_METRICS_NAME_CAPACITY];
    ASSERT_EQ(break_runtime_metrics_create(&cfg, &m), BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < BREAK_RUNTIME_METRICS_MAX_CAPACITY; ++i) {
        snprintf(name, sizeof name, "m%040u", i);
        ASSERT_EQ(break_runtime_metrics_add(m, name, BREAK_RUNTIME_METRIC_COUNTER, UINT64_MAX),
                  BREAK_RUNTIME_OK);
    }
    ASSERT_TRUE(refused_without_contact(NULL, m, BREAK_RUNTIME_OVERLOAD));
    break_runtime_metrics_destroy(m);
}

TEST(plain_http_off_loopback_and_https_without_a_ca_are_failed) {
    BreakRuntimeMetrics *m = sample_registry();
    BreakRuntimeMetricsPushHttp c;
    ASSERT_NOT_NULL(m);
    memset(&c, 0, sizeof(c));
    c.cfg.io_timeout_ms = 1000u;
    snprintf(c.base_url, sizeof(c.base_url), "http://192.0.2.1");
    ASSERT_EQ(break_runtime_metrics_push_http(&c, m), BREAK_RUNTIME_FAILED);
    snprintf(c.base_url, sizeof(c.base_url), "https://127.0.0.1:9");
    ASSERT_EQ(break_runtime_metrics_push_http(&c, m), BREAK_RUNTIME_FAILED);
    break_runtime_metrics_destroy(m);
}

/* io_timeout_ms bounds the whole exchange: a collector that accepts and then
 * says nothing cannot hold the push past it. This depends on the socket being
 * non-blocking on every platform. */
TEST(a_silent_collector_is_cut_off_at_the_io_timeout) {
    static Fake f;
    BreakRuntimeMetrics *m = sample_registry();
    BreakRuntimeMetricsPushHttp c;
    unsigned long long started, took;
    int port = 0;
    ASSERT_NOT_NULL(m);
    ASSERT_TRUE(fake_start_held(&f, OK200, 4000u, &port));
    ctx_for(&c, port);
    c.cfg.io_timeout_ms = 300u;
    started = test_now_ms();
    ASSERT_EQ(break_runtime_metrics_push_http(&c, m), BREAK_RUNTIME_FAILED);
    took = test_now_ms() - started;
    fake_stop(&f);
    ASSERT_NOT_NULL(strstr(f.got, "POST /metrics HTTP/1.1\r\n"));
    ASSERT_TRUE(took < 2500ull);
    break_runtime_metrics_destroy(m);
}

static const BreakRuntimeMetricAlertRule kRules[] = {
    {"q.depth", BREAK_RUNTIME_METRIC_ALERT_ABOVE, 5u},
    {"pool.free", BREAK_RUNTIME_METRIC_ALERT_BELOW, 2u},
};

TEST(alert_edges_are_posted_to_the_alerts_endpoint) {
    static Fake f;
    BreakRuntimeMetricsPushHttp c;
    const BreakRuntimeMetricAlertEdge edges[] = {BREAK_RUNTIME_METRIC_ALERT_STEADY,
                                                 BREAK_RUNTIME_METRIC_ALERT_CLEARED};
    int port = 0;
    ASSERT_TRUE(fake_start(&f, OK200, &port));
    ctx_for(&c, port);
    ASSERT_EQ(break_runtime_metrics_push_alerts_http(&c, kRules, edges, 2u), BREAK_RUNTIME_OK);
    fake_stop(&f);
    ASSERT_NOT_NULL(strstr(f.got, "POST /alerts HTTP/1.1\r\n"));
    ASSERT_NOT_NULL(strstr(f.got, "Content-Type: text/x-break-alerts\r\n"));
    ASSERT_NOT_NULL(strstr(f.got, "\r\n\r\nBRKA1 cleared pool.free below 2\n"));
    ASSERT_EQ(f.got_len, strlen(f.got));
}

/* The collector's answer body carries nothing the push needs: a 200 with a
 * body larger than any fixed response buffer is still a delivery. */
static char g_big_answer[2400];

static const char *big_ok_answer(void) {
    static const char head[] = "HTTP/1.1 200 OK\r\nContent-Length: 2000\r\nConnection: close\r\n\r\n";
    size_t n = strlen(head);
    memcpy(g_big_answer, head, n);
    memset(g_big_answer + n, 'x', 2000u);
    g_big_answer[n + 2000u] = '\0';
    return g_big_answer;
}

TEST(a_200_answer_with_a_large_body_is_still_ok) {
    static Fake f;
    BreakRuntimeMetricsPushHttp c;
    BreakRuntimeMetrics *m = sample_registry();
    const BreakRuntimeMetricAlertEdge edges[] = {BREAK_RUNTIME_METRIC_ALERT_STEADY,
                                                 BREAK_RUNTIME_METRIC_ALERT_CLEARED};
    int port = 0;
    ASSERT_NOT_NULL(m);
    ASSERT_EQ(push_against(big_ok_answer(), m, &f), BREAK_RUNTIME_OK);
    ASSERT_TRUE(fake_start(&f, big_ok_answer(), &port));
    ctx_for(&c, port);
    ASSERT_EQ(break_runtime_metrics_push_alerts_http(&c, kRules, edges, 2u), BREAK_RUNTIME_OK);
    fake_stop(&f);
    /* a large body on a non-200 answer is still a failure */
    ASSERT_EQ(push_against("HTTP/1.1 503 Busy\r\nContent-Length: 1000\r\nConnection: close\r\n\r\n",
                           m, &f),
              BREAK_RUNTIME_FAILED);
    break_runtime_metrics_destroy(m);
}

TEST(all_steady_edges_send_nothing_and_succeed) {
    static Fake f;
    BreakRuntimeMetricsPushHttp c;
    const BreakRuntimeMetricAlertEdge edges[] = {BREAK_RUNTIME_METRIC_ALERT_STEADY,
                                                 BREAK_RUNTIME_METRIC_ALERT_STEADY};
    int port = 0;
    ASSERT_TRUE(fake_start(&f, OK200, &port));
    ctx_for(&c, port);
    ASSERT_EQ(break_runtime_metrics_push_alerts_http(&c, kRules, edges, 2u), BREAK_RUNTIME_OK);
    fake_stop(&f);
    ASSERT_EQ(f.got_len, 0u); /* no transition: no request */
}

TEST(alert_delivery_failures_and_local_refusals) {
    static Fake f;
    BreakRuntimeMetricsPushHttp c;
    const BreakRuntimeMetricAlertEdge raised[] = {BREAK_RUNTIME_METRIC_ALERT_RAISED,
                                                  BREAK_RUNTIME_METRIC_ALERT_STEADY};
    const BreakRuntimeMetricAlertEdge bogus[] = {(BreakRuntimeMetricAlertEdge)7,
                                                 BREAK_RUNTIME_METRIC_ALERT_STEADY};
    int port = 0;
    ASSERT_TRUE(fake_start(&f, "HTTP/1.1 503 Service Unavailable\r\nContent-Length: 0\r\n\r\n",
                           &port));
    ctx_for(&c, port);
    ASSERT_EQ(break_runtime_metrics_push_alerts_http(&c, kRules, raised, 2u),
              BREAK_RUNTIME_FAILED);
    fake_stop(&f);
    ASSERT_TRUE(fake_start(&f, OK200, &port));
    ctx_for(&c, port);
    ASSERT_EQ(break_runtime_metrics_push_alerts_http(&c, kRules, bogus, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_push_alerts_http(NULL, kRules, raised, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_metrics_push_alerts_http(&c, NULL, raised, 2u),
              BREAK_RUNTIME_INVALID);
    {
        size_t used = strlen(c.base_url);
        snprintf(c.base_url + used, sizeof(c.base_url) - used, "/");
    }
    ASSERT_EQ(break_runtime_metrics_push_alerts_http(&c, kRules, raised, 2u),
              BREAK_RUNTIME_INVALID);
    fake_stop(&f);
    ASSERT_EQ(f.got_len, 0u);
}


/* Best-effort delivery: a failed push parks its encoded body in the retry
 * queue; a later drain re-POSTs it and releases it on success. This is the
 * caller-side composition the push and retry docs describe (the library does
 * not retry on its own). */
typedef struct {
    int port;
    u32 sends;
} DrainSendCtx;

static BreakRuntimeError drain_send_post(void *user, const void *bytes, usize len) {
    DrainSendCtx *d = (DrainSendCtx *)user;
    BreakRuntimeMetrics *tmp = NULL;
    BreakRuntimeMetricSample rows[8];
    u32 n = 0u;
    BreakRuntimeMetricsPushHttp c;
    BreakRuntimeError r;
    d->sends++;
    /* Rebuild a registry from the queued encoding, then POST it. */
    if (break_runtime_metrics_decode((const char *)bytes, len, rows, 8u, &n) != BREAK_RUNTIME_OK)
        return BREAK_RUNTIME_INVALID;
    if (break_runtime_metrics_create(NULL, &tmp) != BREAK_RUNTIME_OK) return BREAK_RUNTIME_OOM;
    for (u32 i = 0u; i < n; i++) {
        BreakRuntimeError put = rows[i].kind == BREAK_RUNTIME_METRIC_COUNTER
            ? break_runtime_metrics_add(tmp, rows[i].name, BREAK_RUNTIME_METRIC_COUNTER, rows[i].value)
            : break_runtime_metrics_set(tmp, rows[i].name, BREAK_RUNTIME_METRIC_GAUGE, rows[i].value);
        if (put != BREAK_RUNTIME_OK) { break_runtime_metrics_destroy(tmp); return put; }
    }
    ctx_for(&c, d->port);
    r = break_runtime_metrics_push_http(&c, tmp);
    break_runtime_metrics_destroy(tmp);
    return r;
}

TEST(a_failed_push_is_parked_and_a_later_drain_delivers_it) {
    static Fake down;
    static Fake up;
    BreakRuntimeMetrics *m = sample_registry();
    BreakRuntimeMetricsRetryQueue *q = NULL;
    BreakRuntimeMetricsRetryConfig qc;
    BreakRuntimeMetricsRetryStats st;
    BreakRuntimeMetricsRetryDrainResult dr;
    BreakRuntimeMetricsPushHttp c;
    DrainSendCtx d;
    char body[8192];
    usize body_len = 0u;
    int down_port = 0, up_port = 0;
    ASSERT_NOT_NULL(m);
    memset(&qc, 0, sizeof(qc));
    qc.capacity = 8u;
    qc.max_payload_bytes = sizeof(body);
    ASSERT_EQ(break_runtime_metrics_retry_create(&qc, &q), BREAK_RUNTIME_OK);

    /* 1) Push to a collector that answers 503 -> FAILED, so we park the body. */
    ASSERT_TRUE(fake_start(&down, "HTTP/1.1 503 Service Unavailable\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", &down_port));
    ctx_for(&c, down_port);
    ASSERT_EQ(break_runtime_metrics_push_http(&c, m), BREAK_RUNTIME_FAILED);
    fake_stop(&down);
    ASSERT_EQ(break_runtime_metrics_encode(m, body, sizeof(body), &body_len), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_enqueue(q, body, body_len), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 1u);

    /* 2) Drain against a collector that now answers 200 -> delivered, queue empty. */
    ASSERT_TRUE(fake_start(&up, OK200, &up_port));
    d.port = up_port;
    d.sends = 0u;
    ASSERT_EQ(break_runtime_metrics_retry_drain(q, drain_send_post, &d, 4u, 0u, &dr),
              BREAK_RUNTIME_OK);
    fake_stop(&up);
    ASSERT_EQ(dr.delivered, 1u);
    ASSERT_EQ(dr.failed, 0u);
    ASSERT_EQ(d.sends, 1u);
    ASSERT_NOT_NULL(strstr(up.got, "POST /metrics HTTP/1.1\r\n"));
    ASSERT_EQ(break_runtime_metrics_retry_stats(q, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 0u);
    ASSERT_EQ(st.released, 1u);

    break_runtime_metrics_retry_destroy(q);
    break_runtime_metrics_destroy(m);
}

/* Per-channel delivery over real sockets: a channel's send POSTs its parked
 * body to its own endpoint path on its own collector. */
typedef struct {
    int port;
    const char *path;
    const char *content_type;
    u32 sends;
} ChannelPost;

static BreakRuntimeError channel_post(void *user, const void *bytes, usize len) {
    ChannelPost *p = (ChannelPost *)user;
    char url[128];
    u8 resp[64];
    usize resp_len = 0u;
    int status = 0;
    BreakHttpConfig cfg;
    p->sends++;
    memset(&cfg, 0, sizeof(cfg));
    cfg.io_timeout_ms = 3000u;
    snprintf(url, sizeof(url), "http://127.0.0.1:%d%s", p->port, p->path);
    return break_http_post(&cfg, url, bytes, len, p->content_type, resp, sizeof(resp), &resp_len,
                           &status) == BHTTP_OK &&
                   status == 200
               ? BREAK_RUNTIME_OK
               : BREAK_RUNTIME_FAILED;
}

TEST(a_dead_metrics_collector_does_not_hold_back_alert_delivery) {
    static Fake metrics_down;
    static Fake alerts_up;
    BreakRuntimeMetricsRetryChannelConfig ch[2];
    BreakRuntimeMetricsRetryRouterConfig cfg;
    BreakRuntimeMetricsRetryRouter *r = NULL;
    BreakRuntimeMetricsRetryRouterResult res;
    BreakRuntimeMetricsRetryStats st;
    ChannelPost mp, ap;
    int mport = 0, aport = 0;
    static const char kMetricsBody[] = "BRKM1 net.sent counter 7\n";
    static const char kAlertBody[] = "BRKA1 raised q.depth above 5\n";
    memset(ch, 0, sizeof(ch));
    ch[0].queue.capacity = 4u;
    ch[0].queue.max_payload_bytes = 256u;
    ch[0].send = channel_post;
    ch[0].user = &mp;
    ch[0].max_sends = 4u;
    ch[0].backoff.base_us = 1000u;
    ch[0].backoff.max_us = 1000u;
    ch[1] = ch[0];
    ch[1].user = &ap;
    memset(&cfg, 0, sizeof(cfg));
    cfg.channels = ch;
    cfg.channel_count = 2u;
    ASSERT_EQ(break_runtime_metrics_retry_router_create(&cfg, &r), BREAK_RUNTIME_OK);

    ASSERT_TRUE(fake_start(&metrics_down,
                           "HTTP/1.1 503 Service Unavailable\r\nContent-Length: 0\r\n"
                           "Connection: close\r\n\r\n",
                           &mport));
    ASSERT_TRUE(fake_start(&alerts_up, OK200, &aport));
    mp.port = mport;
    mp.path = "/metrics";
    mp.content_type = BREAK_RUNTIME_METRICS_PUSH_HTTP_CONTENT_TYPE;
    mp.sends = 0u;
    ap.port = aport;
    ap.path = "/alerts";
    ap.content_type = BREAK_RUNTIME_METRICS_PUSH_HTTP_ALERTS_CONTENT_TYPE;
    ap.sends = 0u;
    /* The metrics snapshot is enqueued first. With one shared FIFO it would
     * sit at the head and the alert behind it would wait for the collector. */
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 0u, kMetricsBody, strlen(kMetricsBody)),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_enqueue(r, 1u, kAlertBody, strlen(kAlertBody)),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_metrics_retry_router_drain(r, 0u, &res), BREAK_RUNTIME_OK);
    fake_stop(&metrics_down);
    fake_stop(&alerts_up);
    ASSERT_EQ(mp.sends, 1u);
    ASSERT_EQ(ap.sends, 1u);
    ASSERT_EQ(res.delivered, 1u);
    ASSERT_EQ(res.failed, 1u);
    /* The alert reached its own endpoint with its own content type... */
    ASSERT_NOT_NULL(strstr(alerts_up.got, "POST /alerts HTTP/1.1\r\n"));
    ASSERT_NOT_NULL(strstr(alerts_up.got, "text/x-break-alerts"));
    ASSERT_NOT_NULL(strstr(alerts_up.got, kAlertBody));
    /* ...while the metrics snapshot stays parked for its next due time. */
    ASSERT_NOT_NULL(strstr(metrics_down.got, "POST /metrics HTTP/1.1\r\n"));
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(r, 0u, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 1u);
    ASSERT_EQ(break_runtime_metrics_retry_router_stats(r, 1u, &st), BREAK_RUNTIME_OK);
    ASSERT_EQ(st.queued, 0u);
    break_runtime_metrics_retry_router_destroy(r);
}

#if defined(_WIN32)
/* Runs before the test itself starts Winsock: a push must start it on its own,
 * which shows up as socket() working afterwards in a process that never called
 * WSAStartup. */
TEST(the_transport_starts_winsock_by_itself) {
    BreakRuntimeMetrics *m = sample_registry();
    BreakRuntimeMetricsPushHttp c;
    SOCKET probe;
    ASSERT_NOT_NULL(m);
    ctx_for(&c, 9);
    c.cfg.io_timeout_ms = 300u;
    c.cfg.connect_timeout_ms = 300u;
    (void)break_runtime_metrics_push_http(&c, m);
    probe = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT_TRUE(probe != INVALID_SOCKET);
    if (probe != INVALID_SOCKET) closesocket(probe);
    break_runtime_metrics_destroy(m);
}
#endif

TEST_MAIN_BEGIN()
#if defined(_WIN32)
    RUN_TEST(the_transport_starts_winsock_by_itself);
    {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;
    }
#else
    signal(SIGPIPE, SIG_IGN);
#endif
    RUN_TEST(a_200_answer_is_ok_and_the_body_decodes_to_the_snapshot);
    RUN_TEST(any_other_status_or_a_broken_answer_is_failed);
    RUN_TEST(an_empty_registry_is_pushed_as_an_empty_body);
    RUN_TEST(bad_arguments_are_refused_before_any_connection);
    RUN_TEST(a_registry_too_large_to_send_is_overload_and_never_sent);
    RUN_TEST(plain_http_off_loopback_and_https_without_a_ca_are_failed);
    RUN_TEST(a_silent_collector_is_cut_off_at_the_io_timeout);
    RUN_TEST(alert_edges_are_posted_to_the_alerts_endpoint);
    RUN_TEST(a_200_answer_with_a_large_body_is_still_ok);
    RUN_TEST(all_steady_edges_send_nothing_and_succeed);
    RUN_TEST(alert_delivery_failures_and_local_refusals);
    RUN_TEST(a_failed_push_is_parked_and_a_later_drain_delivers_it);
    RUN_TEST(a_dead_metrics_collector_does_not_hold_back_alert_delivery);
TEST_MAIN_END()
