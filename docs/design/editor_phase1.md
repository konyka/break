# Scene Editor Phase 1 — shell 架构与已交付合同（Phase 1 收口，Task 5 验证定稿）

## 1. 文档定位与状态词汇

本文记录 Stage 4 scene editor Phase 1 的 **editor shell**（`editor` 可执行 +
`engine/apps/editor/editor_panels.h/.c`）的**已交付**行为，并
明确列出仍是 **Phase 2+ / 设计-only** 的部分。状态词汇沿用
`docs/design/lua_runtime.md` 惯例：已交付 = 代码 + 测试 + sanitizer lane
证据齐备；设计-only = 仅有意图记录，无代码承诺。证据链：
`.superpowers/sdd/2026-10-23-scene-editor-phase1/task-{1..5}-report.md`。

**本 shell 是正式可选工具 target，不是生产级 editor 产品。**

## 2. 目标与分层

```
editor 可执行（engine/apps/editor/editor_main.c，薄 main）
  └─ BreakEditorShell（editor_panels.c：全部面板逻辑，headless 可测）
       ├─ BreakEditorDoc（break_editor 库：文档 + 命令栈 + save/load + 组件注册表）
       └─ myui 控件树（list_view / edit / button / label / text_area）
```

- `editor_main.c` 只做 platform_create → rhi_device_create → break_ui_* →
  `break_editor_shell_create(break_ui_get_window(ui))` → 主循环 → 逆序销毁
  （`dxx_break_main.c` 先例）。argv[1] 可选：仅作为 Ctrl+S/调色板 save 的
  目标路径（Phase 1 无 save-as 对话框；argv 加载有意不接——doc 层已支持
  load，shell UI 的打开流程留给后续 phase）。
- `BreakEditorShell` 拥有恰好一个 `BreakEditorDoc` 与整棵面板控件树；两条
  窗口路径共享同一套 builder 与快捷键表：
  - **真实窗口**：`break_editor_shell_create(my_window_t*)`，窗口借用
    （BreakUI bridge 拥有）；shell root 挂进 window content，content 上装
    linear layouter（`w:100% h:1f`），窗口 resize 时面板随动（palette 是
    floating 子节点，layouter 跳过）。
  - **headless 测试**：`break_editor_shell_create_for_test()`——dummy PAL
    （无 RHI）+ 自建 800x480 窗口/WM/loop，测试经
    `break_editor_shell_dispatch_key` 直驱快捷键、经真实 emitter
    （"click"/"activate"）驱动控件。
- **分层铁律（plan Global Constraint）**：控件回调绝不直接调 `world_*`；
  一切文档变更只走 `break_editor_doc_*` / `break_editor_undo/redo`，命令栈
  是唯一变更路径。由 `test_editor_shell.c` 的
  `rename_via_name_edit_then_undo_reverts_displayed_name` 与
  `inspector_field_edit_routes_through_command_stack` 钉住（UI 改名/改字段
  后 undo 必须回退显示值）。
- **selection 归属 shell**（`BreakEditorEntityId selected`），不在 doc：
  Task 1-3 的 doc API 无 selection set，Phase 1 保持如此（sidecar 也只存
  名字）。outliner 行点击经 `break_editor_shell_select_index` 设置；每次
  refresh 重新对照 doc 校验，实体不存在（remove/undo/load）即清空。

## 3. 面板地图（panel map）

窗口 content（vertical layouter）内自顶向下：

