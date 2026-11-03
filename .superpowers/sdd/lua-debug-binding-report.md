# P9 Lua 调试、表绑定与 Actor 接线报告

## 状态

已在 `cry-wave2-lua` 完成实现、focused normal/ASan+UBSan/TSan 验证、自审和变异验证。未修改 `docs/Implementation_Status.md`，未修改 master 或其他子项目，未 push、未创建 PR。

设计：`docs/design/lua_debug_binding.md`（commit `734cf882`）。计划：`docs/superpowers/plans/2026-11-02-lua-debug-binding.md`（commit `01c3d1f0`）。实现与本报告在后续本地提交中。

## 交付内容

- `break_lua_debug`：独立可选库，创建后默认 disabled；32 个断点、INTO/OVER/OUT、同步暂停回调、最多 32 个 Lua 帧的栈检查和有界局部变量检查。检查仅在暂停现场有效，输出容量不足显式 `OVERLOAD`，不向脚本暴露 `debug/package`。
- `break_lua` 内部组合 hook：同一回调按事件分发 count 预算和 line 调试，arm/disarm 后恢复正确 mask。直接 call、call_ref、table call 也纳入单次指令预算。
- `break_lua_table.h/.c`：预分配节点树，硬上限 256 节点、16 层表递归、127 字节字符串；创建参数可进一步收紧。支持字符串/整数键、标量、嵌套表和 host 句柄。Lua 输出先写 scratch，成功才交换；深度/节点/字符串超限、循环和不支持类型均保持旧输出。
- host 句柄：每 runtime 64 个固定槽，`{slot, generation}`，release 和槽复用后旧身份 `STALE`。Lua full userdata 只含两个整数，metatable 锁定，marshal 回 host 时重新验证 registry；不传 C host 地址。
- `break_game_lua`：独立适配库；`break_game` 只保存无 Lua 依赖的通用脚本桥。类 `lua_module` 经真实 `break_lua_runtime_call` 调用 `on_actor_tick(handle, dt)`；Entity index/generation 编入 host token，despawn 立即 release。脚本错误、缺失 hook、句柄容量或预算失败只记录有界 fault，后续 Actor 继续 tick。
- 没有新增远程调试、socket、监听线程或认证旁路。未来远程调试必须在独立应用中显式启用并授权。

## RED / GREEN 证据

- 基线：现有 runtime/module/value/binding/actor 5 项 CTest 全过。
- 句柄与直接预算：最小桩运行 `test_break_lua_handle`，0/3；句柄实现后 2/3，直接调用预算用例仍 RED；布防后 3/3。
- 表：最小桩运行 `test_break_lua_table`，3 个行为用例 RED，创建硬上限用例通过；构建器完成后边界用例转绿，两个 Lua 调用用例仍 RED；递归 marshal/scratch 提交后 4/4。
- 调试：可执行但不安装 hook 的桩使断点、三种步进、栈/局部变量和预算协作均 RED；加入宿主主动 INTO 后合计 6 个失败、沙箱封闭性 1 个通过。完整实现后 7/7。
- Actor：未接桥的 adapter 使两个用例均 RED；通用桥和适配器实现后 2/2，既有 game/cry 回归 10/10。

测试夹具修正均有实际诊断依据：直接调用测试不再别名输入/返回缓冲；表 key 不再意外超过同例字符串上限；Lua 算式改为 `5*2+3=13`；调用者帧以定义行验证，因为宿主 C 调用的外层帧没有 Lua 名称；预算测试以普通 `inner` 断点夹住布防/撤防，而不是依赖空循环行事件。

## 变异证据

所有变异均临时修改、运行、随后恢复；最终三 lane 在恢复后全绿。

- stale：忽略 generation 后，槽复用旧句柄 resolve 错误地成功，测试 RED。
- 直接预算：禁用 call/call_ref arm 后，有限长 spin 调用错误地返回 OK，测试 RED。
- 表深度：放宽一层最初因测试 key 超长而被掩蔽；修正 key 后同一变异常被深度断言杀死。节点判断收紧一层后，恰好容量准入 RED。字符串 `>` 改成 `>=` 后，恰好上限的 key/value RED。
- 断点：禁用 breakpoint match 后 5 个相关用例 RED。INTO、OVER、OUT 分别禁用后，对应步进测试 RED；INTO 变异同时被宿主主动步进用例杀死。
- 栈：不推进捕获帧数后，栈内容断言和 OUT 深度断言 RED。局部变量 number 改成 0 后，`value == 5` 断言 RED。
- 预算共存：组合 hook 删除 `LUA_MASKCOUNT` 后，启用调试器的 spin 不再跳闸，测试 RED。
- Actor 隔离：发生一次 fault 后跳过后续 Actor 调用，bad/good 与 missing/good 两个隔离用例均 RED。省略 despawn release 后，旧 Actor 句柄未变成 STALE，测试 RED。

## 构建与最终测试

所有编译命令使用 `cmake --build ... -j3`。

