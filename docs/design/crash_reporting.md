# Crash Reporting — Stage 5 Phase C（捕获 + 本地 spool + 脱敏 + 上传接缝）

`break_crash` 的崩溃捕获、有界本地 spool、纯函数脱敏与调用方上传接缝。
Phase C 交付的是**客户端机制**：仓库内**无任何服务端代码、无任何真实传输
代码**（计划 Global Constraints）；服务端符号化/聚类/回归统计与真实传输
属 Phase D+（§9）。脱敏契约的上游是
`docs/design/security_threat_model.md` §6（本文为其客户端执行点）。

- 实现：`engine/src/crash/break_crash.h/.c`（逐条语义、记录语法字节级规范、
  handler 白名单以头注释为准；本文为设计契约与诚实边界）
- 测试：`engine/tests/test_break_crash.c`（36 例；fork 崩溃用例父子双钉
  WIFSIGNALED+WTERMSIG **与**记录内容）
- 上游契约：原子写（`platform_fs.h` 的 `PlatformAtomicWriter`）、构建身份
  （`break_version.h`）、脱敏义务（`security_threat_model.md` §6）

## 1. 捕获清单（捕获什么 / 不捕获什么）

**捕获什么**（每条记录，恰好一次崩溃/进程运行）：

| 字段 | 来源 | 说明 |
|---|---|---|
| signo / code | siginfo_t | 信号号与 si_code（u32 hex8） |
| fault_addr | siginfo_t si_addr | 故障地址（hex16） |
| pid / tid | getpid / syscall(SYS_gettid) | 进程本地标识符（hex16） |
| rip / rsp / rbp | ucontext（Linux x86-64） | 其余架构为 0（文档化降级） |
| build-id | install 期 `break_version_string()` 的 "+" 后缀 | 字符集 `[0-9a-z-]`，无后缀则 `"unknown"` |
| module 行（≤64） | install 期解析 /proc/self/maps | 文件-backed 映射按捕获序合并；每条 = ELF load bias + 尺寸 + **basename** 名 |
| stack-window（≤4 KiB） | handler 内拷 [rsp, rsp+4KiB) | 栈溢出守卫：SIGSEGV 故障地址落在 rsp±8 KiB 内或 rsp==0 → 空窗口；再经 argv/env 隐私区钳制（§2） |
| context-blob（≤4 KiB） | `break_crash_set_context_blob` 发布时拷入预分配槽 | **app 预脱敏义务**（§6.3 白名单字段）；发布期截断 |

**不捕获什么（privacy-by-omission，捕获侧执行）**：

| 永不捕获 | 机制 |
|---|---|
| 命令行参数（argv） | 不读；栈窗口经 zone_lo 钳制（下） |
| 环境变量（env，含 HOME/SECRET 类） | 不读；同上钳制 |
| 用户名/宿主标识 | 不读（无 getpwuid/hostname 调用） |
| peer 地址 / IP / 端口 / 连接 identity | 不读（无网络栈接触） |
| secrets / tokens / 完整网络 payload | §6.4 零记录义务；无捕获面 |
| 其他线程的寄存器/栈 | 只捕获故障线程 ucontext 与故障线程栈窗口 |
| 堆内容 / 全量内存 | 无 minidump；只有有界栈窗口 |
| 时间戳 | 不采集（关联/排序由服务端按到达序做） |

**argv/env 隐私区钳制（Task 2 交付，捕获侧封堵）**：argv/env 字符串块位于
初始 `[stack]` 映射顶部；浅主线程崩溃的窗口本会把它 hex 转储进记录。
install 期计算 `zone_lo` = argv[0]（glibc `program_invocation_name`）与全部
environ 字符串中落在 `[stack]` 内的最低地址；handler 把窗口钳在
`zone_lo` 之下（rsp 落入区内 → 空窗口）。线程栈不带 argv/env，不钳。

**该钳制的测试钉是概率性的，如实注明**：`crash_segv_captures_record` 的
HOME hex 泄漏钉单次执行敏感性约 10-40%（浅崩溃窗口是否触达字符串块随
libc/测试 harness 栈深变化），单次绿不证明钳制；其牙在 lane×CI 多轮重复
（钳制关闭时 12 连跑即现 1 次泄漏）。**钳制正确性不由该概率钉承担**——
Task 2 审查以反例独立实证：钳制禁用 → HOME hex 1/12 泄漏；启用 → 0/16；
且 `window_len == zone_lo − rsp` 逐字节核验。

## 2. 异步信号安全白名单（handler 的完整调用集）

