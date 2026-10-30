# Lua Runtime（`break_lua`）facade 合同

## 1. 文档定位与状态词汇

本文记录 Stage 3 正式可选静态库 `break_lua` 到 Task 4 为止的**已交付** facade 合同，并明确区分仍为**设计-only** 的部分。状态词汇沿用 runtime 设计文档惯例：

- **已交付**：代码、测试与 sanitizer lane 证据齐备的行为（Task 5 closeout 干净树 `build-sdd-l5{,-asan,-tsan}`，报告 `.superpowers/sdd/2026-10-23-lua-runtime/task-{1,2,3,4,5}-report.md`）。
- **设计-only / 未实现**：接口或意图已记录，但当前无任何代码承诺；不得写成已完成。

`break_lua` 是正式可选库：`engine/CMakeLists.txt` 顶层 target（`ENGINE_BUILD_TESTS=OFF` 时同样产出），**不**链入 `engine`、`engine_demo`、`dxx_break`；本条目不构成 engine/demo 集成证据。兼容层 `engine/src/script/script_lua.c/.h` 保持逐字节不变，`test_script_lua` 在每个 lane 绿灯。

## 2. 已交付合同总览

### 2.1 类型与错误分类法（Task 1）

- `BreakLuaError` 九类：`OK / INVALID / CLOSED / OVERLOAD / OOM / TIMEOUT / STALE / REJECTED / FAILED`，形状镜像 Stage 2 runtime_core 分类法但不依赖其头文件。当前映射现状：`CLOSED` 保留（尚无 close 语义）；`TIMEOUT` 保留（指令预算故障走 FAILED 类记录，不映射 TIMEOUT）。
- 硬上限：`BREAK_LUA_MAX_MODULE_BYTES = 1 MiB`（与 `LUA_SCRIPT_MAX_FILE_BYTES` 同一信任边界）、`BREAK_LUA_MAX_MODULES = 1024`（默认 64）、`BREAK_LUA_MAX_VALUES = 64`（per-call args/returns 上限）、`BREAK_LUA_MAX_MODULE_NAME_BYTES = 128`（module 名与函数名共用该有界扫描）、`BREAK_LUA_VALUE_STRING_CAPACITY = 128`（Task 3，含 NUL）。
- `BreakLuaRuntimeConfig`：`max_modules / max_values / max_module_bytes / instruction_budget`，0 ⇒ 默认值；超硬上限 fail-closed 返回 NULL（INVALID 类，绝不 clamp）。
- opaque `BreakLuaRuntime`；公共 API 永不暴露 `lua_State*` 或任何裸 host 句柄（World/RHI/network/线程）。

### 2.2 生命周期与 owner 线程（Task 1）

- one runtime = one lua_State = one owner thread：create 记录调用线程；无 mutex，多 owner 是合约违规而非支持模式（runtime_coordinator 同一约定）。
- base libs 经 `luaL_openlibs` 在 `lua_pcall` 保护下打开：Lua 侧分配失败 fail-closed 返回 NULL，绝不 panic。
- owner-only 查询 API（`break_lua_runtime_effective_config`）跨线程 → `REJECTED`；`break_lua_runtime_check_owner` 是文档化探针。
- `destroy(NULL)` no-op；double destroy 在 `BREAK_LUA_TESTING` 构建下 fail-stop abort，production 未定义。

### 2.3 模块：加载与版本化 reload（Task 2）

