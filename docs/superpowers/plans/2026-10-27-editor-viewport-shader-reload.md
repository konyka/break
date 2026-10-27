# Editor Viewport Shader Reload Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 为 editor 的 proxy/gizmo viewport 交付可恢复、失败保旧、owner-thread 提交的 vertex/fragment shader 热加载。

**Architecture:** `editor_shader_source` 统一路径解析；`BreakEditorViewport3D` 独占 GPU candidate/live 状态；`BreakEditorShaderReload` 由 viewport 持有并用一个 Runtime Core coordinator 聚合两个文件请求。watcher 只发提示，worker 只读 VFS，shell tick 在 frame 外构建并发布完整 candidate。

**Tech Stack:** C11、CTest、现有 Runtime Core/VFS/FileWatcher、RHI、现有 myui console/render debugger、Vulkan 与 OpenGL。

## Global Constraints

- 设计合同：`docs/superpowers/specs/2026-10-27-editor-viewport-shader-reload-design.md`。
- 默认 Vulkan 不变；OpenGL 永久保留为最终降级方案和渲染对比基准。
- 生产代码 C11；不增加依赖、UI 框架、线程池、RenderThread 或 Runtime Core batch ABI。
- `engine/src/asset/hotreload.c` 和游戏 renderer 的现有同步 hot reload 行为不变。
- 每个文件不超过 `SHADER_MAX_FILE_BYTES`（4 MiB）；路径不得截断成另一个资源名。
- 新功能先 RED 后实现；mutation 后恢复源码；不对已提交 golden 使用 `GOLDEN_UPDATE=1`。
- 不交付纹理热加载、scene-faithful 材质、`#include` 依赖、device migration、Metal/D3D12 或 Windows/macOS 运行证据。
- 每个任务独立提交；完成后复验并独立 review，最后 `--no-ff` 合并到本地 master，不推送远端。

## File Structure

- Create `engine/apps/editor/editor_shader_source.{h,c}`：固定五个候选根、backend variant 逻辑名、bounded read、实际命中路径。
- Create `engine/apps/editor/editor_shader_reload.{h,c}`：watcher/VFS/coordinator、pair staging、trailing pending、stats、bounded shutdown。
- Modify `engine/apps/editor/editor_viewport3d.{h,c}`：source 初始加载、事务式 GPU candidate、reload owner 生命周期、owner tick/request/stats。
- Modify `engine/apps/editor/editor_panels.c`、`editor_panels.h`、`editor_shell_internal.h`：shell tick/device/logger 接线和精确的 Ctrl+Shift+R chord。
- Modify `engine/apps/editor/editor_main.c`：只补充 shader reload 生命周期说明；host 仍只创建 shell/device，GPU owner 留在 viewport。
- Modify `engine/apps/editor/editor_panel_render.c`：一行只读 shader reload 状态，不增加控制按钮。
- Create `engine/tests/rhi_editor_fake.h` 并 modify `engine/tests/rhi_stubs.c`：测试专用、显式启用的 RHI fake；默认 stub 行为不变。
- Modify `engine/tests/test_editor_shell.c`、`engine/tests/test_break_editor_target_contract.cmake`、`engine/CMakeLists.txt`：RED、集成测试、production/test/fuzz 成员合同。
- Modify `docs/design/editor_hot_reload.md`、`docs/design/editor_viewport.md`、`docs/design/roadmap_2026-10-22.md`、`docs/Implementation_Status.md`、`docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`：只追加/纠正交付事实，保留纹理和跨平台未交付边界。

---

### Task 1: 统一 source resolver 与事务式 GPU candidate

**Files:**
- Create: `engine/apps/editor/editor_shader_source.h`, `engine/apps/editor/editor_shader_source.c`
- Modify: `engine/apps/editor/editor_viewport3d.h`, `engine/apps/editor/editor_viewport3d.c`
- Create: `engine/tests/rhi_editor_fake.h`
- Modify: `engine/tests/rhi_stubs.c`, `engine/tests/test_editor_shell.c`
- Modify: `engine/CMakeLists.txt`, `engine/tests/test_break_editor_target_contract.cmake`

**Interfaces:**
- Produces:

