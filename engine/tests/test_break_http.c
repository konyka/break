#define _POSIX_C_SOURCE 200809L
#if defined(__APPLE__)
#define _DARWIN_C_SOURCE 1 /* INADDR_LOOPBACK */
#endif
/* break_http: bounded HTTP/1.1 client. A scripted server thread (plain or TLS,
 * one connection per script) lets each test dictate the exact bytes the client
 * sees, so framing, range, TLS and timeout rules are exercised for real. */

#include "test_framework.h"

#include <net_http/break_http.h>

#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdatomic.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#ifndef BREAK_TEST_SSL_FIXTURE_DIR
#error "BREAK_TEST_SSL_FIXTURE_DIR is required"
#endif

#define CERT BREAK_TEST_SSL_FIXTURE_DIR "/break_test_cert.pem"
#define KEY BREAK_TEST_SSL_FIXTURE_DIR "/break_test_key.pem"

/* What a finished test wants to know about the request the server saw. */
typedef struct { char request[8192]; size_t request_len; } SeenRequest;

/* ---- scripted server ---- */

typedef struct {
    int listen_fd;
    unsigned short port;
    bool tls;
    const char *cert_path;    /* NULL = the shared fixture */
    const char *key_path;
    SSL_CTX *ctx;
    const char *reply;        /* bytes to send after the request head, verbatim */
    size_t reply_len;
    int split_at;             /* >0: send reply in two parts with a pause */
    int pause_ms;
    bool stall_after_reply;   /* keep the socket open and silent afterwards */
    int linger_ms;            /* how long to keep a stalled socket open */
    bool reply_on_first_bytes; /* answer without waiting for a full request head */
    int half_close_ms;        /* >0: send FIN, wait, then close with unread data (RST): the client's
                               * socket goes CLOSE_WAIT, then its next write is EPIPE (SIGPIPE) */
    bool drip;                /* one byte every drip_ms (slow-drip server) */
    int drip_ms;
    char request[8192];       /* what the client sent */
    size_t request_len;
    atomic_bool saw_connection;   /* written by the server thread, read by server_stop */
    pthread_t thread;
} Server;

static void *server_main(void *arg) {
    Server *s = (Server *)arg;
    /* a client that gives up (timeout tests) must not kill the test process
     * through the SERVER's writes; the client under test is checked separately */
    {
        sigset_t blk;
        sigemptyset(&blk);
        sigaddset(&blk, SIGPIPE);
        pthread_sigmask(SIG_BLOCK, &blk, NULL);
    }
    struct sockaddr_in peer;
    socklen_t pl = sizeof(peer);
    int fd = accept(s->listen_fd, (struct sockaddr *)&peer, &pl);
    SSL *ssl = NULL;
    size_t sent = 0;
    if (fd < 0) return NULL;
#if defined(SO_NOSIGPIPE)
    {
        /* macOS raises SIGPIPE for the whole process rather than the writing thread, so the
         * thread mask above does not protect the test's main thread there; the socket flag does */
        int one = 1;
        (void)setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &one, sizeof(one));
    }
#endif
    atomic_store(&s->saw_connection, true);
    if (s->tls) {
        ssl = SSL_new(s->ctx);
        SSL_set_fd(ssl, fd);
        if (SSL_accept(ssl) != 1) {
            SSL_free(ssl);
            close(fd);
            return NULL;
        }
    }
    /* read until the blank line (and the body of a POST, if declared) */
    for (;;) {
        char buf[1024];
        int n = ssl ? SSL_read(ssl, buf, sizeof(buf)) : (int)read(fd, buf, sizeof(buf));
        if (n <= 0) break;
        if (s->request_len + (size_t)n < sizeof(s->request)) {
            memcpy(s->request + s->request_len, buf, (size_t)n);
            s->request_len += (size_t)n;
        }
        s->request[s->request_len] = '\0';
        if (s->reply_on_first_bytes) break;
        {
            char *end = strstr(s->request, "\r\n\r\n");
            if (end != NULL) {
                const char *cl = strstr(s->request, "Content-Length: ");
                size_t head = (size_t)(end - s->request) + 4u;
                size_t want = cl != NULL ? (size_t)strtoul(cl + 16, NULL, 10) : 0u;
                if (s->request_len >= head + want) break;
            }
        }
    }
    if (s->half_close_ms > 0) {
        struct timespec ts = {s->half_close_ms / 1000, (long)(s->half_close_ms % 1000) * 1000000L};
        shutdown(fd, SHUT_WR);              /* FIN: the client sees EOF but is still sending */
        nanosleep(&ts, NULL);               /* the client keeps writing into a peer that no longer reads */
        close(fd);                          /* unread data -> RST */
        if (ssl) SSL_free(ssl);
        return NULL;
    }
    if (s->drip) {
        while (sent < s->reply_len) {
            struct timespec ts = {0, (long)s->drip_ms * 1000000L};
            int w = ssl ? SSL_write(ssl, s->reply + sent, 1) : (int)write(fd, s->reply + sent, 1);
            if (w <= 0) break;
            sent++;
            nanosleep(&ts, NULL);
        }
    } else {
        size_t first = s->split_at > 0 ? (size_t)s->split_at : s->reply_len;
        if (first > s->reply_len) first = s->reply_len;
        if (first > 0u) {
            if (ssl) (void)SSL_write(ssl, s->reply, (int)first);
            else (void)write(fd, s->reply, first);
        }
        if (first < s->reply_len) {
            struct timespec ts = {s->pause_ms / 1000, (long)(s->pause_ms % 1000) * 1000000L};
            nanosleep(&ts, NULL);
            if (ssl) (void)SSL_write(ssl, s->reply + first, (int)(s->reply_len - first));
            else (void)write(fd, s->reply + first, s->reply_len - first);
        }
    }
    if (s->stall_after_reply) {
        struct timespec ts = {s->linger_ms / 1000, (long)(s->linger_ms % 1000) * 1000000L};
        nanosleep(&ts, NULL);
    }
    if (ssl) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
    }
    close(fd);
    return NULL;
}

static bool server_start_cert(Server *s, bool tls, const char *reply, size_t reply_len,
                              const char *cert_path, const char *key_path) {
    struct sockaddr_in a;
    socklen_t al = sizeof(a);
    int one = 1;
    memset(s, 0, sizeof(*s));
    s->tls = tls;
    s->cert_path = cert_path;
    s->key_path = key_path;
    s->reply = reply;
    s->reply_len = reply_len;
    s->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (s->listen_fd < 0) return false;
    setsockopt(s->listen_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (bind(s->listen_fd, (struct sockaddr *)&a, sizeof(a)) != 0 || listen(s->listen_fd, 1) != 0 ||
        getsockname(s->listen_fd, (struct sockaddr *)&a, &al) != 0) {
        close(s->listen_fd);
        return false;
    }
    s->port = ntohs(a.sin_port);
    if (tls) {
        s->ctx = SSL_CTX_new(TLS_server_method());
        if (s->ctx == NULL ||
            SSL_CTX_use_certificate_chain_file(s->ctx, s->cert_path ? s->cert_path : CERT) != 1 ||
            SSL_CTX_use_PrivateKey_file(s->ctx, s->key_path ? s->key_path : KEY, SSL_FILETYPE_PEM) != 1) {
            return false;
        }
    }
    return true;
}

static bool server_start(Server *s, bool tls, const char *reply, size_t reply_len) {
    return server_start_cert(s, tls, reply, reply_len, NULL, NULL);
}

static void server_go(Server *s) {
    pthread_create(&s->thread, NULL, server_main, s);
}

static void server_stop(Server *s) {
    /* unblock accept() if the client never connected */
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!atomic_load(&s->saw_connection) && fd >= 0) {
        struct sockaddr_in a;
        memset(&a, 0, sizeof(a));
        a.sin_family = AF_INET;
        a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        a.sin_port = htons(s->port);
        (void)connect(fd, (struct sockaddr *)&a, sizeof(a));
    }
    if (fd >= 0) close(fd);
    pthread_join(s->thread, NULL);
    close(s->listen_fd);
    if (s->ctx) SSL_CTX_free(s->ctx);
}

static void url_of(const Server *s, const char *scheme, const char *host, const char *path,
                   char *out, size_t cap) {
    snprintf(out, cap, "%s://%s:%u%s", scheme, host, (unsigned)s->port, path);
}

#define OK200(body) "HTTP/1.1 200 OK\r\nContent-Length: " #body "\r\n\r\n"

/* runs one GET against a scripted reply */
static BreakHttpError run_get(const char *reply, size_t reply_len, u8 *out, u64 cap, u64 *got,
                              SeenRequest *keep) {
    Server s;
    char url[128];
    BreakHttpConfig cfg;
    BreakHttpError e;
    memset(&cfg, 0, sizeof(cfg));
    cfg.io_timeout_ms = 3000;
    if (!server_start(&s, false, reply, reply_len)) return BHTTP_ERR_CONNECT;
    server_go(&s);
    url_of(&s, "http", "127.0.0.1", "/x", url, sizeof(url));
    e = break_http_get(&cfg, url, out, cap, got);
    server_stop(&s);
    if (keep) { memcpy(keep->request, s.request, sizeof(keep->request)); keep->request_len = s.request_len; }
    return e;
}

#define GET_REPLY(lit, cap, expect)                                           \
    do {                                                                      \
        u8 buf_[64];                                                          \
        u64 got_ = 99;                                                        \
        BreakHttpError e_ = run_get(lit, sizeof(lit) - 1u, buf_, cap, &got_, NULL); \
        if (e_ != (expect)) printf("    got %s want %s\n", break_http_error_name(e_), break_http_error_name(expect)); \
        ASSERT_EQ(e_, (expect));                                              \
    } while (0)

/* ---- plain HTTP: framing ---- */

TEST(get_returns_a_content_length_body) {
    u8 buf[16];
    u64 got = 0;
    static const char r[] = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nhello";
    ASSERT_EQ(run_get(r, sizeof(r) - 1u, buf, sizeof(buf), &got, NULL), BHTTP_OK);
    ASSERT_EQ(got, 5u);
    ASSERT_TRUE(memcmp(buf, "hello", 5) == 0);
}

TEST(request_has_the_expected_shape) {
    Server s;
    char url[128];
    u8 buf[8];
    u64 got = 0;
    BreakHttpConfig cfg;
    static const char r[] = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
    memset(&cfg, 0, sizeof(cfg));
    ASSERT_TRUE(server_start(&s, false, r, sizeof(r) - 1u));
    server_go(&s);
    url_of(&s, "http", "127.0.0.1", "/a/b?q=1", url, sizeof(url));
    ASSERT_EQ(break_http_get(&cfg, url, buf, sizeof(buf), &got), BHTTP_OK);
    server_stop(&s);
    ASSERT_TRUE(strncmp(s.request, "GET /a/b?q=1 HTTP/1.1\r\n", 23) == 0);
    ASSERT_TRUE(strstr(s.request, "\r\nConnection: close\r\n") != NULL);
    ASSERT_TRUE(strstr(s.request, "\r\nAccept-Encoding: identity\r\n") != NULL);
    ASSERT_TRUE(strstr(s.request, "\r\nHost: 127.0.0.1:") != NULL);
    ASSERT_TRUE(strstr(s.request, "\r\nRange:") == NULL); /* a plain GET has no range */
}

TEST(non_200_and_redirects_are_status_errors) {
    GET_REPLY("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n", 8u, BHTTP_ERR_STATUS);
    GET_REPLY("HTTP/1.1 500 Oops\r\nContent-Length: 0\r\n\r\n", 8u, BHTTP_ERR_STATUS);
    GET_REPLY("HTTP/1.1 301 Moved\r\nLocation: http://127.0.0.1:1/\r\nContent-Length: 0\r\n\r\n", 8u, BHTTP_ERR_STATUS);
    GET_REPLY("HTTP/1.1 302 Found\r\nLocation: http://evil/\r\nContent-Length: 0\r\n\r\n", 8u, BHTTP_ERR_STATUS);
    GET_REPLY("HTTP/1.1 206 Partial\r\nContent-Length: 0\r\n\r\n", 8u, BHTTP_ERR_STATUS); /* plain GET expects 200 */
}

