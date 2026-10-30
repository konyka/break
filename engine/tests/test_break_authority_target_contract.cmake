# Stage 5 subproject 5 — break_authority + break_integrity target contract.
#
# Pins:
#   1. Both are formal STATIC libraries, each source TU named exactly once in
#      engine/CMakeLists.txt (break_authority also owns the two small network
#      TUs it reuses; the test targets link the library, not the TUs).
#   2. engine / engine_demo / dxx_break / editor never link either.
#   3. nm gate: each archive exports EXACTLY its documented public symbols and
#      no test hooks / *_for_test symbols.
#   4. The trust boundary is structural: break_authority's sources never
#      include the integrity header (a client signal cannot reach a ledger),
#      and the integrity header declares no allow/grant/deny/authorize API.
#
# -DENGINE_CMAKE -DAUTH_ARCHIVE -DINTEG_ARCHIVE -DSRC_DIR

foreach(var ENGINE_CMAKE AUTH_ARCHIVE INTEG_ARCHIVE SRC_DIR)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

file(READ "${ENGINE_CMAKE}" cmake_text)

# --- 1. targets and sources --------------------------------------------------
if(NOT cmake_text MATCHES "add_library\\(break_authority STATIC[ \n]+src/authority/break_authority.c[ \n]+src/network/break_replay_window.c[ \n]+src/network/break_msg_rate.c\\)")
    message(FATAL_ERROR "break_authority must be a STATIC library owning exactly authority + replay_window + msg_rate")
endif()
if(NOT cmake_text MATCHES "add_library\\(break_integrity STATIC src/integrity/break_integrity.c\\)")
    message(FATAL_ERROR "break_integrity must be a STATIC library owning exactly src/integrity/break_integrity.c")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(break_integrity PUBLIC break_crypto\\)")
    message(FATAL_ERROR "break_integrity must link break_crypto PUBLIC")
endif()
string(REGEX MATCHALL "src/authority/break_authority\\.c" a_mentions "${cmake_text}")
list(LENGTH a_mentions a_count)
if(NOT a_count EQUAL 1)
    message(FATAL_ERROR "src/authority/break_authority.c must appear exactly once, got ${a_count}")
endif()
string(REGEX MATCHALL "src/integrity/break_integrity\\.c" i_mentions "${cmake_text}")
list(LENGTH i_mentions i_count)
if(NOT i_count EQUAL 1)
    message(FATAL_ERROR "src/integrity/break_integrity.c must appear exactly once, got ${i_count}")
endif()

# --- 2. no-link pins ----------------------------------------------------------
string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break|editor)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_authority|break_integrity")
        message(FATAL_ERROR "a stage-5 security library leaked into a consumer link line: ${line}")
    endif()
endforeach()
string(REGEX MATCH "add_library\\(engine STATIC[^)]*\\)" engine_block "${cmake_text}")
if(engine_block MATCHES "src/authority/|src/integrity/")
    message(FATAL_ERROR "engine must not compile src/authority/ or src/integrity/ sources")
endif()

# --- 3. nm gate ---------------------------------------------------------------
find_program(NM NAMES nm llvm-nm)
if(NOT NM)
    message(FATAL_ERROR "nm not found")
endif()

function(check_exports archive prefix_regex expected)
    execute_process(COMMAND ${NM} -g --defined-only --format=posix "${archive}"
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
    if(NOT rc EQUAL 0)
        message(FATAL_ERROR "nm failed on ${archive}: ${err}")
    endif()
    string(REPLACE "\n" ";" lines "${out}")
    set(actual "")
    foreach(line IN LISTS lines)
        if(line MATCHES "^([A-Za-z_][A-Za-z0-9_]*) [TDBR] ")
            set(sym "${CMAKE_MATCH_1}")
            # the two reused network TUs inside break_authority export their own symbols
            if(sym MATCHES "${prefix_regex}")
                list(APPEND actual "${sym}")
            elseif(NOT sym MATCHES "^break_(replay_window|msg_rate)_")
                message(FATAL_ERROR "${archive} exports an unexpected symbol: ${sym}")
            endif()
        endif()
    endforeach()
    list(SORT actual)
    set(want ${expected})
    list(SORT want)
    if(NOT actual STREQUAL want)
        message(FATAL_ERROR "export list of ${archive} differs.\n  actual: ${actual}\n  wanted: ${want}")
    endif()
    foreach(sym IN LISTS actual)
        if(sym MATCHES "for_test|_test_|testing")
            message(FATAL_ERROR "test hook exported from ${archive}: ${sym}")
        endif()
    endforeach()
endfunction()

check_exports("${AUTH_ARCHIVE}" "^break_authority_"
    "break_authority_create;break_authority_destroy;break_authority_define_item;break_authority_item_price;break_authority_open_session;break_authority_close_session;break_authority_grant_server;break_authority_intent_spend;break_authority_intent_attack;break_authority_balance;break_authority_health;break_authority_item_count;break_authority_decode_intent;break_authority_apply")
check_exports("${INTEG_ARCHIVE}" "^break_integrity_"
    "break_integrity_check_files;break_integrity_check_debugger;break_integrity_check_modules")

# --- 4. the trust boundary is structural --------------------------------------
file(GLOB auth_sources "${SRC_DIR}/authority/*.c" "${SRC_DIR}/authority/*.h")
foreach(f IN LISTS auth_sources)
    file(READ "${f}" body)
    if(body MATCHES "break_integrity|integrity/")
        message(FATAL_ERROR "${f} references the integrity library: a client signal must never reach a ledger")
    endif()
endforeach()
file(READ "${SRC_DIR}/integrity/break_integrity.h" integ_header)
# strip comments so the explanation of what the library does NOT do can name those words
string(REGEX REPLACE "/\\*([^*]|\\*+[^*/])*\\*+/" "" integ_code "${integ_header}")
if(integ_code MATCHES "(allow|grant|deny|authori[sz]e|permit|revoke|ban|trust)[a-z_]*[ ]*\\(")
    message(FATAL_ERROR "the integrity header declares a function that sounds like a decision")
endif()
if(integ_code MATCHES "bool[ ]+break_integrity_[a-z_]*(ok|clean|trusted|valid)[a-z_]*[ ]*\\(")
    message(FATAL_ERROR "the integrity header declares a pass/fail style function")
endif()

message(STATUS "break_authority / break_integrity contract OK")
