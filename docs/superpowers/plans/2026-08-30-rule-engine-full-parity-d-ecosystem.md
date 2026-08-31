# Sub-project D: Ecosystem Parity — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: superpowers:subagent-driven-development. Steps use checkbox (`- [ ]`) syntax.

**Goal:** close the ecosystem deltas against upstream v1.21.4 per the spec (`docs/superpowers/specs/2026-08-29-rule-engine-full-parity-design.md` §Sub-project D): plugin boundary parity (pure helpers as local built-ins; host-specific ones documented out), example-family coverage via C-side smoke tests, Redis runtime verification attempt (probe documented; row promoted only with a live service), and the all-features → CMake option-set mapping.

**Base:** sub-project C delivered (5e51e75, pushed). Build/test conventions as in the C plan: gate tree `build-gate` (focused `ctest -R "rule_engine|backward_machine"` 20/20, full headless `ctest -LE graphics` 77/78 effective), ASan+UBSan tree `build-rule-fresh-asan`, MSVC tree `build-rule-debug`, bench regression `engine/scripts/rule_engine_bench_regression.cmake`.

**Ledger:** `.superpowers/sdd/2026-08-29-rule-engine-full-parity/progress.md` (append D entries).

## Global Constraints

- Evidence rule: no conformance row is promoted without implementation + executed local test reference.
- Append-only ABI; no `RE_ABI_VERSION_MINOR` bump expected for D (built-ins dispatch by name behind `re_builtin_call`, not header API — if a task adds public header API anyway, it must flag it in its report).
- C99, clang `-Wall -Wextra -Werror -pedantic` clean, MSVC-compilable.
- Line endings: LF in every rule_engine source/test file written (verify with `file` or `tr -cd '\r' | wc -c` — do NOT trust `grep -c $'\r'` under Git Bash); doc files keep their per-file on-disk convention.
- Never touch the ~22 pre-existing dirty non-rule-engine files or `.omo/`. Work stays uncommitted until D4's selective commit.
- Upstream semantics are the reference; cite f80a541 file:line for every semantic claim.
- Known environment noise (pre-existing, not D's): `test_async_loader` parallel flake; `test_network` 3 UDP failures from remote commit 76871ec.

## Upstream anchors (verified from ref f80a541 = v1.21.4, fetched fresh 2026-08-30/31)

- **Plugin suite** (`src/plugins/mod.rs:1-11`): exactly five plugins, none feature-gated; all implement `RulePlugin` (`src/engine/plugin.rs:48`), attached via `engine.load_plugin` (engine.rs:1977) — NOT auto-loaded. Registered surface:
  - `string_utils.rs`: actions ToUpperCase(:57) ToLowerCase(:69) StringLength(:81) StringContains(:93) StringTrim(:117) StringReplace(:129); functions concat(:148) repeat(:163, capped 1000) substring(:190). Metadata also declares StringSplit/StringJoin/padLeft/padRight — NEVER registered (vapor).
  - `math_utils.rs`: actions Add/Subtract/Multiply/Divide(÷0 errors)/Abs/Round (:60-120); functions min(:134) max(:152) sqrt(:170, rejects negatives) sum(:188) avg(:201). Metadata declares Modulo/Power/Ceil/Floor/random — NEVER registered (vapor).
  - `collection_utils.rs`: actions ArrayLength/ArrayPush/ArrayPop/ArraySort/ArrayFilter/ArrayFind/ObjectKeys/ObjectValues/ObjectMerge (:66-211); functions length(:252) contains(:269) first(:286) last(:308) reverse(:330) join(:350) slice(:372) keys(:404) values(:421). Metadata declares ArrayMap — NEVER registered (vapor).
  - `date_utils.rs`: actions CurrentDate/CurrentTime/FormatDate/AddDays/IsWeekend; functions now/today/dayOfWeek/year/month/day — clock/environment-dependent (Local::now() :61-62). Metadata declares ParseDate/AddHours/DateDiff/dayOfYear — NEVER registered (vapor).
  - `validation.rs`: actions ValidateEmail/ValidatePhone/ValidateUrl/ValidateRegex/ValidateRange/ValidateLength/ValidateNotEmpty (:70-157); functions isEmail(:179, rexile regex) isPhone(:191) isUrl(:203, starts_with http://+https://) isNumeric(:215) isEmpty(:228) inRange(:246). PURE but regex-dependent (rexile::Pattern).
- **Existing local equivalents** (builtins.c dispatch :856-914; A3/A4 families): len/length/size/count, isEmpty/is_empty, contains/includes, exists/notExists, log/print/println, now/timestamp, random, format/sprintf, sum/add, max/min, avg/average, round/floor/ceil/abs, startswith/endswith, lowercase/uppercase, trim, split, join. Local MISSING vs upstream plugins: concat, repeat, substring, replace (string); sqrt (math); first, last, reverse, slice, keys, values (collection, expression-form); isEmail, isPhone, isUrl, isNumeric, inRange (validation).
- **Cargo features** (Cargo.toml): `default = []`, `streaming = ["tokio"]`, `streaming-redis = ["streaming","redis"]`, `backward-chaining = []`. No aggregate feature; `--all-features` = {streaming, streaming-redis, backward-chaining}.
- **Examples** (upstream.yml inventory :213-220 holds the 29 names; families: 01 basic execution/expressions, 02 RETE core, 03 advanced GRL, 04 streaming, 09 backward chaining, 10 module system, 05/07 performance+parallel). upstream.yml:219-220: ~13 promoted, the rest unpromoted.
- **Redis**: local probe 2026-08-31 — no `redis-server`/`redis-cli` on PATH, localhost:6379 closed, `RE_TEST_REDIS_URL` unset → the spec's unavailable branch applies (row stays compile-verified optional_backend; probe evidence documented).
- **Honesty notes**: upstream lib.rs marketing ("44+ actions & 33+ functions") overcounts the actually-registered 33 actions + 29 functions; the plugin metadata-vs-registered gaps above are vapor to document, not replicate.

## Task D1: plugin boundary parity — pure helpers as built-ins

**Files:** Modify `engine/src/rule_engine/builtins.c` (+ maybe `ir_eval.c` dispatch surface — only if the builtin fallback needs it); Test: create `engine/tests/test_rule_engine_plugin_parity.c` (+ CMake registration mirroring engine/CMakeLists.txt:796-800)

**Interfaces:** existing `re_builtin_call` name-dispatch + classifiers (builtins.c:154-188), A4 function idiom (scratch, status returns), `re_engine_register_function` override-first rule (builtins.c:139-141 — new built-ins must NOT break host override).

- [ ] Step 1: string helpers: `concat` (variadic join of stringified args), `repeat` (cap 1000 per upstream :163 — over-cap → RE_STATUS_LIMIT), `substring` (start,len byte semantics over UTF-8 bytes — document byte-vs-char), `replace` (all occurrences, upstream StringReplace body idiom).
- [ ] Step 2: math helper: `sqrt` (negative → RE_STATUS_INVALID_ARGUMENT per upstream :170).
- [ ] Step 3: collection expression functions over local array/object values: `first`, `last`, `reverse`, `slice` (start,end clamped), `keys`, `values` (object → array of keys/values; document iteration order = insertion order or sorted — pick the local re_value_t object's actual order and pin it). Empty-array first/last → NOT_FOUND (document; check upstream :286/:308 semantics in the brief-fetch and match honestly).
- [ ] Step 4: validation helpers WITHOUT a regex engine: `isNumeric` (full-string numeric per upstream's digit/dot/minus logic — fetch the exact body), `isUrl` (starts_with http://|https:// per :203), `inRange` (numeric bounds inclusive — fetch exact), `isEmail`/`isPhone`: implement documented simplified checks (no rexile regex available; e.g. single-@ + domain-dot + no spaces for isEmail) with the simplification documented in code + conformance note; tests pin the implemented semantics, not upstream's regex.
- [ ] Step 5: date_utils family: NOT implemented (clock/environment-dependent) — add a documented comment at the builtin dispatch listing the family and the reason; now/timestamp (A4) is the bounded equivalent. The metadata-declared-but-never-registered upstream items (StringSplit, StringJoin, padLeft, padRight, Modulo, Power, Ceil, Floor, random-in-math, ArrayMap, ParseDate, AddHours, DateDiff, dayOfYear, ValidateNumeric) are vapor — documented in the conformance row, not implemented.
- [ ] Step 6: tests: each new function's exact semantics (concat mixed types, repeat cap, substring bounds, replace all-occurrences, sqrt negative, first/last empty → NOT_FOUND, slice clamping, keys/values order pin, isNumeric/isUrl/inRange tables, isEmail/isPhone simplified-semantics pins incl. false cases), host override still wins over the new names, purity classification consistent with A4 rules.
- [ ] Step 7: focused suite + full headless + ASan + MSVC green.

## Task D2: example-family coverage tests

**Files:** Test: create `engine/tests/test_rule_engine_example_coverage.c` (+ CMake registration); docs touch only in D4

**Interfaces:** the 29-example inventory (upstream.yml:213-220); existing suites that already cover families (test_rule_engine.c, grl_surface, agenda, backward_ext, tms, stream_*, query_blocks, templates — enumerate from the ledger + CMake).

- [ ] Step 1: build the per-family mapping table (in the test file's header comment): family → upstream examples → local covering suite(s). Families: 01 basic/expressions, 02 RETE core (incl. tms_demo → B1 suites, deffacts → existing row), 03 advanced GRL (accumulate/no-loop/action handlers/templates → A-phase suites; conflict_resolution → salience+recency bounded, B-documented; streaming_with_rules → C suites), 04 streaming → C suites, 09 backward → B suites (proof_graph_cache_demo ↔ B2 stats tests), 10 module system → NO local module system (documented not_applicable with reason), 05/07 performance/parallel → bench regression + B-documented parallel vapor.
- [ ] Step 2: write smoke tests for the families whose machinery is local and real but had no exercise test NAMED for the example family (expect ~5-8 tests: e.g. a fraud_detection-style forward-chain smoke, a grl_query-style backward smoke, a streaming_with_rules-style window+rule smoke over C5's injection, a templates smoke, an action-handlers smoke). Each test names the upstream example(s) it covers in a comment. Do NOT duplicate already-pinned behavior — smoke level only (end-to-end: parse rules → run → assert outcome).
- [ ] Step 3: module-system and parallel/performance families get comment-documented not_applicable entries (no fake tests) — the conformance rows land in D4.
- [ ] Step 4: focused + full + ASan + MSVC green.

## Task D3: Redis runtime verification attempt

**Files:** Modify none (code); Test: existing `redis_roundtrip_when_service_available` + `redis_kind_disabled_without_native_client` (test_rule_engine_stream_ext.c) stay green; a probe script may be added under `engine/scripts/` if genuinely useful (justify; else keep it a documented command in the report + docs)

- [ ] Step 1: probe (document exact commands + outputs in the report): `redis-server`/`redis-cli` on PATH; localhost:6379 connect probe; `RE_TEST_REDIS_URL` env. (Controller's 2026-08-31 probe already found all three absent — re-verify and record.)
- [ ] Step 2: if a service IS available: configure a scratch build tree with RULE_ENGINE_ENABLE_REDIS=ON (requires hiredis — if hiredis is absent, that path dies here, documented), set RE_TEST_REDIS_URL, run the roundtrip test, and report the evidence for D4's row promotion. If unavailable (expected): run the boundary test (`redis_kind_disabled_without_native_client`) to prove the NOT_SUPPORTED surface is green, and record the probe evidence verbatim.
- [ ] Step 3: conformance impact is D4's (the row stays `optional_backend` compile-verified on the unavailable path, with the probe evidence cited — per the spec's one allowed exception).

## Task D4: all-features mapping + docs + phase commit + push

- [ ] Step 1: conformance.yml: `plugins` surface — promote the upstream.yml plugins row (:119-125) from pending → the delivered state (pure helpers as built-ins verified_local; date family out-of-scope-documented; metadata vapor documented); new row or fragment for example-family coverage (29 examples: per-family promoted/not_applicable with test refs); `streaming-redis-state` row gains the D3 probe evidence (stays optional_backend unless D3 found a service); upstream.yml: plugins row + all-features row (:181-187) reworked to the CMake option-set mapping (upstream features {streaming, streaming-redis, backward-chaining} ↔ local always-on + {RULE_ENGINE_ENABLE_REDIS, RULE_ENGINE_ENABLE_C11_PARALLEL, ENGINE_USE_ASAN, ENGINE_USE_UBSAN, ENGINE_BUILD_TESTS} — a documented list, no single switch); examples inventory note (:219-220) updated with the D2 mapping.
- [ ] Step 2: Rule_Engine_Design.md / Rule_Engine_Architecture.md ecosystem paragraphs; Implementation_Status.md dated entry with gate numbers. The `focused_ctest_result`/evidence-baseline lines in conformance.yml (:660-668) updated for the new suites.
- [ ] Step 3: full gate: build-gate clang Debug all-target + `ctest -LE graphics`; build-rule-fresh-asan focused (ASan+UBSan); build-rule-debug MSVC focused; bench regression; `git diff --check`. Known environment noise documented, not "fixed".
- [ ] Step 4: selective commit (rule_engine sources/tests + the 5 doc files + CMakeLists if touched) + push (fetch+merge first if the remote moved; re-run focused + full after merge).
