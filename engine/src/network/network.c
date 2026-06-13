/*
 * Cross-platform network module (UDP / TCP).
 *
 * Backends:
 *   - Linux: BSD sockets (poll, fcntl, close)
 *   - Windows: Winsock2 (WSAPoll, ioctlsocket, closesocket)
 */

/* Bump POSIX feature level to expose getaddrinfo/freeaddrinfo (requires 200112L).
   The engine globally defines _POSIX_C_SOURCE=199309L which is too low. */
#if !defined(ENGINE_PLATFORM_WINDOWS)
#  ifdef _POSIX_C_SOURCE
#    undef _POSIX_C_SOURCE
#  endif
#  define _POSIX_C_SOURCE 200112L
#endif

#include "network.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(ENGINE_PLATFORM_WINDOWS)
    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif
    #include <winsock2.h>
    #include <ws2tcpip.h>
    typedef SOCKET RawSocket;
    typedef int    socklen_t_compat;
    #define INVALID_RAW_SOCKET INVALID_SOCKET
    #define NET_LAST_ERROR()   WSAGetLastError()
    #define NET_EWOULDBLOCK    WSAEWOULDBLOCK
    #define NET_EAGAIN         WSAEWOULDBLOCK
    #define NET_EINPROGRESS    WSAEWOULDBLOCK
    #define NET_ECONNRESET     WSAECONNRESET
    #define NET_CLOSE_FN(s)    closesocket(s)
    #define NET_POLL_FN        WSAPoll
    typedef WSAPOLLFD          NativePollFd;
    typedef int                NativePollCount;
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <poll.h>
    #include <errno.h>
    typedef int RawSocket;
    typedef socklen_t socklen_t_compat;
    #define INVALID_RAW_SOCKET (-1)
    #define NET_LAST_ERROR()   errno
    #define NET_EWOULDBLOCK    EWOULDBLOCK
    #define NET_EAGAIN         EAGAIN
    #define NET_EINPROGRESS    EINPROGRESS
    #define NET_ECONNRESET     ECONNRESET
    #define NET_CLOSE_FN(s)    close(s)
    #define NET_POLL_FN        poll
    typedef struct pollfd      NativePollFd;
    typedef nfds_t             NativePollCount;
#endif

struct NetSocket {
    RawSocket    fd;
    NetProtocol  proto;
    bool         nonblocking;
    bool         connected;
};

/* ---------- helpers ---------- */

static NetSocket *net__alloc_socket(RawSocket fd, NetProtocol proto)
{
    NetSocket *s = (NetSocket *)calloc(1, sizeof(NetSocket));
    if (!s) {
        NET_CLOSE_FN(fd);
        return NULL;
    }
    s->fd          = fd;
    s->proto       = proto;
    s->nonblocking = false;
    s->connected   = false;
    return s;
}

static bool net__is_would_block(int err)
{
    if (err == NET_EWOULDBLOCK || err == NET_EAGAIN || err == NET_EINPROGRESS) {
        return true;
    }
    return false;
}

static void net__fill_address_from_sockaddr(const struct sockaddr_in *sa,
                                            NetAddress *out)
{
    if (!out) return;
    memset(out, 0, sizeof(*out));
    /* inet_ntop is portable for IPv4 since Vista on Windows. */
    if (inet_ntop(AF_INET, &sa->sin_addr, out->host, sizeof(out->host)) == NULL) {
        snprintf(out->host, sizeof(out->host), "0.0.0.0");
    }
    out->port = ntohs(sa->sin_port);
}

static bool net__resolve_to_sockaddr(const char *host, u16 port,
                                     struct sockaddr_in *out)
{
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    char port_str[16];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM; /* protocol is irrelevant for resolution */
    snprintf(port_str, sizeof(port_str), "%u", (unsigned)port);

    if (getaddrinfo(host, port_str, &hints, &res) != 0 || res == NULL) {
        return false;
    }

    memset(out, 0, sizeof(*out));
    memcpy(out, res->ai_addr, sizeof(struct sockaddr_in));
    freeaddrinfo(res);
    return true;
}

/* ---------- lifecycle ---------- */

bool net_init(void)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
    WSADATA wsa;
    int rc = WSAStartup(MAKEWORD(2, 2), &wsa);
    return rc == 0;
#else
    return true;
#endif
}

void net_shutdown(void)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
    WSACleanup();
#endif
}

/* ---------- socket creation ---------- */

NetSocket *net_udp_create(u16 bind_port)
{
    RawSocket fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == INVALID_RAW_SOCKET) {
        return NULL;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons(bind_port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        NET_CLOSE_FN(fd);
        return NULL;
    }
    return net__alloc_socket(fd, NET_PROTO_UDP);
}

