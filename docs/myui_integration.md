# myui 集成与 Break RHI 后端

本文描述 `engine/src/myui`、`engine/external/SheenBidi` 和
`engine/apps/duanxianxia` 如何接入 Break 引擎的 `Platform` 与 `RHI`。

## 目标

- 复用 `myui` 的 widget、窗口、MVVM、Bidi/断行、字体和图像加载能力。
- 不绑定特定 OS 窗口或 GL/Vulkan API：所有后端统一通过 `Platform` 与 `RHI`。
- 在 GL 和 Vulkan 上使用同一套 CPU 三角化和双缓冲动态 VBO 路径。
- 用可测试的桥接层隔离平台输入、IME 与渲染后端。

## 冷却按钮

按钮冷却是 widget 层能力，不依赖 Break RHI、OpenGL、Vulkan 或软件 canvas 的私有类型：

```c
my_button_set_cooldown(button, 1500);
if (!my_button_is_cooling_down(button)) {
    /* 可选：显示或启用业务操作 */
}
```

成功 click 后按钮保存 PAL 提供的单调 deadline。冷却期间 pointer down/up 被拒绝且不
产生 `click`；查询接口实时检测 deadline，因此 timer 丢失、主循环暂时停顿或窗口未
挂载都不会绕过限制。按钮只在冷却期间启用一个 16ms timer，timer tick 触发局部
invalidate，绘制通过公共 `my_vgcanvas_fill_rect()` 输出半透明进度遮罩。冷却完成后
timer 自动停止，按钮销毁流程、`my_button_set_cooldown(button, 0)` 也会移除它。

动画不参与业务判定：帧率、timer 抖动、GL/Vulkan 提交延迟只影响遮罩刷新，不影响
deadline。所有后端都获得同一输入和视觉契约；不支持透明混合的后端仍执行公共绘制，
由该后端的颜色语义处理，不引入 shader 分支。

集成基线是上游 `myui` commit `676bfd10f96992a3efa100d67118690063c279cf`。
上游源码以 vendored 形式置于本仓库，平台与 RHI 适配层只在 `mypal/break`、
`myr/my_vgcanvas_break_rhi.c` 和 `src/ui/myui_break*` 中实现，避免把 Break API
反向泄漏到 widget、MVVM 或文本排版核心。

## 目录

```text
engine/
├── external/SheenBidi/            # BiDi + Arabic shaping
├── src/myui/
│   ├── mypal/break/               # Break PAL adapter
│   ├── myr/my_vgcanvas_break_rhi.c # Break RHI vgcanvas backend
│   └── ...                        # myui core
├── src/ui/
│   ├── myui_break.h/c             # BreakUI 应用桥
│   └── myui_break_input.h/c       # Platform key -> myui key
├── apps/duanxianxia/
│   ├── dxx_app.h/c                # 可复用的 dxx 首页组合
│   └── dxx_break_main.c           # Break RHI 可执行入口
└── shaders/ui_img*                # RHI UI image pipeline
```

## CMake 目标与选项

| 目标 | 说明 |
|------|------|
| `myui_core` | myui 核心静态库，包含 font/image/xml/bidi/mvvm/widget 子系统 |
| `break_myui` | `my_pal_break` + RHI vgcanvas + `BreakUI` 桥 |
| `dxx_core` | duanxianxia 视图构建器 |
| `dxx_break` | Break-aware duanxianxia demo |

| 选项 | 默认 | 说明 |
|------|------|------|
| `MYUI_FONT_STB` | ON | stb_truetype 字体后端 |
| `MYUI_FONT_FREETYPE` | ON（找到 FreeType 时） | 启用 hinting、TTC 多字面和 CJK 默认字体 |
| `MYUI_IMAGE_STB` | ON | stb_image 解码 |
| `MYUI_UI_XML` | ON | XML UI loader |
| `MYUI_BIDI` | ON | 内置 SheenBidi |

## 构建与测试

```bash
# OpenGL
cmake -S engine -B build-myui -DENGINE_BUILD_TESTS=OFF
cmake --build build-myui --target dxx_break break_myui myui_core dxx_core -j

# Vulkan
cmake -S engine -B build-myui-vk -DENGINE_BUILD_TESTS=OFF -DENGINE_VULKAN=ON
cmake --build build-myui-vk --target dxx_break break_myui -j

# Headless myui 单元测试
cmake -S engine -B build-myui-tests -DENGINE_BUILD_TESTS=ON -DENGINE_VULKAN=OFF
cmake --build build-myui-tests -j
ctest --test-dir build-myui-tests -R 'test_break_ui_input|test_myui_vggeometry|test_myui_window_manager|test_myui_font' --output-on-failure

# Wayland + OpenGL
cmake -S engine -B build-myui-wayland -DENGINE_ENABLE_WAYLAND=ON -DENGINE_BUILD_TESTS=ON
cmake --build build-myui-wayland --target dxx_break -j

# Wayland + Vulkan
cmake -S engine -B build-myui-wayland-vk -DENGINE_ENABLE_WAYLAND=ON -DENGINE_VULKAN=ON -DENGINE_BUILD_TESTS=OFF
cmake --build build-myui-wayland-vk --target dxx_break -j
```

