# myui 后续阶段方案与状态

本文记录 `myui` 与 Break `Platform/RHI` 整合中仍未完成的能力、架构风险和
可执行的性能优先实施顺序。每个阶段必须先增加跨后端失败契约，再实现，最后
通过定向测试、构建矩阵和 sanitizer 门禁。

## 当前已完成

- CSS universal、多 class、typed direct-child、selector specificity、source order
  和 normal-slot specificity fallback。
- CSS 数值输入的有限值、整数范围和颜色 alpha 边界检查。
- UAX#14 实用子集的上下文规则：combining mark、数字标点和 Regional Indicator。
- 软件开放 contour 的 fill 自动闭合；开放 stroke 不自动闭合。
- 共享 surface damage 的逻辑坐标到 drawable scissor 纯函数；向外取整、裁剪和
  64 位乘法均有测试，但暂不把它冒险用于默认 swapchain composite。
- 编辑器光标闪烁、变高列表 prefix-sum、跨后端 nearest/bilinear 已存在，不再作为
  未实现能力记录。
- vgcanvas 已提供零分配的 capability 查询；AA/filter 请求先检查能力，状态只在后端
  成功后更新并对重复请求短路。GL 只有当前 surface 报告 multisample 时才暴露 level 2；
  Break RHI/Vulkan 在事务式 sample-count target 尚未接通前只暴露 level 0。
- 新增后端无关的 sample-count/resize 事务 helper：候选资源按 `create -> validate ->
  submit -> activate -> retire` 提交；创建、验证或提交失败只销毁 candidate，保留
  active resource、样本数和尺寸。相同请求零分配、零重建；支持的样本数通过显式的
  power-of-two capability mask 表示。该 helper 已由 fake 状态机覆盖，但尚未接入真实
  Vulkan 或 Break RHI。

## 未完成能力

| 能力 | 当前边界 | 主要风险 | 完成判据 |
| --- | --- | --- | --- |
| GPU AA 动态协商 | capability 查询、非法请求拒绝、失败回滚、GL surface multisample 识别和后端无关的 target/resize 事务 helper 已完成；Vulkan/Break RHI 公共 level 2 仍未开放，Vulkan 仅有内部 MSAA 选择 | 重建失败后切换半成品 target、render-pass 不兼容、同步错误 | fake RHI 状态机 + Vulkan/Break RHI adapter 创建失败回滚 + 真实窗口 smoke |
| OpenType shaping | Arabic fallback，不含完整 GSUB/GPOS、mark positioning、脚本 shaping | glyph/advance 与逻辑边界错配，字体缓存跨字体污染 | HarfBuzz 可选构建；golden glyph/advance、fallback、cache key 和禁用依赖构建 |
| 复杂 RTL rebreaking | 单段落 UBA visual reorder；多段落/换行后 visual-order 重排未完成 | 光标、选区和 line hit-test 错位 | 段落模型 golden visual order、重排后逻辑映射、JUSTIFY/selection 契约 |
| 高级编辑器 | 行号、折叠、增量语法高亮未实现 | 大文档单帧 O(n) 卡顿、折叠后索引失效 | 行模型增量更新、预算化重排、折叠/行号/高亮 TDD |
| 真 partial present | 默认 swapchain 每帧清屏，全屏 composite；无平台 damage 协商 | 未损伤区域内容丢失、Wayland/X11/WSI 语义不一致 | 平台 capability + 保留 backbuffer + dirty threshold + 每平台 smoke |
| Vulkan 窗口 readback | 仅离屏 readback；WSI readback 明确不支持 | 传输 usage、layout、fence 和窗口性能回归 | 显式截图 API、尺寸预算、staging/fence、validation clean |
| 完整 UAX#14 | SA dictionary、Hebrew quotes、复杂 numeric/context tailoring 未覆盖 | 错误断词或标点孤行 | 版本化 UCD golden corpus + 超长输入预算测试 |
| 完整 CSS/XML | 复杂 combinator、at-rule 语义、完整 selector tree 未实现 | 解析器静默接受错误、运行期主题污染 | capability registry、strict diagnostics、AST/bridge 回滚测试 |
| 平台 runtime CI | Windows/macOS/Wayland compositor runtime 缺少本机矩阵 | 构建通过但 DPI、IME、present 在实际 compositor 失败 | runner build + 启动 smoke + HiDPI/IME/resize 证据 |

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
2. RHI 提供最大 color sample count 和 resolve compatibility 查询；GL 读取已创建
   surface 能力，Vulkan 使用 physical-device limits 与 format properties。
3. 离屏 target 增加 sample-count descriptor；MSAA color 与 single-sample resolve
   target 一起候选创建，render pass/pipeline 全部验证后再激活。
4. 旧 target 保持可用直到新 target 首次提交成功；resize、DPI、device lost 都走
   同一事务路径。设备不支持时返回 `MY_RET_NOT_SUPPORTED`，不静默降低用户设置。

### 阶段 C：可选 HarfBuzz shaping

1. CMake 自动检测 HarfBuzz，默认可选；关闭或缺失时保留现有 Arabic fallback。
2. 以 UTF-32 paragraph/run 为输入，按 script、direction、font identity 和字号
   分割 shaping run；输出 glyph id、advance、offset 与 logical span。
3. 缓存键必须包含字体身份、face index、字号、script、direction、feature set 和
   text hash；缓存容量固定上限，命中失败只回退当前 run。
4. 先接入测量与 Break RHI，再接入 GLES/Vulkan/soft 的 glyph upload；任一后端失败
   不改变其他后端路径。

### 阶段 D：段落、编辑器和断行

1. 把单字符串 layout 升级为 paragraph model，保留 logical/visual boundary 双向
   映射；换行、justify、selection、cursor 共用同一段落结果。
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
