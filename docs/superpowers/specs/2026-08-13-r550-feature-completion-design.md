# R550 特性收口 + 性能统一轮 — 实施计划

## 背景（盘点结论）

`docs/Implementation_Status.md`（R1–R549）+ 源码核查后，真实剩余缺口按性能优先级：

1. **5 个后处理 pass 写了 FBO 但从不合成**（开启即 100% 浪费 GPU）：
   - `ssr_apply`（main.c:7227-7230，输出 `ssr_sys.ssr_fbo`，`ssr_get_texture` 无消费者）
   - `ssgi_apply`（main.c:7232-7235，输出 ssgi_fbo→blur_fbo，无消费者）
   - `volumetric_apply`（main.c:7213-7218）、`lens_flare_apply`（main.c:7220-7225）、`contact_shadow_apply`（main.c:7203-7211）——三者同样写私有 FBO 无人消费
   - 对应 main.c:2558-2562 五个 `*_enabled = false` 注释自证 "never composited"
   - **合成惯例已存在**：god_rays（main.c:7391-7396）shader 内部采样输入色并混合，写自身 FBO，main.c 把链尾指到 `gr_sys.fbo.color_tex`
2. **R445 悬案**：showcase 场景 GPU unified cull 把 11 个 mega cmd 全标不可见、每帧走回退（unified 单 dispatch 收益没拿到）
3. **motion blur 近 no-op**（R446 实测：模糊跨度恒 ≈1px，与速度无关）—— `renderer/motion_blur.c` + `shaders/motion_blur*.frag`
4. **clustered 光照 near/far 硬编码 0.1/100**（lighting.c:156-158, 358-359），不随相机
5. **VALIDATION GATE 在 Release 因 `#ifndef NDEBUG`（rhi_vk.c, R439）空转**（test_vulkan.c:2150 "gate skipped"）
6. **文档矩阵过时**：Implementation_Status.md 728 行（GL cubemap RGBA8、compute sampler）、737 行（"前向无 velocity"——R21-2 已有相机速度）、738 行（auto-exposure/cinematic 多 pass 链——R13-3/R19-1 已合并）

刻意不做（保持挂账记录，不动）：真 bindless、物理旋转模型（大改）、macOS 实测（无环境）、Wayland 真实 compositor 验证、stb_truetype 加固、GPOS 取舍项。

## 环境事实

- 本机有 GPU（vulkaninfo OK、/dev/dri 存在、DISPLAY=:0），graphics 测试可跑（docs 载 `-L graphics` 1/1 先例）
- 构建惯例：Debug GNU + Clang/LLD Release 双构建，非图形 ctest 40/40（R549 口径）；shader 改动需 glslang 验证；遵循 TDD（先红后绿 + 反向验证）
- 远程：origin = git@github.com:konyka/break.git（用户已明确要求提交并推送）

## 实施项（R550，按序执行）

### R550-A：SSR/SSGI/volumetric/lens_flare/contact_shadow 五路合成接线
按 god_rays 惯例（shader 内合成 + main.c 链尾替换），逐 pass：
- 各 `*_apply` 增加"链入色"纹理参数；shader 增加对应 sampler（VK 版同步 push/uniform 映射，走 `rhi_pipeline_get_uniform_location` 既有机制）
  - volumetric / lens_flare / ssgi：加法混合（光贡献叠加）
  - ssr：按反射置信度 alpha lerp
  - contact_shadow：乘法变暗（仅影响太阳直射项近似——场景色乘以 mask，注释说明近似）
- main.c：5 处 `*_apply` 调用后把下游链纹理（TAA 输入处的 `scene_fbo.color_tex` 引用，main.c:7237 起）指向合成输出；默认仍关（成本取舍保留），但 UI 预设/按键开启后真实生效；更新 main.c:2558-2562 注释
- 测试：`test_shader_io` 增双后端 shader 契约断言（新增 sampler/uniform 存在，R447 先例）；GPU 上 BREAK_SCREENSHOT A/B 像素证据（开/关对比非零差异）
- 风险：合成新增 sampler 可能触动 VK 描述符布局/push 范围——逐项 glslang + test_vulkan VALIDATION GATE 验证

### R550-B：showcase unified cull 全剔悬案（性能最高优先）
- GPU 复现：VK demo 跑 showcase，加/用既有观测（`g_fwd_mega_taken` main.c:6648、unified 计数日志）确认 11 cmd 全不可见
- 怀疑方向：unified 包围球上传与 showcase 程序化网格变换/AABB 不匹配（R445-B 网格 bake 顺序）
- 修复后验证：unified 路径实际命中（fallback 计数为 0）、TEST 9/10/11/12 全绿、VALIDATION GATE 0
- 若根因超出一轮可修范围，如实记录最小复现与定位结论，不硬修