```c
typedef enum { BREAK_EDITOR_SHADER_VERTEX = 0,
               BREAK_EDITOR_SHADER_FRAGMENT = 1 } BreakEditorShaderStage;

typedef struct {
    char roots[5][VFS_MAX_PATH]; /* highest priority first */
    u32 root_count;
    char logical[2][96];
    u32 skipped_roots;
} BreakEditorShaderSource;

typedef struct {
    char *data;       /* owned; data[size] == '\0' */
    usize size;
    char path[1024];  /* actual successful path, not a guessed prefix */
} BreakEditorShaderBytes;

bool break_editor_shader_source_configure(BreakEditorShaderSource *s,
                                          RHIShaderVariant variant);
void break_editor_shader_source_destroy_bytes(BreakEditorShaderBytes *bytes);
bool break_editor_shader_source_read(const BreakEditorShaderSource *s,
                                     BreakEditorShaderStage stage,
                                     BreakEditorShaderBytes *out);
const char *break_editor_shader_source_path(
    const BreakEditorShaderSource *s, BreakEditorShaderStage stage);

bool break_editor_viewport3d_prepare(BreakEditorViewport3D *vp,
                                     void *rhi_device);
bool break_editor_viewport3d_reload_shader_source(
    BreakEditorViewport3D *vp, const void *vert, usize vert_size,
    const void *frag, usize frag_size);
```

- `prepare` records the borrowed non-NULL device even if a later step fails; it never supports migration to a different device. `reload_shader_source` builds a complete candidate and returns false without altering live state.
- Test-only under `BREAK_EDITOR_SHELL_TESTING`:

```c
typedef struct {
    RHIPipeline pipeline;
    const void *bindings;
    i32 loc_mvp, loc_color;
    RHIBuffer vbo;
} BreakEditorViewport3DGpuState;
void break_editor_viewport3d_gpu_state_for_test(
    const BreakEditorViewport3D *vp, BreakEditorViewport3DGpuState *out);
```

- [ ] **Step 1: 写 resolver RED**

在 `test_editor_shell.c` 新建临时 `<root>/shaders`，设置 `BREAK_SHADER_DIR=root`，测试 GL 与 VK 两个逻辑名、实际命中路径、file bytes 和 cleanup。POSIX 用 `setenv/unsetenv`，Windows 用 `_putenv_s`；每个测试恢复原环境。

```c
BreakEditorShaderSource source;
BreakEditorShaderBytes bytes;
ASSERT_TRUE(break_editor_shader_source_configure(
    &source, RHI_SHADER_VARIANT_GLSL));
ASSERT_STR_EQ(break_editor_shader_source_path(
    &source, BREAK_EDITOR_SHADER_VERTEX), "shaders/editor_color.vert");
ASSERT_TRUE(break_editor_shader_source_read(
    &source, BREAK_EDITOR_SHADER_VERTEX, &bytes));
ASSERT_STR_EQ(bytes.path, vert_path);
ASSERT_STR_EQ(bytes.data, "REV=1 vertex\n");
break_editor_shader_source_destroy_bytes(&bytes);
ASSERT_TRUE(bytes.data == NULL && bytes.size == 0u);
```

再加一个空文件/缺失文件测试：高优先级缺失时读取低优先级；所有候选缺失时 `out` 保持零初始化，不能返回部分 allocation。

- [ ] **Step 2: 编译并确认 resolver RED**

Run: `cd build-current-vk && make -j6 test_editor_shell && ./test_editor_shell`

Expected: 因 `editor_shader_source.h`/接口尚不存在而编译失败。不得通过删除测试或复制旧 `vp_read_shader` 来变绿。

- [ ] **Step 3: 实现 bounded resolver**

候选顺序严格为 `BREAK_SHADER_DIR`（非空时）、`.`、`engine`、`../engine`、`../../engine`。`shader_variant_path` 生成逻辑名；root 必须短于 `VFS_MAX_PATH`，完整读取路径必须短于 1024，否则跳过该候选并计 `skipped_roots`。join 用显式长度检查，不依赖截断的 `snprintf` 结果。

`read` 每次都按当前文件是否存在重新选择候选，因此高优先级删除后可回退。`shader_read_file` 继续负责 4 MiB 限制；成功后同时复制实际 path 到调用方 1024-byte buffer。把新 TU 加入 editor/test_editor_shell/fuzz_editor_remote，确保三个目标都能链接。

