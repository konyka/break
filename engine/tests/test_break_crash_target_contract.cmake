# Stage 5 Phase C Tasks 1-3 — break_crash target contract.
#
# Pins (mirrors the test_break_update_target_contract.cmake shape):
#   1. The break_crash target lives inside the if(BREAK_ENABLE_CRASH)
#      gated block (OFF → target absent); the option exists.
#   2. Source-list pin: break_crash is a formal STATIC library owning
#      exactly one TU (src/crash/break_crash.c, one mention in the file);
#      the engine target does not compile it. break_crash links NOTHING
#      (zero dependencies — the PAL and break_version are consumed
#      header-only; callers link platform_fs.c / break_version.c
#      themselves).
#   3. No-link pins: engine / engine_demo / dxx_break / editor never link
#      break_crash (their target_link_libraries calls are single-line).
#   4. Focused test registration pins (inline platform_fs.c +
#      break_version.c precedent).
#   5. nm gate: the production archive exports exactly the 36 public
#      break_crash_* symbols (14 record + 10 builder + 8 spool + 4 capture).
#   6. Minimal archive link test: a tiny executable links ONLY
#      libbreak_crash.a (plus the PAL TU src/platform/platform_fs.c and the
#      build-identity TU src/core/break_version.c compiled inline — the
#      test_break_update / test_break_version precedent, engine keeps sole
#      production ownership of both) and runs one builder→finish→parse
#      golden round-trip + one spool put/read/mark pass + one
#      install/is_installed/double-install/uninstall smoke + one
#      redact/serialize round-trip and one upload pass smoke.

if(NOT DEFINED ENGINE_CMAKE)
    message(FATAL_ERROR "ENGINE_CMAKE is required")
endif()
if(NOT DEFINED CRASH_CONTRACT_ARCHIVE)
    message(FATAL_ERROR "CRASH_CONTRACT_ARCHIVE is required")
endif()
if(NOT DEFINED CRASH_CONTRACT_CC)
    message(FATAL_ERROR "CRASH_CONTRACT_CC is required")
endif()
if(NOT DEFINED CRASH_CONTRACT_INCLUDE)
    message(FATAL_ERROR "CRASH_CONTRACT_INCLUDE is required")
endif()
if(NOT DEFINED CRASH_CONTRACT_WORK)
    message(FATAL_ERROR "CRASH_CONTRACT_WORK is required")
endif()
if(NOT DEFINED CRASH_CONTRACT_SAN)
    set(CRASH_CONTRACT_SAN "")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)

# --- 1. gated block -------------------------------------------------------
if(NOT cmake_text MATCHES "option\\(BREAK_ENABLE_CRASH")
    message(FATAL_ERROR "missing option(BREAK_ENABLE_CRASH ...)")
endif()

string(FIND "${cmake_text}" "if(BREAK_ENABLE_CRASH)" crash_block_pos)
if(crash_block_pos LESS 0)
    message(FATAL_ERROR "missing if(BREAK_ENABLE_CRASH) block")
endif()
string(SUBSTRING "${cmake_text}" ${crash_block_pos} -1 crash_block_rest)
# The top-level gated block has no nested if(), so its first endif() closes it.
string(FIND "${crash_block_rest}" "endif()" crash_block_end_rel)
if(crash_block_end_rel LESS 0)
    message(FATAL_ERROR "if(BREAK_ENABLE_CRASH) block is not closed")
endif()
string(SUBSTRING "${crash_block_rest}" 0 ${crash_block_end_rel} crash_block)

# --- 2. formal target + source-list pin -----------------------------------
if(NOT crash_block MATCHES "add_library\\(break_crash STATIC src/crash/break_crash.c\\)")
    message(FATAL_ERROR "break_crash must be a STATIC library owning exactly src/crash/break_crash.c")
endif()
if(NOT crash_block MATCHES "set_property\\(TARGET break_crash PROPERTY C_STANDARD 11\\)")
    message(FATAL_ERROR "break_crash does not pin C_STANDARD 11")
endif()
if(crash_block MATCHES "target_link_libraries\\(break_crash")
    message(FATAL_ERROR "break_crash must link NOTHING (zero dependencies)")
endif()

