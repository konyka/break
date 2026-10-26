# RHI 后端证据台账

- 冻结日期：2026-10-14（基线）；上位规格：`docs/superpowers/specs/2026-10-14-multi-backend-rhi-design.md` §2
- 证据等级（严格递增，升级必须有对应收据）：`NONE → COMPILED → HEADLESS → NATIVE_SURFACE → GPU_RUNTIME → BENCHMARK_COMPARABLE`
- 收据字段（每次等级变更必填，benchmark 类收据遵循 `docs/rhi_benchmark_receipt_schema.md`）：日期 / 机器 / GPU / 驱动版本 / 执行命令 / 结果（CI run URL 或本地 run 标识）
- 纪律：编译成功 ≠ GPU-runtime；模拟器证据只计入 COMPILED/HEADLESS；MoltenVK 证据不计入原生 Metal；Proton 只作兼容参考；headless stub（`engine_rhi_headless`）永不构成 GPU 证据。

## 基线矩阵（2026-10-14 冻结）

| 平台 × 后端 | 当前等级 | 依据 | 收据 |
|---|---|---|---|
| Linux X11 × OpenGL（兼容期，deprecated，计划 v2.0.0 移除——Task 6 闸门 BLOCKED） | GPU_RUNTIME | CI `lane-gpu-runtime-linux-gl`（DEPRECATED lane，Xvfb 软渲染 GL；原 `gl` job） | CI run：https://github.com/konyka/break/actions/runs/38990768014 （@3c92a06b，2026-10-17，`evidence-receipt-gpu-runtime-linux-gl` artifact；软渲染收据如实标注） |
| Linux X11 × Vulkan | GPU_RUNTIME（lavapipe/llvmpipe，软渲染） | CI `lane-gpu-runtime-linux-vk`（原 `vk`+`linux-graphics-smoke` 合并）+ `lane-validation-linux-vk` + `lane-benchmark-linux-vk`（lavapipe 收据注明软渲染） | CI run：https://github.com/konyka/break/actions/runs/38990768014 （@3c92a06b，2026-10-17，`evidence-receipt-gpu-runtime-linux` / `-validation-linux` / `-benchmark-linux-vk` artifacts）；历史绿 run 38979612930（@89f2d444，`vk`/`linux-graphics-smoke`） |
| Linux Wayland × GL/VK | NATIVE_SURFACE | CI `wayland-gl`（兼容期 DEPRECATED） / `lane-native-surface-wayland`（原 `wayland-vk`；weston headless） | CI run：https://github.com/konyka/break/actions/runs/38990768014 （@3c92a06b，2026-10-17，`evidence-receipt-native-surface-wayland{,-gl}` artifacts）；历史绿 run 38979612930（@89f2d444） |
| Windows × Vulkan | GPU_RUNTIME（本机 + CI win32 runtime trio） | 本机 `build-win-vk/`、CI `lane-headless-windows-clang`（原 `windows-clang`；win32 runtime trio 另由 `lane-native-surface-win32` 出证） | 本机：`cmake --build build-win-vk && ctest --test-dir build-win-vk -LE "graphics|fuzz"` 全绿（2026-10-14，Task 1 记录）；CI：绿 run https://github.com/konyka/break/actions/runs/38990768014 （@3c92a06b，2026-10-17，`evidence-receipt-headless-windows-clang` / `-native-surface-win32` artifacts；pinned Vulkan SDK 1.4.321.0）；历史绿 run 38979612930（@89f2d444） |
| Windows × D3D12 | BENCHMARK_COMPARABLE（本机，真 GPU 全栈：设备/swapchain/资源/PSO/DXIL/DXR/debug 工具链 + benchmark 收据：d3d12 fps_avg = 同机 Vulkan 基线 122% ≥ 90% 阈值） | `engine/src/rhi/rhi_d3d12.c/h`：真实设备（计划 D Task 3）+ flip-model swapchain/acquire/submit/present/resize（Task 4）+ 资源/PSO/indirect（Task 5）+ HLSL→DXIL shader 路径（Task 6）+ DXR BLAS/TLAS fail-closed（Task 7）+ debug layer/GBV/DRED（Task 8） | 本机：NVIDIA GeForce RTX 4060 Laptop GPU（驱动 32.0.16.1742，Agility SDK 1.616.0），2026-10-15：`ctest --test-dir build-d3d12-debug -L graphics -R test_d3d12` 6/6 绿（含 WARP floor，gpu=WARP 标注）；全量 `ctest --test-dir build-d3d12-debug` 165/171（失败仅已知环境性/未构建项，与 D3D12 无关，见下方计划 D 收据追加）；CI：windows-d3d12 lane 绿 run https://github.com/konyka/break/actions/runs/38703749329 （@65d01ec，WARP floor），ci.yml 全 lane 绿 run https://github.com/konyka/break/actions/runs/38703749404；Task 7 六 lane 后全绿 run https://github.com/konyka/break/actions/runs/38990768014 （15 个 evidence-receipt artifact；hosted d3d12 由常开孪生 job 出 UNAVAILABLE 收据，真机 lane `lane-gpu-runtime-windows-d3d12` 待 `ENABLE_GPU_LANES`） ；benchmark（2026-10-17）：`docs/receipts/rhi_receipt_windows_d3d12_planf.json` + 基线 `docs/receipts/rhi_receipt_windows_vulkan_planf.json`（rhi_swapchain_bench 同场景 640×480 600 帧 vsync off，fps_avg 2174.19 vs 1779.58，ratio 1.222 ≥ 0.90；判定细节见尾部「收据追加（计划 F 前置：D3D12 benchmark）」） |
| macOS × Vulkan(MoltenVK) | GPU_RUNTIME | CI `lane-native-surface-cocoa`（原 `macos-vulkan`；133/133 CTest 基线 2026-10-13） | CI run：绿 run https://github.com/konyka/break/actions/runs/38990768014 （@3c92a06b，2026-10-17，`evidence-receipt-native-surface-cocoa` artifact）；历史绿 run 38979612930（@89f2d444；brew 补 spirv-cross 后 headless 套件全绿） |
| macOS/iOS × 原生 Metal | BENCHMARK_COMPARABLE（macOS：metal fps_avg = 同机 MoltenVK 基线 101% ≥ 90% 阈值）；iOS 保持 COMPILED（模拟器 compile only，无真机收据） | `engine/src/rhi/rhi_metal.m`：计划 C Task 1-9（设备/能力、drawable 生命周期、资源族、pipeline/FBO/MRT/shadow 契约、compute/blit/screenshot/indirect/timer）+ Task 15 修复轮（spvBufferSizeConstants 喂表、UBO 逐绘制重放、postfx 纹理绑定、pixelFormat 变体、screenshot 行序） | 见下方「收据追加（计划 C：Metal）」与「收据追加（计划 C Task 15）」 |
| Android × Vulkan | COMPILED（host-injected ANativeWindow） | `engine/src/rhi/rhi_vk.c:1482-1700` | 源码审查记录（2026-10-14 冻结） |
| iOS × Vulkan(MoltenVK) | COMPILED（host-injected CAMetalLayer） | `engine/src/platform/platform_compat.h:86-95` | 源码审查记录（2026-10-14 冻结） |
| OHOS | NONE（UNAVAILABLE，fail-closed） | `engine/src/platform/platform_compat.h:111-120`；`engine/CMakeLists.txt:1073-1075` FATAL_ERROR | 契约测试 `test_platform_compat_harmonyos` |
| Proton (Wine/vkd3d) × D3D12 | compat-verified（兼容验证，不计入 Windows 原生证据） | lane: proton-d3d12（Wine/vkd3d-proton）+ CI `lane-proton`（steamrt sniper 钉 digest 容器构建，周跑，`evidence-receipt-proton`） | lane 实跑绿 run https://github.com/konyka/break/actions/runs/38703986572 （@65d01ec；契约退出码记录于 lane 日志与 CI artifact proton-d3d12-receipt） |

## 变更规则

1. 等级升级必须在本表对应行更新「当前等级」并追加收据（日期/机器/GPU/驱动/命令/结果）。
2. 已知异常（如 NVIDIA 616.56 混合 GPU 的 `VK_ERROR_DEVICE_LOST` 与 Hi-Z {1,1}）只登记在规格 §7，不作为本表等级依据。
3. 本表由 `test_rhi_evidence_register`（`engine/tests/test_rhi_evidence_register.cmake`）做存在性与行完整性 gate。

