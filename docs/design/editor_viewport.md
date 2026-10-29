# Scene Editor Phase 2 — 3D Viewport 设计合同（交付定稿，Task 4 验证收口）

## 1. 文档定位

本文记录 Stage 4 scene editor Phase 2 的 **3D viewport**（GPU 面板 +
渲染器 + shell 接线）的**已交付**合同与明确排除项。状态词汇沿用
`docs/design/editor_phase1.md` 惯例：已交付 = 代码 + 测试 + sanitizer
lane + 记录在案的 live smoke 证据；设计-only = 仅有意图记录。
证据链：`.superpowers/sdd/2026-10-23-scene-editor-phase2/task-{1,2,3,4}-report.md`。
Task 4 收口：全套验证 lane（normal/ASan+UBSan/TSan/notests/全量套件）+
终态 live smoke 复跑记录于 task-4-report.md。

分层总览：

```
editor 可执行
  └─ editor_main.c（薄 main：platform + RHI + BreakUI）
       ├─ break_editor 库（纯 CPU）：editor_viewport.*（相机/射线/拾取）
       │    + editor_gizmo.*（gizmo 状态机，单一 undoable 命令/段）
       └─ editor_panels.c + editor_viewport3d.c（shell 侧，唯一碰 RHI 的文件）
            └─ myui 控件树：viewport 面板控件（自定义 on_paint + on_event）
```

**铁律（plan Global Constraints）**：所有相机/gizmo/拾取数学是纯 CPU 且
确定性，位于 `engine/src/editor/`；GPU 侧（`editor_viewport3d.c`）只做
离屏 FBO 渲染与事件路由，不含行为断言——其证据仅为编译/链接 + 记录在案
的 live smoke run（非 GPU 正确性验证）。

## 2. 数学合同（CPU 核心，Tasks 1-2 已钉）

- **相机**：orbit 相机，`eye = target + d·R(yaw,pitch)·(0,0,1)`；yaw 绕 +Y
  先于 pitch；yaw==pitch==0 时 eye 在 target 正后方 +Z。pitch 钳 ±89°，
  distance 钳 [0.05, 1e4]，fov_y 默认 60°。view = `mat4_lookat`，proj =
  GL 式右手 perspective（clip z ∈ [-1,1]，无 jitter）。
- **screen→ray**：`inv_proj · ndc(x,y,1)` → `inv_view`，退化透视除法
  （|w|<1e-20）有界 false。屏幕坐标 = 左上原点逻辑像素。
- **拾取**：每次调用重建 BVH（文档化 Phase 2 选择；编辑器规模实体数；
  增量 refit 为后续优化），候选 ≤ 4096。最近命中（最小 t）获胜。
- **EditorTransform.rot 语义（本 plan 定义并钉死）**：`rot[k]` = 绕轴 k 的
  角度（**度数**），存储映射与 Phase 1 inspector 字段名一致（rot[0]=
  rot.x=绕 X 的 pitch，rot[1]=rot.y=绕 Y 的 yaw，rot[2]=rot.z=绕 Z 的
  roll）；组合顺序为 **M = T(pos) · R_y(rot.y) · R_x(rot.x) · R_z(rot.z)
  · S(scale)**。Task 3 的 `break_editor_viewport3d_model_matrix`（纯 CPU、
  headless 已知答案测试钉住：yaw 90° 下局部 +X→世界 -Z；组合顺序
  R_y·R_x 与 R_x·R_y 可区分；90 是度非弧度）是渲染侧唯一施加处。
- **gizmo 拖拽**：轴 translate = 鼠标射线与轴线两线最近点；CENTER = 相机
  朝向平面自由平移；rotate = 水平像素 ×0.5°/px（右拖=正角度）；scale =
  2^(s-s0) 逐轴乘性（CENTER 均匀，200px/倍频程，钳 ≥0.01）。**整段拖拽
  = 恰好一条 undoable 命令**（begin 快照、drag 就地写、end 提交；
  位级相同不录命令）。

## 3. 代理语义（EDITOR-ONLY）