- load：text chunk（拒绝 bytecode）在全新 per-module 环境编译执行；环境全局经 metatable `__index` 解析到固定**白名单沙箱**（§2.7；base 全局表对 module 永不可达）；`state` 全局指向与 chunk 分离的持久 state 表，跨 reload 按身份保留。覆盖语义与代码一致：chunk 把 `state` 覆盖成**另一张 table** 时该新 table 从此按身份保留；仅 nil 化（或替换为非 table 值）才放弃保留，下一次 reload 对全新空表 staging。
- 身份 = 名字 + 单调递增 u32 version（首载 1）；hash = 源字节 FNV-1a-64（签名验证属 Stage 5，仅记录元数据字段）。
- reload 三段式原子提交：staging（新环境 + 保留 state）→ 旧环境可选 `on_unload`（pcall 保护）→ commit（退役旧环境、version+1）。任一失败保持旧版本完整服务（`committed == false`）；只有环境/版本 commit 是原子的，staging 对 `state` 的部分写入不回滚（文档化并测试钉住）。
- 错误面：重复 load → `REJECTED`；source 超字节上限 → `OVERLOAD`（含边界值准入）；registry 满 → `OVERLOAD`；未知名字 reload → `STALE`（绝不隐式 load）；staging/on_unload 失败 → `FAILED`；Lua 侧分配失败 → `OOM`（所有会分配的 Lua C API 均在 pcall 保护的 dispatch 闭包内）；version 达 `UINT32_MAX` → `REJECTED`。`BreakLuaReloadReport` 在每条返回路径完整写回。
- 模块在运行时不得覆盖核心代码、网络协议或安全策略：当前 facade 无任何此类入口（bindings 尚未存在）。

### 2.4 值编组与模块调用（Task 3）

- `BreakLuaValue`：nil / bool / f64 number / 有界 string（`data[128] + len`，产出串恒 NUL 结尾于 `data[len]`，len ≤ 127）。模型外的 Lua 值（table/function/userdata/thread）不可表示 → 调用以 `FAILED` 有界失败，绝不静默映射。
- `break_lua_runtime_call(runtime, module, function, args, arg_count, returns, return_capacity)`：
  - 目标函数必须是 module 活动环境的**原始字段**（chunk 自定义）；仅经 metatable 白名单回落可解析的名字（如 `tostring`）**不可**调用 → `INVALID`。
  - 检查顺序（全部有界）：owner（非 owner → `REJECTED`，最先检查）→ 形状（NULL/空/超长名字、NULL 指针配对 → `INVALID`，畸形调用不触碰 Lua 状态）→ 计数上限（arg_count 或 return_capacity 超 `max_values` → `OVERLOAD`，恰在上限准入）→ 未知 module → `STALE`（与 reload 合同一致）→ 字段缺失或非函数 → `INVALID`。
  - STRING 参数 `len >= 128`（有界缓冲放不下）→ `OVERLOAD`，不发生任何读取；返回串超长 → `OVERLOAD`，绝不溢出。
  - 被调函数抛 Lua 错误 → `FAILED`；路径上任何 Lua 侧分配失败 → `OOM`（整个调用经共享 pcall dispatch，Lua 错误绝不 panic 进程）。
  - 返回缓冲：准入通过后先整体 NIL 预填，再以 exactly `return_capacity` 个期望返回值调用（Lua 自动 nil 补齐不足、丢弃多余），缓冲必然写满、Lua 栈在所有出口平衡；准入前失败不写缓冲。
- Lua 栈纪律：测试用 test-only VM accessor 断言每次 call/frame 后 `lua_gettop == 0`。
- **指令预算覆盖范围**：只有帧 hook（`on_frame_begin`/`on_frame_end`，§2.5）在计数钩子下运行；`break_lua_runtime_call` 与 load/reload/`on_unload` **全程无指令预算**。已知边界：预算按 VM 指令计数，单个 C 调用内部的循环不计入——白名单内的 `string.rep` 一次调用即可完成大额分配/拼接而不触发预算（文档化已知边界；allocator 级内存预算见 §3 设计-only）。

### 2.5 帧生命周期（Task 3）

