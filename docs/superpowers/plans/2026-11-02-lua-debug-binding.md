# Lua Debug Binding Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 交付默认关闭的 Lua 断点/步进/栈/局部变量检查、受界限表与 generation host 句柄，以及隔离单脚本失败的 Actor `on_actor_tick` 接线。

**Architecture:** `break_lua` 内部统一组合 count/line hook；独立 `break_lua_debug` 在同步暂停回调中检查真实 Lua 帧。受限表采用创建时预分配节点和 scratch 提交，独立 `break_kernel_lua` 通过 `break_kernel` 的无 Lua 依赖脚本桥适配 Actor。

**Tech Stack:** C11、vendored Lua 5.4、现有 `BreakLuaRuntime`/`BreakKernel`/ECS Entity、CMake、CTest、`test_framework.h`、ASan+UBSan、TSan。

## Global Constraints

- 只修改 `.worktrees/cry-lua`；不 push、不建 PR、不改 `docs/Implementation_Status.md`。
- 遵循 `docs/superpowers/specs/2026-11-02-core-capability-completion-design.md` 第 4、5、6、8 节及 `docs/design/lua_debug_binding.md`。
- 每项行为先看到断言 RED，再实现 GREEN；编译/链接缺失不是最终 RED 证据。
- 热路径不临时分配 host 内存；固定容量、深度、节点数、字符串长度，超限返回错误，不静默截断。
- 不公开 `lua_State` 或 C host 指针；模块白名单不增加 `debug/package/require/coroutine/load`。
- 不增加远程调试、socket、监听线程或未认证入口。
- 所有构建命令使用 `-j3`；focused normal、ASan+UBSan、TSan 均通过后，只读审查并修复 Critical/Important。

---

### Task 1: generation host 句柄与直接调用预算

**Files:**
- Modify: `engine/src/script/break_lua.h`
- Modify: `engine/src/script/break_lua_internal.h`
- Modify: `engine/src/script/break_lua_value.c`
- Modify: `engine/src/script/break_lua_module.c`
- Create: `engine/tests/test_break_lua_handle.c`
- Modify: `engine/CMakeLists.txt`
- Modify: `engine/tests/test_break_lua_target_contract.cmake`

**Interfaces:**

```c
#define BREAK_LUA_MAX_HOST_HANDLES 64u
typedef struct BreakLuaHostHandle { u32 slot; u32 generation; } BreakLuaHostHandle;
BreakLuaError break_lua_host_handle_acquire(BreakLuaRuntime *, u64 token,
                                             BreakLuaHostHandle *out);
BreakLuaError break_lua_host_handle_resolve(BreakLuaRuntime *,
                                             BreakLuaHostHandle, u64 *out_token);
BreakLuaError break_lua_host_handle_release(BreakLuaRuntime *,
                                             BreakLuaHostHandle);
```

向 `BreakLuaValueType` 末尾追加 `BREAK_LUA_VALUE_HOST_HANDLE`，向 union 追加 `BreakLuaHostHandle handle`。内部槽固定 64 个，保存 `token/generation/used`。内部执行 hook 入口：

```c
void break_lua_execution_hook_arm(BreakLuaRuntime *, int budget_count);
void break_lua_execution_hook_disarm(BreakLuaRuntime *);
```

- [ ] **Step 1: 写句柄、沙箱句柄值和直接调用预算的失败测试**

创建 `test_break_lua_handle.c`，至少包含：acquire/resolve 返回原 token；release 后 resolve/double-release 为 `STALE`；释放全部 64 个后槽复用而旧 handle 仍 `STALE`；第 65 个 live handle 为 `OVERLOAD`；Lua `echo(handle)` 往返相同；直接 `runtime_call` 的无限循环在 `instruction_budget=1000` 下有界返回 `FAILED` 且 trip count 增加。先用返回 `BREAK_LUA_INVALID` 的最小实现保证可构建，再运行行为 RED。

