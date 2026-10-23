# Update Client — Stage 5 Phase B（下载/续传/A-B/回滚 客户端离线机制）

`break_update` 的客户端状态机 + 分块下载器 + stage/activate/confirm/rollback
管线。Phase B 交付的是**客户端离线机制**：传输由调用方回调注入（本仓库以
in-process fake 测试），**无任何真实网络代码**（计划 Global Constraints）。
Phase A 的签名 manifest、CAS chunk store、原子写 PAL 的契约见
`engine/src/update/break_update.h` 头注释与
`docs/design/security_threat_model.md` §4；本文不重复，只钉 Phase B 新增面。

- 实现：`engine/src/update/break_update_client.h/.c`（接口与逐条语义以头注释
  为准；本文为设计契约与诚实边界）
- 测试：`engine/tests/test_break_update_client.c`（43 例）
- 上游契约：manifest/CAS（`break_update.h`）、原子写（`platform_fs.h` 的
  `PlatformAtomicWriter`）、密码学原语（`break_crypto.h`）

## 1. 状态机（文本图）

状态由 state 文件四字段决定：`current`（A/B/none）、`staged`（A/B/none）、
`pending`、`confirmed`。合法转换（全部 write-ahead，见 §5）：

```text
                        open（root 无 state → 建布局 + 初始态）
                        ┌──────────────────────────────────────┐
                        ▼                                      │
   current=none, staged=none, pending=no, confirmed=no         │
   current-version=none, previous-version=none                 │
                        │                                      │
        stage(manifest, pubkey, channel, platform, fetch)      │
        〔verify 签名 → compatible() 策略 → staged 互斥检查     │
          → fetch_all（传输只在这里发生）→ 物化非活跃槽         │
          → staged 标记最后持久化〕                            │
                        ▼                                      │
   staged=A|B（current 不变；pending=no, confirmed=no）         │
                        │                                      │
              ┌─────────┴──────────┐                           │
        activate│                  │unstage（唯一不激活         │
              ▼                    ▼  的清 staged 途径）        │
   current=staged 槽        staged=none（先持久化清除标记，      │
   pending=yes              再删槽树；删除失败留下惰性残树，      │
   confirmed=no             下次 stage 的 clean 回收）          │
   previous=旧 current ──────┘                               │
                        │                                      │
              ┌─────────┴──────────┐                           │
   confirm_boot│                   │rollback（pre-confirm       │
              ▼                    ▼  关键安全路径：见 §7）      │
   pending=no, confirmed=yes  current↔previous 交换             │
   （启动验证通过，新槽转正）  （pending 清、confirmed=yes）     │
                        │                                      │
        已确认稳态上 rollback 仍允许（受 §7 地板与互斥约束）     │
                        └──────────────────────────────────────┘
```

拒绝面（fail-closed，全部只改 `last_error` 不改状态）：

- `confirm_boot`：无 pending → STATE。
- `rollback`：staged 存在 → STATE（先 unstage）；无 previous → STATE；
  previous-version < min-rollback-version → POLICY。
- `stage`：签名无效 → VERIFY（**零 fetch 调用、零磁盘写、零状态变**，
  测试三层钉死）；channel/platform/min-version 不符 → POLICY（同样零
  fetch）；staged 已存在 → STATE。
- `activate`/`unstage`：无 staged → STATE。
- open：state 文件任何解析异常（截断/未知键/坏值/越 64 KiB/跨字段不变量
  违反）→ NULL，**无启发式修复**。

`current` 是 state 文件里的**数据**，不是符号链接——槽目录在存活期间永不
改名（计划 Crash-safety 约束）；激活与回滚都是 state 内的指针翻转。

## 2. 盘上布局

```text
<root>/
├── state                     # canonical 文本，≤64 KiB，原子替换（见 §3）
├── chunks/                   # Phase A CAS，跨槽共享
│   ├── <sha256hex>           # 已提交 chunk（写入 tmp+fsync+rename；读出前
│   │                         #   重新哈希 verify-on-read；单 chunk ≤128 MiB）
│   └── <sha256hex>.part      # 在途 spool——任意时刻至多一个（顺序下载）
└── slots/
    ├── A/
    │   ├── files/<name>      # 物化的 manifest 负载（名 = manifest chunk NAME，
    │   │                     #   嵌套名逐组件 platform_mkdir；原子写逐文件提交）
    │   └── update-version    # "M.m.p\n" 单行标记（staged manifest 版本；
    │                         #   在 files/ 之外，任何 manifest 名撞不上它）
    └── B/                    # 同构
```

