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
| `3746a3ee` | 本报告、实际设计/实施状态与计划完成记录 |

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

---

# P8 fix round 1 追加报告

## 7. 评审与修复提交

独立评审全文见 `.superpowers/sdd/review-findings.md`。本轮按 Critical、Important、Minor 逐项做真实 RED 后修复，未以合法 loopback 代替攻击测试。

| 提交 | 修复 |
|---|---|
| `32dc37ff` | NAT challenge、session-key HMAC、replay window、recipient 和冲突/重复控制 |
| `af74bee8` | 允许合法下一代 aspect adopt，旧 generation 仍拒绝 |
| `ef228f19` | 新 delta 淘汰未完成旧 delta，迟到旧 delta 拒绝 |
| `bef21aa3` | pending_leave/kind 在空 AOI 优先重试 |
| `35fa4be9` | 认证 CLOSE、endpoint reset、tombstone 和 re-pair |
| `f7b40a7a` | wire 相对 TTL，endpoint 本地时钟 deadline，过期 CLOSE |
| `df8394bd` | DESTROY/DORMANT 真实 ghost 消费 |
| `4dab29fc` | nonce、pair capacity、stale peer、revision overflow、MPSC overload 负例 |
| `48819035` | 分配式/固定存储分片 API 共用 planner/fill |
| `6ab22850` | 可选 session_key 完整初始化，修复大厅 `-Werror` 构建 |
| `3e04dc23` | 本报告和实际协议/状态文档 |

## 8. RED -> GREEN 证据

### NAT 控制面认证与重放

- 当前合法旧报文先复现三项漏洞：**7 passed, 3 failed, 10 total**：跨 socket HELLO 改变 observed address、未注册 PUNCH 被接受、重复 PUNCH 重置 connected。
- 加入独立有效 HMAC captured HELLO 后为 **7 passed, 4 failed, 11 total**，其中新测试收不到 challenge。
- 实现后首轮 **13/13**，包含 captured HELLO 跨 socket 重放、pre-registration、精确/冲突 PUNCH 和篡改 MAC。最终加入 CLOSE/TTL/容量等回归后为 **19/19**。
- 变异：删除 PUNCH MAC 校验后 tampered PUNCH 被接受，**12 passed, 1 failed, 13 total**；恢复后 13/13。

### Aspect adopt / 持久重组 / pending leave

- gen2：authoritative+remote 双销毁后 create/adopt gen2 失败，**5 passed, 1 failed, 6 total**；修复后 6/6，旧 gen1 仍拒绝。
- 持久重组：新 delta supersession 单测为 **9 passed, 1 failed, 10 total**；调度端第二片失败为 **3 passed, 1 failed, 4 total**，均因旧 reassembler 冲突。允许单调新 delta 淘汰旧未完成流后分别为 10/10、4/4；迟到旧 delta 仍返回 `CONFLICT`。
- pending leave：预算耗尽和发送失败后空 AOI 均不发控制记录，**4 passed, 2 failed, 6 total**；保存 pending_leave/kind 并优先重试后 6/6。

### CLOSE / 相对 TTL / 控制消费

- CLOSE：after-connect 未 reset、close-before-PUNCH 仍可 arm，**13 passed, 2 failed, 15 total**；认证 CLOSE 和 tombstone 后 15/15，含 late PUNCH 拒绝和新 generation re-pair。
- 相对 TTL：端点时钟大于 coordinator 时，旧绝对 deadline 导致五秒连接超时，**15 passed, 1 failed, 16 total**。wire 改相对 TTL 后 16/16；coordinator 过期仍发认证 CLOSE，避免迟到 PUNCH 被重新接受。
- 控制消费：direct DESTROY/DORMANT **6 passed, 1 failed, 7 total**，scheduler **3 passed, 3 failed, 6 total**，均因 `break_aspect_apply` 返回 INVALID。实现后分别 7/7、6/6；DORMANT 清 active mask，DESTROY 使旧句柄失效。

### 必要负例与共享 planner

