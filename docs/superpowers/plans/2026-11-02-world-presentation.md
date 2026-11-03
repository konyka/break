# World Presentation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 将旧世界网格、植被、昼夜、VisArea 和 V1 流式块接入同一套 Vulkan 默认/OpenGL 降级的 RHI 呈现路径。

**Architecture:** 保留 28 字节 staging ABI，在上传前迁移为 36 字节带 UV 顶点。GameThread 用固定容量 POD 快照完成可见性过滤和 LOD 分桶，RenderThread 用共享 RHI 提交普通/流式 draw 与实例批次。

**Tech Stack:** C11、CMake/CTest、现有 `test_framework.h`、RHI、Vulkan GLSL push constants、OpenGL uniforms、现有 LOD/VisArea/Vegetation/StreamTileData。

## Global Constraints

- 只修改本工作树；不 push、不建 PR、不改 `docs/Implementation_Status.md` 或其他子系统。
- 新库代码使用 C11；热路径不动态分配；对象 512、植被 1024、prototype 8、LOD 4、批次 32，超限显式失败。
- GameThread 独占输入和 LOD 状态；提交后的快照不可变，RenderThread 只读 POD 和 RHI 句柄。
- 失败保持旧输出、LOD 状态或 presenter 资源所有权不变；所有构建/测试并行度为 `-j3`。
- Vulkan 默认、OpenGL 最终降级；不得增加直接 GL/Vulkan 后端调用。fake/headless 不是像素证据。
- 每项行为先 RED 后 GREEN；材质、可见性、LOD、流式同源至少各做一次变异检查。

---

### Task 1: 旧顶点迁移与双后端布局

**Files:**
- Modify: `engine/src/renderer/mesh_stage.h`, `engine/src/renderer/mesh_stage.c`
- Modify: `engine/src/renderer/mesh_buffer.h`, `engine/src/renderer/mesh_buffer.c`
- Modify: `engine/src/rhi/rhi.h`, `engine/src/rhi/rhi_gl.c`, `engine/src/rhi/rhi_vk.c`
- Test: `engine/tests/test_mesh_buffer.c`, `engine/tests/test_mesh_stage.c`

**Interfaces:**
- Produces: `MeshVertex { px,py,pz,nx,ny,nz,material,u,v }`（36 字节）。
- Produces: `bool mesh_vertices_migrate(const MeshStageVertex *in, u32 count, MeshVertex *out, u32 cap)`。
- Produces: `bool mesh_buffer_from_legacy(MeshBuffer *b, const MeshStageVertex *in, u32 count, u32 *dropped)`；完整 quad 自动生成既有 6-index 模式。

- [ ] **Step 1: 写迁移 RED**

在 `test_mesh_buffer.c` 添加两个不同法线的 28 字节顶点，断言迁移后 position/normal/material 不变、stride 为 36、Y 法线使用 `(u,v)=(px,pz)`、Z 法线使用 `(px,py)`；断言 V1 四顶点得到 6 个索引。

```c
MeshStageVertex old_[4] = {0};
old_[0].px = -1.0f; old_[0].pz = 2.0f; old_[0].ny = 1.0f; old_[0].material = 7;
MeshBuffer b;
u32 dropped = 99;
ASSERT_TRUE(mesh_buffer_from_legacy(&b, old_, 4, &dropped));
MeshDrawDesc d;
ASSERT_TRUE(mesh_buffer_draw_desc(&b, &d));
ASSERT_EQ(d.stride, 36u);
ASSERT_EQ(d.index_count, 6u);
ASSERT_FLOAT_EQ(b.verts[0].u, -1.0f, 1e-6);
ASSERT_FLOAT_EQ(b.verts[0].v, 2.0f, 1e-6);
ASSERT_EQ(b.verts[0].material, 7u);
```

- [ ] **Step 2: 编译运行并确认 RED**

