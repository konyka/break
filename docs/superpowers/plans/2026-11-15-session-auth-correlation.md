# Session AUTH 回复回带关联 ID（2026-11-15）

## 目标
客户端 session 层收到 CHALLENGE 后自动发出 AUTH v2 回复。回复应带上 CHALLENGE 的
`correlation_id`，让 trace flow 能把握手请求和回复连成一条链。

## 步骤
1. 测试辅助：`break_net_reactor_enqueue_correlated_message_for_test(reactor, key, id,
   version, cid, data, size)`；原 `enqueue_message_for_test` 转调并传 0。
2. RED：`break_session_challenge_auth_reply_echoes_correlation_id` 注入 cid 为
   `0x5151` 的 CHALLENGE，断言 outbound AUTH 的 `correlation_id == 0x5151`。
3. GREEN：`break_session_challenge_received` 改用 `break_net_reactor_send_correlated`，
   传 `event->message.correlation_id`。
4. 变异：把传入的 cid 改为 `cid & 0u`，测试必须失败。
5. `build-net-master` 与 `build-core-app-master` 全量 ctest，追加文档，提交推送。

## Status
完成。RED 在第 1480 行失败；GREEN 后 `test_break_session` 42/42；`& 0u` 变异被捕获；全量 ctest 405/405（`build-net-master`）与 401/401（`build-core-app-master`）。
