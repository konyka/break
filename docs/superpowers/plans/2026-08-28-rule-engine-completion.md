# Rule Engine Completion Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Complete the five deferred rule-engine areas (GRL method/property + deffacts + templates; recognize–act agenda + persistence + provenance; backward negation/aggregation/strategies/shared proof graph; streaming min/max/first/last + Redis/concurrency boundary; full gate + selective commit/push) per `docs/superpowers/specs/2026-08-28-rule-engine-completion-design.md`.

**Architecture:** C99 static library `rule_engine_core` under `engine/src/rule_engine/`; append-only ABI in `rule_engine.h`; parser → AST → canonical IR (`ir.c`) → executor (`engine.c`) with bounded RETE (`rete.c`), TMS (`tms.c`), backward machine (`backward*.c`), streaming windows (`extensions.c`, `tumbling_session.c`, `stream_correlation.c`). Bounded semantics follow upstream `rust-rule-engine` v1.21.4 (MIT).

**Tech Stack:** C99, CMake + Ninja, clang (primary) and MSVC (matrix), ctest, custom `test_framework.h` harness (`TEST(name)`, `ASSERT_EQ`, `ASSERT_TRUE`).

## Global Constraints

- C99 only; warnings-as-errors posture already set in `engine/CMakeLists.txt` — new code must compile clean under clang AND MSVC.
- Append-only ABI: new struct fields go last; structs with `struct_size` keep it first; new enum values append with explicit numbers; new functions add at the end of their header section. `RE_ABI_VERSION_MINOR` bumps 2u → 3u in Phase 2 when the agenda API lands.
- Evidence rule: no capability bit (`RE_CAP2_*`) is advertised and no conformance row is promoted without an executed local test (`docs/rule_engine_conformance.yml`).
- Status codes: use existing `re_status_t` values only (`RE_STATUS_NOT_SUPPORTED` for unknown method/Redis-off, `RE_STATUS_LIMIT` for caps, `RE_STATUS_INVALID_ARGUMENT`, `RE_STATUS_NOT_FOUND`, `RE_STATUS_PARSE_ERROR`).
- Parser errors are atomic: a bad `deffacts`/template/method construct must leave the whole `re_program_load` failing with no partial rules.
- Line endings: `engine/src/rule_engine/*.c` files use CRLF; match surrounding style (4-space indent, K&R braces).
- Do NOT touch the 21 pre-existing dirty files outside `engine/src/rule_engine/`, `engine/tests/test_rule_engine*`, `engine/src/rule_engine`-related CMake lines, and `docs/`. `git status` before every commit.
- Commits: one commit per phase (not per task), staged selectively by explicit file list. Push only in Phase 5 after the full gate is green.
- Docs updates ride in the same phase commit as the code: `docs/rule_engine_conformance.yml`, `docs/rule_engine_upstream.yml`, `docs/Rule_Engine_Design.md`, `docs/Rule_Engine_Architecture.md`, `docs/Implementation_Status.md`.

## Build / test commands (used in every task)

```bash
# one-time configure (from repo root E:/work/break)
cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug
# build one test target
cmake --build build-gate --target <target_name> --parallel
# run one suite
ctest --test-dir build-gate -R <target_name> --output-on-failure
# run all rule-engine suites (phase gate)
cmake --build build-gate --parallel
ctest --test-dir build-gate -R "rule_engine|backward_machine" --output-on-failure
```

Test registration pattern (engine/CMakeLists.txt ~:774, inside the existing rule-engine test block):

```cmake
add_executable(test_rule_engine_grl_semantics tests/test_rule_engine_grl_semantics.c)
set_property(TARGET test_rule_engine_grl_semantics PROPERTY C_STANDARD 99)
target_include_directories(test_rule_engine_grl_semantics PRIVATE ${TEST_INCLUDE_DIRS})
target_link_libraries(test_rule_engine_grl_semantics PRIVATE rule_engine_core)
add_test(NAME test_rule_engine_grl_semantics COMMAND test_rule_engine_grl_semantics)
```

Test file skeleton (pattern from `engine/tests/test_rule_engine_tms.c`):

```c
#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include <string.h>

static re_string_t text(const char *value) { return (re_string_t){value, strlen(value)}; }
static re_value_t number(int64_t value) { return (re_value_t){RE_VALUE_INT64, {.int64_value = value}}; }

TEST(example) { ... }

int main(void) { RUN_TEST(example); return TEST_RESULT(); }
```

(Check `engine/tests/test_framework.h` for exact macro names — existing suites use `TEST`, `RUN_TEST`, `ASSERT_EQ`, `ASSERT_TRUE`; mirror whatever `test_rule_engine_tms.c` uses for `main`.)

## File Structure

New files:
- `engine/src/rule_engine/templates.c` — rule-template object, substitution, instantiate (Phase 1)
- `engine/src/rule_engine/redis_provider.c` — compiled only when `RULE_ENGINE_ENABLE_REDIS=ON` and hiredis found (Phase 4)
- `engine/tests/test_rule_engine_grl_semantics.c` (Phase 1)
- `engine/tests/test_rule_engine_agenda.c` (Phase 2)
- `engine/tests/test_rule_engine_backward_ext.c` (Phase 3)
- `engine/tests/test_rule_engine_stream_ext.c` (Phase 4)

Modified files:
- `engine/src/rule_engine/rule_engine.h` — new API per phase (append-only), ABI minor bump
- `engine/src/rule_engine/re_internal.h` — engine gains `re_agenda_t *agenda`, `re_proof_graph_t *proof_graph`; program gains deffacts tables; window gains busy flag
- `engine/src/rule_engine/values.c` — `re_facts_set_path`
- `engine/src/rule_engine/parser.c`, `ir.h`, `ir.c`, `ir_validate.c` — method-call action, deffacts forms
- `engine/src/rule_engine/engine.c` — method-call execution, recognize–act loop, provenance read-set merge, agenda ownership
- `engine/src/rule_engine/rete.c` — multi-rule network attachment support
- `engine/src/rule_engine/backward.c`, `query.c` — NOT prefix, strategy dispatch, aggregate API, shared proof graph
- `engine/src/rule_engine/stream_correlation.c`, `extensions.c`, `tumbling_session.c` — new aggregate kinds, busy guards
- `engine/CMakeLists.txt` — test registration, Redis option
- the five docs listed in Global Constraints

---

## Phase 1 — GRL semantics (method/property, deffacts, templates)

### Task 1: Nested write path `re_facts_set_path`

**Files:**
- Modify: `engine/src/rule_engine/values.c` (add after `re_facts_get_path`, ~:237)
- Modify: `engine/src/rule_engine/rule_engine.h` (declare next to `re_facts_get_path`, ~:431)
- Test: `engine/tests/test_rule_engine_grl_semantics.c` (create)

