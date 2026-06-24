# Round 11+ 性能优先补全计划

> 在 Round 0–10 完成后，依据 [Implementation_Status.md](./Implementation_Status.md) 中仍为 **部分 / 桩 / 缺失** 的条目，制定后续补全路线。
> **原则：性能最优先** — 先修“算了但没生效 / 多 pass 可合并 / CPU 热点可 GPU 化”，再补 gameplay / 工具链特性。

## 当前缺口总览（按性能影响排序）

| 优先级 | 模块 | 现状 | 性能损失 |
|--------|------|------|----------|
| P0 | 遮挡剔除 Hi-Z | ~~compute 跑通但结果未驱动 draw~~ **R11 已接线**，默认开 | — |
| P0 | GPU 间接绘制默认路径 | ~~mega-buffer 有但 gpucull 默认关~~ **R11 mega-buffer 就绪时默认开** | — |
| P0 | 合并后处理 | ~~demo 仍多 pass~~ **R11 demo 默认 combined 路径**(auto-exp/cine 除外) | — |
| P1 | unified_cull | ~~单 pass 压缩已实现，main 未用~~ **R12 阴影/点光阴影默认 unified** | 前向仍 per-mat compact |
| P1 | 粒子 GPU cull | ~~`particle_cull.comp` 未接线~~ **R12 已接线** | draw 随 alive 数而非 max |
| P1 | 延迟渲染 | light_data 忽略、环境光硬编码 | deferred 路径光照质量/一致性差 |
| P2 | TAA motion vector | 无 per-object / 相机 MV | TAA 质量差、重影 |
| P2 | 点光阴影(前向) | 仅 deferred cube | 前向 PBR 无点光阴影 |
| P2 | Async loader 优先级 | 字段未生效 | 流式资源争抢 I/O |
| P3 | Network 复制 | socket 有、无游戏同步 | 非渲染热点 |
| P3 | Animation blend/IK demo | 代码有、demo 未接 | 非帧预算热点 |
| P3 | 字体 SDF / UI 完善 | Latin-1 atlas | 非 GPU 瓶颈 |
| P3 | RHI bindless / push API | 部分缺失 | 大场景材质切换 |

---

## Round 11：剔除闭环 + 合并后处理默认化（已完成）

**目标**：让已有 GPU 路径在 demo 默认生效，减少无效 draw 与 post pass 切换。

### [x] R11-1 遮挡结果驱动前向 draw
- [x] 建立 `scene node → occ 紧凑索引` 映射（与 Hi-Z upload 同序）
- [x] 前向 mega-buffer indirect：`vis_flags &= occlusion(prev frame)`
- [x] 非 indirect CPU 路径：在 `frustum_cull_batch` 后 AND 遮挡位
- [x] 保留 1 帧延迟（已有 readback 设计）

### [x] R11-2 GPU 剔除默认开启
- [x] `mega_buf.valid` 时默认 `gpu_indirect_enabled && gpucull_enabled`
- [x] 初始化时调用 `gpucull_init_unified`（为 R12 铺路）

### [x] R11-3 合并后处理接入 demo
- [x] 初始化 `CombinedAA` / `CombinedColor`
- [x] 当 `taa && fxaa` 且 combined 管线可用 → 单 pass AA
- [x] 当 `tonemap && cg && !cine` 且 combined 可用 → 单 pass 调色（auto-exposure 仍走原 tonemap 路径）

**验收（实测）**：双后端 `engine_demo` 构建通过；VK CTest **30/30**、GL CTest **29/29**；`test_vulkan` TEST 6 合并管线 + golden 通过；debug UI 显示 occ culled / CombinedPost 状态。

---

## Round 12：统一 GPU 驱动绘制 + 粒子剔除（已完成）

### [x] R12-1 unified_cull 替换 shadow/forward 的 flags+compact
- [x] mega-buffer 构建后 `mega_upload_unified_cull` 上传 `GPUCullDrawCmd` + `GPUCullObject`
- [x] CSM 阴影 + 点光 cubemap 面：默认 `gpucull_dispatch_unified` + `gpucull_execute_indirect_draws`（1 compute pass）
- [x] 前向/G-Buffer 仍走 CPU frustum+LOD+occ + per-material compact（材质切换需分组 bind）
- [ ] Hi-Z 并入 unified（占位参数保留，→R13+）

### [x] R12-2 粒子 `particle_cull.comp` 接线
- [x] `particles_cull` compute 写 alive index + draw_count
- [x] `particle.vert` 改 `gl_InstanceID` + indices 查找，只 draw alive 实例
- [x] debug UI 显示 alive 数

### [ ] R12-3 点光阴影前向采样（可选，未做）

**验收（实测）**：`test_vulkan` TEST 9 unified smoke 3 帧 dispatch 通过；VK CTest **30/30**、GL CTest **29/29**；demo 阴影 unified 路径 + 粒子 GPU cull 默认开。

---

## Round 13：延迟渲染与 TAA 质量（已完成）

### [x] R13-1 deferred 吃真实 light_data + IBL 环境项
- [x] `deferred_light.frag`/`deferred_light_vk.frag` 接 cluster grid + `light_data`、CSM PCSS、split-sum IBL
- [x] 去掉 5% 硬编码环境光；deferred 路径每帧 light cull/upload

### [x] R13-2 TAA 重投影修复（velocity pass 未做）
- [x] `combined_aa`/`taa_resolve` 使用 `inv(curr_view_proj)` 而非 `inv(proj)`
- [ ] Motion vector G-buffer / velocity pass（→后续）

### [x] R13-3 合并后处理与 auto-exposure 共存
- [x] `combined_color_apply` 传入真实 `tonemap.exposure`/gamma/mode
- [x] 先 `tonemap_update_auto_exposure` 再 combined pass；移除 `!auto_exposure` 门禁

**验收（实测）**：双后端构建通过；VK CTest **30/30**、GL CTest **29/29**。

---

## Round 14：资源 I/O 与内存（已完成）

### [x] R14-1 Async loader 优先级 + 解码管线
- [x] I/O 队列按 `priority` 值 dequeue（低值优先）
- [x] `async_loader_request_range_priority` / `async_loader_request_texture`（worker 上 stbi 解码）
- [x] `mipmap_stream` 按 mip level 设优先级；`asset_load_texture_async` 走 decode 路径

### [x] R14-2 纹理热重载
- [x] 实现 `hotreload_texture_init/poll/shutdown`（mtime + stbi + GPU 重建）
- [x] `mipmap_stream_invalidate` 驱逐驻留 level，供热重载协同

### [x] R14-3 Pool/Arena 接入热点
- [x] 主循环 `frame_arena`（256KB）每帧 reset；截图像素走 arena
- [x] unified cull upload 改用持久 scratch 缓冲，去掉每帧 malloc

**验收（实测）**：双后端构建通过；VK CTest **30/30**、GL CTest **29/29**；`test_async_loader` 增 priority 顺序测；`test_mipmap_stream` 增 invalidate 测。

---

## Round 15：工具链与长期质量（已完成）

### [x] R15-1 Profiler Chrome trace 导出
- [x] `profiler_export_chrome_trace()`：CPU regions + GPU timer 样本 → Chrome Trace JSON
- [x] demo：**F11** 即时导出；`PROFILER_TRACE=1` 退出时写 `profile_trace.json`
- [x] `test_profiler` 增导出结构验证

### [x] R15-2 GL golden + test_vulkan 条件编译镜像
- [x] `#ifdef ENGINE_VULKAN` 切换 golden 路径与着色器/backend
- [x] GL 构建 CTest 跑 `test_vulkan`（golden-only 快速路径）
- [x] 提交 `tests/golden/test_vulkan_gl.ppm`

### [x] R15-3 Network 最小复制原型
- [x] `net_replication.{h,c}`：`NET_PKT_TRANSFORM_SNAPSHOT` + unreliable UDP
- [x] `test_net_replication` localhost loopback 测

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 16：剔除深化 + TAA motion（已完成）

### [x] R16-1 unified_cull Hi-Z 遮挡
- [x] `unified_cull.comp` 增可选 Hi-Z 球体测试（与 `occlusion_cull` 同深度约定）
- [x] `gpucull_dispatch_unified` 绑定 Hi-Z 金字塔 + fallback 1×1 纹理（满足 VK descriptor 要求）
- [x] CSM / 点光阴影 unified 路径传入 `occ_sys.hi_z_texture`（1 帧延迟）

### [x] R16-2 Velocity G-Buffer
- [x] 延迟 MRT 增 RT3 velocity（`R16G16B16A16`，NDC delta）
- [x] `gbuffer*.vert/frag` 写 per-pixel motion；demo 传 `u_prev_vp`

### [x] R16-3 TAA 采样 velocity
- [x] `taa_resolve` 可选第 4 路 velocity 纹理；`u_taa_use_velocity` 切换 per-pixel / 相机重投影
- [x] 延迟路径自动绑定 `gbuf_velocity`；combined AA history 仍绑 current（→R18-1）

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**；`test_vulkan` unified smoke 0 VUID。

---

## Round 17：Combined AA motion + Demo 接线（已完成）

### [x] R17-1 Combined AA velocity
- [x] `combined_aa_apply(..., velocity_tex)` 对齐 `taa_resolve` 第 4 路 velocity
- [x] `combined_taa_fxaa*.frag` 增 `u_taa_velocity` / `u_taa_use_velocity`（VK push@212）
- [x] 延迟路径 combined AA 自动绑定 `gbuf_velocity`

### [x] R17-2 net_replication demo 接线
- [x] `BREAK_NETREP=1`：UDP :19900 loopback；每 10 帧广播角色 transform
- [x] 非阻塞 recv + debug UI 显示 sent/recv/last 计数

### [x] R17-3 hotreload_texture demo 接线
- [x] `BREAK_HOTRELOAD_TEX=<path>` 监视并热重载 `render.fallback_tex`
- [x] 主循环 `hotreload_texture_poll`

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 18：TAA 历史缓冲 + 延迟点光阴影 + 网络可见化（已完成）

**目标**：修复 combined AA 路径下 TAA 实际不生效的缺陷；补齐延迟路径点光阴影采样；让 R17 网络复制在画面上可见。

### [x] R18-1 Combined AA history ping-pong
- [x] `CombinedAA` 增 `history_fbo[2]`、`history_idx`、`first_frame`（对齐 `TAASystem`）
- [x] combined 路径：hist 读 ping-pong 缓冲，结果写 write FBO；`combined_aa_get_output` 返回当前帧输出
- [x] resize/shutdown 生命周期与 `first_frame` 重置（re-init 清零）

### [x] R18-2 延迟路径点光阴影采样
- [x] `deferred_light*.frag` binding 5(VK)/10(GL) 接 `u_point_shadow_cubes[4]`
- [x] `point_shadow_test()` + push/uniform 映射 light index → cubemap slot
- [x] `deferred_lighting_pass(..., &pt_shadows)` + `bind_material_textures_ibl` 扩展 cubemap 绑定
- [x] `PointLightShadow.src_index` 记录 light_data 索引

### [x] R18-3 Net replication 远端 transform 应用
- [x] `BREAK_NETREP=1` spawn ghost entity（entity_id=1 快照）
- [x] recv 成功后写 ghost `CTransform`；`BREAK_NETREP_APPLY=0` 仅统计
- [x] debug UI 显示 ghost pos / apply 状态

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 19：后处理合并 + 动画混合 + NetRep 插值（已完成）

### [x] R19-1 Combined color + cinematic 单 pass
- [x] 移除 `!cine_enabled` 门禁；`combined_color_apply` 传入 `cine_sys` aberration/vignette/grain
- [x] combined 路径成功时跳过独立 `cinematic_apply`（避免双 pass）

### [x] R19-2 Animation blend demo 接线
- [x] `skeleton_apply_local_trs()`：将 `anim_blend_evaluate` 输出写入 skinning 矩阵
- [x] `BREAK_ANIM_BLEND=1`：`anim_layer_play` + 每帧 blend evaluate；**F12** crossfade 切换 clip

### [x] R19-3 NetRep ghost 线性插值
- [x] recv 更新 `netrep_ghost_target`；每帧 lerp 写入 ghost transform
- [x] `BREAK_NETREP_LERP=0` 恢复即时 snap

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 20：前向点光阴影 + Animation IK + NetRep 去重（已完成）

### [x] R20-1 前向点光阴影（R12-3）
- [x] `pbr_clustered*.frag` 增 `point_shadow_test` + binding 10 cubemap 数组
- [x] push/uniform：`u_point_shadow_count` + `u_point_shadow_light_0..3`
- [x] VK 描述符 binding 10（SSAO 保持 binding 5）；`bind_material` 传 cubemap
- [x] 延迟路径仍用 binding 5（`ssao=NULL` 时 RHI 自动路由）

### [x] R20-2 Animation IK demo
- [x] `skeleton_compute_world_transforms()` 供 IK 使用
- [x] `BREAK_ANIM_IK=1`：`anim_ik_solve` 在 blend 后、skinning 前；目标绕相机轨道

### [x] R20-3 NetRep 序列去重
- [x] `NetReplicator.seq_dedup` + `last_recv_seq`；丢弃 stale 包
- [x] `BREAK_NETREP_DEDUP=0` 关闭；debug UI 显示 `stale=` 计数

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 21：Unified 前向 + Forward Velocity + NetRep 可靠层（已完成）

### [x] R21-1 Unified 前向单 dispatch
- [x] `mega_unified_cull_draw()` 共享 shadow/forward；Hi-Z + frustum + compact 单 pass
- [x] `BREAK_UNIFIED_FORWARD=1`：mega-buffer 前向路径跳过 CPU vis，单次 indirect draw

### [x] R21-2 前向 velocity pass
- [x] `forward_velocity.{h,c}` + `camera_velocity*.frag`：由 depth 重建 NDC motion
- [x] `BREAK_FORWARD_VEL=1`：前向路径 TAA/combined AA 使用 camera velocity 纹理

### [x] R21-3 NetRep 可靠重传
- [x] `PACKET_RELIABLE` + pending 缓存 + `net_replicator_retry_pending()`
- [x] header `ack` 字段双向确认；`BREAK_NETREP_RELIABLE=1`；debug UI `retry=` 计数

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 22：Unified per-material + NetRep 有序层（已完成）

### [x] R22-1 Unified 前向/延迟 per-material
- [x] `unified_cull.comp` binding 4 `VisibleFlags`；`gpucull_read_vis_flags()` 读回 per-draw 可见性
- [x] `mega_unified_vis_flags()` + `mega_mat_groups_draw()`：单 dispatch 后按材质分组 indirect
- [x] `BREAK_UNIFIED_FORWARD=1`：前向 + 延迟 G-Buffer mega 路径均走 unified vis + per-material

### [x] R22-2 NetRep 有序层
- [x] `PACKET_ORDERED` + 32-slot 重排 buffer；`net_replicator_feed()` 供单测
- [x] `BREAK_NETREP_ORDERED=1`；debug UI `reord=` 计数

### [x] R22-3 VK 描述符
- [x] compute `storage_layout` 扩至 8 binding，修复 unified cull binding 4 校验错误

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 23：Unified 延迟独立开关 + NetRep 可靠有序组合（已完成）

### [x] R23-1 Unified 延迟 G-Buffer 独立路径
- [x] `BREAK_UNIFIED_DEFERRED=1`：延迟 mega-buffer 路径单独启用 unified vis + per-material
- [x] `mega_use_unified_vis()`：前向仅 `BREAK_UNIFIED_FORWARD`；G-Buffer 可用 `DEFERRED` 或 `FORWARD` 任一
- [x] debug UI 显示 `+deferred` / `+fwd+def`

### [x] R23-2 NetRep 可靠+有序组合
- [x] `BREAK_NETREP_RELIABLE_ORDERED=1` 同时开启 ACK 重传与有序重排
- [x] 有序路径抑制 reliable 重传重复交付（`reorder_duplicate` 计数）
- [x] `test_net_replication` 增 `reliable_ordered_combined` 单测

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 24：Shadow per-material unified + NetRep 双通道（已完成）

### [x] R24-1 Shadow per-material unified
- [x] `BREAK_UNIFIED_SHADOW=1`：CSM / 点光阴影 unified vis + `mega_mat_groups_indirect`
- [x] 回退链：per-material → 单 indirect compact → legacy flags/CPU

### [x] R24-2 NetRep channel 分离
- [x] `NetRepUnreliableChannel` / `NetRepOrderedChannel` / `NetRepReliablePending` 独立状态
- [x] 发送端双序列号（unordered vs ordered）；接收端按 `PACKET_ORDERED` 标志路由
- [x] `test_net_replication` 增 `dual_channel_sequences` 单测

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 25：Unified shadow 默认化 + NetRep 多类型 channel（已完成）

### [x] R25-1 Unified shadow 默认化
- [x] mega-buffer + mat groups + unified ready 时默认 `unified_shadow_enabled`
- [x] `BREAK_UNIFIED_SHADOW=0` 关闭；`=1` 强制开启

### [x] R25-2 NetRep 多类型 channel
- [x] `unreliable[]` / `ordered[]` 按 `NET_PKT_*` type 索引（transform / heartbeat）
- [x] `net_replicator_send_heartbeat()` + `multitype_independent_sequences` 单测

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 26：Unified forward/deferred 默认化 + NetRep heartbeat demo（已完成）

### [x] R26-1 Unified forward/deferred 默认化
- [x] mega-buffer + mat groups + unified ready 时默认 `unified_forward_enabled` 与 `unified_deferred_enabled`
- [x] `BREAK_UNIFIED_FORWARD=0` / `BREAK_UNIFIED_DEFERRED=0` 可分别关闭

### [x] R26-2 NetRep heartbeat demo
- [x] heartbeat payload 携带 send_time_ms；接收端计算 `hb_last_rtt_ms`
- [x] demo 每 60 帧发 heartbeat、recv 排空循环；debug UI `hb=sent/recv rtt=`
- [x] `BREAK_NETREP_HEARTBEAT=0` 关闭；`heartbeat_rtt` 单测

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 27：Unified 全路径默认文档 + NetRep 双向 RTT（已完成）