Run: `cmake --build build-world-normal --target test_mesh_buffer test_mesh_stage -j3 && ./build-world-normal/test_mesh_buffer`
Expected: 新 API 编译失败，或先加声明后链接/断言失败；记录实际诊断，不能把未运行当 RED。

- [ ] **Step 3: 最小实现迁移和布局**

保留 `MeshStageVertex` 为 28 字节。`MeshBuffer.verts` 改为 `MeshVertex`，decal/voxel/road 使用固定 256 项旧顶点临时数组后迁移。`mesh_stage_vertex=true` 时，`vertex_stride` 只允许 0/28/36；0 默认 28，36 在 location 3 增加 `vec2`，Vulkan 添加与 GL 相同的专用分支。

- [ ] **Step 4: 回归并确认 GREEN**

Run: `cmake --build build-world-normal --target test_mesh_buffer test_mesh_stage test_mesh_gpu -j3 && ctest --test-dir build-world-normal -R 'test_mesh_(buffer|stage|gpu)$' --output-on-failure`
Expected: 3/3 PASS，`sizeof(MeshStageVertex)==28`、`sizeof(MeshVertex)==36`。

- [ ] **Step 5: 提交本任务**

`git add docs/design/world_presentation.md docs/superpowers/plans/2026-11-02-world-presentation.md engine/src/renderer/mesh_* engine/src/rhi/rhi* engine/tests/test_mesh_* && git commit -m "world: migrate legacy mesh vertices for textures"`

### Task 2: 受光材质管线和实际昼夜参数

