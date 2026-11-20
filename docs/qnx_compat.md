# QNX 平台兼容（feat/qnx-compat，2026-11-20 更新）

当前里程碑包括：**默认 headless 兼容层、真实 QNX Screen 窗口与软件 LCD/post、
显式 SwiftShader CPU Vulkan 离屏渲染及 CPU readback + Screen post**。默认
`MYUI_PAL=dummy` 用于无显示测试；`MYUI_PAL=screen` 显式选择 Screen 软件 PAL。
Vulkan 必须显式选择，不会静默替换默认 headless。本文记录架构决策、TDD、
可复现环境、验证结果与尚未验收的边界。

**2026-11-20 最终复验**：Linux 普通、ASan/UBSan、隔离 Mesa TSan 均为 **235/235**
（消毒器套件按运行器约定使用 64 MiB 栈，TSan 无竞态报告）；QNX x86_64 目标机
headless 清单 **191/191**。定时器跨平台路径在目标机复验：`test_platform_time`
**5/5**（含 `clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME)` 的 EINTR 同 deadline
续睡、永久错误不忙循环、读时钟失败不睡），`test_myui_timer_stress` 1 万 pending
提交中位约 80 µs；四生产者高并发 1/5/16/100 ms 三轮均 256 回调/0 失败且
min 延迟 ≥ 0。本轮修复 `test_rhi_vk_screen_post` 链接缺失 6 个
`--wrap=screen_*` 导致首帧 capture 调用真实 Screen 的段错误（11/11）。ARM 完整
`test_vulkan`、ARM ASan 全量、物理 GPU、QNX TSan、硬实时仍未验收，最终推送与
主分支合并以这些边界为准，见 §7。

**Screen 运行证据**：QNX SDP 8.0 软件虚拟显示器上可创建、查询、显示并销毁
真实 `screen_context` / `screen_window`。当前 x86_64 普通与 ASan/UBSan 的十项
Screen 定向矩阵均全部通过：myui runtime **14/14**、failures **17/17**、
concurrency **3/3**、present **3/3**、stability **3/3**、E2E **1/1**，引擎
display **3/3**、input **4/4**，软件 cursor **7/7**、GLES **5/5**。GLES 的
`VK_ICD_FILENAMES` 恢复环境所有权问题已修复，旧四轮共 416 字节泄漏不再作为
当前状态；ASan GLES 5/5 无未预期 LSan 报告，ES2 pbuffer 为 **64/64** 像素精确
且 bottom-up。上述结果来自虚拟显示器上的 NATIVE_SURFACE / accepted post 和 CPU
渲染/readback，不是物理显示、物理 GPU、原生 Vulkan surface 或实际显示 FPS。

**Vulkan 与 ARM 边界**：固定提交的 SwiftShader 已在 x86_64 和 AArch64 QNX 上各完成
64×64 CPU 离屏绘制，4096/4096 像素匹配；x86_64 引擎的 headless surface、
CPU readback + Screen post 另有 480000 个 clear 像素一致的记录。x86_64 完整
`test_vulkan` 已退出 0；500 帧墙钟 **126.60 秒**、平均 **3.9 FPS**、wall frame
min/max **186.79/4080.50 ms**、simulation time **50.00 秒**。这些数字仅来自
软件渲染与并行验证负载，不是硬件性能或绝对最优证明。myui 显式 offscreen
Vulkan→LCD 普通 11/11（禁用版 3/3）、Vulkan ASan 11/11 无泄漏报告。
`VK_QNX_screen_surface` 未被该 ICD 声明，Khronos validation 亦未覆盖。
ARM 2307 的 headless 清单为 **192/192**，但完整 `test_vulkan` 与 ARM ASan 最终运行
均尚未取得最终退出码，不能写成完整 ARM 验收或以 headless/定向探针替代。

**当前门禁**：2026-11-20 最终复验 Linux 普通、ASan/UBSan、隔离 Mesa TSan 均为
**235/235**，均有 1 个 Windows-only 平台设计内跳过，无 suppression；QNX x86_64
目标机 headless 清单 **191/191**。既有 x86 默认 191/191、Vulkan 192/192、
ARM 2307 headless 192/192 收据保留。`_LIBCPP_HAS_NO_ASAN` 容器注解、物理
GPU/原生 surface、ARM 完整 `test_vulkan` 与 ARM ASan 最终退出码、QNX TSan、
硬实时与绝对最优仍未验证；这些未完成项继续作为推送/合并的边界记录，不以
定向绿灯缩小门禁。

## 1. 范围与证据等级

| 能力 | 状态 | 证据 |
|------|------|------|
| 平台描述符与 poll net_loop | 契约及目标语义验证 | 描述符模拟/目标测试；`test_net_loop`/`test_net_replication` |
| 引擎核心与 myui headless | **2026-11-20 复验：x86_64 目标机 191/191** | 目标命令清单见 §5；Linux 三配置 235/235 见 §6.2 |
| 时钟与定时器跨平台 | **目标机复验 5/5 + 高并发 min 延迟 ≥ 0** | QNX `clock_nanosleep` TIMER_ABSTIME 路径；1/5/16/100 ms 四周期三轮 256 回调/0 失败；10k pending 提交 ~80 µs，见 §6.1 |
| 效率（吞吐与时限断言） | 目标定向验证 | LOD、异步加载及 `test_qnx_perf_smoke`，不是绝对最优或 GPU 基准 |
| 引擎 QNX Screen 窗口/WSI | **x86_64 与 AArch64 虚拟显示器 NATIVE_SURFACE** | 双架构 usage、输入、resize 与清理；ARM 定向 4/4，见 §5.3 |
| myui Screen 原生软件 PAL | **x86_64 与 AArch64 虚拟显示器 NATIVE_SURFACE** | x86 普通/ASan 十项全矩阵通过，ARM 定向 10/10；30 秒 soak 收据见 §5.2/§6.4，最新分项见 §5.6 |
| SwiftShader CPU Vulkan / Screen post | **双架构离屏 CPU 验证；x86_64 完整 `test_vulkan` 已通过；ARM 全场景待完成** | 两架构各 4096 个离屏像素；x86_64 Screen post 480000 个像素、完整 `test_vulkan` 退出 0；非原生 surface |
| myui 显式 Vulkan canvas | **x86_64 CPU RUNTIME；Vulkan ASan 11/11 无泄漏报告** | offscreen canvas→readback→Screen LCD 普通 11/11、禁用版 3/3；真实非对称像素、resize、多窗口、pending 与清理；非原生 surface |
| shaderc | **AArch64/x86 均构建；普通目标各 2/2；ARM ASan 仅定向 shaderc 无未预期 LSan** | 静态 mutex 补丁见 §4.3；123 字节负向仍检出，不代表全量 ARM 通过 |
| 物理 GPU、原生 Vulkan surface、Khronos validation 与硬件性能 | **当前环境未验证** | 不以 CPU ICD、虚拟显示器、headless 或 accepted post 冒充硬件能力 |

编译、无 GPU 契约、原生窗口和 accepted post 是不同证据等级；完整边界见 §7。

## 2. 架构决策

### 2.1 平台描述符（`engine/src/platform/platform_compat.h`）

默认 headless（Screen 可用时）：

```
TARGET_FAMILY = QNX          NET_LOOP = POLL
SURFACE      = QNX_SCREEN    REQUIRES_HOST_SURFACE = 0
GRAPHICS_API = NONE          TARGET_GRAPHICS_API = NONE
VULKAN       = UNAVAILABLE   SUPPORT_EVIDENCE = COMPILED
```

显式 Vulkan 时保留 `SURFACE=QNX_SCREEN`，并切换为
`TARGET_GRAPHICS_API=VULKAN`、`VULKAN_SUPPORT=COMPILED`；编译期
`SUPPORT_EVIDENCE` 仍为 COMPILED，不会根据 configure 结果伪造 GPU_RUNTIME。
`REQUIRES_HOST_SURFACE=0` 表示 headless 核心不依赖宿主注入 surface，Screen
窗口由平台自行创建；没有 Screen 服务或依赖缺失时必须 fail-closed。

### 2.2 net_loop POLL 后端（`engine/src/network/net_loop_poll.c`）

QNX Neutrino 没有 epoll/kqueue，`poll()` 是原生就绪通知机制。在 poll 的
约束内做吞吐优化：

- 兴趣集保存在用户态 slot 数组，**仅注册变更时置 dirty**，稳态 `wait()`
  一次调用恰好一次 `poll()` 系统调用、零数组重建；
- `poll()` 一次系统调用返回一批就绪 fd（批量语义与其余后端一致）；
- 非阻塞 pipe 实现跨线程 wakeup（`write()` 异步信号安全）；
- 电平触发（poll 固有）：每次 wait 都报告仍就绪的 socket；调用方按
  文档化的高吞吐模式排空 socket，在 ET 后端与 LT 后端下保持一致语义；
- slot↔pollfd 映射在 wait 期间稳定（loop 线程亲和），但 rebuild 前被
  remove 的 slot 会残留旧映射——`test_net_loop` 的 QNX 段专门验证该
  陈旧映射不会上报死 slot。

### 2.3 RHI 解析与依赖门控

`ENGINE_RHI_BACKEND=auto` 在 QNX 默认解析为 `headless`；显式 `vulkan` 或
兼容选项 `ENGINE_VULKAN=ON` 选择完整 Vulkan RHI：

- opengl/metal/d3d12 在 QNX 配置期 FATAL，不静默回退；
- Vulkan 配置必须有 Screen 头文件/库、Vulkan loader/头文件和目标架构的
  shaderc，缺任一项即配置期 FATAL；
- `engine_link_rhi_backend()` 分别链接 `engine_rhi_headless` 或
  `engine_rhi_vulkan`；链接和 shader 编译通过不等于存在 GPU/ICD。

### 2.4 平台层与系统库

- SDP 提供 Screen 时由 `window_screen.c` 自建窗口；否则 `window_mobile.c`
  提供 fail-closed 的平台入口，不能伪称存在原生窗口；
- filewatch 走可移植轮询回退分支（无 inotify）；
- QNX socket API 在 libsocket：`check_library_exists` 探测式链接
  （glibc/macOS 宿主模拟时在 libc，自动跳过）；
- 引擎编译定义 `ENGINE_PLATFORM_QNX=1 _POSIX_C_SOURCE=200112L`。

### 2.5 myui

- `MYUI_PAL` 默认 `dummy`（离屏、确定性），与 QNX headless 形态一致；
  `MYUI_PAL=screen` 显式选择 `engine/src/myui/mypal/screen/`，要求 QNX
  Screen 头文件/库及 `ENGINE_QNX_SCREEN=ON`。该配置下 `my_pal_create`
  直接返回 Screen 创建结果，失败时**不回落 dummy**；
- Screen PAL 创建真实 `screen_window`，提供 RGBA8888 软件 LCD、固定两个
  render buffer、dirty `x/y/w/h`、resize 以及 run/quit/post_event/timer/command
  主循环。dequeue/post 均使用 `SCREEN_DONT_BLOCK`，`EWOULDBLOCK` 映射为
  `MY_RET_PENDING`，避免无可用 buffer 时卡住事件循环。两个 buffer 的
  pointer/stride 包装按需缓存，热路径不分配 myui 内存；
- CPU shadow 保存最近一次完整帧，每次新取得 native buffer 都先恢复完整帧，
  不依赖同槽或异槽的旧 native 内容。`my_window_paint()` 将同帧所有 dirty rect
  的 bounding box 交给底层；Screen 在 post 前保存实际 damage，失败重试合并
  尚未显示的 damage，避免双缓冲历史分叉和漏提交。resize 只释放内部旧
  buffer/mem 包装并重建，LCD 外包装保持稳定，最终销毁时才释放外包装；
- 外部修改 native `SCREEN_PROPERTY_SIZE` 后，尺寸/LCD 查询会同步并重建
  buffers，原生 SIZE 与 BUFFER_SIZE 保持一致；`SCREEN_EVENT_PROPERTY` 的
  SIZE 事件转换为 `MY_EVENT_RESIZE`。resize 失败时旧 canvas/LCD 调用安全
  失败，不访问已释放 LCD；恢复重建保留 OOM 类别。该 myui 路径不能与 §2.6
  引擎 Platform 的 WSI resize 验收混为一谈；
- 原生键盘、绝对/相对指针、滚轮和 manager close 已接入；`KEY_CAP` 转换为
  Unicode `MY_EVENT_IME_COMMIT`，与直接按键去重并拒绝非法标量。公开的协作
  关闭 subtype 为 `MY_PAL_SCREEN_MANAGER_CLOSE=0x4d595543u`。myui E2E 通过
  真实 Screen 事件注入覆盖控件与自动重绘，不代表物理 HID 验证；
- command wake 会合并：仅空队列的首次投递触发唤醒，已有 pending wake 时不
  重复发送；队列真正清空才重置状态。nested command 复用同一 pending wake，
  不额外唤醒。主循环每批最多处理 256 个 queued event，随后重新调度 timer，
  避免持续投递造成 queue starvation；quit 后只对退出时已排队快照做有限
  drain，不把快照内事件直接丢弃；
- clipboard 是**每个 PAL 实例的进程内文本存储**，支持复制、定长读取和分配
  读取，OOM 保留旧值，UTF-8 截断不拆开码点；它不是系统剪贴板。IME setter
  保存本地状态，`KEY_CAP` 文本提交不等于操作系统预编辑、候选词或完整 IME；
- 默认 cursor 路径使用真实 `screen_session_t` 和形状属性，失败时释放新建
  session；当前软件虚拟显示驱动拒绝 `cursor`，运行时得到明确的
  `MY_RET_NOT_SUPPORTED`，不能声称该 VM 已验证物理 cursor。可显式启用
  应用合成的软件 cursor，其形状、移动、边界、双缓冲历史、pending、resize、
  多窗口与释放在普通/ASan/UBSan 各 7/7；它不是原生 cursor，也不会伪装成
  GL/Vulkan mount。GLES mount 使用独立 pbuffer/context 和 `glReadPixels` 翻行
  复制到 LCD；共享 EGLDisplay 以互斥引用计数管理，最后一个 mount 才 terminate。
  Vulkan provider 只声明 `VK_KHR_surface` 与 `VK_EXT_headless_surface`，adapter
  使用真实 offscreen canvas、左上原点 RGBA readback 和每窗口 staging，pending
  保留原帧，成功后交给 LCD post；不伪造 VkSurfaceKHR 或 swapchain。两条路径
  仍需显式后端与对应运行库，不会因选择 Screen PAL 自动获得原生 GPU 能力；
- 不直接读取已 post 像素；现有测试在下一次 begin 后采样当前 back buffer，
  并检查非灰阶历史、post 次数/参数。当前虚拟显示器的 `screen_read_window`
  探针返回 ENOENT，没有最终显示读回证据，不据此声称物理显示内容正确。
  myui headless 测试覆盖布局/CSS/编辑器/echart/MVVM/窗口管理/指标等，也不
  替代上述原生路径。

### 2.6 引擎 Screen 窗口层（`engine/src/platform/window_screen.c`）

