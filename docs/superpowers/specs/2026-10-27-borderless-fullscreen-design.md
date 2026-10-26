# 无标题栏全屏（borderless fullscreen）设计

状态：设计。用户要求：跨平台、运行时切换全屏/窗口、切换时渲染尽量流畅、TDD、测试通过后提交并维护文档。

## 1. 现状（已核实）

| 后端 | `platform_toggle_fullscreen` 现在做什么 | 问题 |
|---|---|---|
| Win32 | 保存 `GWL_STYLE` + `WINDOWPLACEMENT`，去掉 `WS_OVERLAPPEDWINDOW`，`SetWindowPos` 铺满所在显示器 `rcMonitor` | 已是无边框全屏；状态只在内部翻转，没有查询接口 |
| X11 | 向根窗口发 `_NET_WM_STATE_FULLSCREEN` 切换消息 | 本地布尔假设 WM 一定照做；WM 拒绝或用户用快捷键切换时状态失配 |
| Wayland | `xdg_toplevel_set/unset_fullscreen` | 同上：不读 configure 的 `states` 数组里的 `XDG_TOPLEVEL_STATE_FULLSCREEN` |
| Cocoa | `[NSWindow toggleFullScreen:]` | macOS 原生全屏：约 0.7 s 动画 + 独立 Space，不是「无边框窗口」，切换明显卡顿 |
| QNX Screen / 移动端 | 空函数 | 移动端本来就是全屏；QNX 未实现 |

- 只有 `toggle`，没有 `set(mode)` / `get_mode()`，也没有启动参数；`main.c` 的 `G` 键调用它。
- **主要卡顿来源在引擎侧**：`main.c` 检测到尺寸变化后，先 `rhi_device_resize`（交换链重建，合理），然后把约 20 个后处理系统 `*_shutdown` + `*_init`，其中包括**重新编译全部着色器与管线**（VK/GL 在进程内编 GLSL，D3D12 读 DXIL 再建 PSO）。真正必须随分辨率变化的只有渲染目标。
- 切换时窗口管理器往往分两次通知尺寸（先去边框、再铺满），引擎会重建两次。

## 2. 目标与验收

1. 公共 API：
   ```c
   typedef enum { PLATFORM_WINDOW_MODE_WINDOWED = 0, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN } PlatformWindowMode;
   bool               platform_set_window_mode(Platform *p, PlatformWindowMode mode); /* 幂等；不支持返回 false */
   PlatformWindowMode platform_get_window_mode(Platform *p);   /* 反映平台确认后的真实状态 */
   ```
   `platform_toggle_fullscreen` 保留，改为基于前两者实现。`PlatformConfig` 增加 `start_fullscreen`；`engine_demo` 读 `BREAK_FULLSCREEN=1`。
2. 语义：**无边框、铺满窗口当前所在显示器、不改显示器分辨率、不独占**（与 DXGI flip 模型 / Vulkan 的合成器直通一致，Alt-Tab 不黑屏）。退出时恢复原位置、尺寸、最大化状态。
3. 切换流畅：一次切换的「最长单帧」不超过 3 个正常帧时间（目标：VK/GL/D3D12 Release 下切换帧 < 50 ms），切换过程中不出现黑帧以外的错误画面（允许 1 帧拉伸）。
4. 各后端：Win32、X11、Wayland、Cocoa 真实实现；QNX Screen 与移动端返回「已是全屏 / 不支持窗口模式」并有测试。

## 3. 设计

### 3.1 纯逻辑：`platform/window_mode.h`（header-only，全后端共用，可在任何主机测试）

```c
typedef struct {
    PlatformWindowMode current;     /* 平台已确认 */
    PlatformWindowMode requested;   /* 最近一次请求 */
    bool  pending;                  /* 已发请求、尚未被平台确认（X11/Wayland/Cocoa 异步） */
    bool  saved_valid;
    i32   saved_x, saved_y; u32 saved_w, saved_h; bool saved_maximized;
} PlatformWindowModeState;

/* request：返回需要执行的动作（NONE/ENTER/LEAVE），幂等（current==mode 且无 pending 时 NONE）。 */
/* confirm：平台回报的真实状态（WM 拒绝、用户快捷键切换都走这里），清 pending。 */
/* 进入时保存窗口矩形；离开时给出要恢复的矩形；显示器矩形由调用方传入。 */
```
状态机覆盖：重复请求、切换中再次反向请求（以最后一次为准）、平台拒绝（confirm 回旧值）、平台自发切换（外部快捷键）。

### 3.2 各后端

