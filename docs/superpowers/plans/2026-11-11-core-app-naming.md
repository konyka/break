# Core App Naming Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 将尚未进入主分支的 P12 应用统一迁移到 `core_app` 领域命名与数据格式，不改变其事务加载、保存和卸载行为。

**Architecture:** 先以可执行合同固定路径、标识符和格式，再通过版本控制重命名完成源码与构建迁移，最后由真实 baker 重建资产并重跑完整生命周期。既有兼容库保持原 API/ABI；历史证据不改写。

**Tech Stack:** C11、CMake/CTest、现有场景/Flow/动画/WAV/Lua readers、Git、Linux 普通/ASan+UBSan/TSan。

## Global Constraints

- 工作树固定为 `/home/timeshift/opensource/break/.worktrees/cry-integration`；所有构建和并行 CTest 使用 `-j3`，不 push、不建 PR。
- 设计合同以 `docs/superpowers/specs/2026-11-10-core-app-naming-design.md` 为准。新应用路径、库、类型、函数、变量、宏、target、测试和当前描述采用 `core_app` 体系；不引入禁止的外部引擎前缀。
- 既有 P0–P11 公共 API/ABI、其它应用、历史报告和已完成故障记录不重命名。不要对仓库执行全局字符串替换。
- 当前应用与资产尚未发布，不接受新旧两种 checkpoint/trace/scenario 格式。旧 reader 必须拒绝旧 magic；正式资产由最终 baker 重建。
- 行为保持不变：三态 checkpoint、mount 隔离、commit fatal、I/O quiescence、迟到完成、sticky FAILED 和逆序销毁必须继续通过真实测试。
- 每项修改先取得预期 RED，再写最小实现取得 GREEN；至少对命名或格式条件做一次生产变异并恢复验证。
- 生成物只写构建树或测试临时路径；正式资产仅由维护 baker 命令修改。不得把 record/null 当成 GPU、声卡或听测证据。

---

### Task 1: 源码、构建与当前文档命名

**Files:**
- Rename: 旧名 → `engine/apps/core_app/`
- Rename: 旧名 → `core_app.[ch]`；旧名 → `core_app_audio.[ch]`；旧名 → `core_app_render.[ch]`；旧名 → `core_app_checkpoint.[ch]`；旧名 → `core_app_asset_bake.c`
- Rename: 旧名 → `engine/assets/core_app/`
- Rename: 旧名 → `engine/tests/test_core_app_*`
- Rename: 旧名 → `docs/design/core_app_integration.md`
- Rename: 旧名 → `docs/superpowers/plans/2026-11-03-core-app-integration.md`
- Modify: `engine/CMakeLists.txt`、`.gitignore`、`docs/Implementation_Status.md`、`docs/design/editor_phase1.md`、`engine/tests/test_editor_scene.c` 中真实引用
- Test: `engine/tests/test_core_app_naming_contract.cmake`、`test_core_app_target_contract.cmake`、`test_core_app_formal_assets.cmake`

**Interfaces:**
- Consumes: 当前 Task 3 已验收的应用入口、record render/audio 与 checkpoint API。
- Produces: `core_app_runtime`、`core_app`、`core_app_asset_bake` targets；`CoreAppConfig`、`CoreApp`、`CoreLevel`、`CoreAppRender*`、`CoreAppAudio*`、`CoreAppCheckpoint*` 类型；`core_app_*`、`core_app_render_*`、`core_app_audio_*`、`core_app_checkpoint_*` 函数；`CORE_APP_*` 宏。
- Preserves: 既有外部 `break_kernel`、`BreakKernel*`、`BREAK_KERNEL_*`、`break_flow`、`break_ai`、`break_kernel_lua`、`runtime_core` 的名称和链接关系。局部外部对象用 `actor_runtime` 等职责名，不改外部 API。

- [ ] **Step 1: 先提交设计和本计划，再写新命名合同**

将新测试要求写成以下可执行断言：所有新路径存在、旧应用/测试/资产路径不存在；`core_app_runtime` 使用四个新源文件；`core_app` 通过 `engine_link_rhi_backend` 链接；`core_app_asset_bake` 链接 `core_app_runtime`；`core_app_run` 出现在符号扫描中；11 个新资产路径精确等于 Git 跟踪列表。

扫描新应用、新测试与当前设计时，先移除明确豁免的 `break_kernel`、`BreakKernel`、`BREAK_KERNEL`、`kernel/break_kernel` 以及既有 `test_core_style_prototype` 合同字符串，再拒绝遗留应用前缀、`Cry` 前缀和旧的 `application` 领域命名。不要用宽泛豁免隐藏新代码；历史文档不加入扫描。checkpoint 仍暂用现有格式，本步只检查名称。

```cmake
foreach(required IN ITEMS
        "${ENGINE_SOURCE_DIR}/apps/core_app/core_app.c"
        "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_audio.c"
        "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_render.c"
        "${ENGINE_SOURCE_DIR}/apps/core_app/core_app_checkpoint.c"
        "${ENGINE_SOURCE_DIR}/tests/test_core_app_assets.c")
    if(NOT EXISTS "${required}")
        message(FATAL_ERROR "missing core_app migration file: ${required}")
    endif()
endforeach()
```

