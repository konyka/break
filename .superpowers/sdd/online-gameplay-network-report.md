# P8 Online Gameplay Network 交付报告

日期：2026-11-03

## 1. 范围与计划

- 仓库/工作树：`/home/timeshift/opensource/break/.worktrees/cry-network`
- 分支：`cry-wave2-network`，base `a0bfeb95`；未改 master，未 push。
- 总体设计：`docs/superpowers/specs/2026-11-02-cry-capability-completion-design.md` P8。
- 具体计划：`docs/superpowers/plans/2026-11-03-online-gameplay-network.md`。
- 正式可选目标：`break_online`，不链入 `engine`、demo 或编辑器；无新增依赖。
- 实现文档：`docs/design/online_gameplay_network.md`，并同步 `session_protocol.md`、`ecs_snapshot_replication_aoi.md`、`docs/Implementation_Status.md`。

交付行为包括认证大厅/目录/加入离开/主机迁移/服务端匹配，真实 UDP NAT 协调，有界 PCM 语音与 jitter/丢失处理，以及 aspect schema/变化掩码/带宽编码/AOI 调度。复用了现有认证 Session、NetSocket、AOI、分片/reassembler 和安全传输边界，没有实现第二套可靠传输或认证。

## 2. 提交

| 提交 | 内容 |
|---|---|
| `29b2b581` | P8 具体 TDD 计划 |
| `3ba4fd6e` | 认证有界大厅、目录、迁移、匹配和真实 Session 适配 |
| `d3e7980b` | 有界收件队列与 UDP NAT 协调 |
| `f5051049` | PCM 语音、序号、jitter 和丢失隐藏 |
| `a95adbd0` | 调用方固定存储分片视图 |
| `1c1ed6b3` | aspect schema/store/变化掩码编码和事务 apply |
| `461bf3af` | AOI 驱动的按连接 aspect 复制调度 |
| `8b408cb5` | 自审修复：禁止 adopt 旧 generation |
| 最终文档提交 | 本报告、实际设计/实施状态与计划完成记录；最终 HEAD hash 在交付手-off 中给出 |

## 3. 逐行为 RED -> GREEN

以下均为实际工具输出，不把“能编译”当作功能证据。

### Lobby / Session

- 初始 RED：`test_break_online_lobby.c:2: fatal error: network/break_online_lobby.h：没有那个文件或目录`。
- 行为 RED：最小生命周期和返回 `FAILED` 的桩可执行后，**0 passed, 10 failed**；首项在 `break_lobby_room_create(...) != BREAK_RUNTIME_REJECTED` 失败，其余创建、加入、迁移、匹配、错误线程均失败。
- GREEN：实现后 **10 passed, 0 failed**。中间曾出现 9/10：满房间重复玩家先返回 `OVERLOAD`，修正为优先 `REJECTED` 后全绿。
- 真实 Session RED：`fatal error: network/break_online_session.h：没有那个文件或目录`；实现后钉住 Snowflake 的 `test_break_session` **38 passed, 0 failed**，包括 NEW/AUTHENTICATING 拒绝、AUTHENTICATED 创建和断连清理。

### NAT / Inbox

- 初始 RED：`fatal error: network/break_online_inbox.h：没有那个文件或目录`。
- 行为 RED：inbox 两个行为测试和 socket 初始化通过，NAT 注册/配对、错误来源、TTL、malformed 四项失败，**3 passed, 4 failed, 7 total**。
- GREEN：实现后 **7 passed, 0 failed**。真实三 socket loopback 完成 HELLO/WELCOME、双向 PUNCH/PING、ACK 和 observed address；伪造来源、容量、重复、TTL、关闭均通过。

### Voice

- 初始 RED：`fatal error: network/break_online_voice.h：没有那个文件或目录`。
- 行为 RED：仅初始化通过，**1 passed, 7 failed, 8 total**；精确编码、流校验、入队、jitter、UDP 均在目标行为处失败。
- GREEN：实现及修正三处小于 1ms 的非法测试流配置后，**8 passed, 0 failed**。没有放宽生产端的帧时长校验。

### 固定存储分片

- 初始 RED：`implicit declaration of function break_replication_fragment_payload_into`。
- 行为 RED：旧 7 项通过，新往返和短容量失败，**7 passed, 2 failed, 9 total**。
- GREEN：**9 passed, 0 failed**，4/4/2 切片与分配式 API 逐字段一致并可逆序重组；短容量返回 `OVER_LIMIT` 且计数为 0、元数据不变。

### Aspect schema / codec

- 初始 RED：`fatal error: network/break_online_aspect.h：没有那个文件或目录`。
- 行为 RED：**0 passed, 5 failed**，覆盖对象创建、schema 校验、手工编码、事务 apply 和 generation。
- GREEN：**5 passed, 0 failed**。手工 health=300 包为 25 字节，mask=2，值 varint=`ac 02`；baseline/dirty、负值/浮点/字节、容量和 malformed 均通过。
- 自审新增 RED：销毁后 adopt 同一旧 generation 返回成功，测试变为 **4 passed, 1 failed**，断言 `break_aspect_object_adopt(...) != BREAK_RUNTIME_STALE`。`8b408cb5` 修复后 normal/ASan+UBSan/TSan 的 aspect 5/5 和 scheduler 3/3 均恢复。

### AOI 调度