- **Win32**：沿用现有路径（`WS_POPUP` 等价：去 `WS_OVERLAPPEDWINDOW`，`SetWindowPos(HWND_TOP, rcMonitor, SWP_FRAMECHANGED|SWP_NOOWNERZORDER)`），改成**一次** `SetWindowPos` 同时改样式与尺寸（避免两次 WM_SIZE）；同步，立即 confirm。保持 `WINDOWPLACEMENT` 恢复最大化。可选按住 Alt+Enter 切换（引擎层快捷键，不靠 DXGI；D3D12 已 `DXGI_MWA_NO_ALT_ENTER`）。
- **X11**：发 `_NET_WM_STATE` 客户端消息（已有），**以 `PropertyNotify(_NET_WM_STATE)` 读回为准**做 confirm；同时设 `_NET_WM_BYPASS_COMPOSITOR=1`（全屏时，减少合成延迟）。没有 EWMH 的 WM：回退为 override-redirect 无效时用 `_MOTIF_WM_HINTS` 去装饰 + 移到显示器矩形。
- **Wayland**：`xdg_toplevel_set_fullscreen(NULL)`；在 `xdg_toplevel.configure` 的 `states` 中读 `XDG_TOPLEVEL_STATE_FULLSCREEN` 做 confirm；客户端装饰（`platform_needs_client_decoration`）在全屏时报告 false。
- **Cocoa**：**不用** `toggleFullScreen:`。进入：保存 `frame` 与 `styleMask`，改为 `NSWindowStyleMaskBorderless`，`setFrame:[screen frame] display:YES`，`NSApp.presentationOptions = HideDock|HideMenuBar`，窗口级别 `NSMainMenuWindowLevel+1`。离开：恢复。同步完成，无动画、不切 Space。
- **QNX Screen / 移动端**：`get` 返回 BORDERLESS_FULLSCREEN；`set(WINDOWED)` 返回 false。

### 3.3 引擎侧：切换不卡顿

1. **resize 只重建渲染目标**：给需要尺寸相关资源的后处理系统增加 `*_resize(sys, dev, w, h)`（只销毁并重建纹理/FBO，保留着色器和管线）；没有尺寸相关资源的系统不动。`main.c` 的重建块改为调用 resize。系统内部 init 拆为「管线创建」与「目标创建」两个静态函数，resize 只调后者。逐个系统迁移，每个系统一个单元/运行测试保护（重建前后 handle 不变的管线、尺寸正确的目标）。
2. **尺寸去抖**：一次模式切换期间（`pending` 或切换后 2 帧内）合并多次尺寸通知，只按最终尺寸重建一次。
3. **TAA/时间性效果**：重建目标后历史失效，标记首帧不混合（避免拖影），已有的 history reset 机制复用。
4. **测量**：`engine_demo` 增加 `BREAK_TOGGLE_FULLSCREEN_AT=frame[,frame...]` 自动切换，日志输出 `WINDOW_MODE_SWITCH mode=... rebuild_ms=... frame_ms=...`，统计切换帧时间，用于验收第 3 条。

## 4. 测试（TDD）

- `test_platform_window_mode.c`（纯逻辑，所有主机）：请求幂等、进入/离开保存与恢复矩形、切换中反向请求、平台拒绝、外部切换、多显示器矩形选择（复用 `monitor_selection.h`）。
- 运行时测试（真实窗口）：
  - Win32（本机）`test_platform_win32_runtime`：进入后 `GWL_STYLE` 无 `WS_CAPTION|WS_THICKFRAME`、客户区等于显示器矩形、`platform_get_window_mode` 为全屏；离开后样式与 `WINDOWPLACEMENT` 恢复（含最大化）；重复调用幂等。
  - X11（CI Xvfb + 无 WM 时回退路径）/ Wayland（CI headless weston）/ Cocoa（macOS CI）：进入后窗口尺寸等于显示器、模式查询正确、离开恢复。
  - QNX/移动端：模拟测试 `get` 与 `set(WINDOWED)` 语义。
- 引擎：每个迁移到 `*_resize` 的后处理系统，测试「resize 后管线 handle 不变、目标尺寸更新」（WARP / 无头后端可跑的放 ctest）。
- 端到端：三后端 Release 用 `BREAK_TOGGLE_FULLSCREEN_AT` 自动来回切换，校验无验证层错误、切换帧时间，截图检查全屏画面铺满且无边框。

## 5. 不做

- 独占全屏（改显示器分辨率 / DXGI `SetFullscreenState`）：与无边框目标冲突，且 Alt-Tab 体验差。
- 在全屏状态下跨显示器拖动（全屏总在进入时所在的显示器）。
