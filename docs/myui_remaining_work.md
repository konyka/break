# myui 后续阶段方案与状态

本文记录 `myui` 与 Break `Platform/RHI` 整合中仍未完成的能力、架构风险和
可执行的性能优先实施顺序。每个阶段必须先增加跨后端失败契约，再实现，最后
通过定向测试、构建矩阵和 sanitizer 门禁。

## 当前已完成

- 冷却按钮已完成：按钮成功 click 后以 PAL 单调时钟建立截止时间，冷却期间拒绝
  pointer down/up 重入；只在冷却期间创建一个 16ms 按钮级 timer 驱动失效和遮罩动画，
  截止时间到达后自动停止。remaining/progress 查询均做过期检测、饱和转换和无 PAL
  回退，销毁与 duration=0 会清理 timer。soft/GLES/Vulkan/Break RHI 统一复用
  `fill_rect` 与 RGBA 颜色，不引入后端特定 shader。

- CSS universal、多 class、最多 4 级祖先路径、typed descendant/direct-child 链、祖先
  type/class/id、selector specificity、source order 和 normal-slot specificity fallback。
  路径匹配使用固定数组并且查询零分配；完整 at-rule 语义仍未实现。
- 未知 CSS `@` 规则仍按兼容策略跳过，但跳过器现在能正确处理字符串转义、注释和嵌套
  block 的大括号，不会吞掉后续合法规则；结构错误仍硬失败，声明值错误仍按既有
  lenient 规则告警并跳过。
- UI 配置已废弃 XML，统一使用 YAML。loader 要求根对象包含字符串 `type`，控件属性
  使用类型化 YAML 标量，子控件使用 `children` 序列，MVVM 绑定使用 `bindings` map，
  窗口主题使用 `style` 字符串。非法类型、错误容器和 XML 输入均拒绝。
- YAML loader 直接消费 `my_conf` 类型树，不做字符串属性二次解析；整数范围、有限浮点、
  绑定规则 512 bytes 上限和 widget 构造失败均有明确失败路径，避免配置输入污染运行时树。
- YAML loader/parser TDD 定向测试现为 `14/14`，覆盖控件、嵌套子节点、绑定、错误类型、
  非 YAML 标记拒绝、输入大小、行数、block/flow 深度、集合规模和标量大小；UI 配置不再
  维护 XML DOM 资源预算或 XML 兼容层。flow/map key 同样受 1 MiB 限制，序列内联 map
  也拒绝重复键，避免替换语义掩盖配置错误。
- CSS 数值输入的有限值、整数范围和颜色 alpha 边界检查。
- UAX#14 实用子集的上下文规则：combining mark、数字标点、Unicode 数字小数分隔符、
  Hebrew quotes 和 Regional Indicator；新增
  shaping-aware paragraph model，按逻辑 codepoint 范围输出换行段，保护 ligature cluster
  不被拆分，并已接入 text area 的 wrap 重排。新增 Unicode glue（NBSP、figure space、
  narrow NBSP、word joiner）、ZWJ、variation selector、Emoji modifier 和 tag sequence
  扩展的不可断边界，所有规则均为 O(1) 上下文判断。
- 软件开放 contour 的 fill 自动闭合；开放 stroke 不自动闭合。
- 共享 surface damage 的逻辑坐标到 drawable scissor 纯函数；向外取整、裁剪和
  64 位乘法均有测试；新增 `SKIP/PARTIAL/FULL` 合成决策层，能力缺失、碎片过多或面积
  过大时安全回退全屏，当前默认 swapchain 仍不宣称保留未更新像素。
- 编辑器光标闪烁、变高列表 prefix-sum、跨后端 nearest/bilinear 已存在，不再作为
  未实现能力记录。
- text area wrap 重排采用候选 cache 事务：分配失败或 paragraph 构建失败不会清空旧
  visual lines，dirty 标志保持到下一次成功重建，避免 OOM 时文本内容静默消失。
