# Compose + MVI Task 1 报告：C11 描述树与 keyed diff

## 范围与提交

- Worktree：`/home/timeshift/opensource/break/.worktrees/compose-mvi`
- Base / 起始 HEAD：`2129bc397220c0fc1314b8b888867f53a57d69d1`
- Commit subject：`feat: add declarative tree diff`
- Commit SHA：本报告与实现随同一个 scoped commit 提交，最终 SHA 以该提交后的 `git rev-parse HEAD` 和交付返回为准。
- 未 push、未建 PR、未合并其它分支。
- 仅实现 C11 描述树、双缓冲构建、property/event 固定存储和 keyed/unkeyed diff；未实现 remember、store、runtime、myui adapter 或 C++ DSL。

改动文件：

- `engine/CMakeLists.txt`
- `engine/src/myui/mycompose/my_compose.h`
- `engine/src/myui/mycompose/my_compose.c`
- `engine/src/myui/mycompose/my_compose_tree.h`
- `engine/src/myui/mycompose/my_compose_tree.c`
- `engine/src/myui/mycompose/my_compose_internal.h`
- `engine/tests/test_mycompose_tree.c`
- `.superpowers/sdd/2026-11-11-compose-mvi/task-1-report.md`

## TDD 证据

### 1. 缺 API / target RED

先写真实 `test_mycompose_tree.c` 并注册 `test_mycompose_tree`，此时尚无公共头或实现。

```sh
cmake -S engine -B build-compose-normal -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_BUILD_TESTS=ON -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-compose-normal --target test_mycompose_tree -j3
```

结果：configure 成功，build exit 2，按预期因缺 API 失败：

```text
Building C object CMakeFiles/test_mycompose_tree.dir/tests/test_mycompose_tree.c.o
engine/tests/test_mycompose_tree.c:3:10: fatal error:
  myui/mycompose/my_compose.h：没有那个文件或目录
compilation terminated.
gmake: *** [Makefile:1473：test_mycompose_tree] 错误 2
```

### 2. 公共声明 + `MY_COMPOSE_FAILED` stub 的行为 RED

随后补齐 brief 指定的公共类型、入口和 `mycompose` target；create stub 返回 NULL，其余 API 返回 `MY_COMPOSE_FAILED`（查询返回 NULL/0）。

```sh
cmake --build build-compose-normal --target test_mycompose_tree -j3
./build-compose-normal/test_mycompose_tree
```

结果：编译和链接成功，运行 exit 1；当时的 21 项测试全部行为失败，而非把编译成功当作功能证据：

```text
[1] lifecycle_insert_noop_and_delete ... FAIL: builder is NULL
...
[18] root_parent_and_build_state_validation ...
  FAIL: my_compose_tree_builder_begin(NULL) != MY_COMPOSE_INVALID
...
=== Results: 0 passed, 21 failed, 21 total ===
```

### 3. 实现与补充边界 RED

首个实现得到 20/21。唯一失败是测试手算 arena 上限少算了 value 自身的终止 NUL；修正测试期望为 65525 bytes 后得到 21/21，没有通过放宽生产检查来掩盖错误。

继续对同任务边界做组合验证，均先看到真实 RED 再修生产代码：

- 满 256 节点跨 parent：`add_node(... stack, "k0" ...) != MY_COMPOSE_OK`，21/22。原因是所有 slot 都被 current 占用；修复为只在无空闲 slot、当前 key 唯一且未被 next 保留时，以旧 slot 的新 generation 做 DELETE+CREATE，绝不保留旧 handle。
- 将相邻 A/B 交换钉住为一个最小 MOVE 后，原实现 `diff->count != 1u`；删除导致的自然位移也被误报为 MOVE。改为模拟工作顺序后通过。
- keyed reorder + CREATE + 固定位置 unkeyed：`finish(builder) != MY_COMPOSE_OK`，22/23。原因是 MOVE 模拟尚未先放置 CREATE；修复为模拟顺序与 diff 应用顺序一致，先放 CREATE，再只移动 keyed 保留节点。

### 4. 最终 focused GREEN

```sh
cmake --build build-compose-normal --target test_mycompose_tree -j3
./build-compose-normal/test_mycompose_tree
ctest --test-dir build-compose-normal -R '^test_mycompose_tree$' \
  --output-on-failure -j3
```

最终直接运行输出：

