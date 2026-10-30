#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include "test_framework.h"

#include <crash/break_crash.h>
#include <crash/break_crash_upload_http.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
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

static void ctx_for(BreakCrashUploadHttp *c, int port) {
    memset(c, 0, sizeof(*c));
    c->cfg.io_timeout_ms = 3000u;
    snprintf(c->base_url, sizeof(c->base_url), "http://127.0.0.1:%d", port);
}

#define OK200 "HTTP/1.1 200 OK\r\nContent-Length: 3\r\nConnection: close\r\n\r\nok\n"

static bool upload_against(const char *answer, const char *record, size_t len, Fake *f) {
    BreakCrashUploadHttp c;
    int port = 0;
    bool r;
    if (!fake_start(f, answer, &port)) return false;
    ctx_for(&c, port);
    r = break_crash_upload_http(&c, record, len);
    fake_stop(f);
    return r;
}

TEST(a_200_answer_is_success_and_the_request_is_exactly_the_record) {
    static Fake f;
    const char rec[] = "break-crash-v1\nrecord bytes here\n";
    ASSERT_TRUE(upload_against(OK200, rec, sizeof(rec) - 1u, &f));
    ASSERT_NOT_NULL(strstr(f.got, "POST /crash HTTP/1.1\r\n"));
    ASSERT_NOT_NULL(strstr(f.got, "Content-Type: application/x-break-crash\r\n"));
    ASSERT_NOT_NULL(strstr(f.got, "Content-Length: 33\r\n"));
    ASSERT_NOT_NULL(strstr(f.got, "\r\n\r\nbreak-crash-v1\nrecord bytes here\n"));
    ASSERT_EQ(f.got_len, strlen(f.got));
}

TEST(any_other_status_is_failure) {
    static Fake f;
    const char rec[] = "x";
    const char *answers[] = {
        "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\nConnection: close\r\n\r\n",
        "HTTP/1.1 409 Conflict\r\nContent-Length: 0\r\nConnection: close\r\n\r\n",
        "HTTP/1.1 413 Payload Too Large\r\nContent-Length: 0\r\nConnection: close\r\n\r\n",
        "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\nConnection: close\r\n\r\n",
        "HTTP/1.1 503 Service Unavailable\r\nContent-Length: 0\r\nConnection: close\r\n\r\n",
        "HTTP/1.1 204 No Content\r\nConnection: close\r\n\r\n",
        "HTTP/1.1 201 Created\r\nContent-Length: 0\r\nConnection: close\r\n\r\n",
        "HTTP/1.1 302 Found\r\nLocation: http://127.0.0.1:1/crash\r\nContent-Length: 0\r\nConnection: close\r\n\r\n",
    };
    for (size_t i = 0; i < sizeof(answers) / sizeof(answers[0]); i++) {
        ASSERT_FALSE(upload_against(answers[i], rec, 1u, &f));
    }
}

TEST(a_200_with_broken_framing_is_failure) {
    static Fake f;
    const char rec[] = "x";
    /* declares 10 body bytes, sends 3, closes */
    ASSERT_FALSE(upload_against("HTTP/1.1 200 OK\r\nContent-Length: 10\r\nConnection: close\r\n\r\nok\n", rec, 1u, &f));
    /* no Content-Length on a 200 */
    ASSERT_FALSE(upload_against("HTTP/1.1 200 OK\r\nConnection: close\r\n\r\nok\n", rec, 1u, &f));
    /* chunked */
    ASSERT_FALSE(upload_against("HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\nConnection: close\r\n\r\n3\r\nok\n\r\n0\r\n\r\n",
                                rec, 1u, &f));
    /* bytes after the declared body */
    ASSERT_FALSE(upload_against("HTTP/1.1 200 OK\r\nContent-Length: 3\r\nConnection: close\r\n\r\nok\nEXTRA", rec, 1u, &f));
    /* an answer larger than the adapter's buffer */
    {
        static char big[1000];
        int n = snprintf(big, sizeof(big), "HTTP/1.1 200 OK\r\nContent-Length: 600\r\nConnection: close\r\n\r\n");
        memset(big + n, 'a', 600u);
        big[n + 600] = '\0';
        ASSERT_FALSE(upload_against(big, rec, 1u, &f));
    }
}

TEST(no_answer_at_all_is_failure) {
    static Fake f;
    const char rec[] = "x";
    ASSERT_FALSE(upload_against(NULL, rec, 1u, &f));
    ASSERT_FALSE(upload_against("", rec, 1u, &f));
    ASSERT_FALSE(upload_against("HTTP/1.1 200", rec, 1u, &f));
    ASSERT_FALSE(upload_against("garbage\r\n\r\n", rec, 1u, &f));
}

TEST(bad_arguments_are_refused_before_any_connection) {
    BreakCrashUploadHttp c;
    static char big[BREAK_CRASH_UPLOAD_HTTP_MAX_BYTES + 1u];
    memset(&c, 0, sizeof(c));
    snprintf(c.base_url, sizeof(c.base_url), "http://127.0.0.1:9");     /* nothing listens there */
    ASSERT_FALSE(break_crash_upload_http(NULL, "x", 1u));
    ASSERT_FALSE(break_crash_upload_http(&c, NULL, 1u));
    ASSERT_FALSE(break_crash_upload_http(&c, "x", 0u));
    ASSERT_FALSE(break_crash_upload_http(&c, big, sizeof(big)));        /* over 64 KiB */
    snprintf(c.base_url, sizeof(c.base_url), "%s", "");
    ASSERT_FALSE(break_crash_upload_http(&c, "x", 1u));
    snprintf(c.base_url, sizeof(c.base_url), "http://127.0.0.1:9/");    /* trailing slash */
    ASSERT_FALSE(break_crash_upload_http(&c, "x", 1u));
    memset(c.base_url, 'a', sizeof(c.base_url));                        /* no terminator */
    ASSERT_FALSE(break_crash_upload_http(&c, "x", 1u));
}

