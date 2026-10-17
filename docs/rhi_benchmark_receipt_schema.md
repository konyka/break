# RHI Benchmark Receipt Schema

每次证据等级升级到 `GPU_RUNTIME` 或 `BENCHMARK_COMPARABLE` 必须附一份符合本 schema 的 JSON 收据（benchmark 类）；其他等级升级收据至少包含相同的环境字段（**metrics 可整体省略**——生成器 `engine/tools/make_evidence_receipt.cmake` 仅在 benchmark 类或显式给出全部四项时写入）。字段级校验脚本（`engine/tests/test_evidence_receipt_schema.cmake`，计划 F task 7 起）入 CI：除下表必填字段外，`build_config/os_version/gpu/driver_version/cpu/ram` 亦须非空（生成器对未提供值落 `unknown`）。lane 不可得/失败时收据降级 `UNAVAILABLE`（CI 各 lane 的收据步以 `job.status` 与 ctest `***Skipped` 计数判定，2026-10-17 规范化）。

## 字段定义

| 字段 | 类型 | 必填 | 说明 |
|---|---|---|---|
| `schema_version` | integer | 是 | 当前固定为 1 |
| `timestamp` | string | 是 | ISO 8601 UTC（如 `2026-10-14T12:00:00Z`） |
| `platform` | string | 是 | `linux-x11` / `linux-wayland` / `windows` / `macos` / `ios` / `android` / `ohos`；兼容验证收据允许 `proton`（steamrt 容器证据，不计 Windows D3D12 台账） |
| `os_version` | string | 是 | 操作系统与版本（如 `Ubuntu 24.04`） |
| `backend` | string | 是 | `opengl` / `vulkan` / `metal` / `d3d12` / `vulkan-moltenvk` |
| `gpu` | string | 是 | GPU 型号；软渲染必须注明（如 `llvmpipe (LLVM 17.0.6, 256 bits)`） |
| `driver_version` | string | 是 | 驱动版本（如 `Mesa 24.0.9`） |
| `cpu` | string | 是 | CPU 描述（如 `8 × x86_64`） |
| `ram` | string | 是 | 内存（如 `16 GiB`） |
| `build_commit` | string | 是 | 40 位 git commit hash |
| `build_config` | string | 是 | `Debug` / `Release` |
| `command` | string | 是 | 产生该收据的完整命令行 |
| `metrics` | object \| 省略 | benchmark 类必填 | `BENCHMARK_COMPARABLE` 必填且四项俱全；其他等级可整体省略，或显式四项俱全地附带实测（生成器拒绝部分提供） |
| `metrics.fps_avg` | number | benchmark 必填 | 平均 FPS |
| `metrics.fps_p1` | number | benchmark 必填 | 1% 低帧 FPS |
| `metrics.frame_ms_avg` | number | benchmark 必填 | 平均帧时长 ms |
| `metrics.frame_ms_p99` | number | benchmark 必填 | P99 帧时长 ms |
| `evidence_level` | string | 是 | `NONE` / `COMPILED` / `HEADLESS` / `NATIVE_SURFACE` / `GPU_RUNTIME` / `BENCHMARK_COMPARABLE` / `UNAVAILABLE`（lane 不可得或失败时的诚实降级值） |
| `runner` | string | 是 | 运行器标识（如 `github-actions/ubuntu-latest (job: vk)` 或本机描述） |

## 示例收据

```json
{
  "schema_version": 1,
  "timestamp": "2026-10-14T12:00:00Z",
  "platform": "linux-x11",
  "os_version": "Ubuntu 24.04",
  "backend": "vulkan",
  "gpu": "llvmpipe (LLVM 17.0.6, 256 bits)",
  "driver_version": "Mesa 24.0.9",
  "cpu": "8 × x86_64",
  "ram": "16 GiB",
  "build_commit": "0123456789abcdef0123456789abcdef01234567",
  "build_config": "Debug",
  "command": "ctest --test-dir build -R '^test_vulkan$' --output-on-failure",
  "metrics": {
    "fps_avg": 61.2,
    "fps_p1": 54.8,
    "frame_ms_avg": 16.34,
    "frame_ms_p99": 22.10
  },
  "evidence_level": "GPU_RUNTIME",
  "runner": "github-actions/ubuntu-latest (job: vk)"
}
```

## 已知对齐项（计划 F 字段级校验落地前必须处理）

以下 receipt ↔ schema 偏差经 Task 7 评审确认，均为计划 F 的设计决策项：

1. `driver_version`：bench 输出 RHI 层 `u32` 原始编码值（如 NVIDIA `"2588573696"`），schema 期望人读字符串——正确修法是设计决策（vendor 解码 vs schema 放宽），归计划 F；
2. `platform`：无 `linux-x11`/`linux-wayland` 细分（x11/wayland 是运行期属性，bench 只有编译期宏）——归计划 F；
3. `build_config`：CI 传 `RelWithDebInfo` 超出 schema 枚举（Debug/Release）——归计划 F；
4. `command`：bench 硬编码 `"rhi_swapchain_bench"` 非完整命令行——归计划 F；
5. `BENCHMARK_COMPARABLE` 在 CI 的产出方式（task 7 修复轮 I1）：bench 可执行自产收据硬编码 `GPU_RUNTIME`（`rhi_swapchain_bench.c`），真机 `lane-benchmark-steam-deck-vk` 在 bench 成功后用 `make_evidence_receipt.cmake` 按同一实测重建台账收据（收割 bench metrics + `BENCHMARK_COMPARABLE`），bench 原始收据随同 artifact 上传留档；
6. 平台扩展值 `proton`、可省略 metrics、`UNAVAILABLE` 等级已随 task 7 修复轮（I3）写入上表规范。