- 每个带 EditorTransform 的实体渲染**一个单位立方体代理**（36 顶点，
  中心在原点、边长 1，顶点缓冲手工内联）；拾取 AABB 半轴 =
  0.5·|scale|、最小钳 0.05，二者共享同一几何尺度约定。
- 代理是**编辑器专用的渲染表示**，不声称游戏场景保真（Phase 1 记录在案
  的 SCENE_NODES-dropped 限制不变；本 phase 不新增 Scene 所有权）。
- **选中高亮（已交付的最小变体）**：选中实体代理以暖色平涂
  （1.0, 0.62, 0.18）替代默认灰蓝（0.55, 0.58, 0.64）——纯颜色替换，
  无 outline/wireframe pass。
- gizmo 手柄渲染消费 `break_editor_gizmo_handles` 同一几何源（命中与
  渲染同源），轴色 X=红/Y=绿/Z=蓝/CENTER=浅灰；手柄在代理之后绘制并先
  `rhi_cmd_clear_depth`——编辑器式置顶覆盖（Phase 2 最小方案，无
  stencil/轮廓 pass）。

## 4. FBO / blit 路径（GPU 侧唯一新机制）

- **myui RHI canvas 加法扩展槽**（plan 允许的唯一 myui 改动）：
  `my_vgcanvas_break_rhi_blit_texture(vg, RHITexture tex, x, y, w, h)`——
  用 canvas 既有 image pipeline/batch 路径把一张现存 RHI 纹理画进当前
  帧命令流。**无 vtable 变更、不碰 image-cache 槽位**（句柄直接使用，
  绝不进 CPU-bitmap 缓存）。UV 约定与 draw_image 一致：v=0 落在 dst
  **顶边**。外来 canvas（如 dummy-PAL LCD）有界拒绝（INVALID_PARAMS），
  无效句柄/非有限尺寸同。`rhi_draw_image` 的批量逻辑抽出为
  `emit_texture_quad` 静态助手，两调用点共享（行为等价重构）。
- **离屏 FBO 生命周期**：`break_editor_viewport3d_create` 不建任何 GPU
  对象；管线（新 `engine/shaders/editor_color.{vert,frag}` + `_vk` 变体，
  push-constant/uniform 双约定经 `rhi_pipeline_bindings_resolve` 同一名称
  解析）与立方体 VBO 在首个带活设备的 render 惰性创建；FBO 仅在面板
  像素尺寸变化时重建（plan bound）；面板 < 32×32 整体跳过；惰性初始化
  失败粘性记录（不再逐帧重试/刷屏）。设备中途更换 = 有界 no-op（不
  支持，文档化）。**2026-10-27 更新**：设备挂接时 `prepare` 先记录设备，
  再经统一 resolver 读取 shader 并走事务式候选构建；粘性失败只阻止逐帧
  重试，shader 热加载事件或 `Ctrl+Shift+R` 可以恢复；部分初始化的资源
  不再泄漏。见 `docs/design/editor_hot_reload.md` §7。
- **帧序（editor_main.c）**：`platform_poll → break_ui_pump →
  break_editor_shell_tick → break_ui_frame_begin（可能跳过）→
  break_editor_shell_render_viewport（同一 cmd；bind=clear 依 R617）→
  break_ui_render（控件 on_paint blit FBO color_tex 进 retained UI
  surface）→ rhi_frame_end/present`。unbind 用全屏 drawable 尺寸恢复
  swapchain pass（shell 每帧经 `set_screen_size` 刷新）。
- **纹理朝向（双后端视口约定的代码分析 + 与 smoke 一致；非像素证据）**：
  源码层面 FBO bind 的默认视口在两后端都把 NDC +Y 存到纹理 v=1 侧
  （rhi_gl.c `gl_set_fbo_pass_state` / rhi_vk.c `rhi_offscreen_fbo_bind`），
  而 blit 在 dst 顶边采样 v=0——渲染器把投影矩阵的 Y 缩放取反
  （`proj.e[1][1] *= -1`），使场景上方落在 v=0。已记录的 smoke run 仅
  捕获 init+存活日志、不含像素判读，与该分析一致但不构成像素级钉住。
  **仅渲染侧**翻转；拾取/gizmo 数学用未翻转矩阵。VK 变体另做 clip z
  [-1,1]→[0,1] 重映射（blinn_phong_vk 先例 R214-A）。三角形绕向因 Y
  翻转改变，管线 `disable_culling` 故无影响。
