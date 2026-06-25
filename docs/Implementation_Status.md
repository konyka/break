# Break 引擎 — 实现状态矩阵（唯一事实来源）

> 本文档是各模块"真实实现程度"的唯一事实来源（single source of truth）。
> 它依据源码逐一核查，纠正 `PureC_Engine_ExecutionPlan.md` 中被高估为"全部完成"的标记。
> 状态分级：完整 / 部分 / 桩(占位) / 缺失。每轮补全工作完成后更新对应行。

最近更新：**R117 BVH/光照 calloc NULL 检查** — **R117-1**（ROBUSTNESS）：BVH SAH 构建路径 5 处内存分配未检查返回值：`bvh_init` calloc 失败时 `bvh->nodes=NULL` 后续崩溃；`bvh_alloc_node` realloc 失败时旧指针泄漏 + `bvh->nodes` 置 NULL；`bvh_build` 中 leaf_map/nodes/_build_indices 三处 calloc/malloc 失败解引用 NULL。修复：全路径 NULL 检查，realloc 使用临时指针避免泄漏。**R117-2**（ROBUSTNESS）：`light_system_upload_grid` 中 staging buffer calloc 未检查 NULL，OOM 时后续 `memcpy` 崩溃。修复：添加 NULL 检查 + LOG_ERROR。审查确认 3 个子系统（地形、异步加载、遮挡剔除）无需修复。23/23 测试通过。
此前：**R116 字体/脚本/ECS/LOD 防御性加固** — **R116-1**（ROBUSTNESS）：`font_renderer_init` 中着色器源码 `malloc` 和 `quad_data` `malloc` 未检查 NULL，失败时 `fread(NULL, ...)` 崩溃。修复：添加 NULL 检查。**R116-2**（ROBUSTNESS）：`script_load` 中 `ftell` 返回 -1 时 `malloc(0)` 可能返回非 NULL，`fread` 读取 `SIZE_MAX` 字节溢出；`malloc` 返回 NULL 时崩溃。修复：`sz < 0` 提前返回 + NULL 检查。**R116-3**（ROBUSTNESS）：ECS 核心路径多处 `calloc`/`malloc`/`realloc` 未检查返回值（`chunk_alloc`、`create_archetype`、`world_create`、`world_add_component`、`world_remove_component`、`world_query`/`ecs_query_refresh`），失败时解引用 NULL 崩溃。修复：全路径添加 NULL 检查，query 路径降级不崩溃。**R116-4**（ROBUSTNESS）：`lod_select_by_*` 中 `level_count - 1` 当 `level_count==0` 时 u32 下溢为 `UINT32_MAX`，越界读 `thresholds_sq`。修复：`lod_register` 拒绝 `level_count==0`。审查确认 11 个子系统（延迟渲染、点光阴影、相机、视锥剔除、分配器、池分配器、性能分析器、Lua 脚本、场景序列化、输入、日志）无需修复。23/23 测试通过。
此前：**R115 网络复制缓冲区溢出 + glTF 资产加载防御性加固** — **R115-1**（ROBUSTNESS）：`net_replicator_process` 未检查 `len > PACKET_MAX_SIZE`，导致 `net_reorder_store` 中 `memcpy(slot->wire, wire, len)` 溢出 1400 字节缓冲区。公共 API `net_replicator_feed`/`net_replicator_feed_from` 接受任意 `len`。修复：入口添加 `len > PACKET_MAX_SIZE` 检查。**R115-2**（ROBUSTNESS）：`asset_load_gltf` 中多处 `calloc`/`malloc` 缺少 NULL 检查，分配大小来自不可信 glTF 文件数据。修复：添加 NULL 检查。**R115-3**（ROBUSTNESS）：`cgltf_buffer_data` 返回值未检查 NULL（R109-2 已使该函数可返回 NULL）。修复：循环条件添加 NULL 守卫。审查确认 8 个子系统（物理、动画、渲染图、命令缓冲、任务系统、网络核心、包序列化、主循环）无需修复。23/23 测试通过。
此前：**R114 平台窗口管理与手柄输入审查（无需修复）** — 审查全平台窗口管理（window_x11.c 381 行 / window_wayland.c 719 行 / window_win32.c 518 行）、手柄输入（gamepad_linux.c 421 行 / gamepad_win.c 178 行）、剔除辅助（cull.c 31 行）。所有文件代码质量高：calloc + NULL 检查、资源释放完整、strncpy + memset 安全、设备热插拔处理完善。审查未发现问题，无需代码修改。
此前：**R113 SSGI uniform 位置硬编码 + VK buffer_update NULL deref 修复** — **R113-1**（CORRECTNESS）：`ssgi_init` 硬编码 blur uniform 位置 `loc_blur_dir_x = 0`，但 GL 链接器不保证 `u_direction` 在位置 0。`post_process.c` 正确查询了该位置，`ssgi.c` 遗漏。修复：用 `rhi_pipeline_get_uniform_location` 查询，并添加 `>= 0` 守卫。**R113-2**（ROBUSTNESS）：VK `rhi_buffer_update`/`rhi_buffer_update_region` fallback 路径 `vkMapMemory` 失败时 `mapped` 未定义，`memcpy` 崩溃。修复：检查返回值。审查确认 19 个子系统（全后期处理小文件、骨骼动画、引擎核心、RHI 句柄管理、平台时间）无需修复。23/23 测试通过。
此前：**R112 test_vulkan.c file_read 防御性加固（全引擎 read_file 统一完成）** — **R112-1**（ROBUSTNESS）：`test_vulkan.c` 的 `file_read` 缺少 `ftell` 返回值检查和 `malloc` NULL 检查，是引擎中最后一个未加固的 `read_file` 实现。R110 修复了 `particles.c` 和 `water.c`，R112 修复了 `test_vulkan.c`，至此全引擎 28 个 `read_file`/`file_read` 实现全部完成统一加固。审查确认 10 个子系统（光照系统、SSAO、Tonemap、Mipmap 流式加载、DoF、SSR、TAA、FileWatch Windows/Linux、全引擎 read_file 验证）无需修复。23/23 测试通过。
此前：**R111 GPU 剔除初始化验证 + 热重载路径终止修复** — **R111-1**（ROBUSTNESS）：`gpucull_init` 创建 3 个 GPU 缓冲区后未验证有效性就设置 `ready = true`。修复：添加三缓冲区有效性检查，失败时 `gpucull_shutdown` 清理并返回 false。**R111-2**（ROBUSTNESS）：`hotreload_pipeline_init` 未 `memset` 结构体就 `strncpy` 路径。修复：入口添加 `memset(hr, 0, sizeof(*hr))`。审查确认 12 个子系统无需修复。23/23 测试通过。
此前：**R109 字符串/glTF 资产加载防御性修复** — **R109-1**（ROBUSTNESS）：`str_copy` 当 `buf_size==0` 时，`buf_size-1` 无符号下溢为 `SIZE_MAX`，使长度钳制失效，`memcpy` 向零大小缓冲区写入 `s.len` 字节。修复：入口添加 `buf_size==0` 提前返回。**R109-2**（ROBUSTNESS）：`cgltf_buffer_data` 未检查 `bv->buffer`/`bv->buffer->data` 空指针。当 `buffer->data` 为 NULL 时返回 `NULL+offset` 悬空指针，调用者的 NULL 检查无法拦截。修复：添加 `!bv->buffer || !bv->buffer->data` 检查返回 NULL。**R109-3**（ROBUSTNESS）：`load_gltf_texture` 路径拼接 `memcpy(tex_path, gltf_path, dir_len)` 当 `gltf_path` 超过 512 字节时栈缓冲区溢出。修复：钳制 `dir_len` 不超过 `sizeof(tex_path)-1`。审查确认 10 个子系统（渲染图、命令缓冲、CSM 阴影、点光阴影、延迟渲染、后期处理、材质系统、字符串工具、glTF 加载、场景世界变换）无需修复。23/23 测试通过。
此前：**R108 场景序列化边界验证修复** — **R108-1**（ROBUSTNESS）：`scene_load_binary` 读取 BSCN 文件后直接访问 chunk 表和 chunk 数据，未验证偏移+大小是否在文件缓冲区内。畸形文件的 `offset=0, size=0xFFFFFFFF` 会使 `rd_bytes` 的边界检查通过（差值巨大）但 `memcpy` 读取缓冲区外内存。修复：读取 header 后验证 chunk 表 `table_off + chunk_count * sizeof(BscnChunkEntry) <= fsz`；每个 chunk 访问前验证 `offset + size <= fsz`（使用 u64 避免溢出）。审查确认 10 个子系统（Arena/Heap/Pool 分配器、Profiler、输入系统、Frustum culling、LOD、相机、场景 JSON 路径、组件加载）无需修复。23/23 测试通过。
此前：**R107 音频流槽位泄漏修复** — **R107-1**（CORRECTNESS）：`audio_stream_open`/`audio_stream_open_3d` 在 `audio_play_streamed` 失败时未将已分配的流槽位归还自由链表，每次打开失败永久泄漏一个槽位，最终导致 `AUDIO_STREAM_MAX_SOURCES` 次失败后所有槽位耗尽。修复：在失败路径中添加 `free_next[idx] = next_free; next_free = idx` 归还槽位。审查确认 9 个子系统（物理 CCD、角色控制器、动画 IK、网络序列化、网络复制、地形、任务系统、脚本、Pool allocator）无需修复。23/23 测试通过。
此前：**R106 VK 帧开始状态重置 + GL 缓存失效修复** — **R106-1**（CORRECTNESS）：VK `rhi_frame_begin` 调用 `vkResetDescriptorPool` 释放所有描述符集后，未重置 `storage_set_valid`（仍为上一帧 `true`）和 `current_pipeline_data`（仍指上一帧管线）。若新帧中 `rhi_cmd_bind_storage_buffer` 在 `rhi_cmd_bind_pipeline` 之前调用，会使用被释放的悬空描述符集句柄执行 `vkUpdateDescriptorSets` → UB。修复：帧开始时添加 `current_pipeline_data = NULL` + `storage_set_valid = false`。**R106-2**（CORRECTNESS）：GL 后端 `g_tex_cache[16]`/`g_sam_cache[16]`/`g_gl_ssbo_cache[8]` 绑定缓存在 `rhi_texture_destroy`/`rhi_cubemap_destroy`/`rhi_sampler_destroy`/`rhi_buffer_destroy` 时未失效。GL 删除对象后绑定点恢复为 0，但缓存仍持有旧 GL name；GL 复用 name 时缓存误判为“已绑定”跳过实际绑定。修复：在每个 destroy 函数中遍历对应缓存清除匹配条目；`g_gl_ssbo_cache` 从 static 局部提升为文件作用域。23/23 测试通过。
此前：**R105 VFS NULL 检查 + packer 缓冲区边界检查** — **R105-1**（ROBUSTNESS）：`vfs_mount_dir`/`vfs_mount_pak` 添加 NULL 路径检查 + 显式 null 终止。**R105-2**（ROBUSTNESS）：packer `add_file` 在 `memcpy` 前检查 `g_name_size + name_len` 边界。23/23 测试通过。
此前：**R104 decode pipeline 优先级队列修复** — **R104-1**（PERF）：`input_queue_push` 从 FIFO 追加改为优先级排序插入，低 priority 值 = 高优先级（与 async loader min-heap 一致）。23/23 测试通过。
此前：**R103 ECS 查询增强 + 延迟点光阴影 + 异步加载优先级解码管线 + Windows Packer** — **R103-1**（FUNC）：ECS 查询新增 Exclude/Optional 组件支持，位掩码 O(1) 过滤。新增 API：`ecs_query_exclude`（排除含指定组件的原型）、`ecs_query_optional`（可选组件，匹配但跳过不含的原型）、`ecs_query_refresh`（查询失效时重建匹配原型列表）。`Query` 结构扩展 `exclude_mask`/`optional_mask` 位域，`query_matches_archetype` 用位运算一次判定，避免遍历排除列表。`test_ecs` 新增 5 项 Exclude/Optional 测试。**R103-2**（FUNC）：`deferred_light.frag`/`deferred_light_vk.frag` 接入点光 cubemap 阴影采样（`HAS_POINT_SHADOW` 条件编译）；前向管线 `blinn_phong_clustered`/`pbr_clustered` 双后端同步 `HAS_POINT_SHADOW` 守卫；`PointLight` 增加 `shadow_index` 字段指向 cubemap 阴影槽位；`deferred.c` 绑定点光阴影纹理到延迟光照 pass。**R103-3**（FUNC）：异步加载器 priority 最小堆替换 FIFO 队列，高优先级请求（如 mipmap）优先出队；新增 2-worker 解码线程池 `decode_pipeline.c/h`，stb_image 解码 + mipmap 生成不阻塞主线程，解码完成后回调主线程上传 GPU。`test_async_loader` 新增优先级和解码管线测试。**R103-4**（FUNC）：Windows packer 重写为 `CreateFileMapping` 零拷贝打包（内存映射直读文件数据，无额外 memcpy），`FindFirstFile`/`FindNextFile` 递归遍历目录，与 POSIX 版二进制兼容（相同 `VFS_PAK_MAGIC` + 字节序 + 对齐）；新增 `verify_pak.c` 验证工具。
此前：**R102 ECS archetype edge 缓存** — **R102**（PERF）：`world_add_component`/`world_remove_component` 的目标 archetype 查找从 O(N) 线性扫描降为 O(E) edge 查找。首次 add/remove 某 component 仍走 `find_archetype` 并缓存结果到 `edges_add[]`/`edges_remove[]`；后续相同 component 的转换直接用缓存的 `target` 指针。`ArchetypeEdge` 结构与字段此前已定义但为桩，现已完整实现四个辅助函数。`test_ecs` **23/23** 通过。
此前：**R101 冗余遮挡剔除消除 + 动画事件回调触发** — **R101-1**（PERF）：当 unified cull 路径全激活时（`mega_buf.valid && unified_forward_enabled`，即 mega-buffer 默认生效），`occlusion_cull_dispatch` 的结果无人消费——`node_occ_visible()` 不被调用因为 CPU 回退路径被跳过。跳过该 dispatch 每帧节省 1 compute pipeline bind + 3 SSBO/texture bind + 4 uniform set + 1 dispatch + 1 barrier + 1 buffer copy。Hi-Z 生成仍然运行（unified_cull 采样它）。当 unified 关闭或 mega-buffer 无效时照常 dispatch。**R101-2**（FUNC）：动画事件回调从“存储但不触发”改为在 `anim_blend_evaluate` 中按时间区间检测并触发。新增 `AnimEvent` 结构体（时间戳+名称）、`AnimClip.events[]` 事件轨道（最多 32 条）、`anim_clip_add_event()` API。支持循环 wrap-around（两段区间检测）。`test_animation` 新增 4 项事件测试（触发/循环 wrap/无回调安全/上限裁断），**24/24** 通过。
此前：**R86 关键bug修复 + 粒子GPU回读消除 + VBO/IBO绑定缓存 + sun_color缓存** — **R86-1**（CRITICAL）：R85 引入的 blinn_phong_clustered 平方链错误。**R86-2**（HIGH）：粒子 GPU 回读消除。**R86-3**（MEDIUM）：VBO/IBO 绑定缓存。**R86-4**（LOW）：sun_color 缓存。23/23 测试通过。