open 时若 state 缺席：建 `chunks/`、`slots/A/`、`slots/B/` 并持久化初始态
（逐字节钉死于测试）。root 路径上限在 open 时一次检查：为最紧后缀
`"/slots/A/files/"`（15）+ 128 字节 manifest 名 + 写侧 `".tmpXXXXXX"`（10）
+ NUL = 154 字节预留（同时覆盖 `/chunks/<64hex>.part`、
`/slots/A/update-version`、`/state`），此后一切拼接按构造安全。

## 3. 状态文件 canonical 格式

与 `break-manifest-v1` 同一纪律（键序固定如下、LF、ASCII 可打印子集、未知/
畸形 → open 失败）：

```text
break-update-state-v1
current: A|B|none
staged: A|B|none            (materialization 完成的槽)
pending: yes|no             (staged 且已 activate，待 confirm)
confirmed: yes|no
current-version: M.m.p      (current=none 时为 none)
previous-version: M.m.p     (无 previous 时为 none)
min-rollback-version: M.m.p (rollback 策略地板；恒为版本三元组，
                             全新安装为 0.0.0 = 无地板)
resume-chunk: <sha256hex>|<offset>  OR  none
```

跨字段不变量（任何合法转换都造不出的组合 = 畸形）：current=none 当且仅当
current-version=none；current=none ⇒ previous-version=none；永不
pending=yes 且 confirmed=yes；pending=yes ⇒ current≠none；
confirmed=yes ⇒ current≠none。实测最坏序列化 ≈326 字节（上限 64 KiB）。

**完整性边界（诚实声明）**：state 文件与槽内 `update-version` 标记只受
**解析校验**保护（canonical 格式 + 跨字段不变量），**没有任何 MAC/签名**。
对 update root 有本地写权限的攻击者可以重写 state（翻转 current、压低
min-rollback 地板、伪造 confirmed=yes）与槽内标记，客户端会接受任何解析
合法的内容。这不扩大既有威胁模型边界：能写 update root 的本地攻击者本
就能整体替换槽内容（§7 的 known-good 论证同样失效）——**本地写盘权限已
等价完全篡改**，签名保护的是传输与来源，不是本地盘。见
`security_threat_model.md` §4/§10。

## 4. 下载与字节级续传语义

`break_update_client_fetch_all(c, manifest, fetch, user)`：下载 manifest
所有 CAS 缺失 chunk，每个经 `chunks/<hash>.part` spool，流式 SHA-256 全量
校验 == manifest 哈希后才 `store_put_chunk`（put 自身重算哈希，chunk 按构造
落在 manifest 名下）。顺序、单 .part、返回 true 即全部在 CAS。

- **对象身份**：fetch 对象名 = chunk 的 sha256 hex（manifest 的 chunk NAME
  字段是槽相对路径，只供 stage 物化用，此处不参与）。
- **CAS 去重**：`has_chunk` 命中的 chunk **永不重取**（调用计数钉死）；
  已完成 chunk 跨 reopen 不重取（进度已持久化）。
- **范围钳制**：一切 fetch 范围从 manifest 声明的 size 派生——
  `len = min(64 KiB, size - offset)`，offset+len ≤ size ≤ UINT64_MAX，
  按构造无 u64 溢出（每次调用前检查，接口契约）。传输从不被询问大小，
  其声称从不被信任；spool 缓冲是固定 64 KiB 块，任何分配尺寸都不由
  manifest 值决定（>128 MiB 的 chunk 在 store 自身上限处以 IO 失败）。
- **顺序**：有效 resume 条目的 chunk **最先**续传（起别的 chunk 会覆盖其
  条目），之后按 manifest 序。