- hook 名（测试钉住）：`on_frame_begin(dt)` 原样收到 `delta_seconds`（Lua number）；`on_frame_end()` 无参。hook 必须是环境的原始函数字段；无 hook 的 module 直接跳过（非错误）。hook 返回值丢弃。
- `begin_frame` / `end_frame` 是两次相互独立的 dispatch：配对是 host 的责任，单独调用任一个都合法；`begin_frame` 递增 u64 帧序号（诊断用）。
- **稳定 registry 快照**：每次 dispatch 先把每个占用 slot 的活动环境用 **Lua 栈引用** pin 住（ref-based，绝不持 registry slot 指针），连同名字与 hooks-disabled 标志一起快照；dispatch 只服务该快照：
  - module 在 dispatch 中途被 reload：本次仍以被 pin 的旧环境服务（pin 保活已退役表），新版本从下一次 dispatch 起服务。Task 3 中脚本尚无法触发 reload（bindings 属 Task 4），该路径经 test-only `_test_reload_now` binding 验证；host 在 begin/end 之间调 reload 则两次 dispatch 各自独立快照。
  - 快照时刻被禁用的 module 整个 dispatch 保持跳过，即使中途 reload。
- **hook 错误策略**：每个 hook 在各自的 `lua_pcall` 下运行。失败的 hook 产生一条**有界错误记录**（module 名、hook 名、127 字节截断 + NUL 的消息、帧序号、生命周期计数器；本任务经 `BREAK_LUA_TESTING` 探针观测），其余 module 继续运行。普通 hook 错误**不**禁用 module，下一帧照常服务。
- **指令预算**（`config.instruction_budget`，0 = 禁用）：启用时每次 hook 调用在独立的 Lua 计数钩子（`lua_sethook LUA_MASKCOUNT`）下运行；超过 2³¹-1 的预算 clamp 到 2³¹-1。记账是**每次 hook 调用**独立的，不跨 module、不跨帧累计。**coroutine 逃逸已在 Task 4 关闭（已交付）**：Lua 5.4 hook 是 per-coroutine 的（lstate.c: `lua_newthread` → `resethookcount`，加载期线程 hook mask 为 0），故 Task 4 沙箱**不向 module 环境暴露 `coroutine` 全局**（§2.7）——module 代码只能跑在主 coroutine 上，预算 hook 内的一切嵌套 Lua 执行（pcall 链、test-only reloader、`brk.ecs`/`brk.config` 闭包等）都递减同一 armed countdown。测试钉住：预算 hook 内尝试 `coroutine.wrap` 得到的是全局缺失（有界普通 hook 错误，非 budget trip，不标记禁用 module）。**pcall 逃逸通道已在 Stage 4 Phase 3 Task 2 评审修复中关闭（NEW-C4）**：计数钩子在触发前会重置 countdown（ldebug.c `resethookcount`）且错误落到**最近的** pcall——若 trip 是普通字符串错误值，脚本自己的 pcall 就能捕获它，每轮 pcall 烧满一次预算后自我续命（实测 `while true do pcall(function() while true do end end) end` 永不返回）。现 trip 抛出的是 **host 持有的 sentinel 值**（lightuserdata，指向 runtime 自有字段地址——沙箱内无任何构造/获取/比较 lightuserdata 的路径），且沙箱版 `pcall`/`xpcall` 是对该 sentinel **透明重抛**的 C 包装（普通错误仍按原样返回 `(false, err)`；xpcall 的脚本 handler 由包装器在调用返回后（post-unwind）自行调用——仅对普通错误；handler 自身抛出的普通错误被 xpcall 吸收，返回 `(false, "error in error handling")`，与 base 5.4 的 LUA_ERRERR 语义逐字节一致——Stage 4 Phase 3 Task 2 评审轮 5 修复实证；handler 内触发的 trip 仍被穿透重抛，不可捕获。post-unwind 相对 base 的 pre-unwind（经 VM errfunc）有一处**纯外观**残余差异：沙箱内唯一可及的栈相关操作是 `error(msg, level)` 的位置前缀（debug 库缺席）。解析到 handler 帧及其直接调用者的 level 在两侧一致（该帧两侧都是 C 帧——base 侧是触发 handler 的 error() C 帧，wrapper 侧是包装器自身）；第一个**不同**的帧再深一层：base 沿尚未退栈的错误链走到被调函数的出错行，wrapper 则落到 xpcall 的调用点——差异仅限位置前缀内容，消息文本、结果值与可捕获性均与 base 逐比特一致，`test_break_lua_binding` 轮 5 用例钉住）；**脚本无法在任何嵌套深度捕获 trip，也永远观测不到 sentinel 值**。一次 trip 必然传播到 host 侧捕获点（per-hook pcall / staging pcall / commit pcall）并终止该次受保护执行。残余事实：单轮 pcall 最多可烧满一次预算才触发 trip，但 trip 不可捕获 ⇒ 恰好一次 trip 即终止，界限成立。超预算 → hook 以 sentinel 错误中止：错误文本捕获统一映射为规范文本 "break_lua: instruction budget exceeded"（sentinel 为 lua_error 裸抛，**从不带位置前缀**，error_line 为 0），记录带 budget 标志的错误记录，并**标记**该 module——后续 dispatch 跳过其帧 hook，直到下一次成功提交的 reload 清除标记（fail-closed 的失控 module 确定性策略）；其余 module 不受影响。生命周期 trip 计数经 `break_lua_runtime_budget_trip_count()` 公开（owner-only，NULL/非 owner 返回 0）——host 借此区分 trip 与 dispatch 级故障。另：staging 执行（load/reload 的 chunk 运行）与 commit 路径 `on_unload` 同样在预算布防之下（同次评审修复——此前这两条路径无预算，死循环 chunk 会挂死 host 线程；跳闸=有界 FAILED/staging 失败+旧版本保留/有界 veto）。`call`/`call_ref` 保持**不布防**（文档化——需要预算的 host 走帧 hook 派发）。
- owner 线程：`call` 非 owner → `REJECTED`；`begin_frame`/`end_frame` 返回 void，非 owner 调用是合约违规——test 构建 fail-stop abort（double-destroy 同一先例），production 构建忽略（no-op）；NULL runtime 对 begin/end 是 no-op。

