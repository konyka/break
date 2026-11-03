# System Extensions：CVar、XML 场景侧车与受控插件

状态：P11 已交付，2026-11-03。实现位于独立 `break_system` 静态库；它不会链入 `engine`、`engine_demo`、`dxx_break` 或 `editor`，并在 `ENGINE_BUILD_TESTS=OFF` 时继续构建。插件需要现有 `BREAK_ENABLE_CRYPTO` / `break_crypto`，不引入新依赖。

## 1. CVar

公开接口：`engine/src/system/break_cvar.h`。实现：`break_cvar.c`；直接测试：`test_break_cvar`。

### 注册与值

- 每个 registry 在 create 时确定 1..256 个槽，并一次分配主表、暂存表和配置缓冲；register/set/load 不分配或扩容。
- 类型为 bool、int64、finite double、UTF-8 string。int/double 各自有闭区间；越界返回 `BREAK_CVAR_OVERLOAD`，非有限 double 和非法 UTF-8/控制字符返回 `INVALID`。
- 名字为 1..63 字节 ASCII 标识符，首字符是字母或 `_`，后续还允许数字、`.`、`-`。字符串值最多 127 字节加 NUL；空串和中间空格合法，首尾空格在注册/set 时拒绝以保证 save/load 可逆。重复名字返回 `REJECTED`，容量满返回 `OVERLOAD`。
- `READONLY` 不允许运行时 set。配置中相同的 readonly 值是幂等 no-op，不同的值整份拒绝；save 不写 readonly 项。`CHEAT` 只有 set/load 的 `allow_cheat=true` 时才可修改。
- 实际值变化才同步调用一次回调。回调执行期间 registry 拒绝重入写；查询仍可使用。回调中的外部副作用不属于 registry 的回滚范围。
- 回调可以请求 destroy：此时只标记 `destroy_pending`，最外层 set/load 通知完成后才实际释放。该次 set/load 返回后调用方不得再使用 registry；load 会在释放前完成当前已提交值的剩余通知。
- get 返回的 string 指针归 registry 所有，只保证到下一次写或 destroy；set 接受指向当前值的偏移指针并以 `memmove` 处理重叠。registry 由创建线程独占，不是并发数据结构。

### 配置文法与事务

每行是 `name=value`。名字和值两侧的 ASCII 空白被 trim；空行和第一个非空白字符为 `#` 的行被忽略。字符串没有引号或反斜杠转义，也不能包含控制字符或首尾空格；其余文本原样保存。bool 只接受 `true` / `false`，int 是完整十进制，double 必须有限且完整消费。

未知名字、重复名字、非法值、NUL、超过 64 KiB 的文件或超过 255 字节的行都会失败。load 先读入创建时分配的缓冲，在暂存表应用并验证所有行，成功后才交换主/暂存表并按注册顺序通知变化；失败不改变值或触发回调。

save 使用现有 `PlatformAtomicWriter`，int 用十进制、double 用 `%.17g`，失败返回 `FAILED`。`engine` 仍是 `platform_fs.c` 的唯一生产 owner；使用 CVar 文件 API 的独立消费者须按现有静态库约定提供 `platform_fs.c`，不能同时重复定义该 PAL。测试目标内联编译它。

## 2. XML 与场景侧车

公开接口：`engine/src/system/break_xml.h`。实现：`break_xml.c`；直接测试：`test_break_xml`。

### 有界 XML 子集

create 接收 `max_input_bytes`、`max_nodes`、`max_attributes`、`max_depth`、`max_text_bytes`，为主/暂存存储一次分配。根深度为 1。每轴都有调用方上限及硬上限：输入 1 MiB、节点 1024、属性 2048、深度 64、字符 arena 1 MiB。任何超限返回 `OVERLOAD`，不截断。

