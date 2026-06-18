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