### 2.6 host bindings：有界 ECS batch 命令与 config（Task 4）

- **安全边界（验收标准）**：scripts 永不可达裸 RHI/physics/network 句柄——`break_lua` 内**不存在任何 World 指针**，且任何 host 指针都绝不压入 Lua 状态（无 userdata/lightuserdata；闭包经 `lua_getextraspace` 取得 runtime，与 Task 3 预算回调同一先例）。唯一 host 接触面是脚本可见的 `break` 表链。
- **`break` 名字与 Lua 关键字冲突（合同决策）**：`break` 是 Lua 保留字，brief 字面的 `break.ecs.spawn()` 不是合法 Lua 语法。host 表以字面名 `"break"` 注册于白名单，**并**以别名 `brk` 注册同一 proxy；脚本写 `brk.ecs.spawn()` 或 `_G["break"].ecs.spawn()`（测试同时钉住两种形式与 `_G['break'] == brk` 同一性）。
- **ECS batch**：opaque `BreakLuaEcsBatch` 是 **host 所有**的有界 FIFO 命令缓冲（`break_lua_ecs_batch_create(capacity)`，0 ⇒ 默认 256，硬上限 4096 与 checked multiply 超限 fail-closed 返回 NULL；`break_lua_ecs_batch_destroy`）；runtime 经 `break_lua_runtime_bind_ecs_batch` **借用**（一对一、一次性；任一侧已绑定 → `REJECTED`；runtime destroy 或 batch destroy 都会解除借用，永不悬垂）。脚本 `brk.ecs.spawn()` / `brk.ecs.set(component, field, value)` enqueue 记录；host 以 `break_lua_ecs_batch_drain(batch, out, capacity)` 按 FIFO 取出（返回条数；NULL/零容量/非 owner 线程 → 有界 0）。facade **从不自行 apply**——无 World 存在，apply 完全是 host 的事。
  - **记录格式（drain 线格式）**：`BreakLuaEcsRecord` 定长 POD——`u16 kind`（SPAWN=1/SET=2）+ 有界 payload：`u16 value_type`（NONE/NUMBER/BOOL/STRING）、NUL 结尾的 component/field（各 ≤ 63 字节，`BREAK_LUA_ECS_NAME_CAPACITY 64` 含 NUL；SPAWN 为零化）、值 union（f64 / bool / ≤ 63 字节 NUL 结尾 string）。
  - **有界失败**：batch 满 → 脚本得 `(false, "break.ecs: batch full")`——绝不阻塞、绝不 raise；未绑定 batch → `(false, "break.ecs: no batch bound")`；参数形状错误（component/field 非 string、空、超 63 字节；value 非 number/bool/string 或 string 超 63 字节）→ 同样有界 `(false, message)`，且**先于** batch 检查、不入队任何记录。
