# 运行时 LOD 设计（草案，待确认）

状态：设计草案。**尚未实现任何代码。** 实现前需要用户确认「待决定」一节。

## 1. 目标与非目标

目标：让引擎在运行时根据物体距离（或屏幕占比）选择它的低面数版本绘制，作为一项**引擎能力**，在大场景里减少顶点/三角形处理量。

非目标：
- 不是为了提高当前演示的帧率。2026-10-26 的测量显示，哪怕把演示里整个场景网格都不画，帧率上限也只有 D3D12 +2.1%、GL +5.2%、VK +3.4%（场景只有约 1.7 万三角形，瓶颈在 pass 数量、阴影 pass 和填充像素）。所以**不能用演示帧率验证 LOD**，必须有单独的压力场景（见第 7 节）。
- 不做 mesh shader / 虚拟化几何（Nanite 类）。
- 不做 HLOD（把多个物体合并成代理网格）和 impostor/billboard。

## 2. 现状（已在代码里确认）

| 项目 | 现状 |
|---|---|
| `renderer/lod.{c,h}` | 框架完整且有单元测试（`test_lod`，约 20 个用例）：`LODGroup`（最多 4 级 `meshes[]`/`thresholds[]`）、`lod_select`（距离或屏幕占比两种策略，带迟滞和全局 bias）、`lod_update_all`、`lod_group_set_auto_thresholds`。 |
| 注册 | `main.c` 启动时把每个静态场景节点注册成 1 级的 LOD 组（`level_count = 1`，只有原始网格）。 |
| 选级结果的使用 | 非 mega 的前向路径调用 `lod_select`，但立刻 `(void)lod_level` 丢弃；只用 `thresholds[0] × 2` 做距离剔除。 |
| mega 路径 | 默认路径。所有静态节点预烘焙进一个合并 VBO/IBO（世界空间顶点），每个节点一条 `DrawIndexedIndirectCmd`。GPU 剔除只决定画不画，不选级别。 |
| 减面 | 无。代码库里没有 meshoptimizer，也没有自己的 QEM 实现。 |
| ECS 实例绘制 | 完全不经过 LOD 系统。 |
| 阴影 | R688/R691 起，点光和 CSM 的 mega 绘制走 CPU 球体剔除 + 直接绘制（`mega_draw_direct_culled`）。 |

## 3. 设计

### 3.1 总体思路

LOD 选择**放在 CPU**，每帧对每个节点调用现有的 `lod_select`，把选中级别写进「本帧该节点用哪条绘制命令」。理由：
1. `lod_select` 已经写好并测过，包括迟滞；重写成 GPU 着色器要在 GLSL/VK/HLSL 三套里各来一份，并且迟滞需要上一帧状态的读回，复杂得多。
2. 场景里的节点数是上千量级（`GPUCULL_MAX_OBJECTS = 4096`），CPU 每帧选级是微秒级。
3. 与 R688/R691 的 CPU 直接绘制路径同构，改动小。

### 3.2 数据：每级一条绘制命令

mega-buffer 烘焙时，对每个节点的**每个 LOD 级别**各追加一段顶点/索引，并各生成一条 `DrawIndexedIndirectCmd`。命令数组改成按「节点 × 级别」排布：

```
cmd index = node_cmd_base[node] + level      （level < node.level_count）
```

新增 `MegaBuffer.lod_cmd_base[]`、`lod_level_count[]`。每个节点的包围球不随级别变化（取 LOD0 的），保证剔除结果与级别无关。

### 3.3 选级与绘制

每帧：

```
for node in nodes:
    level = lod_select(&lod_sys, node, center, camera, fov)     // 已有，带迟滞
    cmd   = lod_cmd_base[node] + level
    visible[cmd] = frustum/occlusion result of node
```

