#if defined(__APPLE__)
#define _DARWIN_C_SOURCE 1
#else
#define _POSIX_C_SOURCE 200809L
#endif
#include <net_http/break_http.h>

#include <openssl/err.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define HTTP_MAX_BODY_SEND (16u * 1024u * 1024u)

const char *break_http_error_name(BreakHttpError e) {
    switch (e) {
    case BHTTP_OK: return "ok";
    case BHTTP_ERR_URL: return "url";
    case BHTTP_ERR_CONNECT: return "connect";
    case BHTTP_ERR_TLS: return "tls";
    case BHTTP_ERR_TIMEOUT: return "timeout";
    case BHTTP_ERR_STATUS: return "status";
    case BHTTP_ERR_RANGE: return "range";
    case BHTTP_ERR_TOO_BIG: return "too-big";
    case BHTTP_ERR_PROTOCOL: return "protocol";
    }
    return "?";
}

static u64 now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (u64)ts.tv_sec * 1000u + (u64)ts.tv_nsec / 1000000u;
}

/* ---------------- SIGPIPE ----------------
 * Linux: block SIGPIPE for the call and consume one this call raised.
 * BSD/macOS: SO_NOSIGPIPE on the socket (sigtimedwait does not exist there). */

typedef struct {
    sigset_t old;
    bool was_pending;
} SigGuard;

static void sig_enter(SigGuard *g) {
    sigset_t s, p;
    sigemptyset(&s);
    sigaddset(&s, SIGPIPE);
    (void)pthread_sigmask(SIG_BLOCK, &s, &g->old);
    sigemptyset(&p);
    (void)sigpending(&p);
    g->was_pending = sigismember(&p, SIGPIPE) == 1;
}

static void sig_leave(SigGuard *g) {
#if defined(__linux__)
    if (!g->was_pending) {
        sigset_t p;
        sigemptyset(&p);
        (void)sigpending(&p);
        if (sigismember(&p, SIGPIPE) == 1) {
            sigset_t s;
            struct timespec zero = {0, 0};
            sigemptyset(&s);
            sigaddset(&s, SIGPIPE);
            (void)sigtimedwait(&s, NULL, &zero);
        }
    }
#endif
    (void)pthread_sigmask(SIG_SETMASK, &g->old, NULL);
}

/* ---------------- URL ---------------- */

typedef struct {
    bool https;
    char host[256]; /* without brackets */
    bool host_is_ip;
    bool host_is_v6;
    char port[8];
    bool port_explicit;
    char path[BREAK_HTTP_MAX_URL];
} Url;

static bool host_char_ok(unsigned char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ||
           c == '.' || c == '-';
}

static bool parse_port(const char *p, usize n, char out[8]) {
    unsigned long v = 0;
    if (n == 0u || n > 5u) return false;
    for (usize i = 0; i < n; i++) {
        if (p[i] < '0' || p[i] > '9') return false;
        v = v * 10u + (unsigned long)(p[i] - '0');
    }
    if (v == 0u || v > 65535u) return false;
    memcpy(out, p, n);
    out[n] = '\0';
    return true;
}