```c
BreakLuaHostHandle h = {0, 0};
ASSERT_EQ(break_lua_host_handle_acquire(rt, 42u, &h), BREAK_LUA_OK);
ASSERT_EQ(break_lua_host_handle_release(rt, h), BREAK_LUA_OK);
ASSERT_EQ(break_lua_host_handle_resolve(rt, h, &token), BREAK_LUA_STALE);
```

- [ ] **Step 2: 构建并确认行为 RED**

Run: `cmake -S engine -B build-p9-lua -DENGINE_BUILD_TESTS=ON && cmake --build build-p9-lua -j3 --target test_break_lua_handle && ./build-p9-lua/test_break_lua_handle`
Expected: 测试可执行但句柄/stale/echo/预算断言失败；记录失败用例。

- [ ] **Step 3: 实现固定槽与 Lua userdata 编组**

acquire 找空槽并初始化非零 generation；resolve 在任何 token 写入前验证 slot、used、generation；release 推进 generation，溢出槽退役而不绕回旧身份。Lua 句柄使用 `lua_newuserdatauv` 写入两个整数并设置 registry 中的锁定 metatable；`take_value` 先校验 metatable，再调用 resolve，stale 映射 `STALE`。所有 Lua touchpoint 仍在共享 pcall 内。

- [ ] **Step 4: 把直接调用纳入预算并验证 GREEN**

在 `break_lua_call_impl` 和 `break_lua_call_ref_impl` 的 `lua_pcall` 前后使用统一 arm/disarm；budget 为 0 时不启用 count。保持普通错误、返回缓冲 NIL 预填和 Lua 栈纪律。运行句柄测试及既有 value/module/runtime 测试。

Run: `ctest --test-dir build-p9-lua -R 'test_break_lua_(handle|value|module|runtime)$' --output-on-failure`
Expected: 全通过。

- [ ] **Step 5: 变异 stale 与直接调用预算**

临时让 resolve 忽略 generation，运行 `test_break_lua_handle`，确认 stale 用例变红；恢复。临时跳过直接 call 的 arm，确认预算用例变红；恢复并重跑 GREEN。不得保留变异 diff。

### Task 2: 有界递归表值

**Files:**
- Create: `engine/src/script/break_lua_table.h`
- Create: `engine/src/script/break_lua_table.c`
- Modify: `engine/src/script/break_lua_internal.h`
- Modify: `engine/CMakeLists.txt`
- Modify: `engine/tests/test_break_lua_target_contract.cmake`
- Create: `engine/tests/test_break_lua_table.c`

**Interfaces:**

```c
#define BREAK_LUA_TABLE_MAX_NODES 256u
#define BREAK_LUA_TABLE_MAX_DEPTH 16u
#define BREAK_LUA_TABLE_MAX_STRING 127u
typedef struct BreakLuaTable BreakLuaTable;
BreakLuaTable *break_lua_table_create(u32 nodes, u32 depth, u32 string_bytes);
void break_lua_table_destroy(BreakLuaTable *);
void break_lua_table_clear(BreakLuaTable *);
u32 break_lua_table_root(const BreakLuaTable *);
u32 break_lua_table_count(const BreakLuaTable *);
BreakLuaError break_lua_table_add(BreakLuaTable *, u32 parent,
    const char *key, usize key_len, const BreakLuaTableValue *, u32 *out_node);
BreakLuaError break_lua_table_add_index(BreakLuaTable *, u32 parent,
    i64 key, const BreakLuaTableValue *, u32 *out_node);
BreakLuaError break_lua_table_node(const BreakLuaTable *, u32 node,
    BreakLuaTableNodeInfo *out);
BreakLuaError break_lua_runtime_call_table(BreakLuaRuntime *,
    const char *module, const char *function,
    const BreakLuaTable *argument, BreakLuaTable *result);
```

`BreakLuaTableValue` 支持 `NIL/BOOL/NUMBER/STRING/TABLE/HOST_HANDLE`；string 输入是 `{const char *data; u32 len}`，构建时复制。`BreakLuaTableNodeInfo` 含 key、`first_child/next_sibling/depth` 和值，字符串指针仅在表未修改时借用。

- [ ] **Step 1: 写表往返与全部边界的失败测试**

