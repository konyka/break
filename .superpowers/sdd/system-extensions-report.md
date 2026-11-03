# P11 System Extensions 交付报告

日期：2026-11-03
工作树：`/home/timeshift/opensource/break/.worktrees/cry-system`
分支：`cry-wave2-system`（base `a0bfeb95`，未 push）

## 状态与提交

状态：实现和本地验证完成。实际执行计划为 `docs/superpowers/plans/2026-11-03-system-extensions.md`；恢复指令提到的 `2026-11-02-system-extensions.md` 在仓库中不存在。

- `90344f0a` `docs: plan P11 system extensions`
- `78534392` `system: add transactional registered cvars`
- `d91dc59d` `system: add bounded XML scene sidecars`
- `e7324353` `system: load allowlisted plugins through PAL`
- 最终文档与本报告随 `docs: record P11 system extension evidence` 提交。

## 交付内容

- `break_system` 独立 C11 静态库，在 `ENGINE_BUILD_TESTS=OFF` 时仍生成，不链入核心 engine/demo/editor。
- CVar：固定 1..256 项；bool/int64/finite double/UTF-8 string；范围、readonly/Cheat、变化回调、回调重入拒绝；配置 load 主/暂存表事务提交，save 复用 `PlatformAtomicWriter`。
- XML：create 时固定主/暂存树和 arena；非递归解析；严格 UTF-8 和 XML 字符检查；拒绝 DTD、自定义/数值实体、CDATA、非法语法及所有输入/节点/属性/深度/arena 超限；失败保留旧文档。`break-scene` v1 只读写实体 index/generation/class，不是 BSCN 替代。
- 插件：POSIX/Win32 PAL；load 前复用 `break_integrity` 的流式 SHA-256 文件检查；精确 descriptor size、ABI 1、build id、名字检查；固定槽/load-order、generation 句柄、引用计数、失败关闭库、显式注册顺序和逆序卸载；任何引用都阻止单个或批量卸载。
- 文档：`docs/design/system_extensions.md`、`docs/design/cry_style_gameplay.md`、`docs/Implementation_Status.md`。

## 真实 RED → GREEN 与变异

### CVar

- 基线 `test_scene_serial`、`test_break_integrity`、`test_platform_fs_write`：3/3。
- 最小空实现 RED：0/8，8 个行为测试均运行并失败；首个失败为注册未返回 `OK`，不是仅链接缺失。
- 首轮实现 6/8：发现一处测试误把无类型标签 union 当作运行时 set 类型信息，删除无效断言；另修正 readonly 配置应先按权限保持/拒绝，而非先返回范围错误。恢复后 8/8。
- 范围变异（删除 int 上下限检查）：5/8，注册越界、set 越界和配置范围用例变红。
- 提前提交变异（失败 load 也交换主/暂存表）：6/8，cheat 拒绝后的回调计数与失败回滚值变红。
- 恢复后 CVar 8/8，相关 CTest 全绿。

### XML

- 最小空实现 RED：2/10，8 个有效解析/上限分类/侧车/旧文档保持用例失败；DTD/语法拒绝类在空实现下的通过不计作功能证据。
- 完整实现 GREEN：10/10；`test_scene_serial` 同时通过。
- DOCTYPE 变异：8/10，DTD 拒绝与失败保留旧文档用例变红。
- UTF-8/字符检查跳过变异：9/10，非法 UTF-8 用例变红。
- 失败时也交换暂存树变异：9/10，旧 root 从 `old` 变成部分解析的 `new`，被精确断言杀死。
- 恢复后 XML 10/10，相关 CTest 全绿。

### 插件

- CMake 先真实生成 A、B、bad-ABI、register-fail、no-entry 五个 `.so`；最小 manager RED：1/8，7 个 load/生命周期测试失败。
- 完整 PAL/manager GREEN：8/8，真实执行 `dlopen`、entry 调用、register/unregister、`dlclose`；覆盖错误 digest、追加字节副本、ABI/build id/缺入口/注册失败、重复/容量、stale handle、引用防卸载和逆序事件。
- target contract 初次失败为测试注册变量 `CMAKE_CURRENT_SOURCE_FILE` 不存在；改为 `CMAKE_CURRENT_LIST_FILE` 后通过，生产行为未变。
- 哈希比较跳过变异：7/8，错误 digest 被错误接受而变红。
- 单个 unload 引用检查删除变异：7/8，被引用插件被错误卸载而变红。
- `unload_all` 正序变异：6/8，两个事件顺序断言变红。
- 恢复后插件 8/8，target contract 通过。