- text area wrap 重排现采用前缀复用 + 后缀候选事务：编辑只从受影响物理行开始重排，
  未受影响的 visual-line 对象保持稳定；候选构建失败时保留旧缓存，避免大文档编辑每次
  修改都重新分配和扫描全文。
- text area 已支持可选物理行号栏和非重叠物理行折叠：默认关闭行号和折叠，折叠只保留
  header 行，wrap 时隐藏物理行不会生成 visual line；可见物理行有缓存，编辑导致物理
  行结构变化时安全清除折叠，避免偏移引用失效。可见行缓存 OOM 时使用不分配内存的线性
  回退，继续隐藏折叠行，不以错误的全物理行视图替代正确性。
- text area justify 在 wrap 的普通 LTR 路径中统一正文、选区和光标的 stretched-space
  坐标，避免固定 cell 宽度造成命中和编辑位置漂移；复杂 RTL 的 paragraph visual mapping
  仍按后续能力处理。
- text area IME 候选框锚点已复用 wrapped visual-line index 与 justify 边界，跨 visual line
  的候选框 y 坐标和拉伸空格后的 x 坐标保持一致；平台只消费 PAL 的统一全局坐标。
- text area 变宽字体的非 wrap 点击、水平滚动、光标和 IME 坐标已统一使用 glyph advance，
  无字体才走固定 cell fallback；当前 visual line 边界计算保持无额外缓存。
- text area pointer 垂直命中对负坐标和超出底部坐标做有符号边界钳制，避免负值转换为
  `size_t` 后错误跳到文档末尾；正常路径仍为常数开销。
- text area pointer y 命中复用统一的字体 line-height，避免带额外 leading 的字体按字号
  提前切换到下一行；不增加缓存或每帧扫描。
- text area 的 wrap 分页已按缓存中的 visual line 实现 `MY_KEY_PAGE_UP/DOWN`：长物理行
  会按 viewport 行数正确跨越，折叠行继续保持隐藏；目标查找复用已有二分索引和 RTL 边界
  映射，不新增 visual-line cache 分配且索引路径为 O(log V)。
- text area 绘制已使用 widget 生命周期内的可复用 scratch buffer：同一内容的后续重绘不再
  为每个 visual line 和光标临时分配字符串，容量仅在更长行出现时增长；普通 LTR 路径的
  scratch buffer 保持零新增 allocator 调用，分配失败继续走既有安全回退。
- JUSTIFY 单词绘制已改为 scratch buffer 原地切分并恢复分隔符，不再按单词分配临时字符串；
  连续绘制的分配契约覆盖普通 wrap 与 JUSTIFY 两条高频路径。
- visual-line cache 已保存 paragraph 提供的物理行内 byte 区间；绘制和光标文本准备直接
  复制缓存范围，避免长物理行按每个 visual line 重复扫描 UTF-8，保持可见字节数级别的
  工作量和既有 codepoint 坐标 API。
- RTL 绘制已在 widget scratch 文本未变化时跨帧复用 layout：默认方向对齐、选区矩形共享
  同一对象，光标方向判断和 visual-x 计算也只构建一次；scratch 改变会事务式失效旧对象，
  居中/右对齐等无需方向 layout 的路径继续保持快速分支。
- text area 已加入当前热物理行的 glyph boundary 前缀缓存：命中测试、光标、选区和 IME
  查询复用同一组 advance，重复边界查询为 O(1)；文本 revision、字体或字号变化会失效，
  OOM 时保留原逐 codepoint fallback，不为整篇文档增加几何缓存。
- 文本布局与 paragraph 入口增加 4 MiB 字节预算；超限输入在缓存、复制和字体测量前
  有界拒绝，拒绝路径不调用调用方 allocator，正常路径保持原有缓存与排版复杂度。
- 新增后端无关的 `my_syntax_cache_t` 行级增量 lexer：C-like/YAML 词法 token、跨行
  block-comment 状态、后缀失效和每次重建预算均有明确边界；text area 现以懒创建和
  `syntax_line_budget` 消费 ready 行，并在非 RTL、有字体路径进行 token 颜色分段绘制。
  默认关闭时保持零 cache、零全文扫描；无字体、RTL、justify 继续回退整行绘制。
