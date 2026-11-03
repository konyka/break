# System Extensions Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [x]`) syntax for tracking.

**Goal:** 交付 P11 的固定容量注册式 CVar、有界 XML 与明确场景侧车，以及经 PAL 加载、哈希 allowlist 控制的真实动态插件生命周期。

**Architecture:** 新增独立 `break_system` 静态库，不修改或链入 `engine`。CVar 在创建时分配主/暂存表，配置加载先写入暂存表，完整验证后交换并回调。XML 在创建时分配主/暂存树与字符 arena，以索引表示节点，解析成功才交换；场景侧车是 `break-scene` v1 的有限实体身份/类名映射。插件管理器固定槽位与 load-order 数组，加载前复用 `break_integrity` 的流式 SHA-256 文件检查，再经新 PAL 打开真实共享库；注册/卸载由显式顺序与 generation 句柄约束。

**Tech Stack:** C11、现有 `core/types.h`、CTest、`test_framework.h`、现有 `platform_fs` 原子写、`break_integrity`/`break_crypto`、POSIX `dlopen` 与 Win32 `LoadLibraryA`、真实 CMake `SHARED` 测试库。

## Global Constraints

- 遵循 `docs/superpowers/specs/2026-11-02-cry-capability-completion-design.md` 第 4、5、6、8 节，特别是 C11、固定容量、失败原子、无新依赖和真实 RED→GREEN。
- 只在 `.worktrees/cry-system` 的 `cry-wave2-system` 分支提交；不改 master、其它子项目，不 push。
- 每个行为测试必须因目标行为缺失而失败；编译/链接缺失只用于首次启动 RED，随后至少保留一个运行期行为 RED。每项至少做一次能杀死关键防护的变异并恢复复测。
- 热路径不分配；create 后的 register/set/parse/serialize/acquire/release/unload 不扩容。超限返回 `OVERLOAD`，非法输入返回 `INVALID`，失效插件句柄返回 `STALE`，权限或仍被引用返回 `REJECTED`。
- `break_system` 在 `ENGINE_BUILD_TESTS=OFF` 时仍生成；不链入 `engine`、`engine_demo`、`dxx_break`、`editor`。现有 `engine` 保持 `platform_fs.c` 的唯一生产 owner；CVar 文件 API 的消费者沿用现有静态库先例提供该 PAL，测试目标内联编译它，避免重复定义。
- XML 不是 BSCN 的无损替代；不支持 DTD、自定义/数值实体、CDATA 或混合声明。仅五个预定义 XML 实体被解码。非法 UTF-8、NUL、XML 禁止控制字符、重复属性、多根、深度/大小/节点/属性/arena 超限全部拒绝。
- 插件哈希 allowlist 是完整性门，不是签名、发布者认证或权限边界；本地攻击者可改 allowlist，路径在哈希与加载间被替换的 TOCTOU 以及未逐项验证的依赖库均在文档中明确保留。

---

### Task 1: 注册式 CVar 与事务式配置存取

**Files:**
- Create: `engine/src/system/break_cvar.h`
- Create: `engine/src/system/break_cvar.c`
- Create: `engine/tests/test_break_cvar.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**

```c
#define BREAK_CVAR_NAME_CAPACITY 64u
#define BREAK_CVAR_STRING_CAPACITY 128u
#define BREAK_CVAR_CONFIG_MAX_BYTES (64u * 1024u)

typedef enum BreakCVarStatus {
    BREAK_CVAR_OK = 0, BREAK_CVAR_INVALID, BREAK_CVAR_OVERLOAD,
    BREAK_CVAR_OOM, BREAK_CVAR_REJECTED, BREAK_CVAR_FAILED
} BreakCVarStatus;
typedef enum BreakCVarType {
    BREAK_CVAR_BOOL = 1, BREAK_CVAR_INT, BREAK_CVAR_FLOAT, BREAK_CVAR_STRING
} BreakCVarType;
enum { BREAK_CVAR_READONLY = 1u << 0, BREAK_CVAR_CHEAT = 1u << 1 };
typedef union BreakCVarValue {
    bool boolean; i64 integer; f64 number; const char *string;
} BreakCVarValue;
typedef struct BreakCVarRegistry BreakCVarRegistry;
typedef void (*BreakCVarChangedFn)(const char *name, void *user);
typedef struct BreakCVarDesc {
    const char *name;
    BreakCVarType type;
    u32 flags;
    BreakCVarValue default_value;
    i64 min_integer, max_integer;
    f64 min_number, max_number;
    BreakCVarChangedFn changed;
    void *changed_user;
} BreakCVarDesc;

