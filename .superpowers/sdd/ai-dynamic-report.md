# P3 动态 AI 交付报告

## 状态

已在 `cry-wave1-ai` 完成动态 AI 实现、 focused 回归、变异检查、自审和本地提交。未修改 master、其他子项目或 `docs/Implementation_Status.md`，未 push、未创建 PR。

实现位于既有 `break_ai`，没有新增平行导航系统或 RHI 依赖。`BreakAiRuntime` 借用既有 mesh，在创建时分配全部容量和 A* 工作区；GameThread owner 之外的 runtime 调用返回 `REJECTED`。

## 交付内容

- 动态障碍：XZ 矩形按 base-poly 中心栅格化；每个 poly 使用重叠阻挡计数；add/update/remove 真实改变共享 A* 的可达区域。
- 导航失效：版本从 1 开始随有效障碍变化递增；旧 expected version 返回 `STALE`；缓存键包含版本、start、end；旧 `BreakAiPath` 可用 `break_ai_path_is_current` 拒绝。
- 查询行为：动态整墙返回 `FAILED`，移除后重新开路；失败不改变输出；重叠障碍不会提前重开。
- 无分配热路径：旧 `break_nav_find_path` 与动态查询共用 `break_nav_find_path_workspace`，工作区在 bake/runtime create 时分配；源码合同拒绝查询、障碍、agent、编组、预约和速度避障热文件中的堆分配。
- 速度避障：固定 35 候选、horizon 内相对速度最近距离评分、最大速度限制、16 邻居硬上限；agent runtime 确定性选择最近 16 个邻居。
- 编组：固定成员顺序和 generation 句柄，确定性 wedge 槽位；跟随复用 `break_nav_follow_wish`，输出限速且可重放。
- 智能对象：固定容量、单预约者、同者幂等、异者竞争/错误释放拒绝、释放后转移、stale generation 拒绝。
- 原子性：agent/障碍/编组/智能对象容量及非法输入均在写状态前失败；持有预约或属于编组的 agent 不能直接被移除。

主要文件：

- `engine/src/ai/break_ai.h`
- `engine/src/ai/break_ai_runtime.c`
- `engine/src/ai/break_ai_obstacle.c`
- `engine/src/ai/break_ai_query.c`
- `engine/src/ai/break_ai_agent.c`
- `engine/src/ai/break_steer_velocity.c`
- `engine/src/ai/break_ai_formation.c`
- `engine/src/ai/break_ai_smart_object.c`
- `engine/src/ai/break_nav_workspace.c`
- `engine/src/ai/break_nav_query.c`
- `docs/design/ai_dynamic.md`
- `docs/superpowers/plans/2026-11-02-ai-dynamic.md`

## TDD RED / GREEN 证据

1. 热路径合同先 RED：`break_nav_query.c allocates in a query hot path`。工作区重构后旧 AI 测试和合同 8/8 GREEN。
2. 动态 API 最初因类型/函数缺失编译 RED；加入最小桩后行为 RED 为 0/6，失败点为真实路径、障碍创建、容量和 owner 拒绝。实现后动态查询与回归 3/3 GREEN。
3. 速度避障与 agent 最小桩行为 RED 分别为 0/4、0/2。首次实现后相对速度符号错误仍使 steer 1/4；根因是相对位置与相对速度采用不一致方向，修正后 steer/agent/合同 4/4 GREEN。
4. 编组最小桩行为 RED 为 0/3；实现后编组/follow/agent/合同 4/4 GREEN。
5. 智能对象最小桩行为 RED 为 0/2；实现后完整 normal focused 14/14 GREEN。

## 变异检查

所有变异均单独临时修改、用 `-j3` 重建、看到预期 RED 后恢复，未提交 mutant：

| 变异 | 结果 |
| --- | --- |
| 非零旧导航版本绕过 `STALE` 检查 | 动态套件 1/6 失败；旧版本查询断言变红 |
| A* 跳过动态阻挡邻居检查 | 动态套件 3/6 失败；整墙和重叠障碍场景出现错误路径 |
| 竞争 reserve 覆盖原 owner | 智能对象套件 1/2 失败；竞争拒绝断言变红 |
| 障碍容量满由 `OVERLOAD` 改为 `STALE` | 动态套件 1/6 失败；容量错误及原子性断言变红 |