**Files:**
- Modify: `engine/src/renderer/mesh_gpu.h`, `engine/src/renderer/mesh_gpu.c`
- Create: `engine/tests/test_world_mesh_fake.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `MeshMaterial { Vec3 base_color; f32 roughness; RHITexture albedo; RHISampler sampler; }`。
- Produces: `bool mesh_pipeline_create_lit(RHIDevice *, MeshPipeline *, bool instanced)`。
- Produces: `void mesh_pipeline_bind_frame(RHICmdBuffer *, const MeshPipeline *, const Mat4 *view, const Mat4 *projection, const TimeOfDayLighting *, Vec3 camera)`。
- Produces: `void mesh_pipeline_bind_material(RHICmdBuffer *, const MeshPipeline *, const MeshMaterial *, RHITexture white, RHISampler fallback)`。
- Produces: `bool mesh_gpu_draw_desc(RHICmdBuffer *, const MeshGpu *, const MeshDrawDesc *, u32 instance_count)`。

- [ ] **Step 1: 写 fake RHI 材质 RED**

fake 返回可追踪句柄和 GL/VK 两套绑定槽，记录 texture/sampler、vec3/f32/mat4 和 draw。测试创建受光管线，绑定红色 1x1 纹理和 `TimeOfDayLighting`，断言材质句柄、base color、roughness、sun/ambient/fog 和 view/projection 均到达命令记录；无纹理材质必须绑定 white fallback。

- [ ] **Step 2: 运行并确认 RED**

Run: `cmake --build build-world-normal --target test_world_mesh_fake -j3 && ./build-world-normal/test_world_mesh_fake`
Expected: 缺少 `mesh_pipeline_create_lit`/材质接口或断言失败。

- [ ] **Step 3: 实现双变体 shader 与绑定**

内嵌 GL/VK GLSL；Vulkan push block 不超过 208 字节，GL 使用同名 uniform。普通 shader 直接变换 position；实例 shader 从 `samplerBuffer` 读取 4 行 model matrix。片元采样 albedo，并计算方向光、roughness 高光、ambient 和距离雾。创建后解析所有必需 binding，缺失即销毁并返回 false。`mesh_gpu_draw_desc` 同时支持 indexed/non-indexed 与实例数。

- [ ] **Step 4: 运行并确认 GREEN**

Run: `cmake --build build-world-normal --target test_world_mesh_fake test_mesh_gpu -j3 && ctest --test-dir build-world-normal -R 'test_(world_mesh_fake|mesh_gpu)$' --output-on-failure`
Expected: 2/2 PASS；fake 明确显示材质和昼夜记录，不声称像素通过。

- [ ] **Step 5: 材质变异后恢复**

临时把 shader 的 sun contribution 改成 0，运行测试确认 RED；恢复后确认 GREEN。再让 fake 丢失一个必需 binding，确认创建失败且资源清理计数平衡。

- [ ] **Step 6: 提交本任务**

`git add engine/src/renderer/mesh_gpu.* engine/tests/test_world_mesh_fake.c engine/CMakeLists.txt && git commit -m "world: bind lit materials through RHI"`

### Task 3: 不可变世界快照、VisArea、LOD 与流式迁移

**Files:**
- Create: `engine/src/renderer/world_presentation.h`, `engine/src/renderer/world_presentation.c`
- Modify: `engine/CMakeLists.txt`
- Test: `engine/tests/test_world_presentation.c`

**Interfaces:**
- Produces: `WorldObject`、`WorldVegetationPrototype`、`WorldPresentationInput`、`WorldFrameSnapshot`，字段与设计文档一致。
- Produces: `WorldPresentationStatus world_presentation_snapshot(const WorldPresentationInput *, WorldFrameSnapshot *out)`。
- Produces: `bool world_presentation_stream_mesh(const StreamTileData *, Vec3 translation, MeshBuffer *out)`。
- Status enum: `WORLD_PRESENTATION_OK/INVALID/OVERLOAD`。

- [ ] **Step 1: 写 CPU 合同 RED**

构造 outdoor 可见 id `{10,30}` 和对象 `{10,20,30}`，断言仅 10/30 进入快照且 30 的 `stream=true`。用 4 个 V1 顶点生成流式 `MeshBuffer`，断言平移已烘焙且 stride/index 与普通路径相同。构造近/远两个植被实例和两级 error `{0,0.02}`，断言远距离选择 coarse LOD 且批次引用对应 mesh。

容量/原子性用 sentinel 检查：

```c
WorldFrameSnapshot out;
memset(&out, 0x5a, sizeof(out));
WorldFrameSnapshot before = out;
WorldPresentationInput in = valid_input;
in.object_count = WORLD_PRESENT_MAX_OBJECTS + 1u;
ASSERT_EQ(world_presentation_snapshot(&in, &out), WORLD_PRESENTATION_OVERLOAD);
ASSERT_EQ(memcmp(&out, &before, sizeof(out)), 0);
```

- [ ] **Step 2: 运行并确认 RED**

Run: `cmake --build build-world-normal --target test_world_presentation -j3 && ./build-world-normal/test_world_presentation`
Expected: 新模块/函数缺失或行为断言失败。

- [ ] **Step 3: 实现验证后写入**

先验证全部计数、指针、36 字节 stride、RHI 句柄、材质有限值、LOD error 和可见集容量，再清零并写输出。VisArea dropped 非零返回 `OVERLOAD`。LOD 使用 `lod_instance_select`，排序使用 `lod_bucket_instances`；任何可能的失败都发生在修改输出和 LOD state 之前。实例 matrix 使用 `mat4_translation`，普通和流式 draw 使用同一记录类型。

- [ ] **Step 4: 运行并确认 GREEN**

Run: `cmake --build build-world-normal --target test_world_presentation test_visarea test_vegetation test_time_of_day test_world_stream_world -j3 && ctest --test-dir build-world-normal -R 'test_(world_presentation|visarea|vegetation|time_of_day|world_stream_world)$' --output-on-failure`
Expected: 5/5 PASS。

- [ ] **Step 5: 可见性、LOD、流式变异**

分别临时让过滤器保留所有对象、LOD 恒为 0、流式 helper 跳过 legacy 迁移；每次确认对应测试 RED，恢复后 GREEN。保存命令输出供最终报告引用。

- [ ] **Step 6: 提交本任务**

`git add engine/src/renderer/world_presentation.* engine/tests/test_world_presentation.c engine/CMakeLists.txt && git commit -m "world: build visible lod render snapshots"`

### Task 4: RHI 实例资源与共享提交路径

**Files:**
- Modify: `engine/src/renderer/world_presentation.h`
- Create: `engine/src/renderer/world_presenter.c`
- Create: `engine/tests/test_world_presenter_fake.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `WorldPresenter { object_pipeline, vegetation_pipeline, white, sampler, instances, ready }`。
- Produces: `bool world_presenter_create(RHIDevice *, WorldPresenter *)` / `void world_presenter_destroy(RHIDevice *, WorldPresenter *)`。
- Produces: `WorldPresentationStatus world_presenter_submit(RHICmdBuffer *, WorldPresenter *, const WorldFrameSnapshot *, WorldSubmitStats *)`。

