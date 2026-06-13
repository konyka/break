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
