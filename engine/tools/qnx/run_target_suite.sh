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

ulimit -s 8192 2>/dev/null
root="${BREAK_QNX_TARGET_ROOT:-/tmp/bt}"
# Cross libs deployed beside the binaries (e.g. libscreen.so.1 when the
# engine links the Screen window layer but the target image lacks it).
LD_LIBRARY_PATH="$root${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
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
    sh -c "$line" > out_cmd.log 2>&1
    rc=$?
    ok=0
    if [ "$expect_fail" -eq 0 ] && [ "$rc" -eq 0 ]; then ok=1; fi
    if [ "$expect_fail" -eq 1 ] && [ "$rc" -ne 0 ]; then ok=1; fi
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