- [ ] **Step 1: 写提交 RED**

fake 记录 pipeline/vertex/index/texture/texel/uniform/update/draw。快照包含一个普通、一个流式、两个同 prototype/LOD 植被和一个隐藏对象。断言普通与流式 pipeline 相同；植被只发一个 batch，`instance_count==2`，上传两个 matrix；隐藏 mesh 从未绑定；stats 的 `stream_draws==1`、`instance_count==2`。

- [ ] **Step 2: 运行并确认 RED**

Run: `cmake --build build-world-normal --target test_world_presenter_fake -j3 && ./build-world-normal/test_world_presenter_fake`
Expected: presenter API 缺失或提交断言失败。

- [ ] **Step 3: 实现事务创建和预验证提交**

创建失败逆序清理并清空整个 presenter。提交先验证所有 draw/batch 的计数、stride 和句柄，失败时不发命令。普通/流式共同调用 `mesh_gpu_draw_desc(...,1)`；植被一次 `rhi_cmd_update_buffer`，每批设置 instance offset 并调用 `mesh_gpu_draw_desc(...,batch.count)`。实例上传最大 `1024*64==65536` 字节，符合 Vulkan update 上限。

- [ ] **Step 4: 运行并确认 GREEN**

Run: `cmake --build build-world-normal --target test_world_presenter_fake test_world_presentation -j3 && ctest --test-dir build-world-normal -R 'test_world_(presenter_fake|presentation)$' --output-on-failure`
Expected: 2/2 PASS。

- [ ] **Step 5: 提交本任务**

`git add engine/src/renderer/world_presentation.* engine/tests/test_world_presenter_fake.c engine/CMakeLists.txt && git commit -m "world: submit stream and vegetation through RHI"`

### Task 5: Vulkan/OpenGL 真实像素验收

**Files:**
- Create: `engine/tests/test_world_presentation_gpu.c`
- Modify: `engine/CMakeLists.txt`
- Modify: `engine/tests/gl_fallback_whitelist.txt`（仅注册明确 GL fallback 测试）

**Interfaces:**
- Consumes: Task 1–4 全部公共 API。
- Produces: 同一测试源码的 `test_world_presentation_vk` 与 `test_world_presentation_gl` 图形目标；无 display/device 返回 77。

- [ ] **Step 1: 注册像素合同并以变异验证 RED**

测试以 128x128 绘制：左下普通 quad 使用红/品红双色纹理，右下为 V1 流式绿色 quad，上方为两个蓝色实例 quad；VisArea 排除黄色全屏 quad。断言红/绿/蓝/品红像素均超过阈值、黄色为 0，并比较实际 `time_of_day_eval` 正午/午夜帧的亮度。像素测试是在核心实现后添加的，初次运行即绿，没有独立前置 RED；临时跳过流式 draw 后绿色计数为 0，得到明确 RED，恢复后再转绿。

- [ ] **Step 2: 在可用后端确认最终 GREEN**