### [x] R27-1 Unified 全路径默认文档
- [x] env 矩阵表（shadow / forward / deferred + NetRep 开关）
- [x] mega-buffer 默认 unified 路径说明与回退链

#### Unified env 矩阵（mega-buffer + mat groups + `unified_ready` 时默认开启）

| 环境变量 | 默认 | `=1` | `=0` |
|----------|------|------|------|
| `BREAK_UNIFIED_SHADOW` | 开 | 强制开 | 关闭 shadow per-material |
| `BREAK_UNIFIED_FORWARD` | 开 | 强制开 | 关闭前向 unified vis |
| `BREAK_UNIFIED_DEFERRED` | 开 | 强制开 | 关闭延迟 G-Buffer unified vis |

回退链：unified per-material indirect → 单 indirect compact → legacy flags / CPU cull。

#### NetRep env 矩阵（需 `BREAK_NETREP=1`）

| 环境变量 | 默认 | 说明 |
|----------|------|------|
| `BREAK_NETREP_HEARTBEAT` | 开 | 60 帧周期发 heartbeat |
| `BREAK_NETREP_HB_ECHO` | 开 | 收到 heartbeat 自动 echo ack |
| `BREAK_NETREP_DEDUP` | 开 | 序列号去重 |
| `BREAK_NETREP_RELIABLE` | 关 | ACK + 重传 |
| `BREAK_NETREP_ORDERED` | 关 | 32-slot 有序重排 |
| `BREAK_NETREP_RELIABLE_ORDERED` | 关 | 可靠 + 有序组合 |
| `BREAK_NETREP_APPLY` | 开 | ghost 应用远端 transform |
| `BREAK_NETREP_LERP` | 开 | ghost 线性插值 |

### [x] R27-2 NetRep 双向 RTT
- [x] `NET_PKT_HEARTBEAT_ACK` + `net_replicator_send_heartbeat_ack()`
- [x] 收到 heartbeat 向 `from` echo ack（payload：原 `send_time_ms` + `echo_seq`）
- [x] 发送方收到 ack 计算 `hb_roundtrip_ms`；demo UI `echo=` / `rt=`
- [x] `BREAK_NETREP_HB_ECHO=0` 关闭 echo；`heartbeat_roundtrip_echo` / `heartbeat_ack_feed` 单测

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 28：Unified draw 基准 + NetRep 多 peer RTT（已完成）

### [x] R28-1 Unified draw 基准
- [x] `BREAK_DRAW_BENCH=1` 帧内统计 `mega` draw calls vs `legacy~` 逐 mesh 估算
- [x] shadow / forward / deferred mega 路径接入；debug UI `DrawBench: mega= legacy~ ratio=`

### [x] R28-2 NetRep 多 peer RTT
- [x] `NetRepPeerStats peers[8]` 按 `NetAddress` 维护 per-peer `last_rtt_ms` / `roundtrip_ms`
- [x] `net_address_equal()` + `net_replicator_peer_count/at()`；demo UI 列出 peer
- [x] `peer_rtt_table` / `heartbeat_ack_feed` 单测扩展

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 29：DrawBench GPU 对比 + NetRep peer 老化（已完成）

### [x] R29-1 DrawBench GPU 帧时间对比
- [x] unified / legacy mega 路径帧标记 + shadow/scene/forward GPU timer 累计均值
- [x] debug UI `gpu_u=` / `gpu_l=` 帧数样本（`BREAK_DRAW_BENCH=1`）

### [x] R29-2 NetRep peer 老化
- [x] `last_seen_ms` + 默认 TTL 60s；`net_replicator_peer_evict_stale()`
- [x] 表满 LRU 复用最旧 slot；`BREAK_NETREP_PEER_TTL=0` 关闭 TTL
- [x] `peer_evict_stale` / `peer_lru_full` 单测

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 30：DrawBench 导出 + NetRep peer 持久（已完成）

### [x] R30-1 DrawBench 导出
- [x] 120 帧 ring buffer 记录 frame/mega/legacy/gpu_ms
- [x] `draw_bench_export_csv()` + `BREAK_DRAW_BENCH_EXPORT=<path>`（默认 `draw_bench.csv`）
- [x] F11 / `PROFILER_TRACE=1` 时同步导出；Chrome trace 增 `draw_bench_*` meta instant 事件

### [x] R30-2 NetRep peer 持久
- [x] `net_replicator_peer_save/load()` 文本格式 v1
- [x] `BREAK_NETREP_PEER_FILE=<path>` 启动 load、退出 save
- [x] `peer_save_load` + `profiler_export_chrome_meta` 单测

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 31：DrawBench 对比脚本 + NetRep peer 分片（已完成）

### [x] R31-1 DrawBench 对比脚本
- [x] `engine/scripts/draw_bench_compare.sh`：unified 默认 vs legacy（unified 全关）两阶段跑分
- [x] 输出 `draw_bench_unified.csv` / `draw_bench_legacy.csv` + summary 行对比

### [x] R31-2 NetRep peer 分片 / 增量
- [x] `net_replicator_peer_save_dir/load_dir()`：每 peer 独立 `.peer` 文件
- [x] `net_replicator_peer_save_delta/load_delta()`：追加 dirty peer 到 `delta.log`
- [x] `BREAK_NETREP_PEER_DIR=<dir>` + 60 帧增量 save；`peer_save_dir`/`peer_save_delta` 单测

**验收（实测）**：双后端构建通过；VK CTest **31/31**、GL CTest **31/31**。

---

## Round 32+ backlog（未排期）

| 项 | 说明 | 优先级 |
|----|------|--------|
| DrawBench CI 集成 | CTest 或脚本纳入回归 | P3 |
| NetRep peer 压缩 | delta.log 轮转 / 压缩 | P3 |

---

## 文档维护约定

每轮完成后更新：
1. [Implementation_Status.md](./Implementation_Status.md) — 状态矩阵 + 「最近更新」+ 修复进度 checklist
2. 本文档 — 对应 Round 小节标记 `[x]` 与实测结论
3. **不修改** [PureC_Engine_ExecutionPlan.md](./PureC_Engine_ExecutionPlan.md) 历史 Phase 勾选（仅作 archive）

## R49-R60 CPU 侧性能优化 + 审查修复

**目标**：消除主循环 CPU 侧冗余矩阵运算与三角函数调用，修复 cam_fwd 前方向约定不一致。

### [x] R49 mat4_mul_ortho_diag
- 正交投影×视图矩阵稀疏乘法，利用 D 矩阵对角+平移结构
- 21 mul + 12 add vs 通用 64 mul + 48 add
- 对称正交(d3x=d3y=d3z=0)时 12 mul + 0 add

### [x] R50 mat4_mul_proj_view
- 透视投影×视图矩阵稀疏乘法，利用 P 矩阵稀疏结构
- 24 mul + 10 add vs 通用 64 mul + 48 add
- 支持 TAA jitter (e[2][0..1])

### [x] R51 fast_rsqrt 重力循环
- 重力方向归一化用 fast_rsqrt 替换 sqrtf + 除法
- 距离阈值从 gdist < 0.5 改为 gd2 < 0.25（等价）

### [x] R52 复用缓存三角函数 + camera_inv_view
- 主循环 cam_cy/cam_sy/cam_cp/cam_sp 从 camera._cy 等缓存读取（省 4 cosf/sinf）
- camera_inv_view: 解析逆视图矩阵，利用 R 正交性 R^T 列=V 旋转行，0 额外 trig

### [x] R53-fix mat4_inv_perspective + inv(VP) 合成
- 透视矩阵解析逆：3 div + 6 mul vs 通用 ~120 mul + 1 div
- inv(VP) = camera_inv_view * mat4_inv_perspective 替代通用 mat4_inverse(VP)
- third-person 时调整 inv(V) 的平移列
- top-down 视角回退通用逆

### [x] R58/R59 增量三角旋转
- IK 轨道与轨道灯用 Taylor 近似(cos≈1-x²/2, sin≈x-x³/6)替代每帧 cosf/sinf
- 256 帧周期性精确重置消除漂移
- dt 尖峰回退到精确 trig

### [x] R60-fix cam_fwd 前方向约定 + 路径缓存 trig
- 旧 cam_fwd = (cy*cp, sp, sy*cp)：yaw=0 指向 +X（右方），与 camera_view 不一致
- 新 cam_fwd = (cp*sy, sp, -cp*cy)：yaw=0 指向 -Z（前方），对齐 camera_view FPS 约定
- 所有下游使用已更新：实体发射/地形笔刷/阴影级联/物理推力/音频监听
- 路径摄像机分支手动更新 _cy/_sy/_cp/_sp 防止缓存过期

### [x] 审查修复
- 纠正 mat4_mul_ortho_diag 注释（7 非零元素/21 mul，非 4/16）
- 删除冗余 cam_fwd 局部变量遮蔽（main.c L2888）
- 修正 camera_inv_view 注释存储约定（e[col][row] 列主序，非 e[row][col]）
- 补充 3 项新测试：逆 VP 端到端、非对称正交、极端 FOV

**验收**：test_math 45/45、test_camera_frustum 22/22、engine_demo 编译通过。

## R61 审查修复：三角缓存顺序 + 第三人称逆VP测试

**目标**：消除 camera_update 缓存三角函数一帧延迟，补充第三人称逆VP端到端测试。

### [x] R61-1 camera_update 三角缓存顺序修复
- 旧代码：先缓存 trig → 再更新 yaw/pitch → 下游读到旧帧 trig（一帧延迟）
- 新代码：先 WASD 移动（用旧缓存 trig） → 更新 yaw/pitch → 缓存新 trig
- 效果：cam_fwd / camera_view / camera_inv_view / main.c cam_cy 等均反映当帧朝向
- WASD 移动仍使用旧帧朝向（语义正确：朝哪走）

### [x] R61-2 第三人称逆VP端到端测试
- 新增 camera_inv_vp_third_person 测试
- 验证：view 矩阵应用 R*fwd*tp 偏移后，inv(VP) = (inv_view with eye-fwd*tp) * inv_proj
- 与通用 mat4_inverse(VP) 逐元素比对（容差 1e-3）
- 覆盖延迟光照/TAA 世界坐标重建路径

## R62 审查修复：ecam_right 符号 + mat4_lookat 约定 + 等价性测试

**目标**：修正 ecam_right 与 camera right 方向不一致，修正 mat4_lookat 矩阵存储约定，补充 camera_view 等价性测试。

### [x] R62-1 ecam_right 符号修正
- 旧代码：ecam_right = vec3(cam_cy, 0, cam_sy) — 指向摄像机左侧（与 camera_update right = (-cy,0,-sy) 反向）
- 新代码：ecam_right = vec3(-cam_cy, 0, -cam_sy) — 与 camera right 方向一致
- 效果：实体从右到左正确发射

### [x] R62-2 mat4_lookat 矩阵存储约定修正
- 旧代码：right = cross(f,up) 右手约定 + 平移在行3 — 与 camera_view 不兼容
- 新代码：right = -cross(f,up) 左手约定 + 平移在列3 — 与 camera_view 一致
- 效果：top_down_view 路径矩阵约定与主渲染路径统一

### [x] R62-3 camera_view_matches_lookat 等价性测试
- 新增测试：验证 camera_view 与 mat4_lookat 逐元素一致
- 确保 camera_view 的解析构造与 mat4_lookat 的通用构造等价

**验收**：test_math 45/45、test_camera_frustum 24/24、engine_demo 编译通过。

## R63 审查加固：CSM lview 约定对齐 + API 契约 + 互斥逻辑 + 测试加强

**目标**：消除 CSM 阴影视图矩阵与 camera_view 约定不一致，文档化 mat4_lookat API 契约，显式化互斥逻辑，加强测试覆盖。

### [x] R63-1 CSM lview 行0 对齐左手约定
- 旧行0：(sx, 0, sz, -(sx*ex+sz*ez)) — 右手叉积 right = cross(f,up)
- 新行0：(-sx, 0, -sz, sx*ex+sz*ez) — 左手叉积 right = -cross(f,up)
- 与 camera_view 行0 模式一致：(-s_RH, dot(s_RH, eye))
- 阴影渲染+采样使用同一 VP，约定统一不影响正确性

### [x] R63-2 math.h mat4_lookat API 契约文档化
- 声明上方添加左手约定注释：right=-normalize(cross(f,up))、平移在 e[i][3]
- 防止调用者按 textbook 右手约定使用

### [x] R63-3 top_down_view 互斥逻辑显式化
- 从 `if(top_down_view)` 改为 `else if(top_down_view)`
- 显式表达 third_person 与 top_down_view 互斥
- 添加注释标明 top_down 替换整个 view 矩阵

### [x] R63-4 camera_view_matches_lookat 测试加强
- 补充近 gimbal-lock 参数组合（pitch=1.5f，cp≈0.0707）
- 验证 vec3_normalize 在小分母下 1e-4f 容差仍足够

**验收**：test_math 45/45、test_camera_frustum 24/24、engine_demo 编译通过。


## R65 审查修复：CSM u向量叉积修正 + 栈安全加固

### R65-1 CSM lview u向量叉积公式修正（Critical）

**问题**：R64 将 u 向量从 `cross(s_unnorm, f)` 改为 `cross(s_norm, f)` 时，叉积展开公式三处全部错误：
- `ux_raw = -fy * sx`（实际计算 `fy*fz*inv_sl`）→ 应为 `-fy * fx`
- `uy_raw = sx*fz + sz*fx`（实际计算 `inv_sl*(fx²-fz²)`）→ 应为 `fx*fx + fz*fz`
- `uz_raw = -fy * sz`（实际计算 `-fy*fx*inv_sl`）→ 应为 `-fy * fz`

典型太阳方向 `(0.465, -0.814, 0.349)` 下，错误 u 向量与正确方向夹角 ~83.5°，视空间 y 坐标相对误差 124%，CSM 阴影大面积错位。

**修正**：回退为 `cross(s_unnorm, f) = (-fy*fx, fx²+fz², -fy*fz)` + `fast_rsqrt` 归一化。该公式与 `cross(s_norm, f)` 方向相同（`s_norm = s_unnorm * inv_sl` 为标量缩放），语义清晰且不会引入新展开错误。

### R65-2 渲染热路径栈数组→static持久缓冲区

**问题**：main.c 中 12 处 16-64KB 栈数组（7× u32[16384] + 2× u8[16384] + 2× mega_mat_groups 内 u32[16384] + positions/radii[GPUCULL_MAX_OBJECTS]），最大并发路径栈占用 144KB。在受限栈环境（WASM 256KB、工作者线程 512KB）下可导致栈溢出。

**修正**：
- 新增 5 个文件作用域 static 缓冲区：`g_vis_flags[16384]`、`g_draw_vis[16384]`、`g_node_vis[16384]`、`g_cull_positions[GPUCULL_MAX_OBJECTS*3]`、`g_cull_radii[GPUCULL_MAX_OBJECTS]`
- 所有路径（CSM/point shadow/forward/deferred）顺序执行，不并发访问，可安全复用
- `node_vis = {0}` 零初始化改为显式 `memset(g_node_vis, 0, sizeof(g_node_vis))`
- 最大并发路径栈占用从 **144KB → 0KB**

**验收**：test_math 45/45、test_camera_frustum 24/24、engine_demo 编译通过。


## R66 审查加固：栈安全补漏 + 遮挡剔除对齐 + Debug UI门控 + 冗余消除

### R66-1 512KB occ_aabbs 栈数组→static缓冲区（Critical）

**问题**：R65 修复了 12 处栈数组，但遗漏了 `ObjectAABB occ_aabbs[OCCLUSION_MAX_OBJECTS]`（16384×32B=512KB），是最大的单处栈分配。

**修正**：新增 `static ObjectAABB g_occ_aabbs[OCCLUSION_MAX_OBJECTS]`，改为指针引用。至此所有大栈数组已消除，总 static 常驻 720KB，最大并发栈占用 0KB。

### R66-2 延迟渲染路径补遮挡剔除检查

**问题**：前向路径有 `if (!node_occ_visible(ni)) g_vis_flags[gi] = 0;`，延迟路径缺少，两路径行为不对称，延迟 overdraw 增加。

**修正**：延迟路径 visibility 构建循环中添加遮挡检查。

### R66-3 g_vis_flags 跨材质组迭代防御性清零

**问题**：static 缓冲区跨组迭代复用，未填满的尾部保留前组值（假阳性）。

**修正**：4 处填充循环前添加 `memset(g_vis_flags, 0, gcount * sizeof(u32))`。

### R66-4 CSM u 向量归一化复用 inv_sl

**问题**：对单位光方向 `u_len2 = s_len2 = fx²+fz²`，第二次 `fast_rsqrt` 完全冗余。

**修正**：直接用 `inv_sl` 乘各分量，消除冗余 rsqrt 和 u_len2 计算。

### R66-5 Debug UI 可见性门控

**问题**：720 行计算和 136 次 `vsnprintf` 无论 UI 可见性都执行，每帧 ~2ms+ 浪费。

**修正**：`if (ui.visible) { ... }` 包裹计算；`debug_ui_text` 添加 `!ui->visible` 短路返回。

### R66-6 memset(g_node_vis) 精确清零

**修正**：`memset(g_node_vis, 0, nc)` 仅清零实际使用范围（典型 nc<<16384）。

**验收**：test_math 45/45、test_camera_frustum 24/24、engine_demo 编译通过。


## R67 审查加固：occ_map提前 + terrain stats门控 + com_drift一致性 + psc缓存

### R67-1 occ_rebuild_node_map 提前至 forward/deferred 分支前（Critical）

**问题**：R66 在延迟路径添加 `node_occ_visible` 检查，但 `occ_rebuild_node_map` 仅在 forward 分支内调用。延迟路径 `occ_idx_by_node` 全为 BSS 零值，若 object 0 被遮挡则全画面剔除。