- vgcanvas 已提供零分配的 capability 查询；AA/filter 请求先检查能力，状态只在后端
  成功后更新并对重复请求短路。GL 只有当前 surface 报告 multisample 时才暴露 level 2；
  Break RHI/Vulkan 的真实 offscreen target 已支持设备能力允许的 2x+ 路径。
- 独立 Vulkan vgcanvas 现按 physical-device 与 image-format 能力报告 1x/2x/4x AA；
  level 切换、resize 和 swapchain out-of-date 重建均先构造 candidate target、render pass、
  pipeline 与 descriptor 资源，设备空闲且候选完整后一次性交换。创建、验证或提交失败只
  清理 candidate，不销毁 active；候选 MSAA 失败不再静默降级。顶层 `ENGINE_VULKAN` 现在
  同时启用 `myui_core` 的 Vulkan 编译定义与链接依赖。
- 新增后端无关的 sample-count/resize 事务 helper：候选资源按 `create -> validate ->
  submit -> activate -> retire` 提交；创建、验证或提交失败只销毁 candidate，保留
  active resource、样本数和尺寸。相同请求零分配、零重建；支持的样本数通过显式的
  power-of-two capability mask 表示。该 helper 已由 fake 状态机覆盖；BreakUI 的 resize
  与 AA 切换已接入同等的 candidate/active/retire 生命周期，独立 Vulkan vgcanvas 仍保留
  自己的 backend-specific target 边界。
- Break RHI 已新增只读 `RHICapabilities` 查询：统一报告后端类型、颜色/深度样本数能力、
  当前 surface 样本数和 resolve 能力；GL 从当前上下文查询，Vulkan 从 physical-device
  sample-count limits 与 depth-stencil resolve properties 查询。查询本身无分配、无同步、
  无状态改变。
- RHI 新增 `RHIOffscreenFBODesc` 与无副作用的 descriptor validation；旧创建 API 明确保持
  `1x`，不会因新增能力改变现有渲染行为。OpenGL 的 descriptor 路径已实现 multisample
  color/depth renderbuffer、单采样可读 texture 和切换时 resolve；Vulkan 使用 multisample
  color/depth attachment、单采样 resolve attachment 及匹配 sample-count 的 render-pass/
  pipeline variant。能力不足时明确拒绝，不静默降级。
- 已修复 resize 与 AA 请求同帧合并时 pending 请求被清除的缺陷；候选 target 激活后仍会
  保留尚未满足的 AA 请求，直到下一次 render 边界成功切换。OpenGL 候选 FBO 的 multisample
  renderbuffer、resolve FBO 和可采样纹理也统一走失败清理路径，避免资源泄漏。
- 已加入可选 OpenType shaping 契约：启用 `MYUI_HARFBUZZ` 且存在 FreeType/HarfBuzz 时，
  字体后端输出 glyph id、cluster、26.6 advance/offset；缺少依赖或后端不支持时返回
  `MY_RET_NOT_SUPPORTED`。Break RHI、GLES/OpenGL、Vulkan 和 soft canvas 的纯 LTR 路径
  已消费 glyph-run，并使用独立 glyph-id raster/cache key；shaping 失败仍回退 Unicode
  codepoint 路径。
- YAML UI 文件入口现于 payload 分配前检查 4 MiB 文件预算；超限输入立即关闭文件并失败，
  不再先申请整文件缓冲；文件中的嵌入 NUL 也明确拒绝，避免后续 YAML 字节被 C 字符串
  截断。字符串 loader 与 parser 的既有行数、深度、集合和标量预算保持不变；JSON、TOML
  与 BSON 直解析入口同样受 4 MiB 输入预算保护。
- RHI 窗口截图现提供带目标缓冲区长度的统一 RGBA8 API；GL 和 Vulkan 均在后端读回前
  校验 drawable 边界、零尺寸、乘法溢出和目标容量。Vulkan 继续使用一次性 staging
  buffer 与队列等待，失败返回 `false` 且不触碰目标缓冲；截图是诊断路径，不进入每帧热路径。