- **续传恢复**：resume 时把 .part 既有前缀重新喂入流式 sha256（前缀无法对
  最终 digest 验证；这些字节被信任到完成时刻，由**全量** digest 把关
  入库——VERIFY 失败丢 .part 清条目，CAS 不进任何东西）。
- **入口 triage**（state `resume-chunk = H|O`）：
  - H 已在 CAS → 陈旧条目（store_put 与清条目之间崩溃）：删 .part、清
    条目、fetch_all **继续**（可恢复部分态，非错误）；
  - H 在 manifest 中且不在 CAS、O ≤ chunk size、.part 与 O 一致（O==0
    当且仅当 .part 缺席，否则精确等大；O==size 合法 = 待校验入库的完整
    spool）→ 从字节偏移 O 续传；
  - 其余（未知哈希、O > size、.part 缺/短/长）→ CORRUPT：删 .part、清
    条目（均已持久化）、false + STATE；下次调用该 chunk 从 0 干净重下。
- **错误**：FETCH = 回调 false（进度保留——持久化偏移与 .part 一致，再
  调即续）；VERIFY = digest 不符（.part 弃、条目清）；IO = 本地资源失败
  （store 打开、.part 读写/fflush、OOM、sha256 后端、状态持久化、store
  put、.part 删除）——内存态与持久化条目保持一致（半写块由下次调用的
  corrupt 检测自愈）；STATE = resume 条目腐败（返回时已干净重启）；
  INVALID = NULL manifest/fetch。

**崩溃代价（准确表述）**：.part 不做 fsync（有意的性能决策）。进程被杀时
已 fflush 的字节留在 OS，.part 比持久化偏移**长**至多一个块；断电时页缓存
丢失可让 .part 呈任意尺寸。两种情形下持久化偏移与 .part 尺寸不一致 →
triage 判 CORRUPT → **整个在途 chunk 从字节 0 重下**（已 spool 字节全部
丢弃）。故崩溃代价上界 = 一个 chunk（≤ store 的 128 MiB 上限；已在 CAS 的
字节永不重取），**不是最后一个块**；"逐块粒度"只对持久化偏移本身成立。
fail-closed 检测以该重下代价覆盖进程与电源丢失。

## 5. Write-ahead 持久化顺序

铁律：**每次状态变更先把 NEXT 态序列化为 canonical 文本并经
`PlatformAtomicWriter`（fsync file → rename → fsync dir）提交，内存态
（可见效果）才翻转**。持久化失败 → false + IO，内存态不动（瞬时 IO 错误
不楔死客户端，操作可重试）；任何操作后无 writer tmp 残留（commit/abort
都清理，测试钉死）。

各操作的持久化点：

- **fetch_all**：起一个 chunk 先持久化 `resume-chunk=hash|0`，**.part 之后
  才创建**；每个取到的块先 fwrite + fflush，**再**持久化新偏移。
- **stage**：staged 标记是**最后一次** write-ahead 持久化——此前崩溃留下
  staged=none 与部分槽树，下次 stage 的 clean 回收。
- **activate**：持久化（current=staged 槽、staged=none、pending=yes、
  confirmed=no、previous=旧 current）**先于**翻转可见。
- **confirm_boot / rollback**：同样先持久化后翻转。
- **unstage**：**先**持久化 staged=none，**再**删槽树——崩溃留下惰性残树
  （下次 stage 的 clean 回收），绝无"标记在而树没了"的 staged 槽。持久化
  后删除失败报 false + IO 但 staged 已清（rollback 的 staged 互斥不再
  适用，不楔死，文档化）。

## 6. stage → activate → confirm 管线

`stage` 编排顺序（行级钉死）：**verify 签名（pubkey）→ compatible()
策略（channel/platform/来自 state 的当前版本）→ staged 互斥检查 →
fetch_all → clean + 物化非活跃槽 → staged 标记**。签名先于一切
（cross-cutting 门）：VERIFY/POLICY 失败**零 fetch 调用、零磁盘写、零状态
变**（单测 + 契约 + 实现三层钉住）。

- **fresh 客户端 0.0.0 语义**：current=none 时 compatible() 的源版本视为
  0.0.0——完整策略照常运行（channel + platform + manifest min-version ≤
  0.0.0），故只有 min-version 地板为 0.0.0 的负载能 provisioning 无已装
  版本的设备。