覆盖字符串/整数键、嵌套表、标量、host 句柄 echo；根不计入递归深度，`max_depth=1` 允许一层子表而第二层子表 `OVERLOAD`；节点容量恰好准入、再加一个 `OVERLOAD`；key/value string 恰好上限准入、超 1 字节 `OVERLOAD`；Lua 返回超深、超节点、超长字符串时 call 返回 `OVERLOAD` 且输出保持调用前内容；循环 Lua 表有界失败；不支持 function 值返回 `FAILED`。

```c
ASSERT_EQ(break_lua_table_add(t, root, "child", 5u, &table_value, &child),
          BREAK_LUA_OK);
ASSERT_EQ(break_lua_table_add(t, child, "too_deep", 8u, &table_value, &ignored),
          BREAK_LUA_OVERLOAD);
ASSERT_EQ(break_lua_table_count(t), before);
```

- [ ] **Step 2: 确认行为 RED**

以最小构建器/返回 `INVALID` 的 `call_table` 使测试可执行。

Run: `cmake --build build-p9-lua -j3 --target test_break_lua_table && ./build-p9-lua/test_break_lua_table`
Expected: 深度、节点、字符串、往返或输出原子性断言实际失败。

- [ ] **Step 3: 实现预分配构建器和事务式 Lua marshal**

每个表持有 nodes/scratch 两块固定存储。add 在写入前检查父节点、深度、节点数、key/value string 并复制；TABLE 新建空子表，不能引用旧节点。Lua push 按节点树递归，take 用 `lua_next` 有界遍历并写入 scratch；只有完整成功后交换 active/scratch。所有路径恢复栈，环靠表深度上限终止。

- [ ] **Step 4: 验证 GREEN 与三类变异**

Run: `ctest --test-dir build-p9-lua -R 'test_break_lua_(table|handle|value|module|runtime)$' --output-on-failure`
Expected: 全通过。分别临时禁用深度检查、节点检查、字符串检查，确认对应用例变红；每次恢复后重跑表测试。

### Task 3: 独立调试库、预算 hook 组合与沙箱不变性

**Files:**
- Create: `engine/src/script/break_lua_debug.h`
- Create: `engine/src/script/break_lua_debug.c`
- Modify: `engine/src/script/break_lua_internal.h`
- Modify: `engine/src/script/break_lua_value.c`
- Modify: `engine/src/script/break_lua_module.c`
- Create: `engine/tests/test_break_lua_debug.c`
- Modify: `engine/CMakeLists.txt`
- Modify: `engine/tests/test_break_lua_target_contract.cmake`

**Interfaces:**

```c
typedef struct BreakLuaDebug BreakLuaDebug;
BreakLuaDebug *break_lua_debug_create(BreakLuaRuntime *,
                                      BreakLuaDebugPauseFn, void *user);
void break_lua_debug_destroy(BreakLuaDebug *);
BreakLuaError break_lua_debug_set_enabled(BreakLuaDebug *, bool enabled);
BreakLuaError break_lua_debug_breakpoint_set(BreakLuaDebug *,
    const char *module, u32 line, u32 *out_id);
BreakLuaError break_lua_debug_breakpoint_clear(BreakLuaDebug *, u32 id);
BreakLuaError break_lua_debug_step(BreakLuaDebug *, BreakLuaDebugStep mode);
BreakLuaError break_lua_debug_stack(BreakLuaDebug *, BreakLuaDebugFrame *out,
                                    usize capacity, usize *out_count);
BreakLuaError break_lua_debug_locals(BreakLuaDebug *, u32 frame,
    BreakLuaDebugLocal *out, usize capacity, usize *out_count);
```

回调 typedef 返回 `BreakLuaDebugStep`（`NONE/INTO/OVER/OUT`，NONE 即继续），暂停结构含 reason/module/line。帧和局部变量结构严格使用设计中的固定容量；检查仅在回调内有效。

- [ ] **Step 1: 写默认关闭、断点、步进、栈和局部变量测试**

