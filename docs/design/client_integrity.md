# Client integrity signals (`break_integrity`)

Status: delivered 2026-10-30 as an optional static library (needs `break_crypto` for SHA-256). Stage 5 subproject 5, second half.

Source: `engine/src/integrity/break_integrity.{h,c}`. Tests: `engine/tests/test_break_integrity.c` (8), `engine/tests/test_break_authority_target_contract.cmake`.

## 1. What it is, and what it is not

It **observes and reports**. Nothing else. The library has no function that allows, denies, grants or revokes anything, and it is **not an authority input**: anything a client reports about itself is untrusted, and anyone who can run code on their own machine can defeat every check here. These signals only raise the cost of casual tampering, and at most they are one input to a server-side risk score. The server never relaxes a check because a client claims to be clean (`security_threat_model.md` section 2).

This is enforced structurally, not just promised. The contract test fails when the public header declares a function that sounds like a decision (`allow`, `grant`, `deny`, `authorize`, `revoke`, `ban`, `trust`) or a pass/fail style function, and when any `break_authority` source references the integrity library, so a client signal cannot reach a ledger.

## 2. Signals

`BreakIntegritySignals` is a bit mask:

| bit | meaning |
|---|---|
| `BINT_SIG_FILE_MISMATCH` | a listed file's SHA-256 differs from the expected digest |
| `BINT_SIG_DEBUGGER` | a tracer is attached to this process |
| `BINT_SIG_UNKNOWN_MODULE` | a file-backed mapping whose basename is not in the allow-list |
| `BINT_SIG_CHECK_ERROR` | a check could not run, or the arguments were bad |

**A check that cannot run never reports clean.** A missing or unreadable file, a directory instead of a file, an unreadable `/proc`, a line too long to parse, an unsupported platform, a NULL or empty argument or an over-large count all set `CHECK_ERROR`. Several bits can be set together (a mismatching file next to a missing one).

- `break_integrity_check_files(files, count)`: up to 64 files, streamed through SHA-256 in 64 KiB blocks. A short or extended file is a mismatch, not an error.
- `break_integrity_check_debugger()`: `TracerPid` in `/proc/self/status`.
- `break_integrity_check_modules(allowed, count)`: every file-backed mapping in `/proc/self/maps` must have a basename equal to an entry (up to 256 entries). Anonymous mappings and `[heap]`/`[stack]`/`[vdso]` are skipped; a `(deleted)` mapping is judged by its name. Matching is exact in both directions: an entry that is a prefix of a mapped name does not admit it, and a mapped name that is a prefix of an entry does not either.

## 3. Platforms

File hashing is portable (stdio). The debugger and module checks read `/proc` and are **Linux only**. Elsewhere they return `CHECK_ERROR`. Windows (`IsDebuggerPresent`, module enumeration) and macOS (`sysctl` P_TRACED, the dyld image list) are not implemented, and the Windows and macOS lanes were not run.

## 4. Tests and mutation checks

The debugger test runs a real tracer: a forked child calls `PTRACE_TRACEME`, stops itself, and checks that it reports the bit; a normal process reports none. The module tests build the allow-list from the test binary's own `/proc/self/maps`, show that dropping one name flags it, show that a file mapped after the list was built is flagged, and alter the longest name in both prefix directions while the rest of the list stays correct. Mutations that each turned a test red: skipping the hash comparison, counting an unreadable file as clean, ignoring the tracer, allowing a prefix match (both directions), and never reporting an unknown module. (My first two prefix checks passed vacuously: a build error left the old binary in place, and the original test also failed for a different reason. Both were redone and now fail for the intended reason.) One mutation does not change behavior and is not claimed as covered: dropping the `S_ISREG` pre-check, because `fread` on a directory fails with `EISDIR` and `ferror` already catches it; the pre-check is defence in depth.

## 5. Not delivered

- Windows and macOS implementations of the debugger and module checks.
- Integration into the editor, demos or an application: nothing links this library (pinned by the contract test), so no running binary reports these signals.
- A transport for the signals and the server-side risk scoring that would consume them.
- Code-section or memory integrity checks, anti-injection, obfuscation, anything that resists an attacker with local code execution. By design none of that is claimed.


## 补充（2026-11-20）：Linux arm64 QEMU 边界

arm64 lane 将 `test_break_integrity` 纳入统一二十项 CTest。文件哈希、正常进程无 tracer、模块白名单和参数检查等七项在 QEMU 中实际执行；`a_traced_process_reports_the_debugger_bit` 的测试设置步骤依赖 `PTRACE_TRACEME`，而 QEMU user 实测返回 `ENOSYS`（errno 38），子进程按既有代码 exit 90。

只有 exit 90 且显式设置 `BREAK_TEST_QEMU_USER=1` 时，该用例打印 `skipped (QEMU user has no PTRACE_TRACEME)` 后结束。exit 91（产品返回错误 debugger 信号）、后续 `PTRACE_CONT`/wait 断言和无显式环境值的原生运行都继续严格判红。原生 ptrace 正例实际执行且无 skip。

因此 QEMU 的 integrity 8/8 不能解释为 ptrace 正向反调试证据；它只表示七项实际用例通过加上述一个明确设置跳过。客户端完整性信号仍只是辅助观察，不能作为授权或放行依据。
