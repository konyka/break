# Core App P12 Task 12：fuzz 与三棵验证树报告（2026-11-14）

## 范围

本步交付两个显式 fuzz target 并跑通三棵验证树（普通 / ASan+UBSan / TSan）与 no-tests 真实进程。Task 11 的真实 GPU 像素证据不在本步。

## 交付物

| 文件 | 内容 |
|---|---|
| `engine/tests/fuzz_core_app_checkpoint.c` | manifest/BSCN/Flow/Actor/runtime 变异的 checkpoint fuzzer |
| `engine/tests/fuzz_core_app_scenario.c` | 文本变异的 scenario fuzzer |
| `engine/CMakeLists.txt` | 两个 `EXCLUDE_FROM_ALL` target 与 `fuzz` 标签 smoke 注册 |

## fuzzer 设计要点

- **每轮从干净状态重建**：fuzzer 启动时删除并重建自己的 `valid`/`sentinel` 临时树，因此中断后重跑仍与首次逐位一致。这是本步修掉的一个真实缺陷：早期版本留下旧目录，导致第二次运行结果漂移。
- **sentinel 不变量**：`sentinel` 树在整个变异过程中从不被写入，每轮都重新读取并对比字节，同时确认它仍能 probe。被拒的变异不可能污染无关 state。
- **拒绝不留部分状态**（scenario）：解析失败时 `event_count` 必须为 0。
- **诊断充分**：每个提前返回都带 stderr 说明，避免“静默 rc=1”。

## 结果

| 树 | 命令（要点） | 结果 |
|---|---|---|
| 普通 | `ctest -L fuzz` | 9/9 PASS |
| ASan+UBSan | `ctest -R 'fuzz_core_app\|test_core_app_(runtime\|network\|lifecycle)'` | 16/16 PASS，无报告 |
| TSan | 同上 | 14/14 PASS，无报告 |
| no-tests | `core_app --render=record --audio=record --fixed-step --scenario assets/core_app/deterministic.scenario` | 退出 0，完整生命周期 trace |

checkpoint fuzz 确定性：200 次固定 seed → `accepted=45 rejected=155`，重复运行一致。

## 已知边界

- 无 libFuzzer 结构感知、无落盘 corpus；变异是自实现 RNG。
- `fuzz_core_app_network` 未做；snapshot 边界由 `test_core_app_network` 的确定性单元测试覆盖。
- TSan 只覆盖 core_app 的单元与 lifecycle 目标，不覆盖真实网络线程（本构建 `BREAK_ENABLE_SNOWFLAKE=OFF`）。