/* Runs an upload that must be refused locally: a live fake collector that would answer 200 is
 * waiting, and the adapter must not touch it (a dead port would fail either way). */
static bool refused_without_contact(const char *base_suffix, const void *rec, size_t len) {
    static Fake f;
    BreakCrashUploadHttp c;
    int port = 0;
    bool r;
    if (!fake_start(&f, OK200, &port)) return false;
    ctx_for(&c, port);
    if (base_suffix != NULL) {
        size_t used = strlen(c.base_url);
        snprintf(c.base_url + used, sizeof(c.base_url) - used, "%s", base_suffix);
    }
    r = break_crash_upload_http(&c, rec, len);
    fake_stop(&f);
    return !r && f.got_len == 0u;
}

TEST(a_refusal_made_locally_never_reaches_a_live_server) {
    static char big[BREAK_CRASH_UPLOAD_HTTP_MAX_BYTES + 1u];
    static char exact[BREAK_CRASH_UPLOAD_HTTP_MAX_BYTES];
    memset(big, 'a', sizeof(big));
    memset(exact, 'a', sizeof(exact));
    ASSERT_TRUE(refused_without_contact(NULL, big, sizeof(big)));          /* one byte over the limit */
    ASSERT_TRUE(refused_without_contact("/", "x", 1u));                    /* trailing slash on the base URL */
    ASSERT_TRUE(refused_without_contact(NULL, "x", 0u));                   /* empty record */
    /* the limit itself is allowed: 64 KiB exactly is sent (and the fake answers 200) */
    {
        static Fake f;
        ASSERT_TRUE(upload_against(OK200, exact, sizeof(exact), &f));
        ASSERT_EQ(f.got_len > sizeof(exact), true);
    }
}

TEST(plain_http_to_a_non_loopback_host_and_https_without_a_ca_are_refused) {
    BreakCrashUploadHttp c;
    memset(&c, 0, sizeof(c));
    c.cfg.io_timeout_ms = 1000u;
    snprintf(c.base_url, sizeof(c.base_url), "http://192.0.2.1");
    ASSERT_FALSE(break_crash_upload_http(&c, "x", 1u));
    snprintf(c.base_url, sizeof(c.base_url), "https://127.0.0.1:9");
    ASSERT_FALSE(break_crash_upload_http(&c, "x", 1u));                 /* no CA file */
}

TEST(the_spool_keeps_a_record_pending_after_a_failed_upload_and_sends_it_once_it_works) {
    static Fake f;
    char root[300];
    BreakCrashSpool *sp;
    BreakCrashRecordBuilder *b = break_crash_record_builder_create();
    u8 rec[BREAK_CRASH_RECORD_MAX];
    usize n;
    BreakCrashUploadHttp c;
    int port = 0;
    ASSERT_NOT_NULL(b);
    break_crash_record_builder_set_signal(b, 11, 1, 0);
    break_crash_record_builder_set_process(b, 1u, 1u);
    break_crash_record_builder_set_registers(b, 0x401000u, 0x7ffd0000u, 0x7ffd0020u);
    break_crash_record_builder_set_build_id(b, "testbuild");
    n = break_crash_record_builder_finish(b, rec, sizeof(rec));
    break_crash_record_builder_destroy(b);
    ASSERT_TRUE(n > 0u);
    test_tmp(root, sizeof(root), "crash_upload_spool");
    {
        char cmd[400];
        snprintf(cmd, sizeof(cmd), "rm -rf '%s'", root);
        (void)!system(cmd);
    }
    sp = break_crash_spool_open(root);
    ASSERT_NOT_NULL(sp);
    ASSERT_TRUE(break_crash_spool_put_pending(sp, rec, n));
    ASSERT_TRUE(fake_start(&f, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\nConnection: close\r\n\r\n", &port));
    ctx_for(&c, port);
    ASSERT_EQ(break_crash_spool_upload_pending(sp, break_crash_upload_http, &c), 0u);
    fake_stop(&f);
    ASSERT_EQ(break_crash_spool_count(sp, 0), 1u);
    ASSERT_TRUE(fake_start(&f, OK200, &port));
    ctx_for(&c, port);
    ASSERT_EQ(break_crash_spool_upload_pending(sp, break_crash_upload_http, &c), 1u);
    fake_stop(&f);
    ASSERT_EQ(break_crash_spool_count(sp, 0), 0u);
    ASSERT_EQ(break_crash_spool_count(sp, 1), 1u);
    /* what went over the wire is the redacted canonical record */
    ASSERT_NOT_NULL(strstr(f.got, "\r\n\r\nbreak-crash-v1\n"));
    break_crash_spool_destroy(sp);
    {
        char cmd[400];
        snprintf(cmd, sizeof(cmd), "rm -rf '%s'", root);
        (void)!system(cmd);
    }
}

TEST_MAIN_BEGIN()
    signal(SIGPIPE, SIG_IGN);
    RUN_TEST(a_200_answer_is_success_and_the_request_is_exactly_the_record);
    RUN_TEST(any_other_status_is_failure);
    RUN_TEST(a_200_with_broken_framing_is_failure);
    RUN_TEST(no_answer_at_all_is_failure);
    RUN_TEST(bad_arguments_are_refused_before_any_connection);
    RUN_TEST(a_refusal_made_locally_never_reaches_a_live_server);
    RUN_TEST(plain_http_to_a_non_loopback_host_and_https_without_a_ca_are_refused);
    RUN_TEST(the_spool_keeps_a_record_pending_after_a_failed_upload_and_sends_it_once_it_works);
TEST_MAIN_END()