static bool parse_url(const char *s, Url *u) {
    const char *p, *auth_end, *after;
    usize len;
    memset(u, 0, sizeof(*u));
    if (s == NULL) return false;
    len = strnlen(s, BREAK_HTTP_MAX_URL + 1u);
    if (len == 0u || len > BREAK_HTTP_MAX_URL - 1u) return false;
    for (usize i = 0; i < len; i++) {
        unsigned char c = (unsigned char)s[i];
        if (c <= 0x20u || c >= 0x7fu || c == '\\' || c == '#') return false;
    }
    if (strncasecmp(s, "https://", 8) == 0) {
        u->https = true;
        p = s + 8;
    } else if (strncasecmp(s, "http://", 7) == 0) {
        p = s + 7;
    } else {
        return false;
    }
    auth_end = p + strcspn(p, "/?");
    if (memchr(p, '@', (usize)(auth_end - p)) != NULL) return false; /* no userinfo */
    if (*p == '[') {
        const char *close = memchr(p, ']', (usize)(auth_end - p));
        unsigned char tmp[16];
        usize hl;
        if (close == NULL) return false;
        hl = (usize)(close - (p + 1));
        if (hl == 0u || hl >= sizeof(u->host)) return false;
        memcpy(u->host, p + 1, hl);
        u->host[hl] = '\0';
        if (inet_pton(AF_INET6, u->host, tmp) != 1) return false;
        u->host_is_ip = true;
        u->host_is_v6 = true;
        after = close + 1;
    } else {
        const char *h = p;
        unsigned char tmp[16];
        usize hl;
        while (h < auth_end && *h != ':') {
            if (!host_char_ok((unsigned char)*h)) return false;
            h++;
        }
        hl = (usize)(h - p);
        if (hl == 0u || hl >= sizeof(u->host)) return false;
        memcpy(u->host, p, hl);
        u->host[hl] = '\0';
        u->host_is_ip = inet_pton(AF_INET, u->host, tmp) == 1;
        after = h;
    }
    if (after < auth_end) {
        if (*after != ':') return false;
        if (!parse_port(after + 1, (usize)(auth_end - (after + 1)), u->port)) return false;
        u->port_explicit = true;
    } else {
        snprintf(u->port, sizeof(u->port), "%s", u->https ? "443" : "80");
    }
    if (*auth_end == '/') {
        snprintf(u->path, sizeof(u->path), "%s", auth_end);
    } else if (*auth_end == '?') {
        snprintf(u->path, sizeof(u->path), "/%s", auth_end);
    } else {
        snprintf(u->path, sizeof(u->path), "/");
    }
    return true;
}

/* ---------------- connection ---------------- */

typedef struct {
    int fd;
    SSL *ssl;
    SSL_CTX *ctx;
    u64 deadline; /* total I/O budget, set after the TCP connect */
    bool tls;
} Conn;

static void conn_close(Conn *c) {
    if (c->ssl != NULL) {
        SSL_free(c->ssl);
        c->ssl = NULL;
    }
    if (c->fd >= 0) {
        close(c->fd);
        c->fd = -1;
    }
    if (c->ctx != NULL) {
        SSL_CTX_free(c->ctx);
        c->ctx = NULL;
    }
}

/* 1 ready, 0 timed out, -1 error */
static int wait_fd(int fd, short ev, u64 deadline) {
    for (;;) {
        u64 n = now_ms();
        struct pollfd p;
        u64 rem;
        int r;
        if (n >= deadline) return 0;
        rem = deadline - n;
        if (rem > (u64)INT_MAX) rem = (u64)INT_MAX;
        p.fd = fd;
        p.events = ev;
        p.revents = 0;
        r = poll(&p, 1, (int)rem);
        if (r < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        if (r == 0) return 0;
        return 1;
    }
}

static bool addr_is_loopback(const struct addrinfo *ai) {
    if (ai->ai_family == AF_INET) {
        const struct sockaddr_in *a = (const struct sockaddr_in *)(const void *)ai->ai_addr;
        return (ntohl(a->sin_addr.s_addr) >> 24) == 127u;
    }
    if (ai->ai_family == AF_INET6) {
        const struct sockaddr_in6 *a = (const struct sockaddr_in6 *)(const void *)ai->ai_addr;
        if (IN6_IS_ADDR_LOOPBACK(&a->sin6_addr)) return true;
        if (IN6_IS_ADDR_V4MAPPED(&a->sin6_addr)) {
            return a->sin6_addr.s6_addr[12] == 127u;
        }
    }
    return false;
}

static void sock_setup(int fd) {
    int one = 1;
    int fl = fcntl(fd, F_GETFL, 0);
    if (fl >= 0) (void)fcntl(fd, F_SETFL, fl | O_NONBLOCK);
    (void)fcntl(fd, F_SETFD, FD_CLOEXEC);
    (void)setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));
#if defined(SO_NOSIGPIPE)
    (void)setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &one, sizeof(one));
#endif
}

