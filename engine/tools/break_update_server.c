#define _POSIX_C_SOURCE 200809L
#if defined(__APPLE__)
#define _DARWIN_C_SOURCE 1 /* O_NOFOLLOW */
#endif
/* break_update_server — a small REFERENCE server for the update client
 * (docs/design/update_transport.md). It exists so the whole path (signed
 * manifest -> TLS range downloads -> resume -> stage/activate) can be run end
 * to end; it is not a production deployment (no access control, logging
 * pipeline, CDN, rate limiting per client, or hot reload of the release).
 *
 *   break_update_server --root <dir> --cert <pem> --key <pem> [--port N]
 *                       [--bind 127.0.0.1] [--print-port] [--rollout <bp>]
 *                       [--truncate-request K] [--log <file>] [--max-requests N]
 *                       [--insecure-loopback]
 *
 * <dir> holds what `break_manifest_tool` produced:
 *   <dir>/manifest        the signed manifest
 *   <dir>/objects/<hex>   one file per chunk, named by its SHA-256 (64 lowercase hex)
 * Routes (exact match only, GET only):
 *   /manifest            the signed manifest
 *   /rollout             "<bp>\n" (only with --rollout)
 *   /objects/<64 hex>    a chunk; honours a single "Range: bytes=a-b"
 * Anything else is a 404; no request value is ever used as a path, so there is
 * no traversal surface: the file name is rebuilt from a validated 64-char hex
 * string. TLS is required; plain http is allowed only with --insecure-loopback
 * AND a loopback bind address.
 *
 * Test options, not code paths a release could reach:
 *   --truncate-request K  the K-th /objects request (1-based) sends half of its
 *                         body and closes, so a client's resume can be exercised
 *                         (the client downloads in 64 KiB blocks: use a chunk of
 *                         more than one block and K = 2)
 *   --log <file>          append one line per request: METHOD PATH [RANGE]
 *   --max-requests N      exit after N requests (0 = run until killed)
 * Requests are served one at a time; the process is single-threaded. */
#include <openssl/err.h>
#include <openssl/ssl.h>

#include <stdbool.h>

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
#include <sys/stat.h>
#include <unistd.h>

#define US_MAX_REQ 8192
#define US_MAX_FILE (128u * 1024u * 1024u)
#define US_IO_MS 5000

typedef struct {
    const char *root;
    const char *cert, *key;
    const char *bind_host;
    int port;
    bool print_port;
    bool insecure;
    long rollout_bp; /* -1 = no /rollout route */
    long truncate_request; /* 0 = never */
    long object_requests;
    const char *log_path;
    long max_requests;
} Opt;

typedef struct {
    int fd;
    SSL *ssl;
} Peer;

static int wait_io(int fd, short ev) {
    struct pollfd p;
    p.fd = fd;
    p.events = ev;
    p.revents = 0;
    for (;;) {
        int r = poll(&p, 1, US_IO_MS);
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
    int n = snprintf(head, sizeof(head),
                     "HTTP/1.1 %d %s\r\nContent-Length: %zu\r\nContent-Type: text/plain\r\n"
                     "Connection: close\r\n\r\n", code, reason, bl);
    if (n > 0 && peer_write(p, head, (size_t)n)) (void)peer_write(p, body, bl);
}

static bool hex64(const char *s) {
    if (strlen(s) != 64u) return false;
    for (int i = 0; i < 64; i++) {
        if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f'))) return false;
    }
    return true;
}

/* Reads a whole regular file (<= US_MAX_FILE) into memory. */
static unsigned char *read_file(const char *path, size_t *out_len) {
    struct stat st;
    unsigned char *buf;
    int fd = open(path, O_RDONLY | O_NOFOLLOW);
    size_t got = 0;
    if (fd < 0) return NULL;
    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode) || st.st_size < 0 ||
        (unsigned long long)st.st_size > US_MAX_FILE) {
        close(fd);
        return NULL;
    }
    buf = (unsigned char *)malloc((size_t)st.st_size + 1u);
    if (buf == NULL) { close(fd); return NULL; }
    while (got < (size_t)st.st_size) {
        ssize_t r = read(fd, buf + got, (size_t)st.st_size - got);
        if (r <= 0) { free(buf); close(fd); return NULL; }
        got += (size_t)r;
    }
    close(fd);
    *out_len = got;
    return buf;
}

