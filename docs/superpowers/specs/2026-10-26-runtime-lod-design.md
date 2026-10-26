# 运行时 LOD 设计（第二版，待确认）

状态：**一期已实现**（R701，见 `docs/Implementation_Status.md`；与本设计的差别记录在那里）；**二期 2.1（ECS 实例化静态网格）已实现**（R702，见第 8 节）；**二期 2.2 抖动交叉淡入淡出：ECS 实例化与 mega 路径均已实现（R703a/R703b）**；**二期 2.3 简化级别磁盘缓存已实现（R704，默认关闭，`BREAK_LOD_CACHE=<directory>` 启用）**。阴影级别 +1 已做伪影排查（R706：三后端近/中距、低太阳下无可见痤疮/漏光，保留固定 bias，见下文阴影级别一段的附注）。以下为设计原文。 第一版（同名文件的上一次提交）经代码复核后发现若干错误与遗漏，本版逐条修正（见第 0 节）；减面按用户要求改为**纯 C 实现**（移植 meshoptimizer 的简化器，第 4 节）。

## 0. 第一版的问题清单（复核结果）

按严重程度排序。「已核实」表示在代码里确认过。

| # | 问题 | 性质 | 本版处理 |
|---|---|---|---|
| 1 | **「着色器一行都不用改」不成立。** `unified_cull.comp` 是按 `obj_count` 个对象各写一个可见标志、各追加一条命令，**对象 i 必须对应命令 i**（着色器注释原文）。每个节点有多条级别命令后，对象表要么跟着变成「每条命令一项」，要么着色器要能「对象 → 选中命令」。第一版只考虑了 compact 路径，漏了 unified 路径。（已核实） | 设计错误 | 第 3.3 节：对象表改为每条命令一项（同一节点的各级共享包围球），可见性 = 剔除结果 AND CPU 写的级别掩码；`unified_cull` 增加一个只读掩码缓冲（GLSL/VK/HLSL 三份各加约 3 行）。 |
| 2 | **flags-only 路径有一帧延迟。** `mega_unified_vis_flags`（R169）读的是**上一帧**的 GPU 可见标志（「Read previous-frame staging」）。第一版写「叠加级别掩码再上传」，但标志是 GPU 产生、CPU 回读的，级别掩码若在 CPU 上叠加，用的是上一帧的剔除结果加本帧的级别，两者会在一帧内不一致（物体刚进入视野时那一帧，旧级别命令可见、新级别不可见，会闪一帧空洞）。（已核实） | 设计错误 | 第 3.3 节：掩码在 GPU 上与本帧剔除结果相与，不在 CPU 叠加；回读的标志按「节点」而不是「命令」去解释。 |
| 3 | **命令上限写错了一处。** 第一版说 N=200×3=600 条命令「没超过前两项」，但同时依赖 `MEGA_DIRECT_MAX_DRAWS = 64`：超过后 R688/R691 的直接阴影路径整体关掉，阴影会退回逐面 GPU 剔除，**性能会倒退**。（已核实） | 遗漏 | 第 5 节：直接阴影路径的命令表改为按需分配，上限与 `MEGA_MAX_CMDS` 统一；压力场景下仍走直接路径。 |
| 4 | **CPU 剔除路径的标志按「节点」写。** `g_draw_vis[ci] = g_node_vis[ni]` 和 `g_vis_flags[ci] = g_node_vis[ni]`（`main.c` 前向/延迟各 2 处）用 `cmd_node_index[ci]` 从节点映射到命令。多级后 `cmd_node_index` 一对多，这几处天然能工作，但要额外乘上「这条命令是不是选中级别」。第一版没列出这 4 处。（已核实） | 遗漏 | 第 3.3 节：统一由一个 `mega_cmd_selected(mb, ci)` 判断。 |
| 5 | **材质分组表按命令建。** `cmd_mat_group[]`、`group_cmd_offsets[]`、`group_cmd_list[]`（R437 的 per-group compact）在 bake 时按命令建立；多级后命令数翻 3 倍，分组区间与容量都要跟着按命令算。`mega_mat_groups_draw` 用 `group_cmd_list[ci]` 重排可见标志。（已核实） | 遗漏 | 第 3.2 节：bake 时把各级命令视为普通命令放进同一个材质组，分组逻辑不改，只是条目变多。 |
| 6 | **LOD 选择用的距离与剔除用的球心不一致。** 非 mega 前向路径里，选级用 `world_transform.e[3]`（节点原点），剔除用 `node_spheres[]`（包围球心）。原点可以离几何很远（glTF 常见），选级会偏。（已核实） | 缺陷 | 第 3.4 节：统一用包围球心算距离。 |
| 7 | **屏幕占比策略更合适，第一版选了距离。** 距离阈值与物体大小无关：一个 0.5 m 的杯子和一栋 50 m 的楼用同一个 80 m 阈值显然不对。现有 `lod_compute_screen_fraction` 已经写好。 | 设计不佳 | 第 3.4 节：默认改为屏幕占比；阈值按「相对 LOD0 的几何误差 ≤ 1 像素」推导，而不是拍一个距离。 |
| 8 | **没有 LOD 生成与误差的对应关系。** 第一版只说「每级 50% 面数」。按目标面数减面得到的误差是不可控的；正确做法是 meshoptimizer 返回的 `result_error`（相对网格尺寸的几何误差），用它决定切换时机。 | 设计不佳 | 第 3.4 节：每级保存 `error`（世界空间），切换条件为 `error × 投影比例 ≤ 像素阈值`。 |
| 9 | **内存估算偏乐观且未对比可选方案。** 「多 87%」只算了顶点；索引同样翻倍。更省的做法是**所有级别共享 LOD0 的顶点、只存不同的索引**——这正是 meshoptimizer `simplify` 的工作方式（输出是原顶点的索引子集）。 | 优化缺失 | 第 3.2 节：各级共享 LOD0 顶点，只追加索引。内存增量降到约「索引 × 0.75」（3 级时），顶点 0 增量。 |
| 10 | **退化与边界情况未列。** 小网格（< 几百三角形）减面意义不大；退化面、非流形、开放边界、UV 接缝、硬边（法线不连续）需要锁定；减面结果比目标差很多时（`result_error` 超阈值）应放弃该级。 | 遗漏 | 第 4.3 节。 |
| 11 | **加载时间。** 运行时在加载阶段对每个网格减面会拖慢启动；第一版没估算，也没提缓存。 | 遗漏 | 第 4.4 节：估算 + 结果缓存（按网格内容哈希）。 |
| 12 | **蒙皮网格（skinned）不进 mega 路径**（`if (!nd->has_mesh || nd->skinned) continue;`），第一版没说明 LOD 是否覆盖它们。（已核实） | 遗漏 | 第 2 节非目标：一期不覆盖蒙皮网格。 |
| 13 | **阴影与相机用同一级别**写成约束，但阴影级别其实可以更低（阴影贴图分辨率低，CSM 远级联尤其如此），这是常见优化。 | 优化缺失 | 第 3.5 节：阴影级别 = 相机级别 + `shadow_bias`（默认 +1，不超过最低级），可关闭。 |
| 14 | **验证方案没覆盖「选级跳变」的视觉问题和迟滞参数**，也没有测 CPU 选级本身的耗时。 | 遗漏 | 第 7 节。 |
| 15 | **meshoptimizer 依赖**：用户要求纯 C。 | 需求变化 | 第 4 节：移植为纯 C。 |