static BreakHttpError tcp_connect(const Url *u, bool require_loopback, u32 connect_ms,
                                  int *out_fd) {
    struct addrinfo hints, *res = NULL, *ai;
    u64 deadline = now_ms() + connect_ms;
    bool timed_out = false;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV | (u->host_is_ip ? AI_NUMERICHOST : 0);
    if (getaddrinfo(u->host, u->port, &hints, &res) != 0 || res == NULL) {
        return BHTTP_ERR_CONNECT;
    }
    if (require_loopback) {
        for (ai = res; ai != NULL; ai = ai->ai_next) {
            if (!addr_is_loopback(ai)) {
                freeaddrinfo(res);
                return BHTTP_ERR_URL;
            }
        }
    }
    for (ai = res; ai != NULL; ai = ai->ai_next) {
        int fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        int w;
        if (fd < 0) continue;
        sock_setup(fd);
        if (connect(fd, ai->ai_addr, ai->ai_addrlen) == 0) {
            freeaddrinfo(res);
            *out_fd = fd;
            return BHTTP_OK;
        }
        if (errno == EINPROGRESS) {
            w = wait_fd(fd, POLLOUT, deadline);
            if (w == 1) {
                int err = 0;
                socklen_t el = sizeof(err);
                if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &el) == 0 && err == 0) {
                    freeaddrinfo(res);
                    *out_fd = fd;
                    return BHTTP_OK;
                }
            } else if (w == 0) {
                timed_out = true;
            }
        }
        close(fd);
        if (now_ms() >= deadline) {
            timed_out = true;
            break;
        }
    }
    freeaddrinfo(res);
    return timed_out ? BHTTP_ERR_TIMEOUT : BHTTP_ERR_CONNECT;
}

/* returns >0 bytes, 0 end of stream, -1 error, -2 timeout */
static long conn_read(Conn *c, u8 *buf, usize n) {
    if (n > (usize)INT_MAX) n = (usize)INT_MAX;
    for (;;) {
        if (!c->tls) {
            ssize_t r = recv(c->fd, buf, n, 0);
            int w;
            if (r >= 0) return (long)r;
            if (errno == EINTR) continue;
            if (errno != EAGAIN && errno != EWOULDBLOCK) return -1;
            w = wait_fd(c->fd, POLLIN, c->deadline);
            if (w == 0) return -2;
            if (w < 0) return -1;
        } else {
            int r = SSL_read(c->ssl, buf, (int)n);
            int err, w;
            if (r > 0) return r;
            err = SSL_get_error(c->ssl, r);
            if (err == SSL_ERROR_ZERO_RETURN) return 0;
            if (err == SSL_ERROR_SYSCALL && r == 0) return 0; /* EOF without close_notify */
            if (err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE) return -1;
            w = wait_fd(c->fd, err == SSL_ERROR_WANT_READ ? POLLIN : POLLOUT, c->deadline);
            if (w == 0) return -2;
            if (w < 0) return -1;
        }
    }
}

/* 0 ok, -1 error, -2 timeout */
static int conn_write_all(Conn *c, const u8 *buf, usize n) {
    while (n > 0u) {
        if (!c->tls) {
            int flags = 0;
            ssize_t r;
            int w;
#if defined(MSG_NOSIGNAL)
            flags = MSG_NOSIGNAL;
#endif
            r = send(c->fd, buf, n, flags);
            if (r > 0) {
                buf += r;
                n -= (usize)r;
                continue;
            }
            if (r < 0 && errno == EINTR) continue;
            if (r < 0 && errno != EAGAIN && errno != EWOULDBLOCK) return -1;
            w = wait_fd(c->fd, POLLOUT, c->deadline);
            if (w == 0) return -2;
            if (w < 0) return -1;
        } else {
            int chunk = n > (usize)INT_MAX ? INT_MAX : (int)n;
            int r = SSL_write(c->ssl, buf, chunk);
            int err, w;
            if (r > 0) {
                buf += r;
                n -= (usize)r;
                continue;
            }
            err = SSL_get_error(c->ssl, r);
            if (err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE) return -1;
            w = wait_fd(c->fd, err == SSL_ERROR_WANT_READ ? POLLIN : POLLOUT, c->deadline);
            if (w == 0) return -2;
            if (w < 0) return -1;
        }
    }
    return 0;
}

