## 本轮更新：流式块测试临时目录跨平台（2026-11-02）

- **根因**：GitHub Actions run `41276867563` 中，Windows Clang/MSVC 因 `test_world_stream_world.c` 直接包含 `unistd.h` 编译失败，MinGW 因双参数 `mkdir` 编译失败。这是测试 fixture 引入的 POSIX 依赖，不是生产流式实现缺陷。
- **修复**：测试改用现有 `test_tmp`、`TEST_MKDIR`、`TEST_RMDIR`，目录按进程隔离；四个文件路径均由 `snprintf` 构造并检查返回值。保留全部流式行为断言，未改 `world_stream_world.c` 或其他生产逻辑，也未屏蔽告警。
- **验证**：`cmake -S engine -B build-cry-final && cmake --build build-cry-final -j6 --target test_world_stream_world && ./build-cry-final/test_world_stream_world` 通过，2/2。`cmake --build build-sdd-p4-asan -j6 --target test_world_stream_world && ./build-sdd-p4-asan/test_world_stream_world` 通过，2/2，无 sanitizer 报告；该树先按原缓存重新配置，并因本机 Snowflake 外部源码不符合提交钉而对此 focused 构建关闭可选 Snowflake，ASan+UBSan 保持开启。
- **限制**：本机没有完整 Windows 工具链或 Windows 运行环境。`clang-cl` 的 TU 语法检查因缺少 Windows SDK 的 `stdio.h` 无法开始编译；Windows 结果由后续 CI 验证，不在此提前声称通过。
