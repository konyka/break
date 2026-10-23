# Stage 5 威胁模型与安全契约

## 1. 目的、范围与状态语义

本文是 Stage 5（online update / crash reporting / security，roadmap `docs/design/roadmap_2026-10-22.md:109-126`）的威胁模型与安全契约**设计文档**，是 `docs/design/runtime_security.md` §3.3（`:60-62`）与 §10（`:249-258`）的 Stage 5 扩展，不是实现报告。它正式化四件事：客户端信任边界、服务端权威范围、更新信任链、以及崩溃数据/传输/重放/反篡改的契约范围声明。

状态词沿用 `runtime_security.md:11-16` 的严格口径：

- **当前已有**：源码和现有测试可以直接证明的行为；不等于正式产品集成。
- **focused/test-only**：源码存在且有专项测试，但仅由测试 target 编译或链接。
- **设计目标**：本文建议的接口、边界或验收标准，尚未实现。
- **未实现/风险**：明确不在当前交付范围，不能由本文推断为已有能力。

Phase A 的实施计划是 `docs/superpowers/plans/2026-10-24-stage5-security-foundations.md`；本文只立契约与模型，各库（`break_crypto`/`break_update`/写侧 PAL）的交付状态以 `docs/Implementation_Status.md` 与该计划台账为准——在本文首次提交时它们全部是**设计目标**；Phase A 收口（Task 5）时它们已交付为正式可选 target，本文 §4/§9/§12 已按收口状态更新。Stage 5 的执行顺序依据是 roadmap Execution Order 第 7 条（`roadmap_2026-10-22.md:146-155`）。

## 2. 客户端信任边界

**核心契约：客户端永非权威（client is NEVER authoritative）。** 客户端上报的一切——位置、伤害、库存、经济行为、匹配结果、版本号、崩溃上下文——都是不可信输入。任何安全决策不得以客户端自报状态为依据。

现有事实锚点（**当前已有/focused**，均不是认证机制）：

- fragment checksum 是 FNV-1a 完整性检查，只能发现传输损坏/错误重复，不能证明来源、抗篡改或保密（`runtime_security.md:115-119`；字段定义 `engine/src/network/break_replication_fragment.h:20-26`）；
- Session 不是 player authentication backend；默认 AUTH/PING registry 允许协议测试流转，不等于身份认证（`runtime_security.md:131`；Session ownership 见 `docs/design/session_protocol.md:21-37`）；
- Snowflake 源码树中 `snow_auth` 的 keyed-FNV-1a 同样是**非密码学**构造，Stage 5 **不复用**它做任何认证（计划 Global Constraints，`2026-10-24-stage5-security-foundations.md:13`）；
- VFS 的 16 mounts / 4096 entries / 128 MiB 单文件上限是资源防护，不是恶意 package 的真实性证明（`runtime_security.md:255`；`engine/src/asset/vfs.h:5-12`）。

**反篡改成本模型（anti-tamper raises attack cost only）。** 客户端侧完整性自检、调试器探测、混淆等手段的全部语义是**提高攻击成本**，永远不构成信任依据：拥有本地代码执行能力的攻击者最终可以绕过任何客户端检查。因此：

- 反篡改信号最多作为服务端风控/封禁决策的一个**输入特征**，从不能放行特权操作；
- 服务端不得因客户端"自称未被篡改"而放宽任何校验；
- 本阶段**不实现**任何反篡改代码（属子项目 5，见 §10）；本文只交付该成本模型的语义地位声明。

## 3. 服务端权威（设计目标枚举）

本仓库不含任何服务端实现；以下为**设计目标**级枚举，用于钉住"权威在服务端"的边界，供后续 Phase 与服务器侧计划引用：