**修正**：将调用从 forward 分支内提升至分支之前。

### R67-2 terrain stats 移入 ui.visible 门控

**问题**：R66 遗漏 L2352 的 terrain stats O(nn) 循环（4096迭代/10帧），仅供 debug UI。

**修正**：用 `if (ui.visible)` 包裹。

### R67-3 com_drift/prev_com 一致性修复

**问题**：UI隐藏时 prev_com 停止更新，恢复后 com_drift 累加永久偏移。

**修正**：CoM 计算和 drift 累加移出门控，仅显示留在门控内。

### R67-4 fps_history 持续采集

**修正**：fps_history 两行移至 `if(ui.visible)` 之前。

### R67-5 point_shadow_gather 帧级缓存

**问题**：每帧 9 次 point_shadow_gather 调用，帧内点光状态不变。

**修正**：`g_psc` 帧级缓存，gather 一次，bind_material/clustered/terrain 读缓存。9→1 次/帧。

**验收**：test_math 45/45、test_camera_frustum 24/24、engine_demo 编译通过。

---

## Round 68：CoM合并 + 死参数移除 + Deferred g_psc缓存

### R68-1 CoM双重遍历合并

**问题**：R67 将 com_drift/prev_com 更新移出 `if(ui.visible)` 门控后，门控内遗留旧 CoM 计算循环。UI 可见时同一组物理体被遍历两次——一次显示、一次累加。逻辑完全相同，维护风险高。

**修正**：CoM 计算提升至 `if(ui.visible)` 之前，声明 `frame_com`/`frame_com_mass`。门控内仅读 `frame_com` 显示，门控后仅用 `frame_com` 累加。消除冗余 O(n) 循环。

### R68-2 死参数移除

**问题**：R67 `g_psc` 帧级缓存后，`bind_material` 的 `pt_shadows` 参数和 `clustered_set_point_shadow_uniforms` 的 `pt` 参数变为死代码（仅 `(void)` 抑制警告），12+1 处调用点仍传递 `&pt_shadows`，API 契约漂移误导维护。

**修正**：移除两个函数的死参数，更新所有 12+1 调用点。同步移除 `mega_mat_groups_draw` 的 `pt_shadows` 参数及 2 处调用点。

### R68-3 Deferred g_psc缓存统一

**问题**：`deferred_lighting_pass` 仍内联执行 `point_shadow_gather`，与前向路径读 `g_psc` 帧级缓存不一致。每次延迟帧多做一次冗余 gather 遍历。

**修正**：`deferred_lighting_pass` 签名从 `const PointShadowSystem *pt_shadows` 改为 `(u32 psc_count, const RHITexture *psc_tex, const u32 *psc_light_idx)`。调用方传入 `g_psc` 缓存数据。`deferred.c` 移除 `point_shadow.h` 依赖。延迟路径与前向路径完全统一读帧级缓存。

**验收**：test_math 45/45、test_camera_frustum 24/24、engine_demo 编译通过。

---

## Round 69：栈数组补漏 + Deferred采样器修复 + terrain预计算 + 除法转乘法

### R69-1 light_system_cull 栈数组改 static

**问题**：`light_system_cull` 中 10 个局部数组共 ~16.5KB 在栈上分配，每帧调用。与R65-R66已修复的模式一致但遗漏。

**修正**：全部改为 `static`。函数每帧最多调用一次，无并发访问。

### R69-2 Deferred GL路径点阴影采样器修复

**问题**：R68 移除 `pt_shadows` 参数后，GL 后台的延迟路径中点阴影立方体贴图绑定采样器从 `pt_shadows->sampler`(LINEAR) 降级为 `sys->_gbuf_sampler`(NEAREST)，导致阴影边缘锯齿。这是R68引入的渲染回归。

**修正**：在 `DeferredSystem` 新增 `_linear_sampler`(LINEAR/CLAMP)。GL 路径点阴影绑定改用 `_linear_sampler`。

### R69-3 帧循环 pl_pos/pl_rad 栈数组改 static

**问题**：`pl_pos[256]`(3KB) + `pl_rad[256]`(1KB) 在帧循环栈上分配。

**修正**：改为 `static`。

### R69-4 point_shadow_update cand 栈数组改 static

**问题**：`PSCandidate cand[256]`(2KB) 在栈上分配，每帧调用。

**修正**：改为 `static`。

### R69-5 deferred.h 残留 include + psc_light_idx NULL 防护

**问题**：`deferred.h` 残留 `#include "point_shadow.h"`；`psc_light_idx` 指针参数无 NULL 防护。

**修正**：移除残留 include；添加 NULL 检查（传 NULL 时写 0xFFFFFFFF 哨兵值）。

### R69-6 terrain inv_scale/inv_nm1 预计算

**问题**：terrain 热路径中 `x / t->scale` 和 `(f32)(grid_size - 1)` 每次调用执行除法。`scale` 和 `grid_size` 初始化后不变。

**修正**：`Terrain` 结构体新增 `inv_scale` 和 `inv_nm1`，`terrain_init` 中预计算。所有热路径 `x/t->scale` → `x*t->inv_scale`，`(f32)(grid_size-1)` → `inv_nm1`。

### R69-7 light_system_cull 逐光源除法→乘法

**问题**：`screen_r[li] = pl->radius / (-view_pos[li].e[2])` 对每个光源执行除法（最多256次/帧）。

**修正**：改为 `inv_vz = 1.0f / (-view_pos[li].e[2])`，`screen_r = pl->radius * inv_vz * screen_w * 0.5f`。

**验收**：test_math 45/45、test_camera_frustum 24/24、engine_demo 编译通过。

---

## R70 动画子系统栈安全 + test_terrain 回归修复

### R70-1 test_terrain make_terrain 助手缺 inv_scale/inv_nm1 初始化

**问题**：R69-6 给 `Terrain` 结构体新增 `inv_scale`/`inv_nm1` 预计算字段，`terrain_init` 中赋值。但 `test_terrain.c` 的 `make_terrain` 助手通过 `calloc` 创建 Terrain 并手动设置字段，未同步添加两个新字段（calloc 零初始化为 0.0f），导致 5 个测试失败。

**修正**：在 `make_terrain` 中补上 `t->inv_scale = (scale > 0.0f) ? 1.0f / scale : 0.0f; t->inv_nm1 = (f32)(grid - 1);`。

**验收**：test_terrain **22/22**（从 17/22 恢复）。

### R70-2 anim_blend_evaluate 10KB 栈数组改 static

**问题**：`anim_blend_evaluate`（每帧调用）中 6 个局部数组 `sample_pos[128]`/`sample_rot[128]`/`sample_scl[128]` + crossfade 路径 `from_pos[128]`/`from_rot[128]`/`from_scl[128]` 共 ~10KB 栈分配。R65-R69 已修复 main.c/lighting.c/point_shadow.c 的同类问题，但动画子系统尚未触及。

**修正**：全部添加 `static` 关键字。

### R70-3 skeleton_evaluate 5KB 栈数组改 static

**问题**：`skeleton_evaluate`（每帧调用）中 `translations[128]`/`rotations[128]`/`scales[128]` 共 ~5KB 栈分配。

**修正**：全部添加 `static` 关键字。

### R70-4 main.c ik_world 8KB 栈数组改 static

**问题**：`main.c` 帧循环 L3914 `Mat4 ik_world[SKELETON_MAX_JOINTS]`（128×64=8192B）在 R65-R69 批量修复中被遗漏。

**修正**：添加 `static` 关键字。

### R70-5 point_shadow_update face_vp 改 static

**问题**：`point_shadow_update` 循环内 `Mat4 face_vp[POINT_SHADOW_FACES]`（6×64=384B）在 R69-4 修复同函数 `cand[256]` 时被遗漏。

**修正**：添加 `static` 关键字。

**验收**：test_terrain 22/22、test_math 45/45、test_camera_frustum 24/24、test_animation 20/20。

---

## R71 fallback路径栈安全补全

### R71-1 VisTaskCtx vctxs[8] 改 static

**问题**：`main.c` 前向渲染 fallback 路径（L4812）和延迟渲染 fallback 路径（L5045）中 `VisTaskCtx vctxs[8]`（每元素~168B，8元素共~1.3KB）为非静态栈数组，每帧分配。R65-R70 批量修复中遗漏了此结构体数组。

**修正**：两处均添加 `static` 关键字。安全性保证：前向与延迟路径互斥执行（由 `render.render_path` 决定）；`task_wait(tasks)` 确保 worker 线程完成后才可能重用；数组在使用前被完全初始化。

**验收**：test_terrain 22/22、test_math 45/45、test_camera_frustum 24/24、test_animation 20/20。

---

## R72 terrain_erode一致性 + 物理栈安全 + frustum_from_vp指针化

### R72-1 terrain_erode inv_scale/inv_nm1 转换

**问题**：R69-6 将 `terrain_get_height`/`modify_height`/`flatten`/`noise_stamp` 中的 `x / t->scale` → `x * t->inv_scale`、`(f32)(n-1)` → `t->inv_nm1`，但遗漏了 `terrain_erode`（L435-440 仍用旧模式）。

**修正**：`inv = 1.0f / t->inv_nm1`，`cgx/cgz = (wx * t->inv_scale + 0.5f) * t->inv_nm1`，`gr = radius * t->inv_scale * t->inv_nm1`。

### R72-2 char_slide_resolve candidates[64] 改 static

**问题**：`character.c` 的 `char_slide_resolve` 中 `u32 candidates[64]`（256B）在栈上分配，每帧最多调用 5 次（垂直/水平/step-up 解析）。R65-R71 处理了 main.c/lighting.c/animation.c 等但遗漏 character.c。

**修正**：添加 `static` 关键字。

### R72-3 ccd_sweep_static candidates[64] 改 static

**问题**：`physics.c` 的 `ccd_sweep_static` 中 `u32 candidates[64]`（256B）在栈上分配，每个动态刚体每帧调用一次。

**修正**：添加 `static` 关键字。

### R72-4 frustum_from_vp Mat4 按值改 const 指针

**问题**：`frustum_from_vp(Mat4 vp)` 按值接收 64 字节的 `Mat4` 结构体，每帧约 11 次调用（主视锥 1 + 级联阴影 4 + 点光源面 6），每次复制 64 字节。

**修正**：签名改为 `frustum_from_vp(const Mat4 *vp)`，实现中 `vp.e` → `vp->e`，更新全部 15 处调用点（main.c 3处 + test_camera_frustum.c 12处）。

**验收**：test_terrain 22/22、test_math 45/45、test_camera_frustum 24/24、test_animation 20/20、test_physics 34/34、test_character 20/20。

---

## R73 CSM冗余消除 + 视锥内联化 + 地形双重绘制修复 + mat4_mul内联化

### R73-1 CSM legacy gpucull_update_objects 提升到级联循环前

**问题**：Legacy CSM 路径中，`gpucull_update_objects` 的 O(N) 打包循环+GPU buffer upload 在 `for (c = 0; c < 4; c++)` 级联循环内执行，但对象数据（`mega_buf.node_spheres`）在 4 个级联间完全相同，导致每帧 4 次冗余打包+上传。

**修正**：将打包循环+`gpucull_update_objects` 提升到级联循环前，设置 `legacy_gpucull_packed` 标志。循环内 legacy 路径仅调用 `gpucull_dispatch_flags`（依赖每级联的 `cascade_vp[c]`）。

### R73-2 frustum_test_sphere/aabb/point 移至头文件 static inline

**问题**：`frustum_test_sphere`、`frustum_test_aabb`、`frustum_test_point` 定义在 cull.c（非 inline），编译器无法将其内联到 main.c 的逐节点裁剪循环（每帧数千次调用）。无 LTO 时产生函数调用开销。

**修正**：将三个函数移至 cull.h 作为 `static inline`，从 cull.c 删除旧定义。`frustum_from_vp` 保留在 .c 中（调用频率低，函数体较大）。

### R73-3 前向路径地形双重绘制修复

**问题**：前向渲染路径中，`terrain_render`（使用硬编码光照的 terrain pipeline）和 `clustered_pipeline`（使用 PBR 聚簇光照）在同一 FBO 上绘制同一地形几何体（`terrain.vbo`/`ibo`/`index_count`）。当 clustered pipeline 可用时，`terrain_render` 的整个 GPU draw（顶点处理+光栅化+片元着色）被 clustered 路径覆盖，完全浪费。

**修正**：当 `rhi_handle_valid(render.clustered_pipeline)` 时跳过 `terrain_render`，仅保留 clustered 路径的地形绘制（PBR 光照、IBL、点阴影）。

### R73-4 mat4_mul 改为 static inline

**问题**：`mat4_mul(Mat4 a, Mat4 b)` 定义在 math.c（非 inline），按值传递两个 64B 的 Mat4 参数（共 128B 栈拷贝）。在骨架动画热路径中每帧调用 100-300 次（`skeleton_evaluate` 2×/关节 + `skeleton_apply_local_trs` 2×/关节 + `skeleton_compute_world_transforms` 1×/关节）。项目未启用 LTO，编译器无法跨编译单元内联。

**修正**：将 `mat4_mul` 从 math.c 的函数定义改为 math.h 中的 `static inline` 定义（含 SSE 标量双路径），从 math.c 删除旧定义。所有调用点自动获得内联版本。

**验收**：test_terrain 22/22、test_math 45/45、test_camera_frustum 24/24、test_animation 20/20、test_physics 34/34、test_character 20/20。


## R74 gpucull SSE打包bug修复 + 地形双重绘制方向修正 + mat4_vec4指针化

### R74-1 gpucull_update_objects SSE 打包 bug 修复（CRITICAL）

**问题**：`gpucull_update_objects` 中的 SSE 打包代码使用 `_mm_movelh_ps(pos, _mm_shuffle_ps(pos, rad, _MM_SHUFFLE(0, 0, 2, 2)))` 将位置 `(x, y, z, next_x)` 和半径 `(r, 0, 0, 0)` 打包为 `(x, y, z, z)`——第 4 个元素（半径 `r`）被错误替换为 z 坐标。这导致 GPU 剔除着色器使用 z 坐标作为包围球半径：z < 实际半径的物体被错误剔除（阴影缺失），z > 实际半径的物体过度通过（浪费 GPU 绘制）。

R73-1 将此调用从级联循环内提升到循环前后，该 bug 进一步影响 unified 路径（覆盖了 `gpucull_upload_objects_unified` 写入的正确数据）。

**修正**：将 SSE 打包替换为标量循环。原 SSE 代码每迭代处理一个元素（非两个），标量循环性能等同且正确。

### R74-2 R73-3 地形双重绘制方向修正（视觉回归修复）

**问题**：R73-3 假设 `terrain_render`（硬编码光照）是冗余绘制，当 clustered pipeline 可用时跳过它。但深度分析表明方向相反：

1. `terrain_render` 先绘制，通过 LESS 深度测试并写入深度 D
2. clustered 地形绘制后绘制，相同几何体产生相同深度 D，LESS 测试失败（D 不小于 D）→ 被深度剔除，零像素输出
3. 因此 `terrain_render` 是可见绘制，clustered 地形才是被浪费的那次

R73-3 跳过 `terrain_render` 导致：海岸泡沫（`terrain.frag` 依赖 `u_water_y`）、水下焦散（依赖 `u_water_y` + `u_time`）、水下变暗效果全部丢失。聚簇路径从未设置 `water_y`/`time` uniform。

**修正**：恢复 `terrain_render` 无条件调用，改为跳过 clustered 中的冗余地形绘制（被深度剔除，纯浪费 GPU draw call）。

### R74-3 mat4_vec4 改为 const Mat4* 参数

**问题**：`mat4_vec4(Mat4 m, Vec4 v)` 按值传递 Mat4（64B/次拷贝），是代码库中最后一个在逐帧热循环中按值传递 Mat4 的函数。在 `light_system_cull` 的逐光源预变换循环中被调用 2 次/光源，最多 256 个点光源 = 512 次按值拷贝/帧。此外 `light_system_cull` 中 `Mat4 v = *view; Mat4 p = *proj;` 产生 128B 不必要本地拷贝。

**修正**：将 `mat4_vec4` 签名改为 `const Mat4 *m`，删除本地拷贝，直接传递 `view`/`proj` 指针。与 `mat4_mul`（R73-4）、`frustum_from_vp`（R72）的指针化模式一致。

**验收**：全部 23/23 测试通过。


## R75 聚簇块裁剪跳过 + mega_mat_groups逆索引O(N×G)→O(N)

### R75-1 聚簇块裁剪/上传/绑定整体跳过

**问题**：R74-2 跳过聚簇地形绘制后，聚簇块仍执行全部设置工作：
- `light_system_cull`（CPU路径）：O(CLUSTER_COUNT × 点光数) = O(3072 × 32) ≈ 98,304 次迭代/帧
- 或 `light_system_cull_gpu`（GPU路径）：compute dispatch + memory barrier
- `light_system_upload`/`upload_lights`：2次buffer update
- `rhi_cmd_bind_pipeline` + ~10次 `rhi_cmd_set_uniform_*` + 纹理/texel buffer绑定

经追踪确认，`lights.light_data_buf`/`light_grid_buf` **仅在聚簇块内部**被引用——粒子、蒙皮管线、主管线均不使用聚簇光照缓冲。`lights` 的下一次引用在延迟路径（与前向互斥）。

但光源填充（`light_system_clear` + `add_dir` + 32×`add_point`）**必须保留**——pt_shadows 在聚簇块之前读取 `lights.point_count`/`lights.point_lights`（读取上一帧填充的数据）。

**修正**：在光源填充后直接跳过 cull/upload/bind 部分。删除未使用的 `clustered_set_point_shadow_uniforms` 函数（-Werror=unused-function）。

### R75-2 mega_mat_groups 预构建逆索引 O(N×G)→O(N)