## 未完成能力

| 能力 | 当前边界 | 主要风险 | 完成判据 |
| --- | --- | --- | --- |
| OpenType shaping | 可选 HarfBuzz + FreeType glyph-run 已接入四个 canvas 的 LTR 与受限 bidi visual-run 绘制/测量；完整 script/features 级 paragraph shaping 仍未完成 | glyph/advance 与逻辑边界错配、字体缓存跨 key 污染、复杂 RTL 视觉顺序错误 | 保持 glyph-id/codepoint 独立缓存；golden glyph/advance、禁用依赖回退和四后端构建；后续补 script/features 级 run shaping |
| 复杂 RTL rebreaking | paragraph 按逻辑范围生成 cluster-safe wrapped lines，text area 已消费该模型；RTL 行内视觉映射和跨 face glyph-run 已接入，跨段落增量预算与 JUSTIFY selection 联动仍未完成 | 光标、选区和 line hit-test 在 bidi run/换行边界错位 | 段落模型 golden visual order、重排后逻辑映射、JUSTIFY/selection 契约；后续补完整 script/features run shaping |
| 高级编辑器 | 物理行折叠支持严格包含嵌套、有界 YAML v1 状态快照、legacy v0/无版本快照显式升级、可见行缓存 O(rows+ranges) 构建、OOM 正确性回退、行号栏、wrap 增量缓存、visual-line 分页、绘制 scratch 复用、行级 lexer、LTR/RTL 受限 token 着色已实现；完整 RTL GSUB、跨 face token shaping 和 JUSTIFY 联动未实现 | 大文档单帧 O(n) 卡顿、折叠后索引失效、token 状态跨行污染 | 继续保持 lexer/cache 单帧预算，并补齐 paragraph/run 级 RTL shaping |
| 真 partial present | 已完成后端无关的 `SKIP/PARTIAL/FULL` 决策、RHI 有界 damage 帧接口、Wayland EGL buffer-age/damage-present 接入和 dxx 集成；Vulkan 仍安全全屏，`VK_KHR_incremental_present` 不启用为能力位，因为该扩展不保证 present 后 swapchain image 内容可被 `LOAD`；新增固定容量 `rhi_present_history` 作为未来具备明确保留契约的平台基础；X11/Win32/macOS 仍安全全屏 | 未损伤区域内容丢失、WSI 内容保留语义误用、Vulkan 缺少标准 buffer-age/内容保留契约、真实平台能力未覆盖 | 具备明确 image 保留保证的 Vulkan/WSI 方案；X11/Win32/macOS runtime smoke；Wayland compositor smoke；异常 present 与真实 image 轮转验证 |
| 完整 UAX#14 | SA dictionary、复杂 numeric/context tailoring、部分 LB 类别和完整 UCD 版本规则仍未覆盖；当前实用子集已覆盖 combining mark、Unicode 数字小数分隔符、Hebrew quotes、Regional Indicator、Unicode glue、joiner 与 emoji 扩展 | 错误断词或标点孤行 | 版本化 UCD golden corpus + 超长输入预算测试 |
| 完整 CSS/YAML UI | CSS 已支持最多 4 级祖先路径、descendant/direct-child 链及祖先 type/class/id；完整 at-rule 语义仍未实现；YAML UI loader 已替代 XML 并采用类型化 schema；CSS/YAML/JSON/TOML/BSON 入口均有 4 MiB 输入预算 | 解析器静默接受错误、运行期主题污染、恶意输入耗尽内存 | capability registry、strict diagnostics、schema/bridge 回滚测试；继续评估 at-rule 语义 |
| 平台 runtime CI | Windows 已有无 graphics 的 Win32 platform smoke（UTF-8 标题、非法输入、WM_SIZE、销毁）；macOS/Wayland compositor 仍缺本机 runtime 矩阵 | 构建通过但 DPI、IME、present 在实际 compositor 失败 | Windows platform smoke + 各平台启动 smoke + HiDPI/IME/resize/present 证据；当前 smoke 不代表 GPU/WGL/Vulkan 成功 |