# The break_crash TU has exactly one mention in the whole file (the test
# targets link the library rather than compiling the TU inline).
string(REGEX MATCHALL "src/crash/break_crash\\.c" crash_src_mentions "${cmake_text}")
list(LENGTH crash_src_mentions crash_src_mentions_count)
if(NOT crash_src_mentions_count EQUAL 1)
    message(FATAL_ERROR "src/crash/break_crash.c must appear exactly once (break_crash owns it); got ${crash_src_mentions_count}")
endif()

# The engine target must not compile it.
string(REGEX MATCH "add_library\\(engine STATIC[^)]*\\)" engine_block "${cmake_text}")
if(NOT engine_block)
    message(FATAL_ERROR "could not isolate the engine add_library block")
endif()
if(engine_block MATCHES "src/crash/")
    message(FATAL_ERROR "engine must not compile src/crash/ sources")
endif()

# --- 3. no-link pins --------------------------------------------------------
string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break|editor)[^\n]*" consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_crash")
        message(FATAL_ERROR "break_crash leaked into a consumer link line: ${line}")
    endif()
endforeach()

# --- 4. focused test registration pins -------------------------------------
if(NOT cmake_text MATCHES "add_executable\\(test_break_crash tests/test_break_crash.c src/platform/platform_fs.c src/core/break_version.c\\)")
    message(FATAL_ERROR "missing test_break_crash executable (with inline platform_fs.c + break_version.c)")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(test_break_crash PRIVATE break_crash")
    message(FATAL_ERROR "test_break_crash does not link break_crash")
endif()
if(NOT cmake_text MATCHES "add_test\\(NAME test_break_crash COMMAND test_break_crash\\)")
    message(FATAL_ERROR "missing test_break_crash ctest registration")
endif()
if(NOT cmake_text MATCHES "add_test\\(NAME test_break_crash_target_contract")
    message(FATAL_ERROR "missing test_break_crash_target_contract registration")
endif()

# --- 5. nm gate: exactly the 36 public symbols ------------------------------
find_program(CRASH_CONTRACT_NM NAMES nm llvm-nm)
if(NOT CRASH_CONTRACT_NM)
    message(FATAL_ERROR "nm not found (required for the break_crash export gate)")
endif()
execute_process(
    COMMAND ${CRASH_CONTRACT_NM} -g --defined-only --format=posix "${CRASH_CONTRACT_ARCHIVE}"
    RESULT_VARIABLE nm_rc
    OUTPUT_VARIABLE nm_out
    ERROR_VARIABLE nm_err)
if(NOT nm_rc EQUAL 0)
    message(FATAL_ERROR "nm failed on ${CRASH_CONTRACT_ARCHIVE}: ${nm_err}")
endif()

set(expected_symbols
    break_crash_install
    break_crash_is_installed
    break_crash_record_build_id
    break_crash_record_context_blob
    break_crash_record_destroy
    break_crash_record_fault_addr
    break_crash_record_module_at
    break_crash_record_module_count
    break_crash_record_parse
    break_crash_record_pid
    break_crash_record_redact
    break_crash_record_registers
    break_crash_record_serialize
    break_crash_record_signo
    break_crash_record_stack_window
    break_crash_record_tid
    break_crash_record_builder_add_module
    break_crash_record_builder_create
    break_crash_record_builder_destroy
    break_crash_record_builder_finish
    break_crash_record_builder_set_build_id
    break_crash_record_builder_set_context_blob
    break_crash_record_builder_set_process
    break_crash_record_builder_set_registers
    break_crash_record_builder_set_signal
    break_crash_record_builder_set_stack_window
    break_crash_set_context_blob
    break_crash_spool_count
    break_crash_spool_destroy
    break_crash_spool_mark_discarded
    break_crash_spool_mark_sent
    break_crash_spool_open
    break_crash_spool_put_pending
    break_crash_spool_read_pending
    break_crash_spool_upload_pending
    break_crash_uninstall)

string(REPLACE "\n" ";" nm_lines "${nm_out}")
set(actual_symbols "")
foreach(line IN LISTS nm_lines)
    # posix format: "<symbol> <type> <value>"; defined globals only (-g).
    if(line MATCHES "^([A-Za-z_][A-Za-z0-9_]*) ([A-Za-z]) ")
        set(sym "${CMAKE_MATCH_1}")
        if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
            string(REGEX REPLACE "^_" "" sym "${sym}")
        endif()
        # UCRT <stdio.h> inline helpers are emitted as external definitions
        # by clang on Windows; they are header artifacts, not library API.
        if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows" AND sym MATCHES
           "^(__local_stdio_printf_options|__local_stdio_scanf_options|_?v?s?n?printf|_?v?snprintf(_l)?|_vsprintf_l|_?sprintf|_vsscanf_l|_?sscanf)$")
            continue()
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
        "libbreak_crash.a must export exactly the 36 public symbols.\n"
        "expected: ${expected_sorted}\nactual: ${actual_symbols}")
