# Lua 调试、受限表值与 Actor 脚本适配设计

日期：2026-11-02

## 1. 目标与边界

本子项目实现总设计 P9：默认关闭的断点与单步、真实调用栈和局部变量检查、与指令预算共存的调试 hook、有递归/节点/字符串上限的表值、带 generation 的稳定 host 句柄，以及 Actor 类 `lua_module` 到 `on_actor_tick` 的真实接线。

不实现远程调试协议、socket 监听、网络命令面或阻塞式调试会话。宿主若未来增加远程调试，必须在独立应用中显式启用并完成授权；本设计不新增任何入口。`break_lua`、`break_game`、`engine`、`engine_demo`、`dxx_break` 不因调试器或 Actor 适配器而相互耦合。

## 2. 方案取舍

### 采用：同步暂停回调 + 私有执行 hook 组合层

独立 `break_lua_debug` 库注册运行时内部的执行观察者。暂停发生在 Lua line hook 内，宿主回调同步读取仍然存活的帧与局部变量，并返回继续或下一步动作。VM 不带状态返回宿主事件循环，因此不存在“恢复一份已退栈上下文”的假象，也不需要跨线程控制 `lua_State`。

`break_lua` 内部组合预算 count hook 与调试 line hook。预算布防/撤防统一经过组合层，二者不会互相覆盖；count trip 仍抛宿主私有 sentinel，脚本不可捕获。

### 不采用：公开 `lua_State` 或脚本 `debug` 库

直接暴露 `lua_State` 会破坏稳定 ABI、owner 线程和 pcall 边界；把 Lua `debug`/`package` 加入白名单会让沙箱模块绕过预算、读取其他模块或加载未审查代码。调试库仅包含项目私有头并使用 C API，公开消费者只接触 opaque runtime/debugger 和有界 POD。

### 不采用：阻塞轮询或本轮实现远程调试

在 hook 内自旋等待另一线程既违反单 owner 线程约束，也会与 TSan/预算语义冲突。同步回调足以覆盖确定性断点、步进和检查，且不扩大攻击面。

## 3. 调试器合同

### 3.1 生命周期与默认状态

- `break_lua_debug_create(runtime, config)` 创建一个 runtime 至多一个的调试器；runtime 与 debugger 均为单 owner 线程对象，debugger 必须先于 runtime 销毁。
- 创建后 `enabled == false`。可以预设有界断点，但禁用时不安装 line hook、不产生暂停，也不改变既有执行结果。
- `break_lua_debug_set_enabled` 显式启停。断点表容量固定为 32；断点 id 单调分配，清除未知 id 返回 `STALE`，容量满返回 `OVERLOAD`。
- `STEP_INTO` 在下一条 Lua 行事件暂停；`STEP_OVER` 只在不超过请求时调用深度的行事件暂停；`STEP_OUT` 只在更浅调用深度暂停。继续执行会清除一次性步进请求，已启用断点继续有效。

### 3.2 暂停与检查

暂停回调收到原因（断点/步进）、模块名和行号。只有回调执行期间检查 API 有效；其他时刻返回 `REJECTED`，避免保存 Lua 内部帧指针。

- 调用栈按当前帧到最外帧排列，每项含有界模块名、函数名、当前行和定义行。最多捕获 32 帧；更深或调用方输出容量不足显式返回 `OVERLOAD`，不静默截断。
- 局部变量通过 `lua_getlocal` 在暂停现场读取。名字最多 63 字节；字符串值最多 127 字节；超出显式返回 `OVERLOAD`。nil/bool/number/string 保留值，其他 Lua 类型以 `OTHER` 和有界类型名报告，不伪装成 nil。
- 回调返回 `CONTINUE`、`STEP_INTO`、`STEP_OVER` 或 `STEP_OUT`。检查过程不调用 runtime 重入 API，不分配内存，不修改脚本变量。

### 3.3 与预算协作及沙箱

统一 hook 分派 count 事件给既有预算回调、line 事件给调试观察者。预算在模块加载/reload、`on_unload`、frame hook、直接 call/call_ref 中都按单次受保护执行记账；调试启停不改变预算计数，也不会清除 budget trip。直接 call/call_ref 因而不再是无预算逃逸口。

调试器只存在于宿主 C 侧。启用前后模块中的 `debug`、`package`、`require`、`coroutine`、`load` 均保持缺席；既有白名单和只读 proxy 不增加字段。

## 4. 受限表值与稳定 host 句柄