### R550-C：motion blur 速度响应修复
- 审查 `motion_blur*.frag` 速度重建（depth+prev_vp）与 strength 缩放；R446 实测跨度恒 1px → 找根因（疑似速度未按屏幕尺寸/帧率缩放或被 clamp）
- 修复为跨度 ∝ 像素速度 × strength（上限 clamp 防拖影爆炸）
- 验证：BREAK_CAM_SPIN 脚本化摆动 A/B 截图，跨度随转速单调增长；glslang 双后端

### R550-D：clustered near/far 随相机
- `light_system_cull`/`light_system_cull_gpu` 改收 near/far 参数（或 `light_system_set_depth_range` API），调用方（main.c / deferred.c）传相机 `near_plane/far_plane`；LUT dirty 机制复用
- 测试：test_lighting（若存在）或纯函数断言 LUT 边界随参数变化；全量回归

### R550-E：VALIDATION GATE Release 修复
- rhi_vk.c debug messenger 守卫从 `#ifndef NDEBUG` 改为显式宏（如 `ENGINE_VK_VALIDATION`，Debug 默认开）；test_vulkan 目标 CMake 定义该宏，保证门禁在所有构建类型生效
- 验证：Release 构建 test_vulkan 不再打印 "gate skipped"，0 消息通过

### R550-F：文档收口
- 修正矩阵 728/737/738 三处过时表述（对照源码现状）
- Implementation_Status.md 头部新增 R550 轮次条目（分项、验证口径、如实记录未修项）
- 设计/计划存档 `docs/superpowers/specs/2026-08-13-r550-feature-completion-design.md`
- Build_Guide 如有新 env/行为变化同步

## 执行与验证流程

1. 依赖关系：A/C/D/E/F 文件交集小，但 A 与 B 都碰 main.c → 顺序执行：B（调查先行，改动可能最小）→ A → C/D/E 可并行委派 → F 最后
2. 每项遵循仓库 TDD 口径：先写失败测试/复现 → 修复 → 反向验证 → 定向测试 → 双构建非图形 ctest 全绿 →（涉 GPU 项）`-L graphics` + VALIDATION GATE
3. 每项单独 commit（`fix(R550-x): ...` / `feat(R550-x): ...`，对齐 git log 风格）
4. 全部完成后：`git diff --check`、推送 origin（用户已授权）
5. 委派 coder 子代理执行各工作流，主代理串行协调与终验

## 完成判据

- 双构建非图形 ctest 全绿（≥40/40，新增测试递增）+ graphics 1/1 + VALIDATION GATE 0
- 5 个 pass 开启后有像素级可见效果（A/B 截图证据）
- showcase unified 路径不再全剔（或有如实记录的定位结论）
- motion blur 跨度随速度变化（截图证据）
- 文档三处过时修正 + R550 条目入库，git 推送到 origin

## 执行结果（回填）

全部 6 项完成并各自独立 commit（执行顺序 B → A → C/D → E → F）：

- `a6cd0f8` fix(R550-B)：根因与初判不同——GL 下 Hi-Z chunk 生成用 BASE/MAX clamp 绑原纹理对象触发 Mesa feedback 守卫，mip 4–8 恒 0 导致 showcase unified 全剔；改单 mip `glTextureView` 后 58/59 帧 11/11 可见，反向验证复现。
- `4dfa087` feat(R550-A)：五路合成全部按 god_rays 惯例接线；SSR 零新 sampler；SSGI 末级新增 ssgi_blur 双后端 shader；GPU A/B 像素证据（GL ssr mean|Δ|=12.77 等）。
- `fa0ce0a` fix(R550-C)：步长缺速度模长；修复后 spin 0→20°/帧 速度场亮度 7.14→226.69 严格单调。
- `80c6573` fix(R550-D)：`light_system_set_depth_range`，test_lighting +4（19/19）。
- `3a4aec2` fix(R550-E)：显式运行时开关 + `ENGINE_VK_VALIDATION`；顺带修复存量 3 条 TRANSFER_SRC（offscreen FBO 缺 usage），Debug/Release 门禁均 0。
- `38d27c2` fix(R550-F)：`audio_bus_valid` 容量守卫，GNU Release 构建恢复。

遗留（如实记录，见 Implementation_Status.md R550 条目）：GL 粒子 compute `GL_INVALID_OPERATION` 与每帧一条 0x502（另立案）；VK lens flare 静态视角 Y 方向疑点；VK 首帧 unified 全 0 瞬态；spin0 伪速度（楔形物体 depth 疑点）。