BreakCVarRegistry *break_cvar_create(u32 capacity);
void break_cvar_destroy(BreakCVarRegistry *registry);
BreakCVarStatus break_cvar_register(BreakCVarRegistry *registry,
                                    const BreakCVarDesc *desc);
BreakCVarStatus break_cvar_get(const BreakCVarRegistry *registry,
                               const char *name, BreakCVarType type,
                               BreakCVarValue *out_value);
BreakCVarStatus break_cvar_set(BreakCVarRegistry *registry, const char *name,
                               BreakCVarValue value, bool allow_cheat);
BreakCVarStatus break_cvar_load(BreakCVarRegistry *registry, const char *path,
                                bool allow_cheat);
BreakCVarStatus break_cvar_save(const BreakCVarRegistry *registry,
                                const char *path);
```

- [x] **Step 1: 注册 CMake 行为测试并写 RED**

注册四种类型，覆盖重复/非法名字、容量满、默认值越界、非有限浮点、字符串过长；覆盖 int/float 范围、类型不匹配、readonly、cheat 权限和变更回调恰好一次。核心断言：

```c
BreakCVarValue value = { .integer = 11 };
ASSERT_EQ(break_cvar_set(registry, "actor.speed", value, false), BREAK_CVAR_OK);
ASSERT_EQ(break_cvar_get(registry, "actor.speed", BREAK_CVAR_INT, &value), BREAK_CVAR_OK);
ASSERT_EQ(value.integer, 11);
value.integer = 21;
ASSERT_EQ(break_cvar_set(registry, "actor.speed", value, false), BREAK_CVAR_OVERLOAD);
ASSERT_EQ(callback_count, 1u);
```

先让目标编译但链接缺少实现，再提供最小声明/空实现以观察上述运行期断言失败。

- [x] **Step 2: 运行 CVar RED**

Run: `cmake -S engine -B build-system-normal -DENGINE_BUILD_TESTS=ON && cmake --build build-system-normal -j6 --target test_break_cvar && ./build-system-normal/test_break_cvar`
Expected: 首次链接失败；最小实现落地后测试运行并因范围、权限或回调行为不满足而 FAIL，记录实际断言。

- [x] **Step 3: 实现固定容量注册、校验、存取与回调**

创建时一次分配两个 `BreakCVarEntry[capacity]` 和 64 KiB+1 配置缓冲；entry 内嵌名字和字符串值。所有字符串用有界长度检查。注册完整验证 desc 后才占槽。set 先找项、校验类型/权限/范围/UTF-8 与字符串容量，成功后写值并同步调用回调；回调期间拒绝重入写。get 的字符串指针只保证到下一次写或 destroy。

- [x] **Step 4: 为配置原子性写第二个 RED→GREEN 循环**

配置语法为每行 `name=value`，允许空行与以 `#` 开头的注释；trim 名字和值两侧 ASCII 空白，重复/未知名字、readonly 项、无权限 cheat、非法值、NUL、超过 64 KiB 或超过一行的缓冲边界均失败。保存跳过 readonly，使用 `PlatformAtomicWriter`，canonical 格式为 bool `true/false`、int 十进制、float `%.17g`、string 原始单行值。

先写事务测试：已有 speed=11、volume=0.5；文件把 speed 改成 20 后携带非法 volume，load 必须失败且 speed/callback 不变。合法文件含 string/bool/int/float 时全部更新，save→新 registry→load 后值相同。写入 `/dev/full` 或不可提交路径在 POSIX 返回失败；已存在配置在失败前不被替换。

```c
ASSERT_EQ(break_cvar_load(registry, bad_path, false), BREAK_CVAR_INVALID);
ASSERT_EQ(break_cvar_get(registry, "actor.speed", BREAK_CVAR_INT, &value), BREAK_CVAR_OK);
ASSERT_EQ(value.integer, 11);
ASSERT_EQ(callback_count, 0u);
```