### 冷却按钮契约

`my_button_set_cooldown(button, duration_ms)` 设置下一次成功 click 后采用的默认冷却时长。
`duration_ms == 0` 会禁用冷却并立即取消动画 timer；修改非零 duration 不会中断当前
冷却，只影响下一次 click。`my_button_is_cooling_down()` 每次按当前 PAL 单调时钟检查
deadline，不能以 timer 是否存在作为业务判断。`remaining_ms` 返回饱和值，
`cooldown_progress` 返回 `[0, 1]`，其中 `1` 表示刚开始、`0` 表示完成。

冷却中的按钮不进入 pressed 状态，也不发出 `click`。成功 click 先建立 deadline 再
发射事件，防止同步回调重入绕过限制。动画是从上到下的半透明公共 canvas 遮罩；timer
抖动不会改变实际冷却时长。没有 PAL/loop 时查询仍安全，按钮可在挂载后正常获得动画
驱动；timer 创建失败不影响 deadline 检测和输入安全。

性能约束：非冷却状态无 timer、无逐帧扫描、无堆分配；冷却期间每个按钮最多一个
timer，每 tick 只读取单调时间、计算进度和 invalidate。按钮销毁始终先移除 timer，
避免回调访问已释放对象。

## 实施顺序

### 阶段 A：基础契约与观测

1. 保持 `my_vgcanvas` 公共 API 稳定；新增只读 RHI capability query，不让 widget
   直接依赖 Vulkan/OpenGL 类型。
2. 为所有候选资源采用 `create -> validate -> submit -> activate -> retire` 状态机；
   失败只释放 candidate，不触碰 active resource。resize 与 sample-count 必须共用
   同一事务，避免窗口尺寸变化和质量切换产生两个不一致的生命周期。
3. 为每帧记录 damage area、draw calls、atlas misses、layout passes 和 fallback
   次数；默认关闭高成本日志，诊断模式才采样。

### 阶段 B：GPU AA

1. 先写 fake device 的能力和事务测试：支持/不支持/创建失败/提交失败/重复设置。
2. RHI 提供 color/depth sample count 和 resolve compatibility 查询；GL 读取已创建
   surface 能力，Vulkan 使用 physical-device limits 与 depth-stencil resolve properties。
3. 离屏 target 增加 sample-count descriptor；MSAA color/depth 与单采样 resolve target
   一起候选创建，render pass/pipeline 全部验证后再激活。Vulkan shadow/MRT 多采样 pipeline
   在 attachment 契约完整实现前明确拒绝，避免误用 1x render pass。
4. 旧 target 保持可用直到新 target 首次提交成功；resize、DPI、device lost 都走
   同一事务路径。设备不支持时返回 `MY_RET_NOT_SUPPORTED`，不静默降低用户设置。

### 阶段 C：可选 HarfBuzz shaping

1. CMake 自动检测 HarfBuzz，默认可选；关闭或缺失时保留现有 Arabic fallback。
2. 以 UTF-32 paragraph/run 为输入，按 script、direction、font identity 和字号
   分割 shaping run；输出 glyph id、advance、offset 与 logical span。
3. 缓存键必须包含字体身份、face index、字号、script、direction、feature set 和
   text hash；缓存容量固定上限，命中失败只回退当前 run。
4. 已接入测量与 Break RHI、GLES/Vulkan/soft 的 glyph upload；任一后端失败
   不改变其他后端路径。当前限制是纯 LTR 直连 face，RTL 仍由现有 UBA/Arabic fallback
   路径负责，fallback chain 仍按 codepoint 路由。

### 阶段 D：段落、编辑器和断行

1. 已新增 paragraph model，保留逻辑 codepoint 范围并让 text area wrap 共用该结果；
   下一步把每个 line 的 visual layout、justify、selection、cursor 也统一到 paragraph-owned mapping。
