#define _POSIX_C_SOURCE 200809L
/* break_crash_server — a small REFERENCE crash collector
 * (docs/design/crash_symbolization.md). It accepts redacted crash records over
 * TLS, symbolizes them against the build's symbol files, clusters them by
 * signature and keeps the per-build statistics. It is not a production
 * deployment: no authentication of reporters, no per-client rate limit, no
 * storage of the records themselves, no retention policy, requests are served
 * one at a time.
 *
 *   break_crash_server --symbols <dir> --stats <file> (--cert <pem> --key <pem> | --insecure-loopback)
 *                      [--port N] [--bind 127.0.0.1] [--print-port] [--log <file>]
 *                      [--max-requests N] [--drop-response K]
 *
 * Route: POST /crash, Content-Type application/x-break-crash, Content-Length
 * at most 64 KiB, body = one canonical "break-crash-v1" record. Answers:
 *   200  counted ("ok ...") or already counted ("duplicate")
 *   400  malformed head, body that is not exactly one canonical record, or a
 *        signal number outside 1..64
 *   404  any other path          405  any other method on /crash
 *   409  the record's build id is not registered (break_crash_report register-build)
 *   411  no Content-Length       413  body over 64 KiB (up to 1 MiB is drained so
 *        the client sees the answer)   415  other content type
 *   500  the statistics file could not be locked, read or written; it is
 *        NEVER replaced by an empty one
 * The whole exchange (TLS handshake, request, response) must finish within 10 s.
 *
 * <dir> is laid out <dir>/<build-id>/<module> (unstripped binaries). A record
 * whose symbols are missing is still counted; its frames then cluster by
 * module and offset.
 *
 * Test options, not code paths a release could reach:
 *   --log <file>        append one line per request: "POST /crash <status> [sig=<16 hex> ...]"
 *   --max-requests N    exit after N connections (0 = run until killed)
 *   --drop-response K   the K-th request (1-based) is processed normally (a valid
 *                       record IS counted) but the answer is never sent and the
 *                       connection just closes: the client cannot tell whether
 *                       its record arrived, retries, and the retry must not be
 *                       counted twice */
#include <crash/break_crash.h>
#include <crash/break_crash_cluster.h>
#include <crash/break_crash_symbolize.h>
#include <crypto/break_crypto.h>

#include <openssl/err.h>
#include <openssl/ssl.h>

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define CS_MAX_HEAD 8192
#define CS_MAX_BODY 65536u
#define CS_DRAIN_MAX (1024u * 1024u)
#define CS_REQ_MS 10000
#define CS_CONTENT_TYPE "application/x-break-crash"

typedef struct {
    const char *symbols, *stats;
    const char *cert, *key;
    const char *bind_host;
    int port;
    bool print_port, insecure;
    const char *log_path;
    long max_requests, drop_response, requests;
    BreakCrashSymbolStore *store;
} Opt;

typedef struct {
    int fd;
    SSL *ssl;
    bool mute;   /* test hook: swallow every answer */
} Peer;

static long g_deadline_ms;

static long now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long)ts.tv_sec * 1000L + (long)(ts.tv_nsec / 1000000L);
}

static int wait_io(int fd, short ev) {
    struct pollfd p;
    p.fd = fd;
    p.events = ev;
    p.revents = 0;
    for (;;) {
        long left = g_deadline_ms - now_ms();
        int r;
        if (left <= 0) return 0;
        r = poll(&p, 1, (int)left);
        if (r < 0 && errno == EINTR) continue;
        return r;
    }
}

static long peer_read(Peer *p, void *buf, size_t n) {
    for (;;) {
        if (p->ssl == NULL) {
            ssize_t r = recv(p->fd, buf, n, 0);
            if (r >= 0) return (long)r;
            if (errno == EINTR) continue;
            if (errno != EAGAIN && errno != EWOULDBLOCK) return -1;
            if (wait_io(p->fd, POLLIN) <= 0) return -1;
        } else {
            int r = SSL_read(p->ssl, buf, (int)n);
            int err;
            if (r > 0) return r;
            err = SSL_get_error(p->ssl, r);
            if (err == SSL_ERROR_ZERO_RETURN) return 0;
            if (err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE) return -1;
            if (wait_io(p->fd, err == SSL_ERROR_WANT_READ ? POLLIN : POLLOUT) <= 0) return -1;
        }
    }
}

