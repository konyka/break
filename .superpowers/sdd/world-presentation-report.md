# P6 世界呈现报告

日期：2026-11-03
工作树：`/home/timeshift/opensource/break/.worktrees/cry-world`
分支：`cry-wave2-world`

## 状态与提交

状态：P6 请求的受光材质/纹理、28→36 字节迁移、植被实例化与 LOD、昼夜着色参数、VisArea 过滤、V1 流式块统一提交均已实现；focused normal、ASan+UBSan、TSan、真实 Vulkan/OpenGL 像素和 GL-only 回归通过。未 push、未建 PR、未改 master 或 `docs/Implementation_Status.md`。

本地提交：

- `f4e204d3` `world: migrate legacy mesh vertices for textures`：设计/计划、旧顶点迁移、双后端 RHI 顶点布局。
- `d3e4f374` `world: submit lit visible objects and vegetation`：受光管线、CPU 快照、LOD 分桶、RHI presenter、CPU/fake 测试。
- `a89cebc7` `test: verify world presentation pixels`：双后端像素测试、自审修复、GL-only 配置修正和最终文档同步。

报告文件随后单独提交；最终 HEAD 以分支日志为准。

## 实现

- `MeshStageVertex` 保持 28 字节；`MeshVertex` 为 36 字节并追加 UV。`mesh_vertices_migrate`/`mesh_buffer_from_legacy` 保留 position/normal/material，按主法线轴生成平面 UV，quad 继续使用既有索引路径。
- `mesh_pipeline_create_lit` 生成普通/实例两种 GL/VK shader。材质包含 base color、roughness、albedo、sampler；无纹理时使用 presenter 的白色 fallback。片元实际执行纹理采样、方向光、roughness 高光、ambient 和距离雾。
- Vulkan 使用 208 字节 push block 与反射偏移；OpenGL 使用同名 uniforms。两条路径均只调用 RHI。RHI 的 `mesh_stage_vertex` 在 GL/VK 支持 28/36 字节布局，36 字节增加 location 3 UV。
- GameThread 的 `world_presentation_snapshot` 按值复制帧参数、对象、材质、prototype 和实例 matrix；VisArea id 集过滤普通/流式对象。植被 LOD 复用 `lod_instance_select` 和 `lod_bucket_instances`。
- `world_presentation_stream_mesh` 迁移 V1 流式顶点、拒绝非有限值/平移溢出并烘焙块平移；上传后普通与流式对象调用同一个 `mesh_gpu_draw_desc` 和同一条对象管线。
- RenderThread 的 `world_presenter_submit` 在发命令前完整验证快照。实例 matrix 一次写入固定 texel buffer，批次通过 instance offset 读取对应区间，实际 draw 的 instance count 为批次实例数。
- 固定上限：对象 512、植被实例 1024、prototype 8、LOD/prototype 4、批次 32；实例上传上限恰为 65536 字节。构建和提交热路径无动态分配。
- 快照/LOD 状态失败原子；presenter 创建失败逆序清理。提交后的快照不可变，GameThread 不得再写；RenderThread 只读 POD/句柄，存储复用和 GPU 资源销毁由调用者推迟到对应 in-flight 帧完成之后。

主要文件：`engine/src/renderer/mesh_stage.*`、`mesh_buffer.*`、`mesh_gpu.*`、`world_presentation.*`、`world_presenter.c`、`engine/src/rhi/rhi.h`、`rhi_gl.c`、`rhi_vk.c`、`engine/CMakeLists.txt`。测试位于 `engine/tests/test_world_*`、`test_mesh_buffer.c`、`test_mesh_gpu.c`、`world_fake_rhi.*` 和 `gl_fallback_whitelist.txt`。`rhi_headless.c` 的临时改动已完全回退，最终无净差异。

## RED / GREEN 记录

- 顶点迁移先 RED：`mesh_buffer_from_legacy`、`MeshVertex`、UV 字段不存在。实现后 `test_mesh_(stage|buffer|gpu)` 3/3 GREEN。
- 材质管线先 RED：`MeshMaterial`、`mesh_pipeline_create_lit`、材质/昼夜绑定接口不存在。实现后 fake 与 headless 2/2 GREEN。
- 世界快照先 RED：`renderer/world_presentation.h` 不存在。实现后快照及既有 world 测试 5/5 GREEN。
- presenter 先 RED：`WorldPresenter`、提交和统计接口不存在。实现后快照/presenter 2/2 GREEN。
- 自审新增 V1 非有限顶点测试先 RED（helper 错返回 true），修复后 GREEN 且输出保持不变。
- 自审新增非法 VisQuery 测试先触发实际崩溃（空 rooms 在既有函数检查前被遍历）；快照层预验证后 GREEN，非法输入不再进入该调用。
- 像素测试是在核心实现完成后加入的，修正测试 fixture 编译错误后，第一次有效图形运行即 Vulkan/OpenGL 双绿。因此它没有独立的前置 RED，不把该运行冒充 RED；其敏感性由下面的真实流式变异补证。

## 变异证据

每次只临时改一处，运行后恢复：

- 将实际写入 shader 的 sun color 改为零：`test_world_mesh_fake` RED，`sun_color.e[1]` 预期 0.7、实际 0；恢复后 GREEN。
- 绕过 VisArea 过滤：`test_world_presentation` RED，`draw_count != 2`；恢复后 GREEN。
- 将 LOD 选择结果掩为零：RED，`batch_count != 2`；恢复后 GREEN。
- 跳过 V1 legacy 迁移：RED，`mesh.count != 4`；恢复后 GREEN。
- 在 presenter 中只跳过流式 draw：真实 Vulkan 像素测试 RED，`red=400 green=0 blue=800 yellow=0`，明确缺少流式绿色块；恢复后双后端 GREEN。该变异发生在最终双色 UV 断言加入前，但流式颜色/统计断言未变。