| 区域 | 控件 | 说明 |
| --- | --- | --- |
| toolbar（h:28） | `editor-add-button` / `editor-remove-button`（my_button）+ `editor-tool-label`（my_label） | Add 走 `doc_add_entity` 命令并选中新实体；Remove 删当前选中；工具标签显示 select/translate/rotate/scale 状态 |
| 左 outliner（w:34%） | `editor-outliner`（my_list_view，虚拟化，行 = 可点击按钮 `editor-outliner-row`） | adapter `get_count` = `break_editor_doc_entity_count`；行点击选中；refresh 重绑显示名 |
| 右 inspector（w:1f） | `editor-inspector` 容器（选中变更时整体重建） | `editor-name-edit`（my_edit，"activate" 提交 rename 命令）；每个已注册组件一节：存在 ⇒ 组件名 + `editor-component-remove-<id>` 按钮 + 9 个 f32 字段行 `editor-field-<id>-<f>`（`break_editor_parse_f32` 严格解析 + `set_field_f32` 命令）；缺失 ⇒ `editor-component-add-<id>` 按钮 |
| 底部 console（h:96） | `editor-console`（只读 my_text_area） | 有界 **64 条 × 128 字节** 环形日志，drop-oldest；每个动作（add/remove/rename/set/save/undo/redo/tool/palette/focus）写一行 |
| 状态栏（h:22） | `editor-status`（my_label） | `entities=N dirty=0/1 last=<命令 describe> note=<意图便签>` |
| 调色板 overlay | `editor-palette`（floating 容器：`editor-palette-edit` + `editor-palette-list`，行 `editor-palette-row`） | Ctrl+P 开合；大小写不敏感子串过滤 10 条命令（Add Entity / Remove Selected / Rename Selected / Save Scene / Undo / Redo / Tool: ×4）；Enter("activate") 执行首条匹配，行点击执行对应命令，Esc 关闭 |

## 4. 快捷键表（单一表驱动，editor_panels.c `k_editor_shortcuts`）

| 键 | 修饰 | 动作 |
| --- | --- | --- |
| Q / W / E / R | 无（字母忽略 SHIFT） | 工具状态 select / translate / rotate / scale（仅标签状态，无 gizmo） |
| F | 无 | focus-selected **意图记录**（status note + console 行；相机聚焦是 Phase 2） |
| Ctrl+S | Ctrl | 保存到 `break_editor_shell_set_scene_path` 配置的路径（未配置 = 有界 no-op + 日志） |
| Ctrl+Z / Ctrl+Y | Ctrl | undo / redo（命令栈） |
| Ctrl+P | Ctrl | 调色板开关 |
| Esc / Return | 调色板打开时 | 关闭 / 执行首条匹配 |

真实窗口的按键路由：myui dispatcher 只把 KEY_DOWN 投给焦点控件并**向父级
冒泡**（`my_event_dispatch.c`）；shell 在 root 容器上挂 "key_down" 监听并在
create 时把焦点设到 root，故快捷键只在焦点控件未消费该键时触发（在编辑框
里打 Q 不会切工具）。测试直接调 `break_editor_shell_dispatch_key`。

## 5. 有界性与所有权

- console 环 64×128B（join 缓冲 64×129+1 字节，定长内联于 shell 结构）；
  名字/调色板编辑框 max_len 127/63 codepoints；scene path ≤
  `BREAK_EDITOR_SCENE_PATH_CAPACITY`(1024)；行点击 ctx 池固定 64（虚拟化
  list 只创建可见+1 行，耗尽时行仍渲染、点击退化，文档化）；inspector
  字段 ctx 池 16×9=144（重建时顺序分配，零堆分配）。
- 控件/监听 ctx 生命周期：面板树由窗口树持有（add_child 后 shell 只留
  weak）；真实路径 destroy 时 remove_child 摘树（释放树引用），测试路径
  destroy 时窗口 teardown 连带销毁整树；监听器 ctx（shell/池内嵌结构）
  不会晚于控件存活。
- **World 借用指针的 load 失效（Task 2 review 遗留收口）**：
  `break_editor_doc_load` 成功即整体交换内部 World（staging world
  swap），此前经 `break_editor_doc_world()` 借用的指针全部悬垂，调用方
  必须重新获取；load 失败则 World 不变（editor_doc.h / editor_scene.h
  合同均已注明）。
- **scene_serial 单份解析（carried review item 收口）**：`libbreak_editor.a`
  与 `libengine.a` 都含 `scene_serial.o`。`editor` 链接行把 `break_editor`
  列在最前（`target_link_libraries(editor PRIVATE break_editor break_myui
  engine m)`）：静态归档只为解析仍未定义的符号拉取成员，editor_panels.o →
  editor_scene.o → scene_serial.o 全部从 break_editor 解析，engine 的副本
  永不因同名符号被拉取。`nm` 验证三个 lane 的 `editor` 二进制：
  `scene_save_binary` 等 5 个导出各恰好 1 份定义、0 未定义；contract ctest
  （`test_break_editor_target_contract`）断言该链接顺序。