- CMake 在 QNX 平台探测 SDP 的 `screen/screen.h` + `libscreen`（默认
  `ENGINE_QNX_SCREEN=ON`）；toolchain 的 `CMAKE_FIND_ROOT_PATH` 同时挂
  `$QNX_TARGET` 与 `$QNX_TARGET/<arch>`（头文件在 `usr/include`，库在
  `<arch>/usr/lib`）；
- 平台描述符的 surface 为 `ENGINE_SURFACE_QNX_SCREEN`（自建、非宿主注入）。
  默认 RHI 仍为 headless；显式 Vulkan 时 target API 为 VULKAN，支持等级和
  编译期证据均为 COMPILED；
- `platform_create` 依次创建 context/window/event，设置
  SIZE/FORMAT_RGBA8888/USAGE 并 flush。显式 Vulkan 增加
  `SCREEN_USAGE_VULKAN`。任一步失败均销毁已经创建的句柄并返回 NULL；
  运行时测试用链接器 wrapping 注入 SIZE/FORMAT/USAGE/flush 失败，验证
  context/window/event 各释放一次；
- `platform_poll` 非阻塞处理 CLOSE、POINTER（坐标/左中右键/垂直滚轮）和
  KEYBOARD（`screen_keymap.h` 映射）。尺寸查询实时读取
  `SCREEN_PROPERTY_SIZE`；键映射常量以 `_Static_assert` 对照 QNX 真头文件；
- 显示器通过 `SCREEN_PROPERTY_DISPLAY_COUNT/DISPLAYS` 枚举，最多向公共 API
  暴露 `PLATFORM_MAX_MONITORS` 个；读取名称、位置、分辨率、刷新率和 DPI。
  当前窗口的 DISPLAY 决定 primary，未关联时使用首个显示器；DPI 优先使用
  原生值，再以物理毫米数计算，极端值不直接转 int。查询失败返回 0/false
  并清零输出；这些显示器查询不属于 §2.5 的 myui clipboard/IME 能力；
- WSI 使用 `PLATFORM_WSI_BACKEND_QNX`，不借用 X11 标识。
  `platform_window_native/surface_native` = `screen_window_t`，
  `platform_display_native` = `screen_context_t`。默认原生路径请求
  `VK_KHR_surface`/`VK_QNX_screen_surface` 并调用 `vkCreateScreenSurfaceQNX`，
  失败时清空输出。仅当显式设置 `BREAK_VK_HEADLESS_SURFACE=1` 时，改为请求
  `VK_EXT_headless_surface`；再加 `BREAK_VK_SCREEN_POST=1` 才启用 CPU
  readback + Screen post。后两种选项不伪造原生 surface 或交换链能力；
- 本节是引擎 Platform/WSI 适配，不是 §2.5 的 myui PAL，也不是 Break 专有
  RHI 桥。`test_platform_screen_input_runtime` 的输入来源 window 过滤、
  native SIZE 到 Platform/WSI RESIZED、真实 `SCREEN_EVENT_MANAGER` close
  已有普通及 ASan/UBSan 各 4/4 定向收据；myui 结果不能替代这些引擎用例。
  上述 4/4 已包含异源 manager close 和未知 subtype 的负向过滤；纯键映射
  测试同样不等于交互运行收据。

## 3. TDD 记录

| 循环 | 红 | 绿 |
|------|----|----|
| 平台描述符 | `test_platform_compat_qnx` 编译失败（枚举不存在） | `platform_compat.h` 增加 QNX 族 + `ENGINE_NET_LOOP_POLL` |
| poll 后端 | `test_net_loop_qnx` 配置失败（后端源不存在） | `net_loop_poll.c` 实现 + 故障注入钩子 |
| 平台接线 | 宿主 QNX 模拟构建失败（`task.c` nanosleep、`platform_vk_surface.c` unused-function、测试目标缺 qnx 分支） | 引擎/测试 CMake qnx 分支 + `pvk_resolve` WSI 条件定义 |
| 效率冒烟 | `test_qnx_perf_smoke`（新） | 三条吞吐下限断言 + 实测打印 |
| 宿主 CI | Windows 构建 `test_qnx_perf_smoke` 失败（无 `poll.h`/`sys/socket.h`/`clock_gettime`）；macOS `_SC_NPROCESSORS_ONLN` 被 `_POSIX_C_SOURCE` 隐藏 | 该目标仅在 linux/macos/qnx 构建；macOS 追加 `_DARWIN_C_SOURCE` |
| 真实 SDP 交叉编译 | qcc 构建失败：`_SC_NPROCESSORS_ONLN`/`CLOCK_MONOTONIC` 被 `-std=c11` 严格模式隐藏；`-lpthread`/`-ldl` 不存在（QNX 8 并入 libc）；独立网络测试缺 `-lsocket`；`__isfinitef` 需 `-lm` | toolchain 加 `-D_QNX_SOURCE` + 交叉 binutils；qnx 分支去 pthread/dl、补条件 socket/m 链接 |
| 目标机运行 | 首轮 127/137：4 个 Memory fault（QNX 默认栈过小）、6 个数据路径/参数问题 | 运行器 `ulimit -s 8192`（README 的 8MB 栈假设）；`ENGINE_TEST_SOURCE_ROOT` 可覆盖 + 目标机部署布局；ctest 参数/WILL_FAIL 语义纳入运行器 → **144/144** |
| Screen 窗口层 | `test_platform_compat_qnx_screen` 编译失败（`ENGINE_SURFACE_QNX_SCREEN` 不存在） | `platform_compat.h` 增加枚举与 ENGINE_QNX_SCREEN 描述符变体；`window_screen.c` 双架构交叉编译 100% |
| Screen 键映射 | `test_screen_keymap` 编译失败（头不存在） | `screen_keymap.h` 纯整数映射 + `_Static_assert` 钉死 `<sys/keycodes.h>` 镜像 |
| 目标机 test_vfs 偶发 | qnx6 `ftruncate` 按剩余空间截断却返回成功 → >MAX 前置条件静默失效 | 测试前置校验实际文件大小（文件系统给不出 >MAX 稀疏文件时跳过断言；引擎逻辑本身正确） |
| QNX Vulkan 描述符/WSI | 旧 WSI 源码契约失败、缺少 QNX usage/后端标识 | 描述符变体、ABI 对照、5 个无 GPU 创建用例及 QNX WSI 生命周期变体 |
| Screen 初始化失败清理 | 注入 SIZE 设置失败后 `platform_create` 仍返回非 NULL | SIZE/FORMAT/USAGE/flush 全部检查返回值；失败时三个句柄各销毁一次，运行时 2/2 |
| 目标运行器隔离 | `BREAK_QNX_TARGET_ROOT` 探针仍进入固定 `/tmp/bt`，退出码 2 | 运行器支持独立部署根路径，默认 `/tmp/bt` 不变；宿主探针通过 |
| 测试源码根 | `test_shader_io` 在目标机读不到 shader（21 项失败） | shader/source 均优先读取 `TEST_SOURCE_ROOT`，保留旧回退；目标定向 58/58 |
| 运行器假绿 | 缺失命令清单返回 0 并打印 0/0 | 缺失/不可读清单和空清单均退出 2；正常探针 1/1 |
| myui Screen wake storm（2026-10-27） | 4 个 producer 共 256 个 command 产生 257 次 wake，1 ms 定向用例红灯 | 空队列才唤醒、队列真正清空才重置；1/5/16/100 ms 每轮均为 256 command/256 回调/256 析构且 wakeups=2，普通及 ASan/UBSan 最终并发套件均 2/2 |
| myui Screen nested command（2026-10-27） | parent 内提交 child 共产生 3 次 wake，断言期望 2 次而红灯 | nested command 复用 pending wake；parent/child 均执行和析构一次、wakeups=2，普通及 ASan/UBSan 均通过 |
| myui Screen buffer 包装缓存（2026-10-27） | 热路径 myui alloc/free 计数非零；每种 present 模式 320 帧的 pointer/stride 查询各为 320，断言红灯 | 固定两个 buffer 的 LCD 包装缓存；热路径 myui alloc/free 为 0，pointer/stride 查询各降为 0，普通及 ASan/UBSan present 均 2/2 |
| myui Screen 控件 E2E（2026-10-27） | 先写真实路径测试，首轮即 1/1，通过记录中没有红灯，不补造红 | 普通及 ASan/UBSan 均 1/1；真实控件、原生事件、软件 canvas、LCD/post 和 manager close 全链路见 §5.2 |
| myui Screen native property resize（2026-10-27） | 外部 SIZE 改变后 LCD 仍保留旧尺寸，SIZE property 事件未产生 `MY_EVENT_RESIZE`；中间轮还暴露定时器退出红灯 | 外部尺寸同步重建 LCD/buffers，property 事件转换 resize；当时普通及 ASan/UBSan runtime 9/9、failures 13/13、E2E 1/1、同树合计 30/30；最新计数见 §5.2 |
| myui E2E resize 与 UAF（2026-10-27） | 新增真实 SIZE/property 到 280x220 后，ASan 初轮实际报 heap-use-after-free | LCD 外包装在 resize 中保持稳定，只释放内部旧 buffer/mem 包装；根 widget、PAL size、LCD/canvas 重建和自动重绘通过，普通及 ASan/UBSan E2E 均 1/1，最终定向运行无消毒器报告 |
| myui Screen cold resize（2026-10-27） | 冷启动 resize 失败，定位到原生 SIZE 与 BUFFER_SIZE 不一致；故障注入覆盖创建/恢复失败 | 同步 SIZE/BUFFER_SIZE 并保留稳定 LCD 外包装；失败时旧 canvas/LCD 安全失败，恢复保留 OOM 类别，普通及 ASan/UBSan failures 均 13/13 |
| myui Screen queue fairness（2026-10-27） | 无节流回归中 submitted 与 executed 严重不等，持续生产使命令执行/帧调度饥饿 | 每批最多 64 个 queued event 后重新调度 timer，保留 wake 合并；最终 1 秒回归普通及 ASan/UBSan 的 submitted/executed/destroyed、FIFO/errors/watchdog 均满足门禁，不以不同配置吞吐差宣称优化提升 |
| myui Screen quit 已排队事件（2026-10-27） | quit 提前退出使已排队 user event/command 未执行，普通及 ASan runtime 均只有 7/9 | 退出时对已排队快照做有限 drain，快照内事件按 FIFO 交付后退出；最终普通及 ASan/UBSan runtime 均 9/9 |
| 引擎 Screen input/manager（2026-10-27） | 异源输入被消费、native resize 未到 WSI RESIZED、真实 manager close 未产生 quit | 来源过滤、native SIZE→WSI resize、真实 manager close 普通及 ASan/UBSan 各 4/4，已包含异源窗口和未知 subtype 负向过滤 |
| myui Screen 非阻塞与 pending（2026-10-27） | 故障注入发现 dequeue/post 未传 `SCREEN_DONT_BLOCK`，post 的 `EWOULDBLOCK` 未映射为 pending，见 `/tmp/qnx-screen-nonblock-red.log` | dequeue/post 显式非阻塞；pending 时 timer 继续推进，post 重试累计未显示 damage；普通及 ASan/UBSan failures 均 15/15 |
| myui 多 dirty bounding box（2026-10-27） | 新增真实 dummy PAL + soft canvas 用例只收到首个 dirty，Linux 239 项中 1 项失败，见 `/tmp/build-linux-myui-dirty/logs/test-red.log` | `my_window_paint()` 汇总全部 dirty 的 bounding box，不改公共 API；Linux window manager 239/239 |
| myui Screen 双缓冲与 RGBA（2026-10-27） | 交错不相交 dirty 丢失历史像素；native RGBA 和非灰阶断言在 BGRA 实现上红灯，见 `/tmp/qnx-screen-history-red2.log`、`/tmp/qnx-screen-rgba-project-red.log` | 每次 acquire 恢复完整 CPU shadow；原生/LCD 切换 RGBA，软件像素路径补齐非灰阶与混合支持；6 个 Screen 命令普通及 ASan/UBSan 各 33/33，普通 100 轮 present 均 3/3 |
| 上游 mobile-layer QNX 链接（2026-10-27） | 合并后默认、Vulkan、Screen 和 ARM 构建均在 mobile-layer 链接处报 `__isfinitef` 未定义 | QNX 条件链接 `libm`，四个 mobile-layer 目标先验证链接，再恢复各配置全量构建；不改变其他平台依赖 |
| 上游 fake Screen SDK（2026-10-27） | 合并后的宿主编译缺少 `SCREEN_EVENT_MANAGER`、WINDOW/SUBTYPE 和 `screen_get_event_property_pv`，见 `/tmp/linux-merged-screen-fake-red.log` | fake SDK 补齐声明和事件注入；宿主 manager 来源/subtype 过滤与上游窗口模式、mobile/null-safety 合计 10/10，见 `/tmp/linux-merged-screen-focused-green2.log` |
| 图表与软件光栅 UB（2026-10-28） | UBSan 复现负颜色通道插值和超大 float→int32 转换；新增极端范围用例在修复前同样失败 | 有符号通道插值、极端范围安全采样和饱和坐标转换；chart 普通及 ASan/UBSan 各 59/59，QNX 软件后端普通及 ASan/UBSan 各 50/50 |
| Screen 显示器与 DPI（2026-10-28） | 原实现无枚举，宿主新增用例出现 49 个断言失败；极端物理尺寸另复现 float→int UB | 真实显示器枚举、主屏关联、失败清零及 DPI 饱和换算；宿主普通及 ASan/UBSan 各 12/12，目标显示器 runtime 各 3/3 |
| myui 输入能力（2026-10-28） | 剪贴板/IME/cursor 占位实现红灯；初版 keycap 文本有重复事件，虚拟驱动的 cursor flush 返回 ENOTSUP | 进程内剪贴板、非原生 IME 状态、Unicode 去重、相对位移和真实 session 路径；普通及 ASan/UBSan runtime 14/14、failures 17/17。当前驱动不支持 cursor，验证的是明确错误与资源回收，不是正向形状验收 |
| QNX 完整部署（2026-10-28） | 新测试盘首轮 144/157，12 项缺二进制/动态库，网络压测另有一次丢包，独立复测 17/17 | 部署补齐且保留真实失败记录；QNX 默认清单 157/157、Vulkan 清单 158/158；不删除失败项或以编译替代目标执行 |
| 新上游模块与临时目录（2026-10-28） | 源码宏指向不存在的目标路径；`RLIMIT_FSIZE` 不可用；crash 线程 ID 为 0，卸载后 SIGSEGV 被掩码；旧 `/tmp` 分区写满导致大文件创建失败 | 源码按目标根部署；write 错误注入；真实线程 ID、调用方掩码保存及两阶段恢复，crash 普通/ASan 36/36；`TMPDIR` 指向独立测试盘，大文件场景 17/17、editor shell 80/80、fs 10/10。超长路径仅对 ENAMETOOLONG 显式标记边界 |
| 自定义 OpenSSL 与消毒器契约（2026-10-28） | 自定义根下 `-lcrypto` 链接失败；ASan 的 `___asan_globals_registered` 被误计为产品导出符号 | 传递真实 include/library 路径，RHI/crypto/update 三个契约普通及 ASan 均 3/3；过滤消毒器合成符号，不关闭检查或测试 |
| OpenGL depth cubemap 生命周期（2026-10-29） | 创建登记为 `RHI_RES_CUBEMAP`，销毁却按 `RHI_RES_TEXTURE` 查找；32 次生命周期遗留 32 个包装对象，槽断言失败 | `rhi_gl.c` 按 cubemap 类型查找并销毁；`test_rhi_x11_runtime` 在真实 X11/OpenGL 普通与 ASan/UBSan 下各 3/3 |
| 应用级 IPC allocator 与 EINTR（2026-10-29） | 共享 debug allocator 被 accept/clipboard 线程并发使用，TSan 报告 `live_count` 竞态；poll 在 EINTR 后重复使用原 timeout，真实信号用例提前返回 | allocator 操作统一由 server mutex 串行化，连接在锁外 join、锁内释放；每次 poll 前按单调时钟原 deadline 重算剩余时间。Linux 普通/ASan/UBSan/TSan 及 QNX 普通各 10/10 |
| Screen post 失败后的 Vulkan present（2026-10-29） | 强制前两次 post 失败后，第三次 acquire 报 `VK_ERROR_OUT_OF_DATE_KHR`，25 秒测试超时；失败提前返回使 acquired image 未进入 present 生命周期。组合用例另复现 post ERROR 被 present OUT_OF_DATE 覆盖 | post 失败仍执行 `vkQueuePresentKHR`、推进 frame 并清理状态；组合故障保留 ERROR（DEVICE_LOST 除外）且照常重建交换链。真实 QNX 普通与组合恢复用例 **2/2**，post 故障与尺寸用例 7/7 |
| myui offscreen Vulkan→LCD（2026-10-29） | 未实现时 provider 与 mount 场景失败，见 `build-validation/qnx-myui-vulkan-x86-red-target.log` | 真实 offscreen canvas/readback、独立 staging、pending 保留、resize/OOM/多窗口和销毁顺序；真实 QNX 复跑 11/11、禁用版 3/3，关联回归共 351 项。SwiftShader ASan 映射问题仍未通过 |
| Screen GLES 纹理与共享 display（2026-10-29） | `glGenTextures` 未绑定导致 `glIsTexture` 为 false；随后第二个窗口销毁使第一个窗口无法再 make-current，普通仅 4/5 | 先绑定纹理名称以建立真实对象；共享 EGLDisplay 按 mutex 引用计数管理，最后一个 mount 才 terminate。普通及 ASan 功能用例均 5/5；ASan 仍有 2217 字节泄漏，未记通过 |
| QNX ASan 启动与死亡测试 helper（2026-10-29） | 新清单漏掉 `on -ad` 导致 7/192；修正启动后死亡测试又误用 ASan 子进程，190/192 | 运行器增加 `BREAK_QNX_ON_AD=1`；无前缀的死亡测试同样选择普通 helper，父进程保留 sanitizer。两个死亡测试定向 2/2，完整清单继续复验 |
| Screen 无节流退出延迟（2026-11-02） | 截止回调按时执行，但逐事件自旋锁竞争使首次退出再延迟约 6.9 秒并触发 watchdog；仅换互斥锁仍延迟约 3.04 秒 | 互斥锁保护队列，单次锁内摘下至多 256 个 FIFO 事件后在锁外分发，保留 wake 合并与有界调度。真实 QNX 完整普通稳定性 **3/3**，500 次生命周期、30 秒 soak、无节流均为零错误/看门狗，截止后返回约 138–141 微秒；日志 `qnx-screen-unthrottled-isolated-before.log`、`qnx-screen-unthrottled-mutex-1.log`、`qnx-screen-unthrottled-batch-1.log`、`screen-normal-test_mypal_screen_stability-batch-2.log`。ASan 和最终回归仍需通过 |