## normal / 消毒器

所有构建使用 `-j3`。

最终 normal：

```sh
cmake --build build-world-normal -j3
ctest --test-dir build-world-normal \
  -R 'test_(mesh_|world_|vegetation$|time_of_day$|visarea$|rhi_|no_hidden_gl_fallback)' \
  --output-on-failure -j3
```

结果：完整构建成功，44/44 PASS。覆盖 mesh、world、植被、昼夜、VisArea、流式 job/VFS、fake RHI、RHI 合同、运行时可回退性和图形目标。首次 focused 运行为 43/44，唯一失败是 fake 的 OpenGL capability token 未登记 GL 审计白名单；登记后最终 44/44。

收尾另运行 `ctest --test-dir build-world-normal --output-on-failure -j3`：共 297 项，296 PASS、0 FAIL，只有 `test_d3d12_dependency_gate` 因当前非 Windows 环境按合同 SKIP。

ASan+UBSan：

```sh
cmake -S engine -B build-world-asan -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_BUILD_TESTS=ON -DENGINE_RHI_BACKEND=auto \
  -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON -DENGINE_ENABLE_IPO=OFF
cmake --build build-world-asan --target \
  test_mesh_stage test_mesh_buffer test_mesh_gpu test_world_mesh_fake \
  test_world_presentation test_world_presenter_fake test_vegetation \
  test_time_of_day test_visarea test_world_stream test_world_stream_job \
  test_world_stream_world test_rhi_capabilities -j3
ctest --test-dir build-world-asan \
  -R 'test_(mesh_(stage|buffer|gpu)|world_(mesh_fake|presentation|presenter_fake|stream|stream_job|stream_world)|vegetation|time_of_day|visarea|rhi_capabilities)$' \
  --output-on-failure -j1
```

结果：13/13 PASS，无 ASan/UBSan 报告。

TSan 使用同样目标，配置为 `-DENGINE_USE_TSAN=ON -DENGINE_ENABLE_IPO=OFF`，构建目录 `build-world-tsan`，CTest 正则相同。结果：13/13 PASS，无 TSan 报告。该范围含真实 task 流式 job 测试，但不是完整 GameThread/RenderThread 并发压力证明。

## 真实图形证据

`build-world-vk` 的 `ENGINE_RHI_BACKEND=auto` 解析为 Vulkan，并链接 OpenGL 最终降级。同一测试源码分别创建真实设备，执行 128x128 正午/午夜各三帧并读回像素；不是 headless/fake 证据。

最终直接运行：

```sh
./test_world_presentation_vk
./test_world_presentation_gl
```

工作目录：`build-world-vk`。两后端一致：

- `red=200 green=400 blue=800 magenta=200 yellow=0`
- `day_luma=462000 night_luma=18200`
- 普通对象/流式对象/实例统计分别为 2/1/2，植被一个双实例 batch。
- 红/品红双色普通块证明实际纹理 UV；绿色块来自 V1 流式网格；两个蓝色块直接消费 `vegetation_build` 布局；黄色 VisArea 隐藏全屏网格未出现；午夜显著变暗。
- Vulkan 设备：NVIDIA RTX A5000 Laptop GPU，`validation_messages=0`。
- OpenGL 设备：Mesa Intel UHD Graphics (TGL GT1)，OpenGL 4.6 compatibility profile。
- 两后端 PPM 已写入构建目录并实际转换/查看过对应 PNG，图像与计数一致。

GL-only 配置也实际验证：

```sh
cmake -S engine -B build-world-gl -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_BUILD_TESTS=ON -DENGINE_RHI_BACKEND=opengl
cmake --build build-world-gl --target test_mesh_gpu_gl test_world_presentation_gl -j3
ctest --test-dir build-world-gl -R 'test_(mesh_gpu_gl|world_presentation_gl)$' \
  --output-on-failure -j3
```

结果：2/2 PASS，包括迁移后的既有 mesh GL 路径。GL-only 初次链接暴露 Vulkan validation 符号未裁剪，已用 `ENGINE_VULKAN` 编译期 guard 修复并重跑通过。

## 只读自审

自审覆盖资源失败原子、快照所有权、批次覆盖/溢出、实例上传上限、GL/VK 布局、push 反射、V1 兼容、像素断言真实性。未调用独立 reviewer 子代理。

修复的 Important：

- headless capability 临时实现与 `rhi.c` 重复定义，已由 `test_rhi_capabilities` 链接 RED 复现；改为 `test_mesh_gpu` 局部 fail-closed 桩，最终公共后端无净改动。
- V1 非有限顶点与非法 VisQuery 边界，见 RED 记录。
- GL-only 的 Vulkan validation 链接依赖，见图形记录。

未发现遗留 Critical/Important。

## 限制

- 仅验证 Linux X11 的 Vulkan/OpenGL；未验证 Windows/D3D12、Metal、Wayland 或真实多 GPU 切换。
- TSan focused 通过不替代完整渲染线程并发压力测试；快照不可变和 GPU 资源延迟销毁是需要调用者遵守的明确合同。
- 像素场景是有代表性的固定合同，不是完整 CryENGINE 材质系统、阴影或全部纹理格式 parity 证明。
- 未改全局实现状态文档，未 push，未运行远程 CI。