此前：**R82 静态数据生命周期优化：遮挡剔除AABB缓存 + 遗留gpucull跳过 + 点阴影per-face uniform提升 + occ节点映射移至init** — R82-1 遗留gpucull跳过、R82-2 AABB缓存、R82-3 点阴影per-face uniform提升、R82-4 occ节点映射移至init。23/23 测试通过。

此前：**R79 FBO绑定缓存 + 纹理上传缓存失配修复 + buffer尾部解绑消除 + scissor状态缓存** — R79-1 FBO绑定缓存、R79-2 纹理上传缓存失配修复、R79-3 buffer尾部解绑消除、R79-4 scissor状态缓存。23/23 测试通过。

此前：**R78 cubemap缓存修复R77回归 + skybox深度缓存 + 点阴影FBO解绑批处理** — R78-1 cubemap缓存修复、R78-2 skybox深度缓存、R78-3 点阴影FBO解绑批处理。23/23 测试通过。

此前：**Round 30 完成** — DrawBench 导出 + NetRep peer 持久。**DrawBench export(R30-1)**：CSV ring + Chrome meta；`BREAK_DRAW_BENCH_EXPORT`；F11 联动。**Peer persist(R30-2)**：`peer_save/load` + `BREAK_NETREP_PEER_FILE`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 29 完成** — DrawBench GPU 对比 + NetRep peer 老化。**GPU bench(R29-1)**：unified/legacy 路径 GPU timer 均值；UI `gpu_u=`/`gpu_l=`。**Peer TTL(R29-2)**：`last_seen_ms` + LRU/TTL 淘汰；`BREAK_NETREP_PEER_TTL`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 28 完成** — DrawBench mega/legacy 对比 + NetRep 多 peer RTT。**DrawBench(R28-1)**：`BREAK_DRAW_BENCH=1` 帧内 mega vs legacy draw 估算；debug UI ratio。**Peer RTT(R28-2)**：`NetRepPeerStats[8]` + `net_address_equal()`；UI 列出 peer。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 27 完成** — Unified env 矩阵文档 + NetRep 双向 RTT。**Unified docs(R27-1)**：`Round11_Performance_Plan.md` 增 shadow/forward/deferred + NetRep env 矩阵表。**Heartbeat echo(R27-2)**：`NET_PKT_HEARTBEAT_ACK` + 自动 echo；`hb_roundtrip_ms`；UI `echo=`/`rt=`；`BREAK_NETREP_HB_ECHO=0`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 26 完成** — Unified forward/deferred 默认化 + NetRep heartbeat demo。**Unified default(R26-1)**：mega-buffer 默认 forward+deferred unified vis；`=0` 关闭。**Heartbeat(R26-2)**：60 帧周期 heartbeat + RTT；debug UI `hb=`/`rtt=`；`BREAK_NETREP_HEARTBEAT=0`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 25 完成** — Unified shadow 默认化 + NetRep 多类型 channel。**Unified shadow default(R25-1)**：mega-buffer 有 mat groups 时默认 shadow per-material；`BREAK_UNIFIED_SHADOW=0` 关闭。**NetRep multitype(R25-2)**：按 packet type 独立 unreliable/ordered 序列；`NET_PKT_HEARTBEAT` + `net_replicator_send_heartbeat()`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 24 完成** — Shadow per-material unified + NetRep 双通道。**Unified shadow(R24-1)**：`BREAK_UNIFIED_SHADOW=1` CSM/点光 unified vis + 按材质 indirect。**NetRep channels(R24-2)**：unreliable/ordered 双序列号 + `NetRepReliablePending`；接收按 `PACKET_ORDERED` 路由；`dual_channel_sequences` 单测。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 23 完成** — Unified 延迟独立开关 + NetRep 可靠有序组合。**Unified deferred(R23-1)**：`BREAK_UNIFIED_DEFERRED=1` G-Buffer mega 路径单独 unified vis + per-material；与 `BREAK_UNIFIED_FORWARD` 解耦。**NetRep combo(R23-2)**：`BREAK_NETREP_RELIABLE_ORDERED=1`；重传重复包 `reorder_duplicate` 抑制；`reliable_ordered_combined` 单测。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 22 完成** — Unified per-material + NetRep 有序层。**Unified per-material(R22-1)**：`unified_cull.comp` binding 4 `VisibleFlags`；`mega_unified_vis_flags` + `mega_mat_groups_draw`；`BREAK_UNIFIED_FORWARD=1` 前向/延迟 mega 路径单 dispatch 后按材质 indirect。**NetRep ordered(R22-2)**：`PACKET_ORDERED` 32-slot 重排 buffer；`BREAK_NETREP_ORDERED=1`；`test_net_replication` 乱序单测。**VK(R22-3)**：compute storage layout 扩至 8 binding。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 21 完成** — Unified 前向 + Forward Velocity + NetRep 可靠层。**Unified forward(R21-1)**：`BREAK_UNIFIED_FORWARD=1` mega-buffer 单 dispatch（Hi-Z+frustum+compact）。**Forward velocity(R21-2)**：`BREAK_FORWARD_VEL=1` camera motion 纹理供 TAA。**NetRep reliable(R21-3)**：`BREAK_NETREP_RELIABLE=1` ACK+重传。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 20 完成** — 前向点光阴影 + Animation IK + NetRep 去重。**Forward pt shadow(R20-1/R12-3)**：`pbr_clustered` 采样 binding 10 cubemap；push/uniform 传 light slot 映射。**Anim IK(R20-2)**：`BREAK_ANIM_IK=1` + `skeleton_compute_world_transforms` + 轨道 target。**NetRep dedup(R20-3)**：序列号过滤 stale 包；`BREAK_NETREP_DEDUP=0` 关闭。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 19 完成** — 后处理合并 + 动画混合 + NetRep 插值。**Combined color+cinematic(R19-1)**：移除 `!cine_enabled` 门禁，combined pass 传入 vignette/grain/aberration，跳过独立 cinematic pass。**Anim blend(R19-2)**：`skeleton_apply_local_trs` + `BREAK_ANIM_BLEND=1` + F12 crossfade。**NetRep lerp(R19-3)**：ghost target 线性插值；`BREAK_NETREP_LERP=0` 即时 snap。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 18 完成** — TAA history + 延迟点光阴影 + 网络 ghost。

此前：**Round 17 完成** — Combined AA motion + Demo 接线。**Combined AA(R17-1)**：`combined_aa_apply` 可选 velocity 纹理；`combined_taa_fxaa*.frag` 增 per-pixel motion 重投影（VK push `u_taa_use_velocity@212`）；延迟路径 combined AA 绑定 `gbuf_velocity`。**NetRep demo(R17-2)**：`BREAK_NETREP=1` UDP :19900 loopback 广播角色 transform；debug UI 显示 sent/recv。**Hot reload tex(R17-3)**：`BREAK_HOTRELOAD_TEX=<path>` 监视并重载 `fallback_tex`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 16 完成** — 剔除深化 + TAA motion。**Unified Hi-Z(R16-1)**：`unified_cull.comp` 可选 Hi-Z 球体测试；阴影 unified 路径传入上一帧 Hi-Z；fallback 1×1 纹理满足 VK descriptor。**Velocity G-Buffer(R16-2)**：延迟 MRT RT3 写 NDC motion vector；gbuffer 传 `u_prev_vp`。**TAA(R16-3)**：`taa_resolve` 可选 velocity 纹理；延迟路径自动用 `gbuf_velocity`。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 15 完成** — 工具链与长期质量。**Profiler(R15-1)**：`profiler_export_chrome_trace()` 导出 Chrome Trace JSON（CPU regions + GPU timer 样本）；demo 按 **F11** 或 `PROFILER_TRACE=1` 退出时写 `profile_trace.json`。**Golden(R15-2)**：`test_vulkan` 双后端条件编译（GL 仅 golden 回归；VK 全集成套件）；新增 `tests/golden/test_vulkan_gl.ppm`；GL 构建纳入 CTest。**Network(R15-3)**：`net_replication.{h,c}` transform 快照 unreliable UDP 广播/接收；`test_net_replication` loopback 测。**回归**：VK CTest **31/31**、GL **31/31**。

此前：**Round 13 完成** — 延迟光照质量 + TAA 重投影 + combined/auto-exposure 共存。**Deferred(R13-1)**：`deferred_light.frag`/`deferred_light_vk.frag` 接 `light_data`/`light_grid` cluster、CSM PCSS(`shadow_test`)、split-sum IBL(`HAS_IBL`)；去掉 5% 硬编码环境光；`deferred_lighting_pass` 绑定 texel buffer + IBL；deferred 路径每帧 `light_system_cull`/`upload`。**TAA(R13-2)**：`combined_aa`/`taa_resolve` 传 `inv(curr_view_proj)` 而非 `inv(proj)` 修复相机 motion 重投影。**Combined color(R13-3)**：`combined_color_apply` 扩展 exposure/gamma/tonemap_mode/cinematic 参数；先 `tonemap_update_auto_exposure` 再 combined pass 读 `tonemap.exposure`；移除 `!auto_exposure` 门禁。**回归**：VK CTest **30/30**、GL **29/29**。

此前：**Round 12 完成** — unified 剔除默认化 + 粒子 GPU cull。

此前：**Round 11 完成** — 性能路径默认生效：剔除闭环 + 合并后处理接入 demo。**遮挡 Hi-Z(R11-1)**：`main.c` 建立 `scene node → occ 紧凑索引` 映射(`occ_rebuild_node_map`/`node_occ_visible`)，与 Hi-Z upload 同序；前向 mega-buffer indirect 路径 `vis_flags &= occlusion(上一帧)`，CPU frustum 回退路径跳过被挡节点；默认开启 1 帧延迟 Hi-Z(`occ_cull_enabled=true`，`BREAK_OCCLUSION=0` 可关)；debug UI 显示 culled/occ 对象数。**GPU 剔除默认(R11-2)**：`mega_buf.valid` 时默认 `gpu_indirect_enabled && gpucull_enabled`，初始化 `gpucull_init_unified` 为 R12 unified 路径铺路；`BREAK_GPUCULL=1` 仍可强制开启。**合并后处理(R11-3)**：demo 初始化/resize `CombinedAA`/`CombinedColor`；TAA+FXAA 均开且 combined 管线就绪→单 pass AA；tonemap+调色+cg 且 `!cine && !auto_exposure`→单 pass 调色；debug UI 显示 CombinedPost on/off。**实测**：双后端 `engine_demo` 构建通过；VK CTest **30/30**、GL CTest **29/29**；`test_vulkan` golden+合并管线子测通过。