- **economy（经济）**：货币余额、交易、兑换比率只由服务端记账；客户端只能提交意图（intent），服务端按规则校验、限速、落账后下发结果；
- **inventory（库存）**：物品增减、装备、消耗以服务端台账为准；客户端展示的是服务端快照的只读视图；
- **damage（伤害/战斗结算）**：命中与伤害数值由服务端（或服务端指定的权威模拟）裁定；客户端至多做预测渲染，命中自报一律不采信；
- **matchmaking（匹配）**：匹配分、房间分配、段位变化由服务端计算；客户端不得自选对手池或自报战绩。

统一原则：客户端发送的是**请求/意图**，服务端返回的是**裁定/快照**；客户端预测只可影响表现层，不得提前落账。以上全部是**设计目标/未实现**——当前仓库没有服务端、没有权威模拟、没有结算代码。

## 4. 更新信任链（Phase A 离线验证 + Phase B 客户端离线机制当前已有）

信任链的形状与界限钉死如下，验收对应 roadmap acceptance 行；其**离线验证侧当前已有**（Phase A Tasks 2-4 交付为正式可选 target，证据见本节末与 §12），**客户端离线机制（分块下载/字节级续传/A-B activation/rollback/channel 策略经 compatible()）亦当前已有**（Phase B Tasks 1-4，`docs/design/update_client.md`）；真实传输接线、灰度客户端逻辑、服务端与签名后的在线流程仍**未实现**（§10）：

```text
离线 Ed25519 签名密钥（signing key 永不离开离线环境；客户端与构建产物只携带公钥）
        │  签名
        ▼
canonical manifest（break-manifest-v1 文本规范：UTF-8 ASCII 子集、LF、键序固定、
        │  chunk 行按名逐字节排序、签名覆盖 signature 行之前的全部字节；
        │  有界：总 ≤1 MiB、≤65536 chunk 条目、名单 ≤128B、字段值 ≤64B）
        ▼
content-addressed chunk store（文件名 = 内容 SHA-256 hex；写入经 tmp+fsync+rename
        原子提交；每次读出前重新哈希校验 verify-on-read；单 chunk ≤128 MiB）
```

契约要点：

- **客户端只验签（client verifies only）**：签名动作只发生在离线 tooling；客户端代码路径上不存在签名能力；
- **release 无未签名路径**：roadmap 验收行 "No default remote debug or unsigned update path in release configuration"（`roadmap_2026-10-22.md:126`）——验签失败、manifest 结构异常、哈希不匹配一律 fail-closed，不存在"跳过校验"的 release 配置；
- **密码学原语只用维护中的平台/库实现**：系统 OpenSSL 3 libcrypto EVP（SHA-256 / HMAC-SHA256 / Ed25519 verify / CSPRNG），roadmap 验收行 "Cryptographic tests use maintained platform/library primitives; no home-grown authentication"（`roadmap_2026-10-22.md:123`）；禁止自造 hash/MAC/签名，`snow_auth` keyed-FNV-1a 与 fragment FNV-1a 均不复用（§2）；
- **版本与兼容性**：manifest 的 `version`/`min-version` 三元组与产品身份 `BREAK_VERSION_MAJOR/MINOR/PATCH`（当前 0.1.0，`engine/src/core/break_version.h`，CMake 注入 `BREAK_BUILD_ID` 短哈希、回退 `"unknown"`，`engine/CMakeLists.txt:409-423,531`）比较；兼容策略 = platform 相等 AND channel 相等 AND 当前版本 ≥ min-version；
- **解析失败无 oracle**：verify API 对任何校验失败只返回 false；parse API 失败只返回 NULL + 内部原因枚举，不向攻击者控制的输入泄漏细节化解析错误（文档化决策，见计划 Global Constraints）；
- **OpenSSL OOM 路径不可被本仓库测试钩子拦截**：文档化声明，不声称该路径的注入覆盖。
- **本地 state 与槽内标记为解析校验、非认证（Phase B 记录）**：update client 的 `state` 文件与槽内 `update-version` 标记只受 canonical 解析校验与跨字段不变量保护，**无 MAC/签名**；对 update root 有本地写权限的攻击者可重写它们（翻转 current、压低 min-rollback 地板、伪造 confirmed=yes）并被接受。这不扩大既有边界：**本地写盘权限已等价完全篡改**（可直接整体替换槽内容，known-good 论证同样失效）——签名保护的是传输与来源，不是本地盘。记录的纵深防御观察（非边界关闭）：树删除 `upc_remove_tree_at` 的顶层 `opendir` 跟随符号链接（条目侧 lstat 不跟随），若 `slots/<slot>/files` 被换为符号链接则删除会穿透到链接目标；后续加固方向为顶层 lstat + nofollow。详见 `docs/design/update_client.md` §3/§10。