- 支持单根 element、单/双引号属性、文本节点、注释和 `<?...?>`。mixed content 以有序 element/text 子节点保留。
- 只解码 `amp`、`lt`、`gt`、`quot`、`apos` 五个预定义实体。DTD、`<!ENTITY`、自定义实体、数值实体、CDATA 和其它声明均拒绝；没有实体展开器。
- 整个输入先做严格 UTF-8 校验，再按 XML 1.0 字符闭包检查解码后的码点：只接受 TAB/LF/CR、U+0020..U+D7FF、U+E000..U+FFFD、U+10000..U+10FFFF。overlong、surrogate、超出 Unicode、截断序列、NUL、C0 非法字符以及 U+FFFE/U+FFFF 均拒绝。
- 拒绝重复属性、多根、根外非空白、未闭合/错配标签、非法名字和畸形注释。解析使用当前 element 的父索引，不递归、不分配临时栈。
- 解析写入暂存树，只有完整成功才交换；失败保留旧文档。serialize 以父索引迭代遍历树，不递归；对五个特殊字符重新转义，容量不足时 `out_size=0`，失败后的输出缓冲内容不可作为文档使用。
- 注释和处理指令不进入树，序列化不会重建它们；原标签格式、引号风格与空白也不做词法级无损保留。这是受限结构化 XML，不是通用无损 XML 编辑器。

### `break-scene` v1

XML 的场景用途仅是如下侧车，不替代 BSCN 的 World、组件、资源、网格、材质或动画数据：

```xml
<break-scene version="1"><entity index="1" generation="7" class="Player"/><entity index="8" generation="2" class="Enemy.Grunt"/></break-scene>
```

root 只有 `version="1"`；entity 只有非零 decimal `index`、非零 decimal `generation` 和 `class`。class 是 1..63 字节 `[A-Za-z_][A-Za-z0-9_.-]*`。未知元素/属性、entity 非空白内容、整数溢出和重复 `(index,generation)` 整份拒绝。reader 完整验证后才写输出；容量不足返回 `OVERLOAD` 和总条数且不修改行。writer 先验证所有行，最多写 682 个实体（root 与全局 2048 属性容量闭包），683 在修改输出前返回 `OVERLOAD`。输出是 canonical XML，可由通用 parser 和 sidecar reader 读回。BSCN/JSON 仍由既有 `scene_serial` 负责。

## 3. PAL 动态加载与插件

PAL：`engine/src/platform/platform_dynamic.{h,c}`。管理器：`engine/src/system/break_plugin.{h,c}`。真实共享库测试：`test_break_plugin`。

`platform_dynamic_open_verified` 把验证和原生加载收在同一 PAL 原语中，不提供先哈希再按路径打开的替代 API，文件上限 64 MiB。初始大小或累计读取超限返回 `PLATFORM_DYNAMIC_OPEN_OVERLOAD`，由 manager 映射为 `BREAK_PLUGIN_OVERLOAD`；普通打开/读取/写入/哈希失败仍为 `FAILED`，不匹配仍为 `REJECTED`。

- Linux：打开源对象后把字节流式复制到 memfd，同时用现有 `break_crypto` 计算 SHA-256；添加 WRITE/GROW/SHRINK/SEAL seals，digest 匹配后只从 `/proc/self/fd/<fd>` `dlopen`。验证 fd 由库句柄持有到卸载，避免 fd/path 复用把不同库误认为同一对象。
- Windows：源句柄只允许 `FILE_SHARE_READ`，不允许写或删除共享，并拒绝 reparse point；在同一受保护句柄上哈希，digest 匹配后用 `GetFinalPathNameByHandleA` 取得最终路径并在句柄仍打开时 `LoadLibraryA`。该共享模式同时阻止验证后修改、删除和 rename；没有退回不受保护路径的分支。
- 其它平台当前返回 `FAILED`，不执行不受验证对象约束的 loader。测试宏 `BREAK_SYSTEM_TEST_UNSUPPORTED` 在 Linux/Windows loader 实现和 dispatcher 都排除平台分支，因此 Windows 静态 loader 也不会进入编译产物，测试统一覆盖公共零输出句柄/零副作用路径。符号解析和卸载仍使用 PAL 的 `dlsym`/`GetProcAddress` 与 `dlclose`/`FreeLibrary`。