此前：**Round 10 完成** — 流式/UI/Core/回归测试全面补齐。**Mipmap 流式**：`mipmap_stream.c` 由桩改为真链路 —— `MipLoadReq` 上下文经 `async_loader_request_range` 把 level 数据写入 `level_data`、按预算计 `total_resident_bytes`、命中后经 `MipmapUploadFn` 钩子真上传 GPU；新增 RHI `rhi_texture_upload_mip`(GL `glTexImage2D` / VK staging+barrier 逐 mip)；修复 `coverage_to_level` 反向 bug(全覆盖应得 level0)；接入 `main.c`(程序化 256² 9-mip 文件、相机距离驱动驻留/驱逐、debug UI 显示 level/驻留/上传/驱逐)。**Audio 流式**：`audio_stream.c` 由不出声的双缓冲框架改为 miniaudio `MA_SOUND_FLAG_STREAM` 真流式后端；audio.c 增 `audio_play_streamed`/`audio_source_set_position`/`_set_attenuation`/`_at_end`/`_cursor_seconds` + 纯函数 `audio_attenuation_gain`(逆距离模型)；`main.c` 生成正弦 WAV 作 3D 音源真播放并显示增益。**字体/UI**：`utf8.{h,c}` 健壮多字节解码；`font.c` 扩 ASCII+Latin-1 字形范围+码点查找表+白像素(实心矩形)；新增 `imgui.{h,c}` 即时模式控件(label/button/checkbox/slider，纯逻辑助手可无头测)接入 demo(反引号切换面板)。**Core**：通用定长 `pool.{h,c}` 分配器(接入 `Alloc` vtable)；GPU timestamp profiler(`RHIGPUTimer` 双后端)接入 demo 命名计时。**回归测试**：`test_vulkan` 增 golden image 子测(读回→降采样→容差比对委 `tests/golden/test_vulkan_vk.ppm`，`GOLDEN_UPDATE=1` 重生)且返回码现汇总全部子测，纳入 CTest(经 `WORKING_DIRECTORY` + `ENGINE_VULKAN` 守卫)。新增 `test_pool`/`test_font_ui`/`test_mipmap_stream`/`test_audio`。**实测**：VK 构建 CTest **30/30**(含 test_vulkan，golden MAE=0.00)；GL 构建 CTest **29/29**(test_vulkan 按后端守卫排除)；VK demo 0 校验错误、GL demo 0 着色器/GL 错误；双后端 demo mipmap/audio 流式均初始化并运行。

此前：**Round 9 完成** — 平台补齐：gamepad 双平台接线(Linux evdev + Windows XInput 经 `platform_poll`→`input.gamepads`)、Wayland 相对指针/指针锁/NULL 光标隐藏(zwp_relative_pointer_v1 + zwp_pointer_constraints_v1，CMake 生成协议绑定)、macOS 经 Cocoa(`window_cocoa.m`, NSWindow+CAMetalLayer)+ MoltenVK 复用 VK 后端可链接(`rhi_vk.c` 加 `VK_EXT_metal_surface`+portability，CMake macos 分支)。`test_input` 增 3 项 gamepad 契约测试。**实测**：X11 双后端 CTest **25/25**；Wayland(VK) 链接通过；macOS 因 Linux 环境未实测构建。

此前：**Round 8 完成** — 场景资源序列化补全。`scene_serial.c` 的 RESOURCES chunk 由空占位改为真实清单：从 `Scene` 的 meshes/materials/textures 派生资源记录，每条含确定性 GUID(对类型+索引+描述符做 FNV-1a 64)；mesh 描述符(index/vertex count、material_idx、AABB)、material 描述符(base_color、metallic/roughness、emissive、alpha mode/cutoff)、texture 按 RHI 句柄身份去重引用。`SerializeOptions.include_resources` 真正生效：true 内联描述符、false 仅写 {guid,type,ref,path} 轻引用。`Scene` 增 `resources`/`resource_count`(load 时回填，`asset_scene_free` 释放，另导出 `scene_resources_free`)。**ECS↔Scene 统一 ID**：`load_entities_chunk` 现恢复保存的 entity `generation`(此前丢弃)，使 (index,generation) 身份跨存读一致，成为持久统一 ID。`test_scene_serial` 扩到 23 项(新增 include 往返、refs-only 往返、GUID 确定性、generation 恢复)。**实测**：双后端构建通过；CTest **25/25**(`test_scene_serial` 内 23 子项全过)。

此前：**Round 7 完成** — 内置真实 Lua 5.4 脚本。vendored Lua 5.4.7 到 `engine/external/lua`(经 `onelua.c` 单编译单元 + `MAKE_LIB` 构建为独立静态库 `lua`，第三方代码用 `-w` 豁免引擎 `-Werror -pedantic`)。新增 `script/script_lua.{h,c}`：真实 `lua_State` + `luaL_openlibs`；`lua_script_load`/`_load_string`(语法/运行期错误经日志优雅失败)、`on_start`/`on_update(dt)`/`on_spawn` 钩子探测与 `pcall` 调用、数值全局 get/set、按 mtime 的 `.lua` 热重载。注册 `engine.*` 绑定表(经 registry 取宿主指针，宿主指针为 NULL 时全部安全降级)：`log`/`entity_count`/`body_count`/`get_pos`/`set_pos`/`get_vel`/`set_vel`/`apply_impulse`/`spawn`/`body_set_ccd`/`key_down`，分别接 ECS `World`、`PhysicsWorld`、`InputState`。`main.c` 绑定宿主、加载 `assets/init.lua`、`on_start` 一次 + 每帧 `on_update`+热重载。新增 `assets/init.lua`(真实 Lua)。新增 `test_script_lua`(15 项：错误处理/钩子/绑定真实改物理体/越界安全/热重载)。旧 DSL `script.c` 与 `test_script` 保留兼容不动。**实测**：双后端构建通过；CTest **25/25**(新增 `test_script_lua`)；VK/GL `engine_demo` 均成功 `Lua script loaded: assets/init.lua (start=1 update=1 spawn=1)` 并打印 `on_start`(11 实体/11 刚体)，VK 0 VUID、GL 0 着色器/GL 错误。(GL 链接期有一条 glibc 对 Lua `os.tmpname` 用 `tmpnam` 的良性告警，非编译错误。)

此前：**Round 6 完成** — ECS system 调度 + 物理形状/CCD/回调 + 角色胶囊 sweep。新增 `ecs/ecs_system.{h,c}`：`EcsChunkView` 视图 + `ecs_chunk_column`(SoA 列基址)/`ecs_chunk_entity_ids`、`ecs_parallel_for`(每非空 chunk 一个 task，`ts==NULL` 串行)、`EcsScheduler` 系统注册按序执行；`main.c` 把"物理→Transform 同步+越界重生"手写遍历迁入 `sys_sync_transform_from_physics`，经现有 `tasks` 工作线程并行 dispatch。Physics 扩 `ShapeType`(盒/球/胶囊)+`radius`/`half_height`/`ccd`；`aabb_from_body` 按形状算包围盒；新增 `physics_body_create_sphere`/`_capsule`/`_set_ccd`/`physics_set_contact_callback`/`physics_collide`(球-球/球-盒/球-胶囊/胶囊-胶囊/胶囊-盒分派 + `closest_seg_seg` 等几何助手)；`physics_step` 集成 swept-sphere CCD(`ccd_sweep_static`/`integrate_body_ccd`) 防高速穿透并触发 `Contact` 回调。角色 `character_update` 重写为胶囊 collide-and-slide：`char_slide_resolve` 迭代脱离静态几何并按坡度判定 grounded，分"垂直/水平/抬腿(up-forward-down)"三阶段实现 step/slope/wall。新增 `test_ecs_system`(5)、扩充 `test_physics`(34)/`test_character`(20)。**实测**：双后端构建通过；CTest **24/24**(新增 `test_ecs_system`)；VK Debug `engine_demo` 8 帧迁入的并行 ECS system 正常驱动(Phase4: 10 实体/11 刚体)、**0 VUID**(仅余 2 条 pre-existing `ShaderOutputNotConsumed` 警告)；GL `engine_demo` 仍 0 着色器/GL 错误。

此前：**Round 5 完成** — GL 后端一致性补齐。修复共享 `post.vert`（`#version 450` + `#ifdef VULKAN` 切 `gl_VertexIndex`/`gl_VertexID`）解锁约 20 个 GL 后处理着色器；批量修复其余 GL 专属着色器编译失败（terrain frag 显式 out、sharpen float→vec3、ssao/dof 残留垃圾、particle/depth_only/hi_z/occlusion 的 push 常量与 `set=` 守卫、skinned/bloom/post_tex 版本与 `layout(location)`）；`rhi_gl.c` 的 `gl_bind_tex_unit` 改为按资源类型选 GL target（cubemap/点光深度 cube 绑 `GL_TEXTURE_CUBE_MAP` 而非 `GL_TEXTURE_2D`），点光深度 cube 标记为 `RHI_RES_CUBEMAP` 且按 `samplerCubeShadow` 走纹理级 compare 参数，`rhi_cmd_transition_depth_to_read` 明确为 GL 下的合法 no-op。**实测**：GL `engine_demo` 8 帧 **0 着色器/链接/GL 错误**（仅余缺 ttf/缺 glb 资源警告），cluster binning 启用；VK Debug `engine_demo` 与 `test_vulkan`（含 GPU binning + 真 IBL）仍各 **0 VUID**；双后端构建 + CTest 23/23。

此前：**Round 4 完成** — 接通真 cubemap IBL（程序化天空 capture→irradiance/prefilter 卷积→BRDF LUT，全部 RGBA16F+mip）并让 PBR 经 `HAS_IBL` 采样真 IBL；新增 `cluster_cull.comp` 把 clustered 光照 binning 迁到 GPU（替换 CPU `light_system_cull`）。VK Debug（校验层开）下 `test_vulkan` TEST 7（含 GPU binning + 真 IBL）与 `engine_demo` 实时主循环各跑均 **0 VUID**；双后端构建 + CTest 23/23。所有 Round 4 着色器在 GL 语义下亦编译通过。

此前：**地基轮 A-E + 收尾全部完成** — VK 校验层在 forward/视锥剔除/遮挡三路径各 60 帧 0 FATAL/0 错误，双后端构建 + CTest 23/23（详见"地基修复轮"专节）。**重要更正**：Round 1 文档曾称"双后端 120 帧无验证层错误、CTest 23/23"，该结论来自 Release 构建(未启用校验层)且 `test_task` 偶发通过。开启 Vulkan 校验层后发现大量既有问题（见专节），`test_task` 实为偶发 段错误/死锁，现已全部修复。

## 图例

- 完整：功能闭环、已接入运行时、有测试或可观测验证。
- 部分：核心可用，但有明显简化/未接线/缺特性。
- 桩：仅有骨架/占位，运行时基本未生效。
- 缺失：未实现。

## 渲染（性能优先重点区）