## 本机冻结证据检查（opt-in）

`test_rhi_evidence_register` 对本机冻结证据文件（`<repo>/.scratch-vkprobe/` 目录与
`<repo>/engine/profile_trace.json`）的存在性检查**默认关闭**：fresh clone 与 CI 不携带这些
冻结产物，行完整性与证据等级 token 检查（可移植部分）始终执行。

在持有冻结证据的机器上启用方式（二选一）：

1. 通过 CMake cache 变量透传（推荐）：configure 时加
   `-DRHI_EVIDENCE_REQUIRE_LOCAL_FROZEN=ON`。`engine/CMakeLists.txt` 的测试注册区定义了
   `option(RHI_EVIDENCE_REQUIRE_LOCAL_FROZEN "..." OFF)` 并在
   `test_rhi_evidence_register` 注册行透传
   `-DRHI_EVIDENCE_REQUIRE_LOCAL_FROZEN=${RHI_EVIDENCE_REQUIRE_LOCAL_FROZEN}`，
   之后正常 `ctest` 即可。
2. 直接脚本调用：`ctest` 前手动运行
   `cmake -DREPO_ROOT=<repo> -DEVIDENCE_DOC=<repo>/docs/rhi_backend_evidence.md -DRHI_EVIDENCE_REQUIRE_LOCAL_FROZEN=ON -P engine/tests/test_rhi_evidence_register.cmake`。

## 收据追加（计划 B：WSI / Vulkan-first，2026-10-15）

| 日期 | 机器 | GPU / 驱动 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-15 | 本机（Windows） | NVIDIA GeForce RTX 4060 Laptop / driver_version=2588573696（NVIDIA 解码 617.42） | `ctest --test-dir build-vk -R 'rhi_fault\|vk_alloc_fault\|isolation_gates\|vk_probe\|vk_surface_abi\|wsi\|platform_size' --output-on-failure` | 16/16 PASS；含 graphics 标签的 `test_rhi_vk_alloc_fault`（真 GPU 分配失败注入）与 `test_rhi_fault_injection`（out-of-date/device-lost/surface-loss 注入）→ Windows × Vulkan 维持 GPU_RUNTIME |
| 2026-10-15 | 本机（Windows） | 同上 | `rhi_swapchain_bench` → `build-vk/rhi_receipt_local.json`（Task 7 产出）；`cmake -DRECEIPT=build-vk/rhi_receipt_local.json -P engine/tests/test_rhi_benchmark_receipt_validate.cmake` | 收据校验通过：fps_avg=2120.57 / fps_p1=622.21 / frame_ms_avg=0.4716 / frame_ms_p99=1.6072，evidence_level=GPU_RUNTIME，runner=local |
| 2026-10-15 | 本机（Windows） | 同上 | `ctest --test-dir build-vk -R '^test_vulkan$' --output-on-failure` | init 日志行有效（`Vulkan GPU:`、`VK: swapchain present mode=IMMEDIATE images=3 vsync=off`；一次性探针实测 feature_bits=0x7、dynamic_rendering=1、synchronization2=1、device_type=2(discrete)、surface=B8G8R8A8_SRGB，探针已还原不入库）；graphics 段失败为本机已知环境性失败（混合 GPU 驱动，规格 §7 风险登记），不构成新收据、也不降级既有等级 |
| 2026-10-15 | — | — | `steam-deck-vulkan-benchmark` lane（`.github/workflows/ci.yml`） | 仓库变量 `ENABLE_GPU_LANES` 未开启（self-hosted runner 未上线）→ lane 存在但无运行收据；Linux X11/Wayland 的 WSI 接线仅有 token 级契约证据（`test_platform_wsi_wiring_contract` / `test_platform_wsi_lifecycle_*`，本机无 Linux 编译环境），各等级不变 |

## 收据追加（计划 D：D3D12，2026-10-15）

| 日期 | 机器 | GPU / 驱动 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-15 | 本机（Windows） | NVIDIA GeForce RTX 4060 Laptop GPU / 驱动 32.0.16.1742（Agility SDK 1.616.0，Windows SDK 10.0.26100.0） | `ctest --test-dir build-d3d12-debug -L graphics -R test_d3d12 --output-on-failure` | 6/6 PASS：device/swapchain/pipeline/shader/dxr 契约 + `test_d3d12_warp_runtime`（`gpu=WARP`，证据下限标注）——真 GPU 全栈帧生命周期 → Windows × D3D12 维持 GPU_RUNTIME；BENCHMARK_COMPARABLE 不可标（无 benchmark receipt schema 收据） |
| 2026-10-15 | 本机（Windows） | 同上 | `ctest --test-dir build-d3d12-debug --output-on-failure`（全量 171 项） | 165/171 PASS；失败仅 `test_vulkan`（本机已知环境性失败，规格 §7 登记，与 D3D12 无关）与 `fuzz_*_smoke`×5 "Not Run"（EXCLUDE_FROM_ALL 目标本树未构建，先于计划 D 存在）；`rhi_swapchain_bench` Skipped（既存） |

## 收据追加（计划 C：原生 Metal，2026-10-15）

| 日期 | 机器 | GPU / 驱动 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-15 | 远程 Mac mini（LAN） | Apple M2（G14）/ macOS 26.7.1（25G241），Xcode SDK 26.5，Metal 4 运行时 | `ctest --test-dir ~/break/build-metal -R test_rhi_metal --output-on-failure`（@4d087f36 及修复轮） | 5/5 PASS：`test_rhi_metal_ownership` / `format_mapping` / `device_contract` / `frame_lifecycle` / `resources`（31/31 用例：buffer/texture/sampler/cubemap R587-R602/R624 字节契约、pipeline 字段映射、FBO/MRT/shadow R616-R619、compute dispatch、fill/update/copy blit、screenshot、indirect draw、gpu timer 降级）→ macOS × 原生 Metal 升 GPU_RUNTIME；iOS 未覆盖（无设备） |
| 2026-10-15 | 同上 | 同上 | `cd ~/break/build-metal && caffeinate -i ctest`（全量 165 项，@4d087f36） | 164/165 PASS；唯一失败 `test_vulkan` 为前置基线（干净 a3f2dc94 重建后同挂，test_vulkan.c:432 device create，metal 配置既存问题，与计划 C 无关） |
| 2026-10-15 | 同上 | 同上 | GPU timer 能力探针（独立小程序，`supportsCounterSampling:` 五点查询 + 实际 `sampleCountersInBuffer:` 编码） | stage=1 其余=0，但三种 encoder 实际采样均硬断言 abort（Metal 4 运行时禁用 legacy counter sampling，查询谎报）→ timer 按需求书降级条款处理（macOS 26+ 静态门控，warn-once 恒 0），不构成计时证据 |

## 收据追加（计划 C Task 14：CI lanes，2026-10-16）

| 平台 × 后端 | 等级 | 依据 |
|---|---|---|
| macOS × 原生 Metal | COMPILED（CI lane 首跑） | CI `macos-metal` lane（macos-14，brew shaderc+spirv-cross，metallib 产物断言 + headless/契约测试）run 链接见下；**与既有 M2 GPU_RUNTIME 收据并列**（证据来源机器不同：M2 真机为 GPU_RUNTIME，macos-14 runner 仅编译+契约面） |
| iOS × 原生 Metal | COMPILED（**模拟器证据 = compile only，不构成 GPU-runtime 证据**） | CI `ios-metal-build` lane（Xcode -G + iOS Simulator destination build-only + 产物断言 `test -s` metallib×2 / `test -d` .app，零匹配即失败）；模拟器无可信 GPU-runtime 通道；**lifecycle（simctl boot/install/launch harness）缺口归 Task 15** |

