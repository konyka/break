# Scene Temp Path Truncation Design

## 根因证据

Windows 实机在 master `c583b9a0` 上稳定复现 `failed_load_keeps_previous_scene` 失败。只记录长度和相等性的临时诊断得到 `keep_len=63,63 equal=1`：`pa[64]` 与 `pb[64]` 被长 TEMP 路径截断为同一字符串。随后 B 的保存覆盖了 A，损坏 B 又使 A 不可加载，所以第一次 `scene_load_binary(wd, &dst, pa)` 返回 false。产品序列化实现不是这次失败的根因，诊断改动已恢复。

## 修复边界

本次只修改 `failed_load_keeps_previous_scene` 的测试夹具：

1. `pa` 和 `pb` 从 64 字节扩为 512 字节，匹配 `test_tmp` 的常规 Windows 路径规范化缓冲。
2. 在任何文件写入前加入 `strcmp(pa, pb) != 0` 断言。若以后再次碰撞，测试会在覆盖文件之前明确指出夹具问题。
3. 不修改 `test_tmp`、`test_tmp_root`、产品代码、序列化格式或其他测试语义。

共享 `test_tmp` 的静默截断、其他小缓冲调用和 Windows `norm` 的内部截断属于独立整改。不能在本项目加入全局 `abort()`：现有其他 64 字节调用会在目标用例之前终止，使完整 Windows 场景验收无法到达修复点。

## TDD 验收

先保留旧实现上 Windows 的 `failed_load_keeps_previous_scene` 失败及 `keep_len=63,63 equal=1` 证据，再只修改两个缓冲和 distinct 断言。相同 Windows 环境下完整 `test_scene_serial` 必须从 121/122 变为 122/122。

另验证 `test_runtime_io`、`test_runtime_reload`、`test_core_app_diagnostics`，完整 Vulkan/OpenGL 和 sanitizer focused。所有平台既有条件 skip 保持不变，不推断无关 Windows 平台或 GPU 用例已修复。

## 文档与交付

追加测试基础设施说明，保留这次 Windows 证据、最小修复范围、共享截断整改和其他未解决问题。独立评审后同步 `origin/master`，直接推送 `master`，不创建 PR，并核验最终 CI、arm64、Windows D3D12 和 Proton。