使用嵌套 Lua 函数和已知行号。未启用时断点不触发；启用后只命中预设模块/行，回调内断言 stack 的当前函数/调用者和局部变量值，容量过小 `OVERLOAD`，回调外检查 `REJECTED`。依次请求 INTO/OVER/OUT，验证下一暂停原因与深度关系；清除断点后不再命中，未知 id `STALE`。

- [ ] **Step 2: 写预算共存和沙箱测试**

调试 enabled 且 breakpoint 命中后，一个超预算函数仍 `FAILED`/trip count 增加且预算不能被调试 hook 覆盖；普通函数在预算布防/撤防后仍命中断点。模块函数返回 `debug == nil and package == nil and require == nil and coroutine == nil and load == nil`，启用调试器前后均为 true。

- [ ] **Step 3: 确认行为 RED**

最小 debug 实现允许 create/destroy/set API 但不触发暂停。

Run: `cmake --build build-p9-lua -j3 --target test_break_lua_debug && ./build-p9-lua/test_break_lua_debug`
Expected: 命中/步进/栈/局部变量断言失败，而非只因符号缺失失败。

- [ ] **Step 4: 实现组合 hook 与同步检查**

runtime 保存观察者和 enabled 标志；arm 使用 `LUA_MASKCOUNT|LUA_MASKLINE`（按启用状态），disarm 恢复 observer-only 或空 hook。所有旧 `lua_sethook` 调用点改走组合层。debug line 回调匹配 `@module` 断点或步进条件，快照 `lua_Debug` 帧并同步调用宿主；`lua_getlocal` 仅在暂停内使用。禁用调试时零 line hook。

- [ ] **Step 5: 验证 GREEN 与逐项变异**

Run: `ctest --test-dir build-p9-lua -R 'test_break_lua_(debug|table|handle|binding|value|module|runtime)$' --output-on-failure`
Expected: 全通过。分别禁用 breakpoint match、INTO 条件、OVER/OUT 深度条件、栈快照、局部变量 marshal、预算 count mask，确认对应测试变红并恢复。沙箱断言在调试 enabled 时必须保持 GREEN。

### Task 4: Actor 通用脚本桥与独立 Lua 适配器

**Files:**
- Modify: `engine/src/kernel/break_kernel.h`
- Modify: `engine/src/kernel/break_kernel_internal.h`
- Modify: `engine/src/kernel/break_kernel_actor.c`
- Create: `engine/src/kernel/break_kernel_lua.h`
- Create: `engine/src/kernel/break_kernel_lua.c`
- Create: `engine/tests/test_break_kernel_lua.c`
- Modify: `engine/CMakeLists.txt`
- Modify: `engine/tests/test_break_kernel_target_contract.cmake`

**Interfaces:**

```c
typedef struct BreakKernelScriptBridge {
    void *user;
    void (*actor_tick)(void *, const char *module, Entity, f32);
    void (*actor_despawn)(void *, Entity);
} BreakKernelScriptBridge;
BreakKernelError break_kernel_set_script_bridge(BreakKernel *,
                                             const BreakKernelScriptBridge *);

typedef struct BreakKernelLuaAdapter BreakKernelLuaAdapter;
BreakKernelLuaAdapter *break_kernel_lua_create(BreakKernel *, BreakLuaRuntime *);
void break_kernel_lua_destroy(BreakKernelLuaAdapter *);
BreakKernelLuaFault break_kernel_lua_last_fault(const BreakKernelLuaAdapter *);
```

- [ ] **Step 1: 写真实 Actor tick、稳定身份和失败隔离测试**

注册 bad/good 两个类和模块，bad 的 `on_actor_tick` 抛错，good 增加 `state.count`。bad Actor 排在 good 前；调用两次 `break_kernel_tick` 后 good count 为 2，fault total 为 2，证明一个失败不阻断其他 Actor。good 模块保存最近收到的 handle/dt；host resolve token 验证 Entity index/generation，连续 tick handle 相同。despawn 后旧 handle `STALE`，再次生成复用 index 的新 Entity 不继承旧 handle。缺失 `on_actor_tick` 也仅记 fault 并继续。

```c
break_kernel_tick(application, 0.25f);
break_kernel_tick(application, 0.25f);
ASSERT_EQ(good_tick_count(rt), 2u);
ASSERT_EQ(break_kernel_lua_last_fault(adapter).total, 2u);
```

