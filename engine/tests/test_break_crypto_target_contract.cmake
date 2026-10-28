# Stage 5 Phase A Task 2 — break_crypto target contract.
#
# Pins (mirrors the test_break_editor_target_contract.cmake shape):
#   1. BREAK_ENABLE_CRYPTO option exists (default ON) and fail-closed
#      find_package(OpenSSL REQUIRED) + the break_crypto target live inside
#      its if() block (OFF → target absent).
#   2. Source-list pin: break_crypto is a formal STATIC library owning
#      exactly one TU (src/crypto/break_crypto.c, single mention in the file);
#      the engine target does not compile it.
#   3. break_crypto links OpenSSL::Crypto PUBLIC.
#   4. No-link pins: engine / engine_demo / dxx_break / editor never link
#      break_crypto (their target_link_libraries calls are single-line).
#   5. nm gate: the production archive exports exactly the 8 public
#      break_crypto_* symbols (zero OpenSSL symbols re-exported — a static
#      archive only carries undefined references to them).
#   6. Minimal archive link test: a tiny executable compiled here links ONLY
#      libbreak_crypto.a + -lcrypto and runs one Ed25519 verify.

if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()
if(NOT DEFINED CRYPTO_CONTRACT_ARCHIVE)
    message(FATAL_ERROR "CRYPTO_CONTRACT_ARCHIVE is required")
endif()
if(NOT DEFINED CRYPTO_CONTRACT_CC)
    message(FATAL_ERROR "CRYPTO_CONTRACT_CC is required")
endif()
if(NOT DEFINED CRYPTO_CONTRACT_INCLUDE)
    message(FATAL_ERROR "CRYPTO_CONTRACT_INCLUDE is required")
endif()
if(NOT DEFINED CRYPTO_CONTRACT_WORK)
    message(FATAL_ERROR "CRYPTO_CONTRACT_WORK is required")
endif()
if(NOT DEFINED CRYPTO_CONTRACT_SAN)
    set(CRYPTO_CONTRACT_SAN "")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)

# --- 1. option + fail-closed gated block --------------------------------
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

# ON + not found -> FATAL_ERROR: find_package(OpenSSL REQUIRED) IS the
# fail-closed gate (REQUIRED aborts configure when libcrypto is absent).
if(NOT crypto_block MATCHES "find_package\\(OpenSSL REQUIRED\\)")
    message(FATAL_ERROR "break_crypto block lacks find_package(OpenSSL REQUIRED) fail-closed gate")
endif()

# --- 2. formal target + source-list pin ----------------------------------
if(NOT crypto_block MATCHES "add_library\\(break_crypto STATIC src/crypto/break_crypto.c\\)")
    message(FATAL_ERROR "break_crypto must be a STATIC library owning exactly src/crypto/break_crypto.c")
endif()
if(NOT crypto_block MATCHES "set_property\\(TARGET break_crypto PROPERTY C_STANDARD 11\\)")
    message(FATAL_ERROR "break_crypto does not pin C_STANDARD 11")
endif()

# src/crypto/break_crypto.c has exactly one mention in the whole file (the
# test target links the library rather than compiling the TU inline).
string(REGEX MATCHALL "src/crypto/break_crypto\\.c" crypto_src_mentions "${cmake_text}")
list(LENGTH crypto_src_mentions crypto_src_mentions_count)
if(NOT crypto_src_mentions_count EQUAL 1)
    message(FATAL_ERROR "src/crypto/break_crypto.c must appear exactly once (break_crypto owns it); got ${crypto_src_mentions_count}")
endif()

# The engine target must not compile it.
string(REGEX MATCH "add_library\\(engine STATIC[^)]*\\)" engine_block "${cmake_text}")
if(NOT engine_block)
    message(FATAL_ERROR "could not isolate the engine add_library block")
endif()
if(engine_block MATCHES "src/crypto/")
    message(FATAL_ERROR "engine must not compile src/crypto/ sources")
endif()

# --- 3. PUBLIC OpenSSL::Crypto -------------------------------------------
if(NOT crypto_block MATCHES "target_link_libraries\\(break_crypto PUBLIC OpenSSL::Crypto\\)")
    message(FATAL_ERROR "break_crypto does not link OpenSSL::Crypto PUBLIC")
endif()

# --- 4. no-link pins ------------------------------------------------------
string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break|editor)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_crypto")
        message(FATAL_ERROR "break_crypto leaked into a consumer link line: ${line}")
    endif()
endforeach()

# --- 4b. focused test registration pins -----------------------------------
if(NOT cmake_text MATCHES "add_executable\\(test_break_crypto tests/test_break_crypto.c\\)")
    message(FATAL_ERROR "missing test_break_crypto executable")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_break_crypto PRIVATE break_crypto\\)")
    message(FATAL_ERROR "test_break_crypto does not link break_crypto")
endif()
if(NOT cmake_text MATCHES "add_test\\(NAME test_break_crypto COMMAND test_break_crypto\\)")
    message(FATAL_ERROR "missing test_break_crypto ctest registration")
endif()
if(NOT cmake_text MATCHES "add_test\\(NAME test_break_crypto_target_contract")
    message(FATAL_ERROR "missing test_break_crypto_target_contract registration")
endif()

