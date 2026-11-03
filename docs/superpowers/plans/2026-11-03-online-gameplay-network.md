# Online Gameplay Network Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver the P8 online-session, UDP coordination, bounded PCM voice, and aspect-based replication behaviors as real C11 libraries with direct loopback and failure-path tests.

**Architecture:** Add an optional `break_online` static library beside the existing network libraries. GameThread-owned lobby, NAT protocol state, voice playout, and aspect replication use create-time fixed storage; network-facing receive entry points only validate datagram bounds and copy into mutex-protected bounded rings. Existing `BreakSessionManager` supplies authenticated identity through a narrow adapter, existing `NetSocket` supplies UDP I/O, and aspect scheduling consumes existing `BreakAoIResult` plus `BreakReplicationFragment` rather than reimplementing AOI, transport security, reliable delivery, or fragmentation checksums.

**Tech Stack:** C11, CMake/CTest, `test_framework.h`, existing `platform_thread.h`, `network.c`/`net_loop`, `break_replication_core`, no new dependencies.

## Global Constraints

- Work only in `.worktrees/cry-network` on `cry-wave2-network`; do not modify master or push.
- Engine and new libraries use C11 with fixed capacity and no hot-path allocation after create.
- GameThread owns mutable lobby/NAT protocol/voice playout/replication state; network callbacks validate and enqueue only, never call game logic.
- External persistent identity uses `{index,generation}` handles; stale handles return `BREAK_RUNTIME_STALE`.
- Invalid external data returns `INVALID`, full capacity returns `OVERLOAD`, wrong owner returns `REJECTED`, unavailable work returns `FAILED`.
- Every mutating operation validates before commit; failure leaves prior state and outputs unchanged unless network datagrams already handed to the OS make recall impossible.
- UDP evidence is real IPv4 loopback on this host; it does not claim arbitrary NAT traversal, external deployment, audio listening quality, or a reliable transport.
- Aspect traffic is handed to the caller's authenticated transport; checksums remain integrity checks, not authentication.
- Each behavior follows RED -> GREEN, records concrete output, and each task is locally committed after focused and relevant regression tests pass.
- At least one real source mutation per major subsystem must make an existing test fail; restore the source and rerun green. Do not edit tests to hide a defect.

## File Structure

- `engine/src/network/break_online_types.h`: shared `BreakRuntimeError` use, generation handle, authenticated identity/provider POD.
- `engine/src/network/break_online_lobby.{h,c}`: bounded room directory, membership, host migration, matchmaking, owner checks.
- `engine/src/network/break_online_session.h`: static-inline adapter from authenticated `BreakSessionManager` state to `BreakOnlineAuthSource`.
- `engine/src/network/break_online_inbox.{h,c}`: internal fixed-size datagram ring, MPSC producers and single GameThread consumer.
- `engine/src/network/break_online_nat.{h,c}`: versioned NAT coordination wire messages, peer/pair state, borrowed UDP sockets, loopback-observable connected state.
- `engine/src/network/break_online_voice.{h,c}`: bounded little-endian PCM frame codec, queued receiver, sequence-aware jitter buffer and explicit concealment.
- `engine/src/network/break_online_aspect.{h,c}`: fixed aspect schema/store, stable object identity, dirty-mask canonical packet encode and transactional apply.
- `engine/src/network/break_online_aspect_replication.{h,c}`: per-connection baseline/dirty masks, bandwidth budgets, AOI enter/stay/leave scheduling and fragment emission.
- `engine/src/network/break_replication_fragment.{h,c}`: add caller-storage fragment views while preserving the allocating compatibility API.
- `engine/tests/test_break_online_{lobby,nat,voice,aspect,aspect_replication}.c`: direct behavior tests.
- `engine/tests/test_break_replication_fragment.c`: caller-storage fragmentation and regression coverage.
- `engine/tests/test_break_session.c`: real authenticated-session identity adapter coverage when Snowflake is enabled.
- `engine/CMakeLists.txt`: formal optional target and focused tests; no link into `engine`, demos, or editor.
- `docs/design/online_gameplay_network.md`: actual API, wire formats, ownership, limits, and evidence.
- `docs/design/session_protocol.md`, `docs/design/ecs_snapshot_replication_aoi.md`: links and actual new integration boundaries only.
- `docs/Implementation_Status.md`: concise verified P8 status and limitations.
- `.superpowers/sdd/online-gameplay-network-report.md`: final commands, RED/GREEN/mutation evidence, commits, and limitations.

---

### Task 1: Authenticated Bounded Lobby and Matchmaking