/* true when a byte is available right now (best effort: late bytes are not seen) */
static bool conn_extra_byte(Conn *c) {
    u8 b;
    if (!c->tls) {
        return recv(c->fd, &b, 1, MSG_DONTWAIT) > 0;
    }
    if (SSL_pending(c->ssl) > 0) return true;
    return SSL_read(c->ssl, &b, 1) > 0;
}

static BreakHttpError io_error(const Conn *c, long code) {
    if (code == -2) return BHTTP_ERR_TIMEOUT;
    return c->tls ? BHTTP_ERR_TLS : BHTTP_ERR_PROTOCOL;
}

static SSL_CTX *tls_ctx_new(const char *ca_file) {
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (ctx == NULL) return NULL;
    if (SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION) != 1) {
        SSL_CTX_free(ctx);
        return NULL;
    }
    {
        long opts = SSL_OP_NO_COMPRESSION | SSL_OP_NO_RENEGOTIATION;
#if defined(SSL_OP_IGNORE_UNEXPECTED_EOF)
        opts |= SSL_OP_IGNORE_UNEXPECTED_EOF; /* truncation is caught by the length check */
#endif
        SSL_CTX_set_options(ctx, opts);
    }
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
    /* only the given file: the system trust store is deliberately not used */
    if (SSL_CTX_load_verify_locations(ctx, ca_file, NULL) != 1) {
        SSL_CTX_free(ctx);
        return NULL;
    }
    return ctx;
}

static BreakHttpError tls_handshake(Conn *c, const Url *u) {
    c->ssl = SSL_new(c->ctx);
    if (c->ssl == NULL || SSL_set_fd(c->ssl, c->fd) != 1) return BHTTP_ERR_TLS;
    if (u->host_is_ip) {
        if (X509_VERIFY_PARAM_set1_ip_asc(SSL_get0_param(c->ssl), u->host) != 1) {
            return BHTTP_ERR_TLS;
        }
    } else {
        (void)SSL_set_tlsext_host_name(c->ssl, u->host);
#if defined(OPENSSL_VERSION_MAJOR) && OPENSSL_VERSION_MAJOR >= 4
        if (SSL_set1_dnsname(c->ssl, u->host) != 1) return BHTTP_ERR_TLS;
#else
        if (SSL_set1_host(c->ssl, u->host) != 1) return BHTTP_ERR_TLS;
#endif
        SSL_set_hostflags(c->ssl, X509_CHECK_FLAG_NO_PARTIAL_WILDCARDS);
    }
    for (;;) {
        int r = SSL_connect(c->ssl);
        int err, w;
        if (r == 1) break;
        err = SSL_get_error(c->ssl, r);
        if (err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE) return BHTTP_ERR_TLS;
        w = wait_fd(c->fd, err == SSL_ERROR_WANT_READ ? POLLIN : POLLOUT, c->deadline);
        if (w == 0) return BHTTP_ERR_TIMEOUT;
        if (w < 0) return BHTTP_ERR_TLS;
    }
    if (SSL_get_verify_result(c->ssl) != X509_V_OK) return BHTTP_ERR_TLS;
    c->tls = true;
    return BHTTP_OK;
}

/* ---------------- response head ---------------- */

typedef struct {
    int status;
    bool have_cl;
    u64 cl;
    bool have_cr;
    u64 cr_first, cr_last;
} Head;

static bool tchar(unsigned char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) return true;
    return c != '\0' && strchr("!#$%&'*+-.^_`|~", (int)c) != NULL;
}

static bool parse_u64_digits(const char *s, usize n, u64 *out) {
    u64 v = 0;
    if (n == 0u || n > 19u) return false;
    if (n > 1u && s[0] == '0') return false; /* canonical decimal only */
    for (usize i = 0; i < n; i++) {
        if (s[i] < '0' || s[i] > '9') return false;
        v = v * 10u + (u64)(s[i] - '0');
    }
    *out = v;
    return true;
}

static bool name_is(const char *n, usize nl, const char *want) {
    return strlen(want) == nl && strncasecmp(n, want, nl) == 0;
}

