#define _POSIX_C_SOURCE 200809L
#if defined(__APPLE__)
#define _DARWIN_C_SOURCE 1 /* INADDR_LOOPBACK */
#endif
#define _DEFAULT_SOURCE
/* runtime_metrics_push_http: POSTs the BRKM1 encoding of a registry to a
 * collector over break_http, against a one-connection loopback fake. */
#include "test_framework.h"

#include <runtime/runtime_metrics.h>
#include <runtime/runtime_metrics_push_http.h>
#include <core/platform_thread.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

/* A one-connection fake collector on the loopback: it records the request it
 * received and answers with a canned byte string (or nothing). */
typedef struct {
    int listen_fd;
    const char *answer;      /* NULL: close without answering */
    size_t answer_len;
    char got[70000];
    size_t got_len;
    pthread_t th;
} Fake;

static void *fake_main(void *arg) {
    Fake *f = (Fake *)arg;
    int fd = accept(f->listen_fd, NULL, NULL);
    size_t head_end = 0, want = 0;
    if (fd < 0) return NULL;
    for (;;) {
        ssize_t r = recv(fd, f->got + f->got_len, sizeof(f->got) - f->got_len, 0);
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
    if (f->answer != NULL) (void)!write(fd, f->answer, f->answer_len);
    close(fd);
    return NULL;
}

static bool fake_start(Fake *f, const char *answer, int *port) {
    struct sockaddr_in a;
    socklen_t al = sizeof(a);
    int one = 1;
    memset(f, 0, sizeof(*f));
    f->answer = answer;
    f->answer_len = answer != NULL ? strlen(answer) : 0u;
    f->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (f->listen_fd < 0) return false;
    setsockopt(f->listen_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (bind(f->listen_fd, (struct sockaddr *)&a, sizeof(a)) != 0 || listen(f->listen_fd, 1) != 0 ||
        getsockname(f->listen_fd, (struct sockaddr *)&a, &al) != 0) {
        return false;
    }
    *port = (int)ntohs(a.sin_port);
    return pthread_create(&f->th, NULL, fake_main, f) == 0;
}

static void fake_stop(Fake *f) {
    /* a connection the adapter never made would leave the thread blocked in accept(): make one,
     * so a refusal that happens before connecting ends the test with a failure, not a hang */
    struct sockaddr_in a;
    socklen_t al = sizeof(a);
    int poke = socket(AF_INET, SOCK_STREAM, 0);
    if (poke >= 0 && getsockname(f->listen_fd, (struct sockaddr *)&a, &al) == 0) {
        (void)connect(poke, (struct sockaddr *)&a, sizeof(a));
    }
    if (poke >= 0) close(poke);
    pthread_join(f->th, NULL);
    close(f->listen_fd);
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

TEST_MAIN_BEGIN()
    signal(SIGPIPE, SIG_IGN);
    RUN_TEST(a_200_answer_is_ok_and_the_body_decodes_to_the_snapshot);
    RUN_TEST(any_other_status_or_a_broken_answer_is_failed);
    RUN_TEST(an_empty_registry_is_pushed_as_an_empty_body);
    RUN_TEST(bad_arguments_are_refused_before_any_connection);
    RUN_TEST(a_registry_too_large_to_send_is_overload_and_never_sent);
    RUN_TEST(plain_http_off_loopback_and_https_without_a_ca_are_failed);
TEST_MAIN_END()