运行 `dxx_break`：

```bash
./build-myui/dxx_break          # OpenGL
./build-myui-vk/dxx_break       # Vulkan
```

默认字体候选会优先选择系统的简体中文 CJK 字体：Linux 为 Noto Sans CJK SC（TTC 第
`2` 面）、Windows 为微软雅黑/宋体、macOS 为苹方。FreeType 可用时会正确加载 TTC
中的目标面并使用字形 hinting；若 CMake 未找到 FreeType，则只支持独立 TTF/OTF 的
`stb_truetype` 回退，不能正确解析 Noto 的可变 TTC。

可用 `BREAK_MYUI_FONT=/path/to/font.ttf` 覆盖默认字体；当覆盖文件是 TTC 时，配合
`BREAK_MYUI_FONT_FACE=<non-negative-index>` 选择面（例如 Linux Noto Sans CJK SC 为
`2`）。覆盖 TTC 需要启用 `MYUI_FONT_FREETYPE`。着色器搜索顺序为当前目录、`engine/`、
`../engine/`、`../../engine/`，也可用 `BREAK_SHADER_DIR` 指向引擎根目录。

## 桥接结构

### Break PAL (`my_pal_break`)

包装已有 `Platform *` 和 `RHIDevice *`：

- 布局尺寸来自 `platform_get_logical_size()`；RHI device、swapchain、viewport 和
  BreakUI offscreen surface 使用 `platform_get_drawable_size()`。旧
  `platform_get_size()` 仅保留为平台原生事件单位兼容接口，不能再传给 RHI。
- `platform_get_content_scale()` 描述逻辑坐标到 drawable 像素的内容缩放；
  `platform_get_input_scale()` 描述平台输入坐标归一化到 myui 逻辑坐标所需的除数。
  X11/Win32 输入为物理像素，除数等于内容缩放；Wayland/Cocoa 输入已经是逻辑点，除数为 1。
- 即时调试 UI 同样遵循这条边界：布局和 hit-test 使用 logical 尺寸及已归一化的鼠标，
  `my_vgcanvas_break_rhi` 目标和 RHI compositing 使用 drawable 尺寸，并由 canvas scale
  将逻辑几何转换为物理像素。
- IME spot 转发至 `platform_ime_set_spot`。
- OpenGL 使用 `platform_window_native`，引擎 Vulkan 使用 `platform_surface_native`。
  Wayland 中前者是 `wl_egl_window`，后者是 `wl_surface`，不能交叉传给 RHI。
- Break PAL 不实现 `my_pal_window_vk_create_surface`：该可选接口要求返回由 myui
  私有 `VkInstance` 创建的 `VkSurfaceKHR`，而 BreakUI 已经复用宿主 RHI 的 device、
  swapchain 和 offscreen surface。返回 native handle 会违反 API 所有权与类型契约。
- timer 使用 `time_microseconds() / 1000`。
- 多个 myui 逻辑窗口共享一个 Break OS window、一个 RHI vgcanvas 和一次合成提交；
  root window 是唯一允许请求原生窗口拖动的窗口，dialog 的移动保持在共享表面坐标内。
- posted event 队列是带原子锁的 O(1) FIFO，不会因 burst 事件产生 `darray_remove_at(0)`
  的 O(n^2) 移动成本。
- `break_loop_run()` 是嵌入式 PAL 的 drain 操作：没有已排队事件或到期 timer 时立即返回，
  不负责阻塞等待，也不调用 OS `platform_poll()`。独立宿主必须在自己的每帧循环中按
  `platform_poll()` -> `break_ui_pump()` -> `rhi_frame_begin/render/end/present` 顺序驱动。

### Clipboard

`clipboard_get_text_alloc` 是控件使用的完整文本接口：调用方以其 myui allocator
释放返回值，因此 edit/text-area 不再受早期 `256`/`4096` 字节临时缓冲限制。粘贴使用
一次过滤、一次文档插入和一条 undo 记录，避免逐字符重分配的 O(n^2) 行为。

- Windows 使用 `CF_UNICODETEXT`；Cocoa 使用 `NSPasteboardTypeString`，二者同步读取。
- X11 使用 `CLIPBOARD`/`UTF8_STRING`/`TARGETS`，含 `INCR` 分块传输；读取永不等待
  外部 owner。Wayland 使用 `wl_data_device` 和非阻塞 pipe，读取同样由 `platform_poll`
  增量推进，最多缓存 16 MiB。
- 外部 X11/Wayland selection 的第一次 `Ctrl+V` 返回 `MY_RET_PENDING` 并由控件的 10 ms
  临时 timer 自动完成；无需用户再次按键。失焦或销毁会取消 timer。
- 旧有有界 `clipboard_get_text` 保留给兼容调用方；新的控件路径使用分配式接口。

### 文本事件边界

所有平台的 commit/preedit/delete 事件先进入 `PlatformTextQueue`，再由 `BreakUI` 消费：

- `PlatformTextEvent` 为不超过 64 字节的常见文本保留内联存储，超出部分由事件独占
  `utf8_extra`；出队后所有权转移给调用方，调用方必须调用
  `platform_text_event_destroy()`。