**当前已有（Phase A Tasks 1-4 交付）**：产品版本/构建身份（`break_version_string()` 返回 `"0.1.0[+buildid]"`，静态存储、永非 NULL；`engine/src/core/break_version.h/.c`，测试 `engine/tests/test_break_version.c` 7/7）；`break_crypto`（`engine/src/crypto/break_crypto.h/.c`，SHA-256/HMAC-SHA256/Ed25519 verify/CSPRNG 全走 OpenSSL EVP，测试 20/20）；`break_update`（`engine/src/update/break_update.h/.c`，canonical manifest parse/verify + CAS chunk store，测试 19/19）；原子写 PAL（`engine/src/platform/platform_fs.h/.c` 的 `PlatformAtomicWriter`（fsync file → rename → fsync dir）+ `platform_mkdir`/`platform_file_size`，测试 10/10）。四者均为正式 target/引擎 TU，由契约 ctest 钉住不泄入 `engine`/`engine_demo`/`dxx_break`/`editor`（§12）。

**当前已有（Phase B Tasks 1-4 交付，2026-10-24，branch `sdd/stage5-update-client`，提交范围 `bb4a1a2e..HEAD`）**：update client 状态机 + A/B 槽（canonical state 文件 ≤64 KiB、write-ahead 持久化、fail-closed 解析）+ 分块下载器（chunk 粒度、`.part` 字节级续传、CAS 去重、流式 SHA-256 全量校验后入库）+ stage/activate/confirm/unstage/rollback 管线（**签名与策略先于一切传输**——VERIFY/POLICY 失败零 fetch 调用零磁盘写零状态变，三层钉死；min-rollback 地板 + staged 互斥 + unstage 语义），测试 `engine/tests/test_break_update_client.c` 43/43 三树绿。全部经调用方 `BreakUpdateFetchFn` 回调注入传输——**无任何 socket/HTTP/TLS/curl 代码**（grep 门核验）。签名后真实在线流程、灰度客户端逻辑、服务端仍**未实现**（§10）。契约文档 `docs/design/update_client.md`（含 A/B 槽窗口与崩溃代价的诚实边界）。

## 5. 传输认证与密钥/会话生命周期（范围声明，Phase B/C）

属 Stage 5 子项目 4，由后续 Phase B/C 计划交付；本阶段只立范围声明：

- **范围**：`break_net` adapter 的 TLS 接线、密钥生成/存储/轮换/吊销生命周期、会话密钥协商与过期、`snow`（Snowflake）TLS 能力的采用决策；
- **现状**：`break_net` 是 Snowflake 条件的正式可选库（`engine/CMakeLists.txt:388-407`），当前只提供 bounded queue 与 lifecycle 契约，**无任何传输认证**；`runtime_security.md:119` 已明确 fragment 层正式接入前必须由 Stage 5 transport security contract 提供认证；
- **本阶段声明**：在传输认证落地前，任何跨网消息都不具备来源认证与保密性；`break_net` 的使用者不得把现有 envelope/fragment 完整性检查当作安全边界。

TLS 接线进 `break_net` adapter 与 `snow` TLS 使用均**未交付**（§10）。

## 6. 崩溃数据隐私与脱敏契约

属子项目 3；**脱敏契约先于任何上传实现存在**（当前无任何 crash capture/spool/upload 代码）。契约（**设计目标**）：

