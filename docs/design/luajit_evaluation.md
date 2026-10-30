# LuaJIT 评估（Workstream D，2026-10-30）

> 状态：**已评估，不采纳**（结论与阻塞原因见 §8）。本文是证据文档，不是实现计划。LuaJIT 源码与构建物只存在于 `/tmp/luajit-eval`，没有进入仓库；`engine/src/script/break_lua*.c` 与 `engine/CMakeLists.txt` 未改动。文中数字全部来自本机实际运行的命令输出；没有测到的内容列在 §9。

## 1. 范围与方法

问题：`break_lua`（`engine/src/script/break_lua*.c`，基线是 `engine/external/lua` 中 vendored 的 Lua 5.4.7）能否在不改合同的前提下提供 LuaJIT 作为可选后端（`BREAK_LUA_BACKEND=luajit`）。

- D1：取源码、构建、探测 C API 与语言差异（§3）。
- D2：用一层 5.4→5.1 shim 把现有 `test_break_lua_*` 合同测试编译到 LuaJIT 上，统计 passed/total 并按原因分类（§4）。
- D3：基准与内存（§5、§6）。
- D4：按 gate 给结论（§7、§8）。

## 2. 环境与 LuaJIT 版本

| 项 | 值 |
| --- | --- |
| 主机 | `Linux fedora 7.2.8-200.fc44.x86_64 #1 SMP PREEMPT_DYNAMIC Fri Sep 25 21:05:44 UTC 2026 x86_64 GNU/Linux`（`uname -a`） |
| 编译器 | `gcc (GCC) 16.2.1 20260819 (Red Hat 16.2.1-2)` |
| CPU | Intel Xeon W-11955M @ 2.60GHz，16 逻辑核（`lscpu`）；基准期间 `/proc/loadavg` 约 1.6，不是空闲机器 |
| 来源 | `git clone https://luajit.org/git/luajit.git /tmp/luajit-eval`（默认分支 `v2.1`；GitHub 镜像没有用到） |
| commit | `8ca762976ebc85ad9bde3e15f147a7e326e0dd01`（2026-10-29，`DynASM/ARM64: Prevent sanitizer warning in dasm_encode().`） |
| 版本 | `LuaJIT 2.1.1793275035`，`_VERSION` 为 `Lua 5.1` |
| 许可证 | MIT（`COPYRIGHT`：Copyright (C) 2005-2026 Mike Pall）；内含的 Lua 5.1/5.2 代码同为 MIT，dlmalloc 为公有领域 |
| 构建 | `make -j8 XCFLAGS=-DLUAJIT_ENABLE_LUA52COMPAT`，wall 4.787 s（user 28.131 s） |
| GC64 | 开（`require("ffi").abi("gc64")` 输出 `true`） |
| `jit.status()` | `true SSE3 SSE4.1 BMI2 fold cse dce fwd dse narrow loop abc sink fuse`；`jit.version/os/arch` = `LuaJIT 2.1.1793275035 Linux x64` |

计划中的 `git clone --depth 1` 在 luajit.org 上失败（`致命错误：哑 HTTP 传输不支持浅克隆能力`），改为完整克隆，耗时 29.083 s。以下所有探测都在这个 `-DLUAJIT_ENABLE_LUA52COMPAT` 构建上运行；没有对比不带该宏的构建，所以不把任何差异归因于该宏。

## 3. D1：API 与语言探测（逐字输出）

探测程序 `/tmp/luajit-eval/api_probe.c`、`hook_probe.c`（不入库），编译与运行：

```
gcc -O1 -I src api_probe.c src/libluajit.a -lm -ldl -Wl,-E -o api_probe && ./api_probe
gcc -O1 -I src hook_probe.c src/libluajit.a -lm -ldl -Wl,-E -o hook_probe && ./hook_probe
```

`api_probe` 输出（每项一行，未做任何改写；`MISSING (no symbol …)` 表示 `dlsym(RTLD_DEFAULT, …)` 找不到符号，`-Wl,-E` 保证静态库符号可见）：

