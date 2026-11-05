# P5 fix round 1 完整修复报告

分支：`cry-wave1-physics`
基线：`5bd73fe2`
范围：agent-178 的 2 Critical、6 Important、1 Minor，全部逐项 TDD 修复；未 push。

## 交付与提交

- `63535ac7` — body/constraint generation 句柄及所有有效调用者迁移。
- `1860bb9a` — 非有限 dt/body/vehicle 输入在任何状态写入前原子拒绝。
- `4dade0fa` — cone twist 在当前 A-local 坐标系中分解和投影。
- `1775e075` — 布娃娃中途失败的完整世界快照回滚，含 tombstone generation。
- `7c065ff2` — 约束删除、稳定接触和非零约束速度的休眠一致性。
- `821076e6` — chassis 局部坐标转向、制动和有效横摆惯性。
- `cd6ad5a5` — 多 ragdoll 共享 IK 的所有权计数。
- 最终文档/报告提交见分支最后一次 `git log`。

公共 API 使用 `{index,generation}` 的 `PhysicsBodyHandle` 和 `PhysicsConstraintHandle`。BVH/Contact 的当步 slot 仍是纯内部索引，不提供旧裸 id 变更入口。Rope、cloth、soft body、destructible、ragdoll、vehicle、Lua、scene 与 main 均显式迁移。

## 每项 RED / GREEN 与测试文件

### Critical 1 — stale 身份

文件：`test_physics_identity.c`、`test_ragdoll.c`、`test_vehicle.c`、`test_character.c`、`test_rope.c`、`test_cloth.c`、`test_soft_body.c`、`test_destructible.c`、`test_script_lua.c` 及既有约束测试。

- 旧 constraint 删除复用槽和 park 后旧图绑定新 occupant：`0 passed, 2 failed`。
- 旧 ragdoll deactivate：`6 passed, 1 failed`；旧 vehicle destroy：`5 passed, 1 failed`。
- 修复后 identity `2/2`，ragdoll/vehicle `2/2` CTest；完整消费者 focused `14/14`，`engine` 目标编译通过。
- Lua 保留原数字 id ABI：首次创建仍为 1、2、3；slot 复用使用新 serial，并同时校验 serial 与 generation。Lua 回归 `25/25`。

### Critical 2 — 非有限输入

文件：`test_physics.c`、`test_vehicle.c`。

- RED：普通物理 `74 passed, 3 failed`，vehicle `6 passed, 1 failed`。
- dt、position、extent、mass、shape、pose、impulse、push 与 vehicle create/step 的 NaN/±Inf 均前置拒绝；快照和 caller 对象不变。
- GREEN：普通物理 `77/77`、vehicle `7/7`；FLT_MAX mass 与 FLT_MIN dt 对照保持有限。负有限 extent 保留 clamp。

### Important 1 — cone twist 坐标系

文件：`test_physics_cone_twist.c`。

- 旋转动态 A、双动态端和组合 swing/twist：`7 passed, 1 failed`，45° twist 未夹到 20°。
- 统一当前 A-local 相对旋转与投影后：`8/8`，并裁剪界外相对角速度。

### Important 2 — 布娃娃事务回滚

文件：`test_ragdoll.c`、`physics.c`（仅 `test_ragdoll` 编译的失败计数钩子）、`CMakeLists.txt`。

- 链接 RED：失败注入入口不存在。加入测试专用钩子后，4 组中途失败完整世界快照不相等。
- 覆盖第 1/2/3 个骨体失败和第 1/2 个约束失败；第一次创建失败无副作用。
- 直接恢复受影响 slot、count 与 `bvh_dirty`，不使用会产生二次副作用的 park 回滚。加入既有 tombstone 后，其 generation 和全部字段也恢复。
- GREEN：ragdoll `8/8`，随后共享 IK 后 `9/9`。

### Important 3/4 — 销毁、接触和速度休眠

文件：`test_physics.c`。

- RED：约束删除不醒、持续地面接触不睡、纯速度约束不醒，`77 passed, 3 failed`。
- 中间证据：接触不断将 rest 清零，且慢速墙接触将最终速度消零，导致两类相反误判。
- 统一 step 末评估，并保留碰撞前相对速度与法线：重力支撑可休眠，非支撑运动接触和纯速度修正唤醒。
- GREEN：普通物理 `80/80`，地面支撑与 0.04 m/s 穿墙回归同时通过。

### Important 5 — 载具坐标与有效惯性

文件：`test_vehicle.c`、`physics.c`、`vehicle.c`。

- 底盘旋转 90° 后接地转向、制动和抓地：`8 passed, 1 failed`。
- 改为绕 chassis up 转向、按该轴有效逆惯性判断并按 chassis forward 制动后，主场景转绿。
- 零惯性对照随后暴露四元数归一化产生的 `3.55e-15` 伪非零重量，使用 `1e-12` 数值容差后 `9/9`。
- 零有效横摆惯性保持锁定，非零惯性正常转向。

