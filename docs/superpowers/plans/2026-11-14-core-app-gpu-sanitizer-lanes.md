# core_app GPU 用例在 sanitizer 树中通过

## 背景

`test_core_app_gpu_vulkan`、`_opengl`、`_fallback`（标签 `gpu`）在 ASan+UBSan 树和 TSan 树中失败。CI 用 `-LE "graphics|fuzz|gpu"` 排除它们，所以这个问题只在本机真实设备上出现。

## 原因

1. 引擎缺陷：`vk_retire_collect_budget`（`engine/src/rhi/rhi_vk.c`）在 `retired_count == 0` 时直接返回。`retired` 数组分配以后，如果帧内回收已把计数降到 0，`vk_shutdown` 里的 `vk_retire_collect(vk, true)` 就不会释放数组本身。启动时 `rhi_set_vsync` 触发 swapchain 重建，第一次 push 分配了 64 项（1536 字节），之后每次运行都泄漏这一块。
2. 第三方：NVIDIA 驱动的进程级缓存（`libnvidia-glcore.so`、`libnvidia-glsi.so`，以及经 glvnd 加载、退出前被卸载的 `libEGL_nvidia.so` 的 GL 模块）。
3. 第三方：Khronos validation layer 自己的队列线程（`vvl::Queue::ThreadFunc`）与 `DestroyFence` 之间的竞争。Debug 构建默认打开 validation。

## 步骤

1. 修复 1：`all` 为真且数组仍在时继续执行，走到释放数组的分支。
2. 只对这三个 GPU 用例、只在 Linux 的 sanitizer 树里加按模块名的 suppression：
   - ASan：`VK_LOADER_DISABLE_DYNAMIC_LIBRARY_UNLOADING=1`，`LSAN_OPTIONS=suppressions=engine/tests/core_app_gpu_lsan.supp:fast_unwind_on_malloc=0`。关闭 fast unwind 后，栈才能回溯到仍处于映射状态的 `libEGL_nvidia.so` 帧。
   - TSan：`TSAN_OPTIONS=suppressions=engine/tests/core_app_gpu_tsan.supp`，只匹配 `libVkLayer_khronos_validation.so`。
3. 验证：两棵 sanitizer 树中 GPU 用例都是 3/3。撤掉修复 1 后，Vulkan 用例在 suppression 下仍会判红，报告 `vk_retire_push` 的 1536 字节泄漏，说明 suppression 没有掩盖引擎代码。
4. 文档追加、normal 全量、提交、推送。
