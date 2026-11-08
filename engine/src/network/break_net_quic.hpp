#pragma once
// break_net_quic.hpp — C++20 wrapper over the break_net_quic C API
// (dual-language policy, docs/Build_Guide.md §1.1): same features, RAII
// ownership, std types at the boundary. Header-only; the C module carries
// all behavior, so the two languages can never drift.

#include <optional>
#include <span>
#include <string>
#include <vector>

#include "network/break_net_quic.h"

namespace breakxx::quic {

using Event = BreakNetQuicEvent;
using EventType = BreakNetQuicEventType;
using DisconnectReason = BreakNetQuicDisconnectReason;

inline constexpr std::size_t kMaxMessage = BREAK_NET_QUIC_MAX_MESSAGE;

class Server;

/* Server-side connection handle; borrowed from Server, valid until its
 * DISCONNECT event is consumed. */
class Conn {
  public:
    Conn() = default;

    /* Copies the inbox message out; std::nullopt when empty or over cap. */
    [[nodiscard]] std::optional<std::vector<u8>> Read() {
        if (server_ == nullptr || conn_ == nullptr) {
            return std::nullopt;
        }
        std::vector<u8> out(kMaxMessage);
        u32 len = 0;
        if (!break_net_quic_conn_read(server_, conn_, out.data(),
                                      static_cast<u32>(out.size()), &len)) {
            return std::nullopt;
        }
        out.resize(len);
        return out;
    }

    [[nodiscard]] bool Send(std::span<const u8> data) {
        return server_ != nullptr && conn_ != nullptr &&
               break_net_quic_conn_send(server_, conn_, data.data(),
                                        static_cast<u32>(data.size()));
    }

    void Close() {
        if (server_ != nullptr && conn_ != nullptr) {
            break_net_quic_conn_close(server_, conn_);
        }
    }

    [[nodiscard]] bool Valid() const { return conn_ != nullptr; }

  private:
    friend class Server;
    Conn(BreakNetQuicServer *server, BreakNetQuicConn *conn)
        : server_(server), conn_(conn) {}
    BreakNetQuicServer *server_ = nullptr;
    BreakNetQuicConn *conn_ = nullptr;
};

class Server {
  public:
    struct Config {
        std::string cert_file;
        std::string key_file;
        std::string alpn;
        u16 port = 0;
        u32 max_connections = 0;
        u32 handshake_timeout_ms = 0;
        u32 max_idle_timeout_ms = 0;
    };

    [[nodiscard]] static std::optional<Server> Create(const Config &cfg) {
        BreakNetQuicServerConfig c{};
        c.cert_file = cfg.cert_file.c_str();
        c.key_file = cfg.key_file.c_str();
        c.alpn = cfg.alpn.c_str();
        c.port = cfg.port;
        c.max_connections = cfg.max_connections;
        c.handshake_timeout_ms = cfg.handshake_timeout_ms;
        c.max_idle_timeout_ms = cfg.max_idle_timeout_ms;
        BreakNetQuicServer *raw = break_net_quic_server_create(&c);
        if (raw == nullptr) {
            return std::nullopt;
        }
        return Server(raw);
    }

    ~Server() { break_net_quic_server_destroy(&raw_); }
    Server(const Server &) = delete;
    Server &operator=(const Server &) = delete;
    Server(Server &&o) noexcept : raw_(o.raw_) { o.raw_ = nullptr; }
    Server &operator=(Server &&o) noexcept {
        if (this != &o) {
            break_net_quic_server_destroy(&raw_);
            raw_ = o.raw_;
            o.raw_ = nullptr;
        }
        return *this;
    }

    [[nodiscard]] u16 Port() const { return break_net_quic_server_port(raw_); }
    bool Step(u32 timeout_ms) { return break_net_quic_server_step(raw_, timeout_ms); }

    [[nodiscard]] std::optional<Event> PollEvent() {
        Event ev{};
        if (!break_net_quic_server_poll_event(raw_, &ev)) {
            return std::nullopt;
        }
        return ev;
    }

    [[nodiscard]] Conn GetConn(u32 conn_id) {
        return Conn(raw_, break_net_quic_server_conn(raw_, conn_id));
    }

    [[nodiscard]] u64 DroppedDatagrams() const {
        return break_net_quic_server_dropped_datagrams(raw_);
    }
    [[nodiscard]] u64 EventsOverflow() const {
        return break_net_quic_server_events_overflow(raw_);
    }

  private:
    explicit Server(BreakNetQuicServer *raw) : raw_(raw) {}
    BreakNetQuicServer *raw_ = nullptr;
};

class Client {
  public:
    struct Config {
        std::string host;
        u16 port = 0;
        std::string server_name;
        std::string trust_store_file;
        std::string cert_file; // client certificate (snow contract)
        std::string key_file;
        std::string alpn;
    };

    [[nodiscard]] static std::optional<Client> Create(const Config &cfg) {
        BreakNetQuicClientConfig c{};
        c.host = cfg.host.c_str();
        c.port = cfg.port;
        c.server_name = cfg.server_name.c_str();
        c.trust_store_file = cfg.trust_store_file.c_str();
        c.cert_file = cfg.cert_file.c_str();
        c.key_file = cfg.key_file.c_str();
        c.alpn = cfg.alpn.c_str();
        BreakNetQuicClient *raw = break_net_quic_client_create(&c);
        if (raw == nullptr) {
            return std::nullopt;
        }
        return Client(raw);
    }

    ~Client() { break_net_quic_client_destroy(&raw_); }
    Client(const Client &) = delete;
    Client &operator=(const Client &) = delete;
    Client(Client &&o) noexcept : raw_(o.raw_) { o.raw_ = nullptr; }
    Client &operator=(Client &&o) noexcept {
        if (this != &o) {
            break_net_quic_client_destroy(&raw_);
            raw_ = o.raw_;
            o.raw_ = nullptr;
        }
        return *this;
    }

    bool Step(u32 timeout_ms) { return break_net_quic_client_step(raw_, timeout_ms); }
    [[nodiscard]] bool HandshakeDone() const {
        return break_net_quic_client_handshake_done(raw_);
    }
    [[nodiscard]] bool Failed() const {
        return break_net_quic_client_failed(raw_);
    }

    [[nodiscard]] bool Send(std::span<const u8> data) {
        return break_net_quic_client_send(raw_, data.data(),
                                          static_cast<u32>(data.size()));
    }

    [[nodiscard]] std::optional<std::vector<u8>> Read() {
        std::vector<u8> out(kMaxMessage);
        u32 len = 0;
        if (!break_net_quic_client_read(raw_, out.data(),
                                        static_cast<u32>(out.size()), &len)) {
            return std::nullopt;
        }
        out.resize(len);
        return out;
    }

    [[nodiscard]] std::optional<Event> PollEvent() {
        Event ev{};
        if (!break_net_quic_client_poll_event(raw_, &ev)) {
            return std::nullopt;
        }
        return ev;
    }

    void Close() { break_net_quic_client_close(raw_); }

  private:
    explicit Client(BreakNetQuicClient *raw) : raw_(raw) {}
    BreakNetQuicClient *raw_ = nullptr;
};

} // namespace breakxx::quic
