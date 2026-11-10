# OpenGL clip 原生 Wayland 超时修复报告

- 日期：2026-11-10
- 工作树：`/home/timeshift/opensource/break/.worktrees/remove-x11`
- 基线：`7f1656ae5feca210128c8d93fb49028f5ec56a29`
- 范围：只修复 `test_myui_break_rhi_clip` 的既有 OpenGL/Wayland 超时；不改生产默认 vsync，不删除 present/readback，不削弱断言，不处理 CI 或其它生产问题，不合并、不 push。

## 1. 结论与证据边界

最终代码改动只有一处：在测试设备创建成功后调用 `rhi_set_vsync(g_dev, false)`。这使测试的离屏/readback 工作不再依赖默认帧缓冲的 Wayland vsync 回调进度。

真实 gdb 卡点栈确认主线程等待路径为：

`draw_and_count` → `rhi_present` → `gl_present` → `eglSwapBuffers` → Mesa `dri2_wl_swap_buffers_with_damage` → `loader_wayland_dispatch` → `wl_display_poll` → `ppoll`。

同一未修二进制、同一受控 Wayland 环境下，默认设置 3 秒超时，`vblank_mode=0` 则在 107 ms 内完成全部 4 个 case。修复后不依赖该环境变量，在同一环境 96 ms 完成全部 4 个 case。临时令生产 `gl_set_vsync` 无视关闭请求后，修复后的测试重新在 3 秒超时被捕获；生产文件随即精确恢复并再次通过。

重要边界：输入给出的原始现象是普通原生 Wayland 下 text OK 后、image 统计前 60 秒超时。本轮普通桌面会话中，未改源码基线没有再次自然复现；本报告没有伪造原现场栈。实际栈来自原生 headless Mutter 的 0.01 Hz 虚拟显示器，它确定性地放大同一 Mesa/Wayland back-buffer 等待。受控 RED 停在 text 首个 case 内，与原随机失败的进度位置不同，报告和状态页均明确保留这一差异。

## 2. 环境与构建身份

初始环境：

```text
XDG_SESSION_TYPE=wayland
WAYLAND_DISPLAY=wayland-0
XDG_RUNTIME_DIR=/run/user/1000
DISPLAY=:0
```

所有本任务图形测试均使用 `env -u DISPLAY`，不使用 X11。受控 compositor 使用 `mutter --headless --wayland --no-x11`，也未启动 Xwayland。

构建目录：

- `build-remove-x11-auto`：名称虽有 `auto`，实际 cache 为 `ENGINE_RHI_BACKEND=opengl`、`ENGINE_RHI_BACKEND_EFFECTIVE=opengl`、`ENGINE_RHI_MULTI_BACKEND_ACTIVE=OFF`，Debug，带调试信息。
- `build-remove-x11-vk`：`ENGINE_RHI_BACKEND=auto`、`ENGINE_RHI_BACKEND_EFFECTIVE=vulkan`、multi-backend active，默认选择 Vulkan。
- 配置变量是 `ENGINE_RHI_BACKEND`；multi-backend 的运行时选择变量是 `BREAK_RHI_BACKEND`。一次探测中把 `ENGINE_RHI_BACKEND=opengl` 当作环境变量传给 multi-backend 二进制，日志确认仍选择 Vulkan，因此没有把该次运行当作 OpenGL 证据。

实际设备：

- OpenGL：`OpenGL 4.6 (Core Profile) Mesa 26.2.5`，renderer 为 `Intel / Mesa Intel(R) UHD Graphics (TGL GT1)`。
- 默认 Vulkan：`NVIDIA RTX A5000 Laptop GPU`，`backend_selected` 的 reason 为 `platform-default`，swapchain 为 `MAILBOX` / `vsync=off`。

## 3. 输入原始失败

任务输入提供的 BASE 复现：

```text
ENGINE_RHI_BACKEND=opengl + 原生 Wayland
test_myui_break_rhi_clip
text_respects_the_clip_rect ... OK
image_respects_the_clip_rect ...（统计输出前阻塞，CTest TIMEOUT=60s）
```

测试的 `draw_and_count` 每轮依次执行 `rhi_frame_begin`、离屏 FBO 绘制、`rhi_frame_end`、`rhi_texture_read_pixels`、`rhi_present`；text 与 image 各调用 3 轮。测试没有平台 event poll，也没有关闭 vsync。所有 present/readback 和像素断言在修复中保留。