- **VK render-pass 兼容**：管线 color_format 默认（R8G8B8A8），FBO 为
  R8G8B8A8；后端 `vk_pipeline_for_fmt` 按当前 pass 格式自动重建变体
  （与 UI surface_fbo 上的 font/image 管线同一机制）。

## 5. 面板控件 + 指针路由（shell 侧合同）

- **布局**：中间行 = outliner `w:25%` + viewport `w:1f h:100%` +
  inspector `w:28%`；palette/console 不变。
- **控件**：`my_widget_subclass_init` 轻量子类（无自有资源，user_data =
  借用 shell），on_paint = 深色占位（30,31,34）+ FBO 纹理 blit（无 FBO
  时仅占位——dummy-PAL 路径唯一 paint）。on_event 消费落在其上的全部
  指针事件；dispatcher grab 语义保证 move/up 持续送达。
- **路由（坐标恒为控件当前 rect 的本地逻辑像素）**：
  - 左键按下：gizmo `begin_drag` 命中 → 拖拽；命中手柄但 grab 退化 →
    保持选择（用户明显瞄准 gizmo，非空处）；否则 pick → 命中选中 /
    miss 清空选择并进入“待框选”（Ctrl 按住时不清空）。
  - 左键在空白处按下后移动超过 4 逻辑像素：框选。拖动中画半透明强调色
    矩形（`#3574F0`，1px 边）；松开时 `break_editor_viewport_box_select`
    选中中心（Transform pos）投影落在矩形内（含边）且位于近平面前方的
    实体，按文档顺序，第一个为主选；Ctrl 时加入当前选择且新框中第一个成为
    主选。空框清空选择。框选是视图状态，不进撤销栈。单次最多 256 个。
  - 左键拖拽（gizmo 活动）：`gizmo_drag`；**中途返回 false = 拖拽已被
    外部提交结束（见 §6 的 Ctrl+Z 策略），控件自愈丢弃拖拽态**。
  - 右键 / Alt+左键拖拽：orbit（0.25°/px）。
  - 按住右键时飞行（2026-10-29）：W/A/S/D 前/左/后/右，Q/E 降/升（不带
    Ctrl/Alt）。这期间这些键不再切换工具；松开右键即退出飞行并丢弃仍按着
    的键。前进沿视线方向（含俯仰），左右沿相机水平右轴，升降沿世界 +Y；
    移动的是 pivot（眼睛随之移动），yaw/pitch/distance 不变。速度 =
    `distance` 单位/秒（至少 0.5），按 tick 间的真实时间积分，单次步长上限
    1 秒。核心 `break_editor_camera_fly` / `_fly_step`，shell
    `break_editor_shell_set_flying` / `_fly_advance`。视图状态，不进撤销栈。
  - 中键 / Shift+左键拖拽：pan（像素增量按当前控件高度重缩放，使一逻辑
    像素在 pivot 平面恰好平移一屏幕像素——核心 pan 的参考高度是 720）。
  - 滚轮：zoom（指数，正 delta 拉近）。
