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

## 11. core_app 自动 context-blob 接入（2026-11-22）

### 11.1 默认关闭、构建边界与生命周期

`core_app` 现在可以把运行时的 RHI/GPU、网络和输入摘要发布到现有 context-blob。该行为**运行时默认 OFF**：不传 `--crash-context DIR` 时，`CoreAppConfig.diagnostics` 为 NULL，不安装处理器、不创建 spool、不发布摘要，也不增加输入帧复制或 512 槽扫描。CMake 的 `BREAK_ENABLE_CRASH` 默认 ON 只表示构建捕获能力，不改变这个运行时默认。

- `core_app_diagnostics` 是独立 C11 静态库，只有 `core_app` 在 `TARGET break_crash` 存在时链接它；`core_app_runtime` 的源列表和依赖不增加 `break_crash`。既有 engine、演示和编辑器链接边界不变。
- CLI 同时接受 `--crash-context DIR` 与 `--crash-context=DIR`，空 DIR 以退出码 2 拒绝。其他参数和网络配置校验完成后才执行 start；start 失败在 `core_app_run` 前返回 2。
- `BREAK_ENABLE_CRASH=OFF` 仍构建 `core_app`，但选项明确报错 `core_app: --crash-context is unavailable in this build`、退出 2 且不创建 spool。它与“构建包含能力但未传选项”是两种不同状态。
- 正常顺序为：`core_app_diagnostics_start(DIR)` → 初始快照 → `core_app_run` → `core_app_diagnostics_stop()` 恰好一次 → 保留原运行结果。stop 先清空 context-blob，再 `break_crash_uninstall`。
- 初始快照使用请求的 `record`/`auto`/`vulkan`/`opengl` 后端、固定 `gpu=pending`、`live=false`、`tick=0`，其余计数全部为 0。这里的 `pending` 是 GPU 初始化状态字符串，**不是** `pending/*.bcr` 文件。
- `runtime_running` 成功写入后发布 tick 0，以实际后端和设备名替换初始值；之后在每个完整 tick 末尾发布一次。quit/max_frames 导致的未完成 tick 不发布。
- 默认真实 record 运行没有 `pending`、`sent`、`discarded` 或 `crash.inbox`。显式启用后的正常成功和运行时失败路径都执行 stop，实测均没有 pending 记录。

Windows 的 `break_crash_install` 仍是返回 false 的编译期 stub，因此启用该选项会 start 失败，不能记录为 Windows 捕获能力。非 Linux 的 full-process 测试只保留明确 skip 边界，不声称生成过真实崩溃记录。

### 11.2 privacy 字段 allowlist

`core_app_diagnostics_publish` 只生成以下三个 section；未列出的输入、网络或设备事实不得加入 blob。

| section | 允许的 key | 含义 |
|---|---|---|
| `[rhi]` | `backend`, `gpu` | record 路径固定为 `record`/`none`；live GPU 使用现有 backend/device 名称 |
| `[net]` | `live`, `seen`, `dropped` | 网络是否 live、总线事件总数、reactor 丢弃计数 |
| `[input]` | `tick`, `keys`, `pads`, `touches`, `gestures`, `touch_status`, `haptic_status` | 当前 tick、held/pressed key 数、已连接 pad 数、touch/gesture 数及状态枚举数值 |

禁止采集原始按键码、输入文本、坐标、输入设备名、触摸来源 ID，以及 IP、端口、连接 key、session id、PSK 和数据包内容。GPU 名称沿用 `BreakCrashSummary` 的截断与字符清理；hooks 和字符串只在回调期间借用。发布只在 `CoreAppThread` 上同步执行，不在 worker、网络回调或信号处理器内执行；使用栈上 POD 和固定容量缓冲，无堆分配或跨线程状态读取。

这是**本地捕获边界，不是上传功能**。`core_app` 不链接或调用 `break_crash_upload_http`，diagnostics 不读取网络地址、不建立上传连接；真实进程验收也没有上传或网络访问。独立上传适配器与参考服务的既有能力不改变这一边界。

### 11.3 已执行的 RED/GREEN 与真实 Linux 证据

Task 3 在生产 CLI 前运行 target contract 与 full-process 两项，得到预期 **0/2 通过**。严格记录验证器补强时，旧实现分别为 **3 passed / 2 failed / 5 total**，放松 seen 零断言的受控变异为 **6 passed / 1 failed / 7 total**；恢复严格实现后，独立 `test_core_app_diagnostics` 为 **7/7 通过**。