TEST(body_larger_than_the_buffer_is_too_big_before_it_is_read) {
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 9\r\n\r\n123456789", 8u, BHTTP_ERR_TOO_BIG);
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 99999999999\r\n\r\n", 8u, BHTTP_ERR_TOO_BIG);
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 8\r\n\r\n12345678", 8u, BHTTP_OK); /* exactly the cap fits */
}

TEST(a_response_without_content_length_is_refused_not_read_until_close) {
    /* The head arrives, then the body a moment later. With "read until close" framing
     * the client would return the body; with trailing-bytes detection alone it would
     * return OK with ZERO bytes (nothing had arrived yet). Only the framing rule
     * itself gives PROTOCOL. */
    Server s;
    char url[128];
    u8 buf[64];
    u64 got = 77;
    BreakHttpConfig cfg;
    static const char r[] = "HTTP/1.1 200 OK\r\nConnection: close\r\n\r\nthe whole body, delimited by the close";
    memset(&cfg, 0, sizeof(cfg));
    cfg.io_timeout_ms = 3000;
    ASSERT_TRUE(server_start(&s, false, r, sizeof(r) - 1u));
    s.split_at = 38;      /* exactly the 38-byte head, so no body byte rides with it */
    s.pause_ms = 300;
    server_go(&s);
    url_of(&s, "http", "127.0.0.1", "/x", url, sizeof(url));
    ASSERT_EQ(break_http_get(&cfg, url, buf, sizeof(buf), &got), BHTTP_ERR_PROTOCOL);
    server_stop(&s);
    /* the same split WITH a length is fine: the only difference is the framing */
    {
        static const char ok[] = "HTTP/1.1 200 OK\r\nContent-Length: 38\r\n\r\nthe whole body, delimited by the close";
        ASSERT_TRUE(server_start(&s, false, ok, sizeof(ok) - 1u));
        s.split_at = 39;  /* exactly the 39-byte head */
        s.pause_ms = 300;
        server_go(&s);
        url_of(&s, "http", "127.0.0.1", "/x", url, sizeof(url));
        ASSERT_EQ(break_http_get(&cfg, url, buf, sizeof(buf), &got), BHTTP_OK);
        ASSERT_EQ(got, 38u);
        ASSERT_TRUE(memcmp(buf, "the whole body", 14) == 0);
        server_stop(&s);
    }
}

TEST(truncated_body_and_missing_framing_are_protocol_errors) {
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 10\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\n\r\nno length, read until close", 64u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 3\r\n\r\nabcEXTRA", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 3\r\n", 16u, BHTTP_ERR_PROTOCOL);   /* head never ends */
    GET_REPLY("", 16u, BHTTP_ERR_PROTOCOL);                                           /* closed at once */
    GET_REPLY("garbage that is not http\r\n\r\n", 16u, BHTTP_ERR_PROTOCOL);
}

TEST(forbidden_or_ambiguous_headers_are_protocol_errors) {
    /* chunked: refused outright */
    GET_REPLY("HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n3\r\nabc\r\n0\r\n\r\n", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\nContent-Length: 3\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    /* a smuggling-style pair of lengths */
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 3\r\nContent-Length: 3\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 3\r\nContent-Length: 4\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    /* non-canonical numbers */
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: +3\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 03\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: -1\r\n\r\n", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 3 4\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: \r\n\r\n", 16u, BHTTP_ERR_PROTOCOL);
    /* encodings: only identity */
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Encoding: gzip\r\nContent-Length: 3\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Encoding: identity\r\nContent-Length: 3\r\n\r\nabc", 16u, BHTTP_OK);
    /* interim responses are not supported */
    GET_REPLY("HTTP/1.1 100 Continue\r\n\r\nHTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n", 16u, BHTTP_ERR_PROTOCOL);
    /* header syntax */
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 3\r\n bad-fold\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nBad Header: x\r\nContent-Length: 3\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nNoColon\r\nContent-Length: 3\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\nContent-Length: 3\n\nabc", 16u, BHTTP_ERR_PROTOCOL);          /* bare LF */
    GET_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 3\r\nX: a\rb\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL); /* bare CR */
    GET_REPLY("HTTP/2 200 OK\r\nContent-Length: 3\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 99 X\r\nContent-Length: 3\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 2000 X\r\nContent-Length: 3\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
    GET_REPLY("HTTP/1.1 200 OK\r\nX-Nul: a\0b\r\nContent-Length: 3\r\n\r\nabc", 16u, BHTTP_ERR_PROTOCOL);
}

TEST(head_size_and_header_count_are_bounded) {
    char big[BREAK_HTTP_MAX_HEAD + 512];
    size_t n = 0;
    u8 buf[8];
    u64 got = 0;
    /* 65 headers: one over the limit */
    n = (size_t)snprintf(big, sizeof(big), "HTTP/1.1 200 OK\r\n");
    for (int i = 0; i < 65; i++) n += (size_t)snprintf(big + n, sizeof(big) - n, "X-%d: v\r\n", i);
    n += (size_t)snprintf(big + n, sizeof(big) - n, "Content-Length: 0\r\n\r\n");
    ASSERT_EQ(run_get(big, n, buf, sizeof(buf), &got, NULL), BHTTP_ERR_PROTOCOL);
    /* exactly 64 headers (63 filler + Content-Length) is accepted */
    n = (size_t)snprintf(big, sizeof(big), "HTTP/1.1 200 OK\r\n");
    for (int i = 0; i < 63; i++) n += (size_t)snprintf(big + n, sizeof(big) - n, "X-%d: v\r\n", i);
    n += (size_t)snprintf(big + n, sizeof(big) - n, "Content-Length: 0\r\n\r\n");
    ASSERT_EQ(run_get(big, n, buf, sizeof(buf), &got, NULL), BHTTP_OK);
    /* a head that never ends within 8 KiB */
    n = (size_t)snprintf(big, sizeof(big), "HTTP/1.1 200 OK\r\nX-Long: ");
    memset(big + n, 'a', BREAK_HTTP_MAX_HEAD);
    n += BREAK_HTTP_MAX_HEAD;
    ASSERT_EQ(run_get(big, n, buf, sizeof(buf), &got, NULL), BHTTP_ERR_PROTOCOL);
}

TEST(204_has_no_body_and_a_declared_one_is_refused) {
    u8 buf[8];
    u64 got = 5;
    static const char ok[] = "HTTP/1.1 204 No Content\r\n\r\n";
    GET_REPLY("HTTP/1.1 204 No Content\r\nContent-Length: 4\r\n\r\nabcd", 16u, BHTTP_ERR_STATUS); /* GET expects 200 */
    (void)ok; (void)buf; (void)got;
}

/* ---- range requests ---- */

static BreakHttpError run_range(const char *reply, size_t reply_len, u64 off, u64 len, u8 *out,
                                SeenRequest *keep) {
    Server s;
    char url[128];
    BreakHttpConfig cfg;
    BreakHttpError e;
    memset(&cfg, 0, sizeof(cfg));
    cfg.io_timeout_ms = 3000;
    if (!server_start(&s, false, reply, reply_len)) return BHTTP_ERR_CONNECT;
    server_go(&s);
    url_of(&s, "http", "127.0.0.1", "/objects/x", url, sizeof(url));
    e = break_http_get_range(&cfg, url, off, len, out);
    server_stop(&s);
    if (keep) { memcpy(keep->request, s.request, sizeof(keep->request)); keep->request_len = s.request_len; }
    return e;
}

#define RANGE_REPLY(lit, off, len, expect)                                              \
    do {                                                                                \
        u8 buf_[64];                                                                    \
        BreakHttpError e_ = run_range(lit, sizeof(lit) - 1u, off, len, buf_, NULL);     \
        if (e_ != (expect)) printf("    got %s want %s\n", break_http_error_name(e_), break_http_error_name(expect)); \
        ASSERT_EQ(e_, (expect));                                                        \
    } while (0)

TEST(range_request_sends_the_header_and_accepts_the_exact_range) {
    SeenRequest s;
    u8 buf[8];
    static const char r[] = "HTTP/1.1 206 Partial Content\r\nContent-Range: bytes 10-14/100\r\nContent-Length: 5\r\n\r\nhello";
    ASSERT_EQ(run_range(r, sizeof(r) - 1u, 10u, 5u, buf, &s), BHTTP_OK);
    ASSERT_TRUE(memcmp(buf, "hello", 5) == 0);
    ASSERT_TRUE(strstr(s.request, "\r\nRange: bytes=10-14\r\n") != NULL);
}

TEST(range_answered_with_anything_but_the_exact_range_is_rejected) {
    /* 200: the server ignored the range */
    RANGE_REPLY("HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nhello", 10u, 5u, BHTTP_ERR_RANGE);
    /* Content-Range for another window */
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Range: bytes 0-4/100\r\nContent-Length: 5\r\n\r\nhello", 10u, 5u, BHTTP_ERR_RANGE);
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Range: bytes 10-13/100\r\nContent-Length: 4\r\n\r\nhell", 10u, 5u, BHTTP_ERR_RANGE);
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Range: bytes 11-15/100\r\nContent-Length: 5\r\n\r\nhello", 10u, 5u, BHTTP_ERR_RANGE);
    /* no Content-Range at all */
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Length: 5\r\n\r\nhello", 10u, 5u, BHTTP_ERR_RANGE);
    /* Content-Range right, body shorter than the range */
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Range: bytes 10-14/100\r\nContent-Length: 3\r\n\r\nhel", 10u, 5u, BHTTP_ERR_RANGE);
    /* Content-Range right, body longer than the range */
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Range: bytes 10-14/100\r\nContent-Length: 9\r\n\r\nhelloextr", 10u, 5u, BHTTP_ERR_TOO_BIG);
    /* malformed Content-Range */
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Range: bytes 10-14\r\nContent-Length: 5\r\n\r\nhello", 10u, 5u, BHTTP_ERR_PROTOCOL);
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Range: items 10-14/100\r\nContent-Length: 5\r\n\r\nhello", 10u, 5u, BHTTP_ERR_PROTOCOL);
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Range: bytes 14-10/100\r\nContent-Length: 5\r\n\r\nhello", 10u, 5u, BHTTP_ERR_PROTOCOL);
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Range: bytes 10-14/12\r\nContent-Length: 5\r\n\r\nhello", 10u, 5u, BHTTP_ERR_PROTOCOL);
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Range: bytes 10-14/100\r\nContent-Range: bytes 10-14/100\r\nContent-Length: 5\r\n\r\nhello", 10u, 5u, BHTTP_ERR_PROTOCOL);
    /* other statuses */
    RANGE_REPLY("HTTP/1.1 416 Range Not Satisfiable\r\nContent-Length: 0\r\n\r\n", 10u, 5u, BHTTP_ERR_STATUS);
    RANGE_REPLY("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n", 10u, 5u, BHTTP_ERR_STATUS);
    /* unknown total is allowed */
    RANGE_REPLY("HTTP/1.1 206 P\r\nContent-Range: bytes 10-14/*\r\nContent-Length: 5\r\n\r\nhello", 10u, 5u, BHTTP_OK);
}

TEST(range_arguments_are_validated_before_any_connection) {
    BreakHttpConfig cfg;
    u8 buf[8];
    memset(&cfg, 0, sizeof(cfg));
    ASSERT_EQ(break_http_get_range(&cfg, "http://127.0.0.1:1/x", 0u, 0u, buf), BHTTP_ERR_URL);          /* len 0 */
    ASSERT_EQ(break_http_get_range(&cfg, "http://127.0.0.1:1/x", UINT64_MAX, 2u, buf), BHTTP_ERR_URL);  /* overflow */
    ASSERT_EQ(break_http_get_range(&cfg, "http://127.0.0.1:1/x", UINT64_MAX - 1u, 2u, buf), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_get_range(&cfg, "http://127.0.0.1:1/x", 0u, 1u, NULL), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_get_range(&cfg, NULL, 0u, 1u, buf), BHTTP_ERR_URL);
}

/* ---- URL rules ---- */