- [ ] **Step 4: 写 candidate 保旧和初次恢复 RED**

`rhi_editor_fake.h` 提供：

```c
typedef struct {
    u32 pipeline_creates, pipeline_destroys;
    u32 binding_destroys, buffer_creates;
    u32 live_shaders, live_pipelines, live_bindings, live_buffers;
} EditorRhiFakeStats;
void editor_rhi_fake_reset(void);
void editor_rhi_fake_set_enabled(bool enabled);
void editor_rhi_fake_stats(EditorRhiFakeStats *out);
u32 editor_rhi_fake_pipeline_revision(RHIPipeline pipeline);
```

fake 仅在 `BREAK_EDITOR_SHELL_TESTING` 且 enabled 时改变旧 stub；capabilities 返回 `RHI_SHADER_VARIANT_GLSL`。唯一非零 handle 追踪 live 状态。bounded source marker 驱动失败：`COMPILE_FAIL`、`LINK_FAIL`、`BINDINGS_FAIL`、`NO_MVP`、`NO_COLOR`；`REV=<decimal>` 记录 pipeline revision。不得用 `strstr` 越过调用方 `len`。

RED 测试先 `prepare`，再发布 `REV=1`，保存完整 GPU state，随后逐个注入上述失败及 `REV=2`：

```c
static const char bad_vert[] = "REV=2 COMPILE_FAIL";
static const char good_frag[] = "fragment";
BreakEditorViewport3DGpuState before, after;
break_editor_viewport3d_gpu_state_for_test(vp, &before);
ASSERT_FALSE(break_editor_viewport3d_reload_shader_source(
    vp, bad_vert, sizeof(bad_vert) - 1u,
    good_frag, sizeof(good_frag) - 1u));
break_editor_viewport3d_gpu_state_for_test(vp, &after);
ASSERT_EQ(before.pipeline.generation, after.pipeline.generation);
ASSERT_TRUE(before.bindings == after.bindings);
ASSERT_EQ(before.loc_mvp, after.loc_mvp);
ASSERT_EQ(before.loc_color, after.loc_color);
ASSERT_EQ(editor_rhi_fake_pipeline_revision(after.pipeline), 1u);
```

断言临时 shaders/bindings/pipeline 全部销毁，live counts 回到 A 的数量。另一个测试从未成功的 `COMPILE_FAIL` 进入 INIT_FAILED，再用 `REV=3` 成功，验证 VBO 创建、READY 和无重试。

- [ ] **Step 5: 运行并确认 candidate RED**

Run: `cd build-current-vk && make -j6 test_editor_shell && ./test_editor_shell`

Expected: 新 GPU-state/fake/reload 接口缺失或断言失败；已有测试不能通过改变默认 `rhi_stubs` 行为来“修复”。

- [ ] **Step 6: 实现 fake 与事务式 candidate**

把 `vp_lazy_init` 的 VS/FS -> pipeline -> bindings -> resolve -> VBO 部分提取为 candidate builder。candidate 使用局部变量；只有所有步骤成功才写 `vp->pipeline/bindings/loc_mvp/loc_color/cube_vbo/init_state`。已有 VBO/FBO 不重建；初次失败创建的 VBO 由 candidate cleanup 回收。发布后再销毁旧 pipeline/bindings。

初次加载从 `BreakEditorShaderSource` 读取两个文件并调用同一个 builder。`prepare` 先记录 device，再解析 caps/source；device 指针不再是资源清理是否发生的猜测条件。无新请求时 sticky INIT_FAILED 仍避免逐帧重试，但显式 `reload_shader_source` 可从该状态恢复。

- [ ] **Step 7: 验证 Task 1 并做保旧 mutation**

Run: `cd build-current-vk && make -j6 test_editor_shell && ./test_editor_shell`

Expected: 全部通过，旧测试数量之外的新测试均实际执行。临时移除 candidate 成功前的 uniform resolve 检查，确认 `NO_MVP`/`NO_COLOR` 测试变红；立即恢复源码并重跑为绿。

- [ ] **Step 8: 提交 Task 1**

```bash
git add engine/apps/editor/editor_shader_source.* \
  engine/apps/editor/editor_viewport3d.* engine/tests/rhi_editor_fake.h \
  engine/tests/rhi_stubs.c engine/tests/test_editor_shell.c \
  engine/CMakeLists.txt engine/tests/test_break_editor_target_contract.cmake
git commit -m "editor: make viewport shader replacement transactional"
```

