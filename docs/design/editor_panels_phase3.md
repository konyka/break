# Scene Editor — Phase 3 Task 3 面板接线（assets / profiler / lua）与布局

Stage 4 scene editor Phase 3 Task 3。本文档覆盖三块面板的布局与接线契约、
Lua 控制台面板契约、asset browser 的范围与限制、profiler 视图的范围与节流。
上游模型/核心各有自己的契约文档与头文件长注释（本文件不重复其内部
语义，只钉面板侧契约）：

- 文档/undo/命令栈：`engine/src/editor/editor_doc.h` / `editor_cmd.h`
- 场景持久化（world-swap + undo 栈清空）：`engine/src/editor/editor_scene.h`
- asset browser 纯 CPU 模型：`engine/src/editor/editor_assets.h`（Task 1）
- Lua console 纯 CPU 核心：`engine/src/editor/editor_lua.h`（Task 2，含
  EVAL PIPELINE / 注入安全 / 预算 / owner 线程全部契约）
- profiler 读取面：`engine/src/core/profiler.h`（`profiler_last_frame`
  :66、`ProfilerFrame` :19-33；region 存储在帧的 `regions[]`/`region_count`）

## 1. 布局（实现 + 钉住的决策）

```
root（vertical）
├─ editor-toolbar        h:28
├─ editor-middle         h:1f（horizontal）
│  ├─ editor-outliner-panel  w:25%（vertical）
│  │  ├─ "Outliner" label    h:22
│  │  ├─ editor-outliner     h:1f     ← 既有 outliner list_view
│  │  └─ editor-assets-panel h:40%    ← 新增：assets 段
│  │     ├─ editor-assets-path（label："assets: /<rel>"）
│  │     └─ editor-assets-list（list_view，行 = button）
│  ├─ editor-viewport        w:1f     ← 既有 3D viewport
│  └─ editor-right-panel     w:28%（vertical）← 新增容器
│     ├─ editor-inspector    h:1f     ← 既有 inspector（整体下移一格嵌套）
│     └─ editor-profiler-panel h:30%  ← 新增：profiler 段
│        ├─ editor-profiler-label（"Profiler (top 16, 4 Hz)"）
│        └─ editor-profiler-list（list_view，行 = label）
├─ editor-bottom         h:96（horizontal）← 新增容器
│  ├─ editor-console       w:1f       ← 既有 log ring text_area
│  └─ editor-lua-panel     w:40%      ← 新增：Lua 控制台
│     ├─ editor-lua-label（"Lua"）
│     └─ editor-lua-edit（my_edit，Enter 求值）
└─ editor-status         h:22
```

> **2026-10-29 更新（工具窗标签页）**：上面的平铺布局已改为标签页。右栏 inspector 之下是 `editor-diag-row`（h:45%，纵向）：标签条 `editor-diag-tabs`（Profiler / Network / Render）+ 三个页面 `editor-profiler-panel`、`editor-network-panel`、`editor-render-panel`，一次只显示一个，页面 `w:100% h:1f`。底部 `editor-bottom` 改为 h:160 纵向：标签条 `editor-bottom-tabs`（Console / Lua）+ 页面 `editor-console`、`editor-lua-panel`。设计见 `docs/superpowers/specs/2026-10-29-editor-tool-window-tabs-design.md`。


坐标注意：myui `widget->rect` 在**父坐标系**（my_widget.h）。inspector
嵌套进 `editor-right-panel` 后，`inspector->rect.x` 不再与 viewport 同一
坐标空间——测试对"inspector 在 viewport 右侧"的断言改为对
`editor-right-panel` 做（`viewport_widget_present_and_laid_out`）。

## 2. Assets 面板（`editor_panel_assets.c`）

- **范围**：仅 DIR 挂载的文件系统树（Task 1 模型边界；VFS pak 枚举明确
  不在范围）。默认 root 为进程 cwd（`.`）；create 失败（cwd 不可列）降级
  为空面板 + label 提示，不致命；`break_editor_shell_set_assets_root`
  换根（失败有界 false 且保留旧模型）。
  2026-10-30 补充：VFS 层已经提供 `vfs_enumerate_pak`（见
  `docs/design/runtime_asset_streaming.md`），但面板还没有接入 pak 列表。
- **行模型**：行 0 恒为 `..`（root 处钳制 no-op）；行 1..N 绑定模型的
  过滤后快照（目录在前、逐字节序）；目录渲染带尾随 `/`。
- **激活手势（决策）**：**单击**行即激活。myui list_view 没有双击/Enter
  惯例，outliner 先例即 click 激活；brief 的"Enter/双击"以单击落地。
  - `..` / 目录 → `break_editor_assets_up` / `enter`（模型做单段校验，
    逃逸 root 不可能——Task 1 契约）。
  - `*.bscn`（逐字节后缀、大小写敏感）→ 文档干净时直接
    `break_editor_doc_load`；**有未保存修改时（2026-10-30 起）第一次点击只在
    控制台与状态栏提示，未再修改的情况下再次点击同一场景才加载并放弃修改**
    （`editor_shell_load_scene_guarded`，与关闭窗口的保护同一规则）：Phase 2 已文档化 world-swap + undo 栈清空；
    console 记 `load <path>` 行（失败记 `load failed <path>`）；加载后
    整壳 `editor_shell_refresh_all`（outliner/inspector/status 全部
    重发布，选择按现存 id 重新校验）。
  - 其他文件 → 有界 `assets: '<name>' is not a .bscn scene` 提示行。
