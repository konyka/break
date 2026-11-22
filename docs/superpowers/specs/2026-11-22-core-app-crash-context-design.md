# core_app 崩溃上下文摘要接入设计

日期：2026-11-22

## 目标与现状

`break_crash` 已提供处理器安装、4 KiB context-blob、`BreakCrashSummary` 格式化与真实崩溃记录测试，但应用没有自动填写 GPU/RHI、网络和输入摘要。`core_app` 已拥有这些事实，并且 `CoreAppThread` 是它们唯一允许的可变状态所有者。

本子项目交付一条显式启用的真实应用路径：运行 `core_app --crash-context DIR ...` 时安装现有崩溃处理器，在运行期间持续发布脱敏摘要，退出时解除安装。默认运行不安装处理器、不创建 spool、不调用摘要发布；不上传任何记录。

不包含：上传接线、生产更新或收集服务、Windows SEH/VEH、DWARF CFI、跨线程状态读取、原始输入文本或坐标采集、网络地址或凭据采集。`core_app_runtime`、`core_app_asset_bake`、`engine`、既有演示和编辑器不直接依赖 `break_crash`。

## 方案比较

1. **中性快照回调 + 独立诊断模块（采用）**：runtime 通过配置中的借用 hooks 发布 POD 快照；`core_app_diagnostics` 独占 `break_crash` 依赖并负责安装、格式化与解除。默认回调为空，测试可以分别验证真实运行快照与真实崩溃记录。
2. **runtime 直接调用 `break_crash`**：入口较少，但 `core_app_runtime` 及其所有使用方被迫共享崩溃依赖和平台分支，违背现有可选库边界，因此不采用。
3. **只格式化或只发布，不安装处理器**：代码简单，却没有实际崩溃记录，无法关闭应用自动采集缺口，因此不采用。

## 公共接口与所有权

`core_app.h` 增加：

```c
typedef struct CoreAppDiagnosticsSnapshot {
    u32 tick;
    const char *rhi_backend; /* borrowed, callback only */
    const char *gpu_name;    /* borrowed, callback only */
    bool network_live;
    u64 network_events_seen;
    u64 network_events_dropped;
    u32 key_down_count;
    u32 pad_connected_count;
    u32 touch_count;
    u32 gesture_count;
    u32 touch_status;
    u32 haptic_status;
} CoreAppDiagnosticsSnapshot;

typedef void (*CoreAppDiagnosticsPublishFn)(
    void *user, const CoreAppDiagnosticsSnapshot *snapshot);

typedef struct CoreAppDiagnosticsHooks {
    void *user;
    CoreAppDiagnosticsPublishFn publish;
} CoreAppDiagnosticsHooks;
```

`CoreAppConfig` 追加 `const CoreAppDiagnosticsHooks *diagnostics`，NULL 为默认。非 NULL 时 `publish` 必须非 NULL，否则配置校验失败。hooks 与字符串只在调用期间借用；runtime 不保存回调产生的数据，回调返回 void，不能改变模拟、帧推进、trace 或退出码。

新独立静态库 `core_app_diagnostics` 提供：

```c
bool core_app_diagnostics_start(const char *spool_root);
void core_app_diagnostics_stop(void);
void core_app_diagnostics_publish(
    void *user, const CoreAppDiagnosticsSnapshot *snapshot);
```

- `start` 仅调用现有 `break_crash_install`，空路径或安装失败返回 false；已经安装时遵循现有 second-install=false。
- `stop` 先清空 context-blob 再 `break_crash_uninstall`，未安装时安全无操作。
- `publish` 使用栈上 `BreakCrashSummary` 和固定容量输出缓冲，无分配；NULL user 被忽略，NULL snapshot 为无操作。它不在 worker、网络回调或信号处理器内运行。

## 运行与 CLI 生命周期

新选项 `--crash-context DIR` 指定 spool 根目录。帮助文本列出该选项；`BREAK_ENABLE_CRASH=OFF` 时 `core_app` 仍构建，但该选项以“当前构建不可用”失败。`start` 失败在任何应用运行前返回退出码 2，不能伪装启用。