- 单个 UTF-8 事件最多 16 MiB，队列 payload 最多 32 MiB、最多 4096 个事件；超出预算、
  分配失败或平台查询失败时丢弃该事件，不阻塞窗口线程。相邻 preedit 更新合并为最后一条，
  避免 IME 高频更新造成无效排队和内存增长。
- 队列是环形 FIFO，出队不搬移剩余事件；平台销毁时通过
  `platform_text_queue_destroy()` 释放未消费文本。新增平台消费者也必须遵守这套所有权规则。
- UTF-16 平台（Win32/Cocoa）按实际 UTF-8 输出计长，不因最坏情况 3/4 倍临时缓冲而拒绝
  大段 ASCII 文本；非法 surrogate 使用 U+FFFD 替换。

### BreakUI (`myui_break`)

应用通常使用：

```c
BreakUI *ui = break_ui_create();
break_ui_init(ui, platform, device, font_path, w, h);
break_ui_pump(ui);
break_ui_render(ui, cmd, w, h);
my_window_t *win = break_ui_get_window(ui);
```

`break_ui_pump` 将 `InputState` 翻译为 myui 的 pointer/key/IME 事件；
设置 window manager 后通过 `my_window_manager_on_pal_event` 路由，支持模态对话框规则。

### RHI vgcanvas (`my_vgcanvas_break_rhi`)

- 统一输出 myui font-vertex 布局：`x,y,u,v,r,g,b,a`。
- `1024x1024` RGBA glyph atlas，仅在脏时上传 mip 0；可容纳完整中文页面的
  千级不同字形，避免滚动后因图集耗尽而丢字。
- GLES/OpenGL 与 Vulkan 的 direct-mapped glyph cache 均使用
  `(font_identity, codepoint, device_font_size)` 作为命中条件；切换字体后即使字符和字号
  相同，也会重新上传字形纹理，不会显示上一字体的字形。canvas 只借用 `my_font_t *`，
  应用必须保证字体存活到 canvas 销毁或不再使用该字体之后。
- solid/image 分别使用双缓冲动态 VBO（按 `rhi_frame_index` 选择）。
- 路径和圆角矩形由共享 `my_vggeometry` CPU 三角化。
- OpenGL 使用 `font.vert/frag` + `ui_img.vert/frag`。

BreakUI 的 AA 设置通过 `break_ui_set_antialias_level()` 进入事务边界。请求不会在
widget paint 回调中销毁或替换当前 FBO；canvas 只记录 pending level，BreakUI 在下一次
render 边界创建候选 `RHIOffscreenFBO`，创建成功后再激活并回收旧目标。候选创建失败时
旧目标、尺寸和当前质量保持不变。level `0` 使用 1x，level `2` 在设备同时支持 color/
depth sample count 与 resolve 时使用 2x；旧 RHI 创建 API 仍固定 1x。
- Vulkan 使用 `font_vk.vert/frag` + `ui_img_vk.vert/frag`。

可选 OpenType shaping 通过 `my_font_shape()` 暴露为后端中立的 glyph run：每个 glyph 携带
font glyph id、UTF-8 byte cluster 和 26.6 fixed-point advance/offset。只有启用
`MYUI_HARFBUZZ`、FreeType 与 HarfBuzz 均可用的直接 FreeType face 支持该接口；bitmap、stb
以及 fallback chain 返回 `MY_RET_NOT_SUPPORTED`。当前 Break RHI、GLES、Vulkan 和 soft
canvas 的纯 LTR 路径已通过独立 `my_font_get_glyph_id()` raster API 消费 glyph run；四个
后端的 glyph cache 均把 font pointer、glyph/codepoint 数值、key 类型和字号作为键，避免把
glyph id 当作 Unicode codepoint 或发生缓存串线。shaping 失败时回退旧 codepoint 路径。当前
RTL 仍使用 UBA/Arabic fallback，fallback chain 仍不伪装支持跨 face 的完整 OpenType shaping。

### Canvas 能力契约

控件只能通过 `my_vgcanvas.h` 的公共接口配置 canvas，不得把某个后端的
`my_vgcanvas_*_set_*` 函数用于通用绘制路径。窗口在创建、切换 GPU 后端和注入
canvas 时统一应用 DPI scale 与当前字体，因此软件、GLES/OpenGL、Vulkan 和嵌入式
Break RHI 路径不会再因创建分支不同而出现字号或坐标不一致。

| 能力 | 软件 | GLES/OpenGL | Vulkan | Break RHI |
|------|------|-------------|--------|-----------|
| `my_vgcanvas_set_scale` | 支持 | 支持 | 支持 | 支持 |
| `my_vgcanvas_set_antialias_level` | 覆盖率 AA（0-2） | 0/非 0 映射 MSAA | `MY_RET_NOT_SUPPORTED` | `MY_RET_NOT_SUPPORTED` |
| `my_vgcanvas_set_scale_filter` | nearest/bilinear | nearest/bilinear | nearest/bilinear | nearest/bilinear |

### Offscreen target 与 MSAA 边界

