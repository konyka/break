# Test Fork EINTR Cleanup Design

## 背景与根因

`engine/tests/test_fork.h` 的 `test_waitpid_deadline` 用 `waitpid(pid, status, WNOHANG)` 轮询子进程。当前实现把任何非零返回值直接交给调用方，因此 `-1/EINTR` 会提前结束等待。此时子进程可能仍在运行，调用方既没有得到终态，也不会执行超时后的 kill/reap。阻塞式回收路径已经正确处理 EINTR。

该问题只存在于 POSIX 测试基础设施。它不修改产品运行时、渲染、资源或网络行为，也不处理 qemu-user 下 fork 后建线程偶发挂起或 Windows scene 单例失败的独立根因。

## 目标

保持 `test_waitpid_deadline(pid, status, timeout_ms)` 的签名和既有返回约定不变：

- 子进程在期限内结束：返回 `pid` 并写入真实 `status`。
- 期限到期：kill/reap，清零 `status`，返回 0。
- `waitpid` 返回 EINTR：继续轮询，不丢弃子进程或期限。
- 其他 `waitpid` 错误：保留 -1 返回；当 `pid > 0` 且错误不是 ECHILD 时，执行 kill/reap，最后清零 `status`。ECHILD 或无效 PID 不发送信号。

回收逻辑与现有超时路径共用同一个静态内联辅助函数，避免两份实现漂移。

## 测试设计

在 `test_fork_deadline.c` 内先包含真实系统声明，再用编译期宏仅替换该测试翻译单元中的 `waitpid` 和 `kill`。删除文件顶部已有的直接 `test_fork.h` 包含，确保首次且仅一次包含位于宏区域内。`#undef` 后定义包装器，使后续调用进入真实 libc 实现。包装器可以注入一次 EINTR、EIO 或记录 kill；防护用例启用只记录、不转发信号的 kill spy，防止错误实现对进程组或重用 PID 真实发信号。不修改其他测试或产品源文件，不依赖信号到达时机或 sleep 制造中断。

新增五个用例，连同现有五例达到 10 例：

1. 正常退出的子进程第一次 wait 返回 EINTR：helper 必须再次调用并最终返回 `pid` 和真实退出码。
2. 卡死子进程第一次 wait 返回 EINTR：helper 必须经过至少 50 ms 期限后 kill/reap，返回 0 且 `status == 0`。在兜底前测量时间，防止把 EINTR 误当立即超时。
3. 卡死子进程第一次 wait 返回 EIO：helper 必须返回 -1，但至少再调用一次真实 `waitpid` 完成 kill/reap，并将 `status` 清零。
4. 已被回收的 PID：helper 返回 -1、清零 `status`，kill spy 必须为 0，禁止对 ECHILD 再发信号。
5. PID 0 且注入 EIO：helper 返回 -1、清零 `status`，kill spy 必须为 0，禁止对进程组或无效 PID 发信号。

测试兜底 `test_waitpid_fallback_reap` 只使用真实 `waitpid`：先用 WNOHANG 检查；只有返回 0、确认该子进程仍存活时才 kill 并回收；返回 `pid` 表示兜底进行了回收，ECHILD 表示无需处理。所有结果、状态、调用计数和计时都在兜底前保存。EIO 用例必须断言“兜底未进行清理”，独立证明 helper 自己已经 kill/reap，不能由兜底制造假绿。

每个派生子进程的用例都在断言前执行兜底，保证 RED 不遗留子进程；兜底不再次 kill 已回收或 PID 可能已重用的对象。

## 验收

先看到五个新用例在旧实现上按各自原因失败：前三个错误所有权/清理失败，后两个至少因错误状态未清零而失败。最小修改后达到 `test_fork_deadline` 10/10。随后运行现有 `test_runtime_io`、`test_runtime_reload`、`test_core_app_diagnostics` 以及完整图形/测试矩阵。POSIX 之外的既有条件跳过保持不变。

## 文档与交付

追加 `docs/Build_Guide.md`、`docs/Implementation_Status.md` 和 `docs/cross_engine/missing_capabilities.md` 的测试基础设施记录。独立代码评审后同步最新 `origin/master`，直接推送 `master`，不创建 PR，并核验最终工作流。

## 后续复审：持续 EINTR 的绝对截止时间

初版实现用无条件 `continue` 重试 EINTR，因而跳过超时计数和轮询睡眠。一次中断的五个原用例无法覆盖持续中断：如果中断持续存在，期限实际被无限延长，并形成忙轮询。初版“保留超时计数”的实现约束由此被后续修正取代。

当前实现仍在每次循环开头调用 `waitpid(..., WNOHANG)`，正常终态立即返回，非 EINTR 错误沿用既有清理策略；EINTR 与返回 0 都必须检查进入函数时由 `CLOCK_MONOTONIC` 计算的绝对截止时间，未到期才睡眠。10 ms 轮询间隔只是睡眠上限，不再充当期限计数。这样 timeout=0、nanosleep 自身被中断以及持续 waitpid EINTR 都不会重置或延长截止时间。

新增第六个确定性故障注入用例：仅对 WNOHANG 轮询持续注入 200 ms EINTR，helper 期限为 50 ms，清理阶段不注入错误。旧实现实测约 275 ms 才 kill/reap，且进行约 722 万次等待调用；新实现约 50–60 ms 完成。用例在断言前以真实 waitpid fallback 验证回收，要求 `cleanup=0`，并检查返回 0、清零状态、至少两次等待以及实际用时小于注入窗口。测试总数由 10 增至 11。