- **限制**：不过滤扩展名（全部列出，文档化选择）；listing 是导航时刻
  快照（磁盘后续变化不自动反映——模型契约）；行点击 ctx 池固定 32
  （虚拟化行只有 visible+1，实际不会耗尽；耗尽时行仍渲染但失去点击——
  outliner 先例）。

## 3. Lua 控制台面板（`editor_panel_lua.c`）

- **求值契约**：`editor-lua-edit` 的 Enter（my_edit "activate"）把输入经
  `break_editor_lua_eval` 送入 Task 2 核心。输入先回显为
  `lua| > <input>`，核心产出的每一行（print 捕获 / 结果值 /
  `error: ...`）以 **`lua| ` 前缀**落进**共享** console ring（Task 2
  核心保证每行 ≤127 可见字节，ring 本身 64×128 有界）。eval 后清空
  输入框并整壳刷新（Lua spawn/set 经可 undo 命令改 doc，outliner 等
  必须跟随）。
- **history**：my_edit 无 history recall（my_edit.h 的 undo 栈是用户编辑
  历史，非命令历史），故面板自持 **32 条有界 history**，Up/Down 用
  `set_text` recall。Up 向旧、Down 向新；首次 Up 暂存编辑中的行，
  Down 越过最新条时还原暂存。连续重复不重复入栈。my_edit 不消费
  Up/Down（`edit_on_key` 对其返回 MY_RET_FAIL），dispatch 的
  "key_down" emitter 路径在冒泡前在 edit 上触发面板处理器；带
  modifier 的 Up/Down 不触发 recall（不劫持 Shift+Up 类组合）。
- **界限**：edit cap 255 codepoints ⇒ 编辑来源的行至多 255×4=1020
  字节，**永远装得进** 1024 字节 history 条目（recall 文本不截断；
  核心接受 4096 字节输入——面板刻意把 widget 上限收得更低，文档化）。
- **降级**：核心 create 失败（OOM 级）→ console 为 NULL，面板照常
  构建，eval 退化为一行有界 `lua| error: console unavailable`。
- **线程**：单 owner 线程——shell 线程创建核心，所有 eval 在 activate
  处理器内（同线程）发生；log_fn 由核心在 eval 的调用线程上同步回调
  （此处恒为 shell 线程）。shell destroy 先毁面板（毁 console）再毁
  doc（console 借用 doc）。

## 4. Profiler 面板（`editor_panel_profiler.c`）

- **纯视图**：只读 `profiler_last_frame()`（无帧时为 NULL ⇒ 空表），
  **从不触碰 profiler 状态**（本文件无 set_enabled/begin/push/pop 调用；
  测试钉住刷新前后 `g_profiler.frame_count` 逐字节不变）。生产侧在
  `editor_main.c`：app 启动 `profiler_set_enabled(true)`，主循环每帧
  `begin → push("editor.frame") → … → pop → end`。
- **渲染**：末帧 region（至多 PROFILER_MAX_REGIONS=64）按 elapsed_us
  降序（稳定，并列保持帧内序）取 top-N（**N≤16**），渲染为
  `<name> <ms> ms` 的 label 行进 list_view。快照拷入面板固定存储
  （16×80 字节），行文本不别名 profiler ring——region 名指针只在刷新
  瞬间借用。
- **节流（文档化决策）**：`break_editor_shell_tick`（主循环每帧已调用）
  里至多 **4 次/秒**刷新（相邻刷新 ≥250,000us，平台单调钟
  `time_microseconds()`）；create 后**首个 tick 必刷新**（时间戳 0），
  编辑器一打开即有数据。刷新零分配。
- **范围**：只有本地 profiler 视图；网络/渲染 debugger 不在 Stage 4
  Phase 3 范围（roadmap 子项目 6 的其余部分仍 pending）。

## 5. 接线与 ownership

- 面板 struct 对 shell **不透明**（shell 只持 3 个指针），跨 TU 访问走
  `apps/editor/editor_shell_internal.h`（editor_viewport3d.c 先例——不摸
  对方 struct）。面板 create=纯 CPU 状态，build=控件构建，
  destroy=只释放 CPU 状态（控件属窗口树）。
- `break_editor`/`break_lua` 公开 API **零改动**（Task 1/2 已审定），
  面板只消费既有接口。新增表面仅 `editor_panels.h` 的 6 个测试/配置
  访问器（set_assets_root、assets row/path、lua history count、
  profiler row count/text）与 apps 内部头。
- **CMake / 契约测试调整（控制器预授权）**：`editor` 目标 +3 面板 TU，
  链接行变为 `break_editor break_lua break_myui engine m`——break_lua
  从"仅经 break_editor PUBLIC 传递"变为**显式列出**（面板引用
  `break_editor_lua_*` 后 editor_lua.o 与 break_lua 归档被拉入二进制；
  Task 2 报告里"editor 二进制尚无 break_editor_lua 引用"的 nm 观测
  描述的是接线前状态，本轮起被新现实取代）。契约 ctest
  `test_break_editor_target_contract.cmake` 的 editor 链接行钉同步更新
  为新行，并新增 editor/test_editor_shell 源列表钉；**engine /
  engine_demo / dxx_break 的禁链钉不动**（consumer 扫描照旧，它们仍
  不链 break_editor/break_lua，nm 复核零符号）。
- `test_editor_shell` 内联编译：3 面板 TU + `platform_fs.c`（模型消费
  platform_list_dir，test_editor_assets 先例）+ `profiler.c` + `time.c`
  （profiler 面板读 last_frame；engine 保持三者唯一 production owner，
  每二进制恰一份定义）；break_lua 符号经 `break_editor_test` PUBLIC
  `break_lua_test` 传递到达。