```
lua_newstate(custom allocator)                       OK: allocator used (1554 calls, 88595 bytes live, 90455 peak)
allocator accounting after lua_close                 live bytes after lua_close = 0
budget allocator returns NULL -> error (no abort)    rc=1 (LUA_ERRMEM=4) msg=not enough memory live=2096631
[jit.off] lua_sethook(MASKCOUNT) aborts `while true do end` rc=1 msg=instruction budget exceeded
MASKCOUNT granularity inside JIT-able numeric for    hook fired 0 times for numeric loop of 1e7 iterations (count=1000, jit on)
luaL_loadbufferx (mode arg)                          OK
lua_absindex                                         MISSING (no symbol in libluajit)
lua_pushglobaltable                                  MISSING (macro absent); LUA_GLOBALSINDEX pseudo-index gives type=table
lua_rotate                                           MISSING (no symbol in libluajit)
lua_pcallk                                           MISSING (no symbol in libluajit)
integer subtype / `//` operator                      chunk rejected: [string "return 2^53+1, math.type, 9007199254740993, 1//1"]:1: unexpected symbol near '/'
number model: 2^53+1 round trip                      2^53+1 = 9007199254740992, lua_isinteger absent
lua_Integer size/round trip                          pushinteger(2^53+1) -> tointeger = 9007199254740992
lua_Integer typedef                                  sizeof(lua_Integer)=8 sizeof(lua_Number)=8 LUA_INTEGER_FMT-like: ptrdiff_t
math.type                                            math.type is nil
string.format('%d', 2^31)                            rc=0 '2147483648'
string.format('%d', 1.5)                             rc=0 '1'
float/int tostring                                   tostring(3.0)=3 tostring(3)=3 10/2=5
bitwise operator `5 & 3`                             rc=0 msg=ok
bitwise operator `5 | 3`                             rc=0 msg=ok
bitwise operator `~5`                                rc=0 msg=ok
bitwise operator `1 << 4`                            rc=0 msg=ok
bit.band(5,3) (LuaJIT bit library)                   rc=0 result=1
goto / labels                                        rc=0 goto ok
utf8 library                                         type(utf8)=nil
string.pack/unpack/packsize                          pack=nil unpack=nil packsize=nil
5.2-5.4 stdlib functions                             move=function pack=function unpack=function global_unpack=function tointeger=nil load=function warn=nil co.close=nil
attribs `<const>` / `<close>`                        rc=1 msg=[string "local t=setmetatable({},{__close=1}) local x ..."]:1: unexpected symbol near '<'
load(chunk, name, mode, env) 4-arg                   rc=0 1
string escapes \u{...} and \z                        rc=0 2
```
同一程序对其余 5.2–5.4 符号的 `dlsym` 结果（逐字）：

```
lua_geti lua_seti lua_isinteger lua_rawlen lua_len lua_compare lua_arith lua_rawgetp lua_rawsetp
lua_stringtonumber lua_closeslot lua_resetthread lua_setwarnf lua_callk lua_yieldk lua_getiuservalue
lua_setiuservalue luaL_tolstring luaL_len luaL_requiref luaL_getsubtable luaL_prepbuffsize
luaL_pushresultsize luaL_buffinitsize luaL_checkversion_ luaL_addgsub lua_newuserdatauv   -> 全部 MISSING
lua_getextraspace                                    MISSING (macro absent)
lua_objlen lua_equal lua_lessthan lua_getfenv lua_setfenv lua_pcall lua_insert lua_replace lua_remove -> PRESENT
jit library                                          rc=0 LuaJIT 2.1.1793275035 jit.status()=true
lua_gc(LUA_GCCOUNT)                                  LUA_GCCOUNT=51 KiB
```

`hook_probe`（每个用例 fork 一个子进程，3 s `alarm` 作为超时；`lua_sethook(L, f, LUA_MASKCOUNT, 100000)`，`f` 调 `luaL_error`）：

```
[jit on ] while true do end                                HANG: hook never fired, killed by 3s alarm
[jit off] while true do end                                rc=1 fired=1 msg=instruction budget exceeded
[jit on ] local i=0 while true do i=i+1 end                HANG: hook never fired, killed by 3s alarm
[jit off] local i=0 while true do i=i+1 end                rc=1 fired=1 msg=instruction budget exceeded
[jit on ] repeat until false                               HANG: hook never fired, killed by 3s alarm
[jit off] repeat until false                               rc=1 fired=1 msg=instruction budget exceeded
[jit on ] for i=1,math.huge do end                         HANG: hook never fired, killed by 3s alarm
[jit off] for i=1,math.huge do end                         rc=1 fired=1 msg=instruction budget exceeded
[jit on ] goto loop                                        HANG: hook never fired, killed by 3s alarm
[jit off] goto loop                                        rc=1 fired=1 msg=instruction budget exceeded
[jit on ] recursion-free f() loop calling a function       HANG: hook never fired, killed by 3s alarm
[jit off] loop calling a function                          rc=1 fired=1 msg=[string "local function f() end while true do f() end"]:1: instruction budget exceeded
[jit on ] while true do end, MASKCOUNT|MASKLINE            rc=1 fired=1 msg=instruction budget exceeded
[jit off] while true do end, MASKCOUNT|MASKLINE            rc=1 fired=1 msg=instruction budget exceeded
[jit on ] while true do end, count=1                       rc=1 fired=1 msg=instruction budget exceeded
[jit off] while true do end, count=1                       rc=1 fired=1 msg=instruction budget exceeded
[jit on ] string.rep-driven busy loop                      HANG: hook never fired, killed by 3s alarm
[jit off] string.rep-driven busy loop                      rc=1 fired=1 msg=instruction budget exceeded
```

解读（只写探测直接支持的部分）：

- 自定义分配器：`lua_newstate(alloc, ud)` 在 x64 + GC64 构建上可用，分配器被调用，`lua_close` 后计数归零；分配器返回 NULL 时得到 `LUA_ERRMEM`（=4），进程不 abort。（`lib_aux.c` 显示：非 GC64 的 64 位构建里 `lua_newstate` 直接返回 NULL 并打印 "Must use luaL_newstate() for 64 bit target"。本机是 GC64，该分支没有实际运行，只是读源码得到的。）
- 指令预算：JIT 开启时，`LUA_MASKCOUNT`（count=100000）钩子**不会**中断循环——9 个 JIT 开用例里 7 个卡死到 alarm；`jit.off()` 后 9 个全部正常中断。JIT 开且仍然中断的两个用例是 `MASKCOUNT|MASKLINE` 与 `count=1`，我没有调查它们为什么能中断。LuaJIT 源码（`lj_record.c:2935–2950`）的注释说明：编译代码默认不检查指令/行钩子，`LUAJIT_ENABLE_CHECKHOOK` 才加检查。这是 LuaJIT 自身行为，不是 shim 问题。
- 缺失的 5.4 API：`lua_rotate`、`lua_pcallk`、`lua_absindex`、`lua_pushglobaltable`、`lua_getextraspace` 全部缺失（`lua_getextraspace` 在 `break_lua` 里用于钩子取回 runtime 指针）。`luaL_loadbufferx` 存在。
- 数值模型：没有整数子类型。`2^53+1` 往返得到 `9007199254740992`；`math.type`/`math.tointeger`/`math.maxinteger` 为 nil；`tostring(3.0)` 是 `3`（5.4 是 `3.0`）；`string.format('%d', 1.5)` 返回 `'1'`（5.4 报错）。
- 位运算：本机这个 v2.1 快照**接受** `& | ~ << >>`（git 历史 `a2ce8114 Backport some v3.0 syntax extensions.`），与计划里"语法错误"的预期不同；但语义是 32 位 `bit` 库语义，不是 5.4 的 64 位整数语义，见 §4 表和 §3.1。`//` 整除与 `<const>`/`<close>` 属性是语法错误。
- `utf8`、`string.pack/unpack/packsize`、`math.tointeger`、`warn`、`coroutine.close` 缺失；`goto`、`load(chunk, name, mode, env)` 可用。