- **config**：`break_lua_runtime_bind_config(runtime, entries, count)` 注册 `{key, min, max, initial}`；`brk.config.get(key)` 返回 Lua number。**clamp 在 bind 时**（initial 越界存 clamp 后边界），脚本读恒在界内；未知/畸形 key → `(nil, message)`，绝不 raise。校验 all-or-nothing（拒绝则一条不注册）：NULL/空/≥128 字节 key、NaN 或 min>max → `INVALID`；重复 key（调用内或已绑定）→ `REJECTED`；累计超 `BREAK_LUA_MAX_CONFIG_BINDINGS 256` → `OVERLOAD`；entry_count 0 → OK no-op；store 分配失败 → `OOM`。动态 host 侧更新本任务不交付（值在 destroy 前固定）。
- **owner 线程**：全部新 API 先查 owner——bind 两个 API 非 owner → `REJECTED`（runtime 与 batch 各自的 owner 都查）；drain 非 batch owner → 有界 0；batch destroy 非 owner：test 构建 fail-stop abort、production no-op；double destroy/外来指针：test 构建按值查 registry 先 fail-stop abort（**绝不先解引用**，ASan lane 实证），production 未定义。

### 2.7 module 沙箱（Task 4，已交付）

- module chunk 在全新 per-module 环境执行，其 metatable `__index` 指向**每 runtime 固定白名单表**（create 时构建于 registry，脚本不可达；`break_lua_binding_bootstrap`）。白名单：base 函数 `assert/error/ipairs/pairs/select/tonumber/tostring/type/print` 与 `_VERSION` 字符串；`pcall`/`xpcall` 以**预算透明 C 包装**安装（普通错误语义不变；budget-trip sentinel 一律重抛，脚本不可捕获——见 §2.5）；库表 `string/table/math/utf8`（全量，经只读 proxy 暴露）；**os 子集恰为 `os.clock`/`os.time`/`os.date`**（重建表）；`break`/`brk` host 表；`env._G` 指向 module 自身环境。
- **按构造缺席**（白名单不复制即不存在）：`io`、`debug`、`package`、`require`、**`coroutine`**（per-coroutine hook 预算逃逸向量，见 §2.5）、`load`/`loadstring`/`loadfile`/`dofile`（**整体丢弃**而非限制——module 只由 host 喂源，无脚本侧编译路径需要监管）、`collectgarbage`、`warn`、`unpack`、`next`、`rawget`/`rawset`/`rawequal`/`rawlen`、`setmetatable`/`getmetatable`。raw/metatable 变更类函数的排除是代理不可伪造的前提：没有它们，脚本无任何路径绕过 proxy 的 `__newindex` 守卫。
- **只读表**：所有脚本可见的绑定/stdlib 表（`break`/`brk` 链、`string`/`table`/`math`/`utf8`、os 子集）是每 runtime 一份的**读穿 proxy**——空表 + metatable `__index` 指向 registry 持有的 impl 表 + `__newindex` raise（"attempted to mutate a read-only table"）+ 锁定 metatable。赋值（`brk.ecs.spawn = f`）以有界 Lua 错误失败；`pairs(proxy)` 为空（proxy 无 raw 字段，枚举找不到任何 userdata）；单 module 无法毒化兄弟 module 的 stdlib 视图（测试钉住：A 的 mutation 尝试全部被 trap，B 的 `string.rep`/`os.clock` 完好）。
- 脚本可达面即 `break.*`/`brk.*` 的 spawn/set/get 三个 C 闭包：不 raise、不阻塞、不触碰 Lua 栈之外的状态；闭包只在既有 dispatch pcall 壳内运行（chunk staging、module call、per-hook pcall、on_unload），新增的公开 bind/drain API 是纯 C（不触碰 Lua 状态），Lua 栈在全部出口平衡（测试断言 `lua_gettop == 0`）。

