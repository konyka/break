# 世界呈现集成设计

日期：2026-11-02

## 目标与边界

本设计实现总体能力设计的 P6：普通世界网格与流式块使用受光、可 textured 的材质；CPU 植被布局进入真实实例化绘制并选择 LOD；昼夜参数进入着色器；VisArea 可见集决定对象提交。Vulkan 仍是默认后端，OpenGL 仅作最终降级，两条路径都只调用现有 RHI。

不修改 ECS 流式驻留策略、VFS、其他游戏子系统或 `docs/Implementation_Status.md`。本设计不声称 D3D12/Metal 的画面 parity，也不把 headless/fake RHI 记录当作图形证据。

## 方案取舍

1. **采用：扩展现有网格/RHI，并增加一个有界世界快照提交层。** 旧 CPU 模块继续负责布局、驻留和可见性；新层只在 GameThread 生成 POD 快照，在 RenderThread 通过同一个绘制辅助函数提交普通对象和流式对象。优点是真实消费链短、可分别做 CPU/fake/像素验收。
2. 不采用：把材质和植被直接塞进各后端。这样会产生 GL-only 旁路，并重复 Vulkan 描述符、顶点布局和实例缓冲逻辑。
3. 不采用：保留 28 字节顶点并用 material id 猜测 UV，或为植被逐实例发出单实例 draw。前者不能可靠采样纹理，后者不是实际实例化且无法验证批次行为。

## 顶点、材质与着色

`MeshStageVertex` 保持 28 字节 ABI：position/normal/material。`MeshBuffer` 使用新的 36 字节 `MeshVertex`，在末尾增加 `vec2 uv`。`mesh_buffer_from_legacy` 完整迁移旧数据，按主法线轴生成确定性的平面 UV； decal/voxel/road 的现有 staging 入口也经过该迁移。V1 流式块因此无需改写磁盘格式即可进入新路径。后续新格式可显式提供 UV，不改变 V1 的含义。

RHI 的 `mesh_stage_vertex` 布局同时支持 28 字节旧布局和 36 字节迁移布局：location 0/1/2 保持 position/normal/material，36 字节时增加 location 3 UV。OpenGL 与 Vulkan 使用相同stride和偏移；Vulkan 补齐此前缺失的专用分支。

`MeshMaterial` 包含 base color、roughness、albedo texture 和 sampler。材质无纹理时由呈现器绑定自有的 1x1 白色 fallback；base color 始终参与着色。新受光管线支持普通与实例两个变体，使用同一组参数：view/projection、sun direction/color、ambient、fog、camera position、base color、roughness，以及实例批偏移。Vulkan 使用反射后的 push-constant 偏移，OpenGL 使用同名 uniform location；创建时缺少必需绑定会失败，不静默黑屏。

片元颜色为 `base_color * texture(albedo, uv)`，再做法线方向光、受 roughness 控制的低强度高光、环境光及距离雾。`time_of_day_eval` 的结果由快照逐值传入这些 uniform，而不是仅保留 CPU 参数。

## GameThread 快照

`world_presentation_snapshot` 是纯 GameThread 构建步骤，输入和输出分离：

- `frame_id`、相机 view/projection、FOV/screen height/pixel error 和 `TimeOfDayLighting` 均按值复制。
- 普通/流式对象记录包含稳定 object id、`MeshGpu` 句柄、`MeshDrawDesc`、材质和来源标记。GPU 资源由 RenderThread 资源所有者管理；快照不拥有或销毁它们。
- 若提供 `VisQuery`，构建器调用 `visarea_visible`，只复制可见 id 对应的对象。可见集溢出是 `OVERLOAD`，不是截断后继续。
- 植被输入只在构建期间读取。每个实例的 prototype 和位置被复制，并生成 unit-scale matrix；LOD 由现有 `lod_instance_select`/`lod_select_by_screen_error` 计算，再由 `lod_bucket_instances` 按 prototype/level 排序。快照保存排序后的 4x4 model matrix 和有界批次，不保存 `VegetationBuild` 或 prototype 数组指针。
- `world_presentation_stream_mesh` 将 `StreamTileData` 的 V1 顶点通过同一个 `mesh_buffer_from_legacy` 迁移，并在 CPU 阶段烘焙块平移。之后的 upload、材质和提交与普通网格完全相同。

容量固定为 512 个普通/流式对象、1024 个植被实例、8 个 prototype、每 prototype 最多 4 个 LOD、最多 32 个实例批次。所有输入、句柄、draw stride/count、材质数值、prototype 引用和非递减 LOD error 在写入输出前验证。失败返回 `INVALID` 或 `OVERLOAD` 且保持旧输出及 LOD 状态不变；成功才替换整个快照。热路径无动态分配。

快照提交后即视为不可变。GameThread 不得继续写该帧存储；RenderThread 只读快照。调用者以 frame 生命周期或双缓冲保证存储复用晚于提交完成，GPU 句柄的销毁晚于引用它们的 in-flight 帧。此边界不使用原子指针掩盖数据竞争。

## RenderThread 提交

`WorldPresenter` 在创建时生成普通/实例两条 RHI 管线、白色纹理、sampler 和固定 1024 实例的 texel buffer。任何资源创建或绑定反射失败都会逆序销毁已创建资源并留下空 presenter。

`world_presenter_submit` 不开始/结束 render pass，也不 present。它：

1. 绑定普通受光管线，写入相机和昼夜参数；逐对象绑定材质并用共享 geometry 辅助函数发出 indexed/non-indexed draw。普通和流式来源走同一代码段。
2. 若有植被，将整个有序 matrix 数组一次写入实例 texel buffer，绑定实例管线、材质和 LOD 对应网格；通过批偏移 uniform 让每个 batch 从正确 matrix 区间读取，并以 `instance_count > 1`（批次内数量）发出真实实例化 draw。
3. 返回普通 draw、实例批次、实例数和流式 draw 统计，供 fake RHI 对照；统计不是图形通过证据。

提交前重新验证快照计数和 stride。渲染调用没有可恢复错误返回的 RHI 入口仍遵循现有 RHI 合同；快照格式错误不会发出部分 draw。

## 测试与变异

严格先添加会失败的测试，再实现：

- CPU：28→36 迁移和 UV、V1 流式块迁移、VisArea 过滤、LOD 近远选择/分桶、容量溢出、非法材质与失败原子性、昼夜数值。
- fake RHI：纹理/sampler 与实际 base color/lighting/fog 写入；普通与流式使用同一管线；可见对象之外的 mesh 不提交；植被批次 instance count、LOD mesh 和实例 matrix 正确；创建失败完整清理。
- 真实图形：同一帧用不同颜色绘制普通网格、V1 流式块和至少两株实例植被，VisArea 排除的高亮全屏网格不得出现；昼夜两帧必须有显著明暗差。Vulkan 和 OpenGL 可创建设备时分别执行并保存像素统计；无 display/device 返回既有 skip code，并在报告标为缺证。
- 回归：focused normal、ASan+UBSan、TSan 均使用 `-j3`；运行现有 mesh/world/RHI 测试和可用 graphics 测试。

至少对材质光照、可见性过滤、LOD 选择和流式同源提交做变异检查：临时破坏实现，确认对应测试变红，再恢复并重新变绿。报告记录每条命令、结果、图形设备/跳过原因和未验证平台。