**Files:**
- Create: `engine/src/network/break_online_types.h`
- Create: `engine/src/network/break_online_lobby.h`
- Create: `engine/src/network/break_online_lobby.c`
- Create: `engine/src/network/break_online_session.h`
- Create: `engine/tests/test_break_online_lobby.c`
- Modify: `engine/CMakeLists.txt` near `break_replication_core` and network tests
- Test: `engine/tests/test_break_session.c`

**Interfaces:**
- Produces:
```c
typedef struct BreakOnlineHandle { u32 index; u32 generation; } BreakOnlineHandle;
typedef struct BreakOnlineMemberHandle {
    BreakOnlineHandle room;
    BreakOnlineHandle member;
} BreakOnlineMemberHandle;
typedef struct BreakOnlineIdentity { u64 session_id; u64 player_id; } BreakOnlineIdentity;
typedef bool (*BreakOnlineAuthenticateFn)(void *user, u64 session,
                                          BreakOnlineIdentity *out_identity);
typedef struct BreakOnlineAuthSource { void *user; BreakOnlineAuthenticateFn authenticate; } BreakOnlineAuthSource;

BreakRuntimeError break_lobby_create(const BreakLobbyConfig *, BreakLobby **out);
BreakRuntimeError break_lobby_room_create(BreakLobby *, const BreakLobbyAuth *,
                                          const BreakLobbyRoomDesc *,
                                          BreakOnlineHandle *out_room,
                                          BreakOnlineMemberHandle *out_member);
BreakRuntimeError break_lobby_join(BreakLobby *, const BreakLobbyAuth *,
                                   BreakOnlineHandle room, BreakOnlineMemberHandle *out_member);
BreakRuntimeError break_lobby_leave(BreakLobby *, const BreakLobbyAuth *,
                                    BreakOnlineMemberHandle member);
BreakRuntimeError break_lobby_disconnect(BreakLobby *, u64 session);
BreakRuntimeError break_lobby_match(BreakLobby *, const BreakLobbyAuth *,
                                    const BreakLobbyMatchQuery *,
                                    BreakOnlineHandle *out_room,
                                    BreakOnlineMemberHandle *out_member);
BreakRuntimeError break_lobby_list(const BreakLobby *, const BreakLobbyMatchQuery *,
                                   u32 offset, BreakLobbyRoomInfo *out, u32 capacity,
                                   u32 *out_count, u32 *out_next_offset);
BreakRuntimeError break_lobby_room_info(const BreakLobby *, BreakOnlineHandle,
                                        BreakLobbyRoomInfo *out);
```
`BreakLobbyAuth` combines the opaque session key and `BreakOnlineAuthSource`; callers cannot supply a player ID directly. `break_online_session.h` maps only `BREAK_SESSION_AUTHENTICATED` to `session_id=player_id=break_session_manager_session_id()`.

- [ ] **Step 1: Write failing lobby behavior tests**

Write tests with a stateful authentication provider containing `NEW`, `AUTHENTICATING`, and `AUTHENTICATED` sessions. The first test must assert unauthenticated create returns `REJECTED` and leaves room count at zero; authenticated create returns room/member handles and one host member. Add independent tests for duplicate player join, room/member capacity, stale handles after slot reuse, host leave selecting the oldest remaining member and increasing `host_epoch`, disconnect removing every membership for that session, deterministic fullest-room match with handle tie-break, and filtered directory pagination.

```c
TEST(lobby_rejects_unauthenticated_identity_without_creating_room)
{
    BreakLobby *lobby = make_lobby(2u, 2u);
    BreakOnlineHandle room = {99u, 99u};
    BreakOnlineMemberHandle member = {{99u, 99u}, {99u, 99u}};
    BreakLobbyRoomDesc desc = make_desc("one", 7u, 3u, 2u);
    BreakLobbyAuth auth = make_auth(11u, false, 101u);
    ASSERT_EQ(break_lobby_room_create(lobby, &auth, &desc, &room, &member),
              BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(room.index, 99u);
    ASSERT_EQ(member.member.index, 99u);
    ASSERT_EQ(break_lobby_room_count(lobby), 0u);
    break_lobby_destroy(lobby);
}
```

The mutation each test must catch is respectively: trusting unauthenticated identity, committing a partial room, omitting generation checks, failing to migrate host, ignoring session cleanup, choosing a non-deterministic room, and silently truncating a directory page.

- [ ] **Step 2: Run RED and record the missing-behavior failure**

Run:
```bash
cmake -S engine -B build-p8-normal -DENGINE_RHI_BACKEND=opengl -DBREAK_ENABLE_SNOWFLAKE=OFF -DBREAK_ENABLE_CRYPTO=OFF -DBREAK_ENABLE_CRASH=OFF
cmake --build build-p8-normal -j6 --target test_break_online_lobby
```
Expected initial RED: missing `network/break_online_lobby.h`. Add the public declarations, target, and functions returning `BREAK_RUNTIME_FAILED`; rebuild and run `./build-p8-normal/test_break_online_lobby`. Expected behavioral RED: authenticated create does not return `BREAK_RUNTIME_OK`, with room count still zero.