**Interfaces:**
- Consumes: existing `re_facts_get_path`, `re_facts_set`, structured-value internals in values.c (`find_member`, `re_value_handle_t` with `members`/`child`).
- Produces: `re_status_t re_facts_set_path(re_facts_t *facts, re_string_t path, const re_value_t *value);` — exact flat key wins (`re_facts_set`); else walk root fact's structured object member-by-member; final member must exist as scalar; any missing/non-object intermediate → `RE_STATUS_NOT_FOUND`. When `facts->transaction != NULL`, operate on the staged copy exactly like `re_facts_get_path` does. Scalar values only (no object replacement) — `value->type` must not be `RE_VALUE_UNKNOWN`.

- [ ] **Step 1: Write the failing tests** — create `engine/tests/test_rule_engine_grl_semantics.c` with the skeleton above plus:

```c
TEST(set_path_updates_nested_structured_member) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out;
    /* build structured fact Car { speed: 80 } via the structured-value API
       (see structured-value tests in engine/tests/test_rule_engine.c for the
       exact re_value_* builder calls) */
    /* ... build & re_facts_set_value(facts, text("Car"), handle) ... */
    ASSERT_EQ(re_facts_set_path(facts, text("Car.speed"), &number(120)), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 120);
    re_facts_destroy(facts);
}

TEST(set_path_flat_key_shadows_nested_walk) {
    /* facts hold BOTH flat key "Car.speed"=5 and structured Car{speed:80};
       set_path("Car.speed", 9) must update the flat key only */
}

TEST(set_path_missing_intermediate_returns_not_found) {
    /* structured Car{speed:80}; set_path("Car.engine.hp", x) → RE_STATUS_NOT_FOUND */
}
```

- [ ] **Step 2: Register + run to verify failure**

Add the CMake registration block (pattern above) to `engine/CMakeLists.txt` after the `test_rule_engine_tms` block. Run:
`cmake --build build-gate --target test_rule_engine_grl_semantics --parallel` → compile/link error: `re_facts_set_path` undefined. (Implement the tests that don't need it with the flat shadow case using existing APIs.)

- [ ] **Step 3: Implement `re_facts_set_path` in values.c**

Mirror `re_facts_get_path`'s control flow: exact `re_facts_set` attempt first (only if key exists — use `re_facts_get` probe, don't create); else split at first `.`, find root entry's `structured`, walk members with `find_member` until the final segment; write `member->scalar = *value` (respect transaction staging: when `facts->transaction != NULL`, retarget `facts = facts->transaction->staged` first, same as get_path). Return codes per interface contract.

- [ ] **Step 4: Run tests to verify pass** — `ctest --test-dir build-gate -R test_rule_engine_grl_semantics --output-on-failure` → PASS.

- [ ] **Step 5: Route rule actions through it** — in `engine.c`'s action loop (~:410, the `re_facts_set` call site), replace with `re_facts_set_path` so `Car.speed = 120` in `then` writes nested members. Add test:

```c
TEST(rule_action_writes_nested_member) {
    /* rule "R" { when Car.speed > 0 then Car.speed = 120; } with structured Car{speed:80};
       after re_engine_run, re_facts_get_path("Car.speed") == 120 */
}
```

- [ ] **Step 6: Full rule-engine suite stays green** — `ctest --test-dir build-gate -R "rule_engine|backward_machine" --output-on-failure`.

### Task 2: Method-call actions `$Fact.method(...)`

**Files:**
- Modify: `engine/src/rule_engine/parser.c` (then-statement parsing; operand atom for `$Fact.getXxx()`)
- Modify: `engine/src/rule_engine/ir.h` + `ir.c` (new action kind + term kind), `ir_validate.c` (validate)
- Modify: `engine/src/rule_engine/engine.c` (execution in the action loop)
- Test: `engine/tests/test_rule_engine_grl_semantics.c`

**Interfaces:**
- Consumes: Task 1 `re_facts_set_path`; structured member helpers in values.c; registered functions via `re_engine_register_function` (see engine.c:60-82 `re_operand_resolve`).
- Produces:
  - IR: `RE_IR_ACTION_METHOD_CALL` appended to the action-kind enum in `ir.h`; action gains `method_name`/`method_name_size` (receiver = existing `target` term).
  - Grammar: in `then` statements only, `$Ident.method(arg, ...)`; `$` anywhere else → `RE_STATUS_PARSE_ERROR`. Operand form `$Ident.getXxx()` allowed as action RHS value.
  - Execution semantics (in order): `setXxx(v)` (1 arg) → write member `Xxx` (first letter uppercased as-is: `setSpeed`→`Speed`? NO — upstream capitalizes method[3..]; implement exactly: property name = method+3 with first char uppercased) on receiver structured fact via Task 1 machinery; `getXxx()` (0 args) → read member `Xxx` as operand value; `reset()` → clear receiver members; `update()` → no-op OK; otherwise call registered function named `Fact.method`, then bare `method`; none → `RE_STATUS_NOT_SUPPORTED`.

- [ ] **Step 1: Failing tests**

```c
TEST(method_set_updates_structured_member) {
    /* structured Car{Speed:0}; rule: when Car.Speed == 0 then $Car.setSpeed(120);
       run; Car.Speed == 120 */
}
TEST(method_get_operand_reads_member) {
    /* rule: when Car.Speed > 0 then Top = $Car.getSpeed(); run; Top == <Speed value> */
}
TEST(method_reset_clears_members) { /* $Car.reset(); afterwards Car.Speed → NOT_FOUND */ }
TEST(method_unknown_without_handler_not_supported) {
    /* then $Car.fly(1); with no registered fn → re_engine_run returns RE_STATUS_NOT_SUPPORTED */
}
TEST(method_dispatches_registered_function) {
    /* register function "honk"; then $Car.honk(1); → called once with 1 arg */
}
TEST(dollar_outside_method_context_parse_error) {
    /* rule with `$Car` in when → re_program_load → RE_STATUS_PARSE_ERROR */
}
```

- [ ] **Step 2: Build → fail** (parse errors / missing symbols).
- [ ] **Step 3: Implement** — parser: recognize `$` in then-statement start and in operand atom; lower to new IR kinds; ir_validate: method name non-empty, receiver term is a fact path, arg count ≤ 8, `setXxx` arity 1 / `getXxx` arity 0 enforced at execution (return INVALID_ARGUMENT on mismatch); engine.c: `execute_method_call` helper called from the action loop, staged-transaction-safe (all writes go through the active transaction like existing actions).
- [ ] **Step 4: Tests pass.**
- [ ] **Step 5: Full rule-engine suite green.**

### Task 3: deffacts

**Files:**
- Modify: `engine/src/rule_engine/parser.c` (new top-level form beside `defmodule`, ~:749), `ir.h`/`ir.c`/`ir_validate.c` (deffacts tables), `re_internal.h` if program-side storage is needed
- Modify: `engine/src/rule_engine/engine.c` or new code in `facts.c` for clear-all; `rule_engine.h` (API)
- Test: `engine/tests/test_rule_engine_grl_semantics.c`