**问题**：`mega_mat_groups_draw`/`mega_mat_groups_indirect` 及两处 legacy 路径执行 O(N×G) 线性扫描——对每个材质组 g（G次迭代），遍历所有 draw command（N次迭代）查找属于该组的命令。该扫描在阴影通道中每帧被调用 12-17 次（CSM 4级联 + 点光阴影 6面/光 + 前向/延迟 1-2次）。以 N=16384、G=8 计，每帧约 160-220 万次迭代。构建阶段也有 O(N×G) 双重扫描（计数+收集）。

**修正**：在 `MegaBuffer` 中添加 `group_cmd_offsets[MEGA_MAX_MAT_GROUPS+1]`（前缀和）和 `group_cmd_list[16384]`（按组排序的cmd索引）。构建时单遍计数+前缀和+填充，总复杂度 O(N)。替换全部 4 处扫描循环 + 构建处双重扫描为逆索引查找。每帧迭代次数减少约 8 倍。

**验收**：全部 23/23 测试通过。


## R76 逆索引越界修复 + glViewport缓存统一 + barrier批处理 + skeleton_upload条件化

### R76-1 修复 >64 材质时逆索引构建栈越界写（CRITICAL）

**问题**：R75-2 逆索引构建中，当场景材质数超过 `MEGA_MAX_MAT_GROUPS`(64) 时，溢出的 draw command 的 `cmd_mat_group[ci]` 值为 64，直接用作 `group_counts[64]` 下标——而 `group_counts` 数组仅 64 元素（0-63），导致栈缓冲越界写。同样，填充阶段 `fill_pos[64]` 也越界。在正常场景（<64 材质）下不会触发，但在大型场景中会导致内存损坏。

**修正**：在计数循环和填充循环中添加边界检查：
- 计数：`if (g < mega_buf.mat_group_count) group_counts[g]++;`
- 填充：`if (g >= mega_buf.mat_group_count) continue;`

### R76-2 glViewport 缓存提升为文件作用域

**问题**：`glViewport` 缓存 `g_gl_vp` 原为 `gl_cmd_set_viewport` 函数内的静态局部变量。但 9 个 FBO/shadow 绑定函数（`rhi_cmd_set_shadow_viewport`、`rhi_cmd_bind_shadow_map`、`rhi_cmd_unbind_shadow_map`、`rhi_offscreen_fbo_bind/unbind`、`rhi_mrt_fbo_bind/unbind`、`rhi_cubemap_depth_fbo_bind_face/unbind`、`gl_init`、`gl_resize`）绕过 `gl_cmd_set_viewport` 直接调用 `glViewport`，导致：
1. 每帧 ~25 次冗余 `glViewport` 驱动调用（即使 viewport 未变）
2. 缓存不同步——FBO 绑定后 viewport 改变但 `g_gl_vp` 未更新，后续 `gl_cmd_set_viewport` 误判为命中缓存而跳过实际 `glViewport` 调用

**修正**：
- 将 `g_gl_vp` 提升为文件作用域变量
- 新增 `gl_set_viewport_cached(x, y, w, h)` 辅助函数封装缓存逻辑
- `gl_cmd_set_viewport` 改为调用 `gl_set_viewport_cached`
- 全部 9 处直接 `glViewport` 调用替换为 `gl_set_viewport_cached`

### R76-3 indirect_draw_compact barrier 批处理

**问题**：`indirect_draw_compact` 在每个材质组结束时发出 `rhi_cmd_memory_barrier`。一个渲染 pass 内有 G 个材质组，就产生 G 次 barrier。barrier 强制 GPU 等待之前的 compute shader 完成，打断命令流并行执行。以 G=8 计，每个 pass 8 次 barrier，每帧 12-17 个 pass → 96-136 次 barrier/帧。

**修正**：
- 新增 `indirect_draw_compact_no_barrier` 函数——与 `indirect_draw_compact` 相同但无 trailing barrier
- `indirect_draw_compact` 重构为调用 `indirect_draw_compact_no_barrier` + `rhi_cmd_memory_barrier`
- 全部 4 处多组循环（`mega_mat_groups_indirect`、`mega_mat_groups_draw`、legacy forward、legacy deferred）改为两阶段模式：
  1. 阶段一：循环所有组执行 upload_visibility + compact_no_barrier
  2. 单个 `rhi_cmd_memory_barrier`
  3. 阶段二：循环所有组执行 bind_material + execute
- 将 G 次 barrier/pass 降为 1 次

### R76-4 skeleton_upload 移入条件检查内

**问题**：`skeleton_upload`（上传骨骼矩阵到 GPU buffer）+ skinned pipeline bind + 7 个 uniform set 在 `skinned_mesh_count > 0` 检查之前无条件执行。当场景无蒙皮网格且无 fallback skinned VBO 时，这些操作全部浪费。

**修正**：将 `skeleton_upload` + pipeline bind + uniform sets 包裹在 `if (scene.skinned_mesh_count > 0 || rhi_handle_valid(render.skinned_vbo))` 条件内。两个分支（skinned meshes / fallback VBO）都在条件内部，无蒙皮渲染时全部跳过。

**验收**：全部 23/23 测试通过。


## R77 纹理缓存提升修复正确性bug + 间接绘制buffer缓存 + occlusion_cull指针化

### R77-1 纹理单元缓存提升为文件作用域（正确性修复 + 性能提升）

**问题（CRITICAL 正确性）**：`g_tex_cache[16]`/`g_sam_cache[16]`/`g_active_unit` 原为 `gl_bind_tex_unit` 函数内的静态局部变量。两个函数绕过缓存直接调 GL：
- `rhi_cmd_bind_texel_buffers`：直接 `glActiveTexture(GL_TEXTURE5/6)` + `glBindTexture(GL_TEXTURE_BUFFER, ...)`，不更新 `g_active_unit`/`g_tex_cache[5/6]`
- `rhi_cmd_bind_texture_mip`：直接 `glActiveTexture(GL_TEXTURE0+unit)` + `glBindTexture(GL_TEXTURE_2D, ...)`，不更新缓存

后果：后续 `gl_bind_tex_unit` 检查 `td->gl_tex == g_tex_cache[unit] && g_active_unit == unit` 时，缓存命中但实际绑定已被覆盖 → 跳过 `glActiveTexture` 和 `glBindTexture`，纹理绑定到错误的纹理单元。

**性能影响**：`rhi_cmd_bind_texel_buffers` 在蒙皮网格循环中每帧调用 N 次，每次 4 次冗余 GL 调用。`rhi_cmd_bind_texture_mip` 在 Hi-Z mip 生成中每帧调用 ~10 次，每次 5 次冗余 GL 调用 + 2 次冗余 `glTexParameteri`。

**修正**：
- 将 `g_tex_cache`/`g_sam_cache`/`g_active_unit` 提升为文件作用域变量
- `rhi_cmd_bind_texel_buffers`：改为通过缓存检查绑定，更新 `g_active_unit`/`g_tex_cache[5/6]`
- `rhi_cmd_bind_texture_mip`：改为调用 `gl_bind_tex_unit`（已处理缓存），额外缓存 `mip_tex`/`mip_level` 避免重复 `glTexParameteri`

### R77-2 间接绘制 buffer 缓存 + 移除冗余解绑

**问题**：`rhi_cmd_draw_indexed_indirect` 和 `rhi_cmd_draw_indexed_indirect_count`（ARB 路径 + fallback 路径）每次调用后无条件 `glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0)` / `glBindBuffer(0x80EE, 0)`。在多材质组循环中（`mega_mat_groups_draw`/`mega_mat_groups_indirect`），产生 bind→draw→unbind→bind→draw→unbind 周期。每次 unbind 是一次冗余 GL 调用，且可能触发驱动 flush。

**修正**：
- 添加 `g_gl_indirect_buf`/`g_gl_param_buf` 文件作用域缓存
- 绑定时检查缓存跳过重复 `glBindBuffer`
- 移除所有尾部 `glBindBuffer(..., 0)` 解绑调用

### R77-3 occlusion_cull_dispatch Mat4 按值传→指针

**问题**：`occlusion_cull_dispatch` 按值传 `Mat4`（64B/次），与 R74-3 `mat4_vec4` 模式不一致。每帧调用 1 次，影响低但修复简单。

**修正**：签名改为 `const Mat4 *view_proj`，调用点改为 `&curr_view_proj`。

**验收**：全部 23/23 测试通过。


## R78 cubemap缓存修复R77回归 + skybox深度缓存 + 点阴影FBO解绑批处理

### R78-1 rhi_cmd_bind_cubemap 缓存修复（CRITICAL 回归 + 性能）

**问题（CRITICAL 回归）**：R77-1 将 `g_tex_cache`/`g_sam_cache`/`g_active_unit` 提升为文件作用域，并让 `rhi_cmd_bind_texel_buffers` 信任 `g_active_unit` 判断是否需要 `glActiveTexture`。但 `rhi_cmd_bind_cubemap` **仍直接调用** `glActiveTexture`+`glBindTexture`+`glBindSampler`，不更新缓存三变量——这是 R77-1 修复的同类 bug，但遗漏了此函数。

**回归机制**：`bind_material` → `rhi_cmd_bind_material_textures_ibl` → `rhi_cmd_bind_cubemap`(unit 8/9) 不更新 `g_active_unit`。之后 `rhi_cmd_bind_texel_buffers` 检查 `g_active_unit != 5`，若 cubemap 使 `g_active_unit` 恰好残留为 5，则跳过 `glActiveTexture(GL_TEXTURE5)`，TBO 绑定到错误单元（unit 9）→ 蒙皮网格/延迟光照渲染错乱。

**性能影响**：IBL cubemap 在所有材质组中完全相同（`rs->ibl.irradiance_map`/`rs->ibl.prefilter_map`），以 64 材质组计每帧 ~380 次冗余 GL 调用（64×2×3）。

**修正**：`rhi_cmd_bind_cubemap` 改为调用 `gl_bind_tex_unit`（已正确处理 `RHI_RES_CUBEMAP` 类型，使用 `GL_TEXTURE_CUBE_MAP` target，并更新缓存三变量）。

### R78-2 skybox_render 深度函数缓存失配修复

**问题**：`skybox_render` 直接调 `glDepthFunc(GL_LEQUAL)` / `glDepthFunc(GL_LESS)` 不更新 `g_gl_depth_func` 缓存。若 skybox 前深度函数为 `GL_LEQUAL`（`g_gl_depth_func = GL_LEQUAL`），skybox 恢复为 LESS 但缓存仍为 LEQUAL → 后续 `rhi_cmd_set_depth_func_less_or_equal` 误判缓存命中跳过 `glDepthFunc`，深度测试函数错误。

**修正**：替换为 `rhi_cmd_set_depth_func_less_or_equal(cmd)` / `rhi_cmd_set_depth_func_less(cmd)`，与缓存路径一致。

### R78-3 点光源阴影逐面 FBO 解绑消除

**问题**：点光源阴影渲染循环中，每个 cubemap 面后调用 `point_shadow_render_end` → `rhi_cubemap_depth_fbo_unbind`（绑定 FBO 0 + 设置屏幕 viewport），下一面立即重新绑定 cubemap FBO。以 4 活跃点光源×6 面计：每帧 48 次冗余 `glBindFramebuffer` + 48 次冗余 `glViewport` = ~96 次冗余 GL 调用。与 R77-2 移除 indirect buffer 尾部解绑的模式一致。

**修正**：移除内循环中的 `point_shadow_render_end`，改为所有面完成后统一调用一次。

**验收**：全部 23/23 测试通过。


## R79 FBO绑定缓存 + 纹理上传缓存失配修复 + buffer尾部解绑消除 + scissor状态缓存

### R79-1 FBO 绑定缓存（HIGH 性能）

**问题**：所有 FBO 绑定函数（`rhi_cmd_bind_shadow_map`、`rhi_offscreen_fbo_bind/unbind`、`rhi_mrt_fbo_bind/unbind`、`rhi_cubemap_depth_fbo_bind_face/unbind`）每次无条件调 `glBindFramebuffer(GL_FRAMEBUFFER, ...)`，无缓存。点阴影渲染中同一 FBO 每光源绑定 6 次（每 cubemap 面一次），以 4 活跃光源计 ~20 次冗余绑定/帧。`glBindFramebuffer` 触发驱动端 FBO 完整性校验，是较昂贵的状态切换。

**修正**：新增 `g_gl_bound_fbo` 文件作用域缓存 + `gl_bind_fbo_cached()` 辅助函数（与 `g_gl_vp`/`g_gl_indirect_buf` 同模式），替换全部 15 处 `glBindFramebuffer` 调用。

### R79-2 rhi_texture_upload_mip 缓存失配修复（正确性）

**问题**：`rhi_texture_upload_mip` 直接调 `glBindTexture(GL_TEXTURE_2D, td->gl_tex)` 上传 mip 数据，但不更新 `g_tex_cache[g_active_unit]`。上传后 `glBindTexture(GL_TEXTURE_2D, 0)` 解绑，但 `g_tex_cache` 仍持有旧纹理 ID。后续 `gl_bind_tex_unit` 在同一单元上若恰好匹配旧 ID 则误判缓存命中跳过 `glBindTexture`，采样到错误纹理（无纹理）。与 R77-1/R78-1 同类缓存失配 bug。

**修正**：上传+解绑后失效缓存 `if (g_active_unit < 16) g_tex_cache[g_active_unit] = 0;`，确保下次 `gl_bind_tex_unit` 必然重绑。

### R79-3 rhi_buffer_map/unmap 尾部解绑消除

**问题**：`rhi_buffer_map` 和 `rhi_buffer_unmap` 末尾各调 `glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0)` 解绑，无意义——下次 `glBindBuffer`/`glBindBufferBase` 会覆盖泛型绑定点。与 R77-2 移除 indirect buffer 尾部解绑同模式。

**修正**：移除两处尾部解绑。

### R79-4 GL_SCISSOR_TEST 状态缓存

**问题**：`rhi_cmd_set_shadow_viewport` 每级联调 `glEnable(GL_SCISSOR_TEST)`，`rhi_cmd_bind_shadow_map`/`rhi_cmd_unbind_shadow_map` 各调 `glDisable(GL_SCISSOR_TEST)`。4 级联 + 2 解绑 = 6 次/帧，其中仅 1 次 enable + 1 次 disable 是实际状态切换。

**修正**：新增 `g_gl_scissor_enabled` 布尔缓存，仅在状态实际变化时调 `glEnable`/`glDisable`。

**验收**：全部 23/23 测试通过。


## R80 VAO缓存提升文件作用域 + skybox深度遮罩/裁剪面缓存化

### R80-1 VAO 缓存提升为文件作用域（防御性修复）

**问题**：`g_gl_vao` 为 `gl_cmd_bind_pipeline` 的函数局部 static 变量，`rhi_pipeline_create` 中两处 `glBindVertexArray` 调用（创建时绑定 VAO 配置属性，配置后解绑回 0）不更新缓存。潜在 desync：若管线创建发生在渲染期间（如热重载），创建结束时 `glBindVertexArray(0)` 将实际 GL 状态置为 0，但 `g_gl_vao` 仍认为旧 VAO 已绑定 → 后续 `gl_cmd_bind_pipeline` 若绑定同一 VAO → 缓存命中 → 跳过 `glBindVertexArray` → 渲染错误。当前未触发（所有管线在初始化阶段创建，此时 `g_gl_vao` 为初始值 0，与创建后状态一致）。

**修正**：将 `g_gl_vao` 提升为文件作用域（与 `g_gl_bound_fbo`/`g_gl_scissor_enabled` 同模式），`rhi_pipeline_create` 中两处 `glBindVertexArray` 后更新缓存。

### R80-2 skybox glDepthMask/glCullFace 缓存化

**问题**：`skybox_render` 直接调 `glDepthMask(GL_FALSE/GL_TRUE)` 和 `glDisable/glEnable(GL_CULL_FACE)` 绕过缓存——与 R78-2 `glDepthFunc` 同类问题。若后续有其他代码路径设置深度遮罩或裁剪面，将出现缓存失配。

**修正**：新增 `g_gl_depth_mask`/`g_gl_cull_enabled` 文件作用域缓存 + `rhi_cmd_set_depth_mask`/`rhi_cmd_set_cull_face` RHI 函数。GL 后端缓存化，VK 后端 no-op（由管线状态处理）。skybox.c 移除所有直接 GL 调用和 `#ifndef ENGINE_VULKAN` 守卫，统一走 RHI 路径。

**验收**：全部 23/23 测试通过。


## R81 VK深度函数no-op修复 + skybox死代码清理 + draw_bench参数门控 + 点阴影冗余uniform移除

### R81-1 VK rhi_cmd_set_depth_func_* 改为 no-op（CRITICAL 正确性）

**问题（CRITICAL）**：R80 移除 skybox.c 的 `#ifndef ENGINE_VULKAN` 守卫后，`rhi_cmd_set_depth_func_less_or_equal`/`_less` 在 VK 后端也被调用。但其 VK 实现调 `vkCmdSetDepthCompareOp`，而 VK 管线未启用 `VK_DYNAMIC_STATE_DEPTH_COMPARE_OP` 动态状态（仅启用 VIEWPORT 和 SCISSOR），深度比较由管线静态设置（`depth.depthCompareOp`）。这是 Vulkan 验证错误/未定义行为。skybox.c 是这两个函数的唯一调用者。

**修正**：VK 后端改为 no-op（与 `rhi_cmd_set_depth_mask`/`rhi_cmd_set_cull_face` 一致）。skybox 管线描述符已设 `depth_compare_lequal=true`，VK 管线创建时映射为 `VK_COMPARE_OP_LESS_OR_EQUAL`。

### R81-2 skybox.c 移除死代码 #include <glad.h>

**问题**：R80-2 将所有直接 GL 调用替换为 RHI 函数后，`#include <glad.h>` 成为死代码。

**修正**：移除 `#ifndef ENGINE_VULKAN / #include <glad.h> / #endif`。

### R81-3 draw_bench_add 参数门控

