# Stage 5 Phase A Task 4 — break_update target contract.
# Stage 5 Phase B Task 1 update: the target grows to TWO TUs
# (+src/update/break_update_client.c — client state machine + A/B slots,
# no download yet); the nm gate grows 15 → 24 symbols (+9 client); the
# minimal archive link test gains a client open/query/refusal pass.
#
# Pins (mirrors the test_break_crypto_target_contract.cmake shape):
#   1. The break_update target lives inside the if(BREAK_ENABLE_CRYPTO)
#      gated block (OFF → target absent).
#   2. Source-list pin: break_update is a formal STATIC library owning
#      exactly two TUs (src/update/break_update.c +
#      src/update/break_update_client.c, one mention each in the file);
#      the engine target does not compile them.
#   3. break_update links break_crypto PUBLIC.
#   4. No-link pins: engine / engine_demo / dxx_break / editor never link
#      break_update (their target_link_libraries calls are single-line).
#   5. nm gate: the production archive exports exactly the 24 public
#      break_update_* symbols (zero OpenSSL/break_crypto symbols
#      re-exported — a static archive only carries undefined references).
#   6. Minimal archive link test: a tiny executable links ONLY
#      libbreak_update.a + libbreak_crypto.a + -lcrypto (plus the PAL TU
#      src/platform/platform_fs.c compiled inline — the focused-test
#      precedent, engine keeps sole production ownership of it) and runs
#      one manifest parse + one store round-trip + one client
#      open/query/refusal pass.

if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()
if(NOT DEFINED UPDATE_CONTRACT_ARCHIVE)
    message(FATAL_ERROR "UPDATE_CONTRACT_ARCHIVE is required")
endif()
if(NOT DEFINED UPDATE_CONTRACT_CRYPTO_ARCHIVE)
    message(FATAL_ERROR "UPDATE_CONTRACT_CRYPTO_ARCHIVE is required")
endif()
if(NOT DEFINED UPDATE_CONTRACT_CC)
    message(FATAL_ERROR "UPDATE_CONTRACT_CC is required")
endif()
if(NOT DEFINED UPDATE_CONTRACT_INCLUDE)
    message(FATAL_ERROR "UPDATE_CONTRACT_INCLUDE is required")
endif()
if(NOT DEFINED UPDATE_CONTRACT_WORK)
    message(FATAL_ERROR "UPDATE_CONTRACT_WORK is required")
endif()
if(NOT DEFINED UPDATE_CONTRACT_SAN)
    set(UPDATE_CONTRACT_SAN "")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)

# --- 1. gated block -------------------------------------------------------
if(NOT cmake_text MATCHES "option\\(BREAK_ENABLE_CRYPTO")
    message(FATAL_ERROR "missing option(BREAK_ENABLE_CRYPTO ...)")
endif()

string(FIND "${cmake_text}" "if(BREAK_ENABLE_CRYPTO)" crypto_block_pos)
if(crypto_block_pos LESS 0)
    message(FATAL_ERROR "missing if(BREAK_ENABLE_CRYPTO) block")
endif()
string(SUBSTRING "${cmake_text}" ${crypto_block_pos} -1 crypto_block_rest)
# The top-level gated block has no nested if(), so its first endif() closes it.
string(FIND "${crypto_block_rest}" "endif()" crypto_block_end_rel)
if(crypto_block_end_rel LESS 0)
    message(FATAL_ERROR "if(BREAK_ENABLE_CRYPTO) block is not closed")
endif()
string(SUBSTRING "${crypto_block_rest}" 0 ${crypto_block_end_rel} crypto_block)

# --- 2. formal target + source-list pin -----------------------------------
if(NOT crypto_block MATCHES "add_library\\(break_update STATIC src/update/break_update.c src/update/break_update_client.c\\)")
    message(FATAL_ERROR "break_update must be a STATIC library owning exactly src/update/break_update.c + src/update/break_update_client.c")
endif()
if(NOT crypto_block MATCHES "set_property\\(TARGET break_update PROPERTY C_STANDARD 11\\)")
    message(FATAL_ERROR "break_update does not pin C_STANDARD 11")
endif()

# Each break_update TU has exactly one mention in the whole file (the test
# targets link the library rather than compiling the TUs inline).
string(REGEX MATCHALL "src/update/break_update\\.c" update_src_mentions "${cmake_text}")
list(LENGTH update_src_mentions update_src_mentions_count)
if(NOT update_src_mentions_count EQUAL 1)
    message(FATAL_ERROR "src/update/break_update.c must appear exactly once (break_update owns it); got ${update_src_mentions_count}")
endif()
string(REGEX MATCHALL "src/update/break_update_client\\.c" update_client_src_mentions "${cmake_text}")
list(LENGTH update_client_src_mentions update_client_src_mentions_count)
if(NOT update_client_src_mentions_count EQUAL 1)
    message(FATAL_ERROR "src/update/break_update_client.c must appear exactly once (break_update owns it); got ${update_client_src_mentions_count}")
endif()