- **非活跃槽**：非 current 槽；current=none 时固定选 'A'。
- **物化**：先 clean 目标槽（回收更老周期的 retained 树——故 staged 槽的
  files/ 与 manifest 精确一致，无陈旧文件），逐 chunk 从 CAS 取（
  verify-on-read 交出字节前重哈希）经原子写落到 `slots/<slot>/files/
  <name>`，最后写 `update-version` 标记。clean 只在 fetch_all 成功后运行：
  **传输失败绝不触碰任何槽**（retained previous 版本的字节在下载失败后
  存活）。
- **失败原子性**：clean 之后任何失败移除部分槽树；state 除 resume 进度外
  不变。
- **activate**：从槽内标记读 staged 版本（缺失/畸形 → false + IO，state
  不动）；持久化后翻转。首次激活 previous-version=none（全新安装无可回
  滚对象）。
- **标记定位**：Task-1 钉死的 state 格式没有 staged-version 字段，版本随
  槽走；标记只喂 activate 的 current-version 记录——rollback 地板比较用
  的是 state（审查裁决 3a：标记不引入新绕过面）。

## 7. 回滚策略与 A/B 槽窗口（诚实边界）

**策略**：`rollback` 交换 current↔previous（槽与版本一起），清 pending，
置 confirmed=yes——previous 槽按构造是确认过一次的启动（它曾是 current），
故回滚后的启动视为 known-good（文档化决策）。拒绝：staged 存在（STATE，
**staged 互斥**——`unstage` 是唯一不激活的清 staged 途径）、无 previous
（STATE）、previous-version < min-rollback-version（POLICY，**地板**；
本期无客户端 API 改地板，属产品策略）。

**A/B 槽窗口（两槽固有，审查裁决 3c 接受为文档化边界）**：

- stage 物化会 clean 目标槽；当有 live current 时目标槽**正是 retained
  previous 槽**——这就是 rollback 对 staged 互斥的原因。
- **stage + unstage 之后**，previous 槽内容已被回收；此时 rollback 仍是
  **state 级成功**（版本策略翻转——指针翻转设计，槽目录永不改名），但
  previous 的**内容可能已不存在**。测试逐字钉住该形态
  （`rollback_while_staged_then_unstage_allows`：回滚返回 true、
  current='A'、版本 2.0.0，而槽 A 树为空）。
- 由此 **confirmed=yes 落在内容已回收槽上时，known-good 论证减弱**：
  state 声称该槽确认过，但其字节可能已不在。confirmed 标记证明的是"该
  版本曾经确认"，不是"该槽当前字节可启动"。
- **关键安全路径完好**：坏更新的 pre-confirm 回滚——current=新槽
  pending、previous=旧好槽——内容完好，因为刚才那次 stage 销毁的是
  **更老**的 previous（新槽的旧 occupant），不是现在的 previous。这是
  A/B 设计要保的那条路径；窗口只开在已确认稳态上的再次 stage。

## 8. 传输接缝契约（BreakUpdateFetchFn）

```c
typedef bool (*BreakUpdateFetchFn)(void *user, const char *object_name,
                                   u64 offset, u64 len, u8 *out);
```

- **ranged read**：按 `[offset, offset+len)` 返回对象字节到 `out`
  （容量 ≥ len）；对象名本期 = chunk sha256hex。
- **false = 可重试**：传输失败不得损坏客户端状态——进度已持久化，再次
  调用 fetch_all/stage 即从断点续传；回调自身不做持久化义务。
- **offset/len 永不溢出**：由 client 从 manifest size 钳制（§4），每次
  调用前检查；回调可假设 offset+len ≤ manifest 声明 size。
- 回调可以部分不诚信（短读、错字节）——完成时全量 digest 把关入库，
  VERIFY 失败丢弃。回调**不应**有客户端可见副作用的假设（失败即重试）。
- 真实传输接线（HTTP/TLS/range 请求映射、认证）属 Phase C+（
  `security_threat_model.md` §5），本接缝是其唯一挂点。

## 9. 错误纪律与有界性