**问题**：`draw_bench_add(mega_calls, legacy_est)` 的 `legacy_est` 参数在 C 中先于函数调用求值。即使 `draw_bench_enabled=false`（默认），`mega_count_visible_draws`/`mega_count_visible_node_vis` 的 O(N) 遍历仍执行。8 处调用点，最坏情况点阴影 pass 中 24 次 O(N) 遍历/帧。

**修正**：8 处调用点添加 `draw_bench_enabled ?` 三元门控，禁用时传 `0u`。

### R81-4 点阴影冗余 u_model uniform 移除

**问题**：点阴影地形绘制中 `u_model=identity` 冗余——`point_shadow_render_begin` 已设为 identity，地形是该函数后的第一个绘制，中间无其他 uniform 变更。4 光源×6 面 = 24 次/帧冗余 `glUniformMatrix4fv`。

**修正**：移除冗余 uniform 设置。

**验收**：全部 23/23 测试通过。


## R82 静态数据生命周期优化：遮挡剔除AABB缓存 + 遗留gpucull跳过 + 点阴影per-face uniform提升 + occ节点映射移至init

### R82-1 统一剔除激活时跳过遗留 gpucull 打包

**问题**：阴影级联渲染中，`legacy_gpucull_packed` 路径每帧执行 O(N) 打包循环（从 `node_spheres` 提取 position/radius）+ `gpucull_update_objects` GPU 上传。但当 `unified_cull_enabled=true`（默认，由 `mega_upload_unified_cull` 在 init 时设置）时，对象数据已通过 `gpucull_upload_objects_unified` 上传到统一 SSBO，级联循环使用统一路径（`mega_unified_cull_shadow`/`mega_unified_cull_draw`），遗留打包输出从不被消费。

**修正**：在遗留打包条件中添加 `!unified_cull_enabled`，跳过完全浪费的 O(N) 循环 + GPU buffer 上传。

### R82-2 遮挡剔除 AABB 移至 init 缓存

**问题**：遮挡剔除每帧对所有场景节点执行 8 角点世界空间 AABB 变换（最多 16384×8=131072 次 mat-vec 乘法），然后通过 `occlusion_cull_upload_aabbs` → `glBufferSubData` 上传最多 393KB 到 GPU。但场景节点的 `world_transform` 是静态的——`local_transform` 仅在加载时设置，运行时无任何修改（已验证：全代码库无 `local_transform` 的运行时赋值）。此路径默认启用（`occ_cull_enabled=true`）。

**修正**：在 init 阶段（紧接 sphere cache 构建之后）预计算世界空间 AABB 并缓存到 `g_occ_aabbs[]` + `g_occ_aabbs_count`。每帧仅需上传 + dispatch（Hi-Z 每帧变化，但 AABB 不变）。

### R82-3 点阴影 per-face uniform 提升

**问题**：`point_shadow_render_begin` 在每个面的调用中都设置 `u_light_pos` 和 `u_far_plane`，但这两个值仅依赖 `light_index` 不依赖 `face`。每个光设置 6 次（每面 1 次）而非 1 次。`POINT_SHADOW_MAX_LIGHTS=8`，每帧最多 8 光×5 冗余面×2 uniform = 80 次冗余 GL uniform 调用。

**修正**：在 `point_shadow_render_begin` 中用 `face == 0u` 门控逐光 uniform。同一 `depth_pipeline` 绑定于所有面，OpenGL 中 uniform 属于 program 状态跨 FBO 切换保持不变，VK 中 push constant 属于 command buffer 状态跨 framebuffer bind 不重置。

### R82-4 occ_rebuild_node_map 移至 init

**问题**：`occ_rebuild_node_map` 每帧重建 `occ_idx_by_node` 映射，遍历所有节点两次（清除 + 构建）。但判定条件（`has_mesh`/`skinned`/`mesh_index`）在运行时不变——场景节点结构初始化后无修改。

**修正**：在 init 阶段调用一次 `occ_rebuild_node_map`（与 R82-2 AABB 缓存合并），删除每帧调用。

**验收**：全部 23/23 测试通过。


## R83 着色器效率优化：聚类Z切片log2替换 + 体积雾循环不变量提升 + DOF const数组 + AABB上传移至init

### R83-1 聚类 Z 切片 pow() 线性扫描替换为 log2（HIGH GPU）

**问题**：6 个着色器（`deferred_light.frag`、`pbr_clustered.frag`、`pbr_clustered_vk.frag`、`deferred_light_vk.frag`、`blinn_phong_clustered.frag`、`blinn_phong_clustered_vk.frag`）中查找聚类 Z 切片使用 24 次迭代线性扫描，每片段调用 24 次 `pow()`。`pow()` 在 GPU 上展开为 `exp2(y * log2(x))`，每次约 10-20 ALU 周期。1080p 延迟光照 pass 中，每帧约 48M 次超越函数调用。

**修正**：数学等价替换为 O(1) `log2`：`ld >= near * (far/near)^(z/24)` ⟺ `z <= 24 * log2(ld/near) / log2(far/near)`。`max(ld/near, 1.0)` 处理 `ld < near` 的情况（原代码此时 cz=0）。

### R83-2 体积雾循环不变量提升（MEDIUM GPU）

**问题**：`volumetric.frag` 和 `volumetric_vk.frag` 中 `texture(u_vol_shadow, vUV).r` 在 16 次迭代循环内执行，但 `vUV` 是片段输入 varying，循环中不变。每次采样返回相同值，造成 15 次冗余纹理采样。`light_visibility` 和 `lighting` 也都是循环不变量。VK 变体额外存在死代码 `vec4 world_pos = inverse(u_vol_view) * vec4(pos, 1.0)`（`world_pos` 未使用）。

**修正**：将 `shadow`、`light_visibility`、`lighting` 提升到循环之前。VK 变体移除死代码 `inverse(u_vol_view)`。

### R83-3 DOF hex_disk const 数组（MEDIUM GPU）

**问题**：`dof.frag` 和 `dof_vk.frag` 中 `hex_disk` 数组的值仅依赖编译期常量 `RINGS=3` 和 `SAMPLES_PER_RING=6`，但每个片段都重新计算 18 次 `cos`/`sin`/`normalize`/`dot`。数组声明为非 `const` 全局变量并在 `main()` 中逐元素赋值，GLSL 编译器不会常量折叠。

**修正**：将 `hex_disk` 改为 `const` 数组，用预计算的字面量初始化（19 个采样偏移）。删除 `main()` 中的循环填充代码。

### R83-4 遮挡剔除 AABB 上传移至 init（LOW CPU）

**问题**：R82-2 将 AABB 计算移至 init 缓存，但每帧仍通过 `occlusion_cull_upload_aabbs` → `glBufferSubData` 上传相同的静态数据到 GPU（最多 393KB）。AABB buffer 在 `occlusion_cull_init` 时创建，`occlusion_cull_resize` 仅重建 Hi-Z 纹理不影响 AABB buffer。

**修正**：在 init 的 AABB 计算后立即调用 `occlusion_cull_upload_aabbs` 一次性上传。每帧仅保留 `occlusion_cull_dispatch`（Hi-Z 每帧变化，dispatch 必须每帧运行）。`sys->object_count` 由 dispatch 每帧设置，upload 的设置冗余。

**验收**：全部 23/23 测试通过。



## R84 着色器效率优化(第二轮)：POM uniform门控 + SSGI循环不变量提升 + shadow_test提升 + F_Schlick pow→mul

### R84-1 POM uniform 门控（HIGH GPU）

**问题**：`pbr_clustered.frag` 和 `pbr_clustered_vk.frag` 中 `parallax_occlusion_mapping` 每片段无条件执行，即使材质没有高度图。POM 函数执行 16 次循环纹理采样 + 2 次插值采样 = 18 次纹理采样。当材质无 normal_map 时，fallback normal map 的 `.b=1.0` 导致循环始终跑满 16 次（`current_depth >= 1.0` 永远不满足 `h=1.0` 的情况直到最后一次）。

**修正**：添加 `u_pom_enabled` uniform（GL: 独立 uniform 声明；VK: push constant offset 228，总块大小 232 字节 < 256 限制）。在 `main.c` 的 `bind_material` 中根据 `mat->normal_map` 是否有效设置 0/1。着色器中 `vec2 pom_uv = u_pom_enabled > 0.5 ? parallax_occlusion_mapping(V, N, vUV) : vUV;`。`rhi_vk.c` 添加 offset 228 映射。无高度图的材质每片段节省 18 次纹理采样 + TBN 构建 + 转置矩阵乘法。

### R84-2 SSGI tangent/bitangent 循环不变量提升（MEDIUM GPU）

**问题**：`ssgi.frag` 和 `ssgi_vk.frag` 中 `tangent_to_world` 函数在 16 次迭代循环内调用，但 `up`/`tangent`/`bitangent` 仅依赖 `normal`（循环不变量）。每次迭代冗余执行 `abs`、`cross`、`normalize` 各一次。此外，`tangent_to_world` 中的 `normalize()` 是冗余的——`tangent` 和 `bitangent` 正交且单位长度，`tangent*cos + bitangent*sin` 的长度已为 1。

**修正**：将 `up`/`tangent`/`bitangent` 计算提升到循环前。循环内直接使用 `(tangent * cos(angle) + bitangent * sin(angle)).xy`，省去冗余的 `normalize()` 和函数调用开销。删除 `tangent_to_world` 函数。

### R84-3 shadow_test 提升到方向光循环外（MEDIUM GPU）

**问题**：`pbr_clustered.frag`、`pbr_clustered_vk.frag`、`deferred_light.frag`、`deferred_light_vk.frag` 中 `shadow_test(vWorldPos/wpos)` 在 `for (uint di = 0u; di < u_dir_count; di++)` 循环内调用，但 `shadow_test` 不依赖循环变量 `di`。`shadow_test` 内部执行 4 次级联矩阵乘法 + blocker 搜索（25 次纹理采样）+ PCF 过滤（最多 121 次纹理采样），是着色器中最重的操作之一。

**修正**：将 `shadow_test` 调用提升到循环前，结果存入 `dir_shadow`，循环内直接使用。当 `u_dir_count > 1` 时节省 (N-1) 次完整的 shadow_test 调用。

### R84-4 F_Schlick pow(x,5) 替换为乘法链（LOW GPU）

**问题**：`F_Schlick`/`fresnel_schlick` 函数中 `pow(1.0 - cosTheta, 5.0)` 在 GPU 上展开为 `exp2(5.0 * log2(x))`，涉及 1 次 `log2` + 1 次 `fma` + 1 次 `exp2`。虽然现代 GPU 的超越函数单元较快，但 `pow(x, 5.0)` 可以用 4 次乘法精确计算：`x*x*x*x*x`，无需超越函数。

**修正**：在 6 个着色器（`pbr_clustered.frag`、`pbr_clustered_vk.frag`、`deferred_light.frag`、`deferred_light_vk.frag`、`ssr.frag`、`ssr_vk.frag`）中将 `pow(x, 5.0)` 替换为 `float t = x; t*t*t*t*t`。F_Schlick 在每个方向光、点光、IBL 环境光计算中都被调用，替换后减少每次调用的 ALU 延迟。

**验收**：全部 23/23 测试通过。
## R85 着色器效率优化(第三轮)：blinn_phong albedo缓存 + skybox循环不变量 + pow→mul批量替换 + F_Schlick去重

### R85-1 blinn_phong_clustered 循环内冗余 albedo 纹理采样（HIGH GPU）

**问题**：`blinn_phong_clustered.frag` 和 `blinn_phong_clustered_vk.frag` 中 `texture(u_albedo, vUV)` 在方向光循环和点光源循环内每次迭代重新采样同一纹素。N 个方向光 + M 个点光源导致 `1 + N + M` 次纹理查找而非 1 次。同时 `pow(max(dot(N,H),0.0), 32.0)` 可用 5 次平方替代。

**修正**：在 main() 开头将 albedo 采样缓存到局部变量 `albedo`，所有循环内直接复用。`pow(x, 32.0)` 替换为 `float NdH = max(dot(N,H),0.0); float spec = NdH * NdH; spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;`（5 次平方 = 2^5 = 32）。影响 blinn_phong_clustered.frag/vk 2 个着色器。

### R85-2 skybox 云层循环冗余 normalize + 循环不变量 cos_light（HIGH GPU）

**问题**：`skybox.frag` 和 `skybox_vk.frag` 中云层 24 次迭代循环内 `float cos_light = max(dot(normalize(pos), sun), 0.0)`。由于 `pos = ray * t` 且 `ray` 已归一化，`normalize(pos) = ray`，因此 `cos_light = max(dot(ray, sun), 0.0) = max(cos_sun, 0.0)` 是循环不变量（`cos_sun` 在 L71/L76 已计算）。每次迭代浪费 1 次 normalize（~4 ALU）+ 1 次 dot + 1 次 max。同时 `pow(horizon_fog, 3.0)` 和 `pow(x, 1.5)` 可用乘法/sqrt 替代。

**修正**：将 `cos_light = max(cos_sun, 0.0)` 提升到循环前。循环内删除 `normalize(pos)` 和 `cos_light` 计算。`pow(x, 3.0)` → `x*x*x`，`pow(x, 1.5)` → `x*sqrt(x)`。影响 skybox.frag/vk 2 个着色器。

### R85-3 pow() 批量替换为乘法（MEDIUM GPU）

**问题**：R84-4 仅替换了 F_Schlick 中的 `pow(x, 5.0)`，但大量其他 `pow()` 调用仍使用超越函数。

**修正**：跨 18 个着色器批量替换所有整数/半整数指数 `pow()` 调用：
- `pow(x, 32.0)` → 5 次平方链（`spec *= spec` × 5）：blinn_phong.frag/vk、blinn_phong_clustered.frag/vk、skinned.frag/vk、instanced.frag/vk、water.frag/vk、terrain.frag/vk（12 着色器）
- `pow(x, 3.0)` → 3 次乘法：skybox.frag/vk、pbr_clustered.frag/vk、sky_to_cube.comp、water.frag/vk、terrain.frag/vk
- `pow(x, 1.5)` → `x * sqrt(x)`：skybox.frag/vk、pbr_clustered.frag/vk、sky_to_cube.comp
- `pow(x, 5.0)` → 5 次乘法：brdf_lut.comp（在 1024 次蒙特卡洛积分循环中，256×256 LUT × 1024 样本 = 67M 次 pow 调用）

### R85-4 pbr_clustered 重复 F_Schlick 调用去重（MEDIUM GPU）

**问题**：`pbr_clustered.frag` 和 `pbr_clustered_vk.frag` 中 `F_Schlick(max(dot(N, V), 0.0), F0)` 在 L362 计算 `kD`（仅 `#else` 非 IBL 路径使用），又在 L366 重新计算 `F_env`（IBL 路径使用）。在 `HAS_IBL` 定义时，L362 的 `kD` 是死代码，但 F_Schlick 仍被求值。

**修正**：合并为单次 `F_env = F_Schlick(...)` 调用，移到 `#ifdef HAS_IBL` 之前。`kD_env = (1.0 - F_env) * (1.0 - metallic)` 也在前面计算。`#else` 路径使用 `kD_env` 替代原来的 `kD`。消除 IBL 路径中每片段 1 次冗余 F_Schlick 调用。

**验收**：全部 23/23 测试通过。
## R86 关键bug修复 + 粒子GPU回读消除 + VBO/IBO绑定缓存 + sun_color缓存

### R86-1 blinn_phong_clustered 平方链错误修复（CRITICAL）

**问题**：R85-1 在 blinn_phong_clustered.frag/vk 中将 `pow(max(dot(N,H),0.0), 32.0)` 替换为平方链时，初始值用了 `float spec = NdH * NdH`（NdH^2）而非 `float spec = NdH`（NdH^1），但两者都执行了相同的 5 次 `spec *= spec`。结果：clustered 变体计算 NdH^(2×2^5) = NdH^64 而非 NdH^32，使镜面高光显著过窄。

**修正**：将初始值从 `NdH * NdH` 改为 `NdH`，使 5 次平方链正确计算 NdH^32。影响 4 处（blinn_phong_clustered.frag L70/L110、blinn_phong_clustered_vk.frag L76/L116）。

### R86-2 粒子渲染 GPU 回读消除（HIGH CPU/GPU）

**问题**：`particles_render`（particles.c L264-288）每帧通过 `rhi_buffer_map`（即 `glMapBufferRange(GL_MAP_READ_BIT)`）将存活粒子数量从 GPU 回读到 CPU，用于设置 `rhi_cmd_draw` 的实例数。这是阻塞式 GPU 回读，强制 CPU 等待 `particles_cull` 计算着色器完成后才能继续，造成 CPU-GPU 管线串行化停顿。但粒子顶点着色器已有早退保护（`if (P_INST >= draw_count) { gl_Position = vec4(0.0); gl_PointSize = 0.0; return; }`），`draw_count` 已通过 SSBO 绑定到着色器，回读完全多余。

**修正**：移除 `rhi_buffer_map`/`rhi_buffer_unmap` 调用，直接绘制 `PARTICLES_MAX` 个实例。`last_alive_count` 设为 `PARTICLES_MAX`（仅用于 debug UI 近似显示）。

### R86-3 VBO/IBO 绑定缓存（MEDIUM CPU）

**问题**：`rhi_cmd_bind_vertex_buffer` 每次调用 `glBindVertexBuffer`，`rhi_cmd_bind_index_buffer` 每次调用 `glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ...)`，均无缓存检查。与引擎中所有其他 GL 状态缓存不一致（纹理 `g_tex_cache`、FBO `g_gl_bound_fbo`、VAO `g_gl_vao`、SSBO `g_gl_ssbo_cache`、间接缓冲 `g_gl_indirect_buf` 等均已缓存）。在多网格绘制循环中连续绘制经常重复绑定相同缓冲区。