---

### Task 2: Runtime Core pair staging、watcher 与 trailing reload

**Files:**
- Create: `engine/apps/editor/editor_shader_reload.h`, `engine/apps/editor/editor_shader_reload.c`
- Modify: `engine/apps/editor/editor_viewport3d.{h,c}`
- Modify: `engine/apps/editor/editor_panels.c`, `engine/CMakeLists.txt`
- Test: `engine/tests/test_editor_shell.c`, `engine/tests/test_break_editor_target_contract.cmake`

**Interfaces:**
- Consumes Task 1 的 source/resolver、`prepare` 和 `reload_shader_source`。
- Produces:

```c
typedef enum { BREAK_EDITOR_SHADER_RELOAD_IDLE = 0,
               BREAK_EDITOR_SHADER_RELOAD_BUSY,
               BREAK_EDITOR_SHADER_RELOAD_APPLIED,
               BREAK_EDITOR_SHADER_RELOAD_FAILED_KEEP_OLD,
               BREAK_EDITOR_SHADER_RELOAD_UNAVAILABLE } BreakEditorShaderReloadResult;

typedef struct {
    bool watching; /* at least one candidate path registered */
    bool busy;
    int last_result;
    u64 events, attempts, reloads, failed;
} BreakEditorShaderReloadStats;

typedef void (*BreakEditorShaderReloadLog)(void *user, const char *line);
void break_editor_viewport3d_set_shader_reload_logger(
    BreakEditorViewport3D *vp, BreakEditorShaderReloadLog log, void *user);
void break_editor_viewport3d_tick(BreakEditorViewport3D *vp);
bool break_editor_viewport3d_request_shader_reload(BreakEditorViewport3D *vp);
bool break_editor_viewport3d_shader_reload_stats(
    const BreakEditorViewport3D *vp, BreakEditorShaderReloadStats *out);
```

- viewport owns `BreakEditorShaderReload`; its source pointer remains valid until reload destroy. logger 只在 shell/owner 线程调用，worker 不接触它。
- [ ] **Step 1: 写真实 watcher -> worker -> swap RED**

fixture 在临时 engine root 写 `REV=1` 两个文件，启用 fake，创建 shell/viewport 并 `prepare`。通过真实初始 render 读取 A；随后将两文件改为 `REV=2`，用现有 `hr_bump_mtime` 强制不同秒，循环 `break_editor_shell_tick` 直到 `stats.reloads == 1`。

```c
BreakEditorShaderReloadStats stats;
BreakEditorViewport3DGpuState current;
EditorRhiFakeStats fake_stats;
ASSERT_TRUE(break_editor_viewport3d_shader_reload_stats(vp, &stats));
break_editor_viewport3d_gpu_state_for_test(vp, &current);
editor_rhi_fake_stats(&fake_stats);
ASSERT_TRUE(stats.watching);
ASSERT_EQ(stats.attempts, 1u);
ASSERT_EQ(editor_rhi_fake_pipeline_revision(current.pipeline), 2u);
ASSERT_EQ(fake_stats.pipeline_destroys, 1u);
ASSERT_EQ(fake_stats.binding_destroys, 1u);
ASSERT_EQ(fake_stats.buffer_creates, 1u);
```

另写 `REV=3 COMPILE_FAIL`，等待 `failed == 1`，断言 revision/live state 仍为 2。再写 `REV=4`，等待第二次成功，证明失败后恢复。

- [ ] **Step 2: 确认接线 RED**

Run: `cd build-current-vk && make -j6 test_editor_shell && ./test_editor_shell`

Expected: reload tick/request/stats 接口不存在，或修改文件后 attempts/reloads 一直为 0。记录实际失败输出。

- [ ] **Step 3: 实现一个 coordinator 的 pair attempt**

`BreakEditorShaderReload` 持有一个 VFS、`FileWatcher`、一个 worker 的 coordinator、两个 handles、两个 owned staging buffers。按 source roots 逆序 mount，watcher 添加每个未超 `FILEWATCH_MAX_PATH` 的候选完整路径；所有路径不能 watch 时仍保留 coordinator 供 manual request。

