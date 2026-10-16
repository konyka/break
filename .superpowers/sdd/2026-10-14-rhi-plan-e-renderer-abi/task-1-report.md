# Plan E / Task 1 报告：rhi_oracle 基础设施（golden-image readback oracle 抽取）

日期：2026-10-14（计划 E Task 1）
需求书：`task-1-brief.md`（同目录）
构建目录：`build-vk`（clang/lld，Debug，ENGINE_VULKAN=ON，-Werror -pedantic，C11）

## 交付物

| 文件 | 变更 |
|---|---|
| `engine/tests/rhi_oracle.h` | 新建 — API 与需求书 Produces 块逐字一致 |
| `engine/tests/rhi_oracle.c` | 新建 — 从 test_vulkan.c 搬迁的 golden 实现 |
| `engine/tests/test_rhi_oracle.c` | 新建 — 需求书给定测试代码，逐字未改（3 个 TEST） |
| `engine/src/test_vulkan.c` | 修改 — 删除 golden_* 本体；`golden_compare_buffer` 保留为 wrapper；头部加 `#include "../tests/rhi_oracle.h"` |
| `engine/CMakeLists.txt` | 修改 — 注册 `test_rhi_oracle`；`test_vulkan` 追加 `tests/rhi_oracle.c` 源 |

行为逐点保持项：box 均值降采样 20x15、`fscanf("P6 %d %d %d")` 解析、`mae<=8.0 && maxd<=56` 容差、`GOLDEN_UPDATE` 环境变量再生语义、reject_blank 全平色检测、LOG 文本逐字不变（`GOLDEN: %s MAE=%.2f max=%u (tol MAE<=8.0 max<=56) -> %s` 等）。

## 红 → 绿证据（TDD）

红（Step 2，`rhi_oracle.c` 为空 TU，仅声明在头文件）：

```
$ cmake --build build-vk --target test_rhi_oracle
lld-link: error: undefined symbol: rhi_oracle_write_ppm
>>> referenced by engine\tests\test_rhi_oracle.c:29
lld-link: error: undefined symbol: rhi_oracle_compare_frame
>>> referenced by engine\tests\test_rhi_oracle.c:43
（同批还有 rhi_oracle_downsample / rhi_oracle_compare_ppm）
ninja: build stopped: subcommand failed.  build_exit=1
```

绿（Step 4）：

```
$ cmake --build build-vk --target test_rhi_oracle && (cd engine && ../build-vk/test_rhi_oracle)
=== Running Tests ===
  [1] downsample_constant_frame_is_constant_grid ... OK
  [2] ppm_roundtrip_and_drift_detection ... OK
  [3] compare_frame_rejects_blank_when_asked ... OK（先打 GOLDEN flat-color ERROR 再判 false，符合预期）
=== Results: 3 passed, 0 failed, 3 total ===
$ ctest --test-dir build-vk -R '^test_rhi_oracle$'
100% tests passed, 0 tests failed out of 1
```

## test_vulkan 重构等价验证（Step 5-6，VK lane）

基线状态说明（规格 §7 已裁定的环境性失败）：本机 NVIDIA 混合 GPU 环境下 test_vulkan **重构前即失败**。重构前基线（`evidence/baseline_test_vulkan_pre.txt`）：运行至 PBR MATERIAL FACTOR 起发生 `VK_ERROR_DEVICE_LOST`（伴 `vkWaitForFences failed`、`UnifiedCull: Hi-Z sampler/fallback creation failed`），此后 PBR/点阴影/Hi-Z/间接绘制/延迟渲染各 TEST 连锁失败；两个 GOLDEN TEST 因设备已丢、捕获不到帧而在比较前失败（日志中**无** MAE 行）；ctest 记 Timeout(180s)。

重构后（`evidence/post_test_vulkan.txt`）：同一失败签名 —— RESULT 集合逐项一致（27 项 RESULT 行 sort|uniq -c 完全相同），GOLDEN 区段日志逐条对应：

| | 重构前 | 重构后 |
|---|---|---|
| GOLDEN IMAGE REGRESSION | `test_vulkan.c:313` → `:352 FAILED` | `test_vulkan.c:210` → `:249 FAILED` |
| GOLDEN CAMERA | `test_vulkan.c:366` → `:415 FAILED` | `test_vulkan.c:263` → `:312 FAILED` |

行号统一偏移 -103（= 删除的 helper 行数），失败点语义完全一致。重构后本次设备丢失发生更早（27.6s Failed vs 180s Timeout），属同一环境性抖动的时间差异，失败集合相同。按任务纪律：未为求绿去修环境性问题。