static bool peer_write(Peer *p, const void *buf, size_t n) {
    const unsigned char *b = (const unsigned char *)buf;
    while (n > 0) {
        if (p->ssl == NULL) {
            ssize_t r = send(p->fd, b, n, MSG_NOSIGNAL);
            if (r > 0) { b += r; n -= (size_t)r; continue; }
            if (r < 0 && errno == EINTR) continue;
            if (r < 0 && errno != EAGAIN && errno != EWOULDBLOCK) return false;
            if (wait_io(p->fd, POLLOUT) <= 0) return false;
        } else {
            int r = SSL_write(p->ssl, b, n > 16384 ? 16384 : (int)n);
            int err;
            if (r > 0) { b += r; n -= (size_t)r; continue; }
            err = SSL_get_error(p->ssl, r);
            if (err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE) return false;
            if (wait_io(p->fd, err == SSL_ERROR_WANT_READ ? POLLIN : POLLOUT) <= 0) return false;
        }
    }
    return true;
}

static void send_simple(Peer *p, int code, const char *reason, const char *body) {
    char head[256];
    size_t bl = strlen(body);
    int n;
    if (p->mute) return;
    n = snprintf(head, sizeof(head),
                     "HTTP/1.1 %d %s\r\nContent-Length: %zu\r\nContent-Type: text/plain\r\n"
                     "Connection: close\r\n\r\n", code, reason, bl);
    if (n > 0 && peer_write(p, head, (size_t)n)) (void)peer_write(p, body, bl);
}

static void log_line(const Opt *o, int status, const char *extra) {
    FILE *lf;
    if (o->log_path == NULL) return;
    lf = fopen(o->log_path, "a");
    if (lf == NULL) return;
    fprintf(lf, "POST /crash %d%s%s\n", status, extra[0] != '\0' ? " " : "", extra);
    fclose(lf);
}

/* reads and throws away `n` bytes (of the body not yet seen) so the client's write completes */
static void drain(Peer *p, unsigned long long n) {
    unsigned char sink[4096];
    while (n > 0) {
        long r = peer_read(p, sink, n > sizeof(sink) ? sizeof(sink) : (size_t)n);
        if (r <= 0) return;
        n -= (unsigned long long)r;
    }
}

static const char *header_value(char *line, const char *name) {
    size_t nl = strlen(name);
    char *v;
    if (strncasecmp(line, name, nl) != 0 || line[nl] != ':') return NULL;
    v = line + nl + 1;
    while (*v == ' ' || *v == '\t') v++;
    return v;
}

static void hex16(const char *sig, char out[17]) {
    memcpy(out, sig, 16u);
    out[16] = '\0';
}

static bool sha256_hex(const unsigned char *data, size_t n, char out[65]) {
    unsigned char d[32];
    static const char hx[] = "0123456789abcdef";
    if (!break_crypto_sha256(data, n, d)) return false;
    for (size_t i = 0; i < 32u; i++) {
        out[2u * i] = hx[d[i] >> 4];
        out[2u * i + 1u] = hx[d[i] & 0xfu];
    }
    out[64] = '\0';
    return true;
}