- **快捷键**：Q/W/E/R = gizmo 模式 NONE/TRANSLATE/ROTATE/SCALE + 工具
  标签（编号与 Phase 1 工具态 0..3 一致）；F = 对选中实体真实
  `break_editor_camera_focus`（视图状态，不可撤销）；多选时 F 框住所有被选实体代理 AABB 的并集（`break_editor_camera_focus_many`，2026-10-29）；没有选中时 F 框住整个场景（所有带 Transform 的实体，最多 1024 个），场景里没有可聚焦的实体时只在控制台提示；Ctrl+S/Z/Y/P 不变；Ctrl+A 全选实体（文档顺序，第一个为主选）、Esc 清空选择（命令面板打开时 Esc 只关面板；文本框获得焦点时 Ctrl+A 仍是全选文字），2026-10-29。上/下方向键把选中移到大纲上一行/下一行（两端钳住；无选中时下键取首行、上键取末行），Shift+上/下从锚点扩展范围；多选时 Ctrl+D 复制全部被选实体（一个撤销步骤，复制品成为选择）；F2 重命名所选（等同命令面板“Rename Selected”，焦点移到名称输入框并全选原名）；Home / 命令面板“Reset view”把相机复位到启动时的视图（目标原点、距离 5、俯仰 25°、yaw 0；文本框里 Home 仍是行首）；命令面板打开或文本框（Lua 控制台、检查器字段）有焦点时方向键归它们。
  字母忽略 SHIFT，Ctrl/Alt 精确匹配（Phase 1 表不变）。
- **gizmo 与选择的粘合**：shell reconcile（幂等——attach 恒先隐式
  end_drag，冗余 attach 会把中段拖拽提前提交，故以缓存 id 去重）；
  选择失效（remove/undo/load）自动 detach。

## 6. 中段 Ctrl+Z 策略（Task 2 minor 的定案，已交付并钉住）

**外部 undo/redo 遇到活动 gizmo 拖拽时，先 end+commit 该拖拽（恰好一条
命令），再执行 undo/redo**——Ctrl+Z 的净效果即回滚该段拖拽，命令栈始终
相干。控件侧经 drag 返回值自愈（§5）。Pinned by
`mid_drag_ctrl_z_commits_then_undoes_the_drag`（拖拽中 pos.x 已变 →
Ctrl+Z 后回到原值 → 后续 move 不再写、up 为 no-op）。
set_mode/attach/detach/destroy 的中段隐式提交为 Task 2 既有合同。

## 7. damage / invalidate 策略

retained UI 仅按 damage 重绘（myui_break.c）。viewport 是**活 3D 视图**：
`break_editor_shell_tick`（主循环每帧、`frame_begin` 跳过判定**之前**
调用）在控件可见时每帧 `my_widget_invalidate`——plan 记录的**有意**
例外，使每帧都有 damage、3D 视图持续刷新。控件事件处理器在相机/gizmo
变更后也即刻 invalidate（非 tick 路径的鲁棒性）。

## 8. headless 证据边界

dummy-PAL 测试壳**无 RHI 设备**：`break_editor_shell_render_viewport` 为
受保护 no-op（设备/命令 NULL 直接返回），整条 dummy 路径零 GPU 调用
（测试钉住）。headless 覆盖：控件在树、W/E/R/Q 模式+标签、F 移动相机
target、注入指针事件 pick 改选择、gizmo 拖拽改 transform 字段且一次
undo 回滚、中段 Ctrl+Z 策略、orbit/pan/zoom 路由、model 矩阵已知答案。
GPU 路径证据 = 编译/链接 + 记录在案的 live smoke run（**非** GPU 正确性
验证）。

## 9. Phase 3+ 明确排除项（设计-only，本 phase 未交付）

- ~~选中高亮 **outline**~~（2026-10-29 已交付：所选代理立方体的 12 条棱以细长盒绘制为亮色描边 `#FFEB8C`，叠在暖色 tint 上；几何由纯 CPU 的 `break_editor_viewport3d_outline_edges` 生成并有已知答案测试；统计 `outline_edges`）、~~rotation rings 手柄可视化~~（2026-10-29 已交付：旋转模式下每轴一圈 48 个小立方体，半径 = 轴手柄远端，颜色同轴；只作可视化，命中仍用手柄 AABB；几何 `break_editor_gizmo_rings`，统计 `ring_segments`）
  可视化、~~多选的框选~~（大纲 Ctrl/Shift 多选、批量删除、多实体随 gizmo 一起拖动、视口框选均已于 2026-10-29 交付；框选按实体中心判定，不做与代理盒的相交）、场景保真渲染
  （mesh/材质/光照——代理立方体不声称游戏画面）、gizmo 局部坐标系模式、
  ~~视口内导航键（flycam）~~（2026-10-29 已交付：按住右键 + WASD/QE）、~~视口 overlay 统计信息~~（2026-10-29 已交付，见文末）、pick 的增量 BVH refit
  优化（当前每次调用重建，编辑器规模足够）。