## 1. 目标与非目标

目标：作为**引擎能力**，在运行时按物体在屏幕上的大小选择较低细节的网格，降低大场景里的顶点/三角形处理量。

非目标：
- 不以演示场景的帧率为目标。2026-10-26 测得，即使演示里整个场景网格都不画，帧率上限也只有 D3D12 +2.1%、GL +5.2%、VK +3.4%（约 1.7 万三角形，瓶颈在 pass 数、阴影 pass 与填充）。**验收只看压力场景**（第 7 节）。
- 不做 mesh shader / 虚拟几何、HLOD（多物体合并代理）、impostor。
- 一期不覆盖：蒙皮网格（不进 mega 路径）、ECS 实例化物体（第 8 节二期）、glTF 自带 `MSFT_lod`（二期）。

## 2. 现状（已在代码里确认）

| 项目 | 现状 |
|---|---|
| `renderer/lod.{c,h}` | `LODGroup`（最多 4 级 `meshes[]` / `thresholds[]`）、`lod_select`（距离或屏幕占比，带迟滞和全局 bias）、`lod_update_all`、`lod_group_set_auto_thresholds`；`test_lod` 约 20 个用例。 |
| 注册 | 启动时每个静态场景节点注册成 1 级组（`level_count = 1`）。 |
| 选级结果 | 非 mega 前向路径调用 `lod_select` 后 `(void)lod_level` 丢弃；只用 `thresholds[0] × 2` 做距离剔除。 |
| mega 路径（默认） | 静态、非蒙皮节点在启动时一次性烘焙进合并 VBO/IBO（顶点已变换到世界空间，`MegaVert = {pos[3], nrm[3], uv[2]}`）；每个节点 1 条 `DrawIndexedIndirectCmd`。 |
| 消费命令表的路径 | ① `unified_cull.comp`（对象 i ↔ 命令 i，GPU 剔除并追加）；② flags-only 模式（R169，回读上一帧标志）；③ R437 分组 compact（`cmd_mat_group` / `group_cmd_list`）；④ R441 材质数组路径（`first_instance` = 数组层）；⑤ R688/R691 CPU 直接阴影路径（`direct_cmds[]`，上限 64）；⑥ 前向/延迟的 CPU 节点剔除写 `g_draw_vis` / `g_vis_flags`（4 处）。 |
| 上限 | `GPUCULL_MAX_OBJECTS = 4096`；CPU 数组 16384；`MEGA_DIRECT_MAX_DRAWS = 64`。 |
| 减面 | 无。 |