/* A parsed, canonical record: symbolize, sign, count. Returns the HTTP status. */
static int accept_record(Opt *o, Peer *p, const unsigned char *body, size_t len) {
    BreakCrashRecord *r = break_crash_record_parse(body, len);
    static unsigned char canon[CS_MAX_BODY];
    BreakCrashFrame fr[BREAK_CRASH_SYMBOLIZE_MAX_FRAMES];
    char sig[65], rec_hash[65], extra[200], reply[128], top[BREAK_CRASH_SYMBOLIZE_NAME_MAX];
    u32 nframes;
    BreakCrashClusterLock *lock;
    BreakCrashClusterStore *stats;
    BreakCrashClusterOutcome out;
    bool counted, saved = true;
    int status;
    extra[0] = '\0';
    if (r == NULL) {
        send_simple(p, 400, "Bad Request", "not a crash record\n");
        return 400;
    }
    /* duplicate suppression hashes the bytes, so only the canonical encoding may be counted */
    if (break_crash_record_serialize(r, canon, sizeof(canon)) != len || memcmp(canon, body, len) != 0 ||
        !sha256_hex(body, len, rec_hash)) {
        break_crash_record_destroy(r);
        send_simple(p, 400, "Bad Request", "record is not canonical\n");
        return 400;
    }
    nframes = break_crash_symbolize_record(o->store, r, fr, BREAK_CRASH_SYMBOLIZE_MAX_FRAMES);
    top[0] = '\0';
    for (u32 i = 0; i < nframes; i++) {
        if (fr[i].resolved) {
            snprintf(top, sizeof(top), "%s", fr[i].symbol);
            break;
        }
    }
    if (!break_crash_signature(break_crash_record_signo(r), fr, nframes, sig)) {
        break_crash_record_destroy(r);
        send_simple(p, 400, "Bad Request", "signal number out of range\n");
        return 400;
    }
    {
        char s16[17];
        hex16(sig, s16);
        snprintf(extra, sizeof(extra), "sig=%s frames=%u top=%s build=%s", s16, nframes,
                 top[0] != '\0' ? top : "-", break_crash_record_build_id(r));
    }
    lock = break_crash_cluster_lock(o->stats);
    stats = lock != NULL ? break_crash_cluster_open(o->stats) : NULL;
    if (stats == NULL) {
        break_crash_cluster_unlock(lock);
        break_crash_record_destroy(r);
        send_simple(p, 500, "Internal Server Error", "statistics unavailable\n");
        return 500;
    }
    memset(&out, 0, sizeof(out));
    counted = break_crash_cluster_add(stats, rec_hash, sig, break_crash_record_build_id(r), top, &out);
    if (counted && !out.duplicate) saved = break_crash_cluster_save(stats, o->stats);
    break_crash_cluster_destroy(stats);
    break_crash_cluster_unlock(lock);
    break_crash_record_destroy(r);
    if (!counted && out.unknown_build) {
        send_simple(p, 409, "Conflict", "unknown build\n");
        status = 409;
    } else if (!counted) {
        send_simple(p, 400, "Bad Request", "rejected\n");
        status = 400;
    } else if (!saved) {
        send_simple(p, 500, "Internal Server Error", "statistics not saved\n");
        status = 500;
    } else if (out.duplicate) {
        send_simple(p, 200, "OK", "duplicate\n");
        status = 200;
    } else {
        snprintf(reply, sizeof(reply), "ok count=%llu regression=%d\n", (unsigned long long)out.count,
                 out.regression_started ? 1 : 0);
        send_simple(p, 200, "OK", reply);
        status = 200;
    }
    log_line(o, status, extra);
    return -status;   /* negative: the log line is already written */
}