- [ ] **Step 3: Implement fixed-capacity rooms and atomic membership**

Allocate `max_rooms * sizeof(Room)` and `max_rooms * max_members_per_room * sizeof(Member)` once. `BreakOnlineMemberHandle` carries both the generation-checked room handle and the generation-checked member-slot handle. Use that shape consistently for join/leave/match outputs. Check owner with `platform_thread_id_equal`. Resolve identity before taking a slot. Validate all names by bounded length (1..63 bytes), capacities, duplicate player, and generation before writes. On leave, clear exactly one member, bump its generation on the next allocation, and commit the host change in the same owner-thread operation:

```c
if (room->member_count == 0u) {
    room->used = false;
    room->generation = next_generation(room->generation);
} else if (room->host_member == leaving_slot) {
    room->host_member = oldest_member_slot(room);
    room->host_epoch++;
}
```

Directory listing copies at most the caller page capacity and returns `next_offset`; this is explicit pagination, not silent truncation. Match considers only public matching non-full rooms, sorts by higher member count then lower packed room handle, and joins atomically.

- [ ] **Step 4: Verify GREEN and real Session adapter**

Run:
```bash
./build-p8-normal/test_break_online_lobby
ctest --test-dir build-p8-normal --output-on-failure -R '^(test_break_online_lobby|test_network|test_net_loop|test_net_loop_qnx|test_break_replication_fragment|test_ecs_replication)$'
```
Expected: all pass. With a pinned Snowflake source available, build `test_break_session`; add a test that binds/authenticates a real manager, creates a room through `break_online_session_auth`, then closes the manager session and verifies `break_lobby_disconnect` removes it. Do not claim this lane if the pinned source is unavailable.

- [ ] **Step 5: Mutate and commit**

Temporarily remove the `host_epoch++` or oldest-member selection. Expected RED: `lobby_host_leave_migrates_to_oldest_member` fails. Restore, rerun focused green, then:
```bash
git add engine/src/network/break_online_* engine/tests/test_break_online_lobby.c engine/tests/test_break_session.c engine/CMakeLists.txt
git commit -m "feat(network): add authenticated bounded lobby"
```

---

### Task 2: Bounded UDP Inbox and NAT Hole-Punch Coordination

**Files:**
- Create: `engine/src/network/break_online_inbox.h`
- Create: `engine/src/network/break_online_inbox.c`
- Create: `engine/src/network/break_online_nat.h`
- Create: `engine/src/network/break_online_nat.c`
- Create: `engine/tests/test_break_online_nat.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces a fixed datagram inbox (`BREAK_ONLINE_MAX_DATAGRAM == 1280`) with nonblocking producer push, FIFO poll, close, and overload/invalid counters.
- Produces `BreakNatCoordinator` and `BreakNatEndpoint`, both with borrowed `NetSocket` and create-time queue/peer/pair capacities. Public messages are `HELLO`, `PUNCH`, `PING`, `ACK`; integers are explicit little-endian, not packed structs.
- `break_nat_*_receive_socket` may run on the network thread and only drains bounded datagrams into the inbox. `break_nat_*_poll` runs on the recorded GameThread and performs protocol transitions and nonblocking sends.

```c
BreakRuntimeError break_nat_peer_hello(BreakNatEndpoint *, u64 session);
BreakRuntimeError break_nat_endpoint_poll(BreakNatEndpoint *, u32 max_messages);
BreakRuntimeError break_nat_coordinator_poll(BreakNatCoordinator *, u32 max_messages);
BreakRuntimeError break_nat_coordinator_pair(BreakNatCoordinator *,
                                             BreakOnlineHandle a,
                                             BreakOnlineHandle b,
                                             u64 nonce, u32 ttl_ms,
                                             BreakOnlineHandle *out_pair);
bool break_nat_endpoint_connected(const BreakNatEndpoint *, BreakOnlineHandle pair);
BreakRuntimeError break_nat_peer_observed(const BreakNatCoordinator *,
                                          BreakOnlineHandle peer, NetAddress *out);
```

- [ ] **Step 1: Write failing queue, wire-validation, and real UDP tests**

Tests must cover bounded FIFO, whole-datagram drop plus counter on full, malformed magic/version/kind/length, stale peer and pair handles, unknown/wrong-source `PING`, duplicate `HELLO`, pair capacity and TTL expiry. The end-to-end test creates three real nonblocking UDP sockets (coordinator and two endpoints), maps wildcard local addresses to `127.0.0.1`, runs HELLO registration through the coordinator's authenticated provider, starts a pair, and alternates bounded receive/poll calls until both endpoints are connected or a monotonic five-second deadline expires.

```c
ASSERT_EQ(net_sendto(a_socket, hello, hello_size, &coordinator_addr), hello_size);
pump_until_peer_registered(&coordinator, &a_peer);
ASSERT_EQ(break_nat_coordinator_pair(coordinator, a_peer, b_peer,
                                     UINT64_C(0x12345678), 1000u, &pair),
          BREAK_RUNTIME_OK);
