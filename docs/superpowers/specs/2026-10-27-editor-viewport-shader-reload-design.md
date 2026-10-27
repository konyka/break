# Editor viewport shader 热加载设计

日期：2026-10-27  
分支：`sdd/editor-shader-reload`  
状态：设计已确认，待详细实施计划

## 1. 目标与边界

本子项目为 scene editor 的 3D viewport 增加 shader 热加载。实际消费者是 `engine/apps/editor/editor_viewport3d.c` 独占的 `editor_color` pipeline；它绘制 entity 代理立方体和 gizmo。默认 Vulkan 不变，OpenGL 永久保留为最终降级路径和渲染对比基准。

交付目标：

- 监视当前 RHI backend 对应的 vertex/fragment shader，外部修改后重新构建候选 pipeline。
- 新 shader、pipeline、bindings 和 uniform ABI 全部有效才发布；失败保持完整旧状态。
- 初次加载失败后，修复文件或按 `Ctrl+Shift+R` 可以恢复，不再被 sticky failure 永久阻断。
- 复用 Runtime Core 的 VFS、worker、staging 和 owner-thread commit，不增加线程池、RenderThread 或 UI 框架。
- 保持普通 `R`/`Shift+R` 的 Scale 工具语义；手动重载只排队，不在按键回调里编译 GPU 资源。

本阶段不交付纹理热加载。勘察确认 viewport 没有材质或纹理消费者，FBO color texture 只是 viewport 的内部输出，不能冒充可热加载资产。纹理的后续顺序是：

1. asset browser 选中真实图片文件的预览；
2. 预览自己持有 `RHITexture`，经 `my_vgcanvas_break_rhi_blit_texture` 绘制；
3. 独立子项目实现当前预览文件的 watch、worker decode、owner swap 和失败保旧。

不得通过清空 `my_image_cache_clear()` 实现纹理热加载：它只清 CPU bitmap cache，不会正确失效 Break RHI canvas 的 GPU bitmap cache。

## 2. 方案比较

### A. viewport 独立 shader owner，复用一个 Runtime Core coordinator（采用）

新增 `BreakEditorShaderReload`，由 `BreakEditorViewport3D` 持有。一个 coordinator 分别请求 vertex 和 fragment，owner 聚合两份 staging 后构建一对候选 GPU 状态。

优点：不改 scene hot reload 的 dirty/undo/hash 保护，不改 Runtime Core ABI，现有测试接缝可复用。代价是需要明确的 pair attempt、两份请求状态和 trailing change。

### B. 扩展 `BreakEditorHotReload` 同时管理 scene 和 shader

拒绝。现有对象只有一个 scene request，并在 `set_scene` 时停止 watcher/VFS/coordinator。混合资源会耦合场景切换和 GPU 生命周期，还会把文档 dirty/undo 规则错误地带入 shader。

### C. 给 Runtime Core 增加通用多文件 batch request

拒绝作为本阶段搭车改造。长期它可服务材质依赖图，但当前需要改 coordinator slot、worker、commit ABI、shutdown 和核心测试，远超一个 viewport shader 消费者的需要。

## 3. 所有权与组件

- `BreakEditorViewport3D` 继续独占 live pipeline、bindings、uniform locations、cube VBO 和 FBO。
- `BreakEditorShaderReload` 拥有 watcher、VFS、一个 Runtime Core coordinator、两个 request handle 和最多两份 owned staged bytes；不拥有 live GPU 资源。
- viewport 在 live GPU 对象销毁前销毁 shader reload owner。shell 仍在 RHI device 之前销毁。
- `break_editor_shell_tick` 驱动 reload，发生在 `break_ui_frame_begin` 之前。不得在 worker、FileWatcher callback 或当前 command buffer 录制期间创建、替换或销毁 RHI 资源。
- FileWatcher callback 只记录 `pending` 和计数。worker 只读 VFS 并验证 bounded bytes；不读取 viewport、widget、document 或 RHI handle。
- reload 结果通过现有有界 editor console 和只读 stats 暴露；logger 由 shell/viewport 接线，不把 document 或 widget 所有权交给 worker。
- `engine/src/asset/hotreload.c` 的现有同步 API 和游戏 renderer 调用方保持不变。

当前 editor 的 shell 与 render owner 是同一线程。本设计不虚构独立 RenderThread，也不声称实现了异步 GPU compile。编译/链接和现有 RHI 的销毁等待可能阻塞 shell，属于开发期编辑器的明确成本。