Run: `cmake --build build-world-vk --target test_world_presentation_vk test_world_presentation_gl -j3 && ctest --test-dir build-world-vk -R 'test_world_presentation_(vk|gl)$' --output-on-failure`
Expected: 设备可用时两者 PASS；若设备不可用，逐项记录 77 和原因，不写“画面通过”。

- [ ] **Step 3: 检查真实证据**

输出 backend、device、各颜色像素数、昼夜亮度和 screenshot 路径。检查 Vulkan validation error 为 0；OpenGL 仅作为独立 fallback 运行，生产默认配置仍为 Vulkan。

- [ ] **Step 4: 提交本任务**

`git add engine/tests/test_world_presentation_gpu.c engine/CMakeLists.txt engine/tests/gl_fallback_whitelist.txt && git commit -m "test: verify world presentation pixels"`

### Task 6: 全量 focused 验证、只读评审与交付

**Files:**
- Create: `.superpowers/sdd/world-presentation-report.md`
- Modify: 仅评审确认的 P6 文件

- [ ] **Step 1: normal 与既有回归**

Run: `cmake --build build-world-normal -j3 && ctest --test-dir build-world-normal -R 'test_(mesh_|world_|vegetation$|time_of_day$|visarea$|rhi_)' --output-on-failure -j3`
Expected: 所有非图形 PASS；图形单独记录，不用正则跳过后来冒充执行。

- [ ] **Step 2: ASan+UBSan 与 TSan focused**

配置 `build-world-asan`（`ENGINE_USE_ASAN=ON ENGINE_USE_UBSAN=ON`）和 `build-world-tsan`（`ENGINE_USE_TSAN=ON`），均 `ENGINE_BUILD_TESTS=ON`。构建上述 world/mesh 目标并串行运行 focused CTest；全部 `-j3`，报告环境不支持 TSan 的真实诊断（若有）。

- [ ] **Step 3: 只读 reviewer 审查**

审查要求覆盖资源失败原子、快照线程边界、Vulkan/GL 布局/push offset、实例缓冲上限、VisArea 过滤、V1 兼容和测试真实性。只修 Critical/Important；修复后重跑受影响 normal/sanitizer/graphics 测试。

- [ ] **Step 4: 最终检查与提交**

Run: `git diff --check && git status --short`
Expected: 无 whitespace error，无测试生成物进入提交。报告列出每个提交、RED/GREEN/变异证据、normal/ASan+UBSan/TSan/graphics 命令及结果、设备限制和未验证平台；最终提交到 `cry-wave2-world`，不 push/PR。

## Fix round 1：agent-179 独立评审

- [x] `mesh_buffer_from_legacy` 在输出写入前验证空输入；整个对象 sentinel 先 RED 后 GREEN。
- [x] GL/VK `rhi_pipeline_create` 在 GPU 分配前仅接受 mesh stride 0/28/36；真实后端合同覆盖合法 0/28/36 和非法 12/32/64，先 RED 后 GREEN。
- [x] GL 缺失 albedo location 创建失败并清理；Vulkan sampler 无 push offset 仍合法。fake 同时覆盖两条路径和资源计数。
- [x] LOD 在修改 state 前验证 projection factor、距离、pixels-per-unit 和误差乘积；两个极端有限输入用例先 RED 后 GREEN。
- [x] 公共注释明确快照存储、GPU 句柄和 presenter 销毁必须等待对应 in-flight 帧完成。
- [x] fake 覆盖 1024 实例/65536 字节成功与 1025 实例 pre-command OVERLOAD。该行为原本已正确；以临时少写 64 字节的变异获得真实 RED，再恢复正确实现取得 GREEN，不把变异称为生产 bug。

最终验证沿用本计划的 normal/ASan+UBSan/TSan focused 命令，并重新运行真实 `test_world_presentation_vk`、`test_world_presentation_gl` 与 GL-only 像素目标。