/* "bytes=a-b" with both ends present, a <= b, canonical digits. */
static bool parse_range(const char *v, unsigned long long *a, unsigned long long *b) {
    char *end;
    if (strncmp(v, "bytes=", 6) != 0) return false;
    v += 6;
    if (*v < '0' || *v > '9') return false;
    errno = 0;
    *a = strtoull(v, &end, 10);
    if (errno != 0 || *end != '-') return false;
    v = end + 1;
    if (*v < '0' || *v > '9') return false;
    *b = strtoull(v, &end, 10);
    if (errno != 0 || (*end != '\0')) return false;
    return *a <= *b;
}

static void serve(Opt *o, Peer *p) {
    char req[US_MAX_REQ + 1];
    size_t used = 0;
    char *line_end, *path, *sp;
    char *range_hdr = NULL;
    /* read the head (until the blank line) */
    for (;;) {
        long r;
        if (used >= US_MAX_REQ) { send_simple(p, 431, "Request Header Fields Too Large", "too large\n"); return; }
        r = peer_read(p, req + used, US_MAX_REQ - used);
        if (r <= 0) return;
        used += (size_t)r;
        req[used] = '\0';
        if (strstr(req, "\r\n\r\n") != NULL) break;
    }
    if (strncmp(req, "GET ", 4) != 0) { send_simple(p, 405, "Method Not Allowed", "GET only\n"); return; }
    line_end = strstr(req, "\r\n");
    path = req + 4;
    sp = memchr(path, ' ', (size_t)(line_end - path));
    if (sp == NULL) { send_simple(p, 400, "Bad Request", "bad request\n"); return; }
    *sp = '\0';
    /* Range header, if any (case-insensitive name) */
    for (char *l = line_end + 2; l[0] != '\r' && l[0] != '\0';) {
        char *e = strstr(l, "\r\n");
        if (e == NULL) break;
        if (strncasecmp(l, "Range:", 6) == 0) {
            char *v = l + 6;
            while (*v == ' ') v++;
            *e = '\0';
            range_hdr = v;
        }
        l = e + 2;
    }
    if (o->log_path != NULL) {
        FILE *lf = fopen(o->log_path, "a");
        if (lf != NULL) {
            fprintf(lf, "GET %.200s%s%.80s\n", path, range_hdr ? " " : "", range_hdr ? range_hdr : "");
            fclose(lf);
        }
    }
    if (strcmp(path, "/manifest") == 0) {
        char file[1100];
        size_t len = 0;
        unsigned char *data;
        char head[256];
        int n;
        snprintf(file, sizeof(file), "%s/manifest", o->root);
        data = read_file(file, &len);
        if (data == NULL) { send_simple(p, 404, "Not Found", "no manifest\n"); return; }
        n = snprintf(head, sizeof(head),
                     "HTTP/1.1 200 OK\r\nContent-Length: %zu\r\nContent-Type: text/plain\r\n"
                     "Connection: close\r\n\r\n", len);
        if (n > 0 && peer_write(p, head, (size_t)n)) (void)peer_write(p, data, len);
        free(data);
        return;
    }
    if (strcmp(path, "/rollout") == 0 && o->rollout_bp >= 0) {
        char body[32];
        snprintf(body, sizeof(body), "%ld\n", o->rollout_bp);
        send_simple(p, 200, "OK", body);
        return;
    }
    if (strncmp(path, "/objects/", 9) == 0 && hex64(path + 9)) {
        char file[1200];
        size_t len = 0;
        unsigned char *data;
        char head[320];
        int n;
        unsigned long long a = 0, b = 0;
        size_t send_len;
        const unsigned char *send_from;
        snprintf(file, sizeof(file), "%s/objects/%s", o->root, path + 9);
        data = read_file(file, &len);
        if (data == NULL) { send_simple(p, 404, "Not Found", "no such object\n"); return; }
        if (range_hdr != NULL) {
            if (!parse_range(range_hdr, &a, &b) || a >= len) {
                n = snprintf(head, sizeof(head),
                             "HTTP/1.1 416 Range Not Satisfiable\r\nContent-Range: bytes */%zu\r\n"
                             "Content-Length: 0\r\nConnection: close\r\n\r\n", len);
                if (n > 0) (void)peer_write(p, head, (size_t)n);
                free(data);
                return;
            }
            if (b >= len) b = len - 1u;
            send_from = data + a;
            send_len = (size_t)(b - a + 1u);
            n = snprintf(head, sizeof(head),
                         "HTTP/1.1 206 Partial Content\r\nContent-Range: bytes %llu-%llu/%zu\r\n"
                         "Content-Length: %zu\r\nContent-Type: application/octet-stream\r\n"
                         "Connection: close\r\n\r\n", a, b, len, send_len);
        } else {
            send_from = data;
            send_len = len;
            n = snprintf(head, sizeof(head),
                         "HTTP/1.1 200 OK\r\nContent-Length: %zu\r\n"
                         "Content-Type: application/octet-stream\r\nConnection: close\r\n\r\n", len);
        }
        if (n > 0 && peer_write(p, head, (size_t)n)) {
            o->object_requests++;
            if (o->truncate_request > 0 && o->object_requests == o->truncate_request) {
                (void)peer_write(p, send_from, send_len / 2u); /* then the socket closes */
            } else {
                (void)peer_write(p, send_from, send_len);
            }
        }
        free(data);
        return;
    }
    send_simple(p, 404, "Not Found", "not found\n");
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
    o.rollout_bp = -1;
    for (int i = 1; i < argc; i++) {
        const char *k = argv[i];
        const char *v = (i + 1 < argc) ? argv[i + 1] : NULL;
        if (!strcmp(k, "--root") && v) { o.root = v; i++; }
        else if (!strcmp(k, "--cert") && v) { o.cert = v; i++; }
        else if (!strcmp(k, "--key") && v) { o.key = v; i++; }
        else if (!strcmp(k, "--bind") && v) { o.bind_host = v; i++; }
        else if (!strcmp(k, "--port") && v) { o.port = atoi(v); i++; }
        else if (!strcmp(k, "--rollout") && v) { o.rollout_bp = atol(v); i++; }
        else if (!strcmp(k, "--truncate-request") && v) { o.truncate_request = atol(v); i++; }
        else if (!strcmp(k, "--log") && v) { o.log_path = v; i++; }
        else if (!strcmp(k, "--max-requests") && v) { o.max_requests = atol(v); i++; }
        else if (!strcmp(k, "--print-port")) o.print_port = true;
        else if (!strcmp(k, "--insecure-loopback")) o.insecure = true;
        else {
            fprintf(stderr, "break_update_server: unknown or incomplete option '%s'\n", k);
            return 2;
        }
    }
    if (o.root == NULL || o.port < 0 || o.port > 65535 || o.rollout_bp > 10000) {
        fprintf(stderr, "usage: break_update_server --root <dir> (--cert <pem> --key <pem> | --insecure-loopback) "
                        "[--port N] [--bind ADDR] [--print-port] [--rollout BP] [--truncate-request K] [--log FILE] [--max-requests N]\n");
        return 2;
    }
    memset(&a, 0, sizeof(a));
    a.sin_family = AF_INET;
    if (inet_pton(AF_INET, o.bind_host, &a.sin_addr) != 1) {
        fprintf(stderr, "break_update_server: --bind must be an IPv4 address\n");
        return 2;
    }
    a.sin_port = htons((unsigned short)o.port);
    if (o.insecure) {
        if ((ntohl(a.sin_addr.s_addr) >> 24) != 127u) {
            fprintf(stderr, "break_update_server: --insecure-loopback needs a loopback --bind address\n");
            return 2;
        }
    } else {
        if (o.cert == NULL || o.key == NULL) {
            fprintf(stderr, "break_update_server: TLS is required: give --cert and --key\n");
            return 2;
        }
        ctx = SSL_CTX_new(TLS_server_method());
        if (ctx == NULL || SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION) != 1 ||
            SSL_CTX_use_certificate_chain_file(ctx, o.cert) != 1 ||
            SSL_CTX_use_PrivateKey_file(ctx, o.key, SSL_FILETYPE_PEM) != 1 ||
            SSL_CTX_check_private_key(ctx) != 1) {
            fprintf(stderr, "break_update_server: cannot load the certificate and key\n");
            return 1;
        }
    }
    signal(SIGPIPE, SIG_IGN);
    ls = socket(AF_INET, SOCK_STREAM, 0);
    if (ls < 0) return 1;
    setsockopt(ls, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if (bind(ls, (struct sockaddr *)&a, sizeof(a)) != 0 || listen(ls, 8) != 0 ||
        getsockname(ls, (struct sockaddr *)&a, &al) != 0) {
        fprintf(stderr, "break_update_server: cannot listen on %s:%d\n", o.bind_host, o.port);
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
        p.fd = fd;
        p.ssl = NULL;
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
    return 0;
}
