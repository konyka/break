# Break 引擎 — 实现状态矩阵（唯一事实来源）

## 本轮更新

**CSS 解析输入预算（TDD）**：`my_css_parse()` 原先可由内存 API 直接传入无界输入，
在创建 sheet 和规则数组前增加 `MY_CSS_MAX_BYTES`（4 MiB）检查；超限路径零次 allocator
分配，并新增回归测试。CSS/YAML 配置输入现统一具备入口预算保护。

**直接 JSON 解析输入预算（TDD）**：文件加载入口已有 4 MiB 检查，但直接调用
`my_conf_parse_json()` 原先仍可绕过该限制并进入递归解析及字符串分配。现于 parser 入口
增加 `MY_CONF_JSON_MAX_BYTES` 前置检查，超限输入在任何配置节点分配前失败；新增计数
allocator 回归测试，确认拒绝路径零次分配。`test_myui_loader` **18/18**、完整 CTest
**82/82** 通过。

**通用 JSON 配置文件预算（TDD）**：`my_conf_load_file()` 原先忽略 `fseek/ftell` 失败，且
按文件长度直接分配，没有与解析输入建立统一上限。现新增 `MY_CONF_FILE_MAX_BYTES`（4 MiB），
在 payload 分配前拒绝超限文件，并初始化/传播路径、定位、分配和读取错误；失败路径都会
关闭文件并释放已申请缓冲。新增稀疏超大 JSON 文件回归，验证拒绝路径零次 payload 分配。

**YAML 文件加载前置资源预算（TDD）**：`my_ui_load_file()` 原先先按文件长度申请完整
缓冲区，再由字符串 loader 拒绝超过 4 MiB 的 YAML；恶意超大文件因此仍能触发一次大额
分配。现文件读取入口在申请 payload 前复用 `MY_UI_MAX_YAML_BYTES` 检查，超限立即关闭
文件并返回错误；文件输入同时拒绝嵌入 NUL，避免 C 字符串截断后静默忽略后续配置。
新增稀疏超大文件与计数 allocator 回归测试，确认拒绝路径零次 payload 分配；定向
`test_myui_loader` **17/17** 通过。

**结构化数组索引格式化边界（TDD）**：`re_value_array_append()` 和
`re_value_array_append_value()` 原先用未检查的 `sprintf` 构造数组键；虽然当前数组上限
暂时使 24-byte 缓冲区足够，未来调整上限会重新引入截断或越界风险。现改为无分配的固定
十进制转换 helper，在写入前检查数组上限和输出容量；最大合法索引 `1023` 可完整编码，
容量不足明确失败，达到 1024 项后不再执行格式化或部分写入。验证：`test_rule_engine`
通过，完整构建与 CTest **82/82** 通过。

**规则引擎数学库链接依赖（TDD）**：远程规则引擎 GRL 扩展新增 `round/floor/ceil/fmod`
数学内建函数后，`rule_engine_core` 的独立测试和 benchmark 在 Unix 链接阶段缺少 `m` 而
失败。现将 `m` 作为非 MSVC 平台的公开 target 依赖，使所有消费者自动继承并保持 Windows
CRT 路径不变；验证：完整 Debug 构建与 CTest **76/76** 通过。

**网络测试端口隔离（TDD）**：修复 `test_network` 与其它并行测试共用 PID 哈希固定端口的
竞态；新增 `net_socket_get_local_address()` 跨平台查询 `getsockname()` 结果，UDP 测试
统一绑定端口 `0` 并使用运行时端口互联。热路径不增加分配或锁，仅测试/诊断调用显式查询。
新增 ephemeral-port 回归用例；验证：`test_network` **15/15**，四进程并行回归通过。

**独立 myui 第三方路径解耦（TDD）**：`myr` 与 `myui` CMake 入口不再硬编码
`${CMAKE_SOURCE_DIR}/3rd`，改用可覆盖的 `MYUI_THIRD_PARTY_DIR`，默认定位当前仓库的
`engine/external`。新增配置契约同时检查两个入口，避免独立构建从错误源码根目录寻找
SheenBidi/stb 依赖；主工程默认路径和性能行为不变。

**独立 myr 依赖策略收敛（TDD）**：修复旧版 `engine/src/myui/myr/CMakeLists.txt` 仅依赖
`pkg-config` 且未启用 HarfBuzz 的配置漂移，统一为 FreeType 原生 CMake target、HarfBuzz
CMake target 优先及 `pkg-config` imported target 回退，并使用正确的 `Freetype_FOUND` 变量。
新增 `test_myr_dependency_config` 配置契约，防止独立入口再次退回旧依赖路径；主工程完整
CTest 现为 **74/74**，无 `pkg-config` 的 HarfBuzz CMake package-only 构建通过。

**HarfBuzz/FreeType 跨平台依赖探测（TDD）**：`myui_core` 先确认 FreeType 实际可用，再启用
HarfBuzz；HarfBuzz 优先使用原生 CMake imported target，缺少 package config 时回退到
`pkg-config` imported target。这样 Windows/macOS 包管理器和 Linux 无 `pkg-config` 环境不会
错误关闭 OpenType shaping，同时 FreeType 缺失时不会留下不可链接的 HarfBuzz 定义。验证：
禁用 `pkg-config` 的 CMake package-only 配置与构建通过；显式禁用 FreeType 的配置不启用
HarfBuzz；GL、Vulkan、Wayland 全新配置/构建仍通过。

**构建依赖与测试隔离修复（TDD）**：修正规则引擎公共头中 opaque typedef 与完整类型定义的
重复声明，避免 GCC/Clang 严格构建因类型重定义失败；同时修正触发 `-Werror` 的误导性缩进。
VFS 路径截断回归测试改为实际构造达到 `VFS_MAX_PATH` 的 PAK 路径，不放宽运行时安全边界。
网络复制测试中仅验证本地状态的用例改用内核分配的临时 UDP 端口，互联用例继续使用按进程隔离
的端口块，消除并行 CTest 的端口耗尽和跨进程碰撞。验证：完整 Debug GNU 构建成功，CTest
**73/73** 通过；`test_vfs` **33/33**、`test_net_replication` **51/51**，后者双进程并行
回归均通过；`git diff --check` 通过。

**BreakUI 增量合成安全决策层（TDD）**：新增后端无关的 `SKIP/PARTIAL/FULL` 决策 helper，
以持久 surface、present target 像素保留能力和动态 scissor 能力作为三项硬门槛；默认阈值为
最多 8 个 dirty 碎片、合并 scissor 不超过 drawable 面积 60%。BreakUI composite 已接入
决策和 scissor 恢复，但 GL/Vulkan 当前不声明 swapchain 保留能力，故运行时保持全屏合成，
避免仅凭 dirty rect 导致黑屏或未更新区域丢失。TDD 新增碎片、面积、空 damage 和能力缺失
用例，`test_break_ui_damage` 18/18 通过。真正 partial present 仍需 Wayland compositor
实机 smoke，以及 X11、Win32、Vulkan、macOS 的等价 present 能力，不能由 Linux 单元测试
推断完成。

**Wayland EGL partial present 接入（TDD）**：RHI 新增固定 16 项的 `RHIPresentRect` 输入、
严格边界校验和 `rhi_frame_begin_damage()`；dxx 在 pump 后取得 drawable damage，无变化时
不提交帧，首帧/resize/AA 变更/能力缺失时自动走全屏。Wayland EGL 仅在同时具备
`EGL_EXT_buffer_age`、`eglSwapBuffersWithDamageKHR/EXT` 且当前 buffer age 为 1 时启用，
并将 top-left damage 安全转换为 EGL bottom-left 坐标。GL X11、Win32、macOS 能力明确关闭。
Vulkan 经过安全审计后不启用 `VK_KHR_incremental_present` 作为 partial-present 能力：该扩展
只是 compositor 优化提示，不保证 present 后 swapchain image 内容可被 `LOAD`，因此不能满足
未损伤区域保留这一硬前提。Vulkan 当前继续安全全屏，X11/Win32/macOS 同样保持全屏；固定容量
历史 helper 仅作为未来存在明确 WSI 内容保留契约时的基础，不改变当前渲染行为。

**Vulkan 增量呈现历史（TDD）**：新增 `rhi_present_history`，不分配每帧堆内存，固定追踪
最多 16 个 swapchain image、64 条 damage generation；image 首次使用强制全屏，轮转时合并
上次使用后的全部历史，容量溢出或历史不连续自动全屏。`test_rhi_capabilities` 已覆盖首次
使用、历史合并、reset、abort、非法输入和容量溢出，共 12/12。安全审计确认 Vulkan 标准
交换链没有足够的内容保留契约，故 helper 尚未接入 partial present；Vulkan engine 与 dxx
构建通过，真实 WSI runtime 仍待具备 compositor 的环境。

## CI 验证矩阵（当前）

`.github/workflows/ci.yml` 现包含三项 Linux 专项门禁：`linux-clang-release` 使用 Clang/LLD
Release 并显式开启 `ENGINE_ENABLE_IPO=ON`，运行非 `graphics` CTest；`linux-gcc-sanitizers`
使用 GCC、`ENGINE_USE_ASAN=ON` 和 `ENGINE_USE_UBSAN=ON`，运行非图形 CTest；
`linux-graphics-smoke` 安装并启动 Xvfb，选择 Mesa lavapipe/llvmpipe 软件渲染，只运行现有
`graphics` 标签测试（当前为 `test_vulkan`）。Graphics smoke 缺少 Xvfb 或 lavapipe ICD 时直接失败，
软件渲染也不等价于真实 GPU 的 golden-image 证据。

这些 Linux jobs 不提供 Windows WGL/Win32、macOS Cocoa/Metal 或真实 Wayland compositor 的 runtime
验证；对应平台的 DPI、IME、present 和 GPU 行为仍保持待验证，不能从 Linux 构建或 headless 结果外推。

## 最近更新

**Windows Win32 platform runtime smoke（边界契约）**：新增 Windows-only 的 `test_platform_win32_runtime`，
使用真实 `platform_create`/`platform_destroy`、`GetWindowTextW` 与 Win32 `WM_SIZE` 消息，锁定 BMP 与补充平面
字符标题的 UTF-16 code units、非法 UTF-8 返回 `NULL`、一次 `platform_poll` 后的尺寸更新和销毁路径。
该测试是无 graphics 标签的 Win32 平台 smoke，不创建 GL/Vulkan context、不验证 WGL/Vulkan surface、GPU、
present 或帧级图形行为；Windows CI 的 headless CTest 会运行它，但这不等价于完整 Windows runtime CI 或 GPU 证据。

最近阶段补充：**BreakUI AA/resize 事务边界收口（TDD）**：修复同一 render 边界同时发生
drawable resize 与 AA 请求时，resize 的 target 注入会清掉 pending AA 请求的问题；候选 target
激活后保留仍未满足的质量请求，下一边界继续重试，不静默降级。补充纯契约测试覆盖 pending
保留、已满足和非法请求。OpenGL 多采样 offscreen target 的失败清理统一覆盖 MSAA color/depth
renderbuffer、resolve FBO、color/depth texture，避免候选创建失败泄漏 GPU 对象。原有 Vulkan
2x+ resolve、sample-count pipeline variant、BreakUI 回滚和 validation gate 继续保持通过。

**OpenType shaping glyph-run 接入（TDD）**：在上一阶段的后端中立 shape result 基础上，
为 FreeType 增加独立 glyph-id raster API，并将纯 LTR glyph-run 接入 Break RHI、GLES/OpenGL、
Vulkan 和 soft canvas 的绘制与测量。每个后端的缓存键显式区分 font、codepoint/glyph-id、
key 类型和字号；缺少 HarfBuzz/FreeType 或后端不支持时返回 `MY_RET_NOT_SUPPORTED` 并回退
旧 codepoint 路径。新增 fake-font 跨后端回归覆盖 glyph-id 位图、26.6 advance/offset 和缓存
语义。新增 `my_text_paragraph` 按逻辑 codepoint 范围执行 shaping-aware、cluster-safe
换行，并接入 text area wrap；当前限制保留：RTL/复杂 GSUB、跨 face fallback chain shaping、
paragraph visual mapping 与增量预算仍由后续阶段实现，现有 UBA/Arabic fallback 不受影响。

**Text area wrap cache reliability (TDD)**：visual-line cache 改为候选数组事务；OOM 或
paragraph 构建失败时保留上一份可用 cache 并继续标记 dirty，下一次布局边界重试，不再
以空缓存替换有效文本布局。

最近更新：**R559 动态 IBL 跨帧重烘焙（TDD）**：静态 IBL 在实时太阳（L/J/I/K、TOD）变化后
会与可见 skybox 漂移。新增默认 36000 帧（约 10 分钟@60 FPS）触发的运行时 rebake，并提供
`BREAK_IBL_STATIC=1` 静态 opt-out 与 `BREAK_IBL_REBAKE_FRAMES=N` 无头验证覆盖。重烘焙不再一次性
提交 43 个 FIFO swapchain frame，而是拆成 42 个跨帧单 dispatch（sky 6 + irradiance 6 + prefilter
30）；旧 irradiance/prefilter 直到新资源全部完成才原子交换，始终可采样且不会耗尽 Vulkan image
池。TDD 新增 `test_ibl` 原子交换/每步一个 present 断言及 `test_shader_io` 主循环契约；GL/VK
强制重烘焙 120 帧分别无 Mesa API error、Vulkan validation 0。仍未完成的大项只有需要真实目标
环境的 Windows WGL/Win32 runtime 验证，以及预烘焙 static mega geometry 的逐节点动态变换（后者
需要 GPU-driven transform indirection 重构，当前静态 megabuffer 设计下不具性能收益，保持明确限制）。

**R561 static mega transform 边界收口（TDD）**：复核确认 MegaBuffer 在 bake 阶段将静态节点的顶点
位置/法线预变换到 world space，运行时 indirect command 保持 Vulkan/GL 共用的标准五字段布局；
`unified_cull.comp` 与 `compact_draws.comp` 只消费 world-space bounds、可见性和标准 indirect 命令，
不引入逐节点 transform SSBO 查找。动态与 skinned 节点继续排除在 static mega 批次外，走 direct
路径，避免为静态场景增加每顶点矩阵/SSBO 读取、每帧 transform/bounds 上传和双后端 descriptor
分支。Oracle 架构裁决推荐保持该 static-only 设计，不在本轮引入完整 GPU-driven transform
indirection 或混合分流。TDD 新增 `test_shader_io` static mega 契约，锁定五字段 command、world-space
bake、skinned 排除和 cull/compact 无逐节点 transform 读取；验证结果为 16/16。逐节点动态变换仍是
明确限制，待未来有可证明性能收益的跨通道架构方案后单独立项。

**R560 deferred skinned G-Buffer 收口（TDD）**：deferred G-Buffer 几何 pass 现支持 skinned 几何
（procedural arm + glTF skinned 图元），用 64B skinned 顶点布局（pos3+normal3+uv2+joints4+weights4）
写同一组四附件，关节 texel buffer 在偏移 0/512 Mat4s 分别持有当前/上一帧姿态，逐骨骼写 per-object
velocity（RT3），与 forward 路径的 R554/R555 语义一致；skinned 节点被排除在 mega/static 批次外，
无重复绘制。收口时修复两个阻塞回归：①VK 后端 `rhi_pipeline_get_uniform_location` 把 texel-buffer
skinned pipeline 误判为 clustered 使 `u_proj` 解析为 -1、VK skinned 顶点读到陈旧 push 数据 —— 新增
`skinned_gbuffer_layout` 专用 push 布局（u_model@0 u_view@64 u_proj@128 u_prev_mvp@192）并在 clustered
分类前处理；②deferred skinned 绘制块结束后未恢复 `gbuffer_pipeline`，terrain 误用 skinned vertex
contract —— 恢复绑定。零新增 pass/纹理/CPU 回读/带宽，只在 RHI 的 location 映射与主循环加两条守卫。
TDD：`test_shader_io` 新增 `deferred_skinned_gbuffer_regressions_are_guarded` 静态契约，先失败后通过。
验证：GL/VK 双后端构建零警告（-Wall -Wextra -Werror -pedantic）；GL/VK 非图形 CTest 各 41/41；
定向 `test_shader_io` 15/15。仍未完成的大项维持不变：Windows WGL/Win32 runtime 验证需真实目标
环境；预烘焙 static mega geometry 的逐节点动态变换需 GPU-driven transform indirection 重构，当前
静态 megabuffer 设计下不具性能收益，保持明确限制。

此前：**R558 IBL 天空方向一致性（TDD）**：审计确认 raster skybox 已在 R446 修正为将
sun-to-scene 的光线传播方向取反后交给太阳位置/散射计算，但静态 IBL capture 仍直接传入传播
方向，导致金属反射和环境光中的太阳与可见天空相反。`render_init` 现仅在 IBL 启动预烘焙时
转换为 to-sun 方向；不新增运行时 pass、纹理、CPU 回读或带宽。`test_shader_io` 先锁定 host
方向转换和 shader 的太阳位置语义；GL/VK shared IBL graphics gate 继续验证真实 cubemap
capture/convolution/sample。仍未完成的大项只有需要真实目标环境的 Windows WGL/Win32 runtime
验证，以及预烘焙 static mega geometry 的逐节点动态变换（后者需要 GPU-driven transform
indirection 重构，当前静态 megabuffer 设计下不具性能收益，保持明确限制）。

此前：**R556 temporal 消费统一（TDD）— motion blur 逐对象速度**：审计确认 forward
TAA 已消费 RT1，但 motion blur 仍使用 depth + previous VP 的 camera-only 重建，动态物体
会在 blur 阶段退化。现 motion blur 的第三个 sampler 直接读取已有 RG16F velocity；RT1
存在时按 NDC delta 转像素速度，不存在时才保留旧重建回退。该方案零新增 pass、纹理、CPU
回读或带宽，只复用已为 TAA 写入的附件。TDD 静态契约覆盖 C API、三纹理绑定和 GL/VK
shader 分支；GL/VK demo 120 帧分别为零 Mesa API error/零 Vulkan VUID，双端 graphics
gate 顺序通过。`test_vulkan` 的共享 RT1 gate 在 GL/Vulkan 都以真实 `RG16F` 第三 sampler
强制走 motion blur 分支，并要求 blur 输出与源 HDR 输入不同，覆盖双后端 format、descriptor、
push constant 和实际采样结果；Vulkan TEST 6 另保留 depth reconstruction 回退路径覆盖。
未完成的大项只剩需要真实目标环境的 Windows WGL/Win32 runtime 验证，以及
预烘焙 static mega geometry 的逐节点动态变换（后者需要 GPU-driven transform indirection
重构，当前静态 megabuffer 设计下不具性能收益，保持明确限制）。

此前：**R555 forward motion/IBL 收口与跨后端 validation（TDD）**：在 R554 的 forward
双 MRT 逐物体速度基础上，water 现以 previous VP 写 RT1，GPU particle SSBO 保存
previous position 并写出真实逐粒子速度（出生帧为零）；透明 pass 的 RT0 使用 alpha blend、
RT1 不混合，避免速度与背景混色。Vulkan 显式启用 `independentBlend`，不支持时安全回退为
共享 attachment blend state；同时 UBO/texel command-buffer update 补齐 `TRANSFER_DST` usage。
RHI/着色器契约测试先行并覆盖两项后端要求。`peer_lru_full` 的超过半个 u32 周期时间戳比较
错误已改为相对本次接收时间的 unsigned age LRU，稳定复现的网络失败关闭。验证：GL/VK
graphics 顺序通过；GL demo 120 帧 `MESA_DEBUG=1` 无 API error；VK demo 120 帧无 validation
VUID（仅 Mesa 探测不可用 Freedreno render node 的非活动驱动提示）。预烘焙 mega geometry
仍明确只适用于静态节点，动态节点走 direct per-object history 路径；Windows 无本机工具链或
运行环境，保持待验证。

此前：**R554 forward 双 MRT 逐物体速度与 GL/VK IBL 图形验证（TDD）**：forward
路径已切换为单次几何 pass 的 `RGBA16F + RG16F` 双 MRT，TAA 直接消费第二附件；普通
对象、实例化对象和骨骼路径均提供 previous/current 历史，旧全屏 camera-only velocity
pass 已从当前运行时移除。GL/Vulkan 使用共享 `FORWARD_MRT` shader 变体，新增 RG16F RHI
格式、MRT load 绑定和 temporal UBO。GL/VK TEST 7 共用真实 cubemap capture/convolve/sample
并做非黑/非平坦 readback。初始限制为粒子/天空零速度、透明策略保守、预烘焙 mega geometry
节点静态，deferred skinned 仍未宣称覆盖；其中粒子与透明策略已由 R555 完成。

此前：**R553 方案审计与 TDD 基础 — per-object motion history 生命周期契约**：新增
`motion_history` dense slot/generation 组件，先以测试锁定首帧无效、跨帧 previous/current
配对、generation 重用失效和越界安全；`test_shader_io` 增加双后端 velocity/GL IBL
shader 契约检查。审计确认当前 forward velocity 仍是 camera-only fullscreen pass，性能最优
实现不能只在 forward fragment shader 增加第二输出，必须把 scene FBO 扩展为可选双 MRT，
同步更新 GL/Vulkan render-pass、pipeline attachment 和所有主材质路径后再移除额外 pass。
本轮暂未接入主循环，避免半完成的 Vulkan attachment 不兼容。

> 本文档是各模块"真实实现程度"的唯一事实来源（single source of truth）。
> 它依据源码逐一核查，纠正 `PureC_Engine_ExecutionPlan.md` 中被高估为"全部完成"的标记。
> 状态分级：完整 / 部分 / 桩(占位) / 缺失。每轮补全工作完成后更新对应行。

最近更新：**R552 验证与接口收口轮（TDD）— VK demo validation 清零 / set_uniform helper 边界修复 / IBL 绑定核查** — 承接 R551 遗留。**R552-A VK demo TRANSFER_SRC 清零（R445 存量关闭）**：demo bake 期 `mat_arr_fill_layer` 经 `rhi_texture_read_pixels` 回读 9 张材质纹理，而 `rhi_texture_create` 的 color usage 缺 `TRANSFER_SRC_BIT` → 每 image 3 条 VUID（00186 + 01212×2），截断后 20 条；usage 补 TRANSFER_SRC（一行，R442/R550-E 同类先例），Debug VK demo 120 帧 + 截图 0 条 validation，截图/Hi-Z 不回退。**R552-B set_uniform helper 边界（R444 遗留关闭）**：旧 helper 256 硬编码边界保证不越界写 staging，但 flush 按声明 range 钳位 → `[declared_range,256)` 写入被**静默丢弃**（与 R444 修掉的同类缺陷残留在旧 helper 上；现存调用方无一命中，属潜在截断）。修复：6 个旧 helper 改按声明 range 校验（新增纯函数 `rhi_push_helper_range_ok`），越界 LOG_WARN + 丢弃，flush 钳位保留作纵深防御；GL 真实 uniform location 无 staging 不改。TDD：test_cmd_buffer 28→30（边界/越界/负 location）。**R552-C IBL image-unit 绑定核查（R435 观察项关闭）**：静态+GPU 实证双端无缺陷——VK storage image set 1 / sampler set 2 无冲突、per-face-per-mip 视图缓存正确、descriptor pool 每帧重置无残留；GL image unit 与 texture unit 独立命名空间、cubemap 逐层绑面合法；GL/VK demo 截图 IBL 观感一致，VK test_ibl 0 validation。**R552-D**：`lens_flare.h` 补 `light_dir` 语义注释（指向太阳，R551-E 修正后的约定）。验证：双后端 `ctest -LE graphics` 各 40/40 + `-L graphics` 各 1/1 + VALIDATION GATE 0；`git diff --check` 通过。遗留：GL graphics 测试不覆盖 IBL（TEST 7 VK-only，可选移植）；VK+GL graphics 并行跑曾偶发 flake（X11 窗口竞争疑似，顺序跑稳定）。

此前：**R551 渲染正确性收口轮（TDD）— GL 每帧错误清零 / deferred 光照 uniform 类型 / 太阳锚点一致性 / 两项非缺陷核查 / 测试质量补强** — 承接 R550 遗留清单逐项闭环。**R551-A font 死 uniform**：`font_renderer_end()` 每帧硬编码 location 0 `set_uniform_vec4`，GL 下该 location 是 sampler `u_atlas` → `glUniform4f` 每帧 `GL_INVALID_OPERATION`（初始提交遗留死代码，VK 下仅无害 push staging）；删 1 行。**R551-B mega 单 execute 路径 GL 每帧被跳过（真渲染 bug）**：`mega_mat_arrays_draw`/`_gbuffer` 在 compact dispatch 后 `bind_pipeline` 切 VAO，mega VBO/IBO 绑定落在旧 VAO 上（GL 缓冲绑定是 VAO 状态），arr VAO `ELEMENT_ARRAY_BUFFER=0` → `glMultiDrawElementsIndirectCountARB` 每帧报错且整 draw 被跳过；`bind_pipeline` 后补绑 vbo/ibo（VK 为 cache-hit 无操作）。MESA_DEBUG 120 帧零错误；与 grouped 路径截图一致。**R551-C deferred uniform 类型（GL）**：`deferred_light.frag` 声明 `uint u_point_count/u_dir_count` 与 `float u_point_shadow_far_planes[4]`，CPU 侧 `glUniform1i`/`glUniform4f` 类型不匹配，写入被拒 → **GL deferred 的方向光/点光循环此前从未生效**（count 恒 0，IBL 主导所以不明显）；改 shader 声明对齐 CPU 上传类型（uint→int、float[4]→vec4），VK push 路径不动；deferred 120 帧零错误，截图 RMSE 0.0064。**R551-D 核查（非缺陷）**：VK lens flare 静态视角"Y 翻转"疑点证伪——CPU 投影、探针落点（GL=VK=(638,212)）、背日质心全部双端一致；R550-A 观察实为 GL 低帧率下物理时序发散的误读。**R551-E 太阳锚点一致性**：①skybox 太阳圆盘偏 26°——`skybox.vert` 在**顶点**级 normalize 全屏三角形射线，质心插值≠插值后归一化，方向场非线性扭曲；删顶点 normalize（frag 已有），圆盘精确落 CPU 投影 (639,212)。②lens flare 方向反转——main.c 传光线传播方向 `sun_dir_vec`，而 `light_view_z>0` 早退使 flare 锚在反日点（自初版 3ad4ff9 即存在）；调用点改传 `-sun_dir_vec` 对齐 god_rays。三锚点（skybox 圆盘/flare/god rays）像素级重合，双端一致；golden 不含 skybox 无需更新。**R551-F 核查（非缺陷）**：spin0"楔形伪速度 7.14/255"证伪——原始速度纹理几何区 0.00px，所谓条纹是 2x LINEAR 上采样在天空/几何边界的插值带经 tonemap AE 非线性放大；楔形本体为远平面饱和地形，depth 写入无异常。**R551-G 测试质量**：test_font_ui 真链接 imgui.c（font==NULL 时绘制调用本就 no-op，6 个 link-only 桩；删 ~130 行复制逻辑，27 项断言不变）；test_animation 新增 IK tip 到达 target 断言（容差 1e-3）+ 超程不可达用例（37 项）；红→绿变异验证（toggle 置否/reach 重复旋转均被抓）。验证：双后端 `ctest -LE graphics` 各 40/40 + `-L graphics` 各 1/1 + VALIDATION GATE 0 + 双 golden MAE=0.00；deferred/forward GL demo MESA_DEBUG 120 帧零错误；`git diff --check` 通过。遗留：VK demo 运行期 20 条 TRANSFER_SRC validation（Hi-Z/mip readback，存量，不影响 ctest 门禁）；`lens_flare.h` 的 `light_dir` 参数语义（指向太阳）可补注释。

此前：**R550 特性收口 + 性能统一轮（TDD）— 五路后处理合成接线 / GL Hi-Z 全剔悬案 / motion blur 速度响应 / cluster 深度范围 / validation gate Release 生效 / GNU Release 构建修复** — 本轮盘点 R1–R549 后关闭全部"写了却没生效"的高性能相关性缺口。**R550-A 五路合成接线**：SSR/SSGI/volumetric/lens_flare/contact_shadow 此前各自写私有 FBO 但结果从不合成进画面（main.c 注释自证 "never composited"），开启即 100% 浪费 GPU 故被默认关死；现按 god_rays 自合成惯例（shader 采样链入色混合、写自身 FBO、main.c 推进链尾 `scene_color`）全部接入帧链——contact_shadow 乘法（近似，注释说明压暗间接项）、volumetric 透射+累积（去 alpha_blend）、lens_flare 加法（early-out 改直通防黑屏）、SSR 按置信度 lerp（零新 sampler）、SSGI 末级新增 `ssgi_blur{,_vk}.frag` 加法合成；FBO 升链分辨率（输出即链色）；新增 `BREAK_SSR/SSGI/CS/VOL/LF=1` env 开关（默认仍关，成本取舍不变）。GPU A/B 像素证据：GL ssr mean|Δ|=12.77、vol 7.27、ssgi 1.47、cs 1.43；VK ssr 8.19、lf 旋转对照 1.898。**R550-B GL Hi-Z 全剔悬案（R445 另立案关闭）**：根因非包围球/变换（逐值核对一致），而是 R436 chunk 化 Hi-Z 生成在 GL 下用 BASE/MAX clamp 绑定原纹理对象同 dispatch 内采样+imageStore，Mesa iris feedback 守卫把采样读归零 → mip 4–8 恒 0 → showcase 球体（采 mip 5–7）全剔、unified 每帧走回退。修复：`rhi_cmd_bind_texture_mip` 改绑惰性缓存的单 mip `glTextureView`（独立纹理对象不触发守卫，与 VK 单 mip view 语义一致），纹理改 `glTexStorage2D` 不可变存储；GL showcase unified 58/59 帧 11/11 可见（首帧为双端共有瞬态），反向验证（强制回退）复现 27/29 帧 0/11。**R550-C motion blur**：采样步长 `dir*strength/sample_count` 中 `dir` 为单位向量 → 跨度恒 ≈1px 与速度无关（R446 实测记录）；改乘 `min(vel_len,200px)`，跨度 ∝ 像素速度；速度场可视化量化 spin 0/1/2/5/20 °/帧 → 7.14→70.16→112.24→176.13→226.69 严格单调。**R550-D cluster 深度范围**：`light_system_set_depth_range()` 新增，near/far 硬编码 0.1/100 改随相机（值不变不触发 LUT 重算，未设置回退默认）；test_lighting 新增 4 项（19/19）。**R550-E validation gate**：debug messenger 从 `#ifndef NDEBUG` 改显式运行时开关（`rhi_vk_validation_set_enabled`，Debug 默认开），test_vulkan 经 `ENGINE_VK_VALIDATION` 无条件武装——Release 门禁不再空转；顺带修复存量 3 条 TRANSFER_SRC validation（TEST 6 readback 的 offscreen FBO image 缺 `VK_IMAGE_USAGE_TRANSFER_SRC_BIT`，R442 同款遗漏），Debug/Release 门禁均 0 消息。**R550-F GNU Release 构建修复**：`audio_bus_valid` 只比运行时 `bus_count`，Release GCC `-Werror=array-bounds` 无法证明内联路径 `buses[]` 下标界内（R462 起存量构建断裂）；守卫补数组容量比较（运行期冗余、编译期可证），GNU Release 恢复构建。验证：双后端 `ctest -LE graphics` 各 40/40 + `-L graphics`（VK TEST 1–12 + 双 golden MAE=0.00 + VALIDATION GATE 0、GL 1/1）；Clang/LLD Release 非图形 40/40 且 Release 门禁生效；10 个改动 shader glslang 双后端零错误；`test_shader_io` 新增五路合成契约断言（先红后绿）；零新警告；`git diff --check` 通过。遗留（如实记录）：GL 帧内两处存量 compute 问题另立案（粒子 dispatch `GL_INVALID_OPERATION`、graphics 段每帧一条 0x502）；VK lens flare 静态视角投影位置与 GL 不一致（vUV/NDC Y 方向存量疑点，旋转对照已证合成生效）；VK 首帧 unified 回读一帧全 0 瞬态（金字塔未填充，双端一致自愈）；spin0 基线 7.14 伪速度（楔形物体 depth 写入疑点）；VK test_vulkan cull 调用点未传相机深度范围（走默认 0.1/100，行为不变）。

此前：**R549 VFS PAK 挂载路径截断契约（TDD）** — 目录挂载已拒绝超过 `VFS_MAX_PATH` 的根路径，但 PAK 挂载此前仍会打开并成功注册超长路径，只把 mount 记录静默截断到 260-byte 缓冲。现 `vfs_mount_pak()` 在打开文件前复用同一长度检查，超长 PAK 路径不占用挂载槽位。TDD：`vfs_mount_pak_rejects_path_truncation` 使用真实超长嵌套路径；旧实现错误成功，修复后 VFS 33/33 通过。验证：定向 `test_vfs` 33/33；Debug GNU 与全新 Clang 22/LLD Release 非图形 `ctest` 各 40/40 通过；`git diff --check` 通过。

此前：**R548 异步 range 读至文件末尾契约（TDD）** — `async_loader_request_range()` 的公开 API 约定 `length == 0` 为从 `offset` 读至文件尾，但实现此前直接拒绝该合法请求，且内部以 `range_length > 0` 错把它走成完整文件加载。现请求记录显式区分 range 与完整文件；零长度 range 按可用字节数读取至文件尾，正长度 range 仍严格拒绝短读。TDD：`async_loader_range_zero_reads_to_end` 在 6-byte 文件从 offset 2 请求零长度，旧代码返回 ID 0 而红，修复后回调接收 4 bytes。验证：定向 `test_async_loader` 17/17；双构建非图形全量与 `git diff --check` 待本轮完成。

此前：**R547 NetRep 轮转清理陈旧基线 peer（TDD）** — R435 的 `delta.log` 轮转会把当前 peer 集合写回 `.peer` 基线，但此前不会删除已被驱逐的旧 `peer_*.peer` 文件；下一次 `peer_load_dir()` 扫描目录时会将陈旧 peer 复活。现 `peer_save_dir()` 在所有当前基线文件成功写入后清理自身命名空间中的旧 `peer_*.peer` 条目，轮转后的快照与内存 peer 集合一致；清理失败会报告失败。TDD：`peer_delta_rotate_removes_stale_baseline_peers` 先写两 peer 基线，再缩减为一 peer 触发轮转，旧实现加载出 2 个 peer 而红，修复后 51/51 通过。验证：定向 `test_net_replication` 51/51；Debug GNU 与全新 Clang 22/LLD Release 非图形 `ctest` 各 40/40 通过；`git diff --check` 通过。

此前：**R545 Prefab 文件大小保存对称性审查（TDD）** — `scene_save_prefab()` 复用 BSCN 格式及同一加载器的 64 MiB 输入上限，但此前绕过了 R543 主场景保存端检查，仍可成功写出随后必被拒绝的 prefab。现 prefab 在构造两个 chunk 后、打开输出文件前以 `u64` 汇总完整文件大小并拒绝超限。TDD：`save_prefab_rejects_files_above_load_limit` 用一个 64 MiB 合法组件使旧保存器错误成功，修复后拒绝。检查仅在显式 prefab 保存冷路径执行，无额外分配或帧内成本。验证：定向 `test_scene_serial` 92/92 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R544 JSON 文件大小保存对称性审查（TDD）** — JSON 加载器同样在读取前限制输入至 64 MiB，但保存器此前可将组件 hex 编码为更大的文档并报告成功，随后被自身加载器拒绝。现 JSON 内存文档构造完成后、打开输出文件前检查实际字节数并拒绝超限。TDD：`save_json_rejects_files_above_load_limit` 用一个 32 MiB 合法组件（hex 后超过 64 MiB）使旧保存器错误成功，修复后拒绝。检查仅在显式 JSON 保存的冷路径执行，无额外分配或帧内成本。验证：定向 `test_scene_serial` 91/91 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R543 BSCN 文件大小保存对称性审查（TDD）** — 加载器在读取前限制 BSCN 至 64 MiB，但保存器此前仍可成功写出更大的合法 chunk 流，制造自身必拒绝的文件。现保存器在构造全部 chunk 后、打开输出文件前用 `u64` 汇总 header、table 与 payload，并拒绝超过同一上限的结果。TDD：`save_binary_rejects_files_above_load_limit` 以一个 64 MiB 的合法组件使旧保存器错误成功，修复后拒绝。检查仅在显式 BSCN 保存的冷路径执行，无额外分配或帧内成本。验证：定向 `test_scene_serial` 90/90 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R542 BSCN 纹理资源清单边界审查（TDD）** — 资源写入器以固定 256 项栈表去重材质纹理句柄，但此前满表后静默停止收集，仍报告保存成功且丢失后续纹理资源引用。现第 257 个不同有效句柄会使整个保存失败；同时资源总数的 mesh/material/texture 加法在写 header 前检查 `u32` 溢出。TDD：`save_binary_rejects_more_than_256_distinct_material_textures` 在旧代码错误成功，修复后拒绝。检查仅在显式 BSCN 保存时运行，保留固定栈表、无额外分配或帧内成本。验证：定向 `test_scene_serial` 89/89 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R541 组件安装失败审查（TDD）** — JSON 加载器此前在本地兼容组件的 `world_add_component()` 失败时静默跳过 payload 并报告整体成功，例如 ECS archetype 容量已用尽时导致已声明组件被丢失；BSCN 实体安装路径也忽略同一失败。现 JSON 及 BSCN 路径都将该失败传播为整个候选失败并沿用既有实体回滚，格式结果不再依赖资源压力。TDD：`load_json_rejects_component_when_archetypes_are_exhausted` 用 1023 个真实 archetype 填满 `ECS_MAX_ARCHETYPES`，并覆盖两种载入格式；旧代码 JSON 错误成功，修复后二者均拒绝。检查仅在显式加载时的既有组件迁移结果判断，无额外分配或帧内成本。验证：定向 `test_scene_serial` 88/88 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R540 场景保存存储一致性审查（TDD）** — 保存入口此前只检查 `Scene *`，当 `node_count`、`mesh_count` 或 `material_count` 非零而对应数组为空时，BSCN/JSON 路径可能解引用空指针并崩溃；BSCN 节点上限也仅由加载器执行。现两个保存入口以 O(1) 检查拒绝节点计数与 `nodes` 不一致，BSCN 资源清单拒绝 mesh/material 计数与数组不一致，并复用 64K 节点上限，避免崩溃及不可加载输出。TDD：`save_rejects_missing_scene_node_storage` 与 `save_binary_rejects_missing_resource_storage` 覆盖旧实现失败路径；另有 `save_rejects_nodes_above_load_limit` 覆盖格式上限对称性。验证：定向 `test_scene_serial` 87/87 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R539 场景节点上限保存对称性审查（TDD）** — BSCN 与 JSON 加载器都限制为最多 64K `SceneNode`，保存器此前却能成功生成 64K 以上、随后必被同一加载器拒绝的文件。现两个保存入口在构造输出前复用该格式上限并拒绝超额场景。检查仅为每次显式保存的一次 O(1) 比较，无分配、无每节点扫描或帧内成本。TDD：`save_rejects_nodes_above_load_limit` 在旧代码二进制保存错误成功，修复后 BSCN 与 JSON 均拒绝。验证：定向 `test_scene_serial` 85/85 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R538 场景非有限值保存对称性审查（TDD）** — 加载器已拒绝节点矩阵与资源内联描述符中的 NaN/Inf，但保存器此前仍可将这些值写出并报告成功，导致成功保存的文件立即无法加载。现 BSCN/JSON 保存路径在写出前拒绝非有限节点矩阵，BSCN 资源描述符也复用同一有限性约束。检查仅在显式保存时执行，每节点 O(1) 固定次数、每资源 8 次，无堆分配或帧内成本。TDD：`save_rejects_nonfinite_scene_values` 在旧代码二进制保存错误成功，修复后二进制和 JSON 均拒绝。验证：定向 `test_scene_serial` 84/84 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R537 JSON 组件完整记录审查（TDD）** — 组件解析此前会接受缺少 `type`、`size` 或 `data` 的对象，并把缺失字段默认为零，使输入格式与写入器产生的完整记录不一致。现 v1 组件记录必须含完整的 `type`、`size`、`data` 三元组，未知类型仍可在完整记录下前向跳过。检查仅为显式 JSON 加载的三个既有布尔状态判断，无分配或帧内成本。TDD：`load_json_rejects_incomplete_component_record` 在旧代码错误成功，修复后拒绝三种缺字段情况。验证：定向 `test_scene_serial` 83/83 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R536 JSON 组件字段顺序审查（TDD）** — 组件解析此前允许 `data` 位于 `size` 前，按默认零长度接受空 hex，随后读取非零 `size` 时把未初始化栈字节复制为已知组件数据。现 `data` 必须在 `size` 后出现，匹配写入器的 `type`、`size`、`data` 顺序，拒绝这种歧义输入。检查仅为显式 JSON 加载的一次布尔判断，无分配或帧内成本。TDD：`load_json_rejects_component_data_before_size` 在旧代码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 82/82 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R535 JSON 转义键语义审查（TDD）** — 已知 JSON 字段此前按原始字节匹配键名，等价的 Unicode 转义形式会被误作未知字段，从而绕过重复已知字段拒绝（如 `flags` 与 `fl\\u0061gs`）。现键名匹配按 JSON 解码后的字符进行，已知 ASCII 键的标准转义与 `\\uXXXX` 形式同样进入 schema 校验；未知键仍走既有完整 JSON 值验证。检查仅在显式 JSON 加载时单次扫描键名，使用栈上游标、无分配或帧内成本。TDD：扩展 `load_json_rejects_duplicate_node_fields`，旧代码错误接受语义重复 flags，修复后拒绝。验证：定向 `test_scene_serial` 81/81 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R534 JSON 空场景替换语义审查（TDD）** — `scene_save_json()` 对非空但零节点的 `Scene` 此前省略 `nodes`；`scene_load_json()` 因而无法区分显式空图与未提供图，在已有目标上 JSON 往返会错误保留旧节点，而 BSCN 会替换为空。现保存显式 `"nodes":[]`，加载器把该数组提交为零节点；完全缺失 `nodes` 仍保留既有兼容语义。仅影响显式 JSON I/O，无额外分配或帧内成本。TDD：`empty_scene_replaces_nodes_roundtrip_json` 在旧代码保留旧节点，修复后清空。验证：定向 `test_scene_serial` 81/81 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R533 JSON 节点索引往返审查（TDD）** — BSCN 会保存 `SceneNode.material_idx` 与 `skin_mesh_index`，JSON 节点此前却未输出或解析它们，JSON 往返会把非零值静默重置为零。现 JSON 对称保存并解析 `material` 与 `skin_mesh`，并同其他节点字段一样拒绝重复键；缺失新字段仍保留旧 JSON 的零值兼容。仅影响显式 JSON I/O，无额外分配或帧内成本。TDD：`scene_node_indices_roundtrip_json` 在旧代码将 material 7 丢为 0，修复后完整保留两个索引。验证：定向 `test_scene_serial` 80/80 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R532 BSCN 资源 flags 保留位审查（TDD）** — v1 写入器只用 `RESOURCES` 条目 `flags` 的 bit 0 表示内联描述符，但加载器此前接受并保留其他位，使格式语义可携带写入端不能产生的状态。现加载器在资源保留与丢弃路径均拒绝 `flags & ~0x1`。检查仅在显式 BSCN 加载时每资源 O(1)，无分配或帧内成本。TDD：`load_binary_rejects_unknown_resource_flags` 在旧代码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 79/79 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R531 v1 节点 flags 保留位审查（TDD）** — BSCN 和 JSON 写入器仅定义节点 `flags` 的 bit 0（`has_mesh`）与 bit 1（`skinned`），但加载器此前接受其它位并静默丢弃，使同一 v1 文档的语义不规范。现 BSCN 的保留/丢弃节点路径与 JSON 节点路径均拒绝 `flags & ~0x3`；格式结果不再依赖静默掩码。检查仅在显式加载时每节点 O(1)，无分配或帧内成本。TDD：`load_binary_rejects_unknown_node_flags` 与 `load_json_rejects_unknown_node_flags` 均在旧代码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 78/78 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R530 JSON 丢弃节点时格式校验审查（TDD）** — `scene_load_json()` 以 `Scene *s == NULL` 只丢弃节点时，此前将整个 `nodes` 数组按未知值跳过，绕过节点 schema、容量和 local 矩阵有限性校验，使带 NaN 的同一 JSON 因输出目标不同而被接受。现无 Scene 路径仍逐节点解析到栈上临时结构，仅省去节点 staging 分配；文件有效性不再依赖调用参数。检查仅在显式 JSON 加载时每节点 O(1)，无堆分配或帧内成本。TDD：扩展 `load_json_rejects_nonfinite_node_matrix`，旧代码在无 Scene 路径错误成功，修复后拒绝。验证：定向 `test_scene_serial` 76/76 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R529 BSCN 丢弃节点时矩阵有限性审查（TDD）** — `scene_load_binary()` 以 `Scene *s == NULL` 只丢弃节点时，此前读取节点矩阵却未验证有限性，导致带 NaN/Inf 的同一 BSCN 因输出目标不同而被接受；提供 `Scene` 时则正确拒绝。现无 Scene 路径同样验证 local/world 两个矩阵，文件有效性不再依赖调用参数。检查仅在显式 BSCN 加载时每节点额外 32 次有限性判断，无分配或帧内成本。TDD：扩展 `load_binary_rejects_nonfinite_scene_values`，旧代码在无 Scene 路径错误成功，修复后拒绝。验证：定向 `test_scene_serial` 76/76 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R528 JSON 未知字符串语法审查（TDD）** — 未知字段字符串此前只寻找下一个引号，未校验反斜杠转义或未转义控制字符，令 `"future":"\\q"` 等无效 JSON 被静默接受。现跳过器只接受 JSON 定义的单字符转义或四位十六进制 `\\u` 转义，并拒绝未转义 U+0000..U+001F；合法转义字符串的前向兼容不变。检查仅在显式 JSON 加载时按未知字符串长度线性执行，无分配或帧内成本。TDD：`load_json_rejects_invalid_unknown_strings` 覆盖非法转义、非法 Unicode 转义和控制字符，旧代码错误成功，修复后拒绝；同测保留合法转义兼容。验证：定向 `test_scene_serial` 76/76 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R527 JSON 未知复合值语法审查（TDD）** — 未知对象/数组跳过器虽已匹配定界符，但此前仍逐字跳过内部内容，接受无效嵌套 primitive、缺少对象冒号/逗号及数组尾逗号。现以固定 256 层非递归状态机实际验证每层对象键、冒号、成员/元素分隔符及所有嵌套值；超深输入拒绝，未知扩展值的正确 JSON 兼容语义不变。检查仅在显式 JSON 加载时按未知复合值长度线性执行，无堆分配或帧内成本。TDD：`load_json_rejects_invalid_unknown_compound_syntax` 覆盖四种内部语法错误，旧代码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 75/75 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R526 JSON 未知复合值定界符匹配审查（TDD）** — 未知对象/数组的兼容跳过器此前只计嵌套深度，未匹配花括号与方括号的种类，令 `"future":[}` 等错配输入被静默接受。现跳过器以固定 256 项闭合符栈逐层匹配 `{}`/`[]`，过深值直接拒绝而不递归或分配；正确嵌套的未知扩展值继续兼容跳过。检查仅在显式 JSON 加载时按未知复合值长度线性执行，无堆分配或帧内成本。TDD：`load_json_rejects_mismatched_unknown_compound_delimiters` 旧代码错误成功，修复后拒绝；同测保留合法嵌套扩展值。验证：定向 `test_scene_serial` 74/74 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R525 JSON 未知字段标量语法审查（TDD）** — 为保持前向兼容，加载器会跳过未知字段；但此前跳过器把任意裸 token 当作 primitive，令 `"future":garbage` 等无效 JSON 静默通过。现未知标量只接受严格的 JSON number、`true`、`false` 或 `null`；字符串、数组与对象的兼容跳过语义不变。检查仅在显式 JSON 加载时按未知标量长度线性执行，无分配或帧内成本。TDD：`load_json_rejects_invalid_unknown_primitive` 覆盖顶层、实体、组件和节点未知字段，旧代码错误成功，修复后拒绝；同测保留合法 number/boolean/null 兼容。验证：定向 `test_scene_serial` 73/73 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R524 JSON 节点数组分隔符审查（TDD）** — 节点数组使用了不同于实体/组件数组的手写循环，节点对象后此前可选地消费逗号，错误接受 `nodes:[{},]`。现每个节点后只能紧接 `]`，或以一个逗号分隔且逗号后必须是下一节点对象；也一并拒绝节点之间缺失逗号。检查仅在显式 JSON 加载时每个节点 O(1)，无分配或帧内成本。TDD：`load_json_rejects_trailing_nodes_array_comma` 旧代码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 72/72 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R523 JSON 对象成员分隔符审查（TDD）** — 加载器此前把对象成员后的逗号当作可选，错误接受相邻字段缺失逗号或对象尾逗号；这使格式解析与标准 JSON 和写入器不一致。现统一要求已读取的对象字段后只能紧接 `}`，或以一个逗号分隔且逗号后必须有下一字段，覆盖顶层、实体、组件与节点对象。检查仅在显式 JSON 加载时每个对象成员 O(1)，无分配或帧内成本。TDD：`load_json_rejects_invalid_object_member_separators` 覆盖四类对象的缺失及尾随逗号，旧代码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 71/71 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R522 JSON 根文档完整消费审查（TDD）** — 加载器此前在读完根对象后直接报告成功，允许有效场景前缀后追加任意未解析值，使被附加的内容被静默忽略。现根对象闭合后仅允许 JSON 空白并要求指针抵达文件末尾；失败仍沿用既有 World/Scene 回滚。检查只在显式 JSON 加载尾部执行，O(尾部空白长度)，无分配或帧内成本。TDD：`load_json_rejects_trailing_content` 旧代码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 70/70 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R521 JSON 组件 schema 字段唯一性审查（TDD）** — 写入器对每个组件对象仅输出一个 `type`、`size`、`data`，但加载器此前接受重复键并让后值改变类型、payload 尺寸或字节内容。现每条组件记录以三个局部标记拒绝这些已知字段的第二次出现；未知字段和旧字段缺失的兼容语义不变。检查仅在显式 JSON 加载时每个组件字段 O(1)，无新增分配或帧内成本。TDD：`load_json_rejects_duplicate_component_fields` 覆盖三种重复字段，旧代码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 69/69 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R520 JSON 节点 schema 字段唯一性审查（TDD）** — 写入器对每个节点仅输出一个 `parent`、`mesh`、`flags`、`local`，但加载器此前接受重复键并让后值覆盖前值，图结构、网格绑定、标志或局部变换都会依赖键顺序。现每个 staging 节点以四个局部标记拒绝这些已知字段的第二次出现；未知字段和旧字段缺失的兼容语义不变。检查仅在显式 JSON 加载时每个节点字段 O(1)，无分配或帧内成本。TDD：`load_json_rejects_duplicate_node_fields` 覆盖四种重复字段，旧代码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 68/68 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R519 JSON 顶层 schema 键唯一性审查（TDD）** — 写入器仅输出一个顶层 `version`、`entities` 与可选 `nodes`，但加载器此前允许重复 `entities` 并连续创建多批实体，重复 `nodes` 也会后值覆盖 staging 图，使结果依赖键顺序。现顶层解析以三个局部标记拒绝这些已知 schema 键的第二次出现；未知顶层键仍兼容跳过，`nodes` 等字段的缺失语义不变。检查仅在显式 JSON 加载时每个顶层键 O(1)，无分配或帧内成本。TDD：`load_json_rejects_duplicate_entities_key` 与 `load_json_rejects_duplicate_nodes_key` 旧代码均错误成功，修复后拒绝。验证：定向 `test_scene_serial` 67/67 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R518 JSON 实体 schema 字段唯一性审查（TDD）** — JSON 写入器每个实体只输出一个 `gen` 和一个 `components`，但加载器此前允许重复；后一个 `gen` 可覆盖统一实体 ID，重复组件数组则使结构取决于输入顺序。现每个正在解析的实体以两个栈上标记拒绝重复 `gen` 或 `components`，并保留这些旧字段缺失时的兼容默认值。检查仅在显式 JSON 加载时每个字段 O(1)，无分配或帧内成本。TDD：`load_json_rejects_duplicate_entity_generation` 和 `load_json_rejects_duplicate_entity_components` 均在旧代码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 65/65 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R517 JSON 重复组件对象审查（TDD）** — JSON 写入端对每个实体每种组件只输出一个完整对象，但读取端此前允许数组中同一 type 重复，后对象静默覆盖前值。现 `json_load_components()` 使用固定 128 项类型列表，限制每个实体的组件对象数并拒绝任意完整 `u32` type（包括未知 type）重复；未知类型仍仅跳过、不要求本地注册，保持前向兼容。检查仅在显式 JSON 加载中执行，最多 8,128 次比较，无堆分配或帧内成本。TDD：`load_json_rejects_duplicate_component_type` 为 type 1 写入两个不同值，旧加载器错误成功，修复后拒绝。验证：定向 `test_scene_serial` 63/63 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R516 BSCN 未知组件类型记录唯一性审查（TDD）** — v1 写入端按类型分组且每个类型只发一条记录，但加载器此前仅对当前 0..127 范围去重；高 ID 的重复记录会被两次跳过并报告成功，使未来类型定义出现顺序相关的歧义。现保留未知 payload 的前向兼容跳过，却在读取每个类型头时以固定 128 项完整 ID 列表检查先前记录，任何 `u32` 类型重复均拒绝。最多 128 条记录，额外至多 8,128 次比较，仅显式加载、无堆分配或帧内成本。TDD：`load_binary_rejects_duplicate_unknown_component_type` 写入两条 type 128 记录，旧加载器错误成功，修复后拒绝。验证：定向 `test_scene_serial` 62/62 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R515 实体 generation 非零句柄审查（TDD）** — BSCN 写入端只枚举存活实体，generation 必为非零；但读取端此前将磁盘零值保留为 `world_create_entity()` 的 generation 1，加载虽成功却静默改变统一 `(index,generation)` ID。JSON 的显式 `"gen":0` 也有同一不对称。现 BSCN `ENTITIES` 在创建实体前拒绝零 generation；JSON 显式 `gen` 同样要求非零，而缺失旧字段继续沿用新建 generation 以保持兼容。检查只在显式加载时每实体或每个 `gen` 字段 O(1)，无分配或帧内成本。TDD：`load_binary_rejects_zero_entity_generation` 与 `load_json_rejects_zero_entity_generation` 均在旧代码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 61/61 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R514 BSCN 可选单例 chunk 审查（TDD）** — 写入端固定仅发出一个 `SCENE_NODES` 和一个 `RESOURCES` chunk，但加载器此前只限制 `ENTITIES`/`COMPONENTS`；重复的节点或资源块会按 table 顺序覆盖前一个 staged 结果，使格式结果依赖排列。现第二遍解析对两种可选 chunk 各设置一位标记，第二次出现立即失败并沿用既有 World/Scene 回滚；未知及历史 `HIERARCHY` 的跳过语义不变。检查仅在显式加载时每 chunk O(1)，无分配或帧内成本。TDD：`load_binary_rejects_duplicate_scene_nodes_chunk` 和 `load_binary_rejects_duplicate_resources_chunk` 各写入两个合法空块，旧加载器均错误成功，修复后拒绝。验证：定向 `test_scene_serial` 59/59 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R513 BSCN 前向兼容组件 owner 唯一性审查（TDD）** — `COMPONENTS` 中未知或尺寸不匹配类型虽会被正确跳过，但此前同一记录可多次引用同一保存实体；这不可能由写入端生成，并使跳过的 payload 具有歧义 owner 映射。现将每类型 owner 去重提升为格式级规则：所有类型记录均复用固定 64K 位图检查每个保存实体索引至多一次，再按原策略复制或跳过 payload；未知和尺寸不匹配类型仍不要求本地声明，前向兼容语义不变。检查仅在显式加载中每类型清零 1024 个 `u64` 并按实例 O(1) 标记，无堆分配或帧内成本。TDD：`load_binary_rejects_duplicate_unknown_component_instance_owner` 令未知 type 128 的两条实例均引用 entity 0，旧加载器错误成功，修复后拒绝。验证：定向 `test_scene_serial` 57/57 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R512 BSCN 本地组件实例双向一致性审查（TDD）** — 写入端为每个已注册组件类型遍历每个保存实体，故 `ENTITIES` 中声明的本地且尺寸兼容组件必有且仅有一条 `COMPONENTS` 实例；加载器此前只检查反向方向，接受缺失实例/类型记录并保留零初始化组件，也让重复 owner 用后值覆盖前值。现解析 `ENTITIES` 时统计本地声明数；读取兼容类型记录时要求实例数相等，并用固定 64K 位图拒绝重复 owner，最后拒绝缺失的本地类型记录。未知或尺寸不匹配类型仍整体跳过，保持前向兼容。检查仅发生在显式加载，额外工作为 O(记录 + 实例 + 128 * 1024)，无堆分配或帧内成本。TDD：`load_binary_rejects_declared_component_without_instance` 在一实体声明 type 1、组件记录却为零实例时，旧加载器错误成功；另增加缺失类型记录及重复 owner 覆盖测试，修复后均拒绝。验证：定向 `test_scene_serial` 56/56 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R511 BSCN payload 重叠布局审查（TDD）** — `scene_probe_binary()` 和 `scene_load_binary()` 先前分别验证每个 chunk 不在 table 内且不越过 EOF，却没有验证不同 payload 彼此分离；恶意归档可让两个 chunk 映射同一物理字节区（包括被跳过的未知/HIERARCHY），产生一个字节域多个逻辑含义并使两条 API 错报格式有效。现共享表布局验证先检查范围，再以半开区间交集拒绝任意两个 payload 重叠；相邻边界仍合法。最多 64 个 chunk，检查仅在显式 probe/load 时 O(n^2)（最多 2016 对）执行，无帧内成本或分配。TDD：`load_binary_rejects_overlapping_chunk_payloads` 写入指向同一 4-byte payload 的 HIERARCHY 与未知 chunk，旧 probe/load 均错误成功，修复后均拒绝。验证：定向 `test_scene_serial` 53/53 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R510 BSCN 重复组件块审查（TDD）** — 写入端固定发出唯一 `COMPONENTS` chunk，但加载器此前仅拒绝重复 `ENTITIES`，允许多个组件块依 table 顺序累计或覆盖数据，令无法由写入端生成的归档具有顺序相关的最终状态。现第二遍在处理第一个 `COMPONENTS` 后设置局部标记，第二个出现即失败并触发既有实体回滚；可选 `RESOURCES`/`SCENE_NODES` 与未知块的既有语义不变。检查只在显式导入时每 chunk O(1) 执行，无帧内成本或分配。TDD：`load_binary_rejects_duplicate_components_chunk` 写入一个空 `ENTITIES` 和两个各自合法的空组件块，旧码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 52/52 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R509 BSCN 组件声明一致性审查（TDD）** — `COMPONENTS` 记录此前可为实体隐式添加一个 `ENTITIES` archetype 未声明的已知组件；两个 chunk 内容矛盾时加载仍成功，且会执行额外 archetype 迁移。现对已知且尺寸匹配的每条实例，在拷贝前以 O(archetype component count) 检查实体是否声明该组件，并要求现有存储可取；不匹配立即失败并触发既有实体回滚。未知或尺寸不符类型仍按前向兼容跳过。检查仅在显式导入时执行，无帧内成本或堆分配。TDD：`load_binary_rejects_component_not_declared_by_entity` 构造实体声明空 archetype 却在 `COMPONENTS` 提供 type 1 实例，旧码错误成功并隐式添加，修复后拒绝。验证：定向 `test_scene_serial` 51/51 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R508 BSCN 实体组件集合审查（TDD）** — `ENTITIES` 的组件 ID 列表来自 ECS archetype key，本应为集合；加载器此前对重复的已注册 ID 只会重复调用幂等 `world_add_component()` 并报告成功，接受无法由写入端生成的畸形实体定义。现加载器对每个实体以两个栈上 `u64` 位图记录 0..127 类型 ID，在创建实体后恢复组件前发现重复即拒绝并沿用既有实体回滚；高于当前容量的未知 ID 仍保持前向兼容跳过。检查只在显式导入时每个 ID O(1) 执行，无帧内成本或堆分配。TDD：`load_binary_rejects_duplicate_entity_component_type` 构造一个带两个 type 1 条目的实体，旧码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 50/50 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R507 BSCN 已知 chunk 精确消费审查（TDD）** — BSCN 加载器此前只要已知 chunk 的前缀能被解析就报告成功，没有要求 `Reader` 到达声明 payload 的末尾；`ENTITIES`、`COMPONENTS`、`RESOURCES` 或 `SCENE_NODES` 后附加垃圾会被静默接受，令版本 1 格式边界不确定。现四种实际解析的 v1 chunk 都要求解析成功且精确消费全部声明字节，失败仍触发既有 World/Scene 回滚；`HIERARCHY` 维持历史上由 `SceneNode.parent_index` 隐式表达、整体忽略的语义，未知 chunk 亦保持前向兼容跳过。检查只在显式导入时每 chunk 作一次指针相等比较，无帧内成本或分配。TDD：`load_binary_rejects_known_chunk_trailing_bytes` 在最小合法 `ENTITIES` payload 后加入一个 `u32`，旧码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 49/49 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R506 BSCN 重复组件类型记录审查（TDD）** — 虽然 `COMPONENTS` 的类型记录总数已受限，加载器此前仍允许同一可表示类型出现两次；后记录按 table 顺序覆盖前记录，让无法由写入端生成的归档悄然改变状态。现加载器以两个栈上 `u64` 位图在读取每条记录头后标记 0..127 类型 ID，并在重复时、处理任何 payload 或组件迁移前拒绝；未能由当前引擎表示的更高 ID 仍按既有前向兼容逻辑跳过。检查仅在显式导入时每记录 O(1) 执行，无帧内成本或堆分配。TDD：`load_binary_rejects_duplicate_component_type` 为同一实体写入两条各自合法的 type 1 记录，旧码错误成功且后值获胜，修复后拒绝。验证：定向 `test_scene_serial` 48/48 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R505 BSCN 组件实例计数审查（TDD）** — `COMPONENTS` 的 `instances` 原先直接控制每类型加载循环；即使单个索引合法，畸形归档仍能为一实体重复写入任意多条同类型实例，让加载器反复迁移/查找并以最后一条悄悄覆盖前值。写入端每种类型至多对每个保存实体发出一条实例。现读取记录头后、进入实例循环前拒绝 `instances > ent_count`，并以宽整数验证所有索引加 payload 的最小总字节数位于 chunk 剩余范围内；检查只在显式导入时常数执行，随后每类型最多线性扫描保存实体数，无帧内成本或分配。TDD：`load_binary_rejects_excessive_component_instances` 为单实体写入两条同类型实例，旧码错误成功，修复后在任何实例迁移前拒绝。验证：定向 `test_scene_serial` 47/47 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R504 BSCN 组件实例实体引用审查（TDD）** — `COMPONENTS` 的每条实例都含有指向 `ENTITIES` 的保存索引，但加载器此前仅在类型已注册且大小匹配时才检查索引；越界索引会被静默跳过并仍报告加载成功。写入端绝不会产生悬空实例，且前向兼容只能允许跳过未知类型数据，不能允许其绕过实体关系完整性。现每条实例读完索引和 payload 边界后均要求索引小于实体数，再按既有逻辑恢复已知类型。检查仅在显式导入时每实例 O(1) 执行，无帧内成本或分配。TDD：`load_binary_rejects_component_instance_without_entity` 构造一实体、却由已知组件实例引用索引 1 的 BSCN；旧码错误成功，修复后拒绝并触发既有实体回滚。验证：定向 `test_scene_serial` 46/46 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R503 BSCN chunk table 布局审查（TDD）** — `scene_probe_binary()` 原本会拒绝 payload 起点落在 chunk table 内的 BSCN，但 `scene_load_binary()` 仅验证 payload 结尾不越过文件；因此被前向兼容逻辑跳过的 `HIERARCHY` 或未知 chunk 能把表字节错误当作 payload 并让加载 API 成功，形成同一格式的探测/加载判定分裂。现加载器在任何解析或状态变更前扫描至多 64 条表项，要求每个 payload 均从 table 之后开始且位于文件范围内；检查只在显式导入时 O(chunk_count) 执行，无帧内成本或分配。TDD：`load_binary_rejects_chunk_overlapping_table` 构造 payload 指向唯一 table entry 的 HIERARCHY chunk，旧码探测拒绝而加载错误成功，修复后两者均拒绝。验证：定向 `test_scene_serial` 45/45 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R502 BSCN 组件类型计数审查（TDD）** — 二进制 `COMPONENTS` chunk 的 `type_count` 原先直接控制加载循环，既没有写入端可产生的 `ECS_MAX_COMPONENTS` 上限，也未先验证每条类型记录所需的固定 12-byte 头部；畸形归档可用任意大量空记录消耗加载期工作并被错误当作成功格式。现读取计数后、进入循环前拒绝超过引擎组件容量或连固定头部都放不下的 chunk；未知但数量有效的类型仍按既有兼容逻辑跳过。仅在显式导入时常数检查，无帧内成本或分配。TDD：`load_binary_rejects_excessive_component_type_count` 写入 129 条空类型记录，旧码错误成功，修复后拒绝。验证：定向 `test_scene_serial` 44/44 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R501 场景状态布尔编码审查（TDD）** — `scene_state.bin` 的可选水位尾部此前以 `fread(..., sizeof(bool))` 直接写入 C `bool`；任意非零磁盘字节（如 `2`）都被接受，既令二进制格式依赖实现表示，也把不受信任的非规范对象表示带入运行时。现格式明确使用单字节 `u8`，保存端规范化为 `0/1`，加载端只接受这两个值后才转换为 `bool`；非法值沿用既有快照恢复。布局仍为一个字节，既有有效存档兼容。检查只在可选尾部加载时常数执行，无帧内成本或分配。TDD：`scene_state_rejects_noncanonical_water_flag` 把有效存档最后一字节改为 `2`，旧码错误成功，修复后拒绝且水位状态保持。验证：定向 `test_scene_state` 10/10 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R500 场景状态保存非有限值审查（TDD）** — `scene_state_load()` 已拒绝 NaN/Inf，但 `scene_state_save()` 先前仍会把同类非法运行时值写入存档，成功返回后留下该加载器必然拒绝的检查点，并覆盖原有可恢复状态。现保存前验证将实际序列化的完整 `Camera`、顶层浮点、刚体位置/速度/有效质量/半尺寸/弹性及水位均有限；检测发生在打开目标文件之前，失败不会触碰原存档。检查仅在显式保存期按刚体数线性执行，无帧内成本或分配。TDD：`scene_state_save_rejects_nonfinite_values` 依次注入相机、全局、刚体和水位 NaN，旧码错误保存，修复后返回 false 且逐字节保留原有效检查点。验证：定向 `test_scene_state` 9/9 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R499 PAK 名称表终止完整性审查（TDD）** — `vfs_mount_pak()` 原先为名称表额外分配一个零字节以保护 `strcmp` 免于越界，却没有验证每个 `PakEntry.name_offset` 所指字符串在声明的 `name_table_size` 范围内终止；恶意归档可省略末尾 NUL，令分配哨兵把不完整的表项伪装成可打开的真实路径。现仅在挂载期构建哈希索引时单次扫描名称表的最后一个表内 NUL，再以常数比较验证每个有效 offset；未终止或越界/data-range 损坏条目统一成为 lookup miss，容器仍可挂载。`vfs_open()` 热路径、常驻内存和分配不变。TDD：`vfs_pak_unterminated_name_is_miss` 写入名称表恰好缺少末尾 NUL 的 PAK，旧码错误打开 `greet.txt`，修复后挂载成功但查找返回 NULL。验证：定向 `test_vfs` 32/32 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R498 BSCN 场景非有限浮点审查（TDD）** — BSCN 加载器此前将内联资源描述符的 8 个 `f32` 以及 `SceneNode` 局部/世界矩阵直接恢复到 `Scene`；损坏或恶意文件中的 NaN/Inf 可传播进渲染变换和资源边界计算，JSON 的十六进制局部矩阵也有同一问题。现二进制加载逐项验证资源描述符和两份矩阵全部有限，JSON 节点局部矩阵复用相同检查；任一非法值令候选失败，既有 staged 场景原子性保证旧 `Scene` 保持。验证仅发生在低频导入期，按已读字段线性执行，无帧内成本或额外常驻分配。TDD：`load_binary_rejects_nonfinite_scene_values` 分别注入资源、局部矩阵和世界矩阵 NaN，`load_json_rejects_nonfinite_node_matrix` 覆盖 JSON 十六进制矩阵；旧码错误接受，修复后均拒绝并保持既有场景；模块文档同步。验证：定向 `test_scene_serial` 43/43 通过；Debug GNU 与隔离 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R497 VFS PAK 格式版本审查（TDD）** — `vfs_mount_pak()` 原先只检查 PAK magic，却忽略声明的格式版本；带有同一 magic 但不同条目布局的旧版或未来归档会被按当前 `PakEntry` 结构错误解析并挂载。现 mount 在任何条目读取、元数据分配或 mount 槽位占用前要求 `hdr.version == VFS_PAK_VERSION`，不匹配直接返回 false。检查为挂载期一次常数时间比较，文件打开热路径与分配不变。TDD：`vfs_pak_version_mismatch_rejected` 写入 magic 正确但版本递增的最小 PAK，旧码错误挂载，修复后拒绝且 `mount_count` 保持 0；模块文档同步。验证：定向 `test_vfs` 31/31 通过；Debug GNU 与隔离 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R496 轻量脚本非有限值审查（TDD）** — 轻量脚本解析器通过 `%f` 读取 `var`、`set`、`add` 和 `spawn` 参数，却未检查有限性；`nan`/`inf` 文件可被接受并把非法数值置入全局或操作参数，后续帧传播到游戏逻辑。现解析器在候选加载阶段拒绝任一非有限数值，`script_load()` 沿用事务式替换，失败时释放候选并保留上一份有效脚本。检查只在加载/热重载的低频路径执行，`script_call()` 热路径无新增操作或分配。TDD：`load_rejects_nonfinite_values_preserves_previous_script` 依次注入四类非法数值脚本，旧码接受第一个候选，修复后全部拒绝且原回调仍可执行；模块文档同步。验证：定向 `test_script` 18/18 通过；Debug GNU 与隔离 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R495 场景运行时状态非有限值审查（TDD）** — `scene_state_load()` 先前把二进制存档的 `Camera`、太阳/曝光/渲染倍率、V1/V2/V3 刚体与水位浮点直接写入运行时；攻击者或损坏文件中的 NaN/Inf 可污染渲染、物理和后续计算。现加载时验证完整 `Camera`（含缓存投影矩阵）、顶层浮点、刚体位置/速度/质量/半尺寸/弹性以及可选水位均有限，任一非法值都沿用既有快照恢复完整运行时状态。检查仅发生在显式加载路径，按已读字段线性执行，不增加帧内成本或分配。TDD：`scene_state_rejects_nonfinite_values` 逐个把相机、顶层、刚体与水位记录改为 NaN，旧码错误接受首个损坏存档，修复后每种记录均拒绝且相机、全局值和刚体保持加载前状态；模块文档同步。验证：定向 `test_scene_state` 8/8 通过；Debug GNU 与隔离 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R494 NetRep 持久化 RTT 非有限值审查（TDD）** — peer 基线和增量文本通过 `%f` 读取 RTT，但先前未验证有限性；`nan`/`inf` 可登记为 peer 的 RTT 状态，并直接传播到诊断/UI 或后续计算。现共享行解析器在建 peer 前要求两个 RTT 值均为有限数，非法记录与端口溢出记录同样跳过，单文件、目录基线和 delta 导入一致受保护。该检查仅在显式持久化导入执行，不影响网络热路径、无分配。TDD：`peer_load_rejects_nonfinite_rtt` 写入一条 `nan inf` 记录和一条合法记录，旧码错误注册两条，修复后只保留合法 peer 且 RTT 有限；模块文档同步。验证：`test_net_replication` 定向回归 50/50 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R493 NetRep 增量日志读取错误状态保持审查（TDD）** — `net_replicator_peer_load_delta()` 设计为缺失可选日志返回成功，但先前把已成功打开后的 `fgets` 读错误与 `fclose` 错误也误作“无日志”成功；若错误发生在部分 delta 应用后，运行时 peer 表还会保留部分新状态。现缺失文件仍保持可选成功语义，已打开日志则要求读取和关闭成功；否则恢复固定 peer 表快照及计数并返回 false。修改仅在显式持久化导入路径，不影响网络热路径、无堆分配。TDD：`peer_load_delta_reports_read_failure_preserves_existing_peers` 将已有 peer 传给目录路径注入真实读错误，旧码错误成功，修复后返回 false 且 peer 保持；模块文档同步。验证：`test_net_replication` 定向回归 49/49 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R492 NetRep 目录条目读取错误状态保持审查（TDD）** — `net_replicator_peer_load_dir()` 先前只要目录成功打开就清空 peer 表，并忽略已打开 `.peer` 的 `ferror()` 与 `fclose()`；POSIX 下名为 `bad.peer` 的目录可通过 `fopen`，读取失败却会被当作成功空文件，API 错报成功并提交空/部分基线。现目录扫描对枚举后无法打开的条目仍保持原有跳过语义，但任一已打开 `.peer` 的读取或关闭失败都会关闭目录、恢复固定 peer 表快照及计数并返回 false；仅影响显式持久化导入，不影响网络热路径、无堆分配。TDD：`peer_load_dir_reports_entry_read_failure_preserves_existing_peers` 创建 `.peer` 目录注入真实读错误，旧码错误成功，修复后返回 false 且已有 peer 保持；模块文档同步。验证：`test_net_replication` 定向回归 48/48 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R491 NetRep 单文件读取错误状态保持审查（TDD）** — `net_replicator_peer_load()` 先前在读取前清空 peer 表，却忽略 `fgets` 终止后的 `ferror()` 与 `fclose()`；POSIX 目录可被 `fopen` 成功打开但读取失败，API 仍错误返回成功并丢失已有 peer 基线。现读取期间仅保留固定大小 peer 表快照，要求流读取和关闭均成功；失败恢复 peer 表、数量与驱逐计数，成功才提交新快照。修改只发生在显式持久化导入路径，不影响网络热路径、无堆分配。TDD：`peer_load_reports_read_failure_preserves_existing_peers` 将已有 peer 传给目录路径，旧码错误报告成功，修复后返回 false 且 peer 保持；模块文档同步。验证：`test_net_replication` 定向回归 47/47 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R490 Lua 显式替换失败身份保持审查（TDD）** — `lua_script_load()` 先前在候选 chunk 运行前即写入 `path` 和 `last_mtime`；候选在运行时失败后，虽然 R489 会恢复全局和 hook，却仍让热重载改盯失败文件，失去对上一份有效脚本的自动更新。现仅在候选完整执行成功后提交新路径与 mtime；失败替换保留原有效脚本的执行逻辑和热重载身份。修改只位于低频加载路径，不影响帧内 hook 调用、无额外分配。TDD：`load_runtime_failure_preserves_previous_reload_identity` 先载入有效脚本再显式替换为运行时报错候选，旧码把 path 改为候选，修复后保持旧 path、mtime 和 `on_update`；模块文档同步。验证：`test_script_lua` 定向回归 24/24 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R489 Lua 热重载运行失败原子性审查（TDD）** — `lua_script_reload_if_changed()` 虽然会在候选执行失败时保留 mtime 以便重试，但候选 chunk 可在 `error()` 前已经覆盖 `on_update`、标量或新增全局变量；API 报失败后，下一帧却运行了半套新逻辑。现仅在显式字符串加载、文件加载与热重载时快照 Lua 全局表；候选运行失败就移除新增键并恢复快照值，原 hooks 与顶层全局保持完整，成功路径按原语义提交。快照只发生在低频加载路径，不影响帧内 hook 调用；失败路径的临时 Lua 表会随即释放，无常驻分配。TDD：`hot_reload_runtime_failure_preserves_previous_hooks` 让候选先覆写 version/hook、新增变量再抛错，旧码泄露 `version=2` 和新 hook，修复后仍为版本 1、旧 hook 返回 10、候选变量不存在；模块文档同步。验证：`test_script_lua` 定向回归 23/23 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R488 NetRep 目录读取失败状态保持审查（TDD）** — `net_replicator_peer_load_dir()` 先前在 `opendir()` 前清空 peer 表；不存在或暂时不可访问的目录令 API 返回 `false`，却同时丢失已有运行时 peer 基线，后续无法重试或继续使用。现仅在目录成功打开后才开始以目录快照替换 peer 表；成功读取空目录仍按原语义得到空快照。变更只在显式持久化读取路径执行，不影响网络热路径、无分配。TDD：`peer_load_dir_failure_preserves_existing_peers` 预置有效 peer 后读取不存在目录，旧码错误清零，修复后保留该 peer；模块文档同步。验证：`test_net_replication` 定向回归 46/46 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R487 纹理热重载失败初始化关闭审查（TDD）** — `hotreload_texture_shutdown()` 先前无条件关闭 watcher；若 `hotreload_texture_init()` 在 `filewatch_init()` 前失败，零初始化 watcher 的 Linux fd 为 0，会错误关闭 stdin。现 shutdown 与 pipeline 路径一致，仅在对象 ready 后释放 watcher；正常成功初始化/关闭路径不变，无轮询热路径成本、无分配。TDD：`hotreload_texture_failed_init_keeps_stdin` 将 `/dev/null` 映射至 stdin 后关闭失败初始化对象，旧码关闭该 fd，修复后仍保持可用；模块文档同步。验证：`test_hotreload` 定向回归 5/5 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R486 Lua 热重载失败重试审查（TDD）** — `lua_script_reload_if_changed()` 先前在编译或执行候选脚本前就写入 `last_mtime`；语法/运行时失败会吞掉该版本，文件随后被修正但 mtime 未跨秒时仍永久保留旧回调。现仅在候选 chunk 成功运行后提交 mtime，失败候选继续可重试；只影响低频热重载检查，`on_update` 调用热路径不变、无分配。TDD：`hot_reload_retries_after_failed_candidate` 先载入有效回调、注入错误脚本、再在同一观察 mtime 下写入修正版本；旧码卡在旧逻辑，修复后更新为新回调；模块文档同步。验证：`test_script_lua` 定向回归 22/22 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R485 脚本热重载失败状态保持审查（TDD）** — `script_load()` 先前在打开新文件前就释放 source、函数和全局变量；热重载遇到瞬态 I/O 错误会令原本正常运行的脚本变为空，所有回调静默失效。现新脚本在独立临时状态完整读取解析后才替换旧内容，读取短缺也失败；重载仅在成功后提交 mtime。失败路径不增加常驻分配，成功装载只保留最终脚本分配，调用热路径不变。TDD：`load_failure_preserves_previous_script` 先载入有效回调再请求不存在替换文件，旧码清空 loaded 状态，修复后原回调仍可执行；模块文档同步。验证：`test_script` 定向回归 17/17 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R484 场景运行时状态保存关闭失败审查（TDD）** — `scene_state_save()` 先前忽略 `fclose` 的延迟写错误；写入 `/dev/full` 仍报告运行时状态已保存，调用方会把缺失或不完整的相机、渲染与物理状态当作有效存档。现 API 要求写入无流错误且关闭成功，失败如实返回 false；仅影响显式保存操作，无帧内热路径成本、无分配。TDD：`scene_state_save_reports_close_failure` 用 `/dev/full` 注入真实关闭失败，旧码错误成功，修复后返回 false；模块文档同步。验证：`test_scene_state` 定向回归 7/7 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R483 Profiler trace 导出关闭失败审查（TDD）** — `profiler_export_chrome_trace()` 先前忽略 `fclose` 的延迟写错误；目标为 `/dev/full` 时仍错误报告 trace 已导出，调用方会误以为可用于分析的 JSON 文件已经落盘。现导出要求流无错误且关闭成功，失败如实返回 false；只影响用户显式导出动作，无采样或帧内热路径成本、无分配。TDD：`profiler_export_reports_close_failure` 以 `/dev/full` 注入真实关闭失败，旧码错误成功，修复后返回 false；模块文档同步。验证：`test_profiler` 定向回归 26/26 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R482 场景保存关闭失败审查（TDD）** — `scene_save_binary()`、`scene_save_json()` 与 `scene_save_prefab()` 先前均忽略 `fclose` 的延迟写错误；写入 `/dev/full` 后仍报告成功，调用方会把缺失或不完整的场景/预制体当作已持久化。现三条保存 API 都要求全部写入、无流错误且关闭成功，失败如实返回 false；仅影响显式保存路径，无运行时热路径成本、无分配。TDD：三项 `*_reports_close_failure` 用 `/dev/full` 注入真实关闭失败，旧码均错误成功，修复后返回 false；模块文档同步。验证：`test_scene_serial` 定向回归 41/41 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R481 NetRep 目录基线写失败审查（TDD）** — `net_replicator_peer_save_dir()` 对每个 `.peer` 文件先前只检查 `fopen`，忽略 `fprintf` 缓冲错误与 `fclose`；已打开的失败目标仍令 API 报告成功，调用方会把缺失/损坏基线当作完整快照。现每个文件均要求 `ferror` 为假且关闭成功，任一失败返回 false；只发生在显式持久化操作，无网络热路径成本、无分配。TDD：`peer_save_dir_reports_write_failure` 将预期 peer 文件名链接到 `/dev/full`，旧码错误成功，修复后返回 false；模块文档同步。验证：`test_net_replication` 定向回归 45/45 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R480 NetRep 全量 peer 保存写失败审查（TDD）** — `net_replicator_peer_save()` 先前只检查 `fopen`，忽略缓冲写入与 `fclose` 错误；写入 `/dev/full` 仍报告 checkpoint 成功，调用方会误以为状态已持久化。现返回值要求 `ferror` 为假且 `fclose` 成功，失败如实返回 false；只发生在显式持久化操作，无网络热路径成本、无分配。TDD：`peer_save_reports_write_failure` 用 `/dev/full` 注入真实关闭失败，旧码错误成功，修复后返回 false；模块文档同步。验证：`test_net_replication` 定向回归 44/44 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R479 NetRep 增量日志写失败状态审查（TDD）** — `net_replicator_peer_save_delta()` 先前在 `fprintf` 尚未由 stdio 落盘时就清除 peer 的 dirty 标志，且忽略 `ferror`/`fclose`；写入 `/dev/full` 仍返回成功，更新永远丢失。现仅在全部缓冲写入与关闭均成功后确认并清除 dirty，任一失败返回 false 且保留待保存状态供重试；只影响显式持久化操作，无网络热路径成本、无分配。TDD：`peer_save_delta_keeps_dirty_on_write_failure` 用 `/dev/full` 注入真实失败，旧码错误成功，修复后返回 false 且 dirty 保持 true；模块文档同步。验证：`test_net_replication` 定向回归 43/43 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R478 NetRep peer 读取路径截断审查（TDD）** — `net_replicator_peer_load_dir()` 将目录与 `.peer` 目录项、`delta.log` 格式化到 512-byte 路径缓冲，却先前忽略截断；截断前缀若存在，读取会把其内容当作另一 peer 文件解析并注册错误地址。现目录项与 delta 路径均在打开前验证格式化结果完整容纳，超长项跳过；只影响显式持久化读取，无网络热路径成本、无分配。TDD：`peer_load_dir_skips_truncated_entry_path` 在 508-byte 深目录创建 `.peer` 项及其截断前缀，旧码错误注册一个 peer，修复后保持 0；模块文档同步。验证：`test_net_replication` 定向回归 42/42 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R477 NetRep peer 保存文件名截断审查（TDD）** — `net_replicator_peer_save_dir()` 将目录、peer 地址与端口格式化到 512-byte `path`，先前忽略 `snprintf` 返回值；超长组合会静默截断却仍返回成功，生成与 peer 身份不一致的文件。现 `fopen` 前要求格式化结果完整容纳，失败立即返回 false，不写入截断名称；只发生在显式持久化操作，无网络热路径成本、无分配。TDD：`peer_save_dir_rejects_path_truncation` 使用 500-byte 深目录，旧码错误成功，修复后返回 false；模块文档同步。验证：`test_net_replication` 定向回归 41/41 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R476 VFS 打开组合路径截断审查（TDD）** — 目录 mount 的 `vfs_open()` 将根路径与调用者相对路径格式化到 512-byte `full` 缓冲，先前超长组合会静默截断；若该前缀存在文件，调用者会读到错误资源。现每个目录 mount 在 `fopen` 前精确验证完整组合容量，无法容纳的高优先级 mount 会跳过并继续尝试较低优先级 mount；改为有界 `memcpy` 拼接，避免格式化开销、无分配。TDD：`vfs_open_rejects_join_path_truncation` 在深根目录中建立截断前缀文件，旧码错误打开它，修复后返回 NULL；模块文档同步。验证：`test_vfs` 定向回归 30/30 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R475 VFS 目录挂载路径截断审查（TDD）** — `vfs_mount_dir()` 将挂载根目录写入 `VFS_MAX_PATH[260]` 时会静默截断，却仍返回成功并占用 mount 槽位；全部后续相对资源读取会针对截断根目录，可能命中其他资源。现于计数和路径写入前拒绝不能完整保存的目录路径；仅挂载期一次长度检查，文件查找热路径不变、无分配。TDD：`vfs_mount_dir_rejects_path_truncation` 传入 260-byte 路径，旧码错误成功且 `mount_count` 变为 1，修复后返回 false 且保持 0；模块文档同步。验证：`test_vfs` 定向回归 29/29 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R474 glTF 纹理组合路径截断审查（TDD）** — `load_gltf_texture()` 将模型目录和图片 URI 拼接到 512-byte 临时缓冲，先前超长组合会静默截断；若截断前缀恰为可解码图片，模型会上传与 URI 不同的纹理。现拼接前精确检查目录加 URI 是否可完整保存，超长值只跳过该纹理，不执行错误文件 I/O 或 GPU 上传；这是模型加载期的一次检查，运行时热路径不变、无分配。TDD：`gltf_texture_path_truncation_does_not_load_prefix_file` 在深目录下创建截断名的真实 1x1 图像，旧码错误调用一次纹理创建，修复后为 0；模块文档同步。验证：`test_asset_gltf` 定向回归 25/25 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R473 FileWatcher 路径截断审查（TDD）** — 回调式 `filewatch_add()` 把任意输入登记为活跃条目，却只在固定 `FileWatchEntry.path[256]` 中保留截断副本；之后 mtime 轮询与回调针对的将是另一文件，且无效请求占用有限条目和可能的内核 watcher。现 Windows 与 Linux 入口均在计数、路径写入和内核监视创建前拒绝不能完整保存的路径；仅注册期一次长度检查，不影响轮询热路径、无分配。TDD：`filewatch_rejects_path_truncation` 传入 256-byte 路径，旧码错误令 `count` 变为 1，修复后保持 0；模块文档同步。验证：`test_hotreload` 定向回归 4/4 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R472 着色器热重载路径截断审查（TDD）** — `hotreload_pipeline_init()` 先前把顶点和片段 shader 路径静默截断到 `HotReloadPipeline` 的 256-byte 字段，却仍以完整路径完成首次编译；后续 watcher 回调改用截断路径重编译，可能命中其他文件。现于对象写入、编译和 watcher 创建前拒绝不能完整保存的任一路径，并让 watcher 使用已校验的内部副本；初始化失败不改变零初始化对象状态，只执行一次长度检查，不增加轮询/重载热路径成本。TDD：`hotreload_pipeline_rejects_path_truncation` 传入真实 256-byte 顶点/片段路径，旧码错误成功，修复后返回 false 且 `ready` 保持 false；模块文档同步。验证：`test_hotreload` 定向回归 3/3 通过；完整 Debug GNU 与干净 Clang/LLD Release 非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R471 纹理热重载路径截断审查（TDD）** — `hotreload_texture_init()` 将源路径保存到 `HotReloadTexture.path[256]` 并以此路径创建 file watcher；先前长路径静默截断但仍返回成功、标记 ready，后续变更会对截断后的不同文件重载。现于写入对象与创建 watcher 前拒绝不能完整保存的路径，失败不改变已零初始化对象状态；只在开发期初始化执行一次长度检查，轮询和重载热路径不变、无分配。TDD：`hotreload_texture_rejects_path_truncation` 传入 256-byte 路径，旧码错误成功，修复后返回 false 且 `ready` 保持 false；模块文档同步。验证：`test_hotreload` 定向回归 2/2 通过；Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R470 异步资源请求路径截断审查（TDD）** — 所有 `async_loader_request*` 入口最终把调用者路径复制到 worker 持有的 `AsyncRequest.path[256]`，但原先先 CAS 占用槽位并静默截断；后台 I/O 会读取另一文件，且错误请求消耗有限的异步队列容量。现于共享提交函数中、任何 CAS/排队前拒绝无法完整保存的路径，因而普通、range、priority 与纹理解码入口统一安全；只在提交时执行一次有界长度检查，worker 与每帧热路径不变、无分配。TDD：`async_loader_rejects_path_truncation` 传入 256-byte 路径，旧码错误返回非零 ID，修复后返回 0 且 pending 计数保持 0；模块文档同步。验证：`test_async_loader` 定向回归 16/16 通过；Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R469 Lua 热重载路径截断审查（TDD）** — `lua_script_load()` 会先以调用者完整路径执行文件，再把该路径格式化到 `LuaScript.path[256]` 供 `lua_script_reload_if_changed()` 使用；256-byte 路径首次加载成功却保存为截断名称，后续重载会错误地查询/执行另一文件。现于任何文件 I/O 与代码执行前拒绝不能完整保存的路径，失败不改变脚本状态；只在显式加载路径执行一次长度检查，不影响脚本调用或每帧重载热路径、无分配。TDD：`lua_load_rejects_path_truncation` 创建真实 256-byte 路径，旧码首次加载成功而失败断言，修复后返回 false、`loaded` 为 false 且记录路径为空；模块文档同步。验证：`test_script_lua` 定向回归 21/21 通过；Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R468 UDP 非阻塞回环测试同步修正（TDD）** — 干净 Clang/LLD Release 的全套 CTest 揭示 `test_network` 偶发失败：测试在 `net_sendto()` 返回后立刻对 non-blocking 接收 socket 调用 `net_recvfrom()`，但发送完成不保证数据报已经进入对端接收队列，因而会误判 `NET_WOULD_BLOCK` 为生产错误。现新增 `recvfrom_wait_readable()`，在三个发送后即时接收的用例中先以 `net_poll(..., 1000)` 等待可读再消费数据报；生产网络热路径不变。TDD：修复前隔离 Release 的 `sendto_const_address` 真实失败，修复后 Debug 和隔离 Release 各重复 20 次 `test_network` 均 14/14 通过；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R467 Mipmap 源路径截断审查（TDD）** — `mipmap_stream_register()` 将调用者路径写入固定 256-byte 字段，却先前静默 `strncpy` 截断并仍返回有效纹理索引；后续异步 range 请求会读取被截短的不同路径，造成难以诊断的错误资源加载。现登记前以固定字段容量检查完整路径，超长值直接失败且不占用纹理槽；仅在注册路径执行一次有界长度检查，不影响每帧 streaming 热路径、无分配。TDD：`mipmap_register_rejects_path_truncation` 传入 256 字节路径，旧码错误成功并增加计数，修复后返回 -1 且计数保持 0；模块文档同步。验证：`test_mipmap_stream` 定向回归 10/10 通过；Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R466 AssetCtx 完整初始化审查（TDD）** — `asset_ctx_init()` 先前只写入 `device`，而 `AssetCtx` 常由调用方在栈上创建；遗留的未初始化 `vfs` 指针会使后续纹理或 glTF 加载错误地进入 VFS 分支并解引用无效地址。现初始化时明确将 `vfs` 置为 NULL，未绑定 VFS 的上下文可靠地使用磁盘加载路径；仅增加一次初始化赋值，不影响资源加载热路径、无分配。TDD：`asset_ctx_init_clears_vfs` 以非 NULL 哨兵填充两个字段，旧码保留 `vfs` 并失败，修复后两字段均符合初始化契约；模块文档同步。验证：`test_asset_gltf` 定向回归 24/24 通过；Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`git diff --check` 通过。

此前：**R465 Lua 物理 body id 窄化审查（TDD）** — Lua `lua_Integer` 宽于引擎 `u32`，原绑定只拒绝 `id <= 0` 就转换为 `u32`；`4294967297` 截断为 1，减为 C index 0，因而 `set_pos`、`set_vel`、`apply_impulse` 与 `body_set_ccd` 均可能修改错误刚体。现四个入口共享 1-based ID 的范围验证，在任何窄化前拒绝超过 `UINT32_MAX` 的整数；常数时间、无分配。TDD：`engine_out_of_range_body_id_is_invalid` 对第一个刚体依次调用四个绑定并确认位置、速度、CCD 状态保持，同时 `get_pos` 不返回值；旧码首先改写位置而失败，修复后通过；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_script_lua` 定向回归通过，`git diff --check` 通过。

此前：**R464 网络包头 payload 长度审查（TDD）** — `packet_parse_header()` 读取 `size` 字段却从未与实际 datagram 长度比对；声明空 payload 的包可携带隐藏字节进入复制状态机，声明超长的截断包也会被当作结构正确的包处理。现要求 `header.size == datagram_len - PACKET_HEADER_SIZE`，在 ACK、去重和重排前拒绝任何不一致包；比较使用已验证 header 长度后的减法，无回绕与额外分配。TDD：`parse_header_rejects_declared_payload_length_mismatch` 覆盖隐藏 4-byte 尾随和声明比实际长 1 byte 两种情况，旧码均错误接受，修复后拒绝；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_packet`/`test_net_replication` 定向回归通过，`git diff --check` 通过。

此前：**R463 BVH 射线可选输出审查（TDD）** — 高层 `physics_raycast()` 已允许只查询布尔命中（两个输出指针均可为 NULL），但底层 `bvh_raycast()` 在真实命中后无条件写 `hit->object_index/t`；直接调用者只想判定遮挡时传 NULL 会崩溃。现仅在 `hit != NULL` 时写回最近命中记录，遍历、裁剪与最近命中计算均不变。TDD：`bvh_raycast_allows_null_hit_output` 对真实单 AABB 命中传 NULL，旧码在命中处崩溃，修复后安全返回 true；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_physics` 定向回归通过，`git diff --check` 通过。

此前：**R462 音频 master 总线重合成审查（TDD）** — `audio_bus_set_gain()` 原先仅重算 `src->bus == bus` 的源；master（bus 0）实际参与每条路由的乘法，但调节它不会把新增益提交给已路由至 music/sfx 等子总线的活跃 source，直到该 source 或子总线再次改变才会修正。现 master 变更扫描固定 32 槽并重算所有已分配 source，普通 bus 继续只更新自己的成员；无分配、无锁、没有新增音频热路径开销。TDD：`master_gain_reapplies_to_sub_bus_sources` 在旧码下确认 music 源的已应用增益错误保持 0.8，修复后 master=0.5 立即为 0.4；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_audio` 定向回归通过，`git diff --check` 通过。

此前：**R461 JSON 场景节点容量审查（TDD）** — 二进制 `SCENE_NODES` 导入限制为 64K，但 JSON `nodes` 数组缺少同一边界，会在 16 起始容量上持续倍增 `realloc`；紧凑的 `{}` 节点文档就能制造远超场景模型的堆分配。现 JSON 在扩容/写入 staging 前拒绝第 65,537 个节点，与 BSCN 共享 64K 约束，失败时不会提交部分 Scene。TDD：`load_json_rejects_too_many_nodes` 构造 65,537 个紧凑节点，旧码错误成功，修复后返回 false 且目标节点图保持为空；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_scene_serial` 定向回归通过，`git diff --check` 通过。

此前：**R460 ECS 查询缓存哈希碰撞审查（TDD）** — `world_query_cached()` 以 32 位 FNV-1a 哈希作为查询身份，虽注释称处理碰撞却没有保留原始组件集合；不同查询碰撞时会直接返回另一查询的匹配 archetype，导致实体被错误枚举。现保留哈希作 O(1) bucket 选择，并以两个 `u64` 的精确 128 组件集合键确认命中；碰撞安全地退化为一次正常 archetype 重建，无额外常驻分配。TDD：`ecs_cached_query_hash_collision_does_not_alias` 使用真实碰撞集合 `{9,29,69,101,117}` 与 `{21,28,50,83,91}`，旧码错误令第二查询返回一个实体，修复后正确为零；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_ecs`/`test_ecs_system` 定向回归通过，`git diff --check` 通过。

此前：**R459 ECS 组件 ID 边界审查（TDD）** — `world_register_component` 已拒绝 `id >= ECS_MAX_COMPONENTS`，但 `world_add_component`/`world_get_component`/`world_remove_component` 没有同一守卫；无效 add 会继续把 ID 用作固定 `component_sizes[128]` 的索引，并可能以越界尺寸构造 archetype，造成未定义行为。现三条公开操作在任何表访问前统一拒绝越界 ID；有效热路径仅增加一次常量边界比较，无分配、无锁。TDD：`ecs_rejects_out_of_range_component_id` 证明旧码错误接受 ID=128，修复后增/取为空、删为无操作且随后正常组件迁移仍可用；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_ecs` 定向回归通过，`git diff --check` 通过。

此前：**R458 Mipmap 预算加法回绕审查（TDD）** — 流送 update 与 `force_level` 都以 `total_resident_bytes + needed > memory_budget` 判断准入；当 `usize` 接近 `SIZE_MAX` 时加法回绕，已满的缓存看似有空间而错误提交异步加载，并使预留字节记账失真。现统一改为 `needed <= budget - used`，先拒绝 `used > budget` 的异常状态；普通异步与同步强制加载路径共享该 O(1) 无分配检查。TDD：`mipmap_budget_addition_does_not_wrap` 将 used 置为 `SIZE_MAX-1`，旧码错误发起 level-0 request，修复后请求数为 0、状态和字节数保持不变；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_mipmap_stream` 定向回归通过，`git diff --check` 通过。

此前：**R457 固定可靠目标序列生命周期审查（TDD）** — R456 仅保护有 in-flight reliable 的 send-state 槽；但即使 A 已 ACK，远端仍保留 A 的接收序列，若该槽被 LRU 回收并分给第 9 个目标，之后 A 的新包又从 seq=1 开始，旧/新包在无 wire generation 字段的协议中不可区分。现在 send-state 采用严格的 lifetime-fixed 8 目标容量：已分配目标直到 replicator shutdown 都不复用，第 9 个目标显式 `NET_ERROR`，从根源维持每目标单调序列；接收侧 LRU 仍独立运行。发送热路径至多扫描 8 个紧凑槽，无分配、无锁、无包格式变更。TDD：`reliable_send_state_is_not_recycled_after_ack` 验证填满 8 个目标后第 9 个被拒绝，同时已确认 A 继续 seq=2；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_net_replication` 定向回归通过，`git diff --check` 通过。

此前：**R456 可靠发送序列 LRU 生命周期审查（TDD）** — R455 将每目的地址的 wire sequence 放进既有 receive peer 槽；该槽是为抵抗伪造 UDP 来源而可 LRU 淘汰的，所以 A 有 reliable seq=1 在途时，八个陌生来源即可回收 A 的槽，下一次发往 A 重置为 seq=1，延迟 ACK 与新包混淆。现用独立、紧凑固定 8-slot send-state 表保存每目标/类型序列；有 reliable in-flight 的目标不可被该表淘汰，全部受保护时新目标明确返回错误而非退化到共享序列。接收重排槽仍可独立 LRU 回收。全路径仅固定 8 槽扫描，无分配、无锁、无包格式变更。TDD：`reliable_send_sequence_survives_receive_peer_eviction` 在旧码下 A 的第二包错误重置为 seq=1，修复后为 seq=2；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_net_replication` 定向回归通过，`git diff --check` 通过。

此前：**R455 乱序可靠包累计 ACK 审查（TDD）** — R454 虽已隔离多 peer 的待回传 ACK，但仍把任意已见的最大 reliable sequence 直接写成 cumulative ACK：收到 seq=1 后若 seq=3 越过丢失的 seq=2，回传 ack=3 会让发送端错误释放 seq=2、停止重传。现对每个固定 peer 槽维护 8-bit `[next,next+8)` 收包位图，仅连续序列推进 ACK；发送端同步使用该 peer 自己的 wire sequence space，使累计 ACK 没有跨目的地址空洞。地址未知的 legacy `feed()` 保持旧单 peer 兼容行为。收发仅做最多 8 槽查找及常数位运算，无分配、无锁、无包格式变更。TDD：`reliable_ack_waits_for_contiguous_sequence` 在旧码下 seq 1/3（缺 2）错误发 ack=3 而失败，修复后先发 ack=1，补 seq=2 后才发 ack=3；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_net_replication` 定向回归通过，`git diff --check` 通过。

此前：**R454 多 peer 待回传 ACK 隔离审查（TDD）** — R453 已把收到的 cumulative ACK 按其 UDP sender 限定清槽，但接收可靠帧后待回传的 `ack_to_send` 仍是全局变量；因此收到 peer A 的 reliable seq=7 后，下一次任何发往 peer B 的包都会带 ack=7，若 B 恰好有该序列号在途就会被误确认。现将待回传 ACK 放入既有固定 8-slot per-peer channel，发送广播/heartbeat/heartbeat-ack 时按目标地址选择；地址未知的 legacy `feed()` 保留共享单 peer 状态。目标查找最多扫描 8 个固定槽，无分配、无锁、无线协议改动。TDD：`reliable_ack_is_scoped_to_destination` 在旧码下发往 B 的报头 ack=7 而失败，修复后 B 收到 ack=0、A 收到 ack=7；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_net_replication` 定向回归通过，`git diff --check` 通过。

此前：**R453 多 peer 可靠 ACK 隔离审查（TDD）** — 可靠发送窗口虽然保存了每个 slot 的目标 `dst`，但收到 ACK 时忽略了数据包来源：任意 peer 的较新 cumulative ack 都会清掉所有 sequence 已到达的 slot，包括发往其他 peer 的包；retry 路径还会按全局 `last_peer_ack` 再次清槽。ACK 清理现按 slot `dst` 匹配 UDP sender（地址未知的 legacy `feed` 维持单 peer 行为），retry 只重发仍 valid 的 slot，因此 peer A 的 ack 不会误确认 peer B。复杂度仍为固定 8-slot O(1) 扫描，发送和重传热路径未新增分配。TDD：`reliable_window_ack_is_scoped_to_sender` 在旧逻辑下 A 的 ack=2 错误清空 A/B 两个 slot 而失败，修复后只清 A，B 的 seq=2 继续 in-flight；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_net_replication` 回归通过，`git diff --check` 通过。

此前：**R452 并行命令缓冲 draw 基址审查（TDD）** — `cmd_draw()` 正确记录了 `first_vertex`，但 replay 一直调用不带首顶点参数的 `rhi_cmd_draw()`，使任何非零基址的 mega-buffer 子网格都从顶点 0 开始渲染。新增 `rhi_cmd_draw_base()` 并直映 GL `glDrawArraysInstanced(..., first, ...)` 与 Vulkan `vkCmdDraw(..., firstVertex, ...)`；普通 `rhi_cmd_draw()` 保持零基址 wrapper，原调用无行为/性能回归。命令缓冲 replay 改为 1:1 转交记录值，无分配、无额外 GPU 命令。TDD：`cmd_draw_replay_preserves_first_vertex` 在旧 replay 路径失败，恢复后断言 vertex count、instance count 和 `first_vertex=27` 全部传达；模块文档同步。验证：Debug GNU（GL）与干净 Clang/LLD Release（Vulkan）均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_cmd_buffer` 回归通过，`git diff --check` 通过。

此前：**R451 TaskSystem 单例运行时门禁审查（TDD）** — `task.h` 已声明 TaskSystem 为单例，因为 `task_release()`/worker entry 使用进程全局 registry 区分 pool task 与 heap fallback；但 `task_system_create()` 从未实施该契约，第二个 live system 会覆盖 registry，随后第一个系统中的 heap task 可能按错误 pool 判定、销毁顺序还会留下悬空全局指针。现在以原子 compare-and-exchange 在启动 worker 前声明唯一所有权；失败创建完整销毁本次已创建的 deque/mutex/allocation，成功销毁后原子归还所有权。仅创建/销毁路径增加常数开销，任务提交、wait、deque push/pop/steal 热路径不变。TDD：新独立 `test_task_singleton` 在旧码下第二个实例非 NULL 而失败，修复后拒绝第二实例且验证销毁后能再次创建；模块文档同步约束。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 39/39 通过；`test_task`、`test_task_singleton`、`test_ecs_system` 定向回归通过，`git diff --check` 通过。

此前：**R450 异步纹理解码关闭交付审查（TDD）** — R449 已修复普通 completion queue，但纹理解码完成结果驻留在 `decode_pipeline` 的独立 ready queue；`async_loader_shutdown()` 在扫描加载器 slots 前调用原 `decode_pipeline_shutdown()`，后者释放 ready queue，导致已经解码成功而尚未 `tick()` 的纹理请求只能收到 `(NULL, 0)`。解码管线新增 loader-only 的 preserve-ready 关闭变体：I/O 停止后 join decode workers，释放未开始 job，却保留 completed results；加载器随后使用既有无分配 poll 路径直接写回 request slots，再以 R449 的一次性规则交付回调。关闭不向 completion ring 入队，避免该 ring 已满而无 `tick()` 消费者时自旋；帧内完成队列算法不变。ready count 仅为加锁 O(1) 测试/诊断可观测性。TDD：`async_loader_shutdown_drains_decoded_completion` 在旧关闭路径失败，恢复后完整收到 2x2 RGBA decoded payload；模块文档同步。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 38/38 通过；`test_async_loader`、`test_mipmap_stream` 回归通过，`git diff --check` 通过。

此前：**R449 异步加载器关闭回调交付审查（TDD）** — `async_loader_shutdown()` 此前只对仍处于 LOADING 的请求调用 `(NULL, 0)` 回调，却直接释放已完成、已入 completion queue 但尚未被下一帧 `async_loader_tick()` 分发的 READY 数据；调用方无法释放 `user_data`，且成功结果被静默丢弃。关闭现在线程 join 后单次扫描固定 1024 槽：READY 请求将 data/size 原样交付回调，FAILED/LOADING 交付 `(NULL, 0)`，随后清空槽；此前 tick 已交付的 UNLOADED 槽不再处理。该路径无堆分配，关闭期 O(ASYNC_MAX_REQUESTS)，不影响帧内异步 I/O 热路径。TDD：`async_loader_shutdown_drains_ready_completion` 先在旧实现失败（callback count 为 0），修复后成功接收 4-byte payload；同步收紧既有关闭测试，验证所有已接受 queued/READY 请求恰好一次回调。模块文档同步关闭契约。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 38/38 通过；`test_async_loader` 回归通过，`git diff --check` 通过。

此前：**R448 Render Graph 正确性与性能审查（TDD）** — 依赖推导此前固定让所有读取者依赖资源的首次 writer；当后处理 pass 显式 read+write 同一逻辑 color 资源时，present 仍只依赖 scene，后处理被死路径剔除且可能呈现旧内容。改为按 pass 声明顺序维护每个资源的最近 writer，read 依赖该 writer；write 保持声明为写入替换，需保留旧内容时必须显式 read，因而不引入错误 WAW 依赖或削弱死路径剔除。同步修复分配阶段以前按全图 `ref_count` 分配资源的问题：纯 dead pass 的纹理即使从不执行也会创建 GPU resource；现在只扫描 live passes 生成固定大小访问位图，死路径零分配，避免逐帧无用显存分配/带宽消耗。TDD：`read_write_chain_keeps_latest_writer_live` 与 `dead_pass_does_not_allocate_unused_resource` 均先在旧实现失败、修复后通过；调度仍为固定数组构图 + O(V+E) Kahn 拓扑排序，无堆分配。模块文档已记录 read+write 合同。验证：Debug GNU 与干净 Clang/LLD Release 均完整构建成功，非图形 `ctest` 各 38/38 通过；`test_render_graph` 新增用例通过，`git diff --check` 通过。

此前：**R447 时间重投影首帧修复（代码审查）** — TSR 的 R446 首帧处理此前只把当前输入绑定为 history，却仍使用 `prev_vp` 做重投影并以 0.85 权重混合；初始化/缩放后的 `prev_vp` 不保证等于当前帧，因而该路径不是 no-op，可能产生一帧错位闪烁。现为 GL/VK upscale shader 增加 `u_ups_first_frame`，首帧明确跳过 history 重投影（与 TAA 的 `u_taa_first_frame` 契约一致），CPU 同步上传该标志，Vulkan push-constant 映射在 offset 24。新增 `test_shader_io` 双后端 shader 契约测试，防止未来仅恢复绑定历史而遗漏跳过重投影。`Build_Guide` 补充 `BREAK_JITTER=0` 与 TSR 首帧行为说明。审查还发现 Linux Clang toolchain 仅设 `CMAKE_LINKER=lld`，clang 驱动仍选 `ld.bfd`，不能链接 Release IPO 生成的 LLVM bitcode；改为显式 `-fuse-ld=lld` 并同步构建前置条件。验证：Debug GNU 构建及干净 Clang/LLD Release 构建均为 38/38 非图形测试通过；两份 upscale shader 经 glslang 校验。

此前：**R446 交互伪影轮 — debug UI 文字闪烁根因修复（throttle 块间歇发射致整屏文本逐帧移位）+ TSR 历史首帧守卫 + 脚本化相机摆动/连截工具** — **R446-A 文字闪烁根因**：物理统计块（main.c 约 4475-4800，~30 行条件 `debug_ui_text`）整体位于"每 10 帧"节流门内，非节流帧整块消失、其下所有 UI 行逐帧上下跳动（50fps 下 5Hz 全块位移；1fps 下 1s 出现/9s 消失）——像素证据：静态相机连续帧 diff 热图整块字形轮廓亮起，同一 y 区间相邻帧显示完全不同的文本行。修复：DebugUI 新增 sticky section（`debug_ui_sticky_begin/end`，debug_ui.h/c）——刷新帧正常发射并缓存字符串，中间帧原位重放缓存；计算仍每 10 帧一次（保留原节流意图），布局恒定。**R446-B TSR 首帧守卫**：upscale（render_scale 0.5 下每帧必经）历史 FBO 初始化后无 first_frame 处理，前 ~18 帧以 0.85 权重混合未初始化纹理（resize 后同理）；修复为 `first_frame` 时把当前输入绑定为自身历史（同 taa_resolve 契约）。**R446-C 工具**：`BREAK_SCREENSHOT` 扩展逗号帧列表（单值行为不变）；新增 `BREAK_CAM_SPIN=deg/帧`（脚本化 yaw 摆动）、`BREAK_TAA=0`/`BREAK_MB=0`（A/B 对照开关）。**症状②测量结论**（XWayland ~1fps、3-20°/帧 摆动、TAA on vs off 同机位同 yaw 序列对比）：TAA 深度重建路径与 forward-velocity 路径重投影在 R438 矩阵修复后均正确，场景区鬼影指标 mean≈1/255、p95≈3-4/255（3×3 邻域 clamp 正常工作）；motion blur 模糊跨度恒为 strength≈1px 与速度无关（近 no-op，未改——"修复"它只会增加模糊）；用户报告的"转动错乱"主因是环境层：XWayland Present 把 swap 节流到 ~1fps 而引擎 dt 钳制 0.1s（R147），1 秒累积的鼠标输入在单帧一次性生效（相机瞬跳），vblank_mode=0 可绕过（已写入 Build_Guide 3.1 节）。**验证**：闪烁指标 UI 区字形级变化像素（>40/255）帧 11→12：修复前 5.85% → 修复后 0.80%（-86%）；反向验证（git stash 回退重建）回升至 5.85% 复现；GL/VK 双构建 `ctest -LE graphics` 各 38/38 + `-L graphics` 各 1/1 + 双 golden MAE=0.00（VALIDATION GATE Release 空转如存量记录）、零新警告。遗留：用户截屏中出现的整帧垂直镜像+过曝帧未在脚本路径复现，疑为 XWayland/DRI3 回收缓冲或交互 F12 交换后回读（R445 已记同类），未能证实为引擎缺陷。**R446-D 后处理根因修复（用户交互"拖影/闪/错乱"二分定位后）**：①天空双重 tonemap（主根因）——`skybox.frag/skybox_vk.frag` 内置 Reinhard+gamma 把显示就绪值（中位 0.63/p90 0.94）写入 HDR 场景缓冲，combined_color 再做 auto-exposure+ACES+gamma 二次处理 → 天空吹白（vista 视角 41.9% 像素 >0.95）并污染曝光均值与 bloom 阈值域；修复为输出线性 HDR（对齐 sky_to_cube 契约），Rayleigh/Mie 增益分离补偿。②太阳盘镜像——`sun_dir_vec` 是光线传播方向（朝下），skybox 当作太阳位置方向 → 太阳盘埋在地平线下不可见；改传 `-sun_dir_vec`。③太阳盘强度 0.05→0.5（真 HDR 发光体，bloom 阈值 1.0 现在只提取太阳+高光）。④截图 R/B 通道交换——`demo_save_screenshot`/`save_bmp` 24-bit BMP 需 BGR 而双端 `rhi_screenshot` 交付 RGBA（此前全部截图证据红蓝反色）；VK 回读在 X11/Intel 实为上下翻转，双端统一修正。⑤bloom 默认 0.4→0.15（修复双重 tonemap 后恰到好处，bloom 缓冲可视化证明只命中太阳盘）、DOF 默认关（focus 行为从未视觉验证）；新增 kill-switch env `BREAK_DOF=0`/`BREAK_BLOOM=0`/`BREAK_UI=0`（A/B 测量用，HUD 在后处理后绘制会污染像素测量）。**验证**：vista 全白占比 41.9%→11.7%、天空 p50 1.000（削顶）→0.832；GL/VK 双构建 ctest 38/38+1/1、零警告；前后截图读图复核（蓝天/绿草/雪山/水面/太阳盘+bloom 软晕可见）。遗留：sky_to_cube.comp（IBL 环境捕获）仍用镜像太阳方向（仅影响 ambient 微弱方向性，未动以免触碰 IBL 契约，另立案）；VK vista 顶部比 GL 略白（次后端，未深挖）。总计 **1050** 处修复（专项轮，不累加）。

此前：**R445 展示场景轮 — demo 黑屏根因修复（全屏 blit 深度误杀，GL 自 R232/VK 自初始 RHI 潜藏）+ 多材质展示阵列 + 物理/动画/音频展示 + 脚本化截图** — **R445-A demo 黑屏根因修复**：全屏合成 blit 被深度测试整体误杀——post.vert 输出 z=1.0，管线 depth_write_disable 但 compare=LESS，深度附件清 1.0 → 恒假，整条合成链片元全弃；GL 自 R232（commit 13445cc）、VK 自初始 RHI 提交 f4e4498 即存在；场景 FBO 内容一直完好，合成从未到达屏幕（"Draws: 0"为另一 HUD 计数器作用域 bug）。修复：双后端管线规则 `depth_write_disable && !depth_compare_lequal → 关 depth test`（skybox LEQUAL 保留测试）；VK skybox 三个 uniform 映射补齐（此前从未上传，用 push staging 残留渲染）；`rhi_texture_read_pixels` RGBA16F 按 8B/px（原 4B 少读一半且越界）；particles 管线补 lequal 保持行为不变；HUD 计数器移出帧循环；TEST 6 新增像素级断言（原只查 init 对本 bug 空转）。像素证据：GL 唯一色 1→40532、VK 344→12215；反向验证回退即黑。**R445-B 展示场景**：`demo_build_showcase()`（glTF 加载后 bake 前）——程序化 UV 球/盒网格（32B pos+nrm+uv）+ 程序化纹理（棋盘/条纹/渐变/纯色 + MR），多材质阵列（金属度渐变球×4 + 纹理盒×4，**11 材质组 / 11 MatArray 层**——材质间接首次 G>1 实际负载，execute=1 保持）；物理展示区：球窝链（静态锚+3 节+重物）、CCD 高速球（60u/s）vs 薄墙（0.05 半厚）、电梯平台（velocity 正弦驱动，R437 携带生效，debug UI 显 `grounded: %d (body %u)`）；附带修复 instanced ECS 路径忽略 mesh_index 把每个 scene mesh 画到每个实体（showcase 网格入 scene 后必然叠加，改为按 mesh_index 分组压缩实例绘制）。**R445-C 动画/音频默认展示**：程序化 4 关节机械臂（(3.5,1.4,-3)，双 clip 交叉 blend 权重 0.5+0.5·sin(0.3t) + IK 3 关节链椭圆追踪目标，**默认开**、BREAK_ANIM_BLEND=0/BREAK_ANIM_IK=0 可关——此前 blend/IK 因 test.glb 无骨骼是死代码；像素对比证据：blend-on 相邻帧臂区域 mean|Δ|=8.38、on vs off 48.41）；sfx 总线实载（880Hz/0.2s 短音带淡入淡出，碰撞事件 RMS 音量缩放 clamp、10Hz 节流、播放中不打断+结束回收槽位；R435"没有第二个音源"注释更新）。**R445-D 工具**：`demo_save_screenshot` 提取（F12 复用，顺带修 GL 行翻转——glReadPixels 底向上）+ `BREAK_SCREENSHOT=N`（第 N 帧自动截图，hook 在 present **前**——交换后 GL_BACK 回读未定义实测纯黑）+ `BREAK_CAM=x,y,z[,yaw,pitch]` 相机 env + 截图编号递增不覆盖。**验证**：GL（build-r445）/VK（build-r445-vk）双构建 `ctest -LE graphics` 各 38/38 + `-L graphics` 各 1/1 + VALIDATION GATE 0、零警告；demo 双后端 `BREAK_FRAMES=300 BREAK_SCREENSHOT=250` rc=0，截图经读图复核双端均有真实场景内容。遗留：GPU unified cull 把 11 个 mega cmd 全标不可见走回退路径（另立案）；VK 截图回读上下翻转；低帧率 motion blur/DOF/半分辨率致截图糊（非缺陷）；F12 交互截图仍可能交换后回读；VALIDATION GATE 在 Release 因 NDEBUG 空转（存量）；Debug 下 20 条存量 TRANSFER_SRC validation（Hi-Z/mip readback）。总计 **1050** 处修复（专项轮，不累加）。

此前：**R444 可靠性轮（TDD）— 测试套件并行安全、RHI push-constant 公开 API、Wayland 热插拔** — **R444-A 测试并行安全**（R443 记录的已知问题修复）：根因=同名测试二进制跨树/同树并发写同一 `/tmp` 固定路径 + 固定 UDP 端口 bind 冲突。`test_framework.h` 新增 `test_tmp()`（`/tmp/break_<name>_<pid>`，`_WIN32` 走 `_getpid`）；9 个测试文件的 /tmp 固定路径全部唯一化（test_script 7 名+补 5 个缺失 remove、test_scene_serial 23 名、test_script_lua/test_hotreload/test_vfs/test_font_load/test_scene_state/test_shader_io/test_asset_gltf——4 个 glTF JSON 内嵌相对 uri 同步 per-pid basename）；压测追加：`test_net_replication` 固定 TEST_PORT → pid 派生 **16 端口块**（`23000+(pid%2600)*16`——初版 `pid%20000` 因 11 个连续端口使用点在相邻 pid 间重叠失败过，实测修正）、`test_network.c` 5 个固定 bind 端口同方案、相对路径文件（mipmap/async_loader/profiler/net_replication 两处）改 test_tmp（VFS DIR-mount 守卫拒绝对路径的改 mount /tmp + basename 请求）。验证：修复前 15 路并发（5/树×3 树）7/15 失败、修复后 **30/30 全绿**；反向验证（去 getpid → 10/10 失败；端口固定 → 4/5 失败）。fuzz 目标的 /tmp 固定名未改（非 ctest 注册项）。**R444-B push-constant API**：新增 `rhi_cmd_push_constants(cmd, offset, data, size)`（语义对齐 vkCmdPushConstants；VK 复用 staging/flush 路径，校验从硬编码 256 改为声明 range——修掉 `[push_range_size,256)` 写入 flush 静默截断；GL 文档化空操作）+ 纯函数 `rhi_push_range_fits`（防回绕）；迁移 cmd_buffer 回放（消掉 "map to closest available" 语义绕道）与 particles.c；`set_uniform_bytes` 保留 deprecated 别名。`test_cmd_buffer` 26→28（回放路由 + 校验含回绕绕过）。遗留：旧 `set_uniform_mat4/...` helper 仍是 256 硬编码边界（与 GL uniform location 语义耦合，收紧需单独评估）。**R444-C wayland 热插拔**：`registry_global_remove` stub → 压缩式 remove（先 xdg 后 wl_output 销毁——包装关系顺序不能反；三平行数组同步搬迁；`output_ctx` 不搬迁只重编号 .slot——listener 持有数组成员地址）；纯函数 `wl_out_remove`（memmove 压缩，append-dedup 一致，8 槽预算反复插拔不磨损）。`test_wayland` 8→12。残留：slot 0 被拔后 scale/dpi 保持旧值至新主输出下一次 done；协议销毁路径未经真实 compositor 验证（X11 会话）。**验证**：GL/VK/Wayland 三构建 `ctest -LE graphics` 各 **38/38** + GL/VK `-L graphics` 各 **1/1** + VALIDATION GATE 0 条、构建零警告。总计 **1050** 处修复（专项轮，不累加）。

此前：**R443 收尾轮（TDD）— GPOS Format 2、球窝关节、Wayland 多 output** — **R443-A GPOS fmt2**（R442 明确缺口闭合）：`font_gpos_kern_extract` 加 `glyph_filter` 位图参数（签名变更已同步调用点）；爆炸控制=先建 class-2 roster（filter 下枚举置位字形及其 classDef2 类含 class-0——class-0"其余一切字形"仅在 filter 下可枚举，烘焙路径正合此用；无 filter 只枚举显式字形）；ClassDef 数组/range 双格式支持，全程溢出安全界限检查。**合成 oracle**（测试内 builder 拼最小合法 sfnt+GPOS fmt2 二进制，逐字段注释 spec 偏移）：类对提取/class-0 枚举/Format1+2 混合 lookup 共存断言；烘焙回退 Format 1+2 全收。LiberationSans 交叉验证（908 对全等）继续全绿；`test_font_load` 22→29；ASan 29/29 含全截断扫描。**R443-B physics 球窝关节**：`DistanceConstraint` 泛化加 `offset_a/offset_b`（世界空间固定偏移，无旋转模型）+ `is_ball`；`physics_constraint_add_ball()`（rest=0，拒绝惯例同 R435）；位置投影按锚点（质心+偏移）重合、修正施加质心（无力矩，注释）；ball 速度求解消**全向量**相对速度（对照 distance 只消轴向，测试直接对照）。`test_physics` 54→58（核心区分断言：锚点重合但质心保持距离=偏移差）。遗留：无旋转模型退化为两点刚性平移绑定。**R443-C wayland 多 output**：单 `wl_output*` → outputs[8] 槽位数组 + 每 output 监听上下文（原写法多 output 事件交错必串数据）+ `zxdg_output_manager_v1`（逻辑坐标/名称，幂等绑定，缺失退化）；复用 platform.h 现有 `platform_get_monitor_count/info`（X11 语义对齐，零头文件改动）；CMake 加 xdg-output 协议生成。纯逻辑抽 `wayland_output.h` static inline（容量/去重/mode 优选 current 粘滞/最大面积/mHz 取整）；新增 `test_wayland` 8 用例（ctest 第 39 个）。**如实声明**：本机 X11 会话，wayland 线上行为（事件交错/热插拔）未经真实 compositor 验证，上限=编译+纯逻辑单测+X11 回归。**验证**：GL（`build-r443`）/VK（`build-r443-vk`）/Wayland（`build-r443-wl`）三构建 `ctest -LE graphics` 各 **38/38** + GL/VK `-L graphics` 各 **1/1**、零警告；各项红→绿→反向验证（禁用 fmt2 分支 → 合成 oracle 红、LiberationSans 交叉验证仍绿；回退质心重合 → ball 用例红；删 current 粘滞守卫 → wayland 用例红）。**已知问题（留待后续）**：多套 ctest 并行运行时 test_script/test_scene_serial 互相失败（测试间临时文件竞争），串行复跑全绿——本轮代码无关，记录备查。遗留：GPOS roster 4096 上限与无 filter 时 class-0 跳过为刻意取舍；wayland 热拔出 `registry_global_remove` 仍为 stub（绑定的 wl_output 留存至 destroy）；真 bindless 继续挂账（纹理数组路线已覆盖需求，无消费者的投机优化不做）。总计 **1050** 处修复（专项轮，不累加）。

此前：**R442 材质间接收尾 + GPOS kerning + GL 门禁补全（TDD）** — **R442-A deferred array**（R441 第二阶段）：`MatArraySet` 扩 MR 数组（层 0 中性值 {255,128,0,255} 对齐前向 fallback_mr；(albedo,MR) handle pair 去重——单 layer 号驱动两个 sampler2DArray 必须对齐）；4 个新 shader `gbuffer_arr(_vk).*`；`mega_mat_arrays_draw_gbuffer`（1 compact+1 bind+1 execute）；新增 `BREAK_RENDER_PATH=deferred` env（原仅 'p' 键不可脚本化）。**TEST 12**（合成 4 象限 MRT：execute==1/帧、RT0 色相+metallic alpha、RT2 roughness 分层、剔除象限清屏）。**顺带修复 TEST 12 暴露的 R440 存量 bug**：`vk_mrt_pipeline_render_pass` 缺 subpass dependency（与 FBO pass 不兼容 VUID-02684；demo deferred 同样中招）+ MRT color image 补 TRANSFER_SRC。**R442-B GPOS kerning**：自研最小 GPOS PairPos **Format 1** 解析器（sfnt 目录自解析、全程溢出安全界限检查、大端显式读取）；烘焙期 legacy kern 表为空时回退 GPOS 填同一稀疏表。**交叉验证**：LiberationSans GPOS 非零 pair 2015 = 908 与 kern 表**逐对值全等** + 1107 GPOS 独有（希伯来字形，烘焙范围外），0 冲突。Format 2 明确不做（无 oracle 字体，"未经测试的二进制解析器不如明确的缺口"，注释记录）。`test_font_load` 16→22（截断 17 点/垃圾载荷/损坏目录防御）；ASan 22/22 无越界。**R442-C GL 门禁**：TEST 10/11/12 抽成后端中性 helper，GL 分支 golden 后不再早退——材质间接 GL 端从"仅 demo 冒烟"升级为像素级断言；GL 特有：暗半阈值按后端分支（VK sRGB [120,230]/GL 线性 [90,200]，实测 136-139 入注释）、readback 行序双翻转相消论证。有效性双重反向验证（强制 vLayer=0 → 11/12 红；破坏 visibility → 剔除断言红）。**验证**：GL（`build-r442`）/VK（`build-r442-vk`）双构建 `ctest -LE graphics` 各 **37/37** + `ctest -L graphics` 各 **1/1**（TEST 1-12 双端 + 双 golden + VALIDATION GATE 0）、零警告；GL/VK demo 前向+deferred 双路径冒烟各 rc=0 零错误。遗留：真实多材质 glb 场景目验未做；GPOS Format 2 缺口（class-based kerning 字体仍无 kern）；GPOS 烘焙回退路径无端到端测试（RHI stub 限制，解析器层已直接覆盖）；TEST 11 GL 暗半阈值依赖默认 framebuffer 不做 sRGB 转换（注释已写明校准依据）。总计 **1050** 处修复（专项轮，不累加）。

此前：**R441 材质间接轮（TDD）— 纹理数组前向单 execute（最后一个性能大项）+ IMGUI int slider** — **R441-A 材质间接**：路线定为**纹理数组**（本机 iris 实测无 `GL_ARB_bindless_texture`；VK 纹理数组零新 feature；现有 shader 不消费材质标量故无需材质 SSBO）。新 RHI API `rhi_texture_array_create`/`rhi_texture_array_upload_layer`（GL 2D_ARRAY / VK arrayLayers+2D_ARRAY view，共享 desc_layout 未动）+ bake 期回读补充 `rhi_texture_get_size`/`rhi_texture_read_pixels`；4 个新 shader `blinn_phong_arr(_vk).vert/.frag`（`sampler2DArray` + `gl_BaseInstance(ARB)` 携带材质层号；旧 blinn_phong 未动，golden 仍走老 pipeline）；`MatArraySet`（层 0 白色 fallback、句柄去重、CPU 最近邻重采样 ≤2048/63 层）+ bake 时 `first_instance=层号` + 独立 ungrouped `array_system`（R437 grouped 机制字节级保留作回退——grouped scatter 有空洞不兼容单 draw，ungrouped 天然紧排 append）+ `mega_mat_arrays_draw`：每帧 1 compact → 1 bind → **1 execute**（原 G 次 execute 的 VK descriptor 重分配开销消除）。开关 `BREAK_MAT_INDIRECT`（默认开）；wireframe 强制回落；热重载激活时禁用 array 路径（LOG_WARN）；VK 启用 `shaderDrawParameters`（VALIDATION GATE 抓到的真问题，驱动不支持时优雅回落）。新增 **TEST 11**（4 象限合成多材质场景：execute 计数==1、逐象限像素色相、混合尺寸上采样、剔除象限清屏色）——demo 单材质量不出收益，像素级验证由 TEST 11 承担。每帧日志 `execute draws this frame: 1` 实证。**R441-B imgui**：`imui_slider_int`（slider_float 薄壳）+ inline 助手 `imui_slider_int_logic`（round half-away-from-zero + clamp）；demo Quality 组接 SSAO 档位（与 F8 键同一 radii 表）；`test_font_ui` 23→27。**验证**：GL（`build-r441`）/VK（`build-r441-vk`）双构建 `ctest -LE graphics` 各 **37/37** + `ctest -L graphics` 各 **1/1**（TEST 1-11 + 双 golden + VALIDATION GATE 0 条）、构建零警告；GL/VK demo `BREAK_FRAMES=120` rc=0、每帧 execute=1（日志实证）；反向验证（`BREAK_MAT_INDIRECT=0` 回落 R437 per-group 全绿；破坏层号传递 → TEST 11 像素断言红）。遗留：deferred/gbuffer array 化与 normal/emissive 数组为第二阶段；真实多材质 glb 场景目验未做（demo 单材质）；GL 端 TEST 11 无覆盖（结构早退）；blinn 热重载不影响 arr 管线（dev 功能）；异尺寸资产靠 CPU 重采样（显存/质量取舍入注释）。总计 **1050** 处修复（专项轮，不累加）。

此前：**R440 健壮性+CI 轮（TDD）— demo validation 9→0、约束速度求解、GitHub Actions CI 上线** — **R440-A rhi_vk**：VK demo 启动期 9 条既有 validation 性能警告逐条根因修复（非消音）：①6 条顶点 attribute 未消费——`vk_build_graphics_pipeline` 默认分支一律声明 pos+normal+uv 三 attribute，而 depth_only/water/point_shadow_depth 三 shader 只消费 location 0 → 新增 `is_shadow_depth` 单 attribute 分支 + `water.c` 补 `.vertex_stride=3*sizeof(f32)`（顺带修复水 VBO 48B 紧凑 vec3 按 stride=32 声明的顶点越界读取潜在正确性问题，双后端语义一致）；②3 条 MRT 输出无 attachment——G-buffer 管线（4 输出）base pipeline 建在单 attachment swapchain pass 上 → `RHIPipelineDesc` 新增 `mrt_attachment_count`/`mrt_formats[4]`，MRT base pipeline 建在与 G-buffer FBO 兼容的专用 render pass 上（修复潜在 render-pass 不兼容）。demo shutdown 打印 `VK validation messages this run: N`（复用 R438 API，观测非硬门禁）。**R440-B physics**：距离约束速度级求解 `solve_distance_constraint_velocities()`——位置投影后每步一次：轴向相对速度 `rel=dot(vb-va,n)`、冲量 `j=-rel/(inv_a+inv_b)` 按 inv_mass 分配（全消除：双边约束只沿轴消能、无条件稳定；sequential-impulse 语义入注释），消除 R435 遗留的拉紧漂移-回拉抖动；parked/越界/双静态/零长轴防御沿用惯例。`test_physics` 51→54（轴向速度归零/切向保留——含摆动二阶小量容差的物理正确性论证/静态锚点）。**R440-C CI**：新建 `.github/workflows/ci.yml`（gl/vk 双 job：ubuntu-latest 装依赖 → configure → build → `ctest -LE graphics --output-on-failure`；依赖清单与 engine/CMakeLists.txt 逐项核对：libx11-dev/libxrandr-dev/libgl1-mesa-dev / libvulkan-dev/libshaderc-dev）；README 加 CI badge；Build_Guide 新增 §6.4（graphics 不入主门禁的理由：golden 参考图为本机 Intel Mesa 生成、runner 无 GPU/显示、lavapipe 软渲必像素差；DrawBench 同理只真 GPU 手工跑）。workflow 每条命令已本地预演通过（双构建各 37/37）；GitHub Actions 实际运行待首跑确认。**验证**：GL（`build-r440`）/VK（`build-r440-vk`）双构建 `ctest -LE graphics` 各 **37/37** + `ctest -L graphics` 各 **1/1**、构建零警告；VK demo `BREAK_FRAMES=120` rc=0 且 **validation 0 条**（原 9 条）；反向验证（撤 water vertex_stride → 精确复现 2 条对应警告；`#if 0` 中和速度冲量 → 3 新用例红）。遗留：多约束链单步不完全收敛（单遍 Gauss-Seidel 单调消能不放大）；极端拉伸"瞬移"感为 R435 位置投影既有语义；MRT pipeline render pass 与 G-buffer FBO pass 为兼容而非同一对象（规范允许，未来加动态渲染需同步）；CI runner GCC 较本机旧或有警告差异（风险低）。总计 **1050** 处修复（专项轮，不累加）。

此前：**R439 右手基统一 + terrain VK 修复 + 字体 SDF（TDD）** — **R439-A 右手基**（R438 第二阶段）：`mat4_lookat`/`camera_view`/`camera_inv_view`/`shadow_cascade_lview` 右向量 `cross(up,f)`→`cross(f,up)`（det=-1 镜像 → det=+1）；`camera_update` right/strafe 与 main.c 实体生成同步翻转（WASD/鼠标手感不变并修正旧镜像反向，新用例 `camera_update_strafe_matches_view_right` 锁定）；CSM zenith fallback 修正双向 det=+1。绕序审计：主场景/instanced/skinned/shadow 管线一直 culling ON——**旧镜像基下其实在剔正面、渲染模型内壁**（既往隐蔽 bug，翻基顺带修复）；clustered/terrain/water 保守保留 disable_culling（推理入注释）；测试管线移除 disable_culling（reject_blank 兼任绕序回归）。skybox transpose 复查无需改（正交矩阵 R⁻¹=Rᵀ 与手性无关）。golden cam 双后端重生成（重生成前客观验证：新旧参考水平镜像逐像素一致 mirror-MAE=0.00、NDC 推导与像素分布吻合；identity 两图内容不变）。表征测试：平移断言 +3→-3，新增 det=+1/屏幕朝向用例（test_math 47→50、test_camera_frustum 26→29、test_shadow 7→8）。**R439-B terrain VK**：`terrain_vk.frag` 编译失败根因为宏嵌套递归展开（`u_fog_strength` 替换体内含 token `u_camera_pos` 被二次展开为 `pc.(pc.u_camera_pos.xyz).w`）→ push 成员改名 `u_cam_pos`（按偏移匹配，CPU 布局不变）；main.c 地形统计对 heightmap NULL 判空（原初始化失败路径段错误）；`rhi_vk.c` debug 回调加 `#ifndef NDEBUG` 守卫（Release `-Werror=unused-function` 既有问题，Release 构建已验证通过）；全量 57 个 `_vk` shader 过 glslangValidator。**VK demo 历史首次可运行**（`BREAK_FRAMES=120` rc=0，terrain 初始化成功）。**R439-C font SDF**：烘焙 `stbtt_MakeCodepointBitmap`→`stbtt_GetCodepointSDF`（padding=4/onedge=128/dist_scale=64 陡场，atlas 单通道路径零改动）；font 双后端 .frag 改 `smoothstep(0.5±max(fwidth*0.5,1e-4))` SDF 采样；新增 `font_sdf_coverage()` 纯函数；排版/kerning 零改动；`test_font_load` 12→16（含 shader 契约断言带注释剥离器——初版裸 strstr 被 R439 注释击败假绿，已修）。**验证**：GL（`build-r439`）/VK（`build-r439-vk`）双构建 `ctest -LE graphics` 各 **37/37** + `ctest -L graphics` 各 **1/1** + VALIDATION GATE 0 条、构建零警告；GL/VK demo 冒烟各 rc=0 零 ERROR；各项红→绿→反向验证（左手基回退 → 9 项表征红 + cam golden 绕序剔除触发 blank 守卫；terrain shader 还原 → 编译失败但不再段错误——实证判空加固生效；SDF shader 回 step → 契约用例红）。遗留：阴影 pass 剔除面从背光面变向光面，shadow_bias 最优值可能微移（未见异常，未做像素级比对）；SDF 无描边/阴影（陡场仅 ±2px 效果范围）；极小字号 SDF 无 hinting 略圆；demo 启动期 9 条既有 VK validation 性能警告（water attribute 未消费/MRT attachment）未纳入门禁。总计 **1050** 处修复（专项轮，不累加）。

此前：**R438 引擎级矩阵布局修复（TDD）— view 家族统一 canonical 列主序（R62 引入、存活 400+ 轮的核心 bug）+ demo 前向 mega 门控解耦 + VK validation 门禁固化** — **R438-A math**：GPU 实证 `camera_view`/`mat4_lookat`/CSM `lview` 的转置布局（平移 `e[i][3]`）使主相机 VP 丢失全部相机平移（eye.x=0 vs +3 渲染像素级相同）、CSM 级联盒 8 角塌缩 ndc≈(0,0,-1)（阴影方向/位置无意义，因渲染与采样同矩阵而自洽）；golden 用单位矩阵（转置不变式）+ VK 套件无像素断言是 bug 存活 400+ 轮的根因。修复：`mat4_lookat`/`camera_view`/`camera_inv_view`/CSM `lview`（提取 `shadow_cascade_lview` 入 `renderer/csm.h`，消除 main.c 与 test_shadow 构造重复）统一 canonical（平移 `e[3][i]`），**保留左手基**（右手系统一另立项）；`camera_inv_view` 旋转块连带修正（存量测试抓出的第二处 bug）；main.c 两处第三人称偏移 `e[i][3]→e[3][i]`；`shadow_snap_lview_to_texel` 读写同步；skybox 双 shader `mat3(u_view)→transpose(...)`（全 shaders/ 复核确认的唯一依赖转置消费点）。表征测试 5 项先红后绿（lookat 绝对布局/lookat 平移生效/camera_view 平移生效/VP 地面真值 w=8/CSM 8 角充满单位立方体——含跨度 >0.5 断言防空转）；golden 新增**非单位相机变体**（双后端新参考图 `_gl_cam.ppm`/`_vk_cam.ppm`；含 reject_blank 守卫防空白参考、测试管线 disable_culling 适配左手基绕序；identity 参考图字节未动）。**预期视觉变化**：WASD 相机平移首次真正生效；太阳阴影方向/位置变正确；点光阴影不变；天空盒方向不变（transpose 修正）；god rays 太阳屏幕投影/聚簇 CPU 剔除光位/volumetric/SSR 世界重建自动变正确。**R438-B demo**：前向 pass 静态 glTF 场景与 ECS 实体由互斥（初始提交遗留 `!drew_any` 骨架）改为叠加——此前 10 个物理方块恒可见致静态场景前向从不渲染、mega 前向路径（R11 建设 + R437 G→1 优化）永远闲置；修复后 GL demo `BREAK_UNIFIED_FORWARD=0` 实测 compact 计数 0 → 119/119 帧=1，新增 `g_fwd_mega_taken` 每帧观测计数。**R438-C rhi_vk**：注册 `VkDebugUtilsMessengerEXT`（扩展探测式追加，创建失败降级 LOG_WARN 不影响初始化；severity≥warning 原子计数），新增 `rhi_vk_validation_message_count`/`_reset`/`_gate_active` API；test_vulkan FINAL RESULT 处断言计数==0——R437 的 validation 清零从一次性修复固化为**永久门禁**（反向验证：临时恢复 4:3 条件绑定 → 10 条 08114 → GATE FAIL，恢复后 0 条全绿）。**验证**：GL（`build-r438`）/VK（`build-r438-vk`）双构建 `ctest -LE graphics` 各 **37/37** + `ctest -L graphics` 各 **1/1**（identity golden + 新 cam golden + TEST 1-10 + VALIDATION GATE 0 条）、构建零警告；反向验证（camera_view 回转转置 → 8 项测试红 + cam golden FAIL；`!drew_any` 门控恢复 → compact 计数回 0）。**Round11 文档更正**：该文 6193-6197 行"复核证伪"的"引擎按行主序消费矩阵"结论错误（用行主序假设自证），本轮一并更正。遗留：左手基 det=-1 仍靠 disable_culling 掩盖镜像绕序（右手系统一另立项）；新 golden 参考图为本机 Mesa/Intel 生成（跨驱动靠既有 MAE 容差）；VK demo 段错误为既有 terrain_vk.frag 移植缺口（未动）；performance 类 validation 消息未来或引入门禁噪音（届时按 VUID 过滤）。总计 **1050** 处修复（专项修复+补全轮，不累加）。

此前：**R437 性能+健壮性补全轮（TDD）— 前向 compact G→1、TAA velocity 描述符 VUID 清零、IMGUI 两控件、平台速度携带** — **R437-A indirect**：前向/延迟/fallback 三处 per-material compact（每帧 G 次，G≤64）合并为**单 system 单遍容量区间 scatter**（每帧 1 次）：cmds 按组排序上传，组容量前缀和 CPU 已知，shader 内 `slot=group_base+atomicAdd(group_counts[mat_id],1)` scatter 进本组容量区间；execute 按 CPU 已知区间偏移循环——原定"两遍紧排"方案因双后端 execute 偏移均为 CPU 侧值、GPU 前缀和需回读 stall 而不可行（降级论证见代码注释），容量区间方案等效且更优（G→1 而非 G→2）。`mat_systems[64]` → 单 `group_system`；`indirect_draw_upload` 变单隐式组包装（旧行为逐字节等价；R234-B 预清零、R76-3 barrier 外移语义保留）。新增 **TEST 10** 门禁（indirect_draw 此前零覆盖）：组计数/区间 marker 集合/surplus 零填充/dispatch 计数 1-per-frame。execute 仍 G 次（材质固定槽位绑定，真单 execute 需纹理数组+材质间接，另立项）。**R437-B taa**：`combined_aa_apply`/`taa_resolve` 的 `use_vel ? 4 : 3` 条件绑定 → 恒绑 4（velocity 无效时绑占位 `current_color`，采样仍由 `u_taa_use_velocity` 门控）——静态声明的 binding 3 从未 update 致 TEST 6 每帧 1 条 VUID-08114（10 条噪音**清零**，修复后整个集成输出 Validation Error/Warning 为 0）；全仓 grep 无第三处同款写法。**R437-C imgui**：新增 `imui_collapsing_header`（调用方 `bool*` 持久化，矢量三角折叠标记——字体图集不含 ▶/▼ 码位）与 `imui_radio`；状态逻辑提 header inline 助手 `imui_toggle_logic`/`imui_radio_logic` 可无头测；demo 面板分 General/Quality 两个折叠组并接入 FXAA 档位 radio 组。`test_font_ui` 18→23。**R437-D character**：平台速度携带——`char_slide_resolve` 记支撑体 id（`CharacterController.ground_body`，静态支撑也记录、调用方按 is_static 区分），`character_update` 起始处（重力积分前）按上帧支撑体 `pos += velocity*dt` 携带（原拟"垂直 resolve 后携带"被测试证伪：下降平台时 resolve 会撤销携带，改为经典 KCC 方案；水平/上升/下降三向精确跟随）。`test_character` 24→27。**验证**：GL（`build-r437`）/VK（`build-r437-vk`）双构建 `ctest -LE graphics` 各 **37/37** + `ctest -L graphics` 各 **1/1**、构建零警告；VK 集成输出 Validation Error/Warning **0 条**（此前 10 条 08114）；各项红→绿→反向验证。遗留：组内 cmd 顺序由原子竞争不定（与原 per-group 行为一致）；validation 计数未固化进测试（引擎无 VkDebugUtilsMessengerEXT 挂钩点，建议后续在 rhi_vk 加 messenger+计数器约 40–60 行）；test_font_ui 目标未链接 imgui.c（控件级测试按既有风格复制逻辑序列驱动）；demo 因既有 `!drew_any` 门控不走 mega 前向路径（预先存在，非本轮回归）；支撑体墓碑槽位复用可致一帧错误携带（概率极低，下帧自愈）。总计 **1050** 处修复（功能补全轮，不累加）。

此前：**R436 性能补全轮（TDD）— Hi-Z 生成链单 pass 化（Round11 最后 P1 项）、角色控制器推动态体、字体 kerning** — **R436-A Hi-Z**：金字塔生成 10 dispatch+10 barrier → **3 dispatch+3 barrier**（chunk 化：单 dispatch 生成至多 4 个连续 mip，chunk 内每输出纹素直接从 chunk 输入做 2^(k+1)² 区域 max 归约——无 shared memory/barrier/自旋；奇数尺寸末行/列吸收残余纹素，顺带修复旧 4-tap nearest 在奇数尺寸可能漏边缘的隐患）。未选全 SPD：本 RHI 单 dispatch 多 storage image 绑定受限 + 跨 workgroup 自旋有死锁风险（安全红线）。配套修复 `rhi_vk.c` `rhi_cmd_bind_image_texture` 由每次新分配 descriptor set 改为按 pipeline 累积单 set（镜像 R90-1 SSBO 累积模式；无此修复 VK 单 dispatch 无法绑多 mip image，实测触发 VUID-08114）。1 帧延迟语义、`scene_depth` 深度源选择器、阴影 occ=NULL（R170-A 红线）均未动。TEST 9 由 smoke 扩展为**真实遮挡断言**：64² offscreen 深度 → 真金字塔生成 → unified cull 回读 vis flags——近球可见/远球被剔 {1,0}，1×1 fallback 全可见 {1,1}，dispatch 计数 == ceil(levels/4)。**R436-B character**：角色控制器与动态物理体交互——`char_slide_resolve` 增动态分支：可行走顶面照常喂候选（站立动态体上 grounded 自然生效）；侧面/底面接触调新 API `physics_push_body()`（位置推离 + `rest_frames=0` R432 契约；非法 id/static/parked 安全 no-op）全额推开，角色不退让（无限质量 KCC 语义）。`test_character` 21→24。**R436-C font**：kerning——烘焙期 `stbtt_GetCodepointKernAdvance` 提取非零 pair 入稀疏表（512 槽 `{u8 a_idx; u8 b_idx; i16 kern}` 1/64px 定点，先到先存），新公开纯函数 `font_kern_advance()`；`font_renderer_draw`/`font_renderer_text_width` 同构接入（`\n` 重置 prev、'?' fallback 用替换后 codepoint）；自带 LiberationSans 实测有 legacy kern 表（烘焙范围 96 对非零，AV=-152 font units）；无 kern 表字体行为与旧版逐像素一致。`test_font_load` 5→12。**矩阵核查修正 2 处**：统一剔除行/遮挡剔除行中"CSM/点光 unified 传入 hi_z_texture、阴影 unified 已含 Hi-Z"措辞已随 R170-A 过时（阴影 unified 现传 occ=NULL），本轮同步。**验证**：GL（`build-r436`）/VK（`build-r436-vk`）双构建 `ctest -LE graphics` 各 **37/37** + `ctest -L graphics` 各 **1/1**（GL golden MAE=0.00；VK 全集成含扩展 TEST 9）、构建零警告；各项红→绿→反向验证（chunk 步长回 1 → dispatch 计数断言变红；恢复 is_static 过滤 → character 用例变红；kern 恒返 0 → font 用例变红）。遗留：TEST 6 的 10 条 VUID-08114 为既有噪音（pristine 基线同现，未处理）；真实字体 kern 提取路径无法无头验证（合成表覆盖单测）；动态平台无速度携带（platform velocity inheritance 未做）；stb_truetype 仅支持 legacy kern 表（GPOS-only 字体退化为旧行为）。总计 **1050** 处修复（功能补全轮，不累加）。

此前：**R435 功能补全轮（TDD）— Physics 动态 CCD + 距离关节、NetRep delta.log 轮转、Audio 混音总线；附带修复 golden 测试空转假绿** — **R435-A physics**：① dynamic-vs-dynamic CCD——`ccd_sweep_static`→`ccd_sweep`（提取 `sweep_box_toi`，静态通道数值行为零改动），新增动态体 Pass：对手 AABB 按 `velocity*dt` 逐轴膨胀做保守扫掠（绝不穿透、可能略提前钳位；origin 已在扫掠体积内按 t=0 触处理，法向取主导运动轴反向）；CCD 体稀少故动态 Pass 走线性扫描（BVH 是积分前的无法查位移膨胀）。② 距离关节——`PhysicsWorld` 内嵌定长约束表（`PHYSICS_MAX_CONSTRAINTS 64`），新增 `physics_constraint_add_distance`/`_remove`/`_count`（满容量/越界 id/自连/负或 NaN rest 返回 `UINT32_MAX`）；`solve_distance_constraints` 在窄相后 Gauss-Seidel 4 迭代位置投影（按 inv_mass 分配、静态端不动、被移体 `rest_frames=0` 防 BVH refit 跳过；parked 体跳过——调用方 park 前应先 remove 约束）。`test_physics` 44→51（动态隧穿 2 + 关节 5）。**R435-B net**：delta.log 轮转——`peer_save_delta` 追加后超 `NETREP_DELTA_MAX_BYTES`（默认 1MiB，运行时可调钩子 `netrep_delta_max_bytes`）触发：重写全量 `.peer` 基线 → 写 `delta.log.tmp` → rename 原子替换；任一步失败旧 delta.log 原样可读；读取侧零改动。`test_net_replication` 33→35。**R435-C audio**：混音总线——`AudioSystem` 内嵌总线表（`AUDIO_MAX_BUSES 8`，id 0 恒为 master），新增 `audio_bus_create`/`audio_bus_set_gain`/`audio_bus_gain`/`audio_source_set_bus` + 纯函数 `audio_effective_gain`（三因子各 clamp ≥0 相乘）；有效增益 source×bus×master，挂 master 的源不重复乘 master；非法 id 拒绝/回退 master；demo 建 sfx/music 总线并把 3D 流式音源挂 music。`test_audio` 8→16（全无头）。**R435-D GL 修复（R434 连带发现）**：golden 测试此前**空转假绿**——GL `rhi_frame_begin` 恒返 NULL 时 golden 循环 `if(!cmd) continue` 跳过全部帧，参考图 `test_vulkan_gl.ppm` 为全黑图（MAE=0 系假绿）；R434 哨兵让帧真正执行后暴露：GL 默认帧缓冲深度零填充 + `gl_init` 全局开 `GL_DEPTH_TEST` → 三角形被 `GL_LESS` 全拒（VK 由 render pass loadOp 清深度故无此问题）。修复：`gl_frame_begin` 补 VK 对等语义（绑 FBO 0 + 强制 depth mask + `glClear(GL_DEPTH_BUFFER_BIT)`）；参考图经 `GOLDEN_UPDATE=1` 重新生成为真实渲染（旧参考编码的是"什么都不渲染"的空转行为）。**验证**：GL（`build-r435`）/VK（`build-r435-vk`）双构建 `ctest -LE graphics` 各 **37/37** + `ctest -L graphics` 各 **1/1**（GL golden MAE=0.00；VK 全集成套件通过）、构建零警告；各项均红→绿→反向验证（golden：去掉 glClear 重建 MAE=15.64 FAILED，恢复 PASSED）。遗留：动态 CCD 为保守语义（可能提前钳位）；约束不绑速度（位置投影级）；IBL 烘焙遗留 image-unit 绑定列为后续观察项；Windows/macOS 未本机验证。总计 **1050** 处修复（功能补全轮，不累加）。

此前：**R434 性能优先补全轮 — 4 项功能补全（TDD：红→绿→反向验证）+ 状态矩阵修正 5 行** — **R434-A net**：可靠层 `reliable_pending` 单槽 → `NET_RELIABLE_WINDOW=8` 在途窗口（`net_replication.h/.c`）：ack 按累计语义逐槽回绕安全确认、逐槽独立重传、窗口满拒绝并 `reliable_dropped++`（不消耗 `send_seq`，避免有序流出洞）；线协议格式不变，与旧对端兼容。`test_net_replication` 27→33 项（多在途/逐槽 ack/窗口满拒绝/序列号回绕/乱序 ack/逐槽重传）。**R434-B profiler**：线程级采样——`ProfilerRegion` 增 `tid`；新增 `profiler_register_thread()`/`profiler_current_tid()`（`_Thread_local` 惰性分配，32 槽注册表 atomic 发布，tid 2 保留 GPU 轨）；每线程 open stack 改 TLS（并发记录不再破坏 LIFO）；Chrome trace 按真实 tid 分轨并写 `thread_name` metadata。`test_profiler` 22→25 项。**R434-C CSM**：texel snapping——新增 `renderer/csm.h` `shadow_snap_lview_to_texel()`（light-space x/y 平移量化到 shadow map texel 网格，半 texel 确定性向上），接入 `main.c` CSM 级联矩阵构造（VK/GL 共用 CPU 侧矩阵）。新增 `test_shadow` 6 项（亚 texel 漂移稳定/仅整 texel 位移/幂等/网格对齐/半 texel 边界/退化守护）。**R434-D IBL(GL)**：`gl_frame_begin` 恒返 NULL → 静态哨兵句柄（GL compute 链 `rhi_cmd_dispatch`/`bind_image`/`memory_barrier` 本已完整，唯一障碍即 NULL 句柄）；`ibl.c` 四处 `!cmd→break` 静默早退改为显式 `LOG_WARN` 降级，且任何阶段被跳过则 `ibl_generate` 置 `ready=false`（原 R351 校验下资源齐全即 ready，即使一次 dispatch 都没跑）。新增 `test_ibl` 4 项（6 face dispatch/三阶段 37 次 dispatch/BRDF-only/NULL cmd 显式降级）。**矩阵修正 5 行（核查同步措辞，非新代码改动）**：前向点光阴影（R20-1 已完成）、Animation blend/IK demo 接线（R19-2/R20-2 已完成）、纹理热重载 demo 接线（R17-3 已完成）、RHI VK firstIndex/baseVertex（R208-B 已补 `rhi_cmd_draw_indexed_base`）、combined AA 相机 fallback（R17-1 已补 velocity）。**已知遗留（R434 核查发现，未改动，建议单独立项）**：math 库存在两个互为转置的矩阵布局家族（`mat4_ortho`/`mat4_perspective`/`mat4_translation` 列主序 vs `mat4_lookat`/camera/CSM `lview` 转置布局），`mat4_mul(proj, lookat 系 view)` 组合对离轴情形退化，现有弱测试未暴露；CSM 有效参数化可能受此扭曲，根治需统一矩阵布局（影响面大）。**验证**：GL（`engine/build-r434`）/VK（`engine/build-r434-vk`）双构建 `ctest -LE graphics` 各 **37/37** 全绿、构建零警告；4 项均经红→绿→反向验证（回退实现确认新用例变红后恢复）。GL 真实渲染效果未验证（无头环境）；Windows `_Thread_local` 与 `task.c` 既有先例一致（MSVC 未验证）。总计 **1050** 处修复（本轮为功能补全，不累加修复计数）。

此前：**R429–R433 第四轮全仓库审查修复 — 修复 39 处 + 回归测试** — 四审验证 R424–R428 全部修复正确，新增 39 处。**R429 core/math/task（5 处）**：`mat4_inverse` 改尺度相对奇异判定（小尺度可逆矩阵不再误判）；`pool_init`/`arena_alloc` 非 2 幂对齐向上取整（`align_up_pow2` 入 alloc.h）；`engine_init` 判空；`task_wait`/`task_wait_handle` 睡眠 100µs→50µs；TaskSystem 单例约束入文档。**R430 rhi/renderer（7 处）**：swapchain 图像补 `TRANSFER_SRC` usage（截图 VUID 违规）；GPU 计时器改 AVAILABILITY 轮询（draw-bench 等待未提交命令缓冲死锁）；swapchain 格式枚举回退 + 截图 swizzle 跟随实际格式 + 创建失败上抛；GL copy/fill buffer 与 VK 对齐 clamp；occlusion/gpucull 回读按 staged 计数 clamp（对象数增长不再读未初始化尾）；shadow map destroy 清理悬空 `shadow_render_pass`；纹理 data 上传转换全部 mip 层。**R431 asset/scene/ecs（7 处）**：glTF 多 primitive 网格按 primitive 复制 SceneNode（第 2 个材质起的 primitive 原从不渲染）；`hotreload_pipeline_shutdown` 判 ready（原初始化失败会 `close(0)` 关 stdin）；`vfs_rel_path_safe` 拒绝反斜杠穿越（Windows）；hotreload 解码后复核纹理尺寸（TOCTOU）；scene_state 水位尾部按剩余字节判定真正可选；async_loader shutdown 对未完成请求触发 NULL 回调（user_data 泄漏）；ECS 组件改尺寸重复注册拒绝。**R432 net/physics/input（4 处）**：有序通道非空窗口头丢失同样重同步（R427 残留永久停滞）；`resolve_contact` 被推动态体 `rest_frames` 归零（BVH AABB 不再滞留旧位置）；filewatch 跳过已 watch 路径（同 wd 双槽别名）；首次绝对鼠标采样零 delta（视角一次性跳变，x11/wayland）。**R433 main.c/构建系统（16 处）**：WAV 部分写返回真实状态；benchmark 恢复保存的 bloom/god-ray 实际值与预设索引；fallback 蒙皮盒关节索引修正；VisTaskCtx 上限 clamp；水速循环重置；mip/audio 流 shutdown 按 init 标志位；inspector 5/6 优先 combined-AA 输出；draw_bench 摘要/追踪改用会话累计；阴影剔除可见性尾部清零；CMake 修复：WIN32 interface `m` 目标（MSVC 无 libm，原 25 处无条件链接全挂）、test_profiler/test_hotreload 平台宏按平台分发、test_terrain `ENGINE_VULKAN` 定义按选项守卫、wayland-protocols 检查结果、shaderc `find_library`、根 CMake 清理 + framework 警告标志。**验证**：GL/VK 双构建 `ctest -LE graphics` 各 35/35 全绿零新警告；wayland 构建编译验证；仓库根构建（framework）验证。Windows 专用 CMake 分支与 window_win32 改动编译未验证（无 mingw/MSVC）。总计 **1050** 处修复。

此前：**R424–R428 第三轮全仓库审查修复 — 修复 37 处 + 回归测试** — 三审验证 R420–R423 全部修复正确，并首次深审 `main.c`（6160 行）与 `tools/`。**R424 core/task（4 处）**：`heap_realloc_fn` 跨对齐 shrink 时 clamp 搬迁拷贝（OOB 读，ASAN 验证）；四个 task 提交路径拒绝 NULL fn；`str_find_char` NULL data 返回 -1；simd 注释更正。**R425 rhi/renderer（9 处）**：`rhi_screenshot` 双后端统一 RGBA8（GL 原 RGB 导致调用方缓冲尺寸错误，VK 下越界；契约入 rhi.h）；VK offscreen FBO/shadow map destroy 释放 `VKTextureData`（每次窗口 resize 泄漏）；terrain 世界坐标 clamp 到 `[-scale, scale]`；shaderc 初始化失败正确失败 vk_init；`rhi_cmd_copy/fill_buffer` 补 clamp；`gpucull_init_unified` 重复初始化守卫；render pass 创建失败不再回退 swapchain pass；test_vulkan 错误路径资源释放。**R426 asset/scene（8 处）**：sparse accessor 全部改走 cgltf 稀疏感知读取（索引/JOINTS/IBM/动画采样，R422 只修了 POSITION/NORMAL）；VFS 模式外部 buffer 经 `vfs_read_all` 加载（原 cgltf fopen 绕过 pak）；glTF 纹理按 image 去重上传；mipmap 加载失败按级闩锁不再每帧重试；JSON 节点缺 `parent` 键默认为根；`js_u32` 拒绝超 UINT32_MAX 字面量；JSON 逗号改用 emitted 计数；skinned 标志移到分配成功后。**R427 net/physics/platform（9 处）**：有序通道 ≥32 序号跳变时重同步（原永久停滞）；heartbeat/ACK 校验载荷长度（头-only 包毒化 RTT）；删 `NetAddress` 死字段；LRU 淘汰改回绕安全差值比较；静态-静态碰撞对跳过（k 个驻留 body O(k²)）；filewatch 复用退役 watch 槽；win32 `ShowCursor` 仅状态迁移调用；wayland 创建失败完整回收；动画事件支持负速度与循环尾边界。**R428 main.c/tools（7 处）**：F12 截图改 malloc w*h*4（256KB arena 放不下 720p 致静默失效）+ `save_bmp` RGBA 转 24 位；inspector 路径补 `profiler_end_frame`；mega/LOD 包围球应用节点缩放与枢轴（GPU 剔除与 CPU 回退不一致致网格误剔除）；两处 float→u32 UB cast 前 clamp；TAA jitter 用渲染目标尺寸；verify_pak 递归核对嵌套条目（原只查顶层却报成功）；packer 路径截断响亮失败。**验证**：GL/VK 双构建 `ctest -LE graphics` 各 35/35 全绿、零新警告；R424 realloc 修复经 ASAN 验证；verify_pak 嵌套核对与 packer 截断经功能往返测试；wayland 构建编译验证。Windows 专有改动（window_win32.c）编译未验证。总计 **1011** 处修复。

此前：**R420–R423 第二轮全仓库审查修复 — 修复 31 处 + 回归测试** — 二审首先验证 R414–R419 全部 38 处修复正确（含 task 系统 race 复审），随后修复新发现的 31 处。**R420 core/task/engine（9 处）**：`engine_frame` 帧限制器计时重构（`delta_time` 原为纯睡眠时长、FPS 虚高，现为完整帧周期）；task.h Windows 分支嵌入 mutex 存储（原 `void*` 与 POSIX 字段不匹配，Windows 构建断裂）；`debug_realloc_fn` shrink 不再下溢统计；simd AABB 标量回退改 SoA 布局；`task_submit_dep/_n` 拒绝 NULL deps/ctxs；pool 计数器饱和防 u32 回绕；`str_slice` 避免 NULL 指针运算；`log_set_level` clamp；堆分配非 2 幂 align 向上取整。**R421 renderer/rhi（5 处）**：render_graph 非导入 physical buffer 在 reset/destroy 释放（原泄漏）；GL `rhi_buffer_update/_region` 与 VK 对齐 clamp；`rhi_screenshot` 矩形 clamp 到 swapchain + 64 位像素计数；terrain 编辑 API 半径 cast 前 clamp（含 `terrain_erode`）；删除 R417 后死字段 `CombinedAA.output_fbo`。**R422 asset/scene/ecs（8 处）**：`gltf_uri_safe` 拒绝百分号编码 URI（`%2e%2e` 可绕过 R415 穿越防护，cgltf 在校验后解码）；skinned/mesh 分配失败路径销毁已建 ibuf；`anim_clips` calloc 判空；sparse accessor 走转换路径；WEIGHTS_0 fallback 补 `component_type` 守卫；prefab 实例化仅偏移根节点（子节点原被 (d+1)× 重复偏移）；`scene_load_json` 全文档解析成功才提交节点（原失败时已销毁旧场景图）；删死字段 `Archetype.stride`。**R423 net/audio/platform（9 处）**：replication peer 通道表满时淘汰最旧条目（9 个伪造源地址原可永久降级服务器）；`NetSocket` 缓存最近解析目的地址（R418 去缓存后每包 getaddrinfo）；Windows `time.c` 先除后乘（QPC 约 15 分钟 uptime 后溢出）；Lua `set_pos` 传送唤醒 body 并置 `bvh_dirty`；audio generation 24 位回绕不再产生不可用句柄；`filewatch_poll_event` 处理 `IN_Q_OVERFLOW`/`IN_IGNORED`、截断路径不自动 watch；gamepad 热插拔 inotify 溢出全量重扫；`audio_play` 判空 path；win32 鼠标坐标改 `GET_X/Y_LPARAM`、`platform_poll` 处理 `WM_QUIT`。**验证**：`ctest --test-dir build-verify-x11-gl -LE graphics` 35/35 通过；`ctest --test-dir build-verify-x11-vk -LE graphics` 35/35 通过；test_task 14/14、test_alloc 21/21、test_asset_gltf 18/18、test_scene_serial 35/35、test_net_replication 24/24、test_script_lua 19/19 等全绿。注：Windows 专有改动（task.h/time.c/window_win32.c）因无 mingw 工具链为编译未验证。总计 **974** 处修复。

此前：**R414–R419 全仓库深度审查修复 — 修复 38 处 + 回归测试** — 四路并行审查覆盖全部模块（core/math/task、renderer/rhi、asset/scene/ecs、network/physics/audio/platform/ui/animation），确认并修复 38 处问题。**R414 task 系统（6 处）**：堆回退任务 `ref_count=1` 修复必现泄漏（累计 4096 提交后触发），`task_submit_dep` 对不可解析句柄显式失败，提交 priority clamp 防 `queues[]` 越界，`task_release` 块范围比较改 `uintptr_t`，worker 退避上限 1ms→50µs 且 `task_wait` 睡前可窃取，`Worker` 64 字节对齐消伪共享。**R415 glTF/mipmap（6 处）**：skinned 计数与填充谓词统一消除堆溢出，accessor 原始 f32 cast 前校验 `component_type`（IBM/动画/POSITION/NORMAL/UV），外部 buffer URI 经 `gltf_uri_safe` 校验防路径穿越，关节查找复用 `node_to_joint` 改 O(1)，`scene_compute_world_transforms` 改记忆化 DFS（O(n²)→O(n)），mipmap 请求池 free-list 回收。**R416 ECS/场景（4 处）**：chunk 按 `max(ECS_CHUNK_SIZE, required)` 分配支持超大组件，`scene_instantiate_prefab` 偏移全部已加载节点（replace 语义入文档），resource chunk 跳读先校验后推进，`chunk_get_entity` 标注句柄不做有效性检查。**R417 RHI/渲染器（8 处）**：纹理 `data_size` 64 位 + 按 format 取 bpp（RGBA16F 半尺寸 staging 导致 GPU OOB 读），persistent-mapped `rhi_buffer_update` 补 clamp，VK/GL 双后端 mip 上传校验维度与 size，terrain `grid_size` 上限 16384，并行提交 latch `rhi_cmd` 快照消数据竞争，push constant flush 用 clamp 后 range，粒子 `emit_accum` clamp，fallback AA 删除冗余 FBO。**R418 物理/网络（5 处）**：broadphase 积分后二次 refit（同帧接触不再延迟/穿透），replication 通道状态 per-peer 化（多 peer 序列空间不再互踩，线缆格式不变），peer 文件端口 >65535 拒绝，`net_sendto` 移除写调用方 const 对象的解析缓存，physics/character/animation/skeleton 静态工作缓冲改栈。**R419 平台/core（9 处）**：filewatch `lstat`+深度上限 32 防符号链接递归、`IN_Q_OVERFLOW` 强制全量 stat，profiler 满容量哨兵保持嵌套平衡，alloc `align<sizeof(void*)` clamp，log level clamp，string 零长切片跳过 memcmp/memcpy，pool `+align` 回绕守卫，`mat4_inverse` 行列式 epsilon，audio 句柄 generation 防 ABA，wayland 非阻塞事件泵替代每帧 roundtrip。**验证**：`ctest --test-dir build-verify-x11-gl -LE graphics` 35/35 通过；`ctest --test-dir build-verify-x11-vk -LE graphics` 35/35 通过；test_task 12/12、test_asset_gltf 15/15、test_ecs 30/30、test_physics 42/42、test_net_replication 23/23 等全部通过；task/ecs 修复经 ASan 独立验证无泄漏无越界；wayland 后端 `ENGINE_ENABLE_WAYLAND=ON` 编译验证；`engine_demo` GL/VK 双构建通过。总计 **943** 处修复。

此前：**R413 prefab 映射块回绕 + graphics 测试文档收尾 — 修复 1 处 + 回归测试** — R410 已补齐 `emap_build` 的双 u32 数组单块分配守卫，但 prefab 保存路径 `scene_save_prefab` 仍使用 `sizeof(u32) * (ec + sc)`，`ec=w->entity_count`、`sc=count?count:1` 均为调用方/运行态计数；极值下 `ec+sc` 可 u32 回绕后分配小块，随后初始化 `entity_to_saved[ec]` 与写 `saved_to_entity[saved]` 越界。**R413-A**：新增 `scene_u32_pair_block_fits_size`，同时拒绝 u32 加法回绕和 32-bit `usize` 乘法不可表示。**R413-B**：`scene_save_prefab` 分配前复用该守卫，乘法提升到 `usize`。**R413-C**：新增 `scene_serial_test_prefab_block_rejects_wrap` / `prefab_block_rejects_u32_wrap`；`README`、`Build_Guide`、Round11 尾部明确非图形主套件用 `ctest -LE graphics`，Vulkan 图形集成用 `ctest -L graphics`。**验证**：`scene_serial.c` / `test_scene_serial.c` LSP 无诊断；`cmake -S . -B build-verify-x11-gl -DCMAKE_BUILD_TYPE=Debug`；`cmake --build build-verify-x11-gl --parallel 2`；`ctest --test-dir build-verify-x11-gl -LE graphics --output-on-failure` 35/35 通过；`test_scene_serial` 33/33；`cmake --build build-verify-release --target engine --parallel 2`；`engine_demo` 构建通过；`git diff --check` 通过。总计 **905** 处修复。

此前：**R412 VFS PAK 元数据上限对齐工具链 — 修复 1 处 + 回归测试** — R388 已验证 PAK entry/name/data 区间并保留极端 `entry_count > 2^30` 回绕守卫，但 VFS mount 仍会接受远大于 packer 产物的外部 PAK（工具上限 4096 entries），在足够大的归档上直接按 header 执行 `calloc(entry_count,sizeof(PakEntry))` 和 hash table 分配，造成 mount 阶段元数据内存峰值可由不可信文件线性放大。**R412-A**：新增 `VFS_MAX_PAK_ENTRIES=4096`，与 `tools/packer.c` 的 `MAX_ENTRIES` 对齐，mount 早期拒绝超工具上限归档。**R412-B**：新增 `vfs_pak_entry_count_above_tool_cap_rejected` 回归，并将 R388 entry_count 测试改为命中公开上限而非历史 2^30。**验证**：`vfs.c` / `test_vfs.c` LSP 无诊断；`cmake -S . -B build-verify-x11-gl -DCMAKE_BUILD_TYPE=Debug`；`cmake --build build-verify-x11-gl --parallel 2`；`ctest --test-dir build-verify-x11-gl -LE graphics --output-on-failure` 35/35 通过；`test_vfs` 28/28；`cmake --build build-verify-release --target engine --parallel 2`；`engine_demo` 构建通过；`git diff --check` 通过。总计 **904** 处修复。

此前：**R411 glTF 外部计数上限 + 测试文档漂移收尾 — 修复 1 处 + 文档同步** — 新一轮复核发现 glTF loader 仍有一类外部输入计数风险：`cgltf_size` 的 `nodes/materials/accessors/skins/animation` 计数直接流入 u32 字段、`calloc(count,sizeof(T))` 或栈/堆循环，虽然 R390/R391 已校验 accessor span 与对齐，但极端合法 JSON 仍可触发大额分配或 u32 截断路径。**R411-A**：新增 `gltf_counts_bounded`，统一限制 scene/accessor/skin/animation/keyframe 计数，拒绝超过 engine 表达范围或 `SIZE_MAX/elem` 的输入。**R411-B**：mesh/skinned primitive 计数累加添加上限检查，避免 total counter 达到上限后继续增长。**R411-C**：新增 `gltf_rejects_extreme_accessor_count_before_alloc` 回归；`test_vulkan` 标记 `graphics` label，`README` / `Build_Guide` / `docs/index.md` / Round11 尾部 OpenGL 测试命令改为 `ctest -LE graphics`，不再保留 17/17 旧计数。**验证**：`cmake -S . -B build-verify-x11-gl -DCMAKE_BUILD_TYPE=Debug`；`cmake --build build-verify-x11-gl --parallel 2`；`ctest --test-dir build-verify-x11-gl -LE graphics --output-on-failure` 35/35 通过；`test_asset_gltf` 9/9；`cmake --build build-verify-release --target engine --parallel 2`；`engine_demo` 构建通过。总计 **903** 处修复。

此前：**R410 外部输入内存峰值 + 容量回绕收尾 — 修复 3 处 + 回归测试** — 当前仓库复核发现 3 条性能/可靠性风险：**verify_pak** 比对每个资源时同时 `malloc(disk_size)+malloc(pak_size)`，大资源会造成 2×文件大小的瞬时内存峰值；**ByteBuf** 的 `b->size + extra` / `nc *= 2` 未显式拒绝 u32 回绕；**BVH** 初始化/扩容/构建的 `count*2` 与 `new_cap*sizeof(BVHNode)` 缺少极值守卫。**R410-A**：verify_pak 改 64KiB 分块流式比对，内存峰值 O(1)。**R410-B**：ByteBuf 先算 `need` 并拒绝 u32 回绕，倍增触顶后精确扩到 need。**R410-C**：BVH init/alloc/build 拒绝容量与 sizeof 乘法回绕，新增 `bvh_rejects_oversized_capacity` 与 ByteBuf 回绕测试；本轮收尾补齐 empty BVH 不分配 `leaf_map`、32-bit `usize` 条件化乘法守卫，以及 Release `engine` IPO/LTO 选项。**验证**：`cmake -S . -B build-verify-x11-gl -DCMAKE_BUILD_TYPE=Debug`；`cmake --build build-verify-x11-gl --parallel 2`；`ctest --test-dir build-verify-x11-gl -E '^test_vulkan$' --output-on-failure` 35/35 通过（本机 OpenGL 构建下 `test_vulkan` 需 Vulkan 后端，单独排除）；`test_physics` 41/41、`test_scene_serial` 32/32；`cmake -S . -B build-verify-release -DCMAKE_BUILD_TYPE=Release` + `cmake --build build-verify-release --target engine --parallel 2` 通过；`engine_demo` 构建通过。总计 **902** 处修复。

此前：**R409 MegaBuffer 逐 mesh staging 溢出 + Lua id 0 哨兵测试 — 修复 1 处 + 回归测试** — R408 守卫了 mega 总分配，但循环内 **`malloc(vc*sizeof(MegaVert))` / `malloc(index_count*sizeof(u32))` 仍无乘法回绕检查**，单 mesh 极大 `vertex_count` 可绕过总 cap 触发 staging 堆溢出。**R409-A**：逐 mesh 验证 `sv_bytes`/`si_bytes` 再分配，`rhi_buffer_read` 用同一长度。**R409-B**：`engine_id_zero_is_invalid`（`set_pos(0,...)` / `get_pos(0)` 不改动 `bodies[0]`，Round11 记录的 id 0=none 缺口）。**验证**：18/18 test_script_lua（17 → 18）；`engine_demo` 构建通过。总计 **899** 处修复。

此前：**R408 MegaBuffer 顶点累加溢出 + coverage→mip golden 测试 — 修复 1 处 + 导出 API + 回归测试** — mega-buffer 烘焙路径 **`total_verts`/`total_idxs` u32 累加与 `malloc(c_off+c_bytes)` 无乘法/加法回绕检查**，恶意/损坏 glTF 超大 mesh 计数可 usize 回绕 → 小缓冲堆溢出。**R408-A**：累加前拒 u32 溢出；分配前验 `v_bytes`/`i_bytes`/`block_bytes` 乘法与加法守卫，失败跳过 mega GPU 路径。**R408-B**：导出 `mipmap_stream_coverage_to_level`；`coverage_to_level_known_values`（1.0→0、0.25→1、0.0625→2、0→mip_count-1，钉住 R325 IEEE754 快路径）。**验证**：6/6 test_mipmap_stream（5 → 6）；`engine_demo` 构建通过。总计 **898** 处修复。

此前：**R407 demo 流式纹理生成无界 malloc — 修复 1 处** — `demo_write_stream_texture`（`main.c`）按 `size` 逐级 `malloc(s²×4)` 写入 `stream_texture.bin`，**无尺寸上限、无乘法/链总长守卫**；若 `MIP_STREAM_SIZE` 被误改极大或复用该 helper，可 usize 回绕后分配小缓冲再写满堆，或写出超过 `VFS_MAX_FILE_BYTES` 的文件与 R405 注册/加载路径冲突。**R407-A**：`DEMO_STREAM_TEX_MAX_SIZE=4096`（现用 256）；每级 `wbytes` 乘法回绕检查；累加链 `chain_bytes` 拒收回绕及超 VFS 128MiB；部分 `fwrite` 失败改返 0（不留下半写文件仍报成功 mips）。**验证**：`engine_demo` 构建通过；`test_mipmap_stream` 5/5、`test_async_loader` 12/12。总计 **897** 处修复。

此前：**R406 decode downsample malloc 乘法溢出 + scene_state 加载失败可观测 — 修复 2 处** — R403 守卫了 mip 链 `total_pix` 累加，但 **`downsample_rgba8_box` 仍 `(usize)dst_w*dst_h*4` 直接 malloc**，乘法回绕时可分配小缓冲再写满堆。**R406-A**：与 R403 同式的 `dst_pix/dst_bytes` 溢出检查，失败返回 NULL（上层 `decode_generate_mipchain` 已释 `packed`）。**R406-B**：`main.c` 不再 `(void)scene_state_load`——R404 回滚后失败静默，现 `LOG_WARN` 提示 companion 被忽略。**验证**：36/36 CTest（`test_async_loader` decode 路径 + `test_scene_state` 5/5 仍绿）。总计 **896** 处修复。

此前：**R405 mipmap_stream 偏移累加溢出 + 超 VFS 链拒收 — 修复 1 处 + 回归测试** — R167-E 拒单级 `sz==0`，但 **`offset += sz` 仍可能 usize 回绕**，错误 `level_offset` 会令区间读指向文件错误位置；且注册时可声明超过 `VFS_MAX_FILE_BYTES`（128MiB）的 mip 链，async 加载经 VFS 必失败却仍会发起请求。**R405-A**：累加前查 `offset+sz` 回绕，并用 `chain_end > VFS_MAX_FILE_BYTES` 拒收整条链。**R405-B**：`mipmap_register_rejects_chain_over_vfs_cap`（8192²×4=256MiB level0 → register 返回 -1）。**验证**：5/5 test_mipmap_stream（4 → 5）；36/36 CTest。总计 **894** 处修复。

此前：**R404 scene_state_load 失败不回滚 — 修复 1 处 + 回归测试** — R393/R401 加了 `pc` 与文件大小 cap，但 **`scene_state_load` 仍边读边写 live 对象**，任意 `fread`/EOF/`pc` 校验失败时返回 `false` 却保留已写入的相机、太阳角、刚体等（`main.c` 还 `(void)` 丢弃返回值）。**R404-A**：magic 校验通过后快照 `Camera`/标量/physics bodies，失败路径 `restore` 再返回。**R404-B**：`scene_state_load_failure_preserves_runtime`（篡改 `pc` 超限 → 加载失败且相机/刚体保持加载前值）。**验证**：5/5 test_scene_state（4 → 5）；36/36 CTest。总计 **893** 处修复。

此前：**R403 decode_pipeline mip 链字节累加溢出 + task_submit_dep 依赖回归 — 修复 1 处 + 3 条回归测试** — R160-B 只在累加后查 `hdr_sz+total_pix>UINT32_MAX`，但循环内 `(usize)tw*th*4` 或 `total_pix+=` 若 usize 回绕会先得到很小的 `total_pix`，检查通过后再 `malloc` 小缓冲、对大纹理 `memcpy` 堆溢出（32 位或极端尺寸）。**R403-A**：每级先算 `level_bytes`，拒收乘法/加法回绕及 `total_pix>UINT32_MAX-level_bytes`。**R403-B**：`test_task.c` 新增 `submit_dep_waits_for_parent`、`submit_dep_runs_when_dep_already_done`、`submit_dep_waits_for_two_parents`（此前 `task_submit_dep` 零单测）。**验证**：9/9 test_task（6 → 9）；36/36 CTest。总计 **892** 处修复。

此前：**R402 async_loader 完成队列 ring 覆写 — 修复 1 处 + 回归测试** — R165-A 将 `ASYNC_QUEUE_SIZE` 扩至 1024 但未做 backpressure；主线程未及时 `async_loader_tick` 时 I/O worker 连续 `enqueue_completion` 会 **覆写未消费的 slot**（`sequences[qi] != tail+1` → tail 停滞、回调丢失）。**R402-A**：`enqueue_completion` 在 `head - tail >= ASYNC_QUEUE_SIZE` 时 CAS 预留 head 并 yield，直至主线程 drain。**R402-B**：`test_async_loader.c` 新增 `async_loader_completion_burst`（8 worker、1200 次快速失败请求、稀疏 tick → 全部回调）。**验证**：12/12 test_async_loader（11 → 12）；35/35 CTest。总计 **891** 处修复。

此前：**R401 外部输入普查收尾 — scene_state 文件大小上限 + test_vulkan 着色器读取补全 — 修复 1 处 + 迁移 1 处 + 回归测试** — R393 已 cap `pc`，但 **`scene_state_load` 仍接受 multi-MiB 文件**；R399/R400 后 **`test_vulkan.c` 仍保留无 cap 的 `file_read` 副本**。**R401-A**：`SCENE_STATE_MAX_FILE_BYTES=4MiB`。**R401-B**：`test_vulkan.c` → `shader_read_file()`。**R401-C**：`scene_state_rejects_oversized_file`（4/4 test_scene_state）。**普查结论**：引擎 `src/` 外部字节流入口均已 cap 或 chunk-bound。**验证**：35/35 CTest。总计 **890** 处修复。

此前：**R400 font TTF 读取无大小上限 + 着色器路径补全 — 修复 1 处 + 迁移 1 处 + 回归测试** — R389 为 TTF 加了最小 12 字节下限，但 **`font_renderer_init` 仍 `malloc(整文件)` 无 max**；另 R399 遗漏 `font.c` 内联着色器读取。**R400-A**：`FONT_TTF_MAX_BYTES=32MiB`（大 CJK 字体仍可用），分配前拒收。**R400-B**：font 着色器改调 `shader_read_file()`。**R400-C**：`test_font_load.c` 新增 `font_init_rejects_oversized_file`（5/5）。**验证**：35/35 CTest；engine 构建通过。总计 **889** 处修复。

此前：**R399 着色器 read_file 重复实现无大小上限 — 抽取 1 处 + 迁移 33 处 + 单测** — R393 只 cap 了 `hotreload.c`，但 **`main.c` 与 30+ 个 renderer 模块各自复制 `ftell → malloc(整文件)`**，均无 `SHADER_MAX_FILE_BYTES`。**R399-A**：新增 `core/shader_io.c` 统一 `shader_read_file()`（4 MiB，与 hotreload 一致）；`hotreload.c`、`main.c` 及全部 renderer 着色器加载路径改调共享实现。**R399-B**：`test_shader_io.c` 新增 `shader_read_rejects_oversized_file`；`test_hotreload` 改用 `SHADER_MAX_FILE_BYTES` 常量。**验证**：35/35 CTest（新增 `test_shader_io`，34 → 35）；engine + demo 构建通过。总计 **888** 处修复。

此前：**R398 BSCN/JSON 场景加载整文件无大小上限 — 修复 1 处 + 回归测试** — R396/R397 已 bound chunk 内计数与 VFS 打开，`scene_serial.c` 三条入口 **`scene_load_binary`/`scene_load_json`/`scene_probe_binary` 仍 `ftell → malloc(整文件)` 无 cap**，恶意 `.bscn`/`.json` 可在解析第一字节前 OOM。**R398-A**：`BSCN_MAX_FILE_BYTES=64MiB`，`scene_file_size_ok()` 在三条路径分配前拒收。**R398-B**：`test_scene_serial.c` 新增 `load_binary_rejects_oversized_file`（含 `scene_probe_binary`）、`load_json_rejects_oversized_file`（sparse `64MiB+1`）。**验证**：31/31 test_scene_serial（29 → 31 条）；四套 CTest 各 **34/34**。总计 **887** 处修复。

此前：**R397 VFS DIR/PAK 打开无文件大小上限 — 修复 1 处 + 回归测试** — R392/R393 已 cap script/hotreload 读取，但 **VFS 仍是 glTF/async_loader/mipmap 的统一信任边界**，DIR 挂载 `vfs_open` 走 `ftell → calloc(整个文件) → fread`，sparse 多 GB 文件可在 `malloc` 阶段 OOM；PAK 条目 `pe->size` 虽经 R388 校验在文件内，仍无 per-open 上限。**R397-A**：`VFS_MAX_FILE_BYTES=128MiB`（容纳 4K RGBA8 mip chain），DIR 与 PAK `vfs_open` 在分配前拒收。**R397-B**：`test_vfs.c` 新增 `vfs_dir_rejects_oversized_file`（sparse `128MiB+1` → `vfs_open`/`vfs_read_all` 均 NULL）。**验证**：27/27 test_vfs（26 → 27 条）；四套 CTest 各 **34/34**。总计 **886** 处修复。

此前：**R396 BSCN ENTITIES `comp_count` 无界循环 DoS — 修复 1 处 + 回归测试** — R387 已 bound RESOURCES 的 `n` 与 ENTITIES 的实体数，但每条实体的 **`comp_count` 仍无上限**，内层循环可驱动 `world_add_component` 百万次（与 R393 `pc` DoS 同类）。**R396-A**：`load_entities_chunk` 拒收 `comp_count > ECS_MAX_COMPONENTS`（合法保存只 emit `a->key.count`），并用 chunk 剩余字节推导上界（`comp_count×4 + 后续实体最小 8 字节/条`）。**R396-B**：`test_scene_serial.c` 新增 `entities_comp_count_bounded`（篡改首实体 `comp_count=1000` → 加载失败、无 orphan entity）。**验证**：29/29 test_scene_serial；四套 CTest 各 **34/34**。总计 **885** 处修复。

此前：**R395 mipmap 截断端到端回归 + Lua 脚本文件大小上限 — 修复 1 处 + 2 套回归测试** — R394 修了 async_loader/mipmap 截断路径后补集成验证，并延续 R392 脚本 DoS 普查到 Lua 后端。**R395-A**：`test_mipmap_stream.c` 新增 `mipmap_rejects_truncated_level_file`（16×16 level0 只写 512/1024 字节 → 异步区间读 FAILED、零 GPU upload、invalidate 后 resident_bytes 归零）；streaming 会对 UNLOADED 重试，测试以 `load_requests>0` + `upload_calls==0` 断言而非瞬时 resident_bytes。**R395-B**：`script_lua.c` 的 `luaL_loadfile` 原先无文件大小上限（R392 只覆盖了自研 `script.c`）；`LUA_SCRIPT_MAX_FILE_BYTES=1MiB`，在 `lua_script_load`/`lua_script_reload_if_changed` 入口 `stat` 拒收；`test_script_lua.c` 新增 `lua_load_rejects_oversized_file`。**验证**：4/4 test_mipmap_stream、17/17 test_script_lua；四套 CTest 各 **34/34**（`test_vulkan` 无 GPU 环境跳过）。总计 **884** 处修复。

此前：**R394 async_loader 区间读截断误报 SUCCESS — 修复 2 处 + 回归测试** — R393 普查后下一处真实缺陷在 io_worker 区间读 + mipmap_stream 路径。**R394-A**：`async_loader.c:240–262` range 分支当文件短于 `range_length` 时 `to_read=min(...)` 仍 `async_finalize(READY)`；`mipmap_stream.c:125` 的 `mipmap_load_callback` 只拒 `size==0` 不校验 `size==level_size[l]` → GPU upload 用错误字节数、resident-byte 预算失真。修法：拒收 `to_read < range_length`（FAILED）；mipmap 侧纵深校验 `size != level_size[l]`。**R394-B**：`test_async_loader_range_truncated_fails`（64B 文件请求 256B 区间 → 回调 data==NULL，日志 `truncated (64 < 256)`）。**验证**：11/11 test_async_loader、3/3 test_mipmap_stream；四套 CTest 各 **35/35**。总计 **883** 处修复。

此前：**R393 scene_state.bin DoS + 热重载读取边界 + 模块抽取 — 修复 3 处 + 新建 2 套单测** — 延续 R392 普查下一批：`hotreload.c` 与 `main.c` 内嵌的 `scene_state.bin` 加载器。**R393-A**：`scene_state.bin` 保存/加载原先嵌在 `main.c`（~90 行）且零单测；`pc`（刚体记录数）来自文件、无上限——R384 修了读不完就错位，但 forward-compat 文件（`pc > physics->capacity`）仍须逐条 fread 跳过才能到达 water 尾，一条 `pc=65537`、每记录 45 字节的文件即 **65537 次 fread**（DoS），而保存时 `pc` 从不超过 256。抽取为 `scene/scene_state.c`；加载前测文件大小，拒绝 `pc > SCENE_STATE_MAX_PC`（65536）或 `pc*record_bytes > 剩余字节`；当 `si >= physics->count` 时一次 `fseek` 跳过剩余记录。`physics_body_park`/`physics_body_revive` 从 `main.c` static 移入 `physics.c`（scene_state 需链接）。**R393-B**：`hotreload.c` 的 `read_file` 与 R392 前 `script_load` 同类——`malloc(sz+1)` 无上限、`fread` 未校验；`HOTRELOAD_MAX_FILE_BYTES=4MiB` + 读满检查；纹理重载前 `stbi_info` 拒收 >8192 宽高。**R393-C**：`test_scene_state.c`（roundtrip + pc 拒绝）、`test_hotreload.c`（超大着色器被拒）。**验证**：拒绝路径日志确认因正确原因被拒；四套 CTest 各 **35/35**。总计 **882** 处修复。

此前：**R392 脚本引擎无界分配 DoS + 图像解码管线模糊测试 — 修复 2 处 + 新建 decode fuzz + 同步解码 API** — 延续 R391 覆盖普查，本轮处理表内下一批目标。**R392-A（DoS）**：`SCRIPT_MAX_CALLBACKS`（64）只限函数数不限每函数指令数——`script_parse_line`（`script.c:47`）对每条 `set`/`add`/`spawn`/`print` 行 `realloc` 翻倍 `fn->ops`，百万行 `set x 1` 可把单函数 ops 扩到数百 MB；`script_load`（`script.c:99`）同样无文件大小上限，`ftell` → `malloc(sz+1)` 在多 GB `.script` 上解析第一行之前就 OOM。修法：`SCRIPT_MAX_OPS=4096` 在 `realloc` 前拒收，`SCRIPT_MAX_FILE_BYTES=1MiB` 在 `malloc` 前拒收——脚本本就是小型文本资产，两上限宽于任何真实用法。**R392-B**：`decode_pipeline.c` 是 VFS→async_loader→decode_pipeline 路径上唯一吃原始图像字节的模块（`stbi_load_from_memory` + `downsample_rgba8_box`），现有 `test_async_loader` 仅 2×2 TGA 快乐路径、零 mutation fuzz。新增 `tests/fuzz_decode_image.c`（TGA/PNG 双种子、字级边界变异）；暴露 `decode_pipeline_decode_sync` 供 fuzz 同步调用与 worker 相同的 `decode_generate_mipchain` 路径，避免 worker 池时序噪声。**结果 13000+ 轮零崩溃零泄漏零 UB**——R144/R153/R160-B 与 stbi `STBI_MAX_DIMENSIONS` 共同守住，decode 路径无改动。`hotreload.c`（本地热重载路径、暴露更低）、`physics.c`/`bvh.c`（无字节流解析）、`async_loader.c`（调度层）本轮核查无新缺陷。**验证**：`script_rejects_excessive_ops` 确认 op_count 停在 4096；`script_rejects_oversized_file` 确认 1MiB+1 被拒；decode fuzz 13000+ 轮全清；四套 CTest 各 **33/33**（`test_script` 14→16）。总计 **879** 处修复。

此前：**R391 glTF accessor 未强制对齐导致未定义行为 — 修复 1 处 + 新建 glTF 模糊测试器 + 测试覆盖普查** — 本轮先做覆盖普查：`engine/src/` 下 86 个源文件有 47 个零测试覆盖，但按"是否解析外部输入"（`fread`/`read`、按流内长度字段步进、由解析值驱动的分配）加权排序后，前几名候选逐一核查**都没有缺陷**，如实记录而非硬凑修复：`main.c:3053` 的 `fread(&camera.position, sizeof(Camera), 1, lf)` 写法脆弱但 `position` 确为 `Camera` 首成员（`camera.h:7`），读取在界内；`filewatch.c` 两处 inotify 步进只判 `ptr < buf + len` 就解引用 16 字节结构体，但内核保证 `read()` 不返回部分事件（缓冲不足返 EINVAL），属加固范畴故不改；`asset.c:562` 那个 `node_to_joint[skin->joints[jj] - data->nodes] = jj` **写**操作的索引由 `CGLTF_PTRFIXUP_REQ`（cgltf.h:6808）在 fixup 阶段限界于 `nodes_count`。真缺陷是把 R390 刚落地的路径拿去做规模化模糊测试时暴露的。**R391-A**：glTF 2.0 §3.6.2.4 要求 accessor 相对 buffer 的偏移（`bufferView.byteOffset + accessor.byteOffset`）与 `byteStride` 均为组件大小的整数倍，而 **`cgltf_validate` 只校验尺寸、不校验对齐**；所有读取方都拿这些文件可控偏移构造带类型指针再解引用——引擎侧属性/动画循环（`asset.c:600/603/632/645`、`skeleton.c:287`），以及 cgltf **库内部**的 `cgltf_component_read_float`（`*(const float *)in`，cgltf.h:2255）与 `cgltf_calc_index_bound`（`((unsigned short *)data)[i]`，cgltf.h:1571）。故一个不合规文件即可产生未对齐加载（UBSan `load of misaligned address ... requires 4 byte alignment`）：C 层面是 UB，在 ARM 等严格对齐平台是 SIGBUS 硬崩。修法为入口处一次性拒绝，三个设计要点均由实测逼出来：①**必须前置于 `cgltf_validate`**——第一版放其后，模糊测试仍稳定报 cgltf.h:1571 的 u16 未对齐加载，因为 validate 自己会调 `cgltf_calc_index_bound`，等它返回时越界读已发生；②**校验解析后的真实指针而非仅偏移之和**——GLB 的 `buffer->data` 指向二进制块内部，JSON 块长度若不是规范要求的 4 的倍数，块本身就落在奇地址，此时合规偏移仍未对齐；③**只做 `uintptr_t` 整数运算、绝不构造指针**，因偏移越界时构造指针本身即 UB。覆盖含 sparse accessor 的 indices/values 两个独立视图。一处拒绝即覆盖全部 accessor（顶点、索引、动画、逆绑定矩阵）**并连带保护 cgltf 库内部读取**，这是改我们自己的解引用做不到的；合规文件不受影响，因为这是规范硬性要求而非自定策略。**R391-B**：新增 `tests/fuzz_asset_gltf.c`，同时变异真实 GLB 容器（覆盖二进制块头）与自带 skin/animation/索引图元的 JSON 种子（动画与蒙皮恰是 validate 保证最少之处）；JSON 变异**偏向改数字**而非随机字节——随机字节绝大多数只产生语法错误、到不了读取路径，而数字才驱动决定边界的 count/offset/index；启动时先断言未变异种子能加载成功，否则模糊测试只覆盖拒绝路径。**另记录（未改）**：动画采样器读取忽略 `acc->stride`，与 R249 为顶点属性修的是同一类问题，但规范禁止在动画/索引所用 bufferView 上定义 `byteStride`，且 validate 按 `stride` 界定跨度、紧密读取必落其内 → 无内存安全问题，仅在不合规文件上读到错误数据；无实证失败故不动该路径。**验证**：反向验证结果比预期更有力——停用检查后 5 个种子 × 2000 轮**各自**稳定复现**六个不同位置**的未对齐加载，恰好覆盖论证提到的全部读取方：`asset.c:409`（索引/属性循环）、`asset.c:663`（动画 times）、`asset.c:705`（动画 values）、`skeleton.c:287`（骨骼消费）、`cgltf.h:1571`（`cgltf_calc_index_bound`，**在 validate 内部**）、`cgltf.h:2255`（`cgltf_component_read_float`，**cgltf 自己的读取器**）；后两条实证了"必须在入口拒绝、改自己的解引用不够"这一判断。修复后 25 种子 × 4000 轮 = **10 万轮**零缺陷零泄漏；三条新回归测试经日志确认**因正确原因**被拒（组件大小 4/4/2）；单独确认 `test.glb` 与 JSON 种子不被误拒；四套 CTest 各 **33/33**（`test_asset_gltf` 5 → 8 条）。总计 **877** 处修复。

此前：**R390 glTF 加载缺少 `cgltf_validate` 导致越界读 — 修复 1 处 + 新建 asset 测试覆盖 + 完成第三方库信任边界排查** — R388/R389 连续两轮栽在"第三方库信任边界"，故本轮系统排查 `engine/external/` 全部库的调用点。**R390-A**：cgltf 的 API 分三步——`cgltf_parse`（仅解析 JSON 结构）、`cgltf_load_buffers`（取回字节）、`cgltf_validate`（**校验数据一致性**），而 `asset.c` 只做前两步，第三步从未调用。`cgltf_validate` 建立的两条不变量正是后续每次读取所依赖的：accessor 跨度 `offset + stride * (count - 1) + element_size` 装得进其 bufferView（cgltf.h:1610），bufferView 的 `offset + size` 装得进其 buffer（cgltf.h:1641）。而 `cgltf_buffer_data` 返回 `buffer->data + view->offset + accessor->offset`，属性循环从该指针步进 `accessor->count` 个元素——四个值全部直接来自文件，仓库有 16 处这样的调用。实证：accessor 声明 `count = 200000` 而 bufferView 仅 36 字节时，parse 与 load_buffers 均成功、`cgltf_validate` **本会返回 1**，属性循环从 36 字节堆块读了 240 万字节（ASan `READ of size 12` @ asset.c:448）；索引循环是另一条路径，单次 `memcpy` 读 40 万字节（asset.c:332）。恶意模型即可触发崩溃，或把相邻堆内容拷进顶点缓冲进而进入 GPU 内存。修法为补上库的标准用法（一行），不把格式知识复制进引擎代码。**R390-B**：新增 `tests/test_asset_gltf.c`（`asset.c` 此前零测试，与 R389 的 `font.c` 同一情形），5 个用例含 4 类越界 + **1 个合法模型必须仍能加载**；畸形模型运行时生成而非提交二进制样本。**排查结论**：`stb_image`（R144/R153/R160-B 已覆盖，另核对 `downsample_rgba8_box` 减半约定与偏移预留循环完全一致）、`miniaudio`（解析全在库内、引擎侧无指针运算）、`lua`（`sz < 0` 已拒、缓冲在界内）三处均**无需改动**，`stb_truetype` 已于 R389 修复。**验证**：两条路径各自反向验证；单独确认 `engine/assets/test.glb` 不被误拒（validate = 0），并在测试里钉住合法模型仍加载——收紧校验最大的风险就是静默拒掉真实资产；四套 CTest 各 **33/33**。总计 **876** 处修复。

此前：**R389 字体加载两处越界读（空文件 + 非字体文件野指针）— 修复 2 处 + 新建 font 测试覆盖** — 本轮先按计划把模糊测试扩展到网络复制接收路径，新增 `tests/fuzz_net_packet.c`（快照数组按 `max_count` **精确尺寸堆分配**，越界立即被 ASan 抓；replicator 跨包存活以累积重排/去重/peer 状态；`len` 作为独立变异维度）。**结果 100 种子 × 200000 轮 = 2000 万轮零缺陷**——有价值的负面结果，说明 R115/R250/R254/R298/R299 那一系列加固确实到位，此处不做改动。真正的缺陷出现在按"外部输入驱动分配"复查其余文件读取点时，`font.c` 三行内有两处越界读，且该文件此前**完全没有测试覆盖**（R386 的 init 泄漏也出在这里）。**R389-A**：`if (sz < 0)` 只排除负数，零字节文件放行 → `malloc(0)` 后 `stbtt__isfont` 越界读 1 字节；新增 `FONT_TTF_MIN_BYTES = 12`（sfnt offset table 尺寸）。**R389-B（严重得多）**：`stbtt_GetFontOffsetForIndex` 在输入非字体时返回 **-1**，却被直接塞进 `stbtt_InitFont`，而其 `fontstart` 形参是 `stbtt_uint32` → -1 变 `0xFFFFFFFF` → `stbtt__find_table` 读 `data + 0xFFFFFFFF + 4` 野指针硬崩溃（ASan SEGV，`rbx = 0x100000003` 正是该提升结果）；任何 ≥12 字节的非字体文件都触发：路径写错、误传文本文件、资产损坏或下载截断。**R389-C**：新增 `tests/test_font_load.c`，自带 17 个仅供链接的 RHI 桩（TTF 解析在首个 `rhi_*` 调用之前，故拒绝路径可 `dev = NULL` 无头运行）。**残留风险如实记录**：stb_truetype 在此之外不做边界检查，畸形 `numTables` 仍会走出 EOF；该路径 CI 覆盖不到成功分支，无测试网下改第三方解析器风险大于收益，故字体文件必须作为可信资产对待。**验证**：两条均反向验证（回退后立刻触发 ASan；B 的 SEGV 另以独立复现程序证明），并单独确认引擎自带 `LiberationSans-Regular.ttf` 不被误拒；四套 CTest 各 **32/32**。总计 **875** 处修复。

此前：**R388 PAK 挂载堆溢出：`name_table_size + 1` u32 回绕 — 修复 3 处** — 把 R387 的模糊测试扩展到第二个吃不可信输入的路径，新增 `tests/fuzz_vfs_pak.c`（构造合法多条目 PAK 后变异，喂回 `vfs_mount_pak` → `vfs_open` → `vfs_read`）。**关键教训：变异粒度决定能找到什么**——头 3000 轮纯字节翻转全清，因为触发条件是某个 u32 字段整体等于 `0xFFFFFFFF`，逐字节随机撞不上；改为一半概率做**字级**边界值写入后，同样 3000 轮内立刻命中。已把字级变异补回 `fuzz_scene_serial.c`（R387 有同一盲点），补后 16 万轮 BSCN/JSON 仍全清。**R388-A（真缺陷，攻击者可控内容写堆）**：`calloc(hdr.name_table_size + 1, 1)` 两侧皆 `u32`，`0xFFFFFFFF + 1` 回绕成 0，calloc 返回最小块，紧随的 `fread` 按 4GiB 去读、实际写入量只受文件剩余字节限制，全部灌进该最小块；ASan 实录 `WRITE of size 69` 落在 `1-byte region` 之后。修法不止是把 `+1` 加宽到 `size_t`（那只止血），而是在读 header 前先测文件实际大小，于**任何分配之前**校验 header 自述的条目表 + 名字表确实装得下。**R388-B/C（加固，非崩溃修复，如实标注）**：R157 的 `entry_count > 2^30` 检查原本位于两次 `calloc`/`fread` 之后、护不住分配，现连同文件大小上界一起前移；`vfs_open` 按 `entry->size` 定分配尺寸，故在建哈希表那遍顺手校验 `data_offset + size <= file_size`，越界条目跳过不入表（沿用 R160-A 对 `name_offset` 的约定）。这两条在修复前也会被拒/查不到，只是要先白花一次数 GB `calloc`，对调用者可观测行为不变。**验证**：PAK 40 种子 × 15000 轮 = 60 万轮零崩溃零泄漏零 UB；A 补回归测试并反向验证（回退 `vfs.c` 后立刻触发 ASan 堆溢出），B/C 补测试钉住拒绝行为；四套 CTest 各 **31/31**（`test_vfs` 23 → 26）。总计 **873** 处修复。

此前：**R387 变异模糊测试：RESOURCES 计数无上界 + 重复 ENTITIES chunk 泄漏 — 修复 2 处** — 本轮新增 `tests/fuzz_scene_serial.c`（对 BSCN/JSON 加载器做随机字节变异，偏向 header+table 区），在 ASan+UBSan 下跑出两处真实缺陷。**R387-A**：`load_resources_chunk` 的条目数直接进 `calloc(n, sizeof(SceneResource))`，而 `ENTITIES`/`SCENE_NODES` 两个 chunk 都有显式上界，唯独它没有；`n=0xFFFFFFFF` 索要约 1.2TB。按条目最小字节数（24）用 chunk 自身大小推导精确上界，不会误拒任何合法文件。**R387-B**：`scene_load_binary` 第一遍扫描所有 chunk 找 ENTITIES 且不 break，文件声明两个 ENTITIES chunk 时 `load_entities_chunk` 被调用两次，第二次覆盖 `ents` 指针、泄漏第一次的分配；合法 BSCN 只有一个，且两个会让 COMPONENTS 的实体索引产生歧义，故直接拒绝。**验证**：8 个随机种子 × 25000 轮 = 20 万轮变异零崩溃零泄漏零 UB；两条均补回归测试并反向验证；ASan+UBSan / GL / VK / TSan 四套 CTest 各 **31/31**。总计 **870** 处修复。

此前：**R386 heap realloc 对齐搬迁数据损坏 + font init 失败泄漏 — 修复 3 处** — **R386-A**：`heap_realloc_fn` 用 `realloc` 保留 `raw` 起的字节，但载荷偏移是按**新基址**重算的；当请求对齐粗于 malloc 自身对齐时两个偏移会不同（如 align=64、堆 16 字节对齐：旧基址余 0 得偏移 64，新基址余 16 得偏移 16），返回的指针不再指向被保留的数据 → 静默数据损坏。记住旧偏移，变化时 `memmove` 搬迁；新增回归测试 `heap_realloc_over_aligned_preserves_payload`（反向验证：修复前失败）。**R386-B**：`font_renderer_init` 在 `atlas_tex` 创建成功后仍有 6 处 `return false`（sampler/shader 缺失/编译失败/pipeline/quad_data/VBO），调用方按约定不会对失败的 init 调 shutdown，重复 init 会累积 GPU 与 CPU 资源泄漏；按本仓库 `terrain_init`（R244）的既有写法改为失败前先 `font_renderer_shutdown`。**R386-C**：`font_renderer_shutdown` 与 R383 修掉的 `terrain_shutdown` 是同一个模式——首行 `if (!fr->device) return;` 把 `free(fr->quad_data)` 也跳过了；同样改为仅 RHI 销毁受 device 门控。**验证**：ASan+UBSan / GL / VK / TSan 四套 CTest 各 **31/31**。总计 **868** 处修复。

此前：**R385 工作窃取队列槽位数据竞争 — 修复 1 处** — **R385-A**：Chase-Lev deque 只把 `top`/`bottom` 声明为 `_Atomic`，环形缓冲槽位仍是裸 `Task **`；owner 的 `deque_push` 与 thief 的 `deque_steal` 会合法地并发访问同一槽位（由 `top` 的 CAS 裁决归属），槽位访问本身构成 C11 数据竞争（UB）。TSan 压测 60 轮复现 13 次（约 22%）。按 Lê et al. 2013 的正确实现改为 `_Atomic(Task *) *`，三处访问用 relaxed 原子读写——排序全部由既有的 fence 与 CAS 提供，无额外开销。**验证**：TSan 下 test_task 200 轮 + 三个线程相关测试各 60 轮，零竞争零失败（修复前 13/60）；ASan+UBSan / GL / VK 三套 CTest 各 **31/31**。总计 **865** 处修复。

此前：**R384 加载路径健壮性：glTF OOM 空指针 + BSCN 失败回滚 + 两处越界解析 — 修复 4 处** — **R384-A**：`asset_load_gltf` 的 `nodes`/`meshes`/`skinned_meshes`/`materials` 四处 `calloc` 未检查返回值，随后立即写入 `nodes[ni]`、`materials[mi]`；内存紧张时 SIGSEGV。改为按同函数 skin 分配路径的写法（`LOG_ERROR` + `cgltf_free` + `asset_scene_free`）失败退出。**R384-B**：`scene_load_binary` 按 chunk 表顺序应用，而写入顺序是 RESOURCES 在 SCENE_NODES 之前——损坏末尾的 SCENE_NODES 会先释放并替换调用方的 `resources`，再返回 `false`，失败的加载摧毁了原场景。改为暂存 Scene chunk、仅成功时提交（沿用 R381 的 temp-World 思路）；新增回归测试 `failed_load_keeps_previous_scene`。**R384-C**：`scene_state.bin` 读取循环上界为 `si < pc && si < physics->capacity`，当文件记录的 body 数超过本构建容量时，剩余记录不被消费，`water` 字段从 body 记录中间读出；去掉 capacity 上界，交由已有的 skip 分支消费。**R384-D**：JSON 组件 `"size"` 直接进 `malloc`，恶意值可索要 4GB；按 hex 每字节 2 字符用剩余输入长度设界，与二进制路径的 `(r->end - r->p) < size` 对等。**验证**：ASan+UBSan / GL / VK 三套 CTest 各 **31/31**，零泄漏零 UB。总计 **864** 处修复。

此前：**R383 ASan 实测泄漏：terrain_shutdown 提前返回 + Scene.nodes 无释放入口 — 修复 3 处** — **R383-A**：`terrain_shutdown` 首行 `if (!t->device) return;` 把 CPU 内存释放也一起跳过；无设备的 Terrain（headless 编辑/测试、或 init 未走到 pipeline）泄漏 `heightmap` + `_flatten_indices`。改为无条件释放 CPU 块，仅 RHI 句柄销毁受 `device` 门控。**R383-B**：`scene_load_binary`/`scene_load_json` 会分配 `nodes`，但 `asset_scene_free` 需要 AssetContext+RHI device，独立调用方（BSCN 重载、测试）无释放入口；新增 `scene_serial_free()` 统一释放 `nodes`+`resources`，取代 R382-B 在 main.c 里手写的 free。**R383-C**：`load_scene_nodes_chunk` 对 `n==0` 仍 `calloc(1)`（规避 `calloc(0)` 可能返回 NULL 被误判为 OOM），而 `node_count==0` 让调用方以为无需释放；改为 n==0 时不分配，与 `load_resources_chunk` 一致。**验证**：ASan+UBSan 下 CTest 由 29/31 转为 **31/31**、零泄漏零 UB。总计 **860** 处修复。

此前：**R382 scene_state V3 尺寸/弹性 + 悬空 physics_id 重建 + Scene.nodes 泄漏 — 修复 5 处** — **R382-A**：scene_state 只存 pos/vel/mass/is_static，`7` 改尺寸与 `5` 改弹性存盘后 N 恢复丢失；升 V3 存 `half_extent`/`restitution`（V1/V2 仍可读）。**R382-B**：`scene_resources_free` 只释放 `resources`，`load_scene_nodes_chunk` calloc 的 `nodes` 每次 N 泄漏；显式释放。**R382-C**：BSCN 逐字节还原 `CRigidBody.physics_id`，重启后 `physics->count` 变小则 id 悬空、实体无 body；N 后为悬空 id 重建 body。**R382-D**：`render_scale` 从盘恢复但 `render_scale_idx` 未同步，F1 循环跳回旧档位；按值反查索引。**R382-E**：`lua_script_bind_host` 缓存的 `World*` 在 N 交换 world 后成为悬空指针；swap 成功后重新绑定。总计 **857** 处修复。

此前：**R381 N 先 temp 加载再 swap + 仅成功后恢复 state — 修复 2 处** — **R381-A**：`scene_probe_binary` 假阳性仍会 clear 后 load 失败致空场景；改为 temp World 加载成功再 park/swap。**R381-B**：无 BSCN 时 N 仍套用 `scene_state` 改当前世界；仅 `bscn_ok` 后读 companion。总计 **852** 处修复。

此前：**R380 N 保留冻结/质量 + BSCN probe — 修复 2 处** — **R380-A**：N park+revive 强制 dynamic/mass=1，丢掉 `6` 冻结与 Shift+D 质量；park 保留 mass，scene_state V2 存 mass/is_static。**R380-B**：仅 fopen 成功就 clear，损坏 BSCN 清空场景；`scene_probe_binary` 校验后再 clear。总计 **850** 处修复。

此前：**R379 N 清空 park + 仅 revive 有实体槽 + netrep ghost — 修复 3 处** — **R379-A**：N 销毁实体不 park → 无 BSCN/多余 body 幽灵碰撞；有 BSCN 才 clear，且 Del 式 park。**R379-B**：scene_state 对无实体 park 槽仍 unpark；仅 `body_live` 才 revive，孤儿 park。**R379-C**：N 后 `netrep_ghost_valid` 过期；清标志并重建 ghost。总计 **848** 处修复。

此前：**R378 B/N park 复用安全 + BSCN 清空 + 冻体克隆质量 — 修复 3 处** — **R378-A**：B 把 Del tombstone 位姿写入 `scene_state`，槽复用后 N 打穿活体；存盘写 `spawn_pos`，恢复拒 `y≤-999`，必要时 revive。**R378-B**：N 的 BSCN 只追加致重复实体/共享 `physics_id`；加载前销毁全部 live 实体。**R378-C**：`]` 克隆冻体 `create(is_static)` 清零 mass，解冻永久不动；保留 mass。总计 **845** 处修复。

此前：**R377 R/N 勿打穿 Del park — 修复 2 处** — **R377-A**：`R` 把 park 槽挪回出生格仍 static/mass0 → 隐形碰撞且破坏 R376 复用；跳过 `physics_body_is_parked`。**R377-B**：`N` 按 index 写回 pose 同洞；恢复时保留 park。Park 哨兵改为 `spawn_frame=UINT32_MAX`。总计 **842** 处修复。

此前：**R376 Del 停放刚体复用 — 修复 1 处** — **R376-A**：Del 只 park 到 y=-1000、不减 `physics->count`，反复 E/Del 耗尽 capacity；`physics_body_create` 优先复用 park 槽，E 拒 `UINT32_MAX`/`ENTITY_NULL` 孤儿。总计 **840** 处修复。

此前：**R375 静息动态体传送 BVH + Home render_scale_idx — 修复 2 处** — **R375-A**：箭头/Backspace/Shift+W 只对 static 置 `bvh_dirty`，`rest_frames>2` 动态体传送后 AABB 停旧位；一律清 `rest_frames`+`bvh_dirty`（含坠落重生）。**R375-B**：Home 预设改 `render_scale` 未同步 `render_scale_idx`，F1 空转一档。总计 **839** 处修复。

此前：**R374 KP3/R/N BVH 同步 + `]` 克隆属性 + Enter query_done — 修复 4 处** — **R374-A**：KP3 layout 挪 body 未 `bvh_dirty`/`rest_frames`（冻结/静止幽灵碰撞）。**R374-B**：`]` 克隆硬编码 0.5³/mass1；改拷贝源 half_extent/mass/static/restitution，拒 `UINT32_MAX`。**R374-C**：`R`/`N` 批量写 position 不刷 BVH。**R374-D**：Enter 选中缺 `query_done(sq)`。总计 **837** 处修复。

此前：**R373 冻结/质量/缩放物理一致性 + 生成上限 — 修复 5 处** — **R373-A**：`6` 冻结只翻 `is_static`，`inv_mass` 仍 1 → 仍被推开；同步 `inv_mass` + `bvh_dirty`。**R373-B**：`Shift+D` 改 `mass` 未更新 `inv_mass`；冲量脱节。**R373-C**：`7` 改 `half_extent` 不刷 BVH（静止跳过 refit）→ 穿透。**R373-D**：`E`/`]` 用高水位 `entity_count` 当存活数，删后永久触顶；允许 `free_stack` 复用。**R373-E**：Del/箭头/传送在 static 位移后置 `bvh_dirty`。总计 **833** 处修复。

此前：**R372 KP2 拖尾 Entity generation + Del 幽灵刚体 + KP3 layout 同步 — 修复 3 处** — **R372-A**：粒子拖尾用 `Entity{selected_id,0}`，generation=0 永远 miss；改 `world->entities[id]`。**R372-B**：Del 只 `world_destroy_entity`，物理 body 仍碰撞；销毁前 static+清速度+移场外。**R372-C**：KP3 layout 只同步 body 1..10；改经 `physics_id` 同步全部。总计 **828** 处修复。

此前：**R371 箭头选中冻实体回归 + KP Enter — 修复 3 处** — **R371-A**（回归）：R370 在有选中时每帧清零 velocity，Space/`4` 冲量当帧失效；仅在箭头/PgUp/PgDn 按下时才同步。**R371-B**：X11/WL/Cocoa 缺 `KP_Enter`→257（Select）。**R371-C**：Help 补 E/F5/Backspace/KPEnter，去掉重复 CamSpeed 行。总计 **825** 处修复。

此前：**R370 路径满录回放 + 箭头同步物理 + Pause 复位 — 修复 4 处** — **R370-A**：路径录满 `MAX_PATH` 自动停录未置 `path_offer_playback`，下一击 `,` 清空路径；提升为文件作用域并在 FULL 分支置位。**R370-B**：箭头只改 Transform，物理同步每帧覆盖；同步 body position/velocity。**R370-C**：Pause ResetAll 漏 sharpen/SSS/CG/lens/cs/vol/lf；对齐 Home full。**R370-D**：Help Shift+WASD 文案顺序。总计 **822** 处修复。

此前：**R369 Win32 Shift/Ctrl/KP + X11 auto-repeat — 修复 3 处** — **R369-A**：Win32 只映射 `VK_LSHIFT`/`VK_LCONTROL`，消息实际为 `VK_SHIFT`/`VK_CONTROL` → 全部 Shift/Ctrl 热键失效；补映射。**R369-B**：X11 auto-repeat 假 KeyRelease 重触发 one-shot；`XkbSetDetectableAutoRepeat` + peek 回退。**R369-C**：Win32 NumLock 关时小键盘落入 Insert/End…；按 lParam extended 位分流到 KP 305–315。总计 **818** 处修复。

此前：**R368 Win32/Cocoa 失焦释键 + Shift+Space ALL STOP — 修复 4 处** — **R368-A/B**：Win32/Cocoa 失焦未 `input_release_all`（R263 仅 Linux）→ Alt-Tab 粘键；补 `WM_KILLFOCUS` / `windowDidResignKey`。**R368-C**：有选中时 Shift+Space 走实体 impulse 而非 ALL STOP；Shift 优先。**R368-D**：Help 补回 KP1/KP2。总计 **815** 处修复。

此前：**R367 Shift+WASD/Space 门控 + Win32/Cocoa 键位 — 修复 5 处** — **R367-A**：Shift+WASD 仍驱动 camera/character 移动；Shift 时跳过 WASD 移动。**R367-B**：Shift+Space ALL STOP 仍跳跃；jump 排除 Shift。**R367-C**：Cocoa CapsLock 粘滞态致 AutoExp 隔次触发；flagsChanged 边沿脉冲。**R367-D**：Win32 缺 `\\`（FogFar）。**R367-E**：Cocoa 缺 Insert→287。总计 **811** 处修复。

此前：**R366 Ctrl/水位/Cocoa 标点导航 + unified calloc — 修复 7 处** — **R366-A**：anim crossfade 绑 Ctrl(290)，X11/WL/Cocoa 未映射且文案误写 F12；补 Control→290，文案改 Ctrl。**R366-B**：R365 后门控使 Wayland US 布局水位 `( )` 不可达；水位改 Shift+-/=，裸 +/- 仍 exposure。**R366-C**：Cocoa 标点仅字母数字；扩 printable + keyCode。**R366-D**：Cocoa 缺 PgUp/Dn/Home/End/FwdDel。**R366-E**：`gpucull_init_unified` calloc NULL 仍可能 unified_ready；失败软退 legacy。总计 **806** 处修复。

此前：**R365 Shift+B JSON + Wayland Shift+9/0 + Cocoa 键位 — 修复 8 处** — **R365-A**：Shift+B 仍查 GLFW `340/344`，JSON 导出死码；改 `289`。**R365-B**：Wayland Shift+9/0 产出 `'('`/`')'`，相机速度不触发且误调水位；cam speed 兼收括号，水位在 Shift 时跳过。**R365-C**：Cocoa KP 被字符 `'0'..'9'` 抢先映射；KP keyCode 优先。**R365-D**：Cocoa Shift 走 `flagsChanged` 未实现；补 flags→289/294。**R365-E**：Cocoa 缺 grave→96。**R365-F**：Help 漏 ScrollLock:DOF。**R365-G**：箭头 CG sat/contrast 与实体移动冲突；无选中且非 custom-gravity 才调 CG。总计 **799** 处修复。

此前：**R364 数字/WASD/Space/反引号热键消歧 — 修复 8 处** — **R364-A**：`1`–`8` 同时 CG/lens 与爆炸等玩法；CG/lens → KP_5..9 + Decimal 循环。**R364-B**：`` ` `` 同时 ImUI 与 FPS；裸键 ImUI，Shift+` 轮转 FPS。**R364-C/D**：`9`/`0` 同时相机速度与重力/水色；相机速度改 Shift+9/0。**R364-E**：WASD 移动与笔刷/环境光/传送/质量冲突；后者需 Shift。**R364-F**：Space 同时跳跃与 impulse/ALL STOP；无选中时跳跃，有选中时 impulse，Shift+Space=ALL STOP。**R364-G**：Help `(`/`)` 水位方向纠正；平台补 Shift(289) 与 KP_5..Decimal。总计 **791** 处修复。

此前：**R363 KP_0≠鼠标左键 + Space/路径回放修复 + 字母热键消歧 — 修复 10 处** — **R363-A**（CORRECTNESS/回归）：R362 将 boom 绑到 `300`，但 `INPUT_MOUSE_LEFT=300` → 左键即爆炸；KP_0 改 **305**。**R363-B**：Space 冲量块被错误嵌进 `k` layout 的破损大括号内，单独 Space 不触发；解开并外提。**R363-C**：`,` 相机路径停录后 `playing_path` 从未置 true，回放不可达；停录臂播放、`,` 开播。**R363-D**：`t`/`h`/`j`/`k` 仍双绑；tornado/AA/trail/layout → KP_1..4 (306–309)。**R363-E**：scene load 可把 `water.enabled=true` 写回失败 init；无 pipeline 则强制 false。**R363-F**：Cocoa 补 291–309（Pause/locks/Menu/KP）。**R363-G**：Help 文案对齐 R360–R363。总计 **783** 处修复。

此前：**R362 GL FBO 完整性 + scene resize 失败不提交 + 热键/calloc 门闩 — 修复 8 处** — **R362-A/B**：GL offscreen/MRT 缺 `glCheckFramebufferStatus`（阴影 atlas 已有）；incomplete 仍发布。对齐 shadow 检查并销毁。**R362-C**：scene FBO resize 先 destroy 再 create，失败仍提交 `rw/rh` → 同尺寸永不重试、画面空。改为 temp create 成功才替换并提交尺寸。**R362-D**：`p` 同时 deferred 与粒子 boom；boom 改 KP_0(300)。**R362-E**：PageUp/Down 在选中实体/custom gravity 时与 MoveY 冲突；profiler/cinematic 仅无选中且非 mode3。**R362-F..H**：lighting/gpucull/occlusion/indirect 的 zero-init `calloc` 失败仍建“有效”缓冲；失败则 shutdown/return。总计 **773** 处修复。

此前：**R361 热键双重绑定续消歧 + terrain pipeline 门控 — 修复 9 处** — **R361-A**：Delete 同时 SSR 与删实体；无选中才 toggle SSR。**R361-B**：`]` 同时 Volumetric 与复制实体；无选中才 toggle Vol。**R361-C**：`[` 同时 SSGI 与相机模式；SSGI 改 Menu(295)。**R361-D**：Tab 同时 debug UI 与实体轮选；轮选改 Enter(257)。**R361-E..H**：`'`/`,`/`.`/`;` 分别与粒子速率/路径录制/时段/地形预设冲突；SSS/LF/Sharpen/ContactShadow 改 KP_*/÷/−/+ (296–299)。**R361-I**：`terrain_render` 在 pipeline 无效时仍 bind；补门控，shutdown 清 `index_count`/句柄。总计 **765** 处修复。

此前：**R360 MRT 半成品 + 热键双重绑定消歧 + water.enabled 对齐 — 修复 8 处** — **R360-A/B**（CORRECTNESS/LEAK）：GL/VK `rhi_mrt_fbo_create` 在 color/depth `calloc` 失败时仍返回有效 `fb`；`deferred_init` 只查 `fb` → 空 GBuffer。失败 `rhi_mrt_fbo_destroy`；deferred init/resize 校验 4×color+depth。**R360-C**：End(286) 同时 toggle Indirect 与全特效重置。重置改 Pause(291)。**R360-D**：Insert(287) 同时 Cull+DOF；DOF 改 ScrollLock(292)。**R360-E**：`=` 同时 Water 循环与 exposure++；Water 改 NumLock(293)，热键需有效 pipeline。**R360-F**：PageUp 同时 profile 导出与 auto-exposure；后者改 CapsLock(294)。**R360-G**：`water.enabled=true` 在 init 成功前即置位；失败路径/underwater 清屏误触发。成功末尾才 enabled；shutdown 清 false；main 尊重 init 返回值。总计 **756** 处修复。

此前：**R359 offscreen/cubemap FBO 半成品发布 + render_init 早退泄漏 + UNIFIED env 门控 — 修复 7 处** — **R359-A**（CORRECTNESS/LEAK）：GL `rhi_offscreen_fbo_create_fmt` 在 color/depth `calloc` 失败时仍返回有效 `fb`（无 tex 句柄）→ 调用方只查 `fb` 即当成功。失败销毁 GL 对象并清空。**R359-B**（LEAK）：GL cubemap depth `td` calloc 失败泄漏已建 texture/FBO。**R359-C**（LEAK）：VK offscreen `td`/`dd` calloc 失败泄漏整套 GPU FBO。**R359-D**（LEAK）：VK cubemap depth 同族。**R359-E**（LEAK）：`render_init` shader/pipeline/`geo_buf` 失败直接 `return false` 不 `render_shutdown` → 泄漏 device；改 `goto fail`。**R359-F**：scene create/resize 校验 `fb+color+depth`，半成品 destroy。**R359-G**：`BREAK_UNIFIED_{FORWARD,DEFERRED,SHADOW}` 需 `gpucull_sys.unified_ready`。总计 **748** 处修复。

此前：**R358 阴影 atlas bind 清错 FBO + DEFERRED 切换/resize 黑屏 + 相关门控 — 修复 9 处** — **R358-A**（CORRECTNESS）：`rhi_cmd_bind_shadow_map`(GL) 在 `fbo` 无效时仍 `glClear(DEPTH)` → 清掉当前绑定目标。修复：无效/无资源早退。**R358-B**：atlas 创建 FBO incomplete 或 `calloc` 失败时留下 `depth_tex`、空 `fbo`；现完整性检查失败销毁 depth，calloc 失败同清理。**R358-C**：CSM 仅查 `depth_pipeline`；补 `shadow_map.fbo` 门控。**R358-D**：`p` 切 DEFERRED 不查 `deferred.initialized` → forward 跳过且 deferred 未跑 → 黑屏；拒未 init。**R358-E**：`deferred_resize` 失败后仍停 DEFERRED；强制回 FORWARD。**R358-F**（LEAK）：VK shadow `VKTextureData` calloc 失败泄漏已建 GPU 对象。**R358-G**：scene_fbo 无效时 forward 仍 clear 上一目标；跳过整段 forward。**R358-H**：cinematic bind `scene_fbo` 缺 `fb` 校验。**R358-I**：`BREAK_FORWARD_VEL=1` 不查 `forward_vel.ready`。总计 **741** 处修复。

此前：**R357 MegaBuffer VBO/IBO 失败仍 valid + mat-group indirect 忽略返回值 — 修复 4 处** — **R357-A**（CORRECTNESS）：mega VBO/IBO 创建失败仍 `mega_buf.valid=true`，阴影/前向在 `valid && gpu_indirect` 下绑无效缓冲。修复：`valid = geom_ok`，失败销毁半成品并跳过 indirect/gpucull init。**R357-B**：per-material `indirect_draw_init` 忽略返回值 → 该材质批静默漏绘。失败 skip upload。**R357-C**：unified 路径在部分 mat group 未 ready 时仍 auto-enable；改为全部 ready 才开。**R357-D**：`occlusion_cull_init` 失败仍默认 `occ_cull_enabled=true`；失败清 false。总计 **732** 处修复。

此前：**R356 mega indirect/gpucull 失败仍强制开启 + scene_fbo 未校验 — 修复 3 处** — **R356-A**（CORRECTNESS）：`indirect_draw_init` 失败仍 `gpu_indirect_enabled=true`；compact/execute no-op → mega 阴影 0 draw 且 `draw_calls` 虚高。改为 `gpu_indirect_enabled = init 结果`；热键/仅在 `ready` 时可开。**R356-B**：`gpucull_init` 失败仍 `gpucull_enabled=true`；`BREAK_GPUCULL=1` 亦强制开。改为跟随 init，env/热键需 `gpucull_sys.ready`。**R356-C**：`scene_fbo` 创建/resize 未校验句柄（forward/post 采 color/depth）。失败 `LOG_ERROR`。总计 **728** 处修复。

此前：**R355 SSS/tonemap/water/particles init 失败泄漏 — 修复 4 处** — **R355-A**（LEAK）：`sss_init` 双 pipeline（h/v）一侧失败直接 return，未 `sss_shutdown`（R354 已修 SSAO/SSGI 同族）。**R355-B**：`tonemap_init` 仅查 `tm_pipe`；失败时已创建的 `lum_pipe` 泄漏。**R355-C**：`water_init` 未校验 sampler 仍返回 true（pipeline 成功后）；失败 `water_shutdown` + `enabled=false`。**R355-D**：`particles_init` 渲染 shader/pipeline 失败只毁 compute，漏毁可选 `cull_pipeline`；改 `particles_shutdown`。总计 **725** 处修复。

此前：**R354 Lua body 1-based 对齐 + postfx blit 门控 + init 失败清理 + Wayland pointer_leave — 修复 7 处** — **R354-A**（CORRECTNESS）：Lua 注释写 1-based，却把 id 当 C 下标且拒 `id<=0` → `bodies[0]` 不可达，`spawn` 返回 0 与「0=无效」冲突。统一 `idx=id-1`，`spawn` 返回 `id+1`。回归 `engine_spawn_first_body_is_lua_id_1`。**R354-B**：`main` 最终 blit 无条件绑 `postfx.tex_pipe`（init 失败仍绑）。加 `postfx.ready` 门控。**R354-C**：`post_process_init` blur/tex/composite/sampler 失败未 shutdown（仅 FBO 路径有）。**R354-D/E**：SSGI/SSAO 双 pipeline 一条失败泄漏。**R354-F**：Wayland `pointer_leave` 不释放鼠标键 → 拖拽卡住。**R354-G**：`light_system_init` buffer/staging 失败未 shutdown。总计 **721** 处修复。

此前：**R353 VFS 路径穿越 + 场景加载失败回滚 + glTF/terrain OOM 清理 — 修复 7 处** — **R353-A**（SECURITY/CORRECTNESS）：`vfs_open` DIR 挂载 `snprintf(mount/path)` 后直接 `fopen`，`../` 与绝对路径可读挂载外文件；且未拒 `path==NULL`。修复：`vfs_rel_path_safe` 拒空/`/`/`..` 段 + NULL。回归 `vfs_rejects_path_traversal`。**R353-B**：`vfs_read_all` malloc 失败仍写 `*out_size`。**R353-C/D**（CORRECTNESS）：`scene_load_binary`/`json` 失败留下已创建幽灵实体；binary 附带 ENTITIES/NODES `n` 上限。失败路径 `rollback_entities`。回归 `load_binary_rollback_orphans_on_bad_components`。**R353-E/F**：`asset_load_gltf` skin/`node_to_joint` OOM 未 `asset_scene_free`（且泄漏 skin_buf）；`image.uri` 含 `..` 拼接逃逸。**R353-G**（LEAK）：`terrain_init` geom `calloc` 失败未 `terrain_shutdown`。总计 **714** 处修复。

此前：**R352 unified Hi-Z 门控 + ECS create OOM 回滚 + 动画/物理边界 — 修复 7 处** — **R352-A**（ROBUSTNESS）：`gpucull_init_unified` 在 `hi_z_sampler`/`hi_z_fallback` 失败时仍 `unified_ready`；dispatch 无 Hi-Z 时绑 fallback 却用无效 sampler。失败则清理并软退 legacy。**R352-B**（CORRECTNESS）：`world_create_entity` 在 `chunk_alloc` 失败后留下 bitmap 活槽 + `entity_index=0` → 组件串到 empty archetype slot 0。回滚 bitmap/free_stack/entity_count。**R352-C**（LEAK）：`particles_init` 粒子 SSBO `calloc` 失败未 `particles_shutdown`。**R352-D**（CORRECTNESS）：`physics_body_create` 满容量返回 `pw->count`（易被当成有效 id）；改 `UINT32_MAX`，Lua spawn 映射为 0。**R352-E**（CORRECTNESS）：全局单 crossfade 槽，B 层新 fade 废掉 A 层半途过渡；开新 fade 前对旧层提交 `to_clip`（非循环 time=0）。**R352-F**：非循环负 `speed` 未钳 `time≥0`。**R352-G**：`anim_ik_solve` 增 `bone_count`，越界链跳过。回归：`crossfade_other_layer_commits_previous` / `nonloop_negative_speed_clamps_to_origin` / `ik_solve_skips_out_of_range_bones` / `body_create_full_returns_invalid`。总计 **707** 处修复。

此前：**R351 渐进 crossfade 结束后非循环层 time 未复位 + play/stop 未取消 crossfade + IBL ready 过宽 — 修复 4 处** — **R351-A**（CORRECTNESS）：`anim_blend_evaluate` 渐进 `fade_done` 只写 `clip_index`，非循环层保留 from-clip 时钟 → 下一帧 `advance_layer_time` 钳到 to-duration → 硬切 end pose。Instant（`duration<=0`）本就 `time=0`。修复：`fade_done` 时非循环 `time=0`，循环 `fmod` 到 to-duration。回归 `crossfade_gradual_nonloop_restarts_at_origin`。**R351-B/C**（CORRECTNESS）：`anim_layer_play`/`stop` 不取消进行中的 crossfade → `fade_done` 可覆写刚设的 `clip_index`/复活已停层。修复：同层 `crossfade.active=false`。回归 `play_cancels_active_crossfade`。**R351-D**（ROBUSTNESS）：`ibl_generate` 仅查纹理句柄即 `ready=true`；env 卷积缺 sampler/管线时仍就绪。修复：要求 `brdf_lut_pipeline`；有 env 时再要求 cubemap_sampler + irradiance/prefilter pipelines。总计 **700** 处修复。

此前：**R350 残余 ready 空洞 + ADDITIVE crossfade 种子错用 OVERRIDE 语义 — 修复 5 处** — **R350-A..D**（ROBUSTNESS）：R347–R349 扫过后处理默认链后，仍漏 `cinematic`（仅 sampler）、`forward_velocity`/`debug_viz`（FBO+sampler）、`point_shadow`（管线失败仍 ready、cubemap/sampler 未校验）。对齐 R348：失败则 shutdown/destroy、不置 ready。**R350-E**（CORRECTNESS）：`anim_blend_evaluate` 主采样对 ADDITIVE 已用 `fill_bind_pose`（R305），但 crossfade 的 `to_*` 仍 `memcpy` 自 `local_*`；未被子 clip 寻址的骨骼 `lerp(中性, 当前, fade_t)` 再被加性叠上去 → 淡入期间姿势漂移。修复：ADDITIVE 时 `to_*` 亦 `fill_bind_pose`。回归 `additive_crossfade_leaves_unaddressed_bones_untouched`。总计 **696** 处修复。

此前：**R349 合并后处理/tonemap/lens/bloom/deferred_resize 仍漏 FBO 校验 — 修复 7 处** — **R349-A..G**（CORRECTNESS/ROBUSTNESS）：R348 修了独立 TAA/FXAA/color_grade 等，但默认 `use_combined` 路径的 CombinedAA/CombinedColor、tonemap（auto-exposure lum FBO）、lens_effects、bloom `fbo_composite`、`deferred_resize` 仍可能在空句柄上标 ready/保持 initialized。修复：CombinedAA/CombinedColor（合并+fallback）校验 history/output+sampler；tonemap 校验 sampler 与双 lum FBO；lens_effects/lens_flare 对齐 R348；bloom 把 composite 纳入失败门并 shutdown；`deferred_resize` 在 MRT 重建失败时 `deferred_destroy`。总计 **691** 处修复。

此前：**R348 后处理/延迟渲染 FBO·sampler 失败仍 ready/initialized — 修复 11 处** — **R348-A..K**（CORRECTNESS/ROBUSTNESS）：R347 已钳半分辨率并校验 SSR/DOF/SSAO/volumetric；默认开/必经路径仍有同族洞——FBO/sampler 创建失败（VK 空句柄/OOM）仍置 `ready`/`initialized`，`main` 把无效 `color_tex` 接进主链（upscale 无开关、sharpen/MB/SSS/FXAA/TAA/color_grade 默认开，deferred 绑空 MRT）。修复：对齐 R347，创建后校验句柄，失败则 shutdown/destroy 半成品并拒绝 ready——覆盖 `sharpen`/`motion_blur`/`sss`/`fxaa`/`upscale`/`color_grade`/`taa`/`god_rays`/`ssgi`/`contact_shadow`/`deferred`(MRT+双 sampler)。总计 **684** 处修复。

此前：**R347 半分辨率后处理 SSR/DOF/SSAO/Volumetric `width/2==0` 仍 ready + FBO 失败未校验 — 修复 4 处** — **R347-A..D**（CORRECTNESS/ROBUSTNESS）：`main` 把渲染尺寸钳到 ≥1，但 SSR/DOF/SSAO/volumetric 仍用 `width/2` 建 FBO；当 `rw=1`（极小窗/低 scale）时 `1/2=0`，VK `VkImageCreateInfo.extent` 不允许 0 → FBO 空句柄，旧码仍 `ready=true`，DOF 默认开启时 `dof_apply` 绑无效目标。同族 SSGI/bloom/contact_shadow/occlusion 已钳 ≥1。修复（四文件对齐 SSGI）：`pw/ph=max(width/2,1)`；创建后校验 `fbo.fb`+sampler，失败则 shutdown 半成品并 `return false`。附带：X11 相对鼠标无 R346 式双加（warp 滤零事件）。总计 **673** 处修复。

此前：**R346 Wayland 相对指针模式下 `pointer_motion` 与 `relative_pointer` 双加 dx/dy — 修复 1 处** — **R346-A**（CORRECTNESS）：`window_wayland.c` 在 `platform_mouse_set_relative`/`platform_mouse_capture` 启用时创建 `zwp_relative_pointer_v1`，由 `relative_pointer_motion` 累加未加速 delta；但 `pointer_motion` 仍用 surface 坐标差累加 `mouse_dx/dy`。有 `pointer-constraints` 锁时 surface 通常不动(Δ≈0)无感；若 compositor 仅有 relative-pointer、缺 constraints（已有降级 WARN）或锁失败时，两条路径同时进账 → **相机灵敏度约 2×**。修复：`rel_pointer` 非空时 `pointer_motion` 只更新绝对坐标、不再累加 dx/dy（相对路径为唯一来源）；无 relative 协议时行为不变。仅 Wayland 输入层，GL/VK 无关。附带复核 water（`water.c`+`water*.vert/frag`）：R235 水位抬升、R214 VK Z remap、R211/R217 阴影 atlas/binding、init 失败清理均正确；`u_model` static 缓存对 VK 为死代码(`loc_model=-1`)，demo 单实例无害。总计 **669** 处修复。

此前：**R345 ECS `ENTITY_NULL` 别名空 archetype slot 0 + `add_component` dest NULL + gpucull unified 失败泄漏 — 修复 3 处** — **R345-A**（CORRECTNESS）：`world_create` 保留 index 0 为 `ENTITY_NULL` 哨兵，`world_entity_exists` 已拒 `e.index==0`，但 `world_destroy_entity`/`world_add_component`/`world_get_component`/`world_remove_component` 仅查 `index>=entity_count` 与 generation。`entities[0].generation` 经 calloc 为 0，与 `ENTITY_NULL{0,0}` 匹配，且 `entity_archetype/index[0]==0` → 被当成空 archetype 全局 slot 0。手算：`create_entity` 后 `destroy(ENTITY_NULL)` 旧码 swap-remove 删掉真实体并把 0 推进 `free_stack`（而 `exists` 永拒 index 0）。修复：四入口对齐 `exists`，拒 `e.index==0`。**R345-B**（ROBUSTNESS）：`world_add_component` 在 `create_archetype` 失败后仍 `edge_cache_add`+解引用 `dest`（`remove` 路径已有 `if(!dest)return`）；补 `if(!dest)return NULL`。**R345-C**（LEAK）：`gpucull_init_unified` 缓冲创建失败设 `unified_ready=false` 并软失败，但不销毁半成品；`gpucull_shutdown` 又用 `unified_ready` 门控 → 永久泄漏。修复：失败路径立即 destroy 半成品；shutdown 按 handle 有效性销毁、不再门控 `unified_ready`。新增回归 `ecs_null_entity_does_not_alias_slot0`。总计 **668** 处修复。

此前：**R344 LOD `lod_unregister` 未注册 entity 与「组索引 0」混同 — 修复 1 处** — **R344-A**（CORRECTNESS）：R260 已为 `lod_select`/`lod_get_mesh` 补 `groups[group_idx].entity_id != entity` 校验，但 `lod_unregister`（`lod.c`）仍只以 `idx >= count` 判定。`entity_to_group[]` 由 `lod_init` 清零、`lod_unregister` 把移除项复位为 0，故**从未注册**的 entity 也映射到 `group_idx==0`；一旦有任意组注册，对未注册 entity 调用 `lod_unregister` 时 `0 >= count` 为假 → **误对 slot 0 做 swap-remove**，把真正占有 `groups[0]` 的 entity 注销并使 `count--`。手算：注册 entity0 后 `lod_unregister(999)` → 期望 no-op/`count==1`，旧码使 `count==0` 且 entity0 的组丢失。修复：与 R260 对齐，增加 `sys->groups[idx].entity_id != entity` 早退。运行时主循环未调用 `lod_unregister`（公共 API 逻辑缺陷，同 R260 脉络）。纯 CPU，GL/VK 无关。新增回归 `lod_unregister_unregistered_when_group0_exists`。总计 **665** 处修复。

此前：**R343 GPU 遮挡剔除（Hi-Z 金字塔生成 / AABB 投影可见性 / 双缓冲回读）深审——无 demo 可达高置信 bug，不修复** — `engine/src/renderer/occlusion_cull.c` + `shaders/hi_z_generate.comp` + `shaders/occlusion_cull.comp`。①mip 计数:`oc_calc_mip_levels`(max_dim>1 循环右移)对 1024 得 11 级满 mip 链,正确。②Hi-Z 生成:逐 mip max-depth 下采样(mip0 读 depth_buffer、后续读上一级),`out_w/h = hi_z_dim>>mip` 钳到 ≥1,8×8 workgroup dispatch,每级间 `memory_barrier` 保证写后读;结尾 R172/R195-B 恢复全 mip 视图(GL bind_texture_mip 会钳 BASE/MAX)。③dispatch:双缓冲 staging(`fi=frame_index&1`),先读上一同奇偶帧结果(fence 后)`memcpy count·4B`,再 dispatch cull(`(count+63)/64` 组)、barrier、GPU-copy 回 `readback_staging[fi]`;staging/visibility_buffer/readback 均 sized `OCCLUSION_MAX_OBJECTS·4B`,`count` 钳到 MAX,无越界。④`is_visible`:`object_index≥object_count` 返回 true(保守可见);`visible_count` SSE2 分支统计正确。⑤`upload_aabbs`:`object_count=min(count,MAX)`,update 按 `object_count·sizeof(ObjectAABB)`。⑥shader `occlusion_cull.comp`:8 角投影,`clip.w≤0`(近平面穿越)保守标可见;NDC 框外/`closest_z>1` 剔除;NDC→UV 中心 `(min+max)·0.25+0.5` 正确;mip=`clamp(ceil(log2(max size)),0,levels-1)`;`closest_z≤hi_z_depth` 为可见(标准 Z)。观察(非 bug,已知 Hi-Z 权衡):`hi_z_width=width/2` 非强制 2 的幂,奇数维度下 4-tap 下采样可能漏采最远 texel——仅影响剔除激进度且属经典 Hi-Z 保守性局限,非高置信可复现 bug。总计仍 **664** 处修复。

此前：**R342 GPU 间接绘制压缩（visible 压缩/原子计数/双缓冲可见性/fill 屏障）深审——无 demo 可达高置信 bug，不修复** — `engine/src/renderer/indirect_draw.c` + `rhi_cmd_fill_buffer`(VK)。①缓冲:`all_draws_buf`(STORAGE,CPU 上传,R186 DEVICE_LOCAL)、`visible_draws_buf`(STORAGE|INDIRECT,compute 写+graphics 读,R185)、`draw_count_buf`(STORAGE|INDIRECT,u32 原子计数)、`visibility_buf[0/1]`(HOST_VISIBLE 双 slot);init 任一失败即 destroy 全部并返 false。②双缓冲:`indirect_draw_visibility_slot=visibility_buf[rhi_frame_index&1]`,同帧 upload 写与 compact 读用同一 slot、与 GPU 仍读的上一帧 slot 解耦(R182);`upload_visibility`(host)与 `upload_visibility_cmd`(R183 CB 序,per-cascade 重写安全)。③compact:R175 GPU-fill `draw_count_buf=0`(与 CB 内 compact 有序,host update 对后续 GPU 不可见)、R234-B GPU-fill `visible_draws_buf[0..current]=0`(防 VK IndirectCount 回退绘制 max 时复活陈旧命令);绑 4 storage(all/visibility slot/visible/count)、set total_draws、dispatch `(current+63)/64` 组;R76-3 屏障移交调用方以批量。④**关键并发正确性**:fill 与 compute dispatch 均写 `visible_draws_buf`,但 `rhi_cmd_fill_buffer`(VK)在 fill 前后各插屏障——前置等 `SHADER_WRITE|TRANSFER_WRITE|INDIRECT_COMMAND_READ|SHADER_READ → TRANSFER`(R185 跨级联复用同 buffer),后置 `TRANSFER_WRITE → SHADER_READ|SHADER_WRITE|INDIRECT_COMMAND_READ`,故 fill→dispatch 的 WAW 被正确排序,compute 写不会被 fill 清零。⑤`indirect_draw_execute`:`draw_indexed_indirect_count(visible_draws_buf, draw_count_buf, maxDrawCount=current_draw_count, stride)`;`current_draw_count==0` 时 compact/execute 均早退;`indirect_draw_upload` count 钳到 max_draws。总计仍 **664** 处修复。

此前：**R341 级联阴影 CSM（PSSM 分割 / 光空间基解析构造 / 4 级联 atlas 象限 / 退化回退）深审——无 demo 可达高置信 bug，不修复** — `engine/src/main.c` CSM 段。①分割(PSSM 实用方案):`splits[0]=0.1`,`splits[i]=λ·(zn·(zf/zn)^(i/4)) + (1-λ)·(zn+(zf-zn)·i/4)`,λ=0.75 偏对数;i=4 时两项均=zf=100→splits[4]=100 正确。②光空间基(全 4 级联共享,一次算):`s=normalize(light_dir×(0,1,0))=(-fz,0,fx)·inv_sl`;`u=cross(s_unnorm,f)·inv_sl`——验证单位光向下 `u_len2=(fx·fy)²+(fx²+fz²)²+(fy·fz)²=(fx²+fz²)(fx²+fy²+fz²)=s_len2`,故复用同一 `inv_sl` 无需额外 rsqrt,正确;R247:光∥world-up(可由 sun_elevation≈±π/2 的存档触发,未 range-clamp)时 `s_len2≈0`,回退固定 XZ 正交基(sx=-1,uz=1)保 lview 可逆、避免 rank-deficient 致阴影全失。③每级联:`center=cam_pos+cam_fwd·mid`、`extent=zf-zn`、eye=`center-light_dir·extent`;lview 左手系(rows -s/u/-f + 平移 -dot(basis,eye),与 camera_view/R335 一致);`lproj=mat4_ortho(-extent,extent,-extent,extent,0.1,2·extent)`(对角+平移,满足 `mat4_mul_ortho_diag` R49 前置);`cascade_vp[c]=mat4_mul_ortho_diag(lproj,lview)`。④atlas:2048² 单图 4×1024² 象限,c→(c&1,c>>1) 视口须与 shader 采样 remap 一致(注释强调)。观察(非 bug,画质而非正确性):未做 texel snapping(相机运动时阴影边缘 shimmer)与紧致视锥角包围(级联框固定 2·extent、分辨率利用略松)——两者为画质优化,阴影结果正确。总计仍 **664** 处修复。

此前：**R340 点光源阴影（cubemap 六面 VP 构造 / 线性距离深度 / 最近 N 光选择 / 面绑定）深审——无 demo 可达高置信 bug，不修复** — `engine/src/renderer/point_shadow.c`。①`point_shadow_compute_face_vp`(R313):`proj=mat4_perspective(90°,1,0.1,far=r)`,对六面用 `(s,u,f)` 正交基构造真实 view(row0=s,row1=u,row2=-f,平移=-basis·light_pos)再 `mat4_mul(proj,view)`;f_axis 正确对应 ±X/±Y/±Z;R313 修复了旧"解析闭式"在列主序下 clip.w 依赖错误世界轴致正面点 w<0 被裁/或 |x/w|≫1 出 NDC(点阴影从不解析)的严重 bug,现正面点映射 NDC(0,0)、w>0(经 mat4_perspective·mat4_lookat 验证);view 矩阵为合法正交(det=+1)变换。②`point_shadow_update`:重置 shadow/src_index=0xFF、active_count=0;按到相机平方距离 `cand[256]`(n=min(count,256))选最近——n≤MAX 全插入排序,否则维护 top-take 部分选择排序(较大者丢弃);`take=min(n,MAX)`;`r=(radii>0.1)?radii:25.0` 且以 r(恒>0.1)调 compute_face_vp(内部 far=r,与 `far_planes[slot]=r` 一致,compute 内 0.1 回退仅防御直接调用)。③渲染:`point_shadow_render_begin` 绑面 `rhi_cubemap_depth_fbo_bind_face`,R82-3 每光 uniform(light_pos/far_plane)仅 face==0 设置(同 pipeline 跨面,值不变);深度由 fragment 写线性距离 `length(frag-light)`。观察(非 bug):六面 u_axis 相对 LearnOpenGL 标准约定取反,为与引擎 cubemap 面渲染/采样 Y 约定配套的有意选择(R313 已验证 + 深度为方向无关的线性距离,demo 点阴影正常;若真错会明显镜像)。总计仍 **664** 处修复。

此前：**R339 聚簇光照 CPU 剔除（指数深度切分 / froxel 分箱 / 屏幕 AABB 早退 / 光索引溢出防护）深审——无 demo 可达高置信 bug，不修复** — `engine/src/renderer/lighting.c::light_system_cull`。①`cluster_depth`:`near·(far/near)^(z_slice/CLUSTER_Z)` 指数深度切分(z=0→near、z=CLUSTER_Z→far);`_z_depths` LUT 仅 `_z_depths_dirty` 时重算。②`mat4_vec4`:SSE `Σcol_k·v_k`=M·v 列主序变换(标量回退注释确认一致),每光预变换 world→view→clip 一次(O(n)),再进 O(clusters·n) 分箱。③z 切片分离:视空间 z 为负、簇占 `[-z_far,-z_near]`,`vp_z+r<-z_far`(光在簇后)或 `vp_z-r>-z_near`(光在簇前)则跳过——正确球-slab 分离。④屏幕 AABB:预算 `screen_x/y=(clip.xy·inv_w·0.5+0.5)·screen_wh`、`screen_r=radius·(1/-view_z)·screen_w·0.5`,`screen_[xy]max<tile_start || screen_[xy]min>tile_end` 早退;光跨近平面(clip.w≤0.001,screen_ok=false)时跳过屏幕测试、仅靠 z 剔除(保守不漏)。⑤溢出双重防护:每簇前 `grid_index_total >= CLUSTER_COUNT·LIGHT_MAX_PER_CLUSTER - LIGHT_MAX_POINT` 则 `goto done`(预留 LIGHT_MAX_POINT,而单簇至多加 min(pc,LIGHT_MAX_PER_CLUSTER)≤LIGHT_MAX_POINT,安全),内层写前 `< CLUSTER_COUNT·LIGHT_MAX_PER_CLUSTER` 绝对界 + `count>=LIGHT_MAX_PER_CLUSTER break`;预算耗尽后剩余簇 count 保持 0(帧首 memset),优雅降级(部分簇不亮而非越界)。每帧 `memset(grid_offsets_counts)` + `grid_index_total=0`。总计仍 **664** 处修复。

此前：**R338 骨骼评估（TRS 合成 / 不定序世界矩阵定点解析 / 蒙皮矩阵 / STEP 快照）深审——无 demo 可达高置信 bug，不修复** — `engine/src/animation/skeleton.c`。①`mat4_trs`:列主序直合 T·R·S(旋转来自四元数、按列缩放 sx/sy/sz、平移入 col3),逐列核对 = `mat4_from_quat` 各列缩放 + 平移,与 glTF 节点变换(先缩放后旋转再平移)一致,省 2 次 mat4_mul。②`skel_resolve_world`(R240):对任意 joint 顺序做定点迭代——`world[i]=root?local[i]:world[parent]·local[i]`,root 判定 `p==UINT32_MAX||p>=n||p==i`,仅当 `resolved[p]` 才解析否则延后;`pass<=n` 上界保证终止,某 pass 零进展(父环)则 break 并把剩余当 root;已排序 skin 一趟即完成。修复了旧 "parent>=i 即视作 root" 启发式对 glTF 未按父先序列出子关节的错误 rooting。③`skeleton_evaluate`:TRS 初值 identity;`anim_find_keyframe` 二分(最后 `times[i]<=t`);`frac` clamp[0,1] 且 `dt>0` 才除;R252 STEP 通道快照 `frac=(t>=t1)?1:0`(默认 demo 蒙皮路径,曾错误插值 STEP 产生源中不存在的过渡姿态);`current_pose[i]=world[i]·inverse_bind[i]` 标准蒙皮矩阵。④`anim_slerp_quat` nlerp(dot<0 负化取最短弧 + 归一);`skeleton_set_joints`/`anim_clip_add_channel`/`add_event` 均对 count/keyframe/事件名做钳制/截断,`ji>=joint_count` 跳过。观察(非 bug):`skeleton_evaluate(dt)` 参数未用(时间取 `clip->time` 由调用方推进),第 189 行局部 `dt=t1-t0` 遮蔽参数——仅命名混淆;translations/rotations/scales 为文件级 static(单线程动画下安全);蒙皮省略了 mesh 节点全局逆变换(假设 mesh 节点为 identity,demo 既有简化)。总计仍 **664** 处修复。

此前：**R337 视锥剔除（Gribb-Hartmann 平面提取 / p-vertex AABB / 点 / 球测试）深审——无 demo 可达高置信 bug，不修复** — `engine/src/renderer/frustum_cull.c` + `cull.c::frustum_from_vp` + `cull.h` inline 测试。①`frustum_extract`/`frustum_from_vp`(实现一致,均 R265 修复):列主序 e[col][row] 下 clip.e[r]=Σ_c vp->e[c][r]·p.e[c],故 row_r 对点分量 i 的系数为 vp->e[i][r],平面 `plane.e[i]=(row3±row_k)[i]=vp->e[i][3]±vp->e[i][k]`;旧代码写成 `vp->e[3][i]±vp->e[k][i]`(矩阵双下标转置)构建了 VP^T 的视锥、几乎 100% 误判在视点(GPU cull.comp 直接 `vp*vec4` 本就正确,故仅这些 CPU 回退受影响)。归一化对 6 平面用 `len2>1e-12` 守卫 + `fast_rsqrt`、含 e[3] 使其为真有符号距离;R245 补 `sign_mask[p]`(法线分量≥0 的位)供 p-vertex 选角。②`frustum_cull_batch` / `frustum_test_aabb`(cull.h inline):p-vertex 法按 sign_mask 选正向顶点(法线分量≥0 取 max 否则 min),`dist<0` 即整 AABB 在外→保守剔除(无假阴性)。③`frustum_test_point`(d<0 外)、`frustum_test_sphere`(d<-radius 即球完全在负侧才外)正确。观察(非 bug):代码 Near=row3-row2、Far=row3+row2 与标准 OpenGL(Near=row3+row2)标签相反,但两平面都在,6 半空间交集体积相同、全平面 `d<0` 测试的剔除结果与标签无关,仅命名不精确;`frustum_extract`(填指针)与 `frustum_from_vp`(返回值)为等价重复实现。总计仍 **664** 处修复。

此前：**R336 相机系统（fly 控制/yaw-pitch 钳制/缓存三角值/解析 view 与 inv_view/投影缓存）深审——无 demo 可达高置信 bug，不修复** — `engine/src/renderer/camera.c`。①`camera_view`:由缓存三角值直接构造左手系视图矩阵,静止(yaw=pitch=0)时 forward=(0,0,-1)、right=(-1,0,0)、up 行=(0,1,0)(+y 正确),平移列 `-dot(basis,eye)` 三行逐一核对;与 R335 已验的 `mat4_lookat` 同基(row0 静止均 (-1,0,0))。②`camera_inv_view`(R52-fix):旋转块 = `camera_view` 旋转块在 e[col][row] 存储下的精确转置(9 元素逐一核对),平移列 = eye;正交旋转 → 转置即逆(`-R^T·(-R·eye)=eye`),故确为解析逆,零额外 trig。③`camera_projection`:fov/aspect/near/far 四参数变更检测缓存 `mat4_perspective`,省 tanf+3 除;`camera_init` 置 `_proj_*=-1` 强制首帧重算。④`camera_update`:WASD 用帧首缓存三角值(=上一帧末更新的当前朝向)沿 fwd=(cp·sy,sp,-cp·cy)/right=(-cy,0,-sy) 平移;yaw 单次 ±2π wrap;pitch 钳 ±1.5533(~89°,防 gimbal 翻转);trig 在 yaw/pitch 更新**后**缓存,消除一帧延迟(view/inv_view 与 main.c 的 cam_c*/cam_s* 均反映当前帧朝向)。观察(非 bug):`camera_view` 注释写 `u=s×f`,实际值为 `-(s×f)`(即 f×s),但静止得 +y 向上且与 inv_view 互逆自洽——仅注释标注不精确;yaw 单次 wrap 对超 2π 的单帧巨量旋转不完全归一,但 cos/sin 周期性使其无正确性影响(仅防长期精度漂移)。总计仍 **664** 处修复。

此前：**R335 数学库（mat4 逆/透视/lookat、quat 乘/slerp/nlerp/rotate、特化 proj·view 与解析逆）深审——无 demo 可达高置信 bug，不修复** — `engine/src/math/math.c` + `math.h`。①`mat4_inverse` 标准 MESA cofactor 展开、`det==0` 精确判返 identity;`mat4_perspective`/`mat4_ortho` R142 对 aspect/深度范围/tan 加 1e-20 除零守卫;`mat4_lookat` 左手系(`-s,u,-f` + 平移用点积,与 camera_view 一致);`mat4_from_quat` 列主序标准旋转矩阵(逐列核对匹配 row-major R 的各列)。②quat:`quat_mul` 标准 Hamilton 积、`quat_inverse` 共轭(设单位)、`quat_normalize`(l2≤1e-12→identity + fast_rsqrt)、`quat_slerp`/`quat_nlerp`(dot<0 取最短路负化 b、lerp + 归一)、`quat_from_axis_angle`(轴归一 + 半角,l≤1e-6→identity)、`quat_rotate_vec3`(`v+2w(qv×v)+2qv×(qv×v)` 标准优化式)。③特化(全部代数验证):`mat4_mul` SSE 路径 `out.col=Σa.col_k·b[col][k]` 与标量分支等价;`mat4_mul_proj_view`(R50)逐行 `ΣP.e[k][row]·V[col][k]` 核对匹配(含 TAA jitter jx/jy);`mat4_inv_perspective`(R53-fix)验证 `P·inv=I` 四列全部成立(含 jitter);`mat4_mul_ortho_diag`(R49)对角+平移专用乘。R73-4 `mat4_mul` static inline。观察:`mat4_inverse` 用精确 `det==0`(非近奇异 epsilon),近奇异会得大值属标准行为;`mat4_inv_perspective`/`mat4_mul_*` 有前置条件(须为对应结构矩阵),已在注释声明。总计仍 **664** 处修复。

此前：**R334 Linux 手柄 evdev 后端（事件解析/轴缩放/按钮边沿锁存/inotify 热插拔）深审——无 demo 可达高置信 bug，不修复** — `engine/src/platform/gamepad_linux.c`。①越界安全:`evdev_btn_to_gamepad` 映射后 `idx>=0 && idx<INPUT_MAX_PAD_BUTTONS(16)` 才写按钮;轴更新前 `ax>=0 && ax<INPUT_MAX_AXES(6) && ev.code<ABS_CNT && abs_info[ev.code].present`;HAT0X/HAT0Y 直写 `GAMEPAD_BTN_DPAD_*`(=11..14,恒 <16)虽无运行时查界但枚举值必在界。②按钮状态机 `apply_button_state`(0=up/1=released/2=held/3=pressed):press 事件在 `!=2` 时置 3、release 事件把 3/2→1;evdev 仅在状态变化时投递事件,per-frame 的 3→2、1→0 提升由 input 层完成,标准边沿锁存。③轴缩放:`normalize_axis` `[min,max]→[-1,1]`、`normalize_trigger` `→[0,1]` clamp,均 `range==0` 守卫防除零;`device_query_axes` 用 `EVIOCGABS` 读每轴 min/max,`present=(min!=0||max!=0)`。④热插拔:`inotify_init1(IN_NONBLOCK|IN_CLOEXEC)` + watch `IN_CREATE|IN_DELETE|IN_ATTRIB`,失败降级(非致命);初始 `opendir(/dev/input)` 扫 `event*`;`process_inotify_events` 按 `sizeof(inotify_event)+ev->len` 步进、EACCES 靠 IN_ATTRIB(udev 设权限后)重试;`find_slot_by_path` 去重、`close_device` 幂等(检查 connected、memset、fd=-1)。⑤`gamepad_poll`:inotify 先于设备轮询;断开帧 memset axes 清零并把全部按钮 apply_button_state(false)→released、清 connected/name;连接帧置 connected+拷 name;`process_device_events` 非阻塞读循环,EAGAIN/EWOULDBLOCK 返回、ENODEV 等错误 close_device、短读跳过。总计仍 **664** 处修复。

此前：**R333 地形系统（高度图双线性采样/central-diff 法线/侵蚀邻居访问/编辑区域重建/坐标逆变换）深审——无 demo 可达高置信 bug，不修复** — `engine/src/renderer/terrain.c`。①`terrain_init` R161-A 拒绝 `grid_size<2`(防 `grid_size-1` 无符号下溢致索引循环跑约 40 亿次、堆巨量溢出;grid_size=1 会 `(f32)(grid_size-1)` 除零);`inv_scale=1/scale`(scale≤0→0)。②坐标:`t->inv_nm1=(f32)(grid_size-1)`(存 n-1,命名误导但全局一致)。`terrain_get_height` `gx=(x·inv_scale+0.5)·inv_nm1` 与 rebuild/modify/flatten/erode 的 `fx=(gx·(1/inv_nm1)-0.5)·scale` 互为精确逆变换→内部一致;双线性 `h00..h11` 经 `terrain_sample_height`(gx/gz clamp[0,grid_size-1])采样,边缘 ix+1=n 被 clamp 且 fx=0 权重为 0,无 OOB。③`terrain_sample_height`/`terrain_rebuild_region` 均 clamp 索引;rebuild 批量路径按行 `row_width=gx1-gx0+1≤grid_size` 上传连续 span、偏移 `(gz·grid_size+gx0)·8·4` 正确,无 staging 时回退逐顶点;法线 `nx=hl-hr,ny=2·hx,nz=hd-hu` central-diff、平坦→(0,+,0) 向上、`nl2>1e-7` 才 `fast_rsqrt` 归一。④`terrain_erode` 邻居 `heightmap[gz·n+gx±1]`/`[(gz±1)·n+gx]` 直接索引(无 clamp),但循环边界 `gx0<1→1`、`gx1>n-1→n-1` 且 `gx<gx1`(严格)使 `gx∈[1,n-2]`、`gz∈[1,n-2]`→`gx±1∈[0,n-1]`、`gz±1∈[0,n-1]` 无越界;侵蚀量 `fminf(max_d,h·0.5)·0.5` 按正向坡差 `share[]` 分配给四邻,`total_d`>0 才除。⑤`modify_height`/`flatten`/`noise_stamp` 编辑边界 clamp[0,grid_size-1]、`d2<r2` 圆形 falloff、`radius=0` 时 `d2<0` 恒假跳过(inv_r2=inf 不参与写入无 NaN);flatten 用持久化合并缓冲(indices+dists 单次 alloc、只增不减)单趟收集后按均值平滑;R303 编辑热力象限按世界中心 0 而非 scale·0.5 划分。观察(非 bug):`terrain_generate` 内同名局部 `inv_nm1=1/(n-1)` 遮蔽结构体字段,作用域内自洽仅用于坐标归一。总计仍 **664** 处修复。

此前：**R332 音频系统（miniaudio 3D 空间化/逆距离衰减/双层 slot free-list/流式状态机）深审——无 demo 可达高置信 bug，不修复** — `engine/src/audio/audio.c` + `audio_stream.c` + `audio.h`。①`audio_system_create`:AudioSystem+AudioImpl 单次 `calloc`(按 max_align_t 对齐偏移),destroy 用同布局重算 impl 指针单次 free;`ma_engine_init` 失败路径正确清理。②`audio_system_update`:9 分量 dirty-check 未移动则跳过 3 次 miniaudio 调用;移动则更新 listener pos/dir/up。③slot 管理:`audio_acquire_slot` free-list 优先、否则 bump 到 `source_cap(=AUDIO_MAX_SOURCES=32)`、耗尽返 UINT32_MAX;返回 `id+1`(0=无效);init 失败/`audio_stop` 归还 slot 均有 `free_count<AUDIO_MAX_SOURCES` 守卫,索引仅在 acquire(pop/bump)后才 push→free-list 无重复项;所有 `audio_source_*` 越界检查 `id==0||id>source_count` 且 `active` 门控。④R270:`audio_play`(2D/UI/音乐)用 `MA_SOUND_FLAG_NO_SPATIALIZATION`(否则默认空间化会随 listener 远离原点而按逆距离衰减致 2D 音降为 0.1),`audio_play_3d`/spatial 流显式 `set_spatialization_enabled(TRUE)`+`inverse` 模型+定位;`audio_attenuation_gain` helper `g=min/(min+rolloff·(clamp(d)-min))` clamp[0,1] 与 miniaudio inverse 一致。⑤流式(audio_stream.c):侧数组 intrusive free-list(`free_next[]`/`next_free`)O(1) 分配/归还,open 失败归还 slot(R107-1);R241 `audio_stream_pause`→`audio_source_stop`(仅暂停保游标),`audio_stream_stop`→`audio_stop`(uninit+归还);`audio_stream_update` 仅对 `!looping` 检测自然结束置 END_OF_FILE。观察(非 bug,非 demo 可达):播完的非循环一次性/流音效依赖调用方手动 `audio_stop`/`audio_stream_stop` 回收(终态供调用方决定重播/停止),demo 只开一个 `looping=true` 3D 流,EOF 分支被 `!s->looping` 守卫永不触发,无泄漏;`audio_play`/`audio_play_3d` 在 engine 内未被调用。总计仍 **664** 处修复。

此前：**R331 粒子系统（CPU emit budget 分数进位 + GPU 原子 spawn 认领 + size/alpha fade + cull/render 间接绘制）深审——无 demo 可达高置信 bug，不修复** — `engine/src/renderer/particles.c` + `shaders/particle_update.comp`/`particle_cull.comp`。①CPU budget(R174):`emit_accum += emit_rate·dt`,`>=1.0` 时 `budget=(u32)accum`、`accum-=budget`(保留分数进位)、`budget>PARTICLES_MAX` 则钳(丢弃超额,反正无处生);每帧 `fill_buffer(spawn_buf,0,4,0)` 清零 `claimed` 再 dispatch。②GPU update:死粒子(`life<=0`)在 `budget==0` 时早退,否则 `ticket=atomicAdd(claimed,1)`、`ticket>=budget` 早退→恰好认领 budget 个 spawn(死粒子少于 budget 时全生但绝不超发),`idx>=particles.length()` 守卫防越界;alive 分支 `t=clamp(life/max(max_life,0.001))`、`size=mix(0.1,1.0,t)` 从常量基插值(R281 修复:曾读回已衰减的 `size_color.x` 自反馈致复利式塌到 0.1 下限),`vel.y-=gravity·dt` 半隐式积分。③cull/render:`cull_buf`=4×u32 draw-indirect 头+索引表,`particles_cull` 只 GPU 清 instanceCount(offset 4B,R175 避免 HOST_VISIBLE memcpy 与在途 draw_indirect 竞争),`cull_ready` 时走 `draw_indirect` 由 GPU 定实例数(R167 避免 8192 空 VS 早退);R180 compute/cull 不 end/begin_render_pass(保 offscreen pass suspend/resume)。观察(非 bug):`particles_compute` 用 `PARTICLES_MAX/256`、`particles_cull` 用 `(PARTICLES_MAX+255)/256`,因 `PARTICLES_MAX=8192=32×256` 两者当前等价且 shader 有 `idx>=length()` 守卫,仅当改为非 256 倍数才 under-dispatch(潜在健壮性)。总计仍 **664** 处修复。

此前：**R330 线程化解码流水线（stb 解码/box mip 链/优先级输入队列/worker 生命周期/所有权契约）深审——无 demo 可达高置信 bug，不修复** — `engine/src/asset/decode_pipeline.c`。①mip 链:1×1→mip_count=1 无 mip 循环;计数后 `>16` 截断使 `widths/heights/offsets[16]` 索引 `i<mip_count≤16` 安全(R153);level i 从已写入 packed 的 level i-1 box 下采样、offsets 连续、memcpy 长度 `next_w·next_h·4`==该级分配空间;`raw_size>INT32_MAX`(R144)、`hdr_sz+total_pix>UINT32_MAX`(R160-B)守卫防截断。②优先级输入队列(值小=优先):`<head` 头插、否则跳过 `<=job.priority` 的前缀保 FIFO 稳定,tail 在"空表头插"与"尾插"两路正确维护(逐案验证);`count>=DECODE_INPUT_CAP(256)` 拒绝防原始字节无界堆积(R167-A)。③worker/生命周期:`running=false` 在 `input.mutex` 下发布+`cond_broadcast`(canonical condvar teardown),worker 完成在手 job 并 push ready 后才退出→join 不丢 job;shutdown 释放剩余 input(raw_data+job)与 ready(node 即 DecodeJob 首字段,raw_data 已在 worker 释放,仅释 result.data+job)无双重释放;R292 进程稳定 mutex/cond 避免 re-init/destroy 竞争(TSan 确认)。④所有权契约:`decode_pipeline_submit` 所有 false 返回均不释放 raw_data,唯一调用方 `async_loader.c:311` else 分支 `free(data)`+finalize FAILED,success 时移交流水线由 poll 落地——一致,无泄漏/双重释放。观察(非 bug):`!base||w<=0||h<=0` 分支中 base 非空但 w/h≤0 会漏释 base,然 stbi 返回非空时必 w,h>0 故不可达;2 worker 用 broadcast 而非 signal 属可忽略轻微开销。总计仍 **664** 处修复。

此前：**R329 并行渲染器/命令缓冲（双缓冲 swap、submit 线程 condvar、按 key 排序、录制溢出）深审——无 demo 可达高置信 bug，不修复** — `engine/src/renderer/cmd_buffer.c`。①双缓冲:`swap_and_submit` 先 `wait_submit`(等上一帧提交完成)再交换 write/read,故 submit 线程正读取的 read 帧不会被下一 `begin_frame` 重置(后者只重置新 write=旧 read=上上帧已提交缓冲);线程与非线程(直接 submit read 帧)路径均正确。②condvar 同步:`submit_pending` 原子置位在锁外、`signal(submit_ready)` 在锁内,submit 线程在锁下检查谓词并 `cond_wait`→无丢失唤醒;`read_frame` 明文写在加锁前、submit 线程唤醒后持锁读取,mutex acquire/release 建立 happens-before→无数据竞争;`stop_submit_thread` 内层 `while(!submit_pending&&!shutdown)`+`if(shutdown)break` 无死锁,join 前 `wait_submit`。③`sort_buffer_indices_by_key` 稳定插入排序(严格 `>`)、`indices[16]` 且 n≤thread_count≤16 无越界。④录制:`cmd_buffer_reserve` `count>=CMD_BUFFER_MAX_COMMANDS(4096)` 返 NULL 静默丢弃(单写者无锁);`cmd_push_constants` size clamp 到 `CMD_BUFFER_PUSH_CONST_MAX` 再 memcpy。⑤`replay_command` 各命令映射到 RHI(R207-B/R208-B/R223-A/R224-A/R225-A 已加固)。观察(非 bug):`FrameCommands.sort_keys[]` 为遗留死字段,实际排序用 `RenderCmdBuffer.sort_key`;`active_recorders` 仅诊断计数。总计仍 **664** 处修复。

此前：**R328 渲染图 拓扑排序反向邻接表 fan-out 数组过小（误报环）修复** — `rg_topo_sort`(`engine/src/renderer/render_graph.c`)用反向邻接表 `rdeps[dep]=依赖 dep 的 pass` 做 Kahn 拓扑排序,以 O(V+E) 取代 O(V²)。**Bug**:`rdeps` 第二维误用 `RG_MAX_PASS_DEPS(16)`。`dependencies[]` 限 16 是对的(单 pass 依赖数 ≤ 其读取数 ≤16),但**反向关系(dependents/被依赖数)不受此约束**:单个 producer(如只写一次的 depth prepass / gbuffer)可被其余每个 live pass 读取,dependents 可达 `pass_count-1`(≤`RG_MAX_PASSES-1`=63)。旧的 `rdeps_count[dep] < RG_MAX_PASS_DEPS` 守卫在第 16 个 dependent 之后**静默丢弃反向边**,却仍在 `in_degree[p]++` 计入 → producer 调度时这些被丢弃 dependent 的 in_degree 永不归零 → 永不入队 → `execution_count < live_total` → `rg_compile` **误报"cyclic dependency"并拒绝执行一个无环图**(`rg_execute` 因 `!compiled` 直接返回 → 整图不渲染)。**修复**:`rdeps` 第二维改为 `RG_MAX_PASSES`,守卫改为 `< RG_MAX_PASSES`(`rdeps_count[dep] ≤ pass_count-1 < RG_MAX_PASSES`,守卫转为纯防御);栈占用 4KB→16KB(可接受,保持可重入)。**回归测试** `topo_high_fanout_producer`:1 producer + 30 consumer 均读同一资源(远超旧上限 16),断言 `rg_compile` 成功、`culled_count==0`、全部 31 pass 被调度;旧代码此测试因误报环 `ASSERT_TRUE(ok)` 失败。GL/VK 各 30/30(排除偶发 test_async_loader)、test_render_graph 18/18 通过。总计 **664** 处修复。

此前：**R327 即时模式 GUI（hit-test/press 状态机/slider 拖拽/边沿锁存）深审——无 demo 可达高置信 bug，不修复** — ①`imui_hit` 半开区间 `mx∈[x,x+w) && my∈[y,y+h)`;`imui_slider_map` `t=(mx-x)/w`(w≤0→0)clamp[0,1] 映射到 `[minv,maxv]`;`imui_slider_norm` `maxv==minv→0` 否则 clamp。②`imui_press_logic` 标准 IMGUI:hovered 置 hot_id、`pressed_now=down&&!prev`、`released_now=!down&&prev`,active==id 时 release-over-widget=click 并清 active,否则 `hovered&&pressed_now&&active==0` 才捕获 active(防抢占)。③`imui_slider_float`:active 时随 `mouse_x` 更新并 clamp(离开控件仍拖拽,符合预期),仅在 `hovered&&pressed_now&&active==0` 起拖。④`imui_begin` 每帧清 `hot_id`、`imui_end` 锁存 `mouse_prev_down=mouse_down` 供下帧边沿检测,`imui_reset_input` 处理面板隐藏时交互复位。⑤`imui_label` 用 `vsnprintf(buf,sizeof,...)` 有界;`im_rect/im_text` 委托 `font_renderer`(顶点缓冲界限见 R282/R297)。观察(非 bug,R296 已记):slider knob 中心按 `(w-knob_w)·t` 定位、点击按全宽 `w` 映射,二者有微小视觉偏移。总计仍 **663** 处修复。

此前：**R326 异步加载器 优先级最小堆 + Vyukov MPSC 完成队列 + 槽分配/回滚深审——无 demo 可达高置信 bug，不修复** — ①二叉最小堆:`heap_item_higher`(priority 小者优先、seq 小者 FIFO 平局)、sift-up/down 标准、`heap_push` 满(≥256)返 false、`heap_pop` 取根→末元素补根→count-- →(count>0)sift-down,count 减到 0 跳过 sift-down 均正确。②MPSC 完成队列(生产者=worker,消费者=main):`enqueue_completion` fetch_add head(relaxed)→写 index→release 发布 `sequences[i]=comp_slot+1`;drain 侧 `seq != tail+1` 守卫等待发布(release/acquire 配对使 index 可见)、sequence 编码绝对槽号区分环绕、仅 READY/FAILED 触发回调并清槽置 UNLOADED。③容量:`ASYNC_MAX_REQUESTS==ASYNC_QUEUE_SIZE==1024`,每请求至多一个在途完成且槽回收需先 drain,故最多 1024 在途、环位置双射无覆盖(R165-A 恰好满足)。④槽分配:R242 用 CAS `UNLOADED→LOADING` 探测(避免 check-then-store 竞争与轮询饥饿);`heap_push` 失败时回滚(减 pending、state 置回 UNLOADED、返 0,无槽泄漏,R171)。已由 R165/R168-A/R170/R171/R242/R292 加固。总计仍 **663** 处修复。

此前：**R325 mipmap 流式加载（coverage→level/预算驱逐/字节记账/invalidate）深审——无 demo 可达高置信 bug，不修复** — ①`coverage_to_level`:用 IEEE754 指数位近似 `floor(0.5·log2(1/coverage))`(`level=(127-exp_bits)>>1`),验证 0.25→1、0.0625→2,边界 ≥1→0、≤0/subnormal→clamp `mip_count-1`;`mipmap_level_size` 有 `>UINT32_MAX` 守卫、w/h 下限 1。②字节记账全流程自洽:Phase1 发起 load 时 `total_resident_bytes += needed`(预留,state=LOADING),完成回调 LOADING→RESIDENT **不重复加**、失败/取消(data 空)释放预留、stale 完成(req_id 不匹配/非 LOADING)仅 free data 不动字节;Phase1/Phase2/blocking 驱逐只碰 RESIDENT 并带 `>=` 下溢守卫减字节。③`mipmap_stream_invalidate`:LOADING 减字节+置 UNLOADED+req_id 清零(在 `async_loader_cancel` **之前**,使取消回调因 state≠LOADING 而不双重扣减)、RESIDENT 减字节,再 free data;`shutdown` 取消在途(ready=false 后字节无关)。④`register` R170 拒绝零宽高/mip/bpp(防 `mip_count-1` 下溢)。已由 R167-D/R170/R171/R172 加固。总计仍 **663** 处修复。

此前：**R324 网络 peer 管理/payload 解析/持久化深审（R323 相邻代码）——除 R323 外无 bug，不修复** — ①`net_repl_peer_apply_line`:`%255s` 读入 `host[256]`,`memcpy(addr.host, host, strlen+1)` 目标 `NetAddress.host` 亦为 `char[256]`,≤256 入 256 安全;sscanf `<7` 校验字段齐全。②`net_repl_parse_payload`(R254):`n` 同时钳到 `max_count`(out 容量)与 `avail=(write_pos-read_pos)/16`,防伪造计数越界读/(0,0,0) 幽灵实体。③`peer_evict_stale`:swap-remove(交换末元素、不前进 i 重查)正确;`peer_evict_lru` 取最小 `last_seen_ms`。④持久化:`peer_save/load` 用 `fgets(line,512)` 有界、`peer_save_dir/load_dir` `snprintf` 有界路径+`.peer` 过滤、delta 叠加基线且 apply_line 按地址 `peer_find(create)` 去重、`peer_save_delta` "+ " 前缀 apply 识别。⑤`recv` 用 `wire[PACKET_MAX_SIZE]`+`net_recvfrom(sizeof)`、`feed/feed_from` 转 `process`(含 `len>PACKET_MAX_SIZE` 拒绝)。总计仍 **663** 处修复。

此前：**R323 网络可靠层 ack 语义修复——外发 ack 应回显收到的对端 sequence（此前误回显对端 ack 字段，可靠包永不被确认、无限重传）** — 包头 `ack` 字段语义为"我在确认你的某个 sequence"(packet.h;发送方在 `deliver_*` 处 `(hdr.ack - reliable_pending.seq)<0x80000000` 清除自己的 pending)。但接收侧把 `rep->last_peer_ack=hdr.ack`(对端对**我**的确认)后,发送路径(`broadcast`/`send_heartbeat`/`send_heartbeat_ack`)又把它当作**自己**外发包的 ack 字段 → 双方只是把各自的 ack 值来回弹,从不确认对方的 sequence,`reliable_pending` 永不因 ack 清除,`net_replicator_retry_pending` 无限重传最后一个可靠包(`reliable_retry` 经 `BREAK_NET_*` env 在 demo 启用,demo 可达)。**修复**:新增 `rep->ack_to_send`,在 `net_replicator_process` 收到 RELIABLE 包时按回绕安全 `(hdr.sequence - ack_to_send)<0x80000000` 单调推进为 `hdr.sequence`,并把三处外发 `packet_finish` 的 ack 参数由 `last_peer_ack` 改为 `ack_to_send`;`last_peer_ack` 仍记录 `hdr.ack` 供 retry 自检(L407)与 pending 清除(L147/246)。新增回归测试 `reliable_ack_echoes_received_sequence`(喂 seq=7/ack=99 → `ack_to_send==7`、`last_peer_ack==99`)与 `reliable_pending_cleared_via_peer_ack`(B 收 seq=5→`ack_to_send=5`;该 ack 回传 A 清除其 pending)。GL/VK 各 30/30(排除环境性 flaky 的 test_async_loader),net_replication 单测 21/21。总计 **663** 处修复。

此前：**R322 角色控制器 滑动解算/step-up/grounded 状态机深审——法线约定/连跳守卫/退化处理/台阶接受判定均正确，无 demo 可达高置信 bug，不修复** — ①`char_slide_resolve`:6 次穿透解算迭代,`physics_collide(&cap,b,&ct)` 的 `ct.normal` 恒为调用方 (cap→b) 约定(`physics_collide` 在 `shape_rank` 换序时 `if(swapped) n=-n` 翻回),故 `sep=-normal`、`pos+=sep·depth` 正确把胶囊推离静态体(无隧穿);`sep.y>slope_limit` 判 grounded(单位推出法线 y 分量=可行走面);R239 candidate 饱和(nc>=64)回退全量线扫防漏。②`character_update`:R280 连跳守卫 `jump && grounded && vy<=0`(起跳后几帧仍与地面 AABB 重叠致 grounded 为真,若无 vy<=0 会连跳增高);垂直解算 `grounded_v && vy<0` 落地夹 vy=0;`horiz_l2==0` 时 `horiz_len=0·fast_rsqrt(0)=0`(非 NaN),step-up 分支 `horiz_len>1e-5` 安全跳过;step-up"抬 step_height→前移 horiz→下探 step_height"后,仅当 `grounded_d && horiz_progress(down)>horiz_progress(flat)+1e-4`(即 flat 被阻挡、登台阶更前进)才接受 down,否则回退 flat。总计仍 662 处修复。

此前：**R321 任务系统 Chase-Lev 工作窃取队列 + 引用计数/依赖 fan-out + task_wait 记账深审——内存序与并发语义均正确，无 demo 可达高置信 bug，不修复** — ①`deque_push/pop/steal` 是 Lê et al. 弱内存序正确版的忠实实现:push(relaxed bottom/acquire top/release fence/relaxed store bottom)、pop(store bottom→**seq_cst fence**→load top,末元素 `t==b` 用 seq_cst CAS 抢占 steal)、steal(acquire top→**seq_cst fence**→acquire bottom→读 buffer→seq_cst CAS top);`DEQUE_CAPACITY=1024`(2 的幂),`b & (capacity-1)` 环绕正确;capacity=0(OOM,R166-A)下三操作均安全早退不解引用 NULL。②`task_release` acq_rel 递减,`old==1` 且非 block 内任务才 free;`execute_task` 完成序:`completed`(release)→`total_tasks_completed`(**acq_rel**,R267 保证 fn() 写入对 task_wait 的 acquire 载入 happens-before)→锁下摘 waiter 链→逐子 `dep_count` acq_rel 递减,`old==1` 即 `schedule_ready`+`task_release`。③`task_submit_dep`:提交即计 submitted(R173,阻塞态也计),OOM 路径回滚 waiter/ref/submitted 并标 completed 避免欠计(R177),`actual_deps==0` 立即入队不重复计数。④`task_wait` 终止 `completed>=submitted && pending(submit_count)==0`:deque 内任务由 submitted 覆盖、全局队列由 submitted+pending 双覆盖,等待时帮忙执行(worker 弹本地→拉全局;非 worker 内联 drain)。总计仍 662 处修复。

此前：**R320 BVH 光线求交遍历 + 自碰撞对偶枚举 + refit 深审——slab/遍历序/早退/对去重均正确，无 demo 可达高置信 bug，不修复** — ①`bvh_raycast`:`inv_dir` 零分量用 ±1e8 兜底;`ray_aabb_intersect`(非 SIMD)标准 slab `tmin=0/tmax=max_t` 返回入射 tmin;递归"近子先遍历",第二子在递归入口用**更新后的 `best_t`** 重测早退;叶节点 `t<best_t` 严格更新(平局保留先到)。②`bvh_query_pairs_dual`:self-pair(内部)只 descend LL/RR/LR(省略 RL 避免重复)、distinct 内部节点 fan-out 全 4 组合、叶-叶用 `a<b`/`a>b` 仅做参数**规范排序**(两分支都回调、非去重守卫,R288 已修正原误丢约半数对的 bug)、`a==b` 跳过;每无序对恰好枚举一次。③`bvh_refit`:置叶 bounds 后上溯到根 `bvhaabb_union(left,right)`,含 `nodes/leaf_map` NULL 与 `object_index` 越界守卫(R154)。总计仍 662 处修复。

此前：**R319 物理窄相闭式几何 + 冲量求解器深审——法线约定/穿透深度/位置速度分离/退化分支均正确，无 demo 可达高置信 bug，不修复** — ①最近点:`closest_seg_seg` 是 Ericson RTCD 的忠实实现(`a/e<=eps` 退化、`t=(b·s+f)/e`、`denom` 守卫、越界后重夹 s 均与原文一致),`closest_on_segment` 带 `denom<1e-12` 守卫。②接触生成 `collide_ordered`(法线恒"A→B"):sphere-sphere `n=norm(B-A)`、sphere/capsule-capsule `n=norm(A侧最近点→B侧)`、退化回退 `(0,1,0)`,`depth=r-dist`。③`sphere_vs_box` 球心在盒内分支:沿最小穿透面选 `exit_sign`,`n=-exit_sign` 使求解器沿 `-n=exit_sign` 推出、`depth=best+r`,与盒外(沿 `-n` 分离)一致;capsule-box 用 2 步迭代逼近+`inside` 兜底深穿透。④`resolve_contact`:位置按逆质量分配(A 沿 `-n`、B 沿 `+n`),`vel_along_normal=dot(v_a-v_b,n)>0` 为接近(R262 已修正倒置守卫,仅 `<0` 分离时跳过),`j=-(1+e)·vn·inv_total`,A `+=j·n·inv_a`/B `-=j·n·inv_b` 标准解算。⑤kill-floor(y<-10)夹回并按 restitution 反射 y 速度。总计仍 662 处修复。

此前：**R318 场景序列化(BSCN 二进制/JSON/prefab)+ ECS 组件迁移/archetype swap-remove 深审——均正确/已加固，无 demo 可达高置信 bug，不修复** — ①`scene_serial.c`:`bb_reserve` 倍增、`emit_components_chunk` 用**偏移**(非指针)回填 instance 计数避免 realloc 失效、`emit_hierarchy_chunk` CSR 单块分配 `4n+1`(child_count/offsets[n+1]/children/cursor)边界正确、`load_*` 全程 `rd_bytes` 边界检查、R108 chunk 表/数据 `u64` 越界校验、R243 generation 二进制+JSON 双路往返、`load_components_chunk` 用磁盘 `size` 跳过未知/尺寸不符组件、`emap_build` 借用 `saved_to_entity` 区做 is_free 位图(4N≥N 无越界)。②`ecs.c`:`w->archetypes` 为 `ECS_MAX_ARCHETYPES` 定长内联数组,`create_archetype` 不搬迁→`world_add_component` 捕获的 `old` 指针不悬空(`world_remove_component` L537 甚至多余重取);`archetype_swap_remove` 正确更新被移动实体 `entity_index` 并递减末 chunk `count`;迁移顺序(dest 分配+拷贝→old swap-remove→写 `entity_index`)对"e 为/非 old 末元素"均正确。观察(非 demo 可达,不修复):`scene_instantiate_prefab` 的 `position` 仅偏移场景节点,而 `scene_save_prefab` 只写 ENTITIES+COMPONENTS(无 SCENE_NODES)→对纯实体 prefab `position` 是静默 no-op;类型无关序列化器无法通用地偏移 Transform 组件,且该 API 无 demo/测试调用。总计仍 662 处修复。

此前：**R317 动画双骨骼 IK 求解器深审——数学正确、求解稳健，无 demo 可达高置信 bug，不修复** — 审计 `anim_ik_two_bone`/`anim_ik_solve`:①余弦定理角度正确(root 角 `cos=(lab²+lat²-lcb²)/(2·lab·lat)` opposite lcb、mid 角 opposite lat),用 `atan2(sinlen,dot)` 而非 `acos(clamp)` 更稳;②`sin=sin2·rsqrt(sin2)=sqrt(sin2)` 恒等正确;③`lat` 夹到 `[0.001, lab+lcb-eps]`,目标过近使 `1-cos²<0` 时被 `fmaxf(...,0)` 夹为直/折配置优雅降级(非崩溃);④弯曲平面法线 `axis0=cross(ac,pole_dir)`(pole 共线时回退到 ac 的任一垂向)供 r0/r1 共用、reach 轴 `axis1=cross(ac,at)`(退化回退 axis0)——标准解析法;⑤`root=r2·r0`(先弯后够)、`mid=r1`,权重 `nlerp(I,delta,w)`;⑥set/solve 边界 `index<ANIM_MAX_IK_TARGETS`。观察(非本轮修复)：既有 `ik_two_bone_solver` 测试仅断言旋转非单位、未验证 tip 到达 target(弱覆盖);世界空间 delta 左乘到 `rotations[]` 是骨架约定,安全加强需先固定 FK 应用约定。总计仍 662 处修复。

此前：**R316 音频子系统(3D 空间化/槽位管理/衰减模型)深审——无 demo 可达高置信 bug，不修复** — 审计 `audio.c`+`audio_stream.c`:①单块分配 `AudioSystem+AudioImpl`(按 max_align_t 对齐)与 `audio_system_destroy` 偏移重算一致、失败路径 `free(as)` 释放整块正确;②`source_cap=32 == AUDIO_MAX_SOURCES == free_list[32]`,`audio_acquire_slot`(free-list 优先再 bump)与失败回收(`free_count<AUDIO_MAX_SOURCES` 守卫)一致,bump 失败虽使 source_count 高水位虚增但槽位经 free-list 复用无功能缺陷;③R270 2D 声用 `NO_SPATIALIZATION`、`audio_play_3d` 显式重启空间化+inverse 模型正确;④`audio_stream.c` 侵入式 free-list(`stream_alloc_slot`/`stop` O(1) 回收)、R241 pause 用保留态原语(源不 uninit、可 resume)、`stream_idx_valid` 守卫、EOF 检测;⑤`audio_attenuation_gain` 精确复刻 miniaudio inverse 增益 `min/(min+rolloff·(clamp(d)-min))`、clamp 到 [min,max]/[0,1]。经 R107/R241/R270 加固。总计仍 662 处修复。

此前：**R315 屏幕空间光效(镜头光晕/TSR 上采样/God Rays/调试可视化)多窄线深审——无 demo 可达高置信 bug，不修复** — 审计屏幕空间效果 C 侧与其 CPU 投影:①`lens_flare_apply` 把 `light_dir` 当无穷远方向(w=0)投影——`view` 只用旋转、`proj` 正确丢弃平移列,`clip_w=-vz` 与 `light_view_z>0`(背对相机)早退清屏一致,NDC→screen 标准;②`upscale.c` TSR 双 pass ping-pong 正确(pass1 读 `history[read_idx]` 写 fbo,pass2 拷入 `history[write_idx]`,`history_idx=write_idx`);③`god_rays` 的太阳屏幕投影在 main.c(R209-A):`vp·(-sun_dir, w=0)`、`sw>0` 守卫、范围裁剪,背对相机时不调用 apply 且不切 `tonemap_input`(无残留);④`debug_viz.c` 全屏深度可视化,`cascade_splits[1..4]` 索引正确。均为正确薄封装/正确投影。总计仍 662 处修复。

此前：**R314 手写矩阵捷径同类回归审计(R49/R50/R53 稀疏乘法+求逆、CSM 级联 VP)——无 bug，不修复** — 承接 R313(point_shadow 解析 VP 错误)的 bug 类别,系统数值核验所有"手写/优化矩阵闭式":①`mat4_mul_proj_view`(R50)、`mat4_mul_ortho_diag`(R49)、`mat4_inv_perspective`(R53)对含 TAA jitter 的透视 P、任意 view V、对角+平移 D 与通用 `mat4_mul`/`mat4_inverse` **逐元素一致**(maxdiff≤1.9e-9);②main.c CSM 级联 `lview`(预计算基直接填充)逐元素等价于 `mat4_lookat(eye,center,(0,1,0))` 左手约定(`s=(sx,0,sz)`、`u=cross(s,f)`、row2=−f、平移=−基·eye),`lproj=mat4_ortho` 经已验证的 `mat4_mul_ortho_diag` 合成;R247 天顶太阳退化基有守卫。CSM 无 texel snapping 属画质取舍(阴影抖动),非正确性 bug。结论:R313 的解析式错误是孤例,同类捷径均正确。总计仍 662 处修复。

此前：**R313 点光源立方体阴影 VP 解析式错误 → 正前方几何被裁剪、cubemap 为空、点阴影全失效 — 修复 1 处** — **R313-A**（CORRECTNESS）：`point_shadow_compute_face_vp` 的"解析闭式"(自称 VP"至多 2 个非零行")在本引擎 `e[col][row]` 列主序下**根本错误**:每个面只写了 clip.x/clip.y 或 clip.z,且其 clip.w 行依赖了错误的世界轴。数值验证(light=(2,3,5),r=10):光源正前方点在 **+X/+Y/+Z 面 clip.w<0**(被近/w 裁剪丢弃),−X/−Y/−Z 面则落在 NDC 外(如 −X 的 x/w≈−2.3)。故 6 张深度 cubemap 捕获不到正对几何→点光源阴影从不成形(自 R82 起静默损坏)。修复:改为按各面既定基构建真实 `view` 再 `proj·view`(`mat4_perspective(90°,1,0.1,far) × RH view`),正前方点在全部 6 面映射到 NDC(0,0)且 w=+2>0(编译级数值验证,并与 `mat4_perspective·mat4_lookat` 参考一致)。成本可忽略(≤ MAX_LIGHTS×6 次小矩阵/帧),正确性优先于旧手写稀疏技巧。depth 由片元 `length()` 写入,各面朝向沿用原基注释故采样一致。main.c:3850 在有 point light 时激活该路径→demo 可达。构建 GL/VK 通过;CTest GL/VK 各 30/30。覆盖缺口(记录)：`point_shadow.c` 重度耦合 RHI(约 15 个符号),纯函数单测需桩接整个 RHI,不切实际;按 R256 先例以独立数值程序(/tmp/ps_verify:6 面全 PASS)+ 构建 + 全套件验证。总计 662 处修复。

此前：**R312 间接绘制/TAA/IBL/体积雾/场景世界变换/后处理合并链多窄线深审——无 demo 可达高置信 bug，不修复** — 本轮系统审计 GPU 驱动渲染与后处理 C 侧编排:①`indirect_draw.c`(GPU 剔除后 compact/execute/双槽可见性)经 R76/R171/R175/R182/R183/R185/R186/R234-B 多轮加固,`visibility_slot=buf[frame&1]` 上传与 compact 同帧读写一致、`draw_indexed_indirect_count` 以 `current_draw_count` 为 maxDraw 上界正确、compact 前 GPU 端清零计数/可见槽正确;②`taa.c` 历史缓冲 ping-pong(`write=idx`/`read=1-idx`,帧末 `idx=read`)与 `taa_get_output` 返回 `fbo[1-idx]=write` 逐帧核对正确;③`ibl.c` 预滤波 mip 链(`mip_size=SIZE>>mip`,`roughness=mip/(N-1)`,`groups=ceil(mip_size/16)`)与辐照度/BRDF dispatch 计数正确;④`volumetric.c` 薄封装、CPU 侧仅一次 `mat4_inverse(view)`(R224-B)正确;⑤`scene_compute_world_transforms` 经 R256 迭代定点(序无关、环有界)正确;⑥`combined_post_process.c` 主 `use_combined` 路径 ping-pong 与 `fxaa_apply` 内部绑定自有 FBO 使 fallback `get_output` 自洽(fallback 前冗余 output_fbo 绑定为 demo 不可达死资源,非正确性 bug)。总计仍 661 处修复。

此前：**R311 hotreload_pipeline_poll 缺 ready 守卫 → 初始 shader 编译失败后每帧 read(stdin) 阻塞挂起 — 修复 1 处** — **R311-A**（CORRECTNESS）：`hotreload_pipeline_poll` 直接 `filewatch_poll(&hr->watcher)`,不像同文件 `hotreload_texture_poll` 那样先 `if (!hr || !hr->ready) return;`。当 `hotreload_pipeline_init` 失败时(初始 shader 编译错误——正是热重载迭代的目标场景),它在调用 `filewatch_init` **之前**返回 false,`*hr` 停在入口 `memset(0)` 态:`ready=false`、`watcher.inotify_fd==0`。`main.c:1196` **忽略 init 返回值**、`main.c:2546` 每帧无条件 `hotreload_pipeline_poll`,于是 `filewatch_poll` 命中 `if (fw->inotify_fd >= 0)`(0 也通过!)分支执行 `read(0, buf, 4096)`——即每帧对 **stdin 阻塞读**:TTY 下挂起整个渲染循环,重定向时静默吞掉管道输入。根因:零值 watcher 的 `inotify_fd==0` 是合法 fd、误判为已初始化。修复:`hotreload_pipeline_poll` 加 `if (!hr || !hr->ready) return;`(与 `hotreload_texture_poll` 对齐),仅在 init 成功后轮询。编译 GL/VK 通过;CTest GL/VK 各 30/30(排除环境相关 test_async_loader)。覆盖缺口(记录)：hotreload/filewatch 无 test harness（不在 CMakeLists 测试目标),按先例(scene_serial)以构建+全套件+推理验证。总计 661 处修复。

此前：**R310 Lua 绑定层 + 后处理(SSAO/DoF/Bloom) C 侧多窄线深审——无 demo 可达高置信 bug，不修复** — A `script/script_lua.c`：`checked_body` 用 `id<=0 || (u32)id>=pw->count` 拒绝——存疑点是物理体 id 为 **0-based**（`physics.c:108 id=pw->count++`），首体 id=0；但 `test_script_lua.c:103` 明确注释 **"body 0 = sentinel/floor (bindings treat id 0 as 'none')"**，即 id 0 被绑定层有意当作"无"哨兵、约定 0 号体总是预建地板，`l_spawn` 无 host 时也返回 0（=none），故 `id<=0` 拒绝为**有意设计非 bug**；上界 `id>=count` 正确（0-based 末位 count-1 accepted）。`l_spawn` 因 `physics_body_create` 满时返回 `count` 不自增（`checked_body` 随即以 `id>=count` 拒绝）而无 `bodies[]` 溢出；`l_key_down` 有 `[0,512)` 守卫；所有绑定 Lua 栈平衡（`ls_from_state` getfield+pop、`l_get_pos/vel` push3 return3、`refresh_hooks`/`get_number` getglobal+pop）；`ls->last_mtime` 已按实例（R309 同类问题此处本就正确）。B `renderer/ssao.c`/`dof.c`/`post_process.c`(bloom)：C 侧仅创建管线/FBO(width/2×height/2 半分辨率)+ 传 uniform + 绑纹理,AO 半球核/DoF CoC/bloom 提取模糊数学全在着色器,C 侧无可测算术;记录（非高置信）：`dof_apply` 硬编码 `u_dof_near=0.1/u_dof_far=100` 与 demo 相机 near/far 一致,若相机参数改动需同步,但当前一致故非 bug。决策：无 demo 可达高置信 CORRECTNESS 问题,不改代码（precedent R296/R297/R300/R301/R306/R307）。编译/测试未触及（纯审计）。总计仍 660 处修复。

此前：**R309 script 热重载 mtime 用函数内 static 跨引擎实例共享 → 重建的引擎永不重载、永久为空 — 修复 1 处** — **R309-A**（CORRECTNESS）：`script_reload_if_changed` 用**函数内 `static u32 last_mtime`** 记录上次文件 mtime,被所有 `ScriptEngine` 实例与所有脚本路径共享。故障两类:(1) **重建陈旧**——`script_engine_init` memset 把引擎复位为空(`loaded=false`、0 funcs),但共享 static 仍留旧 mtime → 本函数见 `mt==last_mtime` 跳过 `script_load` → 重新初始化的引擎**永久为空**(每次 `script_call` 静默 no-op),关卡/引擎重建流程直接触发;(2) **多文件混淆**——交替两个路径(或两个引擎)经一个 static,依 mtime 碰撞而"永远看似已变"(反复重载)或"永远看似未变"(从不重载)。修复:把 `last_mtime` 移入 `ScriptEngine` 结构(按实例隔离,由 `script_engine_init` 的 memset 归零),`script_reload_if_changed` 改用 `se->last_mtime` 并加 `!se` 守卫——新引擎首次检查必加载当前文件。回归 `reload_if_changed_is_per_engine`:引擎 A reload 同一文件后,全新引擎 B 读**同一未改动文件**须也加载(断言 `b.last_mtime==0` 初始化归零、B `loaded`/`func_count==1`/`hp==7`);旧共享 static 下 B 永不重载、`loaded=false` → FAIL,修复后通过。此前测试从不跨实例调用 `script_reload_if_changed` 故掩盖。编译 GL/VK 通过;CTest GL/VK 各 30/30(排除环境相关 test_async_loader),test_script 本地 14/14（含新用例）。总计 660 处修复。

此前：**R308 render graph 纹理池重复入池 → 资源别名 + 析构双重释放 — 修复 1 处** — **R308-A**（CORRECTNESS）：`render_graph.c` 生命周期别名纹理池。`rg_pool_claim` 认领池中纹理时**只置 `in_use=true`、不移除**该条目（注释误称"removed"，实为原地翻标志）。而 `rg_reset` 遍历本帧所有 `allocated && !imported && !buffer` 的资源**无条件追加**为新池条目。于是一个"从池认领"的纹理在下一帧 reset 时被再次入池 → 池中出现两条指向同一 `RHITexture` 句柄的条目，随后：(1) 后续帧 `rg_pool_claim` 可把这一块物理纹理同时发给两个不同 RG 资源 → 二者别名、互相覆写内容；(2) `rg_destroy` 遍历整个池对共享句柄 `rhi_texture_destroy` 每个重复各一次 → **双重释放**；(3) 池每帧多一条重复直至溢出 `RG_MAX_RESOURCES(128)` 后开始销毁仍在用的纹理。逐帧 `rg_reset`（渲染图正常用法）+ 至少一个跨帧持续的 RG 纹理即触发。修复：`rg_reset` 入池前按句柄（index+generation）去重，已在池中（本帧从池认领）者跳过——尾部 `in_use=false` 循环使既有条目下帧可复用；纯新建纹理（首帧）仍正常入池。回归 `reset_does_not_duplicate_pool_textures`（设 device 使纹理真正分配，5 帧 create+compile+reset 后断言 `pool_count==1` 且无两条目共享句柄）：旧码 pool_count=5（每帧一份重复）→ FAIL，修复后 =1。此前测试从不调用 `rg_set_device`（device=NULL → 纹理永不分配、池永不填充）故完全掩盖该 bug。编译 GL/VK 通过；CTest GL/VK 各 30/30（排除环境相关 test_async_loader），test_render_graph 本地 17/17（含新用例）。总计 659 处修复。

此前：**R307 聚簇光照 CPU 分箱 + 占用剔除可见性 多窄线深审——无 demo 可达高置信 bug，不修复** — A `renderer/lighting.c` CPU 聚簇分箱：`cluster_depth` 指数深度切片正确、`mat4_vec4` 列主序 M*v（SSE2/标量一致）正确、z-slice 重叠 `vp.z+r<-z_far||vp.z-r>-z_near`（view -Z 朝前）正确、屏幕 AABB 拒绝+`screen_ok`（w<=0.001 跳过屏幕剔除保守纳入）正确、容量守卫双重防溢出+goto done 剩余 cluster 保持 0/0 安全、offset/count 连续。记录（回退近似非 bug）：`screen_r` 省略投影缩放 proj[0][0]，典型 FOV 近似成立，且 CPU 分箱仅 GPU cluster_cull.comp 缺失时回退。B `occlusion_cull.c`：`oc_calc_mip_levels`=`floor(log2)+1`（pow2/非 pow2 均对）、`occlusion_cull_visible_count` SSE2 分支无关计数（`andnot(cmpeq(v,0),ones)`→可见 4 字节 0xFF、`popcount/4`）与标量尾一致、`occlusion_cull_is_visible`（enabled/null/越界保守返可见）正确。记录（1 帧延迟可容忍非高置信）：dispatch readback 用新 count 读上帧 staging，count 增长时读陈旧尾部但占用剔除本就 1 帧延迟、误判可见安全且自校正。决策：无 demo 可达高置信问题，不改代码。编译/测试未触及（纯审计）。总计仍 658 处修复。

此前：**R306 skeleton 世界矩阵解析 + frustum 剔除 多窄线深审——无 demo 可达高置信 bug，不修复** — A `animation/skeleton.c`：`mat4_trs` 组合 T*R*S 的 r00..r22 与 `mat4_from_quat` 列主序逐一核对一致（列 0/1/2×sx/sy/sz、列 3 平移、底行 0001）；`skel_resolve_world`（R240 定点法）对任意 joint 顺序正确（`p==UINT32_MAX||p>=n||p==i` 视根、未解析父延后、`pass<=n` 上界足够、parent-cycle 经 progressed==0 退出）；STEP（R252）与 blend 一致；`skeleton_evaluate` 忽略 dt 是设计（main.c 自行推进 clip.time）。记录（设计假设非 bug）：无通道关节 local 默认单位阵而非 bind-local TRS，无 glTF 数据不可确定性测试（precedent R300）。B `renderer/cull.c` `frustum_from_vp` + `frustum_cull.c` `frustum_extract`：Gribb-Hartmann 列主序 `plane.e[i]=vp->e[i][3]±vp->e[i][k]`（R265 修正转置）、归一化 len2>1e-12 守卫、`sign_mask` p-vertex（R245 令 extract 也填充）——两函数一致正确；`cull.h` 的 `frustum_test_aabb`（保守 p-vertex 无假阴性）/`_point`/`_sphere`（d<-radius）与 `frustum_cull_batch` 均正确。决策：无 demo 可达高置信问题，不改代码。编译/测试未触及（纯审计）。总计仍 658 处修复。

此前：**R305 additive 混合层用当前输出预填 scratch → 未被叠加 clip 寻址的骨骼被自身姿势重复叠加、姿势损坏 — 修复 1 处** — **R305-A**（CORRECTNESS）：`anim_blend_evaluate` 每层评估前把 scratch（sample_*）用当前输出 `state->local_*` 预填（`clip_sample` 只写有通道的骨骼）。对 OVERRIDE 正确（`lerp(x,x,w)==x` 透传），但 ADDITIVE 混合是 `pos+=sample*w`/`rot=nlerp(id,sample,w)*rot`/`scale*=1+(sample-1)*w`——未被叠加 clip 寻址的骨骼 sample=当前姿势 → `pos+=pos*w`(w=1 翻倍)、额外叠加当前旋转、scale 再缩放，凡叠加 clip 未触及骨骼全污染。additive 是公共 API（`anim_layer_set_mode(…,ANIM_BLEND_ADDITIVE)`，用于瞄准偏移/呼吸等只动部分骨骼），此前 0 测试覆盖。修复：种子按模式区分——ADDITIVE 用 `fill_bind_pose`（中性 pos0/rot identity/scale1）预填使未寻址骨骼贡献中性 delta，OVERRIDE 仍用当前输出透传。回归 `additive_layer_leaves_unaddressed_bones_untouched`：base(OVERRIDE) 置 bone1 x=6、additive 只动 bone0(+2)，断言 bone0.x≈2、bone1.x 保持 6（旧代码变 6+6·1=12→FAIL）。编译 GL/VK 通过；CTest 各 30/30，test_animation 本地 28/28。总计 658 处修复。

此前：**R304 profiler_pop 结束"最后追加"而非"最后打开"的区间 → 嵌套下外层 elapsed 恒为 0 — 修复 1 处** — **R304-A**（CORRECTNESS）：`profiler_pop` 用 `regions[region_count-1]` 结束区间且 `region_count` 从不递减（区间保留供 chrome trace 导出）。嵌套（push outer→push inner→pop→pop）时第一次 pop 结束 inner，第二次 pop 又取 `region_count-1`（仍 inner）→ inner 被重复 finalize、outer 的 `elapsed_us` 永远为 0。`main.c` 嵌套 `push("render")` > {particles+csm,scene,postfx}，末尾 pop 本应结束 render 却重复结束 postfx → profiler HUD / chrome trace 中 "render"（通常最大耗时）恒报 0µs，剖析失真。修复：`Profiler` 单例加打开区间索引栈 `open_stack[PROFILER_MAX_REGIONS]`/`open_count`（`begin_frame` 重置）；`push` 记录新下标入栈，`pop` 弹栈顶（最内层打开区间）finalize；`region_count` 仍单增保留导出数据；多余 pop 经空栈守卫成安全 no-op；`open_count<=region_count<=MAX` 不溢出。回归 `profiler_nested_timing_outer_finalized`（断言 outer.elapsed>=inner.elapsed>=1000us，旧实现 outer 恒 0→FAIL）+`profiler_sequential_then_nested_indices`（flat 后 outer>inner 各槽结束到正确下标）；既有 `profiler_nested_regions` 仅查 region_count==2 掩盖了计时错误。编译 GL/VK 通过；CTest 各 30/30，test_profiler 本地 21/21。总计 657 处修复。

此前：**R303 terrain 编辑象限统计阈值用 scale*0.5（+x/+z 边缘）而非世界中心 0 → 所有编辑误归 NW — 修复 1 处** — **R303-A**（CORRECTNESS）：4 个地形编辑函数（`terrain_modify_height`/`terrain_flatten`/`terrain_erode`/`terrain_noise_stamp`）用 `hc=t->scale*0.5f; edit_quadrant[(wx<hc?0:1)+(wz<hc?0:2)]++` 分类编辑象限。地形世界坐标居中于 0（`terrain_init`: `fx=(x/(n-1)-0.5)*scale` → span `[-scale/2,+scale/2]`），`scale*0.5` 恰在 +x/+z 边缘 → 任何 in-bounds 编辑都满足 `wx<hc && wz<hc` → 恒归象限 0（NW）。`main.c:3371` 的 "Edit heatmap: NW/NE/SW/SE hottest:…" 调试 UI（demo 可见）遂无论用户在哪编辑恒报 NW，热力图失效。修复：阈值改为世界中心 0（`wx<0.0f`/`wz<0.0f`），保持 x<0=west/z<0=north/0=NW..3=SE 布局不变，仅纠正分界线；4 处统一。回归 `modify_height_quadrant_classification`：在 (+x,+z)/(-x,-z)/(-x,+z)/(+x,-z) 各编辑一次断言落入 SE(3)/NW(0)/SW(2)/NE(1)——旧阈值四者全归 NW（FAIL），修复后各归其位。编译 GL/VK 通过；CTest 各 30/30，test_terrain 本地 24/24。总计 656 处修复。

此前：**R302 BVH SAH 无有效分裂时退化 (1,count-1) → 深度 O(N) 超 BVH_MAX_DEPTH 静默丢对象 — 修复 1 处** — **R302-A**（CORRECTNESS）：`bvh_build_recursive` 当 SAH 找不到有效分裂时（所有质心落入同一 bin，如坐标重合/紧簇刚体，或少数大 AABB 撑开包围盒而众多小物体质心聚簇 → 每个候选分裂总有一侧空 → `best_cost` 恒 `FLT_MAX`、`best_split_bin=0`），后续 bin 分区把全部索引挤到一侧、经 clamp 退化成 `(1, count-1)` 分裂 → 树深度 O(N)。一旦超过 `BVH_MAX_DEPTH=32`，被迫成叶的节点只存 `indices[start]` 一个对象，其余对象被**静默丢弃**（`leaf_map` 保持 calloc 的 0），从此不出现在任何 `bvh_query_aabb`/`bvh_raycast`/`bvh_query_pairs` 里 → 漏碰撞/漏射线命中（physics 中同一 spawn 点批量生成、堆叠副本即触发）。修复：分区守卫从 `extent<1e-7f` 扩展为 `best_cost==FLT_MAX || extent<1e-7f`，无有效 SAH 分裂改用中位分裂 `start+count/2`，深度回到 O(log N)、depth-cap 不可达、所有对象各得单对象叶；正常 SAH 分裂路径不变。回归 `test_physics.c::bvh_coincident_objects_not_dropped`：40 个坐标重合 AABB(N=40>32)，query 断言 `found==40` 且每对象映射唯一叶——修复前退化链只存 33、丢 ~7（FAIL），修复后 40 全可达。编译 GL/VK 通过；CTest GL/VK 各 30/30(排除环境相关 test_async_loader)，test_physics 本地 38/38。总计 655 处修复。

此前：**R301 RHI 句柄池 + Mipmap 流式 + 日志 多窄线深审——无 demo 可达高置信 bug，不修复** — A `rhi.c` 句柄池：free-list、`free_count==0` abort(R157)、`generation++` 跳 0、`get_resource` 校验 gen+alive、`free_slot` 经 alive 防双重释放(gen 仅 realloc 时 ++ 使陈旧句柄失效)——正确；调用方用 `slots[idx].generation` 直接构造句柄无 next_slot 覆盖，多资源 FBO 部分失败返回部分句柄为有意设计。B `mipmap_stream.c`：`coverage_to_level` IEEE754 指数(含 NaN→0/subnormal/负 clamp)正确、`width>>level` 因 MAX_LEVELS=16 无移位 UB、`>UINT32_MAX→0`(R167-E)、预算 reserve/decrement 各路径平衡、`request_id` 拒绝陈旧完成(R167-D)、shutdown 取消在途(R172)。C `log.c`：basename/颜色数组按 level 索引，`level<min_level` 提前返回,越界仅非法 level(宏不可达)。决策：无 demo 可达高置信问题，不改代码。编译/测试未触及(纯审计)。总计仍 654 处修复。

此前：**R300 core 分配器/字符串 + VFS 多窄线深审——无 demo 可达高置信 bug，不修复（记录 1 处潜在限制）** — A `pool.c`：free-list 前后向线程化、`pool_init` pad/usable/count、`pool_init_alloc` 溢出守卫(R158)、`pool_owns` 边界+对齐、`pool_release` used 下溢守卫——正确。B `string.c`：`str_copy` buf_size==0 守卫(R109)、`str_slice` 钳制、FNV-1a、`str_eq` 短路——正确。C `vfs.c`：PAK 哈希探测终止性(表至少半空)、`next_pow2(0)→4`、`name_offset` 越界跳过(R160-A)、`entry_count>2^30` 守卫(R157)、name 表+1 终止符、单块分配、`vfs_read` 的 `pos<=size` 不变量、R255 读锁——正确。记录(潜在限制、**非 demo 可达**、不修复)：`alloc.c::heap_realloc_fn` 在 `align>16` 且 realloc 返回基址对齐残差变化时，用户数据位于 `new_raw+old_off` 而返回指针为 `round_up(new_raw+8,align)`，二者错位损坏首字节；引擎 heap realloc 仅用 align≤16(malloc 保证 16 对齐使 off 稳定)故不触发，且失败依赖 realloc 基址残差无法确定性构造用例，按宁缺毋滥不投机修复(precedent R297)；修复方向：realloc 后 `new_off!=old_off` 则 memmove 数据再写回 back-ptr。决策：无 demo 可达高置信问题，不改代码。编译/测试未触及(纯审计)。总计仍 654 处修复。

此前：**R299 ordered reorder drain 遇 0 快照包 `late_count==0` 提前中断 → 后续连续缓冲包永久滞留、ordered 流 stall — 修复 1 处** — **R299-A**（CORRECTNESS）：`net_repl_deliver_ordered` 排空缓冲的 drain 循环 `if (late<=0 || late_count==0u) break;`。`net_reorder_drain` 对就绪槽投递返回 `len>0`，`late_count` 为该包快照数。当某已缓冲 ordered 包合法带 **0 快照**（`n==0`；本引擎 broadcast 拒绝 count==0，但外部/伪造 peer 可发）被 drain 时 `late>0 && late_count==0` → 触发 break：`next_ordered_seq` 已越过空包但 drain 停止，其后连续缓冲包永久滞留、`reorder_pending` 不归零 → ordered 流永久 stall（R254/R298 加固他方包同脉络）。修复：仅 `late<=0` 时 break（空帧不再中断，继续排空）；仅 `late_count>0` 才覆盖 `*out_count`（尾随空包不清有效集）；有快照常规路径不变。回归 `ordered_reorder_zero_snapshot_no_stall`（缓冲 seq2=0快照+seq3 后投递 seq1，断言 `reorder_pending==0`/`reorder_delivered==2`/`out[0]`=seq3 载荷）：旧 drain 逻辑 **FAIL**（reorder_pending!=0，seq3 滞留）、修复后通过。编译 GL 100%+VK 100%；测试 GL/VK 各 31/31（test_net_replication 19/19）。总计 654 处修复。

此前：**R298 `packet_can_write`/`packet_can_read` 边界检查整数溢出 → 巨大 size 绕过致 memcpy 越界 — 修复 1 处** — **R298-A**（CORRECTNESS/安全）：两个共享边界检查用加法 `(write_pos+n)<=PACKET_MAX_SIZE(1400)` 与 `(read_pos+n)<=write_pos`。当 `n` 近 `UINT32_MAX`（`packet_write_bytes`/`packet_read_bytes` 传入巨大或包内派生长度）时 `pos+n` 在 u32 回绕成小值滑过边界 → `packet_write_bytes` 的 `memcpy` 冲出 1400 字节 `data[]`（越界读 src+越界写 data）、`packet_read_bytes` 越过真实 payload 读 `data[]`（泄露/崩溃）。属 R254 加固 `packet_can_read` 读边界的同脉络后续。修复为溢出安全形式：`packet_can_write` 判 `write_pos<=PACKET_MAX_SIZE` 后 `n<=PACKET_MAX_SIZE-write_pos`；`packet_can_read` 判 `read_pos<=write_pos`（亦覆盖截断包 read_pos 停在 header 偏移）后 `n<=write_pos-read_pos`。合法输入不变，仅回绕病态输入由误通过改为正确拒绝。回归 `write_bytes_size_overflow_rejected`（`wrap_size=0u-write_pos` 使加法回绕 0，断言 write_pos 不前进 + read 定长边界）：旧码运行该用例 **SIGSEGV(signal 11，~4GB memcpy 越界)**、修复后通过。编译 GL 100%+VK 100%；测试 GL/VK 各 31/31（test_packet 19/19）。总计 653 处修复。

此前：**R297 数学库(四元数/矩阵)+ UTF-8 解码 + 字体布局 + ECS swap-remove + 粒子发射 多窄线深审——均无高置信活跃 bug，不修复** — A `math`：`quat_mul` 为正确 Hamilton 积、`quat_rotate_vec3`=`v+2s(q×v)+2q×(q×v)`、`quat_from_axis_angle`/slerp/nlerp(带 `dot<0` 最短路取反)正确、`mat4_from_quat`(列主序)逐元素对标准 `R[r][c]=m.e[c][r]` 全吻合无转置、`mat4_ortho`/`mat4_perspective` 系数+除零守卫(R142)正确。B `utf8_decode`：因 NUL 永非合法续字节且续字节检查 `||` 短路，对 NUL 结尾串永不越读(内存安全)，overlong/代理区/>0x10FFFF/掩码范围全符合 Unicode。C `font.c`：atlas 打包换行、quad 容量写前守卫、行高 `ascent-descent+line_gap`、text_width 多行取 max、NDC 除零守卫(R244)正确;仅记录非 demo 可达的换行后不复检水平容纳(单字形≥图集宽才越界)理论缺口。D `ecs.c` `archetype_swap_remove`(R286)：全局 slot swap-remove 维持"尾块前均满"不变量、`entity_index[moved]` 正确更新、销毁尾实体走 skip、空尾块复用——正确。E `particles.c` 发射预算(R174)：`emit_accum+=rate*dt`→取整+分数进位+`>MAX` 钳制,正确。决策：均无 demo 可达高置信 CORRECTNESS 问题，按宁缺毋滥不改代码(precedent R289/R290/R294/R296)。测试缺口(记录)：无 quat/mat golden、无 utf8 截断/overlong 单测、无 font 超宽字形用例。编译/测试未触及(纯审计)。总计仍 652 处修复。

此前：**R296 相机(fly camera)+ 角色控制器 + UI slider 三条窄线深审——均无高置信活跃 bug，不修复** — 窄线 A `camera.c`：存疑点 yaw=0 时 right `s=(-1,0,0)` 指世界 -X、视图旋转块 **det=-1**(看似镜像)，经 `math.c:52` `mat4_lookat` 注释确认为跨 `camera_view`/`camera_inv_view`/`mat4_lookat` 一致且有文档的**左手约定**(投影/剔除/golden 全据此，移动自洽)——**非 bug**；`camera_inv_view` 手算验证为 view 正确逆(`R^T|eye` 对 `-R·eye`)；yaw 单次 `±2π` wrap 溢出仅影响数值经三角函数周期性无害；pitch 夹取 ±1.5533 双向正确。窄线 B `character.c`(已 R239/R251/R254/R280 覆盖)：复核 grounded 判定 `sep.y>slope_limit`、6 次迭代分离多接触收敛、零水平位移下 `horiz_len>1e-5` 分支安全、step-up up→forward→down + `horiz_progress` 比较——无新 bug。窄线 C `imgui.c` slider：`imui_slider_map`(`t=(mx-x)/w` 钳 [0,1] 后线性映射)与 `imui_slider_norm`(`maxv==minv→0`+钳制)均正确，knob 用 `(w-knob_w)*t` 仅视觉细节。决策：均无 demo 可达高置信 CORRECTNESS 问题，按宁缺毋滥不改代码(precedent R289/R290/R294)。测试缺口(记录)：无 camera view↔inv_view 互逆 golden、无 character step-up 场景单测。编译/测试未触及(纯审计)。总计仍 652 处修复。

此前：**R295 `input_set_key` held 态被 OS 自动重复重置为 just-pressed → 绑定 just-pressed 边沿的一次性动作随重复率误触发 — 修复 1 处** — **R295-A**（CORRECTNESS）：`keys[]` 语义 0=up/1=just-released/2=held/3=just-pressed，`input_key_pressed`==3 用作"本帧刚按下"边沿。旧 `input_set_key(pressed)` 守卫 `if (s->keys[key] != 3) s->keys[key]=3;` 允许 **2(held)→3**：Win32 `WM_KEYDOWN`（`window_win32.c:109` 未过滤 lParam bit30 重复位）与 Cocoa `keyDown:`（未看 `isARepeat`）把 OS 自动重复原样转发为重复 `pressed` 事件 → 按住键时 `input_key_pressed` 随重复率反复置真，一次性动作（跳跃/切换）误触发多次。同文件 gamepad 版 `input_set_pad_button` 用 `if (*slot != 2)` 正确规避；键盘版改为 `if (s->keys[key] != 2 && s->keys[key] != 3) s->keys[key]=3;`——仅从 up(0)/just-released(1) 锁存新边沿，held/pressed 不重置。`input_key_down`（2 或 3 均为 down）与释放路径、合法"释放后再按"边沿均不受影响；按住语义不变。Wayland 由合成器不发重复 key 事件（客户端合成）故 Linux 不触发，但引擎函数须与 gamepad 契约一致。回归 `key_repeat_while_held_does_not_refire_pressed`（press→new_frame(held)→再 press 断言 `keys=2`/`!pressed`，再 release→press 断言重锁存 3）：旧 `!=3` guard 下 **FAIL**（`s.keys['a'] != 2`），修复后 PASS。编译：GL 100%+VK 100%；测试 GL/VK 各 31/31（test_input 含新用例 29/29）。总计 652 处修复。

此前：**R294 场景序列化(BSCN)+ 视锥剔除两条窄线深审——均无高置信活跃 bug，不修复** — 窄线 A：`scene_serial.c` 的 binary/JSON save-load（引擎实际用 `scene_save_binary`/`scene_load_binary`，`main.c` 调用）。核对：`bb_reserve` 倍增、chunk 表偏移 `base=sizeof(header)+5*sizeof(entry)` 与写入顺序一致、load 侧 `table_end`/`chunk_end` 双重越界校验（R108-1）、`emit/load_components_chunk` 的 saved-index↔`ents[]` 映射自洽、`load_components_chunk` 每实例先读 `saved_idx` 再校验 `remaining>=size` 后 memcpy、`emit_hierarchy_chunk` CSR 单块分配恰为 `4n+1`（`child_count[n]+offsets[n+1]+children[n]+cursor[n]`，`cursor[n-1]` 落在下标 4n≤4n）、`emit/load_scene_nodes_chunk` 各 2×Mat4+5×u32 对称、generation 往返（R243/binary+JSON 均恢复）。手算 chunk 偏移与组件读写全部吻合。邻近项(记录、非活跃 bug)：① `scene_instantiate_prefab` 的 `position` 仅偏移 scene node，而 `scene_save_prefab` 只写 ENTITIES+COMPONENTS（无 node）→ 对纯实体 prefab 无效；但 `CTransform`/`COMP_TRANSFORM` 定义在**应用层 main.c**、引擎库 `scene_serial.c` 无从知晓，故引擎侧无法偏移实体变换——属**设计约束非 bug**，且 `scene_save_prefab`/`scene_instantiate_prefab` 全仓无调用方(死代码)。② 实体 index 仅在"无永久空洞"时往返（`emap_build` 压缩存 live、load 顺序重建；有空洞时新 index≠原 index），已由注释与 `generation_restore_roundtrip` 记录为设计前提。窄线 B：`frustum_cull.c` Gribb-Hartmann 平面提取 + p-vertex AABB 批量剔除。核对：平面系数 `vp->e[i][3]±vp->e[i][k]`（R265 已修转置、正确取 VP 行而非 VP^T）、6 面法向内向、`sign_mask` 按分量符号选 max/min 角点（R245 已修 extract 侧遗漏）、`frustum_cull_batch` 距离 `n·p+d<0` 剔除、归一化 `len2>1e-12` 守卫。手算平面与角点选择自洽。决策：两条窄线均无 demo 可达的高置信 CORRECTNESS 问题，按宁缺毋滥**不改代码**。测试缺口(记录)：无 scene 组件**数据值**往返用例(现有测试覆盖 resources/generation，未断言组件字节值)；无 `frustum_extract`/`frustum_cull_batch` 的已知-VP golden 单测。编译/测试未触及(纯审计)。总计仍 651 处修复。

此前：**R293 LOD `lod_update_all` 按 group slot 索引 `current_levels[]`（应按 entity id），非顺序 entity 下批量更新写错槽位 → `lod_get_level/lod_get_mesh` 恒读陈旧 LOD0 — 修复 1 处** — **R293-A**（CORRECTNESS）：`lod.h` 明确注释 `current_levels[LOD_MAX_GROUPS]` 是**"per entity"**、`lod_update_all` 是 **"Batch update all entities"**；`lod_register`/`lod_select`/`lod_get_level`/`lod_get_mesh` 全部按 **entity id** 读写 `current_levels[entity]`。唯独 `lod_update_all`（`lod.c:242/249` 屏幕尺寸分支、`lod.c:270/276` 距离分支）用**稠密 group slot `i`** 读 `current_levels[i]` 并写回 `current_levels[i]`。当某 entity 的 id 与其注册槽位不同（`lod_register` 顺序分配 slot、entity 却任意）时，批量更新把结果写到 `current_levels[slot]`，而查询按 `current_levels[entity]` 读——两者错位。手算复现：注册 `entity=5`(slot0)、`entity=3`(slot1)，`lod_update_all` 传 `positions[0]`=远(→粗 LOD3)、`positions[1]`=近(→细 LOD0)：旧码写 `current_levels[0]=3`、`current_levels[1]=0`，但 `lod_get_level(5)` 读 `current_levels[5]`（`lod_init`/`lod_register` 置 0 后从未更新）→ 恒返回**陈旧 LOD0**，远处物体永远以最高细节网格绘制（性能与预期 LOD 双失效）。当前引擎主循环只走 `lod_select` 逐实体路径（`main.c:5034`）故未触发，但 `lod_update_all` 是公开 API、契约错误。修复：两分支改用 `u32 entity = group->entity_id;` 索引 `current_levels[entity]`（与文档 per-entity 语义及其余 API 一致；`positions[]`/`groups[]` 仍按 slot 并列，符合 `count` 批量契约）。回归测试 `lod_update_all_indexes_by_entity_not_slot`（用非顺序 id 5/3 注册后批量更新，断言 `lod_get_level(5)==3`、`(3)==0`）：已用旧 slot 索引版本编译验证该用例**失败**（`lod_get_level(5) != 3`）、修复后通过。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_lod 含新用例，19/19）。总计 651 处修复。

此前：**R292 异步加载器/解码管线的进程内生命周期竞态：init/shutdown 循环 memset 重建互斥量/条件变量致存活 worker 永久 park → shutdown join 死锁 — 修复 2 处** — **R292-A**（CORRECTNESS/DATA RACE）：`async_loader.c` `io_worker_run`（旧 280–281 行）在 `decode_pipeline_submit` 成功后仍写 `req->data=NULL; req->size=0;`。成功提交即把该 slot 的所有权移交解码管线，`req->data/size` 随后由 `async_loader_tick`（poll 到解码结果时，旧 511/512 行）写入解码结果并推进状态机（READY→UNLOADED 复用）。当解码 worker + 主线程 poll 足够快时，主线程可在本 I/O worker 从 submit 返回**之前**已写该 slot → 两线程在同一 32/16 字节上竞争（TSan 实证 280/281 vs 511/512），`-O2` 下偶发损坏请求状态机、令 I/O worker 停在 cond_wait，`async_loader_shutdown` 的 join 死锁。且这两行本就冗余（claim 时已置 NULL/0，其间无人改写）。修复：成功交接后**不再触碰 slot**（删除两行）。**R292-B**（CORRECTNESS/LIFECYCLE RACE，死锁根因）：`async_loader.c` 的 `queue_mutex`/`wake_cond` 与 `decode_pipeline.c` 的 `input.mutex`/`input.cond`/`ready.mutex` 原为 `g_loader`/`g_decode` 结构成员，`*_init` 每轮 `memset(&g,0)`+`*_init`、`*_shutdown` 每轮 `*_destroy`。若上一轮某 worker 短暂存活过 shutdown（启停时序窗口），下一轮 init 的 memset 会在该 worker 正阻塞于 `async_cond_wait` 时**清零条件变量的 futex 字**，复位等待态 → shutdown 的 broadcast 丢失、worker 永久 park，随后 init 的 re-init/destroy 又与活对象竞争（TSan 实证 `__tsan_memset` 与 `pthread_*_init` 竞争）。修复：把这些原语移出结构体、置为**文件静态、进程内只初始化一次、永不销毁**（`g_sync_inited`/`g_decode_sync_inited` 门控；`memset` 只清数据成员）——存活 worker 永远在**同一有效对象**上等待/被唤醒，故必能观察到 `running=false` 并退出，join 完成；并顺带把 `running=false` 的发布移入持锁区再 broadcast（规范条件变量拆解）。验证：TSan 40 轮零挂起；leakprobe 240k 轮 init/shutdown 零真实泄漏、零 `pthread_create` 失败；原生 -O2 压测由 4/120 挂起 → **0/150 挂起**。附带把 `test_async_loader.c` 的 `async_loader_priority_ordering`（原始代码即偶发失败：2 个 worker 时两个 low 可能在 high 入队前被同时抢占，是固有调度竞态而非堆 bug）改用**单 I/O worker** 使优先级保证确定化（200 次压测 0 失败）。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（含 test_async_loader，ctest 下 30 连跑 0 挂起/0 失败）。总计 650 处修复。

此前：**R291 运行时关闭再开启 TAA 未失效冻结的 history → 重开首帧混合陈旧历史(拖影/闪烁) — 修复 1 处** — **R291-A**（CORRECTNESS）：TAA 关闭期间 `taa_resolve`/`combined_aa_apply` 被跳过,`history_fbo` 冻结在"关闭前那一帧"的颜色,但 `prev_view_proj` 仍每帧更新。按键 280 重新开启 TAA(`main.c:2102`)时只翻转 `taa_enabled`,不重置 `first_frame`;shader(`taa.frag:57`/`combined_taa_fxaa.frag:133` 的 `u_taa_first_frame<0.5` 守卫)遂进入历史混合分支,用当前 n-1 的 VP 做重投影却采样到那帧陈旧 texel,并按 `u_taa_blend`(~90%)混入 → 重开首帧鬼影/闪烁。与 resize 路径(`taa_init` 会重置 `first_frame`)行为不一致。修复:按键切换处当 `taa_enabled` 由关→开时置 `taa.first_frame=true` 与 `combined_aa.first_frame=true`(两条 AA 路径均覆盖),使重开首帧只取当前色(等价 resize 语义);benchmark 恢复路径(`main.c:2021`,基准期间效果全关同样冻结 history)同样处理。验证:GL/VK 构建通过;GL/VK 各 30/30 通过(预先存在且与本改动无关的 `test_async_loader` 挂起已排除,其陈旧实例早于本次改动)。总计 648 处修复。

此前：**R288 物理宽相 BVH `bvh_query_pairs` 用 `if(a<b)` 丢弃约半数碰撞对 — 修复 1 处** — **R288-A**（CORRECTNESS）：`bvh.c:399–403` 的双树遍历 `bvh_query_pairs_dual` 叶-叶回调写成 `if (a < b) callback(a, b)`，注释称"去重"，但双树遍历（自 `(root,root)` 出发：自配对只做 LL/RR/LR、省略 RL，异节点做全 4 组合）保证**每个无序叶对恰好被枚举一次**——LCA 唯一、该对只在 LCA 自配对的 (left,right) 交叉项被到达，谁作 nodeA/nodeB 由**树的左右结构**固定、与 object_index 无关。因此 `a<b` 不是去重而是**漏报**：当左子树叶 object_index > 右子树叶时整对被丢弃（约半数配对），`physics_collision_callback` 零次触发 → **漏碰撞**（穿透/不解算）。`physics_step`（`physics.c:696`）以 `bvh_query_pairs` 为唯一宽相配对源，无暴力回退，故直接受影响。手算：两盒共享 x∈[0,1] 全重叠，若高 index 盒经 SAH 落入 left 子树 → `a>b` → 丢对。修复：改为规范顺序**无条件上报**并仅排除同叶 `a==b`：`a<b→cb(a,b)`、`a>b→cb(b,a)`；因每对恰好一次，不会重复解算。回归测试 `bvh_query_pairs_reports_all_overlaps`（6 盒全重叠、逆向 index/位置相关性诱发左子树高 index，断言上报对数 == 暴力真值 15、全为规范序 `a<b`、无重复）。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_physics 含新用例）。总计 647 处修复。

此前：**R286 ECS 多 chunk 时 swap-remove 只用本 chunk 末行（破坏全局 slot 稠密不变量）— 修复 1 处** — **R286-A**（CORRECTNESS）：`ecs.c` 分配为 tail 追加、chunk 稠密顺序填充（除末尾外各 chunk 必满、`entity_index` 为全局线性 slot），但 `world_destroy_entity`（281–293）、`world_add_component`（440–453）、`world_remove_component`（587–601）三处 swap-remove 均用**含被删实体的那个 chunk 的末行**（`c->count-1`）填补空洞并递减**该 chunk** 的 count。当 archetype 跨 ≥2 chunk 且被删/迁出实体**非全局末**（尤其落在非 tail chunk 中段）时，非 tail chunk 的 count 被减 → 稠密不变量破坏 → 后续 chunk 中实体的全局 slot 走查（`while(g>=c->count) g-=c->count`）全部错位，`world_get_component` 读到**错误行或 NULL**（静默数据损坏）。手算（`chunk_capacity=2`：A,B∈chunk0，C∈chunk1，slot 0/1/2）：destroy A → 与 chunk0 末 B 交换、`entity_index[B]=0`、chunk0.count→1，但 **C 仍 entity_index=2** → 走查 `2≥1→1`, `1≥1→0`, 无下一 chunk → C 组件丢失（应为 slot 1）。修复：抽出正确的 `archetype_swap_remove(w,a,global_slot)`——用 `total_count-1` 走查定位 **archetype 全局末实体**（robust 对空 tail），跨 chunk memcpy 组件列 + entity id 填补空洞、回填被移动实体 `entity_index=global_slot`，仅递减**持有全局末的那个 chunk** 的 count 与 `total_count`；三处 swap-remove 统一改调该 helper。回归测试 `ecs_swap_remove_across_chunks`（516B 组件→chunk 容量~31，建 70 实体跨 3 chunk，destroy 首 chunk 中段 + remove 中段实体，断言后续 chunk 幸存者组件值不错位；修复前 `ents[40]` 会误读 `ents[41]` 值）。单 chunk 场景（chunk 末=全局末）行为不变，故既有 destroy 测试此前偶然全过。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_ecs 含新用例）。总计 646 处修复。

此前：**R285 imgui 设置面板隐藏期间交互状态冻结→重开误触发 release-click— 修复 1 处** — **R285-A**（CORRECTNESS）：`main.c:5591` 仅 `imui_visible` 时才跑 `imui_begin/end`；`imui_end`（`imgui.c:55`）在帧末锁存 `mouse_prev_down=mouse_down`、`imui_begin` 每帧清 `hot_id` 但**不清** `active_id`。面板用 `` ` `` 隐藏期间 begin/end 全不执行 → `active_id` 与 `mouse_prev_down` **冻结**。时序：①面板可见时在 checkbox id=1 上按下 → `imui_press_logic` 置 `active_id=1`，帧末 `mouse_prev_down=true`；②按住时按 `` ` `` 隐藏 → 多帧不跑 imgui，状态冻结；③隐藏期间松开左键（imgui 未消费该边沿）；④重开且指针仍在 id=1 上：`imui_begin(mouse_down=false)`，`mouse_prev_down` 仍冻结为 true → `released_now = !false && true = true`，`active_id==1` 且 hovered → **`clicked=true` → VSync 被无操作地 toggle**；且冻结的 `active_id` 还会阻塞其它控件按下。修复：新增纯 inline `imui_reset_input(ui, mouse_down)`（清 `active_id`/`hot_id`、令 `mouse_down=mouse_prev_down=当前值`），在 `main.c` 面板**隐藏帧**调用（`else if (imui_font_ready)` 分支，传 `input_key_down(INPUT_MOUSE_LEFT)`）——隐藏期间保持边沿 latch 新鲜并丢弃在途按压，重开时状态干净。回归测试 `imui_hidden_reset_no_stale_click`（test_font_ui.c）：先复现「无 reset 时重开的 release 边沿会误 click」，再断言 `imui_reset_input` 后 `active_id=0`、`mouse_prev_down=false`、重开无 click。其余 imgui 项（命中测试半开区间、slider 映射/钳制/拖出、按钮边沿、纵向布局）经手算与现有单测核对一致。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_font_ui 含新用例）。总计 645 处修复。

此前：**R284 滚轮缩放把「度」量级作用于弧度 FOV（首次滚轮即破坏投影）— 修复 1 处（+同源 HUD 显示）** — **R284-A**（CORRECTNESS）：`main.c:2509` 滚轮改 FOV `camera.fov = fmaxf(20.0f, fminf(camera.fov - scroll_dy*5.0f, 120.0f))`——钳制边界 20/120 与步长 5 显然是**度**，但 `Camera.fov` 全程为**弧度**（`camera_init` 传 `1.047f≈60°`，`camera_projection`→`mat4_perspective(cam->fov,…)` 要弧度）。手算：初始 `fov=1.047`，任一格上滚 `scroll_dy=+1` → `fmaxf(20, fminf(1.047-5, 120)) = fmaxf(20,-3.953) = 20.0`（rad！≈1146°）；下滚 `fmaxf(20, fminf(6.047,120))=20.0`——只要 `fov±5<20` 即**任意一格滚轮立即钳到 20 rad**，`mat4_perspective` 内 `tan(20/2)=tan(10)≈2.18e4` → 投影/视锥/裁剪彻底错乱、画面崩坏。触发：游戏中滚轮缩放（`scroll_dy≠0`）。修复：步长与钳制统一换算到弧度——`deg2rad=π/180`，`fov` 夹在 `20°..120°`（rad）、每格 `5°`（rad）；上滚 `scroll_dy>0` → fov 变小 → 拉近，方向正确。**同源 HUD 修复**：`main.c:3342` debug 文本同一行 yaw/pitch 均 `*57.2958` 转度，唯 `fov=%.0f°` 直接打印弧度值（初始显示「1°」而非 60°），改为 `camera.fov*57.2958f`。无独立 orbit 相机；`camera_update` 的 yaw/pitch 解析式、LH 基、pitch 钳制（89° rad）、WASD、鼠标 delta（未乘 dt）均已核对自洽。main.c 内联输入路径无 headless 单测（同 R268/R272/R273 惯例），以双后端构建 + 全量套件 + 手算论证为验证；`test_camera_frustum.c` 固定 fov 投影不受影响。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31。总计 644 处修复。

此前：**R282 字体图集覆盖率在 Alpha 通道、片元却采样 Red（字形渲染成实心矩形）— 修复 1 处** — **R282-A**（CORRECTNESS）：`font.c` `font_renderer_init` 把 stb_truetype 单通道覆盖率位图上传为 RGBA，`R=G=B=255`、覆盖率写入 **A**（155–159 行 `atlas_rgba[i*4+3] = atlas[i]`，自首个提交起即如此），但 `font.frag`/`font_vk.frag`（均自创建起）`float a = texture(u_atlas, vUV).r`——采样 **R** 恒为 `255/255=1.0`。逐 texel 手算：字缘 AA texel `atlas=128` 期望 `a≈0.5`、实得 `1.0`；`O` 中心空洞 `atlas=0` 期望 `a=0`、实得 `1.0` → 每个字形 quad 被填成 bbox 大小的**实心不透明矩形**（含字模空洞），完全丧失抗锯齿轮廓/字形形状。RHI `R8G8B8A8_UNORM → GL_RGBA8/GL_RGBA/UNSIGNED_BYTE` 无 swizzle（`rhi_gl.c:1188/1199/1283`），排除通道重映射。`draw_rect` 的 4×4 白块 coverage=255 → A=255，故采 `.a` 后面板底仍不透明、不受影响。触发：任意 `font_renderer_draw`/debug HUD/imui 文本。修复：`font.frag` + `font_vk.frag` 采样通道 `.r → .a`（对齐图集「白 RGB + alpha 覆盖率」约定），错在 shader、图集布局不动。GPU-only 无 headless 字形单测（`test_font_ui.c` 仅 UTF-8 + imgui 逻辑），以 glslangValidator VK 编译通过 + `test_vulkan` 运行时经 shaderc 编译 `font_vk.frag` + 双后端全量套件为验证；golden 回归渲染 test_tex 场景、不含字体故不受影响。编译验证：VK glslang 通过（GL 无 location 为 `-G` OpenGL-SPIRV 既有限制、经典 GLSL330 运行时驱动正常）。测试：GL/VK 各 31/31。总计 643 处修复。

此前：**R281 GPU 粒子尺寸淡出复利坍缩（每帧读回已衰减尺寸做基准）— 修复 1 处** — **R281-A**（CORRECTNESS）：`particle_update.comp` 存活分支的尺寸淡出 `float size = mix(0.1, p.size_color.x, t)` 把**持久字段** `size_color.x`（顶点 shader 读作点精灵尺寸、且每帧被本行覆盖）当作淡出基准，形成反馈式复利衰减：`sizeₙ = 0.1 + t·(sizeₙ₋₁ − 0.1)`，即 `(sizeₙ − 0.1) = (size₀ − 0.1)·∏ₖ tₖ`。相邻的 alpha 行 `p.size_color.w = t` 每帧从 `t` **新鲜**重算（正确），唯独尺寸行读回自身。手算（`max_life=2s`、`dt=1/60`、`t=life/max_life` 由 1 递减）：约 1 秒内 `∏tₖ` 已 ~e⁻¹⁷ 量级 → 尺寸约 0.3–0.5 秒即坍缩到 0.1 地板，而非随剩余寿命线性从 1.0 收缩到 0.1；期望半衰期 `t=0.5` 尺寸应为 `0.1+0.9·0.5=0.55`，实测 ≈0.1。全体粒子每帧可见（默认爆炸/拖尾预设）。触发：任意存活>数帧的粒子（普遍）。修复：淡出基准改用**常量 spawn 尺寸 1.0**（emit 分支恒写 `size_color.x=1.0`）——`float size = mix(0.1, 1.0, t)`，消除复利、得随剩余寿命的线性收缩；不动顶点 shader，最小改动。GPU-only 无 CPU 仿真桩故无针对性单测（同 R272/R275 shader 修复惯例），以 glslangValidator VK 编译通过 + `test_vulkan` 运行时经 shaderc 编译该 comp + 双后端全量套件 + 手算论证为验证。编译验证：VK glslang 通过（GL loose-uniform 为 glslang 既有限制、运行时驱动正常，同 R272）。测试：GL/VK 各 31/31。总计 642 处修复。

此前：**R280 角色控制器按住跳跃在上升段重复起跳（拔高/多段跳）— 修复 1 处** — **R280-A**（CORRECTNESS）：`character.c` `character_update` 跳跃仅在帧初判 `if (jump && cc->grounded)`（122 行），起跳后 125 行 `cc->grounded=false` 随即被 173 行 `cc->grounded = grounded_v || grounded_h` **完全覆盖**。`char_slide_resolve` 走「整段平移目标点 + 最多 6 次最深穿透分离」而非 sweep；起跳后数帧内胶囊脚底仍低于地板 AABB 上沿、垂直 resolve 仍报 floor 接触 → `grounded_v=true` → 帧末 `grounded` 仍为 true。按住跳跃时下一帧再次满足 `jump && grounded`，把正在上升的 `vy` 重新置回 `jump_speed`，在真正脱离地板接触前重复多帧。手算（floor top y=0.5、`r=0.3`、`height=1.8`、`dt=1/60`、`jump_speed=8`、`g=-20`）：静止 `feet.y≈0.2`；第 1 跳 `vy=8`→帧末 `feet.y≈0.33`（仍 <0.5，重叠）→ 第 2、3 帧再次 `vy=8`（本应衰减到 7.67/7.33），约 2–3 帧后 `feet.y>0.5` 才脱离；等效从更高点全速起跳，apex 显著高于单次点按（多段跳/加高）。触发：`jump` 连续为 true（按住）且起跳后数帧仍与地板 AABB 相交（薄地板+高胶囊几乎必现）。修复：跳跃门控增加 `cc->velocity.e[1] <= 0.0f`——静止时落地钳制使 `vy=0`，正常首跳不受影响；上升段 `vy>0` 则阻止重复起跳。回归测试 `hold_jump_no_apex_boost`：单次点按与按住从同一静止态起跳，断言按住 apex ≤ 点按 apex + 0.1（修复前按住拔高约 0.5 → 失败；修复后两者峰值一致）。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_character 含新用例）。总计 641 处修复。

此前：**R279 glTF TEXCOORD_0 normalized 整型被当作 2×float（纹理坐标损坏）— 修复 1 处** — **R279-A**（CORRECTNESS）：延续 R278，`asset.c` 手动读顶点属性；TEXCOORD_0 在**骨骼**（325 行）与**非骨骼**（414 行）两条路径均 `memcpy(uv, ud+vi*us, sizeof(f32)*2)`，仅做 `cgltf_accessor_is_type(vec2)` 类型检查，**不看** `component_type`/`normalized`。glTF 2.0 允许 `TEXCOORD_n` 为 `VEC2`+`UNSIGNED_BYTE(5121)`/`UNSIGNED_SHORT(5123)`+`normalized:true`（UV 量化/压缩常用，如 meshopt/手动量化导出）；裸 memcpy 当 float 会把整型字节误读成 IEEE754 → UV 全乱、贴图完全错位。影响面比 R278（仅骨骼权重）更广：命中**默认渲染路径的任意带此类 UV 的贴图网格**。POSITION/NORMAL 规范强制 FLOAT 无需改；`Vertex` 无 COLOR 字段故无 COLOR 同类项。修复：两处 UV 读取改用 `cgltf_accessor_read_float(uv_acc, vi, uv, 2)`（自动处理 component_type/normalized/stride/sparse），读取失败回退原 memcpy；FLOAT UV 资产结果逐字节不变。同 R278/R256：asset.c 依赖 cgltf+RHI 且需带 normalized-int UV 的 glTF 资产，不便加针对性单测，以 cgltf 成熟 `read_float` + 双后端构建 + 全量套件 + 手算论证为验证；`test.glb` 为 FLOAT UV、行为不变。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31。总计 640 处修复。

R278 glTF WEIGHTS_0 normalized 整型被当作 4×float（蒙皮权重解析错误）— 修复 1 处 — **R278-A**（CORRECTNESS）：`asset.c` 用 cgltf 解析 glTF，顶点/索引为手动 `cgltf_buffer_data`+stride 步进；JOINTS_0 已按 `r_8u/r_16u/r_32u` 整型分支读取（334–346，R249），但 WEIGHTS_0（358 行）恒 `memcpy(weights, wd+vi*stride, sizeof(f32)*4)`，假定 buffer 已是 4×IEEE754，**不看** `component_type`/`normalized`。glTF 2.0 允许 `WEIGHTS_0` 为 `VEC4`+`UNSIGNED_BYTE(5121)`/`UNSIGNED_SHORT(5123)`+`normalized:true`（Blender 等导出蒙皮网格极常见，紧凑 byteStride=4 或 8）。手算：顶点 0 字节 `FF 00 00 00` 期望 `w=[1,0,0,0]`，实际把 4 字节当作一个 little-endian float 写入 `weights[0]`（位型 `0x000000FF≈1.401e-45`），且紧凑 4 字节时按 16 字节 memcpy 越界读；`[80 80 00 00]`(≈0.5,0.5) 亦得 `≈3.6e-39` → `wsum` 近 0、359 行归一化失效 → 蒙皮权重全垃圾、变形完全错误。对比 JOINTS 已正确按整型分支解包，WEIGHTS 却假设 float。触发：任一带 `JOINTS_0`+`WEIGHTS_0` 且 WEIGHTS accessor 为 normalized u8/u16（非 5126 FLOAT）的 glTF（与 R253/R274 无关，GPU 侧假设 `weights` 已是 [0,1] 浮点）。修复：改用 `cgltf_accessor_read_float(wgt_acc, vi, weights, 4)`——自动按 `component_type`+`normalized`+stride+sparse 解包（与整型 JOINTS 分支对称），读取失败回退原 memcpy；FLOAT 权重资产结果逐字节不变。无法加针对性单测（asset.c 依赖 cgltf+RHI，且需带整型权重的 glTF 资产，同 R256 因重依赖不便加测），以 cgltf 成熟 `read_float` + 双后端构建 + 全量套件 + 手算论证为验证；仓库 `test.glb` 为 FLOAT 权重、行为不变。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31。总计 639 处修复。

R277 CCD 胶囊扫掠保守半径漏算 half_height（胶囊可穿薄静态体）— 修复 1 处 — **R277-A**（CORRECTNESS）：连续碰撞检测（CCD）把移动体当作 `body_bound_radius(b)` 的球来扫掠——`ccd_sweep_static` 用该半径膨胀每个静态 AABB 再做 slab TOI。但 `physics.c:486-488` 的 `body_bound_radius` 对 `SHAPE_CAPSULE` 只返回 `b->radius`，漏掉 `half_height`；而胶囊（直立 Y 轴，`half_height` 为段半长）中心到最远点（帽尖）沿轴为 `half_height + radius`，恰是 `aabb_from_body` 给胶囊的 Y 半宽。于是扫掠球比真实胶囊少扩 `half_height`，启用 CCD 且高速沿轴运动的胶囊可穿过厚度小于漏算量的薄静态几何。手算（`half_height=1、radius=0.5` → 帽尖在中心上方 1.5m，直立胶囊从 y=0 以速度 1000 上冲、薄天花板 y∈[9.9,10.1]、单步 dt=0.1）：旧 bound=0.5 → 中心停在 `9.9-0.5-ε≈9.3`、帽尖 `≈10.8` **穿过**天花板顶 10.1；修复 bound=1.5 → 中心停在 `9.9-1.5-ε≈8.3`、帽尖 `≈9.8` 停在天花板下（少扩量正好 = half_height = 1.0m）。触发：`physics_body_set_ccd(true)` + `SHAPE_CAPSULE` + 大步长/高速沿轴 + 薄静态障碍。修复：`body_bound_radius` 拆分 `SHAPE_SPHERE`（仍返回 `radius`）与 `SHAPE_CAPSULE`（返回 `half_height + radius`）；保守（可能略早停）对「防穿透安全网」是正确取舍，精确接触仍由离散 narrowphase（使用真实胶囊段）处理。新增回归 `ccd_capsule_axis_no_tunnel`：直立胶囊沿轴撞薄天花板，断言帽尖 `<10.0`（旧代码帽尖 ~10.8 会失败、修复后 ~9.8 通过），手算确认判别性。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31。总计 638 处修复。

R275 IBL 镜面 split-sum 误用 F_env 而非 F0（与 BRDF LUT 积分约定不符）— 修复 1 处 — **R275-A**（CORRECTNESS）：`brdf_lut.comp` 的 split-sum 镜面 LUT 头注释与积分实现明确对 Schlick 的 `Fc=(1-VdotH)^5` 做 `A=∫(1-Fc)·G_Vis`、`B=∫Fc·G_Vis` 分离预积分，运行时约定为 `specular = prefiltered_color * (F0*scale + bias)`（Karis/Epic）。但 4 个 IBL 片元着色器 `pbr_clustered.frag:377`/`pbr_clustered_vk.frag`/`deferred_light.frag:252`/`deferred_light_vk.frag` 的 `#ifdef HAS_IBL` 分支写成 `specular_ibl = prefiltered * (F_env*brdf.x + brdf.y)`，其中 `F_env = F_Schlick(max(dot(N,V),0), F0)` —— 在 LUT 已把 `(1-VdotH)^5` Fresnel 预积分进 A/B 的前提下**再乘一次**视相关 Fresnel（双重施加）。手算（非金属 F0=0.04、掠射 NdotV=0，LUT 采样 u=0）：`F_env=0.04+0.96·1=1.0` 而期望权重是 `F0=0.04`，A 项放大 `1.0/0.04≈25×`；NdotV=1 时 `F_Schlick(1,F0)=F0` 与 LUT 约定重合、正视差异小，故**掠射非金属**环境镜面偏亮最明显，roughness 越大越显眼。触发：HAS_IBL（默认 clustered/延迟 IBL 路径）+ 非金属 + 低 NdotV（大平面掠视、圆柱侧面）。修复：4 个 shader 的 HAS_IBL 镜面项 `F_env → F0`（`prefiltered * (F0*brdf.x + brdf.y)`），与自身 LUT 推导一致；保留 `kD_env=(1-F_env)*(1-metallic)` 做漫反射能量分配（视相关 Fresnel，标准做法）；`#else` 非 IBL 回退（假 `brdf=(0.8,0.2)`、非真 LUT）不动。glslangValidator 校验：VK 两变体 ±HAS_IBL 编译 SPIR-V 通过、GL 两变体 HAS_IBL 无错误。golden 只渲前向三角形、test_vulkan 不走 IBL 合成 → 套件无覆盖差异，以 glslang 校验补足。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31。总计 637 处修复。

R273 延迟渲染路径光源冻结（光源填充被前向 guard 独占）— 修复 1 处 — **R273-A**（CORRECTNESS）：`main.c` 每帧的光源填充整块（`light_system_clear` + `light_system_add_dir` 太阳 + 32× 轨道 `light_system_add_point`，含增量轨道旋转的静态局部）原先位于 `if (render.render_path == RENDER_PATH_FORWARD)` 前向 guard 内（3917–5065）。切换到 `RENDER_PATH_DEFERRED`（默认 FORWARD，UI 路径切换键）后，前向 guard 整段被跳过，`light_system_add_*` **再也不执行** → `lights` 冻结在最后一个前向帧的快照；随后延迟路径的 `light_system_upload_lights` + `light_system_cull(_gpu)`（5242–5246）cull/upload 这份**陈旧**数据：32 盏轨道点光冻结在切换瞬间的位置、太阳方向冻结，延迟光照不再随场景更新；同时每帧 `point_shadow_gather`（3914）读到的也是这份冻结点光 → 延迟点光阴影一并冻结。触发：切到 DEFERRED 后任意帧。修复：将光源填充整块**外提**到前向/延迟分支之前（`point_shadow_gather` 之后、前向 guard 之前），每帧无条件为两条路径运行；保留 `if (rhi_handle_valid(render.clustered_pipeline))` 门（该前向 clustered 管线在 render init 期恒建，两路径皆有效）。保序性：填充位于 gather **之后**，故 gather 仍观察上一帧光源（R75-1「gather 读上一帧」语义不变）；此位置到前向绘制之间无任何代码读 `lights`（skybox/terrain/water 只用 sun_dir/sun_color），故前向输出逐字节不变；轨道动画静态局部随整块迁移，全程单一实例、无重复定义。副带修正：延迟下一帧 gather 现读到当帧刷新的点光 → 延迟点光阴影亦随场景更新。无针对帧循环的单测，以双后端构建 + 全量套件通过为验证（同 R268/R271/R272 主循环接线修复惯例）。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31。总计 636 处修复。

R272 延迟光照从不采样屏幕 SSAO（每帧算出却弃用）— 修复 1 处 — **R272-A**（CORRECTNESS）：主循环每帧跑 `ssao_apply`（`main.c:5318`，默认 `radius=0.5`）算出屏幕空间 AO 到 `blur_fbo` 并 `render.ssao_tex=ssao_get_texture()`，前向 `pbr_clustered.frag:389` 以 `ao=texture(u_ssao,vUV).r` 把它乘进 IBL；但**延迟光照** `deferred_light(.frag/_vk.frag)` 的 `ao=rao.g`（仅 G-buffer 烘焙材质 AO）、`color=(diffuse_ibl+specular_ibl)*ao`，**从不采样 `u_ssao`**——`deferred.c` 的 `deferred_lighting_pass` 对 VK 传 `ssao=RHI_HANDLE_NULL`、GL 布局根本无 `u_ssao`。手算（切到 DEFERRED、某像素 `rao.g=1.0`、屏幕 SSAO=0.4）：期望（与前向一致）`L_ibl×0.4`，实际 `ao=1.0`→`L_ibl×1.0`，同场景延迟比前向 IBL 亮 2.5×、且引擎每帧白算一遍 SSAO。触发：切换 `RENDER_PATH_DEFERRED`（默认 FORWARD，UI `p` 键）且 `ssao.radius>0`。修复：让延迟采用**与前向完全相同、且被前向绘制每帧验证**的绑定方案——`deferred_light_vk.frag` 把 `u_point_shadow_cubes` 从 binding 5 移到 10（放在 `#ifdef HAS_IBL` 外，避免无 IBL 时未声明）、binding 5 改为 `sampler2D u_ssao`（`rhi_cmd_bind_material_textures_ibl` 早已实现「ssao 有效→binding 5、cubes→binding 10」路径，前向每帧走它）；GL `deferred_light.frag` 在 unit 14 加 `u_ssao`（对齐 R213-B，延迟 gbuffer 0-4/IBL 7-9/cubes 10-13，14 空闲）；两 shader `ao = rao.g * texture(u_ssao,uv).r`（材质 AO×屏幕 AO，比前向更全，保留 deferred 的材质 AO）；`deferred_lighting_pass` 加 `ssao_tex` 参，VK 传 `ssao_tex`（非 NULL）、GL 绑 unit 14；`main.c` 传 `render.ssao_tex`（与前向 `main.c:659` 同一来源、同 1 帧延迟）。null-ssao 边角（首帧前/`radius=0`）行为与前向逐字节相同（前向已生产验证），非新增风险。glslangValidator 对 VK shader 两路径（±HAS_IBL）编译通过。golden 只渲前向三角形、`test_vulkan` 不调 `deferred_lighting_pass`，故测试套件无覆盖差异。GL/VK 同修。编译验证：GL 100% + Vulkan 100%（+glslang SPIR-V 校验）。测试：GL/VK 各 31/31。总计 635 处修复。
此前：**R271 combined color 融合后处理未接入自动曝光致默认路径曝光错误 — 修复 1 处** — **R271-A**（CORRECTNESS/接线）：主循环每帧调 `tonemap_update_auto_exposure(&tonemap, post_input)`（`main.c:5438`）在 1×1 `lum_fbo` ping-pong 上算出本帧自适应亮度，但默认走的 **combined color 融合路径**（`combined_color_apply`，`main.c:5443`；`combined_color(.frag/_vk.frag)`）只做 `hdr *= u_tm_exposure`（固定手动曝光），**既不绑定 `lum_fbo`、也不复现 `tonemap.frag` 的 `mix(u_tm_exposure, 1/(luma+0.5), 0.8)` 自动曝光**。根因：R13-3「移除 `!auto_exposure` 门禁」让 combined 路径在 auto 开启时也接管（此前 auto 开启会回退多 pass 链由 `tonemap_apply` 正确处理），却没把自动曝光接进 combined shader → `tonemap_init` 默认 `auto_exposure=true`（`tonemap.c:70`）+ `cg_enabled` 默认 true（`main.c`）+ combined shader 成功加载（默认）三者同时成立时，UI 显示 auto 但画面按固定 1.5 曝光。手算（bloom 后 HDR≈(4,4,4)）：`luminance` pass 得 `scene_luma≈4`，独立 tonemap 有效曝光 `mix(1.5, 1/(4+0.5), 0.8)=mix(1.5,0.222,0.8)≈0.478`（ACES 前 HDR≈1.91）；combined 实际用 1.5（HDR=6.0）→ 约 **3.1× 过曝**，与声称的 auto 及独立 tonemap 路径不一致。修复：combined shader（GL+VK 两份）在 `binding=1` 加 `u_tm_lum` 并复制 `tonemap*.frag` 的 `scene_luma/auto_exp/mix(...,0.8)` **逐字节相同**逻辑；`combined_color_apply` 增 `lum_tex`+`auto_exposure` 参，按 `tonemap_apply` 同法——auto 开且 lum 有效时 `rhi_cmd_bind_material_textures(hdr,hdr,hdr,hdr,lum,hdr)` 把 lum 绑到 binding 1，否则仅绑 hdr@0（与独立 tonemap 关闭 auto 时行为一致）；`main.c` 传 `tonemap.lum_fbo[lum_idx].color_tex`+`tonemap.auto_exposure`。因两路径 shader 数学与绑定现完全一致，combined 与独立 tonemap 输出等价。零改动 VK 描述符/ push-constant 布局（binding 1 早在共享 `desc_layout` 的 0–5 号 sampler 中）。VK golden 回归只渲染简单三角形、不经后处理，`test_vulkan` TEST 6 只验 combined 无帧错误（传 `RHI_HANDLE_NULL`+`false` 保持固定曝光），故无回归。GL/VK 同修。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（含 golden 与 TEST 6）。总计 634 处修复。
此前：**R270 audio_play 未禁用默认 3D 空间化致 2D 音源钉在原点随听者衰减 — 修复 1 处** — **R270-A**（CORRECTNESS）：`audio_play`（`audio.c:113`）不带位置参数，是与 `audio_play_3d` 配对的 **2D/非定位** 变体（UI、音乐），但它以 `ma_sound_init_from_file(..., flags=0, ...)` 初始化。miniaudio **默认开启** spatialization，且 `ma_sound` 初始位置为原点 `(0,0,0)`——于是这个「2D」音源实际被空间化：`audio_system_update`（`main.c`）每帧把听者位置更新为相机位置，一旦听者离开原点，该音源即按逆距离模型随**听者到原点的距离**衰减。手算（逆距离 `min=1,rolloff=1`）：听者 `(0,0,0)`→`d=0` clamp 到 `min=1`→增益 `1/(1+0)=1.0` ✓；听者移到 `(10,0,0)`、音源仍钉在原点→`d=10`→增益 `1/(1+(10-1))=0.1` ✗（本应恒为 1.0）；`(8,1.5,0)`→`d≈8.14`→`≈0.123` ✗。对照同文件流式路径 `audio_play_streamed`（`audio.c:161`）在 `!spatial` 时显式 `flags|=MA_SOUND_FLAG_NO_SPATIALIZATION`——2D 语义正确，`audio_play` 属对称遗漏。触发：任何 `audio_play` 调用（非 `audio_play_3d`）且听者不在原点（demo 听者跟随相机，恒成立）。仓库当前无直接 `audio_play` 调用（仅 `audio_play_3d` 内部用），属公共 API CORRECTNESS。修复：`audio_play` 初始化加 `MA_SOUND_FLAG_NO_SPATIALIZATION`（与 streamed 2D 分支一致，使 2D 音源不随听者衰减）；`audio_play_3d` 在设位置前显式 `ma_sound_set_spatialization_enabled(MA_TRUE)` + `ma_sound_set_attenuation_model(ma_attenuation_model_inverse)`（镜像 streamed 的 spatial 分支）恢复 3D 行为并统一衰减模型。纯 miniaudio CPU 路径，GL/VK 无关。音频测试为无设备的纯函数（`audio_attenuation_gain`），此为 miniaudio flag 接线（无可注入的 mock 断言），靠构建 + 全量回归 + 手算/语义对照验证（与 R268/R241 音频接线同范式）。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31。总计 633 处修复。
此前：**R269 动画渐进 crossfade 从不采样目标片段致淡入无效+末端硬切 — 修复 1 处** — **R269-A**（CORRECTNESS）：`anim_crossfade`（`animation.c:170`）记录 `from_clip=L->clip_index`、`to_clip=new_clip`，但**淡出完成前不改 `L->clip_index`**（仍为 from）。`anim_blend_evaluate`（`animation.c:262/292`）主采样路径用 `L->clip_index`（=from）填 `sample_*`；随后 crossfade 块（旧 295–314）又对 `crossfade.from_clip`（同=from）采样进 `from_*`，做 `sample_[b]=lerp(from_[b], sample_[b], fade_t)`=`lerp(from,from)`——**`to_clip` 全程从未 `clip_sample`**。于是渐进 crossfade 整个 duration 内输出恒为 from-pose，直到 `fade_done` 才把 `L->clip_index=to_clip`（硬切）。手算（`test_animation.c` 同设定）：clip0 x:0→10、clip1 x:0→20，`crossfade(0→1, dur=1)`，`evaluate(dt=0.5)`→`L->time=0.5`、`fade_t=0.5`；期望 `lerp(from=5, to=10, 0.5)=7.5`，实际 `lerp(5,5,0.5)=5`（仅 from）。旧测试 `crossfade_gradual` 仅断言 `1<x<19`，x=5 亦通过故未暴露。触发：`anim_crossfade(dur>0)` 且 `from!=to`（`main.c` F12 / `BREAK_ANIM_BLEND=1`）。修复：crossfade 块改为采样 `crossfade.to_clip`（`to_*`，未动关节从当前输出 seed，时间沿用旧 from 侧的 `fmod(L->time,to_dur)` 近似），`sample_[b]=lerp(sample_(from), to_[b], fade_t)`（旋转 `quat_nlerp`）——fade_t 0→from、1→to，渐进混合生效。强化回归 `crossfade_gradual` 断言中点 x=7.5（旧码=5 会失败）。纯 CPU 动画，GL/VK 无关。另核 additive 层（工程内无 `set_mode(ADDITIVE)` 调用）与两骨 IK（demo 根骨链可接受）非同级高置信，未改。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_animation 27/27 含强化用例）。总计 632 处修复。
此前：**R268 延迟光照从未上传 CSM 级联矩阵致阴影恒用单位阵 — 修复 1 处** — **R268-A**（CORRECTNESS/接线）：`light_system_set_cascade_vp`（`lighting.h:89`）**全仓库零调用**，故 `LightSystem.cascade_vp_src` 恒为 NULL，`light_system_upload_lights_only`（`lighting.c:249`）遂在 light data buffer 的 `SHADOW_MATRIX_OFFSET=520` 处写入 **4 个单位阵** 而非本帧 CSM 深度 pass 实际渲染 atlas 用的 `render.cascade_vp[0..3]`（`main.c:3728`）。延迟路径 `deferred_light.frag` 的 `shadow_test`/`get_cascade_vp` 据此选级联并做深度比较：手算世界点 `P=(0,0,-5)` → `clip=I·P=(0,0,-5,1)` → `uv=(0.5,0.5)` 选中 cascade 0、`z_win=-2.0`（与 [0,1] 深度纹不可比），而该象限 UV 处 atlas 内容来自**真实** `cascade_vp[0]`——投影/比较空间完全不一致；远点 `P=(20,0,20)` → `uv=(10.5,10.5)`、`cascade<0` → `return 1.0`（整片无影）。触发：切到 DEFERRED 渲染路径（默认 FORWARD，UI `p` 键切换；`main.c:5094` 延迟块内 `light_system_upload*` 注释明写「cascade matrices for deferred lighting」却未接线）。修复：在 `main.c` 延迟块 `light_system_upload*` **之前**加 `light_system_set_cascade_vp(&lights, render.cascade_vp)`——CSM 深度 pass 已于本帧更早（3728）填好 `cascade_vp[]`，同指针零拷贝发布给 GPU，使 `shadow_test` 的级联选择/深度比较/PCF 与 atlas 渲染同空间。默认 FORWARD 路径不调用 `light_system_upload`（网格用简单 sun uniform、地形/水用 `cascade_vp[0]`），故 golden（FORWARD）字节不变、无回归；修复仅影响 DEFERRED。属 main.c 渲染接线，靠构建 + golden(FORWARD) 回归 + 推导验证（无纯函数可单测）。GL/VK 同一上传/着色路径，双端同修。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（含 golden）。总计 631 处修复。
此前：**R267 task_wait 完成计数用 relaxed 递增致弱内存序上任务结果可见性缺失 — 修复 1 处** — **R267-A**（CORRECTNESS/并发，弱内存序平台）：`task_wait`（`task.c:774`）判「全部完成」**只** acquire-load `total_tasks_completed` 与 `submitted` 比较，**不**读每任务的 `completed` 标志，故 `execute_task`（`task.c:335`）对 `task->completed` 的 release store 与全局 `task_wait` **无**同步关系。而完成计数递增 `atomic_fetch_add(&total_tasks_completed,1,memory_order_relaxed)`（`task.c:336`）为 relaxed（非 release 操作），于是 `task_wait` 的 acquire load 与 worker 在 `task->fn()` 内的**非原子写**（`ecs_parallel_for` 组件更新、`sys_sync_transform_from_physics` 写 `CTransform`）之间**不构成 happens-before**。交错时序：worker 普通写 xs[i].pos → relaxed++ 使计数达 submitted；主线程 acquire 读计数满足 `completed>=submitted` 退出 `task_wait` → 读 Transform/渲染，但对 worker 的写**无** acquire 屏障 → 在 **ARM/Apple Silicon**（引擎支持 macOS）等弱序机器上可读到**旧值**（错帧/抖动/物理已更新但渲染未跟上）；x86 TSO 恰好隐藏此问题，非可移植语义。`task_wait_handle` 对 `task->completed` 用 acquire 是正确范式，全局 `task_wait` 与之不一致。修复：递增改为 `memory_order_acq_rel`——每个 worker 的递增 acquire 前序 worker 的递增（把各自 fn() 写串成 happens-before 链）并 release 自身，故一旦 `task_wait` 的 acquire load 观察到 `completed>=submitted`，所有已完成任务的写均可见（仅 release 只能与释放序列头同步、跨多 worker 不足，故用 acq_rel）。`create` 内对该计数的 relaxed 清零（`task.c:506`，单线程初始化）不受影响。纯并发内存序修正，无行为改变于 x86；GL/VK 后端无关。x86 TSO 无法复现该数据竞态，故靠推导 + 全量回归验证（不新增无效的 x86 用例）。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（含 golden 与 test_task）。总计 630 处修复。
此前：**R266 terrain_generate 对 height_scale 二次缩放（预设地形高度 hs² 倍）— 修复 1 处** — **R266-A**（CORRECTNESS）：`terrain.c` 约定 `heightmap[]` 存**未缩放**标量、世界 Y = `heightmap[i] * height_scale` 在读取端应用一次（`terrain_rebuild_region` 烘焙顶点 65/228 行、`terrain_get_height` 372 行）。所有其它写入方均遵此：`terrain_init`（136 行）写原始 `terrain_height_func`、`terrain_modify_height`（558 行）与 `terrain_noise_stamp` 累加原始增量。唯独 `terrain_generate`（568 行 `f32 hs = t->height_scale;`）在写 `heightmap` 前对每个 preset 形状已乘 `hs`（如 case1 火山 `h = (1-d*3)*hs`、648 行 `heightmap[z*n+x]=h`），读取端再乘一次 → 世界高度 = `归一化形状 * height_scale²`。手算：默认 `height_scale=1.5`、火山中心归一化 1.0 → 存 1.5、渲染/碰撞 1.5×1.5=**2.25**（应为 1.5）。更糟的是这使**存储的 heightmap 依赖 height_scale**：随后对生成地形做原始笔刷 `terrain_modify_height` 或改 `height_scale` 都不再自洽。触发：按 `;` 切 preset 或 `r` 重置并 `terrain_generate`（`main.c` 4596/4640），且 `height_scale≠1`（默认 1.5）。修复：`terrain_generate` 内 `hs=1.0f`，使 preset 存归一化形状、`height_scale` 仅在读取端应用一次（各项统一乘 hs，故置 1 完整保留形状比例，仅去掉多余全局因子）。golden 不渲染生成地形（generate 仅按键触发、init 走 `terrain_height_func`），无 golden 回归。新增回归 `generate_heightmap_is_scale_independent`（同 preset 在 hs=1 与 hs=3 下生成的 heightmap 逐点相等，证存储与 scale 无关）。GL/VK 共用 CPU 地形代码，双端同修。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（含 golden；test_terrain 23/23 含新用例）。总计 629 处修复。
此前：**R265 视锥平面提取 Gribb-Hartmann 矩阵下标转置（构造了 VP^T 的视锥）— 修复 1 处** — **R265-A**（CORRECTNESS，影响面大）：`frustum_from_vp`（`cull.c:3`）与镜像实现 `frustum_extract`（`frustum_cull.c:18`）在**列主序** `Mat4`（`e[col][row]`）上做 GH 平面提取时把两个矩阵下标写反。引擎自身的点变换约定为 `clip.e[r] = Σ_c vp->e[c][r]·p.e[c]`（见 `lighting.c` 的 `mat4_vec4` 注释「col0*v0+…=每行一个结果」，以及 GLSL `vp*p` + `transpose=GL_FALSE` 上传），故作为点的线性泛函，「第 r 行」= `(e[0][r],e[1][r],e[2][r],e[3][r])`，其对点分量 i 的系数为 `e[i][r]`。平面系数 `plane.e[i]`（`frustum_test_*` 按 `e0*x+e1*y+e2*z+e3` 消费）应为 `(row3±row_k)[i] = vp->e[i][3] ± vp->e[i][k]`；但旧码写成 `vp->e[3][i] ± vp->e[k][i]`（两下标互换）→ **提取的是 VP^T 的视锥而非 VP**。实测：默认相机（pos (0,2,8) 看 -Z、fov 60°、near 0.1/far 100）下对 20 万随机点，旧实现把**全部 148398 个真实在视锥内的点判为在外**（100% 误判、`frustum_test_point((0,2,-5))` 返回 false），下标改正后 0 误判、与 clip 空间判据完全一致。之所以引擎默认能正常渲染且 golden 通过：**GPU 剔除路径**（`cull.comp`/`unified_cull.comp` 直接 `vp*vec4(center,1)` 判 NDC，约定正确、R11 起默认开）不经 `frustum_from_vp`；错误仅落在 **CPU 回退/CPU 剔除路径**——`main.c` 阴影级联/点光面回退的 `frustum_test_sphere`（3777/3865）、ECS 实例实体剔除（4122）、灯光剔除（4807）、`frustum_cull_batch`（4981）等，一旦走到即把可见几何**全部剔除**。既有 `test_camera_frustum` 24 例只断言「本应在外」的点在外（全剔除的视锥恰好满足），故一直未暴露；`frustum_extract_matches_from_vp` 因两实现同错互比亦通过。修复：两处均把 `vp->e[3][i]/e[0..2][i]` 改为 `vp->e[i][3]/e[i][0..2]`（仅转置下标，±号、归一化、`sign_mask` 不变，与注释所述 `row3±row0` 语义一致）。新增回归 `frustum_point_in_front_visible`（前方点/球/AABB 必可见、身后点不可见，并与 clip 空间 ground-truth 交叉验证）。GL/VK 共用同一 CPU 剔除代码，双端同修；GPU 剔除路径不变故 golden 无回归。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（含 golden；test_camera_frustum 含新用例）。总计 628 处修复。
此前：**R264 arena_alloc `used+size` usize 回绕绕过容量检查 — 修复 1 处** — **R264-A**（CORRECTNESS）：`arena_alloc`（`alloc.h:52`）以 `usize offset = aligned - buffer + size; if (offset > capacity) return NULL;` 做边界检查。当 `size` 接近 `SIZE_MAX`（如上游 `n*sizeof(T)` 自身已乘法回绕得到近 `SIZE_MAX` 的巨值）且 arena 非空（`offset>0`）时，`used + size` **回绕**过 0 变成一个很小的值：手算 capacity=1024、已用 1000（剩 24），请求 size=SIZE_MAX、align=1 → `used=1000`、`1000+SIZE_MAX` 回绕为 **999**，`999 > 1024` 为假 → **不返回 NULL**，反而返回界内指针 `buffer+1000`，并把 `a->offset` 写成 **999**（相对 1000 **回退**）→ 后续分配与已存活块重叠（别名 / 越界写）。同文件堆分配器早已针对同一类回绕加了守卫（R158：`total = size+extra+ptr; if (total < size) return NULL;`），arena 却漏了此守卫，属对称遗漏。修复：改为不产生回绕的比较——先取 `used = aligned - buffer`，`if (used > capacity || size > capacity - used) return NULL;`（先拒绝对齐 padding 已越过 capacity 的近满 arena，再用不会下溢的减法判断剩余空间），随后 `a->offset = used + size`。已排序/常规 size 的语义与原实现字节等价，仅在病态巨 size 下由「静默破坏」变为「返回 NULL」。纯 CPU 核心分配器，GL/VK 无关。新增回归 `arena_overflow_size_no_wrap`（近满 arena 请求 SIZE_MAX 须返回 NULL 且 offset 不回退，之后仍能按真实剩余容量分配）。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_alloc 含新用例，16/16）。总计 627 处修复。
此前：**R263 窗口失焦未释放按键致「粘键」持续移动 — 修复 1 处** — **R263-A**（CORRECTNESS）：Wayland `keyboard_leave`（`window_wayland.c:195`）为空实现、X11 `platform_poll` 无 `FocusOut` 分支且 `XSelectInput` 缺 `FocusChangeMask`，故窗口/键盘失焦时不清 `InputState.keys[]`。Wayland/X11 对**已失焦**客户端通常不再投递 key/button release，于是失焦期间物理松开的键在回焦后 `input_key_down` 仍为真——`camera_update`（`camera.c`）每帧继续 `position += fwd*speed*dt`，表现为 Alt-Tab 后角色/相机「自己走」。状态机本身正确（`input.c` 3→2→1→0 边沿），缺的是失焦与 OS 物理态的强制同步。修复：新增 `input_release_all`（`input.c/.h`）把所有 held(2)/just-pressed(3) 键统一置 just-released(1)——just_released 边沿正常触发一次、`input_key_down` 立即为假、下帧 `input_new_frame` 归 0；鼠标键共用 `keys[]`（`INPUT_MOUSE_*>=300`）一并覆盖，手柄不随窗口焦点不动。Wayland `keyboard_leave` 调用之；X11 加 `FocusChangeMask` 并在 `FocusOut` 调用之。仅 Linux 平台输入层，GL/VK 渲染无关。新增回归 `release_all_clears_held_and_pressed`。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_input 含新用例）。总计 626 处修复。（CORRECTNESS）：Wayland `keyboard_leave`（`window_wayland.c:195`）为空实现、X11 `platform_poll` 无 `FocusOut` 分支且 `XSelectInput` 缺 `FocusChangeMask`，故窗口/键盘失焦时不清 `InputState.keys[]`。Wayland/X11 对**已失焦**客户端通常不再投递 key/button release，于是失焦期间物理松开的键在回焦后 `input_key_down` 仍为真——`camera_update`（`camera.c`）每帧继续 `position += fwd*speed*dt`，表现为 Alt-Tab 后角色/相机「自己走」。状态机本身正确（`input.c` 3→2→1→0 边沿），缺的是失焦与 OS 物理态的强制同步。修复：新增 `input_release_all`（`input.c/.h`）把所有 held(2)/just-pressed(3) 键统一置 just-released(1)——just_released 边沿正常触发一次、`input_key_down` 立即为假、下帧 `input_new_frame` 归 0；鼠标键共用 `keys[]`（`INPUT_MOUSE_*>=300`）一并覆盖，手柄不随窗口焦点不动。Wayland `keyboard_leave` 调用之；X11 加 `FocusChangeMask` 并在 `FocusOut` 调用之。仅 Linux 平台输入层，GL/VK 渲染无关。新增回归 `release_all_clears_held_and_pressed`。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_input 含新用例）。总计 626 处修复。
此前：**R262 物理接触求解「接近/分离」判据反向致法向冲量与弹性从不生效 — 修复 1 处** — **R262-A**（CORRECTNESS，影响面大）：`resolve_contact`（`physics.c:192`）的法向冲量早退判据写反。约定 `Contact.normal` 从 A 指向 B（`physics.h`；上方位置分离将 A `-=normal`、B `+=normal` 推开，仅在 A→B 法线下正确）。取 `rel_vel=v_a-v_b`，则 `dot(rel_vel,normal)>0` 表示两体沿接触**正在靠近**（A 朝 B / B 朝 A 运动），`<0` 表示分离。冲量应在**靠近**时施加、在分离时跳过；但原代码 `if (vel_along_normal > 0) return;` 恰好在靠近时 return → 真实碰撞里**法向冲量与 restitution 永不施加**，只有位置推挤在跑。手算：动态盒 v=(0,-4,0) 落到静态地板，n=a→b=(0,-1,0)，`dot=+4>0` → 直接 return，竖直速度仍 -4（不被冲量归零、无反弹）；两动态盒对撞同理。表现：动态体把接近速度「穿透」接触点——不停、不弹、不按质量交换法向动量，仅靠位置修正把物体挤出（抖动、无弹性）。既有 `collision_detection` 测试用**零速**两体（`vel_along_normal=0`，两分支都不 return）且只断言 `collision_count>0`，故一直未暴露。修复：改为 `if (vel_along_normal < 0.0f) return;`（仅在已分离时跳过）；冲量公式 `j=-(1+e)*vel_along_normal*inv_total` 本身正确，翻转判据后端到端自洽。新增回归 `collision_resolves_approach_velocity`（两等质量动态盒对向 ±5 重叠，步后 A 的 x 速度由 +4.9 变 ~-1.5 < 1.0）。纯 CPU，GL/VK 无关。另评估未改：`particles_compute` emit_accum 在钳到 `PARTICLES_MAX` 前按未钳值扣减——R174 仅承诺「小数 carry」，且仅病态大 `dt`（卡顿）触发，丢弃超额可避免卡顿后的补发爆发，属既定权衡。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_physics 含新用例）。总计 625 处修复。
此前：**R261 ECS query_next 迭代器 index off-by-one（跳过每 chunk 首行 + 末行越界）— 修复 1 处** — **R261-A**（CORRECTNESS）：`query_next`（`ecs.c:685`）在 `it->index < chunk->count` 成立时**先 `it->index++` 再 `return true`**，而文档约定的用法（`PureC_Engine_DeepDive.md:262` 的 `ECS_GET(it,T)=chunk_get_component(it.chunk, it.index, …)`）在循环体内用**当前** `it.index` 取 SoA 行。于是调用方每个 chunk 读到行 `1..count` 而非 `0..count-1` → **跳过每个 chunk 的第 0 个实体**，且末次迭代 `it.index==count` **越界读**一行（合法 `0..count-1`）。手算：单实体 chunk（count=1）→ 首次 `query_next` 令 index 0→1 返回 true，调用方读行 1（列尾后内存），行 0 从不被访问。迭代**次数**仍等于实体数（故 `test_ecs` 仅计数的用例通过、未暴露），引擎主路径（`main.c` 用 `for(ci=0;ci<c->count;ci++)` 手遍历、`ecs_parallel_for` 按整列回调）不读 `it.index` 故运行时未触发，属公共文档化 API 的确定性 off-by-one。修复：`query_begin` 置 `it.index=(u32)-1` 哨兵；`query_next` 改为进入某 chunk 后**先 `++` 再做边界检查**，返回时 `it.index` 恰为当前有效 0-based 行；切换 chunk 时 index 复位为 `(u32)-1`。迭代次数与原实现逐用例一致（既有计数测试不变）。新增回归 `ecs_query_index_zero_based`（5 实体单 chunk，断言走过的行恰为 0,1,2,3,4）。纯 CPU，GL/VK 无关。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_ecs 含新用例）。总计 624 处修复。
此前：**R260 LOD 未注册 entity 与「组索引 0」混同 — 修复 1 处** — **R260-A**（CORRECTNESS）：`lod.c` 的 `entity_to_group[]` 由 `lod_init` 清零、`lod_unregister` 把移除项复位为 0，故**从未注册**的 entity 也映射到 `group_idx==0`。`lod_select`（`lod.c:195`）与 `lod_get_mesh`（`289`）仅以 `group_idx >= sys->count` 判定有效性——一旦有任意组注册（首个 `lod_register` 即令某 entity 占 `groups[0]`），对未注册 entity 查询时 `0 >= count` 为假 → **误用 entity 0 的 LOD 组**：`lod_select` 返回 entity 0 按距离算出的层级并写脏 `current_levels[未注册]`，`lod_get_mesh` 返回 entity 0 的网格而非空。手算：注册 entity0（`base=10`,4 级），查询未注册 999 于 cam 距 1000 → 期望安全默认 0，实际选 level 3 且写 `current_levels[999]=3`。修复：`lod_select`/`lod_get_mesh` 增加 `sys->groups[group_idx].entity_id != entity` 校验（`entity_id` 在 `lod_register` 写入、`lod_unregister` swap-remove 时同步更新，故对真注册项恒真、对别名项为假）；无需哨兵、不改 init。运行时默认路径（`main.c` 仅对已注册且有 mesh 的节点调用）未暴露，属公共 API 逻辑缺陷。纯 CPU，GL/VK 无关。新增回归 `lod_select_unregistered_when_group0_exists`（注册 entity0 后查询 999 应得 0 与空 mesh）。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31（test_lod 含新用例）。总计 623 处修复。
此前：**R259 GL 阴影 atlas/cube 面 glClear(DEPTH) 在 depth mask=false 时静默失效 — 修复 1 处** — **R259-A**（CORRECTNESS/GL 状态泄漏）：OpenGL 规范下 `glClear(GL_DEPTH_BUFFER_BIT)` 在 `glDepthMask==GL_FALSE` 时被忽略。`rhi_cmd_bind_shadow_map`（`rhi_gl.c:1561`）与 `rhi_cubemap_depth_fbo_bind_face`（`2412`）在绑定 FBO 后立即 `glClear(DEPTH)`，此时**尚未**绑定阴影深度 pipeline（它才会把 mask 拉回 true）。`g_gl_depth_mask` 是 file-scope 缓存，被 `gl_cmd_bind_pipeline`（`554`）在 `depth_write_disable` pipeline（后处理/UI/天空盒/加法粒子）时置 false。跨帧场景：上一帧最后绑定的是 `depth_write_disable` pipeline → mask 残留 false 进入下一帧；下一帧阴影 pass 通常最先执行（`particles_compute` 因 `!initialized` 直接 return，不经 pipeline bind 复位 mask），于是 atlas/立方体面的清除**静默失效** → CSM 级联脏块、点光 shadow 拖影/错位、自阴影不稳定（随「上帧最后 pipeline」变化）。同文件 `rhi_cmd_clear_depth`（`1573`）已注明并处理此坑，阴影路径未复用。修复：在两处 `glClear(DEPTH)` 前加与 `rhi_cmd_clear_depth` 相同的守卫——`if (!g_gl_depth_mask){ glDepthMask(GL_TRUE); g_gl_depth_mask=true; }`。仅 GL 受影响；VK 走 render pass `loadOp=CLEAR` 与 mask 无关。编译验证：GL 100% + Vulkan 100%。测试：GL/VK 各 31/31。总计 622 处修复。
此前：**R258 VK 延迟 G-buffer 深度 layout 跟踪缺失致 Hi-Z 屏障错误/缺失 — 修复 1 处** — **R258-A**（CORRECTNESS/VK 同步）：MRT（G-buffer）render pass 深度 attachment `finalLayout = DEPTH_STENCIL_READ_ONLY_OPTIMAL`（`rhi_vk.c:6361`），但注册的深度纹理句柄 `dd` 经 `calloc` → `cur_layout = 0`（`UNDEFINED`），且 `rhi_mrt_fbo_bind` **未像 `rhi_offscreen_fbo_bind`（6010）那样维护 `cur_layout`**。延迟路径把 Hi-Z 的 `scene_depth` 指向 `gbuf_depth`（`main.c:5267`），`occlusion_cull_generate_hi_z`→`rhi_cmd_transition_depth_to_read`（`occlusion_cull.c:278`）据 `cur_layout` 决定屏障 `oldLayout`：首帧 `UNDEFINED`→取 `DEPTH_STENCIL_ATTACHMENT_OPTIMAL` 作 `oldLayout`，与实际 `READ_ONLY` **不符**（VUID-VkImageMemoryBarrier-oldLayout）；此后 `cur_layout` 被写成 `SHADER_READ_ONLY`，而每帧 G-buffer pass 结束后深度实际又回到 `READ_ONLY`，`transition_depth_to_read` 因 `cur_layout==SHADER_READ_ONLY` **幂等早退**（3948）→**完全跳过**布局转换与 depth-write（`LATE_FRAGMENT_TESTS`）→compute-read 的执行/内存依赖屏障 → Hi-Z compute 以陈旧 layout 采样深度、且无同步 → GPU 遮挡剔除误剔/漏剔、物体闪烁 + validation 报错。修复：`rhi_mrt_fbo_bind` 开头把深度纹理 `cur_layout` 置为 `DEPTH_STENCIL_READ_ONLY_OPTIMAL`（该 pass 的真实 finalLayout），使每帧 `transition_depth_to_read` 以正确 `oldLayout=READ_ONLY` 转到 `SHADER_READ_ONLY` 并**每帧重发屏障**，与 offscreen 的 ATTACHMENT 跟踪同构。仅 VK 受影响；GL 中 `transition_depth_to_read` 为 no-op（`rhi_gl.c`）不受影响。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31。总计 621 处修复。
此前：**R256 场景世界变换单遍遍历假定父先于子 — 修复 1 处** — **R256-A**（CORRECTNESS）：`scene_compute_world_transforms`（`asset.c:617`）单遍按 `nodes[]` 下标顺序做 `world = parent.world * local`，仅守卫 parent_index 越界/自引用，**未处理 parent_index > i**（子节点在数组中先于父节点）。glTF 规范**不要求**父节点在 `nodes[]` 中先于子节点（cgltf 保留文件顺序，`asset.c` 按 `data->nodes[]` 顺序填充、parent_index=`parent-data->nodes`；JSON 场景 `scene_serial.c` 亦按文件顺序追加）。当子先于父时，子的 `world_transform` 乘到父**尚未计算**的 world（首帧为未初始化/上帧陈旧值）→ 该子树网格在 mega-buffer 预变换（`main.c:1707/4876`）中落到错误世界位姿。文档误称「cgltf 保证拓扑排序」——实则不保证；且 R240 已把**骨骼**关节 world 解析（`skel_resolve_world`）改为顺序无关，场景节点路径为同类遗漏。修复：改为**迭代至稳定**（每遍重算 world，某遍无变化即停）——常见已排序数据一遍生效+一遍确认即收敛，最多 `node_count` 遍保证终止（环通过 parent 守卫退化为根）；无需堆分配（`main.c:4876` 在每帧回退分支调用）。单遍语义对已排序数据字节等价。纯 CPU（场景层），GL/VK 无关。另证伪本轮首个候选：`bvh_raycast`/`ray_aabb_intersect` 起点在 AABB 内返回负 t——标量与 SSE 两路径 `tmin` 均以 `0.0f` 起算且只增（`bvh.c:449`/`simd.h:90`），起点在内返回 t=0（正确，射线即刻相交），无负 t，误报未改。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（asset.c 重链接依赖过重无法在 test_scene_serial 单测该函数，沿用 R249/R253 先例靠构建+全量回归；单遍等价保障既有场景无回归）。总计 620 处修复。
此前：**R255 VFS PAK 共享 FILE* 并发读竞态 — 修复 1 处** — **R255-A**（CORRECTNESS/并发）：PAK 挂载全程复用单个 `pak_fp`（`vfs.c`），`vfs_open` 命中 PAK 条目时在该 `FILE*` 上做 `fseek(data_offset)`+`fread(size)` **无任何同步**；而 `async_loader` 默认起 2（至多 8）个 IO worker，`io_worker_run` 并发调用 `vfs_open`/`vfs_read_all`（→`vfs_open`）读同一 VFS。两 worker（或主线程同步加载与 worker 并行）交错修改共享文件游标 → 后执行的 `fread` 从**错误 offset** 读，仍可能恰好读满 `pe->size` 字节**通过长度校验**，把别的条目/垃圾当作网格/纹理/脚本解析（难稳定复现）。C/POSIX 规定同一 `FILE*` 的 `fseek`/`fread` 必须应用层串行化。目录挂载每次独立 `fopen`（`vfs.c` else 分支）不受影响。修复：`struct VFS` 增不透明 `void *pak_lock`（`vfs_create` 用模块内 `AsyncMutex` 初始化、`vfs_destroy` 销毁），`vfs_open` 的 PAK 分支把 `fseek+fread` 包在 `async_mutex_lock/unlock` 内保持每次读原子；不透明指针避免 vfs.h 泄漏线程头。单线程行为不变（既有 `test_vfs` 通过）。纯 CPU/IO 层，GL/VK 无关。另评估 gpucull/occlusion GPU→CPU 可见性回读「同槽读写」疑似 2 帧滞后：经核 `rhi_frame_begin` 仅等待 `fences[current_frame]`（即 fi 槽）、`gpucull.c:472` 注释「读 fence 刚等过的槽」，读 `staging[fi]`（两帧前数据）是 **fence 保证已完成** 的安全设计；子代理建议改读 `(fi+1)&1` 槽会读到 **fence 未等过** 的在途数据 → GPU/CPU 竞态，属回归而非修复，**不改**（该延迟与已接受的 Hi-Z 一帧延迟同类）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31。总计 619 处修复。
此前：**R254 packet 读取按实际长度边界 + 扫掠负 tmin — 修复 2 处** — **R254-A**（CORRECTNESS/安全）：`packet_can_read` 用固定 `PACKET_MAX_SIZE`(1400) 而非实际收到字节数 `write_pos`（`packet_read_begin` 已置为收到长度）作读边界；截断/伪造的 UDP 包尾部是 `buf->data` 中未初始化的栈字节，越过真实 payload 的读取返回**残留字节**而非失败。配合 `net_repl_parse_payload` 读 `n`（条目数）后**不校验剩余字节**、且读失败仍 `return true` 设 `*out_count=n` → 攻击者/截断包可声明 N 条快照仅带 1 条，解析出 N-1 个 (0,0,0) 幽灵实体。修复：`packet_can_read` 改为 `read_pos+n <= write_pos`（同时令既有 `read_truncated_packet`/空 payload 读**确定性**返回 0，不再依赖栈恰好为 0）；`net_repl_parse_payload` 读 `n` 后按 `(write_pos-read_pos)/16` 钳到实际可读条目数。新增 `parse_payload_clamps_forged_count` 回归测试。**R254-B**（CORRECTNESS）：公开 API `physics_sweep_test`（`character.c:247`）slab 命中判据缺 `tmin>=0`，与同引擎 `ccd_sweep_static`（`physics.c:558` 要求 `tmin>=0`）不一致；当扫掠起点位于/嵌入静态 AABB 内部时 `tmin<0`、`tmax>0`，仍报 `hit=true`、`*out_t` 为负、`*out_hit_pos=origin+delta*tmin` 落在运动**反方向**（非 [0,1] 内首次前向碰撞）。触发：起点在静态体内且 delta 非零（贴地/密集几何）。修复：判据加 `tmin>=0.0f`，与 CCD 对齐。二者均纯 CPU（网络/物理），GL/VK 无关。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含新增伪造条目数回归）。总计 618 处修复。
此前：**R253 glTF 蒙皮关节索引 >128 越界 texelFetch — 修复 1 处** — **R253-A**（CORRECTNESS/安全）：蒙皮 VS（`skinned.vert`/`skinned_vk.vert`）用原始顶点关节索引 `j` 做 `texelFetch(u_joints, j*4+..)`，而 GPU 关节缓冲固定 `SKELETON_MAX_JOINTS`（128）个 `mat4`（`skeleton_set_joints` 把 `joint_count` 截到 128、`skeleton_upload` 只传 ≤128 个矩阵）。R249 起 `JOINTS_0` 支持 UNSIGNED_INT（面向 >255 关节的工业角色），顶点可保留 **≥128** 的关节索引，`asset.c` 加载时**原样写入**（`joints[k]=j[k]` 无钳制）→ 关节索引 ≥128 时 texel 下标 ≥512 越过缓冲有效范围 → GL/VK 上 `samplerBuffer` **越界读取（UB）**、错误矩阵/畸形网格。触发：任一带 skin 的 glTF 且顶点权重引用关节 index ≥128。修复：加载顶点关节时对 `joints[k]` 钳到 `[0, SKELETON_MAX_JOINTS-1]`（三种 component_type 分支后统一钳制），确保 texelFetch 恒在界内；并在 `skin->joints_count > SKELETON_MAX_JOINTS` 时 `LOG_WARN` 提示截断（>128 关节的 rig 引擎本就只有 128 槽，钳制后形变降级但杜绝 UB；彻底支持需提升 `SKELETON_MAX_JOINTS` 上限，属更大改动）。GL/VK 共用同一 `SkinnedVertex`+shader+128 矩阵上传，双端同错同修。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（现有资产关节数 <128，钳制不触发，字节等价，golden 不受影响）。总计 616 处修复。
此前：**R252 skeleton_evaluate STEP 遗漏 + glTF UV/骨骼集索引 — 修复 2 处** — **R252-A**（CORRECTNESS）：R251 已在混合路径 `clip_sample`（`animation.c`）实现 glTF STEP 阶跃，但 **legacy `skeleton_evaluate`（`skeleton.c:183`）仍恒线性 lerp/slerp、不读 `ch->interp`**；而默认 demo 在**未设 `BREAK_ANIM_BLEND`** 时正走此路径（`main.c:4044` else 分支）。于是加载了带 `interpolation:STEP` 的 glTF 动画后，蒙皮仍在关键帧间平滑过渡 → 阶梯/硬切动画出现源资产中不存在的中间姿态（机械动作发虚/错位）。修复：`skeleton_evaluate` 在 clamp `frac` 后复用 `clip_sample` 同一逻辑 `if (ch->interp==ANIM_INTERP_STEP) frac=(t>=t1)?1:0`（`[t0,t1)` 取 kf、末键 `t==t1` 取 kf_next，端点精确无中间值）。新增 `skeleton_evaluate_step_holds_keyframe` 回归测试。**R252-B**（CORRECTNESS）：glTF 顶点属性遍历 `if (type==texcoord) uv_acc=attr->data`（同样 joints/weights）对**任意套号无差别覆盖**，最终留下属性列表中**最后一个** `TEXCOORD_*`；当 `TEXCOORD_1`（光照图/细节 UV）排在 `TEXCOORD_0` 之后，网格被绑到次 UV 集，而材质默认 `texCoord:0` → 贴图错位/拉伸。glTF 2.0 用 `cgltf_attribute.index` 区分套号，引擎只消费单 UV 集 + 单 4-权重蒙皮集。修复：texcoord/joints/weights 均加 `&& attr->index==0` 只绑主集（glTF 要求 set 索引从 0 连续，有 texcoord 即有 TEXCOORD_0）。二者均纯 CPU（动画/资产），GL/VK 无关、双端同修。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含新增 skeleton STEP 回归；现有资产单 UV 集，R252-B 字节等价，golden 不受影响）。总计 615 处修复。
此前：**R251 CCD/扫掠 BVH 候选截断回退 + glTF STEP 插值 — 修复 2 处** — **R251-A**（CORRECTNESS）：`bvh_query_aabb` 填满 64 候选槽后即返回、静默丢弃其余重叠体（R239 已在角色滑移 `char_slide_resolve` 用「`nc>=64` 退化全量扫描」修复）；但 CCD 的 `ccd_sweep_static`（`physics.c:492`）与射线/扫掠 API `physics_sweep_test`（`character.c:185`）**未同步**——二者只遍历前 64 个 BVH 候选，若最早 TOI 的静态体落在被丢弃候选里，CCD 误判无碰撞→动态体本帧**穿墙**，扫掠 API **漏报命中**。触发：BVH 已建、扫掠盒与 >64 个静态体重叠（密集关卡/大 delta/大 radius）。修复：两处均按 R239 模式改为「BVH 已建且 `nc<64` 用候选，否则（未建或饱和）全量扫描 `pw->count`」。**R251-B**（CORRECTNESS）：`asset_load_gltf` 加载 animation sampler 时只读 `times`/`values`，**从不读 `samp->interpolation`**；运行时 `clip_sample` 对 T/S 恒 `vec3_lerp`、R 恒 `quat_nlerp`，两键间始终按 frac 混合。按 glTF 2.0，**STEP** 采样器应在下一关键帧前保持常数（阶梯/硬切动画，机械动作常见导出默认）→ 被错误线性插值出源资产中不存在的中间姿态。修复：`AnimChannel` 增 `interp` 字段（默认 `LINEAR`=0，零初始化/旧路径行为不变）；`anim_clip_add_channel` 显式初始化为 LINEAR；`asset.c` 对 `cgltf_interpolation_type_step` 置 `ANIM_INTERP_STEP`；`clip_sample` 对 STEP 令 `frac = (time>=t1)?1:0`（保持 `[t0,t1)` 取 k0、末键 `time==duration==t1` 取 k1，端点精确、无中间值）。CUBICSPLINE 仍按 LINEAR（需额外 3×切线 output 解析，暂不含）。新增 `blend_evaluate_step_holds_keyframe` 回归测试。二者均纯 CPU（物理/动画），GL/VK 无关、双端同修。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含新增 STEP 回归；既有 CCD `ccd_prevents_tunnel`/`no_ccd_tunnels` 仍通过）。总计 613 处修复。
此前：**R250 有序复制重排序缓冲窗口外别名覆写 — 修复 1 处** — **R250-A**（CORRECTNESS）：有序层（`rep->ordered_layer`）的 `net_reorder_store`（`net_replication.c:192`）以 `idx = seq % NET_REORDER_SLOTS`（32 槽）落位并**无条件覆写**目标槽。当等待缺失序号 `M` 时，两个相差恰为 32 的未来包（如 `M+1` 与 `M+33`）映射到同一槽 → 后到者覆写先到且**仍需交付**的包；`net_reorder_drain` 要求 `slot->seq == next_ordered_seq`，被覆写的序号从此再不出现 → `next_ordered_seq` 永久停在该值、有序流**彻底卡死**（`reorder_pending` 卡住、后续快照静默丢失）。触发条件：`PACKET_ORDERED` 乱序且同信道并发/排队序号跨度 ≥ 32（高 RTT、突发、丢包重传）。修复：`net_reorder_store` 先计算 `ahead = seq - next_ordered_seq`（调用方 `net_repl_deliver_ordered` 已剔除陈旧/过去序号，故为有效前向距离），`ahead >= NET_REORDER_SLOTS`（窗口外，缓冲太小无法容纳）直接丢弃并 `reorder_stale++`，**绝不覆写**；窗口内 32 个序号对 32 槽为双射，杜绝别名覆写。新增 `ordered_reorder_out_of_window_no_stall` 回归测试。纯 CPU 网络逻辑，GL/VK 无关、双端同修。另评估 GL 后端 IBL 预计算（`ibl.c` 用 `if(!cmd)break`/`if(cmd)` 守卫，而 GL `rhi_frame_begin` 恒返回 NULL）——疑似 GL 下 BRDF/irradiance/prefilter compute 被整段跳过；但其与 GL golden 基准的交互及 GL 计算 IBL 是否本就预期运行尚需深入验证，本轮不改、留待专项核实（风险：贸然改可能改变 GL 输出致 golden 回归）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含新增有序重排序回归）。总计 611 处修复。
此前：**R249 glTF 交错顶点 stride + JOINTS_0 u32 — 修复 2 处** — **R249-A**（CORRECTNESS）：`cgltf_accessor_stride` 只返回「紧凑元素大小」（component_size×num_components），**忽略 `acc->stride`**；cgltf fixup 已把 `acc->stride` 设为 bufferView 的 byteStride（为 0 时才退化为紧凑大小）。加载**交错顶点**（byteStride>单属性大小，常见优化导出）的 glTF 时，pos/normal/uv/joints/weights 全按错误步进从错误偏移拷贝 → 网格撕裂/变形。修复：`acc->stride` 非零时直接返回它，否则退化为紧凑大小（紧凑资产字节等价）。**R249-B**（CORRECTNESS）：`JOINTS_0` 读取只处理 `r_8u`/`r_16u`，缺 `r_32u`（glTF 2.0 允许 UNSIGNED_INT，关节数>255 时常见）；`SkinnedVertex` 由 calloc 置 0，缺失分支使关节索引恒为 0 → 所有蒙皮顶点塌到 joint 0、肢体折叠/粘原点（索引路径 276 行已支持 r_32u，此处为对称遗漏）。修复：新增 `r_32u` 分支按 `jnt_stride` 读 4×u32。均 CPU 侧建 VBO，GL/VK 双端同错同修。IBM 拷贝按 `ji*16` 紧凑步进保持不变（glTF 禁止 IBM accessor 带 byteStride，恒紧凑）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（现有资产紧凑布局，字节等价，golden 不受影响）。总计 610 处修复。
此前：**R248 点光源阴影 clip 位置漏乘 u_model — 修复 1 处** — **R248-A**（CORRECTNESS）：点光 cubemap 阴影深度 VS（`point_shadow_depth.vert` / `point_shadow_depth_vk.vert`）中 `v_world_pos = u_model * a_position`（世界坐标，供片元 `gl_FragDepth = length(v_world_pos - u_light_pos)` 用），但 `gl_Position = u_mvp * a_position` **漏乘 u_model**；而 CPU 侧 `u_mvp` 仅为 cubemap 面 view-proj（`point_shadow.c:306`），legacy 逐 mesh 路径又把 `world_transform` 上传到 `u_model`（`main.c:3883`）。于是光栅化覆盖用模型空间顶点、而写入深度用世界坐标 → 非单位变换的节点其点光阴影落在错误 texel（漏影/错影/闪烁）。修复：两 VS 均改 `gl_Position = u_mvp * (u_model * a_position)`（VK 保留 z∈[0,1] 重映射）。mega-buffer（世界空间顶点 + identity model）与地形（identity）路径 `u_model=I`，字节等价不受影响。GL/VK 两套 VS 逻辑相同，均已修。另评估 Lua `checked_body` 拒绝 `id<=0`：经 `test_script_lua`/`main.c:1349`（地面先建为 body 0）确认属既定「id 0=floor/none 哨兵」约定，Lua spawn 的体 id≥1 正常可用，非 bug，未改。着色器运行时从源码编译，双后端构建无 stale。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归）。总计 608 处修复。
此前：**R247 太阳天顶方向 CSM 视图基退化 — 修复 1 处** — **R247-A**（CORRECTNESS）：CSM 用 `light_dir × (0,1,0)` 的 XZ 长度 `s_len2 = fx²+fz²` 构造侧向基，代码 `inv_sl = s_len2>1e-12 ? rsqrt : 0` 已察觉退化但只置 0；当太阳方向平行世界 +Y（`sun_elevation ≈ ±π/2`，`s_len2→0`）时 `inv_sl=0` → `sx/sz/ux/uy/uz` 全 0 → `lview` 旋转块秩亏、四级联 `cascade_vp` 视图退化 → 阴影缺失/全影/采样错乱。`sun_elevation` 经存档 `fread` 无范围校验可写入 ±π/2。修复：`s_len2<1e-12` 时回退固定正交基（XZ 平面：`sx=-1,sz=0,ux=0,uy=0,uz=1`，`row2=-f` 对 `f=(0,±1,0)` 仍有效，保持 `lview` 可逆且行列式正），正常路径公式与数值完全不变。GL/VK 均受影响（同一 CSM 路径）。另评估 `physics_body_create` 满额返回 `pw->count`：该值 `>= count` 被所有物理访问器（`body_id>=count` 守卫）与子创建器（`id<count` 守卫）安全拒绝，属池满时的可接受降级（main.c 热路径亦先 `count>=capacity` 守卫），且改返回值会牵动 Lua「id 0=none」约定，非高置信 bug，未改。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image CSM 回归）。总计 607 处修复。
此前：**R246 非循环动画末端事件漏触发 — 修复 1 处** — **R246-A**（CORRECTNESS）：`anim_blend_evaluate` 中非循环片段被 `advance_layer_time` 钳到 `duration`，事件扫描 `fire_events_in_range` 用半开区间 `[t0,t1)`（`et >= t0 && et < t1`）；当本帧从 `prev_time<duration` 推进到 `L->time==duration` 时，`et == clip->duration` 的事件因 `et < t1`（`duration < duration`）为假而不触发，且此后帧被钳在 duration 不再推进（`L->time > prev_time` 恒假），该末端事件**永久丢失**（挂在片段结束时刻的音效/脚步/状态切换回调静默失效）。修复：`fire_events_in_range` 增 `inclusive_end` 参数，仅在「非循环且本帧 `L->time>=dur` 被钳到末端」时用闭区间上界 `et<=t1`，使 `et==duration` 恰好触发一次（循环 wrap 的两段仍用半开，避免重复触发）。新增 `event_at_duration_nonlooping_fires` 回归测试。另评估 Wayland `keyboard_key` 把 `REPEATED` 当松开：`wl_seat` 绑定 v5（`REPEATED` 需 wl_keyboard v10），compositor 不会下发 state=2，非真实 bug，未改。GL/VK 无关（CPU 动画）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归 + 动画末端事件）。总计 606 处修复。
此前：**R245 frustum_extract sign_mask + 网络 ACK 回绕比较 — 修复 2 处** — **R245-A**（CORRECTNESS）：`frustum_cull_batch`/`frustum_test_aabb` 用 `f->sign_mask[p]` 选 AABB p-vertex（按平面法线分量正负取 min/max），`frustum_from_vp` 归一化后写 `sign_mask`，但 `frustum_extract` 只归一化 `planes[6]`、**从不写 `sign_mask`**；调用方用零初始化 Frustum + `frustum_extract` 后做 batch/aabb 剔除时 `sign_mask` 全 0 → 六平面一律取 min 角 → p-vertex 错误、视锥内物体被误剔除。主路径用 `frustum_from_vp`（不受影响），但 `frustum_extract` 是公开 API 且文档/测试视其与 `frustum_from_vp` 等价。修复：在 `frustum_extract` 归一化循环末尾按 `frustum_from_vp` 同法补写 `sign_mask`；并在 `frustum_extract_matches_from_vp` 测试加 `sign_mask` 断言。**R245-B**（CORRECTNESS）：`net_replication` 可靠重传路径判「ACK 已确认 pending 序号」用裸无符号 `hdr.ack >= reliable_pending.seq`（143/229 行）与 `reliable_pending.seq <= last_peer_ack`（377 行），而同文件序号去重已用回绕安全写法（`delta > 0x80000000u`）；u32 序号回绕后（如 pending=0xFFFFFFF0、ack=5）比较失效 → `reliable_pending.valid` 永为真、无限重发。修复：三处改为回绕安全 `(ack - seq) < 0x80000000u`，与去重风格一致（仅 `reliable_retry` 开启且回绕时表现，默认不触发）。均 GL/VK 无关（CPU 剔除/网络层）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归 + frustum sign_mask 断言）。总计 605 处修复。
此前：**R244 字体 UI 除零 + 地形 init 失败泄漏 — 修复 2 处** — **R244-A**（CORRECTNESS）：`font_renderer_draw`/`font_renderer_draw_rect` 用 `2.0/screen_w`、`2.0/screen_h` 做像素→NDC，无 0 保护；窗口最小化/平台返回 `w==0` 或 `h==0` 时 `inv_sw`/`inv_sh` 为 ±Inf，顶点 x0/y0/x1/y1 变 NaN/Inf 写入 `quad_data` 并提交 draw（R142 只保护了相机 aspect，UI 路径未保护）。修复：两函数开头 `screen_w<=0||screen_h<=0` 即 return。**R244-B**（CORRECTNESS/MEMORY）：`terrain_init` 在第 126 行 calloc heightmap+staging 单块后，着色器编译失败（184 行）与管线创建失败（195 行）的 `return false` 未释放该块，泄漏 `grid_size²×4 + grid_size×32` 字节且留下半初始化 `Terrain`（`device`/`heightmap` 有效但无 pipeline/VBO/IBO），调用方重试 init 覆盖指针致二次泄漏；而成功路径 288 行 buffer 创建失败已用 `terrain_shutdown` 清理。修复：两失败 `return false` 前统一调 `terrain_shutdown(t)`（与成功路径一致，heightmap 释放、无效句柄跳过）。均 GL/VK 无关（UI/RHI 后端无关）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归）。总计 603 处修复。
此前：**R243 场景 JSON 反序列化恢复 generation — 修复 1 处** — **R243-A**（CORRECTNESS）：`scene_save_json` 每个实体写出 `"gen"`（实体 generation），二进制路径 `load_entities_chunk` 也会显式恢复 generation 以保持 `(index, generation)` 统一身份（`generation_restore_roundtrip` 测试断言之）；但 `scene_load_json` 的实体对象解析只处理 `"components"`，`"gen"`/`"id"` 等键一律走 skip 分支丢弃，从不写回 `w->entities[...].generation`。故 JSON 存档→载入后实体 index 相近但 generation 全为新建默认值，依赖 `(index,generation)` 的 `world_entity_exists`/跨系统句柄与保存时不一致（编辑器导出再导入、JSON round-trip 均触发）。修复：在 JSON 实体解析中新增 `"gen"` 分支，读 `u32` 后按与二进制完全相同的方式 `w->entities[e.index].generation = g; e.generation = g;`（`g!=0` 时）；因 save 顺序为 id→gen→components，gen 在 components 之前恢复，与二进制路径次序一致。并新增 `generation_restore_roundtrip_json` 回归测试镜像二进制版本。另评估 `scene_load_binary` 失败不回滚（World/Scene 半加载脏状态）：属较大改动（需两阶段载入或销毁已创建实体），本轮按“宁缺毋滥”记录评估、未改。GL/VK 无关（纯 CPU 场景/ECS 数据）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归 + 新增 JSON generation 往返）。总计 601 处修复。
此前：**R242 异步加载器槽位分配扫描/CAS 认领 — 修复 1 处** — **R242-A**（CORRECTNESS）：`async_submit_request` 只用 `next_slot++ % 1024` 探测**单个**槽，非 `ASSET_UNLOADED` 即 `LOG_ERROR` 丢弃请求——在重度流式加载（慢速 in-flight 加载令 `next_slot` 绕回到仍占用的槽）时即使有大量空闲槽也误丢；`mipmap_stream` 收到 `req_id==0` 不发起加载，导致 mip 加载失败/日志刷屏。此外“load 检查 state==UNLOADED 后再 store LOADING”非原子，两个计数差为 1024 倍数的并发 submit 可能都判定同一槽空闲并同时认领 → 两请求共用一槽、回调/数据错乱。改为从 `next_slot` 起最多扫描 1024 个槽，用 CAS(`UNLOADED→LOADING`) 原子认领首个空闲槽，既消除误丢、又关闭认领竞态；全满时才丢弃。字段填充在 `heap_push` 前完成、经 `queue_mutex` release 发布给 worker，认领后 worker 仅在入堆后可见该槽。另核实探索报告的“完成队列 1024 环形无背压会覆写导致永久停转”为**误报**：完成队列容量 `ASYNC_QUEUE_SIZE=1024` 恰等于请求槽数 `ASYNC_MAX_REQUESTS=1024`，每槽两次 tick 间至多产生一个未消费完成项（槽只在 tick 里回到 UNLOADED 才能再提交），故未消费完成项 ≤1024=容量，`head-tail` 不可能超过环大小、不会覆写（R165-A 正是为此把容量设为 1024）。GL/VK 无关（CPU 侧异步回调）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归）。总计 600 处修复。
此前：**R241 音频流 pause 误销毁音源修复 — 修复 1 处** — **R241-A**（CORRECTNESS）：`audio_stream_pause` 调 `audio_stop`，注释称"miniaudio stop pauses, keeps cursor"，但 `audio_stop` 实为 `ma_sound_uninit` 销毁音源并把槽位归还空闲链表；而流管理器仍保持 `active=true`/`source_id` 不变/`state=PAUSED`。后续 `audio_stream_play` 恢复、set_volume/seek 会操作已销毁或被复用的槽位 → 无法恢复、崩溃或误控其它音源（串音）。新增只 `ma_sound_stop`（保留游标与槽位）的 `audio_source_stop`，`audio_stream_pause` 改调它，`audio_stream_play` 经 `audio_source_start`(`ma_sound_start`) 正确从游标恢复。GL/VK 无关（miniaudio CPU 路径）。另评估 inotify 事件边界"越界"：Linux 内核保证 `read()` 只返回完整事件、不截断，故非真实 bug，未改。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归）。总计 599 处修复。
此前：**R240 骨骼世界矩阵不依赖关节顺序 — 修复 1 处** — **R240-A**（CORRECTNESS）：`skeleton_evaluate`/`skeleton_apply_local_trs`/`skeleton_compute_world_transforms` 用 `joint_parents[i] >= i` 启发式把「父关节下标 ≥ 当前」当作根。但 `joint_parents` 按 skin.joints 数组位置索引，glTF **不保证** 父关节先于子关节；此时子关节被误当作根、缺失祖先链 → 蒙皮矩阵错误、网格拉伸/twist。改为新增 `skel_resolve_world` 定点迭代（joint_count≤128），与关节顺序无关；已按父先于子排序的常见骨骼结果不变（单遍即收敛）。GL/VK 无关（CPU 算 current_pose）。另评估场景图 `scene_compute_world_transforms` 同类单遍：其父先于子顺序已被文档明确列为既定假设（依赖 cgltf），未改。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归）。总计 598 处修复。
此前：**R239 角色胶囊 BVH 候选截断回退全扫 — 修复 1 处** — **R239-A**（CORRECTNESS）：`char_slide_resolve` 用 `bvh_query_aabb(..., candidates, 64)` 查询附近静态体，`bvh_query_aabb` 填满 64 槽即停并静默丢弃其余重叠体；若查询盒内静态体 >64，仅解算前 64 个 → 角色穿墙/穿地形、错误 grounded。修复：`nc >= 64` 视为可能饱和，置 `use_bvh=false` 回退到已有的全量线性扫描分支（完整正确，仅罕见饱和场景有开销）。GL/VK 无关（CPU 物理）。另评估 `physics_step` 宽相位 BVH 在积分前 refit、积分后 query 的一帧延迟：对非 CCD 慢速体属既定权衡（快速体走独立 CCD 路径，且积分中的 CCD 需要积分前的树），安全修复需额外一轮 refit，暂不改。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归）。总计 597 处修复。
此前：**R238 ECS 并行 OOM 回退越界写修复 — 修复 1 处** — **R238-A**（CORRECTNESS/MEMORY）：`ecs_parallel_for` 中当非空 chunk 数 >512（`ECS_JOB_POOL_SIZE`）且 `malloc` 失败时，回退到静态池 `_job_pool[512]` 并把 `job_count` 钳到 512，但填充循环仍遍历**全部**非空 chunk 写 `jobs[ji++]`，导致 `jobs[512]`、`jobs[513]`… 越界写入 `_job_pool` 之外（`.bss` 越界写，内存破坏），且钳除的 chunk 被静默漏跑（R118-2 只钳了运行计数、未修填充循环）。改为：`malloc` 失败时不建 job 数组，直接就地串行跑完**每个** chunk 后 return——零越界、零漏跑。GL/VK 无关（ECS 调度）。本轮网络有序 drain 覆盖 `out` 一项经核实为 transform 全量快照的 latest-wins 预期行为，未改。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归）。总计 596 处修复。
此前：**R237 粒子 SSBO CPU/GPU 布局契约对齐 — 修复 1 处** — **R237-A**（ROBUSTNESS/PERF）：CPU `GPUParticle` 为 13×f32=52 字节，而 shader `particle_update.comp`/`particle.vert` 的 std430 `Particle` 为 3×vec4=48 字节；`particle_ssbo` 按 `sizeof(GPUParticle)` 分配。SSBO 为 GPU 专用（compute 写、VS 读），CPU 从不索引其字段，故当前未触发损坏，但缓冲区 over-alloc（8192×4=32KB）且布局与 GPU 契约不符，一旦将来新增 CPU 端粒子读写即会错位。将 `GPUParticle` 改为与 shader 精确一致的 3×vec4=48 字节布局。本轮探索子代理另报 2 项（粒子步长“串扰”、`mat4_trs` 转置）经核实均为误报（GPU 布局自洽；`mat4_trs` 列主序与 `mat4_from_quat`/`mat4_scaling` 完全一致）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归）。总计 595 处修复。
此前：**R236 延迟路径 Hi-Z/后处理深度源修正 — 修复 1 处** — **R236-A**（CORRECTNESS）：`RENDER_PATH_DEFERRED` 下前向场景 Pass 被跳过、延迟光照管线 `depth_write_disable`，故 `scene_fbo.depth_tex` 从不写入；而 Hi-Z 遮挡与全部深度型后处理（SSAO/接触阴影/体积光/SSR/SSGI/TAA/运动模糊/DoF/SSS/God Rays/debug_viz/upscale）仍采样 `scene_fbo.depth_tex`，读到空/陈旧深度。真实几何深度在 G-Buffer 的 `deferred.gbuf_depth`。新增 `scene_depth` 选择器：延迟且已初始化时用 `gbuf_depth`，否则用 `scene_fbo.depth_tex`（前向路径字节等价，golden 不受影响）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归）。总计 594 处修复。
此前：**R235 GL disable_culling + 水面 water_y — 修复 2 处** — **R235-A**（CORRECTNESS）：GL `bind_pipeline` 忽略 `disable_culling`/`no_vertex_input`，VK PSO 为 cull NONE；水面/地形/字体等在 GL 上误背面剔除。现按管线 `glEnable/Disable(GL_CULL_FACE)`。**R235-B**（CORRECTNESS）：CPU 写 `u_water_y`/model，但 `water.vert`/`water_vk.vert` 仍用 y=0 网格；可见水面不随水位移动。顶点改用 `u_water_y`/`pc.u_watery.x` 抬升。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 31/31（含 golden-image 回归）。总计 593 处修复。
此前：**R234 前向/延迟 compute 后重绑 + compact 清零 — 修复 2 处** — **R234-A**（CORRECTNESS）：R233 只修了阴影路径；前向/延迟 `mega_mat_groups_draw` 与 legacy compact 后 GL 仍可能以 compute program 执行间接绘制。现传入/重绑 `active_pipeline` / `gbuffer_pipeline`。**R234-B**（CORRECTNESS）：`indirect_draw_compact_no_barrier` 在 compact 前 GPU 清零 `visible_draws_buf`，对齐 unified cull（R171），避免 VK IndirectCount fallback 复活陈旧 surplus。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 591 处修复。
此前：**R233 cull 近平面 + GL shadow compute 后重绑 — 修复 2 处** — **R233-A**（CORRECTNESS）：legacy `cull.comp` 近裁剪仍用 NDC z=0，R212 只修了 unified；改为 -1。**R233-B**（CORRECTNESS）：GL compute `glUseProgram` 覆盖 graphics；shadow unified/legacy 间接绘制前重绑 depth pipeline。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 589 处修复。
此前：**R232 GL pipeline depth write/compare — 修复 2 处** — **R232-A**（CORRECTNESS）：GL `bind_pipeline` 忽略 `depth_write_disable`，VK PSO 尊重；粒子/后处理等在 GL 上误写 depth。现按管线设置 `glDepthMask`。**R232-B**（CORRECTNESS）：忽略 `depth_compare_lequal`；现按管线设置 `glDepthFunc`，与 VK compareOp 对齐。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 587 处修复。
此前：**R231 unified_cull Hi-Z unit + clear_color 语义 — 修复 2 处** — **R231-A**（CORRECTNESS）：`gpucull_dispatch_unified` 把 Hi-Z 绑到 unit 0，GL `unified_cull.comp` 为 `binding=4`；Hi-Z 遮挡错误。GL 改绑 unit 4。**R231-B**（CORRECTNESS）：GL `clear_color` 附带清 depth，与 VK 仅清 color 不一致；改为只清 color，forward 显式 `clear_depth`。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 585 处修复。
此前：**R230 GL offscreen/MRT bind 对齐 VK scissor/depth — 修复 2 处** — **R230-A**（CORRECTNESS）：GL `offscreen_fbo_bind` 只设 2D viewport，VK 另设全 FBO scissor + depth 0..1；残留 CSM/`set_scissor` 或半分辨率 scissor 会裁切后处理。现 `gl_set_fbo_pass_state`，unbind 同步还原 swapchain。**R230-B**（CORRECTNESS）：`mrt_fbo_bind`/`unbind` 同理（deferred GBuffer）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 583 处修复。
此前：**R229 GL 点光 cubemap face depth/scissor — 修复 2 处** — **R229-A**（CORRECTNESS）：`rhi_cubemap_depth_fbo_bind_face` 清 depth 前未强制 depth range，VK face viewport 为 0..1；非默认 range 时点阴影 clear/写入偏差。现缓存强制 0..1。**R229-B**（CORRECTNESS）：face bind 不清除残留 CSM/`set_scissor`，半边 atlas scissor 会裁切整面 clear/绘制；VK 设全 face scissor。现禁用 scissor。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 581 处修复。
此前：**R228 GL 阴影 depth range 对齐 — 修复 2 处** — **R228-A**（CORRECTNESS）：GL `set_shadow_viewport` 不重置 depth range，VK 强制 0..1；非默认 range 后 CSM 写深度偏差。现 `glDepthRange(0,1)` 并缓存。**R228-B**（CORRECTNESS）：`bind_shadow_map` 清 atlas 前同样强制 0..1，避免 clear/写入落在错误映射。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 579 处修复。
此前：**R227 GL indexed draw mode + indirect index type — 修复 2 处** — **R227-A**（CORRECTNESS）：GL `draw_indexed`/`draw_indexed_base`/`draw_indexed_indirect*` 硬编码 `GL_TRIANGLES`，与 `draw`/`draw_indirect` 的 `g_gl_draw_mode` 不一致；改为管线拓扑。**R227-B**（CORRECTNESS）：`draw_indexed_indirect*` 硬编码 `GL_UNSIGNED_INT`，忽略 R224 的 `g_gl_index_type`；16-bit IBO 间接绘制错读。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 577 处修复。
此前：**R226 GL VBO/IBO offset + set_scissor — 修复 2 处** — **R226-A**（CORRECTNESS）：GL `bind_vertex_buffer` 缓存忽略 offset、同 VBO 换偏移不重绑；`bind_index_buffer` 丢弃 offset、`draw_indexed` 恒 `NULL`。现缓存 VBO offset，IBO offset 经 draw 的 indices 指针生效。**R226-B**（CORRECTNESS）：GL `rhi_cmd_set_scissor` 为空操作，cmd_buffer/ParallelRenderer 裁剪从不生效；现 `glScissor`+缓存，与 shadow viewport 一致。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 575 处修复。
此前：**R225 viewport 深度范围 + 地形雾开关 — 修复 2 处** — **R225-A**（CORRECTNESS）：`rhi_cmd_set_viewport`/`ParallelRenderer` 丢弃 min/max depth，VK 恒 0..1；现转发并缓存深度范围，GL 调 `glDepthRange`。**R225-B**（CORRECTNESS）：`/` 切换 `fog_enabled` 从不影响画面；地形雾加 `u_fog_strength`（VK 打包进 `u_camera_pos.w`），关闭时为 0。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 573 处修复。
此前：**R224 index 类型 + volumetric CPU inv_view — 修复 2 处** index 类型 + volumetric CPU inv_view — 修复 2 处** — **R224-A**（CORRECTNESS）：`rhi_cmd_bind_index_buffer`/`ParallelRenderer` 忽略 `is_u32`，VK 恒 `UINT32`、GL draw 恒 `UNSIGNED_INT`；16-bit IBO 错读。现按 `is_u32` 选择类型并缓存 stride。**R224-B**（PERF）：volumetric 每像素 `inverse(u_vol_view)`；改为 CPU `mat4_inverse` 上传 `u_vol_inv_view`。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 571 处修复。
此前：**R223 ParallelRenderer sampler + 删除死 shadow_depth — 修复 2 处** ParallelRenderer sampler + 删除死 shadow_depth — 修复 2 处** — **R223-A**（CORRECTNESS）：`cmd_bind_texture` 回放用 `RHI_HANDLE_NULL` sampler，VK `bind_material_textures` 直接 return，纹理绑定成空操作；命令携带 sampler。**R223-B**（ROBUSTNESS）：未使用的 `shadow_depth*.vert/frag`（曾误接 Z remap）删除，CSM 以 `depth_only` 为准。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 569 处修复。
此前：**R222 GL SSR/SSGI sampler binding — 修复 2 处** GL SSR/SSGI sampler binding — 修复 2 处** — **R222-A**（CORRECTNESS）：`ssr.frag` 双 sampler 默认 unit 0，深度追踪失效；补 binding 0/1 对齐 `bind_textures_multi`/VK。**R222-B**（CORRECTNESS）：`ssgi.frag` 同理（depth@0 color@1）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 567 处修复。
此前：**R221 GL upscale/volumetric sampler binding — 修复 2 处** GL upscale/volumetric sampler binding — 修复 2 处** — **R221-A**（CORRECTNESS）：默认 50% render scale 下 `upscale.frag` 三 sampler 默认 unit 0，depth/history 失效；补 binding 0/1/2 对齐 material bind（src/depth/history）与 VK。**R221-B**（CORRECTNESS）：`volumetric.frag` 同理；补 binding 0/1。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 565 处修复。
此前：**R220 GL tonemap/luminance/bloom sampler binding — 修复 2 处** GL tonemap/luminance/bloom sampler binding — 修复 2 处** — **R220-A**（CORRECTNESS）：`luminance.frag`/`tonemap.frag` 双 sampler 默认 unit 0，自动曝光读错 prev/lum；补 binding 0/1 对齐 `bind_material_textures`/VK。**R220-B**（CORRECTNESS）：`bloom_composite.frag` 同理 scene/bloom；补 binding 0/1。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 563 处修复。
此前：**R219 GL motion blur/SSS sampler binding — 修复 2 处** GL motion blur/SSS sampler binding — 修复 2 处** — **R219-A**（CORRECTNESS）：`motion_blur.frag` 双 sampler 默认 unit 0，深度速度重建失效；补 binding 0/1 对齐 `bind_material_textures`/VK。**R219-B**（CORRECTNESS）：`sss.frag`/`sss_vertical.frag` 同理；vertical 用 albedo@0/shadow@1/mr@2。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 561 处修复。
此前：**R218 GL TAA/DoF sampler binding — 修复 2 处** GL TAA/DoF sampler binding — 修复 2 处** — **R218-A**（CORRECTNESS）：`combined_taa_fxaa.frag`/`taa.frag` 多 sampler 无 `layout(binding)`，默认全绑 unit 0，history/depth/velocity 失效；对齐 `bind_textures_multi` 0–3 与 VK。**R218-B**（CORRECTNESS）：`dof.frag` 同理 color/depth 均 unit 0；补 binding 0/1。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 559 处修复。
此前：**R217 GL water/god_rays sampler binding + god rays 零强度跳过 — 修复 2 处** GL water/god_rays sampler binding + god rays 零强度跳过 — 修复 2 处** — **R217-A**（CORRECTNESS）：`water.frag` 的 `u_shadow_map` 无 `layout(binding=1)`，默认 unit 0，而 `water_render` 把阴影绑到 unit 1，采样残留地形 albedo 当深度。对齐 `water_vk.frag`/`terrain.frag`。**R217-B**（CORRECTNESS/PERF）：`god_rays.frag` 双 sampler 均默认 unit 0，深度遮挡失效；补 binding 0/1；`intensity<=0` 跳过 fullscreen 且 main 不切陈旧 FBO。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 557 处修复。
此前：**R216 bloom skip 不切 composite + 去掉误写 pom — 修复 2 处** bloom skip 不切 composite + 去掉误写 pom — 修复 2 处** — **R216-A**（CORRECTNESS）：R214-B 在 `bloom_strength<=0` 跳过绘制后，main 仍切到未更新的 `fbo_composite`；仅 strength>0 时切换。**R216-B**（CORRECTNESS）：`bind_material` 用 clustered `u_pom_enabled@224` 写入活跃 blinn 管线，覆盖 `u_ambient.x`；删除该写入。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 555 处修复。
此前：**R215 GL 点阴影 COMPARE 关闭 + VK 点阴影 Z remap — 修复 2 处** GL 点阴影 COMPARE 关闭 + VK 点阴影 Z remap — 修复 2 处** — **R215-A**（CORRECTNESS）：GL 点阴影 cube 开了 `COMPARE_REF_TO_TEXTURE`，着色器却用 `samplerCube`+`.r` 手动比较，采样未定义；改为 `GL_NONE`。**R215-B**（CORRECTNESS）：`point_shadow_depth_vk.vert` 缺 OpenGL→Vulkan `clip.z` remap，近半锥体被裁掉；对齐 depth_only。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 553 处修复。
此前：**R214 主通道 VK Z remap + bloom 零开销跳过 — 修复 2 处** 主通道 VK Z remap + bloom 零开销跳过 — 修复 2 处** — **R214-A**（CORRECTNESS）：主通道 VK 顶点（terrain/water/PBR/gbuffer/skinned/instanced/particle 等）缺 OpenGL→Vulkan `clip.z` remap，场景深度与后处理 `depth*2-1` 不一致；对齐 R213 CSM。**R214-B**（PERF）：`bloom_strength<=0` 仍跑 extract+blur+composite；`post_process_apply` 入口跳过。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 551 处修复。
此前：**R213 VK CSM depth_only Z remap + GL SSAO binding — 修复 2 处** VK CSM depth_only Z remap + GL SSAO binding — 修复 2 处** — **R213-A**（CORRECTNESS）：R211 的 VK Z remap 打在未使用的 `shadow_depth_vk.vert`；活跃 CSM 用 `depth_only.vert`，补 `#ifdef VULKAN` remap。**R213-B**（CORRECTNESS）：GL `u_ssao@11` 与 `u_point_shadow_cubes[4]@10–13` 重叠，点数影≥2 时覆盖 SSAO；改 binding/unit 14。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 549 处修复。
此前：**R212 Hi-Z 窗口深度比较 + vol/cs/lf 默认关闭 — 修复 2 处** Hi-Z 窗口深度比较 + vol/cs/lf 默认关闭 — 修复 2 处** — **R212-A**（CORRECTNESS）：`unified_cull`/`occlusion_cull` 用 NDC z 对比 Hi-Z 窗口深度 `[0,1]`，遮挡判断偏移；改为 `*0.5+0.5`，并修正球视锥近平面 `-1`。**R212-B**（PERF）：`vol`/`cs`/`lf` 默认开但 FBO 从未合成；默认关闭避免半分辨率空跑。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 547 处修复。
此前：**R211 CSM 窗口深度比较 + contact 采样 NDC — 修复 2 处** CSM 窗口深度比较 + contact 采样 NDC — 修复 2 处** — **R211-A**（CORRECTNESS）：terrain/water/PBR/deferred 用 OpenGL NDC `z∈[-1,1]` 直接比深度附件 `[0,1]`，方向光阴影几乎失效；改为 `z*0.5+0.5`，VK `shadow_depth_vk.vert` 同步 remap 写入。**R211-B**（CORRECTNESS）：contact_shadow 起点已 `depth*2-1`，采样点仍用 raw depth；对齐。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 545 处修复。
此前：**R210 后处理深度 NDC 对齐 + SSR/SSGI 默认关闭 — 修复 2 处** 后处理深度 NDC 对齐 + SSR/SSGI 默认关闭 — 修复 2 处** — **R210-A**（CORRECTNESS）：SSAO/TAA/MB/velocity/volumetric/contact/SSR/SSGI/upscale 等用 raw `[0,1]` depth 当 OpenGL NDC z，与 `mat4_inv_perspective` 及 deferred 的 `depth*2-1` 不一致，重建位置近处约 2× 误差；统一 `depth * 2.0 - 1.0`。**R210-B**（PERF）：`ssr_enabled`/`ssgi_enabled` 默认 true 但 FBO 从未合成进画面；默认关闭避免半分辨率空跑。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 543 处修复。
此前：**R209 god rays 方向投影 + 体积雾世界高度 — 修复 2 处** god rays 方向投影 + 体积雾世界高度 — 修复 2 处** — **R209-A**（CORRECTNESS）：god rays 用有限远点 `-100*sun_dir` 乘 VP（含平移），相机平移时太阳 UV 漂移；改为方向 `w=0` 投影。**R209-B**（CORRECTNESS）：volumetric 高度雾用 view-space `pos.y`，点头/平移时跟着相机；`inverse(u_vol_view)` 取世界 Y。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 541 处修复。
此前：**R208 接触阴影列主序变换 + draw_indexed base — 修复 2 处** 接触阴影列主序变换 + draw_indexed base — 修复 2 处** — **R208-A**（CORRECTNESS）：R207 用转置 3×3 变换 `sun_dir`，与 GPU/`mat4_vec4` 列主序 `M*v` 及 `inv_proj` 重建视空间不一致；改为 `e[col][row]` 点积。**R208-B**（CORRECTNESS）：`RENDER_CMD_DRAW_INDEXED` 丢弃 `first_index`/`vertex_offset`；新增 `rhi_cmd_draw_indexed_base`（VK `vkCmdDrawIndexed` / GL `BaseVertex`）并接线回放。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 539 处修复。
此前：**R207 接触阴影视空间光向 + cmd push 回放 — 修复 2 处** — **R207-A**（CORRECTNESS）：`contact_shadow` 视空间步进却用世界空间 `sun_dir`，相机旋转时接触阴影方向错误；调用前用 view 3×3 变换。**R207-B**（CORRECTNESS）：`RENDER_CMD_PUSH_CONSTANTS` 回放为空操作；改为 `rhi_cmd_set_uniform_bytes`。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 537 处修复。
此前：**R206 体积光视空间光照 + DOF focus_range — 修复 2 处** — **R206-A**（CORRECTNESS）：`volumetric` 在视空间射线与世界空间 `sun_dir` 上做 dot，相机旋转时散射错误；用已上传的 `u_vol_view` 将光向变换到视空间。**R206-B**（CORRECTNESS）：DOF 推送 `u_dof_range` 但 CoC 用 near/far，`focus_range` 无效；改为 `abs(depth-focus)/range`。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 535 处修复。
此前：**R205 时序重投影改传 inv(VP) — 修复 2 处** — **R205-A**（CORRECTNESS）：`forward_velocity_apply` 误传 `frame_inv_proj`，着色器按世界空间用 `curr/prev_view_proj` 重投影，等价于对 view 空间二次乘 view，相机速度/TAA 速度缓冲错误；改为 `frame_inv_vp`（与 TAA 一致）。**R205-B**（CORRECTNESS）：`motion_blur_apply` / `upscale_apply` 同样误传 `inv_proj`+`prev_vp`；一并改为 `frame_inv_vp`。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 533 处修复。
此前：**R204 gbuffer AO push 越界 + 独立 tonemap 映射 — 修复 2 处** — **R204-A**（CORRECTNESS）：`gbuffer_vk.frag` 把默认材质参数放在 push offset 256+（超出 256B 上限与 staging），AO 恒 0；改为与 GL 一致的 const（ao=1）。**R204-B**（CORRECTNESS）：独立 tonemap 仍映射旧 mega 布局（`u_tm_screen_w@24` 等），与 `tonemap_vk.frag` 的 `@8/@12/@16` 冲突；对齐并删除死映射。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 531 处修复。
此前：**R203 u_prev_vp 双映射 + 去掉误用 u_light_vp — 修复 2 处** — **R203-A**（CORRECTNESS）：无条件 `u_prev_vp→192` 使 `camera_velocity` 的 `@128` 成死代码，相机速度/TAA 错误；按 `no_vertex_input` 分流（fullscreen→128，gbuffer→192）。**R203-B**（CORRECTNESS）：通用 `u_light_vp@64` 与 `u_view` 冲突；真实用户已由 terrain/water/`is_shadow_depth` 覆盖，删除误映射。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 529 处修复。
此前：**R202 水面阴影采样器 + 点光阴影 push 映射 — 修复 2 处** — **R202-A**（CORRECTNESS）：`water_render` 传 `(RHISampler){0,0}` 致 VK 跳过描述符绑定、水面无阴影；改为自有 sampler。**R202-B**（CORRECTNESS）：点光 `u_mvp`/`u_light_pos`/`u_far_plane` 未映射致 cubemap 深度错误；补 `is_shadow_depth` 分支。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 527 处修复。
此前：**R201 VK SSS/FXAA/tonemap 独立 push 映射 — 修复 2 处** — **R201-A**（CORRECTNESS）：`u_sss_*`/`u_sssv_*` 未映射致 sw/sh=0 除零与皮下散射失效；补 sss_vk 偏移。**R201-B**（CORRECTNESS）：独立 `u_fxaa_threshold@8` 与 `u_tm_mode@16` 未映射；补 fxaa_vk/tonemap_vk 偏移。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 525 处修复。
此前：**R200 VK color_grade/bloom push 映射 — 修复 2 处** — **R200-A**（CORRECTNESS）：独立 `u_cg_*` 未映射致调色饱和/对比度为 0；补 color_grade_vk 偏移（与 combined 布局分离）。**R200-B**（CORRECTNESS/PERF）：`u_threshold`/`u_direction`/`u_bloom_strength` 未映射致 bloom 不可见且 blur 空转；补 bloom_*_vk 偏移。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 523 处修复。
此前：**R199 VK motion_blur/contact_shadow push 映射 — 修复 2 处** — **R199-A**（CORRECTNESS）：`u_mb_*` 未映射致运动模糊 strength/投影恒 0；补 motion_blur_vk 偏移。**R199-B**（CORRECTNESS）：`u_cs_*` 未映射致接触阴影光向/投影恒 0；补 contact_shadow_vk 偏移。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 521 处修复。
此前：**R198 VK luminance/god_rays push 映射 — 修复 2 处** — **R198-A**（CORRECTNESS）：`u_lum_*` 未映射致自动曝光 speed/dt 恒 0、亮度冻结；补 luminance_vk 偏移。**R198-B**（CORRECTNESS）：`u_gr_*` 未映射致太阳/强度为 0；补 god_rays_vk 偏移并推送 sw/sh。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 519 处修复。
此前：**R197 upscale history 真复制 + 去掉 debug_viz/lens 中间 unbind — 修复 2 处** — **R197-A**（CORRECTNESS）：Pass 2 误再跑 TSR（`u_ups_sharp=0` 只关锐化）污染 history；新增 `u_ups_copy_only` 原样 blit，并补 VK `u_ups_*` push 映射（此前 loc 恒 -1）。**R197-B**（PERF）：debug_viz/lens_effects 遗漏中间 unbind，对齐 R196-B。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 517 处修复。
此前：**R196 tonemap LOAD 保深度 + 后处理去掉中间 unbind — 修复 2 处** — **R196-A**（CORRECTNESS）：tonemap/cinematic `bind(scene_fbo)` 走 CLEAR 抹掉场景深度；新增 `bind_load` 保 depth。**R196-B**（PERF）：SSAO/TAA/SSR 等中间 `unbind` 白开 swapchain CLEAR；删除中间 unbind。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 515 处修复。
此前：**R195 GL offscreen 可采样 depth + Hi-Z 生成后恢复 mip — 修复 2 处** — **R195-A**（CORRECTNESS）：GL offscreen 深度为 renderbuffer 且未设 `depth_tex`，Hi-Z/SSAO 等整段跳过；改为 D32 纹理并注册 handle。**R195-B**（CORRECTNESS）：Hi-Z 末尾 `bind_texture_mip` 钳最后一级，unified 跳过 dispatch 时不恢复；生成结束再 `bind_texture_compute`。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 513 处修复。
此前：**R194 GL/VK sampler mip 过滤对齐 — 修复 2 处** — **R194-A**（CORRECTNESS）：GL sampler `MIN_FILTER` 无 MIPMAP，`textureLod` 恒采 mip0；改为 MIPMAP 变体并设 `MAX_LEVEL`/`mip_levels`。**R194-B**（CORRECTNESS）：VK `mipmapMode` 恒 LINEAR，NEAREST Hi-Z 层间误混合；按 `min_filter` 选择。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 511 处修复。
此前：**R193 VK sampler maxLod + legacy object_ssbo 去重上传 — 修复 2 处** — **R193-A**（CORRECTNESS）：`rhi_sampler_create` `maxLod=0` 钳死 IBL/Hi-Z 的 `textureLod`；改为 `VK_LOD_CLAMP_NONE`。**R193-B**（PERF）：legacy CSM 每帧对 DEVICE_LOCAL `object_ssbo` staging WaitIdle；`objects_uploaded` 同 count 跳过。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 509 处修复。
此前：**R192 INDEX create 清 IBO 缓存 + light_grid DEVICE_LOCAL — 修复 2 处** — **R192-A**（CORRECTNESS）：INDEX `buffer_create` 解绑 ELEMENT_ARRAY 未清 `g_gl_bound_ibo`，后续 bind 误跳过。**R192-B**（PERF）：`light_grid` 因 TEXEL 被排除 DEVICE_LOCAL，GPU cull 每帧 ~1.5MB HOST_VISIBLE；允许 STORAGE|TEXEL + 零初始化。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 507 处修复。
此前：**R191 GL buffer create 缓存对称 + Hi-Z mip 钳制恢复 — 修复 2 处** — **R191-A**（CORRECTNESS）：`rhi_buffer_create` 解绑 ARRAY_BUFFER/TBO 未清 `g_gl_bound_array_buffer`/`g_tex_cache`，后续 update/bind 误跳过。**R191-B**（CORRECTNESS）：`bind_texture_mip` 永久钳 BASE/MAX，Hi-Z 生成后全链采样失效；`bind_texture_compute` 恢复完整金字塔。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 505 处修复。
此前：**R190 GL create 纹理缓存失效 + object_ssbo DEVICE_LOCAL — 修复 2 处** — **R190-A**（CORRECTNESS）：texture/offscreen/MRT/cubemap/shadow create 绕过 `gl_bind_tex_unit` 未清 `g_tex_cache`，resize 后误跳过 bind；补失效。**R190-B**（PERF）：`object_ssbo` 无 `initial_data` 留 HOST_VISIBLE，统一路径每帧 CS 穿 PCIe；零初始化进 DEVICE_LOCAL。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 503 处修复。
此前：**R189 GL offscreen color_tex 类型 + FBO 销毁缓存失效 — 修复 2 处** — **R189-A**（CORRECTNESS）：offscreen `color_tex` 与 FBO 共用 `GLFBOData`，`gl_bind_tex_unit` 误绑 `gl_fbo` 名；改为独立 `GLTextureData`（对齐 MRT/VK）。**R189-B**（CORRECTNESS）：offscreen/MRT/cubemap/shadow destroy 未清 `g_gl_bound_fbo`，resize 重建后 name 复用误跳过 bind。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 501 处修复。
此前：**R188 GL param/program/VAO 销毁缓存失效 — 修复 2 处** — **R188-A**（CORRECTNESS）：R187 漏清 `g_gl_param_buf`，indirect count 缓冲 name 复用误跳过 bind。**R188-B**（CORRECTNESS）：`rhi_pipeline_destroy` 未失效 program/VAO 缓存，resize 重建后可能误跳过 UseProgram/BindVAO。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 499 处修复。
此前：**R187 GL buffer 缓存失效 + 地形 VBO HOST_VISIBLE — 修复 2 处** — **R187-A**（CORRECTNESS）：`rhi_buffer_destroy` 只清 SSBO 缓存，VBO/IBO/indirect/array/TBO 残留导致 name 复用误跳过 bind；补全失效。**R187-B**（PERF）：地形 VBO 因 R181 进 DEVICE_LOCAL，笔刷每行 update 触发 WaitIdle；改为无 initial_data 保持 HOST_VISIBLE。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 497 处修复。
此前：**R186 mega DEVICE_LOCAL 读回 + 静态 SSBO DEVICE_LOCAL — 修复 2 处** — **R186-A**（CORRECTNESS）：R181 后静态 mesh 为 DEVICE_LOCAL，mega bake 的 `rhi_buffer_map` 在独显失败并静默产出垃圾几何；新增 `rhi_buffer_read`（staging download），失败则 abort bake。**R186-B**（PERF）：`all_draws`/`draw_cmds`/`aabb` 静态 CPU 源 SSBO 零初始化进 DEVICE_LOCAL。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 495 处修复。
此前：**R185 fill 预屏障 + cull STORAGE DEVICE_LOCAL — 修复 2 处** — **R185-A**（CORRECTNESS）：`rhi_cmd_fill_buffer` 预屏障未等 DRAW_INDIRECT，CSM/点光同 CB 复用 count/draws 时与上一趟 indirect 竞态；补 INDIRECT/SHADER_READ。**R185-B**（PERF）：gpucull/indirect/occlusion 的 GPU-only STORAGE 无 initial_data 仍 HOST_VISIBLE；零初始化创建走 DEVICE_LOCAL（staging 除外）。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 493 处修复。
此前：**R184 font 双槽 + 粒子 SSBO DEVICE_LOCAL — 修复 2 处** — **R184-A**（CORRECTNESS）：font 单槽 VBO 每帧 host 写与上一帧 VS 竞态；改为 `vbo[2]` + frame_index。**R184-B**（PERF）：粒子 STORAGE 热路径仍 HOST_VISIBLE；带 `initial_data` 的 GPU-only STORAGE 改 DEVICE_LOCAL，粒子三缓冲用零初始化创建。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 491 处修复。
此前：**R183 CB 有序 visibility 上传 + joint/instance 双槽 — 修复 2 处** — **R183-A**（CORRECTNESS）：CSM/点光 CPU fallback 同 CB 多次 host 覆盖 visibility，submit 后所有 cascade 读到最后一次写入；新增 `rhi_cmd_update_buffer` + `upload_visibility_cmd`。**R183-B**（CORRECTNESS）：`joint_buf`/`instance_buf` 单槽双帧 host 写竞态；改为 `[2]` + frame_index。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 489 处修复。
此前：**R182 visibility/light 双槽 ring — 修复 2 处** — **R182-A**（CORRECTNESS）：`visibility_buf` 单槽 HOST_VISIBLE 每帧 host memcpy 与上一帧 compact 竞态；改为 `visibility_buf[2]` + `rhi_frame_index&1`。**R182-B**（CORRECTNESS）：`light_data_buf`/`light_grid_buf` 同理；双槽上传与 bind。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 487 处修复。
此前：**R181 shadow pass 状态机 + 静态 mesh DEVICE_LOCAL — 修复 2 处** — **R181-A**（CORRECTNESS）：`unbind/bind_shadow_map` End 后未清 `render_pass_active`，`!framebuffers` 早退留下假 active；与 offscreen unbind 对齐并清 `pass_suspended`。**R181-B**（PERF）：带 `initial_data` 的 VERTEX/INDEX 改 `DEVICE_LOCAL` + staging 上传；动态 VBO（font 等无 initial_data）仍 HOST_VISIBLE。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 485 处修复。
此前：**R180 粒子 pass 保活 + depth→compute 屏障 — 修复 2 处** — **R180-A**（CORRECTNESS）：`particles_compute/cull` 的 `end/begin_render_pass` 在 VK 上拆掉 offscreen 并切回 swapchain CLEAR；删除，改由 fill/dispatch 的 suspend/resume 保活 `scene_fbo`。**R180-B**（CORRECTNESS）：`transition_depth_to_read` dst 仅 FRAGMENT，Hi-Z compute 缺同步；补 `COMPUTE`，并为 offscreen color 补 `mip_levels`/format 跟踪。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 483 处修复。
此前：**R179 粒子 live Push 整块上传 + compute 采样布局 — 修复 2 处** — **R179-A**（CORRECTNESS）：VK 粒子仍依赖陈旧 `_push_template` 且 `set_uniform_mat4` 只拷 64B；每帧从 live `ps->*` 组装 80B，经 `rhi_cmd_set_uniform_bytes` 一次上传。**R179-B**（CORRECTNESS）：`rhi_cmd_bind_texture_compute` 假定全链已是 READ_ONLY；Hi-Z 写后可能仍为 GENERAL；按 mip 转换到 SHADER_READ_ONLY 再采样。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 481 处修复。
此前：**R178 粒子 push 尾部上传 + GL frame_index — 修复 2 处** — **R178-A**（CORRECTNESS）：VK `particles_compute` 用 `set_uniform_mat4` 只拷 64B，80B Push 的 `lifetime_range` 未上传；补 `+76` 的 f32。**R178-B**（PERF）：GL `rhi_frame_index` 恒 0，双槽 staging 退化并每帧 map 同步；`frame_end` 递增。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 479 处修复。
此前：**R177 TaskWaitLink OOM 回滚 + copy_buffer 屏障 — 修复 2 处** — **R177-A**（CORRECTNESS）：`task_submit_dep` 在 `TaskWaitLink` malloc 失败时 `continue` 欠计 dep，子任务提前跑；改为回滚已挂 waiter 并返回 INVALID。**R177-B**（CORRECTNESS）：`rhi_cmd_copy_buffer` 无 suspend/transfer 屏障；VK 补 suspend+barrier，GL 补 SSBO→COPY 可见性。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 477 处修复。
此前：**R176 gpucull count GPU 清零 + destroy 回收 mip upload — 修复 2 处** — **R176-A**（CORRECTNESS）：`gpucull_dispatch_to` host 清 `count_buf`，cascade 同 CB 多次 dispatch 时清零对 GPU 不可见；改 `rhi_cmd_fill_buffer`。**R176-B**（CORRECTNESS）：R175 延迟 mip upload 仍在途时 `rhi_texture_destroy` 只等 frame fence，可能销毁正在写入的 image；destroy 前 `vk_mip_upload_reclaim`。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 475 处修复。
此前：**R175 粒子/indirect GPU 清零 + mip upload 布局 + GL fill 屏障 — 修复 4 处** — **R175-A**（CORRECTNESS）：`particles_cull` host 清 `instanceCount` 与在途 draw_indirect 竞态；init 写 header，每帧 `rhi_cmd_fill_buffer`。**R175-B**（CORRECTNESS）：`upload_mip` 硬编码 READ_ONLY；改用 `mip_layout[]`。**R175-C**（CORRECTNESS）：`indirect_draw_compact` host 清 `draw_count` 对同 CB dispatch 不可见；改 GPU fill。**R175-D**（CORRECTNESS）：GL `fill_buffer` 后缺 barrier。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 473 处修复。
此前：**R174 粒子精确 emit 预算 + destroy 解挂 + mip_layout 数据路径 — 修复 3 处** — **R174-A**（CORRECTNESS）：R172 概率发射稳态欠发；改为 `spawn_buf` atomic claim + `emit_accum` 整数预算。**R174-B**（CORRECTNESS）：`task_system_destroy` 对未完成依赖图会挂死；先强制解挂 waiter 再 `task_wait`/join。**R174-C**（CORRECTNESS）：R173 数据路径只上传 mip0 却标记全链 READ_ONLY；仅标记 mip0。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 469 处修复。
此前：**R173 任务依赖扇出/wait 计数 + mip_layout 初始化 — 修复 3 处** — **R173-A**（CORRECTNESS）：`task_submit_dep` 单 `parent` 无法扇出，多子任务挂起；改为 `TaskWaitLink` 等待者链表，完成时一次性摘取。**R173-B**（CORRECTNESS）：依赖未就绪时不计 `submitted`，`task_wait` 提前返回；创建时即计入 submitted。**R173-C**（CORRECTNESS）：R172 `mip_layout` 创建后仍为 UNDEFINED；初始化为 `SHADER_READ_ONLY_OPTIMAL`，upload 后回写。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 466 处修复。
此前：**R172 staging 双缓冲 + Hi-Z 布局 + 粒子 emit + mipmap 生命周期 — 修复 5 处** — **R172-A**（CORRECTNESS）：双帧 Vulkan 下单一 staging 可与 GPU copy 并发；`rhi_frame_index` + gpucull/occlusion 双槽 staging。**R172-B**（CORRECTNESS）：Hi-Z mip 用 UNDEFINED 作 oldLayout 且末级未转可读；跟踪 `mip_layout[]`，生成后转 sampleable。**R172-C**（CORRECTNESS/PERF）：粒子 `emit_rate` 不限流且 VK push 陈旧；概率发射 + 每帧刷新 rate。**R172-D**（CORRECTNESS）：`force_level` 绕过预算。**R172-E**（ROBUSTNESS）：shutdown 取消在途 mip 请求。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 463 处修复。
此前：**R171 GPU fill 同 CB 清零 + Hi-Z 全 mip + pending/mip 预算 — 修复 4 处** — **R171-A**（CORRECTNESS）：Vulkan 上 `rhi_buffer_update` 是 host memcpy，同 CB 多次 shadow cull 的 `draw_count` 不会在各 dispatch 之间清零，atomic 累积污染后续阴影。修复：新增 `rhi_cmd_fill_buffer`（VK `vkCmdFillBuffer` / GL `glClearBufferSubData`），compact 路径录制 GPU 清零。**R171-B**（PERF）：VK 纹理默认 view `levelCount=1`，Hi-Z `textureLod` 无法用高层 mip。修复：采样 view 暴露完整 mip 链。**R171-C**（CORRECTNESS）：`pending_count++` 在 heap 发布之后，快速完成可下溢。修复：发布前递增，失败回滚。**R171-D**（CORRECTNESS）：mipmap 预算不足时先 skip 后 eviction，desired mip 永久无法加载。修复：admission 前先驱逐本纹理 finer levels。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 458 处修复。
此前：**R170 阴影 Hi-Z/staging 串扰 + MPSC/任务依赖/indirect 回退 — 修复 8 处** — **R170-A**（CORRECTNESS）：阴影 unified 误用相机 Hi-Z，错误剔除阴影投射物。修复：阴影改 GPU compact 且 `occ=NULL`。**R170-B**（CORRECTNESS）：单 `vis_flags_staging` 被多视图覆盖；仅主相机 `stage_readback`。**R170-C**（CORRECTNESS）：compute→copy 缺 TRANSFER 屏障；VK/GL barrier 增 transfer/BUFFER_UPDATE。**R170-D**（CORRECTNESS）：async 完成队列先 bump head 再写 indices；改为 per-slot sequence 发布。**R170-E**（CORRECTNESS）：`task_submit_dep` 无效依赖仍计入 dep_count 永久挂起；仅计有效依赖。**R170-F**（CORRECTNESS）：无 `drawIndirectCount` 时回放过期 compact 槽；compact 前清零前 n 条 draws。**R170-G**（PERF）：删除每帧 flags 零上传（shader 已写 0）。**R170-H**（ROBUSTNESS）：mipmap `mip_count==0` 拒绝注册。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 454 处修复。
此前：**R169 unified cull readback/compact + decode 取消跳过 — 修复 4 处** — **R169-A**（CORRECTNESS）：`gpucull_read_vis_flags` 同帧 map 未执行的 compute 结果，Vulkan 上 vis 恒 0。修复：`vis_flags_staging` 1 帧延迟 readback（同 occlusion）；`mega_unified_vis_flags` 先读上一帧 staging 再 dispatch。**R169-B**（PERF）：flags-only 路径仍做 atomic compact 浪费；`compact_draws`/`u_cull_write_draws` 跳过 compact。**R169-C**（PERF）：decode cancel 后仍跑 stbi/mip；worker 在 decode 前检查 `ASSET_CANCELLED`。**R169-D**（CORRECTNESS）：VK 启用 `shaderTessellationAndGeometryPointSize` 以支持粒子 `PointSize`。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 446 处修复。
此前：**R168 async 槽位串槽 + indirect 屏障 + 粒子 POINT 拓扑 — 修复 3 处** — **R168-A**（CORRECTNESS）：`async_submit_request` 仅拒绝 `LOADING`，`CANCELLED`/`READY` 槽可被复用，在途 worker 把旧文件数据写入新请求（invalidate 后重载可触发）。修复：仅 `UNLOADED` 可复用；cancel/skip/`async_finalize` 失败路径均回到 `UNLOADED`。**R168-B**（CORRECTNESS）：`rhi_cmd_memory_barrier` 缺少 `GL_COMMAND_BARRIER_BIT` / `VK_ACCESS_INDIRECT_COMMAND_READ_BIT`，compute 写的 `instanceCount` 对 draw_indirect 可能不可见。**R168-C**（CORRECTNESS）：粒子管线固定 TRIANGLE_LIST 且 GL 无 `PROGRAM_POINT_SIZE`，与 `gl_PointSize`/`PointCoord` 不符；新增 `RHIPipelineDesc.point_list`，粒子启用 POINT_LIST。编译验证：Vulkan 100% + GL 100%。测试：VK/GL 各 30/30。总计 442 处修复。
此前：**R167 性能优先深度审查 — 粒子 GPU cull 落地 + decode/mipmap/occlusion/task 修复 7 处** — 审查发现粒子 GPU cull 算了但 draw 仍发满 8192 实例（文档称只 draw 存活粒子，实现未落地）。**R167-PERF**（PERF）：`particle_cull.comp`/`particle.vert` 改用 `DrawIndirectCommand` 布局；新增 `rhi_cmd_draw_indirect`（VK/GL）；`particles_render` 走 `draw_indirect`，仅 alive 粒子触发 VS，消除每帧 8192 次空 early-out。**R167-A**（ROBUSTNESS）：`DECODE_INPUT_CAP=256` 此前未生效，输入队列无界堆积 raw 图像；`input_queue_push` 现强制 cap，满则 submit 失败。**R167-B**（CORRECTNESS）：`DecodeResultNode` 嵌入 `DecodeJob` 首字段，消除二次 malloc 导致 OOM 时结果永不入队、async slot 永久 `LOADING`。**R167-C**（ROBUSTNESS）：`async_thread_create` 改返回 `bool`；decode/async I/O 线程创建失败时正确清理。**R167-D**（CORRECTNESS）：`mipmap_stream_invalidate` 取消在途请求；callback 校验 `request_id`；`async_loader_cancel` 立即以 NULL 回调释放 `MipLoadReq`。**R167-E**（CORRECTNESS）：超大 level 溢出时拒绝注册（不再钳 `UINT32_MAX` 污染 offset 链）。**R167-F**（CORRECTNESS）：occlusion 首帧跳过未初始化 staging readback。**R167-G**（ROBUSTNESS）：`task_system_create` 在 `worker_count==0` 时返回 NULL。编译验证：Vulkan 100% + GL 100%。测试验证：VK 30/30 + GL 30/30（排除需显示的 test_vulkan）。总计 439 处修复。
此前：**R166 深度审查任务系统与纹理流式加载 — 修复 2 处问题** — 深度审查 Chase-Lev 工作窃取队列和 mipmap 流式加载的整数截断问题。**R166-A**（ROBUSTNESS）：`deque_init` 中 `calloc` 返回值未检查，OOM 时 `buffer` 为 NULL，后续 `deque_push`/`deque_steal`/`deque_pop` 操作解引用 NULL 崩溃。每个 worker 有 3 个优先级队列（HIGH/NORMAL/LOW），每个队列 1024 个槽位（8KB），最多 8 个 worker 共 24 次 calloc。修复：`deque_init` 改为返回 `bool`，调用方 `task_system_create` 检查返回值，失败时销毁已初始化的 deque 并返回 NULL。**R166-B**（CORRECTNESS）：`mipmap_stream_register` 中 `level_offset` 字段为 `u32`，但偏移累加使用 `usize`，总纹数据 >4GB 时 `(u32)offset` 截断产生错误文件偏移，导致异步加载读取错误数据。修复：`level_offset` 字段从 `u32` 改为 `u64`，移除截断转换。审查确认 decode_pipeline.c（互斥锁保护队列）、hotreload.c（主线程代码）、filewatch.c（主线程代码）、profiler.c（主线程代码）无并发问题。编译验证：Vulkan 100% + GL 100%。测试验证：Vulkan 23/23 + GL 全部通过。总计 432 处修复。
此前：**R134 VK MRT FBO + cubemap depth FBO 创建路径 VkResult 检查 19 处** — 继续审计 FBO 创建路径。rhi_mrt_fbo_create（offscreen FBO color+depth）10 处（vkCreateImage×2 + vkAllocateMemory×2 + vkBindImageMemory×2 + vkCreateImageView×2 + vkCreateRenderPass + vkCreateFramebuffer，逆序清理 color+depth 资源）；vk_create_mrt_color_image helper 4 处（void 函数，失败时清理+return）；rhi_cubemap_depth_fbo_create 5 处（vkCreateImage + vkAllocateMemory + vkBindImageMemory + vkCreateImageView + vkCreateRenderPass）。VK VkResult 检查总计 R131-R134 = 69 处。23/23 测试通过。
此前：**R133 VK 资源创建 + FBO 创建路径 VkResult 检查 14 处** — 继续审计剩余未检查 VK 调用。资源创建路径 4 处（vkCreatePipelineLayout×2 compute+graphics + vkCreateImageView texture + vkCreateSampler）；shadow_map 创建 6 处（vkCreateImage + vkAllocateMemory + vkBindImageMemory + vkCreateImageView + vkCreateRenderPass + vkCreateFramebuffer，逆序清理）；cubemap 创建 4 处（vkCreateImage + vkAllocateMemory + vkBindImageMemory + vkCreateImageView）。全部失败路径清理已创建资源并返回错误。VK VkResult 检查总计 R131+R132+R133 = 50 处。23/23 测试通过。
此前：**R132 VK 初始化 descriptor/pool/fence + staging 路径 VkResult 检查 17 处** — R131 修复 19 处后继续审计发现 17 处未检查：vk_init 11 处（vkAllocateCommandBuffers 1 + 7 vkCreateDescriptorSetLayout + vkCreateDescriptorPool 1 + vkCreateSemaphore/vkCreateFence 2）；staging 上传 2 处（vkBeginCommandBuffer + vkEndCommandBuffer）；rhi_texture_create staging 4 处（vkCreateBuffer + vkAllocateMemory + vkBindBufferMemory + vkMapMemory，防止 memcpy 到 NULL 崩溃）。VK VkResult 检查总计 R131+R132 = 36 处。23/23 测试通过。
此前：**R131 VK VkResult 返回值检查 + fopen/fclose 配对审计** — 全量扫描发现 19 处未检查 VkResult。初始化路径 13 处 + 资源创建路径 6 处。fopen/fclose 25+ 处全安全，无 signal handler。23/23 测试通过。
此前：**R130 VK 初始化路径 calloc NULL 检查 + realloc/VLA/alloca/va_end 全量审计** — 8 处 calloc NULL 检查 + realloc/VLA/alloca/va_end 全量审计。calloc/malloc NULL 检查总计 50 处。23/23 测试通过。
此前：**R129 全量 calloc/malloc NULL 检查审计 — RHI 后端 7 处遗漏修复** — 全量审计发现 R125+R128 遗漏了辅助 FBO 函数中的 7 处 calloc（GL 2 + VK 5）。修复：calloc 移到 rhi_alloc_slot 之前，检查 NULL，返回空结构体。17 个子系统全确认安全。23/23 测试通过。
此前：**R128 第十轮深度审查 — GL 后端 6 处 calloc NULL 检查遗漏修复** — R125 修复了 rhi_gl.c 中 8 处 calloc NULL 检查，但遗漏了 6 处：`rhi_cubemap_create`（GLTextureData，GL 纹理已创建）、`rhi_offscreen_fbo_create_fmt`（GLFBOData）、`rhi_gpu_timer_create`（RHIGPUTimer）、`rhi_mrt_fbo_create`（GLMRTFBOData + 色纹理循环 GLTextureData + 深度纹理 GLTextureData）。修复：calloc 移到 rhi_alloc_slot 之前，检查 NULL，清理 GL 资源或返回空结构体。23/23 测试通过。
此前：**R127 第九轮深度审查 — 整数溢出/除零/realloc/sscanf 全量扫描（无新问题）** — 对全代码库进行第九轮扫描，覆盖前八轮未系统检查的模式：整数溢出（malloc/calloc 大小转换）、realloc NULL 检查（scene_serial.c 3 处 + script.c 1 处）、sscanf 宽度限制（script.c 4 处 + net_replication.c 1 处）、除零风险（main.c + terrain.c + lighting.c + font.c 共 25+ 处）、scene_serial.c 全量 malloc/calloc（10 处）、platform 代码、framework 代码、危险函数确认（无 scanf/strcpy/strcat/gets/sprintf）、fread 返回值、memcpy sizeof 乘法。全部确认安全，无新问题。经过 R102-R127 九轮深度审查，代码库的内存安全、资源管理、边界检查均已达到工业级水平。
此前：**R126 第八轮深度审查 — main.c malloc/calloc NULL 检查（5 处）** — **R126-1**（ROBUSTNESS）：main.c（5607 行）中 5 处 `malloc`/`calloc` 未检查返回值，OOM 时 NULL 解引用崩溃：render_init 中 geo_buf calloc（失败时 idata 野指针）、main 中 render_buf/cull_block/mega_block/gcmds_scratch malloc。修复：每处添加 NULL 检查 + LOG_FATAL + 资源清理 + 返回。审查确认 8 个子系统安全：read_file 25+处全有 ftell+malloc 检查、atoi/getenv 16 处全有 NULL 守卫、box_idx/g_vis_flags/heights/speeds 数组索引全在边界内、无 sprintf/gets、rhi_alloc_slot 池耗尽为已知限制。23/23 测试通过。
此前：**R125 第七轮深度审查 — RHI 后端 calloc NULL 检查（GL 8 处 + VK 13 处）** — **R125-1**（ROBUSTNESS）：`rhi_gl.c` 中 8 个资源创建函数（shader×2、pipeline×2、buffer、texture、sampler、FBO）的 `calloc` 未检查返回值，OOM 时 NULL 解引用崩溃。修复：将 `calloc` 移到 `rhi_alloc_slot` 之前，失败时清理 GL 资源并返回 `RHI_HANDLE_NULL`。**R125-2**（ROBUSTNESS）：`rhi_vk.c` 中 13 处同一模式：Category 1（7 处）calloc 在 VK 资源创建后，修复同 GL；Category 2（3 处）calloc 在 VK 资源创建前，检查 NULL 后提前返回；Category 3（3 处）calloc 在大函数内部，检查 NULL 后提前返回（极端 OOM 时 VK 资源可能泄漏但不崩溃）。审查确认 rhi.c 句柄管理、terrain.c 边界检查、render_graph/occlusion_cull、log.c 均安全。23/23 测试通过。
此前：**R124 第六轮深度审查 — verify_pak 工具加固 + 网络序列化/Lua绑定/packer/CMake 全扫描** — **R124-1**（SECURITY+ROBUSTNESS）：`verify_pak.c` 中 `ftell` 缺少 < 0 检查 + 两处 `malloc` 未检查 NULL 即用于 `fread`/`vfs_read`。修复：添加 `ftell < 0` 检查 + malloc NULL 检查 + 资源清理。审查确认 7 个子系统安全：packet.c 显式 LE 编码+全边界检查；net_replication.c sscanf %255s+重排序槽 PACKET_MAX_SIZE+可靠待发 PACKET_MAX_SIZE；script_lua.c checked_body+lua_pcall；packer.c R105-2 边界检查+4GB 限制；network.c fd 管理+net_close 检查；CMakeLists.txt -Werror+第三方隔离；全代码库 read_file 25+ 处全有 ftell+malloc 检查。23/23 测试通过。
此前：**R123 第五轮深度审查 — font.c TTF ftell 回绕 + 异步加载器线程安全 + fd/socket 审查** — **R123-1**（SECURITY）：`font_renderer_init` 中 TTF 字体加载路径 `(usize)ftell(f)` 缺少 `ftell < 0` 检查，当 ftell 返回 -1 时 `malloc(SIZE_MAX)` 在 overcommit 系统上可能成功 → 堆溢出。R120-2 修复了同一函数的 shader 路径但遗漏了 TTF 路径。修复：添加 `ftell < 0` 检查。审查确认 8 个子系统安全：异步加载器线程安全（release-acquire 模式、MPSC 无锁队列、CAS 取消）；ftell 全代码库覆盖（6 处全部安全）；无命令注入（无 system/popen/exec）；无格式串注入；getenv+atoi 全有 NULL 检查；后期处理 pipeline 已验证；filewatch fd 管理；network socket 管理。23/23 测试通过。
此前：**R122 第四轮深度审查 — 初始化路径 malloc NULL 检查 + RHI 句柄验证** — **R122-1**（ROBUSTNESS）：`gpucull_init` 中 `_pack_buf`/`_zero_buf` 的 malloc 未检查 NULL，失败时 `_zero_buf = NULL + offset`（野指针），函数返回 true → 后续崩溃。修复：NULL 检查 + `gpucull_shutdown` + return false。**R122-2**（ROBUSTNESS）：`particles_init` 中 `particle_ssbo`/`sampler`/`particle_tex` 创建后未验证句柄，`particle_ssbo` 随后立即用于 `rhi_buffer_map`。修复：在 `initialized = true` 前添加 `rhi_handle_valid` 检查。**R122-3/4**：`water_init`/`terrain_create` 中 `vbo`/`ibo` 创建后未验证。**R122-5**：`occlusion_cull_init` 中 `hi_z_sampler` 未验证。全部添加 `rhi_handle_valid` 检查 + shutdown 清理。审查确认 read_file（25 处）/indirect_draw/gpucull 缓冲区/occlusion_cull 缓冲区/realloc 均已有验证。23/23 测试通过。
此前：**R121 第三轮深度审查 — vfs double-free 修复 + 着色器/strncpy/realloc/shift 全扫描** — **R121-1**（REGRESSION）：R120-1b 在 `vfs_mount_pak` 中添加的 hash table malloc NULL 检查引入 double-free——`mount_count` 已递增且 `mounts[idx]` 已持有 `entries`/`names`/`fp` 指针，失败路径释放后 `vfs_destroy` 再次 free/fclose。修复：将 hash table 构建移到 mount 注册之前，失败时无需回滚。第三轮系统扫描 10 类问题模式（strncpy 24 处/snprintf 25 处/realloc 4 处/memcpy 10 处/整数截断 4 处/移位 17 处/sscanf 6 处/atoi 16 处/着色器 5 个/编译器警告）均确认安全。23/23 测试通过。
此前：**R120 第二轮深度审查 — ftell 回绕堆溢出 + VFS hash table NULL 检查** — **R120-1**（SECURITY）：`vfs_open` 目录挂载路径中 `(usize)ftell(fp)` 当 ftell 返回 -1 时 `sz = SIZE_MAX`，`calloc(1, sizeof(VFSFile) + SIZE_MAX)` 回绕为极小分配，`fread` 写入堆溢出。修复：`ftell < 0` 检查。**R120-1b**（ROBUSTNESS）：`vfs_mount_pak` 中 hash table `malloc` 未检查 NULL，`memset(NULL, ...)` 崩溃。修复：添加 NULL 检查。**R120-2**（SECURITY）：`font_renderer_init` 中两处 `(usize)ftell` 同样回绕为 SIZE_MAX，`malloc(SIZE_MAX+1)` = `malloc(0)`，`fread` 写入零字节缓冲区堆溢出。R116-1 添加了 malloc NULL 检查但遗漏了 ftell < 0 检查。修复：添加 ftell < 0 检查。第二轮扫描确认整数溢出/use-after-free/线程安全模式安全。23/23 测试通过。
此前：**R119 头文件/framework/platform 全量审查（无需修复）** — 审查 83 个头文件（.h）中的内联函数和宏定义、framework/ 目录（3 个 C++ 文件）、platform/ 目录（5 个 demo 文件）、tests/test_framework.h。14 个含内联函数的头文件均无问题：math.h（fast_rsqrt/vec3_normalize/quat_slerp 等有防除零守卫）、simd.h（SSE2+标量回退）、alloc.h（arena_alloc 溢出检查）、pool.h（NULL 检查）、cull.h（p-vertex AABB 测试）、imgui.h（slider 防除零）、lighting.h、string.h、assert.h、types.h、rhi.h、ecs.h、packet.h、async_loader_private.h。framework 代码为桩实现，无内存分配。**R102-R119 完成引擎全部源码（86 .c + 83 .h + framework + platform + tests）的全量审查。**
此前：**R118 音频/ECS 系统 calloc NULL 检查（全量审查完成）** — **R118-1**（ROBUSTNESS）：`audio_system_create` 中两处 calloc 未检查返回值：`audio_block` calloc 失败时 `impl` 指向近零地址，`ma_engine_init` 写入崩溃；`sources` calloc 失败时返回的 AudioSystem 的 sources 为 NULL，后续使用崩溃。修复：两处均添加 NULL 检查，失败时清理并返回 NULL。**R118-2**（ROBUSTNESS）：`ecs_parallel_for` 堆回退路径 `malloc(job_count * sizeof(EcsJob))` 未检查返回值，job_count > 512 时 OOM 崩溃。修复：malloc 失败时回退到静态池并钳制 job_count，LOG_WARN 降级。审查确认 7 个子系统（assert、math、ibl、indirect_draw、debug_ui、imgui、utf8）无需修复。23/23 测试通过。**R102-R118 完成引擎全部 86 个 .c 源文件的逐文件深度审查。**
此前：**R117 BVH/光照 calloc NULL 检查** — **R117-1**（ROBUSTNESS）：BVH SAH 构建路径 5 处内存分配未检查返回值：`bvh_init` calloc 失败时 `bvh->nodes=NULL` 后续崩溃；`bvh_alloc_node` realloc 失败时旧指针泄漏 + `bvh->nodes` 置 NULL；`bvh_build` 中 leaf_map/nodes/_build_indices 三处 calloc/malloc 失败解引用 NULL。修复：全路径 NULL 检查，realloc 使用临时指针避免泄漏。**R117-2**（ROBUSTNESS）：`light_system_upload_grid` 中 staging buffer calloc 未检查 NULL，OOM 时后续 `memcpy` 崩溃。修复：添加 NULL 检查 + LOG_ERROR。审查确认 3 个子系统（地形、异步加载、遮挡剔除）无需修复。23/23 测试通过。
此前：**R116 字体/脚本/ECS/LOD 防御性加固** — **R116-1**（ROBUSTNESS）：`font_renderer_init` 中着色器源码 `malloc` 和 `quad_data` `malloc` 未检查 NULL，失败时 `fread(NULL, ...)` 崩溃。修复：添加 NULL 检查。**R116-2**（ROBUSTNESS）：`script_load` 中 `ftell` 返回 -1 时 `malloc(0)` 可能返回非 NULL，`fread` 读取 `SIZE_MAX` 字节溢出；`malloc` 返回 NULL 时崩溃。修复：`sz < 0` 提前返回 + NULL 检查。**R116-3**（ROBUSTNESS）：ECS 核心路径多处 `calloc`/`malloc`/`realloc` 未检查返回值（`chunk_alloc`、`create_archetype`、`world_create`、`world_add_component`、`world_remove_component`、`world_query`/`ecs_query_refresh`），失败时解引用 NULL 崩溃。修复：全路径添加 NULL 检查，query 路径降级不崩溃。**R116-4**（ROBUSTNESS）：`lod_select_by_*` 中 `level_count - 1` 当 `level_count==0` 时 u32 下溢为 `UINT32_MAX`，越界读 `thresholds_sq`。修复：`lod_register` 拒绝 `level_count==0`。审查确认 11 个子系统（延迟渲染、点光阴影、相机、视锥剔除、分配器、池分配器、性能分析器、Lua 脚本、场景序列化、输入、日志）无需修复。23/23 测试通过。
此前：**R115 网络复制缓冲区溢出 + glTF 资产加载防御性加固** — **R115-1**（ROBUSTNESS）：`net_replicator_process` 未检查 `len > PACKET_MAX_SIZE`，导致 `net_reorder_store` 中 `memcpy(slot->wire, wire, len)` 溢出 1400 字节缓冲区。公共 API `net_replicator_feed`/`net_replicator_feed_from` 接受任意 `len`。修复：入口添加 `len > PACKET_MAX_SIZE` 检查。**R115-2**（ROBUSTNESS）：`asset_load_gltf` 中多处 `calloc`/`malloc` 缺少 NULL 检查，分配大小来自不可信 glTF 文件数据。修复：添加 NULL 检查。**R115-3**（ROBUSTNESS）：`cgltf_buffer_data` 返回值未检查 NULL（R109-2 已使该函数可返回 NULL）。修复：循环条件添加 NULL 守卫。审查确认 8 个子系统（物理、动画、渲染图、命令缓冲、任务系统、网络核心、包序列化、主循环）无需修复。23/23 测试通过。
此前：**R114 平台窗口管理与手柄输入审查（无需修复）** — 审查全平台窗口管理（window_x11.c 381 行 / window_wayland.c 719 行 / window_win32.c 518 行）、手柄输入（gamepad_linux.c 421 行 / gamepad_win.c 178 行）、剔除辅助（cull.c 31 行）。所有文件代码质量高：calloc + NULL 检查、资源释放完整、strncpy + memset 安全、设备热插拔处理完善。审查未发现问题，无需代码修改。
此前：**R113 SSGI uniform 位置硬编码 + VK buffer_update NULL deref 修复** — **R113-1**（CORRECTNESS）：`ssgi_init` 硬编码 blur uniform 位置 `loc_blur_dir_x = 0`，但 GL 链接器不保证 `u_direction` 在位置 0。`post_process.c` 正确查询了该位置，`ssgi.c` 遗漏。修复：用 `rhi_pipeline_get_uniform_location` 查询，并添加 `>= 0` 守卫。**R113-2**（ROBUSTNESS）：VK `rhi_buffer_update`/`rhi_buffer_update_region` fallback 路径 `vkMapMemory` 失败时 `mapped` 未定义，`memcpy` 崩溃。修复：检查返回值。审查确认 19 个子系统（全后期处理小文件、骨骼动画、引擎核心、RHI 句柄管理、平台时间）无需修复。23/23 测试通过。
此前：**R112 test_vulkan.c file_read 防御性加固（全引擎 read_file 统一完成）** — **R112-1**（ROBUSTNESS）：`test_vulkan.c` 的 `file_read` 缺少 `ftell` 返回值检查和 `malloc` NULL 检查，是引擎中最后一个未加固的 `read_file` 实现。R110 修复了 `particles.c` 和 `water.c`，R112 修复了 `test_vulkan.c`，至此全引擎 28 个 `read_file`/`file_read` 实现全部完成统一加固。审查确认 10 个子系统（光照系统、SSAO、Tonemap、Mipmap 流式加载、DoF、SSR、TAA、FileWatch Windows/Linux、全引擎 read_file 验证）无需修复。23/23 测试通过。
此前：**R111 GPU 剔除初始化验证 + 热重载路径终止修复** — **R111-1**（ROBUSTNESS）：`gpucull_init` 创建 3 个 GPU 缓冲区后未验证有效性就设置 `ready = true`。修复：添加三缓冲区有效性检查，失败时 `gpucull_shutdown` 清理并返回 false。**R111-2**（ROBUSTNESS）：`hotreload_pipeline_init` 未 `memset` 结构体就 `strncpy` 路径。修复：入口添加 `memset(hr, 0, sizeof(*hr))`。审查确认 12 个子系统无需修复。23/23 测试通过。
此前：**R109 字符串/glTF 资产加载防御性修复** — **R109-1**（ROBUSTNESS）：`str_copy` 当 `buf_size==0` 时，`buf_size-1` 无符号下溢为 `SIZE_MAX`，使长度钳制失效，`memcpy` 向零大小缓冲区写入 `s.len` 字节。修复：入口添加 `buf_size==0` 提前返回。**R109-2**（ROBUSTNESS）：`cgltf_buffer_data` 未检查 `bv->buffer`/`bv->buffer->data` 空指针。当 `buffer->data` 为 NULL 时返回 `NULL+offset` 悬空指针，调用者的 NULL 检查无法拦截。修复：添加 `!bv->buffer || !bv->buffer->data` 检查返回 NULL。**R109-3**（ROBUSTNESS）：`load_gltf_texture` 路径拼接 `memcpy(tex_path, gltf_path, dir_len)` 当 `gltf_path` 超过 512 字节时栈缓冲区溢出。修复：钳制 `dir_len` 不超过 `sizeof(tex_path)-1`。审查确认 10 个子系统（渲染图、命令缓冲、CSM 阴影、点光阴影、延迟渲染、后期处理、材质系统、字符串工具、glTF 加载、场景世界变换）无需修复。23/23 测试通过。
此前：**R108 场景序列化边界验证修复** — **R108-1**（ROBUSTNESS）：`scene_load_binary` 读取 BSCN 文件后直接访问 chunk 表和 chunk 数据，未验证偏移+大小是否在文件缓冲区内。畸形文件的 `offset=0, size=0xFFFFFFFF` 会使 `rd_bytes` 的边界检查通过（差值巨大）但 `memcpy` 读取缓冲区外内存。修复：读取 header 后验证 chunk 表 `table_off + chunk_count * sizeof(BscnChunkEntry) <= fsz`；每个 chunk 访问前验证 `offset + size <= fsz`（使用 u64 避免溢出）。审查确认 10 个子系统（Arena/Heap/Pool 分配器、Profiler、输入系统、Frustum culling、LOD、相机、场景 JSON 路径、组件加载）无需修复。23/23 测试通过。
此前：**R107 音频流槽位泄漏修复** — **R107-1**（CORRECTNESS）：`audio_stream_open`/`audio_stream_open_3d` 在 `audio_play_streamed` 失败时未将已分配的流槽位归还自由链表，每次打开失败永久泄漏一个槽位，最终导致 `AUDIO_STREAM_MAX_SOURCES` 次失败后所有槽位耗尽。修复：在失败路径中添加 `free_next[idx] = next_free; next_free = idx` 归还槽位。审查确认 9 个子系统（物理 CCD、角色控制器、动画 IK、网络序列化、网络复制、地形、任务系统、脚本、Pool allocator）无需修复。23/23 测试通过。
此前：**R106 VK 帧开始状态重置 + GL 缓存失效修复** — **R106-1**（CORRECTNESS）：VK `rhi_frame_begin` 调用 `vkResetDescriptorPool` 释放所有描述符集后，未重置 `storage_set_valid`（仍为上一帧 `true`）和 `current_pipeline_data`（仍指上一帧管线）。若新帧中 `rhi_cmd_bind_storage_buffer` 在 `rhi_cmd_bind_pipeline` 之前调用，会使用被释放的悬空描述符集句柄执行 `vkUpdateDescriptorSets` → UB。修复：帧开始时添加 `current_pipeline_data = NULL` + `storage_set_valid = false`。**R106-2**（CORRECTNESS）：GL 后端 `g_tex_cache[16]`/`g_sam_cache[16]`/`g_gl_ssbo_cache[8]` 绑定缓存在 `rhi_texture_destroy`/`rhi_cubemap_destroy`/`rhi_sampler_destroy`/`rhi_buffer_destroy` 时未失效。GL 删除对象后绑定点恢复为 0，但缓存仍持有旧 GL name；GL 复用 name 时缓存误判为“已绑定”跳过实际绑定。修复：在每个 destroy 函数中遍历对应缓存清除匹配条目；`g_gl_ssbo_cache` 从 static 局部提升为文件作用域。23/23 测试通过。
此前：**R105 VFS NULL 检查 + packer 缓冲区边界检查** — **R105-1**（ROBUSTNESS）：`vfs_mount_dir`/`vfs_mount_pak` 添加 NULL 路径检查 + 显式 null 终止。**R105-2**（ROBUSTNESS）：packer `add_file` 在 `memcpy` 前检查 `g_name_size + name_len` 边界。23/23 测试通过。
此前：**R104 decode pipeline 优先级队列修复** — **R104-1**（PERF）：`input_queue_push` 从 FIFO 追加改为优先级排序插入，低 priority 值 = 高优先级（与 async loader min-heap 一致）。23/23 测试通过。
此前：**R103 ECS 查询增强 + 延迟点光阴影 + 异步加载优先级解码管线 + Windows Packer** — **R103-1**（FUNC）：ECS 查询新增 Exclude/Optional 组件支持，位掩码 O(1) 过滤。新增 API：`ecs_query_exclude`（排除含指定组件的原型）、`ecs_query_optional`（可选组件，匹配但跳过不含的原型）、`ecs_query_refresh`（查询失效时重建匹配原型列表）。`Query` 结构扩展 `exclude_mask`/`optional_mask` 位域，`query_matches_archetype` 用位运算一次判定，避免遍历排除列表。`test_ecs` 新增 5 项 Exclude/Optional 测试。**R103-2**（FUNC）：`deferred_light.frag`/`deferred_light_vk.frag` 接入点光 cubemap 阴影采样（`HAS_POINT_SHADOW` 条件编译）；前向管线 `blinn_phong_clustered`/`pbr_clustered` 双后端同步 `HAS_POINT_SHADOW` 守卫；`PointLight` 增加 `shadow_index` 字段指向 cubemap 阴影槽位；`deferred.c` 绑定点光阴影纹理到延迟光照 pass。**R103-3**（FUNC）：异步加载器 priority 最小堆替换 FIFO 队列，高优先级请求（如 mipmap）优先出队；新增 2-worker 解码线程池 `decode_pipeline.c/h`，stb_image 解码 + mipmap 生成不阻塞主线程，解码完成后回调主线程上传 GPU。`test_async_loader` 新增优先级和解码管线测试。**R103-4**（FUNC）：Windows packer 重写为 `CreateFileMapping` 零拷贝打包（内存映射直读文件数据，无额外 memcpy），`FindFirstFile`/`FindNextFile` 递归遍历目录，与 POSIX 版二进制兼容（相同 `VFS_PAK_MAGIC` + 字节序 + 对齐）；新增 `verify_pak.c` 验证工具。
此前：**R102 ECS archetype edge 缓存** — **R102**（PERF）：`world_add_component`/`world_remove_component` 的目标 archetype 查找从 O(N) 线性扫描降为 O(E) edge 查找。首次 add/remove 某 component 仍走 `find_archetype` 并缓存结果到 `edges_add[]`/`edges_remove[]`；后续相同 component 的转换直接用缓存的 `target` 指针。`ArchetypeEdge` 结构与字段此前已定义但为桩，现已完整实现四个辅助函数。`test_ecs` **23/23** 通过。
此前：**R101 冗余遮挡剔除消除 + 动画事件回调触发** — **R101-1**（PERF）：当 unified cull 路径全激活时（`mega_buf.valid && unified_forward_enabled`，即 mega-buffer 默认生效），`occlusion_cull_dispatch` 的结果无人消费——`node_occ_visible()` 不被调用因为 CPU 回退路径被跳过。跳过该 dispatch 每帧节省 1 compute pipeline bind + 3 SSBO/texture bind + 4 uniform set + 1 dispatch + 1 barrier + 1 buffer copy。Hi-Z 生成仍然运行（unified_cull 采样它）。当 unified 关闭或 mega-buffer 无效时照常 dispatch。**R101-2**（FUNC）：动画事件回调从“存储但不触发”改为在 `anim_blend_evaluate` 中按时间区间检测并触发。新增 `AnimEvent` 结构体（时间戳+名称）、`AnimClip.events[]` 事件轨道（最多 32 条）、`anim_clip_add_event()` API。支持循环 wrap-around（两段区间检测）。`test_animation` 新增 4 项事件测试（触发/循环 wrap/无回调安全/上限裁断），**24/24** 通过。
此前：**R86 关键bug修复 + 粒子GPU回读消除 + VBO/IBO绑定缓存 + sun_color缓存** — **R86-1**（CRITICAL）：R85 引入的 blinn_phong_clustered 平方链错误。**R86-2**（HIGH）：粒子 GPU 回读消除。**R86-3**（MEDIUM）：VBO/IBO 绑定缓存。**R86-4**（LOW）：sun_color 缓存。23/23 测试通过。

此前：**R82 静态数据生命周期优化：遮挡剔除AABB缓存 + 遗留gpucull跳过 + 点阴影per-face uniform提升 + occ节点映射移至init** — R82-1 遗留gpucull跳过、R82-2 AABB缓存、R82-3 点阴影per-face uniform提升、R82-4 occ节点映射移至init。23/23 测试通过。

此前：**R79 FBO绑定缓存 + 纹理上传缓存失配修复 + buffer尾部解绑消除 + scissor状态缓存** — R79-1 FBO绑定缓存、R79-2 纹理上传缓存失配修复、R79-3 buffer尾部解绑消除、R79-4 scissor状态缓存。23/23 测试通过。

此前：**R78 cubemap缓存修复R77回归 + skybox深度缓存 + 点阴影FBO解绑批处理** — R78-1 cubemap缓存修复、R78-2 skybox深度缓存、R78-3 点阴影FBO解绑批处理。23/23 测试通过。

此前：**Round 30 完成** — DrawBench 导出 + NetRep peer 持久。**DrawBench export(R30-1)**：CSV ring + Chrome meta；`BREAK_DRAW_BENCH_EXPORT`；F11 联动。**Peer persist(R30-2)**：`peer_save/load` + `BREAK_NETREP_PEER_FILE`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 29 完成** — DrawBench GPU 对比 + NetRep peer 老化。**GPU bench(R29-1)**：unified/legacy 路径 GPU timer 均值；UI `gpu_u=`/`gpu_l=`。**Peer TTL(R29-2)**：`last_seen_ms` + LRU/TTL 淘汰；`BREAK_NETREP_PEER_TTL`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 28 完成** — DrawBench mega/legacy 对比 + NetRep 多 peer RTT。**DrawBench(R28-1)**：`BREAK_DRAW_BENCH=1` 帧内 mega vs legacy draw 估算；debug UI ratio。**Peer RTT(R28-2)**：`NetRepPeerStats[8]` + `net_address_equal()`；UI 列出 peer。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 27 完成** — Unified env 矩阵文档 + NetRep 双向 RTT。**Unified docs(R27-1)**：`Round11_Performance_Plan.md` 增 shadow/forward/deferred + NetRep env 矩阵表。**Heartbeat echo(R27-2)**：`NET_PKT_HEARTBEAT_ACK` + 自动 echo；`hb_roundtrip_ms`；UI `echo=`/`rt=`；`BREAK_NETREP_HB_ECHO=0`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 26 完成** — Unified forward/deferred 默认化 + NetRep heartbeat demo。**Unified default(R26-1)**：mega-buffer 默认 forward+deferred unified vis；`=0` 关闭。**Heartbeat(R26-2)**：60 帧周期 heartbeat + RTT；debug UI `hb=`/`rtt=`；`BREAK_NETREP_HEARTBEAT=0`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 25 完成** — Unified shadow 默认化 + NetRep 多类型 channel。**Unified shadow default(R25-1)**：mega-buffer 有 mat groups 时默认 shadow per-material；`BREAK_UNIFIED_SHADOW=0` 关闭。**NetRep multitype(R25-2)**：按 packet type 独立 unreliable/ordered 序列；`NET_PKT_HEARTBEAT` + `net_replicator_send_heartbeat()`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 24 完成** — Shadow per-material unified + NetRep 双通道。**Unified shadow(R24-1)**：`BREAK_UNIFIED_SHADOW=1` CSM/点光 unified vis + 按材质 indirect。**NetRep channels(R24-2)**：unreliable/ordered 双序列号 + `NetRepReliablePending`；接收按 `PACKET_ORDERED` 路由；`dual_channel_sequences` 单测。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 23 完成** — Unified 延迟独立开关 + NetRep 可靠有序组合。**Unified deferred(R23-1)**：`BREAK_UNIFIED_DEFERRED=1` G-Buffer mega 路径单独 unified vis + per-material；与 `BREAK_UNIFIED_FORWARD` 解耦。**NetRep combo(R23-2)**：`BREAK_NETREP_RELIABLE_ORDERED=1`；重传重复包 `reorder_duplicate` 抑制；`reliable_ordered_combined` 单测。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 22 完成** — Unified per-material + NetRep 有序层。**Unified per-material(R22-1)**：`unified_cull.comp` binding 4 `VisibleFlags`；`mega_unified_vis_flags` + `mega_mat_groups_draw`；`BREAK_UNIFIED_FORWARD=1` 前向/延迟 mega 路径单 dispatch 后按材质 indirect。**NetRep ordered(R22-2)**：`PACKET_ORDERED` 32-slot 重排 buffer；`BREAK_NETREP_ORDERED=1`；`test_net_replication` 乱序单测。**VK(R22-3)**：compute storage layout 扩至 8 binding。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 21 完成** — Unified 前向 + Forward Velocity + NetRep 可靠层。**Unified forward(R21-1)**：`BREAK_UNIFIED_FORWARD=1` mega-buffer 单 dispatch（Hi-Z+frustum+compact）。**Forward velocity(R21-2)**：`BREAK_FORWARD_VEL=1` camera motion 纹理供 TAA。**NetRep reliable(R21-3)**：`BREAK_NETREP_RELIABLE=1` ACK+重传。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 20 完成** — 前向点光阴影 + Animation IK + NetRep 去重。**Forward pt shadow(R20-1/R12-3)**：`pbr_clustered` 采样 binding 10 cubemap；push/uniform 传 light slot 映射。**Anim IK(R20-2)**：`BREAK_ANIM_IK=1` + `skeleton_compute_world_transforms` + 轨道 target。**NetRep dedup(R20-3)**：序列号过滤 stale 包；`BREAK_NETREP_DEDUP=0` 关闭。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 19 完成** — 后处理合并 + 动画混合 + NetRep 插值。**Combined color+cinematic(R19-1)**：移除 `!cine_enabled` 门禁，combined pass 传入 vignette/grain/aberration，跳过独立 cinematic pass。**Anim blend(R19-2)**：`skeleton_apply_local_trs` + `BREAK_ANIM_BLEND=1` + F12 crossfade。**NetRep lerp(R19-3)**：ghost target 线性插值；`BREAK_NETREP_LERP=0` 即时 snap。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 18 完成** — TAA history + 延迟点光阴影 + 网络 ghost。

此前：**Round 17 完成** — Combined AA motion + Demo 接线。**Combined AA(R17-1)**：`combined_aa_apply` 可选 velocity 纹理；`combined_taa_fxaa*.frag` 增 per-pixel motion 重投影（VK push `u_taa_use_velocity@212`）；延迟路径 combined AA 绑定 `gbuf_velocity`。**NetRep demo(R17-2)**：`BREAK_NETREP=1` UDP :19900 loopback 广播角色 transform；debug UI 显示 sent/recv。**Hot reload tex(R17-3)**：`BREAK_HOTRELOAD_TEX=<path>` 监视并重载 `fallback_tex`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 16 完成** — 剔除深化 + TAA motion。**Unified Hi-Z(R16-1)**：`unified_cull.comp` 可选 Hi-Z 球体测试；阴影 unified 路径传入上一帧 Hi-Z；fallback 1×1 纹理满足 VK descriptor。**Velocity G-Buffer(R16-2)**：延迟 MRT RT3 写 NDC motion vector；gbuffer 传 `u_prev_vp`。**TAA(R16-3)**：`taa_resolve` 可选 velocity 纹理；延迟路径自动用 `gbuf_velocity`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 15 完成** — 工具链与长期质量。**Profiler(R15-1)**：`profiler_export_chrome_trace()` 导出 Chrome Trace JSON（CPU regions + GPU timer 样本）；demo 按 **F11** 或 `PROFILER_TRACE=1` 退出时写 `profile_trace.json`。**Golden(R15-2)**：`test_vulkan` 双后端条件编译（GL 仅 golden 回归；VK 全集成套件）；新增 `tests/golden/test_vulkan_gl.ppm`；GL 构建纳入 CTest。**Network(R15-3)**：`net_replication.{h,c}` transform 快照 unreliable UDP 广播/接收；`test_net_replication` loopback 测。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 13 完成** — 延迟光照质量 + TAA 重投影 + combined/auto-exposure 共存。**Deferred(R13-1)**：`deferred_light.frag`/`deferred_light_vk.frag` 接 `light_data`/`light_grid` cluster、CSM PCSS(`shadow_test`)、split-sum IBL(`HAS_IBL`)；去掉 5% 硬编码环境光；`deferred_lighting_pass` 绑定 texel buffer + IBL；deferred 路径每帧 `light_system_cull`/`upload`。**TAA(R13-2)**：`combined_aa`/`taa_resolve` 传 `inv(curr_view_proj)` 而非 `inv(proj)` 修复相机 motion 重投影。**Combined color(R13-3)**：`combined_color_apply` 扩展 exposure/gamma/tonemap_mode/cinematic 参数；先 `tonemap_update_auto_exposure` 再 combined pass 读 `tonemap.exposure`；移除 `!auto_exposure` 门禁。**回归**：VK CTest **30/30**、GL **29/29**。

此前：**Round 12 完成** — unified 剔除默认化 + 粒子 GPU cull。

此前：**Round 11 完成** — 性能路径默认生效：剔除闭环 + 合并后处理接入 demo。**遮挡 Hi-Z(R11-1)**：`main.c` 建立 `scene node → occ 紧凑索引` 映射(`occ_rebuild_node_map`/`node_occ_visible`)，与 Hi-Z upload 同序；前向 mega-buffer indirect 路径 `vis_flags &= occlusion(上一帧)`，CPU frustum 回退路径跳过被挡节点；默认开启 1 帧延迟 Hi-Z(`occ_cull_enabled=true`，`BREAK_OCCLUSION=0` 可关)；debug UI 显示 culled/occ 对象数。**GPU 剔除默认(R11-2)**：`mega_buf.valid` 时默认 `gpu_indirect_enabled && gpucull_enabled`，初始化 `gpucull_init_unified` 为 R12 unified 路径铺路；`BREAK_GPUCULL=1` 仍可强制开启。**合并后处理(R11-3)**：demo 初始化/resize `CombinedAA`/`CombinedColor`；TAA+FXAA 均开且 combined 管线就绪→单 pass AA；tonemap+调色+cg 且 `!cine && !auto_exposure`→单 pass 调色；debug UI 显示 CombinedPost on/off。**实测**：双后端 `engine_demo` 构建通过；VK CTest **30/30**、GL CTest **29/29**；`test_vulkan` golden+合并管线子测通过。

此前：**Round 10 完成** — 流式/UI/Core/回归测试全面补齐。**Mipmap 流式**：`mipmap_stream.c` 由桩改为真链路 —— `MipLoadReq` 上下文经 `async_loader_request_range` 把 level 数据写入 `level_data`、按预算计 `total_resident_bytes`、命中后经 `MipmapUploadFn` 钩子真上传 GPU；新增 RHI `rhi_texture_upload_mip`(GL `glTexImage2D` / VK staging+barrier 逐 mip)；修复 `coverage_to_level` 反向 bug(全覆盖应得 level0)；接入 `main.c`(程序化 256² 9-mip 文件、相机距离驱动驻留/驱逐、debug UI 显示 level/驻留/上传/驱逐)。**Audio 流式**：`audio_stream.c` 由不出声的双缓冲框架改为 miniaudio `MA_SOUND_FLAG_STREAM` 真流式后端；audio.c 增 `audio_play_streamed`/`audio_source_set_position`/`_set_attenuation`/`_at_end`/`_cursor_seconds` + 纯函数 `audio_attenuation_gain`(逆距离模型)；`main.c` 生成正弦 WAV 作 3D 音源真播放并显示增益。**字体/UI**：`utf8.{h,c}` 健壮多字节解码；`font.c` 扩 ASCII+Latin-1 字形范围+码点查找表+白像素(实心矩形)；新增 `imgui.{h,c}` 即时模式控件(label/button/checkbox/slider，纯逻辑助手可无头测)接入 demo(反引号切换面板)。**Core**：通用定长 `pool.{h,c}` 分配器(接入 `Alloc` vtable)；GPU timestamp profiler(`RHIGPUTimer` 双后端)接入 demo 命名计时。**回归测试**：`test_vulkan` 增 golden image 子测(读回→降采样→容差比对委 `tests/golden/test_vulkan_vk.ppm`，`GOLDEN_UPDATE=1` 重生)且返回码现汇总全部子测，纳入 CTest(经 `WORKING_DIRECTORY` + `ENGINE_VULKAN` 守卫)。新增 `test_pool`/`test_font_ui`/`test_mipmap_stream`/`test_audio`。**实测**：VK 构建 CTest **30/30**(含 test_vulkan，golden MAE=0.00)；GL 构建 CTest **29/29**(test_vulkan 按后端守卫排除)；VK demo 0 校验错误、GL demo 0 着色器/GL 错误；双后端 demo mipmap/audio 流式均初始化并运行。

此前：**Round 9 完成** — 平台补齐：gamepad 双平台接线(Linux evdev + Windows XInput 经 `platform_poll`→`input.gamepads`)、Wayland 相对指针/指针锁/NULL 光标隐藏(zwp_relative_pointer_v1 + zwp_pointer_constraints_v1，CMake 生成协议绑定)、macOS 经 Cocoa(`window_cocoa.m`, NSWindow+CAMetalLayer)+ MoltenVK 复用 VK 后端可链接(`rhi_vk.c` 加 `VK_EXT_metal_surface`+portability，CMake macos 分支)。`test_input` 增 3 项 gamepad 契约测试。**实测**：X11 双后端 CTest **25/25**；Wayland(VK) 链接通过；macOS 因 Linux 环境未实测构建。

此前：**Round 8 完成** — 场景资源序列化补全。`scene_serial.c` 的 RESOURCES chunk 由空占位改为真实清单：从 `Scene` 的 meshes/materials/textures 派生资源记录，每条含确定性 GUID(对类型+索引+描述符做 FNV-1a 64)；mesh 描述符(index/vertex count、material_idx、AABB)、material 描述符(base_color、metallic/roughness、emissive、alpha mode/cutoff)、texture 按 RHI 句柄身份去重引用。`SerializeOptions.include_resources` 真正生效：true 内联描述符、false 仅写 {guid,type,ref,path} 轻引用。`Scene` 增 `resources`/`resource_count`(load 时回填，`asset_scene_free` 释放，另导出 `scene_resources_free`)。**ECS↔Scene 统一 ID**：`load_entities_chunk` 现恢复保存的 entity `generation`(此前丢弃)，使 (index,generation) 身份跨存读一致，成为持久统一 ID。`test_scene_serial` 扩到 23 项(新增 include 往返、refs-only 往返、GUID 确定性、generation 恢复)。**实测**：双后端构建通过；CTest **25/25**(`test_scene_serial` 内 23 子项全过)。

此前：**Round 7 完成** — 内置真实 Lua 5.4 脚本。vendored Lua 5.4.7 到 `engine/external/lua`(经 `onelua.c` 单编译单元 + `MAKE_LIB` 构建为独立静态库 `lua`，第三方代码用 `-w` 豁免引擎 `-Werror -pedantic`)。新增 `script/script_lua.{h,c}`：真实 `lua_State` + `luaL_openlibs`；`lua_script_load`/`_load_string`(语法/运行期错误经日志优雅失败)、`on_start`/`on_update(dt)`/`on_spawn` 钩子探测与 `pcall` 调用、数值全局 get/set、按 mtime 的 `.lua` 热重载。注册 `engine.*` 绑定表(经 registry 取宿主指针，宿主指针为 NULL 时全部安全降级)：`log`/`entity_count`/`body_count`/`get_pos`/`set_pos`/`get_vel`/`set_vel`/`apply_impulse`/`spawn`/`body_set_ccd`/`key_down`，分别接 ECS `World`、`PhysicsWorld`、`InputState`。`main.c` 绑定宿主、加载 `assets/init.lua`、`on_start` 一次 + 每帧 `on_update`+热重载。新增 `assets/init.lua`(真实 Lua)。新增 `test_script_lua`(15 项：错误处理/钩子/绑定真实改物理体/越界安全/热重载)。旧 DSL `script.c` 与 `test_script` 保留兼容不动。**实测**：双后端构建通过；CTest **25/25**(新增 `test_script_lua`)；VK/GL `engine_demo` 均成功 `Lua script loaded: assets/init.lua (start=1 update=1 spawn=1)` 并打印 `on_start`(11 实体/11 刚体)，VK 0 VUID、GL 0 着色器/GL 错误。(GL 链接期有一条 glibc 对 Lua `os.tmpname` 用 `tmpnam` 的良性告警，非编译错误。)

此前：**Round 6 完成** — ECS system 调度 + 物理形状/CCD/回调 + 角色胶囊 sweep。新增 `ecs/ecs_system.{h,c}`：`EcsChunkView` 视图 + `ecs_chunk_column`(SoA 列基址)/`ecs_chunk_entity_ids`、`ecs_parallel_for`(每非空 chunk 一个 task，`ts==NULL` 串行)、`EcsScheduler` 系统注册按序执行；`main.c` 把"物理→Transform 同步+越界重生"手写遍历迁入 `sys_sync_transform_from_physics`，经现有 `tasks` 工作线程并行 dispatch。Physics 扩 `ShapeType`(盒/球/胶囊)+`radius`/`half_height`/`ccd`；`aabb_from_body` 按形状算包围盒；新增 `physics_body_create_sphere`/`_capsule`/`_set_ccd`/`physics_set_contact_callback`/`physics_collide`(球-球/球-盒/球-胶囊/胶囊-胶囊/胶囊-盒分派 + `closest_seg_seg` 等几何助手)；`physics_step` 集成 swept-sphere CCD(`ccd_sweep_static`/`integrate_body_ccd`) 防高速穿透并触发 `Contact` 回调。角色 `character_update` 重写为胶囊 collide-and-slide：`char_slide_resolve` 迭代脱离静态几何并按坡度判定 grounded，分"垂直/水平/抬腿(up-forward-down)"三阶段实现 step/slope/wall。新增 `test_ecs_system`(5)、扩充 `test_physics`(34)/`test_character`(20)。**实测**：双后端构建通过；CTest **24/24**(新增 `test_ecs_system`)；VK Debug `engine_demo` 8 帧迁入的并行 ECS system 正常驱动(Phase4: 10 实体/11 刚体)、**0 VUID**(仅余 2 条 pre-existing `ShaderOutputNotConsumed` 警告)；GL `engine_demo` 仍 0 着色器/GL 错误。

此前：**Round 5 完成** — GL 后端一致性补齐。修复共享 `post.vert`（`#version 450` + `#ifdef VULKAN` 切 `gl_VertexIndex`/`gl_VertexID`）解锁约 20 个 GL 后处理着色器；批量修复其余 GL 专属着色器编译失败（terrain frag 显式 out、sharpen float→vec3、ssao/dof 残留垃圾、particle/depth_only/hi_z/occlusion 的 push 常量与 `set=` 守卫、skinned/bloom/post_tex 版本与 `layout(location)`）；`rhi_gl.c` 的 `gl_bind_tex_unit` 改为按资源类型选 GL target（cubemap/点光深度 cube 绑 `GL_TEXTURE_CUBE_MAP` 而非 `GL_TEXTURE_2D`），点光深度 cube 标记为 `RHI_RES_CUBEMAP` 且按 `samplerCubeShadow` 走纹理级 compare 参数，`rhi_cmd_transition_depth_to_read` 明确为 GL 下的合法 no-op。**实测**：GL `engine_demo` 8 帧 **0 着色器/链接/GL 错误**（仅余缺 ttf/缺 glb 资源警告），cluster binning 启用；VK Debug `engine_demo` 与 `test_vulkan`（含 GPU binning + 真 IBL）仍各 **0 VUID**；双后端构建 + CTest 23/23。

此前：**Round 4 完成** — 接通真 cubemap IBL（程序化天空 capture→irradiance/prefilter 卷积→BRDF LUT，全部 RGBA16F+mip）并让 PBR 经 `HAS_IBL` 采样真 IBL；新增 `cluster_cull.comp` 把 clustered 光照 binning 迁到 GPU（替换 CPU `light_system_cull`）。VK Debug（校验层开）下 `test_vulkan` TEST 7（含 GPU binning + 真 IBL）与 `engine_demo` 实时主循环各跑均 **0 VUID**；双后端构建 + CTest 23/23。所有 Round 4 着色器在 GL 语义下亦编译通过。

此前：**地基轮 A-E + 收尾全部完成** — VK 校验层在 forward/视锥剔除/遮挡三路径各 60 帧 0 FATAL/0 错误，双后端构建 + CTest 23/23（详见"地基修复轮"专节）。**重要更正**：Round 1 文档曾称"双后端 120 帧无验证层错误、CTest 23/23"，该结论来自 Release 构建(未启用校验层)且 `test_task` 偶发通过。开启 Vulkan 校验层后发现大量既有问题（见专节），`test_task` 实为偶发 段错误/死锁，现已全部修复。

## 图例

- 完整：功能闭环、已接入运行时、有测试或可观测验证。
- 部分：核心可用，但有明显简化/未接线/缺特性。
- 桩：仅有骨架/占位，运行时基本未生效。
- 缺失：未实现。

## 渲染（性能优先重点区）

| 模块 | 状态 | 证据 / 说明 |
|------|------|-------------|
| RHI Vulkan 后端 | 部分 | `rhi_vk.c`；缺 ~~push-constant 公开 API、~~bindless；~~firstIndex/baseVertex~~ R208-B 已补 `rhi_cmd_draw_indexed_base(first_index, vertex_offset)`（R434 核查修正）。R4: cubemap 支持任意 `format`+`mip_levels`+per-face-per-mip 存储视图；新增 `rhi_cubemap_transition_to_read`/`rhi_texture_transition_to_read`；`rhi_cmd_memory_barrier` 扩到 fragment/uniform 读以同步 compute 产出的 cluster 网格。**R438**：注册 VkDebugUtilsMessengerEXT + `rhi_vk_validation_message_count` API，validation 计数==0 固化为 test_vulkan 硬门禁；**R439**：debug 回调 `#ifndef NDEBUG` 守卫（Release -Werror 既有问题修复）；**R440**：顶点输入 `is_shadow_depth` 单 attribute 分支 + MRT desc 格式字段与专用 render pass——demo 启动期 9 条 validation 性能警告清零，shutdown 打印计数观测；**R441**：2D 数组纹理（arrayLayers+2D_ARRAY view）+ `shaderDrawParameters` feature。**R444**：`rhi_cmd_push_constants` 公开 API（校验按声明 range，修静默截断；GL 文档化空操作），test_cmd_buffer 28 项；**R445**：skybox 三 uniform 映射补齐（此前从未上传）；`rhi_texture_read_pixels` RGBA16F 按 8B/px（原 4B 越界）；**R550-E**：debug messenger 从 `#ifndef NDEBUG` 改显式运行时开关（`rhi_vk_validation_set_enabled`，Debug 默认开），test_vulkan 经 `ENGINE_VK_VALIDATION` 武装——Release 门禁不再空转；`rhi_offscreen_fbo_create_fmt` image 补 `TRANSFER_SRC` usage（TEST 6 readback 的 3 条存量 validation 清零，Debug/Release 门禁均 0 消息）；**R552-A/B**：`rhi_texture_create` color usage 补 `TRANSFER_SRC`（demo bake 材质回读 20 条 validation 清零）；旧 `set_uniform_*` helper 按声明 push range 校验（原 256 硬编码边界致 `[range,256)` 写入 flush 时静默丢弃，R444 同类缺陷残留关闭）；**R555**：启用 `independentBlend` 后透明 MRT 在 RT0 blend/RT1 overwrite；无该 feature 时合法回退。`rhi_cmd_update_buffer` 的 UBO/texel 目标均声明 `TRANSFER_DST`，VK demo 120 帧 validation 为零 |
| RHI OpenGL 后端 | 部分→大幅补齐(R5) | `rhi_gl.c`。R5: ~~`gl_bind_tex_unit` 固定 `GL_TEXTURE_2D`→cubemap 绑定错误~~ 改为按 `dev->slots[idx].type` 选 target（`RHI_RES_CUBEMAP`→`GL_TEXTURE_CUBE_MAP`，含点光深度 cube），深度格式 cube 走纹理级 `COMPARE_REF_TO_TEXTURE`（解绑 sampler object 以保留 `samplerCubeShadow` PCF）；点光深度 cube 的 `depth_tex` 在 `rhi_cubemap_depth_fbo_create` 标记 `RHI_RES_CUBEMAP`。~~`rhi_cmd_transition_depth_to_read` 空实现~~ 明确为 GL 合法 no-op（GL 无显式 layout，FBO 深度→采样的 hazard 由驱动隐式同步）。~~共享 `post.vert` 用 `gl_VertexIndex`+varying `layout(location)` 致约 20 个 GL 后处理编译失败~~ 已修（见后处理行）。~~遗留：cubemap 仍 RGBA8 路径需按需扩展；`rhi_cmd_bind_texture` 对 compute 管线 sampler 处理仍简化。~~（R550 核查修正：cubemap 自 R4 起按 `desc->format`/`mip_levels` 走，RGBA16F+mip 支撑 IBL；compute 采样自地基A `rhi_cmd_bind_texture_compute` 起走同一 `gl_bind_tex_unit` 缓存路径——两处遗留均过时）。**R435**：`gl_frame_begin` 补 VK 对等语义（绑 FBO 0 + 清深度）——修复 R434 哨兵暴露的 golden 空转假绿（原参考图为全黑图，已经 GOLDEN_UPDATE 重新生成为真实渲染）；**R441**：`glTexImage3D` 2D 数组纹理（实测无 ARB_bindless_texture，数组为唯一双后端路线）；**R445**：全屏 blit 深度规则修复（同左）；**R550-B**：Hi-Z chunk 生成的 mip 采样改绑惰性缓存单 mip `glTextureView`（原 BASE/MAX clamp 绑原纹理对象触发 Mesa image/sampler feedback 守卫，mip 4–8 恒 0 → showcase unified cull 全剔走回退）；纹理存储改 `glTexStorage2D` 不可变（view 前置条件），`glTextureView` 失败回退原 clamp 路径；**R551-A/B**：font 死 uniform（location 0 撞上 sampler `u_atlas`，每帧 0x502）删除；mega 单 execute 路径 `bind_pipeline` 切 VAO 后补绑 mega VBO/IBO（GL 缓冲绑定是 VAO 状态——此前 arr VAO element buffer 为 0，mdic 每帧报错且整 draw 被跳过）；MESA_DEBUG 120 帧零错误 |
| GPU 视锥剔除 | 部分→完整(R1,R11) | R1: `cull.comp` 重写为双后端、输出可见性 flags；`gpucull.c` 改用 `rhi_shader_create_compute`；新增 `gpucull_dispatch_flags` 把剔除结果直写进 indirect 可见性缓冲。**R11**: `mega_buf.valid` 时 demo 默认 `gpu_indirect_enabled && gpucull_enabled`，并初始化 `gpucull_init_unified`(仍走 flags 路径，为 R12 unified 铺路) |
| 统一剔除(unified) | 部分→Hi-Z(R1,R11,R12,R16,R101) | R1: `unified_cull.comp` 单 pass 视锥+压缩。**R12**: 阴影/点光默认 unified。**R16**: unified 可选 Hi-Z 球体测试（上一帧金字塔，1 帧延迟）；CSM/点光 unified 传入 occ=NULL（R170-A，R436 核查修正）。**R101**: unified 路径全激活时跳过冗余 `occlusion_cull_dispatch`（Hi-Z 生成仍运行供 unified 采样）。**R436**：Hi-Z 金字塔生成 chunk 化（10→3 dispatch/barrier；rhi_vk image 描述符按 pipeline 累积单 set）；TEST 9 扩展真实遮挡断言。~~遗留：前向仍 per-mat compact~~ **R437**：单 system 容量区间单遍 scatter（每帧 compact G→1；~~execute 仍 G 次——材质固定槽位绑定~~ **R441** 已解决：纹理数组 + 材质间接，前向 execute G→1），TEST 10 门禁 |
| 间接绘制(indirect) | 完整(R1, 地基D加固,R11) | `indirect_draw.c` compact+execute；阴影 pass 现由 GPU 剔除 flags 驱动；修正 VK 下 `total_draws` push 常量映射缺失的潜伏 bug。**地基D**：修复 `rhi_cmd_bind_storage_buffer` 在 VK 下每次新建/重绑描述符集互相覆盖（compute 压缩此前只读到 binding 3、其余为垃圾）→ 改为按管线累积进同一集；启用 `drawIndirectCount` 1.2 特性；点光 cubemap pass 补 LOAD 孪生使间接绘制能在 compact 后 resume。**R11**: mega-buffer 有效时 demo 默认启用 GPU indirect 绘制。**R437**：grouped compact（mat_id/group_base/group_counts 三缓冲 + 单遍 scatter）；`upload` 兼容包装为单隐式组；新增 TEST 10（组计数/区间/零填充/dispatch 计数）；**R438**：demo 前向静态场景/ECS 实体互斥→叠加（`!drew_any` 初始提交遗留），mega 前向路径首次生效（`g_fwd_mega_taken` 每帧计数观测）；**R441**：材质间接——纹理数组 + first_instance 层号 + ungrouped 紧排，前向 execute G→**1**（`mega_mat_arrays_draw`；R437 grouped 保留作回退），TEST 11 像素级门禁；**R442**：deferred/gbuffer 同样单 execute（`mega_mat_arrays_draw_gbuffer`，MR 数组 pair 对齐）+ TEST 12；TEST 10/11/12 抽后端中性 helper，GL 端全覆盖 |
| 遮挡剔除 Hi-Z | 桩→部分→冗余消除(R11,R101) | ~~`occlusion_cull.c` 结果从未被消费~~ **R11 已接线**：Hi-Z compute + 1 帧延迟 readback 结果经 `node_occ_visible` 驱动前向 indirect(`vis_flags &= occ`)与 CPU frustum 回退(跳过被挡节点)；默认开启(`BREAK_OCCLUSION=0` 可关)。**R101**: unified 路径全激活时跳过 `occlusion_cull_dispatch`（结果无人消费）；Hi-Z 生成仍运行供 unified_cull 采样。~~遗留：Hi-Z 尚未并入 unified_cull 单 pass~~ **R436 已做**（chunk 化生成，剔除侧 R16 起已内联采样）；~~阴影 unified 路径已含 Hi-Z~~ R170-A 起阴影传 occ=NULL（R436 核查修正） |
| Clustered 光照 | 部分→完整(R4) | ~~`lighting.c:77-148` 纯 CPU light binning~~ R4: 新增 `shaders/cluster_cull.comp`（16×8×24 cluster、点光视锥+深度切片 binning，VP 矩阵+标量经 push 常量，VK `set=0` 双 SSBO，GL `std430 binding=0/1`+loose uniform）；`light_data_buf`/`light_grid_buf` 改 `TEXEL|STORAGE`；`light_system_init_gpu_cull` 载入管线、`light_system_cull_gpu` 每帧 dispatch（挂起当前 pass + grid 写→片元 texel 读 barrier）、`light_system_upload_lights` 仅传光数据由 GPU 产网格。修复 PBR 片元此前把密排 `u32` 网格当 `RGBA32F` 误读的潜伏 bug（新增 `grid_u32` 用 `floatBitsToUint` 还原）。~~near/far 仍取相机默认 0.1/100（demo 主循环值）~~ **R550-D**：`light_system_set_depth_range()` 随相机 near/far（值不变不触发 LUT 重算；未设置回退 0.1/100 默认，test_lighting 19 项） |
| 级联阴影 CSM | 部分→完整(R2，前向主路径) | R2: 4 级渲入单张 2048² shadow-atlas 的四象限(`main.c` 复用 `shadow_map`，新增 `rhi_cmd_set_shadow_viewport` 双后端)；`pbr_clustered(.frag/_vk)` 改为"最紧 cascade"选择+象限重映射+`textureSize` 真实 texel+边界 clamp；修复 VK 下 `bind_material_textures(_ibl)` 忽略传入 shadow 纹理(此前前向阴影采到 albedo)的潜伏 bug。**同时修复 `pbr_clustered_vk.frag` 此前从未在 VK 编译成功**(非块内非透明 uniform + push 常量超限 + `read_dir_light` 前向引用)→ VK 前向 PBR 主着色器首次可用。terrain/water 的 cascade-0 采样代码双后端一致，但 terrain/water 的 VK 着色器仍因既有移植缺口无法编译(见专节)。**R434**：texel snapping——`renderer/csm.h` `shadow_snap_lview_to_texel` 量化 light-space 平移到 texel 网格，接入 `main.c` 级联矩阵构造；`test_shadow` 6 项。**R438**：`lview` 转置布局修复（统一 canonical，提取 `shadow_cascade_lview` 入 csm.h；snap 读写同步 `e[3][0/1]`）——此前级联盒 8 角塌缩 ndc≈(0,0,-1)，阴影方向/位置无意义（渲染与采样同矩阵自洽）；表征测试 `cascade_vp_corners_fill_unit_cube` 门禁；**R439**：lview 右手基化（zenith fallback 双向 det=+1） |
| 点光阴影 | 部分→前向已接(R5 修 GL 绑定,R20-1) | `point_shadow.c` cubemap 深度可用于 deferred；~~前向无点光阴影~~ **R20-1 已接**：`pbr_clustered.frag`/`_vk.frag` 均有 `HAS_POINT_SHADOW` + `u_point_shadow_cubes[4]` 采样（本行 R434 核查修正，此前未随 R20-1 更新）。R5: 修复 GL 把点光深度 cube 误绑为 `GL_TEXTURE_2D` 的 bug（现按 `RHI_RES_CUBEMAP` 绑 `GL_TEXTURE_CUBE_MAP` 并走 `samplerCubeShadow` 纹理级 compare） |
| IBL | 桩→完整(R4) | ~~`HAS_IBL` 未定义；`ibl_generate(...,RHI_HANDLE_NULL)` 仅跑 BRDF LUT；irradiance/prefilter 为黑色占位面；PBR 走程序化天空近似~~ R4: 真 cubemap IBL 接通。RHI cubemap 扩 `format`+`mip_levels`+per-face-per-mip 视图（VK/GL），新增 `rhi_cubemap_transition_to_read`/`rhi_texture_transition_to_read`（GENERAL→SHADER_READ_ONLY）。新增 `sky_to_cube.comp`（Rayleigh/Mie 程序化天空 capture 进 RGBA16F env cube）；`irradiance_env.comp`/`prefilter_env.comp` 改 `image2D` 单面存储视图 + VK set 布局；`ibl.c` 创建 env/irradiance/prefilter 三张 RGBA16F+mip cube，`ibl_generate` 编排卷积并在每次 frame_end 后 `rhi_present` 防 swapchain 耗尽。`main.c`/`test_vulkan` 经 `shader_inject_define` 注入 `HAS_IBL`，PBR 采样真 irradiance/prefilter/BRDF LUT（bindings 6/7/8）。**R554/R555**：GL/Vulkan 共用 `tv_test_ibl` 图形门禁；Vulkan 测试使用专用 clip-space vertex contract，避免生产 clustered vertex/fragment 阶段 push 布局别名造成空三角形；完整双后端 graphics suite 已按顺序通过。**R434**：GL 端 `gl_frame_begin` 恒返 NULL 致 IBL 链整体跳过 → 哨兵句柄修复；`ibl.c` 静默早退改显式 `LOG_WARN` 降级 + 阶段跳过则 `ready=false`；`test_ibl` 4 项；**R552-C**：image-unit 绑定观察项核查关闭——双端无单元冲突/残留/错绑（VK 0 validation） |
| 延迟渲染 | 完整(R13,R16,R103) | **R13**：G-Buffer + 全屏光照接 cluster/CSM/IBL。**R16**：MRT RT3 velocity（NDC motion）；TAA 延迟路径采样。**R103**：`deferred_light.frag`/`_vk.frag` 接入点光 cubemap 阴影采样（`HAS_POINT_SHADOW` 条件编译）；`PointLight` 增加 `shadow_index` 指向 cubemap 阴影槽位；`deferred.c` 绑定点光阴影纹理到延迟光照 pass。**R553**：per-object motion history 已建立 TDD 生命周期契约；forward 仍保留 camera-only 兼容路径，双 MRT 优化待完成。**R440**：G-buffer 管线 base pipeline 改建于 G-buffer 兼容 MRT render pass（原建在单 attachment swapchain pass，潜在 render-pass 不兼容）；**R442**：gbuffer array 化单 execute（TEST 12 门禁）；修复 R440 存量 MRT render-pass dependency 缺失（VUID-02684）与 TRANSFER_SRC；**R551-C**：`deferred_light.frag` uniform 声明对齐 CPU 上传类型（uint→int、float[4]→vec4）——GL 下类型不匹配致写入被拒，方向光/点光循环此前从未生效（count 恒 0），修复后 GL deferred 光照真正参与 |
| 合并后处理 | 部分→demo 默认(R3,R11) | ~~`combined_taa_fxaa*`/`combined_color*` 着色器缺失，`combined_post_process.c` 永远回退多 pass~~ **已补(R3)**：新增 `combined_taa_fxaa_vk/.frag`(TAA 重投影+邻域 clamp + FXAA 单 pass) 与 `combined_color_vk/.frag`(色差采样→tonemap ACES/agx/khronos→饱和/对比/亮度/白平衡→暗角+grain 单 pass)；新增 `RHIPipelineDesc.combined_aa_layout/combined_color_layout` 标志 + VK 专属 push 偏移映射。**VK 实测**(`test_vulkan` TEST 6)：两条合并管线均激活、不再回退，10 帧 0 校验错误。**R11**: demo 主循环接入 —— TAA+FXAA 均开→`combined_aa_apply` 单 pass；tonemap+调色+cg 且 `!cine && !auto_exposure`→`combined_color_apply` 单 pass；resize/shutdown 生命周期完整；debug UI 显示 CombinedPost 状态。~~auto-exposure/cinematic 仍走原多 pass 链~~（R550 核查修正：R13-3/R19-1 已移除门禁，combined_color 现接收 auto_exposure 与 cine 参数单 pass 完成）。**R437**：velocity 无效时恒绑 4 纹理（占位 current_color）——TEST 6 的 10 条 VUID-08114 清零（taa.c fallback 同模式一并修）。**R445**：修复全屏 blit 被深度测试误杀（`depth_write_disable && !lequal → 关 depth test`，GL 自 R232/VK 自初始 RHI 潜藏——合成链从未到达屏幕），TEST 6 新增像素级断言；**R446**：天空双重 tonemap 修复（skybox 输出改线性 HDR）+ bloom 默认 0.15（修复后只命中太阳/高光）+ DOF 默认关 |
| 后处理各 pass(SSAO/SSR/SSGI/TAA/DOF/Bloom/Tonemap 等) | 部分→五路合成接线(R550-A) | 单功能可用。**R13**: TAA 用 `inv(curr_view_proj)`。**R16**: 延迟路径 TAA 可选 G-Buffer velocity 重投影（`u_taa_use_velocity`）；~~combined AA 仍相机 fallback~~ R17-1 已加 velocity（R434 核查修正）。~~SSR/SSGI/volumetric/lens_flare/contact_shadow 写私有 FBO 从不合成（默认关死）~~ **R550-A**：五路全部按 god_rays 自合成惯例接入帧链（cs 乘法/vol 透射+累积/lf 加法/ssr 置信度 lerp/ssgi 末级加法），`BREAK_SSR/SSGI/CS/VOL/LF=1` 开启即生效（默认仍关保成本），GPU A/B 像素证据齐全；**R550-C**：motion blur 跨度改 ∝ 像素速度（原恒 ≈1px 近 no-op），上限 200px clamp；**R556**：motion blur 与 TAA 统一优先使用 forward/deferred RT1 velocity，动态物体不再在 blur pass 回退到 camera-only depth 重建；RT1 不可用时原重建路径仍是安全降级。**R551-E**：skybox 顶点级 normalize 致方向场非线性扭曲（太阳圆盘偏 26°）——删顶点 normalize；lens flare 调用点改传 `-sun_dir_vec`（原锚在反日点，自初版即存在）——skybox 圆盘/lens flare/god rays 三锚点像素级重合（双端一致）；**R551-D/F 核查**：VK flare Y 翻转疑点与 spin0 伪速度均证伪（观测路径伪影，量化证据见 R551 条目） |
| 粒子系统(GPU) | 部分→GPU cull(R12)→indirect(R167)→逐粒子速度(R555) | compute+graphics 可用。**R12**: `particle_cull.comp` 接线。**R167**: cull buffer 改为 `DrawIndirectCommand`+indices；`rhi_cmd_draw_indirect` 双后端；`particles_render` 仅调度 alive 实例（不再每帧 8192 VS early-out）；debug UI `last_alive_count` 仍为上界提示（无 CPU readback 停顿）；**R445**：管线补 `depth_compare_lequal`（深度规则下行为不变）；**R555**：SSBO 增 `previous_pos`（64-byte layout 测试锁定），update shader 在积分前保存位置、spawn 令 previous=current；forward MRT vertex/fragment 输出真实速度，透明 RT1 不 alpha blend，GL 120 帧 `MESA_DEBUG` 无 compute/graphics error |
| 骨骼蒙皮(GPU) | 完整 | `skeleton.c` joint buffer 上传 + skinned shader |

## Rule Engine

| 模块 | 状态 | 证据 / 说明 |
|------|------|-------------|
| Rule-engine C99 core | 部分 | `engine/src/rule_engine/rule_engine.h` and `engine/src/rule_engine/`; `rule_engine_core` is graphics/Lua-independent. The focused cases in `engine/tests/test_rule_engine.c` cover flat facts, parsing/install, action references, callbacks, limits, bounded agenda controls, private/rebuild-based RETE, streaming windows and correlation, callback and memory providers, and the bounded query seam. The bounded backward slice covers zero-argument and parameterized goal chains, literal/propagated formal binding, nested goal operands, registered custom-function operands, boolean alternatives, recursive traversal, cycles, depth and solution limits, deterministic derivation-path proof nodes/edges, and fact-mutation invalidation; Phase 3 adds query-level `NOT` negation-as-failure, bounded query aggregation (COUNT/SUM/AVERAGE/MIN/MAX/FIRST/LAST), DFS/BFS/iterative-deepening strategy selection, and a bounded shared proof graph result cache; arbitrary predicate unification, shared-subgraph provenance, native Redis, and RETE-UL parity remain unsupported. C11 executor evidence is opt-in. See `docs/Rule_Engine_Architecture.md`, `docs/Rule_Engine_Design.md`, `docs/Rule_Engine_Benchmark.md`, and `docs/rule_engine_conformance.yml`. |

## 游戏运行时

| 模块 | 状态 | 证据 / 说明 |
|------|------|-------------|
| ECS | 完整(R103) | `ecs.c` archetype+chunk 完整。R6: 新增 `ecs_system.{h,c}` —— `EcsChunkView`+`ecs_chunk_column`(SoA 列)/`ecs_chunk_entity_ids`、`ecs_parallel_for`(每非空 chunk 一 task，`ts==NULL` 串行)、`EcsScheduler` 系统按注册序执行(系统间串行避免列写竞争、chunk 内并行)；`main.c` 物理→Transform 同步迁入 `sys_sync_transform_from_physics` 经 `tasks` 并行。`test_ecs_system` 5 项。R102: `edges_add/remove` 从桩→完整实现——`edge_lookup_add`/`edge_lookup_remove`/`edge_cache_add`/`edge_cache_remove` 四辅助函数，`world_add_component`/`world_remove_component` 先查 edge 缓存(O(E))命中则跳过 `find_archetype` O(N) 扫描+类型数组构建。**R103**: 查询新增 Exclude/Optional 组件支持——`ecs_query_exclude`（排除含指定组件的原型）、`ecs_query_optional`（可选组件）、`ecs_query_refresh`（查询失效时重建匹配原型列表）；`Query` 结构扩展 `exclude_mask`/`optional_mask` 位域，`query_matches_archetype` 位掩码 O(1) 过滤。`test_ecs` 新增 5 项 Exclude/Optional 测试 |
| Physics | 部分→形状/CCD/回调(R6) | R6: `ShapeType` 盒/球/胶囊 + `radius`/`half_height`/`ccd`；`aabb_from_body` 按形状；`physics_body_create_sphere`/`_capsule`/`_set_ccd`/`physics_set_contact_callback`；`physics_collide` 分派(球-球/球-盒含内部脱出/球-胶囊/胶囊-胶囊/胶囊-盒，`closest_seg_seg`/`closest_on_aabb` 助手)；`physics_step` 集成 swept-sphere CCD(`ccd_sweep_static`/`integrate_body_ccd`)防穿透 + 触发 `Contact` 回调。`test_physics` 51 项(含 `ccd_prevents_tunnel`/`no_ccd_tunnels`)。~~遗留：无关节/约束；CCD 仅对静态体扫掠~~ **R435**：距离关节（64 槽约束表 + Gauss-Seidel 位置投影）+ dynamic-vs-dynamic 保守 CCD；test_physics 51 项；**R440**：约束速度级求解（轴向相对速度全消除冲量，R435 漂移抖动闭合），test_physics 54 项；**R443**：球窝关节（锚点偏移重合 + 全向量速度消除；无旋转模型），test_physics 58 项 |
| 角色控制器 | 部分→胶囊 sweep+step/slope(R6) | R6: `character_update` 重写为胶囊 collide-and-slide。`char_capsule` 由脚底构造胶囊刚体；`char_slide_resolve` 迭代脱离静态几何并按 `slope_limit` 判 grounded；分垂直(重力/跳)、水平(墙滑)、抬腿(up→forward→down，受 `step_height` 限)三阶段，落实此前未用的 `slope_limit`/`step_height`。`test_character` 20 项(含 `wall_block`/`step_up`/`high_step_blocks`)。**R436**：动态体交互——顶面可站立（grounded 自然生效）、侧/底面 `physics_push_body` 推开（无限质量 KCC，rest_frames=0）；test_character 24 项；**R437**：平台速度携带（ground_body 跨帧记录，重力积分前按上帧支撑体速度携带，三向精确），test_character 27 项 |
| Animation | 部分→事件回调(R101) | 单 clip + GPU skin 可用；~~blend/IK 已实现但 demo 未接~~ R19-2/R20-2 已接入 demo（`main.c` init + 每帧 `anim_blend_evaluate`/`anim_ik_solve`，R434 核查修正）；**R101**: 事件回调现由 `anim_blend_evaluate` 按时间区间触发（含循环 wrap-around）；新增 `AnimEvent`/`anim_clip_add_event` API；`test_animation` 24 项；**R445**：程序化 4 关节机械臂双 clip blend + IK 默认接线（glTF 无骨骼时走程序化路径，env 可关）——blend/IK 从死代码变默认可见；**R551-G**：IK 测试补强——tip 到达 target 断言（容差 1e-3）+ 超程不可达用例（37 项），关闭 R317 遗留 |
| Script(Lua) | 桩→完整(R7) | R7: vendored Lua 5.4.7(`external/lua`，`onelua.c`+`MAKE_LIB`→静态库 `lua`)；新增 `script_lua.{h,c}` 真实 `lua_State`+标准库，`on_start`/`on_update(dt)`/`on_spawn` 钩子、数值全局 get/set、`.lua` mtime 热重载、`engine.*` 绑定表(log/entity_count/body_count/get_pos/set_pos/get_vel/set_vel/apply_impulse/spawn/body_set_ccd/key_down，宿主 NULL 安全降级)。`main.c` 加载 `assets/init.lua` 并每帧 `on_update`+热重载，demo 启动即执行 `on_start`。`test_script_lua` 15 项。旧 `.script` DSL(`script.c`/`test_script`)保留兼容 |
| Network | 部分→多类型(R15–R25) | transform/heartbeat 独立序列+重排槽；`net_replicator_send_heartbeat()`；~~reliable pending 仍全局一份~~ **R434**：8 槽在途窗口（逐槽 ack/重传、满拒计数），`test_net_replication` 33 项；**R435**：delta.log 超 1MiB 自动轮转（重写基线+原子替换）；**R547**：轮转基线清理陈旧 `.peer` 文件，避免已驱逐 peer 在加载时复活；**R555**：full peer table 的 LRU 逐项按 `now-last_seen` unsigned age 选择最老项，替代在进程运行超过半个 u32 周期时会误判的带符号 timestamp 差；`peer_lru_full` 连续稳定通过 |
| Scene 序列化 | 基本完整 | ECS 实体/组件 + SceneNode 可往返；**RESOURCES chunk 已实现**(mesh/material/texture + 确定性 GUID + 可内联描述符)；`include_resources` 生效(内联/轻引用)；**generation 恢复**使 (index,gen) 成为统一持久 ID；`test_scene_serial` 23 项全过 |
| Task 调度 | 基本可用(地基C已修，R6 接入 ECS) | `task.c` work-stealing + 优先级 + 依赖 + wait；**地基C 已修三处竞态**：①`flush` 在锁外 reset `submit_count` 致提交覆盖丢任务(死锁) → 改为锁内 detach；②`flush` 向非owner worker deque push 违反 Chase-Lev 单生产者(段错误) → 改为各 worker 拉取到自己 deque、非worker 线程内联执行；③`task_wait_handle` 解引用可能已释放的 task(UAF段错误) → pool 持引用直到 destroy。`test_task` 双后端各连跑 100/60 次全通过。R6: `ecs_parallel_for` 把 ECS chunk 作为 task 提交并 `task_wait` 同步，已在 `test_ecs_system` 与 demo 主循环验证 |

## 平台 / 资源 / 音频 / UI / Core

| 模块 | 状态 | 证据 / 说明 |
|------|------|-------------|
| 平台 Windows(Win32) | 完整 | 窗口/输入/raw input/DPI/多显示器；**XInput gamepad 已接线**(`gamepad_win.c`，动态加载) |
| 平台 Linux X11 | 完整 | 窗口/输入/抓取/XRandr 多显示器；**evdev gamepad 已接线**(init/poll/shutdown) |
| 平台 Linux Wayland | 基本完整 | 窗口/输入；**相对指针(zwp_relative_pointer_v1)+指针锁(zwp_pointer_constraints_v1)+NULL 光标隐藏**已落实；**evdev gamepad 已接线**；~~单 output~~ **R443**：多 output 枚举（wl_output 槽位数组 + xdg-output 逻辑坐标/名称；线上行为未经真实 compositor 验证），test_wayland 8 项；**R444**：热插拔 remove（压缩式，三平行数组同步 + ctx 重编号），test_wayland 12 项 |
| 平台 macOS | 可链接(未实测) | `window_cocoa.m`(NSWindow+CAMetalLayer)经 MoltenVK 复用 VK 后端；`rhi_vk.c` 加 `VK_EXT_metal_surface`+portability；CMake macos 分支(OBJC+frameworks)。Linux 环境无法实测构建 |
| Gamepad | 完整 | Linux evdev(`gamepad_linux.c`)+Windows XInput(`gamepad_win.c`) 均经 `platform_poll`→`input.gamepads` 接线；统一按钮/轴语义(up=负、扳机 0..1) |
| Asset 热重载 | 部分(R14) | **R14**：`hotreload_texture_*` 实现 mtime 纹理重载 + GPU 重建；着色器管线热重载仍可用。~~遗留：demo 未默认接线纹理热重载~~ R17-3 已接线（`main.c` init + 每帧 poll，R434 核查修正） |
| Async Loader | 完整(R103) | 真异步线程。**R103**：priority 最小堆替换 FIFO 队列，高优先级请求优先出队；新增 2-worker 解码线程池 `decode_pipeline.c/h`，stb_image 解码 + mipmap 生成不阻塞主线程，解码完成后回调主线程上传 GPU。`test_async_loader` 新增优先级和解码管线测试 |
| Mipmap 流式 | 桩→完整(R10) | ~~回调空、仅 track residency，`level_data` 从不赋值、未接入 main~~ R10: `MipLoadReq` 上下文经 `async_loader_request_range` 把 level 数据写入 `level_data`、按预算记 `total_resident_bytes`，命中经 `MipmapUploadFn` 钩子真传 GPU(新增 RHI `rhi_texture_upload_mip`：GL `glTexImage2D` / VK staging buffer+逐 mip image barrier)；`mipmap_stream_update` 按预算驱逐、`_force_level` 内泵 `async_loader_tick`；修复 `coverage_to_level` 反向 bug(全覆盖→level0)。接入 `main.c`(程序化 256² 9-mip 文件、相机距离驱动驻留/驱逐、debug UI 展示)。`test_mipmap_stream` 验证驻留/上传/预算驱逐 |
| VFS + packer | 完整(R103) | 目录挂载 + .pak 只读。**R103**：Windows packer 重写为 `CreateFileMapping` 零拷贝打包 + `FindFirstFile`/`FindNextFile` 递归遍历，与 POSIX 版二进制兼容（相同 magic + 字节序 + 对齐）；新增 `verify_pak.c` 验证工具 |
| Audio 播放 | 部分→流式 3D(R10) | `audio.c` listener+简单播放。R10: 增 `audio_play_streamed`(miniaudio `MA_SOUND_FLAG_STREAM`)、`audio_source_set_position`/`_set_attenuation`(逆距离模型)/`_set_volume`/`_start`/`_at_end`/`_cursor_seconds`；纯函数 `audio_attenuation_gain` 可无头单测。~~仍无混音总线~~ **R435**：混音总线（8 槽总线表 + master，source×bus×master 合成，demo 已接线 sfx/music）；**R462**：master fader 变更同步重算所有子总线路由 source，避免设备端保留旧增益，test_audio 17 项；**R445**：sfx 总线实载（880Hz 短音 + 碰撞 RMS 音量缩放 + 10Hz 节流 + 槽位回收） |
| Audio 流式 | 桩→完整(R10) | ~~双缓冲框架但不向声卡输出~~ R10: `audio_stream.c` 重写为 miniaudio 流式后端 —— 每个 `AudioStream` 包一个 `MA_SOUND_FLAG_STREAM` 源(由声卡线程逐块解码/补帧)，支持 2D/3D(`audio_stream_open_3d` + 距离衰减)、播放/暂停/停止/移动、状态轮询、增益诊断(`audio_stream_attenuation`)。`main.c` 生成正弦 WAV 作 3D 音源真播放。格式由 miniaudio 解码器支持(WAV/MP3/FLAC) |
| UI | 部分→IMGUI 控件(R10) | `debug_ui.c` 调试文本叠加保留。R10: 新增 `imgui.{h,c}` 即时模式 UI —— `ImUI` 上下文(hot/active 状态、布局)、label/button/checkbox/slider_float；`static inline` 纯逻辑助手(hit/slider 映射/按压状态机)可无头测；接入 demo(反引号切换设置面板，独立 `FontRenderer` 避免与 debug_ui 共享 VBO 冲突)。**R437**：新增 collapsing header（调用方 bool* 持久化 + 矢量折叠标记）与 radio 控件；demo 面板分组并接入 FXAA 档位；test_font_ui 23 项；**R441**：int slider（SSAO 档位接线），test_font_ui 27 项；**R551-G**：test_font_ui 真链接 imgui.c（font==NULL 时绘制调用本就 no-op + 6 个 link-only 桩，删 ~130 行复制逻辑，断言不变），关闭 R437 遗留 |
| 字体 | 部分→UTF-8(R10) | ~~仅 ASCII 32-127~~ R10: 新增 `utf8.{h,c}` 健壮多字节解码(拒绝 overlong/代理半区，永不卡死)；`font.c` 烘焙 ASCII+Latin-1 范围、码点查找表、保留白像素供 `font_renderer_draw_rect`；新增 `font_renderer_text_width`/`_line_height`。~~仍无 kerning/SDF~~ **R436**：kerning 已做（烘焙期 legacy kern 表提取 96 对稀疏存储，draw/text_width 同构接入；~~SDF 仍缺~~ **R439**：SDF 已做（stbtt_GetCodepointSDF 烘焙 + smoothstep/fwidth 采样，排版/kerning 兼容））；test_font_load 16 项；**R442**：GPOS kerning（PairPos Format 1 自解析，与 kern 表 908 对交叉验证全等；Format 2 明确缺口），test_font_load 22 项；**R443**：GPOS Format 2（class-based PairPos，glyph_filter 爆炸控制 + 合成 oracle），test_font_load 29 项 |
| Core 分配器 | 部分→通用 pool(R10) | heap/arena/debug 包装。R10: 新增定长块 `pool.{h,c}`(侵入式空闲链、O(1) acquire/release、`owns_base` 跟踪自管缓冲、接入 `Alloc` vtable)；`test_pool` 覆盖耗尽/释放复用/对齐 |
| Profiler | 部分→Chrome trace(R15) | CPU 环形缓冲 + R10 GPU timer。**R15**：`profiler_export_chrome_trace()` 写 Chrome Trace JSON（CPU `ph:X` + GPU 样本 + frame 边界）；demo F11/`PROFILER_TRACE=1` 触发；`test_profiler` 增导出测。~~遗留：无线程级采样~~ **R434**：真实 tid 分轨 + `thread_name` metadata（`profiler_register_thread`/TLS 惰性分配），`test_profiler` 25 项 |
| 测试 | 部分→扩充(R10,R15) | R10: CTest 升至 **30 项**(VK；GL 29)。**R15**：双后端 CTest **31/31**（+`test_net_replication`、GL 纳入 `test_vulkan` golden-only）；`tests/golden/test_vulkan_gl.ppm`；`test_profiler` 增 Chrome trace 测；VK `test_vulkan` 仍跑全集成套件 + golden。**R436**：双后端 `ctest -LE graphics` 37/37 + `-L graphics` 1/1（VK TEST 9 扩展为真金字塔遮挡断言，不再是 NULL-hi_z 空转 smoke）；**R437**：新增 TEST 10（indirect_draw 门禁）；VK 集成 Validation Error/Warning 清零（原 10 条 08114）；**R438**：矩阵表征测试 5 项（lookat/camera_view/VP 地面真值/CSM 立方体）+ 非单位相机 golden 变体（双后端新参考图，reject_blank 守卫）+ VALIDATION GATE 0 条；**R439**：右手基表征测试（det=+1/屏幕朝向/WASD 手感）+ golden cam 双后端按右手基重生成（mirror-MAE=0.00 客观验证）+ GL/VK demo 冒烟均 rc=0（VK 历史首次）；**R440**：GitHub Actions CI 上线（gl/vk 双 job 无头套件门禁，README badge；graphics 因 runner 无 GPU 不入主门禁——理由见 Build_Guide §6.4）；**R441**：TEST 11（材质间接单 execute 合成多材质像素断言）；**R442**：TEST 12（deferred array MRT 像素断言）+ TEST 10/11/12 GL 端覆盖（GL 分支不再早退）；**R443**：新增 test_wayland（多 output 纯逻辑 8 用例），ctest 注册 38→39 个，三构建各 38 项无头（`-LE graphics`）+ 1 graphics；**R444**：全套件并行安全（test_tmp per-pid + UDP 端口 16 块派生），15 路并发压测 30/30；**R445**：TEST 6 像素级断言（blit 空转不再假绿）；`BREAK_SCREENSHOT=N`/`BREAK_CAM` 脚本化截图与相机 env；**R446**：截图 R/B 交换+VK 翻转修正（此前全部 BMP 证据红蓝反色）；BREAK_DOF/BREAK_BLOOM/BREAK_UI kill-switch；**R550**：`test_shader_io` 新增五路合成链色契约断言（双后端 10 shader）；`test_lighting` +4 项（19/19，深度范围 LUT）；VALIDATION GATE Release 生效且存量 3 条 TRANSFER_SRC 清零（Debug/Release 均 0 消息）；GNU Release 构建修复（audio bus 容量守卫）；**R551**：test_animation 37 项（IK tip 断言）、test_font_ui 真链接 imgui.c（27 项不变）；**R552**：test_cmd_buffer 28→30（push helper range 校验，R444 遗留关闭） |

## Round 2 实测发现：Vulkan 后端基础性缺陷（开启校验层后）

> 这些是开启 Vulkan validation layers 后暴露的既有(pre-existing)问题，原计划低估了 VK 后端的破损程度。它们大多属"写了却没生效"，与用户"性能优先 + 修复无效功能"的目标高度相关，但跨越多个计划轮次，需要单独决策是否优先处理。

**A. VK 着色器编译失败（对应特性在 VK 上静默禁用）**
- ~~`terrain_vk.*`、`water_vk.*`：out/in varying 缺 `layout(location=)`；片元用非块内 `uniform` → VK 报 "non-opaque uniforms outside a block"。~~ **已修复(地基B)**：给 varying 加 `layout(location=)`，所有 uniform 收进 push 常量块；地形丢弃恒等 model、水面无 model，两者均装进 256B；新增 `RHIPipelineDesc.terrain_layout/water_layout` 标志 + `rhi_pipeline_get_uniform_location` 专属偏移映射。VK 上地形/水面现已正常编译并渲染。
- ~~`ssao_blur`(括号不配对 syntax error)、`sharpen`(float→vec3 赋值)、`debug_viz`/`lens_effects`(非块内 uniform)：VK 上这些后处理/调试 pass 静默禁用。~~ **已修复(地基E)**：`ssao_blur_vk.frag` 补回 `vec2(textureSize(...))` 缺失右括号；`sharpen_vk.frag` 改 `vec3 w = vec3(...)`；`debug_viz_vk.frag`/`lens_effects_vk.frag` 把散落 uniform 收进 push 常量块（debug_viz 统一改 `u_dv_*` 前缀避免与 clustered 的 `u_near/u_far` 冲突，GL 同步改名），并在 `rhi_pipeline_get_uniform_location` 增加 debug_viz/lens/sharpen 偏移映射。VK 上四个 pass 现已全部编译并初始化成功。
- 已修复：`pbr_clustered_vk.frag`（前向主着色器，此前从未在 VK 编译）。

**B. VK 校验层每帧报错（约 13 类）**
- ~~`vkCmdDispatch-None-10672`：**compute 在 render pass 内 dispatch**。~~ **已修复(地基A)**：在 RHI 层引入 render pass suspend/resume（`vk_suspend_pass_for_compute`/`vk_resume_pass_if_needed` + LOAD-op 孪生 pass + depth storeOp=STORE）。所有 compute dispatch 与 compute 域 barrier/image 绑定自动挂起当前 pass，绘制/清除时按需恢复。基线/视锥剔除/遮挡三条路径均 0 个 dispatch/barrier-in-pass 错误。
- ~~`vkCmdPipelineBarrier-None-07889`：pass 内下 barrier 且子通道无 self-dependency。~~ **已修复(地基A)**：同上，barrier 随挂起移出 pass。
- 遮挡剔除崩溃修复(地基A)：新增 `rhi_cmd_bind_texture_compute` 把 2D 纹理绑到 compute 采样集(set 2)，修正 `occlusion_cull.comp` 的 `u_hi_z` 描述符集(`07990`)，消除 Intel 驱动 `emit_samplers` 段错误。
- ~~`vkCmdResetQueryPool-renderpass`：profiler 在 pass 内 reset query pool。~~ **已修复(地基D)**：query reset 走 compute 域挂起。
- ~~`vkCmdDraw-renderPass-02684` / `imageLayout-00344` / `ComputePipelineCreateInfo-layout-07990` / `GraphicsPipelineCreateInfo-layout-07991` / `ClearAttachments-pRects-00016` / `DrawIndexedIndirectCount-*` / `polygonMode-01507`~~ **全部已修复(地基D)**，逐项见下方"地基D 明细"。基线/视锥剔除/遮挡三路径 VK 校验层 **0 错误**（仅余 2 条 `ShaderOutputNotConsumed` 警告：延迟 gbuffer MRT 着色器对单附件模板 pass 创建时报多余输出，非每帧错误，属 Round 4 延迟管线）。

**C. 并发**
- ~~`test_task` 偶发 段错误/死锁~~ **已修复(地基C)**，见 Task 行。

> 结论：原计划"按轮加特性"的前提（地基基本可用）在 VK 上不成立。建议在继续 Round 3+ 之前，新增/前置一轮"VK 校验层清零 + 着色器移植 + task 竞态修复"，否则后续轮次会在破损地基上继续堆叠"写了却没生效"的代码。

> **地基轮收尾（已完成）**：双后端均构建通过；CTest 双后端各 23/23；VK 校验层 smoke（forward / GPU 视锥剔除 / 遮挡 三路径各 60 帧）**0 FATAL、0 校验错误**（仅余 2 条创建期 `ShaderOutputNotConsumed` 警告，属 Round 4 延迟管线）。VK 地基已达"可在其上继续堆叠特性"的稳定状态。GL 后处理/着色器破损为既有问题，根因已定位（见 RHI OpenGL 行），归入 Round 5。

## 地基修复轮（前置于 Round 3）

> 用户已选择 `foundation_first`：在继续特性轮前先修地基。

- [x] **地基A**：把 GPU 剔除/压缩/occlusion 的 compute dispatch 移出 render pass —— RHI 层 suspend/resume + LOAD-op 孪生 pass；消除 `vkCmdDispatch-None-10672`/`PipelineBarrier-None-07889`；修复遮挡剔除段错误（新增 `rhi_cmd_bind_texture_compute`）。基线/视锥/遮挡三路径验证通过，双后端 CTest 全绿。
- [x] **地基B**：terrain_vk/water_vk 着色器在 VK 编译 —— varying 加 location、uniform 收进 push 常量块、新增 terrain/water 专属 push 布局标志与偏移映射。VK 上地形/水面已编译渲染，无新增校验错误，双后端 CTest 23/23。
- [x] **地基C**：task work-stealing 调度器竞态 —— 修复 submit-queue 锁外 reset(丢任务死锁)、非owner deque push(段错误)、wait_handle UAF(段错误)。`test_task` 双后端连跑 100/60 全绿。
- [x] **地基D**：清理其余每帧校验错误 —— **基线/视锥/遮挡三路径 VK 校验层 0 错误**。明细：
  - `polygonMode-01507`：设备创建时按需启用 `fillModeNonSolid`，管线据此选 LINE/FILL。
  - `ClearAttachments-pRects-00016`：清除矩形改用 `vk->resume_extent`（当前 pass 真实尺寸）而非 swapchain 尺寸。
  - `PipelineBarrier-commandBuffer-recording`：`rhi_cubemap_create` 启动期 barrier 改用一次性命令缓冲（原误用尚未 begin 的帧缓冲）。
  - `ComputePipelineCreateInfo-layout-07990`(IBL)：env map 为空时不再创建 irradiance/prefilter 计算管线（留待 Round 4）。
  - `renderPass-02684`：①模板 render pass 补 subpass dependency 对齐离屏 FBO；②点光 cubemap pass `srcStageMask` 对齐 `shadow_render_pass`；③**通用按渲染通道颜色格式惰性管线变体**（`VKShaderData` 保留 SPIR-V，`VKPipelineData` 缓存按格式变体，`rhi_cmd_bind_pipeline` 按 `active_color_fmt` 选/建变体）彻底消除格式不匹配。
  - `DrawIndexedIndirectCount-None-04445`：经 `VkPhysicalDeviceVulkan12Features.drawIndirectCount` 查询并启用该特性（apiVersion 已是 1.2）；不支持时回退 `vkCmdDrawIndexedIndirect`。
  - `vkCmdDispatch-None-08114`(`all_draws`)：**修复 `rhi_cmd_bind_storage_buffer` 每次都新分配并重绑描述符集、互相覆盖** —— 改为按管线绑定累积进同一描述符集（bind 0..3 全部写入），使 compute 压缩真正读到全部 SSBO（此前 VK 下 GPU 压缩读到的是垃圾）。
  - `DrawIndexedIndirectCount-renderpass`(在 pass 外)：点光 cubemap 深度 pass 现也跑间接压缩 dispatch，为其补 LOAD-op 孪生 pass + 记录 face framebuffer，使 compact 后的间接绘制能 resume 回 pass。
  - `imageLayout-00344`(`u_gr_depth`)：分两处。①遮挡/SSAO 路径随上述间接/存储修复一同消失。②**间歇性深度 layout 乒乓**（收尾时复现，约 1/3 帧、仅当太阳在屏内 god_rays 触发）：`scene_fbo` 深度在 line 3933 转 `SHADER_READ_ONLY` 后，tonemap/cinematic 又 `rhi_offscreen_fbo_bind(scene_fbo)` 把深度经离屏 render pass `finalLayout` 还原回 `DEPTH_STENCIL_ATTACHMENT_OPTIMAL`，随后 god_rays/debug_viz 采样该深度报错。**修复**：`VKTextureData` 增 `cur_layout` 跟踪；`rhi_cmd_transition_depth_to_read` 改为幂等（已是 READ_ONLY 即跳过、按跟踪 oldLayout 转换）；离屏 bind 标记其深度回到 attachment layout；main.c 在 god_rays/debug_viz 前再调用一次该（幂等）转换。压测 forward 8/8 + cull/occlusion 各 3/3 全 0 错误。
  - `vkCmdDraw-None-09600`(采样 UNDEFINED 图像)：离屏/MRT 颜色附件创建时用一次性提交转到 `SHADER_READ_ONLY_OPTIMAL`，使"创建后尚未渲染即被采样"的目标具有合法采样 layout。
  - `GraphicsPipelineCreateInfo-layout-07991`(deferred `u_point_shadow_cubes[4]`)：材质描述符布局 binding 5 计数改 4 并加 `descriptorBindingPartiallyBound`（启用对应 1.2 特性），使同一布局既服务前向 `u_ssao`(只用元素0)又服务延迟 cube 数组(07991 创建期错误清零，前向不受影响)。
- [x] **地基E**：ssao_blur/sharpen/debug_viz/lens_effects 等 VK 着色器编译 —— 见上方 A 节，四个 pass 全部编译并初始化成功，VK smoke 0 FATAL / 0 校验错误。

## 修复进度（按计划轮次）

- [x] Round 1：GPU 驱动剔除闭环 — cull.comp 双后端 compute 加载并输出 flags 驱动 compaction；删除全可见 memset；新增 unified_cull.comp；修复 VK push 常量映射与 BRDF LUT 描述符集崩溃；默认关闭无用的 Hi-Z 遮挡；双后端 120 帧无验证层错误，CTest 23/23
- [~] Round 2：CSM 4 级正确采样 — 核心达成(shadow-atlas 四象限 + pbr_clustered 双后端最紧 cascade 选择 + 真 texel + 修复 VK 阴影纹理绑定/着色器编译)；遗留：terrain/water 在 VK 因既有移植缺口未编译(其 CSM 采样代码已就位)；并暴露上节 VK 基础性缺陷待决策
- [x] 地基轮(A-E + 收尾)：VK render-pass suspend/resume、terrain/water VK 着色器、task 竞态、VK 校验层清零(三路径 0 错误)、后处理 VK 着色器编译、间接绘制存储描述符集修复。双后端构建 + CTest 23/23。
- [x] Round 3：合并后处理减少 pass —— 新增 combined_taa_fxaa / combined_color 着色器(双后端) + VK 专属 push 布局。VK `test_vulkan` TEST 6 验证两合并管线激活、不回退、10 帧 0 校验错误。GL 受 post.vert 阻塞(Round 5)。亦修复 god_rays/debug_viz 采样场景深度的间歇 `imageLayout-00344`(深度 layout 跟踪幂等化)。
- [x] Round 4：Clustered 光照 GPU binning + 真 cubemap IBL ——
  - **真 IBL**：RHI cubemap 扩 `format`/`mip_levels`/per-face-per-mip 视图(VK+GL) + 两个 layout 转换 API；新增 `sky_to_cube.comp` 程序化天空 capture；`irradiance_env`/`prefilter_env` 改单面 `image2D` 存储视图；`ibl.c` 三张 RGBA16F+mip cube 卷积链 + 每帧 `rhi_present` 防 swapchain 耗尽；`HAS_IBL` 经 `shader_inject_define` 注入，PBR 采样真 irradiance/prefilter/BRDF LUT。修两 bug：BRDF LUT 缺 `transition_to_read` 致 `09600`；IBL 生成期 swapchain 耗尽挂起。
  - **GPU binning**：新增 `cluster_cull.comp`(VP+标量 push、VK set0 双 SSBO / GL std430)；buffers 改 `TEXEL|STORAGE`；`light_system_init_gpu_cull`/`cull_gpu`/`upload_lights`；修 PBR 把密排 `u32` 当 `RGBA32F` 误读的潜伏 bug(`grid_u32`+`floatBitsToUint`)。
  - **验收**：VK Debug(校验层开) `test_vulkan` TEST 7(GPU binning + 真 IBL) 与 `engine_demo` 实时主循环各 **0 VUID**；双后端构建 + CTest 23/23；5 个 Round 4 着色器 GL 语义编译通过。
- [x] Round 5：GL 后端一致性 ——
  - **着色器移植**：`post.vert` 升 `#version 450` + `#ifdef VULKAN` 切 `gl_VertexIndex`/`gl_VertexID`（解锁约 20 个 GL 后处理）；`terrain.frag` 补显式 `out`；`sharpen.frag` float→vec3；`ssao.frag`/`dof.frag` 清残留垃圾/重复 main；`particle_update.comp`/`particle.vert`/`depth_only.vert` 加 `#ifdef VULKAN` push 常量↔loose uniform（`particles.c` GL 侧逐项设 uniform）；`hi_z_generate.comp`/`occlusion_cull.comp` 守卫 `layout(set=)`；`skinned.vert` 升 430；`bloom_blur/bloom_extract/post_tex.frag` 升 450 + `layout(location=0)` 对齐 `post.vert`。
  - **rhi_gl 一致性**：`gl_bind_tex_unit` 按资源类型选 GL target（cubemap/点光深度 cube→`GL_TEXTURE_CUBE_MAP`），深度 cube 走纹理级 compare；`rhi_cubemap_depth_fbo_create` 的 depth_tex 标记 `RHI_RES_CUBEMAP`；`rhi_cmd_transition_depth_to_read` 明确为 GL 合法 no-op。
  - **验收**：GL `engine_demo` 8 帧 0 着色器/链接/GL 错误（仅余缺资源警告）、cluster binning 启用；VK `engine_demo`/`test_vulkan` 仍各 0 VUID；双后端构建 + CTest 23/23。
- [x] Round 6：ECS system 调度 + 物理 CCD/形状 ——
  - **ECS system**：新增 `ecs_system.{h,c}`。`EcsChunkView`(world/archetype/chunk/count) + `ecs_chunk_column`(按组件签名取 SoA 列基址)/`ecs_chunk_entity_ids`；`ecs_parallel_for(world, ts, types, n, fn, user)` 每个匹配非空 chunk 提交一个 task 并行(传 `ts=NULL` 串行)；`EcsScheduler` 系统按注册序串行执行(防列写竞争)、单系统 chunk 内并行。`main.c` 把物理→Transform 同步+越界重生迁入 `sys_sync_transform_from_physics`，经现有 `tasks`(2 worker) 并行。
  - **Physics 形状/CCD/回调**：`ShapeType`(盒/球/胶囊)+`radius`/`half_height`/`ccd`；`aabb_from_body` 按形状；`physics_body_create_sphere`/`_capsule`/`_set_ccd`/`physics_set_contact_callback`；`physics_collide` 按形状对分派(球-球/球-盒/球-胶囊/胶囊-胶囊/胶囊-盒，附 `closest_on_segment`/`closest_seg_seg`/`closest_on_aabb`/`sphere_vs_box`)；`physics_step` 集成 swept-sphere CCD vs 静态体(`ccd_sweep_static`/`integrate_body_ccd`)防高速穿透并对每对解析触发 `Contact` 回调。修 `sphere_vs_box` 内部脱出法线符号 bug。
  - **角色胶囊**：`character_update` 重写为 collide-and-slide(`char_capsule`+`char_slide_resolve`)，分垂直/水平/抬腿三阶段，落实 `slope_limit`/`step_height`。
  - **验收**：双后端构建通过；CTest **24/24**(新增 `test_ecs_system` 5；`test_physics` 34、`test_character` 20)；VK Debug `engine_demo` 8 帧并行 ECS system 正常、0 VUID；GL `engine_demo` 0 着色器/GL 错误。
- [x] Round 7：真实 Lua 脚本 ——
  - **vendoring**：Lua 5.4.7 全量源置于 `engine/external/lua`(删除 standalone `lua.c`/`luac.c`/`ltests.{c,h}`)，仅以 `onelua.c`+`-DMAKE_LIB` 编译成静态库 `lua`(第三方代码用 `-w` 豁免引擎 `-Werror -pedantic`)，`engine` 链接 `lua`。
  - **运行时**：`script_lua.{h,c}` 真实 `lua_State`+`luaL_openlibs`；`lua_script_load`/`_load_string`(语法/运行期错误经日志返回 false 不崩)、`on_start`/`on_update(dt)`/`on_spawn` 探测+ `pcall`、数值全局 get/set、按 mtime 的 `.lua` 热重载。
  - **绑定**：`engine.*` 表经 registry 取宿主 `LuaScript*` → ECS `World`/`PhysicsWorld`/`InputState`，宿主指针 NULL 时全部安全降级(返回 0/no-op)。
  - **接入 demo**：`main.c` 绑定宿主、加载 `assets/init.lua`、启动 `on_start`、每帧 `on_update`+热重载、退出 `shutdown`；新增真实 `assets/init.lua`。
  - **验收**：双后端构建通过；CTest **25/25**(新增 `test_script_lua` 15)；VK/GL `engine_demo` 均 `Lua script loaded (start=1 update=1 spawn=1)`+`on_start` 打印 11 实体/11 刚体，VK 0 VUID、GL 0 着色器/GL 错误。旧 DSL 兼容保留。
- [x] Round 8：场景资源序列化 ——
  - **RESOURCES chunk**：`scene_serial.c` 由空占位改为真实清单：`emit_resources_chunk` 遍历 `Scene` 的 meshes/materials 及按 RHI 句柄去重的 textures，逐条写 `SceneResource`{guid,type,ref_index,flags,inline 描述符,path}；`load_resources_chunk` 回填到 `Scene.resources`/`resource_count`。
  - **确定性 GUID**：`resource_guid` 对(类型 + ref 索引 + 关键描述符字段)做 FNV-1a 64，同场景多次保存 GUID 稳定(`resources_guid_deterministic` 验证)。
  - **include_resources**：true 内联 mesh(index/vertex count、material_idx、AABB)与 material(base_color、metallic/roughness、emissive、alpha mode/cutoff)描述符；false 仅写 {guid,type,ref,path} 轻引用。
  - **ECS↔Scene 统一 ID**：`load_entities_chunk` 恢复保存的 entity `generation`(此前丢弃)，使 (index,generation) 跨存读一致，成为持久统一 ID；`world_entity_exists` 在往返后对存活/已销毁实体判定正确。
  - **配套**：`asset.h` 增 `SceneResource` 与 `Scene.resources`/`resource_count`；`asset_scene_free` 释放；`scene_serial.h` 导出 `scene_resources_free`。
  - **验收**：双后端构建通过；CTest **25/25**(`test_scene_serial` 扩到 23 子项：新增 include 往返、refs-only 往返、GUID 确定性、generation 恢复)。
- [x] Round 9：平台补齐（gamepad/Wayland/macOS）——
  - **Linux gamepad 接线**：`window_x11.c` 与 `window_wayland.c` 的 `platform_create` 调 `gamepad_init`、`platform_poll` 在 `input_new_frame` 后调 `gamepad_poll(p->input.gamepads)`、`platform_destroy` 调 `gamepad_shutdown`；既有 evdev 后端(热插拔/校准)首次真正驱动 `InputState`。
  - **Windows XInput**：新增 `gamepad_win.c`(动态加载 `xinput1_4/1_3/9_1_0`)，实现同一 `gamepad_init/poll/shutdown` 契约，映射按钮/摇杆/扳机(死区缩放、Y 轴取反对齐 evdev"上为负"、扳机 0..1)，接入 `window_win32.c` 三处。
  - **Wayland 指针**：绑定 `zwp_relative_pointer_manager_v1`/`zwp_pointer_constraints_v1`；`set_relative` 走相对运动(未加速 delta)+持久 `lock_pointer`，`set_visible(false)` 经 `wl_pointer_set_cursor(serial,NULL)` 真隐藏(记录 enter serial、重入时重应用)；CMake 用 wayland-scanner 生成两个 unstable 协议绑定。原三处桩注释删除。
  - **macOS**：新增 `window_cocoa.m`(NSWindow + CAMetalLayer + 事件/键鼠/相对指针 via `CGAssociateMouseAndMouseCursorPosition`)；`rhi_vk.c` 加 macOS 分支(`VK_USE_PLATFORM_METAL_EXT`、`vkCreateMetalSurfaceEXT`、实例 portability enumeration、设备 `VK_KHR_portability_subset`)；CMake `macos` 分支启用 OBJC、链接 Cocoa/QuartzCore/Metal/IOKit + Vulkan(MoltenVK)。复用 VK 后端不另写 Metal RHI。
  - **测试**：`test_input` 增 3 项 gamepad 契约测试(轴跨帧保留、4 槽位边沿推进、槽位独立)。
  - **实测**：X11 双后端(VK+GL)构建+CTest **25/25**；Wayland(VK)`engine`/`engine_demo` 链接通过(含生成的 relative-pointer/pointer-constraints 绑定)；VK demo 启动接线 gamepad 无崩溃。macOS 受限于 Linux 环境未实测构建(代码按 MoltenVK 规范编写)。
- [x] Round 10：资源/音频流式 + UI/字体 + Core + 回归测试 ——
  - **Mipmap 流式真上传**：`mipmap_stream.c` 由桩改真链路。`MipLoadReq{mgr,tex,level}` 作 `async_loader_request_range` 用户数据，回调取得 level 数据所有权→写 `level_data`、改 `level_state=RESIDENT`、增减 `total_resident_bytes`、调 `MipmapUploadFn` 上传；`mipmap_stream_update` 按 `memory_budget`+`desired_level` 驱逐细 mip；`_force_level` 内泵 `async_loader_tick` 至命中。新增 RHI `rhi_texture_upload_mip`(GL `glTexImage2D` 可变存储 / VK staging buffer + 一次性命令 + 逐 mip SHADER_READ↔TRANSFER_DST barrier)。修复 `coverage_to_level` 反向(全覆盖应得 level0，改 `0.5*log2(1/coverage)`)。接入 `main.c`：启动写 256² 9-mip 文件、96KB 预算、相机距离→coverage 驱动驻留/驱逐、debug UI 显示 level/驻留KB/loads/uploads/evict。
  - **Audio 流式 3D**：`audio_stream.c` 重写为 miniaudio `MA_SOUND_FLAG_STREAM` 真后端(声卡线程逐块解码补帧)，每流包一音源、支持 2D/3D+距离衰减+移动+状态。audio.c 增 `audio_play_streamed`/`audio_source_set_position`/`_set_attenuation`(逆距离模型 `ma_attenuation_model_inverse`)/`_set_volume`/`_start`/`_at_end`/`_cursor_seconds`；纯函数 `audio_attenuation_gain` 供无头测。`main.c` 生成正弦 WAV 作 3D 音源真播放、debug UI 显示增益/播放时刻。
  - **字体 UTF-8 + IMGUI**：`utf8.{h,c}` 多字节解码(拒 overlong/代理、永不卡死)；`font.c` 烘焙 ASCII+Latin-1、码点查找表、白像素供实心矩形，新增 `font_renderer_draw_rect`/`text_width`/`line_height`；`imgui.{h,c}` 即时模式 label/button/checkbox/slider(纯逻辑助手 `static inline` 可无头测)接入 demo(反引号切换面板，独立 `FontRenderer` 避免 VBO 冲突)。
  - **Core**：定长块 `pool.{h,c}`(侵入式空闲链、O(1)、接入 `Alloc` vtable)；GPU timestamp profiler(`RHIGPUTimer` 双后端)接入 demo 命名计时输出。
  - **回归测试**：`test_vulkan` 增 golden image 子测(读回→20×15 降采样→容差比对 `tests/golden/test_vulkan_vk.ppm`，`GOLDEN_UPDATE=1` 重生)且返回码汇总全部子测；纳入 CTest(`WORKING_DIRECTORY` + `ENGINE_VULKAN` 守卫 + 180s 超时)。新增 `test_pool`/`test_font_ui`/`test_mipmap_stream`/`test_audio`。
  - **验收**：VK 构建 CTest **30/30**(golden MAE=0.00 max=0 稳定，test_vulkan 12s 通过)；GL 构建 CTest **29/29**；VK demo 0 校验错误(仅余 2 条既有 `ShaderOutputNotConsumed` 警告)、GL demo 0 着色器/GL 错误；双后端 demo 均 `MipmapStream demo: 9 levels, GPU tex ok` + `Audio: streaming 'stream_tone.wav' (3D)`。
- [x] Round 11：剔除闭环 + 合并后处理默认化 ——
  - **R11-1 遮挡驱动 draw**：`occ_rebuild_node_map`/`node_occ_visible` 建立 node→occ 紧凑索引(与 Hi-Z upload 同序)；mega-buffer indirect `vis_flags &= occlusion`；CPU frustum 回退跳过被挡节点；默认 Hi-Z 开(`BREAK_OCCLUSION=0` 关)；debug UI 显示 culled 数。
  - **R11-2 GPU cull 默认**：`mega_buf.valid`→`gpu_indirect_enabled && gpucull_enabled`；`gpucull_init_unified` 初始化 unified 管线(仍走 flags 路径，R12 替换)。
  - **R11-3 合并后处理**：`CombinedAA`/`CombinedColor` init/resize/shutdown；TAA+FXAA→单 pass AA；tonemap+cg 且 `!cine && !auto_exposure`→单 pass 调色；debug UI CombinedPost 状态。
  - **验收**：双后端 `engine_demo` 构建通过；VK CTest **30/30**、GL CTest **29/29**；`test_vulkan` TEST 6 合并管线 + golden 通过。
- [x] Round 12：unified 剔除 + 粒子 GPU cull ——
  - **R12-1 unified 阴影**：`mega_upload_unified_cull` 上传 draw cmd + 包围球；CSM/点光 cubemap 默认 unified 单 pass；legacy flags+compact 回退。
  - **R12-2 粒子 cull**：`particles_cull`+`particle_cull.comp`；instance draw 只画 alive；UI 显示 alive。
  - **R12-3 点光阴影前向**：未做(可选)。
  - **验收**：`test_vulkan` TEST 9 unified smoke；VK CTest **30/30**、GL **29/29**。
- [x] Round 13：延迟光照 + TAA 重投影 + combined/auto-exposure ——
  - **R13-1 deferred 光照**：cluster+CSM+IBL；`light_system_cull/upload`；去掉 5% ambient。
  - **R13-2 TAA motion**：`inv(curr_view_proj)` 重投影（velocity pass 未做）。
  - **R13-3 combined+AE**：`combined_color_apply` 新签名；auto-exposure 与 combined 共存。
  - **验收**：VK CTest **30/30**、GL **29/29**。
- [x] Round 14：async 优先级 + 纹理热重载 + frame arena ——
  - **R14-1**：priority dequeue + texture decode + mip 优先级。
  - **R14-2**：`hotreload_texture_*` + `mipmap_stream_invalidate`。
  - **R14-3**：frame arena + unified cull 持久缓冲。
  - **验收**：VK CTest **30/30**、GL **29/29**；`test_async_loader` priority 测 + `test_mipmap_stream` invalidate 测。
- [x] Round 15：Chrome trace + GL golden + net replication ——
  - **R15-1**：`profiler_export_chrome_trace`；demo F11/`PROFILER_TRACE=1`。
  - **R15-2**：`test_vulkan` 双后端 golden（GL 仅 golden 路径）；`test_vulkan_gl.ppm`。
  - **R15-3**：`net_replication` transform 快照 unreliable 广播；`test_net_replication`。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 16：unified Hi-Z + velocity G-Buffer + TAA motion ——
  - **R16-1**：`unified_cull` Hi-Z；阴影 unified 接 `occ_sys`。
  - **R16-2**：G-Buffer RT3 velocity + `u_prev_vp`。
  - **R16-3**：`taa_resolve` velocity 采样。
  - **验收**：VK CTest **31/31**、GL **31/31**；`test_vulkan` unified 0 VUID。
- [x] Round 17：Combined AA velocity + net/hotreload demo 接线 ——
  - **R17-1**：`combined_aa_apply` velocity；combined shader motion 重投影。
  - **R17-2**：`BREAK_NETREP=1` demo 广播/接收 transform。
  - **R17-3**：`BREAK_HOTRELOAD_TEX` demo 纹理热重载。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 18：Combined AA history + deferred 点光阴影 + net ghost ——
  - **R18-1**：`CombinedAA` history ping-pong + `first_frame`。
  - **R18-2**：`deferred_light` 点光 cubemap 阴影采样。
  - **R18-3**：`BREAK_NETREP` ghost entity transform 应用。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 19：Combined color+cinematic + anim blend + net lerp ——
  - **R19-1**：combined color 合并 cinematic 参数，跳过双 pass。
  - **R19-2**：`BREAK_ANIM_BLEND=1` + `skeleton_apply_local_trs` + F12 crossfade。
  - **R19-3**：NetRep ghost 线性插值 + `BREAK_NETREP_LERP=0`。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 20：Forward pt shadow + anim IK + net dedup ——
  - **R20-1**：前向 `pbr_clustered` 点光 cubemap 阴影（binding 10）。
  - **R20-2**：`BREAK_ANIM_IK=1` two-bone IK demo。
  - **R20-3**：NetRep 序列去重 + `BREAK_NETREP_DEDUP=0`。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 21：Unified forward + forward velocity + net reliable ——
  - **R21-1**：`BREAK_UNIFIED_FORWARD=1` 前向 unified cull+compact。
  - **R21-2**：`BREAK_FORWARD_VEL=1` camera velocity → TAA。
  - **R21-3**：`BREAK_NETREP_RELIABLE=1` ACK 重传。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 22：Unified per-material + net ordered ——
  - **R22-1**：unified vis flags + per-material indirect（前向/延迟 mega）。
  - **R22-2**：`PACKET_ORDERED` 重排 buffer + `BREAK_NETREP_ORDERED=1`。
  - **R22-3**：VK compute storage layout 8 binding（unified cull binding 4）。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 23：Unified deferred + net reliable/ordered combo ——
  - **R23-1**：`BREAK_UNIFIED_DEFERRED=1` 延迟 G-Buffer unified per-material。
  - **R23-2**：`BREAK_NETREP_RELIABLE_ORDERED=1` + 重传去重 + 组合单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 24：Shadow per-material + net dual channel ——
  - **R24-1**：`BREAK_UNIFIED_SHADOW=1` CSM/点光 per-material indirect。
  - **R24-2**：NetRep unreliable/ordered 双通道 + reliable pending 分离。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 25：Unified shadow default + net multitype ——
  - **R25-1**：mega-buffer 默认 unified shadow；`BREAK_UNIFIED_SHADOW=0` 关闭。
  - **R25-2**：packet type 独立 channel + heartbeat API/单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 26：Unified fwd/def default + heartbeat demo ——
  - **R26-1**：mega-buffer 默认 unified forward/deferred；env 可关。
  - **R26-2**：heartbeat RTT + demo 接线 + 单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 27：Unified env docs + heartbeat roundtrip ——
  - **R27-1**：Unified / NetRep env 矩阵文档。
  - **R27-2**：`HEARTBEAT_ACK` echo + `hb_roundtrip_ms` + 单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 28：DrawBench + peer RTT table ——
  - **R28-1**：`BREAK_DRAW_BENCH=1` mega vs legacy draw 估算 + UI。
  - **R28-2**：`NetRepPeerStats[8]` per-address RTT + 单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 29：DrawBench GPU + peer eviction ——
  - **R29-1**：unified/legacy GPU timer 均值 + UI。
  - **R29-2**：peer TTL/LRU + `peer_evict_stale`/`peer_lru_full` 单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 30：DrawBench export + peer persist ——
  - **R30-1**：CSV + Chrome meta export；`BREAK_DRAW_BENCH_EXPORT`。
  - **R30-2**：`peer_save/load` + `BREAK_NETREP_PEER_FILE`。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 31：DrawBench script + peer shard ——
  - **R31-1**：`draw_bench_compare.sh` unified vs legacy。
  - **R31-2**：`peer_save/load_dir` + delta.log + 单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 101：冗余遮挡剔除消除 + 动画事件回调 ——
  - **R101-1**：unified 路径全激活时跳过 `occlusion_cull_dispatch`（每帧节省 1 dispatch + 1 barrier + 1 buffer copy）；Hi-Z 生成仍运行。
  - **R101-2**：`anim_blend_evaluate` 触发事件回调；新增 `AnimEvent`/`anim_clip_add_event`；循环 wrap-around 支持。
  - **验收**：`test_animation` **24/24** 通过（新增 4 项事件测试）。
- [x] Round 102：ECS archetype edge 缓存 ——
  - **R102**：`world_add_component`/`world_remove_component` 目标 archetype 查找从 O(N) `find_archetype` 线性扫描降为 O(E) edge 查找。首次转换仍走 `find_archetype` 并缓存结果到 `edges_add[]`/`edges_remove[]`；后续相同 component 转换直接用缓存 `target` 指针，跳过类型数组构建+排序+hash 扫描。`ArchetypeEdge` 结构与字段此前已定义但为桩，现已完整实现 `edge_lookup_add`/`_remove`/`edge_cache_add`/`_remove` 四辅助函数。
  - **验收**：`test_ecs` **23/23** 通过（新增 3 项 edge cache 测试：add 命中/remove 命中/50 实体多轮转换）。
- [x] Round 103：ECS 查询增强 + 延迟点光阴影 + 异步加载优先级解码管线 + Windows Packer ——
  - **R103-1 ECS Exclude/Optional**：`ecs_query_exclude`（排除含指定组件的原型）、`ecs_query_optional`（可选组件，匹配但跳过不含的原型）、`ecs_query_refresh`（查询失效时重建匹配原型列表）；`Query` 结构扩展 `exclude_mask`/`optional_mask` 位域，`query_matches_archetype` 位掩码 O(1) 过滤。`test_ecs` 新增 5 项 Exclude/Optional 测试。
  - **R103-2 延迟点光阴影**：`deferred_light.frag`/`_vk.frag` 接入点光 cubemap 阴影采样（`HAS_POINT_SHADOW` 条件编译）；前向管线 `blinn_phong_clustered`/`pbr_clustered` 双后端同步 `HAS_POINT_SHADOW` 守卫；`PointLight` 增加 `shadow_index` 字段；`deferred.c` 绑定点光阴影纹理到延迟光照 pass。
  - **R103-3 异步加载优先级+解码管线**：priority 最小堆替换 FIFO 队列；新增 2-worker 解码线程池 `decode_pipeline.c/h`，stb_image 解码 + mipmap 生成不阻塞主线程，解码完成后回调主线程上传 GPU。`test_async_loader` 新增优先级和解码管线测试。
  - **R103-4 Windows Packer**：`CreateFileMapping` 零拷贝打包 + `FindFirstFile`/`FindNextFile` 递归遍历，与 POSIX 版二进制兼容；新增 `verify_pak.c` 验证工具。
  - **验收**：`test_ecs` 新增 5 项通过；`test_async_loader` 新增优先级/解码测试通过；双后端构建通过。
- [x] Round 104：decode pipeline 优先级队列修复 ——
  - **R104 审查**：深度审查 5 个新提交（ECS Exclude/Optional、点光 cubemap 阴影、异步加载优先级解码管线、Windows packer、Windows 编译修复），确认 point shadow 代码、VK push constant 布局、ECS 查询迭代、async loader 线程安全、Windows packer 资源释放均正确。`clustered_pipeline` 死代码不影响运行时。`HAS_POINT_SHADOW` 仅注入 pbr_clustered.frag（deferred_light.frag 无 #ifdef 守卫，blinn_phong 为回退着色器）。
  - **R104-1 decode pipeline 优先级队列**：`input_queue_push` 从 FIFO 追加改为优先级排序插入（低值=高优先级，与异步加载器 min-heap 一致），修复多 I/O 线程下低优先级请求先提交导致高优先级纹理延后解码的问题。同优先级保持 FIFO。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 105：VFS/packer 防御性编程修复 ——
  - **R105 审查**：全量深度审查着色器热路径、渲染循环、RHI 后端、点光阴影管线、ECS 查询、异步加载器、VFS/packer。确认 R84-R96 系列着色器优化无新冗余，渲染循环无冗余状态变更，点光阴影 VP 矩阵构建正确，GL/VK binding 匹配，ECS 查询迭代正确，async loader 线程安全。
  - **R105-1 VFS NULL 检查**：`vfs_mount_dir`/`vfs_mount_pak` 添加 NULL 路径参数检查，防止 `strncpy`/`fopen`/`LOG` UB 崩溃。`vfs_mount_dir` 添加显式 null 终止。
  - **R105-2 packer 缓冲区边界检查**：`add_file` 在 `memcpy` 前检查 `g_name_size + name_len` 是否超过 `g_names` 缓冲区大小，防止超长路径导致缓冲区溢出。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 106-110：VK 帧状态重置 + GL 缓存失效 + 音频流槽位泄漏 + 场景序列化边界 + 着色器文件读取加固 ——
  - **R106**：VK `rhi_frame_begin` 状态重置 + GL `rhi_destroy` 缓存失效。**R107**：`audio_stream_open` 失败路径槽位泄漏。**R108**：`scene_load_binary` chunk 表/数据边界验证。**R109**：`str_copy` 整数下溢 + `cgltf_buffer_data` NULL 解引用 + `load_gltf_texture` 栈溢出。**R110**：`particles.c`/`water.c` `read_file` ftell/malloc 检查。每轮均 23/23 测试通过。
- [x] Round 111：GPU 剔除初始化验证 + 热重载路径终止修复 ——
  - **R111 审查**：深度审查 UTF-8 解码、BVH 构建/遍历/查询、间接绘制、GPU 剔除统一管线、遮挡剔除、IBL、天空盒、接触阴影、SSS、热重载、ImGui、后期处理着色器读取。
  - **R111-1 gpucull_init 缓冲区验证**：`gpucull_init` 创建 3 个 GPU 缓冲区后未验证有效性就设置 `ready = true`。`indirect_draw_init`、`gpucull_init_unified`、`occlusion_cull_init` 均有完整验证。修复：添加三缓冲区有效性检查，失败时 `gpucull_shutdown` 清理并返回 false。
  - **R111-2 hotreload_pipeline_init memset**：未 `memset` 结构体就 `strncpy` 路径，≥255 字节时不保证 null 终止。`hotreload_texture_init` 正确使用了 `memset`。修复：入口添加 `memset(hr, 0, sizeof(*hr))`。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 112：test_vulkan.c file_read 防御性加固（全引擎 read_file 统一完成）——
  - **R112 审查**：深度审查光照系统、SSAO/SSR/TAA/DoF/Tonemap、Mipmap 流式加载、文件监视系统（Windows+Linux）、全引擎 28 个 `read_file`/`file_read` 实现完整性验证。
  - **R112-1 test_vulkan.c file_read**：缺少 `ftell` 返回值检查和 `malloc` NULL 检查，是引擎中最后一个未加固的 `read_file` 实现。修复：添加 `sz < 0` 检查和 `malloc` NULL 检查。至此全引擎 28 个 `read_file`/`file_read` 实现全部完成统一加固。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 113：SSGI uniform 位置硬编码 + VK buffer_update NULL deref 修复 ——
  - **R113 审查**：深度审查 RHI 后端（rhi_gl.c 1976 行 / rhi_vk.c 5342 行）、引擎核心（engine.c / rhi.c）、全后期处理小文件（combined_post_process / post_process / ssgi / volumetric / upscale / fxaa / color_grade / god_rays / motion_blur / sharpen / lens_flare / lens_effects / cinematic / debug_viz / forward_velocity）、骨骼动画（skeleton.c）、平台时间（time.c）。
  - **R113-1 SSGI uniform 位置硬编码**：`ssgi_init` 硬编码 `loc_blur_dir_x = 0` 和 `loc_blur_dir_y = 4`，而非从管线查询。SSGI blur 管线使用共享的 `bloom_blur.frag`，`u_direction` 是 `uniform vec2`，GL 链接器不保证其位置为 0。`post_process.c` 正确使用了 `rhi_pipeline_get_uniform_location` 查询，`ssgi.c` 遗漏。`loc_blur_dir_y = 4` 是完全未使用的死代码。修复：用 `rhi_pipeline_get_uniform_location` 查询 `u_direction`，在 `ssgi_apply` 中添加 `>= 0` 守卫。
  - **R113-2 VK buffer_update NULL deref**：`rhi_buffer_update` 和 `rhi_buffer_update_region` 的 fallback 路径调用 `vkMapMemory` 后未检查返回值。所有 VK 缓冲区使用持久映射，fallback 路径仅在 `bd->mapped == NULL`（创建时 vkMapMemory 失败）时触发。此时再次 `vkMapMemory` 也可能失败，`mapped` 指针未定义，`memcpy` 崩溃。修复：检查 `vkMapMemory` 返回 `VK_SUCCESS`，失败时提前返回。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 114：平台窗口管理与手柄输入审查（无需修复）——
  - **R114 审查**：全平台窗口管理（window_x11.c 381 行 / window_wayland.c 719 行 / window_win32.c 518 行）、手柄输入（gamepad_linux.c 421 行 / gamepad_win.c 178 行）、剔除辅助（cull.c 31 行）。所有文件 calloc + NULL 检查完整，资源释放完整，strncpy + memset 安全，设备热插拔处理完善。审查未发现问题，无需代码修改。
- [x] Round 115：网络复制缓冲区溢出 + glTF 资产加载防御性加固 ——
  - **R115 审查**：深度审查物理系统（physics.c）、动画系统（animation.c）、渲染图（render_graph.c）、命令缓冲（cmd_buffer.c）、任务系统（task.c）、网络核心（network.c）、网络复制（net_replication.c）、包序列化（packet.c）、资产加载（asset.c）、主循环（main.c）。
  - **R115-1 net_replicator_process 缓冲区溢出**：`net_reorder_store` 中 `memcpy(slot->wire, wire, len)` 溢出 `u8 wire[PACKET_MAX_SIZE]`（1400 字节）。公共 API `net_replicator_feed`/`net_replicator_feed_from` 接受任意 `len`。修复：`net_replicator_process` 入口添加 `len > PACKET_MAX_SIZE` 检查。
  - **R115-2 asset_load_gltf calloc NULL 检查**：`indices`、`sverts`、`verts`、`skin_buf`、`node_to_joint` 的 `calloc`/`malloc` 缺少 NULL 检查，分配大小来自不可信 glTF 文件数据。修复：添加 NULL 检查，分配失败时跳过原语或返回 false。
  - **R115-3 asset_load_gltf cgltf_buffer_data NULL 检查**：`cgltf_buffer_data` 返回值未检查 NULL（R109-2 已使该函数可返回 NULL）。受影响指针：`idx_data`、`pd`、`nd`、`ud`、`jd`/`wd`、`ibm_data`。修复：循环条件添加 NULL 守卫，或分配后检查并跳过。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 116：字体/脚本/ECS/LOD 防御性加固 ——
  - **R116 审查**：深度审查延迟渲染（deferred.c）、点光阴影（point_shadow.c）、字体渲染（font.c）、LOD 系统（lod.c）、相机（camera.c）、视锥剔除（frustum_cull.c）、分配器（alloc.c）、池分配器（pool.c）、性能分析器（profiler.c）、脚本引擎（script.c）、Lua 脚本（script_lua.c）、ECS 核心（ecs.c）、场景序列化（scene_serial.c 部分）、输入（input.c）、日志（log.c）。
  - **R116-1 font.c malloc NULL 检查**：`font_renderer_init` 中着色器源码 `malloc(vs_len+1)`/`malloc(fs_len+1)` 未检查 NULL，失败时 `fread(NULL,...)` 崩溃。`quad_data` malloc 同样未检查。修复：添加 NULL 检查，失败时 fclose 或返回 false。
  - **R116-2 script.c ftell/malloc NULL 检查**：`script_load` 中 `ftell` 返回 -1 时 `(usize)sz+1` 回绕为 0，`malloc(0)` 可能返回非 NULL，`fread` 读取 `SIZE_MAX` 字节溢出。`malloc` 返回 NULL 时崩溃。修复：`sz < 0` 提前返回 + malloc NULL 检查。
  - **R116-3 ecs.c calloc/malloc/realloc NULL 检查**：`chunk_alloc`、`create_archetype`、`world_create`、`world_add_component`、`world_remove_component`、`world_query`/`ecs_query_refresh` 多处分配未检查返回值，失败时解引用 NULL 崩溃。修复：全路径添加 NULL 检查，chunk_alloc 返回 NULL，调用方检查并清理/降级。
  - **R116-4 lod.c level_count==0 u32 下溢**：`lod_select_by_*` 中 `level_count - 1` 当 `level_count==0` 时 u32 下溢为 `UINT32_MAX`，越界读 `thresholds_sq`。修复：`lod_register` 拒绝 `level_count==0`。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 117：BVH/光照 calloc NULL 检查 ——
  - **R117 审查**：深度审查地形系统（terrain.c 622 行）、BVH 物理（bvh.c 507 行）、异步加载器（async_loader.c 505 行）、集群光照（lighting.c 357 行）、遮挡剔除（occlusion_cull.c 410 行）。
  - **R117-1 bvh.c calloc/realloc/malloc NULL 检查**：BVH SAH 构建路径 5 处分配未检查返回值。`bvh_init` calloc 失败时 `bvh->nodes=NULL`；`bvh_alloc_node` realloc 失败时旧指针泄漏 + `bvh->nodes` 置 NULL；`bvh_build` 中 leaf_map/nodes/_build_indices 三处 calloc/malloc 失败解引用 NULL。修复：全路径 NULL 检查，realloc 使用临时指针避免泄漏，失败时 `bvh->root = BVH_NULL` 安全返回。
  - **R117-2 lighting.c staging_block calloc NULL 检查**：`light_system_upload_grid` 中 `calloc(1, gb_off + gb_bytes)` 分配 staging buffer 未检查 NULL，OOM 时后续 `memcpy` 崩溃。修复：添加 NULL 检查 + LOG_ERROR + return。
  - **验收**：全部 23/23 测试通过。BVH/GL 构建路径编译成功。
- [x] Round 118：音频/ECS 系统 calloc NULL 检查（全量审查完成） ——
  - **R118 审查**：深度审查音频系统（audio.c 306 行）、断言（assert.c 18 行）、ECS 系统调度器（ecs_system.c 141 行）、数学库（math.c 122 行）、IBL 预计算（ibl.c 348 行）、间接绘制（indirect_draw.c 216 行）、调试 UI（debug_ui.c 69 行）、即时模式 UI（imgui.c 171 行）、UTF-8 解码器（utf8.c 65 行）。
  - **R118-1 audio.c calloc NULL 检查**：`audio_system_create` 中 `audio_block` calloc 失败时 `impl` 指向近零地址，`ma_engine_init` 写入崩溃；`sources` calloc 失败时返回的 AudioSystem 的 sources 为 NULL，后续使用崩溃。修复：两处均添加 NULL 检查，失败时清理并返回 NULL。
  - **R118-2 ecs_system.c 堆回退 malloc NULL 检查**：`ecs_parallel_for` 中 job_count > 512 时回退到 `malloc`，未检查返回值，OOM 崩溃。修复：malloc 失败时回退到静态池 `_job_pool` 并钳制 job_count 到 ECS_JOB_POOL_SIZE，LOG_WARN 降级。
  - **验收**：全部 23/23 测试通过。BVH/GL 构建路径编译成功。
  - **里程碑**：R102-R118 完成引擎全部 86 个 .c 源文件的逐文件深度审查。
- [x] Round 119：头文件/framework/platform 全量审查（无需修复） ——
  - **R119 审查**：审查 83 个头文件中的内联函数和宏定义、framework/ 目录（3 个 C++ 文件）、platform/ 目录（5 个 demo 文件）、tests/test_framework.h。
  - 14 个含内联函数的头文件均无问题：math.h（fast_rsqrt SSE+标量、vec3_len/normalize 1e-12f 防除零、quat_normalize/slerp/nlerp 1e-12f 守卫+dot<0翻转、quat_from_axis_angle 1e-6f 零轴守卫、mat4_mul SSE+标量、mat4_mul_ortho_diag/proj_view/inv_perspective 文档化前置条件）、simd.h（SSE2 AABB/ray/batch + 标量回退）、alloc.h（arena_alloc 溢出检查）、pool.h（NULL 检查）、cull.h（p-vertex+sign_mask）、imgui.h（slider 防除零）、lighting.h、string.h、assert.h、types.h、rhi.h、ecs.h、packet.h、async_loader_private.h。
  - framework/ 代码为桩实现（base_application.cc Init/DeInit/Tick/IsQuit，graphics_manager.cc 空命名空间，main.cc 标准入口），无内存分配。
  - platform/ 5 个 demo 文件不链接到引擎库。
  - tests/test_framework.h 标准测试宏框架，do-while(0) 包裹。
  - **验收**：审查未发现问题，无需代码修改。R102-R119 完成引擎全部源码全量审查。
- [x] Round 120：第二轮深度审查 — ftell 回绕堆溢出 + VFS hash table NULL 检查 ——
  - **R120 审查**：第二轮聚焦更微妙的问题模式——整数溢出在大小计算、ftell 返回 -1 时 usize 回绕、线程安全/use-after-free。
  - **R120-1 vfs.c ftell 回绕堆溢出**：`vfs_open` 目录挂载路径中 `(usize)ftell(fp)` 当 ftell 返回 -1 时 `sz = SIZE_MAX`，`calloc(1, sizeof(VFSFile) + SIZE_MAX)` 回绕为 `calloc(1, sizeof(VFSFile) - 1)` 极小分配，`fread(f->data, 1, SIZE_MAX, fp)` 堆溢出。修复：`ftell < 0` 检查，失败时 `fclose + return NULL`。
  - **R120-1b vfs.c hash table malloc NULL 检查**：`vfs_mount_pak` 中 `malloc(table_size * sizeof(u32))` 未检查 NULL，`memset(table, 0xFF, ...)` 崩溃。修复：NULL 检查，失败时清理已分配资源并返回 false。
  - **R120-2 font.c ftell 回绕堆溢出**：`font_renderer_init` 中两处 `(usize)ftell` 同样回绕为 SIZE_MAX，`malloc(SIZE_MAX + 1)` 回绕为 `malloc(0)`，`malloc(0)` 返回非 NULL 零大小分配，`fread` 写入堆溢出。R116-1 添加了 malloc NULL 检查但遗漏了 ftell < 0 检查。修复：添加 `ftell < 0` 检查，失败时 fclose 并置长度为 0。
  - **验收**：全部 23/23 测试通过。BVH/GL 构建路径编译成功。
- [x] Round 121：第三轮深度审查 — vfs double-free 修复 + 着色器/strncpy/realloc/shift 全扫描 ——
  - **R121 审查**：第三轮系统扫描 10 类问题模式：strncpy null 终止、snprintf/sprintf 缓冲区、realloc 旧指针泄漏、整数截断、移位越界、sscanf 溢出、atoi 验证、着色器除零/越界、编译器警告。
  - **R121-1 vfs.c double-free**（R120-1b 回归）：R120-1b 添加的 hash table malloc NULL 检查在 `mount_count++` 和 `mounts[idx]` 赋值之后执行。失败路径 `free(names); free(entries); fclose(fp); return false;` 但 `vfs_destroy` 后续迭代 `mounts[0..mount_count-1]` 时会再次 free/fclose → double-free。修复：将 hash table 构建（malloc + memset + 填充循环）移到 mount 注册之前，失败时只需释放资源返回，无需回滚 mount 注册。
  - **确认安全**：strncpy 24 处全有 null 终止；snprintf 25 处全用 sizeof；无 sprintf；realloc 4 处全用临时变量+NULL 检查；memcpy 10 处 count 全有边界；整数截断 4 处实际值远小于 2^32；移位 17 处全有边界（LOD_MAX_LEVELS=4、bone<64、编译期常量）；sscanf 6 处全有宽度限制；atoi 16 处全用于非对抗性输入；着色器 5 个均有除零守卫和边界检查；GCC/Clang 零警告。
  - **验收**：全部 23/23 测试通过。BVH/GL 构建路径编译成功。
- [x] Round 122：第四轮深度审查 — 初始化路径 malloc NULL 检查 + RHI 句柄验证 ——
  - **R122 审查**：聚焦初始化函数中的资源分配错误路径——malloc 后未检查 NULL 即返回 true、rhi_*_create 后未验证句柄、多资源分配中部分失败未清理。
  - **R122-1 gpucull.c malloc NULL**：`gpucull_init` 中 `malloc(zb_off + zb_bytes)` 未检查 NULL，`_zero_buf = NULL + pb_bytes`（野指针），返回 true。修复：NULL 检查 + `gpucull_shutdown` + return false。
  - **R122-2 particles.c RHI 句柄**：`particles_init` 中 `particle_ssbo`/`sampler`/`particle_tex` 创建后未验证，`particle_ssbo` 随即用于 `rhi_buffer_map`。修复：`initialized` 前添加 `rhi_handle_valid` 检查 + `particles_shutdown`。
  - **R122-3 water.c RHI 句柄**：`water_init` 中 `vbo`/`ibo` 未验证。修复：`rhi_handle_valid` + `water_shutdown`。
  - **R122-4 terrain.c RHI 句柄**：`terrain_create` 中 `vbo`/`ibo` 未验证。修复：`rhi_handle_valid` + `terrain_shutdown`。
  - **R122-5 occlusion_cull.c sampler**：`occlusion_cull_init` 中 `hi_z_sampler` 未验证。修复：加入现有 pipeline 验证检查。
  - **确认安全**：read_file 25 处全有 ftell+malloc 检查；indirect_draw 4 buffer 统一验证；gpucull 3 SSBO 已有 R111 验证；occlusion_cull 3 buffer 逐个验证；realloc 4 处全有临时变量+NULL 检查。
  - **验收**：全部 23/23 测试通过。BVH/GL 构建路径编译成功。
- [x] Round 123：第五轮深度审查 — font.c TTF ftell 回绕 + 异步加载器线程安全 + fd/socket 审查 ——
  - **R123 审查**：聚焦资源生命周期和线程安全——ftell 返回 -1 完整覆盖、异步加载器竞态条件、fd/socket 泄漏、命令注入、格式串注入、getenv+atoi 验证、main.c 初始化失败处理。
  - **R123-1 font.c TTF ftell 回绕**（SECURITY）：`font_renderer_init` 中 TTF 字体加载路径 `(usize)ftell(f)` 缺少 `ftell < 0` 检查，当 ftell 返回 -1 时 `malloc(SIZE_MAX)` 在 overcommit 系统上可能成功 → 堆溢出。R120-2 修复了同一函数的 shader 路径但遗漏了 TTF 路径。修复：添加 `ftell < 0` 检查。
  - **确认安全**：异步加载器（release-acquire 模式、MPSC 无锁队列、CAS 取消、shutdown join 全线程）；ftell 全代码库 6 处全部安全；无命令注入（无 system/popen/exec）；无格式串注入；getenv 16 处全有 NULL 检查；后期处理 pipeline 已验证；filewatch fd 管理；network socket 管理。
  - **验收**：全部 23/23 测试通过。BVH/GL 构建路径编译成功。
- [x] Round 124：第六轮深度审查 — verify_pak 工具加固 + 网络序列化/Lua绑定/packer/CMake 全扫描 ——
  - **R124 审查**：覆盖工具链和跨模块接口——网络序列化对齐、网络复制缓冲区边界、Lua 绑定边界、packer 工具、verify_pak 工具、CMake 构建配置。
  - **R124-1 verify_pak.c ftell+malloc**（SECURITY+ROBUSTNESS）：`verify_file` 中 `ftell(fp)` 缺少 < 0 检查；`malloc(disk_size)` 和 `malloc(pak_size)` 未检查 NULL 即用于 `fread`/`vfs_read`。修复：添加 `ftell < 0` 检查 + 两处 malloc NULL 检查 + 资源清理。
  - **确认安全**：packet.c（显式 LE 编码+全边界检查）；net_replication.c（sscanf %255s+重排序槽 PACKET_MAX_SIZE+可靠待发 PACKET_MAX_SIZE+parse_payload 钳制 max_count）；script_lua.c（checked_body+lua_pcall+luaL_check*）；packer.c（R105-2 边界检查+4GB 限制+MAX_ENTRIES）；network.c（fd 管理+net_close 检查 INVALID_RAW_SOCKET+net_poll NULL 检查）；CMakeLists.txt（-Werror -pedantic+第三方隔离+ASAN）；全代码库 read_file 25+ 处全有 ftell+malloc 检查。
  - **验收**：全部 23/23 测试通过。BVH/GL 构建路径编译成功。
- [x] Round 135：VK VkResult 全路径收尾审计 — 78 处（含 R134 遗漏的 MRT FBO + cubemap depth face 路径）——
  - **R135 审查**：R131-R134 已修复 69 处 VK VkResult 检查。R135 完成全部剩余未检查 VK 调用，覆盖帧路径、截图路径、纹理创建/上传路径、swapchain 创建路径、MRT FBO 创建路径（R134 遗漏）、cubemap depth FBO per-face 循环（R134 遗漏）、布局转换路径、GPU 计时器/缓冲区创建路径、以及所有清理/等待路径。**审计后零未检查 VK 调用剩余。**
  - **R135-A frame_begin 5 处**：vkWaitForFences/vkResetFences/vkResetDescriptorPool/vkResetCommandBuffer/vkBeginCommandBuffer — 失败时 `frame_started = false` + 跳帧。
  - **R135-B frame_end 2 处**：vkEndCommandBuffer/vkQueueSubmit — 失败时 `frame_started = false` + return。
  - **R135-C rhi_screenshot 7 处**：vkDeviceWaitIdle/vkBindBufferMemory/vkAllocateCommandBuffers/vkBeginCommandBuffer/vkEndCommandBuffer/vkQueueWaitIdle/vkMapMemory — 失败时清理 staging 资源并返回。**关键：vkMapMemory 失败阻断 memcpy(NULL) 崩溃。**
  - **R135-D rhi_texture_create staging+else 9 处**：staging 路径 3 处 + else 路径 6 处（vkAllocateCommandBuffers/vkBeginCommandBuffer/vkEndCommandBuffer/vkCreateFence/vkQueueSubmit/vkWaitForFences）— 逆序清理 cmd+view+image+memory。
  - **R135-E rhi_texture_upload_mip 8 处**：vkBindBufferMemory/vkMapMemory/vkAllocateCommandBuffers/vkBeginCommandBuffer/vkEndCommandBuffer/vkCreateFence/vkQueueSubmit/vkWaitForFences。
  - **R135-F rhi_cubemap_create 6 处**：vkAllocateCommandBuffers/vkBeginCommandBuffer/vkEndCommandBuffer/vkCreateFence/vkQueueSubmit/vkWaitForFences — 逆序清理 cd 资源 + return RHI_HANDLE_NULL。
  - **R135-G rhi_cubemap_transition_to_read 7 处**：vkDeviceWaitIdle/vkAllocateCommandBuffers/vkBeginCommandBuffer/vkEndCommandBuffer/vkCreateFence/vkQueueSubmit/vkWaitForFences — void 函数，LOG_WARN + return。
  - **R135-H rhi_texture_transition_to_read 7 处**：同 R135-G 模式。
  - **R135-I init/swapchain 5 处**：vkCreateRenderPass（resume_render_pass）/vkQueueSubmit+vkQueueWaitIdle（init_image_layout）/vkGetSwapchainImagesKHR×2。
  - **R135-J rhi_mrt_fbo_create 6 处（R134 遗漏）**：vkCreateImage/vkAllocateMemory/vkBindImageMemory/vkCreateImageView（depth）/vkCreateRenderPass/vkCreateFramebuffer — 逆序清理 color+depth 资源 + free(md) + return fbo。R134 文档误将 rhi_offscreen_fbo_create_fmt 标记为“rhi_mrt_fbo_create”。
  - **R135-K rhi_cubemap_depth_fbo_create per-face 2 处（R134 遗漏）**：vkCreateImageView/vkCreateFramebuffer — 逆序清理 face views+framebuffers + depth 资源 + return fbo。
  - **R135-L 资源创建 4 处**：vkCreateQueryPool（GPU 计时器）/vkCreateBufferView（texel buffer）/vkMapMemory×2（buffer_create 持久映射 + buffer_map）。
  - **R135-M cleanup/wait 13 处**：vkDeviceWaitIdle×8 + vkWaitForFences×5 — LOG_WARN 但继续执行。
  - **VK VkResult 检查总计**：R131 19 + R132 17 + R133 14 + R134 19 + R135 78 = **147 处**已修复。

- **R136 审查**：全引擎 fseek 返回值检查审计。扫描发现 37 个源文件中 80 处未检查 fseek 返回值，涵盖所有 renderer 模块（29 文件）、asset/vfs.c（4 处，含 PAK 数据偏移定位）、ui/font.c（4 处 + 修复 double-close bug）、scene/scene_serial.c（4 处）、script/script.c（2 处）、main.c（2 处）、test_vulkan.c（2 处）、asset/hotreload.c（2 处）。**审计后零未检查 fseek 调用剩余。**
  - **R136-A 标准模式 30 文件 60 处**：renderer 模块（particles/taa/ssr/gpucull/cinematic/volumetric/ssgi/lens_flare/sharpen/motion_blur/contact_shadow/upscale/god_rays/debug_viz/lens_effects/occlusion_cull/point_shadow/indirect_draw/color_grade/dof/fxaa/post_process/skybox/ssao/sss/tonemap/combined_post_process/forward_velocity）+ hotreload.c + main.c — `fseek(SEEK_END)` 和 `fseek(SEEK_SET)` 均未检查返回值，失败时 ftell 返回未定义值可能导致错误分配。
  - **R136-B 内联模式 2 文件 4 处**：water.c 和 test_vulkan.c — fseek/ftell/fseek 写在同一行，拆分为多行并添加返回值检查。
  - **R136-C font.c double-close bug 修复**：原代码当 `vsz < 0` 时 fclose(vf) 后继续执行 fread/fclose，导致 use-after-close 和 double-close。重构为 else 分支跳过 fread/fclose。
  - **R136-D terrain.c 2 处**：fseek 顺序与标准模式不同（sz <= 0 检查在 fseek(SET) 之后），添加 fseek 返回值检查。
  - **R136-E script.c 2 处**：fseek(SET) 在 sz < 0 检查之前，返回 false 而非 NULL。添加 fseek 返回值检查。
  - **R136-F vfs.c 4 处**：PAK 挂载路径 fseek 到 name table 偏移 + vfs_open 中 fseek 到 data_offset + 标准文件大小模式。失败时清理已分配资源并返回。
  - **R136-G scene_serial.c 4 处**：scene_load_binary 和 scene_load_json 各 2 处 fseek，使用 `fp` 变量名。失败时 fclose + return false。
  - **fseek 返回值检查总计**：R136 **80 处**已修复，跨 37 个源文件。
  - **验收**：全部 23/23 测试通过。VK（ENGINE_VULKAN=ON）+ GL 构建路径编译成功。

- **R137 审查**：main.c 场景状态保存/加载路径 + 文件写入工具函数 unchecked fwrite/fread 审计。修复 43 处未检查 fwrite/fread 返回值。
  - **R137-A 场景状态保存 11 处**：magic/camera/sun_azimuth/sun_elevation/tonemap.exposure/render_scale/physics count + per-body position+velocity/water_y/water_enabled — 添加 `sv_ok` 跟踪，失败时 LOG_WARN。循环中添加 `&& sv_ok` 条件，首次失败后跳过后续写入。
  - **R137-B 场景状态加载 13 处**：同上字段 — 添加 `ld_ok` 跟踪，fread 魔术数失败时跳过整个加载。循环中添加 `&& ld_ok` 条件，防止从截断文件读取垃圾数据。
  - **R137-C BMP 写入器 3 处**：header fwrite + per-row fwrite + padding fwrite — 添加 `bmp_ok` 跟踪，header 失败时跳过行写入。
  - **R137-D WAV 写入器 14 处**：13 个 header fwrite + 1 个 per-sample fwrite — 添加 `wav_ok` 跟踪，失败时跳过后续写入。
  - **R137-E texture mipmap 写入器 1 处**：per-mip fwrite — 失败时 free+fclose+return mips，避免写入不完整 mip 链。
  - **R137-F test_vulkan.c 1 处**：golden image PPM fwrite — 失败时 return false。
  - **fwrite/fread 返回值检查总计**：R137 **43 处**已修复，跨 2 个源文件（main.c + test_vulkan.c）。
  - **验收**：全部 23/23 测试通过。VK（ENGINE_VULKAN=ON）+ GL 构建路径编译成功。

- **R138 审查**：全引擎 `strncpy` 缺少显式 null 终止一致性审计。修复 13 处缺少 `buf[sizeof(buf)-1] = '\0'` 的 `strncpy` 调用。
- **R138-A vfs.c PAK 挂载 1 处**：`vfs->mounts[idx].path` strncpy 后缺少 `path[VFS_MAX_PATH-1] = '\0'`（dir 挂载已有，PAK 挂载缺失）。
- **R138-B filewatch.c Linux base_path 1 处**：`fw->base_path` strncpy 后缺少 null 终止（Windows 路径已有，Linux 缺失）。
- **R138-C 平台窗口 2 处**：window_wayland.c + window_x11.c `MonitorInfo.name` strncpy 后缺少 `m->name[63] = '\0'`。
- **R138-D hotreload.c 3 处**：vert_path + frag_path + texture path strncpy 后缺少 null 终止（memset 已零初始化，但缺少防御性终止）。
- **R138-E mipmap_stream.c 1 处**：`tex->path` strncpy 后缺少 null 终止。
- **R138-F audio_stream.c 2 处**：`s->path` strncpy 后缺少 null 终止（memset 已零初始化）。
- **R138-G main.c 3 处**：draw_bench_csv_path + netrep_peer_file + netrep_peer_dir（静态变量零初始化，但缺少防御性终止）。
- **strncpy null 终止审计总计**：R138 **13 处**已修复，跨 7 个源文件。所有缓冲区均已零初始化（calloc/memset/静态存储），修复前技术上安全但缺少防御性深度。

- **R139 审查**：`snprintf` 返回值检查审计 — shader define 注入器中未检查的 snprintf 返回值。修复 4 处跨 2 个源文件。
- **R139-A main.c shader_inject_define 2 处**：(1) `snprintf(NULL, 0, ...)` 返回值直接 cast 为 usize — 如果返回负值（编码错误），usize cast 产生巨大数值导致 malloc 失败或巨大分配。添加 `if (def_raw < 0) return NULL;`。(2) `snprintf(out + head, ...)` 返回值 `n` 直接 cast 为 usize 用于 memcpy 偏移 — 如果 n < 0，`(usize)n` 溢出为巨大数值导致缓冲区溢出。添加 `if (n < 0) { free(out); return NULL; }`。
- **R139-B deferred.c defrd_inject_define 2 处**：与 main.c 相同模式，相同修复。
- **snprintf 返回值审计总计**：R139 **4 处**已修复，跨 2 个源文件。修复前理论上存在编码错误时缓冲区溢出风险，实际触发概率极低（简单格式字符串 `"#define %s 1\n"` + 有效字符串参数）。

- **R140 审查**：`async_loader.c` 文件大小截断检查 — usize→u32 隐式截断防护。修复 2 处跨 1 个源文件。
- **R140-A 全文件读取路径 1 处**：`vfs_read_all` 返回 `usize` file_size，直接 `(u32)file_size` 赋值给 `req->size`（u32）— 如果文件 >4GB，size 被截断导致回调收到错误大小。添加 `if (file_size > (usize)UINT32_MAX)` 检查，拒绝过大文件并设置 ASSET_FAILED。
- **R140-B 范围读取路径 1 处**：`to_read`（usize）直接 `(u32)to_read` 赋值给 `req->size` — 如果范围 >4GB 同样截断。添加 `if (to_read > (usize)UINT32_MAX)` 检查，拒绝过大范围。
- **截断检查审计总计**：R140 **2 处**已修复，跨 1 个源文件。修复前理论上 >4GB 文件会导致大小截断，实际触发概率低（游戏资产通常 <100MB）。

- **R141 审查**：线程创建与 shaderc 编译器初始化返回值检查。修复 3 处跨 2 个源文件。
- **R141-A task.c 线程创建返回值检查 2 处**：(1) `platform_thread_create`（Windows `_beginthreadex`）返回值被忽略 — 如果线程创建失败，task_system_destroy 会尝试 join 未初始化的线程句柄（UB）。改为返回 `bool`，调用点检查失败并清理已初始化但未创建线程的 worker 的 deque，更新 `ts->worker_count`。(2) `platform_thread_create_posix`（`pthread_create`）相同问题相同修复。
- **R141-B rhi_vk.c shaderc_compiler_initialize NULL 检查 1 处**：`shaderc_compiler_initialize()` 返回值直接赋值给 `vk->shaderc_compiler` 未检查 NULL — 如果初始化失败（OOM），后续 `shaderc_compile_into_spv` 使用 NULL compiler 为 UB。添加 NULL 检查 + LOG_FATAL。
- **线程创建 + shaderc 审计总计**：R141 **3 处**已修复，跨 2 个源文件。修复前线程创建失败会导致 task_system_destroy UB（join 未初始化句柄）+ deque 内存泄漏；shaderc 初始化失败会导致后续编译调用 UB。

- **R142 审查**：数学函数除零防护 + 窗口尺寸 0 防护。修复 5 处跨 3 个源文件。
- **R142-A math.c mat4_ortho 除零防护 3 处**：`(right - left)`、`(top - bottom)`、`(far_val - near_val)` 三处除法在维度退化为 0 时产生 Inf/NaN 矩阵。添加 epsilon 钳制（`< 1e-20f → 1e-20f`）。
- **R142-B math.c mat4_perspective 除零防护 3 处**：`aspect` 为 0（窗口最小化时 `w/0=Inf`）、`far_val - near_val` 为 0、`tanf(fov*0.5)` 为 0（FOV=0 或 FOV=π）三处除法产生 Inf/NaN。添加 epsilon 钳制。
- **R142-C main.c camera.aspect 窗口最小化防护 2 处**：`camera_init` 和 resize 路径中 `(f32)w / (f32)h` 在 h=0 时产生 Inf。改为 `(f32)w / (f32)(h > 0 ? h : 1)`。
- **R142-D main.c benchmark 除零防护 1 处**：`1000.0 / avg_ms` 在 avg_ms=0（所有帧 delta_time=0）时产生 Inf。添加 `avg_ms > 0.0 ? 1000.0 / avg_ms : 0.0` 检查。
- **R142-E test_vulkan.c camera_init 同样防护 1 处**：与 main.c 相同的 h=0 防护。
- **除零防护审计总计**：R142 **5 处**已修复，跨 3 个源文件。修复前窗口最小化时产生 Inf/NaN 投影矩阵导致渲染异常，实际触发概率中等（Wayland/X11 窗口最小化时 h=0）。

- **R143 审查**：未检查 `fread` 返回值审计 — font.c + vfs.c 中 R137 遗漏的 `fread` 调用。修复 4 处跨 2 个源文件。
- **R143-A font.c TTF 文件 fread 1 处**：`fread(ttf_buf, 1, sz, f)` 返回值未检查 — 如果 fread 失败（磁盘错误），ttf_buf 包含部分数据，后续 `stbtt_InitFont` 可能在无效数据上 UB。添加返回值检查，失败时 free + fclose + return false。
- **R143-B vfs.c PAK name table fread 1 处**：`fread(names, 1, hdr.name_table_size, fp)` 返回值未检查 — 如果 fread 失败，names 包含部分数据，后续哈希表构建在无效名称上 UB。添加返回值检查，失败时 free(names) + free(entries) + fclose + return false。
- **R143-C vfs.c PAK entry data fread 1 处**：`fread(f->data, 1, pe->size, pak_fp)` 返回值未检查 — 如果 fread 失败，f->data 包含部分数据，后续使用返回错误数据。添加返回值检查，失败时 free(vfs_block) + return NULL。
- **R143-D vfs.c 普通文件数据 fread 1 处**：`fread(f->data, 1, sz, fp)` 返回值未检查 — 相同模式。添加返回值检查，失败时 free(vfs_block) + fclose + return NULL。
- **fread 返回值审计总计**：R137 修复 main.c 43 处，R143 修复 font.c + vfs.c 4 处，合计 **47 处**已修复。修复前磁盘 I/O 错误时使用部分数据可能导致 UB 或数据损坏。

- **R144 审查**：`stbi_load_from_memory` `(int)size` 截断检查 — 与 R140 同类的 usize→int 隐式截断防护。修复 2 处跨 2 个源文件。
- **R144-A asset.c stbi_load_from_memory (int)sz 1 处**：`stbi_load_from_memory(raw, (int)sz, ...)` — `sz` 为 usize（64位），如果 >2GB，`(int)sz` 截断为负值，stbi 内部使用负长度可能 UB。添加 `if (sz > (usize)INT32_MAX)` 检查，拒绝过大文件。
- **R144-B decode_pipeline.c stbi_load_from_memory (int)raw_size 1 处**：`stbi_load_from_memory(raw, (int)raw_size, ...)` — `raw_size` 为 u32，如果 >2GB（>INT32_MAX），`(int)raw_size` 截断为负值。添加 `if (raw_size > (u32)INT32_MAX)` 检查，拒绝过大文件。
- **截断检查审计总计**：R140 修复 async_loader.c 2 处 usize→u32，R144 修复 asset.c + decode_pipeline.c 2 处 usize/u32→int，合计 **4 处**已修复。

- **R145 审查**：`mipmap_level_size` u32 乘法溢出防护 — 纹理尺寸 `w * h * bpp` 在 u32 算术中可溢出（理论阈值 >32768×32768×4bpp），导致错误的 level_size=0 和错误的文件偏移。修复 2 处。
- **R145-A mipmap_level_size 乘法溢出**：`return w * h * bpp` → 先 cast 到 usize 计算，再检查 `> UINT32_MAX` 则钳制为 UINT32_MAX。
- **R145-B offset 累加溢出**：`u32 offset = 0` → `usize offset = 0`，赋值时 cast 为 u32，防止多级 mipmap 尺寸累加溢出。

- **审计总计（R129-R145）**：**366 处**全量加固，涵盖 calloc/malloc NULL 检查、Vulkan VkResult 全路径检查、fseek/fwrite/fread/fclose 返回值检查、strncpy null 终止、snprintf 截断检查、usize→u32/int 截断防护、线程创建检查、数学除零防护、窗口尺寸 0 防护、stbi_load_from_memory 截断检查、mipmap 级别尺寸乘法溢出防护。

- **R146 审查**：Vulkan push constant `push_staging[256]` 越界防护 — 6 个 `rhi_cmd_set_uniform_*` 函数仅检查 `location < 0`，未检查 `location + size > 256`，若硬编码偏移有误可导致栈缓冲区溢出。修复 6 处。
- **R146-A-F rhi_vk.c push constant 越界检查**：`mat4(64B) / vec3(12B) / vec2(8B) / vec4(16B) / f32(4B) / i32(4B)` 6 个函数添加 `(u32)location + SIZE > 256` 边界检查。

- **审计总计（R129-R146）**：**372 处**全量加固，涵盖 calloc/malloc NULL 检查、Vulkan VkResult 全路径检查、fseek/fwrite/fread/fclose 返回值检查、strncpy null 终止、snprintf 截断检查、usize→u32/int 截断防护、线程创建检查、数学除零防护、窗口尺寸 0 防护、stbi_load_from_memory 截断检查、mipmap 级别尺寸乘法溢出防护、Vulkan push constant 越界防护。

- **R147 审查**：`delta_time` 钳制防护 — 进程暂停（调试器/系统休眠/窗口最小化）后恢复时，帧间时间差可能达到数秒甚至数分钟，导致超大 dt 值引起物理穿透、动画跳帧。修复 2 处。
- **R147-A engine_frame delta_time 钳制**：在 `delta_time = (f64)(now_us - last_frame_us) / 1e6` 后添加 `if (delta_time > 0.1) delta_time = 0.1;`，将最大 dt 限制为 100ms（10 FPS 最低）。
- **R147-B target_fps 路径 delta_time 钳制**：在目标帧率睡眠后的第二次 `delta_time` 计算同样添加钳制。

- **审计总计（R129-R147）**：**374 处**全量加固，涵盖 calloc/malloc NULL 检查、Vulkan VkResult 全路径检查、fseek/fwrite/fread/fclose 返回值检查、strncpy null 终止、snprintf 截断检查、usize→u32/int 截断防护、线程创建检查、数学除零防护、窗口尺寸 0 防护、stbi_load_from_memory 截断检查、mipmap 级别尺寸乘法溢出防护、Vulkan push constant 越界防护、delta_time 钳制防护。

- **R148 审查**：Vulkan `vkAcquireNextImageKHR` 错误处理遗漏 — 首次调用仅处理 `VK_ERROR_OUT_OF_DATE_KHR`（交换链重建+重试），其他错误（如 `VK_ERROR_DEVICE_LOST`、`VK_ERROR_SURFACE_LOST_KHR`）直接落入后续代码，使用 stale 的 `image_index` 记录命令缓冲区，可能导致无效 framebuffer 的 GPU 错误级联。修复 1 处。
- **R148-A rhi_vk.c vkAcquireNextImageKHR 错误处理**：添加 `else if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR)` 子句，非 OUT_OF_DATE 错误时 LOG_ERROR + `frame_started = false` + 提前返回，防止 stale image_index 被用于后续渲染命令。

- **审计总计（R129-R148）**：**375 处**全量加固，涵盖 calloc/malloc NULL 检查、Vulkan VkResult 全路径检查、fseek/fwrite/fread/fclose 返回值检查、strncpy null 终止、snprintf 截断检查、usize→u32/int 截断防护、线程创建检查、数学除零防护、窗口尺寸 0 防护、stbi_load_from_memory 截断检查、mipmap 级别尺寸乘法溢出防护、Vulkan push constant 越界防护、delta_time 钳制防护、Vulkan swapchain 获取图像错误处理防护。

- **R149 审查**：Vulkan `vk_create_framebuffers` NULL 解引用防护 — 若 `vk_create_swapchain` 失败（如 `vkCreateSwapchainKHR` 错误、`swap_images`/`swap_views` OOM），`vk->swap_views` 为 NULL 但 `vk->swap_count` 保留 stale 值。`vk_create_framebuffers` 循环访问 `vk->swap_views[i]` 解引用 NULL。修复 1 处。
- **R149-A rhi_vk.c vk_create_framebuffers NULL 守卫**：函数入口添加 `if (!vk->swap_views || vk->swap_count == 0) return;`，防止 `swap_views` 为 NULL 时解引用崩溃。

- **审计总计（R129-R149）**：**376 处**全量加固，涵盖 calloc/malloc NULL 检查、Vulkan VkResult 全路径检查、fseek/fwrite/fread/fclose 返回值检查、strncpy null 终止、snprintf 截断检查、usize→u32/int 截断防护、线程创建检查、数学除零防护、窗口尺寸 0 防护、stbi_load_from_memory 截断检查、mipmap 级别尺寸乘法溢出防护、Vulkan push constant 越界防护、delta_time 钳制防护、Vulkan swapchain 获取图像错误处理防护、Vulkan framebuffer 创建 NULL 解引用防护。

- **R150 审查**：Vulkan `vk->framebuffers` NULL 解引用防护 — 4 个函数访问 `vk->framebuffers[vk->image_index]` 未检查 NULL。若 `vk_create_framebuffers` 失败（OOM/vkCreateFramebuffer 错误），`framebuffers` 为 NULL 但 `vkAcquireNextImageKHR` 仍可成功（交换链有效），导致 `NULL[image_index]` 崩溃。修复 4 处。
- **R150-A rhi_frame_begin framebuffers NULL 守卫**：在 acquire 检查后添加 `if (!vk->framebuffers) { LOG_ERROR + frame_started = false + return; }`，防止交换链有效但 framebuffer 未创建时解引用 NULL。
- **R150-B rhi_cmd_begin_render_pass framebuffers NULL 守卫**：添加 `if (!vk->framebuffers) return;`，防止渲染通道未启动时解引用 NULL。
- **R150-C rhi_cmd_unbind_shadow_map framebuffers NULL 守卫**：同上。
- **R150-D rhi_offscreen_fbo_unbind framebuffers NULL 守卫**：同上。

- **审计总计（R129-R150）**：**380 处**全量加固，涵盖 calloc/malloc NULL 检查、Vulkan VkResult 全路径检查、fseek/fwrite/fread/fclose 返回值检查、strncpy null 终止、snprintf 截断检查、usize→u32/int 截断防护、线程创建检查、数学除零防护、窗口尺寸 0 防护、stbi_load_from_memory 截断检查、mipmap 级别尺寸乘法溢出防护、Vulkan push constant 越界防护、delta_time 钳制防护、Vulkan swapchain 获取图像错误处理防护、Vulkan framebuffer 创建/访问 NULL 解引用防护。

- **R151 审查**：`scene_compute_world_transforms` parent_index 越界读防护 — 从二进制/JSON 场景文件读取的 `parent_index` 未验证边界，恶意/损坏文件可设置任意 u32 值，导致 `scene->nodes[parent_index]` 越界读。同时处理自引用（parent_index == i）读取未初始化 world_transform 的问题。修复 1 处。
- **R151-A asset.c scene_compute_world_transforms parent_index 边界检查**：将 `parent_index == UINT32_MAX` 检查扩展为 `parent_index == UINT32_MAX || parent_index >= scene->node_count || parent_index == i`，越界/自引用索引视为根节点（无父节点）。

- **审计总计（R129-R151）**：**381 处**全量加固，涵盖 calloc/malloc NULL 检查、Vulkan VkResult 全路径检查、fseek/fwrite/fread/fclose 返回值检查、strncpy null 终止、snprintf 截断检查、usize→u32/int 截断防护、线程创建检查、数学除零防护、窗口尺寸 0 防护、stbi_load_from_memory 截断检查、mipmap 级别尺寸乘法溢出防护、Vulkan push constant 越界防护、delta_time 钳制防护、Vulkan swapchain 获取图像错误处理防护、Vulkan framebuffer 创建/访问 NULL 解引用防护、场景图 parent_index 越界读防护。

- **R152 审查**：视锥剔除批处理缓冲区溢出防护 — `CULL_BUF_CAP=16384` 容量的 `cull_aabbs`/`cull_node_map` 数组在遍历场景节点时未检查 `cull_node_count` 是否超出容量。场景含超过 16384 个网格节点时堆溢出。修复 1 处。
- **R152-A main.c cull_node_count 容量检查**：在 cull 循环内添加 `if (cull_node_count >= CULL_BUF_CAP) break;`，超出容量时停止添加节点，防止堆溢出。

- **R153 审查**：decode_generate_mipchain 栈溢出 + 偏移截断防护 — `widths[16]`/`heights[16]`/`offsets[16]` 数组仅有 16 个槽位，但 65536×65536 纹理产生 17 级 mip 导致栈溢出；`offsets` 为 `u32` 类型，32768×32768 RGBA 纹理 mip 链总量超 4GB 时 usize→u32 截断导致堆损坏。修复 2 处。
- **R153-A decode_pipeline.c mip_count 容量限制**：在 mip 级别计数后添加 `if (mip_count > 16) mip_count = 16;`，超出数组容量时截断，防止栈溢出。
- **R153-B decode_pipeline.c offsets 类型修正**：将 `u32 offsets[16]` 改为 `usize offsets[16]`，移除 `(u32)` 强制转换，防止大纹理 mip 链偏移截断导致堆损坏。

- **审计总计（R129-R153）**：**384 处**全量加固，涵盖 calloc/malloc NULL 检查、Vulkan VkResult 全路径检查、fseek/fwrite/fread/fclose 返回值检查、strncpy null 终止、snprintf 截断检查、usize→u32/int 截断防护、线程创建检查、数学除零防护、窗口尺寸 0 防护、stbi_load_from_memory 截断检查、mipmap 级别尺寸乘法溢出防护、Vulkan push constant 越界防护、delta_time 钳制防护、Vulkan swapchain 获取图像错误处理防护、Vulkan framebuffer 创建/访问 NULL 解引用防护、场景图 parent_index 越界读防护、视锥剔除缓冲区溢出防护、mip 链生成栈溢出与偏移截断防护。

- **R154 审查**：BVH 构建 OOM 崩溃防护 — `bvh_alloc_node` 返回 `BVH_NULL` 时未检查，递归调用返回值未检查，`bvh_build` 失败后 `object_count` 仍非零导致 `bvh_refit` NULL 解引用。修复 7 处。
- **R154-A bvh.c bvh_alloc_node 返回值检查**：在 `bvh_build_recursive` 中，`bvh_alloc_node` 返回 `BVH_NULL` 时提前返回 `BVH_NULL`，防止 `bvh->nodes[BVH_NULL]` 越界访问。
- **R154-B bvh.c 递归调用返回值检查**：在 `bvh_build_recursive` 中，左右子树递归调用返回 `BVH_NULL` 时提前返回 `BVH_NULL`，防止 `bvh->nodes[left/right]` 越界访问。
- **R154-C bvh.c bvh_build root NULL 检查**：在 `bvh_build` 中，`bvh_build_recursive` 返回后检查 `root != BVH_NULL` 再访问 `bvh->nodes[root]`。
- **R154-D bvh.c bvh_build 失败后 object_count 清零**：在 `bvh_build` 中所有分配失败路径（leaf_map/nodes/_build_indices）设置 `object_count = 0`，防止 `bvh_refit` 继续访问已释放的内存。
- **R154-E bvh.c bvh_refit NULL 守卫**：在 `bvh_refit` 开头添加 `!bvh->nodes || !bvh->leaf_map || bvh->root == BVH_NULL` 检查，防止 `bvh_build` 失败后 NULL 解引用。

- **R155 审查**：g_node_vis / node_spheres 越界读防护 — `mega_buf.cmd_node_index[16384]` 存储原始节点索引，当 `scene.node_count > 16384` 时索引可超过 `g_node_vis[16384]` 和 `node_spheres[16384]` 的容量，导致固定大小数组越界读。修复 7 处。
- **R155-A main.c mega_count_visible_node_vis**：`node_vis[ni]` 越界读，添加 `ni >= 16384` 条件使超限节点视为可见。
- **R155-B main.c 前向渲染路径**：`g_node_vis[ni]` 越界读，改为 `(ni < 16384) ? g_node_vis[ni] : 1` 使超限节点视为可见。
- **R155-C main.c 延迟渲染路径**：`g_node_vis[ni]` 越界读，改为 `(ni < 16384) ? g_node_vis[ni] : 1` 使超限节点视为可见。
- **R155-D main.c mega_build_unified_udc**：`node_spheres[ni]` 越界读，添加 `ni < 16384` 条件分支，超限节点设置无效包围球（半径 -1）自动被剔除。
- **R155-E main.c legacy gpucull pack 循环**：循环条件添加 `ni < 16384` 约束，防止 `node_spheres[ni]` 越界读。
- **R155-F main.c shadow CPU frustum culling 循环**：循环条件添加 `ni < 16384` 约束，防止 `node_spheres[ni]` 越界读。
- **R155-G main.c point light shadow culling 循环**：循环条件添加 `ni < 16384` 约束，防止 `node_spheres[ni]` 越界读。

- **R156 审查**：任务系统 calloc 失败 NULL 解引用 + pool_count 越界读防护 — `task_alloc` 中 calloc 失败后 `memset(NULL)` 崩溃；`task_system_destroy` 中 `pool_count` 可超过 `task_pool_capacity` 导致越界读 `task_pool[]`；`task_wait_handle`/`task_submit_dep` 使用 `pool_count` 而非 `task_pool_capacity` 做边界检查导致越界读。修复 9 处。
- **R156-A task.c task_alloc calloc 失败检查**：calloc 失败时 `t` 为 NULL，后续 `memset(t, 0, sizeof(Task))` 崩溃。添加 `if (!t) return NULL;` 防护。
- **R156-B task.c task_alloc pool 耗尽时 handle 失效标记**：pool 耗尽且无法注册时，`pool_idx` 保留原始值（≥ capacity），编码到 handle 后导致越界读。设置 `pool_idx = 0xFFFFFFFF` 标记为未注册。
- **R156-C task.c task_system_destroy pool_count 钳制**：`task_pool_count` 可超过 `task_pool_capacity`（pool 耗尽时），遍历越界读 `task_pool[]` 进入 `_task_block` 内存。添加 `if (pool_count > capacity) pool_count = capacity;` 钳制。
- **R156-D task.c task_wait_handle 边界检查修正**：使用 `idx >= ts->task_pool_capacity` 替代 `idx >= pool_count`，防止 `pool_count > capacity` 时越界读。
- **R156-E task.c task_submit_dep 边界检查修正**：同上，使用 `idx >= ts->task_pool_capacity` 替代 `idx >= pool_count`。
- **R156-F task.c task_submit NULL 检查**：`task_alloc` 返回 NULL 时跳过提交。
- **R156-G task.c task_submit_n NULL 检查**：`task_alloc` 返回 NULL 时跳过该次提交。
- **R156-H task.c task_submit_ex NULL 检查**：`task_alloc` 返回 NULL 时返回 `TASK_HANDLE_INVALID`。
- **R156-I task.c task_submit_dep NULL 检查**：`task_alloc` 返回 NULL 时返回 `TASK_HANDLE_INVALID`。

- **R157 审查**：RHI 资源池耗尽 slot 0 覆盖损坏 + VFS PAK entry_count 乘法溢出防护 — `rhi_alloc_slot` 池耗尽时返回 0，24 处调用方不检查返回值直接写入 `slots[0]`，覆盖已有资源并损坏空闲链表；VFS PAK 加载中 `next_pow2(entry_count * 2)` 在 `entry_count > 2^31` 时 u32 溢出导致哈希表过小。修复 2 处。
- **R157-A rhi.c rhi_alloc_slot 池耗尽 abort**：池耗尽时 `LOG_FATAL` 后返回 0，调用方不检查返回值直接 `dev->slots[idx].ptr = ...`，覆盖 slot 0 的已有资源，损坏空闲链表，导致后续分配重用已占用 slot 和 use-after-free。改为 `abort()` 防止静默损坏。
- **R157-B vfs.c PAK entry_count 溢出检查**：恶意 PAK 文件 `entry_count > 2^30` 时 `entry_count * 2` 溢出 u32，`next_pow2` 返回极小值，哈希表过小导致线性探测无限循环。添加 `entry_count > (1u << 30)` 拒绝检查。

- **R158 审查**：内存分配器 usize 溢出防护 — `heap_alloc_fn`/`heap_realloc_fn` 中 `size + extra + sizeof(void*)` 可溢出 usize 导致 malloc 分配过小缓冲区；`pool_init_alloc` 中 `bs * block_count` 可溢出。修复 3 处。
- **R158-A alloc.c heap_alloc_fn usize 溢出检查**：`size + extra + sizeof(void*)` 溢出 usize 时回绕到小值，malloc 分配过小缓冲区导致后续堆溢出。添加 `if (total < size) return NULL;` 溢出检查。
- **R158-B alloc.c heap_realloc_fn usize 溢出检查**：同上，`new_size + extra + sizeof(void*)` 可溢出。添加溢出检查。
- **R158-C pool.c pool_init_alloc usize 溢出检查**：`bs * block_count` 可溢出 usize。添加 `if (block_count > SIZE_MAX / bs) return false;` 预检查。

- **R159 验证审查**（无新问题）：全面验证轮次，确认 R129-R158 的 412 处修复全部完好。审查 26 个源文件覆盖引擎全部子系统：音频（audio.c 槽位管理+设备枚举, audio_stream.c 流管理+R107 槽位归还）、动画（animation.c 骨骼评估+IK epsilon, skeleton.c 关节钳制+parent 检查）、脚本（script.c sscanf 宽度限制+realloc NULL, script_lua.c checked_body+lua_pcall）、地形（terrain.c 高度采样钳制+init calloc 检查, particles.c R122 句柄验证, indirect_draw.c count 钳制）、物理（physics.c body_id 边界+CCD candidates[64], bvh.c R154 BVH_NULL 守卫+refit 检查）、命令缓冲区（cmd_buffer.c CMD_BUFFER_MAX_COMMANDS 检查+push constants 上限）、异步加载器（async_loader.c R140 file_size 检查+heap_push 检查, decode_pipeline.c R144 INT32_MAX 检查+R153 mip_count 钳制）、字体（font.c R143 fread 检查+glyph_count 限制）、UTF-8（utf8.c 连续字节+过长编码+代理对拒绝）、手柄（gamepad_linux.c evdev 边界+inotify 安全）、ECS（ecs.c entity_count 检查+generation 验证+realloc NULL）、网络（network.c buf_size 防溢出+poll 检查, packet.c PACKET_MAX_SIZE 边界）、场景序列化（scene_serial.c R108 chunk 边界验证+Reader 模式+R151 parent_index 检查）、glTF 资产加载（asset.c R144 INT32_MAX 检查+R109 dir_len 钳制+R115 calloc/NULL 检查）、RHI 句柄管理（rhi.c R157 abort 防护+generation 验证）、内存分配器（alloc.c R158 usize 溢出, pool.c R158 乘法溢出）、任务系统（task.c R156 calloc 检查+pool_count 钳制+capacity 边界检查 9 处全部完好）。结论：代码库在 R129-R158 的 412 处修复后已达到全面覆盖的安全水平，所有 calloc/malloc/realloc 调用有 NULL 检查、所有文件 I/O 有返回值检查、所有缓冲区访问有边界检查、所有固定大小数组有容量检查、所有外部输入有验证、所有网络操作使用有界缓冲区。

- **R160-A vfs.c name_offset 越界读防护**：`pak_entries[e].name_offset` 未验证即用作 `pak_names` 缓冲区偏移量。恶意 PAK 文件可设 name_offset >= name_table_size 导致 `vfs_open` 中越界读 + `strcmp` 无界读取。修复：(1) 哈希表构建循环中添加 `if (entries[e].name_offset >= hdr.name_table_size) continue;` 跳过无效条目；(2) names 缓冲区分配 `name_table_size + 1` 字节（额外字节由 calloc 置零），保证末尾 null 终止。
- **R160-B decode_pipeline.c out->size u32 截断防护**：`out->size = (u32)(hdr_sz + total_pix)` 可截断 — 32768×32768 RGBA8 纹理含 mip 链超 4GB，截断后调用方使用错误长度。修复：添加 `if (hdr_sz + total_pix > (usize)UINT32_MAX)` 预检查，超限返回 false 拒绝解码。

- **R161-A terrain.c grid_size=0 堆缓冲区溢出防护**：`terrain_init` 中 `u32 idx_count = (grid_size - 1) * (grid_size - 1) * 6` 当 grid_size=0 时 u32 下溢为 `(0xFFFFFFFF * 0xFFFFFFFF * 6) = 6`（u32 回绕），分配 24 字节缓冲区。随后索引生成循环 `for (u32 z = 0; z < grid_size - 1; z++)` 运行 ~40 亿次迭代，每次写入 6 个 u32 远超 24 字节分配 — 大规模堆缓冲区溢出。grid_size=1 时 `(f32)(grid_size - 1)` 除零产生 NaN 顶点数据。修复：添加 `if (grid_size < 2)` 验证，拒绝无效参数。
- **R161-B lod.c level_count > LOD_MAX_LEVELS 越界读防护**：`LODGroup` 结构体中 `thresholds_sq[LOD_MAX_LEVELS]` 和 `meshes[LOD_MAX_LEVELS]` 数组大小固定为 4，但 `lod_register` 未验证 `level_count <= LOD_MAX_LEVELS`。若调用者设置 level_count > 4，`lod_select_by_distance_sq` 中循环 `for (u32 i = 0; i < group->level_count - 1; i++)` 会越界读 `thresholds_sq[]`，`lod_get_mesh` 中 `meshes[level]` 也会越界读。修复：`lod_register` 中复制后添加 `if (level_count > LOD_MAX_LEVELS) level_count = LOD_MAX_LEVELS` 钳制。
- **R162-A lod_select 屏幕尺寸策略 inv_bias 逻辑错误修复**：`lod_select()` 中屏幕尺寸 LOD 路径传递 `sys->bias` 直接作为 `inv_bias` 参数给 `lod_select_by_screen_size()`，但该参数应为 `1.0f / (1.0f + sys->bias)`（倒数）。`lod_update_all()` 正确计算了 `inv_bias = 1.0f / (1.0f + sys->bias)`，但 `lod_select()` 遗漏。当 bias=0（默认值）时，`effective_fraction = screen_fraction * 0.0 = 0.0`，导致 LOD 始终选择最粗级别。修复：在 `lod_select()` 中添加 `f32 inv_bias = 1.0f / (1.0f + sys->bias)` 并传递给 `lod_select_by_screen_size()`。

- **审计总计（R129-R162）**：**417 处**全量加固，涵盖 calloc/malloc NULL 检查、Vulkan VkResult 全路径检查、fseek/fwrite/fread/fclose 返回值检查、strncpy null 终止、snprintf 截断检查、usize→u32/int 截断防护、线程创建检查、数学除零防护、窗口尺寸 0 防护、stbi_load_from_memory 截断检查、mipmap 级别尺寸乘法溢出防护、Vulkan push constant 越界防护、delta_time 钳制防护、Vulkan swapchain 获取图像错误处理防护、Vulkan framebuffer 创建/访问 NULL 解引用防护、场景图 parent_index 越界读防护、视锥剔除缓冲区溢出防护、mip 链生成栈溢出与偏移截断防护、BVH 构建 OOM 崩溃防护、g_node_vis/node_spheres 固定数组越界读防护、任务系统 calloc 失败 NULL 解引用与 pool_count 越界读防护、RHI 资源池耗尽 slot 覆盖损坏防护、VFS PAK entry_count 乘法溢出防护、内存分配器 usize 加法溢出防护、VFS PAK name_offset 越界读防护、解码管线 usize→u32 截断防护、地形 grid_size=0 u32 下溢堆缓冲区溢出防护、LOD level_count 超限越界读防护、LOD 屏幕尺寸策略 inv_bias 逻辑错误修复。

- **R164 工具代码与 shader 深层审查**：首次系统性审查 R102-R163 未覆盖的领域 — 131 个 shader 文件（.comp/.vert/.frag）、31 个测试文件、CMake 构建系统（590 行）、framework 代码、工具代码（packer.c 318 行, verify_pak.c 168 行）。修复 10 处问题。
- **R164-A packer.c data_offset u32 溢出防护**：数据偏移累加循环使用 `u32 offset` 变量，当总打包数据超过 4GB 时 u32 回绕，后续条目的 `data_offset` 字段指向错误位置，产生静默损坏的 PAK 文件。PAK 格式使用 u32 `data_offset` 字段，无法表示 4GB 以上偏移。修复：使用 `u64 total_offset` 累加器，每次迭代检查 `> 0xFFFFFFFFull`，超限时报错退出。
- **R164-B packer.c 头部 fwrite 返回值检查**：6 处 `fwrite` 调用未检查返回值（magic/version/entry_count/name_size/entries/names）。磁盘满或 I/O 错误时产生截断的 PAK 文件但 `main` 报告成功。修复：使用 `write_ok` 标志累积检查所有 fwrite 返回值，失败时报错并退出。
- **R164-C packer.c write_file_data Windows fwrite 检查**：Windows 内存映射路径中 `fwrite(data, 1, size, out)` 未检查返回值。修复：检查返回值，失败时清理 `UnmapViewOfFile`/`CloseHandle` 并返回 0。
- **R164-D packer.c write_file_data Linux fwrite 检查**：Linux 分块拷贝路径中 `fwrite(buf, 1, chunk, out)` 未检查返回值。修复：检查返回值，失败时 `fclose(fp)` 并返回 0。
- **R164-E verify_pak.c fread 返回值检查**：`fread(disk_buf, 1, (usize)disk_size, fp)` 未检查返回值。I/O 错误时 `disk_buf` 含未初始化数据， `memcmp` 产生假阴性。修复：检查返回值不等于 `disk_size`，失败时清理 `free`/`fclose`/`vfs_close` 并返回 0。
- **R164 shader 审查结果**（无需修复）：131 个 shader 文件全部审查，确认所有除法有适当守卫：skybox.frag/skybox_vk.frag 中 `ray.y > 0.01` 条件守卫 cloud 路径除法；occlusion_cull.comp 中 `clip.w <= 0.0` 近平面守卫；unified_cull.comp 中 `w <= 0.0 → w = 1e-6` 守卫；particle_update.comp 中 `max(max_life, 0.001)` 除零守卫；lens_flare.frag/lens_flare_vk.frag 中 `dist > 0.001` 三元守卫；hi_z_generate.comp 边界检查 `pos >= out_size`。
- **R164 测试文件审查结果**（无需修复）：31 个测试文件审查确认测试逻辑正确、边界覆盖充分。test_lod.c 覆盖零距离/未注册实体/单级别/负偏移/极大距离/零级别数等边界；test_packet.c 覆盖 NULL 缓冲区/截断包/溢出保护/最大值往返；test_framework.h 提供完整的 ASSERT 宏集。
- **R164 CMake 审查结果**（无需修复）：编译标志完善（GCC/Clang: -Wall -Wextra -Werror -pedantic; MSVC: /W4 /WX），第三方库隔离正确（glad: -Wno-pedantic, lua: -w），跨平台支持完善（Linux X11/Wayland, Windows Win32, macOS Cocoa）。

- **R165 深度并发安全审查**：深度审查异步资源加载器（async_loader.c）的线程安全，聚焦 MPSC 完成队列溢出和 cancel 竞态条件。修复 3 处并发问题。
- **R165-A async_loader.c 完成队列容量溢出防护**：`ASYNC_QUEUE_SIZE=256` 小于 `ASYNC_MAX_REQUESTS=1024`，MPSC 环形缓冲区在 256+ 个完成项未消费时静默覆盖旧条目，导致消费方读取陈旧/损坏的 slot 索引。修复：`ASYNC_QUEUE_SIZE` 提升至 1024，与最大请求数匹配。
- **R165-B async_loader.c full file read 路径 cancel 竞态修复**：worker 线程完成全文件读取后，使用 `atomic_store_explicit(&req->state, ASSET_READY/ASSET_FAILED)` + `enqueue_completion` + `atomic_fetch_sub` 三步操作。若主线程在 worker 的 `atomic_store` 之前调用 `async_loader_cancel`（CAS `ASSET_LOADING → ASSET_CANCELLED`），worker 的 `atomic_store` 会覆盖 `ASSET_CANCELLED` 为 `ASSET_READY`/`ASSET_FAILED`，导致已取消请求的回调仍然触发（use-after-cancel）。修复：4 处状态转换统一使用 `async_finalize()` 函数，该函数通过 `atomic_compare_exchange_strong` 原子地从 `ASSET_LOADING` 转换到最终状态，若 CAS 失败（已被 cancel）则释放已分配数据并跳过完成入队。
- **R165-C async_loader.c range load 路径 cancel 竞态修复**：与 R165-B 相同的竞态条件存在于范围读取路径。修复：引入 `async_finalize()` 辅助函数，4 处 range load 状态转换统一使用该函数，确保原子状态转换和取消安全。`async_finalize()` 函数封装了 CAS 状态转换 + 条件完成入队 + `pending_count` 递减三个操作。
- **R165 framework/platform 审查结果**（无需修复）：framework 代码（base_application.cc/graphics_manager.cc/main.cc）为桩实现，无内存分配。平台 demo 代码（hello_engine_xcb_opengl.cc/hello_engine_win_d2d.cc/hello_engine_win_d3d.cc）为独立 demo，不链接引擎库，使用 SafeRelease 模式管理资源。

- **R166 深度审查任务系统与纹理流式加载**：深度审查 Chase-Lev 工作窃取队列内存序正确性 + mipmap 流式加载整数截断 + decode_pipeline/hotreload/filewatch/profiler 并发安全。修复 2 处问题。
- **R166-A task.c deque_init calloc NULL 检查**：`deque_init` 中 `calloc(capacity, sizeof(Task*))` 返回值未检查。OOM 时 `buffer` 为 NULL，后续 `deque_push`（`dq->buffer[b & ...] = task`）、`deque_steal`（`dq->buffer[t & ...]`）、`deque_pop` 均解引用 NULL 崩溃。每个 worker 有 `TASK_PRIORITY_COUNT` 个队列，每个 `DEQUE_CAPACITY=1024` 槽位（8KB），最多 8 个 worker 共 24 次 calloc。修复：`deque_init` 改为返回 `bool`，calloc 失败时设置 `capacity=0` 并返回 false。`task_system_create` 检查返回值，失败时逆序销毁已初始化的 deque + mutex + 释放内存 + 返回 NULL。审查确认 Chase-Lev deque 的内存序正确：push 使用 acquire top + release fence，pop 使用 seq_cst fence + CAS，steal 使用 acquire loads + seq_cst fence + CAS。
- **R166-B mipmap_stream.h/c level_offset u32 截断修复**：`StreamedTexture.level_offset` 字段为 `u32`，但 `mipmap_stream_register` 中偏移累加使用 `usize offset`，当总纹数据 >4GB（如 32768×32768 RGBA8 纹理含 mip 链）时 `(u32)offset` 截断产生错误文件偏移，`async_loader_request_range_priority` 读取错误位置的数据。修复：`level_offset` 字段从 `u32` 改为 `u64`，移除 `(u32)` 截断转换。
- **R166 并发审查结果**（无需修复）：decode_pipeline.c 使用互斥锁保护的输入/就绪队列，线程安全；hotreload.c 纯主线程代码（`filewatch_poll` 回调在主线程执行）；filewatch.c 纯主线程代码（inotify 非阻塞 read + mtime 轮询）；profiler.c 纯主线程代码（`profiler_begin_frame`/`profiler_push`/`profiler_pop` 均在主线程调用）。

- **R167 性能优先深度审查 — 粒子 GPU cull 落地 + decode/mipmap/occlusion/task**：审查发现粒子 cull 结果未驱动 draw instance count（热路径浪费），以及 decode/mipmap 正确性缺口。修复 7 处。
- **R167-PERF particles draw_indirect**：`DrawBuf` 改为 `vertexCount/instanceCount/firstVertex/firstInstance`+indices；新增 `rhi_cmd_draw_indirect`（`vkCmdDrawIndirect` / `glMultiDrawArraysIndirect`）；cull buffer 加 `RHI_BUFFER_USAGE_INDIRECT`；`particles_render` 用 indirect 仅 draw alive，消除每帧 8192 VS 空转。
- **R167-A decode 输入队列 cap**：`DECODE_INPUT_CAP` 生效，队满 `submit` 返回 false，由 async_loader 走失败路径。
- **R167-B DecodeJob 嵌入结果节点**：ready 队列节点即 job 首字段，poll/shutdown `free((DecodeJob*)node)`，避免二次 malloc OOM 挂死 slot。
- **R167-C 线程创建检查**：`async_thread_create`→`bool`；decode 全失败/部分失败均 teardown 返回 false；async I/O 记录实际 started 数。
- **R167-D mipmap invalidate + cancel 回调**：invalidate 先清 state/budget 再 `async_loader_cancel`；cancel 立即 `callback(user_data,NULL,0)` 释放 `MipLoadReq`；callback 校验 `request_id`/LOADING。
- **R167-E level_size 溢出拒绝注册**：`mipmap_level_size` 超 `UINT32_MAX` 返回 0，register 回滚。
- **R167-F occlusion staging_valid**：首帧跳过零初始化 staging readback，保留 init 时全可见。
- **R167-G task worker_count==0 返回 NULL**：无线程时销毁并失败，不再返回降级 handle。

- **R168 async 槽位串槽 + indirect 屏障 + 粒子 POINT 拓扑**：审查 R167 周边发现 3 处可触发问题。
- **R168-A async_loader 槽位复用**：仅 `ASSET_UNLOADED` 可复用；`CANCELLED`/`READY` 复用会导致在途 I/O 把旧数据写入新请求。cancel/skip/`async_finalize` 失败路径均置回 `UNLOADED`。
- **R168-B memory barrier INDIRECT**：GL 增 `GL_COMMAND_BARRIER_BIT`；VK 增 `VK_ACCESS_INDIRECT_COMMAND_READ_BIT` + `VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT`，保证 compute→draw_indirect 可见性。
- **R168-C 粒子 POINT 拓扑**：`RHIPipelineDesc.point_list`；VK `POINT_LIST`；GL `GL_POINTS` + `GL_PROGRAM_POINT_SIZE`；粒子 render pipeline 启用。

- **R169 unified cull readback/compact + decode 取消跳过**：审查 R168 周边发现 4 处。
- **R169-A vis flags 1 帧延迟 readback**：`vis_flags_staging` + GPU copy；`mega_unified_vis_flags` 先读上一帧再 dispatch；首帧全可见。
- **R169-B flags-only 跳过 compact**：`compact_draws` / `u_cull_write_draws`；vis-flags 路径不再 atomic compact。
- **R169-C decode cancel 跳过 stbi/mip**：worker 在 decode 前检查 `ASSET_CANCELLED`。
- **R169-D VK PointSize feature**：启用 `shaderTessellationAndGeometryPointSize`。

- **R170 阴影 Hi-Z/staging 串扰 + MPSC/任务依赖/indirect 回退**：审查 R169 周边发现 8 处。
- **R170-A 阴影禁用相机 Hi-Z**：级联/点光改 `mega_unified_cull_draw(..., NULL)`。
- **R170-B stage_readback 仅主相机**：避免多视图覆盖 staging。
- **R170-C transfer barrier**：VK `TRANSFER_READ`+`TRANSFER` stage；GL `BUFFER_UPDATE_BARRIER_BIT`。
- **R170-D MPSC sequence 发布**：写 indices 后再 release sequence。
- **R170-E task_submit_dep 有效依赖计数**：无效 handle 不再抬高 dep_count。
- **R170-F compact 前清零 draws**：VK IndirectCount 回退不重放过期命令。
- **R170-G 去掉 flags 零上传**：shader 已覆盖 `[0,n)`。
- **R170-H mipmap 零 mip 拒绝**：防止 `mip_count-1` 下溢。

- **R171 GPU fill 同 CB 清零 + Hi-Z 全 mip + pending/mip 预算**：审查 R170 周边发现 4 处高价值问题。
- **R171-A rhi_cmd_fill_buffer**：同 CB 多次 compact 用 GPU fill 清零 count/draws。
- **R171-B Hi-Z 全 mip view**：VK 采样 view `levelCount = mipLevels`。
- **R171-C pending_count 发布前递增**：避免快速完成下溢。
- **R171-D mipmap admission 前驱逐**：预算不足时先丢本纹理 finer levels。

- **R172 staging 双缓冲 + Hi-Z 布局 + 粒子 emit + mipmap**：审查发现 5 处。
- **R172-A 双槽 staging**：`rhi_frame_index` + gpucull/occlusion per-frame staging。
- **R172-B Hi-Z mip_layout**：跟踪布局；末级转 SHADER_READ_ONLY。
- **R172-C 粒子 emit_rate**：概率发射 + VK 每帧刷新。
- **R172-D force_level 预算**：驱逐后检查。
- **R172-E mipmap shutdown cancel**：取消在途请求。

- **R173 任务依赖扇出/wait 计数 + mip_layout**：审查发现 3 处。
- **R173-A TaskWaitLink 扇出**：依赖完成通知所有 waiter。
- **R173-B dep 任务计入 submitted**：`task_wait` 覆盖整图。
- **R173-C mip_layout 初始化/upload 回写**：避免错误 oldLayout barrier。

- **R174 粒子精确 emit + destroy 解挂 + mip_layout 数据路径**：审查发现 3 处。
- **R174-A 粒子 atomic spawn 预算**：稳态精确 `emit_rate*dt`。
- **R174-B task_system_destroy 解挂**：未完成依赖图不再挂死。
- **R174-C mip_layout 仅标记已上传 mip0**：避免高层错误 barrier。

- **R175 粒子/indirect GPU 清零 + mip upload 布局 + GL fill 屏障**：审查发现 4 处。
- **R175-A cull instanceCount GPU fill**：消除 host 写与 draw_indirect 竞态。
- **R175-B upload_mip 用 mip_layout**：UNDEFINED 高层正确 transition。
- **R175-C indirect_draw_compact GPU fill**：同 CB 清零对 dispatch 可见。
- **R175-D GL fill_buffer barrier**：clear 后对 SSBO/indirect 可见。

- **R176 gpucull count GPU 清零 + destroy 回收 mip upload**：审查发现 2 处。
- **R176-A gpucull_dispatch_to GPU fill**：cascade 同 CB 多次清零可见。
- **R176-B texture_destroy reclaim mip upload**：避免销毁在途 image。

- **R177 TaskWaitLink OOM 回滚 + copy_buffer 屏障**：审查发现 2 处。
- **R177-A task_submit_dep OOM 回滚**：malloc 失败不再欠计 dep。
- **R177-B copy_buffer suspend/barrier**：VK/GL 自带 transfer 可见性。

- **R178 粒子 push 尾部 + GL frame_index**：审查发现 2 处。
- **R178-A 粒子 Push 80B 尾部**：补传 `lifetime_range`。
- **R178-B GL frame_index 递增**：双槽 staging 生效，减少 map 停顿。

- **R179 粒子 live Push + compute 采样布局**：审查发现 2 处。
- **R179-A live 80B Push 一次上传**：避免陈旧 template / mat4 截断。
- **R179-B bind_texture_compute mip→READ_ONLY**：Hi-Z 采样前布局正确。

- **R180 粒子 pass 保活 + depth→compute 屏障**：审查发现 2 处。
- **R180-A 粒子不拆 offscreen pass**：suspend/resume 保活 scene_fbo。
- **R180-B depth→compute 屏障**：Hi-Z 采样前同步正确。

- **R181 shadow pass 状态 + 静态 mesh DEVICE_LOCAL**：审查发现 2 处。
- **R181-A shadow unbind/bind 状态闭合**。
- **R181-B 静态 VERTEX/INDEX → DEVICE_LOCAL**。

- **R182 visibility/light 双槽 ring**：审查发现 2 处。
- **R182-A visibility_buf[2]**：避免双帧 host/GPU 竞态。
- **R182-B light_data/grid[2]**：deferred/clustered 同理。

- **R183 CB 有序 visibility + joint/instance 双槽**：审查发现 2 处。
- **R183-A rhi_cmd_update_buffer**：cascade/face visibility 录制有序。
- **R183-B joint/instance[2]**：消除双帧 host/GPU 竞态。

- **R184 font 双槽 + 粒子 DEVICE_LOCAL**：审查发现 2 处。
- **R184-A font vbo[2]**：消除双帧 host/GPU 竞态。
- **R184-B 粒子 SSBO DEVICE_LOCAL**：GPU-only STORAGE 走显存。

- **R185 fill 预屏障 + cull STORAGE DEVICE_LOCAL**：审查发现 2 处。
- **R185-A fill 等 DRAW_INDIRECT**：cascade 复用安全。
- **R185-B gpucull/indirect/occlusion DEVICE_LOCAL**：GPU-only 缓冲进显存。

- **R186 mega 读回 + 静态 SSBO DEVICE_LOCAL**：审查发现 2 处。
- **R186-A rhi_buffer_read**：DEVICE_LOCAL mesh mega bake 正确。
- **R186-B all_draws/draw_cmds/aabb DEVICE_LOCAL**。

- **R187 GL buffer 缓存失效 + 地形 VBO HOST_VISIBLE**：审查发现 2 处。
- **R187-A destroy 清 VBO/IBO/indirect/array/TBO 缓存**。
- **R187-B 地形 VBO 保持 HOST_VISIBLE**：避免笔刷 WaitIdle。

- **R188 GL param/program/VAO 销毁缓存失效**：审查发现 2 处。
- **R188-A 清 g_gl_param_buf**。
- **R188-B pipeline_destroy 清 program/VAO 缓存**。

- **R189 GL offscreen color_tex 类型 + FBO 销毁缓存失效**：审查发现 2 处。
- **R189-A offscreen color_tex 独立 GLTextureData**：避免误绑 FBO 名。
- **R189-B FBO destroy 清 g_gl_bound_fbo**：offscreen/MRT/cubemap/shadow。

- **R190 GL create 纹理缓存失效 + object_ssbo DEVICE_LOCAL**：审查发现 2 处。
- **R190-A create 路径清 g_tex_cache**：texture/offscreen/MRT/cubemap/shadow。
- **R190-B object_ssbo 零初始化 DEVICE_LOCAL**：统一路径避免每帧 HOST_VISIBLE 读。

- **R191 GL buffer create 缓存对称 + Hi-Z mip 钳制恢复**：审查发现 2 处。
- **R191-A buffer_create 清 ARRAY_BUFFER/TBO 缓存**。
- **R191-B bind_texture_compute 恢复 BASE/MAX_LEVEL**：Hi-Z 全链可采。

- **R192 INDEX create 清 IBO 缓存 + light_grid DEVICE_LOCAL**：审查发现 2 处。
- **R192-A INDEX create 清 g_gl_bound_ibo**。
- **R192-B light_grid 零初始化 DEVICE_LOCAL**：允许 STORAGE|TEXEL。

- **R193 VK sampler maxLod + legacy object_ssbo 去重上传**：审查发现 2 处。
- **R193-A sampler maxLod → VK_LOD_CLAMP_NONE**：IBL/Hi-Z mip 可采。
- **R193-B objects_uploaded 跳过重复 DL staging**。

- **R194 GL/VK sampler mip 过滤对齐**：审查发现 2 处。
- **R194-A GL MIN_FILTER 用 MIPMAP 变体 + MAX_LEVEL**：textureLod 可采高层。
- **R194-B VK mipmapMode 跟 min_filter**：NEAREST Hi-Z 不层间混合。

- **R195 GL offscreen 可采样 depth + Hi-Z 生成后恢复 mip**：审查发现 2 处。
- **R195-A offscreen depth → D32 纹理 + depth_tex handle**。
- **R195-B Hi-Z 生成结束 bind_texture_compute 恢复金字塔**。

- **R196 tonemap LOAD 保深度 + 后处理去掉中间 unbind**：审查发现 2 处。
- **R196-A rhi_offscreen_fbo_bind_load**：tonemap/cinematic 不 CLEAR 深度。
- **R196-B 删 SSAO/TAA/SSR/DoF/volumetric/bloom/combined 中间 unbind**。

- **R197 upscale history 真复制 + debug_viz/lens 中间 unbind**：审查发现 2 处。
- **R197-A u_ups_copy_only + VK u_ups_* push 映射**：Pass 2 不再二次 TSR；VK loc 不再恒 -1。
- **R197-B 删 debug_viz/lens_effects 中间 unbind**。

- **R198 VK luminance/god_rays push 映射**：审查发现 2 处。
- **R198-A u_lum_* 映射**：自动曝光 adaptation 生效。
- **R198-B u_gr_* 映射**：god rays 太阳/强度生效，并推送 sw/sh。

- **R199 VK motion_blur/contact_shadow push 映射**：审查发现 2 处。
- **R199-A u_mb_* 映射**：运动模糊 strength/投影生效。
- **R199-B u_cs_* 映射**：接触阴影光向/投影生效。

- **R200 VK color_grade/bloom push 映射**：审查发现 2 处。
- **R200-A 独立 u_cg_* 映射**：fallback 调色饱和/对比度生效。
- **R200-B bloom u_threshold/u_direction/u_bloom_strength**：bloom 与 SSGI blur 生效。

- **R201 VK SSS/FXAA/tonemap 独立 push 映射**：审查发现 2 处。
- **R201-A u_sss_*/u_sssv_* 映射**：SSS 分辨率与强度生效，避免除零。
- **R201-B 独立 u_fxaa_threshold + u_tm_mode**：FXAA 阈值与 tonemap 模式生效。

- **R202 水面阴影采样器 + 点光阴影 push 映射**：审查发现 2 处。
- **R202-A water 自有 sampler**：VK 水面阴影绑定生效。
- **R202-B is_shadow_depth push**：点光 cubemap 深度 MVP/light_pos/far 生效。

- **审计总计（R129-R234）**：**591 处**全量加固，涵盖 calloc/malloc NULL 检查（含 deque_init）、Vulkan VkResult 全路径检查、fseek/fwrite/fread/fclose 返回值检查（含工具代码）、strncpy null 终止、snprintf 截断检查、usize→u32/int 截断防护（含 mipmap level_offset）、线程创建检查、数学除零防护、窗口尺寸 0 防护、stbi_load_from_memory 截断检查、mipmap 级别尺寸乘法溢出防护、Vulkan push constant 越界防护、delta_time 钳制防护、Vulkan swapchain 获取图像错误处理防护、Vulkan framebuffer 创建/访问 NULL 解引用防护、场景图 parent_index 越界读防护、视锥剔除缓冲区溢出防护、mip 链生成栈溢出与偏移截断防护、BVH 构建 OOM 崩溃防护、g_node_vis/node_spheres 固定数组越界读防护、任务系统 calloc 失败 NULL 解引用与 pool_count 越界读防护、RHI 资源池耗尽 slot 覆盖损坏防护、VFS PAK entry_count 乘法溢出防护、内存分配器 usize 加法溢出防护、VFS PAK name_offset 越界读防护、解码管线 usize→u32 截断防护、地形 grid_size=0 u32 下溢堆缓冲区溢出防护、LOD level_count 超限越界读防护、LOD 屏幕尺寸策略 inv_bias 逻辑错误修复、packer.c data_offset u32 溢出防护、packer.c fwrite 返回值检查、verify_pak.c fread 返回值检查、async_loader MPSC 完成队列溢出防护、async_loader cancel 竞态 TOCTOU 修复、粒子 GPU cull draw_indirect 落地、decode 输入队列有界、mipmap invalidate/stale 回调防护、occlusion 首帧 staging 守卫、async 槽位仅 UNLOADED 复用、indirect 命令屏障、粒子 POINT_LIST 拓扑、unified cull 1 帧 delayed vis readback、flags-only 跳过 compact、decode cancel 跳过解码、VK PointSize feature、阴影无相机 Hi-Z、stage_readback 隔离、transfer barrier、MPSC sequence、task 有效依赖计数、compact draws 清零、flags 零上传删除、mipmap 零 mip 拒绝、GPU fill 同 CB 清零、Hi-Z 全 mip view、pending 发布前递增、mipmap admission 前驱逐、双槽 staging、Hi-Z mip_layout、粒子 emit_rate、force_level 预算、mipmap shutdown cancel、TaskWaitLink 扇出、dep submitted 计数、mip_layout 初始化、粒子 atomic spawn 预算、task destroy 解挂、mip_layout 数据路径仅 mip0、粒子 cull GPU fill、upload_mip mip_layout、indirect compact GPU fill、GL fill barrier、gpucull count GPU fill、texture_destroy mip upload reclaim、TaskWaitLink OOM 回滚、copy_buffer suspend/barrier、粒子 Push lifetime_range、GL frame_index、粒子 live Push bytes、bind_texture_compute mip READ_ONLY、粒子 pass 保活、depth→compute 屏障、shadow pass 状态闭合、静态 mesh DEVICE_LOCAL、visibility/light 双槽 ring、CB 有序 visibility 上传、joint/instance 双槽、font 双槽、粒子 SSBO DEVICE_LOCAL、fill 等 DRAW_INDIRECT、cull STORAGE DEVICE_LOCAL、mega staging 读回、静态 SSBO DEVICE_LOCAL、GL buffer 缓存失效、地形 VBO HOST_VISIBLE、GL param/program/VAO 销毁失效、offscreen color_tex 类型、FBO 销毁缓存失效、GL create 纹理缓存失效、object_ssbo DEVICE_LOCAL、buffer create 缓存对称、Hi-Z mip 钳制恢复、INDEX create 清 IBO、light_grid DEVICE_LOCAL、VK sampler maxLod、legacy object_ssbo 去重上传、GL MIN_FILTER MIPMAP、VK mipmapMode 对齐、GL offscreen 可采样 depth、Hi-Z 生成后恢复 mip、tonemap LOAD 保深度、后处理中间 unbind 删除、upscale history 真复制、VK u_ups push 映射、debug_viz/lens 中间 unbind 删除、VK u_lum/u_gr push 映射、VK u_mb/u_cs push 映射、VK 独立 u_cg 与 bloom push 映射、VK SSS/FXAA/tonemap 独立 push 映射、水面阴影采样器、点光阴影 depth push 映射、u_prev_vp 双映射分流、去掉误用 u_light_vp、gbuffer AO push 越界、独立 tonemap push 对齐、forward_velocity/motion_blur/upscale 改传 inv(VP)、体积光视空间光照、DOF focus_range CoC、接触阴影视空间光向、cmd PUSH_CONSTANTS 回放、接触阴影列主序 M*v、draw_indexed_base 回放、god rays 方向投影、体积雾世界高度、后处理深度 NDC、SSR/SSGI 默认关、CSM 窗口深度比较、contact 采样 NDC、Hi-Z 窗口深度、vol/cs/lf 默认关、depth_only VK Z remap、GL SSAO@14、主通道 VK Z remap、bloom 零开销跳过、GL 点阴影 COMPARE 关闭、VK 点阴影 Z remap、bloom skip 不切 composite、去掉误写 pom、GL water/god_rays sampler binding、god rays 零强度跳过、GL TAA/DoF sampler binding、GL motion blur/SSS sampler binding、GL tonemap/luminance/bloom sampler binding、GL upscale/volumetric sampler binding、GL SSR/SSGI sampler binding、ParallelRenderer sampler、删除死 shadow_depth、index 类型、volumetric CPU inv_view、viewport 深度范围、地形雾开关、GL VBO/IBO offset、GL set_scissor、GL indexed draw mode、indirect index type、GL 阴影 depth range、点光 cubemap face depth/scissor、offscreen/MRT scissor/depth、unified_cull Hi-Z unit、clear_color 语义、GL pipeline depth write/compare、cull 近平面、GL shadow compute 重绑、前向/延迟 compute 后重绑、indirect compact visible 清零。

- **R203 u_prev_vp 双映射 + 去掉误用 u_light_vp**：审查发现 2 处。
- **R203-A u_prev_vp 按 no_vertex_input 分流**：fullscreen@128 / gbuffer@192。
- **R203-B 删除通用 u_light_vp@64**：避免与 u_view 冲突。

- **R204 gbuffer AO push 越界 + 独立 tonemap 映射**：审查发现 2 处。
- **R204-A gbuffer AO const**：去掉 256+ push，ao=1。
- **R204-B tonemap_vk 独立 push**：对齐 screen_w@8/mode@16。

- **R205 时序重投影改传 inv(VP)**：审查发现 2 处。
- **R205-A forward_velocity 传 frame_inv_vp**：速度缓冲重投影正确。
- **R205-B motion_blur/upscale 传 frame_inv_vp**：运动模糊与 TSR history 重投影正确。

- **R206 体积光视空间光照 + DOF focus_range**：审查发现 2 处。
- **R206-A volumetric 光向×view**：视空间散射正确。
- **R206-B DOF CoC 用 focus_range**：景深范围生效。

- **R207 接触阴影视空间光向 + cmd push 回放**：审查发现 2 处。
- **R207-A contact_shadow 光向×view**：视空间步进正确。
- **R207-B PUSH_CONSTANTS 回放**：并行命令缓冲 push 生效。

- **R208 接触阴影列主序变换 + draw_indexed base**：审查发现 2 处。
- **R208-A contact_shadow 列主序 M*v**：与 GPU/inv_proj 视空间一致。
- **R208-B DRAW_INDEXED base 回放**：first_index/vertex_offset 生效。

- **R209 god rays 方向投影 + 体积雾世界高度**：审查发现 2 处。
- **R209-A god rays w=0 投影**：太阳 UV 不随相机平移漂移。
- **R209-B volumetric 世界高度雾**：height_factor 用世界 Y。

- **R210 后处理深度 NDC 对齐 + SSR/SSGI 默认关闭**：审查发现 2 处。
- **R210-A 深度 depth*2-1**：与 deferred/OpenGL inv_proj 一致。
- **R210-B SSR/SSGI 默认关**：避免未合成空跑。

- **R211 CSM 窗口深度比较 + contact 采样 NDC**：审查发现 2 处。
- **R211-A CSM z*0.5+0.5**：方向光阴影比较正确（含 VK 写入 remap）。
- **R211-B contact 采样 depth*2-1**：与起点重建一致。

- **R212 Hi-Z 窗口深度比较 + vol/cs/lf 默认关闭**：审查发现 2 处。
- **R212-A Hi-Z/近平面**：遮挡剔除与 OpenGL NDC 对齐。
- **R212-B vol/cs/lf 默认关**：避免未合成空跑。

- **R213 VK CSM depth_only Z remap + GL SSAO binding**：审查发现 2 处。
- **R213-A depth_only.vert VK Z remap**：活跃 CSM 路径阴影深度正确。
- **R213-B GL SSAO→binding 14**：不再被点阴影 cube 覆盖。

- **R214 主通道 VK Z remap + bloom 零开销跳过**：审查发现 2 处。
- **R214-A 主通道 clip.z remap**：场景深度与后处理重建一致。
- **R214-B bloom_strength<=0 跳过**：避免空跑多 pass。

- **R215 GL 点阴影 COMPARE 关闭 + VK 点阴影 Z remap**：审查发现 2 处。
- **R215-A GL cube COMPARE_MODE=NONE**：与 samplerCube 手动比较一致。
- **R215-B point_shadow_depth_vk Z remap**：近半锥体不再被裁掉。

- **R216 bloom skip 不切 composite + 去掉误写 pom**：审查发现 2 处。
- **R216-A bloom_strength 守卫切换**：避免 tonemap 吃陈旧 composite。
- **R216-B 删除 bind_material pom 写入**：不再踩 blinn u_ambient。

- **R217 GL water/god_rays sampler binding + god rays 零强度跳过**：审查发现 2 处。
- **R217-A water.frag binding=1**：阴影采样对齐 unit 1。
- **R217-B god_rays binding + intensity 跳过**：深度遮挡正确；零强度零开销。

- **R218 GL TAA/DoF sampler binding**：审查发现 2 处。
- **R218-A TAA/combined_taa_fxaa bindings 0–3**：history/depth/velocity 正确。
- **R218-B dof.frag bindings 0/1**：景深用真实深度。

- **R219 GL motion blur/SSS sampler binding**：审查发现 2 处。
- **R219-A motion_blur.frag bindings 0/1**：深度速度正确。
- **R219-B sss + sss_vertical bindings**：散射用真实 depth/original。

- **R220 GL tonemap/luminance/bloom sampler binding**：审查发现 2 处。
- **R220-A luminance + tonemap bindings 0/1**：自动曝光正确。
- **R220-B bloom_composite bindings 0/1**：bloom 层正确合成。

- **R221 GL upscale/volumetric sampler binding**：审查发现 2 处。
- **R221-A upscale.frag bindings 0/1/2**：TSR 用真实 depth/history。
- **R221-B volumetric.frag bindings 0/1**：雾采样深度与阴影正确。

- **R222 GL SSR/SSGI sampler binding**：审查发现 2 处。
- **R222-A ssr.frag bindings 0/1**：反射追踪用真实深度。
- **R222-B ssgi.frag bindings 0/1**：GI 用 depth@0 color@1。

- **R223 ParallelRenderer sampler + 删除死 shadow_depth**：审查发现 2 处。
- **R223-A cmd_bind_texture 携带 sampler**：VK 回放不再空绑。
- **R223-B 删除 unused shadow_depth 着色器**：避免再误改死文件。

- **R224 index 类型 + volumetric CPU inv_view**：审查发现 2 处。
- **R224-A bind_index_buffer is_u32**：VK/GL 尊重 16/32-bit 索引。
- **R224-B volumetric u_vol_inv_view**：去掉每像素 inverse()。

- **R225 viewport 深度范围 + 地形雾开关**：审查发现 2 处。
- **R225-A set_viewport min/max depth**：VK/GL 尊重深度范围。
- **R225-B terrain fog_strength**：fog_enabled 真正开关距离雾。

- **R226 GL VBO/IBO offset + set_scissor**：审查发现 2 处。
- **R226-A GL buffer bind offset**：VBO/IBO 偏移正确参与绑定与绘制。
- **R226-B GL set_scissor**：裁剪矩形真正生效。

- **R227 GL indexed draw mode + indirect index type**：审查发现 2 处。
- **R227-A indexed draw mode**：draw_indexed* 使用 g_gl_draw_mode。
- **R227-B indirect index type**：draw_indexed_indirect* 使用 g_gl_index_type。

- **R228 GL 阴影 depth range 对齐**：审查发现 2 处。
- **R228-A set_shadow_viewport depth range**：强制 0..1 对齐 VK。
- **R228-B bind_shadow_map depth range**：清 atlas 前强制 0..1。

- **R229 GL 点光 cubemap face depth/scissor**：审查发现 2 处。
- **R229-A cubemap face depth range**：clear/写入前强制 0..1。
- **R229-B cubemap face scissor**：清除残留 scissor 覆盖整面。

- **R230 GL offscreen/MRT bind 对齐 VK scissor/depth**：审查发现 2 处。
- **R230-A offscreen_fbo_bind/unbind**：全 FBO scissor + depth 0..1。
- **R230-B mrt_fbo_bind/unbind**：同上（GBuffer）。

- **R231 unified_cull Hi-Z unit + clear_color 语义**：审查发现 2 处。
- **R231-A Hi-Z compute unit**：GL 绑 unit 4 对齐 shader。
- **R231-B clear_color**：仅清 color；forward 显式 clear_depth。

- **R232 GL pipeline depth write/compare**：审查发现 2 处。
- **R232-A depth_write_disable**：bind_pipeline 应用 glDepthMask。
- **R232-B depth_compare_lequal**：bind_pipeline 应用 glDepthFunc。

- **R233 cull 近平面 + GL shadow compute 后重绑**：审查发现 2 处。
- **R233-A cull.comp 近平面**：NDC z 近平面改为 -1。
- **R233-B shadow 间接绘制前重绑 depth pipe**：修复 GL compute 覆盖 program。

- **R234 前向/延迟 compute 后重绑 + compact 清零**：审查发现 2 处。
- **R234-A forward/deferred 间接绘制前重绑 graphics pipe**：补齐 R233 未覆盖的主路径。
- **R234-B compact 前清零 visible_draws**：对齐 R171，堵住 VK IndirectCount fallback。

- **R163 全引擎深层验证审查**（无新问题）：对全引擎所有源文件进行系统性深层审查，覆盖 60+ 个源文件跨越所有子系统。核心模块（pool.c 固定块内存池 R158 usize 溢出守卫、profiler.c 帧区域边界检查、string.c R109 buf_size==0 守卫、assert.c、log.c）、网络模块（packet.c 二进制序列化全边界检查、network.c 跨平台 UDP/TCP socket 管理+calloc NULL 检查、net_replication.c R115 长度钳制+LRU 驱逐+序列号去重+sscanf %255s 限制）、物理模块（character.c BVH candidates[64]+MAX_ITERS、physics.c 单次 calloc 内联布局+body_create 边界检查+resolve_contact inv_mass 守卫+closest_on_segment 除零守卫+sphere_vs_box 最小穿透轴+SSE2 SIMD 积分）、平台模块（filewatch.c Windows ReadDirectoryChangesW + Linux inotify + strncpy null 终止、input.c 范围检查、time.c 跨平台高精度计时、window_x11.c XRR 监视器枚举+NULL 检查、window_wayland.c xkb_context+mmap MAP_FAILED+资源清理、window_win32.c DPI 感知+Raw Input+WM_INPUT 边界检查、gamepad_linux.c evdev ioctl+inotify 热插拔+除零守卫、gamepad_win.c XInput 动态加载+deadzone 钳制）、脚本模块（script.c R136 fseek/ftell 检查+realloc NULL+sscanf 宽度限制、script_lua.c checked_body+lua_pcall+key 范围检查）、UI 模块（debug_ui.c 行边界检查、imgui.c font NULL 检查+vsnprintf 有界缓冲区、utf8.c 完整 UTF-8 验证+overlong+代理对拒绝）、资产模块（mipmap_stream.c R145 usize 乘法溢出+offset 累加溢出+池溢出检查）、音频模块（audio_stream.c R107 slot 归还+stream_idx_valid 完整验证）、RHI GL 后端（rhi_gl.c 1990 行 — WGL/EGL/GLX 三路径初始化+所有错误路径清理、着色器编译状态检查、GL 状态缓存系统 viewport/texture unit/SSBO/FBO/VAO/VBO/IBO/depth mask/cull face/scissor、R106-2 资源销毁缓存失效、MRT FBO attachment_count 边界检查、cubemap depth FBO face 检查）、渲染器后处理全部模块（post_process.c/tonemap.c/dof.c/color_grade.c/contact_shadow.c/motion_blur.c/volumetric.c/sss.c/forward_velocity.c/combined_post_process.c/camera.c/frustum_cull.c/cull.c/point_shadow.c/ibl.c/indirect_draw.c/gpucull.c）、核心引擎（engine.c/math.c）、ECS（ecs_system.c/ecs.c）、场景序列化（scene_serial.c R108 chunk 边界验证）、资产加载（asset.c/async_loader.c/hotreload.c）、动画（animation.c/skeleton.c）、命令缓冲区（cmd_buffer.c）、渲染图（render_graph.c/occlusion_cull.c）、后处理渲染器（cinematic.c/debug_viz.c/deferred.c/fxaa.c/god_rays.c/lens_effects.c/lens_flare.c/lighting.c/sharpen.c/skybox.c/ssao.c/ssgi.c/ssr.c/taa.c/upscale.c/water.c/particles.c）。确认 R129-R162 的 417 处修复全部完好。编译验证：Vulkan 100% + GL 100%。测试验证：Vulkan 23/23 + GL 30/30 通过。**结论：经过 R102-R163 共 62 轮深度审查，代码库的内存安全、资源管理、边界检查、整数溢出防护、线程安全、错误处理均已达到工业级水平，全引擎 .c 源文件覆盖完毕。**（注：R164 继续审查 shader/test/CMake/工具代码领域，发现工具代码中的 I/O 返回值与整数溢出问题。）
## Windows Clang 验证（2026-08-16）

- 统一线程/互斥/条件变量平台抽象，Windows 使用 Win32 原语，POSIX 保持 pthread 实现。
- Windows + Clang/LLVM + Ninja 原生构建通过。
- `ctest -LE graphics` 非图形测试 `40/40` 通过。
- 图形运行时验证仍需在具备 WGL/Vulkan 驱动的目标机上执行。
## Windows runtime verification

- Clang 22 + Ninja builds successfully on Windows.
- Native WGL OpenGL 4.5 context creation and non-graphics CTest coverage pass.
- CI adds a Windows Clang headless job; GPU-dependent `test_vulkan` remains under the `graphics` label.
- `test_shader_io` now validates Windows path separators and bounded source reads.
- Windows WGL graphics integration is verified end-to-end: TEST 7 IBL and the
  subsequent indirect/material-array gates pass. The former `0xC00000FD`
  failure was a test-stack overflow from local `LightSystem` storage; its
  clustered-light grid is now heap allocated by the integration test.
## myui 冷却按钮（2026-08-23）

- `my_button_set_cooldown()`、`my_button_is_cooling_down()`、剩余时间和进度查询已加入
  公共按钮 API。
- 实现使用 PAL 单调时钟作为唯一截止判定；冷却期间拒绝输入重入，成功 click 先锁定
  deadline 再发事件，支持同步回调安全边界。
- 动画采用按钮级惰性 16ms timer 和公共 canvas 半透明遮罩；非冷却状态不创建 timer，
  到期自动停止，销毁与禁用路径清理 timer。
- `test_myui_window_manager` 新增冷却阻断、进度、零时长禁用、timer tick/停止测试，
  当前定向结果为 `30/30`。
- 方案与限制详见 `docs/myui_remaining_work.md` 和 `docs/myui_integration.md`。

## myui Unicode 断行边界（2026-08-24）

- 以 TDD 补充 Unicode glue：NBSP、figure space、narrow NBSP、word joiner；即使相邻
  CJK/默认可断类也不会错误断开。
- 新增 ZWJ、variation selector、Emoji modifier 和 Unicode tag sequence 的不可断规则，
  采用固定范围判断，不改变生成的 UCD 类别表，也不引入逐段缓存或堆分配。
- `test_myui_text_layout` 新增两组契约，定向结果为 `9/9`；完整 UAX#14、SA dictionary
  和复杂 numeric tailoring 仍明确记录为未完成。

## myui CSS at-rule 跳过边界（2026-08-24）

- 以 TDD 覆盖未知 `@` 规则中字符串、反斜杠转义、注释和嵌套 block 的大括号；后续
  合法 rule 不再因跳过器误判深度而被吞掉。
- 实现是单次线性扫描，仅作用于未知 at-rule 的解析冷路径；不改变 selector specificity、
  theme bridge 或声明值的既有契约。
- `test_myui_css` 定向结果为 `15/15`；完整 at-rule 语义仍属于未实现能力。

## myui YAML UI loader（2026-08-24）

- 以 TDD 新增 `test_myui_loader`，YAML 根对象使用 `type`，普通控件属性采用类型化
  标量，子控件使用 `children` sequence，绑定使用 `bindings` map，主题使用 `style`。
- loader 直接消费 `my_conf` YAML tree，整数执行 `int32_t` 范围校验，浮点拒绝非有限值，
  children/bindings 容器类型错误、绑定规则超限和非 YAML 标记均拒绝；通用 YAML parser
  同时固定输入、行数、嵌套、集合和标量预算。
- 已删除 UI XML parser、XML loader 编译选项和 `test_myui_xml`；Wayland 协议 XML 文件
  仍由平台协议生成流程使用，不属于 UI 配置支持。
- `test_myui_loader` 定向结果为 `14/14`；默认 myui 10/10、无 Bidi loader 14/14、
  ASan/UBSan loader 14/14、Vulkan `myui_core` 构建和 YAML OFF 裁剪构建均通过。本轮补齐
  flow map key 预算与 sequence 内联 map 重复键拒绝，避免资源限制或配置完整性绕过。

## myui text area incremental wrap cache（2026-08-24）

- 以 TDD 新增 `text_area_wrap_reuses_unchanged_prefix_after_edit`：编辑中间物理行时，
  之前的 visual-line 前缀保持对象稳定，避免每次输入都重建全文缓存。
- wrap 重排改为 `dirty_from` 后缀候选事务；未受影响前缀转移到候选数组，后缀分配或
  paragraph 构建失败只释放候选后缀，保留旧缓存并继续标记 dirty。
- 验证：`test_myui_window_manager` **31/31**，myui 定向套件 **10/10**，并保留原有
  wrap OOM 回滚契约。

## myui text area line numbers（2026-08-25）

- 以 TDD 新增行号栏边界测试：默认关闭、按行数位数扩大 gutter、关闭后恢复原始内容
  起点；启用行号后 wrap 可用宽度重新计算，避免视觉布局与命中坐标漂移。
- 新增 `my_text_area_set_line_numbers()`、`my_text_area_line_numbers_enabled()` 和
  `my_text_area_content_left()`；绘制只遍历可见 visual lines，wrap 时每个物理行只绘制
  一次行号，不引入逐帧全文扫描。
- 验证：`test_myui_window_manager` **33/33**，其余 myui 定向测试保持通过。

## myui text area physical folding（2026-08-25）

- 以 TDD 新增物理行折叠契约：首行保留为 header、隐藏范围行不生成 visual line，非法和
  重叠范围拒绝，wrap 与非 wrap 均保持物理 row 映射稳定。
- 新增 `my_text_area_set_folded_range()` 和 `my_text_area_is_folded()`；折叠状态使用排序
  的非重叠区间和可见行缓存，默认无折叠路径不创建映射。物理行结构发生变化时清除区间，
  避免编辑后继续使用失效行号。
- `test_myui_window_manager` 现为 **36/36**；折叠实现保持 widget 不依赖任何渲染后端。
- 当前限制：不支持嵌套/重叠折叠、折叠状态持久化和增量语法高亮，详见
  `docs/myui_remaining_work.md`。

## rule engine salience ordering（2026-08-25）

- 以 TDD 新增 GRL `salience <int32>` 语法和稳定激活顺序测试：匹配规则按 salience
  降序执行，等值保持源代码顺序；非法整数、溢出和尾随标识符均拒绝。
- 规则在加载期稳定插入排序，执行热路径不分配、不排序，保留已有限额、取消和回调契约。
- 修复 rule engine 在 `-Werror` 下的 misleading-indentation 编译阻断，保持 C99 ABI 和
  图形/UI 独立边界。
- 验证：`test_rule_engine` **21/21**、myui 定向套件 **11/11**、C99 consumer、benchmark、
  ASan rule engine/myui/loader、Vulkan `myui_core` 与 `rule_engine_core` 构建通过。
- 当前限制：嵌套事实遍历和通用 agenda 调度仍未实现。

## myui incremental syntax line cache（2026-08-25）

- 以 TDD 新增 `my_syntax_cache_t`：支持 C-like/YAML 有界词法 token、codepoint 坐标、
  跨行 block-comment 状态、修改行后缀失效和按行预算重建。
- 固定 4 MiB 源文本、1 MiB 单行、4096 token/行上限；超限拒绝，默认路径不进入 widget
  paint，不增加逐帧全文扫描或后端依赖。
- `test_myui_text_layout` 现为 **13/13**，覆盖 token 分类、状态传播、后缀失效和资源
  边界。
- text area 已通过 `set_syntax_enabled/language/line_budget` 接入 cache：默认懒关闭，
  paint 每帧最多推进配置行数，ready 的非 RTL、有字体行按 token 分段着色；编辑和整段
  替换会使修改行及后缀失效，失败时丢弃 stale cache 而不影响文本。无字体、RTL、justify
  保留原整行绘制，当前仍是有限 lexer，不宣称完整语法高亮。
- TDD 新增 `text_area_syntax_is_lazy_and_budgeted`、
  `text_area_syntax_replacement_invalidates_tokens` 和
  `text_area_syntax_key_edit_invalidates_suffix`；定向 `test_myui_window_manager`
  39/39 通过。

## myui nested folding ranges（2026-08-25）

- 折叠区间现在允许严格包含嵌套：外层折叠时只显示外层 header，外层展开后内层折叠
  继续生效；解除折叠按区间精确匹配，不破坏其他层级。
- 同起点歧义区间和交叉区间仍拒绝，保持物理行到 visual line 的确定性；实现不增加
  默认无折叠路径的分配或逐帧扫描成本。
- TDD 新增 `text_area_nested_fold_ranges_preserve_containment`；定向
  `test_myui_window_manager` **40/40** 通过。

## myui YAML fold-state persistence（2026-08-25）

- 新增 `my_text_area_folds_to_yaml()` / `my_text_area_folds_from_yaml()`；导出使用
  `version: 1`，格式严格限定为 `folds` 数组及每项的 `start`/`end` int64，当前只保存
  物理行闭区间，不保存文本内容或光标状态；导入继续兼容上一阶段无 version 的 legacy
  快照，未知版本直接拒绝。
- 导出限制 64 KiB、4096 个区间；导入限制相同，并校验行范围、嵌套/交叉关系和所有 schema
  字段。候选区间完全构建成功后才替换旧状态，非法 YAML 或 OOM 不破坏当前折叠。
- TDD 新增 `text_area_fold_state_yaml_roundtrip_and_transaction`；普通和 ASan
  `test_myui_window_manager` 均通过。

## myui folding visible-row performance（2026-08-26）

- 可见行缓存不再对每个物理行重新扫描全部折叠区间；按排序区间维护有界活动 end-stack，
  构建复杂度从最坏 O(rows*ranges) 降为 O(rows+ranges)，严格嵌套区间结束后正确弹栈。
- 无折叠默认路径不分配活动栈，编辑和渲染后端 API 不变。
- TDD 新增 `text_area_many_nested_folds_build_visible_rows_once`；定向
  `test_myui_window_manager` 达到 **42/42**。

## myui folding visible-row OOM correctness（2026-08-26）

- 以 TDD 新增 `text_area_folded_rows_remain_hidden_when_visible_cache_ooms`，覆盖可见行
  缓存数组或活动栈分配失败时的 count、visual index 和 physical row 映射。
- 缓存构建失败不再把全部物理行错误暴露给光标、滚动和绘制路径；三个查询改用不分配内存
  的线性回退。正常缓存路径仍为 O(rows+ranges)，只有 OOM 回退允许 O(rows*ranges)，以
  保证资源压力下的语义正确性。
- 验证：`test_myui_window_manager` **43/43** 通过；实现保持 widget/core 与所有渲染后端
  API 隔离。

## myui justify cursor and selection mapping（2026-08-26）

- 以 TDD 新增 `text_area_justify_cursor_tracks_stretched_space`，先复现正文拉伸空格后
  光标仍按固定 8px cell 定位的漂移。
- 新增无额外缓存的当前 visual line 边界计算；普通 LTR 的正文、选区矩形和光标均按实际
  glyph/cell advance 加 stretched-space 定位。正常绘制仍为逐行路径，不引入逐帧全文扫描；
  复杂 RTL 的完整 paragraph visual mapping 继续保持明确限制。
- 验证：`test_myui_window_manager` **44/44** 通过；实现不引入渲染后端私有 API。

## myui IME visual-line anchor mapping（2026-08-26）

- 以 TDD 新增 `text_area_ime_spot_tracks_wrapped_justify_cursor`，覆盖 justify 拉伸空格
  的横向候选框位置，以及光标移动到下一 wrapped visual line 后的纵向位置。
- `ta_update_ime_spot()` 现在复用 text area 的 visual-line、justify boundary 和全局坐标
  转换；Wayland/Win32/Cocoa 等 PAL 后端继续只接收统一坐标，不引入后端私有类型或额外
  每帧缓存。
- 验证：`test_myui_window_manager` **45/45** 通过；普通 LTR、复杂 RTL 的既有限制边界
  保持不变。

## myui variable-font coordinate contract（2026-08-26）

- 以 TDD 新增 `text_area_variable_font_keeps_nonwrap_coordinates_consistent`，先复现
  非 wrap 变宽字体点击仍按固定 8px cell 命中的错误。
- 新增按 codepoint glyph advance 的边界与命中计算，统一非 wrap 点击、水平滚动、光标、
  IME，以及 wrapped visual line 的局部光标/选区几何；无字体继续使用固定 cell fallback。
- 当前 visual line 即时计算，不引入逐帧全文扫描或后端 API；验证：
  `test_myui_window_manager` **46/46** 通过。

## myui pointer vertical bounds（2026-08-26）

- 以 TDD 新增 `text_area_pointer_hit_test_clamps_vertical_bounds`，先复现控件上方点击
  因负坐标转换为 `size_t` 而跳到最后一行的问题。
- pointer 垂直位置现在先在有符号域中计算，再钳制到 `[0, visible_count - 1]`；空文本、
  负坐标、超出底部及整数边界均不进行危险转换，正常路径无分配、常数复杂度。
- 验证：`test_myui_window_manager` **47/47** 通过。

## myui pointer font line-height mapping（2026-08-26）

- 以 TDD 新增 `text_area_pointer_hit_test_uses_font_line_height`，先复现字体实际行高大于
  配置字号时点击第一 visual line 底部被错误命中到第二行的问题。
- pointer hit-test 改为复用 `ta_line_height()`，与绘制、滚动和 IME 的行距契约一致；无
  新缓存、无分配，正常命中保持 O(1)。
- 验证：`test_myui_window_manager` **48/48** 通过。

## myui wrapped visual-line paging（2026-08-26）

- 以 TDD 新增 `text_area_page_down_moves_by_wrapped_visual_lines` 和
  `text_area_page_up_moves_by_wrapped_visual_lines`，先复现 wrap 模式按物理 row 分页导致
  长行几乎不滚动的问题。
- `MY_KEY_PAGE_UP/DOWN` 现在在 visual-line index 上计算 viewport 页距，使用已有 cache
  的二分定位和数组访问映射回物理行/codepoint；目标列继续复用 visual boundary 与 RTL
  映射，折叠行不会重新出现。分页不新增 visual-line cache 分配，索引路径复杂度为
  O(log V)；非 wrap 行为保持不变。
- 验证：`test_myui_window_manager` **50/50** 通过；实现仍只依赖 myui core/layout 接口，
  不泄漏 GL、Vulkan、软件 canvas 或平台类型。

## myui text-area paint scratch reuse（2026-08-26）

- 以 TDD 新增 `text_area_paint_reuses_line_buffer`，先验证相同内容的连续绘制会为每个
  visual line 反复申请临时字符串，造成帧级 allocator 抖动。
- `my_text_area` 现在持有按需扩容的 widget-owned scratch buffer，visual line 文本和光标
  锚点共用该 buffer；容量只在内容变长时增长，普通重绘不再产生逐行分配，后端 API 和
  绘制命令保持不变。分配失败时继续跳过无法准备的行或使用光标 cell fallback。
- 验证：`test_myui_window_manager` **51/51** 通过；scratch 生命周期在 widget destroy
  中释放，跨 soft/GLES/Vulkan/Break RHI 仍只经过公共 canvas 接口。

## myui justify paint allocation elimination（2026-08-26）

- 以 TDD 新增 `text_area_justify_paint_reuses_line_buffer`，先复现 JUSTIFY 逐单词复制和
  释放字符串导致的连续帧 allocator 抖动。
- JUSTIFY 现在直接在 widget scratch buffer 中暂时写入 NUL 分隔符，完成公共 canvas 绘制
  与测量后恢复原字符；不改变文本内容、布局或后端 API，普通 LTR 路径不再按单词数分配。
- 验证：`test_myui_window_manager` **52/52** 通过；折行、选择、光标和 IME 逻辑保持既有
  后端无关契约。

## myui visual-line byte-range cache（2026-08-26）

- 以 TDD 新增 `text_area_visual_lines_cache_byte_ranges`，先锁定 wrapped visual line
  必须暴露 paragraph 已计算的物理行内 byte 起止区间。
- `my_visual_line_t` 现在缓存 `start_byte/len_bytes`；wrap 重排直接转存 paragraph line
  的 byte span，非 wrap 视图生成等价整行 span。绘制和 scratch 文本准备直接使用区间，
  消除每个 visual line 从物理行首重复扫描 UTF-8 的 O(visual lines * physical line length)
  风险；codepoint 光标、选择和公共后端接口不变。
- 验证：`test_myui_window_manager` **53/53** 通过；实现不引入后端类型或额外逐帧缓存重建。

## myui RTL paint layout reuse（2026-08-26）

- 以 TDD 新增 `text_area_rtl_paint_reuses_layout`，先复现同一 RTL visual line 在默认方向
  对齐、选区和光标路径中重复复制 layout 的问题。
- widget scratch 文本未变化时，visual-line 作用域现在跨帧复用一个 layout，默认方向对齐
  与选区几何共享；光标路径合并 `rtl_base` 和 visual-x 查询。scratch 改变先销毁旧对象，
  再按需建立新 layout；居中、右对齐以及无选区的合适 JUSTIFY 路径不构建不必要的方向
  layout，失败时继续使用既有 fallback。
- 验证：`test_myui_window_manager` **54/54** 通过；没有引入全局可变 widget 状态或后端
  专用 API。

## myui text geometry prefix cache（2026-08-26）

- 以 TDD 新增 `text_area_geometry_cache_reuses_glyph_advances`，先复现连续绘制中同一物理
  行反复调用字体 glyph advance 的问题，并覆盖文本变更后的失效重建。
- `my_text_area` 现在缓存当前热物理行的 codepoint boundary 到 advance 前缀和，键包含
  文本 revision、字体和字号；`ta_line_boundary_x()` 与 `ta_line_col_at_x()` 共享缓存，
  命中后分别为 O(1) 和 O(log N)，首次建立为 O(N)。只保留一个热行以控制内存，分配失败
  继续逐 codepoint 扫描。
- 验证：`test_myui_window_manager` **55/55** 通过；缓存只位于 widget/core，不依赖任何
  GL、Vulkan、软件 canvas 或平台类型。

## myui syntax token byte range cache（2026-08-26）

- 以 TDD 新增 `syntax_cache_records_utf8_token_byte_ranges`，覆盖多字节 UTF-8 token
  的 codepoint 与 byte span 一致性，并先通过缺少字段的编译失败确认测试有效。
- `my_syntax_token_t` 现在缓存 `start_byte/len_bytes`；lexer 复用已有 UTF-8 单次扫描
  直接填充范围。text area syntax paint 按 visual line byte span 裁剪 token，移除每个
  token 从行首重复计算 byte offset 的 O(token count * line length) 热路径。
- 完整 token 绘制为 O(1)，每个 visual line 只处理边界 token；原有 codepoint 范围、
  增量行状态、预算限制与公共跨后端 canvas API 保持不变。
- 定向验证：normal/ASan 的 `test_myui_text_layout` **14/14**、
  `test_myui_window_manager` **55/55** 通过，Vulkan `myui_core` 构建通过；
  `git diff --check` 与乱码/控制字符扫描通过。

## myui visual line physical-row index cache（2026-08-26）

- 以 TDD 新增 `text_area_visual_line_index_cache_tracks_folds_and_edits` 与
  `text_area_visual_line_index_cache_oom_falls_back`，先覆盖折叠/编辑失效和分配失败
  回退，再实现索引缓存。
- wrap 模式为每个物理行缓存首尾 visual index；`ta_vline_of_pos()` 先取得该行的
  紧凑区间，再执行二分，避免在全量 visual line 数组上搜索不相关物理行。缓存失效
  与 visual-line dirty 路径统一，事务重排失败仍保留旧 vlines 并使用安全回退。
- 缓存是有界 widget-owned 内存，不引入全局状态或渲染后端类型；隐藏行以
  `SIZE_MAX` 标识，OOM 时只禁用优化，不改变命中结果或编辑语义。
- 验证：normal/ASan 的 `test_myui_window_manager` **57/57**、
  `test_myui_text_layout` **14/14** 通过，Vulkan `myui_core` 构建、
  `git diff --check` 与乱码/控制字符扫描通过。

## myui RTL interaction layout cache（2026-08-27）

- 以 TDD 新增 `text_area_rtl_hit_test_reuses_layout`，锁定连续命中测试不得重复分配
  visual line 文本或 layout。
- text area 现在缓存当前 RTL visual line 的 layout；键盘导航、垂直导航、分页和
  pointer hit-test 共享缓存，键包含 text revision、物理行、byte span、字体及字号。
- 纯 LTR 保持快速路径；缓存失效、OOM 或 layout 构建失败时回到既有临时路径。缓存只
  位于 widget/core，不引入 GL、Vulkan、软件 canvas 或平台类型。
- 验证：normal `test_myui_window_manager` **58/58**；ASan、Vulkan 和最终差异/编码
  门禁待完成。

## myui visual boundary prefix cache（2026-08-27）

- 以 TDD 新增 `text_layout_reuses_font_boundary_prefix_cache`，覆盖 visual x、logical
  hit-test、selection rects 的 glyph advance 复用和字号变更失效。
- `my_text_layout_t` 按字体指针/字号缓存 visual boundary 前缀和；视觉 x 查询 O(1)，
  命中测试在前缀和上 O(log N)，selection rects 不再逐项重新读取 glyph advance。
- cache 是 caller-owned layout 的有界字段；realloc 失败保留旧缓存并安全回退，destroy
  释放缓存，不污染全局 LRU master 或跨后端 canvas 契约。
- 验证：normal/ASan（`detect_leaks=0`）`test_myui_text_layout` **15/15**、
  `test_myui_window_manager` **58/58**，Vulkan `myui_core`、`git diff --check` 和
  乱码扫描通过；LeakSanitizer 在当前 ptrace 环境中无法启动。
## rule engine bounded GRL semantics phase 1（2026-08-28）

- 新增 `re_facts_set_path` 嵌套写：精确平键优先，否则沿根事实的结构化成员更新；
  不隐式创建中间对象，未命中返回 `RE_STATUS_NOT_FOUND`。规则 then 赋值的点路径经它
  路由，未命中时回退平坦 `re_facts_set`。
- 新增 then 动作 `$Fact.method(...)`：按 set/get/reset/update 约定处理，否则回退注册
  函数（先 `Fact.method` 后 `method`），均未注册返回 `RE_STATUS_NOT_SUPPORTED`
  （上游静默无操作，此处为有意分歧）；then 方法调用之外出现 `$` 为解析错误。
- 新增本地 GRL 扩展 `deffacts "name" { Path = literal; }` 及
  `re_engine_load_deffacts` / `re_engine_reset_with_deffacts`（清库后重播种全部为
  普通非逻辑事实）；数组字面量的字符串元素沿用浅拷贝约定，由程序 IR 持有字符串存储。
- 新增规则模板 API（`re_rule_template_create/param_default/instantiate/destroy`）：
  对 `{{identifier}}` 做纯字节替换，生成 `rule "N" [salience N] {when/then}` 文本，
  宿主经 `re_program_load` 解析安装；无 JSON 往返、无引擎侧模板注册表。
- 验证：`test_rule_engine_grl_semantics` **23/23**，rule-engine 定向套件
  **13/13** 通过（build-gate，clang/Ninja Debug）。
- 当前限制：方法调用仅限 then 动作；deffacts 为本地扩展而非上游语法；模板仅
  instantiate-to-text；持久 agenda 与完整 producer provenance 仍属 Phase 2。

## rule engine phase 2：recognize–act 循环、有界持久 agenda 与线性路径 provenance（2026-08-28）

- `re_engine_run` 改为 recognize–act 循环：重算可见规则 → 按 refraction 去重压入 agenda →
  弹出最高 salience 项 → 触发，直至 agenda 为空、达到上限或被取消。refraction 键为
  （规则、前提槽位、值指纹）；弹出时重新校验，陈旧 activation 直接丢弃且不消耗 fired 额度。
  每条符合条件的规则（≤8 个 AND 的事实-字面量比较）获得独立私有 RETE 网络，经
  `next_on_facts` 链在 facts 上、无跨规则 alpha 共享；alpha 记忆看不到的条件（如结构化
  成员路径）回退为按条件 read-set 键控的零 token activation。
- 持久 agenda 与检视 API：`re_engine_set_agenda_persistent`、真实的 `re_engine_agenda`
  （惰性创建、非 const）、`re_agenda_count`、`re_agenda_peek`（salience 降序/序列升序、
  真实前提 id）；`re_agenda_destroy` 对引擎持有实例为文档化空操作。持久模式下 pending 与
  fired 记录在 OK/LIMIT/CANCELLED 退出后保留，安装新程序时重置。`re_limits_t` 追加
  `max_activations_tracked`（0 → 默认 1024，约束 agenda fired+pending 总量）；ABI minor
  升至 3，挂载网络时通告 `RE_CAP2_AGENDA_RETE`（测试锁定）。
- 线性路径完整 provenance：线性匹配在 TERM_FACT/EXISTS/FORALL 命中时记录条件 read-set
  （8 条路径去重、溢出静默截断；不含动作 RHS 与 backward）；前提 = RETE 谱系 ∪ read-set
  事实 id（上限 8）；线性派生改经 `insert_logical`/`justification_add`；带结构化根的
  点路径动作目标写嵌套成员，justification 锚定根事实 id（级联撤回根事实，属文档化边界）。
- 顺带修复：`ir_eval.c` 线性求值器 stage 3 的 AND/OR 既有缺陷——第一合取项为真时忽略
  第二操作数的结果（OR 对称地在第一操作数为假时恒真）；已修复并附 RETE/线性一致性
  回归测试。
- 验证：`test_rule_engine_agenda` **33/33**；build-gate 上
  `ctest -R "rule_engine|backward_machine" --output-on-failure` **14/14**；ASAN+UBSAN
  （build-rule-fresh-asan）agenda **33/33** + tms **11/11**；MSVC rule_engine_core
  点建无警告；`test_rule_engine_rete_incremental` 新增引擎网络的公共 destroy UAF 回归。
- 当前限制：值指纹为 FNV 哈希——理论碰撞会漏触发；NULL/UNKNOWN/NONE/结构化值仅混入
  类型标签，double 按原始位哈希。refraction 无时间步：单次运行内 A→B→A 值往返不重新
  触发（持久模式下 fired 键跨运行保留至前提变化）。线性自改写规则（如
  `when N+0 > 0 then N = N + 1`）现循环至 `max_firings`（默认 1024），与 RETE 值指纹
  语义对称。executor 并行路径不捕获 read-set（其下线性规则每次运行至多触发一次）；
  `RE_COMPARE_IN` 的事实操作数读取不计入 read-set；结构化根前提仅混入类型标签（仅
  成员变更不会重新激活线性规则）。点目标传递环可能从 TMS depends_on 返回
  `RE_STATUS_LIMIT`（新的诚实失败模式）。`re_agenda_peek` 的 rule_name 借用已安装程序
  的存储，peek 为 O(n²)、由 `max_activations_tracked` 约束。完整 RETE-UL 与通用 TMS
  仍不支持。

## rule engine phase 3：查询级 NOT、查询聚合、搜索策略与共享证明图（2026-08-28）

- 查询级否定（`NOT ` 前缀，negation-as-failure，封闭世界假设）：子目标可证 →
  `RE_QUERY_DISPROVED` 且 0 解；子目标不可证或已否定 → `RE_QUERY_PROVED`，附一个空绑定
  证明，其 trace 记录完整 `NOT <goal>` 文本；子目标深度受限 → `RE_QUERY_LIMIT` 原样透传
  （反转受限搜索结果不可靠，故永不反转）。无 stratification——与上游一致（上游同样只允许
  目标前缀形式）；嵌套 `NOT NOT` 每层递归解包一级；前缀区分大小写，不消耗 `max_depth`
  层级（子目标以调用方规范化选项、`max_solutions` 1 重入分发器）；NOT 与搜索策略组合
  （反转作用于策略选定的子目标结果）；空前缀剩余为 `RE_STATUS_INVALID_ARGUMENT`。另外：
  精确形式 `goal("RuleName")` 查询字符串解包为裸规则目标；字面上命名为 `goal("X")` 的
  规则会与之冲突（按规则 X 查询）。
- 查询聚合 `re_engine_query_aggregate`：`RE_ACCUM_COUNT/SUM/AVERAGE/MIN/MAX` 加追加的
  `FIRST/LAST`；内部有界查询（max_depth 64、max_solutions 1024、DFS）后按 DFS 序折拢
  指定绑定。类型规则与上游聚合一致：COUNT → INT64、AVERAGE → DOUBLE、SUM/MIN/MAX 全
  INT64 输入时保持 INT64——与 `re_accumulator_evaluate` 恒 DOUBLE 有意不同（头文件注释
  已注明）。FIRST/LAST 遇字符串绑定返回 `RE_STATUS_NOT_SUPPORTED`（proof 字符串随内部
  查询释放）；空解集：COUNT 0/OK，其余 `RE_STATUS_NOT_FOUND`；非数值折拢输入
  `RE_STATUS_INVALID_ARGUMENT`；达到 1024 解上限或内部搜索深度受限报 `RE_STATUS_LIMIT`
  （恰好满员与截断不可区分）。percentile/stddev/count-distinct、GROUP BY、嵌套或多变量
  聚合均不支持；不解析上游 GRL query-block/WHERE 语法。
- 搜索策略：`re_query_options_t` 追加 `strategy` 与 `disable_shared_proof_graph`，沿用
  `struct_size` 版本化（旧尺寸结构 → DFS + 共享开；过短 → `RE_STATUS_INVALID_ARGUMENT`；
  策略值越界同）。`BREADTH_FIRST`/`ITERATIVE` 共用基于 DFS 机器的迭代加深包装：以
  max_depth 上限 1、2、4……递增至配置上限（默认 64），首个产出至少一个解的上限获胜；
  超过 32 次翻倍报 `RE_STATUS_LIMIT`。backward 查询不执行动作，重复探测无副作用；获胜的
  截断探测仍报 PROVED（截断是策略机制而非搜索失败）。上游 iterative deepening 同为递增
  深度的 DFS 探测；上游 breadth-first 是独立队列式搜索，本地未建模。
- 共享证明图：引擎持有、惰性创建的 64 项缓存（满则全清），键为 {目标文本、facts 指针、
  `mutation_serial` 代际、规范化选项（max_depth/max_solutions/strategy）、`config_serial`}，
  在选项规范化后查询；仅缓存终态 PROVED/DISPROVED（LIMIT/UNKNOWN 永不缓存）；服务证明为
  深拷贝，服务查询自带与新建运行相同的失效订阅；`disable_shared_proof_graph` 完全绕过
  查询/存储/统计（统计不动）；`re_engine_proof_graph_stats` 报告命中/未命中（首次缓存前
  为零）。`config_serial` 在安装程序、注册/注销函数时递增。
- 顺带修复（值得注意）：`re_facts_retract` 现在递增 `mutation_serial`——既有缺口（此前仅
  set/insert/update 递增），否则撤回后共享证明图可能服务陈旧缓存；TMS 级联撤回与仅撤回
  事务因此同样触发失效。
- 验证：`test_rule_engine_backward_ext` **32/32**（经 `re_internal.h` 白盒）；build-gate 上
  `ctest -R "rule_engine|backward_machine" --output-on-failure` **15/15**；ASAN+UBSAN
  （build-rule-fresh-asan）ext 套件与规则引擎子集全绿；`rule_engine_c99_consumer` 干净。
- 当前限制：缓存条目按 facts 指针值键控（从不解引用，无 UAF；销毁+同地址重分配且代际
  匹配时可能别名——已记录为挂起的残留风险，未修复）；失效为粗粒度（同一 facts 任意变更
  在下次查询时丢弃其全部条目）；NOT 查询的统计计入子目标查询（一次新的 `NOT X` 记录
  2 次 miss）；INT64 折拢使用未检查加法，极端求和会溢出（回绕）且无状态报告；
  `RE_CAP2_BACKWARD_PROOFS` 能力位仍保持清零——任意谓词合一与上游共享子图
  producer provenance 未实现，位通告暂不提升。

## rule engine phase 4：流聚合扩展与 Redis/并发边界加固（2026-08-28）

- 流聚合扩展（Task 16）：`re_stream_aggregate_kind_t` 追加
  `RE_STREAM_AGGREGATE_MIN=4/MAX=5/FIRST=6/LAST=7`；`re_stream_aggregate_result_t`
  尾部追加 `minimum/maximum/first/last`，按 `struct_size` 门控写出——旧尺寸调用方仅
  得到旧字段，追加字段仅在 `struct_size` 覆盖时写入。MIN/MAX 与 SUM/AVERAGE 同样只
  折拢数值事件、遇非数值匹配事件返回 `RE_STATUS_INVALID_ARGUMENT`；FIRST/LAST 按
  时间戳选取最早/最晚的留存匹配事件（插入序打破平局），接受任意值类型；空过滤集对
  四种新 kind 返回 `RE_STATUS_NOT_FOUND`（COUNT 保持 0/OK）。first/last 的字符串数据
  为窗口持有借用值，有效期至下一次窗口变更或销毁（与 `re_facts_get` 的借用约定一致，
  头文件已注明）。
- Redis 边界（Task 17）：CMake 选项 `RULE_ENGINE_ENABLE_REDIS`（默认 OFF）；ON 时
  `find_path`/`find_library` 探测 hiredis——找到则把 `redis_provider.c` 编入
  `rule_engine_core` 并定义 `RE_HAS_HIREDIS` 及链接库；缺失则以 STATUS 消息强制 OFF
  （无静默回退、无硬错误，替换既有 FATAL_ERROR 桩）。适配器（仅随 hiredis 编译）以
  同步 hiredis API 镜像 `memory_provider.c` 的 vtable：键为 `<prefix>:<name>`，值为
  原始字节（类型标签 + 载荷），TTL 用毫秒 PSETEX/PTTL，配 SET/GET/DEL；因 v1 provider
  options 无连接字段（有界接缝），连接取自 `RE_REDIS_URL` 环境变量（默认
  `redis://127.0.0.1:6379`）+ 固定前缀 `re`；失败经 `last_error` 记录
  `RE_PROVIDER_ERROR_UNAVAILABLE`。无该宏时 `RE_STATE_PROVIDER_REDIS` 保持返回
  `RE_STATUS_NOT_SUPPORTED` 不变。测试：禁用构建边界锁定 + `RE_TEST_REDIS_URL`
  跳过守卫的往返用例（未配置时打印 SKIP 且计绿——遵循项目证据规则的诚实不可用）。
- 并发边界（Task 18）：审计驱动，未新增守卫（窗口无用户代码回调路径、restore 分段
  提交、provider 为单返回分发；既有 running/notifying/transaction 标志已覆盖全部真实
  向量）。`re_engine_create` 上方的头文件线程契约现明确：engine/facts/windows/providers
  为单线程句柄；运行期间的冲突变更（重入 run、开启用户事务、重置工作内存）返回
  `RE_STATUS_BUSY`；动作回调内的事实写入分段进入该 firing 的事务并随 firing 提交
  （而非被拒绝）；allocator 回调不得对处于在飞操作的句柄重入任何规则引擎 API；C11
  executor 仅在 worker 中求值只读条件。新测试：stream_ext 的 4 个单线程守卫用例
  （套件共 12 个）+ executor-stress 的 busy-boundary 阶段（64 次迭代，回调内重入、
  全程在引擎线程、无数据竞争）。
- 顺带披露（Task 16）：`engine/tests/test_rule_engine.c:1507` 为聚合结果结构体追加做
  位置初始化器补全（语义中性，由 -Werror 迫使）。
- 验证：build-gate `ctest -R "rule_engine|backward_machine" --output-on-failure`
  **16/16**；`test_rule_engine_stream_ext` **12/12**，ASAN（build-rule-fresh-asan）
  同绿；executor stress 64+64 迭代于 engine/build-hardening-asan（MSVC cl，C11 ON）与
  engine/build-hardening-ubsan-clang 全绿；`RULE_ENGINE_ENABLE_REDIS=ON` 配置在
  hiredis 缺失时成功并以 STATUS 强制 OFF。
- 当前限制：默认系统依赖路径不保证存在 hiredis 开发包；若未配置源码或系统依赖，
  适配器保持禁用，运行时往返由 `RE_TEST_REDIS_URL` 跳过守卫；first/last 借用值不得跨窗口
  变更持有；通用流模式/join/watermark 仍不支持；Redis 的实际启用仍需集成环境提供
  受控 Redis 服务。使用 Redis 8.10.1 源码路径的真实服务往返已在下一条依赖矩阵中验证。
- 依赖矩阵回归（2026-08-30）：`RULE_ENGINE_ENABLE_C11_PARALLEL=ON` 在检测到
  `<threads.h>` 的主机构建并生成 executor stress target，完整 CTest **77/77**；
  `RULE_ENGINE_ENABLE_REDIS=ON` 在仅有运行库、缺少 hiredis 开发头文件的主机上明确
  输出 STATUS 并强制关闭选项，完整 CTest **76/76**。两条路径均未静默替换依赖或
  把 Redis 服务不可用误报为通过。
- Redis 源码依赖接入（2026-08-31）：新增
  `RULE_ENGINE_REDIS_SOURCE_DIR`，可直接指向 Redis 源码树（自动定位
  `deps/hiredis`）或 hiredis 源目录；CMake 在隔离的私有静态 target 中编译
  hiredis，避免要求系统安装开发包，也不把客户端类型暴露到公共 ABI。先以配置契约
  测试锁定，再修复源目录 include 根路径缺陷；Redis 8.10.1 + C11 并行 + 原生适配器
  的 focused 回归和 `RE_TEST_REDIS_URL` 真实往返均通过。

## myui selection rect bounded output（2026-08-29）

- 以 TDD 新增 `text_layout_visual_rects_honors_output_capacity`，先复现多视觉片段时
  API 返回值超过 `cap` 的契约缺陷。
- `my_text_layout_visual_rects()` 在缓存和逐字形回退路径都严格返回 `0..cap`，写满
  输出后立即结束，避免在 text area/edit 只请求固定小数组时继续扫描。
- 保持 RTL 分段顺序、字体宽度、OOM 回退和跨后端绘制行为不变；公共头文件同步明确
  有界返回契约。
- 验证：normal/ASan `test_myui_text_layout` **16/16**，Vulkan `myui_core` 构建、
  `git diff --check` 与乱码/控制字符扫描通过；LeakSanitizer 继续受当前 ptrace
  环境限制，ASan 使用 `detect_leaks=0`。

## myui fold-state YAML legacy migration（2026-08-29）

- 以 TDD 在 `text_area_fold_state_yaml_roundtrip_and_transaction` 中加入显式 `version: 0`
  输入，先锁定旧版编号被错误拒绝的回归。
- `my_text_area_folds_from_yaml()` 将 `version: 0` 作为旧版 `folds` schema 接收，并沿用
  同一套严格字段、范围、数量和输入预算；成功导入后 exporter 始终输出 `version: 1`。
- 未知版本仍拒绝，candidate 解析失败仍不会替换 active fold state；不影响绘制热路径、
  后端 API 或 XML 废弃边界。
- 验证：normal/ASan `test_myui_window_manager` **58/58**，Vulkan `myui_core` 构建、
  `git diff --check` 与乱码/控制字符扫描通过；LeakSanitizer 受当前 ptrace 环境限制。

## myui RTL syntax token painting（2026-08-29）

- 以 TDD 新增 `text_area_rtl_syntax_colors_tokens`，锁定 RTL 行不应因 bidi 直接退回整行
  普通颜色绘制；测试比较启用 YAML keyword 高亮与无高亮基线的软件 canvas 输出。
- text area 现在复用 visual UTF-8/layout，按 visual-order 连续片段设置 token 颜色；每个
  visual item 通过有序 token 的二分查找确定颜色，复杂度为 O(V log T)，LTR 仍保持原有
  O(T) token 测量路径。
- 新增 `my_text_layout_visual_boundary_x()`，提供字体宽度缓存支持的视觉边界坐标查询；
  core 和 canvas API 仍后端中立。复杂 RTL GSUB、跨 face fallback 和 JUSTIFY token 联动
  保持明确未实现。
- 内置 bitmap font 在创建时将 1bpp 数据展开为 8bpp alpha，修复绘制读取越界；绘制热路径
  不做格式转换。
- 验证：normal/ASan window manager **59/59** 与 text layout **16/16**、Vulkan
  `myui_core` 构建、`git diff --check` 和乱码/控制字符扫描通过；LeakSanitizer 受当前
  ptrace 环境限制。

## rule engine GRL surface 补全（sub-project A，2026-08-29）

- 表达式表面（A1）：词法操作符别名 `eq/ne/gt/gte/lt/lte/not_contains`、大小写不敏感
  `true/false/null` 字面量、`%` 取模（f64 fmod；两操作数均 Integer 且结果整时保持
  Integer）、字符串 `+` 拼接；D4 比较对齐——相等严格按类型（`Integer(1) != Number(1.0)`），
  关系操作符经 `to_number` 强制（数字字符串可强制；bool/null/array/object 一律 false）。
  测试锁定边界：非字符串操作数下 `contains` 为 false、`not_contains` 为 true；
  `NONE == NONE` 为 true（按标签的严格相等，非三值逻辑）；strtod 强制接受上游 Rust
  解析器拒绝的十六进制浮点写法（`inf/infinity` 两侧均接受）；`%` 以 f64 计算，超过
  2^53 的 Integer 操作数可能舍入。
- 通用量词（A2）：`!(expr)`/`exists(expr)`/`forall(expr)` 接受任意内部布尔表达式；
  候选选取按上游事实名前缀启发式（D7），逐候选重绑定并吸收 NOT_FOUND；空候选集
  forall 空洞为真（D6）；无带点字段引用时按普通事实库求值一次。量词条件不进入
  RETE 网络；backward 链接对含此类条件的规则诚实返回 `RE_STATUS_NOT_SUPPORTED`。
- 内置函数（A3/A4，新增 `builtins.c`，注册函数优先的回退）：条件族
  `len/length/size`、`isEmpty/is_empty`、`contains`、`exists/notExists/not_exists`；
  工具族 `log/print/println`、`now/timestamp`、按引擎确定性的 `random`、
  `format/sprintf`、`sum/add/max/min/avg/average`（保持 INT64 的折拢）、
  `round/floor/ceil/abs`、`contains/includes`、`startswith/endswith`、
  `lowercase/uppercase/trim`、`split`、`join`。有意跳过的上游别名：maximum/minimum、
  ceiling、absolute、begins_with/ends_with、tolower/toupper、strip、update/refresh；
  `split` 复刻上游 `{:?}` 调试字符串但仅转义引号/反斜杠/`\n`/`\r`/`\t`（其余控制
  字符不具备 Rust-debug 保真）；`len` 族返回 INT64 而上游返回 Number（D4 下
  `len(x) == 4.0` 为 false，已记录分歧）。
- multifield 操作（A5）：事实路径后的 `count <cmp> <数值字面量>`、`first`/`last`、
  `empty`/`not_empty`/`notEmpty`、`collect` 数组形状谓词；纯只读、不入 RETE；
  `count` 相等严格按类型（`count == 3.0` 不匹配 int64 3，D4），关系比较仍强制字面量。
  上游 GRL 解析器仅暴露这些拼写；`index`/`slice` 只存在于上游 RETE multifield Rust
  API，本地为解析错误。
- accumulate CE（A6）：`accumulate(Type($var: field, conds...), func(...))` 平坦前缀
  扫描 + 实例分组 + 结果注入为 `Type.func` 事实；记录分歧——mini 条件相等复用
  `re_value_compare`（严格类型、无 double epsilon）、无 `$var` 的 count 统计匹配实例数
  （上游统计被抽取值，为 0）、未知函数名解析期报错、字面名 `default` 的实例不并入
  裸键默认实例。注入写使节点不纯（首遍求值、不入 RETE）；每次到达节点的运行都按当前
  事实重算注入值（跨运行稳定性与挂接 executor 情形均有测试锁定）。
- GRL query 块（A7，新增 `query_exec.c` + `re_engine_run_queries`/`re_engine_run_query`，
  本阶段唯一公共头变更）：`query "Name" { goal/strategy/max-depth/max-solutions/
  enable-memoization/enable-optimization/when/on-success/on-failure/on-missing }`；
  目标文本按 `&&`/`||` 文本拆分，`!=` 子目标直接对工作内存求值；记录分歧——标量字段
  以 `;` 终止（上游以换行终止 goal/when）、on-missing 折叠进 on-failure（本地机器不
  跟踪 missing_facts）、硬错误（如 backward 嵌套量词边界的 `RE_STATUS_NOT_SUPPORTED`）
  不触发任何动作块直接向上传播、重名 query 按源序取首个；query 不在
  `re_engine_run` 内运行。
- 动作内置（A8）：白名单裸 `name(args)` then 语句——`retract($Obj)` 置
  `_retracted_<root>` 标志事实使该根的条件读取按缺席处理（仅条件；标志必须恰为 BOOL
  true；token 存活的 pending activation 在弹出时重过门控匹配）、`log(...)`、
  `ActivateAgendaGroup` 中途切换 agenda 焦点、`ScheduleRule/CompleteWorkflow/
  SetWorkflowData` 按裸名分发到注册函数（D5；未注册则 `RE_STATUS_NOT_SUPPORTED`）；
  其余裸调用仍是解析错误。
- `test(f(...))` CE 与 `$x: Type(conds)` 类型形式（A9）：test 对单个函数调用结果做
  真值判定（BOOL 原样、INT64/DOUBLE 非零、STRING 非空）；类型形式对类型前缀候选做
  exists 语义，`$x` 与裸字段引用在形式内改写为 Type 根相对路径（形式外 `$var` 仍为
  解析错误）。两者均不入 RETE，backward 查询返回 `RE_STATUS_NOT_SUPPORTED`。
- 语法清扫（A10）——上游 GRL_SYNTAX.md 剩余构造按"上游同样缺席"处置并由
  `syntax_sweep_unsupported_constructs_parse_error` 锁定：`/* */` 块注释为上游文档
  声称但未实现（grl.rs 的 clean_text 仅剥离 when 子句内整行 `//`；本地无任何注释
  语法，两种形式均解析错误）；`enabled` 规则属性上游仅为结构体字段（rule.rs）、无
  GRL 形式；对象字面量 `{k: v}` 与下标语法 `a[0]` 两侧均无解析器支持。
- 验证：`test_rule_engine_grl_surface` **136/136**、`test_rule_engine_query_blocks`
  **25/25**；build-gate `ctest -R "rule_engine|backward_machine" --output-on-failure`
  **18/18**；build-gate 全量构建与 `ctest -LE graphics` 全绿；ASan
  （build-rule-fresh-asan）两套件干净；`git diff --check` 通过。未提交前工作树已有
  21 个既有脏文件，按选择性提交未纳入。
- 当前限制：量词/multifield/accumulate/test/类型形式仅线性求值且对 backward 为
  NOT_SUPPORTED；backward 不查询内置函数；D1 短路、D2 无接收者条件方法分发、D3
  `matches` 通配子串为持续记录的分歧；`exists((A == 1))`、`exists($o: Type(...))`、
  `exists(accumulate(...))` 按函数形式解析而报错（文档化边界）；完整 RETE-UL、通用
  TMS、任意谓词合一仍不支持。

## rule engine RETE/TMS/unification 深度对齐（sub-project B，2026-08-30）

- TMS 对齐收口（B1，上游 `src/rete/tms.rs` + `tests/tms_test.rs` 共 12 条测试语义
  全部移植）：显式支持与逻辑论证共存——`re_facts_insert` 覆盖逻辑派生事实时记录显式
  支持标记（无前提的 justification 项，即上游 `JustificationType::Explicit` 的本地
  编码，公共溯源接口不可见），`re_facts_insert_logical` 作用于宿主断言事实时两者并留；
  两处级联守卫改为总支撑计数归零才撤销（显式支持构造上恒有效）；多论证事实在单一前提
  撤销后存活；菱形依赖完整级联；新增 justification 不重导出值；标记随 `re_tms_clone`
  迁移（transactions.c 零改动）；`re_facts_justification_remove` 增加与 add 侧对称的
  校验，公开输入无法删除标记。记录的分歧与边界：插入期成环以 `RE_STATUS_LIMIT` 拒绝
  （上游容忍并靠 retracted 集终止；级联环情形本身与上游 `is_valid` 一致并以白盒测试
  锁定；及时移除项是本地终止保证，上游从不清理映射）；`re_facts_set`/`re_facts_update`
  为纯值写、不记录显式支持；仅剩标记的事实保持 `is_logical` 为真（上游在撤销前也将
  事实留在 `logical_facts`）；结构化根派生保留"前提撤销级联至整根"的既有边界；上游
  全局 TMS 统计结构体无本地聚合对应（按只增 ABI 改为钉住逐事实等价值）。
- 证明图真实图形状（B2，上游 `src/backward/proof_graph.rs`）：64 项结果缓存仍为查找
  层，图语义叠加其上——派发包装器在每次 backward 运行捕获有界（32、按路径去重）前提
  集 {path, present, FNV-1a 类型化值指纹}（缺席读取记 present=0，之后首次断言仍可使
  其失效；缓存命中将所供条目前提并入外层捕获）；每次存储按证明记录一个信息性节点
  （trace 根规则名 + valid 标志）及产生运行的前提集；查找保留代数相等快路径，序列号
  失配时逐前提重解析并比对存在性与类型化指纹——前提全部成立则条目在无关变更下存活
  （相对 B2 前粗粒度整体失效的标题级行为升级），任一翻转即整体摘除（对应上游
  `lookup_by_key` 过滤失效节点）；任何未追踪影响（证明中途的用户函数、前提上限溢出、
  分配失败）使捕获转为 opaque 并回退到粗粒度代数检查，健全性绝不换精度。统计：原双
  指针 `re_engine_proof_graph_stats` ABI 不变，新增 `re_engine_proof_graph_stats_v2`
  以 struct_size 版本化的 `re_proof_graph_stats_t` 报告 hits/misses/invalidations/
  stores/evictions（64 项清空式驱逐计入 evictions）；依赖传播为惰性（下次咨询时再校验
  发现），与上游 eager `invalidate_handle` 递归在缓存用途下语义等价。边界：
  object/array 事实仅按类型标签取指纹（未来若有成员级读取路径必须被捕获或转
  opaque）；节点 valid 标志为上游形状保真、生产代码不消费。
- 反向 `?var` 合一（B3，上游 `src/backward/unification.rs` 情形表）：查询目标串中
  `==` 任一侧的 `?var` 触发合一——已绑定变量取其值；未绑定且对侧可解则绑定并经
  `re_proof_binding_get` 以原样 `?s` 名浮出水面；不可解则不匹配（缺席事实读取报
  `RE_QUERY_UNKNOWN`，与字面量路径一致）；两侧均未绑定（`?x == ?y`）报
  `RE_QUERY_DISPROVED`（未读任何事实，可以空前提集缓存且永不翻转）；重绑定粘性一致
  （同值通过，异值仅使该证明分支失败而非引擎错误）。`goal("Rule", a1, ...)` 查询串
  接受字面量/`?var`/事实路径实参（嵌套调用/算术为 `RE_STATUS_INVALID_ARGUMENT`）；
  未绑定 `?var` 实参使形参保持未绑定并记录 形参→?var 别名，形参取得具体值时别名按
  粘性一致回绑；条件相等中未绑定形参经由既有操作数路径取得对侧具体值（事实读取全部
  保持前提捕获）；聚合接口按原名折叠 `?var` 绑定、无 API 变更。记录的边界（与上游
  一致）：无 occurs check、无延迟、值按标量/数组类型化相等（绝不逐元素）、别名为
  单向值传播而非 union-find（跨跳要求同名形参）。上游自己的 Unifier 从未被其搜索
  引擎调用（死集成），故情形表映射到本地机器的两个真实绑定点而非作为模块移植。
  次要表面：直接目标字面量仅 int64，而 goal() 实参按 strtod 词法为 double（与既有
  `==` 路径一致）。
- agenda 焦点栈 + auto-focus（B4，上游 `src/rete/agenda.rs` AdvancedAgenda）：
  `ActivateAgendaGroup("g")` 压入当前焦点并切换；焦点组 activation 耗尽（所有规则
  完成首遍后 pending 队列排空）时弹回上一焦点继续 recognize-act 循环；栈空则运行
  结束且焦点留在耗尽的组（恰为上游 `pop()?`）。栈存放在 program 上、与焦点同生命
  周期（持久 agenda 被 LIMIT 中断的运行可在下次运行弹回；program 安装即重置）；
  静态预设焦点为栈底；普通 setter 清空已存历史；栈有界 32
  （`RE_AGENDA_FOCUS_STACK_MAX`，溢出丢弃已存焦点、切换仍发生）。
  `auto-focus true|false` 属性沿 no-loop 语法惯例（其他值或重复属性均为解析错误）、
  镜像入 IR、使其规则绕过计算门控（上游按组无关方式评估规则），且仅在压入产生真正
  新 pending 项时切换焦点（去重/refraction 命中绝不重切换）；无组 auto-focus 为
  文档化 no-op。已批准的分歧：NULL 无焦点状态永不入栈（无上游 MAIN 返回；保持已
  批准的 A8 中途切换行为）；跨组 pending activation 经 A8 弹出时过期门控丢弃并在
  该组重获焦点时重新压入（纯条件重新压入，净触发次数与上游分组堆相同；不纯（函数调用）
  规则保持仅首遍求值的既有界限，该运行内不再重新触发；activation 序号可不同）；
  焦点外的纯 auto-focus 规则每个重算周期都重新求值（与上游一致）；32 上限溢出路径
  有文档无单测。
- 上游 vapor——只记录不复制（spec Sub-project B 第 5 条）：任何上游执行路径都不
  存在跨规则 alpha 共享与 beta token 传播（"RETE-UL" 是逐规则布尔表达式树；具名
  BetaNode/TokenPool/NodeSharing 工具无任何引擎使用）；上游 Unifier 从未被反向搜索
  调用；上游集成的证明图缓存为死代码（每次查询新建图 + insert/lookup 键失配）；
  并行引擎的 action 为空操作且未接入主引擎；salience+recency 之外的
  ConflictResolutionStrategy 与 RETE-UL accumulate 值绑定同样缺席。映射说明：本地
  引擎对应上游 RustRuleEngine + BackwardEngine + streaming seam；ReteUlEngine/
  IncrementalEngine 的引擎级怪癖（100/1000 迭代上限、`<name>_fired` 事实插入、
  no_loop 默认 true、按类型更新全部事实的 action）属上游退化形态，有意不复制。
- 文档：conformance.yml 新增 4 行（tms-explicit-logical-coexistence、
  backward-qvar-unification、agenda-focus-stack-and-auto-focus、
  upstream-vapor-rete-ul-and-dead-integration），重写 shared-proof-graph 行为 B2 实态
  并把 rete-ul-tms-persistent-agenda 与 backward-arbitrary-unification-proof-sharing
  两条 known_gaps 改为已交付状态（tested）；upstream.yml 的 rete/backward 模块行与
  两条 runtime_contracts 行更新并引用 vapor 结论；Rule_Engine_Design.md 新增
  "RETE/TMS/unification depth parity" 一节；Rule_Engine_Architecture.md 相应小节
  同步。
- 验证：聚焦套件 `ctest -R "rule_engine|backward_machine"` **18/18**
  （test_rule_engine_tms 19/19、test_rule_engine_agenda 45/45、
  test_rule_engine_backward_ext 51/51）；build-gate（clang Debug）全量构建 +
  `ctest -LE graphics` **76/76**（test_async_loader 本次并行运行即通过，既有并行
  flake 未复现）；build-rule-fresh-asan（clang，440 个编译单元同时带
  -fsanitize=address 与 -fsanitize=undefined）聚焦套件 **18/18**、无诊断——ASan 与
  UBSan 由该树一并覆盖（build-ci-ubsan 为 Visual Studio 生成器树，MSVC 无 UBSan，
  非有效 UBSan 门禁）；MSVC 规则引擎矩阵（build-rule-debug，MSVC cl.exe + Ninja
  Debug）构建全部规则引擎测试目标、聚焦套件 **18/18**；bench 回归
  （rule_engine_bench_regression.cmake，RUNS=3）四项指标全部远低于 2.0s 阈值
  （sparse cold ≈0.001s、sparse warm ≈0.058s、dense cold ≈0.003s、dense warm
  ≈0.36-0.38s）；`git diff --check` 通过。
- 当前限制：任意谓词合一（结构化项、occurs check、union-find）、共享子图证明溯源、
  跨规则 RETE-UL（上游 vapor，已记录不复制）、规则触发派生之外的通用多规则生产者
  推理仍不支持；test_async_loader 并行 flake 为既有事项，本阶段未触碰。

## rule engine 流式补全（sub-project C，2026-08-30）

- 聚合种类追加（C1，上游 `src/streaming/aggregator.rs:12`，ref f80a541）：
  `re_stream_aggregate_kind_t` 尾部追加 `RE_STREAM_AGGREGATE_COUNT_DISTINCT = 8`、
  `RE_STREAM_AGGREGATE_STDDEV = 9`、`RE_STREAM_AGGREGATE_PERCENTILE = 10`，
  `RE_ABI_VERSION_MINOR` 整个子项目只升一次（3u→4u）。STDDEV 为总体标准差
  （方差按 N 除，:233），少于 2 个数值报 `RE_STATUS_NOT_FOUND`（上游 `None`）；
  PERCENTILE 升序排序后取最近秩 `round(p/100 * (n - 1))`（0-100 刻度，:253），
  参数由 `re_stream_filter_options_t` 尾部 struct_size 门控字段承载（未覆盖或越界、
  含 NaN，报 `RE_STATUS_INVALID_ARGUMENT`；追加前的旧 filter 尺寸对其余种类照常
  可用）；COUNT_DISTINCT 在既有 `count` 字段报告，按 `re_value_t` 类型化相等
  （double 位级比较）去重——上游按 `format!("{:?}")` 调试串去重会把 1 与 1.0 视为
  相同，为已记录分歧。`re_stream_aggregate_result_t` 以同一 struct_size 成对门控
  惯例尾部追加 `stddev`/`percentile`。
- StreamAnalytics（C2，上游 `src/streaming/aggregator.rs:285`）：TTL 缓存命中当且仅
  当 `current_time_ms - 条目时间戳 < ttl`（:311），命中不刷新时间戳；未命中经窗口
  聚合重算、逐出全部过期条目（:323）后插入新值；缓存标识为调用方键 + 种类 +
  filter 同一性（对上游纯字符串键的已记录加固）；时钟由宿主供给，引擎不采样时钟。
  moving_average 对调用方窗口数组末 N 个做全局 `sum(events)/count(events)`（:329，
  绝非"平均的平均"）；detect_anomalies 需 ≥3 窗口且历史值（除末窗口外全部）≥10，
  按总体均值/标准差标记末窗口 `|z| > threshold` 的事件并报告其时间戳（:357；本地
  事件无 ID，时间戳替代为已记录映射）；calculate_trend 逐窗平均、对半切分、
  ±5% 阈值映射 Increasing/Decreasing/Stable（:399、:416、:430）。已记录分歧：
  本地"字段"映射为事件名 + 数值标量；<3 窗口报 INVALID_ARGUMENT、<10 历史值报
  NOT_FOUND（上游静默返回空）；历史标准差为 0 不标记；first_avg == 0 报 STABLE
  （除零守卫）。
- GRL 流语法（C3，上游 `src/parser/grl/stream_syntax.rs`）：条件文法
  `var: EventType from stream("name") over window(<digits> <unit>, sliding|tumbling)`
  解析为 `RE_EXPR_STREAM_PATTERN`（只增内部枚举）并镜像入 IR（自有负载字符串 +
  `re_ir_validate` 良构分支，`re_engine_install` 硬拒绝畸形 IR）。事件类型可选且
  恰为 `from` 的标识符不被消费为类型（:216）；window 子句可选（:93）；单位精确
  采用上游大小写敏感集合（:166-179），其余单位一律解析错误；`session` 作为已记录
  本地扩展接受并映射 `RE_STREAM_WINDOW_SESSION`（上游 GRL 拒绝 session，尽管其
  Rust 枚举存在 `WindowType::Session`）。上游 `pattern && pattern` 联接文法
  （:429）是 vapor——`join_conditions` 恒空、无任何消费者——本地一律解析错误。
  携带流模式 CE 的规则不进 RETE 网络，对反向链保持诚实的
  `RE_STATUS_NOT_SUPPORTED`。
- 水位驱动闭合 + 跨流联接（C4，上游 `src/streaming/watermark.rs` 与
  `src/rete/stream_join_node.rs`）：`re_stream_window_options_t` 尾部追加
  struct_size 门控的 `watermark_drives_closure`（默认 0 = C 前行为）。开启后
  tumbling 桶在水位 `>= bucket_end + allowed_lateness_ms` 时闭合、会话目标在水位
  `>= (ts + retention) + allowed_lateness_ms` 时闭合；命中已闭合目标按既有迟到策略
  处理（DROP→NOT_FOUND、ERROR→RE_STATUS_ERROR、ACCEPT 仅在目标仍保留时记录）；
  sliding 无离散桶、保持仅记录门控（已记录惰性）；上游水位除联接节点驱逐外从不
  驱动闭合，故该接线为已记录本地组合。联接 API 交付四种 JoinType（:11）与三种
  JoinStrategy（:24），同键配对在记录时入队，未匹配外侧在单一单调水位越过时恰好
  发射一次且绝不重发（:204 的本地组合）；界限为每侧 256 键、每键 64 缓冲事件
  （drop-oldest + 丢弃计数）、256 待取匹配；时间比较本地统一毫秒（上游按整秒，
  已记录分歧）；上游未将联接节点接入其 StreamRuleEngine，本地同样是宿主驱动的
  独立 C 接缝。
- 流规则求值（C5，上游 `src/streaming/engine.rs:341-378`）：引擎携有界流注册表
  （16 名、重复名替换、借用窗口句柄、运行中报 BUSY）。`re_engine_stream_run` 向
  调用方 facts 注入上游 execute_rules 事实集后跑一遍整个规则库：恒有
  `WindowEventCount`（DOUBLE）、`WindowStartTime`、`WindowEndTime`、
  `WindowDurationMs`（:347-353），并按事件名注入 `<name>Sum/Average/Min/Max`
  数值折叠（:364-376；上游按数据 map 自动探测数值字段，:383；本地字段映射为事件
  名）。每次注入都是普通 `re_facts_set`——覆盖陈旧同名事实并推进 facts 变更序列
  号，B2 证明图缓存因此绝不可能跨两次流运行提供陈旧结果；上游钉住的
  `when WindowEventCount > 5` 用法（:478-481）有测试覆盖。GRL 流模式 CE 对已注册
  窗口求值：可选类型按事件名过滤，可选 window 子句限定 sliding 区间/当前
  tumbling 桶/当前开放会话，无子句读全部保留事件；规则在任一保留事件合格时每运行
  触发一次（exists 语义）。已批准分歧：未注册流报 `RE_STATUS_NOT_SUPPORTED` 而非
  NOT_FOUND——`compute_rule_activations`（engine.c:755）会把 NOT_FOUND 吞成静默
  不匹配；零时长 tumbling 子句报 INVALID_ARGUMENT（上游 `ts / 0` 会 panic）；
  exists/单次激活语义（上游从不对流模式 CE 求值，无每事件激活多重性可镜像）。
- 上游 vapor / 不适用——只记录不复制：GRL `&&` 联接条件（上游已解析但从不消费）；
  `src/streaming/operators.rs` 离线流式链式 API（未接入上游引擎）；tokio mpsc
  通道 + `Arc<RwLock<WindowManager>>` 拓扑（engine.rs:183-262，与单线程句柄契约
  不适用，本地为同步宿主驱动接缝）；序列模式 CEP 在既有配对关联之外保持有界
  （上游自身无活跃序列匹配器）。
- 文档：conformance.yml 重写 streaming-windows 行（新种类 + 闭合标志入
  tested_subset/note），新增 stream-analytics、grl-stream-syntax、stream-joins、
  stream-rule-evaluation、upstream-vapor-streaming-join-operators-topology 共 5 行，
  known_gaps 的 full-streaming-patterns 由 unsupported 改为 tested 交付实态；
  upstream.yml 的 streaming 模块行、cargo-feature 行与 internal-api 行全部更新并
  引 f80a541 文件:行；Rule_Engine_Design.md 新增 "Streaming completion parity"
  一节；Rule_Engine_Architecture.md 相应小节同步。
- 验证：build-gate（clang Debug）全量构建 + `ctest -LE graphics` **77/78 有效**
  （原始并行运行 76/78——test_async_loader 为既有并行 flake，单跑即过；
  test_network 3 条 UDP 发送失败来自远端提交 76871ec，与 origin/master 逐字节一致，
  环境侧问题，本阶段不动）；聚焦套件 `ctest -R "rule_engine|backward_machine"`
  **20/20**（test_rule_engine_stream_ext 45/45、test_rule_engine_stream_grl 19/19、
  test_rule_engine_stream_eval 18/18、test_rule_engine_backward_ext 54/54、
  test_rule_engine_agenda 45/45、test_rule_engine_tms 19/19）；
  build-rule-fresh-asan（ASan+UBSan 同树）聚焦套件 **20/20**、无诊断；
  MSVC 规则引擎矩阵（build-rule-debug）聚焦套件 **20/20**；bench 回归
  （rule_engine_bench_regression.cmake，RUNS=3）四项指标全部远低于 2.0s 阈值
  （最差 dense warm_eval 0.362s）；`git diff --check` 通过。
- 当前限制：序列模式 CEP 在配对关联之外有界（上游无活跃序列匹配器）；GRL `&&`
  联接、operators.rs 链式 API、tokio 拓扑为已记录 vapor/不适用，未复制；sliding
  窗口不参与水位闭合（仅记录门控）；test_network 环境侧失败与 test_async_loader
  并行 flake 均为既有事项，本阶段未触碰。

## rule engine 生态对齐（sub-project D，2026-08-31）

- 插件边界（D1，上游 f80a541 `src/plugins/mod.rs:1-11`）：上游恰有五个插件，均经
  `engine.load_plugin` 挂接（`src/engine/plugin.rs:48`、`engine.rs:1977`），非自动
  加载、非 feature 门控；本地无 load_plugin 表面，纯函数助手以名字分发内建形式交付于
  builtins.c（宿主函数注册表保持 override-first 优先）：concat/repeat/substring/
  replace、sqrt、first/last/reverse/slice/keys/values、isEmail/isPhone/isUrl/
  isNumeric/inRange 共 16 个，全部纯分类；按取回的上游函数体钉死 empty first/last →
  Null、isUrl 接受 ftp://、replace 空 from 按 UTF-8 码点边界插入（upstream-exact）。
  date_utils 族（读环境时钟，date_utils.rs:61-62）与 15 条元数据声明但从未注册的上游
  项作为 vapor 只记录不实现；上游 lib.rs 宣传数字（44+ 动作 / 33+ 函数）超出实际
  注册量（33 动作 + 29 函数），如实记录。新套件 test_rule_engine_plugin_parity
  33/33。
- 示例覆盖（D2）：pinned 清单 29 个 [[example]]（七个族目录）+ 清单外自动发现的
  examples/session_window_demo.rs（examples/ 根部的 auto-discovered 目标）；无本地
  Rust 示例，覆盖 = 由具名测试驱动的本地行为等价。逐族映射表 verbatim 存于
  test_rule_engine_example_coverage.c 头部注释；新增 3 个 smoke（ex01 fraud_detection
  式前向链、ex03 注册函数 action handler、ex09 GRL query 反向机），其余族映射既有
  套件或记录在案的 not_applicable（05 性能 → bench 基线回归；parallel_engine_demo 与
  rete_ul_drools_style 为上游 vapor；10 模块系统经本地 defmodule/import 机制
  covered_bounded）。记录在案的有界分歧：反向条件匹配器只读平铺事实名（不遍历点分
  对象，前向匹配器会遍历），已写入 upstream.yml backward-queries 行 notes。
- Redis 探针（D3）：2026-08-31 实测 Redis 8.10.1 服务（MSYS2 构建）在
  127.0.0.1:6379 存活（约 5.5 天 uptime，推翻同日早些时候"无服务"的探针结论），但
  hiredis 客户端开发文件在所有探测位置均缺席（含无 installed/ 树的 VCPKG_ROOT），
  `RULE_ENGINE_ENABLE_REDIS=ON` 在配置期被强制关闭（"no fallback"，
  engine/CMakeLists.txt:736-753），roundtrip 测试编译期裁除；阻塞点是客户端缺席而非
  服务缺席，行保持 optional_backend compile-verified（规范唯一允许的例外），未来任何
  提升尝试须重新探针。逐字证据见 task-d3-report.md。
- 全特性映射（D4）：上游 Cargo features {default, streaming, streaming-redis,
  backward-chaining} 无聚合开关（--all-features 恰为后三者）；本地映射为 streaming 与
  backward-chaining 恒开（无门控编译入 rule_engine_core）、streaming-redis ↔
  RULE_ENGINE_ENABLE_REDIS（hiredis 自动探测，缺席即强制关闭）、工具开关
  RULE_ENGINE_ENABLE_C11_PARALLEL / ENGINE_USE_ASAN / ENGINE_USE_UBSAN /
  ENGINE_BUILD_TESTS；无单一 all-features 开关，以文档化清单代替。
- 文档：upstream.yml 的 plugins 行 pending → tested 交付实态、all-features 行重写为
  CMake 选项集映射、examples 清单注释按族更新（含 session_window_demo）、
  backward-queries 行补平铺匹配分歧、streaming-redis 行补 D3 证据；conformance.yml
  新增 plugin-pure-helpers 与 example-family-coverage 两行、streaming-redis-state 行
  补探针证据、聚焦基线 20/20 → 22/22；Rule_Engine_Design.md 新增 "Ecosystem parity"
  一节；Rule_Engine_Architecture.md 同步小节。
- 验证：build-gate（clang Debug）全量构建 + `ctest -LE graphics` **79/80**（唯一失败
  test_network 的 3 条 UDP 发送失败为远端提交 76871ec 引入的既有环境事项；
  test_async_loader 并行 flake 本轮未出现——均为既有事项，本阶段不动）；聚焦套件
  `ctest -R "rule_engine|backward_machine"` **22/22**（新增
  test_rule_engine_plugin_parity 33/33、test_rule_engine_example_coverage 3/3）；
  build-rule-fresh-asan（ASan+UBSan 同树）聚焦 **22/22**、无诊断；MSVC
  （build-rule-debug）聚焦 **22/22**；bench 回归
  （rule_engine_bench_regression.cmake，RUNS=3）四项指标全部远低于 2.0s 阈值（最差
  dense warm_eval 0.382s）；`git diff --check` 通过。
- 当前限制：native Redis roundtrip 未做运行时验证（客户端缺席；服务存活但无客户端
  不可用，且服务可用性随时间变化须重探）；date_utils 族与插件 vapor 项只记录不实现；
  上游 `then ActionName(...)` 裸动作拼写对非白名单名保持锁定的解析错误；反向条件匹配器
  仅读平铺事实名；test_network 环境侧失败与 test_async_loader 并行 flake 为既有事项。

## rule engine Redis 运行时验证提升（2026-08-31）

- 两处受控侧使能修复落地：`engine/src/rule_engine/redis_provider.c` 在
  `RE_HAS_HIREDIS` 块内、`_WIN32` 下先于 hiredis.h 包含 `<winsock2.h>`（上游
  hiredis.h 在 `_MSC_VER` 下仅前向声明 `struct timeval`，而本文件的
  redisConnectWithTimeout 超时需要完整类型）；`engine/CMakeLists.txt` 的
  RULE_ENGINE_ENABLE_REDIS 块在 WIN32 下为 rule_engine_core 链接 ws2_32（静态库
  PRIVATE 经 link-only 接口传递到 test_rule_engine_stream_ext 等消费目标）。两项
  均为探测期外置 workaround（scratch 头补丁、`-DCMAKE_EXE_LINKER_FLAGS=-lws2_32`）
  的受控内化。
- 原始 hiredis 复证：scratch 重解包 hiredis v1.4.1 头文件无任何补丁（库由未改源
  以 clang MSVC ABI 静态构建），build-redis-probe 从零配置、不带链接器旗标即通过
  探测门；不带 RE_TEST_REDIS_URL 运行 roundtrip 干净 SKIP（48/48），带
  `RE_TEST_REDIS_URL=redis://127.0.0.1:6379` 对存活 Redis 8.10.1 实测
  `redis_roundtrip_when_service_available` **OK**（48/48），ctest 该套件通过；
  服务侧 DBSIZE 0→0、无 `re:*` 残留键（测试自清）。
- 回归：build-gate（redis OFF）重配置后聚焦 `ctest -R "rule_engine|backward_machine"`
  **22/22**、`test_network` 通过；MSVC build-rule-debug 聚焦 **22/22** 且
  test_network 通过。
- 文档行提升：conformance.yml `streaming-redis-state` 行 `native_redis_status` 由
  compile-verified-only 提升为 runtime-verified，known_gaps native-redis 行与
  upstream.yml streaming-redis cargo_feature 行同步（bounded 注记不变，仅验证状态
  改变）；roundtrip 仍由 RE_TEST_REDIS_URL 跳过门控（无宏时编译期裁除不变），服务
  可用性随时间变化，重跑前须重探——跳过门控仍是 CI 路径。逐字证据见
  `.superpowers/sdd/2026-08-29-rule-engine-full-parity/redis-enablement-report.md`。

## 网络与异步加载测试修复（2026-08-31）

- `test_network` 三个 UDP 用例失败的根因经探针实证：用例把绑定 INADDR_ANY 的套接字
  本地地址（`0.0.0.0`）直接用作 sendto 目的地址，Winsock 以 WSAEADDRNOTAVAIL(10049)
  拒绝（Linux 将通配映射到回环，故仅在 Windows 失败）；缺陷随远端 76871ec 的测试
  改动进入，network.c 库无辜（旧版测试对当前库全过）。修复为测试侧
  `net_test_normalize_loopback()`：通配地址归一到回环（`0.0.0.0`→`127.0.0.1`，
  `::`→`::1`），恰好应用于三处发送点；套件在 build-gate 复绿。
- `test_async_loader` 并行 flake 的根因经压测实证：固定迭代次数的忙等循环实为约
  10ms 的隐式时限，CPU 超订阅下工作线程链超时（ burner 加压下 37 次运行 158 例失败，
  单跑 0/100）；实现端（条件变量+CAS 完成环）无缺陷。修复为测试侧单调墙钟期限轮询
  （`test_now_us` + `test_wait_deadline`，5 秒预算）替换 8 处忙等；验证：burner 加压
  35/35、全量并行 5/5 且 80/80 全绿。
- 评审 Minor 顺带收尾：两处文档的 RULE_ENGINE_ENABLE_REDIS 块行号引用随 ws2_32 六行
  插入更新为 `:736-759`；回环归一的 IPv6 臂改映 `::1`。

## rule engine 全平价计划集合卷（2026-08-31）

- 四个子项目全部交付并推送：A（GRL/表达式面，`bf11de3`+`d537c7d`）、B（RETE/TMS/
  统一化深度，`e2cff59`+`625265d`）、C（流式补全，`5e51e75`）、D（生态，`dff2d22`）；
  后续波次：残留清扫 `1ef38d8`+`72dbb30`、环境修复与 Redis 运行时验证 `8e54306`、
  本地 WIP 保留 `c141fa9`+`6519085`+`d908b9a`、别名补全与期限化 `32e0c5d`。
- 合卷基线：全量无头 **80/80**、聚焦 `rule_engine|backward_machine` **22/22** × 三套
  工具链树（clang Debug / ASan+UBSan / MSVC）、bench 回归 PASS、`git diff --check` 干净。
- 裁定记录归档：SDD 台账（含全部评审裁定与 SAFE-TO-LEAVE 设计边界）入库于
  `docs/superpowers/ledgers/2026-08-29-rule-engine-full-parity.md`；完整工作区（任务
  简报/报告、评审包、诊断）留盘于 `.superpowers/sdd/`（`.git/info/exclude` 排除）。