### 3.1 同一表达式在两个后端的结果

`sem3.lua`：5.4 用 vendored `onelua.c` 编译的 `l54run`，LuaJIT 用 `src/luajit`。

| 表达式 | Lua 5.4 | LuaJIT |
| --- | --- | --- |
| `return _VERSION` | `Lua 5.4` | `Lua 5.1` |
| `1 << 40` | `1099511627776` | `256` |
| `1 << 63` | `-9223372036854775808` | `-2147483648` |
| `0x100000000 \| 1` | `4294967297` | `1` |
| `-1 >> 1` | `9223372036854775807` | `2147483647` |
| `5 & 3, 5 \| 3, ~5` | `1 \| 7 \| -6` | `1 \| 7 \| -6` |
| `3.5 & 1` | 运行期错误 | `0` |
| `7 // 2` | `3` | 编译错误 |
| `local x <const> = 1` | `1` | 编译错误 |
| `9007199254740993` | `9007199254740993` | `9.007199254741e+15` |
| `tostring(3.0), tostring(3), 2^31` | `3.0 \| 3 \| 2147483648.0` | `3 \| 3 \| 2147483648` |
| `string.format("%d", 1.5)` | 运行期错误 | `1` |
| `type(utf8), type(string.pack)` | `table \| function` | `nil \| nil` |

也就是说，位运算在 LuaJIT 上"能编译但结果不同"，比直接编译失败更危险：5.4 脚本里 `1 << 40` 会静默得到错误值。

## 4. D2：合同测试兼容性 spike

### 4.1 方法

- 被测对象：`engine/src/script/break_lua_{runtime,module,value,binding}.c`，**一字未改**；测试 `engine/tests/test_break_lua_{runtime,module,value,binding,ecs_apply}.c` 的逐字节副本（`cmp` 确认相同）。唯一替换的是同目录的 `test_framework.h`：换成插桩副本，给每个 `TEST` 单独 `fork`（30 s `alarm` 兜底，避免卡死拖垮整个二进制），并把通过/失败的断言数写入共享内存。
- 编译：`-I/tmp/luajit-eval/spike/inc` 放在最前，里面的 `lua/lua.h`、`lua/lauxlib.h`、`lua/lualib.h` 先 include LuaJIT 的真头文件，再 include shim `/tmp/luajit-eval/lua54_shim.h`（65 行）。命令见 `/tmp/luajit-eval/spike/build_jit.sh`：

```
CF="-std=c11 -O1 -g -w -DBREAK_LUA_TESTING=1 -DENGINE_PLATFORM_LINUX=1 -D_POSIX_C_SOURCE=199309L -I$S/inc -I$R/src"
gcc $CF -c $R/src/script/break_lua_<runtime|module|value|binding>.c
gcc $CF $S/tests_copy/test_break_lua_<t>.c bl_*.o /tmp/luajit-eval/src/libluajit.a -lpthread -lm -ldl
```

- 对照组：同样的插桩测试对 vendored Lua 5.4.7 手工编译（`build_base.sh`，不经 CMake）。
- 确认链接的确是 LuaJIT：`nm jit/test_runtime | grep -c "lj_vm\|luaJIT_setmode"` 为 82，对照组为 0；通过 runtime 自己加载模块读 `_VERSION` 得到 `Lua 5.1`。
- 插桩框架本身不改变结果：用**未插桩**的原始测试源码对同一份 LuaJIT 对象再编译运行，得到 runtime 9/9、module 24/24、value 34/34、binding 32/33，和插桩结果一致。

shim 内容（全部在 `lua54_shim.h`，不入库）：