## 最终验证命令与结果

三棵树均执行 focused：

```bash
ctest --test-dir <tree> -R 'break_(cvar|xml|plugin|system)|break_integrity|platform_fs_write|scene_serial' --output-on-failure
```

- `build-system-normal`：7/7。
- `build-system-asan`（`ENGINE_USE_ASAN=ON`、`ENGINE_USE_UBSAN=ON`）：7/7，无 sanitizer 报告。
- `build-system-tsan`（`ENGINE_USE_TSAN=ON`）：7/7，无 sanitizer 报告。

三棵树均完整构建所有目标后执行：

```bash
ctest --test-dir <tree> -L headless --output-on-failure -j<6或4>
```

- normal：129/129，0 失败。
- ASan+UBSan：129/129，0 失败，无 sanitizer 报告。
- TSan：129/129，0 失败，无 sanitizer 报告。

独立 target 验证：

```bash
cmake -S engine -B build-system-no-tests -DENGINE_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug
cmake --build build-system-no-tests -j6 --target break_system
```

结果：成功产出 `libbreak_system.a`。`test_break_system_target_contract` 同时钉住 C11、源清单、真实 SHARED fixture、crypto/dl 链接及核心目标 no-link。

最终 `git diff --check` 无输出；未提交源文件在交付提交后复核。所有变异均已恢复，未提交变异体。

## 限制与未声称事项

- 插件哈希 allowlist 只证明验证对象与预期 SHA-256 相同；不是签名、发布者认证、sandbox 或权限边界。依赖库未逐项哈希；共享库和构造函数仍拥有进程原生权限。
- CVar 回调和插件 register/unregister 的外部副作用不由库回滚。插件 register 返回 false 时必须已自行清理部分外部注册；manager 保证自身槽/顺序和库句柄不遗留。
- Linux 上验证了 POSIX PAL。Win32 `LoadLibraryA/GetProcAddress/FreeLibrary` 分支已提供但未在本机 Windows 编译或运行，不声称 Windows 验收通过。
- 全量验证是 headless；本任务无图形路径，未运行图形/真机测试。默认关闭的独立 fuzz smoke 开关未另行开启。
- XML 是受限结构化子集；注释/处理指令不进入树，不做词法级无损保留。场景权威/完整格式仍是既有 BSCN/JSON。
- `platform_fs.c` 仍由 `engine` 唯一生产持有；独立 CVar 文件 API 消费者须按现有约定提供一次该 PAL，避免重复链接定义。

## 独立评审 fix round 1（起始 HEAD `7286dd25`）

### 根因与 RED → GREEN

- **Critical：验证对象与加载对象不同。** 新 constructor fixture 在测试专用 post-verify/pre-open 钩子中替换路径。旧实现第 9 项插件测试 RED：`file_exists(BREAK_TEST_ATTACKER_MARK_PATH) is true`，证明未批准 constructor 已运行。PAL 改为 `platform_dynamic_open_verified`：Linux sealed memfd + `/proc/self/fd`，Windows 禁止写/删除共享的句柄 + final path；其它平台失败关闭，无原路径 fallback。初次 GREEN 后 A→B 回归发现验证 fd 早关导致路径复用，改为库句柄持有 fd 到卸载。最终插件 10/10，竞态加载批准 A（事件 11），攻击标记不存在。
- **Important：CVar callback destroy UAF。** 新增 set/load 两项回调销毁测试；修复前 ASan 在 `break_cvar_set` 回调返回后的 registry 写报 `heap-use-after-free`。改为 `destroy_pending` 并在最外层通知结束释放，load 完成剩余通知。最终 CVar 12/12，ASan 无报告。
- **Important：generation 回绕。** 测试把槽推进到 `UINT32_MAX-1`，第三次加载旧实现没有返回 `OVERLOAD`，generation 回到 1。改为永久退休耗尽槽，第三次返回 `OVERLOAD`，最老 handle 为 `STALE`。
- **Important：CVar 字符串。** 旧实现接受 leading-space 注册值，RED 为预期 `INVALID` 实际 `OK`；现拒绝首尾空格，空串和中间空格 save/load 往返成功。get→offset pointer→set 旧实现被 ASan 以 `memcpy-param-overlap` 捕获，改用 `memmove` 后得到 `cdef`。
- **Important：scene 属性闭包。** 683 实体旧 writer 返回 `OK` 而非 `OVERLOAD`。现 682 实体写出→解析→读回成功，683 在输出修改前返回 `OVERLOAD`，`out_size=0` 且首字节 sentinel 不变。
- **Minor。** U+FFFE 文本与 U+FFFF 属性曾通过解析；现按 XML 1.0 码点闭包拒绝且旧文档保留，U+FFFD 仍合法。源码 contract 对递归 serializer 调用 RED；改为父索引迭代后，64 层输出逐字一致且 contract 通过。报告原第 3–4 行 trailing whitespace 已删除。