**修正**：添加文件作用域 `g_gl_bound_vbo` 和 `g_gl_bound_ibo` 缓存变量。在 `rhi_cmd_bind_vertex_buffer`/`rhi_cmd_bind_index_buffer` 中检查缓冲区是否已绑定。VAO 变化时（`gl_cmd_bind_pipeline` 和 `rhi_pipeline_create`）同步失效两个缓存。

### R86-4 sun_color/ambient_col 缓存（LOW CPU）

**问题**：`sun_color` 和 `ambient_col` 每帧重新计算，但仅依赖 `sun_elevation`（通过 `sun_t`）和 `ambient_mult`。太阳方向 `cached_sun_dir` 已在 elevation/azimuth 未变时跳过重计算，但 `sun_color`/`ambient_col` 未纳入同一缓存块。

**修正**：添加 `cached_sun_t`、`cached_amb_mult`、`cached_sun_color`、`cached_ambient_col` 静态变量。仅在 `sun_t` 或 `ambient_mult` 变化时重计算 `sun_color` 和 `ambient_col`。

**验收**：全部 23/23 测试通过。

## R87 遮挡剔除GPU回读消除 + 着色器硬编码常量移至shader const

### R87-1 遮挡剔除 GPU 回读消除（HIGH CPU/GPU）

**问题**：`occlusion_cull_dispatch`（occlusion_cull.c L305-310）每帧通过 `rhi_buffer_map`（即 `glMapBufferRange(GL_MAP_READ_BIT)`）将可见性结果从 GPU 回读到 CPU，用于遮挡过滤。与 R86-2 粒子回读相同的管线停顿模式，但数据量更大（最多 16384×4=64KB vs 4 字节）。GL 路径阻塞 CPU 直到 GPU 完成写入。VK 路径因持久映射无停顿，但为保持后端一致性仍统一处理。

**修正**：
1. 新增 RHI 函数 `rhi_cmd_copy_buffer`：GL 用 `glCopyBufferSubData`（GPU 侧复制，非阻塞），VK 用 `vkCmdCopyBuffer`。
2. 在 `OcclusionCullSystem` 中添加 `readback_staging` 缓冲区（与 `visibility_buffer` 相同大小）。
3. `occlusion_cull_dispatch` 改为从 `readback_staging` 读取（上一帧的 GPU 侧副本），dispatch 完成后用 `rhi_cmd_copy_buffer` 将结果从 `visibility_buffer` 复制到 `readback_staging`。
4. VK 后端为 storage buffer 自动添加 `VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT`，使所有 SSBO 可参与 GPU 侧复制。
5. 系统已设计为 1 帧延迟，`object_count` 初始为 0 使首帧全部可见，staging 方案不改变延迟语义。

**影响文件**：rhi.h, rhi_gl.c, rhi_vk.c, occlusion_cull.h, occlusion_cull.c, rhi_stubs.c

### R87-2 terrain 硬编码光照 uniform → shader const（MEDIUM GPU/CPU）

**问题**：`terrain_render`（terrain.c L300-302）每帧通过 `rhi_cmd_set_uniform_vec3` 设置 3 个硬编码常量（`u_light_dir`、`u_light_color`、`u_ambient`），但这些值从不变化。GL 路径每帧 3 次 `glUniform3f` 调用浪费 CPU 时间。VK 路径使用 push constant 且值打包在 vec4 中共享其他字段，不能修改布局。

**修正**：
1. GL 着色器（terrain.frag）：将 `uniform vec3 u_light_dir/color/ambient` 替换为 `const vec3`，编译器内联，无需 CPU 设置。
2. C 代码（terrain.c）：为 3 个 uniform 添加 `if (loc >= 0)` 守卫。GL 路径 `loc=-1`（uniform 被 const 替换后优化掉）跳过设置；VK 路径 `loc>=0`（push constant 仍存在）正常设置。
3. VK 着色器（terrain_vk.frag）不改：push constant 布局无法单独替换为 const。

**影响文件**：terrain.frag, terrain.c

### R87-3 后处理硬编码常量 uniform → shader const（LOW GPU/CPU）

**问题**：`combined_taa_fxaa.frag`、`taa.frag`、`fxaa.frag` 中 `u_taa_blend`（0.1）和 `u_fxaa_threshold`（0.0312）为硬编码常量，但通过 `uniform` 声明，每帧由 CPU 设置。`combined_post_process.c` 已有 `if (loc >= 0)` 守卫，但 GL 着色器仍声明为 uniform 导致 loc 查找成功并每帧设置。

**修正**：将 GL 着色器中的 `uniform float u_taa_blend/u_fxaa_threshold` 替换为 `const float`。uniform 被 const 替换后，`glGetUniformLocation` 返回 -1，`if (loc >= 0)` 守卫跳过 CPU 设置。VK 着色器使用 push constant offset，不受影响。

**影响文件**：combined_taa_fxaa.frag, taa.frag, fxaa.frag

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## R88 着色器效率优化(第四轮)：cluster_cull pow→exp2 + terrain const向量预归一化

### R88-1 cluster_cull.comp pow() → exp2()（MEDIUM GPU）

**问题**：`cluster_cull.comp`（L60-62）的 `cluster_depth()` 函数使用 `pow(FARP / NEARP, float(z) / float(CZ))`。该计算着色器每帧由 `light_system_cull_gpu` dispatch，共 3072 个 invocation（16×8×24），每个调用 `cluster_depth()` 两次，即每帧 6144 次 `pow()` 调用。`pow()` 在 GPU 上使用超越函数指令，比 `exp2()` 更昂贵。R83-1 已将片元着色器中的聚类深度 `pow()` 循环替换为 `log2` O(1) 计算，但遗漏了该计算着色器。

**修正**：将 `pow(base, exp)` 替换为 `exp2(log2(base) * exp)`。`log2(FARP / NEARP)` 是 uniform 不变量表达式，编译器可将其提升到循环外。`exp2()` 在 GPU 上通常映射到单个指令，比 `pow()` 更高效。

**影响文件**：cluster_cull.comp

### R88-2 terrain.frag const 向量预归一化（MEDIUM GPU）

**问题**：R87-2 将 `terrain.frag` 中的 `u_light_dir` 从 `uniform` 改为 `const vec3`，但第 56 行仍对这一常量向量执行 `normalize(-u_light_dir)`。`normalize()` 对每个地形片元执行 `length()` + 3 次除法，而输入是编译期常量，归一化结果也是常量。仅影响 GL 版（VK 版使用 push constant，`u_light_dir` 非常量，`normalize()` 必需）。

**修正**：预计算归一化值 `length(vec3(0.5,-0.8,0.3)) = sqrt(0.98) ≈ 0.98995`，将 const 声明改为已归一化值 `vec3(0.5050763, -0.8081220, 0.3030458)`，并将 `normalize(-u_light_dir)` 替换为 `-u_light_dir`（常量取反，无需归一化）。

**影响文件**：terrain.frag

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## R89 VK pipeline绑定缓存 + 着色器硬编码常量移至shader const(第二轮)

### R89-1 VK pipeline 绑定缓存（MEDIUM CPU）

**问题**：VK 后端 `rhi_cmd_bind_pipeline`（rhi_vk.c L2605）每次调用都执行 `vkCmdBindPipeline`，不检查 pipeline 是否已绑定。GL 后端已有 pipeline 缓存（`g_gl_program`/`g_gl_vao`，R80-1），VK 后端缺少对等优化。在多 draw call 渲染循环中，连续绘制相同 pipeline 的对象会重复记录 `vkCmdBindPipeline` 命令。

**修正**：
1. 在 `rhi_cmd_bind_pipeline` 中添加 `if (bound != vk->current_pipeline)` 检查，跳过冗余 `vkCmdBindPipeline` 调用。`current_pipeline_data` 和 `storage_set_valid` 仍每次更新以保持状态一致性。
2. 在帧起始（`vkResetCommandBuffer` 后）重置 `vk->current_pipeline = VK_NULL_HANDLE`，确保新命令缓冲区的首次绑定不被跳过。

**影响文件**：rhi_vk.c

### R89-2 dof/ssr/upscale 硬编码常量 uniform → shader const（LOW GPU/CPU）

**问题**：`dof.c`、`ssr.c`、`upscale.c` 每帧设置硬编码常量 uniform（`u_dof_near=0.1`、`u_dof_far=100.0`、`u_ssr_thickness=0.05`、`u_ups_sharp=0.0`），但这些值从不变化。与 R87-2/R87-3 相同模式。C 代码已有 `if (loc >= 0)` 守卫。

**修正**：将 GL 着色器中的 `uniform float` 替换为 `const float`。uniform 被 const 替换后，`glGetUniformLocation` 返回 -1，`if (loc >= 0)` 守卫跳过 CPU 设置。VK 着色器使用 push constant offset，不受影响。`u_ups_sharp=0.0` 使 `if (u_ups_sharp > 0.0)` 分支成为死代码，编译器自动优化掉锐化计算。

**影响文件**：dof.frag, ssr.frag, upscale.frag

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

> **R91-1 修正**：`u_ups_sharp` 不是硬编码常量——Pass 1 传入 `0.3f`（锐化），Pass 2 传入 `0.0f`（纯复制）。R89-2 将其改为 `const 0.0` 导致 GL 路径 Pass 1 锐化被静默禁用。R91-1 已恢复为 `uniform float u_ups_sharp;`。

## R90 VK storage描述符集冗余绑定消除

### R90-1 VK rhi_cmd_bind_storage_buffer 冗余 vkCmdBindDescriptorSets 消除（MEDIUM CPU）

**问题**：VK 后端 `rhi_cmd_bind_storage_buffer`（rhi_vk.c L2712）每次调用都执行 `vkCmdBindDescriptorSets`，即使描述符集已绑定。一个计算着色器 dispatch 通常绑定 4-5 个 SSBO，每个绑定都执行一次 `vkCmdBindDescriptorSets`，但首次绑定后后续绑定只需 `vkUpdateDescriptorSets` 更新描述符即可——Vulkan 保证已绑定描述符集的更新对后续 GPU 命令可见。

**修正**：添加 `need_bind` 标志，仅在描述符集首次分配（`storage_set_valid` 为 false）时执行 `vkCmdBindDescriptorSets`。后续 `rhi_cmd_bind_storage_buffer` 调用仅执行 `vkUpdateDescriptorSets` 更新绑定槽位，跳过冗余的描述符集绑定命令。`rhi_cmd_bind_pipeline` 设置 `storage_set_valid = false` 确保新 pipeline 首次绑定时重新分配和绑定描述符集。

**安全性分析**：
- 存储描述符集绑定到 set 0，纹理描述符集绑定到 set 1，UBO 描述符集绑定到 `cpd->ubo_set`——互不干扰。
- `rhi_cmd_bind_pipeline` 是唯一使 `storage_set_valid` 失效的函数，确保 pipeline 变化时重新绑定。
- Vulkan 规范保证：`vkUpdateDescriptorSets` 对已绑定描述符集的更新在后续 draw/dispatch 命令中可见，无需重新绑定。

**影响文件**：rhi_vk.c

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## R91 Bug修复 + 冗余normalize消除

### R91-1 upscale.frag u_ups_sharp const回归修复（HIGH 回归）

**问题**：R89-2 将 `upscale.frag` 的 `u_ups_sharp` 改为 `const float u_ups_sharp = 0.0`，错误地认为它是硬编码常量。实际上 C 代码（`upscale.c`）在 Pass 1 传入 `sharpness = 0.3f`（TSR 锐化），Pass 2 传入 `0.0f`（纯复制）。const 化后 `glGetUniformLocation` 返回 -1，`if (loc_sharp >= 0)` 守卫跳过两次 uniform 设置，shader 中 `u_ups_sharp` 恒为 0.0，`if (u_ups_sharp > 0.0)` 成为死代码。**Pass 1 的锐化效果（0.3f）被静默禁用**，且与 VK 路径（`upscale_vk.frag` 使用 push constant，不受影响）产生行为不一致。

**修正**：恢复为 `uniform float u_ups_sharp;`。

**影响文件**：upscale.frag

### R91-2 volumetric.frag GL uniform名称不匹配修复（MEDIUM BUG）

**问题**：`volumetric.frag`（GL 版）声明 `uniform vec3 u_vol_light_dir;`，但 C 代码（`volumetric.c` L91-93）查询 uniform location 时使用 `"u_vol_ldx"`/`"u_vol_ldy"`/`"u_vol_ldz"`（与 VK 版 `volumetric_vk.frag` 一致）。GL 路径中 `loc_ldx/ldy/ldz = -1`（着色器中不存在这些 uniform），`if (loc >= 0)` 守卫跳过设置，`u_vol_light_dir` 从未被赋值，默认为 `(0,0,0)`，`normalize(vec3(0,0,0))` 产生未定义值。结果：GL 路径体积雾缺少方向光照散射，仅保留环境雾色项。

**修正**：将 GL 着色器的 `uniform vec3 u_vol_light_dir` 拆分为 `uniform float u_vol_ldx/ldy/ldz`，与 C 代码和 VK 着色器统一。同时移除冗余 `normalize()`（C 代码已通过 `vec3_normalize` 归一化 `sun_dir`）。

**影响文件**：volumetric.frag

### R91-3 skybox/volumetric 冗余normalize消除（LOW GPU）

**问题**：`skybox.frag`/`skybox_vk.frag` 中 `normalize(u_sun_dir)` 和 `volumetric_vk.frag` 中 `normalize(vec3(u_vol_ldx,...))` 对已归一化的向量执行冗余归一化。C 代码（`main.c` L3586）通过 `vec3_normalize()` 计算 `cached_sun_dir`，保证传入着色器的方向已是单位向量。

**修正**：移除 4 个着色器中的冗余 `normalize()` 调用。

**影响文件**：skybox.frag, skybox_vk.frag, volumetric.frag, volumetric_vk.frag

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## R92 GL/VK uniform名称不匹配修复（第二轮）

### R92-1 volumetric.frag GL u_vol_light_color 名称不匹配修复（MEDIUM BUG）

**问题**：与 R91-2 相同的模式。`volumetric.frag`（GL 版）声明 `uniform vec3 u_vol_light_color;`，但 C 代码（`volumetric.c` L94-96）查询 `"u_vol_lcx"`/`"u_vol_lcy"`/`"u_vol_lcz"`。GL 路径中 `loc_lcx/lcy/lcz = -1`，光照颜色默认为 `(0,0,0)`，体积雾缺少彩色光照贡献。VK 版 `volumetric_vk.frag` 已正确使用 `u_vol_lcx/ldy/ldz`（push constant offset 140/144/148）。

**修正**：将 GL 着色器的 `uniform vec3 u_vol_light_color` 拆分为 `uniform float u_vol_lcx/ldy/ldz`，与 C 代码和 VK 着色器统一。

**影响文件**：volumetric.frag

### R92-2 occlusion_cull.comp / hi_z_generate.comp uniform名称不匹配修复（HIGH BUG）

**问题**：遮挡剔除系统的计算着色器 uniform 名称在 GL、VK、C 代码三方不匹配：
- C 代码（`occlusion_cull.c` L151-155）查询 `"pc.view_proj"`/`"pc.object_count"`/`"pc.hi_z_width"`/`"pc.hi_z_height"`/`"pc.output_size"`（带点号）
- GL 着色器声明 `pc_view_proj`/`pc_object_count`/`pc_hi_z_width`/`pc_hi_z_height`/`pc_output_size`（带下划线，GLSL 不允许点号）
- VK 后端 `rhi_pipeline_get_uniform_location` 无 `"pc.*"` 名称的 push constant 映射

结果：GL 和 VK 两端 `loc = -1`，`if (loc >= 0)` 守卫跳过所有 uniform 设置。遮挡剔除计算着色器使用默认值（`object_count=0` → 所有调用提前返回，无可见性写入），Hi-Z mip 生成完全失效。**遮挡剔除系统在 GL 和 VK 两端均不工作**。

**修正**：
1. 将 C 代码的查询从 `"pc.*"` 改为 `"pc_*"`（匹配 GL 着色器名称）。
2. 在 VK 后端 `rhi_pipeline_get_uniform_location` 的 compute 分支添加 push constant 映射：`pc_view_proj`@0, `pc_object_count`@64, `pc_hi_z_width`@68, `pc_hi_z_height`@72, `pc_output_size`@0。

**影响文件**：occlusion_cull.c, rhi_vk.c

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## R93 gbuffer.frag 未设置uniform默认值修复

### R93-1 gbuffer.frag u_ao_default 默认值修复（MEDIUM BUG）

**问题**：`gbuffer.frag`（GL 版）声明 4 个 uniform（`u_metallic_default`/`u_roughness_default`/`u_ao_default`/`u_emissive_flag`），但 C 代码（`deferred.c`）从未查询或设置它们。GL 路径中这些 uniform 默认为 0.0：
- `u_metallic_default=0.0` → `metal = mr.x + 0.0 = mr.x`（正确，从纹理读取）
- `u_roughness_default=0.0` → `rough = mr.y + 0.0 = mr.y`（正确）
- `u_ao_default=0.0` → `ao = 0.0`（**BUG：无环境光遮蔽**）
- `u_emissive_flag=0.0` → 无自发光（正确）

VK 版 `gbuffer_vk.frag` 使用 push constant offset 256-268，同样从未设置（deferred 路径可选，暂不处理 VK）。

**修正**：将 4 个 `uniform float` 替换为 `const float`，其中 `u_ao_default` 修正为 `1.0`（完全 AO，无遮蔽变暗）。

**影响文件**：gbuffer.frag

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## R94 着色器gamma校正pow→exp2 + VK viewport/scissor缓存 + VK push constant批量发出

### R94-1 gamma校正 pow() → exp2() (MEDIUM GPU)

**问题**：`pbr_clustered.frag`/`pbr_clustered_vk.frag` 和 `skybox.frag`/`skybox_vk.frag` 中的 gamma 校正使用 `pow(color, vec3(1.0 / 2.2))`。R83-1/R84-4 已优化光照计算中的 `pow()`，但遗漏了这 4 处 gamma 校正。`pow()` 在 GPU 上使用超越函数指令，比 `exp2()` 更昂贵。

