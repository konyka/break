# Metal / D3D12 特性矩阵（规划态）

两个后端的公开入口均为现有 `rhi_*` 符号集（`engine/src/rhi/rhi.h`）；本表跟踪各特性面在后端内的落地状态。状态枚举：NONE（无代码）/ PLANNED（已排期）/ HEADLESS / NATIVE_SURFACE / GPU_RUNTIME / BENCHMARK_COMPARABLE。

| 特性面 | Metal（计划 C） | D3D12（计划 D） |
|---|---|---|
| 设备创建 / 销毁 | PLANNED（MTLDevice/MTLCommandQueue） | HEADLESS（`rhi_d3d12.c/h` gate 契约） |
| Surface / swapchain | PLANNED（`platform_surface_native()` 返回 CAMetalLayer） | PLANNED（HWND → DXGI swapchain） |
| Render pass / pipeline contract | PLANNED（消费 `RHIPipelineDesc` capability contract 字段） | PLANNED |
| Push constants / 绑定模型 | PLANNED（`rhi_cmd_push_constants` → setBytes 映射） | PLANNED（root constants） |
| Compute / storage | PLANNED | PLANNED |
| 加速结构（BLAS/TLAS） | PLANNED（`rhi_acceleration_structure_get_vk_handle` 不适用；后端内转换，公开 ABI 不变） | PLANNED（同上） |
| Present damage / buffer age | PLANNED | PLANNED |
| 验证 gate | PLANNED（Metal validation layer） | PLANNED（DRED + debug layer） |
| Shader 路径 | MSL：`metal-shaderconverter` 或手写 MSL + `xcrun metal` → `.metallib`（构建期） | HLSL → DXIL：dxc（沿用 `test_d3d12_shader_compile_gate` 的 dxc 定位），SDK 版本锁定在计划 F |
| 当前证据等级 | NONE | HEADLESS（contract/gate only，未接入 `RHIBackend`） |

## 纪律

- 禁止用 MoltenVK 冒充原生 Metal 证据，禁止用 D3D11On12 / GL wrapper 冒充 D3D12（规格 §1.2）。
- 本表任何等级提升必须同步更新 `docs/rhi_backend_evidence.md` 并附收据。