NetSocket *net_tcp_connect(const char *host, u16 port)
{
    struct sockaddr_in addr;
    if (!host || !net__resolve_to_sockaddr(host, port, &addr)) {
        return NULL;
    }

    RawSocket fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == INVALID_RAW_SOCKET) {
        return NULL;
    }

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        int err = NET_LAST_ERROR();
        if (!net__is_would_block(err)) {
            NET_CLOSE_FN(fd);
            return NULL;
        }
        /* non-blocking connect in progress is acceptable */
    }

    NetSocket *s = net__alloc_socket(fd, NET_PROTO_TCP);
    if (s) s->connected = true;
    return s;
}

NetSocket *net_tcp_listen(u16 port, u32 backlog)
{
    RawSocket fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == INVALID_RAW_SOCKET) {
        return NULL;
    }

    int yes = 1;
    (void)setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
                     (const char *)&yes, (socklen_t_compat)sizeof(yes));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons(port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        NET_CLOSE_FN(fd);
        return NULL;
    }

    if (listen(fd, (int)backlog) < 0) {
        NET_CLOSE_FN(fd);
        return NULL;
    }
    return net__alloc_socket(fd, NET_PROTO_TCP);
}

NetSocket *net_tcp_accept(NetSocket *listener, NetAddress *out_addr)
{
    if (!listener) return NULL;

    struct sockaddr_in peer;
    socklen_t_compat peer_len = (socklen_t_compat)sizeof(peer);
    memset(&peer, 0, sizeof(peer));

    RawSocket fd = accept(listener->fd, (struct sockaddr *)&peer, &peer_len);
    if (fd == INVALID_RAW_SOCKET) {
        return NULL;
    }

    if (out_addr) {
        net__fill_address_from_sockaddr(&peer, out_addr);
    }

    NetSocket *s = net__alloc_socket(fd, NET_PROTO_TCP);
    if (s) s->connected = true;
    return s;
}

/* ---------- I/O ---------- */

i32 net_send(NetSocket *s, const void *data, u32 size)
{
    if (!s || !data) return NET_ERROR;

#if defined(ENGINE_PLATFORM_WINDOWS)
    int n = send(s->fd, (const char *)data, (int)size, 0);
#else
    ssize_t n = send(s->fd, data, (size_t)size, 0);
#endif
    if (n < 0) {
        int err = NET_LAST_ERROR();
        if (net__is_would_block(err)) return NET_WOULD_BLOCK;
        if (err == NET_ECONNRESET)    return NET_DISCONNECTED;
        return NET_ERROR;
    }
    if (n == 0 && s->proto == NET_PROTO_TCP) {
        return NET_DISCONNECTED;
    }
    return (i32)n;
}

i32 net_recv(NetSocket *s, void *buf, u32 buf_size)
{
    if (!s || !buf) return NET_ERROR;

#if defined(ENGINE_PLATFORM_WINDOWS)
    int n = recv(s->fd, (char *)buf, (int)buf_size, 0);
#else
    ssize_t n = recv(s->fd, buf, (size_t)buf_size, 0);
#endif
    if (n < 0) {
        int err = NET_LAST_ERROR();
        if (net__is_would_block(err)) return NET_WOULD_BLOCK;
        if (err == NET_ECONNRESET)    return NET_DISCONNECTED;
        return NET_ERROR;
    }
    if (n == 0 && s->proto == NET_PROTO_TCP) {
        /* graceful peer shutdown */
        return NET_DISCONNECTED;
    }
    return (i32)n;
}

i32 net_sendto(NetSocket *s, const void *data, u32 size, const NetAddress *addr)
{
    if (!s || !data || !addr) return NET_ERROR;

    struct sockaddr_in dst;
    /* Use cached sockaddr_in if available, otherwise resolve and cache */
    NetAddress *mut_addr = (NetAddress *)addr; /* safe: we only write cache fields */
    if (mut_addr->resolved && sizeof(dst) <= sizeof(mut_addr->_sa)) {
        memcpy(&dst, mut_addr->_sa, sizeof(dst));
    } else {
        if (!net__resolve_to_sockaddr(addr->host, addr->port, &dst)) {
            return NET_ERROR;
        }
        if (sizeof(dst) <= sizeof(mut_addr->_sa)) {
            memcpy(mut_addr->_sa, &dst, sizeof(dst));
            mut_addr->resolved = true;
        }
    }

#if defined(ENGINE_PLATFORM_WINDOWS)
    int n = sendto(s->fd, (const char *)data, (int)size, 0,
                   (struct sockaddr *)&dst, (int)sizeof(dst));
#else
    ssize_t n = sendto(s->fd, data, (size_t)size, 0,
                       (struct sockaddr *)&dst, (socklen_t)sizeof(dst));
#endif
    if (n < 0) {
        int err = NET_LAST_ERROR();
        if (net__is_would_block(err)) return NET_WOULD_BLOCK;
        return NET_ERROR;
    }
    return (i32)n;
}