static bool parse_head(const char *h, usize n, Head *out) {
    usize pos = 0;
    u32 headers = 0;
    memset(out, 0, sizeof(*out));
    /* framing: CRLF only, no NUL */
    for (usize i = 0; i < n; i++) {
        if (h[i] == '\0') return false;
        if (h[i] == '\r' && (i + 1u >= n || h[i + 1u] != '\n')) return false;
        if (h[i] == '\n' && (i == 0u || h[i - 1u] != '\r')) return false;
    }
    if (n < 4u || memcmp(h + n - 4u, "\r\n\r\n", 4u) != 0) return false;
    /* status line */
    if (n < 12u || (memcmp(h, "HTTP/1.1 ", 9) != 0 && memcmp(h, "HTTP/1.0 ", 9) != 0)) return false;
    for (int i = 0; i < 3; i++) {
        if (h[9 + i] < '0' || h[9 + i] > '9') return false;
    }
    out->status = (h[9] - '0') * 100 + (h[10] - '0') * 10 + (h[11] - '0');
    if (out->status < 100 || out->status > 599) return false;
    pos = 12u;
    if (h[pos] == ' ') {
        while (!(h[pos] == '\r' && h[pos + 1u] == '\n')) {
            unsigned char c = (unsigned char)h[pos];
            if ((c < 0x20u && c != '\t') || c == 0x7fu) return false;
            pos++;
        }
    }
    if (!(h[pos] == '\r' && h[pos + 1u] == '\n')) return false;
    pos += 2u;
    while (pos < n) {
        usize line_end = pos, name_end, vs, ve;
        const char *name;
        if (h[pos] == '\r') break; /* blank line: end of head */
        if (++headers > BREAK_HTTP_MAX_HEADERS) return false;
        if (h[pos] == ' ' || h[pos] == '\t') return false; /* no obs-fold */
        while (!(h[line_end] == '\r' && h[line_end + 1u] == '\n')) line_end++;
        name = h + pos;
        name_end = pos;
        while (name_end < line_end && h[name_end] != ':') {
            if (!tchar((unsigned char)h[name_end])) return false;
            name_end++;
        }
        if (name_end == pos || name_end >= line_end) return false;
        vs = name_end + 1u;
        while (vs < line_end && (h[vs] == ' ' || h[vs] == '\t')) vs++;
        ve = line_end;
        while (ve > vs && (h[ve - 1u] == ' ' || h[ve - 1u] == '\t')) ve--;
        for (usize i = vs; i < ve; i++) {
            unsigned char c = (unsigned char)h[i];
            if ((c < 0x20u && c != '\t') || c == 0x7fu) return false;
        }
        {
            usize nl = name_end - pos;
            const char *v = h + vs;
            usize vl = ve - vs;
            if (name_is(name, nl, "content-length")) {
                if (out->have_cl) return false;
                if (!parse_u64_digits(v, vl, &out->cl)) return false;
                out->have_cl = true;
            } else if (name_is(name, nl, "content-range")) {
                usize k = 6;
                usize dash, slash;
                if (out->have_cr) return false;
                if (vl < 9u || strncasecmp(v, "bytes ", 6) != 0) return false;
                dash = k;
                while (dash < vl && v[dash] != '-') dash++;
                slash = dash;
                while (slash < vl && v[slash] != '/') slash++;
                if (dash >= vl || slash >= vl) return false;
                if (!parse_u64_digits(v + k, dash - k, &out->cr_first)) return false;
                if (!parse_u64_digits(v + dash + 1u, slash - dash - 1u, &out->cr_last)) return false;
                if (out->cr_last < out->cr_first) return false;
                if (!(vl - slash - 1u == 1u && v[slash + 1u] == '*')) {
                    u64 total;
                    if (!parse_u64_digits(v + slash + 1u, vl - slash - 1u, &total)) return false;
                    if (out->cr_last >= total) return false;
                }
                out->have_cr = true;
            } else if (name_is(name, nl, "transfer-encoding")) {
                return false;
            } else if (name_is(name, nl, "content-encoding")) {
                if (!(vl == 8u && strncasecmp(v, "identity", 8) == 0)) return false;
            }
        }
        pos = line_end + 2u;
    }
    return true;
}

