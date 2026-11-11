# Core App Deterministic Asset Checkout Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 让 Core App 的 11 个正式资产在 Windows Git checkout 中与真实 baker 输出逐字节一致，不把 CRLF 归一化进资产或比较逻辑。

**Architecture:** 原生 SHA-256/长度已证明文本资产被 Git 检出为 CRLF，而 baker 始终写 LF。按现有 PPM 的 `binary` 规则，将 `engine/assets/core_app/*` 标为 binary，阻止 Git 换行转换。以真实 `git check-attr` 和正式资产比较验收，不改 baker 输出、序列化或比较语义。

**Tech Stack:** Git attributes、Git checkout/CRLF、C11 assets tests、CMake/CTest、SHA-256、Windows/MSVC、Linux。

## Global Constraints

- 正式工作树 `/home/timeshift/opensource/break/.worktrees/core-app-ci`，分支 `core-app-ci`，基线 `987121d9`。不建 PR，不合并临时 validation/APFS/process-probe 分支；controller 负责独立评审后的原生验证与最终 push。
- 原生 run `43033533322`、job `130566358685` 的证据在 `build-core-ci-controller-logs/windows-formal-asset-hashes.log`：`actors.sidecar` 86 vs 79、`broken.lua` 50 vs 47、`deterministic.scenario` 134 vs 127、`director.lua` 44 vs 41、`load_unload.scenario` 131 vs 123、`player.lua` 43 vs 40、`rollback.scenario` 132 vs 125；这些增加值正好等于各文件行数。BSCN/BANM/FG/WAV 的 SHA-256 与 baker 完全一致。
- 只修 checkout 属性，不改资产内容、baker、PAL、序列化、reader、比较算法、公共 API/ABI、RHI、CI 通过条件或临时 probe。不得通过 CRLF 归一化、忽略文本差异或重新生成含 CRLF 的正式资产来掩盖问题。
- 新名称使用 `core_app`/`CoreApp`/`CORE_APP`，不引入旧外部引擎前缀或新 `game` 领域名。Vulkan 默认，OpenGL 只作最后降级/画面对照，不引入 X11。
- 所有构建和并行 CTest 使用 `-j3`。每项先 RED、最小 GREEN、变异/恢复、全量非图形回归、独立规格与质量评审。Linux 属性检查不替代 native Windows 字节证据。

---

### Task 1: 固定 Core App 资产的二进制检出属性

**Files:**
- Modify: `.gitattributes`
- Modify: `engine/CMakeLists.txt`（注册 checkout 属性合同）
- Create: `engine/tests/test_core_app_checkout_attributes.cmake`
- Modify: `docs/Implementation_Status.md`（原生结果后追加）
- Modify: `docs/design/core_app_integration.md`（原生结果后追加）
- Report: `.superpowers/sdd/2026-11-11-core-app-asset-checkout/task-1-report.md`

**Interfaces:**
- Produces: `engine/assets/core_app/* binary` 与 `test_core_app_checkout_attributes`。
- Preserves: 11 个资产的实际字节、真实 baker 输出、无 Git 时仅能力未验证的边界、现有正式资产 tracking 和全部比较断言。

- [ ] **Step 1: 写真实属性 RED**

新增 `test_core_app_checkout_attributes.cmake`，要求 `REPOSITORY_ROOT` 非空并读取真实 `${REPOSITORY_ROOT}/.gitattributes`。`GIT_EXECUTABLE` 可以为空，但只能作为 Git 工具缺失的明确 `UNVERIFIED`，不能伪造执行结果。要求属性文件包含独立行 `engine/assets/core_app/* binary`，覆盖所有 11 个正式资产而不只某个二进制扩展名。

在真实 Git checkout 中，对下列每个文件执行 `git -C <repo> check-attr -a -- engine/assets/core_app/<name>`，要求返回 0 且输出包含 `binary: set`，拒绝 `text: set`：

```text
actors.sidecar broken.lua deterministic.scenario director.lua level.banm
level.bscn level.fg load_unload.scenario player.lua rollback.scenario tone.wav
```

首次运行时该规则不存在，合同必须 RED。不得把 `git check-attr` 换成只读取测试自身写入的属性值。

- [ ] **Step 2: 实现最小属性规则与无 Git 边界**

在 `.gitattributes` 按现有 PPM 的风格追加：

```gitattributes
# Offline Core App assets must be byte-identical to the baker on every OS.
# Text assets must not be rewritten to CRLF on Windows checkout.
engine/assets/core_app/* binary
```

将现有 `Scoped to shaders only.` 改为 `This section is scoped to shaders only.`，保持注释与扩大后的文件范围一致。不要重写资产或运行格式转换。

在 CMake 注册 `test_core_app_checkout_attributes`，传入真实 `REPOSITORY_ROOT` 和 `${BREAK_GIT_EXECUTABLE}`。属性文本检查始终执行。`GIT_EXECUTABLE` 为空时不得执行空命令，在完成属性文本检查后报告同一能力未验证。真实 `check-attr` 只在 `git rev-parse --git-dir` 成功后执行：若 `.git` 存在但命令失败则 FAIL；仅当没有 `.git` 且明确返回 not-a-repository 时，输出 `UNVERIFIED: core_app checkout attribute probe skipped:` 并以 77 表示能力未验证。旧 CMake 的 FATAL_ERROR 回退必须匹配同一个精确 `SKIP_REGULAR_EXPRESSION`，真实属性错误不得借用 skip。

- [ ] **Step 3: GREEN、变异与真实 Windows 验收**

运行新合同和正式资产/诊断 focused，再运行完整非图形 `-j3`。临时删除或缩窄 binary 规则必须使真实 `git check-attr` 和文本检查 RED；精确恢复后 GREEN。确认 11 个实际文件字节未改变。

controller 合并已评审提交到临时验证分支，要求新 checkout 的正式文本恢复 LF 长度和 SHA-256，真实 `test_core_app_assets` 为 16/16、diagnostics 成功，且 A/B 仍逐字节一致。macOS 不得回归。D3D12 compat 的独立后续任务不在本项中宣称完成。

- [ ] **Step 4: 独立评审、提交与文档**

检查属性规则覆盖范围、真实 Git 行为、无 Git/损坏元数据边界、没有忽略文本差异或改变资产字节。提交：

```bash
git commit -m "test: preserve core app asset checkout bytes"
```

原生结果出来后追加 `docs/Implementation_Status.md` 和 `docs/design/core_app_integration.md` 的当前证据与剩余 compat 限制。最终 sanitizer/no-tests/fuzz、全分支终审与 controller push 属于 integration gate。