- 新负例当前实现均通过：NAT 19/19、aspect 8/8、并发 overload accepted=64/overload=64/high-water=64。它们属于既有 guard 的补充证明，不冒充独立功能 RED。
- nonce 变异：删除 nonce 检查后 **18 passed, 1 failed, 19 total**，错误 nonce 被接受；恢复后 19/19。
- pair capacity：仅删除第一个容量比较仍被第二道空槽 guard 拦截，没有假报 RED；临时把第二道 guard 改为复用槽位后 **18 passed, 1 failed, 19 total**，恢复两道 guard 后 19/19。
- aspect revision：删除 `UINT64_MAX` 上限检查后 **7 passed, 1 failed, 8 total**，旧值和 revision 保护测试失败；恢复后 8/8。
- 共享 planner/fill 后固定分片 **10/10**、AOI 调度 **6/6**，分配式与固定存储 API 的 wire、短容量、重试均未漂移。
- 全量构建还发现 `session_key` 新字段使大厅复合字面量触发 `-Werror=missing-field-initializers`；显式初始化可选回调后恢复，不屏蔽告警。

## 9. 最终 focused 命令与输出

normal 无 Snowflake：

```bash
cmake --build build-p8-normal -j6 --target \
  test_break_online_lobby test_break_online_nat test_break_online_voice \
  test_break_online_aspect test_break_online_aspect_replication \
  test_break_replication_fragment test_network test_net_loop test_net_loop_qnx \
  test_packet test_ecs_replication
ctest --test-dir build-p8-normal --output-on-failure \
  -R '^(test_break_online_lobby|test_break_online_nat|test_break_online_voice|test_break_online_aspect|test_break_online_aspect_replication|test_network|test_net_loop|test_net_loop_qnx|test_packet|test_break_replication_fragment|test_ecs_replication)$'
```

结果：**11/11 passed, 0 failed**。

钉住 Snowflake `0fceed6d885bb8578743d82cc4a5d7ab2f6b0620` 的 normal、ASan+UBSan、TSan 三棵树均运行：

```bash
ctest --test-dir <对应构建树> --output-on-failure \
  -L 'network|replication|fragmentation|session'
ctest --test-dir <对应构建树> --output-on-failure \
  -R '^(test_network|test_net_loop|test_net_loop_qnx|test_packet|test_ecs_replication)$'
```

- `build-p8-snow`：**13/13 + 5/5 passed**。
- `build-p8-snow-asan`：**13/13 + 5/5 passed**，无 ASan/UBSan 报告。
- `build-p8-snow-tsan`：**13/13 + 5/5 passed**，无 race 报告。

所有 lane 均保留真实 UDP NAT/语音 loopback；安全套件包含有效 MAC captured HELLO 跨 socket replay，不是仅拒绝旧格式。最终直接行为总数为 lobby 10/10、NAT 19/19、voice 8/8、aspect 8/8、AOI 调度 6/6、固定分片 10/10，真实 Session 38/38。

最终提交前执行 `git diff --check a0bfeb95..HEAD` 和工作树状态检查；结果在交付手-off 中给出。

## 10. 本轮新增限制

- 每 session 的 32 字节密钥 provision、rotation 和 endpoint/coordinator 配套存储仍由应用负责；`break_online_session.h` 不自动提供 NAT 密钥。没有密钥时 NAT 创建 fail-closed。
- 新 delta supersession 只解决未完成旧流的单调重试，不是可靠传输、全局去重或跨重连持久去重；reassembler 仍需上层 bounded lifetime。
- 相对 TTL 从 endpoint 接受 PUNCH 的本地时钟计算，coordinator 自行管理期限并发送 CLOSE；仍不承诺任意 NAT、公网部署、防火墙穿透或可靠送达。
- 未运行 Windows/macOS/移动原生 lane、外部 NAT 设备或听感测试；本报告仅覆盖本机 Linux focused 与攻击 loopback。

---

# P8 fix round 2 追加报告

## 11. 评审与修复提交

第二轮评审全文见 `.superpowers/sdd/review-fix1-findings.md`。保留其已 ADDRESSED 项，只处理五个开放 Important。原 round1 文档 hash 已明确填写为 `3e04dc23`，不再保留“最终文档提交”占位。

| 提交 | 修复 |
|---|---|
| `e539c61a` | endpoint 持久 control high-water，覆盖 TTL、连续 CLOSE 和 re-pair |
| `92af5a71` | stateless 来源绑定 challenge，伪造 DISCOVER 不再占槽 |
| `58406c95` | reassembler 持久 high-water 与全分配成功后的原子淘汰 |
| `9bfb44d7` | 每对象 record epoch、DORMANT/普通 leave 重入和旧 control 拒绝 |
| `1d2487c0` | crypto OFF 的独立 fail-closed 构建与合约测试 |
| `7b33bd0d` | 第二轮实际协议/状态文档与本报告 |

