# Editor 乱码修复与 I18N 设计

日期：2026-10-27
分支：`sdd/editor-i18n`

## 1. 根因

用户看到的“所有字符都是乱码”是 editor 界面文字，不是源码编码问题。实测证据：

- `engine/apps/editor/editor_main.c:52-57` 的 Linux 字体路径是 Debian/Ubuntu 布局（`/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc`、`/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf`）。本机是 Fedora，两个文件都不存在；Noto CJK 在 `/usr/share/fonts/google-noto-sans-cjk-vf-fonts/NotoSansCJK-VF.ttc`。
- `break_ui_init_with_fonts`（`engine/src/ui/myui_break.c:424-430`）在字体链全部加载失败时静默退回 `my_font_bitmap_create`：内置 8×8 位图字体，只覆盖 ASCII 32..126，被放大到 16px。gdb 在运行中的 editor 里确认 `ui->font->vtable == s_bitmap_vtable`。所以 ASCII 是粗糙的块状字，任何非 ASCII（中文、`—`、`…`）都变成同一个替代方块。
- 没有任何日志提示字体加载失败，问题只能靠肉眼发现。
- 次要发现：`engine/src/rhi/rhi.h` 有约 30 处注释里的 `—`（U+2014）被以 GBK 误读后保存成 U+9573 加一个替换字符（`→` 也有同样的损坏）。只影响源码可读性，不影响运行，一并修复。

## 2. 目标

1. 在常见 Linux 发行版、Windows、macOS 上找到可用的 CJK + 拉丁字体；找不到时有明确日志，不再静默。
2. editor 所有用户可见文字可翻译，首批 `en-US` 和 `zh-CN`。
3. 语言可切换：启动时按 `--lang` / `BREAK_LANG` / 系统 locale 选择；运行时可从命令面板切换，界面立即刷新。
4. 修复 `rhi.h` 的 mojibake。

## 3. 方案比较

**A. 内置字符串表 + 运行时切换（采用）。** C11 `break_i18n`：按 key 查当前语言的静态表，缺失时回退到 `en-US`，再回退到 key 本身。翻译表在源码里，编译期覆盖检查。shell 维护“文本刷新”入口，切换语言时重建静态标签并刷新列表。依赖为零，测试简单，符合项目现有 C11/有界数据风格。

**B. 外置 `.po` / JSON 语言包。** 不重编译即可加语言，但要解析器、文件定位、编码与格式容错、更多失败路径。当前只有两种语言，收益不足（YAGNI）。

**C. 只做启动时选择。** 实现最小，但不满足“语言可切换”的直接诉求。

字体方面，比较了：(1) 只扩充硬编码路径列表；(2) 用 fontconfig 解析（本机 2.17，FreeType 已启用）；(3) 打包一份字体进仓库。采用 (1)+(2)：先尝试 fontconfig 按语言匹配，失败再走跨发行版的候选路径表，最后才退回位图字体并打印警告。不打包字体（体积与许可证）。fontconfig 为可选：CMake 检测不到就只用路径表。

## 4. 组件

- `engine/src/editor/editor_i18n.{h,c}`（`break_editor` 库，纯 CPU，可单测）
  - `typedef enum { BREAK_EDITOR_LANG_EN_US, BREAK_EDITOR_LANG_ZH_CN, BREAK_EDITOR_LANG_COUNT } BreakEditorLang;`
  - `const char *break_editor_tr(BreakEditorI18nKey key);` 返回当前语言文本，永不返回 NULL。
  - key 是枚举（`BREAK_EDITOR_TR_TOOLBAR_ADD` 等），不是自由字符串：编译期发现拼写错误，表用 designated initializer 按枚举下标填充，测试检查每种语言每个 key 都非空。
  - `bool break_editor_i18n_set_lang(BreakEditorLang)`、`BreakEditorLang break_editor_i18n_lang(void)`、`bool break_editor_i18n_parse_lang(const char *tag, BreakEditorLang *out)`（接受 `zh-CN`、`zh_CN.UTF-8`、`zh`、`en`、`en_US` 等，大小写不敏感，未知返回 false）、`break_editor_i18n_lang_from_env(void)`（`BREAK_LANG` > `LC_ALL` > `LC_MESSAGES` > `LANG`，都无效时 `en-US`）。
  - 带格式的文本（`"Tool: %s"`、日志行）以 key 取格式串，调用点仍用 `snprintf` 的有界写入；格式参数个数/类型在两种语言中一致，测试会对每个格式 key 做一次 `snprintf` 并检查输出。
  - 状态是进程级单值（editor 单 UI 线程），文档化为 shell 线程专用。
