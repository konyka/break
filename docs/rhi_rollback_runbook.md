# RHI 回滚与 Device-Loss Runbook

## 回滚触发条件（任一成立即启动回滚评估）

- 合并后任一平台 headless 套件（`ctest -LE "graphics|fuzz"`）在 CI 上转红且无法在当日修复；
- `GPU_RUNTIME` 证据行对应的 CI lane 连续两次失败且排除基础设施原因；
- 后端拆分/迁移导致某平台可执行文件链接失败且当日无修复路径。

## 回滚步骤

1. 定位引入 commit（`git log --oneline` + CI history），优先 `git revert` 最小范围 commit；
2. 回滚后在 `docs/rhi_backend_evidence.md` 对应行记录等级回退与原因（降级也是证据变更，必须留收据）；
3. 重新跑两个本机构建目录的 headless 套件确认绿；
4. 在规格 §7 风险登记中新增或更新对应风险条目。

## Device-loss 处置（运行时）

- `RHI_RESULT_DEVICE_LOST` 是 sticky latch（`rhi_device_lost`）：一旦出现，所有阻塞等待 fail-fast，应用层应收束退出而非重试。
- Windows D3D12 路径（计划 D）需采集 DRED；Vulkan 路径记录 validation 计数（`rhi_vk_validation_message_count`）。
- 已知异常隔离：NVIDIA 616.56 混合 GPU 上的 `VK_ERROR_DEVICE_LOST` 与 Hi-Z {1,1} 异常不作为源码修复依据；必须在健康设备独立复现后才立项（规格 §7）。

## 禁止事项

- 禁止把编译成功（COMPILED）当作 GPU_RUNTIME 证据上报；
- 禁止以删除/跳过测试的方式让套件转绿；
- 禁止在未冻结的临时 artifacts（`.scratch-vkprobe/`、`.tmp/` 等）上建立回滚依赖。