```text
[1] lifecycle_insert_noop_and_delete ... OK
[2] keyed_reorder_only_moves_and_preserves_handles ... OK
[3] mixed_keyed_and_unkeyed_nodes_keep_their_identity_rules ... OK
[4] mixed_reorder_with_create_keeps_unkeyed_fixed ... OK
[5] unkeyed_insert_uses_absolute_child_position ... OK
[6] type_change_is_delete_then_create_with_a_new_generation ... OK
[7] cross_parent_key_is_delete_then_create ... OK
[8] full_tree_cross_parent_replace_uses_a_new_generation ... OK
[9] duplicate_key_preflight_leaves_next_and_current_unchanged ... OK
[10] property_and_event_payloads_are_owned_and_update_diffs_are_granular ... OK
[11] message_payload_limit_and_stale_handles_are_checked ... OK
[12] node_and_child_link_capacity_is_exact ... OK
[13] depth_32_is_accepted_and_33_is_overload ... OK
[14] global_property_capacity_is_512 ... OK
[15] per_node_property_capacity_is_64 ... OK
[16] global_event_capacity_is_256 ... OK
[17] per_node_event_capacity_is_32 ... OK
[18] key_type_and_name_lengths_cannot_be_truncated ... OK
[19] string_arena_boundary_and_embedded_nul_are_not_truncated ... OK
[20] root_parent_and_build_state_validation ... OK
[21] diff_op_1024_is_accepted ... OK
[22] diff_op_1025_fails_without_publishing ... OK
[23] generation_near_overflow_never_wraps_and_retires_slot ... OK
=== Results: 23 passed, 0 failed, 23 total ===
```

focused CTest：

```text
1/1 Test #24: test_mycompose_tree .............. Passed
100% tests passed, 0 tests failed out of 1
Labels: compose, headless
```

## 接口与身份决策

- `MyComposeTreeBuilder` opaque；`begin` 清空 next 并允许重新构建，`end` 结束声明，`finalize` 是唯一发布入口。成功后仅交换 current/next 指针；失败时 current 与 slot 发布状态不变且 `diff.count == 0`。
- 首个节点必须是 parent 为零 handle 的 `@root`，之后拒绝第二个零-parent root；parent 必须已在同一份 next 中声明。`key == NULL` 或空 key 表示 unkeyed。
- keyed 只在同一 parent identity 内按 key + type 保留 handle；同 parent duplicate key 与 type 无关，并在节点、字符串 arena、slot 和输出 handle 修改前返回 `DUPLICATE_KEY`。
- 同 key 换 type、跨 parent 都为 DELETE+CREATE 和新 generation。unkeyed 只按直接子节点绝对位置匹配，position/type 规则不会被跨位置同 type 节点绕过。
- DELETE 按深度从深到浅、同深度按声明逆序；随后是声明顺序 CREATE、模拟顺序 MOVE、property/event UPDATE。
- MOVE 只针对 keyed 保留节点；删除或 CREATE 造成的自然位移不额外发 MOVE。相邻 A/B 交换产生一个 MOVE；keyed/unkeyed/CREATE 混合测试同时核对 handle、from/to index、diff 类型和顺序。
- `MyComposeDiffOp.name != NULL` 的 UPDATE 是 property/event 粒度；`on_event` 区分 event。新增、省略、payload/value 变化各产生 UPDATE，因此 1024/1025 diff op 边界由真实树操作到达，而非测试伪造计数。
- `MyComposeString.size` 不含终止 NUL；string value 复制后由树补 NUL。 sized string 中嵌入 NUL 返回 `MY_COMPOSE_INVALID`，超限返回 `MY_COMPOSE_OVERLOAD`，均不截断。key/type/name 按 C string 接收，64-byte 上限包含 NUL。
- event payload 是二进制 inline 复制，可含 NUL；读取时 owner 是当前节点 handle。property string 与 event payload 在调用后修改源 buffer 不影响树。
- `get_node/get_property/get_event` 读取 current；旧 handle 返回 `STALE`，不存在的 property/event 返回 `FAILED`。返回的字符串/payload/diff name 指针由 builder 所有，调用方不得释放，下一次 `begin` 后不得继续使用旧视图。
- 内部近溢出 seed 只声明在 `my_compose_internal.h`，不属于公共 tree API。replacement 在旧 generation >= `UINT32_MAX - 1` 时于发布前返回 OVERLOAD；删除到 `UINT32_MAX` 后永久退休 slot，不回绕。

## 固定容量与行为覆盖