# --- 5. nm gate: exactly the 8 public symbols, zero OpenSSL re-export -----
find_program(CRYPTO_CONTRACT_NM nm)
if(NOT CRYPTO_CONTRACT_NM)
    message(FATAL_ERROR "nm not found (required for the break_crypto export gate)")
endif()
execute_process(
    COMMAND ${CRYPTO_CONTRACT_NM} -g --defined-only --format=posix "${CRYPTO_CONTRACT_ARCHIVE}"
    RESULT_VARIABLE nm_rc
    OUTPUT_VARIABLE nm_out
    ERROR_VARIABLE nm_err)
if(NOT nm_rc EQUAL 0)
    message(FATAL_ERROR "nm failed on ${CRYPTO_CONTRACT_ARCHIVE}: ${nm_err}")
endif()

set(expected_symbols
    break_crypto_ed25519_verify
    break_crypto_hmac_sha256
    break_crypto_random
    break_crypto_sha256
    break_crypto_sha256_ctx_create
    break_crypto_sha256_ctx_destroy
    break_crypto_sha256_final
    break_crypto_sha256_update)

string(REPLACE "\n" ";" nm_lines "${nm_out}")
set(actual_symbols "")
foreach(line IN LISTS nm_lines)
    # posix format: "<symbol> <type> <value>"; defined globals only (-g).
    if(line MATCHES "^([A-Za-z_][A-Za-z0-9_]*) ([A-Za-z]) ")
        set(sym "${CMAKE_MATCH_1}")
        if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
            string(REGEX REPLACE "^_" "" sym "${sym}")
        endif()
        list(APPEND actual_symbols "${sym}")
    endif()
endforeach()
list(SORT actual_symbols)
list(REMOVE_DUPLICATES actual_symbols)
set(expected_sorted ${expected_symbols})
list(SORT expected_sorted)
if(NOT actual_symbols STREQUAL expected_sorted)
    message(FATAL_ERROR
        "libbreak_crypto.a must export exactly the 8 public symbols.\n"
        "expected: ${expected_sorted}\nactual: ${actual_symbols}")
endif()

# --- 6. minimal archive link test ----------------------------------------
file(MAKE_DIRECTORY "${CRYPTO_CONTRACT_WORK}")
set(link_main "${CRYPTO_CONTRACT_WORK}/crypto_link_main.c")
file(WRITE "${link_main}" "
#include <crypto/break_crypto.h>
/* RFC 8032 TEST 1 (empty message); hex decoded at runtime to keep this
 * generated file compact. Returns 0 iff the valid signature verifies. */
static int hexval(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}
int main(void) {
    static const char *pub_hex =
        \"d75a980182b10ab7d54bfed3c964073a0ee172f3daa62325af021a68f707511a\";
    static const char *sig_hex =
        \"e5564300c360ac729086e2cc806e828a84877f1eb8e5d974d873e06522490155\"
        \"5fb8821590a33bacc61e39701cf9b46bd25bf5f0595bbe24655141438e7a100b\";
    u8 pub[32];
    u8 sig[64];
    int i;
    for (i = 0; i < 32; i++)
        pub[i] = (u8)((hexval(pub_hex[2 * i]) << 4) | hexval(pub_hex[2 * i + 1]));
    for (i = 0; i < 64; i++)
        sig[i] = (u8)((hexval(sig_hex[2 * i]) << 4) | hexval(sig_hex[2 * i + 1]));
    return break_crypto_ed25519_verify(sig, \"\", 0, pub) ? 0 : 1;
}
")

# macOS has no system libcrypto on the default search path: the outer lane
# passes the resolved OpenSSL library; elsewhere plain -lcrypto is used.
if(DEFINED CRYPTO_CONTRACT_LIBCRYPTO AND NOT "${CRYPTO_CONTRACT_LIBCRYPTO}" STREQUAL "")
    set(crypto_contract_libcrypto "${CRYPTO_CONTRACT_LIBCRYPTO}")
else()
    set(crypto_contract_libcrypto -lcrypto)
endif()
set(link_exe "${CRYPTO_CONTRACT_WORK}/crypto_link_check")
separate_arguments(crypto_contract_san_flags UNIX_COMMAND "${CRYPTO_CONTRACT_SAN}")
execute_process(
    COMMAND ${CRYPTO_CONTRACT_CC} -std=c11 ${crypto_contract_san_flags}
            -I${CRYPTO_CONTRACT_INCLUDE}
            "${link_main}" "${CRYPTO_CONTRACT_ARCHIVE}" ${crypto_contract_libcrypto}
            -o "${link_exe}"
    RESULT_VARIABLE link_rc
    OUTPUT_VARIABLE link_out
    ERROR_VARIABLE link_err)
if(NOT link_rc EQUAL 0)
    message(FATAL_ERROR
        "minimal link test failed to build (libbreak_crypto.a + -lcrypto only): ${link_err}")
endif()
execute_process(
    COMMAND "${link_exe}"
    RESULT_VARIABLE run_rc
    OUTPUT_VARIABLE run_out
    ERROR_VARIABLE run_err)
if(NOT run_rc EQUAL 0)
    message(FATAL_ERROR "minimal link test binary failed (Ed25519 verify returned false)")
endif()

message(STATUS "break_crypto target contract passed")