TEST(url_rules_reject_before_any_socket_is_created) {
    BreakHttpConfig cfg;
    u8 buf[8];
    u64 got;
    static const char *const bad[] = {
        "", "ftp://127.0.0.1/x", "127.0.0.1/x", "http://", "http:///x", "http://:80/x",
        "http://user@127.0.0.1/x", "http://user:pw@127.0.0.1/x", "http://127.0.0.1:0/x",
        "http://127.0.0.1:70000/x", "http://127.0.0.1:12ab/x", "http://127.0.0.1:/x",
        "http://127.0.0.1/x y", "http://127.0.0.1/x\r\nHost: evil", "http://127.0.0.1/x\n",
        "http://127.0.0.1/x#frag", "http://127.0.0.1/\\x", "http://[::1/x", "http://[]/x",
        "http://[::1]x/x", "http://[zz]/x", "http://exa_mple.com/x", "http://exa mple.com/x",
        "http://127.0.0.1/\x7f", "http://127.0.0.1/\xc3\xa9"};
    memset(&cfg, 0, sizeof(cfg));
    for (size_t i = 0; i < sizeof(bad) / sizeof(bad[0]); i++) {
        if (break_http_get(&cfg, bad[i], buf, sizeof(buf), &got) != BHTTP_ERR_URL) {
            printf("    accepted: '%s'\n", bad[i]);
        }
        ASSERT_EQ(break_http_get(&cfg, bad[i], buf, sizeof(buf), &got), BHTTP_ERR_URL);
        ASSERT_EQ(got, 0u);
    }
    {
        char longurl[BREAK_HTTP_MAX_URL + 64];
        memcpy(longurl, "http://127.0.0.1/", 17);
        memset(longurl + 17, 'a', BREAK_HTTP_MAX_URL);
        longurl[17 + BREAK_HTTP_MAX_URL] = '\0';
        ASSERT_EQ(break_http_get(&cfg, longurl, buf, sizeof(buf), &got), BHTTP_ERR_URL);
    }
}