固定枚举 `BreakUpdateClientError`（OK/INVALID/IO/PARSE/POLICY/FETCH/
VERIFY/STATE），无任何攻击者控制的字符串；`last_error` 反映最近一次
confirm_boot/rollback/fetch_all/stage/activate/unstage 调用（成功 =
OK），open 之后初始为 OK；open 本身只以 NULL 报错（无客户端可持有错误）。
有界：state ≤64 KiB；槽恰 2 个（A/B）；单 stage 的 chunk 数 ≤ manifest
上限（65536）；在途 .part ≤1；resume 进度条目随 chunk 数有界；一切磁盘
算术溢出检查。树删除用 ISO-C `remove()`（POSIX 下文件与空目录通吃），
递归深度 ≤64（manifest 名 ≤128 字节 ⇒ ≤64 组件）。

## 10. 本地盘加固观察（记录，非边界修复）

`upc_remove_tree_at` 经 `platform_list_dir` 枚举——POSIX 侧顶层 `opendir`
**跟随符号链接**（条目本身 lstat 不跟随）。故若 `slots/<slot>/files` 被
替换为指向别处的符号链接，clean/unstage 的树删除会**穿透删除链接目标的
内容**。本期不修的理由（威胁模型口径，见 §3 与
`security_threat_model.md` §4）：能放置该符号链接的本地写权限已等价完全
篡改（可直接改写 state 与槽内容），签名边界管不到本地盘。后续加固方向：
树删除顶层 lstat + nofollow（拒绝对符号链接递归），条目侧已是 lstat
不跟随。此为纵深防御项，非安全边界关闭。

## 11. 明确 NOT delivered 清单

以下各项**不在本 Phase 交付**，不得由本文任何内容推断为已有能力：

1. **真实传输**：无 socket/HTTP/TLS/curl 代码；`BreakUpdateFetchFn` 是唯一
   接缝，仓库内仅以 in-process fake 测试（grep 门：无传输符号引入）。
2. **灰度（gray rollout）客户端逻辑**：灰度是服务端策略——客户端唯一
   旋钮是配置的 channel（经 `compatible()` 生效）；无分桶/百分比/白名单
   客户端代码。
3. **服务端**：无更新服务端、无 manifest 分发、无版本协商。
4. **签名之后的在线流程**：离线签名 tooling、密钥生成/保管/轮换/吊销、
   发布流水线均未定义（Phase B/C 范畴，
   `security_threat_model.md` §11 密钥管理未决风险不变）。
5. **Win32 lane 未跑**：树删除只用既有 PAL 原语（无新 `_WIN32` 分支），
   Win32 编译形态按检视保持，首个 Windows lane 待办同 Phase A。
6. **fuzz lane `Not Run`**（house 惯例）。
7. `break_update` 不进 `engine`/`engine_demo`/`dxx_break`/`editor` 链接
   闭包（契约 ctest 钉住）——本交付是正式可选 target 证据，**不是已接线
   的在线更新功能**。

## 12. 证据索引

- 计划：`docs/superpowers/plans/2026-10-24-stage5-update-client.md`；
  台账 `.superpowers/sdd/2026-10-24-stage5-update-client/progress.md`；
  任务报告同目录 task-{1..4}-report.md。
- 测试：`engine/tests/test_break_update_client.c`（43 例，三树绿）——
  状态机/持久化/腐败拒绝（Task 1，15 例）、下载/续传/CAS 去重（Task 2，
  11 例）、管线端到端（Task 3，17 例）。
- 回滚验收对号（roadmap "Offline update rollback tests"）：
  pre-confirm 回滚 = `rollback_after_activate_preconfirm`；confirm 后回滚
  + 地板拒绝 = `rollback_after_confirm_and_floor`（+ Task 1 的
  `rollback_below_min_policy`）；staged 互斥 =
  `rollback_with_staged_state`（Task 1）+
  `rollback_while_staged_then_unstage_allows`（含 unstage 语义与 A/B 窗口
  形态钉住）。
- 上游：manifest/CAS `engine/src/update/break_update.h`；原子写
  `engine/src/platform/platform_fs.h`；威胁模型
  `docs/design/security_threat_model.md` §4（信任链）/§10（NOT-delivered）。