- `engine/src/editor/editor_i18n_tables.c`：`en-US` 与 `zh-CN` 两张表。文件为 UTF-8，测试校验每条文本是合法 UTF-8。
- 字体：`engine/apps/editor/editor_fonts.{h,c}`
  - `size_t break_editor_font_candidates(BreakEditorLang lang, my_font_source_t *out, size_t cap, char *storage, size_t storage_cap)`：生成有序候选（fontconfig 匹配结果在前，然后是各平台路径表），只保留实际存在的文件。
  - Linux 路径表覆盖 Fedora（`google-noto-sans-cjk-vf-fonts`、`google-droid-sans-fonts`）、Debian/Ubuntu（`opentype/noto`、`truetype/dejavu`）、Arch（`noto-cjk`）和 wqy；拉丁字体优先放第一位保证西文观感，CJK 字体紧随其后，字体链按码位逐个回退。
  - `zh-CN` 时 CJK 字体放前面，以便标点按中文字体排版。
  - `editor_main.c` 改为使用该模块；`break_ui_init_with_fonts` 在退回位图字体时打 `LOG_WARN`（只此一处修改 myui_break，行为不变）。
- shell 刷新：`editor_panels.c` 把所有创建时写死的文本改为 `break_editor_tr(...)`；新增 `editor_shell_retranslate(shell)`，切换语言时更新工具栏、面板标题、标签、命令面板列表、状态栏，并让各列表面板 refresh。命令面板新增 “Language: English” / “语言：中文”两条命令。动态内容（实体名、文件名、日志历史）不翻译；已写入 console 的旧行保持原语言。
- `editor_main.c`：解析 `--lang <tag>`（与现有 `--remote` CLI 同一处），优先级 `--lang` > 环境。

## 5. 不做的事

- 不翻译日志文件 / `LOG_*` 输出、远程协议消息、引擎库（非 editor）文本。
- 不做 RTL、复数规则、日期/数字本地化。
- 不打包字体文件。
- 不改 myui 字体子系统，只在退回位图字体时加一条警告。

## 6. 测试（TDD）

- `test_editor_i18n`（新，headless）：每种语言每个 key 非空且为合法 UTF-8；`zh-CN` 与 `en-US` 文本不同（防止漏翻）；缺失回退；`parse_lang` 各种 tag；环境优先级；格式 key 的 `snprintf` 往返。
- `test_editor_shell`：设置 `zh-CN` 后创建 shell，工具栏/面板标题/工具标签显示中文；运行时经命令面板切换为英文后，同一批控件文本立即变化，`Tool:` 标签与当前工具一致，命令面板列表条目数不变；dummy-PAL PPM 冒烟仍通过。
- `test_editor_fonts`（新）：用临时目录模拟路径表，候选只包含存在的文件、顺序随语言变化、存储有界不截断。fontconfig 部分以“可用时至少返回一个存在的文件”断言，不依赖具体字体名。
- 源码检查：`rhi.h` 不再含误读标记；新增 CTest 脚本 `test_source_encoding.cmake` 扫描 `engine/` 与 `docs/` 中常见的 GBK 误读标记（列表在脚本里），防止回归。
- live：真实 editor 截图确认中文与英文都以矢量字体渲染（无块状 8×8 字），切换后截图变化。

## 7. 验收与交付

- 四棵非图形测试树、ASan/TSan、fuzz smoke 全绿；真实窗口中英文截图。
- 文档：`docs/design/editor_i18n.md`（用户可见行为、加新语言的步骤、字体查找顺序）；更新 `Implementation_Status.md`、roadmap、todo。
- 推送：远端 `origin` 为 `git@github.com:konyka/break.git`。2026-10-27 `git fetch` 显示两边已分叉：本地 master 有 156 个远端没有的提交（之前各阶段在本地合并、从未推送），`origin/master` 有 255 个本地没有的提交（iOS/macOS/Windows 工作，357 个文件）。直接推 master 需要先做一次大规模合并，属于另一个高风险任务，不在本次范围。本次只推送功能分支 `sdd/editor-i18n`（不 force push、不改远端 master），并用 `gh` 开 PR，在 PR 描述里说明分叉情况，由维护者决定集成方式。