- [ ] **Step 2: 运行合同，确认因旧路径和旧 target 失败**

先配置一个独立普通构建：

```bash
cmake -S engine -B build-core-integration-normal \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-core-integration-normal -j3
```

直接运行新命名脚本，预期因 `apps/core_app/core_app.c` 和新测试文件不存在而 RED。不得通过复制旧文件制造第二套应用；使用 `git mv` 保留历史。

- [ ] **Step 3: 完成机械但受合同约束的命名迁移**

路径统一为：

```text
core_app
core_app_runtime
core_app_asset_bake
CORE_APP_ENABLE_NETWORK
CORE_APP_FIXED_DT
CORE_APP_MAX_SUBSTEPS
CORE_APP_CHECKPOINT_VERSION
CORE_APP_TRACE_VERSION
CORE_APP_RENDER_RECORD
CORE_APP_AUDIO_RECORD
CORE_APP_CHECKPOINT_MANIFEST_NAME
```

公开 C 接口采用以下形状，参数和返回类型保持原义：

```c
typedef struct CoreAppConfig CoreAppConfig;
typedef struct CoreApp CoreApp;

BreakRuntimeError core_app_run(const CoreAppConfig *config, int *out_exit_code);
BreakRuntimeError core_app_render_start(CoreAppRender *render, FILE *trace);
BreakRuntimeError core_app_audio_start(CoreAppAudio *audio, FILE *trace);
BreakRuntimeError core_app_checkpoint_probe(const char *directory);
```

旧名 必须改为 `core_app_runtime`，不能使用重复的 `core_app_core`。局部变量 `application` 改为 `app`，其它内部 helper 改为 `app_*` 或明确的 `stage_*` 职责名；`CoreLevel.actor_runtime` 保存既有 Actor adapter 指针。测试 preload 类型和 `CORE_APP_TEST_*` 环境变量同步迁移。CTest 名称、构建目录、`.gitignore` 和当前 editor 引用同步更新。

当前 P12 计划改为 Core App Integration，后续 Task 4–13 使用 `core_app_input`、`core_app_simulation`、`core_app_network`、`core_app_script`。历史提交标题和旧报告不编辑。

- [ ] **Step 4: 构建并验证命名与真实 CLI**

```bash
cmake -S engine -B build-core-integration-normal \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-core-integration-normal -j3
ctest --test-dir build-core-integration-normal --output-on-failure -j3 \
  -R '^test_core_app_(naming_contract|target_contract|nm_missing|nm_unsupported|formal_asset_tracking)$'
```

预期全部 PASS；nm 不支持的两个测试只能按原合同明确 SKIP。`core_app --help` 必须显示 `Usage: core_app`，非法参数仍退出 2，合法 record 参数到达真实运行时而不是被 CLI 误拒。

- [ ] **Step 5: 运行全量非图形并做命名变异**

```bash
ctest --test-dir build-core-integration-normal -LE 'graphics|fuzz' \
  --output-on-failure -j3
```

预期与迁移前相同数量的测试通过，只有已记录的 D3D12 与 nm 平台合同跳过。临时把一个新 target 改回旧名，确认命名/链接合同 RED，立即恢复并重跑 GREEN。

- [ ] **Step 6: 独立规格/质量评审并提交**

评审 diff、API 边界、测试真实性和未修改的兼容接口。Critical/Important 必须修复并 scoped re-review。通过后只提交本步文件，标题使用 `refactor: rename integrated app to core app`。

### Task 2: 数据格式、正式资产与生命周期回归

**Files:**
- Modify: `engine/apps/core_app/core_app.c`、`core_app_checkpoint.[ch]`、`main.c`
- Modify: `engine/tests/test_core_app_assets.c`、`test_core_app_lifecycle.cmake`、`test_core_app_naming_contract.cmake`
- Modify: `engine/assets/core_app/*.scenario`、`docs/design/core_app_integration.md`
- Regenerate: `engine/assets/core_app/` 下全部 11 个正式资产
- Report: `.superpowers/sdd/core-app-naming-report.md`

**Interfaces:**
- Consumes: Task 1 的新 targets、readers、tests 与真实 CLI。
- Produces: 固定 8 字节 `CORECKPT`、`manifest.core`、`COREAPPTRACE`、`core-app-scenario 1`。其它 manifest 字段宽度、hash、generation、错误码与原子提交语义不变。

- [ ] **Step 1: 添加格式 RED**

在 `test_core_app_assets.c` 中同时固定 writer 与 reader 两侧：

```c
static const u8 expected_magic[8] = {
    'C', 'O', 'R', 'E', 'C', 'K', 'P', 'T'
};
ASSERT_EQ(core_app_checkpoint_probe(valid_directory), BREAK_RUNTIME_OK);
ASSERT_TRUE(memcmp(manifest_bytes, expected_magic, sizeof(expected_magic)) == 0);
ASSERT_EQ(core_app_checkpoint_probe(old_magic_directory), BREAK_RUNTIME_INVALID);
```