# The engine target must not compile them.
string(REGEX MATCH "add_library\\(engine STATIC[^)]*\\)" engine_block "${cmake_text}")
if(NOT engine_block)
    message(FATAL_ERROR "could not isolate the engine add_library block")
endif()
if(engine_block MATCHES "src/update/")
    message(FATAL_ERROR "engine must not compile src/update/ sources")
endif()

# --- 3. PUBLIC break_crypto ------------------------------------------------
if(NOT crypto_block MATCHES "target_link_libraries\\(break_update PUBLIC break_crypto\\)")
    message(FATAL_ERROR "break_update does not link break_crypto PUBLIC")
endif()

# --- 4. no-link pins --------------------------------------------------------
string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break|editor)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_update")
        message(FATAL_ERROR "break_update leaked into a consumer link line: ${line}")
    endif()
endforeach()

# --- 4b. focused test registration pins -------------------------------------
if(NOT cmake_text MATCHES "add_executable\\(test_break_update tests/test_break_update.c src/platform/platform_fs.c\\)")
    message(FATAL_ERROR "missing test_break_update executable (with inline platform_fs.c)")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_break_update PRIVATE break_update")
    message(FATAL_ERROR "test_break_update does not link break_update")
endif()
if(NOT cmake_text MATCHES "add_test\\(NAME test_break_update COMMAND test_break_update\\)")
    message(FATAL_ERROR "missing test_break_update ctest registration")
endif()
if(NOT cmake_text MATCHES "add_executable\\(test_break_update_client tests/test_break_update_client.c src/platform/platform_fs.c\\)")
    message(FATAL_ERROR "missing test_break_update_client executable (with inline platform_fs.c)")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_break_update_client PRIVATE break_update")
    message(FATAL_ERROR "test_break_update_client does not link break_update")
endif()
if(NOT cmake_text MATCHES "add_test\\(NAME test_break_update_client COMMAND test_break_update_client\\)")
    message(FATAL_ERROR "missing test_break_update_client ctest registration")
endif()
if(NOT cmake_text MATCHES "add_test\\(NAME test_break_update_target_contract")
    message(FATAL_ERROR "missing test_break_update_target_contract registration")
endif()

# --- 5. nm gate: exactly the 24 public symbols ------------------------------
find_program(UPDATE_CONTRACT_NM nm)
if(NOT UPDATE_CONTRACT_NM)
    message(FATAL_ERROR "nm not found (required for the break_update export gate)")
endif()
execute_process(
    COMMAND ${UPDATE_CONTRACT_NM} -g --defined-only --format=posix "${UPDATE_CONTRACT_ARCHIVE}"
    RESULT_VARIABLE nm_rc
    OUTPUT_VARIABLE nm_out
    ERROR_VARIABLE nm_err)
if(NOT nm_rc EQUAL 0)
    message(FATAL_ERROR "nm failed on ${UPDATE_CONTRACT_ARCHIVE}: ${nm_err}")
endif()

set(expected_symbols
    break_update_client_confirm_boot
    break_update_client_confirmed
    break_update_client_current_slot
    break_update_client_current_version
    break_update_client_destroy
    break_update_client_last_error
    break_update_client_open
    break_update_client_pending
    break_update_client_rollback
    break_update_manifest_channel
    break_update_manifest_chunk_at
    break_update_manifest_chunk_count
    break_update_manifest_compatible
    break_update_manifest_destroy
    break_update_manifest_min_version
    break_update_manifest_parse
    break_update_manifest_platform
    break_update_manifest_verify
    break_update_manifest_version
    break_update_store_destroy
    break_update_store_get_chunk
    break_update_store_has_chunk
    break_update_store_open
    break_update_store_put_chunk)

string(REPLACE "\n" ";" nm_lines "${nm_out}")
set(actual_symbols "")
foreach(line IN LISTS nm_lines)
    # posix format: "<symbol> <type> <value>"; defined globals only (-g).
    if(line MATCHES "^([A-Za-z_][A-Za-z0-9_]*) ([A-Za-z]) ")
        list(APPEND actual_symbols "${CMAKE_MATCH_1}")
    endif()
endforeach()
list(SORT actual_symbols)
list(REMOVE_DUPLICATES actual_symbols)
set(expected_sorted ${expected_symbols})
list(SORT expected_sorted)
if(NOT actual_symbols STREQUAL expected_sorted)
    message(FATAL_ERROR
        "libbreak_update.a must export exactly the 24 public symbols.\n"
        "expected: ${expected_sorted}\nactual: ${actual_symbols}")
endif()