## 12. 第二轮 RED -> GREEN

### 持久控制序号与 CLOSE

- 本地 TTL 后有效 MAC captured PUNCH 可重新 arm，**19 passed, 3 failed, 22 total**；另两项在连续 CLOSE 消费后证实最早 PUNCH 和旧 CLOSE 乱序可复活。
- 持久 high-water 后 22/22；合法更大 generation/sequence re-pair 仍通过。临时删除 PUNCH high-water 检查后 **20 passed, 2 failed, 22 total**，恢复后 22/22。

### DISCOVER 生命周期

- 伪造 8 个 session 在容量 2 的 coordinator 刷槽，合法注册五秒超时，**22 passed, 1 failed, 23 total**。
- stateless 来源绑定 nonce 后伪造刷量不占状态，合法两端注册成功，23/23。challenge expiry 对 endpoint 是不透明字段，只有 coordinator 在自己的时钟上验证，避免跨 epoch 误判。

### Reassembler high-water 与原子淘汰

- 完成后旧 delta 可重新开始、超大新 delta 淘汰失败后旧流丢失，**10 passed, 2 failed, 12 total**。
- 新流元数据、首片和结果分配全部成功后才替换旧流，完成后旧 delta 冲突、失败淘汰保留旧流，12/12；显式 reset 才开启新 epoch。删除 high-water 检查后 **11 passed, 1 failed, 12 total**，恢复后 12/12。

### DORMANT 与普通 AOI 重入

- direct DESTROY 仍错误退休 generation，**7 passed, 1 failed, 8 total**；普通 AOI leave 后同 handle 重入失败，**6 passed, 1 failed, 7 total**。
- 引入 record epoch 后，普通 leave/DORMANT 仅去激活，后续更高 epoch baseline 可重入，旧 control 被拒绝。最终 aspect 8/8、scheduler 7/7。临时不提交 scheduler record epoch 后 **1 passed, 6 failed, 7 total**，恢复后 7/7。

### Crypto OFF

- 初次真实 configure/build 在 crypto OFF 下因 `#else` 分支未使用变量 `-Werror` 失败，完整 HMAC 目标也不适合该配置。
- crypto-only 声明与成功路径测试改为 `if(BREAK_ENABLE_CRYPTO)`，新增无 crypto API 引用的 `test_break_online_nat_nocrypto` 后，create 均 REJECTED 且输出为空，其余测试继续通过，11/11。

## 13. 第二轮最终验证

### crypto ON 无 Snowflake normal

```bash
cmake --build build-p8-normal -j6 --target \
  test_break_online_lobby test_break_online_nat test_break_online_voice \
  test_break_online_aspect test_break_online_aspect_replication \
  test_break_replication_fragment test_network test_net_loop test_net_loop_qnx \
  test_packet test_ecs_replication
ctest --test-dir build-p8-normal --output-on-failure \
  -R '^(test_break_online_lobby|test_break_online_nat|test_break_online_voice|test_break_online_aspect|test_break_online_aspect_replication|test_network|test_net_loop|test_net_loop_qnx|test_packet|test_break_replication_fragment|test_ecs_replication)$'
```

结果：**11/11 passed**。

### 钉住 Snowflake normal / ASan+UBSan / TSan

三棵树均运行：

```bash
ctest --test-dir <对应构建树> --output-on-failure \
  -L 'network|replication|fragmentation|session'
ctest --test-dir <对应构建树> --output-on-failure \
  -R '^(test_network|test_net_loop|test_net_loop_qnx|test_packet|test_ecs_replication)$'
```

- `build-p8-snow`：**13/13 + 5/5 passed**。
- `build-p8-snow-asan`：**13/13 + 5/5 passed**，无 ASan/UBSan 报告。
- `build-p8-snow-tsan`：**13/13 + 5/5 passed**，无 race 报告。

### no-crypto normal / ASan+UBSan / TSan