容量变异故意改变错误合同而不是越过数组边界，避免以越界写入作为验证手段。恢复后 normal focused 再次 14/14 GREEN。

## 最终验证

所有构建均使用 `-j3`。

### Normal

```bash
cmake --build build-ai -j3 --target \
  test_break_nav_bake test_break_nav_query test_break_nav_follow \
  test_break_perception test_break_behavior test_break_steer \
  test_break_ai_dynamic test_break_steer_velocity test_break_ai_agents \
  test_break_ai_formation test_break_ai_smart_object test_cry_style_prototype
ctest --test-dir build-ai \
  -R 'break_ai|test_break_nav|test_break_steer|test_break_perception|test_break_behavior|test_cry_style_prototype' \
  --output-on-failure
```

结果：14/14 通过。包含六个旧 AI 测试、五个新行为测试、两个 AI 合同和 `test_cry_style_prototype`。

### ASan+UBSan

```bash
cmake -S engine -B build-ai-asan -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_ENABLE_IPO=OFF -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON
cmake --build build-ai-asan -j3 --target \
  test_break_nav_bake test_break_nav_query test_break_nav_follow \
  test_break_perception test_break_behavior test_break_steer \
  test_break_ai_dynamic test_break_steer_velocity test_break_ai_agents \
  test_break_ai_formation test_break_ai_smart_object test_cry_style_prototype
ctest --test-dir build-ai-asan \
  -R 'break_ai|test_break_nav|test_break_steer|test_break_perception|test_break_behavior|test_cry_style_prototype' \
  --output-on-failure
```

结果：14/14 通过，无 ASan/UBSan 报告。

### TSan

```bash
cmake -S engine -B build-ai-tsan -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_ENABLE_IPO=OFF -DENGINE_USE_TSAN=ON
cmake --build build-ai-tsan -j3 --target \
  test_break_nav_bake test_break_nav_query test_break_nav_follow \
  test_break_perception test_break_behavior test_break_steer \
  test_break_ai_dynamic test_break_steer_velocity test_break_ai_agents \
  test_break_ai_formation test_break_ai_smart_object test_cry_style_prototype
ctest --test-dir build-ai-tsan \
  -R 'break_ai|test_break_nav|test_break_steer|test_break_perception|test_break_behavior|test_cry_style_prototype' \
  --output-on-failure
```

结果：14/14 通过，无 TSan 报告。

### 无测试生产目标

```bash
cmake -S engine -B build-ai-notests -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_ENABLE_IPO=OFF -DENGINE_BUILD_TESTS=OFF
cmake --build build-ai-notests -j3 --target break_ai
```

结果：`libbreak_ai.a` 构建成功，确认测试开关不影响 formal library 注册。

## 自审

按续作要求对 `48e64a2a..5f351c8a` 的全部 23 个文件做只读自审，检查导航版本/缓存键、阻挡计数对称性、失败输出、容量边界、generation、owner、槽位数组索引和 RHI/核心消费者边界。未发现 Critical 或 Important，未因自审改变生产代码。当前子代理环境没有 Agent 工具，因此没有独立 reviewer 结果；此处只声明实际完成的自审。

`git diff --check 48e64a2a..HEAD` 通过，分支差异仅包含 P3 设计、计划、`break_ai` 实现和测试。

## 提交

- `933cc769` — `docs: design dynamic AI runtime`
- `1cb159b5` — `ai: preallocate navigation query workspace`
- `d7c48127` — `ai: add versioned dynamic navigation`
- `4fece340` — `ai: add velocity avoidance and agent registry`
- `5e45c11a` — `ai: add deterministic formation following`
- `5f351c8a` — `ai: add smart object reservations`
- 最终文档/报告提交以分支 HEAD 为准。

## 限制

- 动态障碍是多边形中心栅格化覆盖层，不是任意连续形状的精确侵蚀；agent 半径仍由基础 bake 处理。
- 局部避障是固定候选集上的有界最优选择，不提供极度拥挤场景的全局无死锁保证。
- 编组 tick 确定性趋向槽位，不为每个槽位自动规划独立 A* 路径；调用方可组合版本化路径和局部避障。
- 智能对象为单预约者，不含等待队列。
- 本轮按 focused 范围验证，未运行全仓所有非图形测试、Windows 构建或真机图形测试。
- 未进行独立 reviewer 评审；原因是当前工具集无 Agent，不能将此限制描述为评审已通过。