## 3. 设计

### 3.1 总体

- **选级在 CPU**：每帧对每个节点计算屏幕占比、调用 `lod_select`（带迟滞），结果写入一个**每节点级别数组** `lod_level[node]`。节点数在千级，CPU 耗时微秒级（第 7 节要求实测）。
- **剔除结果与级别相与**：每条命令带一个「是否为本帧选中级别」的标志 `selected[cmd]`，由 CPU 每帧上传（小缓冲，`命令数 × 4 B`）。GPU 端最终可见 = 视锥/遮挡结果 AND `selected[cmd]`。

### 3.2 数据布局：共享顶点、按级别追加索引

- 烘焙时 LOD0 的顶点照常写入 mega VBO。各简化级**不写顶点**，只把简化后的索引（引用 LOD0 的顶点）追加到 mega IBO。
- 每个节点 `L` 级 → `L` 条命令：`first_index` 各不相同，`vertex_offset` 相同（都是 LOD0 那段顶点的基址；R687 修过的「顶点偏移被加两次」那类错误要专门测试，第 7 节）。
- 新表：`MegaBuffer.node_cmd_base[node]`、`node_level_count[node]`、`cmd_level[cmd]`、`cmd_node_index[cmd]`（已有，改成一对多）。
- 所有级别的命令放进节点原来的材质组（`cmd_mat_group`），R437 分组 compact 与 R441 材质数组路径**逻辑不改**，只是条目变多。
- 可选的进一步优化：简化级的索引做一次顶点缓存优化（第 4.2 节移植范围里包含）。

内存：3 级、每级约为上一级 50% 时，索引增量约 0.75 × LOD0 索引，顶点增量 0。对比第一版的「顶点+索引各 +87%」节省明显。

### 3.3 各消费路径的改法（对应第 2 节 ①–⑥）