pump_until_connected(a, b, pair);
ASSERT_TRUE(break_nat_endpoint_connected(a, pair));
ASSERT_TRUE(break_nat_endpoint_connected(b, pair));
```

The test catches a fake coordinator that marks connected without receiving the peer's nonce from the expected observed UDP address.

- [ ] **Step 2: Run RED**

Build `test_break_online_nat`. After declarations/stubs make it compile, expected behavioral RED includes `break_nat_endpoint_connected` remaining false and queue stats remaining zero. Save the exact assertion output.

- [ ] **Step 3: Implement inbox first, then coordination state**

The inbox allocation is one object plus `capacity` fixed slots. `push` holds `PlatformMutex` only for copy/ring bookkeeping; it never waits or calls a callback. Poll detaches one slot under the same lock and returns a value copy.

HELLO handling authenticates on GameThread, records the datagram source as the observed address, and returns a peer handle. Pairing validates two distinct live peers and nonzero nonce, then sends each a PUNCH containing the other observed address, pair handle, nonce, and expiry. PUNCH arms an endpoint; PING is accepted only for the armed pair, nonce, and source. A valid PING sends one PING reply and ACK to the coordinator, then marks the endpoint connected. Both endpoint ACKs complete coordinator pair state. Expiry clears only the matching generation.

```c
if (!address_equal(&source, &endpoint->peer_address) ||
    message.nonce != endpoint->nonce || message.pair_generation != endpoint->pair.generation) {
    return BREAK_RUNTIME_REJECTED;
}
endpoint->connected = true;
```

- [ ] **Step 4: Run GREEN and concurrent-producer check**

Run `./build-p8-normal/test_break_online_nat` and the Task 1 regression selection. Add a TSan-visible test with two producer threads pushing distinct bounded datagrams while the owner drains; assert received counts equal accepted pushes and overload counters equal rejected pushes. No producer may call poll or NAT state.

- [ ] **Step 5: Mutate and commit**

Remove the PING source-address comparison. Expected RED: `nat_rejects_ping_from_unexpected_source` fails and connected remains false. Restore and rerun real loopback green.
```bash
git add engine/src/network/break_online_inbox.* engine/src/network/break_online_nat.* engine/tests/test_break_online_nat.c engine/CMakeLists.txt
git commit -m "feat(network): add bounded UDP NAT coordination"
```

---

### Task 3: PCM Voice Frames, Sequence Jitter, and Loss Handling

**Files:**
- Create: `engine/src/network/break_online_voice.h`
- Create: `engine/src/network/break_online_voice.c`
- Create: `engine/tests/test_break_online_voice.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
```c
#define BREAK_VOICE_MAX_SAMPLES 960u
typedef struct BreakVoiceFrame {
    u32 sequence;
    u32 sample_rate;
    u16 channels;
    u16 sample_count;
    i16 samples[BREAK_VOICE_MAX_SAMPLES];
} BreakVoiceFrame;
typedef struct BreakVoicePlayback {
    u32 sequence;
    u16 sample_count;
    bool concealed;
    i16 samples[BREAK_VOICE_MAX_SAMPLES];
} BreakVoicePlayback;

BreakRuntimeError break_voice_encode(const BreakVoiceFrame *, u8 *out, u32 cap, u32 *out_size);
BreakRuntimeError break_voice_receiver_receive_socket(BreakVoiceReceiver *);
BreakRuntimeError break_voice_receiver_pump(BreakVoiceReceiver *, u32 max_frames, u64 now_ms);
BreakRuntimeError break_voice_receiver_pop(BreakVoiceReceiver *, u64 now_ms,
                                           BreakVoicePlayback *out, bool *out_ready);
```

The stream config fixes sample rate, mono/stereo channels, interleaved scalar sample count per frame (1..960 and divisible by channels), jitter delay, and buffer/queue capacities. Sequence comparison uses unsigned serial arithmetic, including wrap. The receive path copies validated bounded datagrams only; pump decodes on GameThread. An empty/not-yet-due pop returns `OK` with `*out_ready=false` and leaves playback unchanged.

- [ ] **Step 1: Write failing codec and playout tests**

Cover exact little-endian wire bytes, stereo interleaved PCM round trip, invalid rate/channels/sample count/trailing bytes, queue full, duplicate/stale/out-of-order frames, initial jitter delay, ordered playout, wraparound, and missing sequence concealment. A concealed frame must contain zeros, carry the missing sequence, and set `concealed=true`; a late copy of that sequence is stale and cannot displace later PCM.