**Interfaces:**
- Produces:
  - GRL: top-level `deffacts "name" { Path = literal; ... }` — paths are dotted fact paths, values scalar or `[...]` array literals (scalar elements, existing 64-cap). Multiple blocks allowed; duplicate block name in one source → `RE_STATUS_PARSE_ERROR`.
  - `re_status_t re_engine_load_deffacts(re_engine_t *engine, re_facts_t *facts, const char *name_or_null);` — asserts the named set (or all sets when NULL) as plain non-logical facts via `re_facts_set`/`re_facts_set_path`; unknown name → `RE_STATUS_NOT_FOUND`; no program installed → `RE_STATUS_INVALID_ARGUMENT`.
  - `re_status_t re_engine_reset_with_deffacts(re_engine_t *engine, re_facts_t *facts);` — clears working memory (all facts, TMS justifications, and pending agenda state if Phase 2 has landed — guard with `#ifdef`-free internal call that is a no-op when agenda is NULL), then loads all deffacts. No deffacts → just clears.

- [ ] **Step 1: Failing tests**

```c
TEST(deffacts_load_seeds_facts_and_rules_fire) {
    /* source: deffacts "base" { A = 1; B = 2; }
               rule "R" { when A == 1 and B == 2 then C = 3; }
       load program, install, re_engine_load_deffacts(engine, facts, "base"),
       re_engine_run → C == 3 */
}
TEST(deffacts_null_name_loads_all) { /* two blocks; NULL name; both paths present */ }
TEST(deffacts_unknown_name_not_found) { /* → RE_STATUS_NOT_FOUND */ }
TEST(deffacts_duplicate_block_parse_error) { /* two deffacts "x" → RE_STATUS_PARSE_ERROR */ }
TEST(reset_with_deffacts_clears_and_reseeds) {
    /* seed, run a rule deriving D, set Extra = 9 manually;
       re_engine_reset_with_deffacts → Extra/D gone (NOT_FOUND), deffacts paths present */
}
```

- [ ] **Step 2: Build → fail.**
- [ ] **Step 3: Implement** — parser top-level dispatch on `deffacts` keyword (same quoting style as `rule "name"`); IR: append `deffacts` tables (per set: name span, entry range; per entry: path term, literal value term); ir_validate: path non-empty, value scalar/array-of-scalars; engine API + internal `re_facts_clear_all` (also drops justifications — see tms.c for justification storage) + agenda-clear hook (NULL-safe until Phase 2).
- [ ] **Step 4: Tests pass.**
- [ ] **Step 5: Full rule-engine suite green.**

### Task 4: Rule templates

**Files:**
- Create: `engine/src/rule_engine/templates.c`
- Modify: `engine/src/rule_engine/rule_engine.h` (API at end of program section), `engine/CMakeLists.txt` (add templates.c to `rule_engine_core` sources)
- Test: `engine/tests/test_rule_engine_grl_semantics.c`

**Interfaces:**
- Produces (all in rule_engine.h):
```c
typedef struct re_rule_template_t re_rule_template_t;
typedef struct re_template_param_t { re_string_t name; re_string_t value; } re_template_param_t;
re_status_t re_rule_template_create(re_string_t name, re_string_t condition_template,
                                    re_string_t action_template, int32_t salience,
                                    re_rule_template_t **out_template);
re_status_t re_rule_template_param_default(re_rule_template_t *t, re_string_t param,
                                           re_string_t default_value);
re_status_t re_rule_template_instantiate(const re_rule_template_t *t, re_string_t rule_name,
                                         const re_template_param_t *params, size_t param_count,
                                         char *out_text, size_t *inout_text_size);
void re_rule_template_destroy(re_rule_template_t *t);
```
  - Placeholder syntax `{{param}}` in both templates; plain byte substitution (upstream parity — no escaping, no type checks).
  - `instantiate` emits exactly: `rule "<rule_name>" [salience N] {\nwhen\n<cond>\nthen\n<action>;\n}` (omit `[salience N]` when salience == 0); output via caller buffer: `*inout_text_size` carries capacity in, required size out; too small → `RE_STATUS_LIMIT` + required size set.
  - Missing required param (no default, not supplied) → `RE_STATUS_INVALID_ARGUMENT`; supplied param with no matching placeholder → `RE_STATUS_INVALID_ARGUMENT`.
  - Bounded exclusions (document in header comment): no JSON round-trip, no CLIPS-deftemplate schema validator, no engine-side registry — the host parses the emitted text via `re_program_load`.

- [ ] **Step 1: Failing tests**

```c
TEST(template_substitutes_params_and_defaults) {
    /* condition "Speed > {{limit}}", default limit=50; instantiate with no params
       → text contains "Speed > 50"; with param limit=80 → "Speed > 80" */
}
TEST(template_missing_required_param_invalid) { /* no default, not supplied → INVALID_ARGUMENT */ }
TEST(template_unknown_supplied_param_invalid) { /* param "zzz" with no {{zzz}} → INVALID_ARGUMENT */ }
TEST(template_generated_rule_parses_and_fires) {
    /* instantiate into buffer, re_program_load the text, install, seed facts, run,
       derived fact present */
}
TEST(template_buffer_too_small_reports_required_size) { /* → RE_STATUS_LIMIT, size updated */ }
```

- [ ] **Step 2: Build → fail.**
- [ ] **Step 3: Implement `templates.c`** — object holds copied name/cond/action/salience + param-default list; two-pass instantiate (first pass computes required size, second writes); placeholder scan for `{{` … `}}` with param lookup (supplied value first, then default, else error when a placeholder stays unresolved; note: placeholders with no definition are an error only when they match the `{{ident}}` shape — literal `{{` in text is out of scope, documented).
- [ ] **Step 4: Tests pass.**
- [ ] **Step 5: Full rule-engine suite green.**

### Task 5: Phase 1 docs + phase commit

- [ ] **Step 1:** Update docs:
  - `docs/rule_engine_conformance.yml`: promote/add rows for `grl-method-calls` (verified_local, test refs), `nested-property-access` (read existing + write new), `deffacts` (local extension, verified_local), `rule-templates` (verified_local, bounded: no JSON/registry); adjust known_gaps line :252 wording ("method/property calls remain pending" → implemented bounded).
  - `docs/rule_engine_upstream.yml`: expression row note (method-call actions = bounded parity), examples `rete_deffacts_demo`/`rule_templates_demo` → equivalent_behavior via API/local GRL extension.
  - `docs/Rule_Engine_Design.md` + `docs/Rule_Engine_Architecture.md`: new bounded sections; remove the "method/property pending" gap lines.
  - `docs/Implementation_Status.md`: dated entry for Phase 1.
  - Design-doc trim note: in `docs/superpowers/specs/2026-08-28-rule-engine-completion-design.md` §1.4, drop the program-side registry (`re_program_add_template`/`re_program_generate_rules`) — replaced by instantiate-to-text + host `re_program_load` (YAGNI; registry adds no semantics). Edit the spec to match the plan.
- [ ] **Step 2:** `git diff --check` clean; full rule-engine suite green; also run the whole headless suite once: `ctest --test-dir build-gate -LE graphics --output-on-failure`.
- [ ] **Step 3: Commit** (explicit paths only):