/* ---------------- one request ---------------- */

typedef struct {
    const char *method;
    const Url *url;
    bool has_range;
    u64 range_first, range_last;
    const char *content_type;
    const void *body;
    usize body_len;
} Req;

typedef enum { EXPECT_200, EXPECT_206, EXPECT_ANY } Expect;

static bool content_type_ok(const char *ct) {
    usize i = 0, slash = 0;
    if (ct == NULL) return false;
    for (; ct[i] != '\0'; i++) {
        if (i >= 100u) return false;
        if (ct[i] == '/') {
            if (slash != 0u || i == 0u) return false;
            slash = i;
        } else if (!tchar((unsigned char)ct[i])) {
            return false;
        }
    }
    return slash != 0u && slash + 1u < i;
}

static BreakHttpError perform(const BreakHttpConfig *cfg, const Req *rq, Expect ex, u8 *out,
                              u64 out_cap, u64 *out_len, int *status_out) {
    Conn c = {-1, NULL, NULL, 0, false};
    char req[BREAK_HTTP_MAX_URL + 512];
    u8 head[BREAK_HTTP_MAX_HEAD];
    usize head_used = 0, head_len = 0;
    Head h;
    BreakHttpError e = BHTTP_OK;
    u32 connect_ms = BREAK_HTTP_DEFAULT_CONNECT_MS, io_ms = BREAK_HTTP_DEFAULT_IO_MS;
    int n;
    const Url *u = rq->url;
    u64 need;
    usize have_body;
    bool bodiless;

    if (cfg != NULL) {
        if (cfg->connect_timeout_ms != 0u) connect_ms = cfg->connect_timeout_ms;
        if (cfg->io_timeout_ms != 0u) io_ms = cfg->io_timeout_ms;
    }
    if (connect_ms > BREAK_HTTP_MAX_IO_MS || io_ms > BREAK_HTTP_MAX_IO_MS) return BHTTP_ERR_URL;
    if (u->https) {
        if (cfg == NULL || cfg->ca_file == NULL || cfg->ca_file[0] == '\0') return BHTTP_ERR_URL;
        c.ctx = tls_ctx_new(cfg->ca_file);
        if (c.ctx == NULL) {
            ERR_clear_error();
            return BHTTP_ERR_TLS;
        }
    }
    e = tcp_connect(u, !u->https, connect_ms, &c.fd);
    if (e != BHTTP_OK) {
        conn_close(&c);
        return e;
    }
    c.deadline = now_ms() + io_ms;
    if (u->https) {
        e = tls_handshake(&c, u);
        if (e != BHTTP_OK) goto done;
    }

    /* request */
    {
        char host_hdr[300];
        char extra[200] = "";
        if (u->host_is_v6) {
            snprintf(host_hdr, sizeof(host_hdr), "[%s]%s%s", u->host,
                     u->port_explicit ? ":" : "", u->port_explicit ? u->port : "");
        } else {
            snprintf(host_hdr, sizeof(host_hdr), "%s%s%s", u->host,
                     u->port_explicit ? ":" : "", u->port_explicit ? u->port : "");
        }
        if (rq->has_range) {
            snprintf(extra, sizeof(extra), "Range: bytes=%llu-%llu\r\n",
                     (unsigned long long)rq->range_first, (unsigned long long)rq->range_last);
        } else if (rq->content_type != NULL) {
            snprintf(extra, sizeof(extra), "Content-Type: %s\r\nContent-Length: %zu\r\n",
                     rq->content_type, rq->body_len);
        }
        n = snprintf(req, sizeof(req),
                     "%s %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: break-http/1\r\n"
                     "Accept: */*\r\nAccept-Encoding: identity\r\nConnection: close\r\n%s\r\n",
                     rq->method, u->path, host_hdr, extra);
        if (n <= 0 || (usize)n >= sizeof(req)) {
            e = BHTTP_ERR_URL;
            goto done;
        }
    }
    {
        int w = conn_write_all(&c, (const u8 *)req, (usize)n);
        if (w == 0 && rq->body_len > 0u) w = conn_write_all(&c, (const u8 *)rq->body, rq->body_len);
        if (w != 0) {
            e = io_error(&c, w);
            goto done;
        }
    }

    /* head: at most BREAK_HTTP_MAX_HEAD bytes in total until the blank line */
    for (;;) {
        long r;
        usize scan_from = head_used >= 3u ? head_used - 3u : 0u;
        if (head_used >= sizeof(head)) {
            e = BHTTP_ERR_PROTOCOL; /* head too large */
            goto done;
        }
        r = conn_read(&c, head + head_used, sizeof(head) - head_used);
        if (r <= 0) {
            e = r == 0 ? BHTTP_ERR_PROTOCOL : io_error(&c, r);
            goto done;
        }
        head_used += (usize)r;
        for (usize i = scan_from; i + 4u <= head_used; i++) {
            if (memcmp(head + i, "\r\n\r\n", 4u) == 0) {
                head_len = i + 4u;
                break;
            }
        }
        if (head_len != 0u) break;
    }
    if (!parse_head((const char *)head, head_len, &h)) {
        e = BHTTP_ERR_PROTOCOL;
        goto done;
    }
    if (h.status < 200) {
        e = BHTTP_ERR_PROTOCOL; /* interim responses are not supported */
        goto done;
    }
    if (status_out != NULL) *status_out = h.status;
    if (ex == EXPECT_200 && h.status != 200) {
        e = BHTTP_ERR_STATUS;
        goto done;
    }
    if (ex == EXPECT_206 && h.status != 206) {
        e = h.status == 200 ? BHTTP_ERR_RANGE : BHTTP_ERR_STATUS;
        goto done;
    }
    if (ex == EXPECT_206) {
        if (!h.have_cr || h.cr_first != rq->range_first || h.cr_last != rq->range_last) {
            e = BHTTP_ERR_RANGE;
            goto done;
        }
    }
    bodiless = h.status == 204 || h.status == 304;
    if (bodiless) {
        if (h.have_cl && h.cl != 0u) {
            e = BHTTP_ERR_PROTOCOL;
            goto done;
        }
        need = 0u;
    } else {
        if (!h.have_cl) {
            e = BHTTP_ERR_PROTOCOL; /* no read-until-close framing */
            goto done;
        }
        need = h.cl;
    }
    if (ex == EXPECT_206) {
        u64 want = rq->range_last - rq->range_first + 1u;
        if (need > want) {
            e = BHTTP_ERR_TOO_BIG;
            goto done;
        }
        if (need < want) {
            e = BHTTP_ERR_RANGE;
            goto done;
        }
    }
    if (need > out_cap) {
        e = BHTTP_ERR_TOO_BIG;
        goto done;
    }
    have_body = head_used - head_len;
    if ((u64)have_body > need) {
        e = BHTTP_ERR_PROTOCOL; /* bytes after the declared body */
        goto done;
    }
    if (have_body > 0u) memcpy(out, head + head_len, have_body);
    {
        u64 got = have_body;
        while (got < need) {
            u64 left = need - got;
            long r = conn_read(&c, out + got, left > (u64)INT_MAX ? (usize)INT_MAX : (usize)left);
            if (r <= 0) {
                e = r == 0 ? BHTTP_ERR_PROTOCOL : io_error(&c, r);
                goto done;
            }
            got += (u64)r;
        }
    }
    if (conn_extra_byte(&c)) {
        e = BHTTP_ERR_PROTOCOL;
        goto done;
    }
    if (out_len != NULL) *out_len = need;

done:
    conn_close(&c);
    ERR_clear_error();
    return e;
}

