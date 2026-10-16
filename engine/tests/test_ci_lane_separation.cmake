# Plan C Task 14: CI lane separation contract (text-level, platform-free).
# Asserts the macos-metal / ios-metal-build lanes exist alongside
# macos-vulkan, that the metal lane never mentions MoltenVK, and that the
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
string(FIND "${ci}" "macos-vulkan:" pos_vk)
if(pos_vk EQUAL -1)
    contract_fail("ci.yml missing macos-vulkan lane")
endif()
string(FIND "${ci}" "macos-metal:" pos_metal)
if(pos_metal EQUAL -1)
    contract_fail("ci.yml missing macos-metal lane")
endif()
string(FIND "${ci}" "ios-metal-build:" pos_ios)
if(pos_ios EQUAL -1)
    contract_fail("ci.yml missing ios-metal-build lane")
endif()

# 2. The macos-metal block must not mention MoltenVK (case-insensitive).
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
    string(FIND "${metal_lower}" "molten" molten_pos)
    if(NOT molten_pos EQUAL -1)
        contract_fail("macos-metal lane mentions MoltenVK")
    endif()
endif()

# 3. Evidence register: native-Metal rows exist and carry no MoltenVK
# receipt (the register must not contain a row with both tokens).
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
string(REGEX MATCHALL "[^\n]*原生 Metal[^\n]*MoltenVK[^\n]*" bad_rows "${ev}")
list(LENGTH bad_rows bad_count)
if(NOT bad_count EQUAL 0)
    contract_fail("evidence register attaches MoltenVK receipt to a native-Metal row")
endif()

# 4. iOS simulator honesty: the lane and the register must both mark the
# simulator evidence as compile/lifecycle only.
string(TOLOWER "${ci}" ci_lower)
string(FIND "${ci_lower}" "compile/lifecycle only" lane_mark_pos)
if(lane_mark_pos EQUAL -1)
    contract_fail("ios lane missing 'compile/lifecycle only' marking")
endif()
string(TOLOWER "${ev}" ev_lower)
string(FIND "${ev_lower}" "compile/lifecycle only" ev_mark_pos)
if(ev_mark_pos EQUAL -1)
    contract_fail("evidence register missing 'compile/lifecycle only' marking")
endif()

if(failures GREATER 0)
    message(FATAL_ERROR "test_ci_lane_separation: ${failures} contract violation(s)")
endif()
message(STATUS "test_ci_lane_separation: all contract checks passed")