i32 net_recvfrom(NetSocket *s, void *buf, u32 buf_size, NetAddress *out_addr)
{
    if (!s || !buf) return NET_ERROR;

    struct sockaddr_in src;
    socklen_t_compat src_len = (socklen_t_compat)sizeof(src);
    memset(&src, 0, sizeof(src));

#if defined(ENGINE_PLATFORM_WINDOWS)
    int n = recvfrom(s->fd, (char *)buf, (int)buf_size, 0,
                     (struct sockaddr *)&src, &src_len);
#else
    ssize_t n = recvfrom(s->fd, buf, (size_t)buf_size, 0,
                         (struct sockaddr *)&src, &src_len);
#endif
    if (n < 0) {
        int err = NET_LAST_ERROR();
        if (net__is_would_block(err)) return NET_WOULD_BLOCK;
        return NET_ERROR;
    }
    if (out_addr) {
        net__fill_address_from_sockaddr(&src, out_addr);
    }
    return (i32)n;
}

/* ---------- options ---------- */

void net_set_nonblocking(NetSocket *s, bool nonblock)
{
    if (!s) return;

#if defined(ENGINE_PLATFORM_WINDOWS)
    u_long mode = nonblock ? 1u : 0u;
    if (ioctlsocket(s->fd, (long)FIONBIO, &mode) == 0) {
        s->nonblocking = nonblock;
    }
#else
    int flags = fcntl(s->fd, F_GETFL, 0);
    if (flags < 0) return;
    if (nonblock) {
        flags |= O_NONBLOCK;
    } else {
        flags &= ~O_NONBLOCK;
    }
    if (fcntl(s->fd, F_SETFL, flags) == 0) {
        s->nonblocking = nonblock;
    }
#endif
}

/* ---------- poll ---------- */

i32 net_poll(NetPollFd *fds, u32 count, i32 timeout_ms)
{
    if (count == 0) return 0;
    if (!fds)       return NET_ERROR;

    NativePollFd stack_buf[32];
    NativePollFd *native = stack_buf;
    bool heap_alloc = false;

    if (count > (u32)(sizeof(stack_buf) / sizeof(stack_buf[0]))) {
        native = (NativePollFd *)calloc(count, sizeof(NativePollFd));
        if (!native) return NET_ERROR;
        heap_alloc = true;
    } else {
        memset(stack_buf, 0, sizeof(stack_buf));
    }

    for (u32 i = 0; i < count; ++i) {
        native[i].fd      = fds[i].socket ? fds[i].socket->fd : INVALID_RAW_SOCKET;
        native[i].events  = 0;
        native[i].revents = 0;
        if (fds[i].events & NET_POLL_READ)  native[i].events |= POLLIN;
        if (fds[i].events & NET_POLL_WRITE) native[i].events |= POLLOUT;
        fds[i].revents = 0;
    }

#if defined(ENGINE_PLATFORM_WINDOWS)
    int rc = NET_POLL_FN(native, (ULONG)count, (INT)timeout_ms);
#else
    int rc = NET_POLL_FN(native, (NativePollCount)count, timeout_ms);
#endif

    if (rc < 0) {
        if (heap_alloc) free(native);
        return NET_ERROR;
    }

    for (u32 i = 0; i < count; ++i) {
        u32 rev = 0;
        if (native[i].revents & POLLIN)  rev |= NET_POLL_READ;
        if (native[i].revents & POLLOUT) rev |= NET_POLL_WRITE;
        if (native[i].revents & (POLLERR | POLLHUP | POLLNVAL)) rev |= NET_POLL_ERROR;
        fds[i].revents = rev;
    }

    if (heap_alloc) free(native);
    return (i32)rc;
}

/* ---------- close ---------- */

void net_close(NetSocket *s)
{
    if (!s) return;
    if (s->fd != INVALID_RAW_SOCKET) {
        NET_CLOSE_FN(s->fd);
        s->fd = INVALID_RAW_SOCKET;
    }
    free(s);
}

/* ---------- utilities ---------- */

bool net_address_resolve(const char *hostname, u16 port, NetAddress *out)
{
    if (!hostname || !out) return false;

    struct sockaddr_in sa;
    if (!net__resolve_to_sockaddr(hostname, port, &sa)) {
        return false;
    }
    net__fill_address_from_sockaddr(&sa, out);
    return true;
}

bool net_address_equal(const NetAddress *a, const NetAddress *b)
{
    if (!a || !b) return false;
    if (a->port != b->port) return false;
    return strcmp(a->host, b->host) == 0;
}