### 加载门与 ABI

每次 load 的参数 `(path, build_id, expected_sha256)` 是一项 allowlist 记录。顺序固定为：

1. manager 验证参数、重复 path 和可用槽；PAL 对将实际加载的验证对象计算并比较 SHA-256。mismatch 在任何 loader 调用前返回，不会运行 constructor。
2. PAL 从上述不可替换对象完成原生加载；manager 再查找 `break_plugin_entry`，缺入口返回 `FAILED`。
3. descriptor 的 `struct_size` 必须精确等于当前 `BreakPluginDescriptor`，`abi_version == 1`；名字和 build id 都是 1..63 字节可打印 ASCII，build id 与 allowlist 精确匹配，插件名字不能与已加载项重复。
4. 最后调用可选 register。其 false 返回值表示插件已自行清理部分外部注册，manager 关闭库且不留下活动槽。constructor 和 register 的外部副作用不属于 manager 回滚保证。
5. 成功后才提交槽和 load-order，输出 `(index,generation)` 句柄。任何失败关闭已打开的库并清零输出句柄。

哈希 allowlist 是**完整性检查，不是签名或发布者认证**。验证对象机制消除“哈希后按原路径替换”的窗口，但不能抵抗能修改 allowlist 的本地攻击者；依赖库没有逐项哈希，合法共享库及其构造函数仍以进程全部权限执行原生代码。Linux memfd 的 `$ORIGIN` 和依赖搜索语义不等同原目录，需要宿主显式管理依赖。

### 注册、引用与卸载

- A 后 B 加载产生 register A、register B；单插件 unload 按调用者显式顺序，`unload_all` 严格按 load-order 逆序产生 unregister B、unregister A。
- acquire/release 使用 generation 句柄；引用计数溢出/下溢拒绝。卸载后旧句柄返回 `STALE`，槽复用递进到非零 generation；generation 到达 `UINT32_MAX` 后槽永久退休，不再分配，身份耗尽返回 `OVERLOAD`，不回绕复活旧句柄。
- 单个 unload 在引用非零时返回 `REJECTED` 且不调用 unregister、不关闭库。`unload_all` 在任何回调之前预检全部插件，只要一个被引用就整体拒绝。
- destroy 先执行同样的引用预检，再逆序卸载并释放 manager；存在引用时 manager 保持可用。
- 回调期间 manager 拒绝重入生命周期操作，防止注册顺序被重入改变。管理器只由创建线程使用。

## 4. 验证入口

- focused：`test_break_cvar`、`test_break_xml`、`test_break_plugin`、`test_break_plugin_unsupported`、`test_break_system_target_contract`。成功加载 fixture 只在 Linux/Windows 注册；`test_break_plugin_unsupported` 在所有主机运行，以测试宏强制走生产 fail-closed 分支，断言 `FAILED`、零输出 handle、零注册和零 constructor 副作用，不跳过安全断言。
- 相关既有回归：`test_platform_fs_write`、`test_scene_serial`、`test_break_integrity`。
- 六套真实 CMake `SHARED` fixture 分别覆盖正常 A/B、bad ABI、register failure、no entry 和 constructor 攻击体。替换竞态 fixture 在验证后、加载前替换输入路径，断言攻击 constructor 标记从未出现且加载的是原批准对象；64 MiB+1 sparse 文件验证超限状态。
- normal、ASan+UBSan、TSan 命令与最终通过数见 `.superpowers/sdd/system-extensions-report.md`。Linux 之外的 PAL 分支尚未在本机执行；Windows 结果不提前声称。