| 模块 | 状态 | 证据 / 说明 |
|------|------|-------------|
| RHI Vulkan 后端 | 部分 | `rhi_vk.c`；缺 push-constant 公开 API、firstIndex/baseVertex、bindless。R4: cubemap 支持任意 `format`+`mip_levels`+per-face-per-mip 存储视图；新增 `rhi_cubemap_transition_to_read`/`rhi_texture_transition_to_read`；`rhi_cmd_memory_barrier` 扩到 fragment/uniform 读以同步 compute 产出的 cluster 网格 |
| RHI OpenGL 后端 | 部分→大幅补齐(R5) | `rhi_gl.c`。R5: ~~`gl_bind_tex_unit` 固定 `GL_TEXTURE_2D`→cubemap 绑定错误~~ 改为按 `dev->slots[idx].type` 选 target（`RHI_RES_CUBEMAP`→`GL_TEXTURE_CUBE_MAP`，含点光深度 cube），深度格式 cube 走纹理级 `COMPARE_REF_TO_TEXTURE`（解绑 sampler object 以保留 `samplerCubeShadow` PCF）；点光深度 cube 的 `depth_tex` 在 `rhi_cubemap_depth_fbo_create` 标记 `RHI_RES_CUBEMAP`。~~`rhi_cmd_transition_depth_to_read` 空实现~~ 明确为 GL 合法 no-op（GL 无显式 layout，FBO 深度→采样的 hazard 由驱动隐式同步）。~~共享 `post.vert` 用 `gl_VertexIndex`+varying `layout(location)` 致约 20 个 GL 后处理编译失败~~ 已修（见后处理行）。遗留：cubemap 仍 RGBA8 路径需按需扩展；`rhi_cmd_bind_texture` 对 compute 管线 sampler 处理仍简化 |
| GPU 视锥剔除 | 部分→完整(R1,R11) | R1: `cull.comp` 重写为双后端、输出可见性 flags；`gpucull.c` 改用 `rhi_shader_create_compute`；新增 `gpucull_dispatch_flags` 把剔除结果直写进 indirect 可见性缓冲。**R11**: `mega_buf.valid` 时 demo 默认 `gpu_indirect_enabled && gpucull_enabled`，并初始化 `gpucull_init_unified`(仍走 flags 路径，为 R12 unified 铺路) |
| 统一剔除(unified) | 部分→Hi-Z(R1,R11,R12,R16,R101) | R1: `unified_cull.comp` 单 pass 视锥+压缩。**R12**: 阴影/点光默认 unified。**R16**: unified 可选 Hi-Z 球体测试（上一帧金字塔，1 帧延迟）；CSM/点光 unified 传入 `occ_sys.hi_z_texture`。**R101**: unified 路径全激活时跳过冗余 `occlusion_cull_dispatch`（Hi-Z 生成仍运行供 unified 采样）。遗留：前向仍 per-mat compact |
| 间接绘制(indirect) | 完整(R1, 地基D加固,R11) | `indirect_draw.c` compact+execute；阴影 pass 现由 GPU 剔除 flags 驱动；修正 VK 下 `total_draws` push 常量映射缺失的潜伏 bug。**地基D**：修复 `rhi_cmd_bind_storage_buffer` 在 VK 下每次新建/重绑描述符集互相覆盖（compute 压缩此前只读到 binding 3、其余为垃圾）→ 改为按管线累积进同一集；启用 `drawIndirectCount` 1.2 特性；点光 cubemap pass 补 LOAD 孪生使间接绘制能在 compact 后 resume。**R11**: mega-buffer 有效时 demo 默认启用 GPU indirect 绘制 |
| 遮挡剔除 Hi-Z | 桩→部分→冗余消除(R11,R101) | ~~`occlusion_cull.c` 结果从未被消费~~ **R11 已接线**：Hi-Z compute + 1 帧延迟 readback 结果经 `node_occ_visible` 驱动前向 indirect(`vis_flags &= occ`)与 CPU frustum 回退(跳过被挡节点)；默认开启(`BREAK_OCCLUSION=0` 可关)。**R101**: unified 路径全激活时跳过 `occlusion_cull_dispatch`（结果无人消费）；Hi-Z 生成仍运行供 unified_cull 采样。遗留：Hi-Z 尚未并入 unified_cull 单 pass（但 unified_cull 已独立采样 Hi-Z）；阴影 unified 路径已含 Hi-Z |
| Clustered 光照 | 部分→完整(R4) | ~~`lighting.c:77-148` 纯 CPU light binning~~ R4: 新增 `shaders/cluster_cull.comp`（16×8×24 cluster、点光视锥+深度切片 binning，VP 矩阵+标量经 push 常量，VK `set=0` 双 SSBO，GL `std430 binding=0/1`+loose uniform）；`light_data_buf`/`light_grid_buf` 改 `TEXEL|STORAGE`；`light_system_init_gpu_cull` 载入管线、`light_system_cull_gpu` 每帧 dispatch（挂起当前 pass + grid 写→片元 texel 读 barrier）、`light_system_upload_lights` 仅传光数据由 GPU 产网格。修复 PBR 片元此前把密排 `u32` 网格当 `RGBA32F` 误读的潜伏 bug（新增 `grid_u32` 用 `floatBitsToUint` 还原）。near/far 仍取相机默认 0.1/100（demo 主循环值） |
| 级联阴影 CSM | 部分→完整(R2，前向主路径) | R2: 4 级渲入单张 2048² shadow-atlas 的四象限(`main.c` 复用 `shadow_map`，新增 `rhi_cmd_set_shadow_viewport` 双后端)；`pbr_clustered(.frag/_vk)` 改为"最紧 cascade"选择+象限重映射+`textureSize` 真实 texel+边界 clamp；修复 VK 下 `bind_material_textures(_ibl)` 忽略传入 shadow 纹理(此前前向阴影采到 albedo)的潜伏 bug。**同时修复 `pbr_clustered_vk.frag` 此前从未在 VK 编译成功**(非块内非透明 uniform + push 常量超限 + `read_dir_light` 前向引用)→ VK 前向 PBR 主着色器首次可用。terrain/water 的 cascade-0 采样代码双后端一致，但 terrain/water 的 VK 着色器仍因既有移植缺口无法编译(见专节) |
| 点光阴影 | 部分(R5 修 GL 绑定) | `point_shadow.c` cubemap 深度可用于 deferred；前向无点光阴影。R5: 修复 GL 把点光深度 cube 误绑为 `GL_TEXTURE_2D` 的 bug（现按 `RHI_RES_CUBEMAP` 绑 `GL_TEXTURE_CUBE_MAP` 并走 `samplerCubeShadow` 纹理级 compare） |
| IBL | 桩→完整(R4) | ~~`HAS_IBL` 未定义；`ibl_generate(...,RHI_HANDLE_NULL)` 仅跑 BRDF LUT；irradiance/prefilter 为黑色占位面；PBR 走程序化天空近似~~ R4: 真 cubemap IBL 接通。RHI cubemap 扩 `format`+`mip_levels`+per-face-per-mip 视图（VK/GL），新增 `rhi_cubemap_transition_to_read`/`rhi_texture_transition_to_read`（GENERAL→SHADER_READ_ONLY）。新增 `sky_to_cube.comp`（Rayleigh/Mie 程序化天空 capture 进 RGBA16F env cube）；`irradiance_env.comp`/`prefilter_env.comp` 改 `image2D` 单面存储视图 + VK set 布局；`ibl.c` 创建 env/irradiance/prefilter 三张 RGBA16F+mip cube，`ibl_generate` 编排卷积并在每次 frame_end 后 `rhi_present` 防 swapchain 耗尽。`main.c`/`test_vulkan` 经 `shader_inject_define` 注入 `HAS_IBL`，PBR 采样真 irradiance/prefilter/BRDF LUT（bindings 6/7/8）。VK `test_vulkan` TEST 7 实测 0 VUID |
| 延迟渲染 | 完整(R13,R16,R103) | **R13**：G-Buffer + 全屏光照接 cluster/CSM/IBL。**R16**：MRT RT3 velocity（NDC motion）；TAA 延迟路径采样。**R103**：`deferred_light.frag`/`_vk.frag` 接入点光 cubemap 阴影采样（`HAS_POINT_SHADOW` 条件编译）；`PointLight` 增加 `shadow_index` 指向 cubemap 阴影槽位；`deferred.c` 绑定点光阴影纹理到延迟光照 pass。遗留：前向无 velocity |
| 合并后处理 | 部分→demo 默认(R3,R11) | ~~`combined_taa_fxaa*`/`combined_color*` 着色器缺失，`combined_post_process.c` 永远回退多 pass~~ **已补(R3)**：新增 `combined_taa_fxaa_vk/.frag`(TAA 重投影+邻域 clamp + FXAA 单 pass) 与 `combined_color_vk/.frag`(色差采样→tonemap ACES/agx/khronos→饱和/对比/亮度/白平衡→暗角+grain 单 pass)；新增 `RHIPipelineDesc.combined_aa_layout/combined_color_layout` 标志 + VK 专属 push 偏移映射。**VK 实测**(`test_vulkan` TEST 6)：两条合并管线均激活、不再回退，10 帧 0 校验错误。**R11**: demo 主循环接入 —— TAA+FXAA 均开→`combined_aa_apply` 单 pass；tonemap+调色+cg 且 `!cine && !auto_exposure`→`combined_color_apply` 单 pass；resize/shutdown 生命周期完整；debug UI 显示 CombinedPost 状态。auto-exposure/cinematic 仍走原多 pass 链 |
| 后处理各 pass(SSAO/SSR/SSGI/TAA/DOF/Bloom/Tonemap 等) | 部分(R5,R13,R16) | 单功能可用。**R13**: TAA 用 `inv(curr_view_proj)`。**R16**: 延迟路径 TAA 可选 G-Buffer velocity 重投影（`u_taa_use_velocity`）；combined AA 仍相机 fallback |
| 粒子系统(GPU) | 部分→GPU cull(R12) | compute+graphics 可用。**R12**: `particle_cull.comp` 接线 —— `particles_cull` 写 alive 索引+atomic count，`particle.vert` 经 `gl_InstanceID` 查 indices 只 draw 存活粒子(不再固定 draw PARTICLES_MAX)；debug UI 显示 alive 数 |
| 骨骼蒙皮(GPU) | 完整 | `skeleton.c` joint buffer 上传 + skinned shader |

## 游戏运行时

| 模块 | 状态 | 证据 / 说明 |
|------|------|-------------|
| ECS | 完整(R103) | `ecs.c` archetype+chunk 完整。R6: 新增 `ecs_system.{h,c}` —— `EcsChunkView`+`ecs_chunk_column`(SoA 列)/`ecs_chunk_entity_ids`、`ecs_parallel_for`(每非空 chunk 一 task，`ts==NULL` 串行)、`EcsScheduler` 系统按注册序执行(系统间串行避免列写竞争、chunk 内并行)；`main.c` 物理→Transform 同步迁入 `sys_sync_transform_from_physics` 经 `tasks` 并行。`test_ecs_system` 5 项。R102: `edges_add/remove` 从桩→完整实现——`edge_lookup_add`/`edge_lookup_remove`/`edge_cache_add`/`edge_cache_remove` 四辅助函数，`world_add_component`/`world_remove_component` 先查 edge 缓存(O(E))命中则跳过 `find_archetype` O(N) 扫描+类型数组构建。**R103**: 查询新增 Exclude/Optional 组件支持——`ecs_query_exclude`（排除含指定组件的原型）、`ecs_query_optional`（可选组件）、`ecs_query_refresh`（查询失效时重建匹配原型列表）；`Query` 结构扩展 `exclude_mask`/`optional_mask` 位域，`query_matches_archetype` 位掩码 O(1) 过滤。`test_ecs` 新增 5 项 Exclude/Optional 测试 |
| Physics | 部分→形状/CCD/回调(R6) | R6: `ShapeType` 盒/球/胶囊 + `radius`/`half_height`/`ccd`；`aabb_from_body` 按形状；`physics_body_create_sphere`/`_capsule`/`_set_ccd`/`physics_set_contact_callback`；`physics_collide` 分派(球-球/球-盒含内部脱出/球-胶囊/胶囊-胶囊/胶囊-盒，`closest_seg_seg`/`closest_on_aabb` 助手)；`physics_step` 集成 swept-sphere CCD(`ccd_sweep_static`/`integrate_body_ccd`)防穿透 + 触发 `Contact` 回调。`test_physics` 34 项(含 `ccd_prevents_tunnel`/`no_ccd_tunnels`)。遗留：无关节/约束；CCD 仅对静态体扫掠 |
| 角色控制器 | 部分→胶囊 sweep+step/slope(R6) | R6: `character_update` 重写为胶囊 collide-and-slide。`char_capsule` 由脚底构造胶囊刚体；`char_slide_resolve` 迭代脱离静态几何并按 `slope_limit` 判 grounded；分垂直(重力/跳)、水平(墙滑)、抬腿(up→forward→down，受 `step_height` 限)三阶段，落实此前未用的 `slope_limit`/`step_height`。`test_character` 20 项(含 `wall_block`/`step_up`/`high_step_blocks`) |
| Animation | 部分→事件回调(R101) | 单 clip + GPU skin 可用；blend/IK 已实现但 demo 未接(`animation.c:208-436`)；**R101**: 事件回调现由 `anim_blend_evaluate` 按时间区间触发（含循环 wrap-around）；新增 `AnimEvent`/`anim_clip_add_event` API；`test_animation` 24 项 |
| Script(Lua) | 桩→完整(R7) | R7: vendored Lua 5.4.7(`external/lua`，`onelua.c`+`MAKE_LIB`→静态库 `lua`)；新增 `script_lua.{h,c}` 真实 `lua_State`+标准库，`on_start`/`on_update(dt)`/`on_spawn` 钩子、数值全局 get/set、`.lua` mtime 热重载、`engine.*` 绑定表(log/entity_count/body_count/get_pos/set_pos/get_vel/set_vel/apply_impulse/spawn/body_set_ccd/key_down，宿主 NULL 安全降级)。`main.c` 加载 `assets/init.lua` 并每帧 `on_update`+热重载，demo 启动即执行 `on_start`。`test_script_lua` 15 项。旧 `.script` DSL(`script.c`/`test_script`)保留兼容 |
| Network | 部分→多类型(R15–R25) | transform/heartbeat 独立序列+重排槽；`net_replicator_send_heartbeat()`；reliable pending 仍全局一份 |
| Scene 序列化 | 基本完整 | ECS 实体/组件 + SceneNode 可往返；**RESOURCES chunk 已实现**(mesh/material/texture + 确定性 GUID + 可内联描述符)；`include_resources` 生效(内联/轻引用)；**generation 恢复**使 (index,gen) 成为统一持久 ID；`test_scene_serial` 23 项全过 |
| Task 调度 | 基本可用(地基C已修，R6 接入 ECS) | `task.c` work-stealing + 优先级 + 依赖 + wait；**地基C 已修三处竞态**：①`flush` 在锁外 reset `submit_count` 致提交覆盖丢任务(死锁) → 改为锁内 detach；②`flush` 向非owner worker deque push 违反 Chase-Lev 单生产者(段错误) → 改为各 worker 拉取到自己 deque、非worker 线程内联执行；③`task_wait_handle` 解引用可能已释放的 task(UAF段错误) → pool 持引用直到 destroy。`test_task` 双后端各连跑 100/60 次全通过。R6: `ecs_parallel_for` 把 ECS chunk 作为 task 提交并 `task_wait` 同步，已在 `test_ecs_system` 与 demo 主循环验证 |

## 平台 / 资源 / 音频 / UI / Core

