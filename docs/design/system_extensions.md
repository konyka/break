# System Extensions：CVar、XML 场景侧车与受控插件

状态：P11 已交付，2026-11-03。实现位于独立 `break_system` 静态库；它不会链入 `engine`、`engine_demo`、`dxx_break` 或 `editor`，并在 `ENGINE_BUILD_TESTS=OFF` 时继续构建。插件需要现有 `BREAK_ENABLE_CRYPTO` / `break_integrity`，不引入新依赖。

## 1. CVar

公开接口：`engine/src/system/break_cvar.h`。实现：`break_cvar.c`；直接测试：`test_break_cvar`。

### 注册与值

- 每个 registry 在 create 时确定 1..256 个槽，并一次分配主表、暂存表和配置缓冲；register/set/load 不分配或扩容。
- 类型为 bool、int64、finite double、UTF-8 string。int/double 各自有闭区间；越界返回 `BREAK_CVAR_OVERLOAD`，非有限 double 和非法 UTF-8/控制字符返回 `INVALID`。
- 名字为 1..63 字节 ASCII 标识符，首字符是字母或 `_`，后续还允许数字、`.`、`-`。字符串值最多 127 字节加 NUL。重复名字返回 `REJECTED`，容量满返回 `OVERLOAD`。
- `READONLY` 不允许运行时 set。配置中相同的 readonly 值是幂等 no-op，不同的值整份拒绝；save 不写 readonly 项。`CHEAT` 只有 set/load 的 `allow_cheat=true` 时才可修改。
- 实际值变化才同步调用一次回调。回调执行期间 registry 拒绝重入写；查询仍可使用。回调中的外部副作用不属于 registry 的回滚范围。
- get 返回的 string 指针归 registry 所有，只保证到下一次写或 destroy。registry 由创建线程独占，不是并发数据结构。

### 配置文法与事务

每行是 `name=value`。名字和值两侧的 ASCII 空白被 trim；空行和第一个非空白字符为 `#` 的行被忽略。字符串没有引号或反斜杠转义，也不能包含控制字符；其余文本原样保存。bool 只接受 `true` / `false`，int 是完整十进制，double 必须有限且完整消费。

未知名字、重复名字、非法值、NUL、超过 64 KiB 的文件或超过 255 字节的行都会失败。load 先读入创建时分配的缓冲，在暂存表应用并验证所有行，成功后才交换主/暂存表并按注册顺序通知变化；失败不改变值或触发回调。

save 使用现有 `PlatformAtomicWriter`，int 用十进制、double 用 `%.17g`，失败返回 `FAILED`。`engine` 仍是 `platform_fs.c` 的唯一生产 owner；使用 CVar 文件 API 的独立消费者须按现有静态库约定提供 `platform_fs.c`，不能同时重复定义该 PAL。测试目标内联编译它。

## 2. XML 与场景侧车

公开接口：`engine/src/system/break_xml.h`。实现：`break_xml.c`；直接测试：`test_break_xml`。

### 有界 XML 子集

create 接收 `max_input_bytes`、`max_nodes`、`max_attributes`、`max_depth`、`max_text_bytes`，为主/暂存存储一次分配。根深度为 1。每轴都有调用方上限及硬上限：输入 1 MiB、节点 1024、属性 2048、深度 64、字符 arena 1 MiB。任何超限返回 `OVERLOAD`，不截断。

- 支持单根 element、单/双引号属性、文本节点、注释和 `<?...?>`。mixed content 以有序 element/text 子节点保留。
- 只解码 `amp`、`lt`、`gt`、`quot`、`apos` 五个预定义实体。DTD、`<!ENTITY`、自定义实体、数值实体、CDATA 和其它声明均拒绝；没有实体展开器。
- 整个输入先做严格 UTF-8 校验，拒绝 overlong、surrogate、超过 U+10FFFF、截断序列、NUL 和除 TAB/LF/CR 外的 C0 控制字符。
- 拒绝重复属性、多根、根外非空白、未闭合/错配标签、非法名字和畸形注释。解析使用当前 element 的父索引，不递归、不分配临时栈。
- 解析写入暂存树，只有完整成功才交换；失败保留旧文档。serialize 对五个特殊字符重新转义，容量不足时 `out_size=0`，失败后的输出缓冲内容不可作为文档使用。
- 注释和处理指令不进入树，序列化不会重建它们；原标签格式、引号风格与空白也不做词法级无损保留。这是受限结构化 XML，不是通用无损 XML 编辑器。