## 10. 已知边界与 fast-follow（终审 2026-10-23 记录，均不阻塞合并）

1. ~~**多按钮按下覆盖拖拽态**~~ **已修复 2026-10-29**：视口 DOWN 处理器在切换 drag_kind 前先结束活动 gizmo drag（`test_editor_shell` `second_button_mid_gizmo_drag_commits_the_drag`，修复前红）。原问题：左键拖拽中再按右键会让 gizmo drag 泄漏为未提交状态，下一次 Ctrl+Z 先提交再撤销。
2. ~~**拖拽中经 Inspector 键盘编辑同一字段**~~ **已修复 2026-10-29**：shell 层所有文档修改（改名、改字段、增删组件、增删/复制实体；撤销/重做原本就有）先经 `shell_end_gizmo_drag` 结束活动拖拽，拖拽与编辑成为两个先后有序的命令（`test_editor_shell` `inspector_edit_mid_gizmo_drag_ends_the_drag_first`，修复前红）。
3. ~~`vp_lazy_init` 部分失败泄漏~~ 已在后续重构中消除（2026-10-29 复核）：现在的入口 `break_editor_viewport3d_prepare` 在任何可失败步骤之前先设 `vp->device`，并先把状态置为 `INIT_FAILED`、成功后才改为 `READY`，所以失败路径一次性且由 destroy 用同一 device 释放已建对象。
4. `vp_fbo_ensure` 创建失败后每帧重试（无粘性标志；无泄漏、有界）；可选加粘性标志并在本节记录重试策略。
5. 文档小项：~~`editor_viewport.h` 相机结构注释的 distance/pitch 边界与实现钳制不一致~~ 已更正 2026-10-29（注释改为引用实际钳制常量）；~~`set_mode` 对 >SCALE 枚举值缺钳制~~ 已修复 2026-10-29（越界值按 NONE 处理，`test_editor_gizmo` `set_mode_out_of_range_hides_the_gizmo`，修复前红）。


## 吸附（2026-10-29）

`break_editor_gizmo_set_snap(g, translate_step, rotate_deg, scale_step)`：0 表示该类关闭；吸附结果值（不是增量），所以离网格的起点会落回网格；缩放不低于一个步长；负数或非有限值被拒绝并保留原设置。shell 侧 Ctrl+G / 命令面板切换（默认 0.25、15°、0.1），工具标签带“Snap”，偏好文件 `snap=on|off`。

## 视口统计叠加（2026-10-29）

视口左上角画一行统计：实体数、选中数（主选 + 多选）、上一帧的 draw call 数、FBO 尺寸，随 UI 语言翻译（`Entities 1  Selected 1  Draws 14  818x690` / `实体 1  选中 1  绘制 14  818x690`），12 px 浅色字、半透明黑底。默认开启；命令面板“Toggle viewport stats / 切换视口统计”开关，偏好文件 `stats=on|off`。文本由 `break_editor_shell_viewport_overlay_text` 生成（隐藏时为空串），draw/FBO 数取自 `break_editor_viewport3d_last_stats`，不做 GPU 回读。未做：帧时间（profiler 面板已有）。

## 地面网格（2026-10-29）

XZ 平面（y = 0）上从 -10 到 +10 每 1 单位一条线，共 42 条，以细长盒（截面 0.02）绘制，先于代理立方体、参与深度测试；过原点沿 X 的线为暗红、沿 Z 的线为暗蓝，其余灰色。几何由纯 CPU 的 `break_editor_viewport3d_grid_lines` 生成，统计 `grid_lines`。默认开启；命令面板“Toggle ground grid / 切换地面网格”开关，偏好文件 `grid=on|off`。编辑器相机默认俯仰改为 25°（原为 0°，视线贴着网格平面时网格只是一条线）；`break_editor_camera_init` 本身仍是 0°。未做：随距离自适应间距、无限网格、淡出。