**修正**：将 `pow(x, vec3(1.0/2.2))` 替换为 `exp2(log2(max(x, vec3(0.0))) * (1.0/2.2))`。`exp2()` 在 GPU 上通常映射到单个指令。`max()` 保护防止 log2(0) = -inf。

**影响文件**：pbr_clustered.frag, pbr_clustered_vk.frag, skybox.frag, skybox_vk.frag

### R94-2 VK viewport/scissor 缓存 (LOW CPU)

**问题**：VK 后端 `rhi_cmd_set_viewport`/`rhi_cmd_set_scissor`/`rhi_cmd_set_shadow_viewport` 每次调用都无条件发出 `vkCmdSetViewport`/`vkCmdSetScissor`。GL 后端已有 viewport 缓存（R76-2），VK 后端缺少对等机制。在多 pass 渲染中，连续设置相同 viewport/scissor 产生冗余命令。

**修正**：在 VKBackend 中添加 `cached_vp_x/y/w/h` 和 `cached_sc_x/y/w/h` 缓存字段 + `vp_valid`/`sc_valid` 标志。`rhi_cmd_set_viewport`/`rhi_cmd_set_scissor` 检查缓存命中时跳过 GL 调用。`rhi_cmd_set_shadow_viewport` 分别检查 viewport 和 scissor 缓存。帧起始和 render pass begin 时重置缓存。

**影响文件**：rhi_vk.c

### R94-3 VK push constant 批量发出 (MEDIUM CPU)

**问题**：VK 后端每个 `rhi_cmd_set_uniform_*`（mat4/vec3/vec2/vec4/f32/i32 共 6 个变体）都独立调用 `vkCmdPushConstants`。在前向渲染循环中，每个 pipeline bind 后有 6 次连续 uniform 设置 = 6 次 `vkCmdPushConstants` 命令。50 个 mesh 场景下每帧 300+ 次冗余命令记录。

**修正**：在 VKBackend 中添加 256 字节 `push_staging` 暂存缓冲 + `push_dirty_min`/`push_dirty_max` 脏范围标记。`rhi_cmd_set_uniform_*` 仅写入暂存缓冲并更新脏范围。添加 `vk_flush_push_constants()` 辅助函数，在 `rhi_cmd_draw`/`rhi_cmd_draw_indexed`/`rhi_cmd_draw_indexed_indirect`/`rhi_cmd_draw_indexed_indirect_count`/`rhi_cmd_dispatch` 前 flush 脏范围为单次 `vkCmdPushConstants`。帧起始时设置全范围脏标记（新命令缓冲区需重新发出所有 push constant）。

**安全性**：push constant 是命令缓冲区状态（非管线状态），`vkCmdPushConstants` 写入的值在管线切换后仍然有效。flush 使用 `current_pipeline_data->layout` 确保正确的管线布局。`rhi_cmd_bind_pipeline` 不需特殊处理——下一个 draw/dispatch 的 flush 会使用新管线的布局。

**影响文件**：rhi_vk.c

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

> **R95-1 修正**：R94-2 在 swapchain render pass begin 中将缓存更新为有效状态，但 render pass begin 使用非翻转 viewport（`VkViewport.y=0, height=正`），而 `rhi_cmd_set_viewport` 使用翻转 viewport（`VkViewport.y=y+h, height=-h`）。如果后续调用 `rhi_cmd_set_viewport` 相同参数，缓存命中会跳过，导致 viewport 保持非翻转状态（错误）。R95-1 改为失效缓存。

## R95 viewport/scissor缓存bug修复 + 全render pass begin点缓存失效

### R95-1 swapchain render pass begin viewport缓存bug修复（HIGH 回归）

**问题**：R94-2 在 swapchain `rhi_cmd_begin_render_pass` 中将 viewport/scissor 缓存更新为有效状态（`vp_valid = true`）。但 render pass begin 设置的是非翻转 viewport（`VkViewport = {0, 0, w, h, 0, 1}`），而 `rhi_cmd_set_viewport` 设置的是翻转 viewport（`VkViewport = {0, h, w, -h, 0, 1}`）。如果后续调用 `rhi_cmd_set_viewport(0, 0, w, h)`，缓存会命中并跳过，导致 viewport 保持非翻转状态——与渲染器期望的翻转 viewport 不一致。虽然当前代码中 `rhi_cmd_begin_render_pass` 后没有立即调用 `rhi_cmd_set_viewport` 相同参数，但这是一个潜在的定时炸弹。

**修正**：将 swapchain render pass begin 中的缓存更新改为缓存失效（`vp_valid = false, sc_valid = false`）。

### R95-2 全 render pass begin 点添加 viewport/scissor 缓存失效（LOW CPU）

**问题**：R94-2 只在 swapchain render pass begin 和帧起始处重置了 viewport/scissor 缓存。但还有 6 个 render pass begin 点直接设置 viewport/scissor 而未失效缓存：
- `rhi_cmd_bind_shadow_map`
- `rhi_cmd_unbind_shadow_map`
- `rhi_offscreen_fbo_bind`
- `rhi_offscreen_fbo_unbind`
- `rhi_mrt_fbo_bind`
- `rhi_cubemap_depth_fbo_bind_face`

这些函数设置非翻转 viewport（与 `rhi_cmd_set_viewport` 的翻转 viewport 不同）。如果缓存未被失效，后续 `rhi_cmd_set_viewport` 调用可能错误地跳过。

**修正**：在所有 6 个 render pass begin 点添加 `vk->vp_valid = false; vk->sc_valid = false;`。

**影响文件**：rhi_vk.c

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## R96 — Push constant flush 越界修复 + 着色器 pow/normalize 优化

### R96-1 (正确性 MUST FIX): Push constant flush 超出 compute 管线 128 字节范围

**问题**：R94-3 的帧起始逻辑设置 `push_dirty = true; push_dirty_min = 0; push_dirty_max = 256;`，强制每帧第一次 flush 推送 256 字节。但 compute 管线的 push constant range 只有 128 字节，graphics 管线为 256 字节。当帧内第一个 GPU 操作是 compute dispatch 时，flush 会向 compute layout 推送 256 字节，超出声明的 128 字节范围，违反 Vulkan 规范（VUID-vkCmdPushConstants-offset-01795）。

**触发路径**：每帧默认发生 — particles_compute 是帧内第一个 GPU 操作，使用 compute 管线。

**修复**：
1. 帧起始改为 clean state：`push_dirty = false; push_dirty_min = 256; push_dirty_max = 0;`，让每个 `rhi_cmd_set_uniform_*` 自行标记 dirty 范围
2. 在 `vk_flush_push_constants` 中添加防御性截断：按 `is_compute` 标志将 dirty 范围限制在 128/256 字节内

**影响文件**：rhi_vk.c

### R96-2 (LOW GPU): 后处理着色器 gamma 校正 pow→exp2(log2)

**问题**：R94-1 将 pbr_clustered 和 skybox 中的硬编码 `pow(x, 1/2.2)` 转换为 `exp2(log2())`，但遗漏了使用 uniform `u_tm_gamma` 的 4 个后处理着色器：
- tonemap.frag, tonemap_vk.frag
- combined_color.frag, combined_color_vk.frag

**修复**：`pow(max(ldr, vec3(0.0)), vec3(1.0 / u_tm_gamma))` → `exp2(log2(max(ldr, vec3(0.0))) / u_tm_gamma)`

**影响文件**：tonemap.frag, tonemap_vk.frag, combined_color.frag, combined_color_vk.frag

### R96-3 (MEDIUM GPU): 13 个着色器冗余 normalize(-light_dir) 消除

**问题**：R91-3 已为 skybox 和 volumetric 着色器移除了冗余 `normalize(-light_dir)`，但遗漏了 13 个着色器。C 代码在 main.c 中通过 `vec3_normalize()` 预归一化太阳方向并缓存，上传到 GPU 的方向向量已经是单位向量。着色器中的 `normalize(-dl.dir)` / `normalize(-u_light_dir)` 是冗余的 — 每个 `normalize()` 在 GPU 上展开为 dot + rsqrt + mul（约 3 条指令），在逐像素热循环中白白消耗 ALU。

**修复**：
1. 在 `light_system_add_dir()` (lighting.c) 中添加方向归一化，保证缓冲区路径数据已归一化
2. 13 个着色器中移除 `normalize(-dl.dir)` → `(-dl.dir)` 和 `normalize(-u_light_dir)` → `(-u_light_dir)`

**受影响着色器**（13 个）：
- dl.dir 路径（6 个）：pbr_clustered.frag/vk, deferred_light.frag/vk, blinn_phong_clustered.frag/vk
- u_light_dir 路径（4 个）：terrain_vk.frag, instanced.frag, blinn_phong.frag, skinned.frag
- pc.u_light_dir 路径（3 个）：blinn_phong_vk.frag, instanced_vk.frag, skinned_vk.frag

**影响文件**：lighting.c + 13 个着色器文件

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## R97 — VK 描述符写入批量化 + Terrain 光照方向归一化

### R97-1 (正确性): Terrain 光照方向归一化

**问题**：R96-3 移除了 terrain_vk.frag 中的 `normalize(-u_light_dir)`，但 terrain.c:300 设置的 `u_light_dir = (0.5, -0.8, 0.3)` 未归一化（长度 ≈ 0.99），导致约 1% 的光照亮度误差。

**修复**：在 C 端归一化光照方向后再上传到 GPU。

**影响文件**：terrain.c

### R97-2 (MEDIUM CPU): rhi_cmd_bind_material_textures 描述符写入 9→1

**问题**：`rhi_cmd_bind_material_textures` 创建 9 个独立的 `VkWriteDescriptorSet`（每个 descriptorCount=1），调用 `vkUpdateDescriptorSets(device, 9, writes, ...)`。但绑定 0-8 是连续的，可以用单个写入（descriptorCount=9）完成。

**修复**：使用 1 个 `VkWriteDescriptorSet`（dstBinding=0, descriptorCount=9）替代 9 个独立写入，减少 `vkUpdateDescriptorSets` 的写入条目数。

**影响文件**：rhi_vk.c

### R97-3 (MEDIUM CPU): rhi_cmd_bind_material_textures_ibl 描述符写入 10→4

**问题**：`rhi_cmd_bind_material_textures_ibl` 创建 10 个独立的 `VkWriteDescriptorSet`。绑定 0-4、6-8 是连续的，可以分组合并。

**修复**：将 10 个写入合并为 4 个连续组写入：
- 绑定 0-4（5 个连续）
- 绑定 5（ssao/point_shadow_cubes，1 或 4 个）
- 绑定 6-8（3 个连续）
- 绑定 10（point_shadow_cubes，1 或 4 个）

**影响文件**：rhi_vk.c

### R97-4 (LOW CPU): rhi_cmd_bind_textures_multi 描述符写入 N→1

**问题**：`rhi_cmd_bind_textures_multi` 创建 N 个独立写入（N ≤ 6）。绑定 0..N-1 是连续的。

**修复**：使用 1 个 `VkWriteDescriptorSet`（dstBinding=0, descriptorCount=count）替代 N 个独立写入。

**影响文件**：rhi_vk.c

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## R98 — rhi_cmd_bind_cubemap 描述符写入批量化

### R98-1 (LOW CPU): rhi_cmd_bind_cubemap 描述符写入 2→1

**问题**：`rhi_cmd_bind_cubemap` 创建 2 个独立的 `VkWriteDescriptorSet`（绑定 0 和 1），但两个 `VkDescriptorImageInfo` 完全相同（同一个 cubemap view + sampler）。绑定 0-1 是连续的，可以用单个写入（descriptorCount=2）完成。与 R97 的批量化模式一致。

**修复**：使用 1 个 `VkWriteDescriptorSet`（dstBinding=0, descriptorCount=2）替代 2 个独立写入。消除重复的 `dummy_info` 变量。

**影响文件**：rhi_vk.c

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## R99 — R97-2 回归修复 + terrain VK 纹理绑定 bug 修复

### R99-1 (MEDIUM 正确性): rhi_cmd_bind_material_textures 批量化在 feat_partially_bound 时绑定错位

**问题**：R97-2 将 `rhi_cmd_bind_material_textures` 的 9 个独立
`VkWriteDescriptorSet` 合并为 1 个（dstBinding=0, descriptorCount=9）。但当
`feat_partially_bound=true` 时，描述符布局中 binding 5 的 `descriptorCount=4`
（而非 1）。Vulkan 规范规定跨绑定写入会填充当前绑定的剩余数组元素后再进入
下一绑定，因此 9 个描述符的实际分配为：
- 描述符 0-4 → binding 0-4 ✓
- 描述符 5 → binding 5, 元素 0 ✓
- 描述符 6-8 → binding 5, 元素 1-3 ✗（应为 binding 6-8）
- binding 6-8 → 未写入（未定义）✗

这是 R97-2 引入的回归。当前无可见渲染错误（通过此路径的着色器不访问
binding 6-8），但描述符集状态与 R97 之前不一致。

**修复**：将单次写入拆分为 3 组，参照 R97-3 对
`rhi_cmd_bind_material_textures_ibl` 的正确做法：
- 绑定 0-4：descriptorCount=5（各 binding descriptorCount=1）
- 绑定 5：descriptorCount=1（仅写元素 0，数组大小为 4 时不越界）
- 绑定 6-8：descriptorCount=3（各 binding descriptorCount=1）

**影响文件**：rhi_vk.c, rhi_stubs.c（添加 stub）

### R99-2 (MEDIUM 正确性): VK 路径 rhi_cmd_bind_texture 多调用覆盖 bug（9 个文件）

**问题**：多个渲染器在 VK 路径中连续调用 `rhi_cmd_bind_texture` 绑定多个纹理到
不同 unit。但 VK 路径中 `rhi_cmd_bind_texture` 忽略 `unit` 参数，调用
`rhi_cmd_bind_material_textures` 将全部 9 个描述符槽绑定到同一纹理，然后调用
`vkCmdBindDescriptorSets`。后续调用会覆盖前面的描述符集，使着色器在所有绑定上
只看到最后绑定的纹理。这是预存 bug（非 R95-R98 引入）。

**受影响的文件与绑定映射**：

| 文件 | 原调用数 | 纹理→绑定映射 |
|------|---------|---------------|
| terrain.c | 2 | albedo→0, shadow→1 |
| debug_viz.c | 2 | albedo→0, shadow→1 (depth) |
| ssao.c (blur) | 2 | albedo→0, shadow→1 (depth) |
| post_process.c (bloom) | 2 | albedo→0, shadow→1 (ping color) |
| sss.c (pass 1) | 2 | albedo→0, shadow→1 (depth) |
| sss.c (pass 2) | 3 | albedo→0, shadow→1 (depth), mr→2 (blur color) |
| tonemap.c (auto_exposure) | 2 | albedo→0, shadow→1 (lum_prev) |
| tonemap.c (apply) | 2 | albedo→0, shadow→1 (lum) |
| god_rays.c | 2 | albedo→0, shadow→1 (depth) |
| motion_blur.c | 2 | albedo→0, shadow→1 (depth) |
| upscale.c (pass 1) | 3 | albedo→0, shadow→1 (depth), mr→2 (history) |
| upscale.c (pass 2) | 3 | albedo→0, shadow→1 (depth), mr→2 (history) |

**修复**：将多处的 `rhi_cmd_bind_texture` 调用替换为单次
`rhi_cmd_bind_material_textures` 调用，通过参数顺序正确分配纹理到对应绑定
（albedo→binding 0, shadow→binding 1, mr→binding 2），在单个描述符集中完成。
对于 tonemap.c 的 `tonemap_apply` 函数，当不需要第二个纹理（非 auto_exposure）
时保留单次 `rhi_cmd_bind_texture` 调用。

**影响文件**：terrain.c, debug_viz.c, ssao.c, post_process.c, sss.c, tonemap.c,
god_rays.c, motion_blur.c, upscale.c

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## R100 — pbr_clustered IBL 函数冗余 normalize 消除

### R100-1 (LOW GPU): pbr_clustered 着色器 IBL 函数 normalize(-read_dir_light(0).dir) 冗余消除

**问题**：R96-3 在 C 端（`light_system_add_dir`）预归一化了方向光源方向，并更新了
pbr_clustered 着色器主光照循环中的 `normalize(-dl.dir)` → `(-dl.dir)`。但 IBL 辅助
函数 `irradiance_hemisphere` 和 `prefiltered_specular` 中的
`normalize(-read_dir_light(0).dir)` 被遗漏，仍然在每个像素执行冗余的 `normalize()`
（涉及 dot + sqrt + rsq 指令）。两个函数各调用一次，共 2 次冗余 normalize/像素。

**修复**：将 `normalize(-read_dir_light(0).dir)` 替换为
`(-read_dir_light(0).dir)`，与 R96-3 的主光照循环修复保持一致。

**影响文件**：pbr_clustered.frag, pbr_clustered_vk.frag（各 2 处，共 4 处替换）

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。



### R103-1 (BUG GL): instanced.vert / skinned.vert / blinn_phong_clustered.frag 的 samplerBuffer binding 与 rhi_cmd_bind_texel_buffers 硬编码单元不匹配

**问题**：GL 后端 `rhi_cmd_bind_texel_buffers` 硬编码将 texel buffer 绑定到纹理单元 5（buf0）和 6（buf1），这是为 pbr_clustered/deferred_light 着色器设计的（它们的 `u_light_data` 在 binding 5，`u_light_grid` 在 binding 6）。但 3 个 GL 着色器的 `samplerBuffer` binding 与此不匹配：

1. **instanced.vert**：`u_instances` 在 `layout(binding = 1)`，但 `rhi_cmd_bind_texel_buffers` 绑定到单元 5。GL 端实例化渲染读取到错误数据（纹理单元 1 上没有 TBO 绑定），所有实例矩阵为零。
2. **skinned.vert**：`u_joints` 在 `layout(binding = 1)`，同样的问题。GL 端骨骼动画读取到错误关节矩阵。
3. **blinn_phong_clustered.frag**：`u_light_data` 在 `layout(binding = 1)`，`u_light_grid` 在 `layout(binding = 2)`，应为 5/6。