### Important 6 — 多 ragdoll 共享 IK

文件：`test_ragdoll.c`、`animation.c`、`animation.h`、`ragdoll.c`、`ragdoll.h`。

- 两个 ragdoll 共享 IK，A→B/B→A 两种停用顺序：`8 passed, 1 failed`。
- acquire/release 计数分离于手动挂起；中途始终屏蔽 IK，最后一次停用才恢复。
- GREEN：ragdoll `9/9`、animation `37/37`。

### Minor

删除 `docs/design/physics_extended.md` 行尾空格，最终提交内容通过 `git diff --check`。

## 生产变异证据

变异均临时修改生产实现、构建运行，然后恢复；未提交变异体。

- 绕过 constraint generation：identity `1 passed, 1 failed`，旧 remove 删除新约束。
- twist 投影改回世界轴：cone `7 passed, 1 failed`，旋转 A 场景误差约 0.516 rad。
- 跳过布娃娃 body slot 恢复：4 组中途失败快照变红，最终 `8 passed, 4 failed`（当时含共享 IK 测试）。
- world Y 转向：vehicle `8 passed, 1 failed`。
- IK release 直接清零：共享 IK `8 passed, 1 failed`。
- 禁用实际唤醒函数：普通物理 `78 passed, 2 failed`，运动接触与纯速度约束均未唤醒。

恢复后 normal、ASan+UBSan、TSan focused 均重新通过。

## 三 lane 最终验证

所有构建均使用 `-j3`，target 为：

`test_physics test_physics_identity test_physics_hinge test_physics_slider test_physics_cone_twist test_vehicle test_ragdoll test_animation test_character test_rope test_cloth test_soft_body test_destructible test_script_lua`

CTest 选择：

```bash
-R 'test_physics$|physics_identity|physics_hinge|physics_slider|physics_cone_twist|test_ragdoll|test_vehicle|test_character|test_rope|test_cloth|test_soft_body|test_destructible|test_script_lua|test_animation$' --output-on-failure
```

- `build-physics-normal`：`14/14` 通过，0 失败；`engine` 目标同时构建通过。
- `build-physics-asan`（`ENGINE_USE_ASAN=ON`、`ENGINE_USE_UBSAN=ON`）：`14/14` 通过，无 ASan/LSan/UBSan 报告。
- `build-physics-tsan`（`ENGINE_USE_TSAN=ON`）：`14/14` 通过，无 ThreadSanitizer 报告。

热路径检查：`physics_step`、约束求解、`vehicle_step`、ragdoll 写出只使用内嵌数组或定长栈。分配仅为既有 `physics_world_create/destroy` 和 Lua bind/shutdown 的固定容量映射，不在上述热路径发生。

## 限制

- 轮子仍为射线接触实体，不是独立刚体；不含高级轮胎、轮体侧壁或转动惯量模型，sweep 精度沿用现有 AABB 查询。
- 布娃娃最多 32 骨，假定可分解、非剪切 TRS 绑定；没有自动人体骨生成或专用自碰撞过滤组。
- 线性约束速度仍使用现有质心速度模型，不是完整接触/关节耦合张量求解器。
- 证据范围为 Linux/GCC focused 非图形测试，未声称全仓、Windows、真机 GPU 或交互视觉验收。

---

# P5 fix round 2 完整修复报告

- 日期：2026-11-05
- 基线：`b71f1571`
- 关键实现提交：`a8bf403f`（`physics: close identity and Lua allocation gaps`）
范围：`review-fix1-findings.md` 的全部开放项；round 1 已 ADDRESSED 的七项由同一 focused 套件回归，未 push。

## main 持久身份与真实编译阻断

- RED：`cmake --build build-physics-normal -j3 --target engine_demo` 在 `main.c:317-323` 失败，`PhysicsBodyHandle` 被直接用作数组下标并与整数比较，真实复现 reviewer 的 New Critical 1。
- transform 同步改为先 `physics_body_resolve`，只通过解析后的 body 和 `pid.index` 访问派生插值数组；stale 身份跳过。
- dangling 创建、live-set、elevator、编辑/调试/布局/克隆等持久消费者统一 resolve。dangling 路径明确重建，live-set 只收录可解析身份，其余 stale 路径跳过；最终复核还修正了克隆路径 resolve 后未检查空指针的问题。
- GREEN：normal、ASan+UBSan、TSan 三棵树的 `engine_demo` 均实际编译并链接成功，不再只构建不含 `main.c` 的 `engine` 库。

## revive、scene 与 generation 耗尽

文件：`engine/src/physics/physics.[ch]`、`engine/src/main.c`、`engine/tests/test_physics_identity.c`、`engine/tests/test_scene_state.c`。