- [x] **Step 5: 验证 GREEN、变异并提交**

Run: `./build-system-normal/test_break_cvar && ctest --test-dir build-system-normal -R 'break_cvar|platform_fs_write' --output-on-failure`
Expected: 全通过。临时删除 int 范围检查，确认越界与失败原子断言变红；恢复后复测。再临时让 load 直接写主表，确认中途失败留下 20 的测试变红；恢复复测。

```bash
git add engine/CMakeLists.txt engine/src/system/break_cvar.* engine/tests/test_break_cvar.c
git commit -m "system: add transactional registered cvars"
```

### Task 2: 有界 XML 与 break-scene v1 场景侧车

**Files:**
- Create: `engine/src/system/break_xml.h`
- Create: `engine/src/system/break_xml.c`
- Create: `engine/tests/test_break_xml.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**

```c
#define BREAK_XML_NONE UINT32_MAX
#define BREAK_XML_HARD_MAX_INPUT_BYTES (1024u * 1024u)
#define BREAK_XML_HARD_MAX_NODES 1024u
#define BREAK_XML_HARD_MAX_ATTRIBUTES 2048u
#define BREAK_XML_HARD_MAX_DEPTH 64u
#define BREAK_XML_HARD_MAX_TEXT_BYTES (1024u * 1024u)
typedef enum BreakXmlStatus {
    BREAK_XML_OK = 0, BREAK_XML_INVALID, BREAK_XML_OVERLOAD,
    BREAK_XML_OOM, BREAK_XML_FAILED
} BreakXmlStatus;
typedef enum BreakXmlNodeKind { BREAK_XML_ELEMENT = 1, BREAK_XML_TEXT } BreakXmlNodeKind;
typedef struct BreakXmlLimits {
    u32 max_input_bytes, max_nodes, max_attributes, max_depth, max_text_bytes;
} BreakXmlLimits;
typedef struct BreakXmlDocument BreakXmlDocument;

BreakXmlDocument *break_xml_create(const BreakXmlLimits *limits);
void break_xml_destroy(BreakXmlDocument *document);
BreakXmlStatus break_xml_parse(BreakXmlDocument *document,
                               const void *data, usize size);
BreakXmlStatus break_xml_serialize(const BreakXmlDocument *document,
                                   char *out, usize capacity, usize *out_size);
u32 break_xml_root(const BreakXmlDocument *document);
BreakXmlNodeKind break_xml_kind(const BreakXmlDocument *document, u32 node);
const char *break_xml_name(const BreakXmlDocument *document, u32 node);
const char *break_xml_text(const BreakXmlDocument *document, u32 node);
u32 break_xml_first_child(const BreakXmlDocument *document, u32 node);
u32 break_xml_next_sibling(const BreakXmlDocument *document, u32 node);
u32 break_xml_attribute_count(const BreakXmlDocument *document, u32 node);
bool break_xml_attribute(const BreakXmlDocument *document, u32 node, u32 index,
                         const char **out_name, const char **out_value);

typedef struct BreakSceneXmlEntity {
    u32 index, generation;
    char class_name[64];
} BreakSceneXmlEntity;
BreakXmlStatus break_scene_xml_read(const BreakXmlDocument *document,
                                    BreakSceneXmlEntity *out, u32 capacity,
                                    u32 *out_count);
BreakXmlStatus break_scene_xml_write(const BreakSceneXmlEntity *entities,
                                     u32 count, char *out, usize capacity,
                                     usize *out_size);