### 2.8 测试钩子（test-only，`BREAK_LUA_TESTING`）

`break_lua_test` 变体编译同一批 TU 并加入：分配故障注入（单一 budget 同时覆盖 struct calloc 与 Lua allocator）、runtime 与 ECS batch 两个 double-destroy fail-stop registry（均按值查询、绝不先解引用）、类型擦除 VM accessor、module registry/env/state 探针、帧错误记录与 hooks-disabled 探针、`_test_reload_now` mid-frame reload binding。production `libbreak_lua.a` 经 nm 验证 0 个 test-hook 符号。

### 2.7 内存预算（2026-10-30）

- `BreakLuaRuntimeConfig.memory_budget`（字节，0 = 不限）：VM 分配器统计交给 Lua 的全部字节，任何会让总量超过预算的增长请求返回 NULL；Lua 先做一次紧急 GC，仍不够则抛 LUA_ERRMEM，load/reload/call/帧钩子因此以 `BREAK_LUA_OOM` 失败而不是 abort，垃圾回收后 VM 继续可用。缩小与释放总是成功。预算小到连标准库都打不开时 `create` 返回 NULL。
- `break_lua_runtime_memory_in_use(rt)` 返回当前字节数（owner-only，NULL/非 owner 返回 0）；`effective_config` 回报 `memory_budget`。
- 测试：`test_break_lua_runtime` 新增 `memory_budget_caps_vm_allocation_and_fails_closed`（默认不限、过小预算 create 失败、1 MiB 预算下小请求成功、10 万元素请求 OOM 且用量不超预算、之后 VM 仍可用）；去掉预算判断后该例变红；ASan 树下 4 个 break_lua 二进制全绿。
- 使用方：编辑器 Lua console 的两个 VM 各设 64 MiB（`BREAK_EDITOR_LUA_MEMORY_BUDGET`，`editor_lua.h`）。

### 2.8 host 侧 config 更新（2026-10-30）

- `break_lua_runtime_set_config(rt, key, value)`：更新一个已绑定的 config 值，按该项 `[min, max]` 夹紧（与 bind 相同）；脚本下一次 `break.config.get` 即读到新值。owner-only（非 owner → REJECTED）；NULL runtime、NULL/空/超长 key、NaN → INVALID；未绑定的 key → STALE；失败不改动已存值。
- 测试：`test_break_lua_binding` 新增 `set_config_updates_bound_value_clamped`；去掉上限夹紧后该例变红；ASan 树 33/33。

### 2.9 batch 记录施加到运行时 ECS World（2026-10-30）