审查逐行核验的**白名单**（`break_crash.h` 钉住，Task 2 审查另在二建制
-O0/-O2 上以重定位枚举复核：handler externals 恰为
{fsync, getpid, lseek, syscall, write}，die 尾恰为
{signal, sigemptyset, sigaddset, sigprocmask, raise, _exit}，无编译器合成
memcpy/atomics）：

| 调用 | 依据 |
|---|---|
| siginfo_t / ucontext_t 字段读 | 纯内存，无 libc |
| `atomic_flag_test_and_set` | C11 恒 lock-free 类型（7.14.1.1 允许信号内 lock-free 原子操作）；一次性捕获守卫 |
| `getpid()` | POSIX.1 async-signal-safe 清单 |
| `syscall(SYS_gettid)` | Linux 直陷入口经无状态 libc trampoline（无 TLS/锁；gettid 不会失败故无 errno 写）；不在 POSIX 清单仅因其非 POSIX |
| `lseek` / `write` / `fsync` | POSIX.1 清单（作用于 install 期**预打开**的 inbox fd——handler 从不 open） |
| `signal` / `sigemptyset` / `sigaddset` / `sigprocmask` / `raise` / `_exit` | POSIX.1 清单（恢复并死尾：SIG_DFL + 解除阻塞 + raise → 进程按原语义死，core dump/WIFSIGNALED 保持；`_exit(128+sig)` 兜底） |
| `bs_*` 纯内存 hex 追加助手 | 手写，零 libc |

**handler 内禁止**：malloc/free、stdio、open、锁/pthread、白名单外一切
libc（格式化构造上纯内存）。install 期预置：模块表、build id、64 KiB 记录
缓冲、4 KiB blob 槽、预打开 inbox fd。

**一次性捕获**：每进程运行恰好捕获一次崩溃；任何重入（嵌套信号或第二个
崩溃线程竞入）直接进恢复-死尾，不做嵌套格式化。不用 SA_NODEFER、不用
SA_ONSTACK：栈溢出深到破坏 handler 自身帧时记录丢失但死法保持（fail
closed）。

## 3. 记录格式（break-crash-v1，摘要）

canonical 文本：LF + 可打印 ASCII 子集、固定键序、定宽小写 hex、恰好一个
结尾 LF、总 ≤64 KiB；模块 ≤64、stack-window/context-blob 各 ≤4 KiB。
**任何偏差 → parse NULL**（唯一 oracle；两段式：先全量校验再填充）。
字节级规范与两个 writer（正常上下文 builder/serialize 与信号侧 writer）
的字节互锁钉以 `break_crash.h` 与测试为准，本文不重复。

构造上界：最大记录（64 模块 ×255 字节名 + 4 KiB 窗口 + 4 KiB blob）约
35.8 KB——64 KiB 帽从 writer 侧不可达，仍在 emit 处强制。

## 4. inbox → pending 恢复序列（crash-spool recovery，roadmap 验收行）

spool 布局：`<root>/{crash.inbox, pending/, sent/, discarded/}`。
`break_crash_spool_open` 的恢复序（全部有界 IO：≤64 KiB 读 + 每类 ≤4096
条目录枚举）：

1. 建布局（root + 三类目录），重导 next-id = 三类现有 canonical id 最大
   值 + 1；
2. inbox 不存在或空 → 无需恢复；
3. 非空 inbox：≤64 KiB 才读（更大不整读即判 invalid）→
   `break_crash_record_parse`：
   - **字节合法** → 经 PlatformAtomicWriter 提交为 `pending/<next-id>.bcr`
     （tmp+fsync+rename+dir fsync）→ inbox 原子重置为空 → pending
     retention；
   - **其他一切**（撕裂/垃圾/超尺寸/不可读）→ 整体 rename 进
     `discarded/<next-id>.bcr`（取证字节完整保留）→ inbox 重建为空 →
     discarded retention；
4. 恢复期任何持久化失败 → open 返回 NULL，inbox 留在原地可下次恢复
   （fail closed，绝不阻塞启动超过有界 IO）。

**AT-LEAST-ONCE**：pending 提交与 inbox 重置之间崩溃 → 下次 open 以新 id
重复恢复同一记录（重复窗口文档化；去重是服务端事务）。恢复永不丢记录。
验收测试对号：`spool_inbox_recover_valid` /
`spool_inbox_recover_torn_garbage_oversize`（恢复语义）+
`crash_recovery_upload_end_to_end`（fork 崩溃 → 下次 open 恢复 → 脱敏 →
上传 端到端）+ `spool_retention_*`（retention 恢复）。

## 5. Retention 与 backoff（重试/丢弃）策略