2. 使用增量 dirty paragraph 队列和每帧预算；长文档只重排受影响行及其邻接上下文。
3. 行号、折叠和语法高亮只消费行模型，不进入 widget paint 回调；折叠区间使用
   checked interval tree，所有偏移转换做边界检查。

### 阶段 E：Present 与平台矩阵

1. 先让平台报告 damage/retained-buffer/partial-present 能力；没有三者时继续全屏
   composite，禁止仅凭 dirty rect 设置 scissor。
2. 有 retained backbuffer 时按 dirty area 与全屏成本阈值选择局部合成；合并区域超过
   预算即全屏，避免碎片化 draw call。
3. Wayland 使用 compositor 认可的 damage API；X11/Win32/Cocoa 分别验证 buffer age、
   swap semantics 和 resize；Vulkan WSI 只在 explicit synchronization 契约成立时启用。

## 统一 TDD 与安全门禁

- 单元：每个新增能力先有失败测试；测试输入覆盖空值、边界、溢出、分配失败和重复调用。
- 跨后端：`build-myui`、`build-myui-vk`、Wayland GL/VK；没有本机 runtime 时只报告
  build/headless 证据，不声称运行时通过。
- Sanitizer：ASan/UBSan 覆盖 CSS、文本、damage、资源生命周期；线程相关改动再跑
  TSan，协议队列不允许等待外部 owner。
- 性能：固定 corpus 对比布局时间、峰值内存、draw call、atlas miss 和 composite
  像素面积；性能优化不得牺牲 active resource 回滚和输入预算。
- 交付：文档、测试和实现一起提交；`git diff --check`、乱码扫描、工作区清洁后才推送。

## 已完成：syntax token byte range cache（2026-08-26）

- 以 TDD 新增 `syntax_cache_records_utf8_token_byte_ranges`，先验证多字节 UTF-8
  identifier、ASCII keyword 和 number 的 codepoint/byte 范围同时准确记录。
- lexer 在已有 `at/cp` 单次扫描中填充 `start_byte/len_bytes`；text area syntax paint
  直接使用范围裁剪 wrapped visual line，删除每个 token 调用 `ta_byte_at_cp()` 的
  物理行首扫描，连续 token 绘制不再产生 token 数量乘行长度的重复工作。
- 复杂度：词法分析 O(line bytes + token count)，整 token 绘制 O(1)，每个 visual line
  最多处理其首尾边界 token；codepoint 坐标、后端中立 API、lexer 行预算和失败回退
  行为保持不变。
- 验证：normal/ASan 的 `test_myui_text_layout` **14/14**、
  `test_myui_window_manager` **55/55** 通过，Vulkan `myui_core` 构建通过；全量
  非图形 ctest 仍受当前构建目录缺少历史测试二进制影响，且已有无关的网络测试失败，
  不将这些结果归因于本改动。后续继续审查 paragraph-owned mapping、HarfBuzz shaping
  与 partial present。

## 已完成：visual line physical-row index cache（2026-08-26）

- 以 TDD 新增 `text_area_visual_line_index_cache_tracks_folds_and_edits`，覆盖 wrap
  行映射、折叠隐藏行、整段编辑后的重建；新增
  `text_area_visual_line_index_cache_oom_falls_back` 覆盖索引分配失败回退。
- `my_text_area` 为每个物理行缓存首尾 visual index，命中后只在该物理行的连续 visual
  段内二分；缓存不改变 visual line 所有权、paragraph byte span 或后端 API。
- 映射最多分配 `2 * physical_line_count * sizeof(size_t)`，OOM 时释放候选并回到旧的
  全量二分，不重试每次查询；折叠、编辑、wrap/字号/宽度重排统一失效，避免旧索引
  指向新文本。
- 验证：normal/ASan 的 `test_myui_window_manager` **57/57**、
  `test_myui_text_layout` **14/14** 通过，Vulkan `myui_core` 构建、
  `git diff --check` 与乱码/控制字符扫描通过。

## 已完成：RTL interaction layout cache（2026-08-27）

