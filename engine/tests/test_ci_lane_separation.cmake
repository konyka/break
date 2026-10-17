# Plan C Task 14: CI lane separation contract (text-level, platform-free).
# Asserts the lane-gpu-runtime-macos-metal / ios-metal-build lanes exist
# alongside lane-native-surface-cocoa (plan F task 7 renames: macos-metal ->
# lane-gpu-runtime-macos-metal, macos-vulkan -> lane-native-surface-cocoa),
# that the metal lane never mentions MoltenVK, and that the
# evidence register keeps native-Metal rows free of MoltenVK receipts.
# Run:
#   cmake -DCI_YML=<repo>/.github/workflows/ci.yml \
#         -DEVIDENCE_MD=<repo>/docs/rhi_backend_evidence.md \
#         -P engine/tests/test_ci_lane_separation.cmake
cmake_policy(SET CMP0054 NEW)
if(POLICY CMP0140)
    cmake_policy(SET CMP0140 NEW)
endif()
if(NOT DEFINED CI_YML OR NOT DEFINED EVIDENCE_MD)
    message(FATAL_ERROR "CI_YML and EVIDENCE_MD are required")
endif()

set(failures 0)
macro(contract_fail detail)
    message(WARNING "CONTRACT FAIL: ${detail}")
    math(EXPR failures "${failures} + 1")
endmacro()

file(READ "${CI_YML}" ci)
file(READ "${EVIDENCE_MD}" ev)

# 1. Both lanes exist side by side (metal must not replace the Vulkan lane).
string(FIND "${ci}" "lane-native-surface-cocoa:" pos_vk)
if(pos_vk EQUAL -1)
    contract_fail("ci.yml missing lane-native-surface-cocoa lane (was macos-vulkan)")
endif()
string(FIND "${ci}" "lane-gpu-runtime-macos-metal:" pos_metal)
if(pos_metal EQUAL -1)
    contract_fail("ci.yml missing lane-gpu-runtime-macos-metal lane (was macos-metal)")
endif()
string(FIND "${ci}" "ios-metal-build:" pos_ios)
if(pos_ios EQUAL -1)
    contract_fail("ci.yml missing ios-metal-build lane")
endif()

# 2. The macos-metal block must not mention MoltenVK (case-insensitive).
# Negated mentions are legitimate commentary (e.g. "MoltenVK-free") and are
# scrubbed before the scan so future honest comments are not flagged.
if(NOT pos_metal EQUAL -1)
    string(SUBSTRING "${ci}" ${pos_metal} -1 metal_tail)
    string(REGEX MATCH "\n  [a-z0-9_-]+:\n" next_job "${metal_tail}")
    string(FIND "${metal_tail}" "${next_job}" next_pos)
    if(next_pos GREATER -1)
        string(SUBSTRING "${metal_tail}" 0 ${next_pos} metal_block)
    else()
        set(metal_block "${metal_tail}")
    endif()
    string(TOLOWER "${metal_block}" metal_lower)
    string(REPLACE "moltenvk-free" "" metal_lower "${metal_lower}")
    string(FIND "${metal_lower}" "molten" molten_pos)
    if(NOT molten_pos EQUAL -1)
        contract_fail("macos-metal lane mentions MoltenVK")
    endif()
endif()

# 3. Evidence register: native-Metal rows exist and carry no MoltenVK
# receipt (the register must not contain a row with both tokens).
# Baseline-comparison phrasing is legitimate: BENCHMARK_COMPARABLE is
# DEFINED against the same-host MoltenVK baseline (fps ratio >= 90%), so
# the threshold arithmetic must be allowed on a native-Metal row. Scrub
# those exact comparison tokens before the both-tokens scan; a row that
# actually credits a MoltenVK run as Metal evidence still matches.
string(FIND "${ev}" "macOS × 原生 Metal" ev_metal_row)
if(ev_metal_row EQUAL -1)
    contract_fail("evidence register missing 'macOS × 原生 Metal' row")
endif()
string(FIND "${ev}" "iOS × 原生 Metal" ev_ios_row)
if(ev_ios_row EQUAL -1)
    string(FIND "${ev}" "macOS/iOS × 原生 Metal" ev_ios_row)
endif()
if(ev_ios_row EQUAL -1)
    contract_fail("evidence register missing iOS native Metal row")
endif()
set(ev_scrubbed "${ev}")
foreach(baseline_token "同机 MoltenVK 基线" "MoltenVK 基线" "MoltenVK fps_avg")
    string(REPLACE "${baseline_token}" "" ev_scrubbed "${ev_scrubbed}")
endforeach()
string(REGEX MATCHALL "[^\n]*原生 Metal[^\n]*MoltenVK[^\n]*" bad_rows "${ev_scrubbed}")
list(LENGTH bad_rows bad_count)
if(NOT bad_count EQUAL 0)
    contract_fail("evidence register attaches MoltenVK receipt to a native-Metal row")
endif()

# 4. iOS simulator honesty: the ios-metal-build lane block (anchored, not a
# whole-file search) and the evidence register must both mark the simulator
# evidence as compile only — the lane has no lifecycle harness (gap owned by
# Task 15), so the stronger "compile/lifecycle only" wording must NOT appear.
string(TOLOWER "${ci}" ci_lower)
string(FIND "${ci_lower}" "ios-metal-build:" pos_ios_lower)
if(NOT pos_ios_lower EQUAL -1)
    string(SUBSTRING "${ci_lower}" ${pos_ios_lower} -1 ios_tail)
    string(REGEX MATCH "\n  [a-z0-9_-]+:\n" ios_next_job "${ios_tail}")
    string(FIND "${ios_tail}" "${ios_next_job}" ios_next_pos)
    if(ios_next_pos GREATER -1)
        string(SUBSTRING "${ios_tail}" 0 ${ios_next_pos} ios_block)
    else()
        set(ios_block "${ios_tail}")
    endif()
    string(FIND "${ios_block}" "compile only" lane_mark_pos)
    if(lane_mark_pos EQUAL -1)
        contract_fail("ios lane missing 'compile only' marking")
    endif()
    string(FIND "${ios_block}" "compile/lifecycle only" lane_overclaim_pos)
    if(NOT lane_overclaim_pos EQUAL -1)
        contract_fail("ios lane overclaims 'compile/lifecycle only' (no lifecycle harness)")
    endif()
endif()
string(TOLOWER "${ev}" ev_lower)
string(FIND "${ev_lower}" "compile only" ev_mark_pos)
if(ev_mark_pos EQUAL -1)
    contract_fail("evidence register missing 'compile only' marking")
endif()
string(FIND "${ev_lower}" "compile/lifecycle only" ev_overclaim_pos)
if(NOT ev_overclaim_pos EQUAL -1)
    contract_fail("evidence register overclaims 'compile/lifecycle only' (no lifecycle harness)")
endif()

if(failures GREATER 0)
    message(FATAL_ERROR "test_ci_lane_separation: ${failures} contract violation(s)")
endif()
message(STATUS "test_ci_lane_separation: all contract checks passed")