# --- 6. minimal archive link test -------------------------------------------
file(MAKE_DIRECTORY "${UPDATE_CONTRACT_WORK}")
set(link_main "${UPDATE_CONTRACT_WORK}/update_link_main.c")
file(WRITE "${link_main}" "
#include <update/break_update.h>
#include <update/break_update_client.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef UPDATE_LINK_WORK
#error \"UPDATE_LINK_WORK is required\"
#endif
/* Structurally valid minimal manifest with a zero (wrong) signature:
 * parse must succeed, verify must fail. The base64 is 86 'A' + "=="
 * (64 zero bytes, canonical). The pubkey is the Task-4 test-only key
 * (provenance in test_break_update.c) — a real key, because an all-zero
 * key + all-zero signature satisfies the RFC 8032 verification equation
 * in OpenSSL (small-order point acceptance); the unsigned-path pin needs
 * a genuine key. */
static int hexval(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}
int main(void) {
    static const char text[] =
        \"break-manifest-v1\\n\"
        \"version: 0.1.0\\n\"
        \"channel: stable\\n\"
        \"platform: linux-x86-64\\n\"
        \"min-version: 0.0.0\\n\"
        \"signature: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==\\n\";
    static const char pub_hex[] =
        \"419d3071bda8be4a6cbab81a1822222f792ad811a880b9e7b198e8d17b2610e4\";
    u8 pub[32];
    int i;
    for (i = 0; i < 32; i++)
        pub[i] = (u8)((hexval(pub_hex[2 * i]) << 4) | hexval(pub_hex[2 * i + 1]));
    BreakUpdateManifest *m = break_update_manifest_parse(text, strlen(text));
    if (!m) return 1;
    if (break_update_manifest_chunk_count(m) != 0) return 2;
    if (break_update_manifest_verify(m, pub)) return 3;
    u32 v[3] = {9, 9, 9};
    break_update_manifest_version(m, v);
    if (v[0] != 0 || v[1] != 1 || v[2] != 0) return 4;
    if (!break_update_manifest_compatible(m, \"stable\", \"linux-x86-64\", 0, 1, 0)) return 5;
    break_update_manifest_destroy(m);

    char root[1024];
    snprintf(root, sizeof(root), \"%s/link_store\", UPDATE_LINK_WORK);
    BreakUpdateStore *s = break_update_store_open(root);
    if (!s) return 6;
    if (!break_update_store_put_chunk(s, \"x\", 1)) return 7;
    /* sha256(\"x\") */
    static const char want[] =
        \"2d711642b726b04401627ca9fbac32f5c8530fb1903cc4db02258717921a4881\";
    if (!break_update_store_has_chunk(s, want)) return 8;
    u8 *buf = NULL;
    u64 len = 0;
    if (!break_update_store_get_chunk(s, want, &buf, &len)) return 9;
    if (len != 1 || buf[0] != 'x') return 10;
    free(buf);
    break_update_store_destroy(s);

    /* Phase B Task 1: client open on a fresh root (creates the layout +
     * initial state), query pins, and the two refusal paths. */
    snprintf(root, sizeof(root), \"%s/link_client\", UPDATE_LINK_WORK);
    BreakUpdateClient *cl = break_update_client_open(root);
    if (!cl) return 11;
    if (break_update_client_current_slot(cl) != '-') return 12;
    if (break_update_client_pending(cl) || break_update_client_confirmed(cl)) return 13;
    {
        u32 cv[3] = {9, 9, 9};
        break_update_client_current_version(cl, cv);
        if (cv[0] != 0 || cv[1] != 0 || cv[2] != 0) return 14;
    }
    if (break_update_client_confirm_boot(cl)) return 15; /* no pending */
    if (break_update_client_last_error(cl) != BREAK_UPDATE_CLIENT_STATE) return 16;
    if (break_update_client_rollback(cl)) return 17; /* no previous */
    if (break_update_client_last_error(cl) != BREAK_UPDATE_CLIENT_STATE) return 18;
    break_update_client_destroy(cl);
    return 0;
}
")

set(link_exe "${UPDATE_CONTRACT_WORK}/update_link_check")
separate_arguments(update_contract_san_flags UNIX_COMMAND "${UPDATE_CONTRACT_SAN}")
execute_process(
    COMMAND ${UPDATE_CONTRACT_CC} -std=c11 ${update_contract_san_flags}
            -I${UPDATE_CONTRACT_INCLUDE}
            "-DUPDATE_LINK_WORK=\"${UPDATE_CONTRACT_WORK}\""
            "${link_main}"
            "${UPDATE_CONTRACT_INCLUDE}/platform/platform_fs.c"
            "${UPDATE_CONTRACT_ARCHIVE}" "${UPDATE_CONTRACT_CRYPTO_ARCHIVE}"
            -lcrypto
            -o "${link_exe}"
    RESULT_VARIABLE link_rc
    OUTPUT_VARIABLE link_out
    ERROR_VARIABLE link_err)
if(NOT link_rc EQUAL 0)
    message(FATAL_ERROR
        "minimal link test failed to build (libbreak_update.a + libbreak_crypto.a + -lcrypto + inline platform_fs.c): ${link_err}")
endif()
execute_process(
    COMMAND "${link_exe}"
    RESULT_VARIABLE run_rc
    OUTPUT_VARIABLE run_out
    ERROR_VARIABLE run_err)
if(NOT run_rc EQUAL 0)
    message(FATAL_ERROR "minimal link test binary failed (rc=${run_rc})")
endif()

message(STATUS "break_update target contract passed")