```c
push_frame(receiver, 10u, 1000u, 0u);
push_frame(receiver, 12u, 1200u, 0u);
ASSERT_EQ(pop_at(receiver, 20u), BREAK_RUNTIME_OK);   /* delay elapsed */
ASSERT_EQ(pop_at(receiver, 40u), BREAK_RUNTIME_OK);   /* 11 missing */
ASSERT_TRUE(last_playback.concealed);
ASSERT_EQ(last_playback.sequence, 11u);
ASSERT_EQ(pop_at(receiver, 60u), BREAK_RUNTIME_OK);
ASSERT_FALSE(last_playback.concealed);
ASSERT_EQ(last_playback.samples[0], 1200);
```

- [ ] **Step 2: Run behavioral RED**

After declarations and stubs compile, run `./build-p8-normal/test_break_online_voice`. Expected RED: no frame is emitted at the jitter deadline, and the missing-sequence test reports `BREAK_RUNTIME_FAILED`/empty rather than concealed frame 11.

- [ ] **Step 3: Implement bounded codec, receiver queue, and jitter state**

Encode a fixed header followed by `sample_count` little-endian signed 16-bit interleaved samples; use checked multiplication and exact input length. The ring stores whole frames at pump time. First accepted frame sets `expected_sequence` and `playout_at=now+jitter_delay_ms`. Before that time pop returns `OK` with `out_ready=false` rather than fabricating audio. At/after playout, return expected queued PCM. If expected is absent and a later sequence exists, emit one zero frame and advance expected exactly once. Advance playout time by `(sample_count / channels) * 1000 / sample_rate`; reject a stream whose frame duration rounds to zero.

```c
static bool voice_seq_before(u32 a, u32 b)
{
    return a != b && (u32)(b - a) <= UINT32_C(0x7fffffff);
}
```

- [ ] **Step 4: Verify GREEN and UDP integration**

Run the voice executable and Task 1/2 regressions. Include a real UDP loopback voice test that sends encoded PCM to a bound receiver socket, drains via `break_voice_receiver_receive_socket`, pumps, advances past jitter delay, and verifies sample-exact playback. This is PCM correctness, not a listening test.

- [ ] **Step 5: Mutate and commit**

Change concealment to skip directly to the later sequence. Expected RED: the test requiring concealed sequence 11 fails. Restore and rerun.
```bash
git add engine/src/network/break_online_voice.* engine/tests/test_break_online_voice.c engine/CMakeLists.txt
git commit -m "feat(network): add bounded PCM voice jitter"
```

---

### Task 4: Caller-Storage Fragment Views

**Files:**
- Modify: `engine/src/network/break_replication_fragment.h`
- Modify: `engine/src/network/break_replication_fragment.c`
- Modify: `engine/tests/test_break_replication_fragment.c`
- Modify: `engine/CMakeLists.txt` only if labels/dependencies need adjustment

**Interfaces:**
- Produces:
```c
BreakReplicationFragmentResult break_replication_fragment_payload_into(
    u64 delta_id, u64 base_id, const void *payload, usize payload_size,
    usize fragment_payload_size, BreakReplicationFragment *out_fragments,
    usize fragment_capacity, usize *out_fragment_count);
```
The output data pointers borrow the input payload; metadata storage is caller-owned. Existing allocating `break_replication_fragment_payload` becomes a compatibility wrapper with identical wire metadata.

- [ ] **Step 1: Write failing fixed-storage tests**

Use a hand-computed 10-byte payload split into 4/4/2 bytes. Assert fragment count, indices, common delta/base IDs, per-fragment FNV values against the existing known-good allocating path, and exact reassembly in reverse order. Test zero output capacity and one-slot-short capacity return `OVER_LIMIT` with `out_fragment_count=0` and no partially usable metadata. The production mutation caught here is committing a partial fragment list on capacity failure.

- [ ] **Step 2: Run RED**

Build and run `test_break_replication_fragment`; initial RED is the missing symbol. Add declaration/stub returning `INVALID`, then expected behavioral RED is the fixed-storage call not returning `OK`.

- [ ] **Step 3: Implement shared fragment planning**

Calculate `count=(payload_size+fragment_size-1)/fragment_size` with overflow-safe division, validate count/capacity before writes, and share one internal fill routine between allocating and caller-storage APIs. Do not change checksum, index, payload borrowing, or reassembly semantics.

- [ ] **Step 4: Verify, mutate, and commit**

Run existing and new fragment tests. Temporarily remove the up-front `fragment_capacity < count` check; expected RED: short-capacity test fails under ASan or reports partial output. Restore and rerun before:
```bash
git commit -m "feat(network): add fixed-storage fragment views"
```