| 5.4 API | shim 做法 | 已知限制 |
| --- | --- | --- |
| `lua_absindex` | 宏，基于 `lua_gettop` | 无 |
| `lua_pushglobaltable` | `lua_pushvalue(L, LUA_GLOBALSINDEX)` | 无 |
| `lua_pcallk` | 丢掉 ctx/k，转 `lua_pcall` | 无 continuation；`break_lua` 只传 `0, NULL` |
| `lua_rotate` | `lua_insert` / `lua_pushvalue+lua_remove` 循环 | 与 5.4 逐项比对：idx 1..3 × n −3..3 共 21 种，输出完全相同（`rotate_check.c`） |
| `lua_getextraspace` | 返回线程局部槽，每次从 `lua_getallocf` 的 userdata 重新读取 | 仅因为 `break_lua` 始终以 `lua_newstate(break_lua_alloc, runtime)` 建 state 且 `ud == runtime` 才成立；这是对调用方式的依赖，不是通用实现 |
| `lua_setupvalue(f,1)`（设 `_ENV`） | 主 chunk 无 upvalue 时改走 `lua_setfenv` | 5.1 函数环境语义，不是 `_ENV` 变量 |
| `luaL_openlibs` | 打开库后调用 `jit.off()`（环境变量 `LUA54_SHIM_JIT` 置位时跳过） | 见 §4.3：这是让指令预算生效的必要条件 |

### 4.2 结果：passed / total

| 二进制 | Lua 5.4（对照） | LuaJIT，shim 内 `jit.off()` | LuaJIT，JIT 开（stock） | LuaJIT + `LUAJIT_ENABLE_CHECKHOOK`，JIT 开 |
| --- | --- | --- | --- | --- |
| runtime | 9/9 | 9/9 | 9/9 | 9/9 |
| module | 24/24 | 24/24 | 20/24 | 24/24 |
| value | 34/34 | 34/34 | 33/34 | 34/34 |
| binding | 33/33 | 32/33 | 27/33 | 32/33 |
| ecs_apply | 4/4 | 4/4 | 4/4 | 4/4 |
| **测试合计** | **104/104** | **103/104（99.0%）** | **93/104（89.4%）** | **103/104（99.0%）** |
| 通过的断言数 | 1695 | 1685（99.4%），失败 1 | 1603（94.6%），失败 2 | 1685，失败 1 |

断言说明：失败的测试在第一个失败处 `return`，同一测试里后面的断言没有执行（`sandbox_xpcall_argument_errors_match_base_text` 对照组通过 15 条，LuaJIT 上通过 6 条后失败，其余 8 条未执行）。另外两个循环注入分配失败的测试执行的断言条数随后端分配次数而变（runtime +1、value −2），所以"1695"是对照组的通过数，不是严格的共同分母。百分比按"LuaJIT 通过数 / 对照组通过数"计算。

JIT 开（stock）的 11 个失败：9 个测试卡死被 30 s `alarm` 杀掉（`signal=14`），2 个断言失败（见下表）。其中 `sandbox_xpcall_argument_errors_match_base_text` 与 `jit.off` 配置共有。

### 4.3 失败原因表

| 原因 | jit.off | JIT 开（stock） | 说明 |
| --- | --- | --- | --- |
| 指令预算钩子不能中断已编译的 trace | 0 | 9 个测试卡死 + 1 个断言失败 | module 4 个 `staging_budget_trip_*`/`on_unload_budget_trip_*`；binding 5 个 `budget_trip_*`；value `instruction_budget_trip_marks_module_until_reload` 失败：`kChunkSpin` 的 1e8 次循环在 JIT 下直接跑完，没有触发预算（`fe.valid is false`）。与 §3 `hook_probe` 的结论一致 |
| 尾调用内建函数的错误信息文本 | 1 个测试 | 1 个测试 | `sandbox_xpcall_argument_errors_match_base_text`：脚本 `return xpcall()` 是尾调用，LuaJIT 给 `bad argument #2 to '?' (function expected, got no value)`，5.4 给 `arg:2: bad argument #2 to 'xpcall' (function expected, got no value)`。非尾调用写法在 LuaJIT 上与 5.4 一致（`semantics_probe`：`m5:1: bad argument #2 to 'xpcall' …`） |
| 整数子类型 | 0 | 0 | 测试源码里没有 `math.type`/`math.tointeger`（grep 0 命中）；`BreakLuaValue` 的数字是 f64 |
| 测试脚本里的位运算 | 0 | 0 | Lua chunk 字面量里没有 `& \| ~ << >> //` |
| `lua_rotate` 边界语义 | 0 | 0 | 21 种组合与 5.4 一致 |
| `string.format('%d')` 传浮点 | 0 | 0 | 测试里没有 `string.format` 调用 |
| sandbox 白名单差异 | 0 个失败，**1 个空洞通过** | 同左 | binding 的 `present()` 断言 `type(utf8) == 'table'`：LuaJIT 没有 `utf8`，sandbox 给脚本一个"对 nil 的只读代理"空表，所以断言通过，但 `utf8.char` 是 nil（`semantics_probe`：`utf8_table -> "table"`、`utf8_char -> "nil"`）。LuaJIT 的 `ffi`/`jit`/`bit`/`require` 在 sandbox 里均不可达（探测输出 `nil`） |