TEST(plain_http_to_a_non_loopback_host_is_refused_without_connecting) {
    BreakHttpConfig cfg;
    u8 buf[8];
    u64 got;
    memset(&cfg, 0, sizeof(cfg));
    cfg.connect_timeout_ms = 200;
    /* documentation / test / private addresses: a connect attempt would hang or
     * fail with a different error; the refusal must come first */
    ASSERT_EQ(break_http_get(&cfg, "http://192.0.2.1/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_get(&cfg, "http://10.0.0.1/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_get(&cfg, "http://8.8.8.8/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_get(&cfg, "http://[2001:db8::1]/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_get(&cfg, "http://0.0.0.0/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_get(&cfg, "http://[::ffff:8.8.8.8]/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_get(&cfg, "http://128.0.0.1/x", buf, sizeof(buf), &got), BHTTP_ERR_URL); /* not 127/8 */
}

TEST(loopback_ipv6_and_the_127_block_are_allowed_for_plain_http) {
    BreakHttpConfig cfg;
    u8 buf[8];
    u64 got;
    memset(&cfg, 0, sizeof(cfg));
    cfg.connect_timeout_ms = 500;
    /* nothing listens on port 1: the answer is CONNECT, which proves the URL
     * and loopback rules let it through */
    ASSERT_EQ(break_http_get(&cfg, "http://127.0.0.1:1/x", buf, sizeof(buf), &got), BHTTP_ERR_CONNECT);
    {
        /* Linux routes all of 127/8 to the loopback, so the answer is a refused connection; macOS
         * only configures 127.0.0.1, so the same attempt can run into the connect budget. Either
         * proves the policy let the address through; what it must never be is a URL error. */
        BreakHttpError e = break_http_get(&cfg, "http://127.5.6.7:1/x", buf, sizeof(buf), &got);
        ASSERT_TRUE(e == BHTTP_ERR_CONNECT || e == BHTTP_ERR_TIMEOUT);
    }
    ASSERT_EQ(break_http_get(&cfg, "http://[::1]:1/x", buf, sizeof(buf), &got), BHTTP_ERR_CONNECT);
    ASSERT_EQ(break_http_get(&cfg, "http://localhost:1/x", buf, sizeof(buf), &got), BHTTP_ERR_CONNECT);
}

TEST(https_without_a_ca_file_is_refused_there_is_no_insecure_mode) {
    BreakHttpConfig cfg;
    u8 buf[8];
    u64 got;
    memset(&cfg, 0, sizeof(cfg));
    ASSERT_EQ(break_http_get(&cfg, "https://127.0.0.1:1/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_get(NULL, "https://127.0.0.1:1/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    cfg.ca_file = "";
    ASSERT_EQ(break_http_get(&cfg, "https://127.0.0.1:1/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    cfg.ca_file = "/nonexistent/ca.pem";
    ASSERT_EQ(break_http_get(&cfg, "https://127.0.0.1:1/x", buf, sizeof(buf), &got), BHTTP_ERR_TLS);
}

/* ---- timeouts ---- */

static u64 mono_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (u64)ts.tv_sec * 1000u + (u64)ts.tv_nsec / 1000000u;
}

TEST(a_silent_server_times_out_within_the_io_budget) {
    Server s;
    char url[128];
    u8 buf[8];
    u64 got, t0, dt;
    BreakHttpConfig cfg;
    static const char r[] = "";
    memset(&cfg, 0, sizeof(cfg));
    cfg.io_timeout_ms = 400;
    ASSERT_TRUE(server_start(&s, false, r, 0u));
    s.stall_after_reply = true;
    s.linger_ms = 1500;
    server_go(&s);
    url_of(&s, "http", "127.0.0.1", "/x", url, sizeof(url));
    t0 = mono_ms();
    ASSERT_EQ(break_http_get(&cfg, url, buf, sizeof(buf), &got), BHTTP_ERR_TIMEOUT);
    dt = mono_ms() - t0;
    server_stop(&s);
    ASSERT_TRUE(dt >= 350u);
    ASSERT_TRUE(dt < 1200u);
}

TEST(a_slow_drip_server_cannot_hold_the_call_past_the_total_budget) {
    Server s;
    char url[128];
    u8 buf[64];
    u64 got, t0, dt;
    BreakHttpConfig cfg;
    static const char r[] = "HTTP/1.1 200 OK\r\nContent-Length: 20\r\n\r\n01234567890123456789";
    memset(&cfg, 0, sizeof(cfg));
    cfg.io_timeout_ms = 600;
    ASSERT_TRUE(server_start(&s, false, r, sizeof(r) - 1u));
    s.drip = true;
    s.drip_ms = 60;      /* one byte per 60 ms: every read arrives, the total does not */
    server_go(&s);
    url_of(&s, "http", "127.0.0.1", "/x", url, sizeof(url));
    t0 = mono_ms();
    ASSERT_EQ(break_http_get(&cfg, url, buf, sizeof(buf), &got), BHTTP_ERR_TIMEOUT);
    dt = mono_ms() - t0;
    server_stop(&s);
    ASSERT_TRUE(dt < 1400u);
}

TEST(a_connect_to_an_unroutable_address_is_bounded_by_the_connect_budget) {
    /* TEST-NET addresses are not loopback, so plain http refuses them; use https
     * with a CA so the refusal does not apply, and a short connect budget */
    BreakHttpConfig cfg;
    u8 buf[8];
    u64 got, t0, dt;
    BreakHttpError e;
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = CERT;
    cfg.connect_timeout_ms = 300;
    cfg.io_timeout_ms = 300;
    t0 = mono_ms();
    e = break_http_get(&cfg, "https://192.0.2.1:9/x", buf, sizeof(buf), &got);
    dt = mono_ms() - t0;
    ASSERT_TRUE(e == BHTTP_ERR_TIMEOUT || e == BHTTP_ERR_CONNECT); /* sandboxes may reject at once */
    ASSERT_TRUE(dt < 1500u);
}

static volatile sig_atomic_t g_sigpipe_seen;
static void on_sigpipe(int sig) { (void)sig; g_sigpipe_seen = 1; }

/* The scripted server reads the first bytes of the request and closes WITHOUT
 * answering (reply_on_first_bytes, empty reply). The client is still writing
 * its large body: after the peer's FIN and the RST that follows, the next
 * write is EPIPE, which raises SIGPIPE unless the call prevents it. A handler
 * records any delivery; the call must fail and the handler must stay silent. */
static void sigpipe_case(bool tls, int *seen, BreakHttpError *err) {
    Server s;
    char url[128];
    static u8 body[16 * 1024 * 1024];
    u8 resp[16];
    usize rl = 0;
    int status = 0;
    BreakHttpConfig cfg;
    struct sigaction sa, old;
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = CERT;
    cfg.io_timeout_ms = 4000;
    memset(body, 'x', sizeof(body));
    if (!server_start(&s, tls, "", 0u)) { *err = BHTTP_ERR_CONNECT; *seen = -1; return; }
    s.reply_on_first_bytes = true;
    s.half_close_ms = 400;
    server_go(&s);
    url_of(&s, tls ? "https" : "http", tls ? "localhost" : "127.0.0.1", "/up", url, sizeof(url));
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = on_sigpipe;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGPIPE, &sa, &old);
    g_sigpipe_seen = 0;
    *err = break_http_post(&cfg, url, body, sizeof(body), "application/octet-stream", resp,
                           sizeof(resp), &rl, &status);
    sigaction(SIGPIPE, &old, NULL);
    *seen = g_sigpipe_seen;
    server_stop(&s);
}

TEST(a_write_to_a_closed_peer_raises_no_sigpipe_over_plain_http) {
    int seen = -1;
    BreakHttpError e = BHTTP_OK;
    sigpipe_case(false, &seen, &e);
    ASSERT_TRUE(e != BHTTP_OK);
    ASSERT_EQ(seen, 0);
}

TEST(a_write_to_a_closed_peer_raises_no_sigpipe_over_tls) {
    /* OpenSSL writes with plain write(): only the signal mask protects here */
    int seen = -1;
    BreakHttpError e = BHTTP_OK;
    sigpipe_case(true, &seen, &e);
    ASSERT_TRUE(e != BHTTP_OK);
    ASSERT_EQ(seen, 0);
}

TEST(a_peer_that_closes_early_does_not_kill_the_process_with_sigpipe) {
    /* a POST with a large body to a server that answers and closes: the write
     * may hit a closed socket. The process must survive and SIGPIPE must not
     * be left pending or delivered. */
    Server s;
    char url[128];
    static u8 body[2 * 1024 * 1024];
    u8 resp[64];
    usize rl = 0;
    int status = 0;
    BreakHttpConfig cfg;
    sigset_t pend;
    static const char r[] = "HTTP/1.1 413 Too Large\r\nContent-Length: 0\r\n\r\n";
    memset(&cfg, 0, sizeof(cfg));
    cfg.io_timeout_ms = 3000;
    memset(body, 'x', sizeof(body));
    ASSERT_TRUE(server_start(&s, false, r, sizeof(r) - 1u));
    server_go(&s);
    url_of(&s, "http", "127.0.0.1", "/up", url, sizeof(url));
    (void)break_http_post(&cfg, url, body, sizeof(body), "application/octet-stream", resp,
                          sizeof(resp), &rl, &status);
    server_stop(&s);
    sigpending(&pend);
    ASSERT_EQ(sigismember(&pend, SIGPIPE), 0);
}

/* ---- POST ---- */

TEST(post_sends_the_body_and_reports_any_complete_status) {
    Server s;
    char url[128];
    u8 resp[32];
    usize rl = 0;
    int status = 0;
    BreakHttpConfig cfg;
    static const char r[] = "HTTP/1.1 400 Bad Request\r\nContent-Length: 4\r\n\r\nnope";
    memset(&cfg, 0, sizeof(cfg));
    cfg.io_timeout_ms = 3000;
    ASSERT_TRUE(server_start(&s, false, r, sizeof(r) - 1u));
    server_go(&s);
    url_of(&s, "http", "127.0.0.1", "/crash", url, sizeof(url));
    ASSERT_EQ(break_http_post(&cfg, url, "payload", 7u, "application/x-break", resp, sizeof(resp),
                              &rl, &status),
              BHTTP_OK);
    server_stop(&s);
    ASSERT_EQ(status, 400);
    ASSERT_EQ(rl, 4u);
    ASSERT_TRUE(memcmp(resp, "nope", 4) == 0);
    ASSERT_TRUE(strncmp(s.request, "POST /crash HTTP/1.1\r\n", 22) == 0);
    ASSERT_TRUE(strstr(s.request, "\r\nContent-Type: application/x-break\r\n") != NULL);
    ASSERT_TRUE(strstr(s.request, "\r\nContent-Length: 7\r\n") != NULL);
    ASSERT_TRUE(strstr(s.request, "\r\n\r\npayload") != NULL);
}

TEST(post_validates_its_arguments) {
    BreakHttpConfig cfg;
    u8 resp[8];
    usize rl;
    int st;
    memset(&cfg, 0, sizeof(cfg));
    ASSERT_EQ(break_http_post(&cfg, "http://127.0.0.1:1/x", "a", 1u, "bad type", resp, 8u, &rl, &st), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_post(&cfg, "http://127.0.0.1:1/x", "a", 1u, "text", resp, 8u, &rl, &st), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_post(&cfg, "http://127.0.0.1:1/x", "a", 1u, "text/plain\r\nX: y", resp, 8u, &rl, &st), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_post(&cfg, "http://127.0.0.1:1/x", NULL, 1u, "a/b", resp, 8u, &rl, &st), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_post(&cfg, "http://127.0.0.1:1/x", "a", 1u, NULL, resp, 8u, &rl, &st), BHTTP_ERR_URL);
    ASSERT_EQ(break_http_post(&cfg, "http://127.0.0.1:1/x", "a", 17u * 1024u * 1024u, "a/b", resp, 8u, &rl, &st), BHTTP_ERR_URL);
}

/* ---- TLS ---- */

static BreakHttpError tls_get(const char *host, const char *ca, bool good_server, u8 *out,
                              u64 cap, u64 *got) {
    Server s;
    char url[128];
    BreakHttpConfig cfg;
    BreakHttpError e;
    static const char r[] = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nhello";
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = ca;
    cfg.io_timeout_ms = 3000;
    (void)good_server;
    if (!server_start(&s, true, r, sizeof(r) - 1u)) return BHTTP_ERR_CONNECT;
    server_go(&s);
    url_of(&s, "https", host, "/x", url, sizeof(url));
    e = break_http_get(&cfg, url, out, cap, got);
    server_stop(&s);
    return e;
}

TEST(https_succeeds_when_the_certificate_matches_the_ca_and_the_host) {
    u8 buf[16];
    u64 got = 0;
    ASSERT_EQ(tls_get("localhost", CERT, true, buf, sizeof(buf), &got), BHTTP_OK);
    ASSERT_EQ(got, 5u);
    ASSERT_TRUE(memcmp(buf, "hello", 5) == 0);
}

TEST(https_to_an_ip_literal_fails_because_the_certificate_has_no_ip_san) {
    u8 buf[16];
    u64 got = 0;
    /* the fixture certificate is for DNS:localhost only */
    ASSERT_EQ(tls_get("127.0.0.1", CERT, true, buf, sizeof(buf), &got), BHTTP_ERR_TLS);
}

TEST(https_with_the_wrong_ca_is_a_tls_error) {
    u8 buf[16];
    u64 got = 0;
    /* a different self-signed certificate is not a trust anchor for this server */
    ASSERT_EQ(tls_get("localhost", KEY, true, buf, sizeof(buf), &got), BHTTP_ERR_TLS);
}

/* ---- SPKI pinning ---- */

static bool fixture_spki_sha256(u8 out[BREAK_HTTP_PIN_BYTES]) {
    FILE *f = fopen(CERT, "rb");
    X509 *x;
    unsigned char *der = NULL;
    unsigned int len = 0u;
    int n;
    bool ok;
    if (f == NULL) return false;
    x = PEM_read_X509(f, NULL, NULL, NULL);
    fclose(f);
    if (x == NULL) return false;
    n = i2d_X509_PUBKEY(X509_get_X509_PUBKEY(x), &der);
    ok = n > 0 && EVP_Digest(der, (size_t)n, out, &len, EVP_sha256(), NULL) == 1 &&
         len == BREAK_HTTP_PIN_BYTES;
    OPENSSL_free(der);
    X509_free(x);
    return ok;
}

static BreakHttpError pinned_get(bool tls, const char *ca, const u8 *pins, u32 count) {
    Server s;
    char url[128];
    u8 buf[16];
    u64 got = 0;
    BreakHttpConfig cfg;
    BreakHttpError e;
    static const char r[] = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nhello";
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = ca;
    cfg.io_timeout_ms = 3000;
    cfg.spki_sha256_pins = pins;
    cfg.spki_pin_count = count;
    if (!server_start(&s, tls, r, sizeof(r) - 1u)) return BHTTP_ERR_CONNECT;
    server_go(&s);
    url_of(&s, tls ? "https" : "http", tls ? "localhost" : "127.0.0.1", "/x", url, sizeof(url));
    e = break_http_get(&cfg, url, buf, sizeof(buf), &got);
    server_stop(&s);
    if (e == BHTTP_OK && (got != 5u || memcmp(buf, "hello", 5) != 0)) return BHTTP_ERR_PROTOCOL;
    return e;
}

TEST(https_accepts_a_leaf_key_listed_in_the_pins) {
    u8 pins[2u * BREAK_HTTP_PIN_BYTES];
    memset(pins, 0x11, sizeof(pins));
    ASSERT_TRUE(fixture_spki_sha256(pins + BREAK_HTTP_PIN_BYTES));
    ASSERT_EQ(pinned_get(true, CERT, pins, 2u), BHTTP_OK);
    ASSERT_EQ(pinned_get(true, CERT, pins + BREAK_HTTP_PIN_BYTES, 1u), BHTTP_OK);
}

TEST(https_rejects_a_leaf_key_outside_the_pins) {
    u8 pins[2u * BREAK_HTTP_PIN_BYTES];
    ASSERT_TRUE(fixture_spki_sha256(pins));
    pins[BREAK_HTTP_PIN_BYTES - 1u] ^= 0x01u;
    memset(pins + BREAK_HTTP_PIN_BYTES, 0x22, BREAK_HTTP_PIN_BYTES);
    ASSERT_EQ(pinned_get(true, CERT, pins, 2u), BHTTP_ERR_TLS);
    ASSERT_EQ(pinned_get(true, CERT, pins, 0u), BHTTP_OK);
}

TEST(a_matching_pin_does_not_replace_ca_verification) {
    u8 pin[BREAK_HTTP_PIN_BYTES];
    ASSERT_TRUE(fixture_spki_sha256(pin));
    ASSERT_EQ(pinned_get(true, KEY, pin, 1u), BHTTP_ERR_TLS);
}

TEST(pin_arguments_are_validated_before_any_socket) {
    u8 pins[(BREAK_HTTP_MAX_PINS + 1u) * BREAK_HTTP_PIN_BYTES];
    u8 buf[8];
    u64 got = 0;
    BreakHttpConfig cfg;
    memset(pins, 0, sizeof(pins));
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = CERT;
    cfg.spki_sha256_pins = pins;
    cfg.spki_pin_count = BREAK_HTTP_MAX_PINS + 1u;
    ASSERT_EQ(break_http_get(&cfg, "https://localhost:1/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    cfg.spki_pin_count = 1u;
    cfg.spki_sha256_pins = NULL;
    ASSERT_EQ(break_http_get(&cfg, "https://localhost:1/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    cfg.spki_sha256_pins = pins;
    cfg.spki_pin_count = BREAK_HTTP_MAX_PINS;
    ASSERT_EQ(break_http_get(&cfg, "https://localhost:1/x", buf, sizeof(buf), &got), BHTTP_ERR_CONNECT);
}

TEST(a_handshake_timeout_with_pins_stays_a_timeout) {
    /* The pin check runs only after a completed handshake, so a stalled
     * handshake keeps its TIMEOUT instead of turning into a pin failure. */
    Server s;
    char url[128];
    u8 buf[8];
    u8 pin[BREAK_HTTP_PIN_BYTES];
    u64 got = 0;
    BreakHttpConfig cfg;
    ASSERT_TRUE(fixture_spki_sha256(pin));
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = CERT;
    cfg.io_timeout_ms = 400;
    cfg.spki_sha256_pins = pin;
    cfg.spki_pin_count = 1u;
    ASSERT_TRUE(server_start(&s, false, "", 0u));
    s.stall_after_reply = true;
    s.linger_ms = 600;
    server_go(&s);
    url_of(&s, "https", "localhost", "/x", url, sizeof(url));
    ASSERT_EQ(break_http_get(&cfg, url, buf, sizeof(buf), &got), BHTTP_ERR_TIMEOUT);
    server_stop(&s);
}

TEST(pins_are_ignored_for_loopback_http) {
    u8 pin[BREAK_HTTP_PIN_BYTES];
    memset(pin, 0x33, sizeof(pin));
    ASSERT_EQ(pinned_get(false, NULL, pin, 1u), BHTTP_OK);
}

/* ---- in-process certificate generation (wrong name / expired) ---- */

static void tmp_file(char *out, size_t cap, const char *tag) {
    const char *dir = getenv("TMPDIR");
    snprintf(out, cap, "%s/break_http_%s_%d.pem", dir && dir[0] ? dir : "/tmp", tag, (int)getpid());
}

/* Self-signed EC P-256 certificate for DNS:`san`, valid from `from_days` to
 * `to_days` relative to now (negative = in the past). Cert and key in two files. */
static bool gen_cert(const char *cert_path, const char *key_path, const char *san,
                     long from_days, long to_days) {
    EVP_PKEY *pkey = EVP_EC_gen("P-256");
    X509 *x = X509_new();
    X509_NAME *name;
    X509_EXTENSION *ext = NULL;
    X509V3_CTX v3;
    char conf[300];
    FILE *f;
    bool ok = false;
    if (pkey == NULL || x == NULL) goto out;
    X509_set_version(x, 2);
    ASN1_INTEGER_set(X509_get_serialNumber(x), 7);
    X509_gmtime_adj(X509_getm_notBefore(x), from_days * 24L * 3600L);
    X509_gmtime_adj(X509_getm_notAfter(x), to_days * 24L * 3600L);
    X509_set_pubkey(x, pkey);
    name = X509_NAME_new();
    if (name == NULL) goto out;
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (const unsigned char *)san, -1, -1, 0);
    X509_set_subject_name(x, name);
    X509_set_issuer_name(x, name);
    X509_NAME_free(name);
    X509V3_set_ctx_nodb(&v3);
    X509V3_set_ctx(&v3, x, x, NULL, NULL, 0);
    snprintf(conf, sizeof(conf), "DNS:%s", san);
    ext = X509V3_EXT_conf_nid(NULL, &v3, NID_subject_alt_name, conf);
    if (ext == NULL || X509_add_ext(x, ext, -1) != 1) goto out;
    if (X509_sign(x, pkey, EVP_sha256()) <= 0) goto out;
    f = fopen(cert_path, "wb");
    if (f == NULL) goto out;
    ok = PEM_write_X509(f, x) == 1;
    fclose(f);
    f = fopen(key_path, "wb");
    if (f == NULL) { ok = false; goto out; }
    ok = ok && PEM_write_PrivateKey(f, pkey, NULL, NULL, 0, NULL, NULL) == 1;
    fclose(f);
out:
    if (ext) X509_EXTENSION_free(ext);
    X509_free(x);
    EVP_PKEY_free(pkey);
    return ok;
}

/* Serves a generated certificate on 127.0.0.1 and asks for https://localhost:port/. */
static BreakHttpError tls_get_with_cert(const char *san, long from_days, long to_days, bool trust_it) {
    Server s;
    char url[128], cp[300], kp[300];
    u8 buf[16];
    u64 got = 0;
    BreakHttpConfig cfg;
    BreakHttpError e;
    static const char r[] = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nhello";
    tmp_file(cp, sizeof(cp), "cert");
    tmp_file(kp, sizeof(kp), "key");
    if (!gen_cert(cp, kp, san, from_days, to_days)) return BHTTP_ERR_CONNECT;
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = trust_it ? cp : CERT;       /* untrusted: the fixture CA does not vouch for it */
    cfg.io_timeout_ms = 3000;
    if (!server_start_cert(&s, true, r, sizeof(r) - 1u, cp, kp)) {
        remove(cp); remove(kp);
        return BHTTP_ERR_CONNECT;
    }
    server_go(&s);
    url_of(&s, "https", "localhost", "/x", url, sizeof(url));
    e = break_http_get(&cfg, url, buf, sizeof(buf), &got);
    server_stop(&s);
    remove(cp);
    remove(kp);
    return e;
}

TEST(a_valid_generated_certificate_for_localhost_is_accepted_control) {
    /* the control for the two failure tests below: same generator, right name, valid dates */
    ASSERT_EQ(tls_get_with_cert("localhost", -1, 30, true), BHTTP_OK);
}

TEST(a_trusted_certificate_for_another_name_is_rejected) {
    /* trusted by the client's CA file, valid dates, but the name is not localhost */
    ASSERT_EQ(tls_get_with_cert("other.example", -1, 30, true), BHTTP_ERR_TLS);
}

TEST(an_expired_certificate_is_rejected) {
    ASSERT_EQ(tls_get_with_cert("localhost", -10, -1, true), BHTTP_ERR_TLS);
}

TEST(a_not_yet_valid_certificate_is_rejected) {
    ASSERT_EQ(tls_get_with_cert("localhost", 1, 30, true), BHTTP_ERR_TLS);
}

TEST(a_certificate_signed_by_an_untrusted_issuer_is_rejected) {
    ASSERT_EQ(tls_get_with_cert("localhost", -1, 30, false), BHTTP_ERR_TLS);
}

TEST(a_plain_server_answering_a_tls_client_is_a_tls_error) {
    Server s;
    char url[128];
    u8 buf[16];
    u64 got;
    BreakHttpConfig cfg;
    static const char r[] = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nhello";
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = CERT;
    cfg.io_timeout_ms = 2000;
    ASSERT_TRUE(server_start(&s, false, r, sizeof(r) - 1u));   /* speaks plain HTTP */
    s.reply_on_first_bytes = true;   /* a real plain server answers the ClientHello bytes with HTTP text */
    server_go(&s);
    url_of(&s, "https", "localhost", "/x", url, sizeof(url));
    {
        BreakHttpError e = break_http_get(&cfg, url, buf, sizeof(buf), &got);
        ASSERT_EQ(e, BHTTP_ERR_TLS);
    }
    server_stop(&s);
}

TEST(tls_range_and_framing_rules_apply_over_https_too) {
    Server s;
    char url[128];
    u8 buf[8];
    BreakHttpConfig cfg;
    static const char r[] = "HTTP/1.1 206 P\r\nContent-Range: bytes 3-7/50\r\nContent-Length: 5\r\n\r\nworld";
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = CERT;
    cfg.io_timeout_ms = 3000;
    ASSERT_TRUE(server_start(&s, true, r, sizeof(r) - 1u));
    server_go(&s);
    url_of(&s, "https", "localhost", "/objects/x", url, sizeof(url));
    ASSERT_EQ(break_http_get_range(&cfg, url, 3u, 5u, buf), BHTTP_OK);
    ASSERT_TRUE(memcmp(buf, "world", 5) == 0);
    server_stop(&s);
    {
        static char big[BREAK_HTTP_MAX_HEAD + 200];
        u64 got;
        memcpy(big, "HTTP/1.1 200 OK\r\nX: ", 20);
        memset(big + 20, 'a', sizeof(big) - 21u);
        big[sizeof(big) - 1u] = '\0';
        ASSERT_TRUE(server_start(&s, true, big, sizeof(big) - 1u));
        server_go(&s);
        url_of(&s, "https", "localhost", "/x", url, sizeof(url));
        ASSERT_EQ(break_http_get(&cfg, url, buf, sizeof(buf), &got), BHTTP_ERR_PROTOCOL);
        server_stop(&s);
    }
}

/* ---- adapters ---- */

static const char HASH64[] = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

TEST(update_fetch_asks_for_objects_by_hash_and_range) {
    Server s;
    BreakHttpUpdateCtx ctx;
    u8 out[8];
    static const char r[] = "HTTP/1.1 206 P\r\nContent-Range: bytes 4-7/100\r\nContent-Length: 4\r\n\r\nabcd";
    memset(&ctx, 0, sizeof(ctx));
    ctx.cfg.io_timeout_ms = 3000;
    ASSERT_TRUE(server_start(&s, false, r, sizeof(r) - 1u));
    server_go(&s);
    snprintf(ctx.base_url, sizeof(ctx.base_url), "http://127.0.0.1:%u/stable", (unsigned)s.port);
    ASSERT_TRUE(break_http_update_fetch(&ctx, HASH64, 4u, 4u, out));
    server_stop(&s);
    ASSERT_TRUE(memcmp(out, "abcd", 4) == 0);
    {
        char want[200];
        snprintf(want, sizeof(want), "GET /stable/objects/%s HTTP/1.1\r\n", HASH64);
        ASSERT_TRUE(strncmp(s.request, want, strlen(want)) == 0);
        ASSERT_TRUE(strstr(s.request, "\r\nRange: bytes=4-7\r\n") != NULL);
    }
}

TEST(update_fetch_refuses_bad_object_names_without_connecting) {
    BreakHttpUpdateCtx ctx;
    u8 out[8];
    memset(&ctx, 0, sizeof(ctx));
    snprintf(ctx.base_url, sizeof(ctx.base_url), "http://127.0.0.1:1/stable");
    ASSERT_FALSE(break_http_update_fetch(&ctx, "../etc/passwd", 0u, 4u, out));
    ASSERT_FALSE(break_http_update_fetch(&ctx, "ABCDEF0123456789abcdef0123456789abcdef0123456789abcdef0123456789", 0u, 4u, out)); /* upper case */
    ASSERT_FALSE(break_http_update_fetch(&ctx, "0123", 0u, 4u, out));
    ASSERT_FALSE(break_http_update_fetch(&ctx, NULL, 0u, 4u, out));
    ASSERT_FALSE(break_http_update_fetch(NULL, HASH64, 0u, 4u, out));
    ASSERT_FALSE(break_http_update_fetch(&ctx, HASH64, 0u, 0u, out));
    ASSERT_FALSE(break_http_update_fetch(&ctx, HASH64, 0u, 4u, NULL));
    /* a valid name against a closed port is a plain failure, not a crash */
    ASSERT_FALSE(break_http_update_fetch(&ctx, HASH64, 0u, 4u, out));
    /* a base URL without a terminating NUL inside the struct */
    memset(ctx.base_url, 'a', sizeof(ctx.base_url));
    ASSERT_FALSE(break_http_update_fetch(&ctx, HASH64, 0u, 4u, out));
}

static bool rollout_of(const char *body, u32 *bp) {
    Server s;
    char base[128];
    char reply[512];
    BreakHttpConfig cfg;
    bool ok;
    int n = snprintf(reply, sizeof(reply),
                     "HTTP/1.1 200 OK\r\nContent-Length: %zu\r\n\r\n%s", strlen(body), body);
    memset(&cfg, 0, sizeof(cfg));
    cfg.io_timeout_ms = 3000;
    if (n <= 0 || !server_start(&s, false, reply, (size_t)n)) return false;
    server_go(&s);
    snprintf(base, sizeof(base), "http://127.0.0.1:%u/stable", (unsigned)s.port);
    ok = break_http_rollout_percent_bp(&cfg, base, bp);
    server_stop(&s);
    return ok;
}

static bool rollout_status(const char *reply, u32 *bp) {
    Server s;
    char base[128];
    BreakHttpConfig cfg;
    bool ok;
    memset(&cfg, 0, sizeof(cfg));
    cfg.io_timeout_ms = 3000;
    if (!server_start(&s, false, reply, strlen(reply))) return false;
    server_go(&s);
    snprintf(base, sizeof(base), "http://127.0.0.1:%u/stable", (unsigned)s.port);
    ok = break_http_rollout_percent_bp(&cfg, base, bp);
    server_stop(&s);
    return ok;
}

TEST(rollout_value_is_digits_in_range_and_nothing_else) {
    u32 bp = 12345u;
    ASSERT_TRUE(rollout_of("2500\n", &bp));
    ASSERT_EQ(bp, 2500u);
    ASSERT_TRUE(rollout_of("0", &bp));
    ASSERT_EQ(bp, 0u);
    ASSERT_TRUE(rollout_of("10000", &bp));
    ASSERT_EQ(bp, 10000u);
    bp = 777u;
    ASSERT_FALSE(rollout_of("10001", &bp));
    ASSERT_FALSE(rollout_of("-1", &bp));
    ASSERT_FALSE(rollout_of("1 2", &bp));
    ASSERT_FALSE(rollout_of("05", &bp));          /* leading zero */
    ASSERT_FALSE(rollout_of("", &bp));
    ASSERT_FALSE(rollout_of("\n", &bp));
    ASSERT_FALSE(rollout_of("12\n\n", &bp));      /* only ONE final LF */
    ASSERT_FALSE(rollout_of("12\r\n", &bp));
    ASSERT_FALSE(rollout_of(" 12", &bp));
    ASSERT_FALSE(rollout_of("1e3", &bp));
    ASSERT_FALSE(rollout_of("00000000000000000000", &bp));   /* over 16 bytes */
    ASSERT_FALSE(rollout_status("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n", &bp));
    ASSERT_EQ(bp, 777u);                          /* untouched on every failure */
}

/* ---- certificate revocation lists ---- */

/* A CA, a leaf for localhost signed by it, and CRLs the CA (or another CA)
 * signs. Everything is written to temporary PEM files. */
typedef struct CrlPki {
    EVP_PKEY *ca_key;
    X509 *ca;
    EVP_PKEY *other_key;
    X509 *other_ca;
    char ca_path[300];
    char leaf_path[300];
    char leaf_key_path[300];
    char crl_path[300];
} CrlPki;

static X509 *crl_make_cert(EVP_PKEY *key, EVP_PKEY *issuer_key, X509 *issuer, long serial,
                           const char *cn, bool is_ca) {
    X509 *x = X509_new();
    X509_NAME *name = X509_NAME_new();
    X509V3_CTX v3;
    X509_EXTENSION *ext;
    char san[64];
    if (x == NULL || name == NULL) {
        X509_free(x);
        X509_NAME_free(name);
        return NULL;
    }
    X509_set_version(x, 2);
    ASN1_INTEGER_set(X509_get_serialNumber(x), serial);
    X509_gmtime_adj(X509_getm_notBefore(x), -24L * 3600L);
    X509_gmtime_adj(X509_getm_notAfter(x), 30L * 24L * 3600L);
    X509_set_pubkey(x, key);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (const unsigned char *)cn, -1, -1, 0);
    X509_set_subject_name(x, name);
    X509_set_issuer_name(x, issuer ? X509_get_subject_name(issuer) : name);
    X509_NAME_free(name);
    X509V3_set_ctx_nodb(&v3);
    X509V3_set_ctx(&v3, issuer ? issuer : x, x, NULL, NULL, 0);
    if (is_ca) {
        ext = X509V3_EXT_conf_nid(NULL, &v3, NID_basic_constraints, "critical,CA:TRUE");
        if (ext) { X509_add_ext(x, ext, -1); X509_EXTENSION_free(ext); }
        ext = X509V3_EXT_conf_nid(NULL, &v3, NID_key_usage, "critical,keyCertSign,cRLSign");
        if (ext) { X509_add_ext(x, ext, -1); X509_EXTENSION_free(ext); }
    } else {
        snprintf(san, sizeof(san), "DNS:%s", cn);
        ext = X509V3_EXT_conf_nid(NULL, &v3, NID_subject_alt_name, san);
        if (ext) { X509_add_ext(x, ext, -1); X509_EXTENSION_free(ext); }
    }
    if (X509_sign(x, issuer_key, EVP_sha256()) <= 0) {
        X509_free(x);
        return NULL;
    }
    return x;
}

static bool crl_write_pem_x509(const char *path, X509 *x) {
    FILE *f = fopen(path, "wb");
    bool ok;
    if (f == NULL) return false;
    ok = PEM_write_X509(f, x) == 1;
    return fclose(f) == 0 && ok;
}

/* A CRL from `issuer` revoking `revoked_serial` (0: none), valid from
 * `last_days` to `next_days` relative to now. */
static X509_CRL *crl_make(EVP_PKEY *issuer_key, X509 *issuer, long revoked_serial, long last_days,
                          long next_days) {
    X509_CRL *crl = X509_CRL_new();
    ASN1_TIME *t = ASN1_TIME_new();
    if (crl == NULL || t == NULL) {
        X509_CRL_free(crl);
        ASN1_TIME_free(t);
        return NULL;
    }
    X509_CRL_set_version(crl, 1);
    X509_CRL_set_issuer_name(crl, X509_get_subject_name(issuer));
    X509_gmtime_adj(t, last_days * 24L * 3600L);
    X509_CRL_set1_lastUpdate(crl, t);
    X509_gmtime_adj(t, next_days * 24L * 3600L);
    X509_CRL_set1_nextUpdate(crl, t);
    if (revoked_serial != 0) {
        X509_REVOKED *r = X509_REVOKED_new();
        ASN1_INTEGER *serial = ASN1_INTEGER_new();
        ASN1_INTEGER_set(serial, revoked_serial);
        X509_REVOKED_set_serialNumber(r, serial);
        X509_gmtime_adj(t, -3600L);
        X509_REVOKED_set_revocationDate(r, t);
        X509_CRL_add0_revoked(crl, r);
        ASN1_INTEGER_free(serial);
    }
    ASN1_TIME_free(t);
    X509_CRL_sort(crl);
    if (X509_CRL_sign(crl, issuer_key, EVP_sha256()) <= 0) {
        X509_CRL_free(crl);
        return NULL;
    }
    return crl;
}

static bool crl_write(const char *path, X509_CRL *crl) {
    FILE *f = fopen(path, "wb");
    bool ok;
    if (f == NULL) return false;
    ok = crl != NULL && PEM_write_X509_CRL(f, crl) == 1;
    X509_CRL_free(crl);
    return fclose(f) == 0 && ok;
}

#define CRL_LEAF_SERIAL 42L

static bool crl_pki_init(CrlPki *p) {
    EVP_PKEY *leaf_key = NULL;
    X509 *leaf = NULL;
    FILE *f;
    bool ok = false;
    memset(p, 0, sizeof(*p));
    tmp_file(p->ca_path, sizeof(p->ca_path), "crl_ca");
    tmp_file(p->leaf_path, sizeof(p->leaf_path), "crl_leaf");
    tmp_file(p->leaf_key_path, sizeof(p->leaf_key_path), "crl_leaf_key");
    tmp_file(p->crl_path, sizeof(p->crl_path), "crl_list");
    p->ca_key = EVP_EC_gen("P-256");
    p->other_key = EVP_EC_gen("P-256");
    leaf_key = EVP_EC_gen("P-256");
    if (p->ca_key == NULL || p->other_key == NULL || leaf_key == NULL) goto out;
    p->ca = crl_make_cert(p->ca_key, p->ca_key, NULL, 1, "break test crl ca", true);
    p->other_ca = crl_make_cert(p->other_key, p->other_key, NULL, 2, "break other ca", true);
    if (p->ca == NULL || p->other_ca == NULL) goto out;
    leaf = crl_make_cert(leaf_key, p->ca_key, p->ca, CRL_LEAF_SERIAL, "localhost", false);
    if (leaf == NULL || !crl_write_pem_x509(p->ca_path, p->ca) ||
        !crl_write_pem_x509(p->leaf_path, leaf)) {
        goto out;
    }
    f = fopen(p->leaf_key_path, "wb");
    if (f == NULL) goto out;
    ok = PEM_write_PrivateKey(f, leaf_key, NULL, NULL, 0, NULL, NULL) == 1;
    ok = fclose(f) == 0 && ok;
out:
    X509_free(leaf);
    EVP_PKEY_free(leaf_key);
    return ok;
}

static void crl_pki_free(CrlPki *p) {
    remove(p->ca_path);
    remove(p->leaf_path);
    remove(p->leaf_key_path);
    remove(p->crl_path);
    X509_free(p->ca);
    X509_free(p->other_ca);
    EVP_PKEY_free(p->ca_key);
    EVP_PKEY_free(p->other_key);
}

/* GET https://localhost:port/x (or http when `tls` is false) from a server
 * presenting the CRL test leaf; `crl_file` NULL leaves revocation off. */
static BreakHttpError crl_get(const CrlPki *p, bool tls, const char *crl_file) {
    Server s;
    char url[128];
    u8 buf[16];
    u64 got = 0;
    BreakHttpConfig cfg;
    BreakHttpError e;
    static const char r[] = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nhello";
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = p->ca_path;
    cfg.io_timeout_ms = 3000;
    cfg.crl_file = crl_file;
    if (!server_start_cert(&s, tls, r, sizeof(r) - 1u, p->leaf_path, p->leaf_key_path)) {
        return BHTTP_ERR_CONNECT;
    }
    server_go(&s);
    url_of(&s, tls ? "https" : "http", tls ? "localhost" : "127.0.0.1", "/x", url, sizeof(url));
    e = break_http_get(&cfg, url, buf, sizeof(buf), &got);
    server_stop(&s);
    return e;
}

TEST(a_crl_that_does_not_list_the_leaf_is_accepted_control) {
    CrlPki p;
    ASSERT_TRUE(crl_pki_init(&p));
    ASSERT_TRUE(crl_write(p.crl_path, crl_make(p.ca_key, p.ca, 0, -1, 7)));
    ASSERT_EQ(crl_get(&p, true, p.crl_path), BHTTP_OK);
    /* a CRL revoking another serial does not touch the leaf */
    ASSERT_TRUE(crl_write(p.crl_path, crl_make(p.ca_key, p.ca, CRL_LEAF_SERIAL + 1, -1, 7)));
    ASSERT_EQ(crl_get(&p, true, p.crl_path), BHTTP_OK);
    crl_pki_free(&p);
}

TEST(a_revoked_leaf_is_rejected) {
    CrlPki p;
    ASSERT_TRUE(crl_pki_init(&p));
    ASSERT_TRUE(crl_write(p.crl_path, crl_make(p.ca_key, p.ca, CRL_LEAF_SERIAL, -1, 7)));
    ASSERT_EQ(crl_get(&p, true, p.crl_path), BHTTP_ERR_TLS);
    /* without a CRL file the same leaf still connects: the check is opt-in */
    ASSERT_EQ(crl_get(&p, true, NULL), BHTTP_OK);
    ASSERT_EQ(crl_get(&p, true, ""), BHTTP_OK);
    /* plain loopback http ignores the CRL file */
    ASSERT_EQ(crl_get(&p, false, p.crl_path), BHTTP_OK);
    crl_pki_free(&p);
}

TEST(a_crl_gap_expiry_or_foreign_signer_is_rejected) {
    CrlPki p;
    ASSERT_TRUE(crl_pki_init(&p));
    /* only another CA's CRL: the leaf's issuer has none */
    ASSERT_TRUE(crl_write(p.crl_path, crl_make(p.other_key, p.other_ca, 0, -1, 7)));
    ASSERT_EQ(crl_get(&p, true, p.crl_path), BHTTP_ERR_TLS);
    /* the issuer's CRL, but past its nextUpdate */
    ASSERT_TRUE(crl_write(p.crl_path, crl_make(p.ca_key, p.ca, 0, -10, -1)));
    ASSERT_EQ(crl_get(&p, true, p.crl_path), BHTTP_ERR_TLS);
    /* names the issuer but is signed with another key */
    ASSERT_TRUE(crl_write(p.crl_path, crl_make(p.other_key, p.ca, 0, -1, 7)));
    ASSERT_EQ(crl_get(&p, true, p.crl_path), BHTTP_ERR_TLS);
    crl_pki_free(&p);
}

/* root -> intermediate -> leaf for localhost. The server sends the leaf and
 * the intermediate; the client trusts only the root. */
typedef struct CrlChain {
    EVP_PKEY *root_key;
    EVP_PKEY *mid_key;
    X509 *root;
    X509 *mid;
    char root_path[300];
    char chain_path[300];
    char leaf_key_path[300];
    char crl_path[300];
} CrlChain;

#define CRL_MID_SERIAL 5L

static bool crl_chain_init(CrlChain *c) {
    EVP_PKEY *leaf_key = NULL;
    X509 *leaf = NULL;
    FILE *f;
    bool ok = false;
    memset(c, 0, sizeof(*c));
    tmp_file(c->root_path, sizeof(c->root_path), "crl_root");
    tmp_file(c->chain_path, sizeof(c->chain_path), "crl_chain");
    tmp_file(c->leaf_key_path, sizeof(c->leaf_key_path), "crl_chain_key");
    tmp_file(c->crl_path, sizeof(c->crl_path), "crl_chain_list");
    c->root_key = EVP_EC_gen("P-256");
    c->mid_key = EVP_EC_gen("P-256");
    leaf_key = EVP_EC_gen("P-256");
    if (c->root_key == NULL || c->mid_key == NULL || leaf_key == NULL) goto out;
    c->root = crl_make_cert(c->root_key, c->root_key, NULL, 1, "break test root", true);
    if (c->root == NULL) goto out;
    c->mid = crl_make_cert(c->mid_key, c->root_key, c->root, CRL_MID_SERIAL,
                           "break test intermediate", true);
    if (c->mid == NULL) goto out;
    leaf = crl_make_cert(leaf_key, c->mid_key, c->mid, CRL_LEAF_SERIAL, "localhost", false);
    if (leaf == NULL || !crl_write_pem_x509(c->root_path, c->root)) goto out;
    f = fopen(c->chain_path, "wb");
    if (f == NULL) goto out;
    ok = PEM_write_X509(f, leaf) == 1 && PEM_write_X509(f, c->mid) == 1;
    ok = fclose(f) == 0 && ok;
    if (!ok) goto out;
    f = fopen(c->leaf_key_path, "wb");
    if (f == NULL) {
        ok = false;
        goto out;
    }
    ok = PEM_write_PrivateKey(f, leaf_key, NULL, NULL, 0, NULL, NULL) == 1;
    ok = fclose(f) == 0 && ok;
out:
    X509_free(leaf);
    EVP_PKEY_free(leaf_key);
    return ok;
}

static void crl_chain_free(CrlChain *c) {
    remove(c->root_path);
    remove(c->chain_path);
    remove(c->leaf_key_path);
    remove(c->crl_path);
    X509_free(c->root);
    X509_free(c->mid);
    EVP_PKEY_free(c->root_key);
    EVP_PKEY_free(c->mid_key);
}

/* Writes `a` and then `b` (NULL: only `a`) to one PEM file. */
static bool crl_write_two(const char *path, X509_CRL *a, X509_CRL *b) {
    FILE *f = fopen(path, "wb");
    bool ok;
    if (f == NULL) {
        X509_CRL_free(a);
        X509_CRL_free(b);
        return false;
    }
    ok = a != NULL && PEM_write_X509_CRL(f, a) == 1;
    if (b != NULL) ok = ok && PEM_write_X509_CRL(f, b) == 1;
    X509_CRL_free(a);
    X509_CRL_free(b);
    return fclose(f) == 0 && ok;
}

static BreakHttpError crl_chain_get(const CrlChain *c) {
    Server s;
    char url[128];
    u8 buf[16];
    u64 got = 0;
    BreakHttpConfig cfg;
    BreakHttpError e;
    static const char r[] = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nhello";
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = c->root_path;
    cfg.io_timeout_ms = 3000;
    cfg.crl_file = c->crl_path;
    if (!server_start_cert(&s, true, r, sizeof(r) - 1u, c->chain_path, c->leaf_key_path)) {
        return BHTTP_ERR_CONNECT;
    }
    server_go(&s);
    url_of(&s, "https", "localhost", "/x", url, sizeof(url));
    e = break_http_get(&cfg, url, buf, sizeof(buf), &got);
    server_stop(&s);
    return e;
}

/* The intermediate CA is checked as well as the leaf: a CA revoked by the
 * root is refused even when the leaf is not revoked, and the root's CRL
 * must be in the file. */
TEST(every_certificate_in_the_chain_needs_a_crl_from_its_issuer) {
    CrlChain c;
    ASSERT_TRUE(crl_chain_init(&c));
    ASSERT_TRUE(crl_write_two(c.crl_path, crl_make(c.mid_key, c.mid, 0, -1, 7),
                              crl_make(c.root_key, c.root, 0, -1, 7)));
    ASSERT_EQ(crl_chain_get(&c), BHTTP_OK);
    ASSERT_TRUE(crl_write_two(c.crl_path, crl_make(c.mid_key, c.mid, 0, -1, 7),
                              crl_make(c.root_key, c.root, CRL_MID_SERIAL, -1, 7)));
    ASSERT_EQ(crl_chain_get(&c), BHTTP_ERR_TLS);
    ASSERT_TRUE(crl_write_two(c.crl_path, crl_make(c.mid_key, c.mid, 0, -1, 7), NULL));
    ASSERT_EQ(crl_chain_get(&c), BHTTP_ERR_TLS);
    /* the leaf revoked by the intermediate */
    ASSERT_TRUE(crl_write_two(c.crl_path, crl_make(c.mid_key, c.mid, CRL_LEAF_SERIAL, -1, 7),
                              crl_make(c.root_key, c.root, 0, -1, 7)));
    ASSERT_EQ(crl_chain_get(&c), BHTTP_ERR_TLS);
    crl_chain_free(&c);
}

TEST(an_unreadable_or_empty_crl_file_fails_before_connecting) {
    CrlPki p;
    Server s;
    char url[128];
    u8 buf[16];
    u64 got = 0;
    BreakHttpConfig cfg;
    FILE *f;
    ASSERT_TRUE(crl_pki_init(&p));
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = p.ca_path;
    cfg.io_timeout_ms = 3000;
    ASSERT_TRUE(server_start_cert(&s, true, "", 0u, p.leaf_path, p.leaf_key_path));
    server_go(&s);
    url_of(&s, "https", "localhost", "/x", url, sizeof(url));
    cfg.crl_file = "/nonexistent/break_http_crl.pem";
    ASSERT_EQ(break_http_get(&cfg, url, buf, sizeof(buf), &got), BHTTP_ERR_URL);
    /* a PEM file with a certificate but no CRL */
    cfg.crl_file = p.ca_path;
    ASSERT_EQ(break_http_get(&cfg, url, buf, sizeof(buf), &got), BHTTP_ERR_URL);
    f = fopen(p.crl_path, "wb");
    ASSERT_NOT_NULL(f);
    fclose(f);
    cfg.crl_file = p.crl_path;
    ASSERT_EQ(break_http_get(&cfg, url, buf, sizeof(buf), &got), BHTTP_ERR_URL);
    ASSERT_FALSE(atomic_load(&s.saw_connection));
    server_stop(&s);
    crl_pki_free(&p);
}

/* ---- HTTP CONNECT proxy ---- */

/* Scripted forward proxy: records the CONNECT head, sends `reply` and, when
 * relay_port is set, relays bytes both ways to 127.0.0.1:relay_port. */
typedef struct {
    int listen_fd;
    unsigned short port;
    const char *reply;
    size_t reply_len;
    unsigned short relay_port;
    bool silent;              /* never answer; keep the socket open linger_ms */
    int linger_ms;
    char head[8192];
    size_t head_len;
    atomic_bool saw_connection;
    pthread_t thread;
} Proxy;

static int connect_loopback(unsigned short port) {
    struct sockaddr_in a;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    a.sin_port = htons(port);
    if (connect(fd, (struct sockaddr *)&a, sizeof(a)) != 0) {
        close(fd);
        return -1;
    }
    return fd;
}

static void proxy_relay(int a, int b) {
    for (;;) {
        struct pollfd p[2];
        char buf[4096];
        p[0].fd = a;
        p[0].events = POLLIN;
        p[0].revents = 0;
        p[1].fd = b;
        p[1].events = POLLIN;
        p[1].revents = 0;
        if (poll(p, 2, 5000) <= 0) return;
        for (int i = 0; i < 2; i++) {
            if (p[i].revents != 0) {
                ssize_t n = read(p[i].fd, buf, sizeof(buf));
                if (n <= 0) return;
                if (write(p[1 - i].fd, buf, (size_t)n) != n) return;
            }
        }
    }
}

static void *proxy_main(void *arg) {
    Proxy *p = (Proxy *)arg;
    int fd;
    {
        sigset_t blk;
        sigemptyset(&blk);
        sigaddset(&blk, SIGPIPE);
        pthread_sigmask(SIG_BLOCK, &blk, NULL);
    }
    fd = accept(p->listen_fd, NULL, NULL);
    if (fd < 0) return NULL;
#if defined(SO_NOSIGPIPE)
    {
        int one = 1;
        (void)setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &one, sizeof(one));
    }
#endif
    atomic_store(&p->saw_connection, true);
    while (strstr(p->head, "\r\n\r\n") == NULL && p->head_len + 1u < sizeof(p->head)) {
        ssize_t n = read(fd, p->head + p->head_len, sizeof(p->head) - 1u - p->head_len);
        if (n <= 0) break;
        p->head_len += (size_t)n;
        p->head[p->head_len] = '\0';
    }
    if (p->silent) {
        struct timespec ts = {p->linger_ms / 1000, (long)(p->linger_ms % 1000) * 1000000L};
        nanosleep(&ts, NULL);
    } else {
        if (p->reply_len > 0u) (void)write(fd, p->reply, p->reply_len);
        if (p->relay_port != 0u) {
            int up = connect_loopback(p->relay_port);
            if (up >= 0) {
                proxy_relay(fd, up);
                close(up);
            }
        }
    }
    close(fd);
    return NULL;
}
static bool proxy_start(Proxy *p, const char *reply, size_t reply_len, unsigned short relay_port) {
    struct sockaddr_in a;
    socklen_t al = sizeof(a);
    int one = 1;
    memset(p, 0, sizeof(*p));
    p->reply = reply;
    p->reply_len = reply_len;
    p->relay_port = relay_port;
    p->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (p->listen_fd < 0) return false;
    setsockopt(p->listen_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (bind(p->listen_fd, (struct sockaddr *)&a, sizeof(a)) != 0 || listen(p->listen_fd, 1) != 0 ||
        getsockname(p->listen_fd, (struct sockaddr *)&a, &al) != 0) {
        close(p->listen_fd);
        return false;
    }
    p->port = ntohs(a.sin_port);
    return true;
}

static void proxy_go(Proxy *p) {
    pthread_create(&p->thread, NULL, proxy_main, p);
}

static void proxy_stop(Proxy *p) {
    if (!atomic_load(&p->saw_connection)) {
        int fd = connect_loopback(p->port);
        if (fd >= 0) close(fd);
    }
    pthread_join(p->thread, NULL);
    close(p->listen_fd);
}

static void proxy_url_of(const Proxy *p, char *out, size_t cap) {
    snprintf(out, cap, "http://127.0.0.1:%u", (unsigned)p->port);
}

#define PROXY_OK "HTTP/1.1 200 Connection established\r\n\r\n"

/* https GET of <host>:<target port>/x through a scripted proxy. relay=false
 * leaves the target unreachable through the proxy. */
static BreakHttpError proxied_get(const char *proxy_reply, size_t reply_len, bool relay,
                                  const char *host, const char *ca, Proxy *p, Server *s,
                                  u8 *out, u64 cap, u64 *got) {
    static const char r[] = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\nhello";
    char url[128], purl[64];
    BreakHttpConfig cfg;
    BreakHttpError e;
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = ca;
    cfg.io_timeout_ms = 3000;
    if (!server_start(s, true, r, sizeof(r) - 1u)) return BHTTP_ERR_CONNECT;
    if (!proxy_start(p, proxy_reply, reply_len, relay ? s->port : 0u)) {
        server_go(s);
        server_stop(s);
        return BHTTP_ERR_CONNECT;
    }
    server_go(s);
    proxy_go(p);
    proxy_url_of(p, purl, sizeof(purl));
    cfg.proxy = purl;
    url_of(s, "https", host, "/x", url, sizeof(url));
    e = break_http_get(&cfg, url, out, cap, got);
    proxy_stop(p);
    server_stop(s);
    return e;
}

TEST(https_through_a_connect_proxy_reaches_the_target) {
    Proxy p;
    Server s;
    u8 buf[16];
    u64 got = 0;
    char want[160];
    ASSERT_EQ(proxied_get(PROXY_OK, sizeof(PROXY_OK) - 1u, true, "localhost", CERT, &p, &s, buf,
                          sizeof(buf), &got),
              BHTTP_OK);
    ASSERT_EQ(got, 5u);
    ASSERT_TRUE(memcmp(buf, "hello", 5) == 0);
    snprintf(want, sizeof(want),
             "CONNECT localhost:%u HTTP/1.1\r\nHost: localhost:%u\r\nUser-Agent: break-http/1\r\n\r\n",
             (unsigned)s.port, (unsigned)s.port);
    ASSERT_STR_EQ(p.head, want);
    snprintf(want, sizeof(want), "GET /x HTTP/1.1\r\nHost: localhost:%u\r\n", (unsigned)s.port);
    ASSERT_TRUE(strncmp(s.request, want, strlen(want)) == 0);
}
/* GET url through a proxy that answers `reply` and relays nothing; the proxy
 * URL is the proxy's address plus `suffix`. */
static BreakHttpError proxy_only(const char *reply, size_t reply_len, const char *url,
                                 const char *suffix, Proxy *p) {
    char purl[64];
    u8 buf[16];
    u64 got;
    BreakHttpConfig cfg;
    BreakHttpError e;
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = CERT;
    cfg.io_timeout_ms = 3000;
    if (!proxy_start(p, reply, reply_len, 0u)) return BHTTP_ERR_CONNECT;
    proxy_go(p);
    proxy_url_of(p, purl, sizeof(purl));
    strncat(purl, suffix, sizeof(purl) - strlen(purl) - 1u);
    cfg.proxy = purl;
    e = break_http_get(&cfg, url, buf, sizeof(buf), &got);
    proxy_stop(p);
    return e;
}

TEST(the_connect_line_brackets_ipv6_and_always_names_the_port) {
    static const char r[] = "HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\n\r\n";
    Proxy p;
    ASSERT_EQ(proxy_only(r, sizeof(r) - 1u, "https://[::1]/x", "", &p), BHTTP_ERR_STATUS);
    ASSERT_STR_EQ(p.head, "CONNECT [::1]:443 HTTP/1.1\r\nHost: [::1]:443\r\n"
                          "User-Agent: break-http/1\r\n\r\n");
    ASSERT_EQ(proxy_only(r, sizeof(r) - 1u, "https://localhost/a/b?c", "/", &p), BHTTP_ERR_STATUS);
    ASSERT_STR_EQ(p.head, "CONNECT localhost:443 HTTP/1.1\r\nHost: localhost:443\r\n"
                          "User-Agent: break-http/1\r\n\r\n");
    ASSERT_EQ(proxy_only(r, sizeof(r) - 1u, "https://[2001:db8::1]:8443/x", "", &p),
              BHTTP_ERR_STATUS);
    ASSERT_STR_EQ(p.head, "CONNECT [2001:db8::1]:8443 HTTP/1.1\r\nHost: [2001:db8::1]:8443\r\n"
                          "User-Agent: break-http/1\r\n\r\n");
}

TEST(a_refused_tunnel_is_a_status_error_and_the_target_is_never_reached) {
    static const char *const replies[] = {
        "HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\n\r\n",
        "HTTP/1.1 407 Proxy Authentication Required\r\nProxy-Authenticate: Basic\r\n\r\n",
        "HTTP/1.0 502 Bad Gateway\r\n\r\n",
        "HTTP/1.1 301 Moved\r\nLocation: http://evil/\r\n\r\n"};
    for (size_t i = 0; i < sizeof(replies) / sizeof(replies[0]); i++) {
        Proxy p;
        Server s;
        u8 buf[16];
        u64 got = 99;
        ASSERT_EQ(proxied_get(replies[i], strlen(replies[i]), false, "localhost", CERT, &p, &s, buf,
                              sizeof(buf), &got),
                  BHTTP_ERR_STATUS);
        ASSERT_EQ(got, 0u);
        ASSERT_EQ(s.request_len, 0u);
        ASSERT_TRUE(strncmp(p.head, "CONNECT localhost:", 18) == 0);
    }
}

TEST(a_malformed_or_overlong_proxy_answer_is_a_protocol_error) {
    static char big[BREAK_HTTP_MAX_HEAD + 200];
    static const char *const replies[] = {
        "garbage\r\n\r\n",
        "HTTP/1.1 200 OK\n\n",
        "HTTP/1.1 101 Switching Protocols\r\n\r\n",
        "HTTP/1.1 100 Continue\r\n\r\n",
        "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n",
        PROXY_OK "\x16\x03\x01", /* bytes after the head must not reach TLS */
        "HTTP/1.1 200 Connection established\r\n", /* closes before the blank line */
        ""};                                        /* closes without answering */
    for (size_t i = 0; i < sizeof(replies) / sizeof(replies[0]); i++) {
        Proxy p;
        Server s;
        u8 buf[16];
        u64 got = 99;
        BreakHttpError e = proxied_get(replies[i], strlen(replies[i]), false, "localhost", CERT, &p,
                                       &s, buf, sizeof(buf), &got);
        if (e != BHTTP_ERR_PROTOCOL) printf("    reply %zu: got %s\n", i, break_http_error_name(e));
        ASSERT_EQ(e, BHTTP_ERR_PROTOCOL);
        ASSERT_EQ(s.request_len, 0u);
    }
    {
        Proxy p;
        Server s;
        u8 buf[16];
        u64 got;
        memcpy(big, "HTTP/1.1 200 OK\r\nX: ", 20);
        memset(big + 20, 'a', sizeof(big) - 21u);
        big[sizeof(big) - 1u] = '\0';
        ASSERT_EQ(proxied_get(big, sizeof(big) - 1u, false, "localhost", CERT, &p, &s, buf,
                              sizeof(buf), &got),
                  BHTTP_ERR_PROTOCOL);
    }
}
TEST(a_bad_proxy_url_is_refused_before_any_socket) {
    static const char *const bad[] = {
        "https://127.0.0.1:3128", "http://127.0.0.1:3128/path", "http://127.0.0.1:3128?q",
        "http://127.0.0.1:0", "http://user@127.0.0.1:3128", "ftp://127.0.0.1:3128",
        "127.0.0.1:3128", "http://", "http://127.0.0.1:3128/ ", "http://[::1:3128"};
    BreakHttpConfig cfg;
    u8 buf[8];
    u64 got = 99;
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = CERT;
    cfg.connect_timeout_ms = 200;
    for (size_t i = 0; i < sizeof(bad) / sizeof(bad[0]); i++) {
        cfg.proxy = bad[i];
        if (break_http_get(&cfg, "https://192.0.2.1:9/x", buf, sizeof(buf), &got) != BHTTP_ERR_URL) {
            printf("    accepted proxy: '%s'\n", bad[i]);
        }
        ASSERT_EQ(break_http_get(&cfg, "https://192.0.2.1:9/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
        ASSERT_EQ(got, 0u);
        ASSERT_EQ(break_http_get(&cfg, "http://127.0.0.1:9/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    }
}

TEST(the_target_certificate_is_still_verified_through_the_proxy) {
    Proxy p;
    Server s;
    u8 buf[16];
    u64 got;
    ASSERT_EQ(proxied_get(PROXY_OK, sizeof(PROXY_OK) - 1u, true, "localhost", KEY, &p, &s, buf,
                          sizeof(buf), &got),
              BHTTP_ERR_TLS);
    ASSERT_EQ(proxied_get(PROXY_OK, sizeof(PROXY_OK) - 1u, true, "127.0.0.1", CERT, &p, &s, buf,
                          sizeof(buf), &got),
              BHTTP_ERR_TLS);
    ASSERT_TRUE(strncmp(p.head, "CONNECT 127.0.0.1:", 18) == 0);
}

TEST(a_silent_proxy_times_out_within_the_io_budget) {
    Proxy p;
    char purl[64];
    u8 buf[8];
    u64 got, t0, dt;
    BreakHttpConfig cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = CERT;
    cfg.io_timeout_ms = 400;
    ASSERT_TRUE(proxy_start(&p, "", 0u, 0u));
    p.silent = true;
    p.linger_ms = 1500;
    proxy_go(&p);
    proxy_url_of(&p, purl, sizeof(purl));
    cfg.proxy = purl;
    t0 = mono_ms();
    ASSERT_EQ(break_http_get(&cfg, "https://localhost:9/x", buf, sizeof(buf), &got),
              BHTTP_ERR_TIMEOUT);
    dt = mono_ms() - t0;
    proxy_stop(&p);
    ASSERT_TRUE(dt >= 350u);
    ASSERT_TRUE(dt < 1200u);
}

TEST(an_unreachable_proxy_is_a_connect_error_and_need_not_be_loopback) {
    BreakHttpConfig cfg;
    char purl[64];
    u8 buf[8];
    u64 got, t0, dt;
    BreakHttpError e;
    Proxy p;
    unsigned short dead;
    ASSERT_TRUE(proxy_start(&p, "", 0u, 0u));
    dead = p.port;
    close(p.listen_fd); /* nothing listens there any more */
    memset(&cfg, 0, sizeof(cfg));
    cfg.ca_file = CERT;
    cfg.connect_timeout_ms = 300;
    cfg.io_timeout_ms = 300;
    snprintf(purl, sizeof(purl), "http://127.0.0.1:%u", (unsigned)dead);
    cfg.proxy = purl;
    ASSERT_EQ(break_http_get(&cfg, "https://localhost:9/x", buf, sizeof(buf), &got),
              BHTTP_ERR_CONNECT);
    cfg.proxy = "http://192.0.2.1:3128";
    t0 = mono_ms();
    e = break_http_get(&cfg, "https://localhost:9/x", buf, sizeof(buf), &got);
    dt = mono_ms() - t0;
    ASSERT_TRUE(e == BHTTP_ERR_TIMEOUT || e == BHTTP_ERR_CONNECT);
    ASSERT_TRUE(dt < 1500u);
}

TEST(plain_http_ignores_the_proxy_and_keeps_the_loopback_rule) {
    Proxy p;
    Server s;
    char url[128], purl[64];
    u8 buf[16];
    u64 got = 0;
    BreakHttpConfig cfg;
    static const char r[] = OK200(2) "hi";
    memset(&cfg, 0, sizeof(cfg));
    cfg.io_timeout_ms = 3000;
    ASSERT_TRUE(proxy_start(&p, PROXY_OK, sizeof(PROXY_OK) - 1u, 0u));
    ASSERT_TRUE(server_start(&s, false, r, sizeof(r) - 1u));
    proxy_go(&p);
    server_go(&s);
    proxy_url_of(&p, purl, sizeof(purl));
    cfg.proxy = purl;
    url_of(&s, "http", "127.0.0.1", "/x", url, sizeof(url));
    ASSERT_EQ(break_http_get(&cfg, url, buf, sizeof(buf), &got), BHTTP_OK);
    ASSERT_EQ(got, 2u);
    ASSERT_EQ(break_http_get(&cfg, "http://192.0.2.1/x", buf, sizeof(buf), &got), BHTTP_ERR_URL);
    server_stop(&s);
    proxy_stop(&p);
    ASSERT_EQ(p.head_len, 0u);
}

TEST_MAIN_BEGIN()
    signal(SIGPIPE, SIG_DFL);
    RUN_TEST(get_returns_a_content_length_body);
    RUN_TEST(request_has_the_expected_shape);
    RUN_TEST(non_200_and_redirects_are_status_errors);
    RUN_TEST(body_larger_than_the_buffer_is_too_big_before_it_is_read);
    RUN_TEST(a_response_without_content_length_is_refused_not_read_until_close);
    RUN_TEST(truncated_body_and_missing_framing_are_protocol_errors);
    RUN_TEST(forbidden_or_ambiguous_headers_are_protocol_errors);
    RUN_TEST(head_size_and_header_count_are_bounded);
    RUN_TEST(204_has_no_body_and_a_declared_one_is_refused);
    RUN_TEST(range_request_sends_the_header_and_accepts_the_exact_range);
    RUN_TEST(range_answered_with_anything_but_the_exact_range_is_rejected);
    RUN_TEST(range_arguments_are_validated_before_any_connection);
    RUN_TEST(url_rules_reject_before_any_socket_is_created);
    RUN_TEST(plain_http_to_a_non_loopback_host_is_refused_without_connecting);
    RUN_TEST(loopback_ipv6_and_the_127_block_are_allowed_for_plain_http);
    RUN_TEST(https_without_a_ca_file_is_refused_there_is_no_insecure_mode);
    RUN_TEST(a_silent_server_times_out_within_the_io_budget);
    RUN_TEST(a_slow_drip_server_cannot_hold_the_call_past_the_total_budget);
    RUN_TEST(a_connect_to_an_unroutable_address_is_bounded_by_the_connect_budget);
    RUN_TEST(a_write_to_a_closed_peer_raises_no_sigpipe_over_plain_http);
    RUN_TEST(a_write_to_a_closed_peer_raises_no_sigpipe_over_tls);
    RUN_TEST(a_peer_that_closes_early_does_not_kill_the_process_with_sigpipe);
    RUN_TEST(post_sends_the_body_and_reports_any_complete_status);
    RUN_TEST(post_validates_its_arguments);
    RUN_TEST(https_succeeds_when_the_certificate_matches_the_ca_and_the_host);
    RUN_TEST(https_to_an_ip_literal_fails_because_the_certificate_has_no_ip_san);
    RUN_TEST(https_with_the_wrong_ca_is_a_tls_error);
    RUN_TEST(https_accepts_a_leaf_key_listed_in_the_pins);
    RUN_TEST(https_rejects_a_leaf_key_outside_the_pins);
    RUN_TEST(a_matching_pin_does_not_replace_ca_verification);
    RUN_TEST(pin_arguments_are_validated_before_any_socket);
    RUN_TEST(a_handshake_timeout_with_pins_stays_a_timeout);
    RUN_TEST(pins_are_ignored_for_loopback_http);
    RUN_TEST(a_valid_generated_certificate_for_localhost_is_accepted_control);
    RUN_TEST(a_trusted_certificate_for_another_name_is_rejected);
    RUN_TEST(an_expired_certificate_is_rejected);
    RUN_TEST(a_not_yet_valid_certificate_is_rejected);
    RUN_TEST(a_certificate_signed_by_an_untrusted_issuer_is_rejected);
    RUN_TEST(a_plain_server_answering_a_tls_client_is_a_tls_error);
    RUN_TEST(tls_range_and_framing_rules_apply_over_https_too);
    RUN_TEST(update_fetch_asks_for_objects_by_hash_and_range);
    RUN_TEST(update_fetch_refuses_bad_object_names_without_connecting);
    RUN_TEST(rollout_value_is_digits_in_range_and_nothing_else);
    RUN_TEST(a_crl_that_does_not_list_the_leaf_is_accepted_control);
    RUN_TEST(a_revoked_leaf_is_rejected);
    RUN_TEST(a_crl_gap_expiry_or_foreign_signer_is_rejected);
    RUN_TEST(an_unreadable_or_empty_crl_file_fails_before_connecting);
    RUN_TEST(every_certificate_in_the_chain_needs_a_crl_from_its_issuer);
    RUN_TEST(https_through_a_connect_proxy_reaches_the_target);
    RUN_TEST(the_connect_line_brackets_ipv6_and_always_names_the_port);
    RUN_TEST(a_refused_tunnel_is_a_status_error_and_the_target_is_never_reached);
    RUN_TEST(a_malformed_or_overlong_proxy_answer_is_a_protocol_error);
    RUN_TEST(a_bad_proxy_url_is_refused_before_any_socket);
    RUN_TEST(the_target_certificate_is_still_verified_through_the_proxy);
    RUN_TEST(a_silent_proxy_times_out_within_the_io_budget);
    RUN_TEST(an_unreachable_proxy_is_a_connect_error_and_need_not_be_loopback);
    RUN_TEST(plain_http_ignores_the_proxy_and_keeps_the_loopback_rule);
TEST_MAIN_END()