每次 attempt 对 vertex/fragment 各发一个真实 logical-path request。validate 只检查 `size <= SHADER_MAX_FILE_BYTES` 和 byte pointer 形状。owner commit 按 path 找到 stage，`malloc(size+1)`、复制并 NUL 终止；不得保留 borrowed bytes。poll 消费两个终态后，只有二者均 COMMITTED 且 staging 完整才调用 `reload_shader_source`。

第二次 request 失败时 cancel 第一次并 poll 掉 CANCELLED；任何失败只记一次 attempt failure，pending 已被消费时不每帧自动重试。staging 在 attempt 收尾释放，避免跨 attempt 混用。

- [ ] **Step 4: 接 viewport/shell 生命周期并验证基本路径**

`prepare` 在 source 配置成功后创建 reload owner（创建失败不破坏初始同步加载）；viewport destroy 先 shutdown/destroy reload，再释放 GPU 对象。`break_editor_shell_tick` 调用 `break_editor_viewport3d_tick`，`break_editor_shell_set_render_device` 对非 NULL device 调用 `prepare`；NULL detach 只影响 debugger，不得抹掉 GPU destroy 所需的 borrowed device。

Run: `cd build-current-vk && make -j6 test_editor_shell && ./test_editor_shell`

Expected: A->B、坏版本保旧、修复恢复通过，scene hot reload 既有测试不受影响。

- [ ] **Step 5: 写 worker 不碰 RHI、单侧失败和 trailing RED**

包含 `runtime/runtime_test_hooks.h`。在 `break_runtime_test_reload_set_gates(0,1)` 下发起 attempt，断言 busy 且 pipeline create 计数不变；gate 释放前 RHI create 必须为 0。释放 gate 前写 `REV=3` 并再 request，释放后等待 trailing attempt，最终 revision=3 且 attempts>=2。

单侧失败测试删除 fragment、保留合法 vertex，等待失败，断言 pipeline_creates 不增加。每个 gate 测试必须在所有退出路径恢复 `break_runtime_test_reload_set_gates(0,0)`，不能留下会影响其他测试的全局 gate。

- [ ] **Step 6: 实现 trailing 与有界 teardown**

attempt 期间的 file callback/manual request 只置 `pending`；只有 handles 都 terminal、scratch 清空后才开启下一轮。shutdown 先停 watcher，再 bounded shutdown coordinator；成功才 destroy coordinator/VFS/object，超时保留有界对象并报告。worker hooks 不得 dereference viewport。

用 `gate_claim=1` 让 attempt 停在 QUEUED 后销毁 shell（shutdown 可绕过 claim gate），验证不挂死、不泄漏。另在直接 reload fixture 中用 test-only `shutdown_timeout_ms=0` 和 `gate_load=1` 验证首次 shutdown false，释放 gate 后 retry/destroy 成功；测试 hook 只在 `BREAK_EDITOR_SHELL_TESTING` 暴露。

- [ ] **Step 7: 更新构建合同并复验**

把 `editor_shader_source.c` 和 `editor_shader_reload.c` 同时加入 production editor、test_editor_shell、fuzz_editor_remote；target contract 检查三者成员及 runtime_core/runtime_core_test 链接，不允许 engine/engine_demo/dxx_break 新增 runtime_core 依赖。

Run: `cd build-current-vk && make -j6 test_editor_shell && ctest -R 'test_editor_shell|test_break_editor_target_contract|test_runtime_reload|test_hotreload' --output-on-failure`

Expected: 全部通过。源码中不得出现 worker 调 RHI、logger 或 shell 的路径。

- [ ] **Step 8: 提交 Task 2**

```bash
git add engine/apps/editor/editor_shader_reload.* \
  engine/apps/editor/editor_shader_source.* \
  engine/apps/editor/editor_viewport3d.* engine/apps/editor/editor_panels.c \
  engine/tests/test_editor_shell.c engine/tests/rhi_stubs.c \
  engine/CMakeLists.txt engine/tests/test_break_editor_target_contract.cmake
git commit -m "editor: hot reload viewport shaders through runtime core"
```

---

### Task 3: 手动重载、console 与诊断状态