读这个表要注意盲区：现有合同测试几乎不检查 Lua 语言语义（整数、位运算、`utf8`、`string.pack` 等一处都没用到），所以 99% 说明的是"C API facade 经 shim 能在 LuaJIT 上跑"，不说明"为 5.4 写的脚本能在 LuaJIT 上跑"。后者的差异见 §3.1，没有被任何现有测试覆盖。

补充探测（真实 `break_lua_runtime`，`memory_budget = 512 KiB`，`oom_probe.c`）：Lua 5.4、LuaJIT（`jit.off`）、LuaJIT（JIT 开）三者输出相同：`load_module -> OK`、`call grow -> OOM`、`call ok after OOM -> OK`；OOM 后 `in_use` 分别为 24389 / 44700 / 44700 字节，远低于预算。

## 5. D3：性能

### 5.1 方法

基准源码：`engine/tests/bench_lua_backends.c`（独立文件，**未接入 CMake**）。三个微基准：`fib(32)`、table insert/sum 1e6（`table.insert` 1e6 次再求和）、string concat/format 2e5（`'k'..i` + `string.format('%s=%d')`，最后 `table.concat`）。每次运行新建 `lua_State`（经 `lua_newstate` + 计数分配器），所以 JIT 预热与编译时间包含在计时里；每个基准 5 次，报告中位数与 min–max。`--hook` 开关按 `break_lua` 设置 `instruction_budget` 的方式挂 `lua_sethook(L, f, LUA_MASKCOUNT, INT_MAX)`（回调只在触发时报错，实际从不触发），用来测"钩子挂着"的代价；`--jit off` 在 LuaJIT 上先执行 `jit.off()`。三个基准的返回值在所有后端一致（`2178309`、`500000500000`、`2777789`）。

手工构建命令（与源码头注释一致）：

```
gcc -std=c11 -O2 -w -DMAKE_LIB -I engine/external -c engine/external/lua/onelua.c -o lua54.o
gcc -std=c11 -O2 -I engine/external engine/tests/bench_lua_backends.c lua54.o -lm -o bench_lua54
gcc -std=c11 -O2 -DBREAK_BENCH_LUAJIT -I /tmp/luajit-eval/src engine/tests/bench_lua_backends.c \
    /tmp/luajit-eval/src/libluajit.a -lm -ldl -o bench_luajit
./bench_lua54 --runs 5 [--hook]
./bench_luajit --runs 5 --jit off [--hook]
./bench_luajit --runs 5 --jit on  [--hook]
```

`bench_luajit_checkhook` 是同一源码链接另一份用 `XCFLAGS="-DLUAJIT_ENABLE_LUA52COMPAT -DLUAJIT_ENABLE_CHECKHOOK"` 构建的 LuaJIT（`/tmp/luajit-eval/ch`），见 §6.2。

CMake 接入草图（**未添加，`engine/CMakeLists.txt` 未改动，没有经 CMake 试过**）：

```cmake
add_executable(bench_lua_backends EXCLUDE_FROM_ALL tests/bench_lua_backends.c)
target_link_libraries(bench_lua_backends PRIVATE lua)   # lua 的 PUBLIC include 已含 external/
if(BREAK_LUAJIT_EVAL_DIR)
    add_executable(bench_lua_backends_luajit EXCLUDE_FROM_ALL tests/bench_lua_backends.c)
    target_compile_definitions(bench_lua_backends_luajit PRIVATE BREAK_BENCH_LUAJIT=1)
    target_include_directories(bench_lua_backends_luajit PRIVATE ${BREAK_LUAJIT_EVAL_DIR}/src)
    target_link_libraries(bench_lua_backends_luajit PRIVATE
        ${BREAK_LUAJIT_EVAL_DIR}/src/libluajit.a m ${CMAKE_DL_LIBS})
endif()
```

### 5.2 结果（单位 ms，中位数（min–max），5 次）

主机负载：开始前 `/proc/loadavg` = `1.56 1.76 1.45`，结束后 `1.63 1.77 1.46`（16 核机器上有后台活动，不是静默环境）。

钩子未挂（`hook=off`）：

| 基准 | Lua 5.4 | LuaJIT 解释器（`jit.off()`） | LuaJIT JIT |
| --- | --- | --- | --- |
| fib(32) | 103.66（102.96–107.56） | 74.42（74.16–75.35） | 12.67（11.86–13.60） |
| table insert/sum 1e6 | 36.06（32.92–38.77） | 53.39（53.28–57.06） | 2.89（2.80–5.16） |
| string concat/format 2e5 | 91.00（88.99–108.79） | 55.93（54.87–67.92） | 20.61（20.01–24.75） |

钩子已挂（`hook=on`，`LUA_MASKCOUNT`，count=`INT_MAX`）：

| 基准 | Lua 5.4 | LuaJIT 解释器 | LuaJIT JIT（stock 构建） | LuaJIT JIT + `LUAJIT_ENABLE_CHECKHOOK` |
| --- | --- | --- | --- | --- |
| fib(32) | 219.37（217.61–223.66） | 93.91（92.93–94.76） | 12.64（12.05–13.74） | 595.30（583.66–598.84） |
| table insert/sum 1e6 | 53.74（51.34–55.10） | 60.43（59.41–64.22） | 2.81（2.74–5.33） | 269.50（268.41–272.46） |
| string concat/format 2e5 | 104.18（96.97–111.10） | 60.23（54.26–69.17） | 22.36（21.82–23.81） | 87.55（82.37–91.84） |