| 模块 | 状态 | 证据 / 说明 |
|------|------|-------------|
| 平台 Windows(Win32) | 完整 | 窗口/输入/raw input/DPI/多显示器；**XInput gamepad 已接线**(`gamepad_win.c`，动态加载) |
| 平台 Linux X11 | 完整 | 窗口/输入/抓取/XRandr 多显示器；**evdev gamepad 已接线**(init/poll/shutdown) |
| 平台 Linux Wayland | 基本完整 | 窗口/输入；**相对指针(zwp_relative_pointer_v1)+指针锁(zwp_pointer_constraints_v1)+NULL 光标隐藏**已落实；**evdev gamepad 已接线**；单 output |
| 平台 macOS | 可链接(未实测) | `window_cocoa.m`(NSWindow+CAMetalLayer)经 MoltenVK 复用 VK 后端；`rhi_vk.c` 加 `VK_EXT_metal_surface`+portability；CMake macos 分支(OBJC+frameworks)。Linux 环境无法实测构建 |
| Gamepad | 完整 | Linux evdev(`gamepad_linux.c`)+Windows XInput(`gamepad_win.c`) 均经 `platform_poll`→`input.gamepads` 接线；统一按钮/轴语义(up=负、扳机 0..1) |
| Asset 热重载 | 部分(R14) | **R14**：`hotreload_texture_*` 实现 mtime 纹理重载 + GPU 重建；着色器管线热重载仍可用。遗留：demo 未默认接线纹理热重载 |
| Async Loader | 完整(R103) | 真异步线程。**R103**：priority 最小堆替换 FIFO 队列，高优先级请求优先出队；新增 2-worker 解码线程池 `decode_pipeline.c/h`，stb_image 解码 + mipmap 生成不阻塞主线程，解码完成后回调主线程上传 GPU。`test_async_loader` 新增优先级和解码管线测试 |
| Mipmap 流式 | 桩→完整(R10) | ~~回调空、仅 track residency，`level_data` 从不赋值、未接入 main~~ R10: `MipLoadReq` 上下文经 `async_loader_request_range` 把 level 数据写入 `level_data`、按预算记 `total_resident_bytes`，命中经 `MipmapUploadFn` 钩子真传 GPU(新增 RHI `rhi_texture_upload_mip`：GL `glTexImage2D` / VK staging buffer+逐 mip image barrier)；`mipmap_stream_update` 按预算驱逐、`_force_level` 内泵 `async_loader_tick`；修复 `coverage_to_level` 反向 bug(全覆盖→level0)。接入 `main.c`(程序化 256² 9-mip 文件、相机距离驱动驻留/驱逐、debug UI 展示)。`test_mipmap_stream` 验证驻留/上传/预算驱逐 |
| VFS + packer | 完整(R103) | 目录挂载 + .pak 只读。**R103**：Windows packer 重写为 `CreateFileMapping` 零拷贝打包 + `FindFirstFile`/`FindNextFile` 递归遍历，与 POSIX 版二进制兼容（相同 magic + 字节序 + 对齐）；新增 `verify_pak.c` 验证工具 |
| Audio 播放 | 部分→流式 3D(R10) | `audio.c` listener+简单播放。R10: 增 `audio_play_streamed`(miniaudio `MA_SOUND_FLAG_STREAM`)、`audio_source_set_position`/`_set_attenuation`(逆距离模型)/`_set_volume`/`_start`/`_at_end`/`_cursor_seconds`；纯函数 `audio_attenuation_gain` 可无头单测。仍无混音总线 |
| Audio 流式 | 桩→完整(R10) | ~~双缓冲框架但不向声卡输出~~ R10: `audio_stream.c` 重写为 miniaudio 流式后端 —— 每个 `AudioStream` 包一个 `MA_SOUND_FLAG_STREAM` 源(由声卡线程逐块解码/补帧)，支持 2D/3D(`audio_stream_open_3d` + 距离衰减)、播放/暂停/停止/移动、状态轮询、增益诊断(`audio_stream_attenuation`)。`main.c` 生成正弦 WAV 作 3D 音源真播放。格式由 miniaudio 解码器支持(WAV/MP3/FLAC) |
| UI | 部分→IMGUI 控件(R10) | `debug_ui.c` 调试文本叠加保留。R10: 新增 `imgui.{h,c}` 即时模式 UI —— `ImUI` 上下文(hot/active 状态、布局)、label/button/checkbox/slider_float；`static inline` 纯逻辑助手(hit/slider 映射/按压状态机)可无头测；接入 demo(反引号切换设置面板，独立 `FontRenderer` 避免与 debug_ui 共享 VBO 冲突) |
| 字体 | 部分→UTF-8(R10) | ~~仅 ASCII 32-127~~ R10: 新增 `utf8.{h,c}` 健壮多字节解码(拒绝 overlong/代理半区，永不卡死)；`font.c` 烘焙 ASCII+Latin-1 范围、码点查找表、保留白像素供 `font_renderer_draw_rect`；新增 `font_renderer_text_width`/`_line_height`。仍无 kerning/SDF |
| Core 分配器 | 部分→通用 pool(R10) | heap/arena/debug 包装。R10: 新增定长块 `pool.{h,c}`(侵入式空闲链、O(1) acquire/release、`owns_base` 跟踪自管缓冲、接入 `Alloc` vtable)；`test_pool` 覆盖耗尽/释放复用/对齐 |
| Profiler | 部分→Chrome trace(R15) | CPU 环形缓冲 + R10 GPU timer。**R15**：`profiler_export_chrome_trace()` 写 Chrome Trace JSON（CPU `ph:X` + GPU 样本 + frame 边界）；demo F11/`PROFILER_TRACE=1` 触发；`test_profiler` 增导出测。遗留：无线程级采样 |
| 测试 | 部分→扩充(R10,R15) | R10: CTest 升至 **30 项**(VK；GL 29)。**R15**：双后端 CTest **31/31**（+`test_net_replication`、GL 纳入 `test_vulkan` golden-only）；`tests/golden/test_vulkan_gl.ppm`；`test_profiler` 增 Chrome trace 测；VK `test_vulkan` 仍跑全集成套件 + golden |

## Round 2 实测发现：Vulkan 后端基础性缺陷（开启校验层后）

> 这些是开启 Vulkan validation layers 后暴露的既有(pre-existing)问题，原计划低估了 VK 后端的破损程度。它们大多属"写了却没生效"，与用户"性能优先 + 修复无效功能"的目标高度相关，但跨越多个计划轮次，需要单独决策是否优先处理。

**A. VK 着色器编译失败（对应特性在 VK 上静默禁用）**
- ~~`terrain_vk.*`、`water_vk.*`：out/in varying 缺 `layout(location=)`；片元用非块内 `uniform` → VK 报 "non-opaque uniforms outside a block"。~~ **已修复(地基B)**：给 varying 加 `layout(location=)`，所有 uniform 收进 push 常量块；地形丢弃恒等 model、水面无 model，两者均装进 256B；新增 `RHIPipelineDesc.terrain_layout/water_layout` 标志 + `rhi_pipeline_get_uniform_location` 专属偏移映射。VK 上地形/水面现已正常编译并渲染。
- ~~`ssao_blur`(括号不配对 syntax error)、`sharpen`(float→vec3 赋值)、`debug_viz`/`lens_effects`(非块内 uniform)：VK 上这些后处理/调试 pass 静默禁用。~~ **已修复(地基E)**：`ssao_blur_vk.frag` 补回 `vec2(textureSize(...))` 缺失右括号；`sharpen_vk.frag` 改 `vec3 w = vec3(...)`；`debug_viz_vk.frag`/`lens_effects_vk.frag` 把散落 uniform 收进 push 常量块（debug_viz 统一改 `u_dv_*` 前缀避免与 clustered 的 `u_near/u_far` 冲突，GL 同步改名），并在 `rhi_pipeline_get_uniform_location` 增加 debug_viz/lens/sharpen 偏移映射。VK 上四个 pass 现已全部编译并初始化成功。
- 已修复：`pbr_clustered_vk.frag`（前向主着色器，此前从未在 VK 编译）。

**B. VK 校验层每帧报错（约 13 类）**
- ~~`vkCmdDispatch-None-10672`：**compute 在 render pass 内 dispatch**。~~ **已修复(地基A)**：在 RHI 层引入 render pass suspend/resume（`vk_suspend_pass_for_compute`/`vk_resume_pass_if_needed` + LOAD-op 孪生 pass + depth storeOp=STORE）。所有 compute dispatch 与 compute 域 barrier/image 绑定自动挂起当前 pass，绘制/清除时按需恢复。基线/视锥剔除/遮挡三条路径均 0 个 dispatch/barrier-in-pass 错误。
- ~~`vkCmdPipelineBarrier-None-07889`：pass 内下 barrier 且子通道无 self-dependency。~~ **已修复(地基A)**：同上，barrier 随挂起移出 pass。
- 遮挡剔除崩溃修复(地基A)：新增 `rhi_cmd_bind_texture_compute` 把 2D 纹理绑到 compute 采样集(set 2)，修正 `occlusion_cull.comp` 的 `u_hi_z` 描述符集(`07990`)，消除 Intel 驱动 `emit_samplers` 段错误。
- ~~`vkCmdResetQueryPool-renderpass`：profiler 在 pass 内 reset query pool。~~ **已修复(地基D)**：query reset 走 compute 域挂起。
- ~~`vkCmdDraw-renderPass-02684` / `imageLayout-00344` / `ComputePipelineCreateInfo-layout-07990` / `GraphicsPipelineCreateInfo-layout-07991` / `ClearAttachments-pRects-00016` / `DrawIndexedIndirectCount-*` / `polygonMode-01507`~~ **全部已修复(地基D)**，逐项见下方"地基D 明细"。基线/视锥剔除/遮挡三路径 VK 校验层 **0 错误**（仅余 2 条 `ShaderOutputNotConsumed` 警告：延迟 gbuffer MRT 着色器对单附件模板 pass 创建时报多余输出，非每帧错误，属 Round 4 延迟管线）。

**C. 并发**
- ~~`test_task` 偶发 段错误/死锁~~ **已修复(地基C)**，见 Task 行。

> 结论：原计划"按轮加特性"的前提（地基基本可用）在 VK 上不成立。建议在继续 Round 3+ 之前，新增/前置一轮"VK 校验层清零 + 着色器移植 + task 竞态修复"，否则后续轮次会在破损地基上继续堆叠"写了却没生效"的代码。

> **地基轮收尾（已完成）**：双后端均构建通过；CTest 双后端各 23/23；VK 校验层 smoke（forward / GPU 视锥剔除 / 遮挡 三路径各 60 帧）**0 FATAL、0 校验错误**（仅余 2 条创建期 `ShaderOutputNotConsumed` 警告，属 Round 4 延迟管线）。VK 地基已达"可在其上继续堆叠特性"的稳定状态。GL 后处理/着色器破损为既有问题，根因已定位（见 RHI OpenGL 行），归入 Round 5。

## 地基修复轮（前置于 Round 3）

> 用户已选择 `foundation_first`：在继续特性轮前先修地基。

- [x] **地基A**：把 GPU 剔除/压缩/occlusion 的 compute dispatch 移出 render pass —— RHI 层 suspend/resume + LOAD-op 孪生 pass；消除 `vkCmdDispatch-None-10672`/`PipelineBarrier-None-07889`；修复遮挡剔除段错误（新增 `rhi_cmd_bind_texture_compute`）。基线/视锥/遮挡三路径验证通过，双后端 CTest 全绿。
- [x] **地基B**：terrain_vk/water_vk 着色器在 VK 编译 —— varying 加 location、uniform 收进 push 常量块、新增 terrain/water 专属 push 布局标志与偏移映射。VK 上地形/水面已编译渲染，无新增校验错误，双后端 CTest 23/23。
- [x] **地基C**：task work-stealing 调度器竞态 —— 修复 submit-queue 锁外 reset(丢任务死锁)、非owner deque push(段错误)、wait_handle UAF(段错误)。`test_task` 双后端连跑 100/60 全绿。
- [x] **地基D**：清理其余每帧校验错误 —— **基线/视锥/遮挡三路径 VK 校验层 0 错误**。明细：
  - `polygonMode-01507`：设备创建时按需启用 `fillModeNonSolid`，管线据此选 LINE/FILL。
  - `ClearAttachments-pRects-00016`：清除矩形改用 `vk->resume_extent`（当前 pass 真实尺寸）而非 swapchain 尺寸。
  - `PipelineBarrier-commandBuffer-recording`：`rhi_cubemap_create` 启动期 barrier 改用一次性命令缓冲（原误用尚未 begin 的帧缓冲）。
  - `ComputePipelineCreateInfo-layout-07990`(IBL)：env map 为空时不再创建 irradiance/prefilter 计算管线（留待 Round 4）。
  - `renderPass-02684`：①模板 render pass 补 subpass dependency 对齐离屏 FBO；②点光 cubemap pass `srcStageMask` 对齐 `shadow_render_pass`；③**通用按渲染通道颜色格式惰性管线变体**（`VKShaderData` 保留 SPIR-V，`VKPipelineData` 缓存按格式变体，`rhi_cmd_bind_pipeline` 按 `active_color_fmt` 选/建变体）彻底消除格式不匹配。
  - `DrawIndexedIndirectCount-None-04445`：经 `VkPhysicalDeviceVulkan12Features.drawIndirectCount` 查询并启用该特性（apiVersion 已是 1.2）；不支持时回退 `vkCmdDrawIndexedIndirect`。
  - `vkCmdDispatch-None-08114`(`all_draws`)：**修复 `rhi_cmd_bind_storage_buffer` 每次都新分配并重绑描述符集、互相覆盖** —— 改为按管线绑定累积进同一描述符集（bind 0..3 全部写入），使 compute 压缩真正读到全部 SSBO（此前 VK 下 GPU 压缩读到的是垃圾）。
  - `DrawIndexedIndirectCount-renderpass`(在 pass 外)：点光 cubemap 深度 pass 现也跑间接压缩 dispatch，为其补 LOAD-op 孪生 pass + 记录 face framebuffer，使 compact 后的间接绘制能 resume 回 pass。
  - `imageLayout-00344`(`u_gr_depth`)：分两处。①遮挡/SSAO 路径随上述间接/存储修复一同消失。②**间歇性深度 layout 乒乓**（收尾时复现，约 1/3 帧、仅当太阳在屏内 god_rays 触发）：`scene_fbo` 深度在 line 3933 转 `SHADER_READ_ONLY` 后，tonemap/cinematic 又 `rhi_offscreen_fbo_bind(scene_fbo)` 把深度经离屏 render pass `finalLayout` 还原回 `DEPTH_STENCIL_ATTACHMENT_OPTIMAL`，随后 god_rays/debug_viz 采样该深度报错。**修复**：`VKTextureData` 增 `cur_layout` 跟踪；`rhi_cmd_transition_depth_to_read` 改为幂等（已是 READ_ONLY 即跳过、按跟踪 oldLayout 转换）；离屏 bind 标记其深度回到 attachment layout；main.c 在 god_rays/debug_viz 前再调用一次该（幂等）转换。压测 forward 8/8 + cull/occlusion 各 3/3 全 0 错误。
  - `vkCmdDraw-None-09600`(采样 UNDEFINED 图像)：离屏/MRT 颜色附件创建时用一次性提交转到 `SHADER_READ_ONLY_OPTIMAL`，使"创建后尚未渲染即被采样"的目标具有合法采样 layout。
  - `GraphicsPipelineCreateInfo-layout-07991`(deferred `u_point_shadow_cubes[4]`)：材质描述符布局 binding 5 计数改 4 并加 `descriptorBindingPartiallyBound`（启用对应 1.2 特性），使同一布局既服务前向 `u_ssao`(只用元素0)又服务延迟 cube 数组(07991 创建期错误清零，前向不受影响)。