- `physics_body_revive` 对 live 和 parked tombstone 统一要求 generation 完全一致，删除 parked 的 stale 旁路。
- scene/main 恢复显式从当前 tombstone 构造 `{index,current_generation}`；若 slot 已有新 occupant 或已退休则跳过，不借旧所有者身份恢复。
- body/constraint generation 到达 `UINT32_MAX` 后返回退休标记而不是 1；`retired` slot 不参与创建复用，resolve/revive/remove 拒绝退休身份，旧 `{slot,1}` 不会因回绕重新有效。
- RED/变异证据：恢复 parked 任意 generation 旁路时 identity `3 passed, 1 failed`，旧 handle 被错误接受；把耗尽后的 generation 改回 1 时同样 `3 passed, 1 failed`，退休断言失败。
- GREEN：`test_physics_identity` `4/4`，覆盖旧 tombstone 拒绝、当前 tombstone 可恢复及 body/constraint 近上限退休。`test_scene_state` `11/11`，覆盖当前 tombstone 的正常场景恢复；scene 原本已显式使用当前 generation，因此该项是既有正确行为的表征测试，不虚构独立 RED。

## Lua rebind、serial 与 spawn 原子性

文件：`engine/src/script/script_lua.[ch]`、`engine/tests/test_script_lua.c`。

最终夹具 RED：`test_script_lua` 为 `24 passed, 7 failed, 30 total`，实际覆盖：

- 容量 1 时 `2^32+1` 的 serial 截断为 0 后错误操作 body 0。
- 不同 world rebind 和 NULL/失败 rebind 后，serial 0 raw id 被重新采用；同一 world 重绑则必须继续有效。
- serial 到 `UINT32_MAX` 后回绕并返回旧 id 1。
- 映射不可用及 public id 超过 `0x1FFFFFFFFFFFFF` 时，创建后 park 改变完整世界快照。

实现：

- 同一 world/capacity 且映射完整时，rebind 保留 serial/generation/epoch/retired 数组。换 world、解绑或失败重绑会重建映射并推进 map epoch；只有 epoch 1 的初始映射允许未登记 serial 0 的 legacy raw id adoption，之后必须由当前映射显式发号。
- 所有 body API 同时检查 serial、map epoch 和底层 generation；输入 serial 先以 `u64` 检查，超过 `UINT32_MAX` 直接拒绝，不能截断回绕。
- spawn 在 `physics_body_create` 前镜像其“首个可复用 parked slot，否则 `pw->count`”选择，检查四个映射数组、容量、物理/映射退休状态、serial 和 public id 上限。
- 未登记 serial 从 0 开始，已登记 serial 到 `UINT32_MAX` 后退休映射 slot；public id 超限时同样退休并返回 0，均在 body 创建前结束。
- 预检成功后只进行确定性 serial/generation/epoch 提交；`physics_body_create` 自身失败返回 0，不再用 park 充当回滚。
- 原子测试比较完整 `PhysicsWorld` 和整个 body 数组。public id 边界使用真实 `capacity = 2^21+1`，避免把 51 位 serial 截断为 `u32` 后形成假测试。
- GREEN：`test_script_lua` `30/30`；shutdown 释放全部四个映射数组。

## 本轮生产变异

变异均临时修改生产代码、实际构建运行并恢复，未提交变异体。

- 删除“只有首次映射可 adoption”门禁：Lua `28 passed, 2 failed`，不同 world 与失败 rebind 均重新接受 raw id。
- 删除已登记 serial 耗尽检查：Lua `29 passed, 1 failed`，第二次分配返回旧 id 1。
- generation 耗尽改回 1：identity `3 passed, 1 failed`。
- revive 恢复 parked generation 旁路：identity `3 passed, 1 failed`。

恢复后执行下述三 lane 和 `engine_demo` 验证。

## 三 lane 与 engine_demo 最终验证

所有构建和 CTest 均使用 `-j3`。在 round 1 的 14 个目标外加入 `test_scene_state`，CTest 正则额外包含 `test_scene_state$`；每个 lane 还单独执行对应目录的 `cmake --build ... -j3 --target engine_demo`。

- `build-physics-normal`：focused `15/15`，0 失败；`engine_demo` 编译链接成功。
- `build-physics-asan`（ASan+UBSan）：focused `15/15`，0 失败，无 ASan/LSan/UBSan 报告；`engine_demo` 编译链接成功。
- `build-physics-tsan`：focused `15/15`，0 失败，无 ThreadSanitizer 报告；`engine_demo` 编译链接成功。
- `git diff --check` 无错误。最终提交和工作树状态见本节之后的提交记录/交付回报。

## 限制

- 轮子仍为射线接触实体，不是独立刚体；不含高级轮胎、轮体侧壁或转动惯量模型，sweep 精度沿用现有 AABB 查询。
- 布娃娃最多 32 骨，假定可分解、非剪切 TRS 绑定；没有自动人体骨生成或专用自碰撞过滤组。
- 证据范围为 Linux/GCC focused 非图形测试及真实 `engine_demo` 构建；未运行全仓测试，未做 Windows、真机 GPU 或交互视觉验收。