## 4. 路径解析与监视

首次加载与热加载必须共享一个 resolver，保持现有优先级：

1. 非空 `BREAK_SHADER_DIR`；
2. 当前目录；
3. `engine/`；
4. `../engine/`；
5. `../../engine/`。

逻辑名仍为 `shaders/editor_color.vert` 和 `.frag`，由真实 device capabilities 经 `shader_variant_path` 选择 `_vk` 变体。`BREAK_SHADER_DIR` 指向 engine 根目录，不是 shader 文件或 `shaders` 子目录。

resolver 成功时同时返回 bytes 和实际路径。所有拼接都检查长度；不得把截断路径当成另一个文件读取或监视。

Runtime Core 请求使用上述逻辑名。VFS 按相反优先级挂载候选根，最后挂载 `BREAK_SHADER_DIR`，与 VFS 从后向前搜索的行为一致；空前缀对应 `.`。coordinator 创建后，候选根和环境取值固定，worker 不再读取环境变量。

watcher 登记有界候选路径，包括当前未命中的路径，以支持缺失文件后来出现。活动高优先级文件消失时，下一轮按相同优先级解析，允许回退到仍存在的低优先级文件。无法建立 watcher 时，手动重载仍可使用同一 resolver；路径超出 VFS/coordinator 限制则明确拒绝，不截断。

watcher 是有损提示，不是文件事务日志。整秒 mtime、rename、overflow 和各平台差异不作超出现有 PAL 的保证；`Ctrl+Shift+R` 是确定性兜底。

## 5. Pair staging 与提交流程

同一时刻最多一个 pair attempt 在途：

```text
file event / Ctrl+Shift+R
        -> pending = true
        -> vertex request + fragment request
        -> Runtime Core worker: VFS read + pure validation
        -> owner commit: copy each staged source into attempt-owned storage
        -> poll and consume both terminal handles
        -> 两侧均成功才构建完整 GPU candidate
        -> publish candidate -> retire old pipeline/bindings
        -> trailing pending 时开启下一轮
```

详细规则：

- vertex 和 fragment 是两个真实 path；不得伪造一个 pair path 传给 VFS。
- 每个 attempt 开始时释放上一轮的 staging。第一份到达的 commit 必须复制 bytes，不能保存 coordinator 的 borrowed pointer。
- validate 只检查字节形状和预算，不写 owner 状态。每个 shader 不超过 `SHADER_MAX_FILE_BYTES`；Runtime Core 的总量、队列和 allocation 失败仍走原有终态。
- commit hook 只收集 source。两个 request 都已 poll 到成功终态后，才在 shell tick 中调用 candidate builder；任何一侧失败都不编译另一侧来冒充一对成功。
- 一个 attempt 期间的新文件事件和手动请求只设置 trailing `pending`，不得覆盖当前 staging。当前 attempt 两侧都收尾后才能启动下一轮。
- 空 attempt、重复 terminal poll、取消、shutdown 和路径失败都必须释放对应 handle/scratch；每个用户可见 attempt 只记一次成功或失败，不能把 coordinator 的两个 `COMMITTED` 当成两次 shader 成功。
- 保证的是 live GPU 状态成对替换，不是两个磁盘文件在同一瞬间的原子快照。保存过程中产生的暂时不匹配会失败保旧，后续 trailing attempt 负责收敛。

容量保持有界：一个 worker、最多两个活动文件请求、两个 source staging；request/event/commit 小容量配置参照 scene reload 的 4 槽，不建立无界缓存。

## 6. GPU candidate 与失败保旧

把 `vp_lazy_init` 的 GPU 构建部分提取为事务式 candidate builder。初次加载与 reload 使用同一个 builder：

1. 从 memory source 创建 VS 和 FS；清理所有已创建的临时 stage。
2. 使用现有 `RHIPipelineDesc`：position-only `vertex_stride=12`、`disable_culling=true`，不套用游戏旧 helper 的 `uses_textures=true`。
3. 创建新 pipeline，再创建新 bindings。
4. `u_mvp` 和 `u_color` 都 resolve 成功才继续；compile/link 成功但 ABI 不符仍是失败。
5. 若初始失败导致 cube VBO 尚不存在，先构建 candidate VBO；已有 VBO 和 FBO 不随 shader 重建。
6. 全部成功后，一次性发布 pipeline、bindings、locations 和可能的新 VBO，设置 READY。
7. 发布后销毁旧 pipeline/bindings。初始失败路径的部分 candidate 也必须全部回收，修复当前 `vp->device` 晚赋值导致的清理缺口。

