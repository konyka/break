# QNX 兼容收尾 + 定时器/性能最优计划（2026-11-20）

> 目标：完成 `feat/qnx-compat` 全部遗留问题，以最优化性能、多线程安全、零泄漏
> 崩溃为标准，通过 TDD 与全量门禁后推送并合入 `master`。
> 事实来源：`docs/qnx_compat.md`、`docs/Implementation_Status.md`。

## 1. 现状盘点（已完成分析）

工作树含一批 2026-11-03 已验证但未提交的在飞改动，归纳为五组：

1. **定时器跨平台**：`time_sleep_us` QNX 路径改用
   `clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME)` 绝对截止时间
   （`engine/src/platform/time.c`）；EINTR 按同一 deadline 续睡、永久错误
   不忙循环、读时钟失败不睡。测试以 `__wrap_clock_nanosleep` 注入故障
   （`engine/tests/test_platform_time.c`）。
2. **高并发定时器精度**：`test_myui_timer_concurrency` 的 `due_us` 改用
   `my_pal_time_now_ms()`（与定时器管理器同一时钟源，break PAL 下为
   `time_microseconds()/1000`），断言 `min latency >= 0`，消除毫秒下取整
   造成的负延迟伪象。
3. **离屏 Vulkan→LCD**：surfaceless PAL（仅声明
   `VK_KHR_surface + VK_EXT_headless_surface`）经 readback + 每窗口 staging
   呈现到 LCD（`my_window.c`、`rhi_vk_screen_post.*`）。
4. **性能/安全小项**：async_loader 堆 256→1024；lod_skin 逐三角形 bounds
   预计算 + 分配溢出防护；engine FPS 统计用 raw delta；my_window_paint 的
   make_current/swap 错误恢复。
5. **构建修复**：`test_qnx_spawn.h` 的 envp helper 在非 QNX 分支未被引用，
   按项目惯例加 `__attribute__((unused))`（本文件已修）。

定时器管理器（`my_timer.c`）已是**二叉最小堆 + 开放寻址哈希索引 + pending
压缩**的成熟实现：add/remove/fire/due_in 均 O(log n) 或 O(1)，10k pending
提交 5 轮中位 Linux 80 µs、QNX 72 µs。本轮不重构其数据结构。

## 2. 优化策略（性能最优 = 不回归 + 定点增强）

| 项 | 动作 | 验收 |
|----|------|------|
| 定时器精度 | QNX 绝对 deadline 睡；时钟源对齐 | `test_platform_time` 4/4、`test_myui_timer_concurrency` 四周期 min≥0 |
| 定时器吞吐 | 保持堆实现，跑基准回归 | `test_myui_timer_stress`、pending 提交基准不劣化 |
| 异步加载 | 堆 256→1024 消除并发上限 | `test_async_loader` 全绿 |
| 渲染 CPU 侧 | lod_skin bounds 预计算 | `lod_skin` 相关测试 + ASan |
| 引擎 FPS | raw delta 统计 | 引擎生命周期测试 |
| 并发正确性 | TSan 全量 | 无竞态报告 |
| 泄漏/崩溃 | ASan/UBSan/LSan 全量 | 零报告 |

纪律：不重构已最优的定时器堆；不为微观收益引入平台特例；每个优化必须
附带或复用现有回归测试，先红后绿。

## 3. 执行顺序

1. [x] 修复构建错误（test_qnx_spawn.h）。
2. [ ] Linux Release 全量 ctest（235 项）。
3. [ ] Linux ASan/UBSan 全量 ctest。
4. [ ] Linux TSan 全量 ctest（隔离 Mesa 已知插桩，按 §6.2 流程）。
5. [ ] 高并发定时器精度复测（普通 + ASan），收集 p50/p95/p99/max。
6. [ ] QNX 目标复验：timer 矩阵 + clock_nanosleep 路径（x86_64 VM）。
7. [ ] 文档更新（qnx_compat、Implementation_Status、Engine_Modules）。
8. [ ] 提交、推送 `feat/qnx-compat`，合入 `master`。

## 4. 不可在本环境验收的边界（保持诚实，不写成完成）

物理 GPU/原生 `VK_QNX_screen_surface`、Khronos validation layer、QNX TSan、
硬实时保证、ARM 全量 `test_vulkan` 最终退出码。这些继续作为已知边界记录，
不以 headless/定向探针替代验收。
