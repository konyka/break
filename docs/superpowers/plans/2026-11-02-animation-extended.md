# Animation Extended Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add bounded morph evaluation, named facial curves, validated versioned TRS compression, and a real morph-to-skinning data path without changing existing animation APIs.

**Architecture:** Three independent C11 modules own morph, facial, and codec behavior. Caller-owned fixed-capacity buffers keep hot paths allocation-free; a 64-byte SkinnedVertex adapter feeds the existing CPU skinner. All public operations validate before committing output.

**Tech Stack:** C11, CMake/CTest, `test_framework.h`, existing `math/math.h`, `AnimClip`, `lod_skin_positions`; no new dependencies.

## Global Constraints

- Work only in `.worktrees/cry-animation` on `cry-wave1-animation`; never push or create a PR.
- Do not modify ragdoll/physics or `docs/Implementation_Status.md`.
- Preserve existing animation APIs/tests; use fixed capacities and no hot-path allocation.
- Every production behavior follows observed RED→GREEN; builds use `-j3`.
- Invalid external data is rejected without partial output; corruption, non-finite values, capacity, and round-trip protection receive mutation checks.
- This is not a claim of complete Cry animation equivalence.

---

### Task 1: Bounded morph targets and weight evaluation

**Files:**
- Create: `engine/src/animation/morph.h`
- Create: `engine/src/animation/morph.c`
- Create: `engine/tests/test_anim_morph.c`
- Modify: `engine/CMakeLists.txt` (engine source list and focused test targets)

**Interfaces:**
- Produces: `AnimMorphSet`, `anim_morph_init`, `anim_morph_add_target`, `anim_morph_evaluate`.
- Consumes: caller-owned `Vec3` deltas and packed xyz arrays; no renderer dependency.

- [ ] **Step 1: Write the failing weighted-evaluation test**

```c
TEST(morph_evaluates_bounded_weight_sum) {
    AnimMorphSet set;
    ASSERT_TRUE(anim_morph_init(&set, 1u));
    const Vec3 delta[1] = {{{2.0f, 4.0f, -2.0f}}};
    ASSERT_TRUE(anim_morph_add_target(&set, "smile", delta));
    const f32 base[3] = {1.0f, 2.0f, 3.0f};
    const f32 weights[1] = {0.25f};
    f32 out[3] = {0.0f, 0.0f, 0.0f};
    ASSERT_TRUE(anim_morph_evaluate(&set, base, weights, 1u, out));
    ASSERT_FLOAT_EQ(out[0], 1.5f, 1e-6f);
    ASSERT_FLOAT_EQ(out[1], 3.0f, 1e-6f);
    ASSERT_FLOAT_EQ(out[2], 2.5f, 1e-6f);
}
```

- [ ] **Step 2: Run RED**

Run: `cmake --build build-animation-normal --target test_anim_morph -j3 && ./build-animation-normal/test_anim_morph`  
Expected: compile/link failure because the new API and implementation do not exist; after the API skeleton exists, the weighted assertion must fail rather than being hard-coded green.

- [ ] **Step 3: Implement the minimal fixed-capacity weighted sum**

```c
bool anim_morph_evaluate(const AnimMorphSet *set, const f32 *base_xyz,
                         const f32 *weights, u32 weight_count, f32 *out_xyz) {
    if (!set || !base_xyz || !out_xyz || weight_count != set->target_count ||
        (weight_count && !weights)) return false;
    /* First pass validates every source and computed result; second pass writes. */
    for (u32 pass = 0; pass < 2u; ++pass) {
        for (u32 v = 0; v < set->vertex_count; ++v) {
            for (u32 a = 0; a < 3u; ++a) {
                f32 value = base_xyz[(usize)v * 3u + a];
                for (u32 t = 0; t < set->target_count; ++t)
                    value += set->targets[t].position_deltas[v].e[a] * weights[t];
                if (!isfinite(value)) return false;
                if (pass) out_xyz[(usize)v * 3u + a] = value;
            }
        }
    }
    return true;
}
```

The complete implementation must also reject non-finite/out-of-range weights before either pass and validate target names/deltas at insertion.

- [ ] **Step 4: Add separate RED→GREEN edge tests**

```c
TEST(morph_rejects_nonfinite_weight_without_touching_output) {
    /* Use a one-target set, weight NAN and an output filled with 7.0f. */
    /* Expect false and all output bytes unchanged. */
}

TEST(morph_rejects_thirty_third_target) {
    /* Add 32 valid targets, then expect the 33rd insertion to return false
       while target_count remains 32. */
}

TEST(morph_empty_set_copies_base) {
    /* A zero-target set with finite base returns an exact xyz copy. */
}
```

Run the focused test after each added behavior. Expected RED is the missing rejection/copy behavior; GREEN requires all prior morph tests to remain green.

