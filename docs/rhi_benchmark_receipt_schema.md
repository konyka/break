# RHI Benchmark Receipt Schema

每次证据等级升级到 `GPU_RUNTIME` 或 `BENCHMARK_COMPARABLE` 必须附一份符合本 schema 的 JSON 收据（benchmark 类）；其他等级升级收据至少包含相同的环境字段（metrics 可为 null）。字段级校验脚本随计划 F 入 CI。

## 字段定义

| 字段 | 类型 | 必填 | 说明 |
|---|---|---|---|
| `schema_version` | integer | 是 | 当前固定为 1 |
| `timestamp` | string | 是 | ISO 8601 UTC（如 `2026-10-14T12:00:00Z`） |
| `platform` | string | 是 | `linux-x11` / `linux-wayland` / `windows` / `macos` / `ios` / `android` / `ohos` |
| `os_version` | string | 是 | 操作系统与版本（如 `Ubuntu 24.04`） |
| `backend` | string | 是 | `opengl` / `vulkan` / `metal` / `d3d12` / `vulkan-moltenvk` |
| `gpu` | string | 是 | GPU 型号；软渲染必须注明（如 `llvmpipe (LLVM 17.0.6, 256 bits)`） |
| `driver_version` | string | 是 | 驱动版本（如 `Mesa 24.0.9`） |
| `cpu` | string | 是 | CPU 描述（如 `8 × x86_64`） |
| `ram` | string | 是 | 内存（如 `16 GiB`） |
| `build_commit` | string | 是 | 40 位 git commit hash |
| `build_config` | string | 是 | `Debug` / `Release` |
| `command` | string | 是 | 产生该收据的完整命令行 |
| `metrics` | object \| null | 是 | benchmark 必填；字段见下 |
| `metrics.fps_avg` | number | benchmark 必填 | 平均 FPS |
| `metrics.fps_p1` | number | benchmark 必填 | 1% 低帧 FPS |
| `metrics.frame_ms_avg` | number | benchmark 必填 | 平均帧时长 ms |
| `metrics.frame_ms_p99` | number | benchmark 必填 | P99 帧时长 ms |
| `evidence_level` | string | 是 | `NONE` / `COMPILED` / `HEADLESS` / `NATIVE_SURFACE` / `GPU_RUNTIME` / `BENCHMARK_COMPARABLE` |
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