- nodes 256（含 root）：256 成功，257 返回 OVERLOAD；同一场景以 root + 255 个直接子节点覆盖 255 child links。
- depth 32：32 层成功，33 层 OVERLOAD。
- properties：全局 512 成功、513 OVERLOAD；单节点 64 成功、65 OVERLOAD。
- events：全局 256 成功、257 OVERLOAD；单节点 32 成功、33 OVERLOAD。
- diff ops：真实 property/event rename + value update 组合达到 1024 成功；增加一个 value UPDATE 达到 1025，finalize OVERLOAD，current 保持原值且 diff count 为零。
- string arena：64 KiB 精确耗尽成功，多一个 byte OVERLOAD；嵌入 NUL、空 sized string、key/type/name 的 63-byte 内容与超长输入均覆盖。
- message payload：256 bytes 成功并逐字节验证，257 OVERLOAD。
- generation：近 `UINT32_MAX` replacement 原子失败、删除退休、后续创建不重用退休 index。
- 所有新公共函数均有行为断言，包括 create/destroy、begin/end/finalize、node/property/event、diff/count/getter 和内部 seed。

## 生产变异 / 恢复证明

每项都直接临时修改 `my_compose_tree.c`、重新构建并运行真实测试，然后恢复源码再跑 GREEN。变异时套件为 22 项；随后新增的第 23 项混合 CREATE/MOVE 回归也已在最终版本通过。

1. 忽略 type，强制同位置/key 直接 MATCH：
   - RED：19 passed / 3 failed。
   - 捕获测试：`unkeyed_insert_uses_absolute_child_position`、`type_change_is_delete_then_create_with_a_new_generation`、`generation_near_overflow_never_wraps_and_retires_slot`。
   - 恢复：22/22 GREEN。
2. keyed 查找从同 parent children 改为全树搜索，允许跨 parent 复用旧 handle：
   - RED：20 passed / 2 failed。
   - 捕获测试：`cross_parent_key_is_delete_then_create`、`full_tree_cross_parent_replace_uses_a_new_generation`。
   - 恢复：22/22 GREEN。
3. 在 duplicate 条件前加 `false &&`，跳过同 parent duplicate preflight：
   - RED：21 passed / 1 failed。
   - 捕获测试：`duplicate_key_preflight_leaves_next_and_current_unchanged`。
   - 恢复：22/22 GREEN，focused CTest 同时通过。

## 最终完整非图形回归与依赖检查

最终代码上重新执行，而非沿用修改前的全量结果：

```sh
cmake --build build-compose-normal -j3
ctest --test-dir build-compose-normal -LE "graphics|fuzz" \
  --output-on-failure -j3
```

结果：build exit 0，CTest exit 0。

```text
Built target mycompose
Built target test_mycompose_tree
100% tests passed, 0 tests failed out of 344
compose = 0.00 sec*proc (1 test)
headless = 48.21 sec*proc (182 tests)
Total Test time (real) = 25.20 sec
The following tests did not run:
  134 - test_d3d12_dependency_gate (Skipped)
```

`git diff --check` 通过。完整构建日志含既有 vendored Lua `tmpnam` linker warning，但无构建错误；focused 新目标无新增警告。

`mycompose` 没有 `target_link_libraries`，archive 仅包含 `my_compose.c.o` 与 `my_compose_tree.c.o`。`nm -u build-compose-normal/libmycompose.a`：

```text
my_compose.c.o:

my_compose_tree.c.o:
                 U calloc
                 U free
                 U memchr
                 U memcmp
                 U memcpy
                 U memset
                 U strcmp
```

生产代码只有 builder create/destroy 使用 `calloc/free`；begin/node/property/event/end/finalize/diff 全部使用双份固定存储和栈上固定工作数组，不链接 myui/RHI 或其它新库，也未使用 cry/game 领域名。

## 限制与后续

- 本任务没有 GPU、窗口、像素或声音证据；完整构建中的图形 target 只编译，CTest 明确排除 `graphics|fuzz`，不宣称 GPU 结果。
- 未运行 ASan/UBSan、TSan 或 fuzz；这些不是本 brief 要求的最终验证。steady-state 无 malloc 的证据是固定存储实现与符号/链接检查，不是 allocation-counter 运行证明。
- remember/store/myui adapter/C++ DSL 留待各自后续任务；本报告不扩展其实现或计划。
- 独立规格评审和质量评审由主代理随后安排。