**golden 参考未被再生成**：两次运行前后 `git status --porcelain -- engine/tests/golden/` 均为空（4 个 .ppm 参考保持 HEAD:22582a7a 状态）。

### 补充数值等价证明（compare 路径本机跑不到，用单元级证据补强）

`evidence/equiv_downsample.c`（一次性校验程序，不进构建）：git HEAD 版 `golden_downsample` 与 `rhi_oracle_downsample` 在 640x480 / 800x600 / 1280x720 / 1920x1080 / 20x15 / 37x29 六种尺寸 × 8 组随机帧下 grid **逐字节一致**（`EQUIV: PASS`）；8x8 退化帧按设计分歧（见下「偏差 2」）。PPM 写/读/容差/blank 判定路径由 test_rhi_oracle 的 3 个 TEST 覆盖。

## 全量回归

`ctest --test-dir build-vk -R "rhi|vulkan"`（21 个测试）：**20/21 通过**，唯一失败为 `test_vulkan`（即上述已裁定的环境性基线失败，签名与重构前一致；无新增回归）。见 `evidence/ctest_rhi_vulkan_post.txt`（`95% tests passed, 1 tests failed out of 21`）。运行后 golden/*.ppm 依旧干净。

## 与需求书的偏差（均已在代码注释/上文说明）

1. **test_rhi_oracle 追加链接 `engine_rhi_headless m`**：需求书注册块只列 `src/core/log.c`，但 Debug 构建不做 section GC，`rhi_oracle_capture_presented` 引用的 `rhi_screenshot` 必须可解析（首轮链接即报 `undefined symbol: rhi_screenshot`）。采用同文件上方 test_rhi_capabilities 的既有模式链接 headless 后端解决，headless 静态库只被按需拉取，不改变被测语义。
2. **降采样空 box 回退**：需求书测试 `downsample_constant_frame_is_constant_grid` 用 8x8 帧（< 20x15 网格），旧实现此时 n=0 输出黑色、该测试必失败。实现改为空 box 回退为最近源像素。**w≥20 且 h≥15 时每个 box 恒非空**（floor 差 ≥1），真实 presented 帧（窗口尺寸）永不触发该分支 —— 由上述数值等价证明逐字节验证。头部注释已注明。
3. **行号偏差**：需求书说 `add_executable(test_vulkan ...)` 在 CMakeLists.txt:1107，实际在 :1481（注册块位置以实际文件为准）。
4. **删除 test_vulkan.c 中随搬迁失去唯一消费者的死代码**：`tv_mkdir` 宏块（:28-34）与 `GOLDEN_GW/GH` define —— 它们的唯一使用者就是被删除的 golden_* 本体。wrapper `golden_compare_buffer` 按需求书保留。

## GL lane

本机无 GL 环境（build-vk 为 Vulkan 配置），按任务纪律记为 **CI 验证项**（Linux Xvfb `gl` lane 跑 test_vulkan 并比对 `test_vulkan_gl*.ppm` golden 日志），未伪造。

## 冻结文件与纪律核对

- `.scratch-vkprobe/`、`engine/profile_trace.json`、根 `d3d12_shader_gate.{hlsl,dxil}`、用户 stash：未触碰。
- `.tmp/`：运行日志一度写入后已移出至本目录 `evidence/`，`.tmp/` 内容恢复原状。
- `engine/CMakeLists.txt` 编辑后经字节级核实仍为纯 CRLF（3510 CRLF / 0 lone LF）；`engine/src/test_vulkan.c` 同为纯 CRLF。
- commit 前 `git status --porcelain` 核对暂存清单仅含需求书 Files 列出的 5 个文件；未 amend、未 `git add -A`。

## Commit

- 代码：`9407c222` `test(rhi): extract golden-image readback oracle from test_vulkan into reusable rhi_oracle`（严格 5 文件，暂存清单已核对）
- 报告+证据：本文件与 `evidence/` 随第二个 commit（`.superpowers` 在 .gitignore 中，按需书指示以 `git add -f` 纳入）

## 疑虑 / 后续

- compare 路径（MAE 实比较）在本机环境性 DEVICE_LOST 下未被 test_vulkan 端到端执行，等价性靠「旧代码逐字搬迁 + 单元测试 + 降采样数值等价证明」支撑；建议在 CI 健康 lane（或本机环境修复后）复核一次 GOLDEN MAE 日志数值。
- `rhi_oracle_capture_presented` 当前无调用方（后续 Task 的底座），仅有 headless 链接保障其可链接性。