| 路径 | 改法 |
|---|---|
| ① `unified_cull.comp` | 对象表改为**每条命令一项**（同节点各级共享同一包围球），保持「对象 i ↔ 命令 i」不变。新增只读缓冲 `selected[]`（binding 5）：`if (selected[idx] == 0) { flags[idx] = 0; return; }`，放在视锥测试之前，省掉未选级别的测试。GLSL / VK / HLSL 三份各加约 3 行。 |
| ② flags-only（R169） | 同 ①，掩码在 GPU 上生效，不在 CPU 叠加；回读的标志按命令保存，CPU 侧消费前按 `cmd_node_index` 折回节点（某节点任一级可见即该节点可见），保证一帧延迟语义与现在一致。 |
| ③ R437 分组 compact | 不改着色器；CPU 写 `g_vis_flags[ci]` 时乘上 `selected[ci]`。 |
| ④ R441 材质数组 | 同 ③。 |
| ⑤ 直接阴影（R688/R691） | `mega_draw_direct_culled` 里每个节点只画 `node_cmd_base + shadow_level(node)` 那一条。命令表改为按需分配，上限并入 `MEGA_MAX_CMDS`（第 5 节）。 |
| ⑥ CPU 节点剔除（4 处） | `g_draw_vis[ci] = g_node_vis[ni] && mega_cmd_selected(mb, ci)`。 |

### 3.4 选级：屏幕占比 + 几何误差

- 默认策略改为**屏幕占比**（`lod_set_strategy(true)`）。
- 每个简化级保存减面器返回的**世界空间几何误差** `error[level]`（meshoptimizer 的 `result_error` 是相对网格尺寸的值，乘以 `meshopt_simplifyScale` 得到世界单位）。
- 切换条件：`error[level] × (屏幕高度像素 / (2 · d · tan(fov/2))) ≤ LOD_PIXEL_ERROR`（默认 1.0 像素），取满足条件的最低细节级。这是「屏幕上的几何误差不超过 1 像素」，比按距离或按面数比例拍阈值更稳定，与物体大小无关。
- 距离 `d` 用**包围球心**（修第 0 节 #6），不用节点原点。
- 迟滞：沿用 `lod_select` 现有的迟滞带；参数在压力场景里调（第 7 节）。
- `BREAK_LOD=0` 完全关闭（始终 LOD0，所有路径行为与现在一致）；`BREAK_LOD_PIXEL_ERROR=x` 调阈值；调试 UI 显示各级节点数与三角形数。

### 3.5 阴影级别

阴影 pass 用 `min(相机级别 + LOD_SHADOW_BIAS, 最低级)`，默认 `LOD_SHADOW_BIAS = 1`；`BREAK_LOD_SHADOW_BIAS=0` 时与相机级别一致。理由：阴影贴图分辨率远低于屏幕（点光 512²、CSM 每级联一个象限），多降一级通常不可见，而阴影 pass 在本引擎里次数多（4 级联 + 24 个点光面）。若出现可见的「阴影漏光 / 自阴影痤疮」，再改为与相机一致。

> R706 复核：粗一级的世界误差（压力岩石 7.7/15 mm，演示 glb L1 10 mm）都小于 CSM 级联 0 的纹素（约 13 mm）和深度常数偏移（约 26 mm），截图 bias 0/1/2 差异在噪声内，因此保留固定 +1。`BREAK_LOD_SHADOW_BIAS=N` 语义：阴影级别 = min(相机级别 + N, 最粗级)，0 = 与相机一致；退出时 `LOD_STATS shadow_tris_avg` 给出每级联的阴影三角形数。若以后有误差大的资产，按「误差 / 所在级联纹素」限制 bias 是首选改法。

## 4. 减面器：纯 C 移植 meshoptimizer

### 4.1 为什么移植而不是自写

meshoptimizer（MIT，作者 Arseny Kapoulkine；移植基准钉在正式发布版 **v1.3**（2026-09-25，`MESHOPTIMIZER_VERSION 1030`），不跟 master）的边折叠简化器是业界常用实现，包含：二次误差度量（含属性误差）、边界/接缝/锁定顶点分类、翻转三角形检测、按误差排序的批量折叠、误差上报。自写 QEM 要从零做这些且很难达到同等质量。