1. **路径脱敏**：导出的任何文件路径只保留仓库相对/规范化形式；宿主机绝对路径、用户家目录片段一律移除或替换为占位符；
2. **peer 脱敏**：IP 地址、端口、连接 identity、会话标识不原文落盘/上报；需要关联时用不可逆截断哈希；
3. **用户数据脱敏**：命令行参数、环境变量、Lua/脚本 payload、聊天/昵称等用户生成内容默认不收集；确需记录时走白名单字段；
4. **密钥/令牌零记录**：secrets、tokens、完整网络 payload 永不写入诊断产物（沿用 profiler 元数据 redaction 设计目标，`runtime_security.md:171`；泄漏风险已登记 `runtime_security.md:256`）；
5. **本地 spool 同样有界**：spool 目录大小、文件数、单文件尺寸全部有上限；恢复语义（重启后重传/丢弃）由 Phase B/C 定义；
6. 上传实现存在之前，任何诊断导出（含 profiler Chrome trace/provenance sidecar）即适用第 1-4 条。

## 7. 重放保护与限速模型声明

属子项目 5；本阶段交付**模型声明**（设计目标），实现未交付：

- **重放保护**：`runtime_security.md:254` 已要求 Stage 5 定义密钥、nonce、replay window、认证失败策略。模型：每条认证消息携带单调 nonce/sequence + 时间戳；接收方维护滑动 replay window，窗外重复一律拒绝并计数；窗口状态与会话密钥同生命周期。在传输认证（§5）不存在时，重放保护**不可能生效**——现有 sequence/tick 检查只防乱序不防重放；
- **限速模型**：每连接/每身份的消息速率、字节速率、并发 assembly 数均有界（现有锚点：adapter 256 event/outbound 队列、fragment 16 MiB 总预算，`runtime_security.md:115-127`）；超限 fail-closed、显式计数、可导出；禁止静默丢弃后假报成功（沿用 `runtime_security.md:182` 的 observable-overload 总则）。

## 8. 依赖与供应链风险记录

- **Snowflake 未锁定（风险登记）**：`break_net` 依赖的 Snowflake 源码树经 `SNOWFLAKE_SOURCE_DIR` **路径引用**接入（`engine/CMakeLists.txt:293-311`，fail-closed：缺树即 `FATAL_ERROR`），但 Snowflake **不在** `engine/external/locked_dependencies.json`（2026-10-24 以 `grep -i snow` 验证无条目）——该依赖没有钉版/哈希锁定，供应链完整性与可复现性风险**未决**；缓解方向（vendoring 或入锁定清单）留给后续阶段决策，本阶段只记录风险；
- **OpenSSL（新增唯一外部依赖）**：系统 OpenSSL 3 libcrypto（EVP），维护中的原语来源；已落地为 `BREAK_ENABLE_CRYPTO` 选项（默认 ON）+ `find_package(OpenSSL REQUIRED)` fail-closed 查找——ON 且缺失即 `FATAL_ERROR`，OFF 则 `break_crypto`/`break_update` 两 target 缺席（`engine/CMakeLists.txt:44,313-339`，镜像 `BREAK_ENABLE_SNOWFLAKE` 惯例）；本 lane 实测系统库 3.5.9（`pkg-config --modversion openssl`）；系统库版本漂移风险由 locked_dependencies 流程后续登记；
- **构建身份**：`BREAK_BUILD_ID` 注入 `git rev-parse --short=12 HEAD`，非 git 检出（如 clean-room 导出）回退 `"unknown"`（`engine/CMakeLists.txt:409-423`）——回退路径下产物不可追溯 commit，发布流程须以 git 检出构建为准。注意：该值在 CMake **configure 时刻**捕获，之后新提交上的增量重建**不刷新**它——stale until reconfigure（`engine/src/core/break_version.h` 头注释同述）；

## 9. 本文交付物与状态小结