Break RHI 的 `RHIOffscreenFBODesc` 是跨后端 target 描述，不暴露 OpenGL/Vulkan 类型。
`sample_count == 0` 表示兼容旧行为的 `1x`；旧的 `rhi_offscreen_fbo_create*()` API
始终创建 `1x`，避免升级后改变已有后处理链路。descriptor 在进入后端前会检查尺寸、
格式、power-of-two sample count、颜色样本能力及 resolve 能力，非法请求返回空 target。

OpenGL 的 `2x+` target 使用 multisample color/depth renderbuffer，另建单采样 color/depth
texture 供采样；离开 target 或切换 target 时执行一次 resolve，避免绘制过程中反复 resolve。
`RHIOffscreenFBO.color_tex` 和 `depth_tex` 始终指向可采样的单采样结果。

Vulkan 的 `2x+` target 使用 multisample color/depth image 和单采样 color/depth resolve
image；render pass 通过 depth-stencil resolve 完成 resolve，pipeline 按颜色格式和 sample
count 建立兼容 variant。`color_tex/depth_tex` 始终指向可采样的单采样 resolve 结果，MSAA
attachment 由 FBO 内部持有。设备必须同时支持 color/depth sample count 和至少一种 depth
resolve mode，否则返回空 target，不静默降级。旧的 `rhi_offscreen_fbo_create*()` API 仍固定
创建 `1x`；Vulkan shadow/MRT pipeline 的 `sample_count > 1` 当前明确拒绝。

图像过滤是 canvas 状态的一部分，默认值为 bilinear。GLES/OpenGL 的图像纹理缓存键为
`(rgba 指针, width, height, filter)`，避免同一位图在两种过滤模式间错误复用；没有扩展
回调的旧 GL 适配仍回退到原始 RGBA 上传接口。Vulkan 使用共享的 linear/nearest sampler，
并把 sampler 写入对应的 descriptor；字形 atlas 始终使用 linear。Break RHI 同样创建两种
sampler，并按 `(texture, sampler)` 划分 image batch，避免每个图像 quad 创建资源。公共
`my_vgcanvas_draw_image()` 调用方必须在缓存可能命中期间保持 bitmap 内容不变；需要更新
像素时应提供新的稳定 buffer identity，或主动让 canvas 生命周期结束。`my_image` 解码
缓存满足该生命周期要求。`ztpool` 的 PNG 分享导出是显式离屏软件渲染任务，因而保留
`my_vgcanvas_soft_create` 依赖；它不参与窗口的后端选择，也不会把软件 canvas 传给
GPU 控件路径。

### 能力盘点与阶段计划

本轮已经打通并由 TDD 锁定的能力包括：固定列 Grid 布局、文本编辑缓冲区容量倍增、
软件/GLES/OpenGL/Vulkan/Break RHI 的 nearest/bilinear 图像过滤、Mono 目标的 4x4
ordered dithering、MVVM 的 items 和 condition 绑定，以及文本布局的 UBA L4 镜像、
Arabic joining 和 mandatory Lam-Alef 覆盖映射。布局参数解析同时拒绝负数、非有限数和
超出 `int32_t`/百分比范围的输入；Grid、framebuffer stride、UTF-32/UTF-8 缓冲区和文本
逻辑/视觉索引的乘法与边界均经过溢出保护。CSS 已支持 universal selector、多 class
selector、typed direct-child selector，以及按 selector specificity 和 source order 的
cascade；普通规则在 hover/pressed/disabled 查询时保留 normal-slot 的 specificity。数值
解析拒绝孤立符号、非有限值和超出 `int32_t` 的整数，不会把恶意输入转换成未定义的资源
尺寸或颜色值。软件开放 contour fill 会按 fill 语义自动闭合，开放 stroke 仍保留端点语义。
结构错误会拒绝加载，不会静默生成错误主题。

仍未实现或明确保留为后续阶段的能力如下：

| 范围 | 当前边界 | 后续方案 |
|------|----------|----------|
| GPU AA | Break RHI 的 `RHIOffscreenFBODesc` 已支持按设备能力创建真实 2x+ target；Vulkan/Break RHI 的 `set_antialias_level` 仍未承诺动态窗口级协商 | 将已完成的 target 创建接入窗口级事务；沿用 `create -> validate -> submit -> activate -> retire`，失败时保持旧 target，不静默改变质量 |
| 复杂 RTL | 已支持单段落 UBA 重排、L4 镜像、Arabic joining 和 mandatory Lam-Alef；paragraph 已提供 cluster-safe 逻辑换行并接入 text area；完整 RTL GSUB、跨 face run、多段落增量 rebreaking 仍未实现 | 增加 RTL shaping run、段落级 visual mapping 和 line-break model，先以 golden 字形/视觉顺序测试锁定契约，再接入 RTL canvas |
| 编辑器 | 行号、代码折叠、增量语法高亮等高级编辑器能力未实现；wrap cache 已采用 OOM-safe candidate swap | 单独的 virtualized line model，限制单帧重排预算，避免把大文档编辑路径耦合到 widget 绘制 |
| 图像 | Mono 使用固定成本 4x4 ordered dithering；误差扩散和更高位深量化未实现 | 保持当前有界、可预测的 dither 路径；仅在实测收益明确时增加其他量化策略 |
| Present | 共享 offscreen surface 仍执行一次全屏 composite，未实现真正的局部 present | 先按平台确认 damage/partial-present 语义，再以 dirty region 合并和带宽阈值选择局部或全屏提交 |
| Vulkan readback | 窗口路径 readback 有意不支持，避免把 WSI 资源强制改为可传输并引入同步开销 | 仅为离屏截图提供显式 readback API，使用 staging buffer、fence 和尺寸上限 |
| CSS/XML | CSS 仍是受限子集：后代选择器只支持单级 typed ancestor，复杂 combinator 和完整 at-rule 语义仍未实现；未知 at-rule 会跳过并告警。selector specificity、source order 和数值边界已实现 | 建立 capability registry 和严格诊断模式；扩展语法时保持结构错误可诊断、运行期不破坏已构建树 |
| 平台 | Windows/macOS 及未启用的 GLES/Vulkan/Wayland 构建路径缺少本机 CI runtime | 保持公共接口无平台类型泄漏；在对应 runner 上增加 build、启动烟测和 HiDPI/输入/IME 矩阵 |