- 初始 RED：`fatal error: network/break_online_aspect_replication.h：没有那个文件或目录`。
- 行为 RED：**0 passed, 3 failed**，没有 baseline/调度发送。
- GREEN：**3 passed, 0 failed**。真实 AOI、两个连接独立 dirty、优先级/预算、失败重试、固定分片重组、dormant 和断连均通过。

## 4. 变异证据

| 生产源码临时变异 | 实际失败输出 | 恢复后 |
|---|---|---|
| 删除 lobby `host_epoch++` | 9/10，`info.host_epoch != 2u` | 10/10 |
| 删除 NAT PING 期望源地址比较 | 6/7，`break_nat_endpoint_connected(...) is true`，伪造包被接受 | 7/7 |
| 删除 voice `playback.concealed=true` | 7/8，`playback.concealed is false` | 8/8 |
| 短容量分片错误发布 count | 8/9，`count != 0u` | 9/9 |
| 删除 aspect 精确包结束检查 | 4/5，`delta_size + 1u` 不再返回 INVALID | 5/5 |
| 发送回调结果检查前清 dirty | 2/3，失败重试后 `fixture.sink.count != 1u` | 3/3 |

所有变异均已恢复并重新构建测试；没有通过修改测试来掩盖生产缺陷。测试夹具本身的错误（fake session key 不匹配、非法 sub-ms PCM、误用已注册 aspect mask、重复消费 baseline）均在报告中单独区分并修正。

## 5. 最终验证命令与结果

### 无 Snowflake normal

```bash
cmake --build build-p8-normal -j6 --target \
  test_break_online_lobby test_break_online_nat test_break_online_voice \
  test_break_online_aspect test_break_online_aspect_replication \
  test_break_replication_fragment test_network test_net_loop test_net_loop_qnx \
  test_packet test_ecs_replication
ctest --test-dir build-p8-normal --output-on-failure \
  -R '^(test_break_online_lobby|test_break_online_nat|test_break_online_voice|test_break_online_aspect|test_break_online_aspect_replication|test_network|test_net_loop|test_net_loop_qnx|test_packet|test_break_replication_fragment|test_ecs_replication)$'
```

最终结果：**11/11 passed, 0 failed**。

### 无 Snowflake ASan+UBSan / TSan

两树使用 `ENGINE_USE_ASAN=ON+ENGINE_USE_UBSAN=ON` 或 `ENGINE_USE_TSAN=ON`，相同 11 个 focused 测试均 **11/11 passed**，无 sanitizer 报告。generation 自审修复后，两树再次直接运行 aspect 5/5 与 scheduler 3/3，均通过。最终修复后的全组合又在下列 Snowflake sanitizer 树复验。

### 钉住 Snowflake 的 normal / ASan+UBSan / TSan

测试源码来自本机已有 Snowflake 仓库的钉住提交 `0fceed6d885bb8578743d82cc4a5d7ab2f6b0620`，放置于忽略的构建目录；未修改外部仓库，未引入新依赖。三棵树均执行：

```bash
ctest --test-dir <对应构建树> --output-on-failure \
  -L 'network|replication|fragmentation|session'
ctest --test-dir <对应构建树> --output-on-failure \
  -R '^(test_network|test_net_loop|test_net_loop_qnx|test_packet|test_ecs_replication)$'
```

- `build-p8-snow` normal：**13/13 + 5/5 passed**。
- `build-p8-snow-asan` ASan+UBSan：**13/13 + 5/5 passed**，无 sanitizer 报告。
- `build-p8-snow-tsan` TSan：**13/13 + 5/5 passed**，无 race 报告。

13 项包括 target contract、5 个新在线测试、固定分片、旧 adapter/replication/Session/TLS、replay window 和 msg rate；5 项包括 ECS replication、packet、network、epoll net_loop 和 poll net_loop。首次 normal 标签运行有 2 项因旧可执行文件未构建而 Not Run，补建 `test_break_replay_window`/`test_break_msg_rate` 后完整重跑为 13/13；没有缩小标签掩盖。两棵 sanitizer 树曾把 CMake 脚本测试误列为 build target，随后直接运行已配置的完整测试，结果如上。

每个 normal/ASan+UBSan/TSan lane 都执行了 NAT 和语音真实 UDP loopback，而不是只执行 codec/import。MPSC inbox 双生产者测试也在 TSan 下通过。

### 构建配置与卫生

- C11，GCC 16.2.1，CMake 4.3.0，Linux；`-Wall -Wextra -Werror -pedantic` 生效。
- 新模块分配点自审：仅 create/destroy 中出现 `malloc/calloc/free`，同步/接收/播放热路径无 `realloc`。
- 最终提交前运行 `git diff --check`；结果和最终工作树状态在交付手-off 中给出。

## 6. 限制与未声称事项

- 仅本机 Linux focused 证据；未运行 Windows/macOS/移动原生 lane，也不是全仓库 CTest 或外部部署证明。
- NAT loopback 不承诺任意 NAT、防火墙、公网地址映射或可靠送达；没有生产 NAT 设备测试。
- PCM 测试验证样本与播放状态，不是听感测试；网络线程不混音，未接音频设备。
- `BreakAspectSendFn` 的调用方必须提供认证/安全传输；FNV 分片 checksum 不是认证。没有新增可靠传输、客户端预测、回滚或 authority handoff。
- 内置 Session 身份是 session 域 id，不是跨重连账号系统；coordinator peer 表当前没有回收 API，受固定容量约束。
- 本报告不声称生产账号后端、全 CryNetwork 私有行为兼容或全平台完成。