```

- [x] **Step 1: 写 XML 语法、安全边界和原子性 RED**

用小 limits 创建真实 document。解析 `<root a="1"><child/>text &amp; more</root>`，检查树、属性、文本和 serialize→parse 往返。分别拒绝 DTD、`<!ENTITY`、未知实体、数值实体、非法/截断/过长 UTF-8、surrogate、NUL、重复属性、多根、未闭合/错配标签、深度+1、输入+1、节点+1、属性+1、arena+1。先成功解析 old 文档，再失败解析新文档，root 仍必须指向 old。

```c
const char bad[] = "<!DOCTYPE root [<!ENTITY x \"boom\">]><root>&x;</root>";
ASSERT_EQ(break_xml_parse(doc, bad, sizeof(bad) - 1u), BREAK_XML_INVALID);
ASSERT_STR_EQ(break_xml_name(doc, break_xml_root(doc)), "old");
```

- [x] **Step 2: 运行 XML RED**

Run: `cmake --build build-system-normal -j6 --target test_break_xml && ./build-system-normal/test_break_xml`
Expected: 最小空实现下往返/拒绝断言运行期失败；不能只记录头文件或符号缺失。

- [x] **Step 3: 实现非递归有界解析与序列化**

创建时为主/暂存 storage 分配 node、attribute、字符 arena。UTF-8 validator 覆盖 overlong、surrogate、>U+10FFFF 与截断序列；XML 字符检查拒绝 NUL 和除 TAB/LF/CR 外 C0 控制字符。解析只接受单/双引号属性、五个预定义实体、注释和 `<?...?>`；其它 `<!...` 拒绝。当前 element 索引提供父栈，close tag 与当前名字精确比较，不用递归。所有复制先检查 arena 与 NUL 空间；成功后交换 active/scratch。serializer 对 `& < > " '` 正确转义，容量不足返回 `OVERLOAD` 且 `out_size=0`。

- [x] **Step 4: 写场景侧车 RED→GREEN**

`break-scene` v1 只含 `<entity index="positive-decimal" generation="positive-decimal" class="..."/>`。class 为 1..63 字节 ASCII 标识符 `[A-Za-z_][A-Za-z0-9_.-]*`；拒绝未知元素/属性、非空 entity 内容、零/溢出整数和重复 `(index,generation)`。read 先验证整份再写 out；`out_count` 是总量，超过 cap 返回 `OVERLOAD` 且不改 out。write 产生上述 canonical XML，并可由通用 parser + sidecar reader 读回。

```c
BreakSceneXmlEntity rows[2] = {{1u, 7u, "Player"}, {8u, 2u, "Enemy.Grunt"}};
ASSERT_EQ(break_scene_xml_write(rows, 2u, xml, sizeof(xml), &written), BREAK_XML_OK);
ASSERT_EQ(break_xml_parse(doc, xml, written), BREAK_XML_OK);
ASSERT_EQ(break_scene_xml_read(doc, loaded, 2u, &count), BREAK_XML_OK);
ASSERT_EQ(count, 2u);
ASSERT_STR_EQ(loaded[1].class_name, "Enemy.Grunt");
```

- [x] **Step 5: 验证 GREEN、变异并提交**

Run: `./build-system-normal/test_break_xml && ctest --test-dir build-system-normal -R 'break_xml|scene_serial' --output-on-failure`
Expected: 全通过，BSCN 既有测试不回归。分别删除 DTD 拒绝与 UTF-8 检查，确认对应测试变红；恢复后复测。再临时移除解析成功才交换，确认旧文档保持测试变红。

```bash
git add engine/CMakeLists.txt engine/src/system/break_xml.* engine/tests/test_break_xml.c
git commit -m "system: add bounded XML scene sidecars"
```

### Task 3: PAL 动态加载与受控插件生命周期

**Files:**
- Create: `engine/src/platform/platform_dynamic.h`
- Create: `engine/src/platform/platform_dynamic.c`
- Create: `engine/src/system/break_plugin.h`
- Create: `engine/src/system/break_plugin.c`
- Create: `engine/tests/fixtures/break_system_test_plugin.c`
- Create: `engine/tests/fixtures/break_system_test_plugin.h`
- Create: `engine/tests/test_break_plugin.c`
- Create: `engine/tests/test_break_system_target_contract.cmake`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**