```bash
git add engine/src/rule_engine/ engine/tests/test_rule_engine_grl_semantics.c engine/CMakeLists.txt \
        docs/rule_engine_conformance.yml docs/rule_engine_upstream.yml docs/Rule_Engine_Design.md \
        docs/Rule_Engine_Architecture.md docs/Implementation_Status.md \
        docs/superpowers/specs/2026-08-28-rule-engine-completion-design.md \
        docs/superpowers/plans/2026-08-28-rule-engine-completion.md
git status --short   # verify none of the 21 pre-existing dirty files are staged
git commit -m "Complete bounded GRL semantics: method calls, nested properties, deffacts, templates"
```

---

## Phase 2 — recognize–act agenda, persistence, complete provenance

### Task 6: Agenda object core (internal)

**Files:**
- Modify: `engine/src/rule_engine/re_internal.h` (agenda struct + engine field)
- Create: `engine/src/rule_engine/agenda.c` (internal; add to `rule_engine_core` sources in `engine/CMakeLists.txt`)
- Test: `engine/tests/test_rule_engine_agenda.c` (create + register; public-API tests land in Task 8, this task's tests are via existing suites staying green)

**Interfaces:**
- Produces (internal, declared in `re_internal.h`):
```c
typedef struct re_agenda_entry_internal_t {
    size_t rule_index;
    re_fact_id_t premises[8];
    size_t premise_count;
    int32_t salience;
    uint64_t sequence;
} re_agenda_entry_internal_t;
struct re_agenda_t {
    re_agenda_entry_internal_t *pending;  size_t pending_count, pending_cap;
    re_agenda_entry_internal_t *fired;    size_t fired_count, fired_cap; /* refraction keys */
    uint64_t next_sequence;
    int persistent;
    re_allocator_t *allocator; /* or engine allocator copy — match project idiom */
};
re_status_t re_agenda_create_internal(re_allocator_t *alloc, re_agenda_t **out);
void       re_agenda_destroy_internal(re_agenda_t *agenda);
void       re_agenda_clear_pending(re_agenda_t *agenda);          /* end-of-run default */
void       re_agenda_reset(re_agenda_t *agenda);                  /* pending + fired */
int        re_agenda_refracted(const re_agenda_t *agenda, size_t rule_index,
                               const re_fact_id_t *premises, size_t premise_count);
re_status_t re_agenda_push(re_agenda_t *agenda, size_t rule_index, int32_t salience,
                           const re_fact_id_t *premises, size_t premise_count); /* dedups vs pending+fired */
re_status_t re_agenda_mark_fired(re_agenda_t *agenda, const re_agenda_entry_internal_t *entry);
int        re_agenda_pop_highest(re_agenda_t *agenda, re_agenda_entry_internal_t *out); /* 0 when empty */
```
- Refraction key: (rule_index, sorted premise slot/generation pairs). `re_fact_id_t` is `{slot, generation}` — a premise whose fact is re-asserted gets a new generation, so generation change naturally re-activates.
- Engine gains `re_agenda_t *agenda;` (lazy-created) in `re_internal.h`'s engine struct; destroyed in `re_engine_destroy`.

- [ ] **Step 1:** Implement `agenda.c` (growth doubling like other engine arrays; caps enforced by caller via `re_limits_t.max_activations_tracked`).
- [ ] **Step 2:** Wire create/destroy into engine create/destroy; existing suites must stay green: `ctest --test-dir build-gate -R "rule_engine|backward_machine" --output-on-failure`.

### Task 7: Recognize–act loop in `re_engine_run`

**Files:**
- Modify: `engine/src/rule_engine/engine.c` (`re_engine_run` :287-437 rewrite of the main loop)
- Modify: `engine/src/rule_engine/rete.c` (multi-rule attachment), `engine/src/rule_engine/rule_engine.h` (`re_limits_t` append)
- Test: `engine/tests/test_rule_engine_agenda.c`

**Interfaces:**
- Consumes: Task 6 agenda internals; existing match paths (`re_ir_match_rule`, executor parallel bits, RETE activations); existing action-transaction block (engine.c:389-429 — hoist it into a static `fire_activation(...)` helper reused by the loop).
- Produces:
  - `re_limits_t` appends `size_t max_activations_tracked;` (0 → default 1024) — header comment: source-compatible append, zero-init keeps prior behavior.
  - Run loop: `for (;;) { recompute activations of all visible rules → push into agenda (dedup); if (!pop_highest) break; fire; }` bounded by `max_firings` (default keeps existing behavior when 0→engine limit) and `max_agenda_activations` (cumulative per run, as today). End of successful run: `re_agenda_clear_pending` unless `agenda->persistent`; `fired` history is always cleared at run end in non-persistent mode (full reset), kept in persistent mode.
  - RETE: replace the `rule_count == 1` gate (engine.c:311-319) with per-rule networks: engine owns `re_rete_network_t **rete_networks` (array parallel to program rules, NULL for ineligible); invalidation logic at engine.c:307-310 applies per entry. Eligibility = existing `collect` constraint (≤8 AND of `fact <cmp> literal`). Alpha-sharing across rules is **not** done (documented bound — per-rule networks).
  - All existing controls keep working inside the loop: module/agenda-group focus, date bounds, no-loop, lock-on-active, activation-group (all evaluated at activation-computation time each cycle, same predicates as today), cancellation check each cycle, executor parallel match recomputed per cycle when all conditions pure.

- [ ] **Step 1: Failing tests** — `engine/tests/test_rule_engine_agenda.c`:

```c
TEST(chained_rules_reactivate_within_one_run) {
    /* rules: "A" when X == 1 then Y = 1;   "B" when Y == 1 then Z = 1;
       seed X=1; single re_engine_run; EXPECT Z == 1 (today Z stays absent) */
}
TEST(refraction_prevents_self_refire) {
    /* rule "S" salience 5 { when C > 0 then C = C + 0; } — no-op write;
       run terminates; firing count callback fired exactly once */
}
TEST(changed_premise_reactivates_same_rule) {
    /* rule "D" { when N > 0 then Seen += 1; } then host sets N=2 between runs
       in persistent mode… covered in Task 8; here: within one run, another rule
       bumps N, "D" fires again with new premise generation */
}
TEST(max_firings_limit_still_bounds_loop) {
    /* rule "L" { when N > 0 then N = N + 1; } with explicit limits.max_firings=10
       → RE_STATUS_LIMIT, and callback observed exactly 10 firings */
}
TEST(salience_order_preserved_across_cycles) {
    /* rules S10 (salience 10) and S5 (salience 5) both initially active;
       S10's action activates S7 (salience 7); firing order: S10, S7, S5 */
}
```

- [ ] **Step 2: Build → fail** (new-behavior tests fail on the single-pass loop).
- [ ] **Step 3: Implement** — hoist the per-activation firing block into `fire_activation`; rewrite the loop as above; per-rule RETE array lifecycle (create on first eligible run, invalidate on facts switch, destroy in `re_engine_destroy`/`re_engine_install`).
- [ ] **Step 4: New tests pass.**
- [ ] **Step 5: Full rule-engine suite green** — existing tests must pass unmodified except any that asserted single-pass semantics; for each such test, update it and add a one-line conformance note in `docs/rule_engine_conformance.yml` (expected candidates: none known — salience/no-loop/group tests use disjoint facts; verify).

### Task 8: Persistent agenda + inspection API

**Files:**
- Modify: `engine/src/rule_engine/engine.c`, `extensions.c` (`re_engine_agenda` stub :70-74 replaced), `rule_engine.h`, `re_internal.h`
- Test: `engine/tests/test_rule_engine_agenda.c`

**Interfaces:**
- Produces (public, appended in rule_engine.h agenda section):
```c
typedef struct re_agenda_entry_t {
    uint32_t struct_size;
    re_string_t rule_name;
    int32_t salience;
    uint64_t activation_sequence;
    size_t premise_count;
    re_fact_id_t premises[8];
} re_agenda_entry_t;
re_status_t re_engine_set_agenda_persistent(re_engine_t *engine, int enabled);
/* re_engine_agenda(engine, &out) — existing declaration; now returns the
   engine-owned agenda (created lazily) instead of RE_STATUS_NOT_SUPPORTED.
   re_agenda_destroy stays a documented no-op for engine-owned instances. */
size_t re_agenda_count(const re_agenda_t *agenda);
re_status_t re_agenda_peek(const re_agenda_t *agenda, size_t index, re_agenda_entry_t *out_entry);
```
- `RE_ABI_VERSION_MINOR` 2u → 3u; advertise `RE_CAP2_AGENDA_RETE` in `re_engine_capabilities_v2` now that tests exist.
- Persistence semantics: with `persistent=1`, `pending` and `fired` survive `re_engine_run`; premise generation change re-activates (refraction key mismatch); TMS retraction of a premise cancels pending entries containing it (hook `re_tms_remove_premise` path). A run ending in `RE_STATUS_LIMIT`/`RE_STATUS_CANCELLED` also preserves `pending`+`fired` when persistent (that is how unfired activations carry into the next run); in non-persistent mode every exit path fully resets the agenda.

- [ ] **Step 1: Failing tests**

```c
TEST(agenda_api_replaces_not_supported_stub) {
    /* re_engine_agenda → OK, count 0 before run */
}
TEST(persistent_agenda_refires_only_on_premise_change) {
    /* persistent on; rule "P" { when N > 0 then Hits += 1; } seed N=1; run → Hits==1;
       run again without changes → Hits still 1 (refraction across runs);
       re_facts_set N=2; run → Hits == 2 (new generation re-activates) */
}
TEST(agenda_peek_reports_pending_in_salience_order) {
    /* persistent on; max_firings=1 with two active rules → after run, count==1,
       peek(0) is the lower-salience rule with its premise ids */
}
TEST(tms_retraction_cancels_pending_activation) {
    /* persistent on; logically-derived premise retracted between runs →
       pending activation for the dependent rule gone (count drops) */
}
TEST(non_persistent_default_unchanged) { /* two runs, no persistence → identical fire counts */ }
```

- [ ] **Step 2: Build → fail.**
- [ ] **Step 3: Implement** — public entry struct mapping, persistence flags, TMS cancellation hook, capability advertisement.
- [ ] **Step 4: Tests pass.**
- [ ] **Step 5: Full suite green.**

### Task 9: Complete provenance (condition read-set)

**Files:**
- Modify: `engine/src/rule_engine/ir_eval.c` (record fact reads), `engine.c` (merge into premises), `re_internal.h` (read-set storage on eval state)
- Test: `engine/tests/test_rule_engine_agenda.c`

**Interfaces:**
- Produces (internal): eval state gains `re_string_t read_paths[8]; size_t read_count;` — every `re_facts_get_path` hit inside condition evaluation records the path (dedup, cap 8, overflow silently stops recording — documented bound: conditions reading >8 distinct fact paths get first-8 provenance).
- engine.c firing path: premises = RETE lineage ∪ read-set-resolved fact ids (dedup by slot/generation; cap 8 total). Path→id resolution via existing fact lookup. Union feeds the existing `re_facts_insert_logical` / `re_facts_justification_add` calls (engine.c:405-416) — so derived facts from the **linear evaluator** path now carry producer+premises too.

- [ ] **Step 1: Failing tests**

```c
TEST(linear_path_derivation_records_provenance) {
    /* two rules so RETE per-rule attach does not apply, e.g. rule with arithmetic
       in condition (not RETE-eligible): rule "Arith" { when A + B > 1 then D = 9; }
       after run: re_facts_provenance_get(D) → producer "Arith", premises = {A,B} */
}
TEST(provenance_cascade_retracts_linear_derived) {
    /* same setup; retract A → D auto-retracted (RE_STATUS_NOT_FOUND) */
}
TEST(multi_producer_justifications_accumulate) {
    /* two rules both derive D from different premises;
       re_facts_justification_count(D) == 2 */
}
```

- [ ] **Step 2: Build → fail.**
- [ ] **Step 3: Implement** — read-set recording in ir_eval (both `RE_IR_TERM_FACT` and EXISTS/FORALL reads), merge at firing.
- [ ] **Step 4: Tests pass.**
- [ ] **Step 5: Full suite green** (watch: TMS suite — linear-path logical inserts now cascade; behavior is intended, but confirm no existing test asserted the absence of lineage on the linear path).

### Task 10: Phase 2 docs + phase commit

- [ ] **Step 1:** Docs: conformance rows for recognize–act cycle, persistent agenda (verified_local), provenance-on-linear-path; known_gaps `rete-ul-tms-persistent-agenda` (:254) reworded — persistent agenda + bounded refraction now local-verified, full RETE-UL stays unsupported; Architecture.md "Deferred explicitly" list (:46-60) updated; Design.md agenda/provenance sections updated; Implementation_Status.md dated entry.
- [ ] **Step 2:** `git diff --check`; full headless suite `ctest --test-dir build-gate -LE graphics --output-on-failure`.
- [ ] **Step 3: Commit:**

```bash
git add engine/src/rule_engine/ engine/tests/test_rule_engine_agenda.c engine/CMakeLists.txt \
        docs/rule_engine_conformance.yml docs/rule_engine_upstream.yml docs/Rule_Engine_Design.md \
        docs/Rule_Engine_Architecture.md docs/Implementation_Status.md
git status --short
git commit -m "Add recognize-act agenda with bounded persistence and linear-path provenance"
```

---

## Phase 3 — backward: negation, aggregation, strategies, shared proof graph

### Task 11: Query-level `NOT` (negation-as-failure)

**Files:**
- Modify: `engine/src/rule_engine/backward.c` (goal dispatch `re_backward_machine_dispatch` :943-1085) and/or `query.c`
- Test: `engine/tests/test_rule_engine_backward_ext.c` (create + register in `engine/CMakeLists.txt`)

**Interfaces:**
- Consumes: existing bounded query path `re_engine_query_bounded` → `re_backward_machine_run`.
- Produces: goal strings with prefix `NOT ` (case-sensitive, followed by whitespace) wrap the remaining goal as negation-as-failure: subgoal provable (≥1 solution) → query result `RE_QUERY_DISPROVED`, zero solutions; subgoal unprovable → `RE_QUERY_PROVED` with exactly one solution carrying **empty** bindings and a proof whose trace names the negated goal. Bounded: prefix form only (`!(...)` excluded, documented); no stratification (upstream parity); nested `NOT NOT` allowed (two prefixes).

- [ ] **Step 1: Failing tests**

```c
TEST(query_not_succeeds_when_subgoal_unprovable) {
    /* facts hold no Banned fact; query "NOT Banned == true" → RE_QUERY_PROVED,
       re_query_solution_count == 1, re_proof_binding_count == 0 */
}
TEST(query_not_fails_when_subgoal_provable) {
    /* Banned == true present; same query → RE_QUERY_DISPROVED, 0 solutions */
}
TEST(query_not_with_rule_goal) {
    /* rule "Derive" { when Flag == 1 then Derived = 1; } ... query
       "NOT goal(\"Derive\")" — provable only when Flag != 1 path absent;
       assert both branches */
}
```

- [ ] **Step 2: Build → fail.**
- [ ] **Step 3: Implement** — strip prefix in dispatch; run the subgoal through the existing machine with `max_solutions=1`; map outcomes; construct the empty-binding proof via the existing `make_proof` machinery.
- [ ] **Step 4: Tests pass.**
- [ ] **Step 5: Full rule-engine suite green.**

### Task 12: Query aggregation API

**Files:**
- Modify: `engine/src/rule_engine/backward.c` or new small `aggregate_query.c`; `rule_engine.h` (enum append + API)
- Test: `engine/tests/test_rule_engine_backward_ext.c`

**Interfaces:**
- Produces:
  - Enum append: `RE_ACCUM_FIRST = 6`, `RE_ACCUM_LAST = 7` in `re_accumulator_kind_t`.
  - `re_status_t re_engine_query_aggregate(re_engine_t *engine, re_facts_t *facts, re_accumulator_kind_t kind, re_string_t field, re_string_t pattern, re_value_t *out_value);`
    - `pattern` = ordinary goal string (e.g. `"Score == S"` binds `S` per solution); `field` names the binding to fold (e.g. `"S"`); `field.data == NULL` allowed only for `RE_ACCUM_COUNT`.
    - Runs the bounded query with `max_solutions` = 1024 (documented cap; exceeding → `RE_STATUS_LIMIT`), folds in DFS solution order.
    - Empty solution set: COUNT → int64 0 (OK); all other kinds → `RE_STATUS_NOT_FOUND`.
    - Non-numeric binding value for SUM/AVERAGE/MIN/MAX → `RE_STATUS_INVALID_ARGUMENT`. Result type: COUNT → INT64; AVERAGE → DOUBLE; SUM/MIN/MAX follow input (all-int64 → INT64, any double → DOUBLE); FIRST/LAST → the binding value copied.

- [ ] **Step 1: Failing tests**

```c
TEST(aggregate_count_counts_solutions) { /* 3 facts matching pattern → int64 3 */ }
TEST(aggregate_sum_and_average)          { /* sums bindings of S: 10+20+30 → 60 / 20.0 */ }
TEST(aggregate_min_max_first_last)       { /* order-sensitive first/last == DFS order */ }
TEST(aggregate_empty_set_semantics)      { /* count → 0 OK; sum → RE_STATUS_NOT_FOUND */ }
TEST(aggregate_non_numeric_rejected)     { /* string binding with SUM → INVALID_ARGUMENT */ }
```

- [ ] **Step 2: Build → fail.**
- [ ] **Step 3: Implement** — fold loop over `re_query_next` proofs via `re_proof_binding_get`; reuse the numeric coercion rules from `re_accumulator_evaluate` (advanced.c:35-54).
- [ ] **Step 4: Tests pass.**
- [ ] **Step 5: Full suite green.**

### Task 13: Search strategies (DFS / BFS / iterative)

**Files:**
- Modify: `engine/src/rule_engine/rule_engine.h` (`re_query_options_t` append + strategy enum), `engine/src/rule_engine/backward.c` (dispatch wrapper)
- Test: `engine/tests/test_rule_engine_backward_ext.c`

**Interfaces:**
- Produces:
```c
enum { RE_QUERY_STRATEGY_DEPTH_FIRST = 0u, RE_QUERY_STRATEGY_BREADTH_FIRST = 1u,
       RE_QUERY_STRATEGY_ITERATIVE = 2u };
/* re_query_options_t appends: uint32_t strategy; uint32_t disable_shared_proof_graph; */
```
  - `struct_size <` new tail ⇒ defaults 0/0: DFS, proof sharing ON (Task 14).
  - BFS = iterative-deepening: run the existing DFS machine with `max_depth` = 1, 2, 4, 8, … doubling up to the configured `max_depth` (default 64); stop at the first cap yielding ≥1 solution; that pass's solutions are the result. ITERATIVE behaves identically (documented alias of upstream parity). Backward queries execute no actions, so re-probing is side-effect free. Probe cap: 32 doublings → `RE_STATUS_LIMIT`.
  - Invalid strategy value → `RE_STATUS_INVALID_ARGUMENT`.

- [ ] **Step 1: Failing tests**

```c
TEST(bfs_finds_shallowest_proof_first) {
    /* goal provable via a 1-step rule and a 3-step chain; with
       RE_QUERY_STRATEGY_BREADTH_FIRST and max_solutions large, first proof's
       trace length == 1; with default DFS the 3-step trace comes first
       (order them in source so DFS dives deep) */
}
TEST(default_strategy_is_dfs_unchanged) { /* struct_size = old size → DFS results identical to today */ }
TEST(invalid_strategy_rejected) { /* strategy=99 → RE_STATUS_INVALID_ARGUMENT */ }
```

- [ ] **Step 2: Build → fail.**
- [ ] **Step 3: Implement** the deepening wrapper in dispatch; zero-initialize absent tail via `struct_size` check (pattern already used elsewhere in the engine for versioned structs).
- [ ] **Step 4: Tests pass.**
- [ ] **Step 5: Full suite green.**

### Task 14: Shared proof graph

**Files:**
- Modify: `engine/src/rule_engine/re_internal.h` (graph struct + engine field), `backward.c` (consult/insert/invalidation), `rule_engine.h` (stats API)
- Test: `engine/tests/test_rule_engine_backward_ext.c`

**Interfaces:**
- Produces:
  - Internal `re_proof_graph_t`: 64-entry table; entry = { copied goal string, `re_facts_t *facts` identity, fact-mutation generation stamp, cloned solution proofs (the internal proof representation from `make_proof`), hit/miss counters }. On full → clear-all (documented). Consulted in `re_engine_query_bounded` before running the machine; on success the produced proofs are cloned into the graph. Query result serves cloned proofs (immutable, caller destroys as usual).
  - Generation: reuse the mutation counter that backs query self-invalidation (backward.c:144-158 `invalidate`) — find it in `re_internal.h`'s facts struct; entry is stale when `facts`' current generation != stamp.
  - Opt-out: `re_query_options_t.share_proof_graph == 0`… wait: default 0 must mean **sharing ON** (old struct_size lacks the field). Contract: field absent (small struct_size) → ON; explicit 0 → ON; explicit 1 → OFF. Document the inverted flag as `disable_proof_graph_sharing` instead — rename the field to avoid double-negative: `uint32_t disable_shared_proof_graph;` (0/absent = shared ON, 1 = off). Update Task 13's append comment accordingly: appended fields are `uint32_t strategy; uint32_t disable_shared_proof_graph;`.
  - `re_status_t re_engine_proof_graph_stats(const re_engine_t *engine, uint64_t *out_hits, uint64_t *out_misses);`

- [ ] **Step 1: Failing tests**

```c
TEST(shared_graph_second_query_hits_cache) {
    /* run query Q; stats → misses==1; run identical Q again → hits==1;
       proofs identical bindings/trace */
}
TEST(mutation_invalidates_cached_proof) {
    /* query Q cached; mutate a fact (re_facts_set); query Q again → miss,
       fresh proofs reflecting new facts */
}
TEST(disable_flag_bypasses_cache) {
    /* disable_shared_proof_graph=1 twice → misses==2, hits==0 */
}
TEST(different_facts_objects_do_not_share) { /* same engine, two facts sets → both miss */ }
```

- [ ] **Step 2: Build → fail.**
- [ ] **Step 3: Implement** — clone/destroy helpers for internal proofs; consult/insert in `re_engine_query_bounded`; engine destroy releases the graph.
- [ ] **Step 4: Tests pass.**
- [ ] **Step 5: Full suite green.**

### Task 15: Phase 3 docs + phase commit

- [ ] **Step 1:** Docs: conformance rows for query-level NOT, query aggregation, search strategies, shared proof graph (all verified_local with test refs); known_gaps `backward-arbitrary-unification-proof-sharing` (:255) reworded — shared proof graph now bounded-local, arbitrary unification stays unsupported; upstream.yml backward row (:140) updated; Design.md/Architecture.md backward sections updated; Implementation_Status.md dated entry.
- [ ] **Step 2:** `git diff --check`; full headless suite.
- [ ] **Step 3: Commit:**

```bash
git add engine/src/rule_engine/ engine/tests/test_rule_engine_backward_ext.c engine/CMakeLists.txt \
        docs/rule_engine_conformance.yml docs/rule_engine_upstream.yml docs/Rule_Engine_Design.md \
        docs/Rule_Engine_Architecture.md docs/Implementation_Status.md
git status --short
git commit -m "Extend backward queries with negation, aggregation, strategies, shared proof graph"
```

---

## Phase 4 — streaming aggregation, Redis boundary, concurrency boundary

### Task 16: Stream aggregation min/max/first/last

**Files:**
- Modify: `engine/src/rule_engine/rule_engine.h` (`re_stream_aggregate_kind_t` append, `re_stream_aggregate_result_t` append), `engine/src/rule_engine/stream_correlation.c` (`re_stream_window_aggregate_v1` :24-53)
- Test: `engine/tests/test_rule_engine_stream_ext.c` (create + register)

**Interfaces:**
- Produces:
  - Enum append: `RE_STREAM_AGGREGATE_MIN = 4`, `RE_STREAM_AGGREGATE_MAX = 5`, `RE_STREAM_AGGREGATE_FIRST = 6`, `RE_STREAM_AGGREGATE_LAST = 7`.
  - Result struct appends: `double minimum; double maximum; re_value_t first; re_value_t last;` (`struct_size` versioning already in place).
  - Semantics over the retained, type/key-filtered event set (same filter as count/sum): MIN/MAX fold numeric event values (non-numeric event skipped, matching sum/avg tolerance — check existing behavior and mirror it; if existing code errors, error identically); FIRST/LAST = value of the earliest/latest retained event by timestamp (insertion order breaks ties). Empty filtered set → `RE_STATUS_NOT_FOUND` for all four (COUNT stays 0/OK as today).

- [ ] **Step 1: Failing tests**

```c
TEST(stream_min_max_over_filtered_events) {
    /* sliding window; record values 5, 2, 9 of type "T"; MIN → 2, MAX → 9,
       count/sum/avg unchanged */
}
TEST(stream_first_last_by_timestamp) {
    /* record ts=100 value "a", ts=50 value "b" (out of order insert);
       FIRST → "b", LAST → "a" */
}
TEST(stream_new_kinds_empty_window_not_found) { /* MIN/MAX/FIRST/LAST → RE_STATUS_NOT_FOUND */ }
TEST(stream_aggregate_result_struct_size_compat) {
    /* pass struct_size of the OLD struct → new fields untouched, old fields correct */
}
```

- [ ] **Step 2: Build → fail.**
- [ ] **Step 3: Implement** in `stream_correlation.c`; honor `struct_size` on write-out (only write fields the caller's struct_size covers).
- [ ] **Step 4: Tests pass.**
- [ ] **Step 5: Full suite green.**

### Task 17: Redis state provider boundary

**Files:**
- Modify: `engine/CMakeLists.txt` (option + discovery + conditional source)
- Create: `engine/src/rule_engine/redis_provider.c`
- Modify: `engine/src/rule_engine/extensions.c` (:329 — route `RE_STATE_PROVIDER_REDIS` to the native adapter when compiled in, else keep `RE_STATUS_NOT_SUPPORTED`)
- Test: `engine/tests/test_rule_engine_stream_ext.c` (skip-guarded integration case)

**Interfaces:**
- Consumes: `re_state_provider_t` v1 vtable as implemented by the in-memory provider (`memory_provider.c` — mirror its function signatures exactly).
- Produces:
  - CMake: `option(RULE_ENGINE_ENABLE_REDIS "Enable native Redis state provider" OFF)`; when ON: `find_path(HIREDIS_INCLUDE_DIR hiredis/hiredis.h)` + `find_library(HIREDIS_LIBRARY hiredis)`; both found → compile `redis_provider.c`, define `RE_HAS_HIREDIS`, link the library; otherwise `message(STATUS ...)` and force the option OFF (cache `FORCE`). Missing client ⇒ disabled — never a silent fallback (documented boundary).
  - Adapter (compiled only with `RE_HAS_HIREDIS`): sync hiredis API (upstream parity — upstream uses a synchronous connection); key = `<prefix>:<name>` (prefix from provider options/connection string `redis://host:port[/db]` + optional `?prefix=`); value = raw bytes; TTL via `PSETEX`, plain set via `SET`, get via `GET`, delete via `DEL`; connect/disconnect in create/destroy; command failure → provider error `RE_PROVIDER_ERROR_UNAVAILABLE` with message.
  - Without `RE_HAS_HIREDIS`, `RE_STATE_PROVIDER_REDIS` → `RE_STATUS_NOT_SUPPORTED` (existing tests unchanged).

- [ ] **Step 1: Failing/verification tests**

```c
TEST(redis_kind_disabled_without_native_client) {
#if defined(RE_TEST_HAS_HIREDIS)
    /* compiled with hiredis: provider create without a server →
       RE_PROVIDER_ERROR_UNAVAILABLE surfaced (or skip if RE_TEST_REDIS_URL unset) */
#else
    /* RE_STATE_PROVIDER_REDIS → RE_STATUS_NOT_SUPPORTED (already covered by the
       existing suite — this test documents the boundary in the new file) */
#endif
}
TEST(redis_roundtrip_when_service_available) {
    /* const char *url = getenv("RE_TEST_REDIS_URL"); if (!url) return (skip, recorded
       as unavailable evidence, not a pass); else create provider, set/get/delete
       roundtrip, TTL honored */
}
```

- [ ] **Step 2: Configure matrix** — default configure keeps option OFF; `cmake -S engine -B build-redis-check -G Ninja -DRULE_ENGINE_ENABLE_REDIS=ON` must succeed with the STATUS message whether or not hiredis is present (no hard error).
- [ ] **Step 3: Implement.**
- [ ] **Step 4: Tests pass (skip path verified locally).**
- [ ] **Step 5: Full suite green in both configure modes.**

### Task 18: Concurrency boundary hardening

**Files:**
- Modify: `engine/src/rule_engine/extensions.c`, `tumbling_session.c`, `stream_correlation.c` (in-use guards), `rule_engine.h` (contract comment), `engine/tests/test_rule_engine_executor_stress.c` (extend; only built when `RULE_ENGINE_ENABLE_C11_PARALLEL=ON`)
- Test: `engine/tests/test_rule_engine_stream_ext.c` (single-thread flag checks) + executor stress (threaded)

**Interfaces:**
- Produces:
  - Window/provider gains an internal `busy` flag: `record_v1`/`aggregate_v1`/`correlate_v1`/`snapshot`/`restore` set-and-check; re-entrant/concurrent entry → `RE_STATUS_BUSY` (mirrors the facts `running`/`mutation_allowed` flag idiom in `re_internal.h`:44-51).
  - Header contract comment on `re_engine_t`: "engine, facts, windows and providers are single-threaded; mutating during `re_engine_run` returns `RE_STATUS_BUSY`; the optional C11 executor evaluates read-only conditions in workers" (aligns with Architecture.md:259-263).
  - Executor stress: add a case where a worker-side condition attempts no mutation and the host thread's mutation attempt during run observes `RE_STATUS_BUSY` (orchestrate via the existing public flags/callbacks — do not add real data races; the C11 stress harness pattern is already in that file).

- [ ] **Step 1: Failing tests** — `record_during_snapshot_returns_busy` style flag checks (drive via callback reentry: a subscriber callback that calls `re_stream_window_record_v1` on the same window → `RE_STATUS_BUSY`).
- [ ] **Step 2: Build → fail/pass audit** — first audit which paths already guard; write tests only for genuinely missing guards (TDD on real gaps, not ceremony).
- [ ] **Step 3: Implement guards.**
- [ ] **Step 4: Tests pass; hardening preset builds (asan/ubsan) compile the stress test.**
- [ ] **Step 5: Full suite green.**

### Task 19: Phase 4 docs + phase commit

- [ ] **Step 1:** Docs: conformance rows for stream min/max/first/last (verified_local), Redis boundary (native adapter = optional_backend with discovery rule; `native-redis` known_gap :257 updated from blocked → optional_backend-with-adapter when compiled, keeping the no-fallback rule), concurrency boundary contract; Design.md streaming/Redis sections (:205-213) updated; upstream.yml streaming rows (:147-176) updated; Implementation_Status.md dated entry.
- [ ] **Step 2:** `git diff --check`; full headless suite.
- [ ] **Step 3: Commit:**

```bash
git add engine/src/rule_engine/ engine/tests/test_rule_engine_stream_ext.c \
        engine/tests/test_rule_engine_executor_stress.c engine/CMakeLists.txt \
        docs/rule_engine_conformance.yml docs/rule_engine_upstream.yml docs/Rule_Engine_Design.md \
        docs/Rule_Engine_Architecture.md docs/Implementation_Status.md
git status --short
git commit -m "Extend streaming aggregates and harden Redis/concurrency boundaries"
```

---

## Phase 5 — full gate + delivery

### Task 20: Full gate

- [ ] **Step 1:** Clang/Ninja Debug (fresh dir): `cmake -S engine -B build-gate -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug` → build all + `dxx_break` → `ctest --test-dir build-gate -LE graphics --output-on-failure` — all green.
- [ ] **Step 2:** MSVC matrix: `cmake -S engine -B build-gate-msvc -G Ninja -DCMAKE_C_COMPILER=cl -DCMAKE_BUILD_TYPE=Debug` and `…-Release`; build + `ctest -LE graphics` in each — all green.
- [ ] **Step 3:** Sanitizer presets: `cmake --preset hardening-asan` / `hardening-ubsan` (run from `engine/`, clang) → build → full `ctest` (includes `rule_engine_fuzz_smoke` LABELS hardening and `test_rule_engine_executor_stress`) — all green. A configure/runtime failure of the sanitizer itself is unavailable evidence, not a pass (Build_Guide.md:104-106) — report honestly if so.
- [ ] **Step 4:** Bench regression: build `rule_engine_bench`, then `cmake -DBENCH=<build>/rule_engine_bench.exe -DTHRESHOLD=engine/scripts/rule_engine_bench_thresholds.txt -DRUNS=3 -P engine/scripts/rule_engine_bench_regression.cmake` — under thresholds.
- [ ] **Step 5:** `git diff --check` on the full diff vs the pre-work HEAD (commit `2fee885`).

### Task 21: Selective commit + push

- [ ] **Step 1:** `git status --short` — confirm the only uncommitted paths are the 21 pre-existing non-rule-engine files (+ `Testing/` log) and nothing else; confirm phase commits touched only rule-engine sources/tests/CMake/docs.
- [ ] **Step 2:** `git log --oneline 2fee885..HEAD` — expect: design spec + 4 phase commits (+ plan commit).
- [ ] **Step 3:** `git push origin master`.
- [ ] **Step 4:** Report: pushed range, gate evidence per step, and the deliberately untouched dirty files.

---

## Self-review notes (filled by plan author)

- Spec coverage: items 1→Tasks 1-5, 2→6-10, 3→11-15, 4→16-19, 5→20-21. Design-doc §1.4 registry trimmed (Task 4 implements instantiate-to-text only; Task 5 Step 1 edits the spec to match).
- Type consistency anchors: `re_facts_set_path` (Task 1) consumed by Tasks 2/3; agenda internals (Task 6) consumed by 7/8; `re_query_options_t` appended exactly once (Task 13) with fields `strategy`, `disable_shared_proof_graph` (Task 14 consumes); `RE_ACCUM_FIRST/LAST` (Task 12) are the query-aggregate kinds, `RE_STREAM_AGGREGATE_MIN/MAX/FIRST/LAST` (Task 16) are the stream kinds — do not conflate.
- `re_limits_t` and `re_run_options_t` have no `struct_size`; appending `max_activations_tracked` is source-compatible only — noted in header comments and conformance docs.