**根因**：VK 端使用 `set = 1, binding = 0/1`，与 VK 的 `rhi_cmd_bind_texel_buffers` 一致（绑定到 set 1）。GL 端的 binding 声明没有同步更新为与硬编码单元 5/6 一致。

**修复**：将 3 个 GL 着色器的 `samplerBuffer` binding 改为 5/6，与 `rhi_cmd_bind_texel_buffers` 的硬编码单元一致。GL 纹理单元允许不同目标（GL_TEXTURE_2D / GL_TEXTURE_BUFFER）共存于同一单元，因此 binding 5 上的 `u_ssao`（sampler2D）和 `u_instances`/`u_light_data`（samplerBuffer）不会冲突。

**影响文件**：instanced.vert, skinned.vert, blinn_phong_clustered.frag

### R103-2 (BUG): blinn_phong_clustered 着色器 light grid 读取方式与 pbr_clustered 不一致

**问题**：`blinn_phong_clustered.frag` 和 `blinn_phong_clustered_vk.frag` 使用 `int(texelFetch(u_light_grid, k).r)` 直接读取 grid 数据，而 `pbr_clustered.frag` 使用 `grid_u32(k)` 函数（`floatBitsToUint(texelFetch(u_light_grid, k >> 2u)[k & 3u])`）。

grid buffer 存储的是 `u32` 值数组，通过 RGBA32F texel buffer 上传。每个 texel 打包 4 个 u32。`pbr_clustered` 的 `grid_u32()` 正确解包：texel 索引 = k/4，分量 = k%4，然后用 `floatBitsToUint` 恢复原始 uint。而 `blinn_phong_clustered` 的直接读取会访问错误的 texel 索引（k 而非 k/4），并将 u32 位模式错误地解释为 float 再转 int，产生垃圾值。

**修复**：在两个 `blinn_phong_clustered` 着色器中添加 `grid_u32()` 函数，并将所有 grid 读取调用改为使用该函数，与 `pbr_clustered` 保持一致。

**影响文件**：blinn_phong_clustered.frag, blinn_phong_clustered_vk.frag

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## Round 104

### R104 审查范围

审查以下 5 个新提交中的正确性和性能问题：

- `7a992c8 feat(ecs): add Exclude/Optional query support`
- `2fa351f feat(renderer): integrate point light cubemap shadow`
- `3b53ea1 feat(asset): priority min-heap + 2-worker decode pipeline`
- `4745d93 feat(tools): Windows packer with zero-copy memory mapping`
- `21dd0d9 fix(build): Windows compilation fixes`

### R104 审查结论（无需修复）

1. **Point shadow 代码**：`far_planes[slot] = r`（光源半径），`blinn_phong_clustered` 使用 `light_radius` 替代 `far_plane` 等价。`shadow_index` 初始化正确（0xFF = 无阴影，slot index = 有阴影）。
2. **clustered_pipeline 死代码**：`cl_loc_point_shadow_far_planes` 声明初始化但从未使用，因为 `clustered_pipeline` 从未在渲染循环中绑定。不影响运行时。
3. **VK push constant 布局**：`float[4]` 使用 std430 紧密打包（16 字节），`rhi_cmd_set_uniform_vec4` 正确写入 16 字节。`deferred_light_vk.frag` 中 `u_clip_params.z` 是 shadow_bias 的空间优化打包，正确。
4. **GL/VK deferred_light binding**：GL 和 VK 有不同的 binding 顺序，但各自匹配 C 端绑定代码。正确。
5. **ECS Exclude/Optional**：`exclude_mask`/`optional_mask` 位掩码实现正确，`ecs_query_refresh` 正确保存/恢复 masks 并重新匹配原型。`world_query`/`query_next` 迭代逻辑正确。
6. **async loader 线程安全**：mutex + condition variable + atomic 使用正确，shutdown 正确清理残留 jobs。
7. **Windows packer**：`CreateFileMapping` 零拷贝 + `FindFirstFile`/`FindNextFile` 递归遍历，资源释放正确。
8. **`HAS_POINT_SHADOW` 定义**：仅注入到 `pbr_clustered.frag`。`deferred_light.frag` 无 `#ifdef` 守卫（函数始终编译），`blinn_phong_clustered.frag` 有 `#ifdef` 守卫但该 define 从未为其注入（回退着色器，不影响运行时）。

### R104-1 (PERF): decode pipeline 输入队列忽略 priority 字段

**问题**：`decode_pipeline_submit` 接受 `priority` 参数并存储到 `DecodeJob.priority`，但 `input_queue_push` 简单追加到链表尾部（FIFO），完全忽略 priority。异步加载器使用 2 个 I/O 线程从 min-heap 弹出请求，低优先级请求可能先完成 I/O 并提交到 decode pipeline，导致高优先级纹理被延后解码，加剧纹理 pop-in。commit message 声称 "priority min-heap" 但实际实现是 FIFO。

**修复**：将 `input_queue_push` 从 FIFO 追加改为优先级排序插入。低 priority 值 = 高优先级（与异步加载器的 `heap_item_higher` 一致）。对于 ≤ 256 条目的链表，线性扫描插入比堆更快。同优先级保持 FIFO（插入到最后一个 ≤ priority 的节点之后）。

**影响文件**：decode_pipeline.c

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## Round 105

### R105 审查范围

全量深度审查着色器热路径、渲染循环、内存分配模式、RHI 后端、点光阴影管线、ECS 查询迭代、异步加载器线程安全、VFS/packer 防御性编程。

### R105 审查结论（无需修复）

1. **着色器热路径**：R84-R96 系列已优化 POM 门控、SSGI 循环不变量提升、shadow_test 提升、F_Schlick pow→mul、预归一化光源方向。无新冗余计算。
2. **渲染循环**：`point_shadow_gather` 在前向渲染前调用，`g_psc` 缓存正确。`point_shadow_render_end` 在所有面渲染后调用一次（R78-3）。无冗余状态变更。
3. **点光阴影管线**：`point_shadow_compute_face_vp` 解析构建 6 面 VP 矩阵正确。`point_shadow_update` 偏插入排序选最近光源正确。`light_system_set_point_shadow_indices` 正确映射 shadow slot 到 light index。
4. **RHI 后端**：GL `rhi_cmd_bind_material_textures_ibl` SSAO 绑定 unit 11 匹配 `pbr_clustered.frag` 的 `layout(binding = 11)`。VK 使用 `descriptorBindingPartiallyBound` 允许共享布局服务前向/延迟着色器。`rhi_cubemap_depth_fbo_bind_face` GL/VK 实现正确。
5. **ECS 查询**：`world_query`/`query_next`/`world_query_cached` 迭代逻辑正确。`ecs_query_refresh` 正确处理 exclude/optional masks。
6. **异步加载器**：mutex + condition variable + atomic 使用正确。decode pipeline 2-worker 设置正确（R104-1 修复后优先级队列生效）。
7. **Windows packer**：`CreateFileMapping` 零拷贝 + `FindFirstFile`/`FindNextFile` 递归遍历，资源释放正确。

### R105-1 (ROBUSTNESS): VFS mount 函数缺少 NULL 路径检查

**问题**：`vfs_mount_dir` 和 `vfs_mount_pak` 未检查 `dir_path`/`pak_path` 是否为 NULL。传入 NULL 会导致 `strncpy(NULL, ...)` / `fopen(NULL, ...)` 触发未定义行为（崩溃），且 `LOG_INFO`/`LOG_ERROR` 的 `%s` 格式化 NULL 也是 UB。`test_vfs.c` 已标注此为 engine bug。

**修复**：在两个函数的参数检查中添加 `!dir_path` / `!pak_path` 条件。同时在 `vfs_mount_dir` 的 `strncpy` 后显式设置 `path[VFS_MAX_PATH - 1] = '\0'` 保证终止。

**影响文件**：vfs.c

### R105-2 (ROBUSTNESS): packer add_file 缺少 g_names 缓冲区边界检查

**问题**：`add_file` 中 `memcpy(g_names + g_name_size, rel_path, name_len)` 无边界检查。`g_names` 缓冲区大小为 `MAX_ENTRIES * MAX_PATH_LEN`（1,064,960 字节），但 `rel_path` 来自 `scan_dir` 的 `char[1024]` 缓冲，可超过 `MAX_PATH_LEN`(260)。当总名称数据超过缓冲区大小时，`memcpy` 溢出。

**修复**：在 `memcpy` 前检查 `g_name_size + name_len > MAX_ENTRIES * MAX_PATH_LEN`，超限则跳过文件并警告。将 `name_len` 计算提前到边界检查之前。

**影响文件**：packer.c

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## Round 106

### R106 审查范围

VK 描述符池管理与帧生命周期、GL 状态缓存与资源销毁失效、RHI 资源槽泄漏、compute pipeline 切换状态、uniform ring buffer 溢出、render graph 资源生命周期、pool allocator 双释放。

### R106 审查结论（无需修复）

1. **VK 描述符池**：每帧 `vkResetDescriptorPool` 正确释放所有描述符集，pool maxSets=4096 充足。`VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT` 允许单个释放，但 per-frame reset 更高效。
2. **RHI 资源槽**：`rhi_alloc_slot`/`rhi_free_slot` 使用侵入式自由链表，generation 计数防止悬空句柄。GL/VK `rhi_device_destroy` 正确遍历所有 alive 槽释放。
3. **Uniform ring buffer**：4MB per-frame 环形缓冲，帧开始时 offset 归零。push constant 使用 `push_staging[256]` 固定缓冲，location 偏移由 `rhi_pipeline_get_uniform_location` 硬编码返回（均 ≤256），无溢出风险。
4. **Render graph**：`rg_destroy` 正确释放所有 allocated 纹理和 pool 条目。`rg_compile` 拓扑排序 + 死 pass 剔除正确。`rg_reset` 清零 pass/resource 计数但保留 texture pool。
5. **Pool allocator**：`pool_release` 检查 NULL，`pool_owns` 验证块边界。无双释放检测（标准 pool 设计），但 `pool_reset` 可安全回收所有块。
6. **Render pass suspend/resume**：`vk_suspend_pass_for_compute` 正确结束 pass（STORE op），`vk_resume_pass_if_needed` 用 LOAD-op twin 恢复。`rhi_frame_end` 正确恢复挂起的 pass。
7. **VK pipeline 变体**：`vk_pipeline_for_fmt` 惰性构建 render-pass-compatible 变体，`vk_pipeline_data_free` 正确销毁基础管线 + 所有变体 + 布局 + SPIR-V 副本。

### R106-1 (CORRECTNESS): VK rhi_frame_begin 未重置 storage_set_valid 和 current_pipeline_data

**问题**：`rhi_frame_begin` 调用 `vkResetDescriptorPool` 释放当前帧的所有描述符集，但未重置 `storage_set_valid`（仍为上一帧的 `true`）和 `current_pipeline_data`（仍指向上一帧的管线）。若新帧中 `rhi_cmd_bind_storage_buffer` 在 `rhi_cmd_bind_pipeline` 之前被调用：
1. `current_pipeline_data` 非空（上一帧残留）→ 通过 guard 检查
2. `storage_set_valid` 为 true → 跳过描述符集分配
3. `vk->storage_set` 是被 `vkResetDescriptorPool` 释放的悬空句柄 → `vkUpdateDescriptorSets` 操作已释放的描述符集 → UB/崩溃

当前渲染循环每帧首先 `rhi_cmd_bind_pipeline`（该函数正确重置 `storage_set_valid = false`），因此此 bug 为潜在状态。但 `current_pipeline_data` 未重置导致 guard 逻辑不可靠。

**修复**：在 `rhi_frame_begin` 中添加 `vk->current_pipeline_data = NULL` 和 `vk->storage_set_valid = false`，与 `current_pipeline`（L1286 已重置）保持一致。

**影响文件**：rhi_vk.c

### R106-2 (CORRECTNESS): GL 纹理/采样器/SSBO 缓存在资源销毁时未失效

**问题**：GL 后端维护三个绑定缓存：`g_tex_cache[16]`（纹理单元）、`g_sam_cache[16]`（采样器）、`g_gl_ssbo_cache[8]`（SSBO 绑定点）。当 `rhi_texture_destroy`/`rhi_cubemap_destroy`/`rhi_sampler_destroy`/`rhi_buffer_destroy` 调用 `glDeleteTextures`/`glDeleteSamplers`/`glDeleteBuffers` 时，GL 会将所有引用该对象的绑定点恢复为 0，但缓存仍持有旧 GL name。若 GL 复用该 name 分配新对象，缓存会误判为“已绑定”并跳过 `glBindTexture`/`glBindSampler`/`glBindBufferBase`，导致新对象未实际绑定到 GPU。

此外，`g_gl_ssbo_cache` 原为 `rhi_cmd_bind_storage_buffer` 内的 `static` 局部变量，无法从 `rhi_buffer_destroy` 访问。已提升为文件作用域（与 R77-1 的 `g_tex_cache`/`g_sam_cache` 一致）。

**修复**：
1. 将 `g_gl_ssbo_cache` 从 static 局部提升为文件作用域变量
2. `rhi_texture_destroy`：遍历 `g_tex_cache[16]`，匹配 `td->gl_tex` 的条目置 0
3. `rhi_cubemap_destroy`：同上
4. `rhi_sampler_destroy`：遍历 `g_sam_cache[16]`，匹配 `sd->gl_sampler` 的条目置 0
5. `rhi_buffer_destroy`：遍历 `g_gl_ssbo_cache[8]`，匹配 `bd->gl_buf` 的条目置 0

**影响文件**：rhi_gl.c

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## Round 107

### R107 审查范围

物理系统（CCD 积分、BVH broadphase、地板 clamp）、角色控制器（capsule 碰撞、wall slide、step-up）、动画系统（IK solver、骨骼世界变换、blend）、音频流管理（槽位分配/释放）、网络包序列化（边界检查）、网络复制（序列号、ack）、地形系统（staging buffer 边界、区域重建）、任务系统（work-stealing deque、全局提交队列）、脚本系统（Lua pcall 错误处理）、Pool allocator（自由链表、块边界验证）。

### R107 审查结论（无需修复）

1. **物理 CCD 积分**：`integrate_body_ccd` 正确使用 `ccd_sweep_static` 做射线扫描，clamping motion at first static hit。地板 clamp 使用 `b->half_extent.e[1]`，该字段在 `physics_body_create_sphere`/`physics_body_create_capsule` 中已正确设置为包围盒半高（sphere: radius, capsule: half_height + radius）。
2. **角色控制器**：`char_slide_resolve` 最多 6 次迭代分离，BVH AABB 查询候选体（上限 64）。`character_update` 三步移动（垂直→水平→step-up）逻辑正确。`physics_sweep_test` 预计算 inv_delta 和 axis_parallel 标志优化。
3. **动画 IK solver**：`anim_ik_two_bone` 使用 law of cosines + atan2f 解析式求解，正确处理退化情况（零长度骨骼、共线 pole 向量）。`skeleton_compute_world_transforms` 的 `joint_parents[i] >= i` guard 是防御性设计，对良构骨骼正确，对畸形骨骼降级为根关节。
4. **网络包序列化**：所有 `packet_read_*`/`packet_write_*` 函数通过 `packet_can_read`/`packet_can_write` 做边界检查。`packet_read_bytes` 失败时清零输出缓冲。`packet_parse_header` 验证最小 header 大小。
5. **网络复制**：`net_repl_parse_payload` 从包中读取 count 后 clamp 到 `max_count`。reliable pending retry 通过 `seq <= last_peer_ack` 判断是否已确认。
6. **地形系统**：`terrain_rebuild_region` staging buffer 容量为 `grid_size * 8` floats，单行最多 `grid_size` 顶点，无溢出。区域坐标在入口处 clamp。`terrain_flatten` 使用 grow-only 持久缓冲。
7. **任务系统**：Chase-Lev work-stealing deque 实现正确，全局提交队列在 mutex 保护下 detach。pool 溢出时 heap 分配 + 正确释放。`task_wait`/`task_wait_handle` 等待时帮助执行任务而非空转。
8. **脚本系统**：Lua `lua_pcall` 错误处理正确，`lua_pop` 清理错误对象。mtime 热重载避免不必要 I/O。
9. **Pool allocator**：`pool_acquire` 检查 `free_list` NULL，`pool_release` 检查 ptr NULL，`pool_owns` 验证块边界和对齐。

### R107-1 (CORRECTNESS): 音频流槽位泄漏

**问题**：`audio_stream_open` 和 `audio_stream_open_3d` 通过 `stream_alloc_slot` 从自由链表分配槽位后，若 `audio_play_streamed` 返回 0（失败），直接 `return -1` 而未将槽位归还自由链表。每次打开失败永久泄漏一个槽位，`AUDIO_STREAM_MAX_SOURCES` 次失败后所有槽位耗尽，无法再播放任何流音频。

**修复**：在两个函数的 `sid == 0` 失败路径中，将已分配的 `idx` 槽位归还自由链表：
```c
mgr->free_next[idx] = mgr->next_free;
mgr->next_free = idx;
```
与 `audio_stream_stop` 中的归还逻辑一致。

**影响文件**：audio_stream.c

**验收**：全部 23/23 测试通过。BVH/VK/GL 三个构建路径均编译成功。

## 构建与回归命令

```bash
# Vulkan
cmake -S engine -B engine/build-vk -DENGINE_VULKAN=ON -DENGINE_BUILD_TESTS=ON
cmake --build engine/build-vk -j8
cd engine/build-vk && ctest --output-on-failure

# OpenGL
cmake -S engine -B engine/build-gl -DENGINE_VULKAN=OFF -DENGINE_BUILD_TESTS=ON
cmake --build engine/build-gl -j8
cd engine/build-gl && ctest --output-on-failure
```
