#pragma once
// break_net_quic.hpp — C++20 wrapper over the break_net_quic C API
// (dual-language policy, docs/Build_Guide.md §1.1): same features, RAII
// ownership, std types at the boundary. Header-only; the C module carries
// all behavior, so the two languages can never drift.

#include <functional>
#include <memory>
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

/* One decoded envelope message (the session-layer read result). */
struct Message {
    u16 id = 0;
    u16 version = 0;
    u32 sequence = 0;
    std::vector<u8> payload;
};

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

    /* Session layer (envelope framing + strict inbound sequence). */
    [[nodiscard]] bool SendMessage(u16 id, u16 version, u16 flags,
                                   std::span<const u8> payload) {
        return server_ != nullptr && conn_ != nullptr &&
               break_net_quic_conn_send_message(
                   server_, conn_, id, version, flags, payload.data(),
                   static_cast<u32>(payload.size()));
    }

    [[nodiscard]] std::optional<Message> RecvMessage() {
        if (server_ == nullptr || conn_ == nullptr) {
            return std::nullopt;
        }
        Message m;
        m.payload.resize(kMaxMessage);
        u32 len = 0;
        if (!break_net_quic_conn_recv_message(
                server_, conn_, &m.id, &m.version, &m.sequence,
                m.payload.data(), static_cast<u32>(m.payload.size()), &len)) {
            return std::nullopt;
        }
        m.payload.resize(len);
        return m;
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

    /* CHALLENGE/AUTH-v2 requirement (transport_security.md section 3 wire
     * format). The callback resolves key_id -> PSK with app-side custody.
     * Call right after Create, before any Step. */
    using AuthKeyFn = std::function<bool(const u8 key_id[8], u8 out_psk[32])>;
    [[nodiscard]] bool SetAuth(AuthKeyFn fn, u32 auth_timeout_ms = 0) {
        auth_fn_ = std::make_unique<AuthKeyFn>(std::move(fn));
        return break_net_quic_server_set_auth(raw_, &Server::AuthTrampoline,
                                              auth_fn_.get(), auth_timeout_ms);
    }

  private:
    explicit Server(BreakNetQuicServer *raw) : raw_(raw) {}
    static bool AuthTrampoline(void *user, const u8 key_id[8], u8 out[32]) {
        return (*static_cast<AuthKeyFn *>(user))(key_id, out);
    }
    BreakNetQuicServer *raw_ = nullptr;
    std::unique_ptr<AuthKeyFn> auth_fn_; /* heap-stable across Server moves */
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

    /* Answers the pending CHALLENGE with AUTH v2 (consumes it). */
    [[nodiscard]] bool Authenticate(const u8 key_id[8], const u8 psk[32]) {
        return break_net_quic_client_authenticate(raw_, key_id, psk);
    }

    [[nodiscard]] bool SendMessage(u16 id, u16 version, u16 flags,
                                   std::span<const u8> payload) {
        return break_net_quic_client_send_message(
            raw_, id, version, flags, payload.data(),
            static_cast<u32>(payload.size()));
    }

    [[nodiscard]] std::optional<Message> RecvMessage() {
        Message m;
        m.payload.resize(kMaxMessage);
        u32 len = 0;
        if (!break_net_quic_client_recv_message(
                raw_, &m.id, &m.version, &m.sequence, m.payload.data(),
                static_cast<u32>(m.payload.size()), &len)) {
            return std::nullopt;
        }
        m.payload.resize(len);
        return m;
    }

    void Close() { break_net_quic_client_close(raw_); }

  private:
    explicit Client(BreakNetQuicClient *raw) : raw_(raw) {}
    BreakNetQuicClient *raw_ = nullptr;
};

} // namespace breakxx::quic