- `engine/src/script/break_lua_ecs_apply.{h,c}`：`break_lua_ecs_apply(world, schema, n, records, count, &report)`。host 用 schema 声明脚本可写的字段（组件名 + 字段名 → `ComponentType` + f32 偏移），drain 后调用。SPAWN → `world_create_entity`，成为本次调用中后续 SET 的目标；SET 写一个 f32 字段，实体缺该组件时先添加（零初始化；`world_add_component` 自 2026-10-30 起保证清零，见下）。值可为有限数、bool（1/0）或可完整解析为有限 f32 的字符串。以下情况记为 rejected 且不写入：本次调用里之前没有 SPAWN、schema 中无此组件/字段、组件未在 World 注册或尺寸放不下该字段、值无法转换、未知记录类型。不分配内存，不终止于单条失败。
- 不属于 `break_lua` 目标（该库按契约不依赖 ECS）；host 自行把这个 TU 加入构建。编辑器 Lua console 仍走自己的文档路径（`console_apply_records`，可撤销）。
- 测试：`test_break_lua_ecs_apply` 3 例（真实 Lua 模块 spawn/set 进 World，含 bool/字符串值和两次调用目标隔离；九类非法记录全部拒绝且不写入；复用 chunk 内存时新加组件被清零）。变异：去掉尺寸检查使一例变红；ASan 树 3/3。这条清零测试暴露了 ECS 本身的问题：`world_add_component` 返回的是复用行里被销毁实体的旧字节——已在 `ecs.c` 修复（新加组件 `memset` 清零），`test_ecs` 新增 `ecs_added_component_is_zeroed_on_reused_slot`（修复前失败：读到 11.0）。
- 2026-10-30 补充（修复）：字符串值原来直接交给 `strtod`，结果受 `LC_NUMERIC` 影响：宿主切到 de_DE 等逗号小数点的 locale 后，`"-2.25"` 只能解析出前半段，会被拒绝。现在先按 C 语法 `[+-]digits[.digits][e[+-]digits]` 校验，再把 `.` 换成当前 locale 的小数点后交给 strtod。这样 `"1.5"` 在任何 locale 下结果都一样，`"1,5"` 一律拒绝；多字节小数点的 locale 下，字符串值直接判失败。测试 `string_values_parse_independently_of_the_locale` 在 de_DE.UTF-8 下运行，修复前为红；本机装有 de_DE，没有装逗号 locale 的机器只能覆盖 C locale。4/4，ASan 4/4。

## 3. 设计-only / 未实现

- **LuaJIT**：Stage 3.5 延期项，本计划不交付（gating 条件见 roadmap）。
- LuaJIT 评估结论（已评估，不采纳）：见 [`luajit_evaluation.md`](luajit_evaluation.md)。
- **engine/demo 集成**：未做（§2.9 提供了施加到 World 的 helper，但 demo 未接入）。
- **CLOSED/TIMEOUT 语义**：枚举保留，无 API 映射。

## 4. 验证证据索引

- focused ctest：`test_break_lua_runtime`（9，含 §2.7 内存预算）+ `test_break_lua_module`（19）+ `test_break_lua_value`（27）+ `test_break_lua_binding`（22）+ `test_break_lua_target_contract` + 兼容层 `test_script_lua`，在 Task 5 closeout 干净树 `build-sdd-l5`（normal）、`build-sdd-l5-asan`（ASan+UBSan，零报告；per-task lane 曾抓到并已修复 batch double-destroy 的一例真实 UAF——registry 按值查询必须先于任何解引用）、`build-sdd-l5-tsan`（TSan，四个 break_lua 二进制各连跑 10 次零报告）三树各自 6/6 全绿；`ENGINE_BUILD_TESTS=OFF` 树（`build-sdd-l5-notests`）独立构建 `break_lua` 且 nm 验证 0 个 test-hook 导出符号（仅 26 个 `break_lua_*` production 导出）。
- 全量套件（`ctest -LE 'graphics|fuzz'`，`build-sdd-l5`）：共 180 项，179 通过 + 1 项 platform-skip（`test_d3d12_dependency_gate`，Windows-only 门）、0 失败；兼容层 `engine/src/script/script_lua.c/.h` 与 `engine/tests/test_script_lua.c` 在 `master..HEAD` 全分支逐字节未动（diff 0 行）。
- 任务报告：`.superpowers/sdd/2026-10-23-lua-runtime/task-{1,2,3,4,5}-report.md`。
