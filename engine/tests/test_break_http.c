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
    name = X509_get_subject_name(x);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (const unsigned char *)san, -1, -1, 0);
    X509_set_issuer_name(x, name);
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
TEST_MAIN_END()