| Screen 批量交付边界（2026-11-03） | 初版批量实现新增两个红灯：销毁 loop 后仍执行后续命令、nested wake 从 2 次增至 3 次 | 批交付前检查 `destroy_requested`，只析构后续事件；wake 状态延迟到批交付后按当前队列重置。并发回归 **3/3**，500 次生命周期/30 秒 soak/无节流最终稳定性 **3/3**，最新截止后返回约 242–267 微秒；ASan 仍待复验 |
| QNX ASan 并发初始化隔离（2026-11-03） | 已持有锁的探针仍返回 0；一次 LargeMmap 复现期间另有 ASan 探针/调试进程活动，说明仅按测试名匹配不能可靠防止并发初始化 | `BREAK_QNX_ASAN_LOCK` 以原子 `mkdir` 拒绝第二个运行，正常/信号退出仅 `rmdir` 空锁目录，不强删他人锁。持有锁和并发运行均返回 3，锁清理通过；现有 Python 回归 **17/17**，目标全量仍须串行复验 |
| ARM 部署 inode 耗尽（2026-11-03） | 补齐 Vulkan 闭包后先通过原缺库用例，但 12000 inode 耗尽，剩余 682 MiB 空间仍出现连续写入失败，最终 **172/192** | tar/loopback 共用测试产物清单，仅部署 185 个去重命令程序加完整 `test_vulkan`（共 186 个），源码排除各级 `CMakeFiles`；实际归档检查和宿主测试通过。新 30000-inode 实例正在复验，不把旧现场计为产品通过 |
| 宿主 llvmpipe fence 竞争（2026-11-02） | 精确插桩 Mesa 连续 3 次证明 `lp_fence_signal` 写与 `lp_fence_signalled` 无锁读竞争；不是未插桩库假阳性 | 隔离 Mesa 副本在 `lp_fence_signalled` 的 SW fence 读侧使用同一 mutex，完整 TSan 图形 3 次、普通图形 1 次及完整 Linux TSan **234/234** 通过。未加 `glFinish`、未 suppression、未减 worker。系统 Mesa 未修改，绿色仅适用于显式实验驱动，仍需上游评审 |
| `test_rhi_vk_screen_post` 目标机段错误（2026-11-20） | 链接只加了 8 个 `--wrap=screen_*`，首帧 capture 路径的 `screen_create_pixmap`/`screen_read_window` 等 6 个函数未包装，调用真实 Screen 解析假 handle 段错误（core dump 还瞬时占满测试盘，连带后续 5 个 editor 测试空日志失败） | 补齐 6 个 wrap 共 14 个；同一轮按测试契约补齐产品语义——verify 路径 enqueue 结果必须检查并在失败后保持 buffer 未归还、下一 present 先归还再 dequeue 恢复、post 失败保存 damage 供下次合并重试。真实 QNX 目标机 **11/11**，完整 headless 清单 **191/191** |

## 4. 构建

### 4.1 QNX SDP 交叉编译（目标机）

需要 QNX SDP（本文验证使用 8.0.0，qcc/gcc 12.2）。默认配置是 headless，
即使 SDP 探测到 Screen 也不会自动启用 GPU：

```bash
source /opt/qnx800/qnxsdp-env.sh   # 按实际 SDP 安装位置设置 QNX_HOST/QNX_TARGET
cmake -S engine -B /tmp/build-qnx \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/engine/toolchain-qnx.cmake" \
  -DQNX_ARCH=x86_64 \
  -DENGINE_TEST_SOURCE_ROOT=/tmp/break-qnx-validation
cmake --build /tmp/build-qnx -j
```

`QNX_ARCH` 可选 `aarch64le`（preset 默认）/`x86_64`/`armle`；也可使用
`engine/CMakePresets.json` 的 `qnx-cross`。toolchain 自动选用交叉 binutils，
并定义 `_QNX_SOURCE`，不再给 q++ 传已弃用的 `-lang-c++`。

**在目标机跑 headless 套件**（脚本位于 `engine/tools/qnx/`）：

1. 选择部署根（通常 `/tmp/bt`，也可用独立测试盘上的目录），配置时把
   `ENGINE_TEST_SOURCE_ROOT` 指向该根；
2. 部署清单中的二进制，并保留源目录形状：`engine/src` → `<root>/src`、
   `engine/apps` → `<root>/apps`、`engine/shaders` → `<root>/shaders`、
   `engine/tests/data` → `<root>/tests/data`、`engine/tests/golden` →
   `<root>/tests/golden`、`engine/assets` → `<root>/assets`。仅复制
   `tests/data` 到根目录会生成错误的 `<root>/data`；全新 VM 上不能依赖旧目录。
   二进制须按清单逐项部署，不能只复制 `test_*`：demo、verify 和 fuzz 可执行
   文件同样在清单中；默认配置也可能需要 `libscreen.so.1` 和 `libcrypto.so.3`，
   ABI/Vulkan 配置还需要 `libvulkan.so.1`、`libshaderc_shared.so.1` 和
   `libc++.so.2`；
3. 将 `<根父目录>/src` 链接到 `<root>/src`（例如 `/tmp/bt` 使用 `/tmp/src`），
   满足部分测试的 `../src` 回退读取。默认/Vulkan 配置应使用不同部署根，
   避免覆盖二进制和混用 shaderc；不同源码树并发验证应使用独立 VM；
4. 宿主生成清单：
   `python3 engine/tools/qnx/gen_target_cmds.py <build-dir> "$PWD/engine" <root> cmds.txt`。
   它复刻 `-LE "graphics|fuzz"`，剔除宿主 CMake 脚本测试并保留 WILL_FAIL；
5. 将清单复制为 `<root>/cmds.txt`，目标侧运行：
   `BREAK_QNX_TARGET_ROOT=<root> timeout 1800 sh <root>/run_target_suite.sh cmds.txt`。
   运行器设置 8 MiB 栈和正确的动态库路径，EXPECT_FAIL 的非零退出计为通过。
   QNX ASan/UBSan 清单另设 `BREAK_QNX_ON_AD=1`，由运行器给每个测试进程加
   `on -ad`，不是全局关闭 ASLR；普通清单保持 0。曾漏掉该包装导致 7/192，
   不能据此判断产品失败。完整 ASan 等需要更大栈的套件可用
   `BREAK_QNX_STACK_KB=32768`，其余场景保持默认 8 MiB。QNX ASan 需要独立子进程的 helper 可通过
   `BREAK_QNX_NORMAL_ROOT=<同源码普通构建部署根>` 使用普通子二进制，避免第二份
   ASan HighShadow 冲突；这不等于子进程有 ASan 覆盖。`BREAK_QNX_IPC_CHILD`
   可单独覆盖 IPC 子模式路径。测试临时目录默认为 `<root>/tmp`，可用
   `BREAK_QNX_TMPDIR` 覆盖；不要依赖 `/tmp` 所在的小容量 IFS 或原系统分区，
   尤其创建大文件时必须检查空间；
6. graphics 标签测试不在清单内，必须另外部署和运行（见 §4.3/§4.4）。部署前用
   `df -h` 和 `df -g` 同时检查块与 inode；QNX6 可在有空闲块时因 inode 用尽
   返回 ENOSPC。交叉构建目录中的 QNX ELF 不能由宿主 CTest 直接执行。
   本轮改为独立 VM 叠加系统盘和新增的 4 GiB 测试盘（65536 inode），挂载于
   `/data/break-tests`，未改写原 VM 磁盘。基础镜像没有 `mkqnx6fs` 时，可从
   SDP 的 `<arch>/sbin` 部署该工具；`mkqnx6fs` 和 `mount` 只允许用于明确新增
   的空白测试盘，不得对原系统盘或已有测试盘执行格式化/强制修复。

### 4.2 宿主 QNX 平台模拟（无 SDP 时验证接线）

用一个声明 `CMAKE_SYSTEM_NAME=QNX`、实际用宿主 gcc 的工具链文件配置，
引擎按 qnx 平台分支编译（poll 后端、headless RHI、默认 dummy PAL），
全部 headless 测试照常运行。它验证平台接线与 POSIX 代码路径，
**不**验证 qcc 工具链、Neutrino 目标机运行时或原生 Screen PAL——那需要
§4.1、§4.4 与真实目标环境。

### 4.3 显式 Vulkan、shaderc 与引擎 Screen 运行时

历史基线用 shaderc v2025.3（提交
`8c2e602ce440b7739c95ff3d69cecb1adf6becda`，依赖由该提交的 DEPS 固定）
构建目标库。当前 QNX 构建在该固定源码上应用 `engine/tools/qnx/shaderc-qnx.patch`，
把上游 `GlslangInitializer` 的 `new std::mutex` 8 字节永久分配改为静态 mutex 对象；
AArch64/x86 的补丁构建均已完成，见 `build-validation/shaderc-aarch64le-static-mutex-build.log`
和 `shaderc-x86_64-static-mutex-build.log`。构建证据不代替目标运行验收：

```bash
export SHADERC_SRC=/tmp/shaderc-qnx-v2025.3
# 在该源码目录执行一次 python3 utils/git-sync-deps，拉取 DEPS 固定的依赖。
cmake -S "$SHADERC_SRC" -B /tmp/shaderc-qnx-x86 \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/engine/toolchain-qnx.cmake" \
  -DQNX_ARCH=x86_64 -DCMAKE_BUILD_TYPE=Release \
  -DSHADERC_SKIP_TESTS=ON -DSHADERC_SKIP_EXAMPLES=ON \
  -DSHADERC_SKIP_EXECUTABLES=OFF -DSHADERC_SKIP_COPYRIGHT_CHECK=ON \
  -DSHADERC_SKIP_INSTALL=OFF
cmake --build /tmp/shaderc-qnx-x86 --target shaderc_shared -j
```

保持上游安装/可执行目标的默认组合，避免非默认组合的安装导出问题。
aarch64le 只替换 `QNX_ARCH` 和构建目录。随后配置完整 Vulkan 引擎：

```bash
cmake -S engine -B /tmp/build-qnx-vk \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/engine/toolchain-qnx.cmake" \
  -DQNX_ARCH=x86_64 -DENGINE_RHI_BACKEND=vulkan \
  -DENGINE_TEST_SOURCE_ROOT=/tmp/break-qnx-validation \
  -DSHADERC_LIB=/tmp/shaderc-qnx-x86/libshaderc/libshaderc_shared.so \
  -DSHADERC_INCLUDE_DIR="$SHADERC_SRC/libshaderc/include"
cmake --build /tmp/build-qnx-vk -j
```

目标侧还需部署 `libvulkan.so.1`、`libscreen.so.1`、SONAME 为
`libshaderc_shared.so.1` 的库及 `libc++.so.2`。从 Vulkan 构建重新生成清单；
`test_qnx_shaderc` 在目标 CPU 上把真实顶点/片元 GLSL 编译为 Vulkan 1.2 /
SPIR-V 1.5，检查魔数与 4 字节对齐，**不需要也不证明 GPU**。

引擎 Platform 的基础 Screen runtime 与输入 runtime 可用独立默认 RHI 构建，
不必与 myui Screen PAL 或 Vulkan 产物混用：

```bash
# 宿主：构建两个引擎 Platform 测试。
export QNX_ENGINE_SCREEN_BUILD=/tmp/build-qnx-engine-screen
export QNX_ENGINE_SCREEN_TARGET_ROOT=/tmp/break-qnx-engine-screen
cmake -S engine -B "$QNX_ENGINE_SCREEN_BUILD" \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/engine/toolchain-qnx.cmake" \
  -DQNX_ARCH=x86_64 -DMYUI_PAL=dummy -DENGINE_QNX_SCREEN=ON \
  -DENGINE_BUILD_TESTS=ON \
  -DENGINE_TEST_SOURCE_ROOT="$QNX_ENGINE_SCREEN_TARGET_ROOT"
cmake --build "$QNX_ENGINE_SCREEN_BUILD" -j --target \
  test_platform_qnx_screen_runtime test_platform_screen_input_runtime

# 宿主：生成 Screen 软件虚拟显示器运行时树。
export QNX_SCREEN_STAGE_HOST=/tmp/qnx-screen-runtime
python3 engine/tools/qnx/stage_screen_runtime.py \
  --arch x86_64 --output "$QNX_SCREEN_STAGE_HOST"
```