```c
typedef struct PlatformDynamicLibrary PlatformDynamicLibrary;
PlatformDynamicOpenStatus platform_dynamic_open_verified(
    const char *path, const u8 expected_sha256[32],
    PlatformDynamicLibrary **out_library);
void *platform_dynamic_symbol(PlatformDynamicLibrary *library, const char *name);
void platform_dynamic_close(PlatformDynamicLibrary *library);

#define BREAK_PLUGIN_ABI_VERSION 1u
#define BREAK_PLUGIN_ENTRY_SYMBOL "break_plugin_entry"
typedef bool (*BreakPluginRegisterFn)(void *user);
typedef void (*BreakPluginUnregisterFn)(void *user);
typedef struct BreakPluginDescriptor {
    u32 struct_size, abi_version;
    const char *name, *build_id;
    BreakPluginRegisterFn register_fn;
    BreakPluginUnregisterFn unregister_fn;
} BreakPluginDescriptor;
typedef struct BreakPluginHandle { u32 index, generation; } BreakPluginHandle;
typedef enum BreakPluginStatus {
    BREAK_PLUGIN_OK = 0, BREAK_PLUGIN_INVALID, BREAK_PLUGIN_OVERLOAD,
    BREAK_PLUGIN_OOM, BREAK_PLUGIN_STALE, BREAK_PLUGIN_REJECTED,
    BREAK_PLUGIN_FAILED
} BreakPluginStatus;
typedef struct BreakPluginManager BreakPluginManager;
BreakPluginManager *break_plugin_create(u32 capacity, void *plugin_user);
BreakPluginStatus break_plugin_destroy(BreakPluginManager *manager);
BreakPluginStatus break_plugin_load(BreakPluginManager *manager,
                                    const char *path, const char *build_id,
                                    const u8 expected_sha256[32],
                                    BreakPluginHandle *out_handle);
BreakPluginStatus break_plugin_acquire(BreakPluginManager *manager,
                                       BreakPluginHandle handle);
BreakPluginStatus break_plugin_release(BreakPluginManager *manager,
                                       BreakPluginHandle handle);
BreakPluginStatus break_plugin_unload(BreakPluginManager *manager,
                                      BreakPluginHandle handle);
BreakPluginStatus break_plugin_unload_all(BreakPluginManager *manager);
```

插件导出 `const BreakPluginDescriptor *break_plugin_entry(void)`。`struct_size` 必须精确等于当前描述符大小；名字 1..63、build id 1..63 字节且与 allowlist 项精确相等；register/unregister 可为空，但 register 存在时返回 false 表示它已自行清理，manager 不保留槽或库。管理器只由创建线程使用。

- [x] **Step 1: 构建真实 SHARED fixture 并写插件 RED**

CMake 从同一 C fixture 生成 A、B、bad-ABI、register-fail、no-entry 等真实共享库；A/B 通过编译定义拥有不同名字、build id 与事件 id。fixture 回调向宿主固定数组追加事件。测试运行时用 `break_crypto_sha256` 读取并哈希目标文件，构造 allowlist；错误 hash 和篡改副本必须在 `dlopen` 前拒绝。bad ABI/build id/缺 entry/register fail 均不保留活动槽。加载 A→B 后事件为 register A/B，acquire A 后 unload A 返回 `REJECTED` 且无 unregister；release 后成功，stale handle 返回 `STALE`。`unload_all` 必须预检全部引用并严格按 load 逆序产生 unregister B/A。

```c
ASSERT_EQ(break_plugin_load(manager, plugin_a, "system-test-a", digest_a, &a), BREAK_PLUGIN_OK);
ASSERT_EQ(break_plugin_acquire(manager, a), BREAK_PLUGIN_OK);
ASSERT_EQ(break_plugin_unload(manager, a), BREAK_PLUGIN_REJECTED);
ASSERT_EQ(log_count, 1u);
ASSERT_EQ(break_plugin_release(manager, a), BREAK_PLUGIN_OK);
ASSERT_EQ(break_plugin_unload(manager, a), BREAK_PLUGIN_OK);
ASSERT_EQ(break_plugin_unload(manager, a), BREAK_PLUGIN_STALE);
```

- [x] **Step 2: 运行真实插件 RED**

Run: `cmake --build build-system-normal -j6 --target test_break_plugin && ./build-system-normal/test_break_plugin`
Expected: 真实 `.so` 已由 CMake 编译；最小 manager 实现未满足 ABI/hash/ref/order 时相应运行期断言失败。保留构建日志和失败断言作为 RED，不用伪造 dlopen。

- [x] **Step 3: 实现 PAL 与事务式管理器**