实施原则：先写跨后端契约测试，再实现各 backend adapter；所有候选 GPU 资源采用“创建、
验证、提交、激活、回收”的状态转换，失败保留旧资源。当前通用事务实现位于
`engine/src/myui/myr/my_vgcanvas_quality_transaction.h` 和
`engine/src/myui/myr/my_vgcanvas_quality_transaction.c`，其能力 mask 仅接受幂次样本数，
并把 resize 与 sample-count 放在同一次提交中。RHI 的 `rhi_device_get_capabilities()` 只读
返回设备能力，不能替代 target/render-pass 的兼容性验证。缓存键必须包含影响结果的状态，输入长度、
索引乘法和行列尺寸必须在分配前检查，绘制线程不等待外部平台协议。这样可把性能优化
（缓存、批处理、增量布局）限制在不牺牲安全和可恢复性的范围内。

本轮定向 TDD 门禁为：`test_rhi_capabilities`（2/2）、`test_myui_css`（14/14）、
`test_myui_text_layout`（4/4）、
`test_myui_vgcanvas_backend`（21/21）和 `test_break_ui_damage`（14/14）。其中 CSS 用例覆盖
universal、多 class、direct-child、specificity fallback、数值边界
和 malformed selector；文本用例覆盖 RTL visual mapping、Lam-Alef logical span 和选区；
backend 用例覆盖缩放、过滤、字体缓存隔离、开放 contour fill、Mono dither、framebuffer
尺寸/stride 溢出、能力查询、AA 支持/拒绝、失败回滚和幂等请求；damage 用例覆盖共享
surface 的结构/布局失效、失败回滚和逻辑到 drawable scissor 的向外取整与裁剪。
窗口 GPU 切换还会以 PAL 已协商的 multisample 状态覆盖 GL 查询结果，避免把驱动默认值
误当成 surface 能力。

Floating widget 的绘制与命中语义也分离：`floating=true` 且没有 `on_event` 的普通控件
是 paint-only overlay，不会吞掉其下方控件的 pointer hit-test；带 `on_event` 的浮层仍按
顶层交互控件处理。普通 `my_widget_create()` 控件允许保持 NULL vtable。

### 窗口状态机与尺寸边界

窗口把布局和渲染尺寸分成两个明确的单位：

- `my_pal_window_get_size()`、`MY_EVENT_RESIZE` 和 widget 矩形使用逻辑像素。
- `my_pal_gl_get_size()` 返回 GPU drawable 的物理像素，GLES viewport、Vulkan
  swapchain 和 canvas framebuffer resize 只能使用这个单位。
- 当 PAL 没有独立 drawable 查询时，窗口按 `logical_size * my_pal_get_scale_factor()`
  回退；实现端应尽量提供真实 drawable 查询，避免非整数缩放或 compositor 调整时误差。
- 平台层的等价 API 是 `platform_get_logical_size()`、
  `platform_get_drawable_size()`、`platform_get_content_scale()` 和
  `platform_get_input_scale()`；RHI 调用点只接收 drawable 尺寸，UI/PAL 调用点只接收
  logical 尺寸。
- 软件 canvas 绑定 PAL LCD 的物理尺寸。窗口自有软件 canvas 在 surface resize 时释放，
  下一次绘制按新 LCD 懒创建；注入式 canvas 不由窗口销毁，注入方必须先调整自己的目标，
  再发送逻辑尺寸 resize。
- 内容缩放可在逻辑尺寸和 drawable 尺寸均未变化时独立改变（例如跨 DPI 显示器或分数
  缩放 rounding）。`my_window_refresh_scale()` 是唯一的 canvas 重配入口：它更新 canvas
  scale、保持 widget 坐标不变并使整个逻辑窗口失效。`BreakUI` 在每帧收集 damage 前通过
  window manager 批量调用它；因此注入式 RHI canvas 先完成 drawable target resize，再由
  window 负责其 scale 和字体状态，不能由桥接层直接设置 canvas scale。随后直接录制
  dirty window，不重复查询平台 scale。