```bash
ctest --test-dir build-p8-nocrypto --output-on-failure \
  -R '^(test_break_online_lobby|test_break_online_nat_nocrypto|test_break_online_voice|test_break_online_aspect|test_break_online_aspect_replication|test_network|test_net_loop|test_net_loop_qnx|test_packet|test_break_replication_fragment|test_ecs_replication)$'
ctest --test-dir build-p8-nocrypto-asan --output-on-failure \
  -R '^(test_break_online_lobby|test_break_online_nat_nocrypto|test_break_online_voice|test_break_online_aspect|test_break_online_aspect_replication|test_network|test_net_loop|test_net_loop_qnx|test_packet|test_break_replication_fragment|test_ecs_replication)$'
ctest --test-dir build-p8-nocrypto-tsan --output-on-failure \
  -R '^(test_break_online_lobby|test_break_online_nat_nocrypto|test_break_online_voice|test_break_online_aspect|test_break_online_aspect_replication|test_network|test_net_loop|test_net_loop_qnx|test_packet|test_break_replication_fragment|test_ecs_replication)$'
```

三棵树均 **11/11 passed**，无 sanitizer/race 报告。no-crypto 只运行独立 fail-closed 合约，不执行 HMAC 成功路径；crypto-enabled lane 均保留真实 UDP NAT/语音 loopback和有效 MAC captured replay。

最终直接行为总数为 lobby 10/10、NAT 23/23、voice 8/8、aspect 8/8、AOI 调度 7/7、固定分片 12/12、真实 Session 38/38。最终提交前执行 `git diff --check a0bfeb95..HEAD` 和工作树状态检查；结果在交付手-off 中给出。

## 14. 第二轮新增限制

- `challenge_key` 与每 session 密钥仍由应用 provision/rotation。stateless challenge 消除的是认证前槽位占用，不是公网洪泛防护或速率限制。
- 持久 high-water 防止 endpoint 控制重放，不等于可靠传输、跨进程持久去重或全局 NAT 穿透保证。
- record epoch 只提供单对象记录顺序；显式 `break_aspect_object_destroy` 才退休 generation，普通 AOI leave 只去激活。
- 本报告仍仅覆盖本机 Linux focused 与攻击 loopback，未运行 Windows/macOS/移动原生、外部 NAT 设备、公网服务或听感测试。


---

# P8 fix round 3 追加报告

## 15. 评审与修复提交

第三轮只处理“完整包已交付但 callback 失败，随后修改值并重试”导致的同 epoch 不同内容永久 STALE；round2 其余项保持 ADDRESSED，未重做 NAT/reassembler 工作。round2 文档提交已在上表补记为实际提交 `7b33bd0d`。

| 提交 | 修复 |
|---|---|
| `c90e0fa5` | 只读 epoch 编码、value revision/record epoch 分离、每次实际发送尝试分配新 epoch |

## 16. 第三轮 RED -> GREEN 与生产变异

### 完整交付后的 callback 失败

- 新 sink 在 `fail_after_record_call` 中先保存完整包，再返回 `OVERLOAD`。远端成功应用 A 后，authoritative setter 把值改为 B；旧实现以相同 record epoch 重试不同 packet hash，永久返回 STALE。RED 为 **8 passed, 1 failed, 9 total**。
- `publish()` 在编码、分片和预算预检通过后、首个 datagram 前提交 `real->record_epoch = epoch`。callback 失败保留这个 attempt high-water 和 dirty；后续实际尝试使用更高 epoch，修改后的 B 因而可作为新记录应用。只有全部片段成功才清 dirty/更新 ghost。
- 预算为 0 时预检在首包前返回，不推进 record epoch；提高预算后修改值并重试成功。GREEN：aspect **9/9**、AOI 调度 **9/9**。
- 生产变异：把 attempt high-water 移回 callback 成功之后，交付后失败测试为 **8 passed, 1 failed, 9 total**；恢复后 **9/9**。

### 只读编码与 value revision 分离

- `break_aspect_encode_with_epoch()` 不再写 store 的 record epoch/hash；较小 epoch 返回 `BREAK_RUNTIME_STALE`，同 epoch 不同 hash 也拒绝。较小 epoch 负例初次 RED 为 **8 passed, 1 failed, 9 total**。
- `break_aspect_apply()` 成功只更新 record epoch/hash，不再把 wire record epoch 写回公共 value revision。公共 value revision 只表示本地值变更；value revision 或 record epoch 为 `UINT64_MAX` 时 setter 返回 OVERLOAD。
- 直接连续控制记录显式使用 DORMANT epoch 2、DESTROY epoch 3，不依赖 value revision 隐式分配唯一 epoch。普通 AOI leave/DORMANT 仍只去激活，只有永久 `break_aspect_object_destroy` 退休 generation。
- 生产变异：删除较小 epoch 检查后 aspect 为 **8 passed, 1 failed, 9 total**；恢复后 **9/9**。