- 以 TDD 新增 `text_area_rtl_hit_test_reuses_layout`，先证明连续 pointer hit-test 会
  重复分配 visual line 文本和 layout，再实现 widget-owned 单条缓存。
- 键盘左右移动、上下移动、Home/End、PageUp/PageDown 与 pointer hit-test 共享当前
  visual line 的 layout；缓存键包含 text revision、物理行、byte span、字体和字号，
  文本编辑与字体变化自动失效。
- 命中路径无临时复制、无 layout 分配；纯 LTR 仍无 layout 开销，OOM 或 layout 失败
  保持原有安全回退。生命周期在 widget destroy 中释放，核心 API 与 soft/GLES/Vulkan/
  Break RHI 边界不变。
- 验证：normal `test_myui_window_manager` **58/58** 通过；ASan、Vulkan 和文档门禁
  在本阶段收尾复验。

## 已完成：text layout visual boundary prefix cache（2026-08-27）

- 以 TDD 新增 `text_layout_reuses_font_boundary_prefix_cache`，验证视觉 x、命中测试和
  selection rects 首次计算字形宽度，连续查询不再重复调用 glyph；字号变化会重建。
- `my_text_layout_t` 按调用者 layout 缓存 visual boundary 前缀和，键为字体指针与字号。
  `visual_x` 为 O(1)，`logical_at_x` 在前缀和上二分，selection rects 复用宽度，首次
  建立为 O(visual items)。
- 分配失败保留旧缓存并回退原逐字形路径；缓存由 layout destroy 释放，不影响全局 LRU
  master、glyph-run、soft/GLES/Vulkan/Break RHI API 或字体无关的 bidi 映射。
- 验证：normal/ASan `test_myui_text_layout` **15/15**，normal/ASan
  `test_myui_window_manager` **58/58**，Vulkan `myui_core` 构建和编码门禁通过。

## 已完成：selection rect bounded output（2026-08-29）

- 以 TDD 新增 `text_layout_visual_rects_honors_output_capacity`，先复现多视觉片段时
  API 返回值超过 `cap` 的契约缺陷。
- `my_text_layout_visual_rects()` 在缓存和逐字形回退路径都严格返回 `0..cap`，写满
  输出后立即结束，避免在 text area/edit 只请求固定小数组时继续扫描。
- 保持 RTL 分段顺序、字体宽度、OOM 回退和跨后端绘制行为不变；公共头文件同步明确
  有界返回契约。
- 验证：`test_myui_text_layout` **16/16** 通过；normal/ASan/Vulkan 门禁已复验。

## 已完成：fold-state YAML legacy migration（2026-08-29）

- 以 TDD 新增 `text_area_fold_state_yaml_roundtrip_and_transaction` 的显式 v0 输入断言，
  先验证 loader 错误拒绝 legacy 版本号。
- `version: 0` 现在表示旧版 `folds` schema，与既有无 version legacy 输入使用相同的严格
  字段、范围、数量和字节预算；成功导入后 exporter 始终生成 `version: 1`，形成可观测的
  单向升级，不增加绘制或编辑热路径成本。
- 保持未知版本拒绝和事务回滚语义；不恢复 XML 兼容层，不引入全局迁移状态。
- 验证：normal/ASan `test_myui_window_manager` **58/58**，Vulkan `myui_core` 构建及
  编码门禁通过；LeakSanitizer 继续使用 `detect_leaks=0` 规避当前 ptrace 环境限制。

## 已完成：RTL syntax token painting（2026-08-29）

- 以 TDD 新增 `text_area_rtl_syntax_colors_tokens`，旧实现因 RTL 保护分支退回整行普通
  颜色，测试先验证带 YAML keyword 的 RTL 行与无高亮基线完全相同。
- RTL token 绘制复用 `my_text_layout_t` 的 visual UTF-8 与 visual boundary prefix，按
  visual-order 连续片段设置 token 颜色；token logical 范围用二分查找，避免 token 数量乘
  visual item 数量的扫描。LTR 路径保持原单次 token 测量。