## 4. 普通 Wayland 基线调查：原随机超时未再次自然复现

先在指定 HEAD、干净工作树上构建并运行：

```bash
cmake --build build-remove-x11-auto -j3 --target test_myui_break_rhi_clip
env -u DISPLAY -u vblank_mode \
  ctest --test-dir build-remove-x11-auto \
  -R '^test_myui_break_rhi_clip$' --output-on-failure
```

结果：通过，0.22 s，4/4。

进一步调查：

- 普通原生 Wayland 直接运行 10 次，每次外部 `timeout 5s`：全部 rc=0、4/4，未出现超时。
- 保留原 `DISPLAY=:0` 但二进制仍走原生 Wayland 的 CTest 交叉检查：0.22 s 通过；最终证据不依赖此配置，后续全部显式移除 `DISPLAY`。
- 未修源码执行 OpenGL `-L graphics -j3`：7/7 通过，clip 0.21 s。
- 未修源码执行 100 次 attach-watch：每次若存活到 1.5 s 就自动 gdb attach 并清理；100 次都在 1.5 s 前 rc=0，故没有 attach，也没有遗留进程。
- 普通 60 Hz headless Mutter（`--no-x11`）下基线也通过。
- GTK 遮挡/全屏诊断没有产生超时，未作为根因证据。

普通桌面下 `vblank_mode=1` 与 `vblank_mode=0` 也都通过，因此普通会话 A/B 本身不能区分根因。此时没有直接套用建议修改，而是继续构造能取得真实等待栈的 Wayland 条件。

## 5. 受控 RED 与真实卡点栈

### 5.1 受控条件

使用 Mutter 50.6 的原生 Wayland headless 虚拟显示器：

```bash
mutter --headless --wayland --no-x11 \
  --wayland-display=clip-slow \
  --virtual-monitor=640x480@0.01
```

待 `/run/user/1000/clip-slow` socket 就绪后，运行未修二进制：

```bash
env -u DISPLAY -u vblank_mode WAYLAND_DISPLAY=clip-slow \
  stdbuf -o0 -e0 ../build-remove-x11-auto/test_myui_break_rhi_clip &
pid=$!
# 确认 5 秒后仍存活
gdb -q -batch -ex 'set pagination off' \
  -ex 'thread apply all bt' -p "$pid"
```

Mutter 日志确认：

```text
Running Mutter (using mutter 50.6) as a Wayland display server
Added virtual monitor Meta-0
Using Wayland display name 'clip-slow'
```

测试输出停于：

```text
Platform initialized (Wayland): 64x64 "myui break rhi clip"
OpenGL 4.6 (Core Profile) Mesa 26.2.5 initialized
=== Running Tests ===
  [1] text_respects_the_clip_rect ...
```

### 5.2 主线程完整相关栈

```text
#0  __syscall_cancel_arch () from /lib64/libc.so.6
#1  __internal_syscall_cancel () from /lib64/libc.so.6
#2  __syscall_cancel () from /lib64/libc.so.6
#3  ppoll () from /lib64/libc.so.6
#4  wl_display_poll () from /lib64/libwayland-client.so.0
#5  wl_display_dispatch_queue_timeout () from /lib64/libwayland-client.so.0
#6  wl_display_dispatch_queue () from /lib64/libwayland-client.so.0
#7  loader_wayland_dispatch () from /lib64/libEGL_mesa.so.0
#8  dri2_wl_swap_buffers_with_damage () from /lib64/libEGL_mesa.so.0
#9  dri2_swap_buffers () from /lib64/libEGL_mesa.so.0
#10 eglSwapBuffers () from /lib64/libEGL_mesa.so.0
#11 gl_present (dev=0x35a5f210)
    at engine/src/rhi/rhi_gl.c:1061
#12 rhi_present (dev=0x35a5f210)
    at engine/src/rhi/rhi_gl.c:1436
#13 draw_and_count (kind=DRAW_TEXT, ...)
    at engine/tests/test_myui_break_rhi_clip.c:87
#14 check (kind=DRAW_TEXT)
    at engine/tests/test_myui_break_rhi_clip.c:112
#15 test_text_respects_the_clip_rect ()
    at engine/tests/test_myui_break_rhi_clip.c:174
#16 main ()
    at engine/tests/test_myui_break_rhi_clip.c:272
```