## 17. 第三轮 focused 验证

### crypto ON 无 Snowflake normal

```bash
cmake --build build-p8-normal -j6 --target \
  test_break_online_lobby test_break_online_nat test_break_online_voice \
  test_break_online_aspect test_break_online_aspect_replication \
  test_break_replication_fragment test_network test_net_loop test_net_loop_qnx \
  test_packet test_ecs_replication
ctest --test-dir build-p8-normal --output-on-failure \
  -R '^(test_break_online_lobby|test_break_online_nat|test_break_online_voice|test_break_online_aspect|test_break_online_aspect_replication|test_network|test_net_loop|test_net_loop_qnx|test_packet|test_break_replication_fragment|test_ecs_replication)$'
```

结果：**11/11 passed**。

### 钉住 Snowflake normal / ASan+UBSan / TSan

测试源码仍使用本机已有 Snowflake 仓库的钉住提交 `0fceed6d885bb8578743d82cc4a5d7ab2f6b0620`，未修改外部仓库或新增依赖。三棵树均运行：

```bash
ctest --test-dir <对应构建树> --output-on-failure \
  -L 'network|replication|fragmentation|session'
ctest --test-dir <对应构建树> --output-on-failure \
  -R '^(test_network|test_net_loop|test_net_loop_qnx|test_packet|test_ecs_replication)$'
```

- `build-p8-snow` normal：**13/13 + 5/5 passed**。
- `build-p8-snow-asan` ASan+UBSan：**13/13 + 5/5 passed**，无 sanitizer 报告。
- `build-p8-snow-tsan` TSan：**13/13 + 5/5 passed**，无 race 报告。

### no-crypto normal / ASan+UBSan / TSan

```bash
ctest --test-dir build-p8-nocrypto --output-on-failure \
  -R '^(test_break_online_lobby|test_break_online_nat_nocrypto|test_break_online_voice|test_break_online_aspect|test_break_online_aspect_replication|test_network|test_net_loop|test_net_loop_qnx|test_packet|test_break_replication_fragment|test_ecs_replication)$'
ctest --test-dir build-p8-nocrypto-asan --output-on-failure \
  -R '^(test_break_online_lobby|test_break_online_nat_nocrypto|test_break_online_voice|test_break_online_aspect|test_break_online_aspect_replication|test_network|test_net_loop|test_net_loop_qnx|test_packet|test_break_replication_fragment|test_ecs_replication)$'
ctest --test-dir build-p8-nocrypto-tsan --output-on-failure \
  -R '^(test_break_online_lobby|test_break_online_nat_nocrypto|test_break_online_voice|test_break_online_aspect|test_break_online_aspect_replication|test_network|test_net_loop|test_net_loop_qnx|test_packet|test_break_replication_fragment|test_ecs_replication)$'
```

三棵树均 **11/11 passed**，ASan+UBSan 无 sanitizer 报告，TSan 无 race 报告。no-crypto 只运行独立 fail-closed 合约，不执行 HMAC 成功路径；crypto-enabled lane 保留真实 UDP NAT/语音 loopback和有效 MAC captured replay。

最终直接行为为 NAT **23/23**、voice **8/8**、aspect **9/9**、AOI 调度 **9/9**、固定分片 **12/12**、真实 Session **38/38**。最终提交前执行 `git diff --check a0bfeb95..HEAD` 和工作树状态检查；结果在交付 handoff 中给出。

## 18. 第三轮限制

- `challenge_key` 与每 session 密钥仍由应用 provision/rotation；本切片不提供密钥生命周期服务。
- record epoch 只提供进程内单对象记录顺序和重复/冲突检测，不是跨进程持久去重，也不保证可靠送达。
- 仅本机 Linux focused 验证；不承诺任意 NAT、防火墙穿透、公网部署、Windows/macOS/移动原生验证或可靠送达。