CHECKHOOK 构建在钩子未挂时（JIT 开）：fib 13.66、table 3.00、string 20.74 ms，比 stock 慢 7.8% / 3.8% / 0.6%。

相对 Lua 5.4 的倍数（Lua 5.4 中位数 ÷ 对方中位数，由上表算出，大于 1 表示更快）：

| 基准 | 解释器，无钩子 | JIT，无钩子 | 解释器，有钩子 | stock JIT，有钩子 | CHECKHOOK JIT，有钩子 |
| --- | --- | --- | --- | --- | --- |
| fib(32) | 1.39× | 8.18× | 2.34× | 17.36× | 0.37× |
| table | 0.68× | 12.48× | 0.89× | 19.12× | 0.20× |
| string | 1.63× | 4.42× | 1.73× | 4.66× | 1.19× |

说明与注意：

- table 基准 JIT 档的 spread 很大（min 2.80 / max 5.16）是因为前两次运行慢（5.16、4.65 ms，之后 2.88、2.89、2.80 ms），属于 JIT 预热；其余档位 spread 在 1.5%–25%（hook=off 的 string 档：Lua 5.4 为 21.8%，LuaJIT 解释器为 23.3%），说明机器有噪声，小于 10% 的差异不应当作结论。更早的一轮完整 5 次测量（同一 `.c`，尚无 `--hook` 开关，`/tmp/luajit-eval/bench/bench_all.out`）的 hook=off 中位数与此表相差 ≤ 7.1%。
- 在 stock JIT 下"挂钩子"没有任何代价（12.64 vs 12.67 ms），原因正是 §3 所示：编译后的代码根本不看钩子。这个数字**不能**解读为"预算无开销"，因为此时预算不生效。
- CHECKHOOK + 钩子挂着时，LuaJIT 比它自己的解释器还慢（fib 595 ms vs 94 ms，table 270 ms vs 60 ms）。原因没有深入调查，只确认了现象。
- 5.4 解释器挂钩子本身就有成本：fib 219.37 vs 103.66 ms（2.12×）。
- 计时只覆盖 `luaL_loadstring + lua_pcall`，不含 `lua_newstate/luaL_openlibs`；工作负载是纯 Lua 计算，不含 `break.*` 绑定、ECS batch 或 C 函数调用，**不代表**引擎里脚本的实际形态。

## 6. D3：内存

### 6.1 分配器可见的峰值（`alloc_peak_bytes`，bench 内计数分配器，每次运行取 5 次中最大）

| 基准 | Lua 5.4 | LuaJIT 解释器 | LuaJIT JIT |
| --- | --- | --- | --- |
| fib(32) | 23081 | 39502 | 56765 |
| table insert/sum 1e6 | 16798013 | 8426648 | 8429411 |
| string concat/format 2e5 | 24489179 | 22834045 | 19163885 |

（挂钩子与否对这一列无实质影响，完整输出在 `/tmp/luajit-eval/bench/bench_final.out`。）LuaJIT 的 table 峰值约为 5.4 的一半，这是 5.4 的 TValue 带类型标签、数组部分更大所致的推测，没有单独验证。

### 6.2 `memory_budget` 与指令预算在 LuaJIT 上是否成立

- 分配器预算：`lua_newstate` 自定义分配器返回 NULL 后，三种负载（table 增长、`string.rep` 增长、一次性 64 MiB `string.rep`）全部得到 `lua_pcall` 状态 4（`LUA_ERRMEM`）、消息 `not enough memory`，进程不 abort（`oomstatus.c`）。经真实 `break_lua_runtime`（512 KiB 预算）：`call grow -> OOM`，随后 `call ok after OOM -> OK`，`jit.off` 与 JIT 开结果相同。**成立。**
- JIT 机器码在分配器之外：`lj_mcode.c:137` 用 `mmap` 直接申请机器码区，不经 `lua_Alloc`，所以 `memory_in_use` 看不到。实测（`mcode_probe`，3000 个不同热循环）：

```
jit off: rc=0 allocator_live=85 KiB allocator_peak=87 KiB RSS_growth=136 KiB (untracked ~ 51 KiB)
jit on : rc=0 allocator_live=75 KiB allocator_peak=118 KiB RSS_growth=724 KiB (untracked ~ 649 KiB)
jit on : rc=0 allocator_live=57 KiB allocator_peak=118 KiB RSS_growth=728 KiB (untracked ~ 671 KiB)
```

  即该负载下约 0.6 MiB 的增长不在 `memory_in_use` 里。上限由 `maxmcode` 决定，默认 2048 KB（`lj_jit.h:128`、`doc/running.html`），可用 `jit.opt.start("maxmcode=…")` 调整；我没有跑到上限，所以"每个 runtime 最多 2 MiB 脱离预算"是按文档推算，不是实测。`jit.off()` 时没有这部分（untracked 51 KiB 在噪声范围）。