/* ---------------- public API ---------------- */

BreakHttpError break_http_get(const BreakHttpConfig *cfg, const char *url, u8 *out, u64 cap,
                              u64 *out_len) {
    Url u;
    Req rq;
    SigGuard g;
    BreakHttpError e;
    if (out_len != NULL) *out_len = 0;
    if (!parse_url(url, &u) || (out == NULL && cap > 0u)) return BHTTP_ERR_URL;
    memset(&rq, 0, sizeof(rq));
    rq.method = "GET";
    rq.url = &u;
    sig_enter(&g);
    e = perform(cfg, &rq, EXPECT_200, out, cap, out_len, NULL);
    sig_leave(&g);
    return e;
}

BreakHttpError break_http_get_range(const BreakHttpConfig *cfg, const char *url, u64 offset,
                                    u64 len, u8 *out) {
    Url u;
    Req rq;
    SigGuard g;
    BreakHttpError e;
    u64 got = 0;
    if (!parse_url(url, &u) || out == NULL || len == 0u || offset > UINT64_MAX - len) {
        return BHTTP_ERR_URL;
    }
    memset(&rq, 0, sizeof(rq));
    rq.method = "GET";
    rq.url = &u;
    rq.has_range = true;
    rq.range_first = offset;
    rq.range_last = offset + len - 1u;
    sig_enter(&g);
    e = perform(cfg, &rq, EXPECT_206, out, len, &got, NULL);
    sig_leave(&g);
    if (e == BHTTP_OK && got != len) return BHTTP_ERR_RANGE;
    return e;
}

