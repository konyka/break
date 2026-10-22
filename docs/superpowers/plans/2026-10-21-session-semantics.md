# Session Semantics Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Close Session phase, duplicate, stale-event, apply-failure, and borrowed-message semantics without changing Snowflake or adapter callback source.

**Architecture:** Keep `BreakSessionManager` GameThread-owned and opaque. Add result classifications and counters to the Session API, enforce registry phase and duplicate policy during adapter-event application, and retain closed entries as lifetime slot records so stale events remain classifiable.

**Tech Stack:** C11, existing Break CMake/CTest, focused normal/ASan/TSan builds.

## Global Constraints

- Do not modify Snowflake.
- Do not modify real adapter callback source.
- Preserve GameThread-only Session mutation and borrowed handler-message lifetime.
- Add each behavior as a failing test before implementation.
- Keep closed slots retained; `max_sessions` remains lifetime binding capacity.

---

### Task 1: RED tests for Session classifications and policy

**Files:**
- Modify: `engine/tests/test_break_session.c`
- Modify: `engine/src/network/break_session.h`
- Modify: `engine/src/network/break_net_message_registry.h`

- [x] Add tests for AUTH phase rejection, AUTH handler failure leaving the session unauthenticated and entering closing, duplicate PING idempotence, stale-result classification after close, cumulative result counters, default AUTH/PING phase permissiveness, malformed public registry count, and `poll` versus `poll_adapter` boundaries.
- [x] Add the required public enum/type declarations in the header only so tests compile far enough to expose missing implementation behavior.
- [x] Run `cmake --build build-session-red --target test_break_session -j2`; the new malformed-registry test failed as expected before validation (`manager != NULL`).

### Task 2: GREEN Session state and observability

**Files:**
- Modify: `engine/src/network/break_session.c`
- Modify: `engine/src/network/break_session.h`
- Modify: `engine/src/network/break_net_message_registry.c`

- [x] Add per-entry close generation, PING sequence tracking, and manager last-result/stat counters.
- [x] Enforce registry phases, classify unknown/closed/invalid/phase/duplicate/handler failures, and apply AUTH only after a successful handler.
- [x] Treat repeated PING sequence as an idempotent successful no-op; invoke its handler only for the first sequence.
- [x] Preserve closed entries and classify subsequent events as stale without mutating them.
- [x] Run the focused normal test and confirm all Session tests pass (20/20); adapter dependency is now clean in the current focused tree.

### Task 3: Documentation and sanitizer verification

**Files:**
- Modify: `docs/design/session_protocol.md`
- Create/modify: `docs/superpowers/sdd/2026-10-19-session-protocol/task-outbound-report.md`

- [x] Document phase enforcement, AUTH failure policy, PING duplicate policy, close generation/stale classification, result counters, borrowed handler-message lifetime, lifetime slot capacity, default AUTH/PING `ANY` behavior, public registry count validation, and `poll`/`poll_adapter` roles.
- [x] Run focused normal, ASan, and TSan Session tests using the existing build directories (20/20 each); run `git diff --check`.
- [x] Do not commit changes; report any unavailable sanitizer target plainly.