### `break-scene` v1

XML 的场景用途仅是如下侧车，不替代 BSCN 的 World、组件、资源、网格、材质或动画数据：

```xml
<break-scene version="1"><entity index="1" generation="7" class="Player"/><entity index="8" generation="2" class="Enemy.Grunt"/></break-scene>
```

root 只有 `version="1"`；entity 只有非零 decimal `index`、非零 decimal `generation` 和 `class`。class 是 1..63 字节 `[A-Za-z_][A-Za-z0-9_.-]*`。未知元素/属性、entity 非空白内容、整数溢出和重复 `(index,generation)` 整份拒绝。reader 完整验证后才写输出；容量不足返回 `OVERLOAD` 和总条数且不修改行。writer 先验证所有行，再输出 canonical XML，可由通用 parser 和 sidecar reader 读回。BSCN/JSON 仍由既有 `scene_serial` 负责。

## 3. PAL 动态加载与插件

PAL：`engine/src/platform/platform_dynamic.{h,c}`。管理器：`engine/src/system/break_plugin.{h,c}`。真实共享库测试：`test_break_plugin`。

POSIX 使用 `dlopen(RTLD_NOW | RTLD_LOCAL)`、`dlsym`、`dlclose`；Windows 分支使用 `LoadLibraryA`、`GetProcAddress`、`FreeLibrary`。对象只在 load 冷路径分配，manager 创建后槽和 load-order 数组固定为 1..64 项。

### 加载门与 ABI

每次 load 的参数 `(path, build_id, expected_sha256)` 是一项 allowlist 记录。顺序固定为：

1. 验证参数、重复 path、空槽；用现有 `break_integrity_check_files` 流式计算目标文件的 SHA-256 并精确比较。哈希不匹配返回 `REJECTED`，读取/检查失败返回 `FAILED`，尚未打开库。
2. PAL 打开目标并查找 `break_plugin_entry`。缺入口返回 `FAILED`。
3. descriptor 的 `struct_size` 必须精确等于当前 `BreakPluginDescriptor`，`abi_version == 1`；名字和 build id 都是 1..63 字节可打印 ASCII，build id 与 allowlist 精确匹配，插件名字不能与已加载项重复。
4. 最后调用可选 register。其 false 返回值表示插件已自行清理部分外部注册，manager 关闭库且不留下活动槽。manager 无法回滚插件任意外部副作用；插件必须遵守这一回调合同。
5. 成功后才提交槽和 load-order，输出 `(index,generation)` 句柄。任何失败关闭已打开的库并清零输出句柄。

哈希 allowlist 是**完整性检查，不是签名或发布者认证**。它不能抵抗能修改 allowlist/文件的本地攻击者；path 在哈希与加载之间存在替换竞态，依赖库没有逐项哈希，合法共享库及其构造函数仍以进程全部权限执行原生代码。它也不是 sandbox 或权限边界。

### 注册、引用与卸载

- A 后 B 加载产生 register A、register B；单插件 unload 按调用者显式顺序，`unload_all` 严格按 load-order 逆序产生 unregister B、unregister A。
- acquire/release 使用 generation 句柄；引用计数溢出/下溢拒绝。卸载后旧句柄返回 `STALE`，槽复用递进到非零 generation。
- 单个 unload 在引用非零时返回 `REJECTED` 且不调用 unregister、不关闭库。`unload_all` 在任何回调之前预检全部插件，只要一个被引用就整体拒绝。
- destroy 先执行同样的引用预检，再逆序卸载并释放 manager；存在引用时 manager 保持可用。
- 回调期间 manager 拒绝重入生命周期操作，防止注册顺序被重入改变。管理器只由创建线程使用。

## 4. 验证入口

- focused：`test_break_cvar`、`test_break_xml`、`test_break_plugin`、`test_break_system_target_contract`。
- 相关既有回归：`test_platform_fs_write`、`test_scene_serial`、`test_break_integrity`。
- 五套真实 CMake `SHARED` fixture 分别覆盖正常 A/B、bad ABI、register failure、no entry。测试现场计算实际文件 SHA-256，并验证错误 digest 和追加字节的副本在加载前被拒绝。
- normal、ASan+UBSan、TSan 命令与最终通过数见 `.superpowers/sdd/system-extensions-report.md`。Linux 之外的 PAL 分支尚未在本机执行；Windows 结果不提前声称。