将两个测试二进制部署到目标机 `$QNX_ENGINE_SCREEN_TARGET_ROOT/bin`，完整
runtime 树部署到其 `runtime` 子目录。宿主输出目录与目标机目录是不同命名
空间，以下变量均可替换，不要求目标机路径与宿主 `/opt` 或 `/tmp` 布局相同：

```sh
# 目标机：Screen runtime 与两个测试均使用远端 timeout。
export QNX_ENGINE_SCREEN_TARGET_ROOT=/tmp/break-qnx-engine-screen
export QNX_SCREEN_RUNTIME="$QNX_ENGINE_SCREEN_TARGET_ROOT/runtime"
export QNX_SCREEN_TEST_BIN="$QNX_ENGINE_SCREEN_TARGET_ROOT/bin"
export LD_LIBRARY_PATH="$QNX_SCREEN_RUNTIME/lib:$QNX_SCREEN_RUNTIME/usr/lib:$QNX_SCREEN_RUNTIME/lib/dll:$QNX_SCREEN_TEST_BIN${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
"$QNX_SCREEN_RUNTIME/sbin/screen" \
  -c "$QNX_SCREEN_RUNTIME/graphics-virtual-display.conf" &
cd "$QNX_SCREEN_TEST_BIN" || exit 2
BREAK_QNX_SCREEN_REQUIRED=1 timeout 60 ./test_platform_qnx_screen_runtime
BREAK_QNX_SCREEN_REQUIRED=1 timeout 30 ./test_platform_screen_input_runtime
```

`test_platform_screen_input_runtime` 的真实输入、其他 source window 过滤、
native property resize/WSI 状态、真实 manager close，以及异源窗口和未知
subtype 的负向过滤，已有普通及 ASan/UBSan 各 4/4 定向结果（§5.3）。
宿主 CTest 不能执行 QNX ELF，远端 `timeout` 不可省略；内部 watchdog 也不
替代进程级 timeout。

脚本不安装 Vulkan ICD。`graphics-headless.conf` 在当前 VM 上不能创建窗口
（errno 48），所以运行测试使用 `graphics-virtual-display.conf`。测试不可用时
默认返回 77；`BREAK_QNX_SCREEN_REQUIRED=1` 将这种情况变为失败，防止把缺少
服务静默记为通过。这些引擎测试不包含 GPU present、物理 HID 或物理显示器；
myui PAL 的原生事件注入与控件 E2E 见 §4.4。

### 4.4 myui Screen PAL 定向构建、部署与运行（2026-10-27）

以下五个功能/性能定向目标只在 `MYUI_PAL=screen` 时注册：
`test_mypal_screen_runtime`、`test_mypal_screen_failures`、
`test_mypal_screen_concurrency`、`test_mypal_screen_present` 和
`test_myui_screen_e2e`。另有 `test_mypal_screen_stability`，覆盖 500 次
生命周期、可调时长 command/frame soak 和 1 秒无节流回归。六个目标的当前
分项结果见 §5.2，新增失败路径与无 EGL 结果见 §5.6，不代表全树。
六个目标均带 `graphics` 标签，不进入默认 headless 155 项或 Vulkan 156 项
历史清单，必须单独部署；宿主 CTest 只负责注册/构建，不能执行交叉出的
QNX ELF。

```bash
# 宿主：独立构建目录和独立目标部署根，避免覆盖默认/Vulkan/ASan 产物。
export QNX_SCREEN_BUILD=/tmp/build-qnx-myui-screen
export QNX_SCREEN_TARGET_ROOT=/tmp/break-qnx-myui-screen
export QNX_SCREEN_STAGE_HOST=/tmp/qnx-myui-screen-runtime
cmake -S engine -B "$QNX_SCREEN_BUILD" \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/engine/toolchain-qnx.cmake" \
  -DQNX_ARCH=x86_64 -DMYUI_PAL=screen -DENGINE_QNX_SCREEN=ON \
  -DENGINE_BUILD_TESTS=ON \
  -DENGINE_TEST_SOURCE_ROOT="$QNX_SCREEN_TARGET_ROOT"
cmake --build "$QNX_SCREEN_BUILD" -j --target \
  test_mypal_screen_runtime test_mypal_screen_failures \
  test_mypal_screen_concurrency test_mypal_screen_present \
  test_myui_screen_e2e test_mypal_screen_stability
python3 engine/tools/qnx/stage_screen_runtime.py \
  --arch x86_64 --output "$QNX_SCREEN_STAGE_HOST"
```

将六个测试二进制部署到目标机 `$QNX_SCREEN_TARGET_ROOT/bin`，并将完整
runtime 树部署到 `$QNX_SCREEN_TARGET_ROOT/runtime`。这两个目标路径可替换；
不要把宿主 stage 路径误当成目标机已经存在的路径。随后在目标机运行五个
功能/性能定向测试：

```sh
export QNX_SCREEN_TARGET_ROOT=/tmp/break-qnx-myui-screen
export QNX_SCREEN_RUNTIME="$QNX_SCREEN_TARGET_ROOT/runtime"
export QNX_SCREEN_TEST_BIN="$QNX_SCREEN_TARGET_ROOT/bin"
export LD_LIBRARY_PATH="$QNX_SCREEN_RUNTIME/lib:$QNX_SCREEN_RUNTIME/usr/lib:$QNX_SCREEN_RUNTIME/lib/dll:$QNX_SCREEN_TEST_BIN${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
"$QNX_SCREEN_RUNTIME/sbin/screen" \
  -c "$QNX_SCREEN_RUNTIME/graphics-virtual-display.conf" &
cd "$QNX_SCREEN_TEST_BIN" || exit 2
export BREAK_QNX_SCREEN_REQUIRED=1
for screen_test in \
    test_mypal_screen_runtime test_mypal_screen_failures \
    test_mypal_screen_concurrency test_mypal_screen_present \
    test_myui_screen_e2e
do
    timeout 120 "./$screen_test" || exit $?
done
```

稳定性二进制先执行 500 次生命周期，再执行 command/frame soak；其默认
`BREAK_SCREEN_STRESS_MS=10000` 只有 10 秒，30 秒验收必须显式设为 30000，
并保留远端进程级 `timeout`：

```sh
BREAK_SCREEN_STRESS_MS=30000 timeout 120 ./test_mypal_screen_stability
```

ASan/UBSan 使用另一组构建目录和部署根，配置时追加
`-DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON`，并部署 §6.2 所述 QNX
sanitizer SONAME/符号链接。不要与普通二进制混跑。目标侧仍使用独立 Screen
服务；五个功能/性能定向测试分别把启动命令替换为：

```sh
timeout 120 on -ad env \
  ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
  UBSAN_OPTIONS=halt_on_error=1 \
  "./$screen_test"
```

30 秒 sanitizer 稳定性复验使用：

```sh
BREAK_SCREEN_STRESS_MS=30000 timeout 120 on -ad env \
  ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
  UBSAN_OPTIONS=halt_on_error=1 \
  ./test_mypal_screen_stability
```

这里 `on -ad` 只作用于由它启动的测试进程，外层 `timeout` 只限制测试时长；
不全局关闭 ASLR。普通及 ASan/UBSan 的 500 次生命周期、30 秒 soak 和
1 秒无节流结果见 §6.4。上述定向通过不等于 QNX TSan、GPU、全部 QNX 套件
或其他负载/时长已验收。

无 EGL/GLES 运行库的环境使用独立的 `MYUI_GLES2=OFF` 构建目录，不修改已验证
的 ON 配置，也不提供虚假的空 GL 成功句柄：

```bash
cmake -S engine -B /tmp/build-qnx-screen-noegl \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/engine/toolchain-qnx.cmake" \
  -DQNX_ARCH=x86_64 -DMYUI_PAL=screen -DMYUI_GLES2=OFF \
  -DENGINE_QNX_SCREEN=ON -DENGINE_BUILD_TESTS=ON
cmake --build /tmp/build-qnx-screen-noegl -j --target \
  test_mypal_screen_runtime test_mypal_screen_failures
```

沿用上面的真实 Screen 服务和运行库执行这两个目标。OFF 配置调用
`my_pal_window_gl_enable[_api]` 必须返回 NULL；当前普通及 ASan/UBSan 分别为
runtime 15/15、失败注入 17/17，且 runtime 二进制的动态依赖不含 EGL/GLES。
该结果不代替 ON 配置的真实 ES2 驱动与像素验收。

## 5. 验证记录与当前边界

### 5.1 集成节点历史基线（2026-10-26，26e13732）

以下计数是 `26e13732` 集成节点在隔离 VM 与独立文件系统上的历史基线，
保留用于对照，**不是 2026-10-27 最新全量回归**：

- **Linux 宿主回归：182/182 通过**（`-LE "graphics|fuzz"`；
  `test_d3d12_dependency_gate` 为 Windows-only 设计内跳过）；
- **QNX SDP 8.0.0 x86_64 默认配置：全树 100% 构建**，目标机
  **155/155 命令通过**，覆盖引擎核心、net_loop/network、task、规则引擎、
  LOD/LOD cache/MSFT_lod、当时的全部 myui headless 用例和 verify 工具的
  WILL_FAIL 语义；
- **QNX x86_64 完整 Vulkan 配置：全树 100% 构建**，目标机
  **156/156 命令通过**（默认清单 + `test_qnx_shaderc`）。默认与 Vulkan
  使用不同部署根，`test_shader_io` 前后校验和一致；
- **引擎真实 Screen 窗口：2/2 通过**。软件虚拟显示器上创建/查询/显示/销毁
  `screen_context`、`screen_window`，尺寸/格式/usage/WSI 状态正确；
  注入 SIZE/FORMAT/USAGE/flush 失败时 context/window/event 各清理一次；
  显式 Vulkan 构建下 `SCREEN_USAGE_VULKAN` 断言通过；
- **目标侧 shaderc：2/2 通过**（真实 GLSL 顶点/片元 → Vulkan 1.2 /
  SPIR-V 1.5，检查魔数和 4 字节对齐）。x86_64 与 aarch64le 的
  `libshaderc_shared.so.1` 均用最终 toolchain 从固定 v2025.3 源码干净构建；
- **aarch64le：默认与完整 Vulkan 配置均全树 100% 构建**，产物经 `file`
  确认为 AArch64 QNX 动态可执行；本环境无 aarch64le 目标机，仍为
  COMPILED 证据；
- **GPU 运行时未通过且未误计**：显式部署并运行 `test_vulkan`，`engine_init`
  成功后在 Vulkan 设备创建处失败——loader 报 required instance extension
  `VK_KHR_surface` unavailable；`vulkaninfo --summary` 同样
  `vkEnumerateInstanceVersion failed with ERROR_INITIALIZATION_FAILED`。
  该 VM/SDP 只有 Vulkan loader 和 Screen 软件后端，没有 ICD/GPU；
- 该节点当时尚未覆盖 myui Screen PAL 与原生事件 E2E；2026-10-27 的定向
  进展见 §5.2。aarch64le 目标运行、非 VM 真硬件、GPU/交换链/present、
  物理 HID、文本/IME、剪贴板、显示器枚举和相对鼠标仍未因此获得验收。

历史目标机计数从 144/144 逐步扩展到 154/154，再到上述 155/155 与
156/156；中间 147/150、148/151 等失败均已定位：部署目录缺少
`tests/data`、`../src`/shader 回退路径错误、或部署清单缺失。相关修复与
防假绿检查见 §3。

### 5.2 myui Screen 同树定向结果（2026-10-27）

环境为 QNX SDP 8.0 x86_64、2 CPU / 4 GiB VM 和 Screen 软件虚拟显示器。
普通与 ASan/UBSan 配置分别部署；sanitizer 进程使用
`ASAN_OPTIONS=detect_leaks=1:halt_on_error=1`、
`UBSAN_OPTIONS=halt_on_error=1`，并仅通过 `on -ad` 启动测试。
`/tmp/qnx-screen-rgba-normal-suite1.log` 与
`/tmp/qnx-screen-rgba-asan-suite1.log` 记录同树 6 个定向命令的结果：

| 定向测试 | 普通 | ASan/UBSan | 本轮覆盖 |
|----------|------|------------|----------|
| `test_mypal_screen_runtime` | 9/9 | 9/9 | RGBA 双缓冲、native resize、loop/timer/command、quit drain、原生键鼠与 close |
| `test_mypal_screen_failures` | 15/15 | 15/15 | 冷 buffer、SIZE/BUFFER_SIZE、OOM、非阻塞 pending、timer 推进、累计 damage 与恢复 |
| `test_mypal_screen_concurrency` | 2/2 | 2/2 | 4 线程 command/timer、FIFO/wake 合并及 nested command |
| `test_mypal_screen_present` | 3/3 | 3/3 | dirty、非灰阶双缓冲历史、accepted post 与热路径计数 |
| `test_myui_screen_e2e` | 1/1 | 1/1 | 真实控件、280x220 native resize、canvas 重建、自动重绘与 close |
| `test_mypal_screen_stability` | 3/3 | 3/3 | 500 次生命周期、throttled soak、1 秒无节流回归 |
| **内部用例合计** | **33/33** | **33/33** | **仅 6 个独立部署的定向命令，不是全树** |

`test_myui_vgcanvas_backend` 在 Linux、QNX 普通及 QNX ASan/UBSan 均为
47/47，覆盖 RGBA 非灰阶、stride、透明混合和 soft canvas。普通 100 轮
present 与 30 秒长稳见 `/tmp/qnx-screen-rgba-present100-stability30.log`；
ASan/UBSan 30 秒长稳见 `/tmp/qnx-screen-rgba-asan-stability30.log`，
数据见 §6.4。上述两组 ASan/
UBSan 定向运行无消毒器报告，但不外推为所有路径、其他负载或 QNX TSan 结论。

`test_myui_screen_e2e` 的路径是 `my_window_manager` → 真实
button/edit/slider/progress → `event_dispatch` → software vgcanvas →
Screen LCD/post。除 button down/up、edit 的 `q`、slider down/move/up 和
manager close 外，本轮还注入真实 SIZE/property 到 **280x220**，检查根
widget、PAL size、LCD/canvas 重建和自动重绘；不是 explorer headless
selftest，也不是物理 HID 或显示像素验收。

该 E2E 的 ASan 初轮曾真实复现 heap-use-after-free，修复后最终定向运行无
消毒器报告。LCD 外包装在 resize 中保持稳定，只释放内部旧 buffer/mem
包装，不再让窗口/canvas 持有已释放 LCD。冷启动 resize 的根因是原生 SIZE
与 BUFFER_SIZE 不一致；现在两者同步，失败时旧 canvas/LCD 调用安全失败，
恢复保留 OOM 类别。已 post 像素仍不可读取，像素采样只发生在 begin 后的
当前 back buffer。