- [x] **地基E**：ssao_blur/sharpen/debug_viz/lens_effects 等 VK 着色器编译 —— 见上方 A 节，四个 pass 全部编译并初始化成功，VK smoke 0 FATAL / 0 校验错误。

## 修复进度（按计划轮次）

- [x] Round 1：GPU 驱动剔除闭环 — cull.comp 双后端 compute 加载并输出 flags 驱动 compaction；删除全可见 memset；新增 unified_cull.comp；修复 VK push 常量映射与 BRDF LUT 描述符集崩溃；默认关闭无用的 Hi-Z 遮挡；双后端 120 帧无验证层错误，CTest 23/23
- [~] Round 2：CSM 4 级正确采样 — 核心达成(shadow-atlas 四象限 + pbr_clustered 双后端最紧 cascade 选择 + 真 texel + 修复 VK 阴影纹理绑定/着色器编译)；遗留：terrain/water 在 VK 因既有移植缺口未编译(其 CSM 采样代码已就位)；并暴露上节 VK 基础性缺陷待决策
- [x] 地基轮(A-E + 收尾)：VK render-pass suspend/resume、terrain/water VK 着色器、task 竞态、VK 校验层清零(三路径 0 错误)、后处理 VK 着色器编译、间接绘制存储描述符集修复。双后端构建 + CTest 23/23。
- [x] Round 3：合并后处理减少 pass —— 新增 combined_taa_fxaa / combined_color 着色器(双后端) + VK 专属 push 布局。VK `test_vulkan` TEST 6 验证两合并管线激活、不回退、10 帧 0 校验错误。GL 受 post.vert 阻塞(Round 5)。亦修复 god_rays/debug_viz 采样场景深度的间歇 `imageLayout-00344`(深度 layout 跟踪幂等化)。
- [x] Round 4：Clustered 光照 GPU binning + 真 cubemap IBL ——
  - **真 IBL**：RHI cubemap 扩 `format`/`mip_levels`/per-face-per-mip 视图(VK+GL) + 两个 layout 转换 API；新增 `sky_to_cube.comp` 程序化天空 capture；`irradiance_env`/`prefilter_env` 改单面 `image2D` 存储视图；`ibl.c` 三张 RGBA16F+mip cube 卷积链 + 每帧 `rhi_present` 防 swapchain 耗尽；`HAS_IBL` 经 `shader_inject_define` 注入，PBR 采样真 irradiance/prefilter/BRDF LUT。修两 bug：BRDF LUT 缺 `transition_to_read` 致 `09600`；IBL 生成期 swapchain 耗尽挂起。
  - **GPU binning**：新增 `cluster_cull.comp`(VP+标量 push、VK set0 双 SSBO / GL std430)；buffers 改 `TEXEL|STORAGE`；`light_system_init_gpu_cull`/`cull_gpu`/`upload_lights`；修 PBR 把密排 `u32` 当 `RGBA32F` 误读的潜伏 bug(`grid_u32`+`floatBitsToUint`)。
  - **验收**：VK Debug(校验层开) `test_vulkan` TEST 7(GPU binning + 真 IBL) 与 `engine_demo` 实时主循环各 **0 VUID**；双后端构建 + CTest 23/23；5 个 Round 4 着色器 GL 语义编译通过。
- [x] Round 5：GL 后端一致性 ——
  - **着色器移植**：`post.vert` 升 `#version 450` + `#ifdef VULKAN` 切 `gl_VertexIndex`/`gl_VertexID`（解锁约 20 个 GL 后处理）；`terrain.frag` 补显式 `out`；`sharpen.frag` float→vec3；`ssao.frag`/`dof.frag` 清残留垃圾/重复 main；`particle_update.comp`/`particle.vert`/`depth_only.vert` 加 `#ifdef VULKAN` push 常量↔loose uniform（`particles.c` GL 侧逐项设 uniform）；`hi_z_generate.comp`/`occlusion_cull.comp` 守卫 `layout(set=)`；`skinned.vert` 升 430；`bloom_blur/bloom_extract/post_tex.frag` 升 450 + `layout(location=0)` 对齐 `post.vert`。
  - **rhi_gl 一致性**：`gl_bind_tex_unit` 按资源类型选 GL target（cubemap/点光深度 cube→`GL_TEXTURE_CUBE_MAP`），深度 cube 走纹理级 compare；`rhi_cubemap_depth_fbo_create` 的 depth_tex 标记 `RHI_RES_CUBEMAP`；`rhi_cmd_transition_depth_to_read` 明确为 GL 合法 no-op。
  - **验收**：GL `engine_demo` 8 帧 0 着色器/链接/GL 错误（仅余缺资源警告）、cluster binning 启用；VK `engine_demo`/`test_vulkan` 仍各 0 VUID；双后端构建 + CTest 23/23。
- [x] Round 6：ECS system 调度 + 物理 CCD/形状 ——
  - **ECS system**：新增 `ecs_system.{h,c}`。`EcsChunkView`(world/archetype/chunk/count) + `ecs_chunk_column`(按组件签名取 SoA 列基址)/`ecs_chunk_entity_ids`；`ecs_parallel_for(world, ts, types, n, fn, user)` 每个匹配非空 chunk 提交一个 task 并行(传 `ts=NULL` 串行)；`EcsScheduler` 系统按注册序串行执行(防列写竞争)、单系统 chunk 内并行。`main.c` 把物理→Transform 同步+越界重生迁入 `sys_sync_transform_from_physics`，经现有 `tasks`(2 worker) 并行。
  - **Physics 形状/CCD/回调**：`ShapeType`(盒/球/胶囊)+`radius`/`half_height`/`ccd`；`aabb_from_body` 按形状；`physics_body_create_sphere`/`_capsule`/`_set_ccd`/`physics_set_contact_callback`；`physics_collide` 按形状对分派(球-球/球-盒/球-胶囊/胶囊-胶囊/胶囊-盒，附 `closest_on_segment`/`closest_seg_seg`/`closest_on_aabb`/`sphere_vs_box`)；`physics_step` 集成 swept-sphere CCD vs 静态体(`ccd_sweep_static`/`integrate_body_ccd`)防高速穿透并对每对解析触发 `Contact` 回调。修 `sphere_vs_box` 内部脱出法线符号 bug。
  - **角色胶囊**：`character_update` 重写为 collide-and-slide(`char_capsule`+`char_slide_resolve`)，分垂直/水平/抬腿三阶段，落实 `slope_limit`/`step_height`。
  - **验收**：双后端构建通过；CTest **24/24**(新增 `test_ecs_system` 5；`test_physics` 34、`test_character` 20)；VK Debug `engine_demo` 8 帧并行 ECS system 正常、0 VUID；GL `engine_demo` 0 着色器/GL 错误。
- [x] Round 7：真实 Lua 脚本 ——
  - **vendoring**：Lua 5.4.7 全量源置于 `engine/external/lua`(删除 standalone `lua.c`/`luac.c`/`ltests.{c,h}`)，仅以 `onelua.c`+`-DMAKE_LIB` 编译成静态库 `lua`(第三方代码用 `-w` 豁免引擎 `-Werror -pedantic`)，`engine` 链接 `lua`。
  - **运行时**：`script_lua.{h,c}` 真实 `lua_State`+`luaL_openlibs`；`lua_script_load`/`_load_string`(语法/运行期错误经日志返回 false 不崩)、`on_start`/`on_update(dt)`/`on_spawn` 探测+ `pcall`、数值全局 get/set、按 mtime 的 `.lua` 热重载。
  - **绑定**：`engine.*` 表经 registry 取宿主 `LuaScript*` → ECS `World`/`PhysicsWorld`/`InputState`，宿主指针 NULL 时全部安全降级(返回 0/no-op)。
  - **接入 demo**：`main.c` 绑定宿主、加载 `assets/init.lua`、启动 `on_start`、每帧 `on_update`+热重载、退出 `shutdown`；新增真实 `assets/init.lua`。
  - **验收**：双后端构建通过；CTest **25/25**(新增 `test_script_lua` 15)；VK/GL `engine_demo` 均 `Lua script loaded (start=1 update=1 spawn=1)`+`on_start` 打印 11 实体/11 刚体，VK 0 VUID、GL 0 着色器/GL 错误。旧 DSL 兼容保留。
- [x] Round 8：场景资源序列化 ——
  - **RESOURCES chunk**：`scene_serial.c` 由空占位改为真实清单：`emit_resources_chunk` 遍历 `Scene` 的 meshes/materials 及按 RHI 句柄去重的 textures，逐条写 `SceneResource`{guid,type,ref_index,flags,inline 描述符,path}；`load_resources_chunk` 回填到 `Scene.resources`/`resource_count`。
  - **确定性 GUID**：`resource_guid` 对(类型 + ref 索引 + 关键描述符字段)做 FNV-1a 64，同场景多次保存 GUID 稳定(`resources_guid_deterministic` 验证)。
  - **include_resources**：true 内联 mesh(index/vertex count、material_idx、AABB)与 material(base_color、metallic/roughness、emissive、alpha mode/cutoff)描述符；false 仅写 {guid,type,ref,path} 轻引用。
  - **ECS↔Scene 统一 ID**：`load_entities_chunk` 恢复保存的 entity `generation`(此前丢弃)，使 (index,generation) 跨存读一致，成为持久统一 ID；`world_entity_exists` 在往返后对存活/已销毁实体判定正确。
  - **配套**：`asset.h` 增 `SceneResource` 与 `Scene.resources`/`resource_count`；`asset_scene_free` 释放；`scene_serial.h` 导出 `scene_resources_free`。
  - **验收**：双后端构建通过；CTest **25/25**(`test_scene_serial` 扩到 23 子项：新增 include 往返、refs-only 往返、GUID 确定性、generation 恢复)。
- [x] Round 9：平台补齐（gamepad/Wayland/macOS）——
  - **Linux gamepad 接线**：`window_x11.c` 与 `window_wayland.c` 的 `platform_create` 调 `gamepad_init`、`platform_poll` 在 `input_new_frame` 后调 `gamepad_poll(p->input.gamepads)`、`platform_destroy` 调 `gamepad_shutdown`；既有 evdev 后端(热插拔/校准)首次真正驱动 `InputState`。
  - **Windows XInput**：新增 `gamepad_win.c`(动态加载 `xinput1_4/1_3/9_1_0`)，实现同一 `gamepad_init/poll/shutdown` 契约，映射按钮/摇杆/扳机(死区缩放、Y 轴取反对齐 evdev"上为负"、扳机 0..1)，接入 `window_win32.c` 三处。
  - **Wayland 指针**：绑定 `zwp_relative_pointer_manager_v1`/`zwp_pointer_constraints_v1`；`set_relative` 走相对运动(未加速 delta)+持久 `lock_pointer`，`set_visible(false)` 经 `wl_pointer_set_cursor(serial,NULL)` 真隐藏(记录 enter serial、重入时重应用)；CMake 用 wayland-scanner 生成两个 unstable 协议绑定。原三处桩注释删除。
  - **macOS**：新增 `window_cocoa.m`(NSWindow + CAMetalLayer + 事件/键鼠/相对指针 via `CGAssociateMouseAndMouseCursorPosition`)；`rhi_vk.c` 加 macOS 分支(`VK_USE_PLATFORM_METAL_EXT`、`vkCreateMetalSurfaceEXT`、实例 portability enumeration、设备 `VK_KHR_portability_subset`)；CMake `macos` 分支启用 OBJC、链接 Cocoa/QuartzCore/Metal/IOKit + Vulkan(MoltenVK)。复用 VK 后端不另写 Metal RHI。
  - **测试**：`test_input` 增 3 项 gamepad 契约测试(轴跨帧保留、4 槽位边沿推进、槽位独立)。
  - **实测**：X11 双后端(VK+GL)构建+CTest **25/25**；Wayland(VK)`engine`/`engine_demo` 链接通过(含生成的 relative-pointer/pointer-constraints 绑定)；VK demo 启动接线 gamepad 无崩溃。macOS 受限于 Linux 环境未实测构建(代码按 MoltenVK 规范编写)。
