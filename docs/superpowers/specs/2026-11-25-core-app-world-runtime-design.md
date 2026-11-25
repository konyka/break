# core_app World 控制面生产接线设计（2026-11-25）

## 目标与边界

在 `--world-replication` 下，core_app 实际创建并注册
`BreakRuntimeWorldSession`，让 open/close 和本地 ACK/NEED_FULL 经过
Runtime queue + owner drain。复用 transport 的 BreakWorldSession 与 core_app
net_bus，adapter 在 Coordinator 子系统顺序中先于 `"network"`。

不包含 snapshot/lease handoff、Runtime BRWD/BRFG 数据面、新 wire 消息、
自动后续换级、共享 live World、权威 simulation 合并或默认全局公平调度。

## 方案比较

1. **复用现有 adapter + Coordinator（采用）**。只增加 core_app 组合和初始化/
   回滚所有权，不另造控制协议。
2. 在 transport 内直接调用 World Session。会绕过 Runtime queue 和六阶段
   生命周期，不能关闭常驻 consumer 缺口。
3. 先接 snapshot/BRWD 数据面。还缺引用所有权、聚合字节预算和 completion
   correlation，规模更大，不应混入本项。
4. 权威合并。缺少权限、稳定身份、确定性排序与冲突策略，另立项目。

## 首 tick 初始化与 adapter 注册

`net_world_initialize_level` 不再 destroy/recreate session。首次实际 level
大于当前值时调用 `break_world_session_rebaseline`，随后设置
`world_level_initialized=true`；当前 level 已为 0 时直接初始化。尚无连接可
在初始化前成功 open，因此 reset 不影响已接受连接，adapter 的 session 指针
始终有效。

Coordinator 创建后、其他 subsystem 注册前调用
`core_app_net_transport_world_adapter_register`。它复用 transport session 与
core_app net_bus，创建 adapter 并调用现有
`break_runtime_world_session_register_subsystem`。world 开启时 subsystem table
上限从 5 增至 6，注册顺序为 adapter→network→voice→audio→render→level。
world 关闭时保持上限 5，不创建 adapter、kind、subscription 或新行为。

`BreakRuntimeWorldSessionLifecycle` 末尾增加可选 `on_destroy(void *user_data)`，
成功销毁后调用，不在 TIMEOUT、FAILED 或 abandon 时调用。core_app 用它清空
transport 的 adapter 指针，防止 network destroy TIMEOUT 后回滚再次访问已
释放 adapter。默认 NULL 保持原行为。

## 控制路径

open 由 transport 构造 `OPEN`（key、当前 level、epoch=0），submit 后立即由
CoreAppThread 执行 adapter drain，再读取分配的 connection_epoch。只有成功
才设置 `world_open`，并保存 epoch 供 close/ACK 使用。失败保持原未打开状态。

close 使用保存的 key/epoch/current level，submit+drain 成功后才清
`world_open` 和 epoch。close/reopen 后旧 epoch 命令由 adapter 拒绝，不会修改
新连接。

本地 poll 得到的 ACK/NEED_FULL 转为 `BreakRuntimeWorldCommand`，带保存的
connection_epoch、原 delta/target/tick/level。首个 submit 使用
`break_runtime_correlation_next` 并保存 cid；后续重试保持同一命令与 cid。
adapter queue/submit OVERLOAD 保留 `world_control_pending`，其他终态按既有
terminal error 计数，adapter 的 transport pending 优先于后续 FIFO。

入站 `0x400B` 继续直接调用 `break_world_session_handle_control`，只裁剪本地
sender history/设置 force_full，绝不转换成再次发往对端的 ACK。BRWD publish、
每连接 diagnostic World drain 和 simulation 边界完全不变。

## 正常关闭与回滚

Coordinator 阶段按注册顺序执行：

1. adapter stop_admission/close/drain/join/destroy；
2. network 对应阶段，随后由 transport 销毁 session/reactor；
3. core_app 再退订并销毁 net_bus；
4. 最后销毁 Coordinator。