参数解析成功后：

1. 创建 `CoreAppDiagnosticsHooks`，其 publish 指向 `core_app_diagnostics_publish`。
2. `core_app_diagnostics_start(DIR)` 安装处理器。
3. 在 `core_app_run` 前发布初始快照：请求的 render 后端、固定 `pending` 设备名和归零的网络/输入计数，保证初始化早期崩溃也有上下文。
4. `core_app_run` 在 `runtime_running` 后发布 tick 0，以真实后端和设备名替换初始值，之后在每个完整 tick 末尾发布一次。
5. 无论运行成功或失败，调用 `core_app_diagnostics_stop` 一次，再返回原运行结果。

`core_app` 仅在 `TARGET break_crash` 时链接 `core_app_diagnostics`，并定义 `CORE_APP_CRASH_CONTEXT=1`，否则为 0。`core_app_runtime` 的源文件和链接集合不增加崩溃库；独立测试按需链接诊断模块。`break_crash_upload_http` 及网络上传符号不得进入 `core_app`。

## 快照内容与隐私

- RHI：`rhi_backend`、`gpu_name`；record 路径使用固定 `record` / `none`，GPU 路径使用已有 `CoreAppGpu.backend_name/device_name`。
- 网络：`network_live`、总线事件 `seen` 和 reactor `dropped` 计数。不包含 IP、端口、连接 key、session id、PSK 或数据包内容。
- 输入：当前 tick、512 个 key 槽中 held/pressed 的数量、已连接 pad 数量、touch/gesture 数量以及 touch/haptic 状态枚举的数值。不包含原始按键码、文本、坐标、设备名或触摸来源 ID。

诊断格式沿用 `[rhi]`、`[net]`、`[input]` 三个 section 的 `key=value` 行。`BreakCrashSummary` 负责路径字符、换行和非打印字符清理。hooks 只在 `CoreAppThread` 上执行，读取该线程已经拥有的状态；无锁、无跨线程快照、无堆分配。未设置 hooks 时不生成输入副本，也不增加逐键扫描。

## TDD 验收

1. 配置为 NULL 时现有 `core_app_run` 行为与 trace 不变；非法 hooks 配置在运行前拒绝。
2. 真实 `core_app_run` 的测试 sink 收到 tick 0 和完整 tick 快照：record 后端、网络关闭、真实输入计数和状态正确；不是手工构造的假运行。
3. `core_app_diagnostics_publish` 生成的三个 section 字段与快照一致，并验证长设备名和特殊字符经过既有清理。
4. Linux 子进程执行真实 `start → publish → raise(SIGSEGV)`，父进程确认死亡信号并直接解析 `crash.inbox`：context-blob 包含同一批 RHI/net/input 字段。`stop` 后再次安装可恢复，默认不调用 start 不写 spool。
5. CLI 契约覆盖帮助、空 DIR、安装失败、不支持构建、默认不安装以及成功后解除；`core_app` 不包含上传适配器符号。Windows stub 必须明确失败，不记录为已捕获。
6. 先观察缺少 hooks/诊断符号时的 RED，再写最小实现。普通、ASan/UBSan、相关 TSan、双图形后端和可用平台矩阵复验；崩溃子进程测试保持有界等待，不用 sleep 作为正确性依据。

独立代码评审重点检查回调线程、字符串借用、启停失败、重复 stop、默认链接闭包、原始输入/网络隐私以及真实 crash.inbox 断言。文档以追加方式更新 `crash_reporting.md`、`crash_symbolization.md`、`missing_capabilities.md`、`Implementation_Status.md` 和跨平台测试矩阵。

## 假设

- 用户已要求继续既定计划并采用自动执行模式，因此采用推荐方案，不暂停等待逐项选择。
- 本子项目只交付本地捕获与摘要，不把安装处理器解释为上传，也不把 POSIX 信号测试扩展为 Windows/macOS 客户端捕获证据。
