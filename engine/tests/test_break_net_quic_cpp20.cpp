// test_break_net_quic_cpp20.cpp — dual-language evidence: the same QUIC
// handshake + framed echo round trip as test_break_net_quic.c, driven
// entirely through the C++20 wrapper (breakxx::quic). Same loopback rules:
// port-0 bind, condition polling, no fixed sleeps.

#include "network/break_net_quic.hpp"

#include <cstdio>
#include <cstring>

#define STR2(x) #x
#define STR(x) STR2(x)
#define FIXTURE(name) STR(BREAK_TEST_SSL_FIXTURE_DIR) "/" name

namespace {

namespace bq = breakxx::quic;

int failures = 0;
#define CHECK(x) do { if (!(x)) { \
    std::printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #x); ++failures; \
    return 1; } } while (0)

int run_echo() {
    bq::Server::Config sc;
    sc.cert_file = FIXTURE("break_test_cert.pem");
    sc.key_file = FIXTURE("break_test_key.pem");
    sc.alpn = "break/1";
    auto server = bq::Server::Create(sc);
    CHECK(server.has_value());
    CHECK(server->Port() != 0);

    bq::Client::Config cc;
    cc.host = "127.0.0.1";
    cc.port = server->Port();
    cc.server_name = "localhost";
    cc.trust_store_file = FIXTURE("break_test_cert.pem");
    cc.cert_file = FIXTURE("break_test_cert.pem");
    cc.key_file = FIXTURE("break_test_key.pem");
    cc.alpn = "break/1";
    auto client = bq::Client::Create(cc);
    CHECK(client.has_value());

    for (u32 i = 0; i < 2500u && !client->HandshakeDone(); ++i) {
        server->Step(1);
        client->Step(1);
    }
    CHECK(client->HandshakeDone());

    /* The server's CONNECT lands a round trip after the client's handshake:
     * keep pumping until it is observable. */
    std::optional<bq::Event> ev;
    for (u32 i = 0; i < 2500u && !ev.has_value(); ++i) {
        server->Step(1);
        client->Step(1);
        ev = server->PollEvent();
    }
    CHECK(ev.has_value());
    CHECK(ev->type == BREAK_NET_QUIC_EVENT_CONNECT);
    auto conn = server->GetConn(ev->conn_id);
    CHECK(conn.Valid());

    const char *ping = "ping";
    CHECK(client->Send(std::span<const u8>(
        reinterpret_cast<const u8 *>(ping), 4)));

    bool echoed = false;
    for (u32 i = 0; i < 5000u && !echoed; ++i) {
        server->Step(1);
        client->Step(1);
        while (auto mev = server->PollEvent()) {
            if (mev->type == BREAK_NET_QUIC_EVENT_MESSAGE) {
                auto msg = conn.Read();
                CHECK(msg.has_value());
                CHECK(msg->size() == 4u &&
                      std::memcmp(msg->data(), "ping", 4u) == 0);
                const char *pong = "pong";
                CHECK(conn.Send(std::span<const u8>(
                    reinterpret_cast<const u8 *>(pong), 4)));
            }
        }
        if (auto reply = client->Read()) {
            CHECK(reply->size() == 4u &&
                  std::memcmp(reply->data(), "pong", 4u) == 0);
            echoed = true;
        }
    }
    CHECK(echoed);

    client->Close();
    bool saw_disconnect = false;
    for (u32 i = 0; i < 5000u && !saw_disconnect; ++i) {
        server->Step(1);
        client->Step(1);
        while (auto dev = server->PollEvent()) {
            if (dev->type == BREAK_NET_QUIC_EVENT_DISCONNECT) {
                saw_disconnect = true;
            }
        }
    }
    CHECK(saw_disconnect);
    return 0;
}

} // namespace

int main() {
    if (run_echo() != 0) {
        return 1;
    }
    std::printf("PASS break_net_quic_cpp20 echo\n");
    return 0;
}