PAL 以同一 `platform_dynamic_open_verified` 原语验证并加载：Linux 使用 sealed memfd 的 `/proc/self/fd` 对象，Windows 在禁止写/删除共享的源句柄上哈希并通过最终路径 `LoadLibraryA`；其它平台失败关闭。符号经 `memcpy` 转为函数指针并检查表示大小。manager 先验证参数、空槽和重复 path，再调用 PAL、检查 entry/descriptor/build/name，最后调用 register 并提交 slot 与 load-order；任何失败关闭库且 out handle 清零。slot generation 单调非零且耗尽后永久退休，引用溢出/零下溢均拒绝。unload_all 在任何 unregister 前检查所有引用，然后逆序卸载；destroy 只对无引用管理器执行 unload_all 并释放，否则返回 `REJECTED`。

- [x] **Step 4: 验证 GREEN、真实库变异与 target contract**

Run: `./build-system-normal/test_break_plugin && ./build-system-normal/test_break_system_target_contract`
Expected: 真实共享库加载/卸载全通过。临时跳过哈希比较调用，确认错误 digest 测试变红；恢复。临时删除引用检查，确认被引用卸载测试变红并恢复。临时把 unload_all 改为正序，确认事件序列断言变红并恢复。contract 检查 `break_system` 独立、C11、源清单、crypto/integrity 链接、focused 注册与核心目标 no-link。

```bash
git add engine/CMakeLists.txt engine/src/platform/platform_dynamic.* engine/src/system/break_plugin.* engine/tests/fixtures/break_system_test_plugin.* engine/tests/test_break_plugin.c engine/tests/test_break_system_target_contract.cmake
git commit -m "system: load allowlisted plugins through PAL"
```

### Task 4: 文档、全量相关回归与报告

**Files:**
- Create: `docs/design/system_extensions.md`
- Modify: `docs/design/cry_style_gameplay.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/superpowers/plans/2026-11-03-system-extensions.md`
- Create: `.superpowers/sdd/system-extensions-report.md`

**Interfaces:**
- Consumes: Task 1–3 的公开 API、CTest 结果、真实变异日志。
- Produces: 可复核的 P11 交付说明、测试证据、提交列表与限制；不虚称签名认证、Windows 运行、无损 BSCN 或热卸载被引用插件。

- [x] **Step 1: 更新设计、状态和计划勾选**

`system_extensions.md` 写明配置文法、XML 子集与硬上限、场景 schema、ABI/哈希/生命周期、线程归属、PAL 链接所有权和安全边界。`cry_style_gameplay.md` 将 P11 从待办改为已交付并链接设计；`Implementation_Status.md` 顶部追加真实测试数量与限制。只勾选已执行的步骤。

- [x] **Step 2: 配置并运行 normal / ASan+UBSan / TSan focused**

Run: 三棵树分别构建 `test_break_cvar test_break_xml test_break_plugin test_break_system_target_contract`，再运行 `ctest -R 'break_(cvar|xml|plugin|system)|scene_serial|platform_fs_write|break_integrity' --output-on-failure`。
Expected: 三树全通过，无 ASan/UBSan/TSan 报告；真实 SHARED fixture 在每棵树重新编译并加载。

- [x] **Step 3: 运行全量相关非图形回归**

Run: 三棵树 `ctest -L headless --output-on-failure -j6`；若某项依赖本机外部可选源码或图形环境，保留原始失败并用相同 base 对照，不把它掩盖为通过。另跑 `test_scene_serial` 与 target no-tests 构建 `cmake -S engine -B build-system-no-tests -DENGINE_BUILD_TESTS=OFF && cmake --build build-system-no-tests --target break_system`。
Expected: 新增与既有相关回归全通过；no-tests 树仍产出 `break_system`，且不链入核心目标。

- [x] **Step 4: 最终审计与提交**

Run: `git diff --check && git status --short --branch && git log --oneline a0bfeb95..HEAD`。
Expected: 无 whitespace 错误、无未提交源文件；报告含每个 RED→GREEN、变异、命令/通过数、每个提交 hash、未运行平台和安全限制。文档与报告单独提交：

```bash
git add docs .superpowers/sdd/system-extensions-report.md
git commit -m "docs: record P11 system extension evidence"
```

---