已下载核对（master 2026-10-14 版本，移植时按 v1.3 标签重新取）`src/simplifier.cpp`（2947 行）：从 `meshopt_simplifyEdge` 可达的函数 48 个、约 2300 行，其余是 sloppy / points / prune 等本设计不用的变体。**这部分代码的 C++ 用法很浅**：1 个模板函数（`hashLookup2`）、`meshopt_Allocator`（RAII 分配器，`allocate<T>`）、`namespace meshopt`、引用参数和少量 `reinterpret_cast` / `const_cast`，没有 STL 容器、异常、虚函数。移植成 C 是机械性工作。

### 4.2 移植范围

| 原文件 | 移植 | 说明 |
|---|---|---|
| `simplifier.cpp` | 是（仅 `simplifyEdge` 可达部分，约 2300 行） | 提供 `meshopt_simplify`、`meshopt_simplifyWithAttributes`、`meshopt_simplifyScale`。 |
| `vcacheoptimizer.cpp` | 是（约 470 行） | `meshopt_optimizeVertexCache`：减面后的索引重排，提高顶点缓存命中。 |
| `meshoptimizer.h` | 只取用到的声明 | 改为 C 头文件。 |
| 其余（编码、overdraw、聚类、spatial 等） | 否 | 不需要。 |

新文件：`engine/external/meshopt_c/`（`meshopt.h`、`simplifier.c`、`vcacheoptimizer.c`、`LICENSE.md` 保留原 MIT 版权与许可文本，`README.md` 写明来源版本、提交号与移植改动）。登记进 `locked_dependencies.json`（vendored，按文件 sha256 校验）和 `LOCKED_DEPENDENCIES.md`。

移植规则：
- `meshopt_Allocator` → 一个固定上限的块数组 `MeshoptArena { void *blocks[24]; size_t count; }`，`arena_alloc(&a, bytes)`，函数退出前 `arena_free_all(&a)`；所有提前 `return` 改为 `goto done`。分配失败时返回 0（原版断言），调用方据此放弃该级。
- 模板 `hashLookup2<T, Hash>`：只有 `unsigned int` 一种实例，配 3 个哈希器 → 写成 3 个具体函数（或一个带函数指针的版本，按性能选前者）。
- 引用参数 → 指针；`namespace meshopt` → `meshopt_` 前缀的 `static` 函数。
- `assert` 保留（Debug），Release 中参数检查改为返回 0。
- **不改算法与常量**，保证结果与上游可比；一个对照测试（第 7 节）用上游 C++ 版本在开发机上生成参考输出，比较三角形数与误差。

### 4.3 减面策略与边界情况

- 每个网格生成 LOD1、LOD2（共 3 级，`LOD_MAX_LEVELS` 仍为 4 以兼容现有测试）。目标：上一级索引数 × 0.5；同时设误差上限 `target_error`（相对尺寸 2% / 5%）。两者先到者为准。
- 属性：位置 + 法线（权重约 0.5）+ UV（权重约 1.0），用 `simplifyWithAttributes`，避免 UV 接缝和法线硬边被折叠穿。选项开 `meshopt_SimplifyLockBorder`（开放边界不动，防止拼接网格之间出现裂缝）。
- 用 `meshopt_SimplifyErrorAbsolute` 让 `result_error` 直接是世界单位（mega 顶点已在世界空间），省去 `simplifyScale` 换算；但同一网格被多个不同缩放的节点引用时，误差要按各节点的缩放分别换算——因此**减面在网格的局部空间做**（按 `mesh_index` 去重），误差用相对值，烘焙到各节点时乘以该节点的世界缩放。
- **mega 顶点在烘焙时已被变换到世界空间**（`MegaVert` 写的是 `world_transform × pos`），而简化器的输出是 LOD0 顶点的索引子集，所以「共享顶点、只追加索引」对世界空间顶点同样成立：在局部空间算出的索引直接复用到该节点的世界空间顶点段上。
- 放弃该级的条件：网格 < 512 个三角形；或减面后三角形数 > 上一级的 85%（几乎没减）；或 `result_error` 超过上限；或分配失败。放弃后该节点 `level_count` 变小，选级自动跳过。
- 退化输入（索引越界、面数不是 3 的倍数、零面积面）：在调用前校验，失败只打 WARN、节点只保留 LOD0。