- widget 结构与几何变更必须通过公共 API 进入 root dirty sink：`add_child/remove_child`、
  `set_visible`、`set_rect`、layout params 和 layouter 变更都会请求布局并产生 damage；
  `set_rect` 同时覆盖旧位置和新位置。布局器与 `on_layout` 回调使用
  `my_widget_set_layout_rect()`，避免在布局过程中递归请求同一布局器，但仍保留旧/新区损伤。
- damage 在逐级转换为 root 坐标时会裁剪到每个祖先的可见 bounds，避免滚动内容或越界
  子控件扩大无效重录区域。删除父控件会先清空 retained child 的弱 `parent`，窗口 removal
  hook 同时清理 dispatcher 的 grab/focus/hover 和动画引用，防止结构变化留下悬空指针；
  移除 focus 时发出 `blur` 以关闭 IME，移除 hover 时恢复默认 cursor。
- 内容测量可能触发第二次布局（例如 auto-size 影响父布局）。`my_window_prepare_layout()`
  在最多 8 次有界 pass 内收敛，只遍历 pending 子树；`BreakUI` 必须在跨窗口收集 damage
  之前对全部逻辑窗口调用它，确保 layout 新增的 damage 也参与 overlap expansion。

绘制回调允许关闭、打开窗口或修改 widget 树。窗口管理器在每个绘制 tick 和每个共享
surface frame 开始时建立带强引用的窗口栈快照；绘制期间若 `windows_epoch` 变化，则停止
当前帧、恢复本帧 dirty 并让下一帧从 live 栈重新完整合成。widget 绘制同样快照当前父节点
的 child 引用，只绘制仍属于该父节点的 child；回调新加入的 child 延迟到下一帧，已移除的
child 不会在当前帧继续访问。这样既避免 UAF/跳过窗口，也避免 live 数组变更造成的越界。

`my_window_enable_gpu()` 的状态转换遵循以下规则：

1. 初始状态是 `MY_GPU_SOFT`，请求同一已完整安装的后端是幂等操作。
2. 先完整创建并验证候选 canvas/context，再一次性提交 active state；候选失败时旧
   后端保持可用。提交时释放旧 canvas 必须早于旧 GL context，确保 GPU 资源销毁时
   context 仍然有效。
3. 后端创建失败不会修改 active state，也不会把失败伪装成成功；`MY_GPU_AUTO` 只在
   合法枚举范围内按 GLES2、OpenGL、Vulkan 顺序尝试，全部失败时保留软件状态。
4. BreakUI 使用共享的 Break RHI canvas，窗口只借用它；`break_ui_render()` 负责重建
   RHI surface、resize canvas，再把逻辑 resize 事件交给 window manager。

端口实现不得把“窗口事件尺寸”“RHI framebuffer 尺寸”和“widget 布局尺寸”复用为一个
无单位的变量。新增 PAL 时应同时覆盖 scale=1 和 HiDPI resize，并验证首帧 viewport、
scissor、swapchain extent 与实际 drawable 一致。

### 平台与渲染后端矩阵

| 平台 | OpenGL 句柄 | Vulkan 句柄 | 文本/剪贴板路径 |
|------|-------------|-------------|-----------------|
| X11 | X11 `Window` + `Display` | X11 `Window` + `Display` | XIM、UTF-8、INCR |
| Wayland | `wl_egl_window` + `wl_display` | `wl_surface` + `wl_display` | `text-input-v3`、非阻塞 pipe |
| Win32 | `HWND` + `HINSTANCE` | `HWND` + `HINSTANCE` | IMM32、UTF-16 clipboard |
| Cocoa | `CAMetalLayer` | `CAMetalLayer` | `NSTextInputClient`、pasteboard |

`platform_window_native()` 表示 OpenGL/EGL 目标，`platform_surface_native()` 表示
Vulkan WSI 目标；应用不得仅凭“都是窗口句柄”互换这两个接口。

Wayland 在 `wl_surface.enter/leave` 中跟踪窗口实际覆盖的 output，选择其中最大的
整数 fallback scale。若 compositor 同时提供 `wp_fractional_scale_v1` 和 `wp_viewporter`，
则按 `preferred_scale / 120` 创建物理 backing buffer，保持
`wl_surface_set_buffer_scale(1)`，并用 `wp_viewport.set_destination()` 映射回逻辑尺寸；
`wl_egl_window`、Vulkan swapchain 和 `platform_get_drawable_size()` 都使用同一套半舍入
物理尺寸。协议不可用时仍使用整数 buffer scale，窗口跨显示器时不会提交被 compositor
放大的低分辨率缓冲。若 fractional-scale 或 viewporter global 在运行中撤销，平台会先
销毁其关联对象并原子回退到整数 scale；client-side Xcursor 则使用内容缩放的向上取整
buffer scale，避免 125%/150% 下由 compositor 放大较低分辨率光标。
macOS 在 resize 与 backing scale 变化时同时更新 `CAMetalLayer.contentsScale` 和
`drawableSize`，后者始终是 `view.bounds * backingScaleFactor` 的物理像素。