| 项 | 状态 |
| --- | --- |
| 客户端信任边界 / 反篡改成本模型语义 | 本文交付（契约声明） |
| 服务端权威枚举 | 设计目标 |
| 更新信任链离线验证侧（签名 manifest 格式 + CAS chunk store + 密码学原语 + 原子写 PAL） | **当前已有**（Phase A Tasks 2-4） |
| 更新客户端离线机制（分块下载/字节级续传/A-B activation/rollback/channel 策略） | **当前已有**（Phase B Tasks 1-4；真实传输/灰度客户端逻辑/服务端未实现） |
| 版本/构建身份 `break_version` 0.1.0+buildid | **当前已有**（`engine/src/core/break_version.h/.c`，测试 `engine/tests/test_break_version.c`） |
| 传输认证 / 密钥与会话生命周期 | 范围声明；实现属 Phase B/C，未实现 |
| 崩溃数据脱敏契约 | 本文交付（契约）；capture/spool/upload 未实现 |
| 重放/限速模型 | 本文交付（模型声明）；实现未实现 |

## 10. 明确 NOT delivered 清单

以下各项**明确不在本阶段交付**，不得由本文任何设计目标推断为已有能力：

1. Stage 5 子项目 2 的**在线半侧**：真实传输接线（HTTP/TLS/range 映射）、灰度（gray rollout）客户端逻辑、服务端与签名后的在线流程——客户端离线机制（chunked download、byte-level resume、A/B activation、rollback、channel policy 经 `compatible()`）已由 Phase B 交付（`docs/design/update_client.md`），但传输只经调用方 `BreakUpdateFetchFn` 回调注入，仓库内无任何 socket/HTTP/TLS/curl 代码；
2. Stage 5 子项目 3：crash context capture、local spool、redaction 实现、upload、symbolization（本文只交付脱敏契约）；
3. Stage 5 子项目 4：transport authentication 与 key/session lifecycle；
4. Stage 5 子项目 5：replay protection、rate limit、server authority、client anti-tamper 的实现（本文只交付模型声明）；
5. TLS 接线进 `break_net` adapter；
6. `snow`（Snowflake）TLS 使用；
7. 任何服务端实现与 remote debug 通道（roadmap `:126`：release 无默认 remote debug 路径）；
8. **update client 本地 state 与槽内 `update-version` 标记的认证（MAC/签名）未交付**——它们只受 canonical 解析校验与跨字段不变量保护，**是解析校验、非认证**（§4 契约要点末节）；对 update root 的本地写权限已等价完全篡改，故这不构成新边界，但任何"本地状态可信"的推断都不成立。

## 11. 未决风险

- Snowflake 未钉版（§8）：路径引用依赖无哈希锁定，构建可复现性与供应链审计受限；
- OpenSSL 系统库版本漂移：EVP 行为由宿主机库决定，尚未入 `locked_dependencies.json`；
- OpenSSL OOM 路径不可注入测试：内存耗尽下的 EVP 失败路径无覆盖率声明（文档化，不假称覆盖）；
- 密钥管理未定义：离线签名密钥的生成、保管、轮换、吊销流程属 Phase B/C，在其落地前签名体系不可投入真实发布；
- 本文所有"设计目标"条目均无实现证据；交付状态唯一事实来源是 `docs/Implementation_Status.md` 与各阶段台账（focused/test-only 不等于正式集成，`docs/Implementation_Status.md:215,223` 口径）。

## 12. 证据索引