| 日期 | 机器 | GPU / 驱动 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-16 | GitHub macos-14 runner | （runner GPU 未保证；契约/headless 面） | CI `macos-metal` lane（[run 38863391632](https://github.com/konyka/break/actions/runs/38863391632)，@40e11bab） | **SUCCESS**：metallib 产物断言过、headless+契约 ctest（-LE "graphics\|fuzz"）全绿；首跑红→绿迭代 3 轮（run 38855415643 ctest exit 8、38861481273 同），根因 `test_rhi_backend_selection` 嵌套 auto/opengl configure 在无 Vulkan 主机遇 find_package(Vulkan REQUIRED)，以存在性占位 cache 变量修复（契约对象是 selector 解析而非 Vulkan 发现） |
| 2026-10-16 | GitHub macos-14 runner | 不适用（模拟器 compile only） | CI `ios-metal-build` lane（[run 38863391632](https://github.com/konyka/break/actions/runs/38863391632)，@40e11bab；首个绿为 @87fead51 的 [run 38861481273](https://github.com/konyka/break/actions/runs/38861481273)） | **SUCCESS**：Xcode -G iOS Simulator destination 全量构建过；iOS 工具分离处置：manifest 生成器宿主编译 + iphoneos SDK（CMakeLists M6 注释）。注：首绿时 Verify 步骤为 `find \| head` 弱断言，评审 I-1 后改为 `test -s`/`test -d` 硬断言（见后续 run） |

## 收据追加（计划 C Task 15：macOS 真机全绿 + benchmark，2026-10-16）

| 日期 | 机器 | GPU / 驱动 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-16 | 远程 Mac mini（LAN，M2） | Apple M2（G14）/ macOS 26.7.1（25G241），Xcode SDK 26.5，Metal 4 运行时 | `caffeinate -i ctest --test-dir build-rel-metal --parallel 4 --output-on-failure`（Release，metal 配置，@bc1e5481） | 162/168 PASS（96%）：全部 Metal 用例绿（含 graphics 标签 GPU 用例、`test_rhi_metal_resources` 43/43、consumer smoke `engine_demo --frames 3` 真窗口绿）；失败仅 `test_vulkan`（前置基线，test_vulkan.c:432 device create，台账计划 C 段已登记）+ `fuzz_*_smoke`×5 "Not Run"（EXCLUDE_FROM_ALL 未构建，先于本计划存在）；`rhi_swapchain_bench` Skipped（既存） |
| 2026-10-16 | 同上 | 同上 + MoltenVK（brew，Vulkan API 1.4.0）/ vulkan-loader 1.4.363 | `caffeinate -i ctest --test-dir build-rel-vk --parallel 4 --output-on-failure`（Release，vulkan 配置，@bc1e5481） | 161/167 PASS（96%）：MoltenVK 基线不回归；`rhi_swapchain_bench` PASS（5.65s，产出 build-rel-vk/rhi_receipt_local.json：fps_avg=119.28，synthetic swapchain harness）；失败仅 `test_vulkan` Timeout（前置基线：pristine origin/master 同构建 90s+ 不退出，已实证与本计划改动无关）+ `fuzz_*_smoke`×5 "Not Run" |
| 2026-10-16 | 同上 | 同上（metal） | `BREAK_BENCH_STATS=600 caffeinate -i ./build-rel-metal/engine_demo --frames 600`（vsync off，1280x720，默认场景） | 收据 `docs/receipts/rhi_receipt_macos_metal_task15.json`（`test_rhi_benchmark_receipt_validate.cmake` 通过）：fps_avg=50.05 / fps_p1=41.96 / frame_ms_avg=19.981 / frame_ms_p99=23.833 |
| 2026-10-16 | 同上 | 同上（MoltenVK 基线） | `BREAK_BENCH_STATS=600 caffeinate -i ./build-rel-vk/engine_demo --frames 600`（同场景同帧数） | 收据 `docs/receipts/rhi_receipt_macos_moltenvk_task15.json`（校验通过）：fps_avg=49.57 / fps_p1=41.66 / frame_ms_avg=20.172 / frame_ms_p99=24.006 |
| 2026-10-16 | 同上 | — | 阈值判定 | metal fps_avg / MoltenVK fps_avg = 50.05/49.57 = **1.010 ≥ 0.90** → macOS × 原生 Metal 升 **BENCHMARK_COMPARABLE**（阈值：不低于同机 MoltenVK 基线 90%，需求书 Task 15 Step 3）；iOS 无真机，保持 COMPILED |
| 2026-10-16 | GitHub macos-14 runner | （契约/headless 面） | CI `macos-metal` lane（[run 38863992025](https://github.com/konyka/break/actions/runs/38863992025)，@f58546f6；修复轮后 [run 38866904726](https://github.com/konyka/break/actions/runs/38866904726)，@39431d91） | SUCCESS：编译 + metallib 断言 + headless/契约 ctest 全绿（与本机 GPU_RUNTIME/BENCHMARK_COMPARABLE 收据并列；runner 不构成 GPU-runtime 证据） |
| 2026-10-16 | 同上（y-flip 取证） | 同上 | `BREAK_SCREENSHOT=5 ./build-rel-{metal,vk}/engine_demo --frames 8` → BMP 逐像素比对 + 目视 | Metal present 朝向正确（GL 约定：NDC +Y 朝上、正视口高度；VK 走负视口高度故其 readback 天然 bottom-up）；发现并修复 `rhi_screenshot` 行序违契（Metal blit 为 top-down，RHI 契约为 GL bottom-up——main.c BMP 写出依赖该契约），修复后 Metal 截图与 MoltenVK 截图朝向一致（调试文本正立可读） |

## 收据追加（计划 E Task 3：buffer 契约 C-BUF-1..4，2026-10-16）

契约内容（规范文本固化于 `engine/src/rhi/rhi.h`，双后端测试钉死于 test_vulkan 的 BUFFER STAGING CONTRACT / CMD UPDATE BUFFER ORDERING 两个 phase）：C-BUF-1 initial_data 字节精确回读（HOST_VISIBLE 与 DEVICE_LOCAL+staging 同语义）；C-BUF-2 `rhi_buffer_update_region` 只动 `[off,off+size)`、offset/size 无需调用方对齐、越界钳制；C-BUF-3 同 CB 内 `rhi_cmd_update_buffer` 对后续 dispatch/draw 有序；C-BUF-4 map 写入 unmap 后对 device 与 `rhi_buffer_read` 可见。

> 注：本台账引用的 `.superpowers/sdd/.../evidence/*.txt` 日志文件为执行机本地路径（`.git/info/exclude` 排除），原始日志未随库提交——以 git 历史 receipts/docs 为准。

| 日期 | 机器 | GPU / 驱动 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-16 | 本机（Windows） | NVIDIA GeForce RTX 4060 Laptop / api=1.4.351 driver=0x9a4a8000 | `ctest --test-dir build-vk -R '^test_vulkan$\|test_rhi_capabilities' --output-on-failure`（日志 `.superpowers/sdd/2026-10-14-rhi-plan-e-renderer-abi/evidence/task3_post_test_vulkan.txt`） | VK 本机 LIVE（phase 位于 run order 中 SCENE RESTORE 之后、历史 device-lost 窗口 TEST 7b 之前）：C-BUF-1/2/4 与 C-BUF-3 两 phase 均 `PASSED ✓`；`test_rhi_capabilities` 56/56（含新增 `buffer_region_rejects_overflow_and_null`）。附带发现：修复 C-BUF-3 暴露的 `rhi_cmd_bind_storage_buffer` R90-1 update-after-bind 违规（重绑累积集）后，本机 3/3 次 run 不再于 TEST 7b 触发历史性 `VK_ERROR_DEVICE_LOST`（回滚对照：无修复必复现）——规格 §7 的「环境性」lost 实为该潜在违规在此驱动消费模型下的表现；GOLDEN×2 仍 DRIFT（本机史上首次活设备到达 golden，金样 2026-06 提交，golden 权威在 CI）；UNIFIED GPU CULL 偶发 Hi-Z {0,0}（已知 §7 异常，3/4 run 绿） |
| 待 CI | GitHub Actions | CI `gl` lane（Xvfb 真 GL） | 同 repo push 后 gl lane `test_vulkan` | GL lane 验证项（本机无可运行 GL，不伪造）：共享双后端 phase + `rhi_gl.c` map 补 `GL_MAP_WRITE_BIT`（C-BUF-4 规范符合性修复，仅扩权限不改内容语义） |


## 收据追加（计划 E Task 4：texture/sampler/format 契约 C-TEX-1..3，2026-10-16）

契约内容（规范文本固化于 `engine/src/rhi/rhi.h` 的 `rhi_texture_create`/`rhi_texture_read_pixels`/`rhi_texture_upload_mip`/`rhi_sampler_create` 注释，双后端测试钉死于 test_vulkan 的 TEXTURE NATIVE-BYTE ROUNDTRIP（扩展为全格式矩阵）/ MIP UPLOAD ORACLE / SAMPLER FILTER/WRAP CONTRACT 三个 phase，位于共享 pre-split 路径 f16 roundtrip 之后）：C-TEX-1 7 枚举 `RHIFormat` 矩阵闭合——6 个实格式 .data 上传→`rhi_texture_read_pixels` 回读原生字节（新增 RGBA8 非平凡字节序 {10,20,30,40} 同序返回缺口 phase），`RHI_FORMAT_UNDEFINED` 双后端拒绝创建（共享 `rhi_texture_desc_validate`）；C-TEX-2 `rhi_texture_upload_mip` 写入的 mip2 经 `rhi_cmd_bind_texture_mip`（单 mip 视图）+ compute `textureLod(...,0.0)` 采样 == 上传字节（UNORM ±1）；C-TEX-3 2x2 四色互异纹理 + 边缘外推 UV（角像素中心 UV ∈ {-0.0625,1.0625}）渲染进 4x4 RGBA8 offscreen FBO：NEAREST+CLAMP_TO_EDGE 角像素 == 边缘纹素、REPEAT 对照组 == 环绕纹素（±1；R442 NDC→row 约定使两后端期望一致）。

| 日期 | 机器 | GPU / 驱动 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-16 | 本机（Windows） | NVIDIA GeForce RTX 4060 Laptop / api=1.4.351 driver=0x9a4a8000 | `ctest --test-dir build-vk -R '^test_vulkan$' --output-on-failure`（日志 `.superpowers/sdd/2026-10-14-rhi-plan-e-renderer-abi/evidence/task4_post_test_vulkan.txt`） | VK 本机 LIVE：C-TEX-1（含 RGBA8/UNDEFINED 两缺口 phase）/C-TEX-2/C-TEX-3 全 `PASSED ✓`，VALIDATION GATE 0 messages，**零后端修复**（契约钉死收敛；VK `rhi_texture_upload_mip` 的 mip extent/对齐与 GL `glTexSubImage2D` level 目标两处已知风险点经 oracle 验证本就正确，仅 GL 侧留 CI 复核）；RESULT 签名与 Task 3 基线完全一致（唯一差异 = 新增两行 PASS；GOLDEN×2 MAE=28.75/13.54 逐位不变，前置本机漂移，权威在 CI）；已知 §7 Hi-Z {0,0} 偶发今日率升高（含本 diff 6/9 vs 无 diff 对照 3/5，A/B 无显著差 → 机器/驱动当日状态，非本 diff 回归；失败签名与既往相同，复跑后绿） |
| 待 CI | GitHub Actions | CI `gl` lane（Xvfb 真 GL） | 同 repo push 后 gl lane `test_vulkan` | GL lane 验证项（本机无可运行 GL，不伪造）：三 phase 均为双后端共享代码路径（仅 shader 源 `#ifdef ENGINE_VULKAN` set= 差异，照 hi_z_generate.comp 头部约定）；重点复核 GL `rhi_texture_upload_mip` 的 `glTexSubImage2D` level 目标与单 mip `glTextureView` 采样路径（本机仅代码审查：level/extent/size 校验与 `GL_TEXTURE_2D` level 目标正确） |


## 风险登记（计划 E Task 6：Hi-Z，2026-10-16）

- Hi-Z {1,1} / VK_ERROR_DEVICE_LOST（NVIDIA 616.56 混合 GPU）——未在健康设备复现，按 spec §7 不作为源码修复依据；`TV_ONLY_PSHADOW`/`TV_ONLY_GBUFFER` 隔离 gate 保留。

## 收据追加（计划 E：renderer/shader ABI 迁移完成度，2026-10-16）

上位计划：`docs/superpowers/plans/2026-10-14-rhi-plan-e-renderer-abi.md`。范围：main.c / renderer / ui / myui 的编译期后端分支收敛到 capability contract；412 个 legacy uniform 逐名查询调用点全部迁移 `RHIPipelineBindings`（反射驱动）；VK 手写 push offset 表删除。本机验证 lane：VK = `build-vk`（NVIDIA RTX 4060 Laptop，api=1.4.351）+ GL = `build-gl`（WGL，`ENGINE_VULKAN=OFF`，Task 5b 起确认为本机可跑 lane）每批双跑；CI lanes（gl/vk/wayland/macos）收据待 push 后补记（小 commit 追加，见 DoD 第 7 项）。

### 各 Task 收据

| Task | Commits | 验证 | Lane | 结果 |
|---|---|---|---|---|
| 1 rhi_oracle 抽取 | 9407c222 / 97b61a07 / 59c62a0d | RED/GREEN（断言注入失败即红）；golden-log parity；基线捕获 | VK | oracle 与 test_vulkan 内联实现 golden 日志逐行 parity；本机基线 MAE 28.75/13.54（金样 2026-06 提交，golden 权威在 CI） |
| 2 capability contract：frame/present/resize + main.c 分支替换 | b5034d74 / 49084768 | 零警告构建（`-Werror`）；`ctest -R test_vulkan` 签名比对 | VK | 绿；**计划修订**：`rhi_device_create_compiled` 同时接收 window_native + surface_native（Wayland `wl_surface*` / `wl_egl_window*` 类型分离；VK←surface、GL←window），计划文件已附日期注记 |
| 3 buffer 契约 C-BUF-1..4 | f3159136 | `ctest -R '^test_vulkan$\|test_rhi_capabilities'` | VK（GL 待 CI） | 双 phase PASSED；capabilities 56/56；R90-1 update-after-bind 修复后本机 3/3 不再触发历史 §7 DEVICE_LOST（详见上文 Task 3 收据行） |
| 4 texture/mip/sampler 契约 C-TEX-1..3 | 0c0fd671 | `ctest -R '^test_vulkan$'` | VK（GL 待 CI） | 全 phase PASSED、VALIDATION GATE 0、零后端修复；签名与 Task 3 基线一致（详见上文 Task 4 收据行） |
| 5a std430 push 反射 | 4238f535 / f73fd27b | 反射×VK 表交叉对照 gate（graphics，54 文件） | 静态 gate | 生产 bug 修复：deferred 点光 far-plane 偏移 184→192（见下「生产 bug」#1） |
| 5b RHIPipelineBindings API | 023b7ef3 | legacy parity gate + golden | VK+GL | API 绿；本机 GL lane 就绪（goldens MAE=0.00）——「本机无 GL」前提自本 Task 修正 |
| 5c-1 批次 1-3：main.c(58) + test_vulkan(87) | 3d1efa57 / 3b66e588 / 20cc8c2f | 每批双 lane golden 签名 | VK+GL | VK 签名逐批稳定（MAE 28.75/13.54 不变）；GL goldens 0.00 |
| 5c-2a 批次 4-6：renderer(139) + .comp gate + 手写表删除 | 8360a236 / fe9965f0 / 3d395b95 / 74fdcf7b / 6aad11f6 | 每批双 lane；.comp 交叉对照 gate；particle alias 算术 pin | VK+GL | 评审捕获并修复 push.proj alias delta 64→0（见「生产 bug」#2）；VK 手写 push 表删除后签名不变 |
| 5c-2b 批次 7-9：renderer(128/24 文件) + 全库审计 | 1b550670 / 92d73a01 / 8a64ddf0 | 每批双 lane；engine-wide grep 审计 | VK+GL | legacy 查询调用点 = 0（残留仅声明/实现/注释，见下） |
| 6 pipeline/MRT/depth/shadow/Hi-Z 契约迁移（41 分支 / 28 .c + 2 .h） | 7b20e937 / 3b387e72 | 双 lane 签名（RESULT+VALIDATION GATE+VK VALIDATION） | VK+GL | 修复 skinned gbuffer 变体选择（`gbuffer_skinned_vk.frag`，VALIDATION GATE 2→0）；Hi-Z {1,1} 异常仅登记未改码（见上方风险登记） |
| 7 compute/indirect/HDR/RT/UI 收敛 + 4 处 RHI-ESCAPE fence | 8fff58d5 | 双 lane 签名 35/35 IDENTICAL | VK+GL | rt_trace 按 RAY_TRACING_PIPELINE\|ACCELERATION_STRUCTURE 门控（偏差已核准）；sl_dlss 非 VK 单位 fail-closed |
| 8 token 审计 gate | e37d9df1 | `ctest -R test_renderer_backend_token_gate`（RED 证明先行）+ 全量矩阵 | VK+GL+MSVC(d3d12)+headless | gate 绿（5 白名单命中）；矩阵 VK 170/172、GL 168/169（均仅登记的环境性失败）、headless 18/18×2、MSVC headless 18/18（engine_demo 被先在的 myui_core C4090 阻塞，非本计划引入） |
| 9 文档与 push | （本 commit） | 全绿复核：`ctest --test-dir build-vk --output-on-failure` + `-R '^test_vulkan$'`（签名纪律 RESULT+VALIDATION GATE+VK VALIDATION） | VK | 全量 170/172（= Task 8 矩阵：golden 漂移基线 + OpenClipboard，均登记）；test_vulkan 35 行签名 vs Task 8 参考仅 1 行差 = UNIFIED GPU CULL（`Hi-Z vis flags {0,0}, want {1,0}`——注册 §7 环境性偶发，当日 2/2，Task 8 后无源码变更）；goldens MAE 28.75/13.54 逐位不变；VALIDATION GATE 0；push 首次被远端分叉拒绝后经集成轮 merge `86d159b8` 补推（见 DoD 第 7 项） |

### Token 审计终态

`engine/src/main.c`、`engine/src/renderer/`、`engine/src/ui/`、`engine/src/myui/`（含 myr）中 `ENGINE_VULKAN` / `ENGINE_RHI_BACKEND_*` 命中 = **5 处白名单 RHI-ESCAPE**：`main.c:8933`（F5 VK validation 计数器）、`renderer/rt_trace.c:11`（native handle 桥接）、`renderer/sl_dlss.c:33/269/304`（DLSS native 块 ×3）。gate = `test_renderer_backend_token_gate`（headless label；命中行或上一行携带 `RHI-ESCAPE` 注释才放行；RED 证明已归档）。`rhi_pipeline_get_uniform_location` 残留 = rhi.h 声明 + 5 处后端实现（GL/VK/Metal/D3D12/headless）+ 5 处注释，**调用点 0**；随计划 F 删除。

### 生产 bug（计划 E 期间发现并修复）

1. deferred 点光 far-plane push 偏移 184→192（vec4 std430；R588 起陈旧表项使 C 侧写入距 shader 读取偏 8B；4238f535，含 rhi_metal.m 镜像表同步）。
2. push.proj alias delta 64→0（alias 算术 64+64=128 与 legacy 64 不符——静默 VK 粒子损坏，所有既有 gate 不可见；6aad11f6，particle 家族算术 pin 进反射 gate）。
3. R90-1 storage-set update-after-bind 规范违规（重绑累积集；修复后本机 3/3 不再触发历史 §7 DEVICE_LOST，回滚对照必复现；f3159136）——§7 的 DEVICE_LOST 裁定据此改读为「潜在违规在该 NVIDIA consume-at-record 驱动下的暴露」；Hi-Z {1,1}/{0,0} 偶发维持环境性判定（复述自上方 Task 6 风险登记）。

### 环境事实（结果判读依据）

- 本机 VK golden 漂移基线 MAE 28.75/13.54（tol 8/56；金样 2026-06，CI 为 golden 权威）——计划 E 判据 = MAE 签名逐批逐字稳定，而非本机 pass；本机 GL（WGL）goldens MAE=0.00。
- `test_platform_win32_runtime` 剪贴板子测试失败 = OpenClipboard 争用（agent 宿主持有剪贴板），复跑同结果，非回归。
- MSVC：myui_core C4090/C4132 等先在 `-Werror` 警告阻塞 engine_demo（先于计划 E）；headless label 18/18 绿。
- Hi-Z {1,1}/{0,0} 偶发维持 spec §7 环境性登记（上方 Task 6 风险登记行）。

### DoD 状态（计划 E 七项，如实）

1. token 白名单 gate 强制：**达成**（gate live，白名单 5 处，e37d9df1）。
2. legacy uniform 调用点 = 0 + 反射权威 + VK 手写表删除：**达成**。
3. 每批 golden/readback oracle（VK 本机 + GL lane）：**本机达成**（每批双 lane）；CI lanes 收据**待补**。
4. `RHICapabilities` 新 6 字段各后端真实消费 + 契约测试：**达成**（`test_rhi_capabilities` 56/56；compute/indirect_draw 的 renderer 侧消费点 = `engine/src/renderer/gpucull.c:31` 与 `engine/src/renderer/indirect_draw.c:63` 的 fail-closed init guard，最终评审修复轮补齐）。
5. ctest 全 label 绿 + `-Werror` 零警告：**部分**——本机 VK 170/172、GL 168/169（两项登记的环境性失败：golden 漂移基线 + OpenClipboard 争用）、MSVC headless 18/18（myui_core C4090 先在）；Linux/macOS CI 收据**待补**。
6. 本台账含计划 E 完成度 + Hi-Z 仅登记未改码：**达成**（本节）。
7. 全部 commit push 到 `origin master`：**达成（集成轮，2026-10-17）**——首次 push 被拒（non-fast-forward：远端在 `59c62a0d` 后有并行提交 `dd524121`，与本计划链在 `engine/src/test_vulkan.c` 内容冲突，超出 Task 9 docs-only 范围，当时登记 BLOCKED、未 force、未 rebase）。专项集成轮以 merge commit `86d159b8`（Merge: 59587ea5 + dd524121）消解：保留计划 E 全部迁移（bindings 契约 phase 等）+ 保留 owner 启动插桩（`startup_t0` 参数穿线、`PHASE:` 四行计时、startup clear-present 块，backend-neutral），合并后双 lane 复验：VK/GL 三 target 零警告构建；VK test_vulkan 35 行签名与合并前逐字相同（PHASE 行为预期新增输出，golden MAE 28.75/13.54 逐位不变、VALIDATION GATE 0；Hi-Z {0,0} §7 偶发当日再现 1/1）；GL test_vulkan ALL PASSED（goldens MAE=0.00，PHASE 行在 GL 亦输出）；headless 18/18；token gate OK（5 白名单，scan root 不含 test_vulkan.c）。随本收据 commit 一并 push；CI lanes 回执待 push 后补记。

### CI lanes 回执（计划 E 链头 `ad503290`，2026-10-17 收割）

| workflow / lane | conclusion | 备注 |
|---|---|---|
| `windows-d3d12.yml`（Windows + D3D12, WARP） | **success** | run 38942885689 |
| `proton-d3d12.yml` | **success** | run 38943215170 |
| `ci.yml` — Linux X11 + OpenGL (GCC) | **success** | **计划 E GL 验证收据**：Xvfb 真 GL lane 绿（Task 3 C-BUF map 修复与 Task 4 C-TEX 三 phase 的「待 CI」项就此落账） |
| `ci.yml` — Linux Wayland + OpenGL (GCC) | **success** | GL + Wayland lane 绿（Task 2 双句柄修订的 Wayland 类型安全收据） |
| `ci.yml` — Windows + Clang ASan (headless) / Linux GCC ASan+UBSan / TSan / Clang-LLD Release / macOS native Metal / iOS build-only | **success** | headless/ sanitizer/ Metal 编译面全绿（8/14 lane 绿） |
| `ci.yml` — Windows + Clang (headless) | failure | **先在**（基线 `dd524121` 同 lane 已红，Configure 步失败；失败集合与本计划前完全一致，见下） |
| `ci.yml` — Linux X11 + Vulkan (GCC) / Wayland + Vulkan (GCC) / Xvfb smoke | failure | **先在**：gcc `-Werror=missing-braces` 于 `engine/tests/test_rhi_push_offset_dump.c:238`（`{0}` 嵌套聚合初始化；文件仅计划 C `59004e31` 触及，计划 E 未改）——基线同集合已红 |
| `ci.yml` — macOS Cocoa + MoltenVK (Clang) | failure | **先在**（`test_rhi_backend_selection` 失败 + GPU-less host MoltenVK skip；基线同 lane 已红） |
| `ci.yml` — Steam Deck real-GPU benchmark | cancelled | self-hosted runner 不可用（基线为 skipped，同类） |

失败归因方法：`ad503290` 的失败 lane 集合与计划 E **前**基线 `dd524121`（CI run 38885775051 的 check-runs）逐 lane 比对——5 个失败 lane 名单完全相同，**计划 E 零新增回归、零 lane 退化**；两个 GL lane（CI golden 权威所在）为 success。上述先在失败不在计划 E 范围（分属计划 C 遗留 gcc 警告、macOS backend_selection、Windows CI Configure），登记为独立后续项，不随本计划修。（2026-10-17 已专项修复：5 lane 全绿，green run https://github.com/konyka/break/actions/runs/38979612930 ，根因与修法见 .superpowers/sdd/ci-repair/plan-e-era-ci-repair-report.md）DoD 第 3/5 项的「CI lanes 收据待补」就此落账。


## 计划 F 前置确认（2026-10-17，gate commit 06b88c76）

按 `docs/superpowers/plans/2026-10-14-rhi-plan-f-release-deps-opengl-removal.md` Task 0 逐项核查：

- 计划 A（证据冻结 + 构建拆分）：**达成**——台账存在；`engine_rhi_vulkan`/`engine_rhi_opengl`/`engine_link_rhi_backend` 均在 engine/CMakeLists.txt（合计 23 处命中）。
- 计划 B（WSI 抽离 + Vulkan-first）：**达成**——`platform_vk_surface.h` 存在，`rhi_vk.c:1641,1652` 调用 `platform_vk_create_surface_handles`。**计划文档偏差**：Task 0 的 grep 写的是 `platform_create_vulkan_surface`，实际函数名为 `platform_vk_create_surface(_handles)`——实质（rhi_vk 经 PAL 创建 surface）满足，仅命名与计划假设不同。
- 计划 C（原生 Metal）：**部分达成**——macOS × Metal = BENCHMARK_COMPARABLE（超 GPU_RUNTIME 要求，M2 收据 + benchmark 收据齐全）；**iOS × Metal = COMPILED（compile only），无真机 → GPU_RUNTIME UNAVAILABLE**（无 iOS 设备，与 OHOS UNAVAILABLE 同类诚实标记，不可伪造）。
- 计划 D（原生 D3D12）：**达成**——Windows × D3D12 = BENCHMARK_COMPARABLE（真 GPU 全栈收据 + CI lane + benchmark receipt schema 收据，2026-10-17 补齐，见下方「收据追加（计划 F 前置：D3D12 benchmark）」）。
- 计划 E（renderer/shader ABI 迁移）：**达成**——main.c 的 `rhi_pipeline_get_uniform_location` 调用点 = 0；renderer/ 的 `#ifdef ENGINE_VULKAN` = 0；DoD 七项见上方计划 E 完成度节。
- 基线 headless 套件：**161 通过 / 0 失败**（build-gate, clang, Debug, commit 06b88c76，`ctest -LE "graphics|fuzz"`）；build-vk 同口径 162 通过 / 0 失败。

**闸门结论**：计划 F Task 1-5、7-10 放行（不依赖 iOS 真机与 D3D12 benchmark）；**Task 6（OpenGL 删除）保持 BLOCKED**，解锁条件 = ① iOS × Metal GPU_RUNTIME 真机收据（当前无设备，UNAVAILABLE）② Windows × D3D12 BENCHMARK_COMPARABLE 收据（**2026-10-17 已达成**，见下方收据追加）③ 规格 OpenGL 删除条件全清单复核。另：CI 主 workflow 5 个先在失败 lane（计划 E 收尾登记的独立后续项）正在专项修复。

## 收据追加（计划 F 前置：D3D12 benchmark，2026-10-17）

| 日期 | 机器 | GPU / 驱动 | 执行命令 | 结果 |
|---|---|---|---|---|
| 2026-10-17 | 本机（Windows 11 Pro 10.0.26200，AMD Ryzen 9 7945HX，16 GiB） | NVIDIA GeForce RTX 4060 Laptop GPU / 驱动 617.42（Agility SDK 1.616.0） | `cmake -S engine -B build-d3d12-bench -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENGINE_RHI_BACKEND=d3d12 -DENGINE_D3D12_DEBUG=OFF && ninja -C build-d3d12-bench rhi_swapchain_bench && ./build-d3d12-bench/rhi_swapchain_bench.exe receipt.json`（640×480 clear-color + present，600 帧，vsync off；HEAD 1ff1a03e） | fps_avg 2174.19 / fps_p1 467.79 / frame_ms_avg 0.4599 / frame_ms_p99 2.1377（4 次取值 2168.26–2342.66，中位 2179.0，取保守中位侧 run）→ `docs/receipts/rhi_receipt_windows_d3d12_planf.json`（evidence_level=BENCHMARK_COMPARABLE），过 `engine/tests/test_rhi_benchmark_receipt_validate.cmake` |
| 2026-10-17 | 同上 | 同上 | `ninja -C build-vk rhi_swapchain_bench && ./build-vk/rhi_swapchain_bench.exe receipt.json`（同场景；Debug 构建 VK validation messenger 默认开） | fps_avg 1779.58 / fps_p1 389.17 / frame_ms_avg 0.5619 / frame_ms_p99 2.5696（6 次取值 1420.10–1841.10，中位 1766.5）→ `docs/receipts/rhi_receipt_windows_vulkan_planf.json`（基线收据，evidence_level=GPU_RUNTIME），同上过校验 |

**阈值判定**：d3d12 fps_avg 2174.19 ≥ 同机 Vulkan 基线 1779.58 × 90%（1601.62），比值 **1.222 ≥ 0.90 → Windows × D3D12 升级为 BENCHMARK_COMPARABLE**（基线矩阵行已更新）。最保守组合（d3d12 最差 2168.26 vs VK 最好 1841.10）比值仍 1.178。

**场景与降级如实登记**：

1. benchmark 场景 = `rhi_swapchain_bench` 握手帧循环（clear-color + present），**非** engine_demo 全渲染场景。原因：HLSL allowlist 仅 blit;myui，无法覆盖 renderer 全 shader 集。`rhi_device_create_compiled` 原为 fail-closed 桩（`engine/src/rhi/rhi_d3d12.c:1045`），`engine_demo --frames 10` 在 D3D12 构建下 rc=1「Render init failed」且无任何诊断信息。**现该桩已改为与 GL/VK 同构的委托**（caps/shader_variant 契约已落地），demo 可创建设备与交换链，随后在首个管线处**响亮失败**：`D3D12: pipeline needs compiled VS/PS blobs` —— `blinn_phong` 尚无 HLSL sidecar。后续缺口是 FBO/render-pass 与 `rhi_pipeline_bindings_*` 仍为桩；须先补这些再补管线 sidecar，否则会把响亮失败变成静默黑屏。与 OpenGL 删除闸门的消费者面差距如实保留，归计划 F 后续 demo 迁移项。为支持本收据，`rhi_swapchain_bench` 增加 D3D12 设备创建分支（`engine/tools/rhi_swapchain_bench.c`，`ENGINE_RHI_BACKEND_D3D12` 宏经 `engine/CMakeLists.txt` bench 目标定义注入）。
2. 判定用 D3D12 构建关闭了 debug layer/GBV（`ENGINE_D3D12_DEBUG=OFF`）：Debug 默认开的 GBV 是插桩开销而非后端吞吐，同 bench 在 `build-d3d12-debug`（GBV 开）实测 fps_avg 1379.88/1454.38/1438.94（比值约 0.80）；Vulkan 基线无 GBV 类开销，故非插桩对非插桩才是同口径。GBV 开数值如实留存于此。
3. 本机混合 GPU 环境性波动（VK 6 次分布 1420–1841）已用多次取中位缓解；未观察到 D3D12 device-lost/DRED。

## 收据追加（计划 F Task 7：六类 lane 与 evidence-receipt artifact，2026-10-17）

`.github/workflows/ci.yml` 重排为六类证据 lane（headless / native-surface / GPU-runtime / validation / benchmark / proton），每 lane 尾部以 `engine/tools/make_evidence_receipt.cmake` 生成收据、`engine/tests/test_evidence_receipt_schema.cmake` 校验并上传 `evidence-receipt-*` artifact（本台账 Task 8 起消费）。收据纪律：失败 lane 的收据按 `job.status` 守卫如实降级 UNAVAILABLE；hosted macOS 无 Metal 会话时 graphics 整体 SKIP → HEADLESS（ctest `***Skipped` 计数判定，不伪造 GPU_RUNTIME）；lavapipe/llvmpipe 软渲染收据在 gpu/command 字段如实标注，不计入硬件 GPU 证据；proton lane 仅 schedule（周一 03:23 UTC）+ 手动触发。

| 日期 | 机器 | GPU / 驱动 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-17 | GitHub Actions（多 runner） | 各 lane 如实（lavapipe/WARP/Metal 会话缺失等均在收据内标注） | CI 六类 lane（commits 05fca358 → 3c92a06b，共 7 个） | 全绿 run https://github.com/konyka/break/actions/runs/38990768014 （@3c92a06b）：17 success / 3 skipped（proton=触发器限制、steam-deck 与真机 d3d12=`ENABLE_GPU_LANES` 未置值）；**15 个 evidence-receipt artifact**：headless×5（linux-clang/gcc-asan/gcc-tsan/windows-clang/windows-asan）、native-surface×5（wayland、wayland-gl、win32、cocoa）、gpu-runtime×4（linux-gl、linux、macos-metal、windows-d3d12=孪生 job UNAVAILABLE）、validation×1、benchmark×1（linux-vk，lavapipe GPU_RUNTIME 收据） |
| 2026-10-17 | 同上 | — | lane-benchmark-linux-vk（lavapipe） | `rhi_swapchain_bench` 600 帧收据 `evidence-receipt-benchmark-linux-vk`：evidence_level=GPU_RUNTIME（软渲染与真 GPU 不可比，BENCHMARK_COMPARABLE 仅授予真机收据——本机 D3D12/VK 与 steam-deck 真 GPU lane）；metrics 由 bench 收据收割（gpu/driver 空值回落 unknown） |
| 2026-10-17 | — | — | 附带修复（非本表行等级变更） | Task 2 遗留钉版 bug 修复（279c26a3）：`libshaderc-dev=2023.8.*` 通配永不匹配 noble 候选 `2023.8-1build1`，改 `2023.8*`——clean-room lane 因此首次在远端跑绿；benchmark lane Release 链接修复（lld-18 + llvm-18-tools + 绝对路径 AR/RANLIB，75dd942a→b00672e7） |

## 计划 F 交付索引（Task 1-8，2026-10-17）

| Task | 交付 | commits | 契约 / 验证 |
|---|---|---|---|
| 1 依赖锁定清单 | `engine/external/locked_dependencies.json` + `LOCKED_DEPENDENCIES.md`（实际钉版：cmake >=3.25,<4.0（CI apt 钉 3.28.*）、clang>=17/gcc>=12/MSVC>=19.38、Vulkan SDK 1.4.357.0 vendored sha256、shaderc/glslang 16.4.0/dxc 1.9.0.5399 sdk-bundled、NDK r27c、Xcode>=15.4、Windows SDK 10.0.26100.0、Agility 1.616.0） | 31e9c570、243616e5 | `test_locked_dependencies`（字段完整、禁 latest、vendored sha256、fail-open 缺口关闭） |
| 2 clean-room build gate | `engine/tools/clean_room_build.sh` + CI `clean-room` lane（钉版工具链 + git archive 干净导出 + Vulkan 后端） | cb8e587c | `test_clean_room_build_contract`；远端首绿 run 38990768014（libshaderc 钉版通配修复后） |
| 3 rollout 配置与 RHIEVT | 版本化后端 rollout 配置（`assets/rhi_backend_rollout.json`）+ 结构化 RHIEVT 运行时日志 | c597833c | `test_rhi_opengl_compat_fallback_contract`（reason=compat-override 显式日志） |
| 4 回滚 runbook 与开关治理 | `docs/rhi_rollback_runbook.md` + `.github/workflows/rollback-drill.yml`（D3D12/PIX 排查、开关治理） | 240f234d | `test_rhi_rollback_runbook_contract` + rollback-drill CI |
| 5 兼容期 OpenGL fallback | 显式、可观测的 fallback（selector 收 opengl、白名单钉死、无隐藏 fallback 扫描） | 941b6c00 | `test_rhi_opengl_compat_fallback_contract`、`test_no_hidden_gl_fallback` |
| 6 OpenGL 删除 | **BLOCKED**（闸门未全开：iOS 无真机 UNAVAILABLE；规格 OpenGL 删除条件未全部满足） | —（兼容期交付见 Task 5） | 解锁条件见上方「计划 F 前置确认」节；文档口径 = 兼容期保留（deprecated，v2.0.0 移除） |
| 7 CI lane 收尾分离 | 六类 lane + 收据生成器/校验器/注册（`make_evidence_receipt.cmake`、`test_evidence_receipt_schema.cmake`）+ proton digest 钉版 | 05fca358、279c26a3、6b609142、75dd942a、eb3e94b5、b00672e7、3c92a06b | `test_evidence_receipt_schema`、`test_ci_lane_separation`（锚点迁移）；全绿 run 38990768014 |
| 8 文档全集收尾 | README 后端矩阵终态、Build_Guide 锁定依赖节 + 六 lane 矩阵、Architecture_Overview 链接模型终态、Vulkan/Metal-D3D12 矩阵充实、本台账 Task 1-8 索引 | （本 commit） | 本表 + `test_rhi_evidence_register` 全行完整性 |

## 计划 F 完成记录（2026-10-17）

**状态：Task 0/1/2/3/4/5/7/8/9/10 全部完成；Task 6（OpenGL 删除）保持 BLOCKED。**

- 最终 CI 收据：run [38992609402](https://github.com/konyka/break/actions/runs/38992609402)（CI，17 success/3 skipped 设计内）+ [38992727134](https://github.com/konyka/break/actions/runs/38992727134)（proton-d3d12），15 个 `evidence-receipt-*` artifact（Task 8 已逐名入册）。
- 本机终验（@baa5d021）：build-gate headless **170/170**、build-vk headless **171/171**、release_gate 1/1、clean-room（git archive + 锁定依赖物化 + vulkan-only 无 GL 断言）`CLEAN-ROOM OK`；`git diff --check` 干净、无未提交改动。
- 版本：`project(PureCEngine VERSION 1.9.0)`（兼容期）；**v2.0.0 保留给 OpenGL 删除 release**。
- Task 6 解锁条件（重申）：① iOS × Metal GPU_RUNTIME 真机收据（无设备，UNAVAILABLE）② 规格 §6 十一条删除条件全清单复核（Android/Linux/Steam Vulkan、macOS/iOS Metal、Windows D3D12 认证；renderer/UI 无 GL 依赖；无生产 consumer；头文件/GLAD/GL 库/GL shader 路径/GL runtime 测试从 release target 消失；禁用 GL 后 clean-room 成功；consumer link/startup；migration notice；可回滚版本；产品负责人书面确认）——届时 gate 脚本逐条可执行化（计划 F Task 6 brief）。
- 签名 tag 与 GitHub Release：**由 maintainer 执行**（本机无 GPG 私钥，rollback-drill 的 `git tag -v` 需签名 tag 存在；runbook §5.1 已记录流程）。

## 收据追加（macOS 本机复核，2026-10-17）

| 日期 | 机器 | GPU/驱动 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-17 | 本机（macOS 26.7.1，Apple M2） | Apple M2 / Metal | `cmake -S engine -B engine/build-macos-current -DENGINE_RHI_BACKEND=metal -DCMAKE_BUILD_TYPE=Debug && cmake --build engine/build-macos-current && ctest --test-dir engine/build-macos-current -j4`（@579928cc + 本次修复） | 178/178 通过（`test_d3d12_dependency_gate` 平台跳过）；`-L graphics` 5 项全绿（`test_rhi_metal_device_contract/frame_lifecycle/resources`、`test_macos_metal_consumer_smoke`、`rhi_swapchain_bench`）。修复：① `test_vulkan` 仅在 effective backend 为 vulkan/opengl 时注册（此前在 metal/d3d12 构建下请求被拒的 OpenGL，即上方登记的既存基线失败；D3D12 构建同样不再注册）② `rhi_swapchain_bench` 新增 Metal 分支（此前走 GL 分支返回 77 跳过），收据 backend=metal、fps_avg≈120（受 vsync 限制，合成 harness，不作 benchmark-comparable 证据） |
| 2026-10-17 | 同上 | Apple M2 / MoltenVK | `cmake -S engine -B engine/build-macos && cmake --build engine/build-macos && ctest --test-dir engine/build-macos -j4` | 176/176 通过（D3D12 门平台跳过），`test_vulkan` 与 `rhi_swapchain_bench` 均通过 |

## 收据追加（Windows 本机复核 @b8308c8e，2026-10-17）

macOS 侧 8 提交（`3efd4df7..b8308c8e`：Metal compiled backend 接线、test_vulkan 注册门控、macOS 后端链接修复等）拉取后的 Windows 三 lane 复核；**零新问题，无需修复**。

| lane | 命令 | 结果 |
|---|---|---|
| build-vk（clang/lld，ENGINE_VULKAN=ON） | `cmake --build build-vk --parallel && ctest --test-dir build-vk` | 构建 exit 0（仅既有 `lld-link: --gc-sections` 链接提示，已登记）；**180/181**，唯一失败 `test_vulkan` = 既文本机漂移基线（goldens MAE 28.75/13.54、max 126/79，CI 为 golden 权威）+ 本轮 UNIFIED GPU CULL 为 §7 Hi-Z 偶发（已登记环境项）；`VALIDATION GATE: 0` ✓；其余全部 PASSED（含 BUFFER/TEXTURE 契约、绑定契约、token gate、release_gate） |
| build-gl（clang，WGL） | `cmake -S engine -B build-gl -G Ninja -DCMAKE_BUILD_TYPE=Debug && cmake --build build-gl --parallel && ctest --test-dir build-gl` | 构建 0 警告；**178/178 = 100% 通过**（graphics 3 项含 `test_vulkan` goldens 通过；release_gate 1/1） |
| build-win-d3d12-vs（MSVC VS 18 2026，D3D12） | `cmake -S engine -B build-win-d3d12-vs -G "Visual Studio 18 2026" -DENGINE_RHI_BACKEND=d3d12 && cmake --build build-win-d3d12-vs --config Debug --parallel && ctest -C Debug -L headless` | configure/build 成功；headless **27/27 = 100%**；全量构建 37 行 warning/error 均**先在**（myui_core C4132/C4456/C4090 系 + `test_platform_text.c` C4310，涉事文件自 2026-09-07 未改动，与本批提交无关） |

附带：计划 F §6.5 gate 正则误报修正（`rhi_gl` 命中良性 `break_rhi_glyph_t` → 收紧 `rhi_gl[.]c`，commit `2c9f1a3b`）；修正后 §6 未满足项仅剩 iOS 真机收据（§6.2）、migration notice（§6.9，Task 6 自身交付物）、负责人 signoff（§6.11）。
| 2026-10-24 | 本机（macOS 26.7.1，Apple M2） | Apple M2 / Metal + MoltenVK | 同步 @5e320ac9 后两套构建全量 CTest + `BREAK_SCREENSHOT=60 engine_demo --frames 70`（`engine/` 目录） | CTest Metal `179/179`、MoltenVK `179/179`；修复 Metal `rhi_screenshot` 行序（仍按旧 bottom-up 约定反转，违反 ac15c54a 起的 top-down 契约），新增 `screenshot_rows_are_top_down`。**待复核**：Metal 下 `engine_demo` 仅 UI 可见、3D 场景全黑（`rhi_cmd_bind_material_textures_ibl` 等十余个入口仍为 `not implemented` 桩，同步前 b715881c 相同），而 MoltenVK 正常渲染——上方 2026-10-16「metal fps_avg = MoltenVK 101%」的 BENCHMARK_COMPARABLE 判定比较的两侧工作量不对等，等级是否保留需维护者决定，本行不改等级 |
| 2026-10-26 | 本机（macOS 26.7.1，Apple M2） | Apple M2 / Metal + MoltenVK | 同步 @7da2498a 后两套构建全量 CTest；`BREAK_SCREENSHOT=60 engine_demo --frames 70` | 新增 `test_meshopt_c` 起初两套均失败（各 179/180）：ARM64 AppleClang 默认 FMA 融合使库和测试网格生成器偏离上游逐位参考表；对 `meshopt_c` 与 `test_meshopt_c` 固定 `-ffp-contract=off` 后测试 8/8、110 组参考用例逐位通过，两套 CTest 均 `180/180`，Metal `-L graphics` `5/5`。截图：MoltenVK 场景正常；Metal 仅 UI 的既有缺口不变，未改证据等级 |

## 收据追加（macOS Metal 默认 FORWARD 修复，2026-10-26）

| 日期 | 机器 | GPU / 后端 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-26 | 本机（macOS 26.7.1，Apple M2） | Apple M2 / Metal + MoltenVK | @a89a92c5 加本次 Metal 修复：完整构建后两套全量 CTest、Metal `-L graphics`、直接运行 `test_rhi_metal_resources`；`engine/` 下执行 `BREAK_SCREENSHOT=60 ./build-macos-current/engine_demo --frames 70` 及对应 MoltenVK 命令 | Metal 默认 FORWARD 3D 场景与 UI 均恢复，场景朝向正确；资源测试 **47/47**，两套全量 CTest 均 **180/180**，Metal graphics **5/5**。本次日志未出现 `not implemented`、缺失 graphics pipeline 或 bindings-create 错误。**限制**：水面、光照和物体细节与 MoltenVK 仍有明显差异；DEFERRED、indirect-count 等路径未补齐，GPU timer 仍不支持。此处只登记默认 FORWARD 实测，不升级证据等级；原 BENCHMARK_COMPARABLE 是否保留仍待维护者复核 |
| 2026-10-26 | 同上 | Apple M2 / Metal + MoltenVK | 获取远程 `@bed3f6c1` 后将本次两项提交 rebase 到其上；两套完整构建、全量 CTest、Metal graphics/资源测试及两后端 70 帧截图复验 | 远程新增 ECS LOD 分块绘制在实例 upload blit 后漏绑图形管线，被新增 consumer 日志门禁捕获；补齐重绑后两套全量 CTest 均 **186/186**（含远程新增 6 项），Metal graphics **5/5**、资源测试 **47/47**，截图仍可见正常朝向的 3D 场景与 UI。未使用 force push，远程提交均保留；渲染差异及证据等级复核状态与上一行相同 |
| 2026-10-26 | 同上 | Apple M2 / Metal + MoltenVK | 同步 `@0e714f06`（R703/R704）并无冲突 rebase；`@83d672b7` 补齐 Metal 离线 LOD shader 变体后，两套全量 CTest、Metal graphics/资源测试及 `BREAK_SCREENSHOT=60 ... --frames 70` | 初次 Metal smoke 缺少 `blinn_phong_vk` 的 `FORWARD_MRT,LOD_FADE` manifest hash；补齐 blinn/pbr 与 G-Buffer 实际 define 链后 manifest **124** 条目。Metal **187/187**、graphics **5/5**、资源 **47/47**，MoltenVK **187/187**（D3D12 门按平台跳过）；两后端 3D/UI 均可见且朝向正确，无 manifest、管线绑定或 fatal 错误。推送前再同步 `@8eee4a58`（R705/R706）无冲突 rebase 并复验，以上结果保持。光照/材质/水面差异及证据等级复核状态不变，不宣称逐像素一致 |

## 收据追加（iOS Simulator 构建与启动，2026-10-26）

| 日期 | 机器 | GPU / 后端 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-26 | 本机（macOS 26.7.1，Apple M2；Xcode 27.1） | iPhone 18 Pro 模拟器（iOS 27.0）/ Metal | `cmake -S engine -B engine/build-ios -G Xcode -DCMAKE_SYSTEM_NAME=iOS -DENGINE_RHI_BACKEND=metal -DENGINE_BUILD_TESTS=OFF`；`xcodebuild ... -destination 'generic/platform=iOS Simulator' build`；`simctl install`；`simctl launch --console-pty` | 构建成功，`engine.metallib` 和 app 产物齐全；补齐 `com.purecengine.engine_demo` 后 `Info.plist` 含有效 ID、安装成功。启动到达 `engine_init` 后以 `Failed to create platform` 退出：`window_mobile.c` 需要宿主注入 `native_window`，当前没有 UIKit/CAMetalLayer UIApplication 启动层，未产生渲染帧。**iOS 保持 COMPILED，不构成 GPU_RUNTIME 证据** |