X11 通过 RandR topology 事件和每次 `ConfigureNotify` 的 root 坐标重选活动输出：最大
覆盖面积优先，无覆盖时选择窗口中心最近的输出，面积/距离相同时优先 primary 输出。新的
DPI/scale 会在后续 Bridge frame 由窗口 scale 刷新契约传递给 canvas；因此拖动窗口跨
不同 DPI 的 X11 显示器不会继续使用启动显示器的缩放。

## 性能取舍

- **CPU tessellate + 动态 VBO**：避免每帧切换大量 pipeline；GL/VK 行为一致，易调试。
- **字体隔离的字形缓存 + 单 1024px atlas**：减少 texture bind；图集仅新增字形时上传，
  direct-mapped cache 额外隔离字体身份，避免字体切换后的错误复用；容量覆盖当前中文页面
  的千级不同字形，图像按缓存 key 复用。
- **双缓冲 VBO**：与 RHI in-flight frame 对应，避免 CPU/GPU 写冲突。
- **MVVM 列表增量刷新**：`items_changed` 原地更新 `list_view` adapter，保留滚动位置和
  行池；只有模板切换才重新安装 adapter，避免行情等高频数据刷新跳回列表顶部。
- **MVVM 上下文切换**：更换 ViewModel 时会同时解除并重新订阅 data、items 和 condition
  规则；旧模型不再驱动当前界面，列表会按新数据规模裁剪保留的滚动位置。
- **统一 canvas 配置**：窗口的 DPI scale 与字体配置在安装、后端切换和动态 scale 刷新时
  走同一入口，覆盖软渲染、GL、Vulkan 和 Break RHI 注入路径，避免后端创建分支的状态漂移。
- **stb 实现共享**：`stb_truetype_impl.c`、`stb_image_impl.c`、
  `stb_image_write_impl.c` 全局单实现，避免重复符号。
- **共享表面 damage 合成**：逻辑窗口按 dirty rect 重录到一个 offscreen surface，
  布局先有界收敛，再统一收集并扩展重叠窗口 damage；合成阶段只提交一次全屏纹理 draw，
  dialog 开关不需要创建额外 OS surface。窗口 dirty 在 canvas 创建、begin/end frame
  和逐窗口录制成功前不会被不可逆消费；任一窗口或共享帧失败时恢复所有快照，并让下一帧
  重新覆盖整个逻辑窗口栈，避免 retained surface 留下半帧结果。
- **增量布局路径**：`need_layout` 表示当前 widget 需要运行 measure/layouter/on_layout，
  `subtree_need_layout` 只标记后代路径；窗口帧不会因一个深层 child 变化而遍历无关兄弟子树。
- **固定列 Grid**：可见、非 floating 子项按行主序执行线性布局阶段；行高取该行最大
  子项高度，列宽均分并把余数从左到右分配。行高缓存按需增长，稳态帧不重复分配子项临时数组。
- **非阻塞选择传输**：X11/Wayland 的 clipboard 协议只在事件循环推进，绝不在 render
  frame 等待外部进程；大文本粘贴也维持同一帧时间预算。
- **有界输入背压**：IME/剪贴板输入均有明确的 16 MiB 单文本上限和有限队列预算，
  将异常输入的最坏内存成本限制在可控范围，同时不阻塞渲染线程。

## IME 状态

| 平台 | OS/图形后端 | IME | Cursor/窗口 | Clipboard |
|------|-------------|-----|-------------|-----------|
| X11 | OpenGL、Vulkan | XIM + `Xutf8LookupString`；无 XIC 时仍保留 enabled 状态 | Arrow/Text/Hand；EWMH native move | UTF-8、`INCR`、异步读取 |
| Wayland | EGL OpenGL、Vulkan | `text-input-v3`（compositor 提供时） | cursor-shape-v1 或 Xcursor fallback；CSD + `xdg_toplevel_move` | `wl_data_device`、异步 pipe |
| Windows | WGL OpenGL、Vulkan | IMM32 `WM_IME_*` | Win32 cursor + caption drag | `CF_UNICODETEXT` |
| macOS | MoltenVK/Vulkan | `NSTextInputClient` | Cocoa cursor rect + native drag | `NSPasteboard` |

Wayland 的 `text-input-v3` 和 cursor-shape 均为可选协议：缺失时普通键盘提交和
Xcursor theme fallback 仍可工作。macOS 构建使用 Cocoa `CAMetalLayer` 提供 MoltenVK
surface；它不是独立 Metal RHI。

## 验证

当前验证项：

- X11 OpenGL/Vulkan、Wayland OpenGL/Vulkan 均严格构建 `dxx_break`；四个 Linux 后端
  均完成 8 秒窗口启动烟测且无崩溃。
- 全量 `ENGINE_BUILD_TESTS=ON` 构建通过，`ctest -LE graphics` 为 `53/53`，且是 CI
  门禁。