- [ ] **Step 5: Run normal focused regression**

Run: `ctest --test-dir build-animation-normal --output-on-failure -R '^(test_anim_morph|test_animation)$'`  
Expected: both pass with no warnings or sanitizer diagnostics.

---

### Task 2: Feed morphed positions into real skinning input

**Files:**
- Modify: `engine/src/animation/morph.h`
- Modify: `engine/src/animation/morph.c`
- Modify: `engine/tests/test_anim_morph.c`
- Modify: `engine/CMakeLists.txt` (link `lod_skin.c`, `lod_cache.c`, `lod_gen.c`, and `meshopt_c` to `test_anim_morph`)

**Interfaces:**
- Produces: `ANIM_MORPH_SKIN_VERTEX_BYTES == 64` and `anim_morph_evaluate_skinned(...)`.
- Consumes: existing `lod_skin_positions(const f32 *, u32, const Mat4 *, u32, f32 *)`.

- [ ] **Step 1: Write the failing real-skinner integration test**

```c
typedef struct {
    f32 pos[3]; f32 normal[3]; f32 uv[2]; u32 joints[4]; f32 weights[4];
} TestSkinVertex;
_Static_assert(sizeof(TestSkinVertex) == ANIM_MORPH_SKIN_VERTEX_BYTES,
               "skin vertex layout");

TEST(morphed_vertex_is_consumed_by_existing_skinner) {
    /* Base pos=(1,0,0), delta=(0,2,0), weight=0.5 => pos=(1,1,0).
       A real skin matrix translating x by 3 must therefore yield (4,1,0),
       not the unmorphed (4,0,0). Preserve all non-position attributes. */
}
```

- [ ] **Step 2: Run RED**

Run: `cmake --build build-animation-normal --target test_anim_morph -j3 && ./build-animation-normal/test_anim_morph`  
Expected: missing adapter symbol, then an incorrect skinned xyz if a stub only copies input.

- [ ] **Step 3: Implement the packed 64-byte adapter**

```c
bool anim_morph_evaluate_skinned(const AnimMorphSet *set, const void *base_vertices,
                                 const f32 *weights, u32 weight_count,
                                 void *out_vertices, usize out_bytes);
```

Validate `out_bytes >= vertex_count * 64` with overflow checks. Use `memcpy` for packed access, validate the complete morphed result before writing, copy the full input records when input/output differ, then replace only pos3. Never cast an arbitrary byte pointer to a potentially misaligned `Vec3 *`.

- [ ] **Step 4: Run GREEN and regressions**

Run: `ctest --test-dir build-animation-normal --output-on-failure -R '^(test_anim_morph|test_animation|test_lod_skin)$'`  
Expected: all pass; the integration assertion fails if morph is skipped or joint/weight bytes are destroyed.

---

### Task 3: Named facial expressions and curves

**Files:**
- Create: `engine/src/animation/facial.h`
- Create: `engine/src/animation/facial.c`
- Create: `engine/tests/test_anim_facial.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: `AnimMorphSet` and its stable target names.
- Produces: `AnimFacialLibrary`, `anim_facial_library_init`, `anim_facial_add_expression`, `anim_facial_add_curve`, `anim_facial_evaluate`.

- [ ] **Step 1: Write failing named-curve interpolation tests**

```c
TEST(facial_named_expression_drives_named_morphs) {
    /* Morph targets "smile_l" and "smile_r". Expression "smile" has curves
       "left" and "right" mapping 0->0 and 1->1. At time 0.5 both weights
       must be 0.5, in morph target order. */
}

TEST(facial_curve_holds_endpoints_and_empty_expression_zeroes) {
    /* Before first/after last key return endpoint weights; an expression with
       no curves returns zero for every target. */
}
```

- [ ] **Step 2: Run RED**

Run: `cmake --build build-animation-normal --target test_anim_facial -j3 && ./build-animation-normal/test_anim_facial`  
Expected: missing facial implementation, followed by assertion failures for any non-interpolating stub.

- [ ] **Step 3: Implement bounded libraries and linear curves**

```c
bool anim_facial_add_curve(AnimFacialLibrary *library,
                           const char *expression_name, const char *curve_name,
                           const char *morph_target_name, u32 keyframe_count,
                           const f32 *times, const f32 *values);
bool anim_facial_evaluate(const AnimFacialLibrary *library,
                          const AnimMorphSet *morphs, const char *expression_name,
                          f32 time, f32 *out_weights, u32 weight_count);