adapter pending 或 drain TIMEOUT 时，network/session/reactor/net_bus 必须保持
可用，不能提前销毁。adapter 成功销毁并触发 on_destroy 后，network destroy
自身即使 TIMEOUT，也不会让 rollback 再访问该 adapter。

CREATED 或 FAILED 回滚先停止其他 adapter API，调用
`break_runtime_world_session_abandon`，然后手动 close/drain 到真实 pending=0
并 destroy adapter，最后才执行 network drain/destroy 和 net_bus 关闭。现有
“network 先 drain/destroy”的顺序在 world 开启时必须由 adapter-aware 路径
替代；world 关闭时保持原路径。

## 验证

- world off：无 adapter、subscription 或新增 trace，既有五子系统路径不变。
- world on：首 tick 前后 session 指针相同且有效；恢复 destroy/recreate 的反向
  控制使功能断言或 ASan 判红。
- open/ACK/NEED_FULL 在 submit 前无 World 副作用，drain 后 FIFO 恰好一次；
  高位 cid 保留且旧直接发送路径不重复。close/reopen 旧 epoch 拒绝，入站 ACK
  仅裁剪本地 history。
- adapter drain TIMEOUT 阻断 network destroy；重试后排空才继续。network
  destroy TIMEOUT 时 on_destroy 已清指针，不发生二次释放。
- CREATED/FAILED rollback 先 abandon/manual drain，再销毁 network；错误顺序
  由反向控制捕获。
- inbound 仍只改变对应 diagnostic World，CoreLevel simulation/physics/权威
  trace 不变。
- focused normal、ASan+UBSan（显式 leak 检测）、TSan 和完整 Vulkan/OpenGL；
  独立任务与整分支评审后推送并核验远端矩阵。


## 终审约束（2026-11-25）：跨槽代际所有权与拒绝清理

- connection key 的 World 代际所有权跨全部 transport 槽位生效。旧槽仍保存该 key 的
  OPEN、CLOSE 或取消 OPEN 后的补偿 CLOSE 时，其他槽位的同 key OPEN 只保持
  admission pending，不得进入 Runtime queue。旧连接及补偿关闭完成对账、旧槽释放后，
  才允许新 OPEN 提交。断连后 CLOSE 失败且仍持有旧 epoch 的槽位继续保存 key，不能让
  新连接认领旧状态。该规则不新增 Runtime API、wire 消息或数据面。
- OPEN 提交前记录该 key 的先前 epoch；对账成功要求非零且相对先前值已经变化，不能仅凭
  当前 key 存在任意 epoch 就认领连接。同 key pending CLOSE→OPEN 与取消 OPEN→同 key
  OPEN 回归必须检查旧槽 key/epoch/transition/diagnostic 全部释放、新槽独立 epoch、
  diagnostic 归属以及 opened/closed/open_count。
- 延迟 OPEN 拒绝与正常断连共用同一槽位释放路径，保持正常断连的
  voice→aspect→World→字段清理顺序。拒绝路径额外关闭 session/reactor，并覆盖 voice
  receiver/rate/mute、clock probe、physics baseline/correction、session/auth/welcome
  状态；后续 CLOSED 事件不再承担该已拒绝槽位的清理。回归在 pending OPEN 期间完成真实
  session 认证并接收编码 voice 帧，随后强制 epoch 耗尽拒绝 OPEN，验证资源释放和同槽
  复用后新 receiver 不继承旧帧或速率状态。
- World hooks 的成对检查不依赖 `CORE_APP_NET_TRANSPORT`。半对配置在所有构建中均为
  INVALID；无 concrete transport 时任何非 NULL 成对 hooks 同样明确 INVALID，两个 NULL
  保持原五子系统且不新增链接依赖。transport-enabled 的 world-off 成对注册若返回空
  adapter，也回退原五子系统；真实 world on 仍为六项。
- 删除全槽 key 门禁必须使两条同 key 回归判红；删除延迟拒绝的共享释放必须使认证 voice
  回归判红。恢复后 directed normal、ASan+UBSan（显式 leak 检测）与 TSan 分别验证，既有
  core_app Lua/TSan 进程限制单列，不扩大为完整进程 sanitizer 结论。