BreakHttpError break_http_post(const BreakHttpConfig *cfg, const char *url, const void *body,
                               usize body_len, const char *content_type, u8 *resp,
                               usize resp_cap, usize *resp_len, int *status) {
    Url u;
    Req rq;
    SigGuard g;
    BreakHttpError e;
    u64 got = 0;
    int st = 0;
    if (resp_len != NULL) *resp_len = 0;
    if (status != NULL) *status = 0;
    if (!parse_url(url, &u) || !content_type_ok(content_type) ||
        (body == NULL && body_len > 0u) || body_len > HTTP_MAX_BODY_SEND ||
        (resp == NULL && resp_cap > 0u)) {
        return BHTTP_ERR_URL;
    }
    memset(&rq, 0, sizeof(rq));
    rq.method = "POST";
    rq.url = &u;
    rq.content_type = content_type;
    rq.body = body;
    rq.body_len = body_len;
    sig_enter(&g);
    e = perform(cfg, &rq, EXPECT_ANY, resp, resp_cap, &got, &st);
    sig_leave(&g);
    if (status != NULL) *status = st;
    if (e == BHTTP_OK && resp_len != NULL) *resp_len = (usize)got;
    return e;
}

/* ---------------- adapters ---------------- */

static bool hex64_ok(const char *s) {
    if (s == NULL || strlen(s) != 64u) return false;
    for (usize i = 0; i < 64u; i++) {
        if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f'))) return false;
    }
    return true;
}

bool break_http_update_fetch(void *user, const char *object_name, u64 offset, u64 len, u8 *out) {
    const BreakHttpUpdateCtx *ctx = (const BreakHttpUpdateCtx *)user;
    char url[BREAK_HTTP_MAX_URL];
    int n;
    if (ctx == NULL || !hex64_ok(object_name) || len == 0u || out == NULL) return false;
    if (memchr(ctx->base_url, '\0', sizeof(ctx->base_url)) == NULL) return false;
    n = snprintf(url, sizeof(url), "%s/objects/%s", ctx->base_url, object_name);
    if (n <= 0 || (usize)n >= sizeof(url)) return false;
    return break_http_get_range(&ctx->cfg, url, offset, len, out) == BHTTP_OK;
}

bool break_http_rollout_percent_bp(const BreakHttpConfig *cfg, const char *base_url, u32 *out_bp) {
    char url[BREAK_HTTP_MAX_URL];
    u8 body[16];
    u64 got = 0, v = 0;
    int n;
    if (base_url == NULL || out_bp == NULL) return false;
    n = snprintf(url, sizeof(url), "%s/rollout", base_url);
    if (n <= 0 || (usize)n >= sizeof(url)) return false;
    if (break_http_get(cfg, url, body, sizeof(body), &got) != BHTTP_OK) return false;
    if (got > 0u && body[got - 1u] == '\n') got--;
    if (!parse_u64_digits((const char *)body, (usize)got, &v) || v > 10000u) return false;
    *out_bp = (u32)v;
    return true;
}
