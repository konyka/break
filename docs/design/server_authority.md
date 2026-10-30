# Server authority reference engine (`break_authority`)

Status: delivered 2026-10-30 as an optional static library. Stage 5 subproject 5, first half. It is a **reference engine for the rule, not a game server**: there is still no server product, no network front end and no persistence in this repository.

Source: `engine/src/authority/break_authority.{h,c}`. Tests: `engine/tests/test_break_authority.c` (14), `engine/tests/test_break_authority_target_contract.cmake`.

## 1. What it pins

`security_threat_model.md` section 3 said the client is never authoritative for economy, inventory and damage, but only as prose. This library makes that rule executable:

- The wire carries only the player's request. A SPEND names an item and a quantity; an ATTACK names a target. There is **no field** for a balance, a price, a damage value or a result, so a client has nothing to lie about.
- Balances, item counts and health change only inside the library, against the server's own tables: the item price table (`break_authority_define_item`, defined once, no silent re-pricing) and the weapon damage constant.
- The identity of the acting player is an **argument** (`session_id`), taken from the authenticated transport session. `break_authority_decode_intent` has no session field and rejects a payload with any extra byte, so a payload cannot name a different player.
- `break_authority_grant_server` is the only way money enters a ledger outside of the opening balance. It is a function call for server code (rewards, settled purchases). No intent reaches it.

## 2. Order of checks

For every intent, cheapest and least-trusting first. A denied intent changes no ledger.

1. the session exists (`BAUTH_DENIED_NO_SESSION`);
2. the sequence number: 0 is reserved (`INVALID`), a jump of more than `BREAK_AUTHORITY_MAX_GAP` (1024) ahead is `GAP`, a number already used or older than the 64-wide window is `REPLAY` (reuses `break_replay_window`);
3. the rate bucket (`BREAK_AUTHORITY_RATE_BURST` = 20 at one instant, 10 per second sustained; reuses `break_msg_rate` with an injected clock; a clock that goes backwards refills nothing) gives `RATE`;
4. argument ranges (quantity 1..100, a defined item, a living and different target) give `LIMIT` / `INVALID` / `NO_SESSION`;
5. the ledger rules (price times quantity with overflow checking, funds, count overflow) give `INVALID` / `FUNDS` / `LIMIT`.

**Sequence handling.** A sequence number is marked used only after the rate bucket also admits the intent. A rate refusal therefore does not burn the number and the same intent can be retried later; every other denial after the sequence check does consume it, so a rejected intent cannot be replayed. Pinned by `rate_denied_intent_does_not_burn_its_sequence_number`.

**Arithmetic.** `price * qty` never wraps (`INVALID` when it would), a balance never goes below 0 and never past `INT64_MAX` (a grant that would overflow is `LIMIT`), item counts do not wrap, health stays within `[0, START_HEALTH]`. A property test runs 100000 random intents (grants, spends with random items and quantities, attacks, replays, unknown sessions, a clock that jumps) and checks the invariants after every step.

## 3. Wire layout

Both intents are exactly 17 bytes, little-endian:

```
SPEND : kind u8 = 1, sequence u64, item_id u32, qty u32
ATTACK: kind u8 = 2, sequence u64, target_session u64
```

Shorter, longer, kind 0 or unknown, or sequence 0 all fail the decode.

## 4. Tests and mutation checks

Ten rules were each removed in turn and the matching test turned red: the overflow guard, the replay check, the rate gate, the gap check, the funds check, marking the sequence before the rate check, allowing a negative grant, allowing a self-attack, letting health go negative, and accepting trailing bytes in the decoder. (The last one first survived: the test buffer had sequence 0, so the decoder rejected it for the wrong reason. The test now uses a valid sequence so only the length can reject.) ASan+UBSan and TSan trees are clean.

The contract test pins that the library is not linked into `engine`, `engine_demo`, `dxx_break` or `editor`, that it exports exactly its 14 public functions and no test hook, and that its sources never reference the integrity library.

## 5. Not delivered

- A game server, a network front end, persistence of the ledgers, and a way to load the item table from data. Prices live in whatever calls `define_item`.
- Authoritative simulation. Damage is a single constant; hit detection, range, line of sight and cooldowns are the game's.
- Matchmaking (threat model section 3 still lists it as a design goal only).
- Wiring to `break_net` / `break_session`: the caller maps the connection's session to a `session_id` and feeds the payload to the decoder. That mapping is the part that must come from the authenticated transport.
- Multi-thread use (one owner thread, like the other libraries).