**历史局部组合（保留，不是最新计数）**：较早五测试阶段普通与 ASan/UBSan
曾各计 25/25，分别为 runtime 7/7、failures 13/13、present 2/2、
concurrency 2/2、E2E 1/1。该组合不包含 stability，也不包含后续 resize、
quit/fairness 修复，不能替代上述同树 33/33。

**本文引用的 `/tmp` 日志均为临时收据，均未归档**，不能把路径存在称为
证据已归档。当前主要收据及历史对照包括：

- `/tmp/qnx-screen-rgba-normal-suite1.log`、`/tmp/qnx-screen-rgba-asan-suite1.log`：
  同树 6 个定向命令各 33/33、软件后端 47/47 及最新 timer/present 数据；
- `/tmp/qnx-screen-rgba-present100-stability30.log`、
  `/tmp/qnx-screen-rgba-asan-stability30.log`：普通 100 轮 present、两种配置的
  500 次生命周期、30 秒 soak 和 1 秒无节流数据；
- `/tmp/qnx-screen-queue3-normal.log`、`/tmp/qnx-screen-queue3-asan.log`：
  早期 30/30 与性能数据，仅作历史对照；
- `/tmp/qnx-screen-stability-unthrottled-regression-unfixed-red.log`：
  submitted/executed 失衡的 fairness 红灯；
  `/tmp/qnx-screen-resize-ownership-normal1.log` 与
  `/tmp/qnx-screen-resize-ownership-asan1.log`：quit 丢弃已排队事件的红灯；
- `/tmp/qnx-screen-resize-green2.log`：过渡轮普通 9/9、13/13、1/1；
  `/tmp/qnx-screen-cache-final1.log`、
  `/tmp/qnx-screen-nested-green1.log`、
  `/tmp/qnx-screen-nested-asan-green1.log`：早期 runtime/present/concurrency
  历史结果；
- `/tmp/qnx-screen-present-ab1.log`、`/tmp/qnx-screen-present-base2.log`：
  早期 present A/B 与 swap interval 对照，不能与当前代码混作同条件 A/B。

### 5.3 合并前完整回归与当前边界（2026-10-27）

在最新 RGBA/完整帧修复之前、且尚未集成 `origin/master` 的 `7b6e7738`
时，前一版特性工作树已有以下独立复验；它们只是合并前历史基线，**最新
修复及合并后的源码仍须重新执行这些门禁**，不能转写为当前或合并后结果：

- Linux 普通 **182/182**、graphics **4/4**、TSan **182/182**、
  ASan/UBSan **182/182**；`test_d3d12_dependency_gate` 为 Windows-only
  设计内跳过。日志为 `/tmp/linux-current-full2.log`、
  `/tmp/linux-current-graphics.log`、`/tmp/linux-current-tsan.log` 和
  `/tmp/linux-current-asan3.log`，无 TSan/ASan/UBSan 报告；
- QNX x86_64 默认 **155/155**、完整 Vulkan **156/156**，分别见
  `/tmp/qnx-default-current-target-run.log` 和
  `/tmp/qnx-vk-current-target-run.log`。默认/Vulkan 的 native Screen 各
  **2/2**，目标 shaderc **2/2**。引擎 input/manager 普通及 ASan/UBSan 各
  **4/4**，已含异源窗口和未知 subtype 的负向过滤；这些 graphics 补充收据
  位于 `/tmp/qnx-current-screen-graphics-target2.log`；
- aarch64le 默认、Vulkan 和 Screen PAL 最新全树交叉构建均成功，日志为
  `/tmp/qnx-aarch64-current-build.log`、`/tmp/qnx-vk-aarch64-current-build.log`
  和 `/tmp/qnx-screen-aarch64-current-build.log`。产物为 AArch64 QNX ELF，
  但没有 ARM 目标机 runtime，仍只是 **COMPILED**；
- 最新 `test_vulkan` 探针仍在设备创建时失败：VM 没有暴露 `VK_KHR_surface`
  的可用 ICD，见 `/tmp/qnx-current-vulkan-probe.log`。该失败不伪装成 GPU
  通过，也不通过修改测试消除；
- 宿主 `/tmp` 曾耗尽并引发 VM 块设备 I/O 错误。保留日志、清理可再生构建
  目录后，剩余图形测试改在另一个可写部署目录完成；没有删除或强制修复
  测试盘。通用构建仍须同时检查宿主与目标空间，不能只检查目标 inode；
- 物理 GPU/ICD、物理 HID/显示器、原生文本 IME、clipboard、monitor 枚举、
  relative mouse、aarch64le runtime 和 QNX TSan 仍缺证据。软件虚拟显示器、
  accepted post、30 秒 soak 或交叉构建成功都不覆盖这些范围。主机 CTest
  也不能执行 QNX ELF，所有目标测试均须在目标侧运行并保留远端 timeout。

### 5.4 当前候选源码回归（2026-10-28）

以下是本轮实际执行的证据，后续合入新的上游提交后仍须重新执行相应门禁：

- Linux 普通 **185/185**、graphics **4/4**、Clang ASan/UBSan **185/185**、
  Clang TSan **185/185**；`test_d3d12_dependency_gate` 是 Windows-only 设计内
  跳过。ASan/UBSan 使用 32 MiB 测试进程栈、`detect_leaks=1` 和
  `halt_on_error=1`；Clang 消毒器构建关闭可选 IPO/LTO，未关闭消毒器或失败用例；
- QNX x86_64 默认清单 **157/157**、完整 Vulkan 清单 **158/158**，均在实际
  Neutrino 目标侧执行；目标 shaderc **2/2**。headless/CPU/WSI 契约和 shaderc
  结果不构成 GPU 证据；
- myui Screen 六个定向命令在普通与 ASan/UBSan 下各 **40/40**：runtime 14、
  failures 17、concurrency 2、present 3、E2E 1、stability 3。引擎显示器
  runtime 各 3/3、输入/manager 各 4/4，软件后端各 50/50；宿主 fake Screen
  普通及 ASan/UBSan 各 12/12。没有消毒器报告；
- 两种配置各完成 500/500 生命周期、1500 帧/posts，context 500/500、
  events 1000/1000、windows 500/500、buffer_sets 1000/1000，
  `live_allocation_errors=0`。30 秒长稳数据如下，不同配置不直接比较性能：

| 30 秒 throttled soak | 普通 | ASan/UBSan |
|----------------------|------|------------|
| commands（submitted=executed=destroyed） | 422,432 | 409,504 |
| frames=public posts=native accepted posts | 1,549 | 1,580 |
| `run_elapsed_us` | 30,011,670 | 30,003,900 |
| failed / FIFO errors / errors / watchdog | 0 / 0 / 0 / 0 | 0 / 0 / 0 / 0 |

- aarch64le 默认、Vulkan、Screen 三种全树交叉构建成功，`file` 确认是
  AArch64 QNX ELF；仍然没有 ARM 目标机运行证据。QNX TSan runtime 也未发现；
- `vulkaninfo --summary` 返回 `ERROR_INITIALIZATION_FAILED`，`test_vulkan`
  在设备创建时报告缺少 `VK_KHR_surface`，见本地临时日志
  `build-validation/qnx-vulkan-current-gpu-probe.log`。物理 GPU/ICD、物理
  HID/显示器、最终显示读回、完整 OS clipboard/IME 和 myui GL/Vulkan mount
  仍未验收。软件虚拟驱动还在配置解析时拒绝 `cursor`，所以 cursor 只验证了
  `NOT_SUPPORTED` 与资源回收，未验证正向物理形状；
- 本节的 `build-validation` 路径均为被 `.gitignore` 覆盖的本地临时日志，
  不是随仓库归档的收据。上述范围不能推出全部 QNX 功能、绝对最优、零泄漏或
  零 crash，也不满足原始的全功能合入主分支门禁。

### 5.5 最新上游合并后复验（2026-10-28）

合并最新 `origin/master` 后，重新构建并实际执行了以下门禁，不使用较早的
候选源码计数替代：

- Linux 普通、Clang ASan/UBSan、Clang TSan 各 **226/226**，真实 graphics
  **4/4**；一个 Windows-only 用例设计内跳过。X11 曾有一次连接失败，随后同一
  定向连续 10 次及完整 graphics 复验均通过，未隐藏首次失败；
- QNX x86_64 默认 **187/187**、完整 Vulkan **188/188**，目标 shaderc **2/2**。
  这些清单包含新增的 crypto/update/crash/editor 测试；不关闭这些模块或仅编译；
- myui Screen 六个定向命令普通与 ASan/UBSan 各 **40/40**，引擎显示器各
  3/3、输入/manager 各 4/4、软件后端各 50/50；crash 在两种配置各 36/36，
  没有消毒器报告；
- 普通与 ASan/UBSan 各完成 500/500 生命周期和 30 秒长稳，数据如下：

| 30 秒 throttled soak | 普通 | ASan/UBSan |
|----------------------|------|------------|
| commands（submitted=executed=destroyed） | 403,488 | 404,480 |
| frames=public posts=native accepted posts | 1,514 | 1,572 |
| `run_elapsed_us` | 30,001,236 | 30,018,323 |
| failed / FIFO errors / errors / watchdog | 0 / 0 / 0 / 0 | 0 / 0 / 0 / 0 |

- ARM 默认、Vulkan、Screen 三种全树交叉构建成功，产物为 QNX AArch64 ELF，
  仍没有 ARM 目标机或 QNX TSan runtime 证据；
- `BREAK_QNX_STACK_KB` 默认为 8192，可在完整 ASan 套件中设为 32768；运行器
  探针验证了该覆盖及独立 `TMPDIR`。GPU 探针仍因没有可用 ICD 而在实例/设备
  创建阶段失败，不能将完整清单、软件 accepted post 或 ARM 编译称作 GPU/物理
  硬件验收。完整 OS clipboard/IME、myui GPU mount、物理 HID/显示读回和支持
  cursor 的真实显示驱动仍缺证据，因此仍未满足原始的全功能合入门禁。
- 完整 QNX Screen ASan/UBSan 清单的首轮记录为 **182 通过、5 失败**。
  修复后复验为 **184 通过、3 失败**：RHI helper 与两个 myui 演示的引用/
  析构所有权已修复，编辑器 i18n 7/7、shell 81/81 已通过；两项编辑器测试的
  QNX 环境变量辅助路径改为显式持有 `putenv()` 字符串并释放旧项，断言不变。
  X11 ASan 的真实 `WM_DELETE_WINDOW` 与 `--palshot` 也通过，explorer 补齐了
  main loop 与 software canvas 析构，CTest 不再对这两个演示关闭泄漏检测。
- 基线 `test_break_crypto`、`test_break_update`、`test_break_update_client`
  曾无法通过 QNX ASan。GDB 与不链接项目/OpenSSL 的最小探针均复现 QNX libc
  TLS 数组扩容调用 ASan `realloc` 时的重入崩溃，详见 §6.2 的受限测试兼容
  与负向对照；未关闭检查或跳过用例。临时红灯收据包括
  `build-validation/qnx-screen-asan-full-red5.log`、
  `build-validation/qnx-screen-asan-full-latest.log`、
  `build-validation/agent-crypto-qnx-gdb-tls.log` 和
  `build-validation/agent-crypto-tls-probe-qnx.log`，均未随仓库归档。
- 合入图片预览上游线（`b8a36b65`）后，Linux 普通、ASan/UBSan、TSan 各
  **227/227**，真实 graphics **4/4**；QNX x86_64 默认 **188/188**、Vulkan
  **189/189**，包含新增图片测试。普通 Screen 六个定向命令仍为 **40/40**，
  引擎显示器 **3/3**、输入 **4/4**、软件后端 **50/50**。ARM 默认、Vulkan、
  Screen 全树构建均成功，但没有 ARM 目标机运行证据。上述结果不消除 QNX
  runtime 本身的 TLS 兼容性限制，也不覆盖 GPU、物理 HID/显示、完整 OS
  clipboard/IME。
- 最终完整 QNX ASan/UBSan 清单为 **189/189**，包含受限 TLS shim 的多线程
  回归；收据为 `build-validation/qnx-screen-asan-tls-capacity-final-target.log`。
  该结果只覆盖已接入的主线程及显式 worker 作用域，**不是通用 runtime 修复**，
  也不能据此宣称所有第三方线程、QNX TSan、GPU 或原始全功能验收已通过。
  最新 `test_vulkan` 仍在设备创建前报告缺少 `VK_KHR_surface`，见
  `build-validation/qnx-vulkan-image-preview-gpu-probe.log`。因此当前仍不满足
  原始的全功能推送与主分支合入门禁，不能擅自缩小验收范围。

### 5.6 当前失败路径修复与复验（2026-10-29 起，2026-11-03 更新，未收口）

以下是当前工作树的既有收据与进行中状态，不替代最终上游合并后的完整门禁；
正在复跑的项目不由旧收据预判本次退出码：

- Linux 普通、Clang ASan/UBSan、隔离 Mesa TSan 均为 **235/235**，每条均有 1 个
  Windows-only 平台设计内跳过，包含实际图形用例且无 suppression。普通及 ASan
  图形使用隔离 Xvfb/Mesa，ASan 保持 LSan 并使用 32 MiB 栈。精确 Mesa 26.0.8
  插桩证实 `lp_fence_signal` 与 `lp_fence_signalled` 的真实读侧竞态；隔离实验
  驱动在 `lp_fence_signalled` 的 SW fence 读侧使用同一 mutex 后，完整 TSan
  **235/235**，见 `build-validation/linux-final-tsan-test.log`。未修改系统 Mesa，
  未添加 `glFinish` 或减少 worker；这不是 QNX TSan 证据；
- QNX x86_64 默认完整清单既有 **191/191**、Vulkan headless 清单既有 **192/192**，
  见 `build-validation/qnx-default-current-target-run.log` 和
  `build-validation/qnx-vulkan-current-target-run.log`；两项最终复跑均在进行中。
  x86_64 完整 `test_vulkan` 已在保留全部场景后以退出 0 完成，见
  `build-validation/qnx-smp4/full-target-post-recovery.log`；Khronos validation layer
  仍未提供，该门没有通过；
- QNX 默认 ASan/UBSan 清单既有 **192/192**，保持 LSan、32 MiB 栈及全部断言，见
  `build-validation/qnx-default-asan-current-target-final-2.log`；独立 TLS opt-in
  既有 **197/197**，见 §6.6。两项最终复跑均在进行中。漏掉 `on -ad` 的 7/192
  部署失败已修正；死亡测试 helper 定向 2/2。`test_net_loop` 曾有间歇吞吐失败及
  失败路径泄漏，已补充 sent/received 诊断和清理，随后 20 次定向及既有完整清单
  通过，不把一次绿灯外推为绝无间歇问题；
- x86_64 Screen 普通与 ASan/UBSan 十项矩阵均全部通过：runtime **14/14**、
  failures **17/17**、concurrency **3/3**、present **3/3**、stability **3/3**、
  E2E **1/1**、display **3/3**、input **4/4**、软件 cursor **7/7**、GLES **5/5**。
  这是软件虚拟显示器与 CPU 路径的定向结果，不是物理 GPU、原生 Vulkan surface、
  最终显示读回或全树计数；
