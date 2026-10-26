# 蒙皮网格运行时 LOD 设计

状态：实现中。R707a 已完成 3.1 纯 CPU 模块与 3.3 缓存键（`renderer/lod_skin.{c,h}`、`lod_cache_generate_ex`，未接入 `main.c`）；3.2、3.4、3.5 待做。用户已明确要求「现在就做，作为基本功能」。auto 模式下按下文推荐方案执行，偏差记录在 `docs/Implementation_Status.md`。

## 1. 现状（已核实）

- 每个蒙皮图元一个 `SkinnedMesh`（`asset.h`），顶点 64 字节：pos3 + nrm3 + uv2 + joints u32×4 + weights f32×4（`asset.c` 的 `SkinnedVertex`，权重已归一化）。
- 世界坐标完全由关节矩阵决定（`skin = Σ w·current_pose[j]`，`current_pose = world × inverse_bind`），着色器没有 `u_model`；全场景共用一个 `Skeleton`（最多 128 关节）。
- 绘制：前向 blinn（`skinned_pipeline`）、clustered（`clustered_skin_pipeline`）、延迟 G-buffer（`gbuffer_skinned_pipeline`），各自逐网格 `rhi_cmd_draw_indexed`。无包围体、无剔除、不进阴影 pass。
- 演示场景的程序化手臂只有 48 个三角形（低于 `LOD_GEN_MIN_TRIANGLES=512`），当前没有能体现 LOD 的蒙皮模型。

## 2. 核心问题与方案选择

普通减面只看绑定姿势的几何。蒙皮网格上，绑定姿势里看起来可以合并的两个顶点，可能分别受不同骨骼驱动，动画时被拉开，造成肘部、膝盖塌陷或撕裂。

meshopt 的折叠只删除顶点，**保留下来的顶点仍带原来的关节和权重**，所以蒙皮数据本身不会被破坏；要解决的只是「选哪些折叠」和「误差怎么算」。

| 方案 | 做法 | 评价 |
|---|---|---|
| A. 多姿势属性（推荐） | 在若干采样姿势下计算每个顶点的蒙皮后位置，作为额外属性喂给 `meshopt_simplifyWithAttributes`；折叠若在任一姿势下变形大，属性误差就大，简化器自然避开 | 通用、直接度量真正关心的东西；属性上限 32 个 float，够放 8 个姿势（24）+ 法线（3）+ UV（2） |
| B. 骨骼边界锁定 | 主导关节与邻居不同的顶点用 `vertex_lock` 锁住 | 简单，但过于保守（关节附近不能减面），也挡不住同一主导关节、不同次级权重的情况 |
| C. 权重向量做属性 | 把权重按关节展开成属性 | 关节最多 128 个，超过 32 个属性上限；只取前几个又不准 |

采用 **A**；没有动画片段时退化为「绑定姿势 + 主导关节边界锁定（B）」。

## 3. 设计

### 3.1 纯逻辑模块 `renderer/lod_skin.{c,h}`（无 GPU 依赖）

```c
/* poses[p * joint_count + j] = 关节 j 在姿势 p 下的蒙皮矩阵 (world × inverse_bind)。
 * pose_count 可为 0（只用绑定姿势）。vertices 为 64 字节 SkinnedVertex。 */
void lod_generate_levels_skinned(const f32 *vertices, u32 vertex_count,
                                 const u32 *indices, u32 index_count,
                                 const Mat4 *poses, u32 pose_count, u32 joint_count,
                                 u32 max_levels, LodMeshLevels *out);

typedef struct { f32 c[3]; f32 r; } LodSphere;   /* r < 0 = 空 */
/* 每关节：绑定姿势下权重 > 0 的顶点的包围球。 */
void lod_skin_joint_spheres(const f32 *vertices, u32 vertex_count, u32 joint_count,
                            LodSphere *out /* [joint_count] */);
/* 当前姿势下整网格的保守包围球：每个关节球按 skin_mats[j] 变换（半径乘最大列范数），再求并。 */
LodSphere lod_skin_bounds(const LodSphere *joint_spheres, u32 joint_count,
                          const Mat4 *skin_mats);
```