- 指令预算：stock JIT 下**不成立**（§3 的 JIT 开用例 7/9 卡死；§4 的 9 个卡死测试）。三个可行方式：
  1. `jit.off()`（`luaJIT_setmode(L, 0, LUAJIT_MODE_ENGINE|LUAJIT_MODE_OFF)` 同样有效：`setmode_probe` 输出 `returned 1; loop rc=1 msg=instruction budget exceeded`）——预算成立，但失去 JIT。
  2. 构建 LuaJIT 时加 `-DLUAJIT_ENABLE_CHECKHOOK`（`lj_record.c:2949` 的编译期选项）。`hook_probe_ch` 18 个用例全部 `rc=1 fired=1`，合同测试 103/104，与 `jit.off` 相同；代价见 §5.2（挂钩子时比解释器还慢）。
  3. 不挂钩子、用别的看门狗——超出现有合同，没有评估。
- 构建体积：`size` 的 text+data+bss 合计，`libluajit.a` 558776 字节、Lua 5.4 的 `lua54.o` 264071 字节（两者包含的模块不完全相同，仅作量级参考）。

## 7. D4：按计划 gate 逐项核对

计划里的 gate：断言通过率 ≥ 95%、shim 有文档、内存预算与指令预算可用，才允许走"可选后端"路线。LuaJIT 有三种可运行配置，结果不同，所以按配置分别核对（数字均来自 §4–§6）：

| 条件 | A：stock，JIT 开 | B：`LUAJIT_ENABLE_CHECKHOOK`，JIT 开 | C：stock，`jit.off()`（仅解释器） |
| --- | --- | --- | --- |
| 断言通过率 ≥ 95% | **不满足**：1603/1695 = 94.6%；测试 93/104 | 满足：1685/1695 = 99.4%；测试 103/104 | 满足：1685/1695 = 99.4%；测试 103/104 |
| shim 有文档 | 是（§4.1、§10） | 是 | 是 |
| 分配器内存预算 | 成立 | 成立 | 成立 |
| JIT 机器码计入预算 | **不计入**（`mmap`，实测约 0.6 MiB 在 `memory_in_use` 之外；上限 `maxmcode` 默认 2048 KB，未跑到上限） | 同左 | 无此项 |
| 指令预算 | **不成立**：9 个测试卡死，hook 探测 9 个 JIT 开用例里 7 个卡死 | 成立（18 个探测用例全部中断） | 成立 |
| 钩子挂着时相对 Lua 5.4（fib / table / string） | 17.36× / 19.12× / 4.66×（但预算没有生效，数字无意义） | 0.37× / 0.20× / 1.19× | 2.34× / 0.89× / 1.73× |

另外三条不在计划 gate 里、但影响结论的事实：

- 剩余的那个失败不是 shim 问题：`return xpcall()` 这类尾调用内建函数，LuaJIT 的参数错误信息是 `bad argument #2 to '?' …`，没有位置前缀和函数名；`break_lua` 的合同按文本逐字钉住了 5.4 的信息。
- 现有合同测试没有覆盖语言语义（§4.3 末尾）。§3.1 的差异（32 位位运算、无整数子类型、`//` 与 `<const>` 编译失败、无 `utf8`/`string.pack`）测试一个也发现不了，其中 `1 << 40` 之类会静默给出不同结果。
- `break_lua.h` 与 `docs/design/lua_runtime.md` 把脚本语言写成 Lua 5.4，sandbox 白名单显式暴露 `utf8`（`break_lua_binding.c:693`）。换成 LuaJIT 等于换了一种脚本方言，而不是换了一个更快的同一种语言。

## 8. 决策

**不采纳（evaluated, not adopted）。** 不在 `break_lua` 里加 `BREAK_LUA_BACKEND=luajit`，也不新增依赖。

按 gate 的字面条件，配置 B、C 在数字上过线（99.4%），所以这不是"测试没过"。不采纳的原因是：过线的两种配置都放弃了采用 LuaJIT 的理由，而保留理由的配置过不了线。

1. **想要的性能与必须的安全合同不能同时拿到。** 加速来自 JIT（hook=off：8.18× / 12.48× / 4.42×），但 stock JIT 下 `instruction_budget` 失效——`while true do end` 在宿主线程上永久卡死，`break_lua.h` 把"脚本不能挂住宿主线程"当作合同。要让预算成立只有两条路：关 JIT（配置 C）或自编带 `LUAJIT_ENABLE_CHECKHOOK` 的 LuaJIT（配置 B）。
   - 配置 C 的收益有限且不均匀：解释器相对 5.4 为 1.39× / 0.68× / 1.63×（hook=off），table 基准比 5.4 慢；iOS 禁止 JIT，那里本来就只能是这个配置。
   - 配置 B 在预算生效（钩子挂着）时，fib 与 table 比 5.4 慢到 0.37× / 0.20×，并且要求项目自己维护一份带编译选项的 LuaJIT 构建。
2. **语言不兼容且无法兜底。** LuaJIT 是 Lua 5.1 语义：没有整数子类型（`2^53+1` 往返丢精度）、位运算是 32 位（`1 << 40` 得 `256`）、`//` 与 `<const>` 是语法错误、没有 `utf8`/`string.pack`（sandbox 里 `utf8` 变成指向 nil 的空代理）。shim 只能补 C API，补不了语言；现有合同测试对此是盲的，所以 99.4% 不能被当作"脚本可移植"的证据。
3. **JIT 机器码绕过 `memory_budget`**（配置 A、B）。不是阻塞原因，但意味着预算语义要改写成"分配器字节 + 至多 `maxmcode`"。
4. **构建与维护面。** 克隆里没有 release tag（`git describe` 报"没有发现名称"，版本串是时间戳 `2.1.1793275035`），采用要自行钉 commit；shim 的 `lua_getextraspace` 依赖"分配器 userdata == runtime"这一调用约定。