最终七项 focused CTest 为 **7/7 通过、0 失败**：`test_core_app_diagnostics`、`test_core_app_target_contract`、`test_core_app_nested_contract`、`test_core_app_crash_context`、`test_core_app_crash_build_contract`、`test_core_app_lifecycle_load_unload`、`test_core_app_runtime`。

compat/NM/config 的当前六项记录为 **3 pass + 3 expected skip + 0 fail**：`test_core_app_contract_compat`、`test_core_app_nm_symbol_missing`、`test_core_app_ctest_config_contract` 通过；`test_core_app_nm_missing`、`test_core_app_nm_unsupported`、`test_core_app_nm_symbol_missing_unsupported` 按 NM 能力合同预期跳过。另有 `test_core_app_nested_contract` 包含在上述 focused 7/7 中。

原生 Linux/LD_PRELOAD 的 full-process 验收直接启动真实 `core_app`，不是格式化工件模拟：

| 场景 | 严格结果 |
|---|---|
| 第 2 帧真实 `vfprintf` 后 `abort()` | 唯一帧标记、`Subprocess aborted`、BCR `signo: 00000006`；最后完整快照为 `backend=record`, `gpu=none`, `live=false`, `tick=1`, `seen=0`, `dropped=0`, `keys=1`, `pads=0`, `touches=0`, `gestures=0`, `touch_status=0`, `haptic_status=0` |
| `runtime_running` 转发前 `abort()` | 真实 SIGABRT；初始快照保持 `backend=record`, `gpu=pending`, `live=false`, `tick=0`，其余计数全部为 0，且没有已转发的 `runtime_running` |
| 正常成功 / 运行时失败 | 退出码分别保持 0 / 2；两条路径 sigaction 总计均为 10，pending 记录均为 0；失败路径保留 `runtime returned FAILED` |

七个零计数字段 `seen/dropped/pads/touches/gestures/touch_status/haptic_status` 都有独立非零真实记录负例，验证器必须逐项以 contract exit 5 拒绝；`gpu=pending keys=0` 的初始组合合法，错误 gpu/keys 返回 5。

当前 sanitizer/preload 强制矩阵如下，skip 不得写成真实崩溃通过：

| 强制场景 | 直接脚本退出码 | 实际含义 |
|---|---:|---|
| ASan=TRUE，runtime preload 为空 | 77 | 在创建工作目录或启动进程前明确 UNVERIFIED/skip |
| TSan=TRUE，runtime preload 为空 | 77 | 同上 |
| UBSan=TRUE，runtime preload 为空 | 0 | 完整执行 SIGABRT、initial、成功 stop、运行时失败 stop 四类用例 |
| `FAULT_SUPPORTED=FALSE` | 77 | native LD_PRELOAD 不可用，明确 UNVERIFIED/skip |

当前实际完整执行的是非 sanitizer 原生 Linux 构建；ASan/TSan 只验证了缺 runtime 的 skip 分支，未运行插桩后的 full-process 序列。完整 Vulkan/OpenGL 套件、ASan/UBSan 非图形套件与 fuzz、相关 TSan、root/default 构建契约、Windows/macOS/arm64 可用通道及远端 CI 均留待 Task 4 后续步骤执行；本节不预写其结果或 run-id。

### 11.4 最终本地验收补充（2026-11-23）

本小节记录 §11.3 之后取得的证据；上节“非 sanitizer”与“待执行”是此前时点描述，不由本节回写。

- **rebase 前 `acc3c5d2` 全套**：Vulkan **470/470**、OpenGL **468/468**，各另有 4 项条件 skip；ASan+UBSan 非图形 **443/443**（4 项条件 skip）及 fuzz **14/14**；TSan 相关 **8/8**；根 Makefiles 与 Ninja Multi-Config 契约各 **1/1**。
- **rebase 后 `321cf4f9`**：基线为 `33cc4be4`，两处追加文档冲突均保留双方内容且无冲突标记。Vulkan/OpenGL 资源交集各 **3/3**，core_app focused **7/7**，ASan 资源/崩溃交集 **7/7** + fuzz **14/14**，TSan 资源与并发交集 **9/9**，两种根契约各 **1/1**。这些是受影响交集复验，不改写成 rebase 后全套。
- **ASan 已升级证据**：使用真实 soname `libasan.so.8` 后，ASan 真实 full-process 现已通过。真实 TSan soname 为 `libtsan.so.2`；ASCII linker-script runtime 在创建工作目录或进程前返回 77，空 ASan/TSan runtime 同样返回 77，UBSan 不需要额外 runtime。ASan 早期 sigaction 懒解析和 TSan helper 去插桩仅属测试基础设施修复，`core_app` 本身保持插桩。
- **TSan 仍未验证**：本机 Fedora GCC 16/glibc 2.44 的 full-process 仍在 Lua longjmp CHECK 处退出 **66**。这不是 skip 或成功，等待 Ubuntu CI 独立结果。
- **macOS ARM64 分阶段证据**：中间 `0ddd` 的 Metal 全量 **435/435**、MoltenVK 修正 SDK 前缀后全量 **438/438**，各另有 5 项条件 skip（含 crash_context）。MoltenVK 初轮 staging 失败源于 Homebrew 顶层 include 符号链接，改用实际 `vulkan-headers`/`shaderc` 前缀后才通过，不记作一次全绿。最终 `321cf4f9` 上两套资源/diagnostics/lifecycle 交集各 **7/7**（其中 crash_context 明确 skip），graphics/gpu 各 **6/6**；这些结果仍不构成非 Linux 捕获证据。
- **仍待外部结果**：Windows 实机、主 CI、windows-d3d12、由 `engine/CMakeLists.txt` 变更触发的 QUIC，以及 Proton 均待执行或回收，不预写 run-id 或成功。Windows install=false stub 与非 Linux 捕获边界不变。