---

### Task 5: Aspect Schema, Stable Store, and Canonical Dirty-Mask Codec

**Files:**
- Create: `engine/src/network/break_online_aspect.h`
- Create: `engine/src/network/break_online_aspect.c`
- Create: `engine/tests/test_break_online_aspect.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
```c
typedef enum BreakAspectType {
    BREAK_ASPECT_U32 = 1, BREAK_ASPECT_I32 = 2,
    BREAK_ASPECT_F32 = 3, BREAK_ASPECT_BYTES = 4
} BreakAspectType;
typedef struct BreakAspectSchema {
    u32 aspect_id;       /* 1..64; wire mask bit is aspect_id-1 */
    u32 version;
    BreakAspectType type;
    u32 byte_capacity;   /* BYTES only, 1..configured stride */
} BreakAspectSchema;

BreakRuntimeError break_aspect_store_create(const BreakAspectStoreConfig *, BreakAspectStore **out);
BreakRuntimeError break_aspect_schema_register(BreakAspectStore *, const BreakAspectSchema *);
BreakRuntimeError break_aspect_object_create(BreakAspectStore *, BreakOnlineHandle *out);
BreakRuntimeError break_aspect_object_adopt(BreakAspectStore *, BreakOnlineHandle remote);
BreakRuntimeError break_aspect_object_destroy(BreakAspectStore *, BreakOnlineHandle);
BreakRuntimeError break_aspect_set_u32(BreakAspectStore *, BreakOnlineHandle, u32 aspect_id, u32 value);
BreakRuntimeError break_aspect_set_i32(BreakAspectStore *, BreakOnlineHandle, u32 aspect_id, i32 value);
BreakRuntimeError break_aspect_set_f32(BreakAspectStore *, BreakOnlineHandle, u32 aspect_id, f32 value);
BreakRuntimeError break_aspect_set_bytes(BreakAspectStore *, BreakOnlineHandle, u32 aspect_id,
                                         const void *data, u32 size);
BreakRuntimeError break_aspect_get_u32(const BreakAspectStore *, BreakOnlineHandle,
                                       u32 aspect_id, u32 *out);
BreakRuntimeError break_aspect_get_i32(const BreakAspectStore *, BreakOnlineHandle,
                                       u32 aspect_id, i32 *out);
BreakRuntimeError break_aspect_get_f32(const BreakAspectStore *, BreakOnlineHandle,
                                       u32 aspect_id, f32 *out);
BreakRuntimeError break_aspect_get_bytes(const BreakAspectStore *, BreakOnlineHandle,
                                         u32 aspect_id, void *out, u32 cap, u32 *out_size);
u64 break_aspect_schema_hash(const BreakAspectStore *);
u64 break_aspect_aoi_id(BreakOnlineHandle);
BreakRuntimeError break_aspect_encode(const BreakAspectStore *, BreakOnlineHandle,
                                      u64 mask, u8 kind, u8 *out, usize cap, usize *out_size);