若要重新评估，需要先发生的变化（按依赖顺序）：

- 产品层面决定脚本方言：要么把合同改成"Lua 5.1/LuaJIT 子集"，要么放弃 LuaJIT。这是产品决定，不是实现细节。
- 增加覆盖语言语义的合同测试（整数/位运算/`utf8`/错误信息文本），让"通过率"真正衡量脚本兼容性。
- 决定指令预算的实现路径（CHECKHOOK 构建或 `jit.off`），并在目标平台（含 ARM64、Windows）重新测性能。
- 决定 JIT 机器码如何计入 `memory_budget`（或把 `maxmcode` 设成预算的一部分）。

台账建议：按计划 D4 (b)，将该项关闭为"evaluated, not adopted"，证据路径为本文；路线图 Stage 3 子项目 5 同步更新。这两处台账/Implementation_Status 的改动不在本次允许修改的文件范围内，由调用方处理。

## 9. 没有测到的内容与局限

- 单机单平台：x86-64 Linux、gcc 16.2.1、GC64。没有 ARM64、Windows、macOS、iOS（iOS 禁止 JIT，只能解释器模式，这是平台规则，未实测）、没有 32 位或非 GC64 构建。
- LuaJIT 只测了 `-DLUAJIT_ENABLE_LUA52COMPAT`（以及另一份再加 `-DLUAJIT_ENABLE_CHECKHOOK`）；没有对比不带 `LUA52COMPAT` 的构建。
- 基准是三个纯 Lua 微基准，没有 `break.*` 绑定、ECS batch、C 函数往返、GC 压力、热重载。机器有后台负载（loadavg ≈ 1.6），小于 10% 的差异不可靠；每项只有 5 次。
- 断言总数是"对照组通过数 1695"，不是严格的共同分母（§4.2 说明）。
- 合同测试里有的测试（TSan、ASan、多线程）只在 Lua 5.4 上跑过；LuaJIT spike 没有跑 sanitizer。
- 没有测 coroutine 相关行为（sandbox 里本来就去掉了 `coroutine`）；LuaJIT 的钩子计数器是全局的（读 `lj_dispatch.c:340` 得知），与 5.4 的"每协程"语义不同，没有构造测试验证它对合同的影响。
- JIT 机器码上限只按文档/源码推算，没有跑到 `maxmcode` 上限。
- 所有探测程序、shim、插桩框架、spike 构建产物在 `/tmp/luajit-eval`，不入库、不保证长期存在；可复现所需的 shim 已附在 §10，探测输出已逐字记录在 §3–§6。仓库内唯一新增代码是 `engine/tests/bench_lua_backends.c`。

## 10. 附：shim 全文（`/tmp/luajit-eval/lua54_shim.h`，仅评估用，不入库）

```c
#ifndef LUA54_SHIM_H
#define LUA54_SHIM_H
#include <stdlib.h>

#define lua_absindex(L, i) \
    (((i) > 0 || (i) <= LUA_REGISTRYINDEX) ? (i) : lua_gettop(L) + (i) + 1)
#define lua_pushglobaltable(L) lua_pushvalue(L, LUA_GLOBALSINDEX)
#define lua_pcallk(L, na, nr, eh, ctx, k) ((void)(ctx), (void)(k), lua_pcall(L, (na), (nr), (eh)))

static inline void lua54_shim_rotate(lua_State *L, int idx, int n)
{
    idx = lua_absindex(L, idx);
    for (; n > 0; n--) {
        lua_insert(L, idx);
    }
    for (; n < 0; n++) {
        lua_pushvalue(L, idx);
        lua_remove(L, idx);
    }
}
#define lua_rotate(L, idx, n) lua54_shim_rotate((L), (idx), (n))

static inline void *lua54_shim_extraspace(lua_State *L)
{
    static _Thread_local void *slot;
    (void)lua_getallocf(L, &slot);
    return &slot;
}
#define lua_getextraspace(L) lua54_shim_extraspace(L)

static inline const char *lua54_shim_setupvalue(lua_State *L, int funcindex, int n)
{
    funcindex = lua_absindex(L, funcindex);
    if (n == 1 && (lua_getupvalue)(L, funcindex, 1) == NULL) {
        if (lua_iscfunction(L, funcindex)) {
            return NULL;
        }
        return lua_setfenv(L, funcindex) ? "_ENV" : NULL;
    }
    if (n == 1) {
        lua_pop(L, 1);
    }
    return (lua_setupvalue)(L, funcindex, n);
}
#define lua_setupvalue(L, f, n) lua54_shim_setupvalue((L), (f), (n))
#endif
```

`luaL_openlibs` 的包装（`inc/lua/lualib.h`）：先调真正的 `luaL_openlibs`，除非设置了环境变量 `LUA54_SHIM_JIT`，否则立即执行 `jit.off()`。