- [x] Round 10：资源/音频流式 + UI/字体 + Core + 回归测试 ——
  - **Mipmap 流式真上传**：`mipmap_stream.c` 由桩改真链路。`MipLoadReq{mgr,tex,level}` 作 `async_loader_request_range` 用户数据，回调取得 level 数据所有权→写 `level_data`、改 `level_state=RESIDENT`、增减 `total_resident_bytes`、调 `MipmapUploadFn` 上传；`mipmap_stream_update` 按 `memory_budget`+`desired_level` 驱逐细 mip；`_force_level` 内泵 `async_loader_tick` 至命中。新增 RHI `rhi_texture_upload_mip`(GL `glTexImage2D` 可变存储 / VK staging buffer + 一次性命令 + 逐 mip SHADER_READ↔TRANSFER_DST barrier)。修复 `coverage_to_level` 反向(全覆盖应得 level0，改 `0.5*log2(1/coverage)`)。接入 `main.c`：启动写 256² 9-mip 文件、96KB 预算、相机距离→coverage 驱动驻留/驱逐、debug UI 显示 level/驻留KB/loads/uploads/evict。
  - **Audio 流式 3D**：`audio_stream.c` 重写为 miniaudio `MA_SOUND_FLAG_STREAM` 真后端(声卡线程逐块解码补帧)，每流包一音源、支持 2D/3D+距离衰减+移动+状态。audio.c 增 `audio_play_streamed`/`audio_source_set_position`/`_set_attenuation`(逆距离模型 `ma_attenuation_model_inverse`)/`_set_volume`/`_start`/`_at_end`/`_cursor_seconds`；纯函数 `audio_attenuation_gain` 供无头测。`main.c` 生成正弦 WAV 作 3D 音源真播放、debug UI 显示增益/播放时刻。
  - **字体 UTF-8 + IMGUI**：`utf8.{h,c}` 多字节解码(拒 overlong/代理、永不卡死)；`font.c` 烘焙 ASCII+Latin-1、码点查找表、白像素供实心矩形，新增 `font_renderer_draw_rect`/`text_width`/`line_height`；`imgui.{h,c}` 即时模式 label/button/checkbox/slider(纯逻辑助手 `static inline` 可无头测)接入 demo(反引号切换面板，独立 `FontRenderer` 避免 VBO 冲突)。
  - **Core**：定长块 `pool.{h,c}`(侵入式空闲链、O(1)、接入 `Alloc` vtable)；GPU timestamp profiler(`RHIGPUTimer` 双后端)接入 demo 命名计时输出。
  - **回归测试**：`test_vulkan` 增 golden image 子测(读回→20×15 降采样→容差比对 `tests/golden/test_vulkan_vk.ppm`，`GOLDEN_UPDATE=1` 重生)且返回码汇总全部子测；纳入 CTest(`WORKING_DIRECTORY` + `ENGINE_VULKAN` 守卫 + 180s 超时)。新增 `test_pool`/`test_font_ui`/`test_mipmap_stream`/`test_audio`。
  - **验收**：VK 构建 CTest **30/30**(golden MAE=0.00 max=0 稳定，test_vulkan 12s 通过)；GL 构建 CTest **29/29**；VK demo 0 校验错误(仅余 2 条既有 `ShaderOutputNotConsumed` 警告)、GL demo 0 着色器/GL 错误；双后端 demo 均 `MipmapStream demo: 9 levels, GPU tex ok` + `Audio: streaming 'stream_tone.wav' (3D)`。
- [x] Round 11：剔除闭环 + 合并后处理默认化 ——
  - **R11-1 遮挡驱动 draw**：`occ_rebuild_node_map`/`node_occ_visible` 建立 node→occ 紧凑索引(与 Hi-Z upload 同序)；mega-buffer indirect `vis_flags &= occlusion`；CPU frustum 回退跳过被挡节点；默认 Hi-Z 开(`BREAK_OCCLUSION=0` 关)；debug UI 显示 culled 数。
  - **R11-2 GPU cull 默认**：`mega_buf.valid`→`gpu_indirect_enabled && gpucull_enabled`；`gpucull_init_unified` 初始化 unified 管线(仍走 flags 路径，R12 替换)。
  - **R11-3 合并后处理**：`CombinedAA`/`CombinedColor` init/resize/shutdown；TAA+FXAA→单 pass AA；tonemap+cg 且 `!cine && !auto_exposure`→单 pass 调色；debug UI CombinedPost 状态。
  - **验收**：双后端 `engine_demo` 构建通过；VK CTest **30/30**、GL CTest **29/29**；`test_vulkan` TEST 6 合并管线 + golden 通过。
- [x] Round 12：unified 剔除 + 粒子 GPU cull ——
  - **R12-1 unified 阴影**：`mega_upload_unified_cull` 上传 draw cmd + 包围球；CSM/点光 cubemap 默认 unified 单 pass；legacy flags+compact 回退。
  - **R12-2 粒子 cull**：`particles_cull`+`particle_cull.comp`；instance draw 只画 alive；UI 显示 alive。
  - **R12-3 点光阴影前向**：未做(可选)。
  - **验收**：`test_vulkan` TEST 9 unified smoke；VK CTest **30/30**、GL **29/29**。
- [x] Round 13：延迟光照 + TAA 重投影 + combined/auto-exposure ——
  - **R13-1 deferred 光照**：cluster+CSM+IBL；`light_system_cull/upload`；去掉 5% ambient。
  - **R13-2 TAA motion**：`inv(curr_view_proj)` 重投影（velocity pass 未做）。
  - **R13-3 combined+AE**：`combined_color_apply` 新签名；auto-exposure 与 combined 共存。
  - **验收**：VK CTest **30/30**、GL **29/29**。
- [x] Round 14：async 优先级 + 纹理热重载 + frame arena ——
  - **R14-1**：priority dequeue + texture decode + mip 优先级。
  - **R14-2**：`hotreload_texture_*` + `mipmap_stream_invalidate`。
  - **R14-3**：frame arena + unified cull 持久缓冲。
  - **验收**：VK CTest **30/30**、GL **29/29**；`test_async_loader` priority 测 + `test_mipmap_stream` invalidate 测。
- [x] Round 15：Chrome trace + GL golden + net replication ——
  - **R15-1**：`profiler_export_chrome_trace`；demo F11/`PROFILER_TRACE=1`。
  - **R15-2**：`test_vulkan` 双后端 golden（GL 仅 golden 路径）；`test_vulkan_gl.ppm`。
  - **R15-3**：`net_replication` transform 快照 unreliable 广播；`test_net_replication`。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 16：unified Hi-Z + velocity G-Buffer + TAA motion ——
  - **R16-1**：`unified_cull` Hi-Z；阴影 unified 接 `occ_sys`。
  - **R16-2**：G-Buffer RT3 velocity + `u_prev_vp`。
  - **R16-3**：`taa_resolve` velocity 采样。
  - **验收**：VK CTest **31/31**、GL **31/31**；`test_vulkan` unified 0 VUID。
- [x] Round 17：Combined AA velocity + net/hotreload demo 接线 ——
  - **R17-1**：`combined_aa_apply` velocity；combined shader motion 重投影。
  - **R17-2**：`BREAK_NETREP=1` demo 广播/接收 transform。
  - **R17-3**：`BREAK_HOTRELOAD_TEX` demo 纹理热重载。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 18：Combined AA history + deferred 点光阴影 + net ghost ——
  - **R18-1**：`CombinedAA` history ping-pong + `first_frame`。
  - **R18-2**：`deferred_light` 点光 cubemap 阴影采样。
  - **R18-3**：`BREAK_NETREP` ghost entity transform 应用。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 19：Combined color+cinematic + anim blend + net lerp ——
  - **R19-1**：combined color 合并 cinematic 参数，跳过双 pass。
  - **R19-2**：`BREAK_ANIM_BLEND=1` + `skeleton_apply_local_trs` + F12 crossfade。
  - **R19-3**：NetRep ghost 线性插值 + `BREAK_NETREP_LERP=0`。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 20：Forward pt shadow + anim IK + net dedup ——
  - **R20-1**：前向 `pbr_clustered` 点光 cubemap 阴影（binding 10）。
  - **R20-2**：`BREAK_ANIM_IK=1` two-bone IK demo。
  - **R20-3**：NetRep 序列去重 + `BREAK_NETREP_DEDUP=0`。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 21：Unified forward + forward velocity + net reliable ——
  - **R21-1**：`BREAK_UNIFIED_FORWARD=1` 前向 unified cull+compact。
  - **R21-2**：`BREAK_FORWARD_VEL=1` camera velocity → TAA。
  - **R21-3**：`BREAK_NETREP_RELIABLE=1` ACK 重传。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 22：Unified per-material + net ordered ——
  - **R22-1**：unified vis flags + per-material indirect（前向/延迟 mega）。
  - **R22-2**：`PACKET_ORDERED` 重排 buffer + `BREAK_NETREP_ORDERED=1`。
  - **R22-3**：VK compute storage layout 8 binding（unified cull binding 4）。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 23：Unified deferred + net reliable/ordered combo ——
  - **R23-1**：`BREAK_UNIFIED_DEFERRED=1` 延迟 G-Buffer unified per-material。
  - **R23-2**：`BREAK_NETREP_RELIABLE_ORDERED=1` + 重传去重 + 组合单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 24：Shadow per-material + net dual channel ——
  - **R24-1**：`BREAK_UNIFIED_SHADOW=1` CSM/点光 per-material indirect。
  - **R24-2**：NetRep unreliable/ordered 双通道 + reliable pending 分离。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 25：Unified shadow default + net multitype ——
  - **R25-1**：mega-buffer 默认 unified shadow；`BREAK_UNIFIED_SHADOW=0` 关闭。
  - **R25-2**：packet type 独立 channel + heartbeat API/单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 26：Unified fwd/def default + heartbeat demo ——
  - **R26-1**：mega-buffer 默认 unified forward/deferred；env 可关。
  - **R26-2**：heartbeat RTT + demo 接线 + 单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 27：Unified env docs + heartbeat roundtrip ——
  - **R27-1**：Unified / NetRep env 矩阵文档。
  - **R27-2**：`HEARTBEAT_ACK` echo + `hb_roundtrip_ms` + 单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 28：DrawBench + peer RTT table ——
  - **R28-1**：`BREAK_DRAW_BENCH=1` mega vs legacy draw 估算 + UI。
  - **R28-2**：`NetRepPeerStats[8]` per-address RTT + 单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 29：DrawBench GPU + peer eviction ——
  - **R29-1**：unified/legacy GPU timer 均值 + UI。
  - **R29-2**：peer TTL/LRU + `peer_evict_stale`/`peer_lru_full` 单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 30：DrawBench export + peer persist ——
  - **R30-1**：CSV + Chrome meta export；`BREAK_DRAW_BENCH_EXPORT`。
  - **R30-2**：`peer_save/load` + `BREAK_NETREP_PEER_FILE`。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 31：DrawBench script + peer shard ——
  - **R31-1**：`draw_bench_compare.sh` unified vs legacy。
  - **R31-2**：`peer_save/load_dir` + delta.log + 单测。
  - **验收**：VK CTest **31/31**、GL **31/31**。
- [x] Round 101：冗余遮挡剔除消除 + 动画事件回调 ——
  - **R101-1**：unified 路径全激活时跳过 `occlusion_cull_dispatch`（每帧节省 1 dispatch + 1 barrier + 1 buffer copy）；Hi-Z 生成仍运行。
  - **R101-2**：`anim_blend_evaluate` 触发事件回调；新增 `AnimEvent`/`anim_clip_add_event`；循环 wrap-around 支持。
  - **验收**：`test_animation` **24/24** 通过（新增 4 项事件测试）。
- [x] Round 102：ECS archetype edge 缓存 ——
  - **R102**：`world_add_component`/`world_remove_component` 目标 archetype 查找从 O(N) `find_archetype` 线性扫描降为 O(E) edge 查找。首次转换仍走 `find_archetype` 并缓存结果到 `edges_add[]`/`edges_remove[]`；后续相同 component 转换直接用缓存 `target` 指针，跳过类型数组构建+排序+hash 扫描。`ArchetypeEdge` 结构与字段此前已定义但为桩，现已完整实现 `edge_lookup_add`/`_remove`/`edge_cache_add`/`_remove` 四辅助函数。
  - **验收**：`test_ecs` **23/23** 通过（新增 3 项 edge cache 测试：add 命中/remove 命中/50 实体多轮转换）。