- `docs/design/roadmap_2026-10-22.md:109-126`：Stage 5 范围与验收行（`:123` 无自造密码学；`:126` release 无未签名/remote debug 路径）；`:146-155` Execution Order 第 7 条。
- `docs/design/runtime_security.md:11-16`：状态词定义；`:60-62`（§3.3）与 `:249-258`（§10）：本文的扩展基点；`:115-131` fragment/Session 非认证事实；`:171` profiler 脱敏设计目标；`:182` observable-overload 总则；`:254-256` Stage 5 待定义项与泄漏风险。
- `docs/superpowers/plans/2026-10-24-stage5-security-foundations.md`：Phase A 计划；Global Constraints（`:13` snow_auth 不复用；`:15` OpenSSL fail-closed；`:16-17` 界限与无 oracle；`:21` 诚实范围）与 Tasks 2-4 接口（`:70-178`）。
- `engine/src/update/break_update_client.h/.c`、`engine/tests/test_break_update_client.c`：update client 状态机 + 分块下载/字节级续传 + stage/activate/unstage/rollback 管线（**当前已有**，Phase B；43/43 三树绿；契约 nm 钉住 libbreak_update.a 恰 28 个导出 = 15 manifest/store + 13 client）；`docs/design/update_client.md`：状态机/盘上布局/续传/write-ahead/回滚策略/传输接缝契约与 A/B 槽窗口、崩溃代价、解析校验非认证的诚实边界。
- `docs/superpowers/plans/2026-10-24-stage5-update-client.md`：Phase B 计划；台账 `.superpowers/sdd/2026-10-24-stage5-update-client/progress.md`。
- `engine/src/core/break_version.h`、`engine/src/core/break_version.c`：版本/构建身份接口与实现（**当前已有**）。
- `engine/tests/test_break_version.c`、`engine/CMakeLists.txt:409-423,435,531,3910-3915`：构建身份注入（git 短哈希 / `"unknown"` 回退，configure 时刻捕获、增量重建不刷新）、`engine` target 编入与测试注册证据。
- `engine/CMakeLists.txt:44,313-339`：`BREAK_ENABLE_CRYPTO` 选项（默认 ON）与 `break_crypto`/`break_update` 正式可选 target 块（`find_package(OpenSSL REQUIRED)` fail-closed；OFF ⇒ 两 target 缺席；契约脚本按首 `endif()` 抽取该块，块内禁嵌套 if）。
- `engine/src/crypto/break_crypto.h/.c`、`engine/tests/test_break_crypto.c`、`engine/tests/test_break_crypto_target_contract.cmake`：break_crypto 接口、20/20 测试与契约（**当前已有（本 Phase）**；nm 钉住恰 8 个 `break_crypto_*` 导出、零 OpenSSL 重导出；engine/engine_demo/dxx_break/editor 禁链）。
- `engine/src/update/break_update.h/.c`、`engine/tests/test_break_update.c`、`engine/tests/test_break_update_target_contract.cmake`：签名 manifest + CAS store、19/19 测试与契约（**当前已有**（Phase A）；该部分恰 15 个导出——Phase B 起归档合计 28 = 15 manifest/store + 13 client；unsigned-path 钉用真实测试公钥——OpenSSL 零公钥接受的消息相关性见库头注释块）。
- `engine/src/platform/platform_fs.h/.c`（`PlatformAtomicWriter`/`platform_mkdir`/`platform_file_size`，编入 `engine` target `engine/CMakeLists.txt:446`）、`engine/tests/test_platform_fs_write.c`：原子写 PAL，10/10 测试（**当前已有（本 Phase）**；fsync file → rename → fsync dir；Win32 分支 compile-only）。
- `engine/CMakeLists.txt:293-311,388-407`：Snowflake 路径引用 fail-closed 与 `break_net` 正式可选 target 证据（后者独立于 `ENGINE_BUILD_TESTS`，仅门控 `BREAK_ENABLE_SNOWFLAKE`）。
- `engine/external/locked_dependencies.json`：锁定依赖清单；Snowflake 不在其中（2026-10-24 `grep -i snow` 验证无匹配）。
- `engine/src/network/break_replication_fragment.h:20-26`：FNV-1a checksum 字段（完整性检查，非认证）。
- `engine/src/asset/vfs.h:5-12`：VFS 资源上限（16 mounts / 4096 entries / 128 MiB）。
- `docs/design/session_protocol.md:21-37`：Session GameThread ownership 与队列语义。
- `docs/Implementation_Status.md:200,220,222,230`：房屋口径锚点——fuzz 未构建写 `Not Run`（`:200`/`:220`）、focused/test-only 不等于正式集成（`:222` "因果边界"/`:230` "正式集成边界"；`:230` 另含已修正的 `break_net` 门控表述）。