### 关键变异

- `dlopen(verified_path)` 临时改回 `dlopen(path)`：插件 9/10，攻击 constructor 标记再次出现。
- generation 临时回绕到 1：插件 9/10，身份耗尽测试失败。
- scene 上限临时放宽一个：XML 12/13，683 被错误接受。
- 回调内 destroy 临时立即释放：ASan 再次报 `heap-use-after-free`。
- 所有变异均立即恢复并重新验证，未提交变异体。

### 最终命令与输出

三棵树执行：

```bash
ctest --test-dir <tree> -R 'break_(cvar|xml|plugin|system)|break_integrity|platform_fs_write|scene_serial' --output-on-failure
```

normal、ASan+UBSan、TSan 分别得到 `100% tests passed, 0 tests failed out of 7`。随后三棵树完整构建并执行：

```bash
ctest --test-dir <tree> -L headless --output-on-failure -j<6或4>
```

三棵树分别得到 `100% tests passed, 0 tests failed out of 129`，ASan+UBSan/TSan 无 sanitizer 报告。`cmake --build build-system-no-tests -j6 --target break_system` 成功。

Win32 分支验证命令：

```text
clang-cl /c /W4 /WX /I engine/src engine/src/platform/platform_dynamic.c /Fobuild-system-normal/platform_dynamic_windows.obj
engine/src/platform/platform_dynamic.c(9,10): fatal error: 'stdio.h' file not found
```

本机缺 Windows CRT/SDK，因此不声称 Win32 编译或运行通过；没有以 Linux 头文件或不安全 loader 绕过。最终 `git diff --check a0bfeb95..HEAD` 在交付提交后执行并记录。

### 当前真实限制

验证对象机制关闭了原路径替换窗口，但依赖库未逐项 allowlist 校验，哈希也不是签名认证。Linux memfd 的 `$ORIGIN`/依赖搜索语义与原目录不同，宿主必须显式管理。其它非 Linux/Windows 平台失败关闭而非加载。constructor 和回调外部副作用仍不属于事务回滚范围。

## 独立评审 fix round 2（起始 HEAD `98ce9ae0`）

### Minor 1：明确的容量错误

新增 64 MiB+1 sparse 文件测试。修复前 `break_plugin_load` 返回 `BREAK_PLUGIN_FAILED`，测试 10/11；新增 `PLATFORM_DYNAMIC_OPEN_OVERLOAD` 后，Linux 的 `st_size`/累计 `total` 和 Windows 的 `GetFileSizeEx`/累计 `total` 超限都返回该状态，manager 映射为 `BREAK_PLUGIN_OVERLOAD`。输出 handle 保持 `(0,0)`，注册计数为零；不存在文件仍返回 `BREAK_PLUGIN_FAILED`。最终插件 11/11。

### Minor 2：不支持平台的安全测试与门控

成功 fixture 现在只在 `ENGINE_PLATFORM=linux/windows` 时注册 `test_break_plugin`。新增 `test_break_plugin_unsupported`，在所有主机运行并以 `BREAK_SYSTEM_TEST_UNSUPPORTED` 强制生产 fail-closed 分支。修复前该变体在 Linux 仍加载攻击库，`file_exists(BREAK_TEST_ATTACKER_MARK_PATH) is true`，0/1；修复后返回 `BREAK_PLUGIN_FAILED`，handle index/generation 均为 0、注册计数为 0、constructor 标记不存在，1/1。正常成功 fixture 未被削弱，仍 11/11。

### 三 lane focused

三棵树均执行：

```bash
ctest --test-dir <tree> -R 'break_(cvar|xml|plugin|system)|break_integrity|platform_fs_write|scene_serial' --output-on-failure
```

- normal：`100% tests passed, 0 tests failed out of 8`。
- ASan+UBSan：`100% tests passed, 0 tests failed out of 8`，无 sanitizer 报告。
- TSan：`100% tests passed, 0 tests failed out of 8`，无 sanitizer 报告。

这 8 项包括 CVar、XML、正常插件、unsupported、target contract、BSCN、integrity 和 platform_fs。本轮未重复声称新增全量 headless 结果；round 1 的 129/129 记录保持为其对应提交的证据。`git diff --check` 在交付提交后执行。