**Retention**（`BREAK_CRASH_SPOOL_KEEP = 16`/类）：pending/sent 溢出 →
最旧（最小 id）迁入 discarded；discarded 溢出 → 最旧**删除**。计数经
`break_crash_spool_count` 可观测。记录文件名 canonical（`<id>.bcr`，id≥1
十进制无前导零）；外来（非 canonical）条目永不计数/移动/删除。

**Backoff**（上传失败簿记，`pending/<id>.meta` sidecar）：

```text
break-crash-meta-v1
attempts: <u32 十进制，无前导零>
```

- up()==false → attempts++ 并经 PlatformAtomicWriter 重写 sidecar（崩溃
  窗口新旧二值、无撕裂）；attempts 达 5（`BREAK_CRASH_UPLOAD_ATTEMPTS_MAX`）
  → record 迁 discarded（第 5 次失败即丢弃），sidecar 随之删除；
- sidecar 生命周期绑定 record 在 pending 的停留：mark_sent /
  mark_discarded / retention 隔离任一路径离开 pending 都删除 sidecar；
  sent/discarded 永不持 .meta（Task 4 审查钉
  `upload_retention_overflow_removes_sidecar`）；
- **损坏 sidecar → 读 0，下一个失败 pass 原子重写自愈（一个 pass 内）**：
  重试元数据是本地簿记而非信任边界输入，元数据损坏永不销毁崩溃证据。
  读取拒绝九类结构偏差（尺寸 0/≥64/无前缀/缺尾 LF/>10 位/前导零/非数字/
  >u32max/短读），外加 **attempts ≥ 5 的静置值视同外来损坏**（writer 只
  产出 1..4——第 5 次失败改走丢弃；钳制关闭外来 u32-max 回绕到 0 换取
  无限重试的通道；钉 `upload_sidecar_u32max_clamped_as_corrupt` 与
  `upload_corrupt_sidecar_self_heals_one_pass`）；
- sidecar **写失败**（盘上 IO 坏）→ 本次计数不前进、record 留 pending：
  持久不可写 spool 使 5 次上界退化（文档化降级——保证据优先；spool 可写
  本是 put_pending 的前提）。

## 6. 上传接缝契约（BreakCrashUploadFn）

```c
typedef bool (*BreakCrashUploadFn)(void *user, const void *record_bytes, usize len);
u32 break_crash_spool_upload_pending(BreakCrashSpool *s, BreakCrashUploadFn up, void *user);
```

- **app 拥有传输**：回调注入（Phase B `BreakUpdateFetchFn` 同型）；仓库内
  以 in-process fake 测试，**零 socket/HTTP/TLS/curl 代码**；
- 遍历 pending **newest-first**（id 快照，mark 引起的索引漂移构造上不可
  能），每 record 每 pass 至多一次 up()；
- 每 record：读 → parse → **redact → serialize → up()**——up() 收到的恒
  为**脱敏后** canonical 字节；不可 parse 的 pending 项（外来植入）→ 直接
  discarded 且**不调 up()**（永不发不可脱敏字节）；redact/serialize 失败
  （实践中仅 OOM）→ 本 pass 跳过（证据不因瞬时资源错误丢弃）；
- **true = 已送达**（→ mark_sent）；**false = 可重试失败**（→ attempts++
  按 §5）；返回值 = 本 pass 成功上传计数；NULL spool/up → 0（INVALID 类
  no-op，零副作用）；
- **at-least-once**：up()==true 后 mark_sent 失败 → record 留 pending，
  下一 pass 重发同一记录（字节相同）；**去重是服务端事务**；
- up() 以 *user 不透明运行；不得回调同一 spool（单 owner，不可重入）。

## 7. 脱敏执行点（§6 契约的客户端落地）

`break_crash_record_redact` = 纯函数（输入永不变），输出新 record。
字段级规则：signo/code/fault_addr/pid/tid/rip/rsp/rbp 原样保留（进程本地
标识符与地址——威胁模型注记：地址不是用户数据；符号化必需）；build-id
原样（`[0-9a-z-]` 构造上不能编码路径）；module offset/size 原样；module
**名 → basename**（'/' 与 '\\' 双分隔符，幂等；空 basename → 占位符
`"redacted"`）；stack-window 直通（argv/env 泄漏已在捕获侧 zone_lo 封堵）；
context-blob 直通（**app 预脱敏义务**——白名单字段义务见 §6.3）。上传只
发脱敏字节；spool 存证字节不被上传改写（full-fidelity 本地取证）。

## 8. 符号化契约（客户端永不符号化）