- 应用级 IPC 在 Linux 普通、ASan/UBSan、TSan 与 QNX x86_64 普通、
  ASan/UBSan 配置各 **10/10**。新增共享 debug allocator 压力和真实
  SIGUSR1/EINTR 用例，没有改用全局 malloc 或延长原 timeout。QNX 收据为
  `build-validation/qnx-ipc-fixed-target.log` 和
  `build-validation/qnx-ipc-fixed-asan-dummy-target.log`。后者使用独立 dummy PAL
  构建以避免无关图形运行库依赖，只对测试进程 `on -ad`，保留 LSan/UBSan；
  spawn 子进程使用普通二进制，未声称子进程有 ASan 覆盖；
- `MYUI_GLES2=OFF` 的最小 Screen 配置已在真实 QNX 运行 **15/15**，覆盖窗口、
  resize、输入、timer、clipboard/IME 边界和不可用 GL 的 fail-closed/资源平衡；
  `readelf -d` 仅列出 `libm/libscreen/libc/libgcc_s`，无 EGL/GLES 依赖。普通与
  ASan/UBSan 的失败注入均 **17/17**，收据为
  `build-validation/qnx-screen-noegl-runtime.log`、
  `build-validation/qnx-screen-noegl-failures-runtime.log` 和
  `build-validation/qnx-screen-noegl-asan-runtime.log`；
- `test_rhi_vk_present_recovery` 在真实 QNX + SwiftShader 上验证两组恢复：连续
  两次 post 失败后第三帧返回 OK；post 失败与 `OUT_OF_DATE` 同时发生时保留
  ERROR、重建交换链且下一帧返回 OK。两组 acquire/post/present 均配对，**2/2**、
  退出 0。原始第三次 acquire 失败与 25 秒超时见
  `build-validation/qnx-present-recovery-red.log`，组合错误覆盖红灯见
  `build-validation/qnx-present-out-of-date-red.log`，修复收据为
  `build-validation/qnx-present-recovery-green.log`；Screen post 故障/尺寸用例
  **7/7**、Screen stability **3/3** 见
  `build-validation/qnx-present-recovery-affected-tests.log`；
- myui offscreen Vulkan→LCD 普通运行 **11/11**、禁用版 **3/3**；Vulkan ASan
  **11/11** 已无泄漏报告，见 `build-validation/qnx-asan-libcxx-first-myui-vulkan.log`。
  Vulkan+TLS 组合的 4 项定向检查通过，123 字节故意泄漏仍被检出。GLES 的旧
  416 字节 `VK_ICD_FILENAMES` 恢复环境所有权问题已修复，GLES ASan **5/5** 无未预期
  LSan 报告，最终 ANGLE ASan 构建也已完成，见
  `build-validation/angle-patch-verify-full-2-asan-env-restore-build.log`。版本化
  ASan ES2 pbuffer 为 **64/64** 像素精确、bottom-up；
- 固定源码重建 ICD 的完整 x86 `test_vulkan` 已退出 0，golden MAE/max 为
  **0.33/1** 与 **0.64/1**，完整保留所有场景。计时复验的 500 帧墙钟为
  **126.60 秒**、平均 **3.9 FPS**、wall frame min/max **186.79/4080.50 ms**，
  simulation time 为 **50.00 秒**；见
  `build-validation/qnx-vulkan-final-metrics-target.log`。这些数字仅来自软件渲染及
  并行验证负载，不是硬件性能或绝对最优证明；Khronos validation layer 仍缺席；
- ARM 2307 的新 30000-inode 镜像已完成 headless **192/192**，见
  `build-validation/qnx-unsupported/arm-full-validation-2307/headless.log`。完整
  `test_vulkan` 与 ARM ASan 最终运行均未取得最终退出码，不能用 headless 清单、
  RT-only、离屏探针或定向 shaderc 结果替代完整 ARM 验收；
- shaderc 上游 `new std::mutex` 的 8 字节永久分配已由
  `engine/tools/qnx/shaderc-qnx.patch` 改为静态 mutex；AArch64/x86 均构建完成。
  ARM 定向 `test_qnx_shaderc` 为 2/2 且 `shaderc=0`，无未预期 LSan；故意 123 字节
  泄漏负向仍检出，见 `build-validation/qnx-arm-asan-static-mutex-target.log`。
  这不是 shaderc 全量 ARM 或 ARM ASan 全清单通过；
- `BREAK_QNX_SANITIZER_CLEANUP` 是仅限测试的退出清理选项，preload 顺序、未插桩
  helper 与限制见 §6.8。旧 ARM 全量使用被插桩 helper 的失败记录保留；新未插桩
  helper 尚未完成全量验收，不能宣称 ARM sanitizer 通过或零泄漏；
- 部署与运行器主机测试现为 **29/29**，含新增 `__pycache__`/`*.pyc` 缓存排除的
  红绿用例，见 `build-validation/qnx-arm-runtime-host-current.log`；tar/loopback
  部署包均排除这些缓存。`fetch_angle_qnx.sh` 的完整网络获取仍受 Google/CIPD
  可达性、Python 3.14 `ast.Str` 兼容和 LLVM Gitiles 映射阻塞，不能称成功；
- `_LIBCPP_HAS_NO_ASAN` 容器注解、Khronos validation、物理 GPU/原生 surface、
  QNX TSan、硬实时与绝对最优均未验证。历史失败记录不改写为通过；最终推送和
  主分支合并仍被上述未完成门禁及最终树复验阻止，当前不提交、不推送。

## 6. 效率验证（test_qnx_perf_smoke）

以下为历史吞吐下限断言（刻意宽松，sanitizer/慢 CI 下仍成立）与当时的
目标机实测，不代表最新同树复验：

| 子系统 | 断言下限 | 首轮 x86_64 VM | 隔离 VM 历史复验 | 合并 master 后历史复验 |
|--------|---------|----------------|------------------|------------------------|
| poll net_loop 数据报 | ≥256/s | 61,918 datagrams/s | 37,766 datagrams/s | 74,603 datagrams/s |
| task 系统（2 worker） | ≥5,000/s | 1,775,253 tasks/s | 568,877 tasks/s | 998,901 tasks/s |
| myui 离屏 vg 管线 | ≥20,000 ops/s | 97,799,511 vg ops/s | 50,314,465 vg ops/s | 107,526,882 vg ops/s |

三次历史运行均在 QNX 8.0.0 x86_64 QEMU/KVM、qcc/gcc 12.2 -O3 下通过；
这是 headless CPU/离屏吞吐收据，不是 GPU benchmark 或最优保证。后续数据
须按 §6.4 的同条件复验与完整回归流程更新，证据分级对齐
`docs/rhi_backend_evidence.md`。

### 6.1 时钟与定时器优化

以下为 2026-10-26 历史优化与验证记录，2026-11-20 同树复验数据见本节末段。
`test_platform_time` 以故障注入验证 EINTR 后按剩余时间续睡、永久错误不
忙循环、未来时间戳不造成无符号下溢以及多线程单调读取，当时 Linux 与 QNX
均为 **4/4**。`test_myui_window_manager` 的 238 个生命周期、OOM、嵌套
回调和释放用例当时在两个环境均通过。

定时器管理器由所属主循环拥有；跨线程通过 command/event 让主循环创建和
销毁定时器，不直接并发调用 manager。pending 提交改为一次线性扫描/压缩，
未提交项在 OOM 时保留原顺序供重试，避免反复头删和全量重索引。

| pending 提交（1 万个，5 轮中位数） | 优化前 | 优化后 |
|-----------------------------------|--------|--------|
| Linux Release | 90,175 µs | 80 µs |
| QNX x86_64 Release（同一编译参数） | 106,278 µs | 72 µs |

`test_myui_timer_concurrency` 的 4 个 producer 各投递 64 个 command，
每个 command 在主循环创建一个 one-shot timer。1/5/16/100 ms 四种周期在
Linux 和 QNX 均为 **256 次 command、256 次 timer 回调、0 失败**。延迟相对
期望触发时刻计算，负值来自毫秒向下取整，不表示单调时钟回拨；不把它
解释为微秒级硬实时保证。

| 周期 | Linux p50 / p95 / max | QNX p50 / p95 / p99 / max |
|------|------------------------|----------------------------|
| 1 ms | -29 / -16 / -14 µs | 179 / 204 / 205 / 205 µs |
| 5 ms | -249 / -84 / -83 µs | -168 / 908 / 911 / 912 µs |
| 16 ms | -110 / -94 / -91 µs | 640 / 662 / 663 / 665 µs |
| 100 ms | -117 / -78 / -76 µs | 799 / 806 / 807 / 807 µs |

**2026-11-20 同树复验（含时钟源对齐修复）**：高并发用例的期望触发时刻改由
`my_pal_time_now_ms()`（与定时器管理器同一时钟源）计算，并断言
`min 延迟 >= 0`，毫秒下取整不再产生负延迟伪象。QNX x86_64 目标机三轮复验
1/5/16/100 ms 均为 256 command / 256 回调 / 256 析构 / 0 失败，min 全部
非负（如 1 ms 周期 min 884–1065 µs、5 ms 周期 min 6–941 µs）；QNX
`test_platform_time` **5/5**（含 QNX 绝对 deadline 睡的三个故障注入用例），
`test_myui_timer_stress` 1 万 pending 提交 5 轮 79–112 µs。这些仍是软件
虚拟环境的及时性证据，不是微秒级硬实时保证。

### 6.2 消毒器与线程验证

Linux 历史完整 TSan（不排除 `test_async_loader`）为 **181/181、无竞态
报告**；另有 20 轮 async_loader TSan 定向重复。Linux ASan/UBSan/LSan 的
时钟、pending、并发和 async_loader 定向测试历史结果为 **4/4**。这些计数
不替代当前 Linux 完整重跑。

QNX 的 `ENGINE_USE_ASAN` / `ENGINE_USE_UBSAN` 也经过真实目标验证：
QCC 需要按 SDP SONAME 显式链接运行库（本环境 `libasan.so.8` /
`libubsan.so.1`），部署时提供 `.so.8.0.0` / `.so.1.0.0` 文件及对应
SONAME 符号链接。1 GiB VM 被 ASan 拒绝后改用 4 GiB；按运行库提示仅对
测试进程执行 `on -ad` 禁用 ASLR，不关闭系统默认 ASLR。随后
`test_platform_time`、`test_myui_timer_stress`、`test_myui_timer_concurrency`
和 `test_async_loader` 在 `detect_leaks=1`、`halt_on_error=1` 下通过，
没有消毒器报告。

较早五测试阶段的 Screen sanitizer 历史局部组合为 **25/25**，随后同树
6 个 Screen 定向命令曾各计 **33/33**。2026-10-28 合并后定向结果为 **40/40**，
包括 runtime 14、failures 17、concurrency 2、present 3、E2E 1、stability 3；
2026-11-03 最新十项矩阵见 §5.6。这些历史最终进程无消毒器报告，完整 ASan 清单的
独立结果见 §5.5。E2E 初轮实际
heap-use-after-free 已修复，不能把早期无报告写成当时没有该缺陷，也不能
把最终定向结果外推成所有场景或全树保证。QNX TSan runtime 当前仍未发现，
不宣称 QNX TSan 已验证。

**QNX SDP 8.0 ASan/TLS 测试兼容（仅限测试）**：独立探针和 GDB 证明，libc
扩容线程 TLS keydata 时调用 ASan `realloc`，释放旧数组又会读取同一数组中的
ASan 线程上下文，产生重入崩溃；不是 crypto/update 产品断言失败。为避免这个
runtime 缺陷掩盖真实产品问题，`engine/tests/qnx_asan_tls_capacity.c` 在三个
crypto/update 测试的 main 线程预分配 128 个槽位，退出时先恢复 libc 原数组再
释放新数组。CMake 只在 QNX ASan 下链接它，`_NTO_VERSION=800` 编译门禁防止
未审查的其他 TLS 布局静默复用；不链接产品库、不使用 `LD_PRELOAD`、不替换
分配器、不关闭 ASan/UBSan/LSan 或跳过原断言。

`test_qnx_asan_tls_capacity` 另有主线程与 8 个工作线程的 **2/2** 回归，每个
worker 显式进入作用域，执行 64 次 SHA-256 和分配器操作，调用
`OPENSSL_thread_stop()` 后再恢复。三个原测试为 **20/20、19/19、43/43**。
当前正式 shim 的负向对照仍能检出 9 字节写入 8 字节堆块及 123 字节泄漏，
见本地临时日志 `build-validation/qnx-tls-shim-negative-controls.log`。
**自动预留只覆盖 main 线程**；任意工作线程/第三方线程仍需各自经过验证的
作用域和清理顺序。该方案是 SDP 特定测试兼容，不是通用线程安全或官方
runtime 修复，也不构成 QNX TSan 证据。