失败时 live pipeline、bindings、locations 和已有 VBO 完全不变。已有 READY 状态时不得因为一次坏 revision 改成 INIT_FAILED；从未成功时保持 INIT_FAILED，但允许显式事件再次尝试。无新事件时不得每帧重试和刷日志。

reload 的 compile/swap/destroy 在 frame 外执行。当前 Vulkan `rhi_pipeline_destroy` 会等待既有 frame fences，但该等待跳过正在录制的当前帧，因此 frame 外是必要条件；OpenGL 的 cache invalidation 也必须在同一 render-owner/context 线程执行。本设计不新增全设备 idle，不宣称 device-lost 下额外安全保证，也不支持中途 device migration。

现有首次 lazy init 可保留在 render 路径；本合同特别约束新增 reload 不得进入 command recording。后续若统一移动首次初始化，应另以测试证明兼容，不作为本阶段必需重构。

## 7. 快捷键、状态与关闭

- `Ctrl+Shift+R` 只调用 request API，设置 pending；真正的读取、编译和交换仍走同一 coordinator 路径。
- chord 必须精确匹配 Ctrl+Shift，不把 Shift 全局加入现有字母匹配规则；普通 `R` 和 `Shift+R` 仍为 Scale。
- stats 至少区分 watching、busy、pending attempts、成功、失败和最后一次结果，供 headless 测试与现有 render debugger/console 使用。
- destroy 先停止 watcher，再有界停止 coordinator，之后销毁 VFS 和对象。worker 超时则保留/leak 有界上下文并报告，不得释放仍被 worker 引用的 VFS/callback state。
- scene 切换不重启 shader owner；scene document 的 dirty/undo 不参与 shader 决策。

## 8. TDD 与验收

先写失败测试，再实现。复用 `test_editor_shell` 的真实 FileWatcher/VFS/Runtime Core 和 `rhi_stubs.c`，通过仅测试构建可见、显式启用的 fake RHI 覆盖 shader/pipeline/bindings/buffer 生命周期；默认 stub 行为保持不变，不在生产代码导出 test hook。

至少覆盖：

- 有效 A -> B 成对替换，旧 pipeline/bindings 恰好销毁一次，VBO/FBO 不重建；之后 B -> C 仍可执行。
- VS compile、FS compile、link、bindings allocation、缺少 `u_mvp`/`u_color` 失败时完整保留 A，candidate 无泄漏。
- 初始缺文件/坏 shader 可经文件事件和手动请求恢复，成功后创建缺失 VBO；无事件不重试。
- 单侧 staging 到达时不编译；worker 已读但 owner 未收尾时 RHI create 计数为零。
- attempt 在途时连续修改产生 trailing attempt，最终使用最新 pair，不混合不同 attempt 的 bytes。
- `BREAK_SHADER_DIR` 的实际命中路径被监视，而不是猜测 cwd；缺失后创建、删除后回退、超长路径和非法输入有界处理。
- `Ctrl+Shift+R` 只排队，普通 `R`/`Shift+R` 不变。
- request 在途时按两种支持的顺序 teardown，无 UAF/double free；logger 和 shell 生命周期有效。

构建成员更新覆盖 production `editor`、`test_editor_shell` 和 `fuzz_editor_remote`，以及现有 target contract。没有新增文件格式解析器，不为了本阶段虚构 fuzz target；既有 editor remote fuzz 必须继续通过。

验证顺序：

1. 新测试确认 RED，再实现到 GREEN，并做至少一次针对性 mutation 检查。
2. `build-current-gl`、`build-current-vk`、`/tmp/mb` 和 Snowflake ON 树构建并运行 `ctest -LE 'graphics|fuzz'`。
3. ASan+UBSan、TSan 重跑 editor shell 和相关 RHI/Runtime Core 测试；必要时重复运行以覆盖 worker/teardown 交错。
4. 从 `engine/` 启动真实 editor，分别验证默认 Vulkan 和显式 OpenGL：有效修改生效、坏修改保留旧版、修复后恢复、手动 reload 生效。记录真机证据级别；若只有日志/状态，不宣称视觉或 GPU 正确性。
5. 独立代码审查后修复并复验，文档补充交付事实，再以 `--no-ff` 合并到本地 master。

Windows/macOS 运行时、Metal/D3D12、shader `#include` 依赖、通用材质依赖图、scene-faithful renderer 和纹理热加载均不在本次完成声明中。
