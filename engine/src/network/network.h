#ifndef NETWORK_H
#define NETWORK_H

#include "../core/types.h"

typedef struct NetSocket NetSocket;

typedef enum {
    NET_PROTO_UDP = 0,
    NET_PROTO_TCP = 1
} NetProtocol;

typedef enum {
    NET_OK = 0,
    NET_ERROR = -1,
    NET_WOULD_BLOCK = -2,
    NET_DISCONNECTED = -3
} NetResult;

typedef struct {
    char host[256];
    u16 port;
    bool resolved;        /* true when _sa holds a valid cached sockaddr_in */
    u8   _sa[28];         /* cached struct sockaddr_in (16 bytes on Linux, up to 28 with padding) */
} NetAddress;

/* System init / shutdown (Windows needs WSAStartup) */
bool net_init(void);
void net_shutdown(void);

/* Socket creation */
NetSocket *net_udp_create(u16 bind_port);                    /* UDP socket, bind port (0 = any) */
NetSocket *net_tcp_connect(const char *host, u16 port);      /* TCP connect to remote */
NetSocket *net_tcp_listen(u16 port, u32 backlog);            /* TCP listener */

/* TCP-specific */
NetSocket *net_tcp_accept(NetSocket *listener, NetAddress *out_addr);

/* Common operations */
i32 net_send(NetSocket *s, const void *data, u32 size);
i32 net_recv(NetSocket *s, void *buf, u32 buf_size);

/* UDP-specific (datagram with address) */
i32 net_sendto(NetSocket *s, const void *data, u32 size, const NetAddress *addr);
i32 net_recvfrom(NetSocket *s, void *buf, u32 buf_size, NetAddress *out_addr);

/* Set non-blocking mode */
void net_set_nonblocking(NetSocket *s, bool nonblock);

/* Multiplexing */
typedef enum {
    NET_POLL_READ  = 1,
    NET_POLL_WRITE = 2,
    NET_POLL_ERROR = 4
} NetPollFlag;

typedef struct {
    NetSocket *socket;
    u32 events;    /* requested events */
    u32 revents;   /* returned events */
} NetPollFd;

i32 net_poll(NetPollFd *fds, u32 count, i32 timeout_ms);

/* Close */
void net_close(NetSocket *s);

/* Utilities */
bool net_address_resolve(const char *hostname, u16 port, NetAddress *out);
bool net_address_equal(const NetAddress *a, const NetAddress *b);

#endif /* NETWORK_H */