后续通用化探针显示，`__cxa_thread_atexit` 的回调**早于** pthread key
析构，因此不能用它保证在全部 key 清理完成后恢复 keydata；没有将这一假设
引入实现。公开的 [QNX SDP 8.0.5 OS libraries 更新说明](https://www.qnx.com/developers/docs/relnotes8.0/com.qnx.doc.release_notes/topic/8.0.5_prod_release_notes/8.0.5_os_libraries.html)
未提供本缺陷的 ASan 修复证据，已知问题文档需要 Download Center 权限；
这不等于断言新版无效，但在取得官方修复或可维护源码前，不盲目升级或加入
未经验证的 libc 内部钩子。

### 6.3 myui Screen 队列、定时器与 present 实测（2026-10-28）

Screen command 队列只在没有 pending wake 时发送一次唤醒，并持续到队列
真正清空才重置；嵌套投递复用同一唤醒。最新普通与 ASan/UBSan 的
`test_mypal_screen_concurrency` 中，1/5/16/100 ms 每种周期均由 4 个
producer 各提交 64 个 command，完成 **256 command、256 timer 回调、
256 次析构**，失败和 per-producer FIFO 顺序错误均为 0，每轮 **wakeups=2**。
旧 wake storm 用例的 256 command/257 wake 已降为 2；nested parent+child
也从红灯时的 3 次降为 2 次，两个 command 均只执行、析构一次。

最新延迟相对各 one-shot timer 的期望触发时刻计算，单位均为 µs，取自本地
临时收据 `build-validation/qnx-screen-image-preview-normal.log` 与
`build-validation/qnx-screen-image-preview-asan.log`：

| 周期 | 最新普通 p99 / max | 最新 ASan/UBSan p99 / max |
|------|--------------------|---------------------------|
| 1 ms | 1,290 / 1,291 | 1,405 / 1,407 |
| 5 ms | 1,328 / 1,328 | 1,362 / 1,364 |
| 16 ms | 1,334 / 1,334 | 1,412 / 1,413 |
| 100 ms | 1,377 / 1,378 | 1,427 / 1,429 |

测试参考门禁为提前量不超过 **1 ms**、**p99 ≤ 25 ms**、**max ≤ 250 ms**。
最新样本的 p99 实测仍为毫秒级且 `budget_ok=1`，但样本、VM 和负载有限，
不是硬实时或最优保证，也不证明其他负载下的尾延迟。

当前候选在其他后台验证任务运行时的复验仍为 **2/2**：1/5/16/100 ms 各完成
256 command、256 timer 回调和 256 次析构，失败/FIFO/超时均为零。对应 p99
分别为 **5,534 / 1,247 / 1,197 / 1,185 µs**，max 为 **5,535 µs**；嵌套
command 仍为 2 次 wake。`test_myui_timer_concurrency` 另为 1/1、每轮 256 次
回调与析构。收据为 `build-validation/qnx-screen-timer-current.log` 和
`build-validation/qnx-myui-timer-current.log`；该负载样本不与空闲样本混算性能。

2026-10-29 的 AArch64 定向 10 个可执行项均通过，1/5/16/100 ms 的
`screen_timer_latency` p99 最大约 2.134 ms。首轮 30 秒四生产者 soak 曾出现
`errors=1`、`watchdog_fired=1`；诊断证明不是 native 调用失败，而是高频零超时
poll 导致 backlog 和最终排空超过宽限。将有界 drain 从 64 调整为 256 后，标准
链接的完整测试为 **3/3**：500/500 lifecycle，`errors=0`、`watchdog_fired=0`，
总耗时 30.038 秒，deadline 后首次返回 3.421 ms、第二次排空 1.511 ms；命令的
submitted/executed/destroyed 均为 3,135,804，FIFO errors=0。首轮失败记录保留，
未缩短时长或修改门禁。

早期历史延迟保留如下，来源为 `/tmp/qnx-screen-nested-green1.log` 和
`/tmp/qnx-screen-nested-asan-green1.log`，不与最新样本混算：

| 周期 | 历史普通 p99 / max | 历史 ASan/UBSan p99 / max |
|------|--------------------|---------------------------|
| 1 ms | 667 / 668 | 1,135 / 1,137 |
| 5 ms | 654 / 654 | 1,766 / 1,767 |
| 16 ms | 1,668 / 1,669 | 792 / 793 |
| 100 ms | 1,692 / 1,692 | 786 / 787 |

最新 present 同样取自上述合并后临时收据。两种模式均显式设置
`swap_interval=0`，每个模式每轮 64 帧、共 5 轮，表中为轮耗时中位数；
small 模式提交 `{x=7,y=9,w=16,h=12}` dirty rect，full 模式提交完整 post。
耗时包括每次 acquire 的完整 shadow 恢复和实际 damage 保存，不能与早期
缺少完整帧保护的版本混作同条件优化对照：

| 配置 | small dirty 中位数 | full 中位数 | 每种模式 pointer / stride 查询 |
|------|--------------------|-------------|--------------------------------|
| 普通 | 4,828 µs | 4,246 µs | 0 / 0 |
| ASan/UBSan | 5,578 µs | 4,919 µs | 0 / 0 |

这些耗时只对应 **accepted post**，不是实际显示 FPS 或 GPU 渲染时间；不同
配置不直接比较性能，也不与早期不同代码版本混为 A/B 或据此断言 small 一定
比 full 快。已 post 像素不可读取，因此它不是最终显示内容的读回验证。

历史 present A/B 使用 `/tmp/qnx-screen-present-ab1.log`，测量口径同为
`swap_interval=0`、64 帧 × 5 轮中位数，但代码版本不同，仅作历史对照：

| 测量项 | 优化前 | 两个 buffer 包装缓存后 |
|--------|--------|------------------------|
| small dirty，64 帧轮耗时中位数 | 678 µs | 641 µs |
| full，64 帧轮耗时中位数 | 647 µs | 608 µs |
| 每种模式 320 帧的 pointer / stride 查询 | 320 / 320 | 0 / 0 |
| 8 帧缓存检查中的热路径 myui alloc / free | 非零（红灯） | 0 / 0 |

该历史 A/B 只说明当时同条件负载下缓存包装后的 accepted-post 吞吐变化，
不声称全局或绝对最优，也不测量 compositor/GPU 或最终显示延迟。
默认 `swap_interval=1` 的历史基线见 `/tmp/qnx-screen-present-base2.log`：
small 中位数 **1,066,676 µs**，full 中位数 **1,063,985 µs**，两种模式的
accepted post 都约为 60 Hz。该日志同时保留缓存计数断言红灯，所以只引用
交换间隔对照，不把它列为缓存正确性通过收据；缓存后的历史 2/2 结果见
`/tmp/qnx-screen-cache-final1.log`。

### 6.4 性能与长稳验收结果（2026-10-28）

定向工作按 **先测量 → TDD → 优化 → 同条件复验 → 完整回归** 执行。
以下是本特性分支 Screen 实现的 30 秒长稳收据；图片预览上游合并未修改该
路径，最新同树 10 秒并发与 present 复验见 §6.3，完整回归状态见 §5.5。
不同 sanitizer、swap interval、代码版本或负载的数据不混作同一性能对照。

**500 次完整生命周期**：普通与 ASan/UBSan 各自完成 500/500，均为
1500 帧、1500 次 public post 和 1500 次 native accepted post。两种配置的
`live_allocation_errors=0`，原生创建/销毁计数均平衡：

| 配置 | rounds | contexts 创建/销毁 | events 创建/销毁 | windows 创建/销毁 | buffer_sets 创建/销毁 |
|------|--------|--------------------|------------------|-------------------|------------------------|
| 普通 | 500/500 | 500/500 | 1000/1000 | 500/500 | 1000/1000 |
| ASan/UBSan | 500/500 | 500/500 | 1000/1000 | 500/500 | 1000/1000 |

这些计数只证明该测试内的释放与帧/post 配对，不能外推为所有场景绝无泄漏或
异常。30 秒 throttled soak 使用默认 swap interval，`display_fps` 未测量；
普通与 ASan 运行配置不同，不能直接比较性能：

| 30 秒 soak（有界 drain 调整后） | 普通 | ASan/UBSan |
|------------|------|------------|
| commands（submitted=executed=destroyed） | 3,841,920 | 3,838,720 |
| frames=public posts=native accepted posts | 1,803 | 1,802 |
| dirty frames（另有 2 个 prime frames） | 1,801 | 1,800 |
| `run_elapsed_us` | 30,015,157 | 29,999,891 |
| failed / FIFO errors / errors / watchdog | 0 / 0 / 0 / 0 | 0 / 0 / 0 / 0 |

**1 秒无节流回归**：两种配置均完成 submitted/executed/destroyed 平衡，
`failed=0`、`fifo_errors=0`、`errors=0`、`watchdog_fired=0`，并交付 63 帧
（2 个 prime + 61 个 dirty）及对应 63 次 accepted post：

| 1 秒无节流 | 普通 | ASan/UBSan |
|------------|------|------------|
| commands（submitted=executed=destroyed） | 5,434,811 | 2,372,816 |
| dirty frames | 61 | 61 |

主循环每批最多处理 256 个 queued event 后重新调度 timer，避免 queue
starvation；wake 合并保留。退出采用有限快照 drain，退出时已排队事件按
FIFO 交付，不能把无限新生产理解为退出后仍持续消费。上述批次吞吐只用于
核对公平性和生命周期，**不把不同配置的 commands/s 或帧数比较宣称为优化
提升**，也不把 accepted post 当成 display FPS。

最新 30 秒数据来自 `build-validation/qnx-screen-soak30-batch256-normal.log`
和 `build-validation/qnx-screen-soak30-batch256-asan.log`，两个定向进程均
1/1；同实现的既有完整 stability 为 3/3。ARM 原始日志为
`build-validation/qnx-arm-screen-stress/regression-test_mypal_screen_stability.log`，
500 次生命周期、30 秒 soak、1 秒无节流合计 3/3；其 3,135,804 条命令全部
平衡，errors/watchdog 为零，未缩短时间或修改门禁。临时收据均未随仓库归档。
它们与 §5.5 的定向命令共同证明限定测试门禁，不构成全部 QNX 功能、绝对
最优、硬实时或其他时长/负载的验收。

### 6.5 非官方 ARM 仿真与内存部署（进行中）

不依赖 VMware 的 ARM 路线使用固定提交 `01437f23c75260fc2fcbb24fbc08608947c88f40`
的 `joexue/qemu-virt` BSP、当前已许可的 QNX SDP 8.0，以及工作区内解压的
QEMU 10.2.1。实验文件和日志位于 `build-validation/qnx-unsupported/`；没有把
主机 Linux 二进制复制为 QNX 可执行文件，也没有把模拟设备写成物理 ARM 硬件。

完整镜像最初遇到设备树与 IFS 地址重叠、启动时未传入设备树及缺少
`devb-virtio`。现在改用装载地址 `0x40200000`、`startup-qemu-virt -u reg` 和
BSP 对应的 Cortex-A72。BSP 原先没有真正启动辅助 CPU；经真实 SMP2 启动
红灯复现后，`smp.c` 使用设备树声明的 PSCI/HVC `CPU_ON`。三次最小镜像启动及
自包含测试镜像的 SSH/`pidin info` 均同时显示 Processor1 和 Processor2。
这些是 QEMU 双核结果，不是物理 SMP 或硬实时证据。

当前 SDP 没有可复用的 ARM `devb-virtio`，不能把 `devr-virtio.so` 当作块驱动。
测试部署因此使用自包含 IFS 中的 `devf-ram`（256 MiB）和 SSH，VM 内存为
1 GiB，目标根为 `/var/bt`。该路径不需要修改原 VM 磁盘，但也不是完整磁盘
系统验收；virtio 存储仍单独待验证。SSH 密码仅限隔离测试镜像及本机转发端口，
不读取或上传宿主凭据。

默认、Vulkan、Screen 三份 ARM 命令清单已分别从对应交叉构建生成，默认清单
为 188 项、Vulkan 为 189 项。首轮默认目标测试已完整执行，结果为 **174/188
通过、14 项失败**，原始日志为 `default-target-1.log` 和 `failures-1/`。失败
包括缺少 Screen/Vulkan 运行库、源码资源路径、RTC 未初始化及性能/并发问题；
正在定向修复并复验，不能将首轮结果写成通过。

随后已用真实 ARM 运行库及源码映射复验原先 9 个缺库/资源测试，全部通过；
`test_editor_shell` 另为 **86/86**，`test_shader_io` 为 **59/59**，原 40 个
shader/source 读取失败已消失。收据为 `resource-retest-suite-1.log` 和
`resource-retest-source-followup-1.log`。这里只部署 Vulkan loader，**没有
因此获得 Vulkan ICD 或 GPU 能力**。`deploy_arm_suite.sh` 将上述依赖闭包、
`.so` 平铺部署及 `ENGINE_TEST_SOURCE_ROOT` 映射自动化，正在独立 VM 验证；
procmgr 映射在重启后需要重建。

RTC 使用 QEMU `virt` 的 PL031 设备，而不是修改时间断言。独立 VM 的目标时间
已恢复，`test_rule_engine_grl_surface` 为 **136/136**，`test_platform_time`
为 **4/4**，收据为 `arm-script/rtc-target.log`。镜像定制器的 4 项主机 Python
测试通过，并注册为 `test_qnx_arm_runtime_builder`（`host_tools`，不部署宿主
解释器到 QNX）。

可复现入口为 `engine/tools/qnx/run_arm_qemu.sh`，依赖上述固定提交的 BSP、
QNX SDP 和 `qemu-system-aarch64`。`qemu-virt-psci.patch` 保留 SMP 修复，
`build_arm_runtime.py` 生成带 SSH、RTC 和 RAM 文件系统的 IFS。仓库根目录下：

```sh
QNX_SDP_DIR=/path/to/qnx800 \
QNX_ARM_WORKDIR=$PWD/build-validation/qnx-arm-runtime \
engine/tools/qnx/run_arm_qemu.sh start
```

`QEMU_SYSTEM_AARCH64`、`QNX_ARM_BSP`、`QNX_ARM_SSH_PORT`、`QNX_ARM_RAM_MIB`
和 `QNX_ARM_MEMORY_MIB` 可覆盖默认值。指定 `QNX_SDP_DIR` 时脚本总会加载完整
SDP 环境，避免继承不完整的 `QNX_TARGET`。`stop` 只终止同一工作目录及指定名称的
测试 VM。镜像内的默认测试账户为 `root/root`，仅用于本机端口转发的隔离验证，
不是生产认证配置。

`deploy_arm_suite.sh` 默认使用 tar；`QNX_ARM_STORAGE=loopback` 显式选择预填充
QNX6 内存镜像，避免逐文件部署。默认 1 GiB、12000 inode 可用
`QNX_ARM_IMAGE_SECTORS` / `QNX_ARM_IMAGE_INODES` 调整。此路径要求
`ENGINE_TEST_SOURCE_ROOT=/var/bt/engine`、新的部署工作目录和没有活动 loopback
的隔离 VM，拒绝强卸其他挂载。镜像以 `sync=none` 挂载，**只是易失测试存储，
不具备掉电持久化保证**。完整测试需更大的 VM 内存和磁盘峰值空间：

```sh
QNX_SDP_DIR=/path/to/qnx800 QNX_ARM_SSH_PORT=2303 QNX_ARM_MEMORY_MIB=2048 \
QNX_ARM_WORKDIR=$PWD/build-validation/qnx-arm-vm \
engine/tools/qnx/run_arm_qemu.sh start
QNX_SDP_DIR=/path/to/qnx800 QNX_ARM_STORAGE=loopback \
QNX_ARM_SSH_PORT=2303 QNX_ARM_PASSWORD=root QNX_ARM_SSHPASS=/path/to/sshpass \
QNX_ARM_DEPLOY_WORKDIR=$PWD/build-validation/qnx-arm-deploy-new \
engine/tools/qnx/deploy_arm_suite.sh build-validation/qnx-arm-default run
```

SwiftShader 使用固定提交 `cddb5c91b23ff70a1f607ea31610aa0d7f4b5ad5`，
移植补丁为 `engine/tools/qnx/swiftshader-qnx.patch`。补丁覆盖 20 个文件，
包含 QNX 系统适配、256 字节 push constants、loader 所需扩展，以及
`DrawParameters.BaseInstance` 和 headless extent 修复；已做反向还原、前向重放
及逐文件比较。`MAX_PUSH_CONSTANT_SIZE=256` 是本次自定义移植，不是
上游默认值或硬件能力声明。MemFd 探针验证了 `SHM_ANON` 大小、映射共享、
FD_CLOEXEC、fork/exec 关闭和析构生命周期。

x86_64 与 AArch64 的 CPU 离屏测试都建立真实图形管线、render pass 和
64×64 RGBA 图像，通过 `vkCmdCopyImageToBuffer` 读回：左半纯红、右半纯绿，
**4096/4096 像素匹配**，FNV-64 均为 `0x6f44bfaaf3ac5383`。日志分别为
`swiftshader-validation/vulkan-offscreen-qnx-4.log` 与
`swiftshader-arm-validation/vulkan-offscreen-qnx-aarch64.log`。x86_64 引擎还
验证了 headless surface、真实 RHI 初始化和 CPU readback + Screen post；
`test_rhi_vk_screen_post` 故障、尺寸与 resize 测试 7/7，Screen 接受后的 480000 个 clear 像素
与 Vulkan 读回一致。它不使用 `VK_QNX_screen_surface`，也不等于物理 GPU 或
原生 swapchain。

修复后的 x86_64 完整 `test_vulkan` 已运行 806 秒并以退出码 0 完成，保留
500 帧、1000-draw、10K-entity、compute、材质、IBL、point shadow、GPU cull、
direct/deferred 和 post-process 场景；golden MAE/max 分别为 0.33/1 和
0.64/1。收据为 `build-validation/qnx-smp4/full-target-fixed.log`。当前环境没有
`VK_LAYER_KHRONOS_validation`，测试明确报告 validation gate 未启用，不能把这
一部分写成已通过。ARM 完整场景尚在不同耗时基线上继续验证，不能用 RT-only
或离屏探针替代该全量结果。

QNX SDP loader 的测试配置通过 `graphics_conf_redirect.c` 显式重定向，不修改
SDP 安装。按架构编译 helper 和 SwiftShader，部署对应架构的
`libvulkan.so.1`、`libc++.so.2`、`libgcc_s.so.1` 等真实依赖：

```sh
qcc -Vgcc_ntox86_64 -D_QNX_SOURCE -shared -fPIC \
  engine/tools/qnx/graphics_conf_redirect.c -o libgraphics_conf_redirect.so
# 对 AArch64 改用 -Vgcc_ntoaarch64le，不能混用两种 ELF。
```

测试 `graphics.conf` 的 `vk-icds` 指向目标上的 `swiftshader_icd.json`，JSON 的
`library_path` 指向同架构 `libvk_swiftshader.so`，`api_version` 为 `1.3.0`。
只对指定测试进程设置 `LD_PRELOAD=<helper>`、
`SWIFTSHADER_GRAPHICS_CONF=<配置文件>` 和 `BREAK_VK_HEADLESS_SURFACE=1`。
需要 Screen post 时另设 `BREAK_VK_SCREEN_POST=1`，需要图像收据时设置
`BREAK_VK_SCREEN_POST_PPM`。这些选项都不是默认全局开关；`BREAK_RT_ONLY=1`
只是短探针，不能替代完整 `test_vulkan`。

### 6.6 通用 TLS 拦截探针（限定 ABI，集成中）

在不改动现有限定 shim 的隔离实验中，QNX SDP 8.0 x86_64 的
`pthread_setspecific` 与 `__pthread_key_exit` 双符号拦截已通过真实目标探针。
兼容层在正常 ASan 分配器中预留 128 个 keydata 槽位，真实 key 析构返回后同步
仍需保留的槽位、恢复 libc 原数组并释放 replacement；没有替换分配器或关闭
sanitizer。ABI 探针测得 `_thread_local_storage` 为 120 字节、`__numkeys` 偏移
60、`__keydata` 偏移 64，不能把该布局套用到其他 SDP 或架构。

已核对真实目标探针：正常 return、显式 `pthread_exit` 和 deferred cancel 均保持
正确析构顺序。当前压力回归共 **520 个线程**（含 48 个 detached）、34,304 次
SHA-256、68,608 组分配/realloc、520 次真实 key 析构，`failures=0`；最终
`enter=521 leave=520`（main 在统计时尚未退出）。三个原 crypto/update 测试分别为
**20/20、19/19、43/43**。旧 shim 与新探针的小清单为 **6/6**，堆溢出仍由 ASan
检出，123 字节故意泄漏仍由 LSan 检出。

这些结果不是无限制的线程安全证明。异步取消、运行中 `dlclose`、fork、
enter/leave 或 key 析构内部取消仍未覆盖；QNX LSan 还报告目标线程未 suspend，
因此负向检出不能保证所有并发退出场景绝无漏报。该方案只作为**显式可选的
测试兼容层**，保留旧 shim、ABI guard、负向对照和未覆盖边界，不用全局 preload
或产品 runtime 替换冒充官方修复。默认 ASan/UBSan 完整清单既有 **192/192**，
独立 TLS opt-in 清单既有 **197/197**，含死亡测试及两个负向探针；两项最终复跑
均在进行中，不预判退出码。Vulkan+TLS 组合的 4 项定向检查也已通过，123 字节
故意泄漏仍被检出。仍不扩展为所有第三方线程模型、其他 SDP、AArch64 sanitizer
或硬件能力的保证。

QNX ASan 多进程另有 HighShadow 地址冲突：两个同时初始化的 ASan 进程可能争抢
同一影子地址，不能把它误报为产品内存错误。应用级 clipboard/IME IPC 在 Linux
普通/ASan/UBSan/TSan 及 QNX 普通均为 **8/8**；QNX ASan 父进程 spawn 普通子
模式二进制后也为 **8/8**，协议和泄漏检查保留，但子进程本身没有 ASan 覆盖。
该服务是显式启用的本机可信应用测试总线，不是系统剪贴板、原生 IME 或默认 PAL
行为，也不提供认证、加密、跨设备传输或持久化。

### 6.7 ANGLE/GLES 构建、环境所有权与证据边界

ANGLE 固定为 `db5eb421c4350138e291220646de7764987a07e3`，使用独立
SwiftShader CPU ICD，不把 ANGLE 的 SwiftShader 后端写成物理 GPU。
`engine/tools/qnx/angle-qnx.patch` 包含 QNX 平台宏、工具链、系统 loader 生命周期、
命令缓冲参数防护以及 ICD 环境变量所有权修复。构建入口会检查固定 revision 或
DEPS 指纹，并要求显式提供工具路径和 SDP，不写入本机 SDK 路径：

```sh
QNX_SDP_DIR=/path/to/qnx800 GN=/path/to/gn NINJA=/path/to/ninja \
  engine/tools/qnx/build_angle_qnx.sh ANGLE_SRC OUT_DIR
QNX_SDP_DIR=/path/to/qnx800 GN=/path/to/gn NINJA=/path/to/ninja \
  engine/tools/qnx/build_angle_qnx.sh --asan ANGLE_SRC ASAN_OUT_DIR
```

原始源码的补丁前向应用、反向检查及 GN 生成已通过，见
`build-validation/angle-patch-check-current-gen.log`；普通构建和 ASan 构建分别
验收，不能只凭 `git apply` 或 gen-only 代表运行通过。`fetch_angle_qnx.sh` 的完整
网络获取仍受 Google/CIPD 可达性、Python 3.14 已移除的 `ast.Str` 用法以及 LLVM
Gitiles 映射阻塞。本轮用同 revision 的本地依赖闭包完成编译验证，固定 jsoncpp
另经公开 GitHub archive 获取；这不等于完整网络获取已经复现或成功，网络获取门禁
尚未收口。

版本化部署使用 `engine/tools/qnx/stage_angle_runtime.py` 为同一个不可变目标目录
生成 `graphics.conf` 和 ICD JSON。它只生成配置，不自动收集或伪造运行库；调用方
仍须准备同架构的 ANGLE、SwiftShader、loader、libc++ 和 sanitizer 文件。不能覆盖
QNX 仍映射的旧 `.so`，也不需要停止 Screen 服务。`run_target_suite.sh` 在 Vulkan
与 TLS ASan 同时启用时把 `libc++.so.2` 放在 ASan 前。部署与运行器主机测试现为
**29/29**，包含新增 `__pycache__`/`*.pyc` 缓存排除的红绿用例，见
`build-validation/qnx-arm-runtime-host-current.log`；tar/loopback 部署包已排除各级
`__pycache__/` 和 `*.pyc`。

GLES 红灯曾精确表现为四次初始化各泄漏 104 字节，共 416 字节；符号化定位到
`ScopedVkLoaderEnvironment` 恢复 `VK_ICD_FILENAMES` 的 `setenv()`。QNX 修复在
设置阶段持有临时 `putenv()` 字符串，恢复阶段复用环境表内的原始 `name=value`
字符串，避免每次初始化重新分配。修复后的真实 QNX ASan GLES **5/5** 无未预期
LSan 报告，ES2 pbuffer 为 **64/64** 像素精确、bottom-up，见
`build-validation/qnx-unsupported/angle-swangle/logs/screen-asan-gles-env-restore-2304.log`
和 `es2-pbuffer-env-restore-2304.log`。没有添加泄漏抑制或跳过销毁。

QNX ASan 工具链需要 `_LIBCPP_HAS_NO_ASAN`，因为本环境缺少对应的 double-ended
libc++ 容器 ASan ABI。普通 ASan/UBSan/LSan 仍开启，但 **libc++ 容器注解未覆盖**；
不能把这些结果外推为所有 C++ 容器、其他 SDP、QNX TSan 或物理 GPU 的证明。

### 6.8 测试专用 sanitizer 退出清理（ARM 全量验收中）

`BREAK_QNX_SANITIZER_CLEANUP=1` 只用于显式 QNX 测试环境，要求
`BREAK_QNX_VULKAN_RUNTIME=1`，并禁止与 `BREAK_QNX_TLS_INTERPOSE=1` 同时使用。
运行器按进程设置的 preload 顺序固定为：`libc++.so.2` → `libstdc++.so.6` →
`libasan.so.8` → `libubsan.so.1` → 未插桩 `libqnx_sanitizer_cleanup.so` →
`libgraphics_conf_redirect.so`。该顺序由主机红绿用例钉住，但主机测试不替代目标
全量运行。

helper 的 destructor 分别定位 `libc++.so.2` 与 `libstdc++.so.6` 中的
`_ZN9__gnu_cxx9__freeresEv` 并调用，释放两个 C++ 运行库的 emergency pool。
**仅辅助库不插桩**，以避免 helper 自身的 sanitizer 插桩改变 finalize 顺序；被测
二进制仍保留 ASan/UBSan/LSan 和原断言，不使用 suppression，也不把死亡测试的普通
子进程说成有 sanitizer 覆盖。该兼容路径需要显式 Vulkan runtime，不是产品 runtime
的通用修复，不证明任意并发库析构或其他 SDP/架构安全。

旧 ARM 全量使用被插桩 helper 的失败记录保留在
`build-validation/qnx-arm-asan-full-cleanup-target.log`，不改写为通过。新未插桩 helper
的构建与动态依赖检查见 `build-validation/qnx-arm-asan-cleanup-uninstrumented-build.log`
和 `qnx-arm-asan-cleanup-readelf.log`；其 ARM 全量运行尚未取得最终退出码。静态
mutex 后的 shaderc 定向无未预期 LSan、123 字节故意泄漏负向仍检出，只是 §5.6 所述
定向证据，不代表新 helper 或 ARM ASan 全清单已验收。

## 7. 升级路径（后续里程碑）

1. SDP 交叉编译与真实目标 headless：2026-11-20 复验 x86_64 默认清单 **191/191**；
   既有 Vulkan 192/192、ARM 2307 headless 192/192 收据保留。ARM 完整 `test_vulkan`
   与 ARM ASan 最终退出码仍未取得，不能把早期成功或 ELF 编译替代当前运行；
2. Screen 分层验收：x86 普通及 ASan/UBSan 十项全矩阵通过，分项见 §5.6；ARM
   定向 10/10。引擎 CPU readback + Screen post 已核对像素，但 myui 不直接读取
   已 post 像素，物理 HID/物理显示器交互仍未覆盖；
3. myui Screen 有进程内 clipboard、非原生 IME 状态、keycap 文本、相对位移
   和显式应用级 IPC/软件 cursor；它们不等于完整 OS clipboard/IME 或原生
   cursor。原生能力仍需支持该能力的驱动/硬件验证，不能把可控替代路径当成
   原生能力验收；
4. GL/Vulkan/GPU/ICD：双架构 SwiftShader 离屏与 shaderc 各 2/2，x86_64 完整
   `test_vulkan`、Screen GLES 5/5 与显式 myui Vulkan canvas 11/11 已有定向结果；
   ARM 完整 `test_vulkan` 和 ARM ASan 全量仍未完成。Khronos validation、物理 GPU、
   原生 surface 和交换链没有证据，不能用 CPU 软件路径冒充；
5. 性能与稳定性：500 次生命周期、普通/ASan 30 秒 soak 和 1 秒无节流定向
   门禁已有结果；更长时间、其他负载和完整回归仍待验证，不能把不同配置
   的吞吐数字直接比较为优化提升；
6. QNX TSan：当前仍未发现可用 runtime，不把 ASan/UBSan 或无竞态的 Linux
   历史结果转写为 QNX TSan 证据；
7. `ENGINE_NET_LOOP_POLL` 在高 fd 数下的 tunable（稳态零数组重建已实现）；
8. 目标机套件纳入日常验证（可选 qconn/ssh CI lane；并发不同源码树仍应
   使用独立 VM 或独立源码根）。QNX ELF 必须目标侧执行，不能用宿主 CTest
   或编译成功代替运行验收；
9. 最终推送与主分支合并：2026-11-20 已完成 Linux 三配置 235/235 与 QNX x86_64
   目标机 191/191 的同树复验并推送/合并；ARM 完整 Vulkan、ARM ASan 全量、新 helper
   全量、物理 GPU、QNX TSan 与硬实时仍未验收，继续作为后续里程碑边界，不以
   定向绿灯缩小原始门禁。

## 8. 相关文件

- 平台描述符/契约：`engine/src/platform/platform_compat.h`、
  `engine/tests/test_platform_compat_simulated.c`
- QNX Vulkan WSI/ABI：`engine/src/platform/platform_vk_surface.c`、
  `engine/src/platform/platform_vk_surface_vkabi.h`、
  `engine/tests/test_platform_vk_surface_qnx.c`、
  `engine/tests/test_platform_vk_surface_abi.c`
- WSI 生命周期：`engine/src/platform/platform_wsi.h`、
  `engine/tests/test_platform_wsi_lifecycle.c`
- 引擎 Screen 窗口层与运行测试：`engine/src/platform/window_screen.c`、
  `engine/tests/test_platform_qnx_screen_runtime.c`、
  `engine/tests/test_platform_screen_input_runtime.c`（普通及 ASan/UBSan 各
  4/4，包含异源窗口和未知 manager subtype 负向过滤）
- myui Screen PAL 与选择/注册：`engine/src/myui/mypal/my_pal.c`、
  `engine/src/myui/mypal/screen/my_pal_screen.c`、
  `engine/src/myui/mypal/screen/my_pal_screen.h`、
  `engine/src/myui/mypal/CMakeLists.txt`、`engine/CMakeLists.txt`
- myui Screen 定向测试：`engine/tests/test_mypal_screen_runtime.c`、
  `engine/tests/test_mypal_screen_failures.c`、
  `engine/tests/test_mypal_screen_concurrency.c`、
  `engine/tests/test_mypal_screen_present.c`、
  `engine/tests/test_myui_screen_e2e.c`
- myui Screen 稳定性复验：`engine/tests/test_mypal_screen_stability.c`
  （500 次生命周期、30 秒 soak 与 1 秒无节流，普通及 ASan/UBSan 各 3/3）
- shaderc 目标测试：`engine/tests/test_qnx_shaderc.c`
- 时钟与定时器：`engine/src/platform/time.c`、`engine/src/myui/mypal/my_timer.c`、
  `engine/tests/test_platform_time.c`、`engine/tests/test_myui_timer_stress.c`、
  `engine/tests/test_myui_timer_concurrency.c`
- 效率冒烟：`engine/tests/test_qnx_perf_smoke.c`
- 目标机工作流：`engine/tools/qnx/gen_target_cmds.py`、
  `engine/tools/qnx/run_target_suite.sh`、
  `engine/tools/qnx/stage_screen_runtime.py`
- 工具链：`engine/toolchain-qnx.cmake`、`engine/CMakePresets.json`