其余 4 个 Mesa worker 线程均在 `pthread_cond_wait` → `cnd_wait` → `util_queue_thread_func`，不是主线程卡点。gdb 成功 detach。测试进程和 Mutter 均由 trap 先 TERM、必要时 KILL 并 `wait`，socket/lock 也清理。

结论：栈明确位于 `eglSwapBuffers` 的 Mesa Wayland 分发/等待路径，不在 `glClear`、texture readback 或像素统计循环。允许进入“只在该测试显式关闭 vsync”的修复阶段。

## 6. 无源码 A/B

同一 0.01 Hz Mutter、同一未修二进制，分别运行：

```bash
env -u DISPLAY -u vblank_mode WAYLAND_DISPLAY=clip-ab \
  timeout 3s stdbuf -o0 -e0 \
  ../build-remove-x11-auto/test_myui_break_rhi_clip

env -u DISPLAY WAYLAND_DISPLAY=clip-ab vblank_mode=0 \
  timeout 3s stdbuf -o0 -e0 \
  ../build-remove-x11-auto/test_myui_break_rhi_clip
```

结果：

```text
default:      rc=124, elapsed_ms=3010，停在 text 首个 case
vblank_mode=0: rc=0,   elapsed_ms=107，4 passed / 0 failed / 4 total
```

`vblank_mode=0` 运行中的统计和断言保持：

```text
text:  unclipped=212 clip-outside=0 clip-left-half=63  (outside 0)
image: unclipped=256 clip-outside=0 clip-left-half=128 (outside 0)
order: left=ff0000 right=ffffff
unorm 188 -> 188, srgb 188 -> 128
```

这把真实栈与 swap interval 联系起来，而不是仅凭“可能节流”猜测。

## 7. 最小修复（RED → GREEN）

最终测试 diff：

```diff
@@ -260,6 +260,7 @@ int main(void) {
         platform_destroy(g_platform);
         return 77;
     }
+    rhi_set_vsync(g_dev, false);
     for (i = 0; i < sizeof(k_fonts) / sizeof(k_fonts[0]) && g_font == NULL; i++) {
```

位置：`engine/tests/test_myui_break_rhi_clip.c:263`。没有新增 helper，没有改生产 API 或默认值。

### 7.1 普通原生 Wayland 连续 3 次

构建：

```bash
cmake --build build-remove-x11-auto -j3 --target test_myui_break_rhi_clip
```

连续执行 3 次：

```bash
env -u DISPLAY -u vblank_mode \
  ctest --test-dir build-remove-x11-auto \
  -R '^test_myui_break_rhi_clip$' --output-on-failure -V
```

结果：

- run 1：4/4，CTest 0.10 s。
- run 2：4/4，CTest 0.09 s（总墙钟 0.10 s）。
- run 3：4/4，CTest 0.09 s（总墙钟 0.10 s）。

每次都实际完成 text、image、painter order、sRGB 四个 case，没有跳过 text 字体，也没有把统计或断言删掉。

### 7.2 同一受控慢 Wayland GREEN

不设置 `vblank_mode`，使用同样的 `640x480@0.01` Mutter：

```text
fixed controlled slow-Wayland rc=0 elapsed_ms=96
=== Results: 4 passed, 0 failed, 4 total ===
```

这证明修复自身有效，不是依赖外部环境变量。

## 8. 临时生产变异：确认测试能捕获

临时改动 `engine/src/rhi/rhi_gl.c`：

```diff
-    eglSwapInterval(gl->egl_display, enabled ? 1 : 0);
+    eglSwapInterval(gl->egl_display, 1);
+    (void)enabled;
```

含义：即使测试调用 `rhi_set_vsync(g_dev, false)`，生产代码仍强制 FIFO/vsync。

重建目标后，在同一 0.01 Hz 环境执行修复后的测试，外部 timeout 缩短为 3 秒：

```text
[1] text_respects_the_clip_rect ...（阻塞）
vsync mutation controlled run rc=124 elapsed_ms=3006 (expected 124)
```

因此测试能捕获生产“关闭 vsync 请求失效”的行为。随后立即把两行精确恢复为原来的单行，重新构建：

- 受控 0.01 Hz：rc=0，4/4。
- 普通 Wayland CTest：rc=0，4/4，0.10 s。
- `git diff --exit-code -- src/rhi/rhi_gl.c`：rc=0，生产文件最终 diff 为空。

变异没有进入提交。

## 9. 最终构建和 graphics 回归

### 9.1 构建