在 lifecycle 合同中要求 trace 首字段为 `COREAPPTRACE version=1`、scenario 首字段为 `core-app-scenario 1`；旧 `COREAPPTRACE` 和旧 scenario 标识必须失败。命名脚本要求 `CORE_APP_CHECKPOINT_MANIFEST_NAME` 精确为 `"manifest.core"`，旧 `manifest.core` 不得被 reader 接受。

先在只完成 Task 1 的代码上运行 focused 测试，记录 magic、manifest、trace/scenario 预期失败；不要改测试来接受两种格式。

- [ ] **Step 2: 最小实现新格式**

只替换格式常量和 scenario 版本标识，保持序列化偏移和消息长度：

```c
#define CORE_APP_CHECKPOINT_MANIFEST_NAME "manifest.core"
static const u8 k_magic[8] = {'C', 'O', 'R', 'E', 'C', 'K', 'P', 'T'};
```

trace 保留 `version=1`，scenario 保留后续事件文法；`main.c` 的默认资产路径与 Usage 使用新名称。加载旧 manifest 时必须失败，不能先尝试旧格式。

- [ ] **Step 3: 重建并验证全部正式资产**

运行最终 baker，输出定向到新的空构建目录，再以同一 `--output` 接口显式维护正式资产目录：

```bash
./build-core-integration-normal/core_app_asset_bake --output \
  build-core-integration-normal/fresh-assets
./build-core-integration-normal/core_app_asset_bake --output \
  engine/assets/core_app
```

确认两次均退出 0，不得手工编辑 BSCN/BANM/WAV。随后运行：

```bash
ctest --test-dir build-core-integration-normal --output-on-failure -j3 \
  -R '^test_core_app_(assets|formal_asset_tracking|naming_contract|lifecycle_load_unload)$'
```

预期全部 PASS：11 个正式文件精确跟踪、fresh bake 逐字节一致，BSCN/Flow/BANM/WAV/Lua 由真实 readers 读取；checkpoint 三态、mount 隔离、commit fatal、第二次 I/O stop 失败、sticky FAILED 和卸载清理不回归。

- [ ] **Step 4: 验证 HEAD archive 和格式变异**

用 `git archive HEAD` 解包到构建树，只使用归档中的源码和 11 个资产配置/构建，确认没有依赖 ignored 台账或本地旧资产：

```bash
git archive HEAD | tar -x -C build-core-integration-normal/head-archive
cmake -S build-core-integration-normal/head-archive/engine \
  -B build-core-integration-normal/head-archive-build \
  -DENGINE_BUILD_TESTS=ON -DENGINE_RHI_BACKEND=auto \
  -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-core-integration-normal/head-archive-build -j3
ctest --test-dir build-core-integration-normal/head-archive-build \
  --output-on-failure -j3 -R '^test_core_app_'
```

临时恢复旧 magic，确认 writer/reader 合同 RED；恢复 `CORECKPT` 后重跑 GREEN。随后先提交源码、测试和正式资产，确保下一步的 HEAD 包含刚验证的格式：

```bash
git add engine/apps/core_app engine/tests/test_core_app_* engine/assets/core_app
git commit -m "refactor: migrate core app data formats"
```

- [ ] **Step 5: 普通、sanitizer 与 no-tests 验证**

分别使用独立构建目录，选项均为仓库现有 `ENGINE_USE_ASAN`、`ENGINE_USE_UBSAN`、`ENGINE_USE_TSAN`：

```bash
cmake -S engine -B build-core-integration-asan \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF \
  -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON
cmake --build build-core-integration-asan -j3
ctest --test-dir build-core-integration-asan -LE 'graphics|fuzz' \
  --output-on-failure -j3

cmake -S engine -B build-core-integration-tsan \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF \
  -DENGINE_USE_TSAN=ON
cmake --build build-core-integration-tsan -j3
ctest --test-dir build-core-integration-tsan --output-on-failure -j3 \
  -R '^test_core_app_lifecycle_load_unload$'

cmake -S engine -B build-core-integration-no-tests \
  -DENGINE_BUILD_TESTS=OFF -DENGINE_RHI_BACKEND=auto \
  -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-core-integration-no-tests -j3
```

普通全量必须零失败；ASan+UBSan 全量与 TSan lifecycle 不得有 sanitizer/race 报告。no-tests 必须仍定义三个应用 target，且不引入新链接依赖。

- [ ] **Step 6: 更新事实文档、独立复审并提交**

在 `docs/design/core_app_integration.md` 和 `docs/Implementation_Status.md` 顶部补充当前名称、格式、真实测试数量与 native 限制；保留旧状态段落作为历史，不反向改写。`core_app_integration.md` 和当前 P12 计划使用新格式，不保留旧格式作为可选输入。台账记录每条 RED/GREEN、变异、hash、独立规格/质量评审结论和 Task 3 follow-up 是否仍未覆盖。Task 9 的 256 声音队列扩容不提前伪装完成。

`git diff --check` 通过、Critical/Important 清零后提交，标题使用 `docs: record core app migration evidence`。此时命名迁移才算完成，后续 Compose 和 P12 Task 4–13 使用新名称。