### 4.1 表构建与调用

新增不透明 `BreakLuaTable`，创建时指定并预分配节点容量（硬上限 256）、最大递归深度（硬上限 16）和最大字符串 payload（硬上限 127）。根节点在建表时存在。构建器只允许新增子节点，不允许回指，因此宿主构造的图天然无环；每个节点记录深度，超深、节点满、字符串超界分别返回 `OVERLOAD`，不截断。

表键支持有界字符串和整数；值支持 nil、bool、number、string、子表和 host 句柄。`break_lua_runtime_call_table` 以一个表为参数并以一个表接收返回值：

- Lua → host 遍历设有总节点与深度预算；共享表按新节点展开，环由深度上限有界拒绝。
- 不支持的 key/value 类型返回 `FAILED`；超长字符串、节点或深度超限返回 `OVERLOAD`。
- 输出先写入创建时预分配的 scratch 节点区，完整成功后一次提交；失败保持原输出表不变。
- 调用仍使用既有模块 raw-field 查找、owner 检查、pcall 和指令预算。Lua 栈在所有出口恢复。

### 4.2 host 句柄

`BreakLuaHostHandle` 为 `{slot, generation}`，不含 C 指针。每个 runtime 有 64 个固定句柄槽；acquire 关联一个宿主定义的 `u64 token`（禁止把地址作为 token），resolve 验证槽、占用和 generation，release 使旧 generation 立即失效。越界、已释放或槽复用前的句柄均返回 `STALE`，双重释放也是 `STALE`。

句柄压入 Lua 时使用只含两个整数的 full userdata 和锁定 metatable，绝不压入宿主地址。模块无法构造或修改该 userdata；marshal 回 host 时重新执行 registry 校验，不能靠伪造字节绕过 stale 检查。现有标量 `BreakLuaValue` 增加 `HOST_HANDLE` 类型，Actor 与表绑定共用同一身份机制。

## 5. Actor 适配边界

新增独立可选库 `break_game_lua`，链接 `break_game` 与 `break_lua`；两者本身不互链。`break_game` 只增加一个不依赖 Lua 的通用脚本桥回调，实际适配由 `BreakGameLuaAdapter` 完成。

- 创建 adapter 时登记脚本桥；`break_game_tick` 对每个存活 Actor，在其类配置了非空 `lua_module` 时调用 adapter。已有原生 class tick 保持原行为。
- adapter 首次见到 Actor 时 acquire 一个稳定句柄，token 编码 Entity index/generation；同一 Actor 后续 tick 复用。despawn 桥回调 release 句柄，防止代际复用继承身份。
- 每次 Actor tick 经 `break_lua_runtime_call(module, "on_actor_tick", {handle, dt})`。普通脚本错误、预算跳闸、缺失模块/函数和句柄容量失败只记录该 Actor 的有界诊断，循环继续服务其他 Actor；不会中止 `break_game_tick`，也不会回滚其他 Actor 已完成的脚本状态。
- adapter 保存最近错误和累计失败数，测试可读取诊断而不依赖 stdout。adapter 必须先于 game/runtime 销毁，销毁时注销自己的桥并释放全部句柄。

## 6. 错误与线程

沿用 `BreakLuaError`/`BreakGameError`：畸形输入 `INVALID`，失效句柄或断点 `STALE`，容量/深度/字符串上限 `OVERLOAD`，owner 违规 `REJECTED`，Lua 普通错误或不支持类型 `FAILED`，Lua 分配失败 `OOM`。调试检查和 Actor 脚本均在 GameThread/owner 上同步运行；不引入 mutex、后台线程或热路径分配。

## 7. 验证与变异

严格先写目标行为测试并看到 RED，再实现 GREEN。focused 范围包括全部 `break_lua` 测试、新调试/表/Actor 适配测试、既有 `break_game` 与 `cry_style` 回归，以及 target contract；构建并行度固定 `-j3`。

必须分别变异并确认测试变红后恢复：断点命中、三种步进深度、调用栈内容、局部变量值、表深度、表节点数、表字符串长度、stale generation、Actor 单脚本失败隔离，以及预算与调试 hook 共存。normal、ASan+UBSan、TSan 三棵独立构建树运行 focused CTest；TSan 下不新增跨线程 VM 使用。生产 no-tests 树确认可选库可独立构建且核心应用没有新增链接。

本机测试不证明 Windows、真机编辑器或远程调试授权流程；本轮没有远程调试实现，因此也不声称其已验证。