BreakRuntimeError break_aspect_apply(BreakAspectStore *, const u8 *packet, usize size);
```

The packet carries `BRA1` magic/version, canonical schema hash, generation-bearing object ID, object revision, baseline/dirty kind, unsigned-varint mask, then only set aspects in ascending ID order. U32 uses unsigned LEB128, I32 zigzag LEB128, F32 four explicit little-endian bits with non-finite values rejected, BYTES uses varint length plus exact bytes. Apply validates the entire packet and stages changed values before commit.

- [ ] **Step 1: Write failing schema and encoding tests**

Register scalar position F32, health U32, and name BYTES. Create an object, set health to 1 and a scalar position, and assert baseline mask includes only active aspects. Change health from 300 to 1 and assert the dirty packet is smaller than the baseline and decodes to exactly those values. Hand-check a health-only packet's mask/value bytes rather than deriving expected bytes with the production encoder. Cover duplicate schema, schema freeze after object creation, capacity exhaustion, stale object after destroy/reuse, wrong type/size, non-finite F32, revision overflow, wrong schema hash, unknown mask bits, truncated varint, trailing bytes, and transactional apply leaving all prior values unchanged on any malformed later aspect.

```c
ASSERT_EQ(break_aspect_set_u32(store, object, 2u, 300u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_aspect_encode(store, object, UINT64_C(1) << 1u,
                              BREAK_ASPECT_DIRTY, packet, sizeof(packet), &size),
          BREAK_RUNTIME_OK);
ASSERT_EQ(size, 25u); /* BRA1 + hash + object + revision 1 + DIRTY + mask + value */
ASSERT_EQ(packet[20], 1u);      /* revision 1 */
ASSERT_EQ(packet[21], BREAK_ASPECT_DIRTY);
ASSERT_EQ(packet[22], 2u);      /* aspect 2 mask */
ASSERT_EQ(packet[23], 0xacu);   /* varint 300 low bits */
ASSERT_EQ(packet[24], 0x02u);   /* varint 300 high bits */
```

- [ ] **Step 2: Run behavioral RED**

After declarations/stubs compile, run the executable. Expected RED: the hand-derived dirty packet size/content differs, and malformed apply currently returns `FAILED` without proving state preservation.

- [ ] **Step 3: Implement fixed store and transactional codec**

Use one allocation for schemas, object slots, active/value-size arrays, values (`object * 64 * stride`), and one-object staging scratch. Generation zero is invalid; slot reuse increments generation without wrap to zero. Schema hash iterates ascending aspect ID and hashes explicit little-endian fields. Numeric setters validate all input and revision capacity before writing. `apply` requires a live adopted object and strictly newer revision; parse into staging, verify exact packet consumption, then copy changed values and revision atomically on the owner thread.

- [ ] **Step 4: Verify GREEN and mutation**

Run aspect plus fragment/AOI regressions. Temporarily disable the final trailing-byte check or commit staging before full validation; expected RED: malformed-packet test fails or observes partial mutation. Restore and rerun, then commit:
```bash
git commit -m "feat(network): add aspect schema delta codec"
```

---

### Task 6: AOI-Driven Aspect Replication and Secure-Transport Boundary

**Files:**
- Create: `engine/src/network/break_online_aspect_replication.h`
- Create: `engine/src/network/break_online_aspect_replication.c`
- Create: `engine/tests/test_break_online_aspect_replication.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
```c
typedef BreakRuntimeError (*BreakAspectSendFn)(
    void *user, u64 connection_id, const BreakReplicationFragment *fragment);

BreakRuntimeError break_aspect_replication_create(
    const BreakAspectReplicationConfig *, BreakAspectStore *,
    BreakSpatialIndex *borrowed_index, BreakAspectReplication **out);
BreakRuntimeError break_aspect_object_register(BreakAspectReplication *,
    const BreakReplicationObject *desc_without_entity_id, BreakOnlineHandle *out);
BreakRuntimeError break_aspect_replication_set_u32(BreakAspectReplication *,
    BreakOnlineHandle, u32 aspect_id, u32 value);
BreakRuntimeError break_aspect_connection_open(BreakAspectReplication *,
    u64 authenticated_connection_id, usize bandwidth_budget, usize fragment_size);
BreakRuntimeError break_aspect_replication_sync(BreakAspectReplication *,
    u64 connection_id, const BreakAoIResult *aoi, usize bandwidth_budget);
BreakRuntimeError break_aspect_replication_disconnect(BreakAspectReplication *, u64 connection_id);
```

Each open connection has fixed ghost rows for every object: baseline state, sent revision, and dirty mask. Object setters fan out dirty bits only to existing connection rows. AOI `enter` emits a baseline of all active aspects, `stay` emits only that connection's pending mask, and `leave` emits destroy/dormant before clearing the ghost. Send order remains the AOI result's priority/ID order. A packet is split with Task 4's caller-storage API and emitted through `BreakAspectSendFn`; the callback is the explicit boundary to an authenticated `BreakNetReactor` or another secured transport. No raw socket or World access occurs here.

- [ ] **Step 1: Write failing scheduling tests**

Use the real `BreakSpatialIndex` and `break_aoi_compute` to produce enter/stay/leave. A recording send sink stores bounded fragment copies and returns injected `OVERLOAD` on a selected call. Reassemble emitted fragments with the existing reassembler, then apply to a remote adopted `BreakAspectStore`. Assert: baseline contains all active aspects; two recipients each receive independent dirty state; unchanged stay emits zero bytes; one changed U32 emits only its bit/value; higher-priority AOI object wins a small budget; failed or over-budget sends leave dirty state and are retried; successful send clears only the encoded bits; leave emits dormant/destroy; disconnect removes ghosts; and reassembled remote state matches authoritative state.

```c
ASSERT_EQ(break_aspect_replication_set_u32(replication, object, 2u, 7u),
          BREAK_RUNTIME_OK);
ASSERT_EQ(sync_with_budget(replication, 1u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(sink.fragment_count, 0u);
ASSERT_EQ(sync_with_budget(replication, 1u, 4096u), BREAK_RUNTIME_OK);
ASSERT_EQ(sink.fragment_count, 1u);
apply_sink_to_remote(&sink, remote);
ASSERT_EQ(remote_health(remote, remote_object), 7u);
```

- [ ] **Step 2: Run behavioral RED**

After declarations/stubs compile, expected RED: sink receives no baseline and dirty retry emits no fragment.

- [ ] **Step 3: Implement fixed ghosts and all-or-retry publication**

Allocate object metadata, connection rows, `connection * object` ghosts, packet scratch, and fragment metadata scratch at create. Validate the whole encoded packet and total fragment byte budget before the first send. On callback failure retain baseline/dirty/ghost state; already emitted datagrams cannot be recalled, so retry uses a new delta ID and the receiver's existing duplicate/conflict checks. Only after every fragment returns `OK` clear exactly the encoded dirty mask and advance sent revision. Version/delta-ID overflow returns `OVERLOAD` before any send.

- [ ] **Step 4: Verify GREEN and mutation**

Run all P8 and existing network/replication tests. Temporarily clear the dirty mask before checking the send callback result; expected RED: injected send failure followed by retry emits nothing and remote health stays stale. Restore and rerun.
```bash
git commit -m "feat(network): schedule aspect deltas through AOI"
```

---

### Task 7: Documentation, Full Verification, and Report

**Files:**
- Create: `docs/design/online_gameplay_network.md`
- Modify: `docs/design/session_protocol.md`
- Modify: `docs/design/ecs_snapshot_replication_aoi.md`
- Modify: `docs/Implementation_Status.md`
- Create: `.superpowers/sdd/online-gameplay-network-report.md`
- Modify: this plan's checkboxes to match completed steps

- [ ] **Step 1: Build and run the normal network lane**

```bash
cmake --build build-p8-normal -j6
ctest --test-dir build-p8-normal --output-on-failure -L 'network|replication|fragmentation|session'
```
Run all five new executables directly so their individual behavior totals are captured. Include `test_packet`, `test_network`, both net_loop variants, `test_ecs_replication`, and all configured Snowflake session/replication tests. If Snowflake is enabled, use only the pinned commit required by CMake; a local source/archive is test infrastructure, not a new dependency.

- [ ] **Step 2: Configure ASan+UBSan and TSan independently**

```bash
cmake -S engine -B build-p8-asan -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND=opengl -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON -DBREAK_ENABLE_SNOWFLAKE=OFF -DBREAK_ENABLE_CRYPTO=OFF -DBREAK_ENABLE_CRASH=OFF
cmake -S engine -B build-p8-tsan -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND=opengl -DENGINE_USE_TSAN=ON -DBREAK_ENABLE_SNOWFLAKE=OFF -DBREAK_ENABLE_CRYPTO=OFF -DBREAK_ENABLE_CRASH=OFF
cmake --build build-p8-asan -j6 --target test_break_online_lobby test_break_online_nat test_break_online_voice test_break_online_aspect test_break_online_aspect_replication test_break_replication_fragment test_network test_net_loop test_net_loop_qnx test_ecs_replication
cmake --build build-p8-tsan -j6 --target test_break_online_lobby test_break_online_nat test_break_online_voice test_break_online_aspect test_break_online_aspect_replication test_break_replication_fragment test_network test_net_loop test_net_loop_qnx test_ecs_replication
ctest --test-dir build-p8-asan --output-on-failure -L 'network|replication|fragmentation|session'
ctest --test-dir build-p8-tsan --output-on-failure -L 'network|replication|fragmentation|session'
```
Expected: zero failures and zero sanitizer reports. Run a real UDP loopback in each lane, not just pure codec tests.

- [ ] **Step 3: Self-review and repository hygiene**

Review diffs for hot-path allocation, unchecked multiplication/addition, missing generation checks, wrong-owner access, callbacks under locks, packet trailing bytes, dirty-state loss, and comments describing superseded behavior. Do not weaken a failing test. Run:
```bash
git diff --check
git status --short
```
Remove only build/test artifacts created by this task that are not needed; never remove pre-existing files.

- [ ] **Step 4: Document only observed behavior and write the report**

Document exact capacities/defaults, wire fields, ownership, error/retry behavior, authenticated-session adapter, real UDP evidence, and all command totals. Preserve explicit limitations: arbitrary NAT/firewall traversal is not promised, PCM is not mixed on the network thread and no listening test is claimed, aspect checksums are not authentication, transport security is supplied by the existing session/transport, no client prediction/rollback or reliable delivery is added, and external production deployment is not unit evidence. The report lists plan path, every commit hash, every RED/GREEN assertion, mutations and restored green runs, sanitizer/loopback totals, and any unrun platform lane.

- [ ] **Step 5: Commit documentation/report and finish**

```bash
git add docs engine/CMakeLists.txt .superpowers/sdd/online-gameplay-network-report.md
git commit -m "docs(network): record online gameplay capabilities"
git log --oneline a0bfeb95..HEAD
```
Final handoff must state `DONE` only when all requested code and available-lane verification are complete; otherwise state `DONE_WITH_CONCERNS` with the exact limitation, final hash, and short test summary.