- **直接路径**（`mega_draw_direct_culled`，阴影）：已经是 CPU 循环，直接在循环里挑 `direct_cmds[lod_cmd_base + level]` 绘制。阴影用与相机同一个级别（避免相机看到的与阴影的轮廓不一致）。
- **GPU 间接路径**（前向/延迟/G-Buffer 的 compact）：compact 着色器读 `visibility.flags[idx]`，每个 idx 对应一条命令。让 CPU 在上传可见性标志（`indirect_draw_upload_visibility`，已有）时，**只给选中级别的那条命令置 1，其余级别的命令置 0**。这样 `compact_draws.comp`、`unified_cull.comp`、间接执行**一行都不用改**。
  - 仅走 GPU 视锥/遮挡判断的路径（`unified_cull` 的 flags-only 模式，R169）：它按对象 idx 写标志，需要在 CPU 读回上一帧标志后，叠加「级别掩码」再上传。当前已有这条读回（`gpucull_read_vis_flags`），改动局限在 `mega_unified_vis_flags`。
- **材质数组路径**（`mega_mat_arrays_draw`，R441）：命令按 bake 顺序，`first_instance` 是材质层号；每级命令带相同的层号，这条路径同样靠标志位选择，无需改动。

### 3.4 切换策略

- 默认用**距离**策略（`lod_select` 的 `use_screen_size = false`），阈值由 `lod_group_set_auto_thresholds(group, base_distance)` 生成，也可以由资产显式提供。
- 保留已有的迟滞，避免临界距离上来回跳变。
- **全局 bias**（`lod_set_bias`）作为画质开关暴露为环境变量 `BREAK_LOD_BIAS` 和调试 UI 项；`BREAK_LOD=0` 完全关闭（始终 LOD0，行为与现在一致）。
- 过渡：先不做抖动淡入（dithered crossfade）。第一版允许级别切换时有轻微弹跳；是否需要淡入见「待决定」。

### 3.5 低面数网格从哪来

两个来源，按优先级：

1. **资产自带**：glTF 里同一个节点的 `MSFT_lod` 扩展（或约定命名 `*_LOD1`、`*_LOD2`）。加载时直接生成各级 `Mesh`。
2. **运行时生成**：加载时对没有自带 LOD 的网格做减面。

减面实现的两个选项（见「待决定」）：
- **A. 引入 meshoptimizer**（MIT，纯 C++ 库，单目录约 30 个文件）。`meshopt_simplify` 质量好、有边界锁定、速度快。代价：新增 C++ 依赖，工程当前 `LANGUAGES C`，需要 `enable_language(CXX)`（工程里已有一处 CXX 使用）；要放进 `locked_dependencies.json` 并钉版本和哈希。
- **B. 自己写**一个二次误差度量（QEM）边折叠，纯 C，约 400–600 行。可控、无新依赖，但要自己做边界保护、法线/UV 处理和充分测试，质量和速度不如 meshoptimizer。

### 3.6 法线、UV、材质

减面保持顶点属性（位置、法线、UV）；折叠时按误差加权插值。材质不变：低级别网格继承原节点的 `material_idx`。接缝/边界处理：默认锁定开放边界和 UV 接缝，防止纹理撕裂。

### 3.7 ECS 实例绘制

实例化物体（`instance_data`，按 `mesh_index` 分组）是另一条路径。第一版**不做**：实例化的物体本来数量就多、单个面数小，收益最低，而且分组键要从 `mesh_index` 改成 `(mesh_index, level)`，每帧要按级别重新分桶，复杂度明显更高。放到第二期。

## 4. 各后端影响

