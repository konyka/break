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

- CSS universal、多 class、typed direct-child、selector specificity、source order
  和 normal-slot specificity fallback。
- 未知 CSS `@` 规则仍按兼容策略跳过，但跳过器现在能正确处理字符串转义、注释和嵌套
  block 的大括号，不会吞掉后续合法规则；结构错误仍硬失败，声明值错误仍按既有
  lenient 规则告警并跳过。
- XML subset 现在拒绝重复属性，避免 `my_xml_node_attr()` 的 first-value-wins 歧义；
  实体、CDATA、未引用属性和 root 尾部内容继续按结构契约校验。
- CSS 数值输入的有限值、整数范围和颜色 alpha 边界检查。
- UAX#14 实用子集的上下文规则：combining mark、数字标点、Unicode 数字小数分隔符、
  Hebrew quotes 和 Regional Indicator；新增
  shaping-aware paragraph model，按逻辑 codepoint 范围输出换行段，保护 ligature cluster
  不被拆分，并已接入 text area 的 wrap 重排。新增 Unicode glue（NBSP、figure space、
  narrow NBSP、word joiner）、ZWJ、variation selector、Emoji modifier 和 tag sequence
  扩展的不可断边界，所有规则均为 O(1) 上下文判断。
- 软件开放 contour 的 fill 自动闭合；开放 stroke 不自动闭合。
- 共享 surface damage 的逻辑坐标到 drawable scissor 纯函数；向外取整、裁剪和
  64 位乘法均有测试，但暂不把它冒险用于默认 swapchain composite。
- 编辑器光标闪烁、变高列表 prefix-sum、跨后端 nearest/bilinear 已存在，不再作为
  未实现能力记录。
- text area wrap 重排采用候选 cache 事务：分配失败或 paragraph 构建失败不会清空旧
  visual lines，dirty 标志保持到下一次成功重建，避免 OOM 时文本内容静默消失。
- vgcanvas 已提供零分配的 capability 查询；AA/filter 请求先检查能力，状态只在后端
  成功后更新并对重复请求短路。GL 只有当前 surface 报告 multisample 时才暴露 level 2；
  Break RHI/Vulkan 的真实 offscreen target 已支持设备能力允许的 2x+ 路径。
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

## 未完成能力

| 能力 | 当前边界 | 主要风险 | 完成判据 |
| --- | --- | --- | --- |
| GPU AA 动态协商 | capability 查询、非法请求拒绝、GL/Vulkan offscreen MSAA target、Vulkan 深度 resolve、pipeline/render-pass sample variant、BreakUI 事务切换、失败回滚和真实 2x smoke 已完成；完整 Vulkan vgcanvas 私有 backend 与窗口级独立 swapchain AA 仍未接入 | 重建失败后切换半成品 target、不同后端 sample/resolve 语义不一致、同步错误 | fake RHI 状态机 + BreakUI candidate/active 生命周期 + GL target/readback smoke + Vulkan 2x draw/resolve/destroy + validation clean |
| OpenType shaping | 可选 HarfBuzz + FreeType glyph-run 已接入四个 canvas 的纯 LTR 绘制与测量；RTL/跨 face fallback chain 暂不伪装支持完整 shaping | glyph/advance 与逻辑边界错配、字体缓存跨 key 污染、复杂 RTL 视觉顺序错误 | 保持 glyph-id/codepoint 独立缓存；golden glyph/advance、禁用依赖回退和四后端构建；后续补 paragraph/run 级 RTL shaping |
| 复杂 RTL rebreaking | paragraph 按逻辑范围生成 cluster-safe wrapped lines，text area 已消费该模型；RTL 行内视觉映射、跨 face shaping、多段落增量预算和 JUSTIFY selection 联动仍未完成 | 光标、选区和 line hit-test 在 bidi run/换行边界错位 | 段落模型 golden visual order、重排后逻辑映射、JUSTIFY/selection 契约；后续补完整 RTL run shaping |
| 高级编辑器 | 行号、折叠、增量语法高亮未实现 | 大文档单帧 O(n) 卡顿、折叠后索引失效 | 行模型增量更新、预算化重排、折叠/行号/高亮 TDD |
| 真 partial present | 默认 swapchain 每帧清屏，全屏 composite；无平台 damage 协商 | 未损伤区域内容丢失、Wayland/X11/WSI 语义不一致 | 平台 capability + 保留 backbuffer + dirty threshold + 每平台 smoke |
| Vulkan 窗口 readback | 仅离屏 readback；WSI readback 明确不支持 | 传输 usage、layout、fence 和窗口性能回归 | 显式截图 API、尺寸预算、staging/fence、validation clean |
| 完整 UAX#14 | SA dictionary、复杂 numeric/context tailoring、部分 LB 类别和完整 UCD 版本规则仍未覆盖；当前实用子集已覆盖 combining mark、Unicode 数字小数分隔符、Hebrew quotes、Regional Indicator、Unicode glue、joiner 与 emoji 扩展 | 错误断词或标点孤行 | 版本化 UCD golden corpus + 超长输入预算测试 |
| 完整 CSS/XML | 复杂 combinator、at-rule 语义、完整 selector tree 未实现；未知 at-rule 的结构化跳过和 XML 重复属性拒绝已实现 | 解析器静默接受错误、运行期主题污染 | capability registry、strict diagnostics、AST/bridge 回滚测试 |
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
