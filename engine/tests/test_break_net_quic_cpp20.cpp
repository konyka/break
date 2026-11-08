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

int run_auth_echo() {
    static const u8 kPsk[32] = {0x42};
    static const u8 kKeyId[8] = {0};

    bq::Server::Config sc;
    sc.cert_file = FIXTURE("break_test_cert.pem");
    sc.key_file = FIXTURE("break_test_key.pem");
    sc.alpn = "break/1";
    auto server = bq::Server::Create(sc);
    CHECK(server.has_value());
    CHECK(server->SetAuth([](const u8 key_id[8], u8 out[32]) -> bool {
        (void)key_id;
        std::memcpy(out, kPsk, 32);
        return true;
    }));

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

    /* handshake -> READY -> CHALLENGE -> AUTH v2 */
    bool authed = false;
    for (u32 i = 0; i < 5000u && !authed; ++i) {
        server->Step(1);
        client->Step(1);
        if (client->HandshakeDone()) {
            authed = client->Authenticate(kKeyId, kPsk);
        }
    }
    CHECK(authed);

    /* server verifies and reports AUTHENTICATED */
    std::optional<bq::Event> ev;
    for (u32 i = 0; i < 5000u; ++i) {
        server->Step(1);
        client->Step(1);
        while (auto e = server->PollEvent()) {
            if (e->type == BREAK_NET_QUIC_EVENT_AUTHENTICATED) {
                ev = e;
            }
        }
        if (ev.has_value()) break;
    }
    CHECK(ev.has_value());
    auto conn = server->GetConn(ev->conn_id);
    CHECK(conn.Valid());

    /* envelope-level echo through the wrapper (PING id=2) */
    const char *ping = "P";
    CHECK(client->SendMessage(2, 1, 0,
                              std::span<const u8>(
                                  reinterpret_cast<const u8 *>(ping), 1)));
    bool echoed = false;
    for (u32 i = 0; i < 5000u && !echoed; ++i) {
        server->Step(1);
        client->Step(1);
        if (auto m = conn.RecvMessage()) {
            CHECK(m->id == 2 && m->version == 1 && m->sequence == 2u);
            CHECK(m->payload.size() == 1u && m->payload[0] == 'P');
            CHECK(conn.SendMessage(2, 1, 0, std::span<const u8>(m->payload.data(),
                                                                m->payload.size())));
        }
        if (auto r = client->RecvMessage()) {
            CHECK(r->id == 2 && r->payload.size() == 1u &&
                  r->payload[0] == 'P');
            echoed = true;
        }
    }
    CHECK(echoed);
    return 0;
}

} // namespace

int main() {
    if (run_echo() != 0) {
        return 1;
    }
    if (run_auth_echo() != 0) {
        return 1;
    }
    std::printf("PASS break_net_quic_cpp20 echo + auth\n");
    return 0;
}