- normal `build-p9-lua`：focused CTest 20/20。
- ASan+UBSan `build-p9-lua-asan`：`-fsanitize=address,undefined -fno-omit-frame-pointer`，`ASAN_OPTIONS=detect_leaks=1`、`UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1`，20/20，无报告。
- TSan `build-p9-lua-tsan`：`-fsanitize=thread -fno-omit-frame-pointer`，`TSAN_OPTIONS=halt_on_error=1`，20/20，无报告。
- 三棵树共同 CTest 选择器：`test_break_lua|test_break_game|test_cry_style_prototype|test_script_lua`，覆盖既有兼容层、Lua runtime/module/value/binding/ecs_apply、新 handle/table/debug、全部 break_game、cry_style 和两个 target contract。
- `build-p9-lua-notests` 以 `ENGINE_BUILD_TESTS=OFF` 构建 `break_lua`、`break_lua_debug`、`break_game_lua` 成功。`nm -g --defined-only` 未显示任何 `break_lua_test_*` 导出。
- `git diff --check` 在提交前执行；构建目录未进入 git 状态。

## 自审与修复

只读检查了 owner 线程、pcall/栈恢复、暂停帧生命周期、hook mask 恢复、表递归/事务、generation 复用、Actor 失败隔离和链接方向。未发现未修复 Critical。

一项 Important 已修复：Lua → table 的字符串原先先转为 `u32` 再交给上限检查；现在在 `size_t` 原值上先检查，再转换，避免极长输入 narrowing 后绕过限制。另一个 contract 测试正则误把 `break_game_lua` 前缀视为 `break_game` 核心，已改成精确目标名，没有放宽核心禁链检查。

## 限制

- 验证环境为当前 Linux/GCC；没有执行 Windows 构建或 CI，不声称 Windows 已验证。
- 调试是 owner 线程上的同步暂停回调，不是跨线程挂起/恢复协议；没有远程调试实现或 UI 集成。
- 指令预算按 Lua VM 指令计数，单个 C 标准库调用内部循环不计入；既有内存预算继续提供分配上限。
- 既有 test-only mid-frame reloader 的嵌套 count 覆盖限制仍按源码注释保留；生产沙箱没有 reload 绑定。普通模块执行、直接调用和 frame hook 的预算/调试组合已由测试覆盖。
- 固定上限是有意合同：64 live host handles/runtime、32 breakpoints、32 captured Lua frames、256 table nodes、16 表深度、127 字节字符串；超限返回错误而非增长或静默截断。

## Fix round 1：评审地址泄露与覆盖补强

### 修复与新增覆盖

- `break_lua_value.c` 在 host-handle metatable 初次创建时安装受控 `__tostring`，只返回固定文本 `break_lua.host_handle`。没有使用 `lua_topointer`；`__metatable=false`、userdata 中的 slot/generation、registry 校验和 stale 语义均未改变。
- `test_break_lua_handle.c` 新增 `host_handle_tostring_and_print_do_not_expose_an_address`，真实模块同时执行 `print(handle)` 和 `tostring(handle)`，并继续断言 `debug/package` 缺席。
- `test_break_lua_debug.c` 新增 outer line 7 断点：INTO 必须在 inner line 2 暂停且栈更深，OVER 必须在 outer line 8 暂停且深度不变。
- `test_break_lua_table.c` 新增 `{a=shared,b=shared}`：根加两个独立子树共 5 节点，两个 value 节点不同且都为 7；后续 9 字节字符串超限保持这 5 节点，向 a 添加 `only_a` 不影响 b。

### RED、GREEN 与变异输出

handle 回归在安装 `__tostring` 前实际输出 Lua 堆地址：

```text
host_handle_tostring_and_print_do_not_expose_an_address ... break_lua.host_handle: 0x1efa41f0
FAIL: "break_lua.host_handle: 0x1efa41f0" != "break_lua.host_handle"
Results: 3 passed, 1 failed, 4 total
```

最小修复后，同一真实调用输出固定文本，4/4 通过；原有 release/reuse/stale 测试保持通过：

```text
host_handle_tostring_and_print_do_not_expose_an_address ... break_lua.host_handle
OK
Results: 4 passed, 0 failed, 4 total
```

跨层级步进和共享表属于评审确认的“实现已正确、覆盖不足”，新增测试在原实现上分别为 9/9 和 5/5，不伪造功能缺失 RED。随后用变异证明覆盖有效：

- INTO 改成 OVER 的深度判断：跨层级 INTO 的 `probe.lines[1]` 断言 RED，宿主主动 INTO 也 RED；OVER 改成总是命中后，跨层级 OVER 行号断言 RED。恢复后 9/9。
- 跳过第二棵共享子树展开：新共享表用例在 `count == 5` 处 RED。移除失败时的 scratch 交换/count 恢复后，新共享用例在失败后续调用仍应为 5 节点处 RED，既有输出原子性用例也 RED。恢复后 5/5。

### focused 命令与结果

所有增量构建均为 `cmake --build <tree> -j3 --target test_break_lua_handle test_break_lua_debug test_break_lua_table`，然后执行：

```bash
ctest --test-dir build-p9-lua -R 'test_break_lua|test_break_game|test_cry_style_prototype|test_script_lua' --output-on-failure
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
  ctest --test-dir build-p9-lua-asan -R 'test_break_lua|test_break_game|test_cry_style_prototype|test_script_lua' --output-on-failure
TSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir build-p9-lua-tsan -R 'test_break_lua|test_break_game|test_cry_style_prototype|test_script_lua' --output-on-failure
```

三棵树均输出 `100% tests passed, 0 tests failed out of 20`，ASan+UBSan/TSan 无诊断。`build-p9-lua-notests` 中 `break_lua`、`break_lua_debug`、`break_game_lua` 也以 `-j3` 重建成功。`git diff --check` 无输出、退出码 0。

验证限制同前：仅当前 Linux/GCC focused 范围，未执行 Windows 或全仓库套件；没有远程调试入口。