static void serve(Opt *o, Peer *p) {
    static char req[CS_MAX_HEAD + 1];
    static unsigned char body[CS_MAX_BODY + 1];
    size_t used = 0, head_len = 0, have;
    char *line_end, *path, *sp, *l;
    const char *ctype = NULL;
    unsigned long long clen = 0;
    bool has_clen = false, dup_clen = false, dup_ctype = false, chunked = false, body_read = false;
    int status;
    o->requests++;
    p->mute = o->drop_response > 0 && o->requests == o->drop_response;
    for (;;) {
        long r;
        char *end;
        if (used >= CS_MAX_HEAD) {
            send_simple(p, 431, "Request Header Fields Too Large", "too large\n");
            return;
        }
        r = peer_read(p, req + used, CS_MAX_HEAD - used);
        if (r <= 0) return;
        used += (size_t)r;
        req[used] = '\0';
        end = strstr(req, "\r\n\r\n");
        if (end != NULL) {
            head_len = (size_t)(end - req) + 4u;
            break;
        }
    }
    line_end = strstr(req, "\r\n");
    sp = memchr(req, ' ', (size_t)(line_end - req));
    if (sp == NULL) {
        send_simple(p, 400, "Bad Request", "bad request\n");
        return;
    }
    *sp = '\0';
    path = sp + 1;
    sp = memchr(path, ' ', (size_t)(line_end - path));
    if (sp == NULL || strncmp(sp + 1, "HTTP/1.1", (size_t)(line_end - sp - 1)) != 0) {
        send_simple(p, 400, "Bad Request", "bad request\n");
        return;
    }
    *sp = '\0';
    for (l = line_end + 2; l[0] != '\r' && l[0] != '\0';) {
        char *e = strstr(l, "\r\n");
        const char *v;
        if (e == NULL) break;
        *e = '\0';
        if ((v = header_value(l, "Content-Length")) != NULL) {
            char *endp;
            if (has_clen) dup_clen = true;
            has_clen = true;
            if (*v < '0' || *v > '9' || strlen(v) > 10u) {
                dup_clen = true;
            } else {
                clen = strtoull(v, &endp, 10);
                if (*endp != '\0') dup_clen = true;
            }
        } else if ((v = header_value(l, "Content-Type")) != NULL) {
            if (ctype != NULL) dup_ctype = true;
            ctype = v;
        } else if (header_value(l, "Transfer-Encoding") != NULL) {
            chunked = true;
        }
        l = e + 2;
    }
    have = used - head_len;
    /* An answer sent while request bytes are still unread can be lost to a connection reset, so
     * the declared body is taken in BEFORE any refusal: into the record buffer when it fits,
     * thrown away (up to the drain limit) when it does not. */
    if (has_clen && !dup_clen && !chunked) {
        if (clen <= CS_MAX_BODY) {
            size_t take = have > clen ? (size_t)clen : have;
            memcpy(body, req + head_len, take);
            while (take < clen) {
                long r = peer_read(p, body + take, (size_t)clen - take);
                if (r <= 0) return;
                take += (size_t)r;
            }
            body_read = true;
        } else if (clen <= CS_DRAIN_MAX && clen > have) {
            drain(p, clen - have);
        }
    }
    if (strcmp(path, "/crash") != 0) {
        send_simple(p, 404, "Not Found", "not found\n");
        log_line(o, 404, "");
        return;
    }
    if (strcmp(req, "POST") != 0) {
        send_simple(p, 405, "Method Not Allowed", "POST only\n");
        log_line(o, 405, "");
        return;
    }
    if (chunked || dup_clen || dup_ctype) {
        send_simple(p, 400, "Bad Request", "bad framing\n");
        log_line(o, 400, "");
        return;
    }
    if (!has_clen) {
        send_simple(p, 411, "Length Required", "length required\n");
        log_line(o, 411, "");
        return;
    }
    if (clen > CS_MAX_BODY) {
        send_simple(p, 413, "Payload Too Large", "record too large\n");
        log_line(o, 413, "");
        return;
    }
    if (ctype == NULL || strcmp(ctype, CS_CONTENT_TYPE) != 0) {
        send_simple(p, 415, "Unsupported Media Type", "content type\n");
        log_line(o, 415, "");
        return;
    }
    if (clen == 0u) {
        send_simple(p, 400, "Bad Request", "empty body\n");
        log_line(o, 400, "");
        return;
    }
    if (!body_read) return;
    status = accept_record(o, p, body, (size_t)clen);
    if (status > 0) log_line(o, status, "");
}

