#!/bin/sh
# run_target_suite.sh — QNX on-target suite: run the generated command list.
#
# Pairs with gen_target_cmds.py (host side). Push the cross build's test
# binaries plus the deployment tree to /tmp/bt on the target, then:
#
#   sh run_target_suite.sh cmds.txt
#
# Semantics replicated from the host headless lane:
#   - ulimit -s 8192: QNX default stacks are far below the Linux CI
#     assumption (README: main() needs ~4.4 MB of locals); without this,
#     tests with large local arrays die with Memory fault.
#   - EXPECT_FAIL lines are ctest WILL_FAIL tests: nonzero exit is the pass
#     condition there.
#   - cwd stays the binary directory so bare-name data fallbacks resolve.
#   - BREAK_QNX_TARGET_ROOT can isolate a deployment from other target jobs.
#     Pass the same root to gen_target_cmds.py and configure the build with
#     ENGINE_TEST_SOURCE_ROOT=<root>; the default remains /tmp/bt.
#     Link <root-parent>/src to <root>/src for source-reading fallbacks
#     (for example /tmp/src for /tmp/bt); use a separate VM for concurrent suites.
#   - BREAK_QNX_TMPDIR defaults to <root>/tmp so tests do not fill the IFS or
#     an unrelated small partition; set it to override that isolated location.

#   - BREAK_QNX_STACK_KB overrides the 8192 KiB default when a sanitizer
#     needs more stack (for example 32768 for full-suite ASan runs).
#   - BREAK_QNX_TLS_INTERPOSE=1 opts into per-process SDP 8.0 x86_64 ASan
#     TLS interposition. The legacy scoped-capacity test stays on its old shim;
#     tests using fork stay on the default path because fork is not covered.
#   - BREAK_QNX_ON_AD=1 launches each test with on -ad (required by QNX ASan).
#   - BREAK_QNX_VULKAN_RUNTIME=1 opts into the explicitly deployed SwiftShader
#     software runtime. With TLS interpose, libc++ precedes ASan so its
#     emergency-pool cleanup runs before the final leak check.
#   - BREAK_QNX_ASAN_LOCK optionally names an absolute lock directory. The
#     atomic mkdir prevents concurrent sanitizer initializers on one target;
#     the empty lock directory is removed on exit, never force-deleted.
#   - BREAK_QNX_SANITIZER_CLEANUP=1 opts into the test-only exit cleanup helper
#     after ASan/UBSan and before the graphics redirect. It requires the
#     explicit Vulkan runtime, is incompatible with TLS interpose, and is not
#     a general runtime or concurrent library-teardown fix.
ulimit -s "${BREAK_QNX_STACK_KB:-8192}" 2>/dev/null
case "${BREAK_QNX_ON_AD:-0}" in
    0) ;;
    1) command -v on >/dev/null 2>&1 || exit 2 ;;
    *) printf 'error: BREAK_QNX_ON_AD must be 0 or 1\n' >&2; exit 2 ;;
