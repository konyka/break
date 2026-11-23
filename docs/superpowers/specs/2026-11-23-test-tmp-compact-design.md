# Test Temp Compact Fallback Design

## 现状

`test_tmp` 在大量测试中被调用。Windows 完整 TEMP 路径和调用方缓冲都可能使最终 `snprintf` 截断；Windows `norm[512]` 还存在第二层静默截断。直接 `abort()` 会让大量原本仅路径过长的测试提前失败，不能作为默认行为。已完成 scene 子项目只扩大了目标 `pa/pb`，共享风险仍存在。

## 目标行为

保持 `test_tmp(char *buf, size_t cap, const char *name)` 的签名和正常路径结果不变：

1. 完整路径能够容纳时，继续使用当前格式和位置，不做额外转换。
2. 只有最终 `snprintf` 截断时，才允许紧凑回退：如果名称不含 `/` 或 `\`，只把叶文件名替换为 `break_<name-hash>_<pid>`，仍位于未截断的原 TEMP 根目录。名称哈希使用 32 位 FNV-1a，PID 保持进程隔离。
3. Windows `norm[512]` 自身溢出不是原根，禁止进入哈希回退；`test_tmp` 和 `test_tmp_root()` 都必须立即打印 `TEST PATH TRUNCATED` 并 `abort()`，不继续 I/O。
4. `test_tmp_root()` 的签名和根含义不变，VFS 挂载仍指向原实际目录；不采用 `./` 回退。
5. 含父目录的名称不做哈希，以免把“父目录不存在”的负向测试变成可写路径。任何此类最终路径截断都明确失败。
6. `cap < 32`、负 `snprintf` 返回值、或哈希结果仍无法容纳时，打印 `TEST PATH TRUNCATED` 并 `abort()`。其他情况不引入全局提前终止。
7. 不修改产品代码、序列化格式或已有场景 fixture，不依赖 `GetShortPathNameA` 的可选平台行为。

该设计只处理叶文件名，保持目录所有权和负向路径语义，同时消除静默使用同一截断路径的风险。

## TDD 覆盖

在 `test_fork_deadline` 增加四例，达到 14/14：

- `tmp_rejects_truncated_path`：31 字节缓冲和长名称，旧实现正常退出，期望新实现为 SIGABRT，父进程用有界 wait 回收。
- `tmp_truncation_uses_distinct_compact_fallbacks`：32 字节缓冲和两个长名称。旧实现截成同一路径；新实现必须分别得到 `/tmp/break_8073d8d7_<pid>` 与 `/tmp/break_8173da6a_<pid>`。另断言正常短名称路径保持原格式。
- `tmp_rejects_truncated_parent_path` 和 `tmp_rejects_truncated_backslash_parent_path`：分别含 `/` 与 `\` 的长名称，即使哈希叶名可容纳也期望 SIGABRT，防止改变父目录语义。

在 `test_scene_serial` 增加 Windows 专项：容量按 `R + 17 + P` 计算并下限为 32，其中 `R = strlen(test_tmp_root())`，`P` 是 PID 十进制位数。该容量足以容纳哈希回退，但旧完整长名会多 29 字节并截断，因此在不同根长度下都能区分旧 RED 和新 GREEN。回退路径不含 NUL 的长度为 `R + 16 + P`，必须严格小于上述容量，不能断言所有情况下都等于 `cap - 1`。旧实现产生同一路径；新实现必须得到根目录下不同且以 `break_` 为叶名前缀的路径。无需修改 TEMP，也不输出账户路径。

在 `test_async_loader` 增加真实 VFS 读取：使用同样的容量公式，断言独立计算的哈希叶名后，实际创建文件、挂载 `test_tmp_root()` 并请求该叶名，验证回退后的文件确实可读，而不只是字符串不同。

新增 Windows 专用 `test_tmp_abort` 探针，以 600 字节 TEMP 分别调用 `test_tmp` 和 `test_tmp_root()`。CMake 脚本要求非零退出及 `TEST PATH TRUNCATED` 标记；旧实现返回 0 形成 RED，新实现明确失败形成 GREEN。这样 `norm` 溢出不会伪装成成功的截断根。

最终目标为 `test_fork_deadline` 14/14、Windows `test_scene_serial` 123/123、`test_async_loader` 19/19，以及两个 Windows 溢出探针通过。随后运行相关 consumer、完整 Vulkan/OpenGL、ASan+UBSan、TSan 和远端矩阵。

## 交付

追加根因、回退格式、最小缓冲规则、目录语义、动态容量公式和实测证据。独立评审后同步 `origin/master`，直接推送 `master`，不创建 PR，并核验最终 CI、arm64、Windows D3D12 和 Proton。