int main(int argc, char **argv) {
    Opt o;
    SSL_CTX *ctx = NULL;
    int ls, one = 1;
    struct sockaddr_in a;
    socklen_t al = sizeof(a);
    long served = 0;
    memset(&o, 0, sizeof(o));
    o.bind_host = "127.0.0.1";
    for (int i = 1; i < argc; i++) {
        const char *k = argv[i];
        const char *v = (i + 1 < argc) ? argv[i + 1] : NULL;
        if (!strcmp(k, "--symbols") && v) { o.symbols = v; i++; }
        else if (!strcmp(k, "--stats") && v) { o.stats = v; i++; }
        else if (!strcmp(k, "--cert") && v) { o.cert = v; i++; }
        else if (!strcmp(k, "--key") && v) { o.key = v; i++; }
        else if (!strcmp(k, "--bind") && v) { o.bind_host = v; i++; }
        else if (!strcmp(k, "--port") && v) { o.port = atoi(v); i++; }
        else if (!strcmp(k, "--log") && v) { o.log_path = v; i++; }
        else if (!strcmp(k, "--max-requests") && v) { o.max_requests = atol(v); i++; }
        else if (!strcmp(k, "--drop-response") && v) { o.drop_response = atol(v); i++; }
        else if (!strcmp(k, "--print-port")) o.print_port = true;
        else if (!strcmp(k, "--insecure-loopback")) o.insecure = true;
        else {
            fprintf(stderr, "break_crash_server: unknown or incomplete option '%s'\n", k);
            return 2;
        }
    }
    if (o.symbols == NULL || o.stats == NULL || o.port < 0 || o.port > 65535) {
        fprintf(stderr, "usage: break_crash_server --symbols <dir> --stats <file> "
                        "(--cert <pem> --key <pem> | --insecure-loopback) [--port N] [--bind ADDR] "
                        "[--print-port] [--log FILE] [--max-requests N] [--drop-response K]\n");
        return 2;
    }
    o.store = break_crash_symbol_store_open(o.symbols);
    if (o.store == NULL) {
        fprintf(stderr, "break_crash_server: --symbols is not a directory\n");
        return 2;
    }
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    if (inet_pton(AF_INET, o.bind_host, &a.sin_addr) != 1) {
        fprintf(stderr, "break_crash_server: --bind must be an IPv4 address\n");
        return 2;
    }
    a.sin_port = htons((unsigned short)o.port);
    if (o.insecure) {
        if ((ntohl(a.sin_addr.s_addr) >> 24) != 127u) {
            fprintf(stderr, "break_crash_server: --insecure-loopback needs a loopback --bind address\n");
            return 2;
        }
    } else {
        if (o.cert == NULL || o.key == NULL) {
            fprintf(stderr, "break_crash_server: TLS is required: give --cert and --key\n");
            return 2;
        }
        ctx = SSL_CTX_new(TLS_server_method());
        if (ctx == NULL || SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION) != 1 ||
            SSL_CTX_use_certificate_chain_file(ctx, o.cert) != 1 ||
            SSL_CTX_use_PrivateKey_file(ctx, o.key, SSL_FILETYPE_PEM) != 1 ||
            SSL_CTX_check_private_key(ctx) != 1) {
            fprintf(stderr, "break_crash_server: cannot load the certificate and key\n");
            return 1;
        }
    }
    signal(SIGPIPE, SIG_IGN);
    ls = socket(AF_INET, SOCK_STREAM, 0);
    if (ls < 0) return 1;
    setsockopt(ls, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if (bind(ls, (struct sockaddr *)&a, sizeof(a)) != 0 || listen(ls, 8) != 0 ||
        getsockname(ls, (struct sockaddr *)&a, &al) != 0) {
        fprintf(stderr, "break_crash_server: cannot listen on %s:%d\n", o.bind_host, o.port);
        return 1;
    }
    if (o.print_port) {
        printf("%u\n", (unsigned)ntohs(a.sin_port));
        fflush(stdout);
    }
    for (;;) {
        Peer p;
        int fd = accept(ls, NULL, NULL);
        if (fd < 0) {
            if (errno == EINTR) continue;
            break;
        }
        (void)fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
        g_deadline_ms = now_ms() + CS_REQ_MS;
        p.fd = fd;
        p.ssl = NULL;
        p.mute = false;
        if (ctx != NULL) {
            int ok = 0;
            p.ssl = SSL_new(ctx);
            if (p.ssl != NULL && SSL_set_fd(p.ssl, fd) == 1) {
                for (;;) {
                    int r = SSL_accept(p.ssl);
                    int err;
                    if (r == 1) { ok = 1; break; }
                    err = SSL_get_error(p.ssl, r);
                    if (err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE) break;
                    if (wait_io(fd, err == SSL_ERROR_WANT_READ ? POLLIN : POLLOUT) <= 0) break;
                }
            }
            if (!ok) {
                if (p.ssl) SSL_free(p.ssl);
                close(fd);
                ERR_clear_error();
                continue;
            }
        }
        serve(&o, &p);
        if (p.ssl) {
            SSL_shutdown(p.ssl);
            SSL_free(p.ssl);
        }
        close(fd);
        served++;
        if (o.max_requests > 0 && served >= o.max_requests) break;
    }
    close(ls);
    if (ctx) SSL_CTX_free(ctx);
    break_crash_symbol_store_destroy(o.store);
    return 0;
}