- [x] Round 103：ECS 查询增强 + 延迟点光阴影 + 异步加载优先级解码管线 + Windows Packer ——
  - **R103-1 ECS Exclude/Optional**：`ecs_query_exclude`（排除含指定组件的原型）、`ecs_query_optional`（可选组件，匹配但跳过不含的原型）、`ecs_query_refresh`（查询失效时重建匹配原型列表）；`Query` 结构扩展 `exclude_mask`/`optional_mask` 位域，`query_matches_archetype` 位掩码 O(1) 过滤。`test_ecs` 新增 5 项 Exclude/Optional 测试。
  - **R103-2 延迟点光阴影**：`deferred_light.frag`/`_vk.frag` 接入点光 cubemap 阴影采样（`HAS_POINT_SHADOW` 条件编译）；前向管线 `blinn_phong_clustered`/`pbr_clustered` 双后端同步 `HAS_POINT_SHADOW` 守卫；`PointLight` 增加 `shadow_index` 字段；`deferred.c` 绑定点光阴影纹理到延迟光照 pass。
  - **R103-3 异步加载优先级+解码管线**：priority 最小堆替换 FIFO 队列；新增 2-worker 解码线程池 `decode_pipeline.c/h`，stb_image 解码 + mipmap 生成不阻塞主线程，解码完成后回调主线程上传 GPU。`test_async_loader` 新增优先级和解码管线测试。
  - **R103-4 Windows Packer**：`CreateFileMapping` 零拷贝打包 + `FindFirstFile`/`FindNextFile` 递归遍历，与 POSIX 版二进制兼容；新增 `verify_pak.c` 验证工具。
  - **验收**：`test_ecs` 新增 5 项通过；`test_async_loader` 新增优先级/解码测试通过；双后端构建通过。
- [x] Round 104：decode pipeline 优先级队列修复 ——
  - **R104 审查**：深度审查 5 个新提交（ECS Exclude/Optional、点光 cubemap 阴影、异步加载优先级解码管线、Windows packer、Windows 编译修复），确认 point shadow 代码、VK push constant 布局、ECS 查询迭代、async loader 线程安全、Windows packer 资源释放均正确。`clustered_pipeline` 死代码不影响运行时。`HAS_POINT_SHADOW` 仅注入 pbr_clustered.frag（deferred_light.frag 无 #ifdef 守卫，blinn_phong 为回退着色器）。
  - **R104-1 decode pipeline 优先级队列**：`input_queue_push` 从 FIFO 追加改为优先级排序插入（低值=高优先级，与异步加载器 min-heap 一致），修复多 I/O 线程下低优先级请求先提交导致高优先级纹理延后解码的问题。同优先级保持 FIFO。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 105：VFS/packer 防御性编程修复 ——
  - **R105 审查**：全量深度审查着色器热路径、渲染循环、RHI 后端、点光阴影管线、ECS 查询、异步加载器、VFS/packer。确认 R84-R96 系列着色器优化无新冗余，渲染循环无冗余状态变更，点光阴影 VP 矩阵构建正确，GL/VK binding 匹配，ECS 查询迭代正确，async loader 线程安全。
  - **R105-1 VFS NULL 检查**：`vfs_mount_dir`/`vfs_mount_pak` 添加 NULL 路径参数检查，防止 `strncpy`/`fopen`/`LOG` UB 崩溃。`vfs_mount_dir` 添加显式 null 终止。
  - **R105-2 packer 缓冲区边界检查**：`add_file` 在 `memcpy` 前检查 `g_name_size + name_len` 是否超过 `g_names` 缓冲区大小，防止超长路径导致缓冲区溢出。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 106-110：VK 帧状态重置 + GL 缓存失效 + 音频流槽位泄漏 + 场景序列化边界 + 着色器文件读取加固 ——
  - **R106**：VK `rhi_frame_begin` 状态重置 + GL `rhi_destroy` 缓存失效。**R107**：`audio_stream_open` 失败路径槽位泄漏。**R108**：`scene_load_binary` chunk 表/数据边界验证。**R109**：`str_copy` 整数下溢 + `cgltf_buffer_data` NULL 解引用 + `load_gltf_texture` 栈溢出。**R110**：`particles.c`/`water.c` `read_file` ftell/malloc 检查。每轮均 23/23 测试通过。
- [x] Round 111：GPU 剔除初始化验证 + 热重载路径终止修复 ——
  - **R111 审查**：深度审查 UTF-8 解码、BVH 构建/遍历/查询、间接绘制、GPU 剔除统一管线、遮挡剔除、IBL、天空盒、接触阴影、SSS、热重载、ImGui、后期处理着色器读取。
  - **R111-1 gpucull_init 缓冲区验证**：`gpucull_init` 创建 3 个 GPU 缓冲区后未验证有效性就设置 `ready = true`。`indirect_draw_init`、`gpucull_init_unified`、`occlusion_cull_init` 均有完整验证。修复：添加三缓冲区有效性检查，失败时 `gpucull_shutdown` 清理并返回 false。
  - **R111-2 hotreload_pipeline_init memset**：未 `memset` 结构体就 `strncpy` 路径，≥255 字节时不保证 null 终止。`hotreload_texture_init` 正确使用了 `memset`。修复：入口添加 `memset(hr, 0, sizeof(*hr))`。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 112：test_vulkan.c file_read 防御性加固（全引擎 read_file 统一完成）——
  - **R112 审查**：深度审查光照系统、SSAO/SSR/TAA/DoF/Tonemap、Mipmap 流式加载、文件监视系统（Windows+Linux）、全引擎 28 个 `read_file`/`file_read` 实现完整性验证。
  - **R112-1 test_vulkan.c file_read**：缺少 `ftell` 返回值检查和 `malloc` NULL 检查，是引擎中最后一个未加固的 `read_file` 实现。修复：添加 `sz < 0` 检查和 `malloc` NULL 检查。至此全引擎 28 个 `read_file`/`file_read` 实现全部完成统一加固。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 113：SSGI uniform 位置硬编码 + VK buffer_update NULL deref 修复 ——
  - **R113 审查**：深度审查 RHI 后端（rhi_gl.c 1976 行 / rhi_vk.c 5342 行）、引擎核心（engine.c / rhi.c）、全后期处理小文件（combined_post_process / post_process / ssgi / volumetric / upscale / fxaa / color_grade / god_rays / motion_blur / sharpen / lens_flare / lens_effects / cinematic / debug_viz / forward_velocity）、骨骼动画（skeleton.c）、平台时间（time.c）。
  - **R113-1 SSGI uniform 位置硬编码**：`ssgi_init` 硬编码 `loc_blur_dir_x = 0` 和 `loc_blur_dir_y = 4`，而非从管线查询。SSGI blur 管线使用共享的 `bloom_blur.frag`，`u_direction` 是 `uniform vec2`，GL 链接器不保证其位置为 0。`post_process.c` 正确使用了 `rhi_pipeline_get_uniform_location` 查询，`ssgi.c` 遗漏。`loc_blur_dir_y = 4` 是完全未使用的死代码。修复：用 `rhi_pipeline_get_uniform_location` 查询 `u_direction`，在 `ssgi_apply` 中添加 `>= 0` 守卫。
  - **R113-2 VK buffer_update NULL deref**：`rhi_buffer_update` 和 `rhi_buffer_update_region` 的 fallback 路径调用 `vkMapMemory` 后未检查返回值。所有 VK 缓冲区使用持久映射，fallback 路径仅在 `bd->mapped == NULL`（创建时 vkMapMemory 失败）时触发。此时再次 `vkMapMemory` 也可能失败，`mapped` 指针未定义，`memcpy` 崩溃。修复：检查 `vkMapMemory` 返回 `VK_SUCCESS`，失败时提前返回。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 114：平台窗口管理与手柄输入审查（无需修复）——
  - **R114 审查**：全平台窗口管理（window_x11.c 381 行 / window_wayland.c 719 行 / window_win32.c 518 行）、手柄输入（gamepad_linux.c 421 行 / gamepad_win.c 178 行）、剔除辅助（cull.c 31 行）。所有文件 calloc + NULL 检查完整，资源释放完整，strncpy + memset 安全，设备热插拔处理完善。审查未发现问题，无需代码修改。
- [x] Round 115：网络复制缓冲区溢出 + glTF 资产加载防御性加固 ——
  - **R115 审查**：深度审查物理系统（physics.c）、动画系统（animation.c）、渲染图（render_graph.c）、命令缓冲（cmd_buffer.c）、任务系统（task.c）、网络核心（network.c）、网络复制（net_replication.c）、包序列化（packet.c）、资产加载（asset.c）、主循环（main.c）。
  - **R115-1 net_replicator_process 缓冲区溢出**：`net_reorder_store` 中 `memcpy(slot->wire, wire, len)` 溢出 `u8 wire[PACKET_MAX_SIZE]`（1400 字节）。公共 API `net_replicator_feed`/`net_replicator_feed_from` 接受任意 `len`。修复：`net_replicator_process` 入口添加 `len > PACKET_MAX_SIZE` 检查。
  - **R115-2 asset_load_gltf calloc NULL 检查**：`indices`、`sverts`、`verts`、`skin_buf`、`node_to_joint` 的 `calloc`/`malloc` 缺少 NULL 检查，分配大小来自不可信 glTF 文件数据。修复：添加 NULL 检查，分配失败时跳过原语或返回 false。
  - **R115-3 asset_load_gltf cgltf_buffer_data NULL 检查**：`cgltf_buffer_data` 返回值未检查 NULL（R109-2 已使该函数可返回 NULL）。受影响指针：`idx_data`、`pd`、`nd`、`ud`、`jd`/`wd`、`ibm_data`。修复：循环条件添加 NULL 守卫，或分配后检查并跳过。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 116：字体/脚本/ECS/LOD 防御性加固 ——
  - **R116 审查**：深度审查延迟渲染（deferred.c）、点光阴影（point_shadow.c）、字体渲染（font.c）、LOD 系统（lod.c）、相机（camera.c）、视锥剔除（frustum_cull.c）、分配器（alloc.c）、池分配器（pool.c）、性能分析器（profiler.c）、脚本引擎（script.c）、Lua 脚本（script_lua.c）、ECS 核心（ecs.c）、场景序列化（scene_serial.c 部分）、输入（input.c）、日志（log.c）。
  - **R116-1 font.c malloc NULL 检查**：`font_renderer_init` 中着色器源码 `malloc(vs_len+1)`/`malloc(fs_len+1)` 未检查 NULL，失败时 `fread(NULL,...)` 崩溃。`quad_data` malloc 同样未检查。修复：添加 NULL 检查，失败时 fclose 或返回 false。
  - **R116-2 script.c ftell/malloc NULL 检查**：`script_load` 中 `ftell` 返回 -1 时 `(usize)sz+1` 回绕为 0，`malloc(0)` 可能返回非 NULL，`fread` 读取 `SIZE_MAX` 字节溢出。`malloc` 返回 NULL 时崩溃。修复：`sz < 0` 提前返回 + malloc NULL 检查。
  - **R116-3 ecs.c calloc/malloc/realloc NULL 检查**：`chunk_alloc`、`create_archetype`、`world_create`、`world_add_component`、`world_remove_component`、`world_query`/`ecs_query_refresh` 多处分配未检查返回值，失败时解引用 NULL 崩溃。修复：全路径添加 NULL 检查，chunk_alloc 返回 NULL，调用方检查并清理/降级。
  - **R116-4 lod.c level_count==0 u32 下溢**：`lod_select_by_*` 中 `level_count - 1` 当 `level_count==0` 时 u32 下溢为 `UINT32_MAX`，越界读 `thresholds_sq`。修复：`lod_register` 拒绝 `level_count==0`。
  - **验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。
- [x] Round 117：BVH/光照 calloc NULL 检查 ——
  - **R117 审查**：深度审查地形系统（terrain.c 622 行）、BVH 物理（bvh.c 507 行）、异步加载器（async_loader.c 505 行）、集群光照（lighting.c 357 行）、遮挡剔除（occlusion_cull.c 410 行）。
  - **R117-1 bvh.c calloc/realloc/malloc NULL 检查**：BVH SAH 构建路径 5 处分配未检查返回值。`bvh_init` calloc 失败时 `bvh->nodes=NULL`；`bvh_alloc_node` realloc 失败时旧指针泄漏 + `bvh->nodes` 置 NULL；`bvh_build` 中 leaf_map/nodes/_build_indices 三处 calloc/malloc 失败解引用 NULL。修复：全路径 NULL 检查，realloc 使用临时指针避免泄漏，失败时 `bvh->root = BVH_NULL` 安全返回。
  - **R117-2 lighting.c staging_block calloc NULL 检查**：`light_system_upload_grid` 中 `calloc(1, gb_off + gb_bytes)` 分配 staging buffer 未检查 NULL，OOM 时后续 `memcpy` 崩溃。修复：添加 NULL 检查 + LOG_ERROR + return。
  - **验收**：全部 23/23 测试通过。BVH/GL 构建路径编译成功。