#### Windows 实机补充（`321cf4f9`）

上述 Windows 实机待办已有结果：Windows Clang 的 D3D12 树构建成功，但完整非图形 CTest 为 **425 项、4 失败、5 项条件 skip**，不是全套通过。`test_core_app_diagnostics` **7/7**、`test_core_app_runtime` **65/65**；crash_build OFF 和 nested 契约通过，target 与 crash_context 按平台 skip；`test_vfs`、`test_async_loader`、`test_runtime_io` 分别通过。diagnostics 的 POSIX 用例只是占位，install=false stub 仍不是捕获证据。

`test_locked_dependencies` 首轮缺少 `ENGINE_LOCKED_DEPS_ALLOW_ABSENT=1` 失败，按 CI 环境设置后通过。`test_platform_win32_runtime` 为 **20/26**，远程桌面下窗口样式、最大化、全屏恢复失败；`test_d3d12_uav_matrix` 交换链创建返回 `0x887a0022`，WARP 亦失败，warp_runtime 按条件 skip，不声称 GPU 或交互桌面通过。

`test_scene_serial` 为 **121/122**，`failed_load_keeps_previous_scene` 的 `scene_load_binary(wd,&dst,pa)` 失败。scene 实现与测试从 `0ddd`、rebase base 到当前均无变化，故不是本分支改动引入；根因未关闭，作为独立既有/平台问题保留，未证明是环境原因，待 Windows CI 交叉核验。

主 CI、windows-d3d12、QUIC（因 `engine/CMakeLists.txt` 变更会触发）和 Proton 仍待，不预写 run-id 或成功；Windows install=false stub 与非 Linux 捕获边界不变。

#### 远端验收收据（`7fdcdfe318f43ce4f8620f0e455be795bb66e87b`）

[主 CI 45101195431](https://github.com/konyka/break/actions/runs/45101195431) 为 27 个矩阵作业、24 success、3 conditional skipped、0 failure；Linux arm64 job `137452184436` 的 QEMU 选择套件 276/276，含 VFS、async loader、Runtime IO、core_app runtime。Ubuntu 24.04 TSan job `137452533153` 的 Configure/Build/Test (headless suite) 全成功，但输出重定向且没有逐项 crash-context/BCR 日志，只称 TSan headless suite 通过，不伪造独立 SIGABRT/BCR artifact；Fedora longjmp 边界不变。

[windows-d3d12 45101195116](https://github.com/konyka/break/actions/runs/45101195116) 成功，Headless+contract、WARP floor、push-constant gate、Agility deployment、artifact upload 均成功；托管主 CI 的 Windows Clang 也成功。本机 scene_serial 单例失败仍未定位，本机全套不称通过。[QUIC 45101195104](https://github.com/konyka/break/actions/runs/45101195104) conclusion=success，但 `SNOWFLAKE_READ_TOKEN` 未配置，UNAVAILABLE、No test ran，四个场景未执行，不是 QUIC 测试通过。[Proton 45102712864](https://github.com/konyka/break/actions/runs/45102712864) 成功，上游 run-id=`45101195116`、artifact ID `14785842612`；device/pipeline contract 均 77，仅兼容通道，不是 GPU 或原生 D3D12 通过。

这些结果不属于本收据文档提交之后的工作流。本收据提交还会触发新的主 CI、windows-d3d12、Proton，待实际核验后另行记录，不预写成功或 run-id。
