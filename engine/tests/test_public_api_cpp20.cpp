// test_public_api_cpp20.cpp — dual-language gate (docs/Build_Guide.md):
// every public C API header must be consumable from a C++20 translation
// unit. This file includes the full public set and builds as C++20; a
// header that drops its extern "C" guard, uses a C-only construct, or stops
// being self-contained fails this target's compile, which is the point.
//
// The list mirrors the public break_*.h surface (internal/test-hook headers
// are excluded by policy). Keep it in sync when a public header is added.
// Deliberate boundary: engine.h and below (platform/math/ecs/renderer
// headers) are the C-only runtime surface — they use C11 constructs
// (_Atomic, compound literals) with no C++ spelling and are not part of the
// C++20-consumable contract.

#include <core/types.h>
#include <core/break_version.h>

#include <ai/break_ai.h>
#include <authority/break_authority.h>
#include <crash/break_crash.h>
#include <crash/break_crash_cluster.h>
#include <crash/break_crash_symbolize.h>
#include <crypto/break_crypto.h>
#include <game/break_game.h>
#include <integrity/break_integrity.h>
#include <network/break_aoi.h>
#include <network/break_msg_rate.h>
#include <network/break_net_adapter.h>
#include <network/break_net_envelope.h>
#include <network/break_net_events.h>
#include <network/break_net_message.h>
#include <network/break_net_message_registry.h>
#include <network/break_net_protocol.h>
#include <network/break_replay_window.h>
#include <network/break_replication.h>
#include <network/break_replication_fragment.h>
#include <network/break_session.h>
#include <update/break_update.h>
#include <update/break_update_client.h>

// C++20 really is in effect (concepts + __cplusplus), not just the flag.
static_assert(__cplusplus >= 202002L, "this TU must compile as C++20");

namespace {

template <typename T>
concept BreakSized = requires(T t) { sizeof(t) >= 1u; };

static_assert(BreakSized<BreakNetEnvelope>);

} // namespace

int main() {
    // One live call across the language boundary proves the guards carry
    // through to link time, not just parse time.
    return break_version_string() != nullptr ? 0 : 1;
}