- 减面：属性 = 法线（权重 0.5）+ UV（1.0）+ 每个采样姿势的蒙皮后位置（除以网格尺度后权重 1.0）；姿势超过 8 个时均匀抽取 8 个。沿用 `lod_gen` 的级别比例、停止比例、`LockBorder`、顶点缓存优化。
- 误差：**实测**。对绑定姿势和每个采样姿势，分别算 LOD0 与 LODn 蒙皮后位置的对称 Hausdorff 估计（复用 `lod_authored_error`），取最大值 / scale 作为 `rel_error`，保持逐级非递减。这样运行时的屏幕误差选级、迟滞、淡入淡出不需要区分蒙皮与否。
- 无姿势时：额外用 `vertex_lock` 锁住与相邻顶点主导关节不同的顶点。

### 3.2 采样姿势（`main.c`，加载时）

用一个不上传 GPU 的临时 `Skeleton`，对 `scene.anim_clips` 的每个片段在时间轴上均匀取样，总数上限 8；连同绑定姿势一起传入。没有片段时只用绑定姿势。

### 3.3 磁盘缓存

R704 的缓存键需要包含姿势。新增 `lod_cache_generate_ex`：调用方提供额外参与哈希的字节（姿势矩阵）和生成回调；文件格式不变（只是键不同），`BREAK_LOD_CACHE` 语义不变。

### 3.4 运行时

- 每个 `SkinnedMesh` 加载时生成级别；级别索引追加到每网格一个额外索引缓冲（与 R702 ECS 路径同法），共用原顶点缓冲。
- 每帧：骨骼更新后，用 `lod_skin_bounds(当前姿势)` 得到包围球，按原屏幕误差公式 + 迟滞选级（状态按蒙皮网格下标保存），`BREAK_LOD_PIXEL_ERROR` 共用。
- 淡入淡出：沿用 R703 的 `LodFade` 与 4×4 Bayer 互补 `discard`。蒙皮是直接绘制，新增 RHI 入口 `rhi_cmd_draw_indexed_instanced_base(cmd, index_count, instance_count, first_index, vertex_offset, first_instance)`（VK `vkCmdDrawIndexed`、D3D12 `DrawIndexedInstanced`、GL `glDrawElementsInstancedBaseVertexBaseInstance`），淡入淡出值按 R703b 的约定放在 `first_instance` 高 16 位，着色器读 `gl_BaseInstanceARB` / `SV_StartInstanceLocation`。三条蒙皮管线（blinn、clustered、G-buffer）各加 `LOD_FADE` 变体（GLSL 注入宏，HLSL 用 `*_lodfade_hlsl.*` 副本）。`caps.indirect_first_instance_supported` 为假时不做淡入淡出、直接切换。
- 开关：`BREAK_LOD=0` 不生成、不建表、走原代码；`BREAK_LOD_FADE_MS` 共用。统计 `SKIN_LOD_STATS`（选级耗时、可见三角形、换级次数、淡化计数）。
- 场景重新加载（BSCN `N` 键）时释放并重建。

### 3.5 压力场景 `BREAK_STRESS_LOD_SKIN=N`

程序化高细分管状网格（每个约 2 万三角形、表面有凹凸），每根有自己的 4 关节链和弯曲动画（N ≤ 16，受 128 关节与 64 通道上限约束），放在不同距离，替换演示手臂。

## 4. 测试与验证

- 单元测试（`test_lod_skin.c`）：
  - 输出索引都在原顶点范围内（权重天然保留）。
  - 构造一个在关节处弯折的网格：仅按绑定姿势减面在弯曲姿势下的实测误差，明显大于本方案的结果；本方案报告的 `rel_error` 不小于实测误差。
  - 关节包围球：随机姿势下所有蒙皮后顶点都在 `lod_skin_bounds` 内。
  - 无姿势回退、非法输入（关节越界、权重全 0、空网格）不崩溃。
  - 缓存：姿势变化导致键变化；往返一致。
- 渲染：三后端 Release 跑压力场景（换级、淡化计数、截图检查关节处无撕裂）；VK 验证层 0、D3D12 调试层 0；`BREAK_LOD=0` 与改动前一致；演示场景（小蒙皮网格）不变。
- 真实资产：本地下载 Khronos glTF 示例里的蒙皮模型（如 CesiumMan、BrainStem，CC-BY）做肉眼检查，不提交。
- 构建：各树 0 警告；GCC `-Werror` 检查；ASan 树。

## 5. 不做

- 运行时重新减面（姿势只在加载时采样）。
- 每实例多套骨骼、蒙皮网格的阴影（引擎原本就不画）。
- 混合形状（morph target）：引擎目前不支持。