**Files:**
- Modify: `engine/apps/editor/editor_panels.c`, `engine/apps/editor/editor_panels.h`, `engine/apps/editor/editor_shell_internal.h`
- Modify: `engine/apps/editor/editor_viewport3d.{h,c}`, `engine/apps/editor/editor_shader_reload.{h,c}`
- Modify: `engine/apps/editor/editor_panel_render.c`, `engine/apps/editor/editor_main.c`
- Test: `engine/tests/test_editor_shell.c`

**Interfaces:**
- Consumes Task 2 的 request/stats/logger。
- Produces `ACT_RELOAD_SHADERS` shortcut action；普通 `R`/`Shift+R` 继续映射 `ACT_TOOL_SCALE`。
- [ ] **Step 1: 写快捷键与状态 RED**

在已创建 reload owner 的 fixture 中，将文件改成 `REV=5` 但不 bump mtime；dispatch `r` + `MY_KEYMOD_CTRL|MY_KEYMOD_SHIFT`，等待成功。断言 manual request 没有同步增加 RHI create（dispatch 返回后、tick 前），最终 revision=5。

再分别 dispatch `r`+SHIFT 和 `r`+NONE，断言 tool 为 Scale 且 attempts 不增加。无 owner/NULL 参数必须有界返回，不能因 optional reload allocation failure 使 shell 崩溃。

render debugger 增加一行后，已有 8 行设备状态保留，新增行形如：

```text
shader reload: watching busy=0 applied=2 failed=1
```

无 reload owner 时显示 `shader reload: unavailable`，而不是伪造 watching。

- [ ] **Step 2: 运行并确认 RED**

Run: `cd build-current-vk && make -j6 test_editor_shell && ./test_editor_shell`

Expected: Ctrl+Shift+R 未触发 reload，或 render row 不存在；Shift+R 既有断言必须仍绿。

- [ ] **Step 3: 实现精确 chord 与有界日志**

在 ASCII 字母忽略 SHIFT 的通用循环之前增加专用分支：

```c
if (key == 'r' &&
    modifiers == (MY_KEYMOD_CTRL | MY_KEYMOD_SHIFT)) {
    if (!break_editor_viewport3d_request_shader_reload(shell->vp3d)) {
        editor_shell_log(shell, "shader reload: unavailable");
    }
    return true;
}
```

不修改现有 `relevant` 规则。shell 创建 viewport 后注册一个静态 logger adapter，将 line 通过 `editor_shell_log(shell, "%s", line)` 写入现有 ring；不引入 widget/document worker 引用。成功、失败、watch unavailable 和 trailing 只输出有界一行，不能让 worker 直接写 console。

render panel 只调用 `break_editor_viewport3d_shader_reload_stats`，不得调用 request/tick/RHI mutation；更新只读 source-scan 测试。main 注释说明 reload 由 viewport 拥有、shell 在 device 前销毁。

- [ ] **Step 4: 验证手动路径与 source 边界**

Run: `cd build-current-vk && make -j6 test_editor_shell && ctest -R 'test_editor_shell|test_break_editor_target_contract' --output-on-failure`

Expected: manual、Shift+R、console、diagnostic row、缺失后创建、删除后回退、超长路径不截断均通过；旧 82 个 shell 测试不回归。

- [ ] **Step 5: 提交 Task 3**

```bash
git add engine/apps/editor engine/tests/test_editor_shell.c \
  engine/CMakeLists.txt engine/tests/test_break_editor_target_contract.cmake
git commit -m "editor: add manual shader reload and diagnostics"
```

---

### Task 4: 全量验证、独立 review、文档与合并

**Files:**
- Modify only as review/evidence requires: `docs/design/editor_hot_reload.md`, `docs/design/editor_viewport.md`, `docs/design/roadmap_2026-10-22.md`, `docs/Implementation_Status.md`, `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`
- Modify if defects are found: exact implementation/test files from Tasks 1-3.

**Interfaces:**
- Consumes all previous tasks; does not add texture ownership or new runtime APIs.
- [ ] **Step 1: 四棵正常树全量非图形测试**

对每个目录执行：

```bash
cd /home/timeshift/opensource/break/build-current-gl && make -j6 && \
  ctest -LE 'graphics|fuzz' -j4 --timeout 240
cd /home/timeshift/opensource/break/build-current-vk && make -j6 && \
  ctest -LE 'graphics|fuzz' -j4 --timeout 240
cd /tmp/mb && make -j6 && ctest -LE 'graphics|fuzz' -j4 --timeout 240
cd /home/timeshift/opensource/break/build-sdd-p4-final && make -j6 && \
  ctest -LE 'graphics|fuzz' -j4 --timeout 240
```

