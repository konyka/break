# Core App 音频队列满载压测（2026-11-14）

## 背景

Task 9 的边界写着“256 条满队列的进程级压测未做”。现有用例只在单线程里把队列填满一次；owner 线程存在后，生产者与 owner 并发访问 head/count/sequence，没有用例在并发下反复撞满队列。

## 范围

在 `test_core_app_runtime` 里加一个进程内多线程压测，不改 `core_app_audio.c`。

- FAKE 后端 + `core_app_audio_start_system_owned`。
- 4 个生产者线程（`platform_thread.h`），各用自己的 generation（1..4）入队 4096 条 LISTENER；遇到 OVERLOAD 自己计数，`platform_thread_yield` 后重试同一条，直到被接受。主线程同时循环调用 `core_app_audio_drain_device(&audio, 0u)`。
- 全部生产者 join 后执行 `audio_shutdown`。

断言：

- `device_listener_updates == 4 * 4096`：没有丢命令，也没有重复执行。
- `audio.overloads` 等于各生产者观察到的 OVERLOAD 次数之和。
- `device_calls_off_owner == 0`。
- trace 中 listener 行恰好 16384 行，sequence 按行顺序严格等于 1..16384（FIFO，序号在锁内分配）；每个 generation 各 4096 行。

## 变异（必须变红）

1. 满队列时只在一半情况下计 `overloads++`：`audio.overloads` 与生产者观察到的次数不等。
2. owner 模式下 enqueue 不加锁直接调用 `sound_enqueue_locked`：命令丢失，`device_listener_updates` 不等于总数。
3. owner 出队的 `head`/`count` 更新移到锁外：同上。

## 验证

normal 树 `test_core_app_runtime`；TSan 树连跑 10 次零报告；ASan 树通过；normal 全量。

## 文档

`docs/design/core_app_integration.md` 的 Task 9 部分末尾追加小节；`docs/Implementation_Status.md` 顶部新增条目，原“256 条满队列的进程级压测未做”后括注“进程内多线程压测已在 2026-11-14 补上”。