## 6. Phase 2+ / 设计-only（明确不声称已交付）

> 2026-10-23 更新：第一条（3D viewport/gizmo/相机 + 真实 F focus）已由
> **Phase 2 交付**（branch `sdd/scene-editor-phase2` Tasks 1-4），合同见
> `docs/design/editor_viewport.md`；本表其余各项仍为后续 phase 的设计-only
> 意图。下文为 Phase 1 收口时的原始记录。

- 3D viewport / gizmo / 相机（F 键只记意图）；真正的 focus 相机移动。
- save-as / open 文件对话框；argv 加载；菜单栏（my_menu 已可用，Phase 1
  用 toolbar + 调色板替代）。
- 诊断面板（profiler、metrics）、Lua console、remote session。
- asset browser（Stage 4 子项目 4 不在本 phase）。
- selection 多选集（当前单选）；inspector 多组件类型编辑（注册表只有
  EditorTransform）；非 f32 字段类型。
- ~~窗口内 palette 的键盘上下导航~~：2026-10-29 已交付，上/下键移动高亮行（首尾循环、改过滤时复位），Enter 执行高亮行（`test_editor_shell` `palette_arrow_keys_move_the_highlight_and_enter_runs_it`）。
- ~~undo `remove_entity` 不恢复组件~~：2026-10-29 已修复，删除命令构造时快照该实体全部已注册组件，撤销时按字节恢复（`test_editor_components` `remove_entity_undo_restores_components`）。
- ~~editor 重保存丢游戏侧 BSCN 渲染 scene chunk~~：2026-10-29 已修复，加载时按原字节保留编辑器不负责的全部 chunk（SCENE_NODES、RESOURCES、网格/蒙皮几何、骨骼、动画及未知类型），保存时拼回（`test_editor_scene` `resave_keeps_game_render_chunks`）。这些 chunk 描述游戏渲染图，增删实体时不会重新编号。

## 7. 验证摘要（Task 5 收口定稿；分任务细节见 task-{1..4}-report.md）

**Task 5 全量收口 lane**（报告：task-5-report.md）：

- **normal 树 `build-sdd-e5`**：完整默认 target 集（179 个 target，含
  `break_editor`/`editor`/全部测试）构建零告警（除 vendored Lua 的
  `tmpnam` 链接器既有提示）；editor lane `ctest -L editor` **6/6**
  （`test_editor_doc` 12 + `test_editor_cmd` 14 + `test_editor_scene` 15 +
  `test_editor_components` 15 + `test_editor_shell` 15 +
  `test_break_editor_target_contract`）。
- **sanitizer lane**：ASan+UBSan 树 `build-sdd-e5-asan` 与 TSan 树
  `build-sdd-e5-tsan` 各 **6/6**，零 sanitizer 报告（ASan
  `detect_leaks=1`、UBSan `halt_on_error=1`）。
- **`ENGINE_BUILD_TESTS=OFF` 树 `build-sdd-e5-notests`**：独立构建
  `break_editor` + `editor` 成功；`nm libbreak_editor.a` **零
  `break_editor_test_*` / test-hook 符号**（Task 5 修复后：production
  分支的 `break_editor_test_calloc` 由 static inline 改为宏直通 calloc，
  连本地符号也不再出现——此前 Debug -O0 下会留下 4 个本地 `t` 符号，
  虽无注入机制但名义上是 test 命名符号；注入钩子本体
  `g_break_editor_test_alloc_budget` 等自始至终不存在于 production）。
- **全量非图形/非 fuzz 套件** `ctest -LE 'graphics|fuzz'`：**186/186
  通过、0 失败**；1 项 platform-skip（`test_d3d12_dependency_gate`，
  Windows-only by design）；label 排除 4 项（`test_platform_x11_runtime`、
  `test_rhi_x11_runtime`、`test_vulkan`、`rhi_swapchain_bench`，图形/fuzz
  需 GPU/display 的既有 lane）；预先清除的间歇 flake
  `test_break_replication_fragment` 本轮通过。