- `test_break_ui_input`、`test_break_ui_damage`、`test_myui_vggeometry`、
  `test_myui_window_manager`、`test_myui_break_pal`、`test_myui_mvvm`、`test_imgui_compat`、
  `test_myui_font` 通过；`test_myui_font` 验证 UTF-8 中文码点、TTC 简体中文字面和
  非空字形覆盖；`test_myui_mvvm` 验证大列表数据变更不重置滚动或扩大行池，并验证
  ViewModel 切换后 items/condition 不保留旧 listener。
  window-manager 用例覆盖超过旧 4 KiB 限制的完整 clipboard paste，以及注入 canvas 的
  HiDPI scale 继承及不伴随 resize 的动态 scale 刷新；`test_monitor_selection` 覆盖 X11
  跨输出的最大面积、最近输出和 primary tie-break 选择；`test_myui_vgcanvas_backend` 覆盖公共 scale/AA/filter 能力边界和
  GLES 图像坐标缩放与物理 drawable resize；`test_wayland` 覆盖跨 output 时的最大
  buffer scale 选择、fractional 125%/150% rounding、cursor backing scale 和 global/output
  移除后的安全回退。`test_break_ui_damage` 额外覆盖结构树增删、重复挂载/环拒绝、移动和
  layout params 的旧/新区 damage、布局二次收敛、clean sibling 跳过，以及父销毁后的 child
  弱引用脱离；`test_myui_window_manager` 覆盖 focus/IME、hover/cursor 和 pointer grab
  在 subtree 移除后的恢复，并验证事件处理器自移除后不会继续向父节点冒泡；共享 surface
  用例还验证 pointer 命中非 modal 底层窗口后，
  key/IME 继续路由到该窗口，窗口关闭后安全回退到顶层窗口。

窗口所有权约定：`my_window_manager_open()` 增加 manager 对 `my_window_t` 的独立引用，
调用方必须释放创建时持有的窗口引用；`my_window_widget()` 无论是否 CSD 都只返回借用
指针，不能对它执行 `unref`。这样 CSD 内容容器不会产生隐藏的额外引用，窗口关闭、
BreakUI shutdown 和 dialog 生命周期保持同一套释放规则。

## 架构边界与后续风险

- 共享 offscreen surface 会按逻辑窗口 dirty rect 重录，但最终仍执行一次全屏 composite
  draw；尚未实现真正的局部 present，因此窗口数量增加时合成带宽仍按整面尺寸增长。已
  提供经过整数溢出保护的 `break_ui_damage_to_drawable_scissor()` 纯函数供未来平台
  damage 协商使用，但当前不把它用于 swapchain composite：默认 swapchain 每帧清屏且没有
  保留 backbuffer/平台 partial-present 契约，直接启用 scissor 会丢失未损伤区域。
- Wayland 当前固定使用 CSD，不协商 `xdg-decoration`；这是跨 compositor 行为一致性的
  取舍，代价是 title bar 和拖动逻辑由 myui 维护。
- 分数缩放依赖 compositor 同时支持 `wp_fractional_scale_v1` 与 `wp_viewporter`；旧
  compositor 自动降级为整数 `wl_output.scale`。当前没有可用 Wayland compositor 的
  CI runtime 场景，因此协议回调在 headless 单元测试和四个 Linux 后端的严格构建中验证，
  仍建议在目标桌面环境做一次 125%/150% 实机烟测。
- Wayland 的 `wl_registry.global_remove` 会按子对象到 manager 的顺序清理
  `text-input-v3`、clipboard、relative-pointer、pointer-constraints、cursor-shape、
  fractional-scale/viewporter 和 xdg-output；`wl_seat` 撤销时同时清空输入状态，随后
  新 global 可按当前 surface/seat 状态懒重建。这样 compositor 重启或 seat 热插拔不会
  继续向失效 proxy 发送请求。
- Vulkan vgcanvas 的纹理缓存按 frame fence 延迟释放，以免销毁仍被提交命令引用的
  descriptor；退休队列扩容失败时会保留原缓存条目并跳过该次替换，避免用错误资源
  所有权换取一次绘制。
- Break PAL 不拥有 `Platform` 或 `RHIDevice`，也不拥有 OS 主循环；调用方必须保证它们在
  `BreakUI` 和 PAL 销毁之后才销毁。Windows/macOS 的原生运行时验证仍由 CI 和对应设备提供。
- 文本队列到达预算时采用丢弃而不是阻塞或无限增长；如果应用需要可靠的编辑协议，应在
  上层实现 backpressure/重试，而不是直接绕过 `PlatformTextQueue`。
- `my_vgcanvas` 的 AA 仍是可选能力而非最低公分母语义；调用者必须处理
  `MY_RET_NOT_SUPPORTED`。GLES/OpenGL 的 MSAA 开关依赖已创建 surface 的样本能力；BreakUI
  的 Break RHI canvas 通过 offscreen FBO 事务支持设备能力允许的 2x 切换，失败时保留旧
  target。独立 Vulkan vgcanvas 仍保留自己的能力边界。nearest/bilinear 图像过滤已成为软件、GLES/OpenGL、
  Vulkan 和 Break RHI 的共同能力；Arabic 基础 shaping、L4 mirror 和 Mono ordered dither
  已落地，完整 OpenType shaping、复杂多段落文本和局部 present 仍按阶段计划处理。