Expected: 每树 0 failed；记录实际 selected/passed/skipped 数。若失败，先区分预存问题和本分支回归，不得删测试或缩小集合。

- [ ] **Step 2: Sanitizer 与 fuzz 复验**

```bash
cd /home/timeshift/opensource/break/build-sdd-p4-asan && make -j6 test_editor_shell && \
  ./test_editor_shell && ./test_editor_shell && ./test_editor_shell && \
  make -j6 test_runtime_reload test_hotreload && \
  ctest -R 'test_runtime_reload|test_hotreload' --output-on-failure
cd /home/timeshift/opensource/break/build-sdd-p4-tsan && make -j6 test_editor_shell && \
  ./test_editor_shell && make -j6 test_runtime_reload && ./test_runtime_reload
cd /home/timeshift/opensource/break/build-sdd-p4-asan && \
  make -j6 fuzz_scene_serial fuzz_net_packet fuzz_decode_image fuzz_vfs_pak \
    fuzz_asset_gltf fuzz_editor_remote && ctest -L fuzz --output-on-failure
```

Expected: ASan/UBSan/TSan 零报告，测试和现有 fuzz smoke 全过。再对 worker/teardown 用例做至少 20 次重复运行；不得把普通 stub 测试当成真实 GPU 证明。

- [ ] **Step 3: Vulkan/OpenGL 真实 editor 验证**

复制完整 `engine/shaders` 到临时 engine root，以 `BREAK_SHADER_DIR` 指向它，从 `engine/` 启动 `/tmp/mb/editor`（默认 Vulkan）和 `BREAK_RHI_BACKEND=opengl /tmp/mb/editor`。使用带一个原点实体的临时 `.bscn`，分别修改实际 backend 的 `editor_color[ _vk].frag`：

```c
/* GL: 必须继续消费 u_color，避免 uniform 被优化掉 */
frag_color = u_color * vec4(1.0, 0.0, 1.0, 1.0);
/* VK: 保持 push-constant block 不变，仅替换 main 中的表达式 */
frag_color = pc.u_color * vec4(1.0, 0.0, 1.0, 1.0);
```

用 X11 `import -window <id>` 截取 viewport，并结合 console/stats 验证：有效修改、坏语法保旧、修复恢复、Ctrl+Shift+R。比较 Vulkan/OpenGL 相同场景的颜色与布局，保留截图/日志作为证据；不更新 golden。若某个环境只能取得日志或状态，明确写“逻辑 live smoke，非视觉/GPU 正确性证明”，不得宣称像素验证。

- [ ] **Step 4: 独立 review 与针对性修复**

派发 coder 子代理只读 review `master...HEAD`，重点：pair 的 terminal/staging 配对、路径优先级、旧 GPU 状态保旧、fake 默认行为、worker/logger 生命周期、shutdown timeout、测试是否能捕获真实缺陷。主代理核验每条意见；先为接受的 Important/Critical 写 RED，再修复并重复 Steps 1-3 受影响范围。

- [ ] **Step 5: 文档收口与最终验证**

在 `editor_hot_reload.md` 追加 shader 已交付范围，在 `editor_viewport.md` 更新 GPU 生命周期；roadmap/status/todo 将 shader hot reload 标为完成，纹理仍明确等待“真实图片 preview -> texture reload”。记录实际测试数、live 证据级别和未运行的 Windows/macOS/CI。不得覆盖已有段落或把旧设计报告改成未发生的事实。

最终重跑 `git diff --check`、`git status --short`、受影响测试，确认工作区只含本任务修改。

- [ ] **Step 6: 提交并合并**

```bash
git add docs/design docs/Implementation_Status.md docs/superpowers/plans
# 若有 review 修复，精确 add 对应源码和测试并先提交修复。
git commit -m "docs: record editor viewport shader hot reload"
git switch master
git merge --no-ff sdd/editor-shader-reload -m "merge: editor viewport shader hot reload"
git status --short
```

Expected: 本地 master 包含完整子项目，工作区干净；不推送，不声明未验证平台已完成。