### 4.4 加载时间与缓存

- 估算：meshoptimizer 的简化在百万三角形量级是数十到数百毫秒；纯 C 移植性能应接近。压力场景（约 500 万三角形，但是 200 个相同网格）只需对**唯一网格**做一次——按 `Mesh` 去重（同一 `mesh_index` 共享结果）。
- 多网格时用已有的任务系统（`task_submit`）并行减面。
- 磁盘缓存（二期）：按网格内容哈希把各级索引与误差写到 `assets/.lodcache/`，下次直接读。一期只做内存内去重。
- 启动日志打印：减面网格数、各级三角形数、总耗时。

## 5. 上限与内存

- 统一常量 `MEGA_MAX_CMDS`（默认 16384，与现有 CPU 数组一致），替换 `GPUCULL_MAX_OBJECTS` 在 mega 路径上的使用、`MEGA_DIRECT_MAX_DRAWS`，以及 `g_vis_flags` / `g_draw_vis` 等数组长度。`GPUCULL_MAX_OBJECTS` 的 GPU 缓冲按 `MEGA_MAX_CMDS` 分配。
- 超限时：整体退化为 LOD0（每节点 1 条命令），WARN 一次。
- 直接阴影路径的命令表从定长数组改为按需分配（大小 = 命令数）。

## 6. 各后端影响

| 项目 | D3D12 | GL | VK |
|---|---|---|---|
| CPU 选级、命令表、`selected[]` 上传 | 共用 | 共用 | 共用 |
| `unified_cull` 加 `selected[]` 缓冲 | HLSL 加一个 SRV（t 寄存器）与 rhi:binding 注释 | GLSL binding 5 | VK binding 5 + 描述符布局 |
| 其余着色器 | 不改 | 不改 | 不改 |

## 7. 测试与验证

单元（新增 `test_meshopt_c`、扩展 `test_lod`）：
1. 简化器不变量：输出索引都 < 顶点数、是 3 的倍数、没有退化三角形、三角形数单调不增、`result_error` 非负且随目标降低而增大。
2. 锁定边界：开放平面网格简化后边界顶点集合不变。
3. 与上游对照：同一组输入网格（球、圆环、斯坦福兔子之类的固定网格），C 版与上游 C++ 版的三角形数完全相同、误差相差 < 1e-5（若移植忠实应逐位相同）。上游输出在开发机上生成后作为固定参考数据存入测试目录。
4. 屏幕误差选级：给定误差和距离，选级结果与公式一致；迟滞带内不跳变。

集成：
5. 烘焙表：每条命令 `first_index + index_count ≤ 总索引数`，索引 + `vertex_offset` < 总顶点数（R687 同类回归的专门检查）；`cmd_node_index`、`node_cmd_base`、`cmd_level` 自洽。
6. `BREAK_LOD=0` 时三后端截图与改动前逐像素相同（回归保障）。
7. `BREAK_LOD=1` 近距离（所有物体 LOD0）截图与 `BREAK_LOD=0` 相同；远距离截图平均差 < 阈值，并人工看一遍。

性能（只在压力场景）：
8. 新增 `BREAK_STRESS_LOD=N`：程序化生成 N 个高细分物体（每个约 2.5 万三角形，至少有凹凸细节，避免球体这种「减面后误差为 0」的特例），默认 N=0。N=200 为基线，三后端分别测 `BREAK_LOD=0/1` 的 GPU 帧时间、fps、可见三角形数。
9. CPU 选级耗时（N=200 和 N=2000），要求 < 0.1 ms。
10. 选级跳变：相机匀速推近 / 拉远，录逐帧级别序列，确认迟滞生效、没有来回跳。