> 服务端消费这些输入的参考实现见 `crash_symbolization.md`（2026-10-30）：
> 对非 PIE 可执行文件用 `RIP` 本身、对共享库与 PIE 用 `RIP − load bias`
> 查符号，并沿保存的 RBP 链从栈窗口恢复最多 32 帧（帧指针展开，不是 DWARF）。

**客户端永不符号化**——无符号表、无 backtrace 展开、无调试路径读取。
记录携带的符号化输入（服务端消费）：

- **build-id**：定位该构建的符号库（symbol store 索引键）；
- **module 行**：basename + ELF load bias + 尺寸——服务端以
  `RIP − load bias` 得模块内文件相对地址，对该模块的符号表 addr2line；
- **RIP**（+ fault_addr、siginfo code）：崩溃点；**stack-window** 原始字节
  供栈分析（无服务端不可推导的展开帧——客户端不做 unwind）；
- pid/tid：崩溃关联/去重维度（进程本地，非用户数据）。

跨架构：非 x86-64 Linux 的寄存器为 0（文档化降级），符号化输入退化为
build-id + 模块表 + siginfo。Windows 记录格式不在本阶段（§9）。

## 9. 明确 NOT delivered 清单

以下各项**明确不在本 Phase 交付**，不得由本文任何契约推断为已有能力：

1. **服务端**：**2026-10-30 起库内有参考实现**（符号化、聚类、回归统计、
   记录接收端 `break_crash_server`，见 `crash_symbolization.md`）；仍然没有
   生产服务（无上传者认证、无按客户端限速、不保存记录本身、无保留策略）；
2. **真实上传传输**：**2026-10-30 起有 `break_crash_upload_http`**（经
   `break_http` 的 TLS POST，实现 §6 的回调接缝，`crash_symbolization.md`
   §5）；它是独立的库，**没有任何发布二进制链接它**，应用侧尚未接入；
3. **GPU/RHI/网络/输入摘要的自动采集**：2026-10-30 起库内已有摘要构建器
   `BreakCrashSummary`（`break_crash_summary_init/set/format`）：按
   `[section]` 分组的 `key=value` 文本，最多 16 段、64 条，值截断为 63 B；
   非可打印字符、`=`、`/`、`\` 一律替换为 `_`，因此不会携带路径或换行，
   §6 脱敏义务由构造保证。只输出完整行，不超过 4 KiB，与
   `break_crash_set_context_blob` 直接对接。测试
   `context_summary_sections_bounded_and_sanitized`；变异检查：去掉 `/`
   替换后变红。导出符号合约随之从 36 个扩为 39 个。**仍未交付**：各子系统
   自动填写摘要（break_crash 不进 engine/demos/editor 链接闭包，由契约
   ctest 钉住，因此只能由 app 侧集成）；
4. **minidump/PE 格式**：本记录格式 = canonical 文本 break-crash-v1，非
   minidump；Windows 侧的 PE/minidump 生态不接；
5. **Windows SEH/VEH**：`_WIN32` 为文档化编译期 stub（`break_crash_install`
   返回 false），POSIX 信号路径仅 Linux 实测；
6. fuzz lane：`Not Run`（house 惯例，本仓库未构建 fuzz target）。

## 10. 证据索引

- `engine/src/crash/break_crash.h`：记录语法字节级规范、spool 语义、
  handler 白名单、上传 seam/sidecar 契约（逐条语义唯一权威）。
- `engine/src/crash/break_crash.c`：实现（install 期预置、handler、spool、
  redact/upload、Task 4 审查修复：AtomicWriter 三处 commit 恒执行、
  sidecar ≥5 钳制）。
- `engine/tests/test_break_crash.c`：36 例（builder/parse 字节互锁、拒绝
  电池、retention 16/16/16、inbox 恢复、fork 崩溃捕获 5 例、redact/upload
  含端到端验收、Task 4 三钉）。
- `docs/design/security_threat_model.md` §6：脱敏契约（本文为其客户端执行
  点）；§10 NOT-delivered 同步。
- 服务端半侧（2026-10-30）：`docs/design/crash_symbolization.md`；
  `engine/src/crash/break_crash_{symbolize,cluster,upload_http}.*`、
  `engine/tools/break_crash_{server,report}.c`、`engine/tests/test_break_crash_{symbolize,cluster,upload_http,e2e}`。
- 计划与台账：`docs/superpowers/plans/2026-10-24-stage5-crash-reporting.md`；
  `.superpowers/sdd/2026-10-24-stage5-crash-reporting/progress.md` 与
  task-{1..4}-report.md。
