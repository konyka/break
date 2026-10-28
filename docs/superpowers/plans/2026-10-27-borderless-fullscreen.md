# 无标题栏全屏 实施计划

设计：`docs/superpowers/specs/2026-10-27-borderless-fullscreen-design.md`。全程 TDD：每项先写失败测试、确认失败、再实现、确认通过。

## 任务

1. **纯状态机 `platform/window_mode.h` + `test_platform_window_mode`**（主代理）
   - 测试：请求幂等；进入保存窗口矩形/最大化、离开给出恢复矩形；切换中反向请求以最后一次为准；平台拒绝（confirm 旧值）；外部自发切换（confirm 新值、无 pending）；移动/QNX 固定全屏策略。
   - 注册 ctest（headless、platform_contract 标签），GCC 语法检查。
2. **公共 API + Win32 + 引擎接线**（代理 W，worktree `wt/fs-win`）
   - `platform.h`：`PlatformWindowMode`、`platform_set_window_mode`、`platform_get_window_mode`、`PlatformConfig.start_fullscreen`；`platform_toggle_fullscreen` 改为基于 set/get。所有后端（含 x11/wayland/cocoa/screen/mobile 与测试桩）先给出编译得过的实现（非 Win32 先用旧逻辑 + 状态机），保证全平台可编。
   - Win32：一次 `SetWindowPos` 完成样式 + 尺寸；`test_platform_win32_runtime` 新增用例（样式、客户区 = 显示器、模式查询、恢复含最大化、幂等、`start_fullscreen`）。
   - `engine_demo`：`BREAK_FULLSCREEN=1`、`BREAK_TOGGLE_FULLSCREEN_AT=f1,f2,...`、Alt+Enter 与 `G` 键、日志 `WINDOW_MODE_SWITCH`（切换帧号、模式、重建耗时、切换前后 3 帧最大帧时间）。先在改动前测出**基线卡顿**。
3. **渲染目标按尺寸重建，不重建管线**（代理 R，worktree `wt/fs-resize`）
   - 每个后处理系统加 `*_resize(sys, dev, w, h)`：只重建纹理/FBO，管线/绑定/采样器保留；失败时保持旧目标（与 R362 同样的先建后换）。`main.c` 重建块改为调用 resize；尺寸去抖（同帧多次通知只重建一次）；TAA 等时间性效果重置历史。
   - 测试：WARP（D3D12）或可运行的运行时测试里，对代表性系统验证 resize 后管线 handle 不变、目标尺寸正确、再次渲染像素正确；全量 ctest。
   - 用任务 2 的测量方法（或其等价独立测量）给出重建耗时前后对比。
4. **X11 / Wayland / Cocoa / QNX / 移动端真实实现**（代理 U，worktree `wt/fs-unix`，依赖任务 1、2 的 API；在任务 2 合并后开始）
   - X11：`_NET_WM_STATE` 请求 + `PropertyNotify` 读回确认，`_NET_WM_BYPASS_COMPOSITOR`，无 EWMH 回退（`_MOTIF_WM_HINTS` + 移到显示器矩形）。
   - Wayland：configure `states` 读 `XDG_TOPLEVEL_STATE_FULLSCREEN` 确认；全屏时 `platform_needs_client_decoration` 为 false。
   - Cocoa：borderless styleMask + 屏幕 frame + presentationOptions，不用 `toggleFullScreen:`。
   - QNX/移动端：固定全屏语义。
   - 运行时测试扩展 `test_platform_x11_runtime` / `wayland_runtime` / `cocoa_runtime`（CI 上跑），模拟测试覆盖 QNX/移动。本机无法运行的部分以 CI 结果为准。
5. **合并与验收**（主代理）
   - 合并 W、R、U；7 棵构建树 0 警告；全量 ctest；GCC 语法检查。
   - 三后端 Release：`BREAK_TOGGLE_FULLSCREEN_AT` 来回切换 ≥ 4 次，切换帧 < 50 ms（与基线对比），VK 验证层 0、D3D12 调试层 0，截图确认全屏铺满无边框、回到窗口后位置尺寸恢复。
   - 文档：`docs/Implementation_Status.md` 顶部新节；`docs/Build_Guide.md` 或用户可见文档补充快捷键与环境变量；设计文档状态。推送，确认三条 CI。