```

Use 16 expressions, 8 curves/expression, 16 keys/curve, and 32-byte name arrays. Reject duplicates, overlong names, unsorted/non-finite times, and non-finite/out-of-range values. Resolve every curve target before zeroing or writing output.

- [ ] **Step 4: Add failure/capacity RED→GREEN cases**

Test missing expression/target, NaN time, unchanged output on failure, duplicate curve target within an expression, 17th expression, 9th curve, and 17 keys. Each expected value must be a hand-derived literal.

- [ ] **Step 5: Run focused GREEN**

Run: `ctest --test-dir build-animation-normal --output-on-failure -R '^(test_anim_facial|test_anim_morph|test_animation)$'`  
Expected: all pass.

---

### Task 4: Versioned animation quantizer and round-trip bounds

**Files:**
- Create: `engine/src/animation/anim_compression.h`
- Create: `engine/src/animation/anim_compression.c`
- Create: `engine/tests/test_anim_compression.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: existing `AnimClip`, joint count, caller output storage.
- Produces: `AnimCodecResult`, `anim_codec_encoded_size`, `anim_codec_encode`, `anim_codec_decode`, `anim_codec_time_error_bound`, `anim_codec_scalar_error_bound`, `ANIM_CODEC_ROTATION_ERROR_BOUND`.

- [ ] **Step 1: Write the failing full-TRS round-trip test**

```c
TEST(codec_round_trip_stays_within_explicit_bounds) {
    /* Static AnimClip with translation xyz in different ranges, scale, a
       normalized non-trivial quaternion, one zero-key channel, loop=true.
       Encode/decode and compare every key. Time/scalar tolerance is the
       documented range/(2*65535)+1e-6; rotation uses quaternion angle <=
       0.0001 rad. Empty channels and loop/playing flags must survive. */
}
```

- [ ] **Step 2: Run RED**

Run: `cmake --build build-animation-normal --target test_anim_compression -j3 && ./build-animation-normal/test_anim_compression`  
Expected: missing codec implementation; no production codec is written before observing this failure.

- [ ] **Step 3: Implement v1 validation and quantization**

```c
AnimCodecResult anim_codec_encode(const AnimClip *clip, u32 joint_count,
                                  u8 *out, usize out_capacity, usize *out_size);
AnimCodecResult anim_codec_decode(const void *data, usize size, AnimClip *out);
```

Write the 32-byte header and 40-byte channel headers explicitly as little-endian. Quantize times globally, xyz per channel, normalized quaternions in `[-1,1]`. Use CRC32 over payload. Validate the entire source and compute the exact size before writing; reject events explicitly.

- [ ] **Step 4: Implement two-pass transactional decode**

First pass checks magic/version/sizes/CRC/counts/enums/joints/min-max/times and every dequantized value without touching `out`. Second pass repeats deterministic decoding into `out` and cannot fail. Empty channel/clip and exact input length are supported; trailing or truncated bytes are rejected.

- [ ] **Step 5: Run round-trip GREEN and legacy animation tests**

Run: `ctest --test-dir build-animation-normal --output-on-failure -R '^(test_anim_compression|test_animation)$'`  
Expected: all pass, with measured errors no greater than the hand-computed bounds.

---

### Task 5: Corruption, non-finite data, capacity, and mutation evidence

**Files:**
- Modify: `engine/tests/test_anim_compression.c`
- Modify: `engine/tests/test_anim_morph.c`
- Modify: `engine/tests/test_anim_facial.c`

**Interfaces:**
- Exercises all public validation branches; no new production API.

- [ ] **Step 1: Add malformed-stream RED→GREEN tests**

```c
TEST(codec_rejects_every_single_bit_corruption) {
    /* For each byte in a small valid stream, flip bit 7, restore after the
       call, and require decode != ANIM_CODEC_OK with output unchanged. */
}

TEST(codec_rejects_semantic_corruption_with_valid_crc) {
    /* Independently recompute CRC after patching duration to NAN, a joint to
       joint_count, and path to 255. Each case must reach semantic validation
       and be rejected without modifying output. */
}
```

- [ ] **Step 2: Add source-validation and capacity tests**

Cover NaN/Inf duration, time and value; zero-norm quaternion; out-of-range joint; channel/key overflow; exact-size-minus-one encode buffer with required-size report and unchanged bytes. Decode bad version returns `ANIM_CODEC_VERSION` rather than a generic success or crash.

- [ ] **Step 3: Run focused normal suite**

Run: `ctest --test-dir build-animation-normal --output-on-failure -R '^(test_anim_(morph|facial|compression)|test_animation|test_lod_skin)$'`  
Expected: all pass.

- [ ] **Step 4: Kill actual production mutants**

Create mutated copies under the build directory, compile focused tests against those copies without changing the final source, and require at least one test failure for each mutation:

```text
morph: skip the finite-result check -> non-finite test fails
facial: accept a full curve array -> capacity test fails
codec: omit CRC comparison -> corruption test fails
codec: accept NaN source values -> non-finite test fails
codec: use 255 rather than 65535 quantization steps -> round-trip bound test fails
```

