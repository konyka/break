# World delta wire codec — Task 2 report

## Scope

Base: `598e07bf9d5fb4820f96c31b44c23afb85c83f54` (Task 1 `532326b2` plus approved sparse-rebuild review fix). `origin/master` is `d69e78c471f51a3b5aa7fb9ef4febf8541412244`; no rebase or push was performed.

Task 2 adds edge/fuzz coverage, five design/status supplements, full renderer verification, and focused sanitizer verification. No production codec, session, bridge, core_app, ACK/recovery, or thread behavior was changed. The feature plan’s pre-existing forbidden-name literal was replaced by “遵守项目命名契约” so the repository naming contract can pass without preserving that literal.

## Edge coverage

`engine/tests/test_world_delta_wire.c` increased from 17 to **21 tests; 21/21 passed**:

- `world_delta_wire_multi_entity_component_full_delta_are_canonical`: four entities and three component types; full has 14 records, delta has 10 records and all five record kinds; both rebuild to the expected target ID and complete eight canonical re-encodings.
- `world_delta_wire_wide_u64_fields_survive_repeated_round_trips`: high-bit-set schema/level/base/target IDs and ticks with explicit little-endian byte assertions and 16 canonical re-encodings.
- `world_delta_wire_empty_record_full_message_rebuilds_empty_snapshot`: zero records, exact 60-byte message, empty target rebuild, and eight canonical re-encodings.
- `world_delta_wire_maximum_size_record_round_trips_exactly`: payload of `67,108,864 - 60 - 17 = 67,108,787` bytes; exact 67,108,864-byte message accepted and canonically re-encoded three times, while one payload byte more is rejected as OVER_LIMIT without writing output.

Existing approved coverage remains, including sparse full rebuild, enum validation, REMOVE-with-payload rejection, mixed create/destroy/add/remove/update, malformed/truncated/trailing input, and failure-atomic outputs.

## Fuzz coverage

The repository already had deterministic codec fuzzers and optional Clang libFuzzer targets, so `engine/tests/fuzz_world_delta_wire.c` and matching CMake entries were added rather than inventing a framework.

- Normal deterministic run: **2,000 iterations**, accepted **534**, rejected **1,324**, over-limit **142**.
- ASan+UBSan deterministic run: identical **2,000 / 534 / 1,324 / 142** counts, no sanitizer or leak report.
- TSan deterministic run: identical counts, no race report.
- Opt-in smoke CTest `fuzz_world_delta_wire_smoke`: **1/1 passed**.
- Clang 23.1.5 `libfuzz_world_delta_wire`: **20,000 runs**, no finding; final run used the persisted 9-file build-tree seed corpus and finished with coverage 51 / features 55.

Every payload is copied to an exact-size heap allocation. The harness checks input immutability, zeroed outputs on rejection, and byte-identical re-encoding on acceptance. Cleanup is conditional on successful decode so a hypothetical contract violation cannot free the sentinel output.

## Focused sanitizer verification

All configures used `-DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc`; the pin was verified as `4ab761fc58a9d15970f295e231003c99a7d44df8`.

The focused selection is `test_world_delta_wire`, `test_ecs_replication`, `test_break_replication_session`, `test_break_replication_fragment`, and `test_break_session`: **21 + 35 + 19 + 28 + 43 = 146 inner tests**.

- `engine/build-asan`, `ENGINE_USE_ASAN=ON`, `ENGINE_USE_UBSAN=ON`, `ASAN_OPTIONS=detect_leaks=1:halt_on_error=1`, `UBSAN_OPTIONS=print_stacktrace=1:halt_on_error=1`: **5/5 CTest entries and 146/146 inner tests passed**, no sanitizer or leak report.
- `engine/build-tsan`, `ENGINE_USE_TSAN=ON`, `TSAN_OPTIONS=halt_on_error=1`: **5/5 CTest entries and 146/146 inner tests passed**, no race report.

## Full renderer verification — pre-commit evidence

Both full builds completed successfully. `ENGINE_BUILD_FUZZ_SMOKE=OFF` and `ENGINE_BUILD_LIBFUZZER=OFF` in the ordinary renderer trees; fuzz targets were built explicitly instead.

Vulkan (`engine/build`, `ENGINE_RHI_BACKEND=auto`, effective `vulkan`, multi-backend fallback enabled) registered **471** tests. The first complete run had **464 executed passes, 4 conditional skips, and 3 failures** (215.63 s). The four skips are `test_d3d12_dependency_gate`, `test_core_app_nm_missing`, `test_core_app_nm_unsupported`, and `test_core_app_nm_symbol_missing_unsupported`.

Failures were:

- `test_repo_naming_contract`: the feature plan contained a pre-existing forbidden-name literal. After the documentation-only correction, the focused contract passed **1/1**.
- `test_core_app_contract_compat` and `test_core_app_ctest_config_contract`: their clean `git archive HEAD` configure could not find the not-yet-committed `tests/fuzz_world_delta_wire.c`. This is the same pre-commit archive boundary seen by earlier codec tasks, not a codec test failure. Both must be rerun with the new file in HEAD.

With the new fuzz source and naming correction in HEAD, the final post-commit Vulkan rerun passed all archive and naming contracts: **471 registered, 467 executed passes, 4 conditional skips, 0 failures** (368.76 s). This supersedes the intermediate three-failure result above and completes **471/471 accounted tests**.

OpenGL (`engine/build-gl`, `ENGINE_RHI_BACKEND=opengl`) completed its final committed-source run with **462 registered, 458 executed passes, 4 conditional skips, 0 failures** (355.76 s), completing **462/462 accounted tests**. Its skips are the same four named above (`test_d3d12_dependency_gate`, `test_core_app_nm_missing`, `test_core_app_nm_unsupported`, and `test_core_app_nm_symbol_missing_unsupported`). Neither backend counts the four conditional skips as executed passes; both final suites have zero failures.