```bash
cmake --build build-remove-x11-auto -j3
cmake --build build-remove-x11-vk -j3
```

两者均 exit 0。`build-remove-x11-vk` 自动重新 configure，仍确认 requested=`auto`、effective=`vulkan`、multi-backend。链接仍出现项目既有 Lua `tmpnam` 警告，本任务未处理。

### 9.2 OpenGL graphics

```bash
env -u DISPLAY -u vblank_mode \
  ctest --test-dir build-remove-x11-auto \
  -L graphics --output-on-failure -j3
```

结果：7/7，0 失败，总墙钟 3.74 s。

通过项：

- `test_mesh_gpu_gl`
- `test_rhi_wayland_runtime`
- `test_world_presentation_gl`
- `test_mypal_wayland`
- `test_myui_break_rhi_clip`（0.11 s）
- `test_vulkan`（该 GL 构建的通用图形测试）
- `rhi_swapchain_bench`

实际 renderer：Mesa 26.2.5 / Intel UHD Graphics (TGL GT1)。`UNAVAILABLE` 为 0，CTest skip 为 0。`test_vulkan` 内仍有子项日志：acceleration-structure lifecycle unsupported、one-triangle BLAS size query unsupported、DLSS probe 未启用；这些不是 CTest skip，也不是本任务新增失败。

### 9.3 默认 Vulkan graphics

```bash
env -u DISPLAY -u vblank_mode \
  -u BREAK_RHI_BACKEND -u BREAK_RHI_NO_FALLBACK -u BREAK_RHI_FAIL_VULKAN \
  ctest --test-dir build-remove-x11-vk \
  -L graphics --output-on-failure -j3
```

结果：11/11，0 失败，总墙钟 13.48 s。

通过项：

- `test_vulkan`
- `test_world_presentation_vk`
- `rhi_swapchain_bench`
- `test_myui_break_rhi_clip`（4/4）
- `test_rhi_push_offset_dump`
- `test_rhi_vk_alloc_fault`
- `test_world_presentation_gl`
- `test_mypal_wayland`
- `test_rhi_runtime_fallback_forced`
- `test_rhi_runtime_fallback_env_opengl`
- `test_rhi_runtime_fallback_default`

默认 clip、`test_vulkan` 和 Vulkan world presentation 均实际选择 NVIDIA RTX A5000 Laptop GPU / `platform-default`。套件的显式 OpenGL/fallback 项也实际走 Mesa Intel。`UNAVAILABLE` 为 0，CTest skip 为 0。Vulkan 内仍有 ray-query、RT-trace、DLSS 子项 SKIP 日志，未将这些可选探针虚称执行。

范围外现存诊断：日志共有 16 个 `VK VALIDATION:` 前缀，其中 10 个来自 `test_rhi_push_offset_dump` 的 vertex attribute 未消费警告，6 个来自 clip sRGB image/image-view 的 storage-usage 诊断。clip 的 6 个在未修默认 Vulkan 基线已经看到；本任务未修改相关生产代码，也未把这些诊断包装成不存在。

## 10. 最终文件、清理与未覆盖边界

最终修改/新增：

- `engine/tests/test_myui_break_rhi_clip.c`：一行测试局部 vsync 设置。
- `docs/Implementation_Status.md`：顶部追加本轮根因、证据和限制，历史记录原样保留。
- `.superpowers/sdd/2026-11-10-remove-x11/clip-fix-report.md`：本报告。

临时 touch 过但已精确恢复、最终 diff 为空：

- `engine/src/rhi/rhi_gl.c`（仅强制 vsync 变异及恢复）。

所有诊断源码均为 shell/Python 命令行，没有在工作树新增辅助测试或脚手架。临时日志位于 `/tmp/clip-fix-debug`，整理证据后删除；构建输出仍位于既有 ignored build 目录。未合并、未 push。

保留边界：

1. 普通桌面的原始随机 60 秒超时本轮未再次自然复现；取得的是受控 0.01 Hz 原生 Wayland 下同一路径的真实栈。因此可确认并修复 vsync/back-buffer 等待机制，但不声称掌握原随机场合中 compositor 停止及时回调的上游原因。
2. Vulkan validation、可选子项 SKIP 和 Lua 链接警告仍在，均非本任务范围。
3. 验证仅在本机原生 Wayland、Mesa Intel OpenGL 与 NVIDIA Vulkan 上完成；未使用 X11，未声称其它 compositor/GPU/平台通过。