Restore/rebuild the unmodified sources and rerun GREEN. Record exact mutant/test pairs in `.superpowers/sdd/animation-extended-report.md`.

---

### Task 6: Animation-side IK/ragdoll exclusion

**Files:**
- Modify: `engine/src/animation/animation.h` (additive declaration only)
- Modify: `engine/src/animation/animation.c`
- Create: `engine/tests/test_anim_pose_authority.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: existing `IKSystem`, local TRS, world matrices, and the current `ragdoll_active` boolean supplied by the GameThread owner.
- Produces: `bool anim_ik_solve_unless_ragdoll(IKSystem *, Vec3 *, Quat *, const Mat4 *, u32, bool ragdoll_active)`.

- [ ] **Step 1: Write the failing exclusion test**

```c
TEST(ragdoll_blocks_ik_without_mutating_local_pose) {
    /* Build the existing three-joint two-bone fixture. An enabled ragdoll
       must return false with rotations byte-identical; after release the
       guarded result must equal a direct anim_ik_solve result. */
}
```

- [ ] **Step 2: Run RED, then implement the minimal gate**

Run: `cmake --build build-animation-normal --target test_anim_pose_authority -j3 && ./build-animation-normal/test_anim_pose_authority`
Expected RED: missing symbol, then false return from a stub. GREEN implementation returns false before any solver call when ragdoll is active; otherwise it invokes `anim_ik_solve` and returns true. Null/empty invalid input returns false without mutation.

- [ ] **Step 3: Verify exclusion and existing animation regressions**

Run: `ctest --test-dir build-animation-normal --output-on-failure -R '^(test_anim_pose_authority|test_animation)$'`
Expected: both pass. No ragdoll/physics source or header is modified.

---

### Task 7: Sanitizers, self review, report, and commit

**Files:**
- Create: `.superpowers/sdd/animation-extended-report.md`
- Modify only as review requires: the new animation sources/tests/CMake entries and the two design documents.

**Interfaces:**
- Final public APIs from Tasks 1–4; no ragdoll/physics integration.

- [ ] **Step 1: Run normal and ASan+UBSan focused suites**

```bash
cmake --build build-animation-normal --target test_anim_morph test_anim_facial test_anim_compression test_animation test_lod_skin -j3
ctest --test-dir build-animation-normal --output-on-failure -R '^(test_anim_(morph|facial|compression)|test_animation|test_lod_skin)$'
cmake -S engine -B build-animation-asan -DENGINE_RHI_BACKEND=opengl -DENGINE_BUILD_TESTS=ON -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-animation-asan --target test_anim_morph test_anim_facial test_anim_compression test_animation test_lod_skin -j3
ctest --test-dir build-animation-asan --output-on-failure -R '^(test_anim_(morph|facial|compression)|test_animation|test_lod_skin)$'
```

Expected: configure/build/test exit 0, no ASan/UBSan report.

- [ ] **Step 2: Run TSan focused suite**

```bash
cmake -S engine -B build-animation-tsan -DENGINE_RHI_BACKEND=opengl -DENGINE_BUILD_TESTS=ON -DENGINE_USE_TSAN=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-animation-tsan --target test_anim_morph test_anim_facial test_anim_compression test_animation test_lod_skin -j3
ctest --test-dir build-animation-tsan --output-on-failure -R '^(test_anim_(morph|facial|compression)|test_animation|test_lod_skin)$'
```

Expected: exit 0 and no TSan report. If the host runtime itself fails before tests, record the exact diagnostic and do not claim TSan passed.

- [ ] **Step 3: Obtain read-only review and fix findings**

Request review of the final diff for memory safety, transactional behavior, bounds, quantization math, real skinning integration, and compatibility. Fix every Critical/Important via a new failing regression test where behavior changes; rerun affected normal/sanitizer tests.

- [ ] **Step 4: Write the evidence report and inspect scope**

Report API/capacity/format/error bounds, RED→GREEN and mutation evidence, exact commands/results, reviewer findings, and limitations (CPU/headless only, no event compression, no ragdoll work). Verify `git status --short` contains only intended files and no physics/Implementation_Status changes.

- [ ] **Step 5: Check and commit**

```bash
git diff --check
git add docs/design/animation_extended.md docs/superpowers/plans/2026-11-02-animation-extended.md engine/src/animation engine/tests/test_anim_morph.c engine/tests/test_anim_facial.c engine/tests/test_anim_compression.c engine/CMakeLists.txt .superpowers/sdd/animation-extended-report.md
git commit -m "animation: add morph facial curves and quantized clips"
```

Expected: `git diff --check` is clean and the commit is created locally on `cry-wave1-animation`; no push or PR.