## 8. 分期

1. **一期**：纯 C 简化器移植 + 测试；mega 烘焙多级（共享顶点）；六条消费路径接入；屏幕误差选级；阴影级别偏置；统一上限；压力场景；文档。
2. **二期**：ECS 实例化物体按 `(mesh, level)` 分组；抖动淡入（dithered crossfade）；glTF `MSFT_lod`；磁盘缓存。
   - **2.1 已实现（R702）**：被实体引用的网格在启动时生成 LOD1/LOD2（与 mega 共用 `lod_generate_levels`，mega 已简化的网格直接复用），各级共享 LOD0 顶点缓冲、索引放进每网格一个额外索引缓冲；收集实例时按实例选级（网格局部包围球平移到实例位置，同一屏幕误差公式与迟滞，迟滞状态按实体 index + generation 保存）；`lod_bucket_instances` 按 (网格, 级别) 稳定分桶，每桶一次实例化绘制（每次最多 512 行）。ECS 实例不进阴影 pass 与延迟 G-buffer（既有行为），所以没有阴影级别。`BREAK_LOD=0` 不建表、走原代码。压力场景 `BREAK_STRESS_LOD_ECS=N`。
   - 蒙皮网格保持 LOD0：简化器不考虑骨骼权重，折叠会合并受不同骨骼驱动的顶点；需要权重感知的减面，仍属「不做」。
   - **2.2 已实现（R703a/R703b）**：ECS 实例化路径在换级时两级同时画 `BREAK_LOD_FADE_MS` 毫秒（默认 250），淡入淡出值放在实例行上一帧模型矩阵第 0 列的 w 分量；mega 每节点保存同一 `LodFade`，`selected[]` 在 1..15 时允许细/粗两条命令，signed k 打包在间接命令 `first_instance` 高 16 位，低 16 位保留材质数组层。前向、材质数组与延迟 G-buffer 都使用 4×4 Bayer 互补抖动 + `discard`，深度写入照常；迟滞仍作用在提交的级别上。阴影不做淡入淡出，直接切换。
   - **2.3 已实现（R704）**：`renderer/lod_cache` 以完整网格/参数的双 64-bit hash 为键，用带版本和计数的 little-endian 文件保存各级索引、相对误差、scale 和生成耗时；读取完整校验并回退重新生成，临时文件 + 原子 rename 写入。mega/ECS 共用，`BREAK_LOD_CACHE=<directory>` 显式启用（默认关闭），统计 hits/misses/bytes/estimated_saved_ms。
   - 未做：`MSFT_lod`。
3. 不做：HLOD、impostor、蒙皮网格 LOD。

## 9. 待决定（需要用户确认）

1. **一期的级别数**：3 级（LOD0 + 2）还是 4 级？**建议 3 级**（内存与收益平衡）。
2. **像素误差阈值** `LOD_PIXEL_ERROR` 默认 1.0 是否合适？更激进的 2.0 能多降一级，但更容易看出变化。**建议 1.0。**
3. **阴影级别偏置**默认 +1（第 3.5 节）是否接受？**建议接受，出问题再改 0。**
4. **压力场景规模** N=200（约 500 万三角形）是否合适，或有真实资产要用？
5. **移植目录**放 `engine/external/meshopt_c/`（第三方、MIT）是否可以？**建议是。**

## 10. 风险

- 移植量约 2800 行（简化器 + 顶点缓存优化），主要风险是移植时引入偏差；对照测试（第 7 节 #3）是主要防线。
- 减面质量问题（法线、UV 接缝、薄壁）直接可见；属性权重和锁定选项需要在压力场景和真实资产上人工看。
- `unified_cull.comp` 的修改要三后端各自验证（尤其 HLSL 的绑定与 R680 那类绑定契约测试）。
- 合并网格仍是启动时一次性烘焙，运行时新增/删除的物体不进 mega 路径（本设计不改变）。