- **`editor` 二进制 smoke-run**（不构成 GPU 验证）：headless RHI 路径
  **不存在**——`ENGINE_RHI_BACKEND=headless` 在 configure 期即被
  FATAL_ERROR 拒绝（合法值仅 auto/opengl/vulkan/metal/d3d12，
  `engine/CMakeLists.txt:161-167`）；`engine_rhi_headless`
  （`src/rhi/rhi_headless.c`）是 fail-closed 契约测试后端，
  `rhi_device_create` 恒返 NULL 且 `engine_link_rhi_backend()` 无
  headless 分支；platform 亦无 dummy/headless 后端（Linux 仅
  X11/Wayland 真实窗口）。实际 smoke 命令与结果：
  `cd build-sdd-e5 && DISPLAY=:0 timeout -s TERM 6 ./editor /tmp/editor_smoke.bscn`
  → exit 124（timeout 终止 = 进入主循环），日志两行：
  `Platform initialized: 1280x800 "Break Scene Editor"`（X11/XWayland）与
  `OpenGL 4.6 (Compatibility Profile) Mesa 26.2.4 initialized`，随后 6 秒
  内零错误输出——platform 窗口、GL RHI device、BreakUI 初始化、shell
  创建与渲染主循环全部真实跑通。单元级交互证据仍由
  `test_editor_shell`（dummy PAL + 判别性 PPM）承担。

**Task 4 原始 lane（历史记录）**：`test_editor_shell` 15/15（三 lane：normal
`build-sdd-e4`、ASan+UBSan `build-sdd-e4-asan` 3 连跑零报告、TSan
`build-sdd-e4-tsan` 10 连跑零报告），含**有判别力的 PPM 冒烟**：断言窗口真实
绘制后的两个主题色——window bg `0xF5F5F5`（`my_theme.c:1127-1128`，经
`my_window.c:110-111` 消费）占帧主体 + button bg `0xE0E0E0`
（`my_theme.c:1129-1130`）存在；从未绘制的零填充 dummy lcd 两者皆为 0
（mutate-check：跳过 paint 调用该测试必红）。myui 回归（
`test_myui_window_manager`/`test_myui_mvvm`/`myui_widgets_demo_smoke` 等）
normal lane 42/42、两个 sanitizer lane 各 9/9。

**Fix round 1 记录（Task 4）**（详见 task-4-report.md 附录）：
- outliner 行曾恒显示 `<stale>`：`bind_row` 误传 `out_id=NULL`（
  `entity_at` 有界拒绝 NULL），修复为真实 out 参数；新增
  `rename_then_undo_reverts_outliner_row_text` 钉住"改名→undo/redo 时
  outliner 行显示名双向跟随"。
- 上述 PPM 判别力修复暴露一个 myui 核心潜伏 bug 并一并修复：
  `my_list_view` 的 `on_layout` 无条件 `lv_sync_rows`（重建行子节点）→
  add/remove_child 再次请求布局 → 宿主窗口 `my_window_prepare_layout`
  8 趟永不收敛、整帧放弃（`myui_break.c:707` 同路径）——**任何包含非空
  list_view 的绘制窗口（含真实 `editor` 窗口）都不会渲染**。修复：
  `on_layout` 仅在视口高度变化时重同步（新增
  `my_list_view_t.layout_synced_height`；其余入口本就经
  `lv_on_layout_changed` 同步同步）。这是对 plan"legacy myui 零diff"约束的
  有意例外——任务交付物（真实窗口可绘制 + brief 要求的 PPM 冒烟）被该 bug
  阻断；测试 15 即其回归钉。

**Task 5 adjudicated fix**：`editor_test_hooks.h` production 分支
`break_editor_test_calloc` 从 static inline 函数改为宏（
`#define break_editor_test_calloc(bytes) calloc(1, (bytes))`），使 production
归档在 `nm` 下真正零 `break_editor_test_*` 符号（Debug -O0 未内联的 static
inline 曾留下本地 `t` 符号；语义不变，测试分支不动）。修复后四个树
（normal/ASan+UBSan/TSan/notests）全部重建并复测通过。