### Task 5: Independent review fix round 1

**Files:**
- Modify: `engine/src/platform/platform_dynamic.{h,c}`
- Modify: `engine/src/system/break_{cvar,xml,plugin}.{c,h}`
- Modify: `engine/tests/test_break_{cvar,xml,plugin}.c`
- Modify: `engine/tests/fixtures/break_system_test_plugin.c`
- Modify: `engine/tests/test_break_system_target_contract.cmake`
- Modify: `docs/design/system_extensions.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `.superpowers/sdd/system-extensions-report.md`

- [x] **Step 1: Close the verified-object replacement race**

RED: a test-only post-verify/pre-open hook replaced the path; the old loader executed the attack library constructor and `file_exists(marker)` failed the test. GREEN: PAL hashes into sealed memfd and loads only that object on Linux; Windows hashes and loads under a no-write/no-delete-share handle and final path, other platforms fail closed. The verified fd stays alive until unload after existing A→B tests exposed path reuse. The race now loads approved code and never creates the attack marker.

- [x] **Step 2: Fix CVar lifetime and string ownership**

RED: ASan reported set-callback destroy UAF and `memcpy-param-overlap`; normal tests accepted a leading-space string that could not roundtrip. GREEN: defer destroy to outer notification end, allow both set/load callback destruction, reject leading/trailing spaces while preserving empty/internal-space strings, and use `memmove` for aliased current-value pointers.

- [x] **Step 3: Retire exhausted plugin identities**

RED: a bounded `UINT32_MAX-1` fixture let the third load wrap to generation 1 instead of returning `OVERLOAD`. GREEN: permanently retire the exhausted slot and prove the oldest handle stays `STALE`.

- [x] **Step 4: Close XML output, character and traversal contracts**

RED: 683 entities were serialized despite exceeding the parser's global attribute cap; U+FFFE was accepted; source contract found recursive serializer calls. GREEN: 682 roundtrips and 683 fails before output mutation, XML 1.0 codepoint validation rejects U+FFFE/U+FFFF atomically, parent-index iterative serialization preserves depth-64 output, and report trailing whitespace is removed.

- [x] **Step 5: Run final regression and commit**

Run normal/ASan+UBSan/TSan focused and full headless suites, no-tests target build, `git diff --check a0bfeb95..HEAD`, then commit the implementation and evidence without pushing.

---

### Task 6: Independent review fix round 2

- [x] **Step 1: Distinguish overload from I/O failure**

RED: a 64 MiB+1 sparse file returned `BREAK_PLUGIN_FAILED` instead of `BREAK_PLUGIN_OVERLOAD`. GREEN: `PLATFORM_DYNAMIC_OPEN_OVERLOAD` covers initial and cumulative size overflow on Linux/Windows and maps to `BREAK_PLUGIN_OVERLOAD`; missing files remain `FAILED`.

- [x] **Step 2: Exercise unsupported platforms without weakening assertions**

RED: a simulated unsupported target loaded the attack library and created its constructor marker. GREEN: successful fixtures register only on Linux/Windows, while `test_break_plugin_unsupported` always asserts `FAILED`, zero output handle, zero registration and zero constructor side effects.

- [x] **Step 3: Verify and document**

normal/ASan+UBSan/TSan focused suites each pass 8/8. Design, status and report describe overload mapping, platform gating and exact evidence. Run `git diff --check` and commit without pushing.

---

### Task 7: Independent review fix round 3

- [x] **Step 1: Pin both Windows preprocessor gates**

RED: `DYNAMIC_SOURCE` contract found the Windows loader and dispatcher lacked `!BREAK_SYSTEM_TEST_UNSUPPORTED`. GREEN: only those two `#elif` branches now carry the guard.

- [x] **Step 2: Cross-compile real Windows objects**

zig 0.16.0 `x86_64-windows-gnu` compiles production and test-unsupported objects with warnings as errors. production nm contains `platform_open_windows`; unsupported nm omits it. A public fail-closed probe links as a Windows executable. No Windows runtime was available or claimed.

- [x] **Step 3: Verify and document**

Linux normal/ASan+UBSan/TSan focused suites each pass 8/8. Update design, status, plan and report; run `git diff --check` and commit without pushing.