esac
root="${BREAK_QNX_TARGET_ROOT:-/tmp/bt}"
TMPDIR="${BREAK_QNX_TMPDIR:-$root/tmp}"
mkdir -p "$TMPDIR" || exit 2
export TMPDIR
asan_lock=${BREAK_QNX_ASAN_LOCK:-}
if [ -n "$asan_lock" ]; then
    case "$asan_lock" in
        /*) ;;
        *) printf 'error: BREAK_QNX_ASAN_LOCK must be an absolute path\n' >&2; exit 2 ;;
    esac
    case "$asan_lock" in
        *[!A-Za-z0-9_./-]*) printf 'error: BREAK_QNX_ASAN_LOCK has unsupported characters\n' >&2; exit 2 ;;
    esac
    if ! mkdir "$asan_lock"; then
        printf 'error: another ASan run holds the target lock: %s\n' "$asan_lock" >&2
        exit 3
    fi
    trap 'rmdir "$asan_lock" 2>/dev/null || true' EXIT
    trap 'exit 3' HUP INT TERM
    printf 'info: ASan target lock acquired: %s\n' "$asan_lock"
fi
normal_root=${BREAK_QNX_NORMAL_ROOT:-}
if [ -n "$normal_root" ]; then
    case "$normal_root" in
        /*) ;;
        *) printf 'error: BREAK_QNX_NORMAL_ROOT must be an absolute path\n' >&2; exit 2 ;;
    esac
    case "$normal_root" in
        *[!A-Za-z0-9_./-]*) printf 'error: BREAK_QNX_NORMAL_ROOT has unsupported characters\n' >&2; exit 2 ;;
    esac
    if [ ! -d "$normal_root" ]; then
        printf 'error: BREAK_QNX_NORMAL_ROOT is not a directory: %s\n' "$normal_root" >&2
        exit 2
    fi
fi
vulkan_cxx_preload=""
vulkan_redirect_preload=""
vulkan_library_path=""
case "${BREAK_QNX_VULKAN_RUNTIME:-0}" in
    0) ;;
    1)
        if [ -n "${LD_PRELOAD:-}" ]; then
            printf 'error: BREAK_QNX_VULKAN_RUNTIME requires LD_PRELOAD to be unset\n' >&2
            exit 2
        fi
        vulkan_root="$root/swiftshader"
        vulkan_cxx="$vulkan_root/lib/libc++.so.2"
        for required in \
            "$root/libvulkan.so.1" \
            "$vulkan_root/libvk_swiftshader.so" \
            "$vulkan_root/libshaderc_shared.so.1" \
            "$vulkan_cxx" \
            "$vulkan_root/libgraphics_conf_redirect.so" \
            "$vulkan_root/graphics.conf" \
            "$vulkan_root/swiftshader_icd.json"; do
            if [ ! -f "$required" ]; then
                printf 'error: QNX Vulkan runtime file is missing: %s\n' "$required" >&2
                exit 2
            fi
        done
        vulkan_cxx_preload="$vulkan_cxx"
        vulkan_redirect_preload="$vulkan_root/libgraphics_conf_redirect.so"
        vulkan_library_path="$vulkan_root:$vulkan_root/lib"
        SWIFTSHADER_GRAPHICS_CONF="$vulkan_root/graphics.conf"
        VK_ICD_FILENAMES="$vulkan_root/swiftshader_icd.json"
        export SWIFTSHADER_GRAPHICS_CONF VK_ICD_FILENAMES
        printf 'info: QNX Vulkan runtime is the explicit SwiftShader software ICD, not a physical GPU\n'
        ;;
    *)
        printf 'error: BREAK_QNX_VULKAN_RUNTIME must be 0 or 1\n' >&2
        exit 2
        ;;
esac
tls_preload=""
case "${BREAK_QNX_TLS_INTERPOSE:-0}" in
    0) ;;
    1)
        if [ -n "${LD_PRELOAD:-}" ]; then
            printf 'error: BREAK_QNX_TLS_INTERPOSE requires LD_PRELOAD to be unset\n' >&2
            exit 2
        fi
        tls_asan="${BREAK_QNX_TLS_ASAN:-$root/libasan.so.8}"
        tls_ubsan="${BREAK_QNX_TLS_UBSAN:-$root/libubsan.so.1}"
        tls_hook="${BREAK_QNX_TLS_HOOK:-$root/libqnx_tls_general_interpose.so}"
        for required in "$tls_asan" "$tls_ubsan" "$tls_hook"; do
            if [ ! -f "$required" ]; then
                printf 'error: QNX TLS interpose library is missing: %s\n' "$required" >&2
                exit 2
            fi
        done
        tls_preload="$tls_asan:$tls_ubsan:$tls_hook"
        printf 'info: QNX TLS interpose per-process preload: %s\n' "$tls_preload"
        ;;
    *)
        printf 'error: BREAK_QNX_TLS_INTERPOSE must be 0 or 1\n' >&2
        exit 2
        ;;
esac
sanitizer_preload=""
case "${BREAK_QNX_SANITIZER_CLEANUP:-0}" in
    0) ;;
    1)
        if [ "${BREAK_QNX_VULKAN_RUNTIME:-0}" != 1 ]; then
            printf 'error: BREAK_QNX_SANITIZER_CLEANUP requires BREAK_QNX_VULKAN_RUNTIME=1\n' >&2
            exit 2
        fi
        if [ "${BREAK_QNX_TLS_INTERPOSE:-0}" != 0 ]; then
            printf 'error: BREAK_QNX_SANITIZER_CLEANUP is incompatible with BREAK_QNX_TLS_INTERPOSE\n' >&2
            exit 2
        fi
        if [ -n "${LD_PRELOAD:-}" ]; then
            printf 'error: BREAK_QNX_SANITIZER_CLEANUP requires LD_PRELOAD to be unset\n' >&2
            exit 2
        fi
        sanitizer_stdcxx="${BREAK_QNX_SANITIZER_STDCXX:-$root/libstdc++.so.6}"
        sanitizer_asan="${BREAK_QNX_SANITIZER_ASAN:-$root/libasan.so.8}"
        sanitizer_ubsan="${BREAK_QNX_SANITIZER_UBSAN:-$root/libubsan.so.1}"
        sanitizer_helper="${BREAK_QNX_SANITIZER_CLEANUP_LIB:-$root/libqnx_sanitizer_cleanup.so}"
        for required in "$sanitizer_stdcxx" "$sanitizer_asan" "$sanitizer_ubsan" "$sanitizer_helper"; do
            case "$required" in
                /*) ;;
                *) printf 'error: sanitizer runtime paths must be absolute: %s\n' "$required" >&2; exit 2 ;;
            esac
            case "$required" in
                *[!A-Za-z0-9_+./-]*) printf 'error: sanitizer runtime path has unsupported characters: %s\n' "$required" >&2; exit 2 ;;
            esac
            if [ ! -f "$required" ]; then
                printf 'error: sanitizer cleanup input is missing: %s\n' "$required" >&2
                exit 2
            fi
        done
        sanitizer_preload="$sanitizer_stdcxx:$sanitizer_asan:$sanitizer_ubsan:$sanitizer_helper"
        printf 'info: QNX test-only sanitizer cleanup preload: %s\n' "$sanitizer_preload"
        ;;
    *)
        printf 'error: BREAK_QNX_SANITIZER_CLEANUP must be 0 or 1\n' >&2
        exit 2
        ;;
esac
# Cross libs deployed beside the binaries (e.g. libscreen.so.1 when the
# engine links the Screen window layer but the target image lacks it).
LD_LIBRARY_PATH="$root${vulkan_library_path:+:$vulkan_library_path}${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
export LD_LIBRARY_PATH
cd "$root" || exit 2
list="${1:-cmds.txt}"
if [ ! -f "$list" ] || [ ! -r "$list" ]; then
    printf 'error: command list is not readable: %s\n' "$list" >&2
    exit 2
fi
pass=0; fail=0; failed=""
while IFS= read -r line; do
    [ -z "$line" ] && continue
    expect_fail=0
    case "$line" in
        EXPECT_FAIL\ *) expect_fail=1; line=${line#EXPECT_FAIL };;
    esac
    run_line="$line"
    if [ -n "$normal_root" ]; then
        case "$line" in
            ./test_break_lua_runtime*|./test_break_lua_value*|./test_break_lua_binding*|\
            ./test_runtime_io*|./test_runtime_reload*|./test_break_crash*)
                death_exe=${line#./}
                death_exe=${death_exe%% *}
                if [ ! -x "$normal_root/$death_exe" ]; then
                    printf 'error: normal death-test child is missing: %s\n' "$normal_root/$death_exe" >&2
                    exit 2
                fi
                run_line="env BREAK_QNX_DEATH_CHILD=$normal_root/$death_exe $line"
                printf 'info: normal death-test child starts without LD_PRELOAD (no child ASan coverage): %s\n' "$normal_root/$death_exe"
                ;;
            on\ -ad\ env\ *)
                death_exe=${line#on\ -ad\ env\ }
                death_exe=${death_exe#* }
                death_exe=${death_exe#* }
                death_exe=${death_exe#./}
                death_exe=${death_exe%% *}
                case "$death_exe" in
                    test_break_lua_runtime|test_break_lua_value|test_break_lua_binding|test_runtime_io|test_runtime_reload|test_break_crash)
                        if [ ! -x "$normal_root/$death_exe" ]; then
                            printf 'error: normal death-test child is missing: %s\n' "$normal_root/$death_exe" >&2
                            exit 2
                        fi
                        run_line="on -ad env BREAK_QNX_DEATH_CHILD=$normal_root/$death_exe ${line#on\ -ad\ env\ }"
                        printf 'info: normal death-test child starts without LD_PRELOAD (no child ASan coverage): %s\n' "$normal_root/$death_exe"
                        ;;
                esac
                ;;
        esac
    fi
    case "$line" in
        *test_mypal_screen_ipc*)
            if [ -z "${BREAK_QNX_IPC_CHILD:-}" ] && [ -n "$normal_root" ]; then
                BREAK_QNX_IPC_CHILD=$normal_root/test_mypal_screen_ipc
            fi
            if [ -n "${BREAK_QNX_IPC_CHILD:-}" ]; then
                case "$BREAK_QNX_IPC_CHILD" in
                    /*) ;;
                    *) printf 'error: BREAK_QNX_IPC_CHILD must be an absolute path\n' >&2; exit 2 ;;
                esac
                case "$BREAK_QNX_IPC_CHILD" in
                    *[!A-Za-z0-9_./-]*) printf 'error: BREAK_QNX_IPC_CHILD has unsupported characters\n' >&2; exit 2 ;;
                esac
                if [ ! -x "$BREAK_QNX_IPC_CHILD" ]; then
                    printf 'error: IPC child is not executable: %s\n' "$BREAK_QNX_IPC_CHILD" >&2
                    exit 2
                fi
                case "$run_line" in
                    on\ -ad\ env\ *)
                        run_line="on -ad env BREAK_MYPAL_IPC_CHILD_EXECUTABLE=$BREAK_QNX_IPC_CHILD ${run_line#on\ -ad\ env\ }"
                        ;;
                    env\ *)
                        run_line="env BREAK_MYPAL_IPC_CHILD_EXECUTABLE=$BREAK_QNX_IPC_CHILD ${run_line#env\ }"
                        ;;
                    *)
                        run_line="env BREAK_MYPAL_IPC_CHILD_EXECUTABLE=$BREAK_QNX_IPC_CHILD $run_line"
                        ;;
                esac
                printf 'info: normal IPC child starts without LD_PRELOAD (no child ASan coverage): %s\n' "$BREAK_QNX_IPC_CHILD"
            fi
            ;;
    esac
    if [ -n "$tls_preload$vulkan_cxx_preload$vulkan_redirect_preload$sanitizer_preload" ]; then
        command_preload="$vulkan_cxx_preload${vulkan_redirect_preload:+:$vulkan_redirect_preload}"
        case "$line" in
            *test_qnx_asan_tls_capacity*)
                printf 'info: legacy scoped TLS shim retained for %s\n' "$line"
                ;;
            *test_break_lua_runtime*|*test_break_lua_value*|*test_break_lua_binding*|\
            *test_runtime_facade*|*test_runtime_io*|*test_runtime_reload*|\
            *test_break_crash*|*test_rule_engine_stream_ext*|*test_mypal_screen_ipc*)
                if [ -n "$tls_preload" ]; then
                    printf 'info: fork-uncovered test retained without TLS interpose: %s\n' "$line"
                fi
                if [ -n "$sanitizer_preload" ]; then
                    command_preload="${vulkan_cxx_preload:+$vulkan_cxx_preload:}$sanitizer_preload${vulkan_redirect_preload:+:$vulkan_redirect_preload}"
                fi
                ;;
            *)
                if [ -n "$sanitizer_preload" ]; then
                    command_preload="${vulkan_cxx_preload:+$vulkan_cxx_preload:}$sanitizer_preload${vulkan_redirect_preload:+:$vulkan_redirect_preload}"
                elif [ -n "$tls_preload" ]; then
                    command_preload="${vulkan_cxx_preload:+$vulkan_cxx_preload:}$tls_preload${vulkan_redirect_preload:+:$vulkan_redirect_preload}"
                fi
                ;;
        esac
        if [ -n "$command_preload" ]; then
            case "$run_line" in
                on\ -ad\ env\ *)
                    run_line="on -ad env LD_PRELOAD=$command_preload ${run_line#on\ -ad\ env\ }"
                    ;;
                env\ *)
                    run_line="env LD_PRELOAD=$command_preload ${run_line#env\ }"
                    ;;
                *)
                    run_line="LD_PRELOAD=$command_preload $run_line"
                    ;;
            esac
        fi
    fi
    if [ "${BREAK_QNX_ON_AD:-0}" = 1 ]; then
        case "$run_line" in
            on\ -ad\ env\ *) ;;
            env\ *) run_line="on -ad $run_line" ;;
            *) run_line="on -ad env $run_line" ;;
        esac
    fi
    sh -c "$run_line" > out_cmd.log 2>&1
    rc=$?
    ok=0
    if [ "$expect_fail" -eq 0 ] && [ "$rc" -eq 0 ]; then ok=1; fi
    if [ "$expect_fail" -eq 1 ] && [ "$rc" -ne 0 ]; then
        ok=1
        case "$line" in
            ./test_qnx_sanitizer_leak|on\ -ad\ env\ ./test_qnx_sanitizer_leak)
                leak_log=$(cat out_cmd.log)
                case "$leak_log" in
                    *LeakSanitizer*123\ byte\(s\)\ leaked*|*123\ byte\(s\)\ leaked*LeakSanitizer*) ;;
                    *)
                        ok=0
                        printf 'error: test_qnx_sanitizer_leak requires LeakSanitizer and 123 byte(s) leaked in out_cmd.log\n' >&2
                        ;;
                esac
                ;;
        esac
    fi
    if [ "$ok" -eq 1 ]; then
        pass=$((pass + 1))
        printf 'PASS %s\n' "$line"
    else
        fail=$((fail + 1))
        failed="$failed [$line]"
        printf 'FAIL %s (rc=%d expect_fail=%d)\n' "$line" "$rc" "$expect_fail"
        cp out_cmd.log "out_FAIL_$fail.log"
    fi
done < "$list"
if [ "$pass" -eq 0 ] && [ "$fail" -eq 0 ]; then
    printf 'error: no runnable tests in %s\n' "$list" >&2
    exit 2
fi
printf '\n=== QNX target results: %d passed, %d failed ===\n' "$pass" "$fail"
[ -n "$failed" ] && printf 'failed:%s\n' "$failed"
[ "$fail" -eq 0 ]