| 后端 | 影响 |
|---|---|
| D3D12 / GL / VK | CPU 侧选级 + 可见性标志上传，三后端共用同一份代码。着色器与间接执行不变。 |
| 命令数上限（已在代码里确认） | 三处硬上限都会被节点×级别撞到：`GPUCULL_MAX_OBJECTS = 4096`（`mega_unified_cull_draw` / `mega_unified_vis_flags` 在 `vis_count` 超过它时直接返回 false，退回旧路径）；`main.c` 里的 `g_vis_flags[16384]`、`g_draw_vis[16384]`、`cmd_node_index[16384]`、`node_spheres[16384]` 等 CPU 数组；以及 `MEGA_DIRECT_MAX_DRAWS = 64`（R688 的直接阴影路径只在命令数 ≤ 64 时启用）。**压力场景 N=200、3 级就是 600 条命令，会超过第三项、但没超过前两项；N 再大就要提高前两项。** 设计上把三处上限统一成一个 `MEGA_MAX_CMDS` 常量，超限时整体退化为 LOD0（不报错，只打一条 WARN）。 |
| 内存 | 每个节点的所有级别都常驻 mega VBO。以 3 个附加级别、每级 50% 面数估算，约多出 87% 的几何内存（LOD1 50% + LOD2 25% + LOD3 12.5%）。 |

## 5. 正确性约束

1. `BREAK_LOD=0` 时输出与现在逐像素一致（回归保障）。
2. 阴影与相机用同一级别。
3. 迟滞状态按节点保存，节点被删除/重烘焙时重置。
4. 同一帧内所有 pass（前向、G-Buffer、阴影）看到的级别必须一致。
5. 剔除半径不随级别变化。

## 6. 测试方案

- 单元：沿用 `test_lod`（选级逻辑），新增减面输出的不变量（索引有效、无退化三角形、包围盒不扩大、顶点数单调下降）。
- 烘焙：合并 VBO/IBO 的偏移与命令表（沿用 R687 修过的那个顶点偏移 bug 的同类检查：最大有效索引必须小于顶点总数）。
- 渲染：同一相机下，`BREAK_LOD=0` 与 `BREAK_LOD=1` 在近距离像素一致；远距离允许差异但平均差有阈值。
- 三后端交叉：沿用现有的截图对比方式（D3D12/GL/VK 互相比）。
- 性能：只在压力场景里做（第 7 节）。

## 7. 压力场景（验证 LOD 价值必须有）

新增 `BREAK_STRESS_LOD=N`：程序化生成 N 个高细分物体（如 UV 球，约 2–5 万三角形/个）铺成网格，N 默认 0（不影响现有演示）。以 N=200（约 500 万三角形）为基线，对比 `BREAK_LOD=0` 与 `1` 的 GPU 帧时间和 fps，三后端各测。**LOD 功能的验收标准是这个场景里的收益，而不是演示。**

## 8. 实施分期

1. **一期（本设计的范围）**：选级接线 + 低面网格（来源 3.5）+ mega 烘焙多级 + 直接路径与 GPU 间接路径的标志选择 + 压力场景 + 测试 + 文档。
2. **二期**：ECS 实例绘制按 `(mesh, level)` 分组；抖动淡入。
3. 不做：HLOD、impostor。

## 9. 待决定（需要用户确认）

1. **减面实现**：A（引入 meshoptimizer，新增 C++ 依赖，质量好、工作量小）还是 B（自己写 QEM，纯 C、无依赖、工作量大、质量较差）？**建议 A。**
2. **是否做级别切换时的抖动淡入**：一期不做（建议），还是一期就要？
3. **LOD 级别数**：沿用现有框架的最多 4 级，还是第一期先做 3 级（LOD0 + 2 个简化级）以减少内存？**建议 3 级。**
4. **压力场景的默认规模**：N=200（约 500 万三角形、3 级共 600 条命令）是否合适，还是你有具体的目标场景（比如实际资产）？
5. **glTF 自带 LOD**（`MSFT_lod`）一期是否要支持，还是只做运行时减面？**建议只做运行时减面，自带 LOD 放二期。**

## 10. 风险

- 合并网格是静态一次性烘焙（场景启动时），运行时新增/删除的物体不会进入 mega 路径，本设计不改变这一点。
- 减面质量问题（法线、UV 接缝、薄壁）会直接可见，需要在压力场景和真实资产上人工看。
- 命令数增加会影响 GPU 剔除/compact 的 dispatch 规模（`TOTAL_DRAWS` 变成节点数×级别数）；上限和性能要在压力场景里实测。
- 内存增加约 87%（见第 4 节）。