- [ ] **Step 2: 确认行为 RED**

最小 adapter 可创建但不注册桥，测试可执行。

Run: `cmake --build build-p9-lua -j3 --target test_break_kernel_lua && ./build-p9-lua/test_break_kernel_lua`
Expected: good tick/count、handle 或隔离断言实际失败。

- [ ] **Step 3: 实现桥和固定状态适配器**

`break_kernel` 只存 bridge POD；已有 native tick 先运行，若 Actor 仍存活再发脚本 tick，despawn 先发身份释放通知。adapter 按 actor slot 预分配 handle 状态，首次 acquire，后续复用，despawn release。每次以 `{HOST_HANDLE, NUMBER dt}` 调 `break_lua_runtime_call`，任何非 OK 写固定 fault 后继续；destroy 注销同一 bridge 并释放剩余 handle。

- [ ] **Step 4: 验证 GREEN 与失败隔离变异**

Run: `ctest --test-dir build-p9-lua -R 'test_break_kernel|test_core_style_prototype|test_break_lua' --output-on-failure`
Expected: 全通过。临时让 adapter 在首个脚本错误后停止整次 logic tick，确认 good Actor count 测试变红；恢复。临时让 despawn 不 release，确认 stale 测试变红；恢复并重跑。

### Task 5: target contract、三 lane、只读评审与交付

**Files:**
- Modify: `docs/design/lua_runtime.md`（仅同步实际 Lua 合同，不改状态总表）
- Modify: `docs/design/lua_debug_binding.md`（若实现评审改变合同则同步）
- Create: `.superpowers/sdd/lua-debug-binding-report.md`

- [ ] **Step 1: 验证独立 target 和沙箱/链接边界**

更新 contract 检查 `break_lua_debug`、`break_kernel_lua` 顶层 target、各自源文件和链接方向，且 `engine/engine_demo/dxx_break` 不含新库。配置 `ENGINE_BUILD_TESTS=OFF` 树并以 `-j3` 构建三个生产库；用 `nm` 检查生产 `break_lua` 无 test hooks。

- [ ] **Step 2: 配置并运行三棵 focused lane**

使用项目既有编译选项，正常树和以下两树分别构建；每步 `-j3`：

```bash
cmake -S engine -B build-p9-lua-asan -DENGINE_BUILD_TESTS=ON \
  -DCMAKE_C_FLAGS='-fsanitize=address,undefined -fno-omit-frame-pointer' \
  -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'
cmake -S engine -B build-p9-lua-tsan -DENGINE_BUILD_TESTS=ON \
  -DCMAKE_C_FLAGS='-fsanitize=thread -fno-omit-frame-pointer' \
  -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=thread'
ctest --test-dir build-p9-lua-asan -R 'test_break_lua|test_break_kernel|test_core_style_prototype|test_script_lua' --output-on-failure
ctest --test-dir build-p9-lua-tsan -R 'test_break_lua|test_break_kernel|test_core_style_prototype|test_script_lua' --output-on-failure
```

Expected: focused 全通过，无 sanitizer 报告。若机器运行时 TSan 自身不可用，保留构建/诊断证据并明确限制，不声称运行通过。

- [ ] **Step 3: 只读评审和修复**

以只读 reviewer 视角检查 pcall/栈平衡、hook 恢复、暂停帧生命周期、表环/溢出/事务、handle generation、Actor 失败隔离和 target 链接方向。修复所有 Critical/Important，重新跑受影响测试与三 lane；不修改范围外模块。

- [ ] **Step 4: 报告、diff 检查与提交**

报告逐项记录设计/计划、实际 RED/GREEN、每个变异及结果、三 lane 命令和通过数、独立 target/沙箱/无远程入口证据、未验证平台限制。运行 `git diff --check`、检查 `git status`，只提交本任务文件：

```bash
git add engine docs/design .superpowers/sdd/lua-debug-binding-report.md
git commit -m "lua: add bounded debugging and actor script bindings"
```

不 push、不建 PR。