endif()

# --- 6. minimal archive link test -------------------------------------------
file(MAKE_DIRECTORY "${CRASH_CONTRACT_WORK}")
set(link_main "${CRASH_CONTRACT_WORK}/crash_link_main.c")
file(WRITE "${link_main}" "
#include <crash/break_crash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef CRASH_LINK_WORK
#error \"CRASH_LINK_WORK is required\"
#endif
/* Always-true transport for the upload smoke: verifies the shipped bytes
 * parse (the pass ships redacted canonical text) and reports success. */
static bool crash_link_up_true(void *user, const void *bytes, usize len) {
    (void)user;
    BreakCrashRecord *r = break_crash_record_parse(bytes, len);
    if (!r) return false;
    break_crash_record_destroy(r);
    return true;
}
/* One builder→finish→parse golden round-trip + one spool
 * open/put/count/read/mark pass + one install/is_installed/double-install/
 * uninstall smoke, linking ONLY libbreak_crash.a (+ the inline PAL and
 * break_version TUs). The golden bytes pin the signal-writer grammar. */
int main(void) {
    static const char GOLDEN[] =
        \"break-crash-v1\\n\"
        \"signo: 0000000b\\n\"
        \"code: 00000001\\n\"
        \"fault_addr: 00000000deadbeef\\n\"
        \"pid: 00000000000004d2\\n\"
        \"tid: 000000000000162e\\n\"
        \"rip: 0000000000401000\\n\"
        \"rsp: 00007fffffffe000\\n\"
        \"rbp: 00007fffffffe100\\n\"
        \"build-id: abc123-x\\n\"
        \"module: 0000000000002000 00000000001f0000 libc.so.6\\n\"
        \"module: 0000000000001000 0000000000005000 app\\n\"
        \"stack-window: 0123abcd\\n\"
        \"context-blob: ff\\n\";
    static const u8 window[4] = {0x01, 0x23, 0xab, 0xcd};
    static const u8 blob[1] = {0xff};
    BreakCrashRecordBuilder *b = break_crash_record_builder_create();
    if (!b) return 1;
    break_crash_record_builder_set_signal(b, 11, 1, 0xdeadbeefu);
    break_crash_record_builder_set_process(b, 1234, 0x162e);
    break_crash_record_builder_set_registers(b, 0x401000, 0x7fffffffe000ull,
                                             0x7fffffffe100ull);
    break_crash_record_builder_set_build_id(b, \"abc123-x\");
    if (!break_crash_record_builder_add_module(b, \"libc.so.6\", 0x2000, 0x1f0000)) return 2;
    if (!break_crash_record_builder_add_module(b, \"app\", 0x1000, 0x5000)) return 3;
    break_crash_record_builder_set_stack_window(b, window, 4);
    break_crash_record_builder_set_context_blob(b, blob, 1);
    u8 text[1024];
    usize n = break_crash_record_builder_finish(b, text, sizeof(text));
    break_crash_record_builder_destroy(b);
    if (n != strlen(GOLDEN) || memcmp(text, GOLDEN, n) != 0) return 4;

    BreakCrashRecord *r = break_crash_record_parse(text, n);
    if (!r) return 5;
    if (break_crash_record_signo(r) != 11) return 6;
    if (break_crash_record_fault_addr(r) != 0xdeadbeefull) return 7;
    if (break_crash_record_pid(r) != 1234ull || break_crash_record_tid(r) != 0x162eull) return 8;
    {
        u64 regs[3] = {0, 0, 0};
        break_crash_record_registers(r, regs);
        if (regs[0] != 0x401000ull || regs[1] != 0x7fffffffe000ull ||
            regs[2] != 0x7fffffffe100ull) return 9;
    }
    if (strcmp(break_crash_record_build_id(r), \"abc123-x\") != 0) return 10;
    if (break_crash_record_module_count(r) != 2ull) return 11;
    {
        const char *name = NULL;
        u64 off = 0, size = 0;
        if (!break_crash_record_module_at(r, 1, &name, &off, &size)) return 12;
        if (strcmp(name, \"app\") != 0 || off != 0x1000ull || size != 0x5000ull) return 13;
        if (break_crash_record_module_at(r, 2, &name, &off, &size)) return 14;
    }
    {
        const u8 *bytes = NULL;
        if (break_crash_record_stack_window(r, &bytes) != 4u) return 15;
        if (!bytes || bytes[3] != 0xcd) return 16;
        if (break_crash_record_context_blob(r, &bytes) != 1u) return 17;
        if (!bytes || bytes[0] != 0xff) return 18;
    }
    break_crash_record_destroy(r);
    /* canonical rejection spot-checks (the full battery lives in the test) */
    if (break_crash_record_parse(GOLDEN, strlen(GOLDEN) - 1)) return 19; /* no final LF */
    if (break_crash_record_parse(\"break-crash-v1\\noops\\n\", 21)) return 20;

    char root[1024];
    snprintf(root, sizeof(root), \"%s/link_spool\", CRASH_LINK_WORK);
    BreakCrashSpool *s = break_crash_spool_open(root);
    if (!s) return 21;
    /* rerun-idempotent (the work dir persists across ctest runs): pending
     * must start empty (this checker never leaves pending residue); sent
     * grows by one, or stays saturated at BREAK_CRASH_SPOOL_KEEP with the
     * overflow landing in discarded (itself capped at BREAK_CRASH_SPOOL_KEEP
     * once enough reruns have accumulated). */
    u64 sent0 = break_crash_spool_count(s, 1);
    u64 disc0 = break_crash_spool_count(s, 2);
    if (break_crash_spool_count(s, 0) != 0ull) return 22;
    if (!break_crash_spool_put_pending(s, text, n)) return 23;
    if (break_crash_spool_count(s, 0) != 1ull) return 24;
    {
        u8 *buf = NULL;
        u64 len = 0;
        if (!break_crash_spool_read_pending(s, 0, &buf, &len)) return 25;
        if (len != (u64)n || memcmp(buf, text, n) != 0) return 26;
        free(buf);
    }
    if (!break_crash_spool_mark_sent(s, 0)) return 27;
    if (break_crash_spool_count(s, 0) != 0ull) return 28;
    if (sent0 < BREAK_CRASH_SPOOL_KEEP) {
        if (break_crash_spool_count(s, 1) != sent0 + 1) return 29;
    } else {
        if (break_crash_spool_count(s, 1) != BREAK_CRASH_SPOOL_KEEP) return 30;
        if (break_crash_spool_count(s, 2) !=
            (disc0 < BREAK_CRASH_SPOOL_KEEP ? disc0 + 1 : (u64)BREAK_CRASH_SPOOL_KEEP))
            return 31;
    }
    break_crash_spool_destroy(s);

    /* Task 2 capture smoke from the bare archive: install arms, second
     * install is refused, uninstall disarms; is_installed tracks. */
    if (break_crash_is_installed()) return 32;
    snprintf(root, sizeof(root), \"%s/link_install_spool\", CRASH_LINK_WORK);
#if defined(_WIN32)
    /* Documented compile-time stub on Windows (no SEH/VEH yet): install is
     * refused and nothing is ever armed. */
    {
        BreakCrashConfig cfg = {root};
        if (break_crash_install(&cfg)) return 33;
        if (break_crash_is_installed()) return 34;
        break_crash_set_context_blob(\"evidence\", 8);
        break_crash_uninstall();
        if (break_crash_install(NULL)) return 37;
    }
#else
    {
        BreakCrashConfig cfg = {root};
        if (!break_crash_install(&cfg)) return 33;
        if (!break_crash_is_installed()) return 34;
        if (break_crash_install(&cfg)) return 35;
        break_crash_set_context_blob(\"evidence\", 8);
        break_crash_uninstall();
        if (break_crash_is_installed()) return 36;
        if (break_crash_install(NULL)) return 37;
    }
#endif

    /* Task 3 smoke from the bare archive: redact keeps the already-basename
     * golden record byte-identical (idempotence pin), serialize round-trips,
     * NULL forms are no-ops, and one always-true upload pass moves
     * pending → sent (returned count 1). */
    r = break_crash_record_parse(text, n);
    if (!r) return 38;
    {
        BreakCrashRecord *red = break_crash_record_redact(r);
        if (!red) return 39;
        {
            u8 ser[1024];
            usize sn = break_crash_record_serialize(red, ser, sizeof(ser));
            break_crash_record_destroy(red);
            if (sn != n || memcmp(ser, text, n) != 0) return 40;
        }
    }
    break_crash_record_destroy(r);
    if (break_crash_record_redact(NULL)) return 41;
    if (break_crash_record_serialize(NULL, text, n) != 0) return 42;
    snprintf(root, sizeof(root), \"%s/link_upload_spool\", CRASH_LINK_WORK);
    s = break_crash_spool_open(root);
    if (!s) return 43;
    /* rerun-idempotent (the work dir persists across ctest runs): pending
     * must start empty (this checker never leaves pending residue here). */
    if (break_crash_spool_count(s, 0) != 0ull) return 44;
    sent0 = break_crash_spool_count(s, 1);
    disc0 = break_crash_spool_count(s, 2);
    if (!break_crash_spool_put_pending(s, text, n)) return 45;
    if (break_crash_spool_upload_pending(s, NULL, NULL) != 0) return 46;
    if (break_crash_spool_count(s, 0) != 1ull) return 47; /* NULL up: no-op */
    if (break_crash_spool_upload_pending(s, crash_link_up_true, NULL) != 1) return 48;
    if (break_crash_spool_count(s, 0) != 0ull) return 49;
    if (sent0 < BREAK_CRASH_SPOOL_KEEP) {
        if (break_crash_spool_count(s, 1) != sent0 + 1) return 50;
    } else {
        if (break_crash_spool_count(s, 1) != BREAK_CRASH_SPOOL_KEEP) return 51;
        if (break_crash_spool_count(s, 2) !=
            (disc0 < BREAK_CRASH_SPOOL_KEEP ? disc0 + 1 : (u64)BREAK_CRASH_SPOOL_KEEP))
            return 52;
    }
    break_crash_spool_destroy(s);
    return 0;
}
")

set(link_exe "${CRASH_CONTRACT_WORK}/crash_link_check")
separate_arguments(crash_contract_san_flags UNIX_COMMAND "${CRASH_CONTRACT_SAN}")
execute_process(
    COMMAND ${CRASH_CONTRACT_CC} -std=c11 ${crash_contract_san_flags}
            -I${CRASH_CONTRACT_INCLUDE}
            "-DCRASH_LINK_WORK=\"${CRASH_CONTRACT_WORK}\""
            "${link_main}"
            "${CRASH_CONTRACT_INCLUDE}/platform/platform_fs.c"
            "${CRASH_CONTRACT_INCLUDE}/core/break_version.c"
            "${CRASH_CONTRACT_ARCHIVE}"
            -o "${link_exe}"
    RESULT_VARIABLE link_rc
    OUTPUT_VARIABLE link_out
    ERROR_VARIABLE link_err)
if(NOT link_rc EQUAL 0)
    message(FATAL_ERROR
        "minimal link test failed to build (libbreak_crash.a + inline platform_fs.c + break_version.c): ${link_err}")
endif()
execute_process(
    COMMAND "${link_exe}"
    RESULT_VARIABLE run_rc
    OUTPUT_VARIABLE run_out
    ERROR_VARIABLE run_err)
if(NOT run_rc EQUAL 0)
    message(FATAL_ERROR "minimal link test binary failed (rc=${run_rc})")
endif()

message(STATUS "break_crash target contract passed")