- 新增 `my_text_layout_visual_boundary_x()`，将视觉边界坐标作为公共 core 契约；不依赖
  GL、Vulkan、soft、Break RHI 或平台类型。复杂 RTL GSUB、跨 face fallback 与 JUSTIFY
  token 联动仍由 shaping/paragraph 阶段处理。
- 同步修复内置 bitmap font 的 1bpp-to-8bpp 边界缺陷：创建时展开固定 8x8 alpha 块，避免
  绘制时越界读取，并保持每帧零格式转换。
- 验证：normal/ASan `test_myui_window_manager` **59/59**、normal/ASan
  `test_myui_text_layout` **16/16**，Vulkan `myui_core` 构建及编码门禁通过；LeakSanitizer
  使用 `detect_leaks=0`。

## 已完成：跨字体 glyph-run 事务与 RTL run 顺序（2026-08-31）

- 以 TDD 新增字体链跨 face shaping 测试：Latin/CJK 连续片段分别调用对应 face，输出
  glyph 保存实际字体身份，cluster 继续使用原始 UTF-8 byte offset；四个绘制后端的
  glyph-id 栅格化与 atlas/texture cache 均按 `(font, glyph id, size, key kind)` 区分。
- 字体链的 LTR 单 face 路径保持原有快速路径；RTL 仅在确实跨 face 时建立有界 run 表，
  以逆序提交 face run，避免 CJK fallback 片段在视觉顺序中落到错误位置。候选结果全部
  成功后才交付，任一 segment、扩容或 allocator 失败都会释放候选并清空结果。
- 新增逐分配点 OOM 回滚测试和跨 face RTL 顺序测试；未声明 HarfBuzz/FreeType 时测试
  仍编译为显式 skip，不改变旧 codepoint fallback。
- 当前已把 paragraph bidi run 的 direction、logical byte cluster 和实际字体身份统一
  交给 glyph-run API，并接入四个 canvas；仍未宣称完整 RTL OpenType，script/features
  配置、selection/cursor/justify 的 paragraph-owned glyph mapping 还需继续完善。
- 验证：普通字体/后端测试 **8/8、24/24**，Vulkan 字体/后端测试 **8/8、25/25**，
  ASan 字体/后端测试 **8/8、24/24**；无 HarfBuzz 配置也完成 **8/8、24/24**，其中
  shaping 专项按契约 skip。以上是构建目录定向证据，不替代 Windows/macOS/Wayland
  真实 runtime 验证。

## 已完成：paragraph bidi glyph-run 接入（2026-09-01）

- 新增 `my_text_layout_shape()`：按布局的视觉 bidi run 还原逻辑 UTF-8 输入，按 resolved
  direction 调用字体 shaping，再按视觉顺序合并 glyph；cluster 映射回原始 UTF-8 byte
  offset，并保留实际 face 身份。
- soft、GLES2、Vulkan、Break RHI 的复杂文本绘制和测量统一消费该 glyph-run；字体不支持
  shaping 时显式回退原 visual codepoint 路径，其他错误不提交部分结果。
- 输入长度、run 数量、数组乘法、重复 logical mapping 和 allocator OOM 均有边界检查；
  layout 还保存 caller-owned logical UTF-8 副本，拒绝不匹配输入或非 codepoint 边界的
  provider cluster；输出采用候选事务，失败时清空结果，避免 selection/cursor 使用半成品。
- 当前仍未宣称完整 Unicode script/features shaping：段落的 script 分段、OpenType feature
  配置、跨段落增量 rebreaking 和 JUSTIFY selection 联动留作后续阶段。
- 验证：文本布局 **23/23**，普通字体/后端 **8/8、25/25**，Vulkan 字体/后端 **8/8、25/25**，
  无 HarfBuzz **23/23、8/8、24/24**，ASan **23/23、8/8、24/24**。
  `engine/build` 全量 CTest 中实际存在的 77 个测试全部通过；4 个未生成的可选
  rule-engine 目标为 `Not Run`，不属于本轮源码回归失败。
