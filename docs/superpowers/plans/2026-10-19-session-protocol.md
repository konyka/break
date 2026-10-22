# Session and Protocol Envelope Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build the C11 protocol envelope and GameThread-owned session layer above the completed Snowflake adapter.

**Architecture:** Snowflake remains transport/reactor owner. Adapter callbacks create bounded immutable events; GameThread polls and owns message registry, session state, authentication phase, and connection binding. Outbound commands are copied into an adapter-owned queue and sent through Snowflake notification APIs.

**Tech Stack:** C11, existing Break CMake/CTest, completed `break_net_adapter`, `break_net_message`, `break_net_protocol`, Snowflake C API.

## Global Constraints

- Keep all new core code C11 and opaque-handle based.
- Do not modify Snowflake.
- Do not call SessionManager, Lua, ECS, World, UI, RHI, file IO, or database code from Snowflake callbacks.
- GameThread owns all session mutations.
- Use explicit byte order and checked arithmetic.
- Do not implement ECS replication, AoI, Lua bindings, editor RPC, online update, or anti-cheat in this plan.
- Every behavior gets a failing test before implementation.
- Outbound overload must return a bounded error and never block GameThread.

---

## Task 1: Failing envelope and session tests

**Files:**
- Create/modify: `engine/tests/test_break_net_adapter.c` or new `engine/tests/test_break_session.c`
- Inspect: `engine/tests/test_network.c`, current protocol headers

- [x] Add table-driven envelope round-trip, endian, malformed length, unknown ID, version, and sequence tests.
- [x] Add session transition tests for legal and illegal states.
- [x] Add stale event-after-close and duplicate authentication tests.
- [x] Register the test target and run it red, confirming missing APIs rather than test harness errors.

## Task 2: Protocol registry and envelope codec

**Files:**
- Create: `engine/src/network/break_net_envelope.h`
- Create: `engine/src/network/break_net_envelope.c`
- Create: `engine/src/network/break_net_message_registry.h`
- Create: `engine/src/network/break_net_message_registry.c`
- Modify: CMake and tests

- [x] Define fixed-width envelope fields, magic, flags, maximum size, and explicit little-endian encode/decode helpers (18-byte envelope prefix).
- [x] Define message registration records: ID, minimum version, maximum version, payload limit, authentication phase, duplicate policy.
- [x] Encode only registered IDs.
- [x] Decode with checked arithmetic before every read.
- [x] Reject unknown IDs, unsupported versions, invalid flags, oversized payloads, duplicate/backward sequences.
- [x] Test all malformed and round-trip cases under ASan.

## Task 3: Adapter event and outbound command bridge

**Files:**
- Modify: `engine/src/network/break_net_adapter.h/c`
- Modify: `engine/src/network/break_net_message.h/c`
- Create: `engine/src/network/break_net_events.h/c`
- Modify: tests and CMake

- [x] Add bounded adapter event types for connection opened, message received, send-drained, connection closed, and transport error.
- [x] Add GameThread-only poll/drain API that transfers owned event records.
- [x] Add outbound command API that copies payloads and maps queue overload without blocking.
- [x] Read the exact Snowflake `add_acceptor_with_handlers` and connection callback signatures before wiring parser/open/close callbacks; do not guess signatures.
- [x] Ensure callback path only creates events and never calls SessionManager.
- [x] Test payload lifetime, FIFO ordering, stale connection events, and overload.

## Task 4: GameThread-owned SessionManager

**Files:**
- Create: `engine/src/network/break_session.h`
- Create: `engine/src/network/break_session.c`
- Modify: tests and CMake

- [x] Define opaque manager, connection key, session ID, config, and state enum.
- [x] Implement legal transitions: NEW→AUTHENTICATING→AUTHENTICATED→CLOSING→CLOSED and NEW→CLOSING→CLOSED.
- [x] Reject backward transitions and unknown connection keys.
- [x] Bind at most one session per connection.
- [x] Poll adapter events on GameThread and apply connection/message events deterministically.
- [x] Ensure events queued before close are classified stale after close and cannot mutate a closed session.
- [x] Test transitions, duplicate auth, close ordering, and manager destruction.

## Task 5: Integration validation and documentation

**Files:**
- Create: `docs/design/session_protocol.md`
- Modify: `docs/Architecture_Overview.md`
- Modify: `docs/Implementation_Status.md`
- Test: normal/ASan/TSan focused tests and full CTest

- [x] Document envelope fields, registry, session states, thread ownership, callback restrictions, and failure policy.
- [x] Add Mermaid diagrams for network callback→event queue→GameThread session dispatch and session close ordering.
- [x] Run normal, ASan, and TSan focused tests (adapter 30/30; Session 20/20 in each lane), including the real loopback wire path.
- [x] Run the standard full build/CTest and record unrelated environment failures without hiding them: known failures are outside this Session slice, five fuzz smoke targets were not run because their executables were not built, and the full suite is not a clean gate for this task.
- [x] Run `git diff --check`.

## Completion Gate

This plan is complete only when envelope/registry tests, adapter bridge tests, SessionManager transition tests, sanitizer-focused tests, documentation, and standard validation all pass; parser callbacks are wired using real Snowflake signatures; no later ECS/Lua/editor/security feature is claimed as implemented.
